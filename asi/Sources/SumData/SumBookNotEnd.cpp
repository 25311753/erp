//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <assert.h>
#pragma hdrstop

#include "DataModule.h"
#include "BaseCode.h"
#include "SumBookNotEnd.h"
#include "TConst.h"
#include "LdyInterface.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSumBookNotEndForm *SumBookNotEndForm;
//---------------------------------------------------------------------------

//--------------------------------------------------------------------------
//订购逾期未完成案件统计表接口，文件：SumBookNotEnd.*
void SumBookNotEnd(int nAuth)
{
	CALL_FORM(TSumBookNotEndForm);
}
//-------------------------------------------------------------------------

__fastcall TSumBookNotEndForm::TSumBookNotEndForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TSumBookNotEndForm::btnExitClick(TObject *Sender)
{
	Close();	
}
//---------------------------------------------------------------------------

void __fastcall TSumBookNotEndForm::btnToExcelClick(TObject *Sender)
{
	Variant vExcel,vSheet;
  int nRow,i;
  TListItem *pItem;

  try
  {
	  nRow=1;
		if(!OpenExcel("列表.xls",vExcel,vSheet))	return;
		ListHead2Excel(lstView,vSheet,nRow++);
		for(i=0;i<lstView->Items->Count;i++)
    {
    	pItem=lstView->Items->Item[i];
      InsertExcelItem(vSheet,nRow++,
      	pItem->Caption.c_str(),
        pItem->SubItems->Strings[0].c_str(),
        pItem->SubItems->Strings[1].c_str(),
        pItem->SubItems->Strings[2].c_str(),
        pItem->SubItems->Strings[3].c_str(),
        pItem->SubItems->Strings[4].c_str(),
        pItem->SubItems->Strings[5].c_str(),
        pItem->SubItems->Strings[6].c_str(),
        pItem->SubItems->Strings[7].c_str(),
        pItem->SubItems->Strings[8].c_str(),
        pItem->SubItems->Strings[9].c_str(),
				NULL);
		}
	}
	catch(...)
	{
	}
}
//---------------------------------------------------------------------------

#include "PrnSumNotEnd.h"
void __fastcall TSumBookNotEndForm::btnPrintClick(TObject *Sender)
{
	CString szSQL,szTable;
	TPrnSumNotEndForm *pPrn;
	TListItem *pItem;
	int i;
	TDateTime tNow;

	szTable=GetTmpTableName();
	try
	{
		BeginTransact();
		szSQL.Format("create table dbo.%s ("
                        "m_id   varchar(80),"
			"m_sh   varchar(80),"
			"m_corp varchar(80),"
			"m_ap   varchar(80),"
                        "m_afd  varchar(80),"
			"m_type varchar(80),"
			"m_mnname varchar(80),"
                        "m_mfsname varchar(80),"
			"m_count varchar(80),"
			"m_hm   varchar(80),"
			"m_date varchar(80),"
			"m_money varchar(80)"
			")",szTable);
		RunTransactSQL(szSQL);

		for(i=0;i<lstView->Items->Count;i++)
		{
			pItem=lstView->Items->Item[i];
			szSQL.Format("insert into %s values(",szTable);
     			szSQL+=Int2DBString(i+1);
                     	szSQL+=",";	szSQL+=Str2DBString(pItem->Caption.c_str());
			szSQL+=",";	szSQL+=Str2DBString(pItem->SubItems->Strings[0].c_str());
			szSQL+=",";	szSQL+=Str2DBString(pItem->SubItems->Strings[1].c_str());
			szSQL+=",";	szSQL+=Str2DBString(pItem->SubItems->Strings[2].c_str());
			szSQL+=",";	szSQL+=Str2DBString(pItem->SubItems->Strings[3].c_str());
			szSQL+=",";	szSQL+=Str2DBString(pItem->SubItems->Strings[4].c_str());
			szSQL+=",";	szSQL+=Str2DBString(pItem->SubItems->Strings[5].c_str());
			szSQL+=",";	szSQL+=Str2DBString(pItem->SubItems->Strings[6].c_str());
			szSQL+=",";	szSQL+=Str2DBString(pItem->SubItems->Strings[7].c_str());
			szSQL+=",";	szSQL+=Str2DBString(pItem->SubItems->Strings[8].c_str());
			szSQL+=",";	szSQL+=Str2DBString(pItem->SubItems->Strings[9].c_str());                        
			szSQL+=")";
			RunTransactSQL(szSQL);
		}
		CommitTransact();
	}
	catch(...)
	{
		RollBackTransact();
		ShowMessage("数据库操作异常");
		return;
	}

	pPrn=new TPrnSumNotEndForm(this);
	assert(pPrn!=NULL);

	tNow=GetSysTime(false);

	pPrn->txtPrnTime->Caption=(LPCSTR)Time2DBTimeString(tNow);
	pPrn->txtDate->Caption="呈核日";
        if(!m_bMonth)
        {
                pPrn->txtTitle->Caption="逾期未订购案件周报表(催办单)";
                pPrn->QRLabel12->Caption="逾时说明";
                pPrn->QRLabel17->Caption="说明: 未订购的案件若其订购最後限期在统计范围之内就被视为逾期";
                pPrn->QRLabel19->Caption="      一般件:订购最後限期=呈核日+6  急件:订购最後限期=呈核日+2";
        }
        else
        {
                pPrn->txtTitle->Caption="订购逾期案件月报明细";
                pPrn->QRLabel12->Caption="备注";
                pPrn->QRLabel17->Caption="说明: 逾期案件是指 订购最後限期在统计范围之内并且订购最後限期<实际订购日";
                pPrn->QRLabel19->Caption="      一般件:订购最後限期=呈核日+6  急件:订购最後限期=呈核日+2";
        }
//	pPrn->txtTitle->Caption="订购逾期未完成案件统计表";

	szSQL.Format("select * from %s",szTable);
	OpenQuery(dm1->sqlPrint,szSQL);
	pPrn->PrnView->PreviewModal();
	delete pPrn;

DROP_TABLE:
	szSQL.Format("drop table %s",szTable);
	RunSQL(dm1->Query1,szSQL);
}
//---------------------------------------------------------------------------
void __fastcall TSumBookNotEndForm::btnQueryClick(TObject *Sender)
{
	CString szSQL;
	TListItem *pItem;
	TDateTime tNow;
	char strCorp[80],strFact[80],strTemp[256],strTemp2[256],strDate0[80],strDate1[80],strSHID[256],strID[80];
	CArray<BASE2COLDATA,BASE2COLDATA>lstHM,lstSH;
	BASE2COLDATA rwData;
	int i,nSel;
        int nRightSH,nRightRP;
        unsigned short year0,month0,day0,year1,month1,day1;
//---------- new 0711---取得操作者对应的采购部门别(在StockHandleman中的公司别) 与相应权限-srtSHID-------
        szSQL.Format("select * from StockHandleman where sh_code='%s'",operatorcode);
        RunSQL(dm1->Query1,szSQL,true);
        strcpy(strSHID,dm1->Query1->FieldByName("sh_sdcode")->AsString.c_str());
        nRightSH=GetOperatorRight(operatorcode.c_str(),"IDM_PRSHLPRICE");            //取得权限
        nRightRP=GetOperatorRight(operatorcode.c_str(),"IDM_RAWPRICERIGHT");            //取得权限
//------------------------------------------------------------------------------
//	tNow=GetSysTime(false);
//	tNow -= atoi(edtDays->Text.c_str());

	szSQL="select * from HandleMan order by hm_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		strcpy(rwData.strCode,dm1->Query1->FieldByName("hm_code")->AsString.c_str());
		strcpy(rwData.strName,dm1->Query1->FieldByName("hm_name")->AsString.c_str());
		lstHM.Add(rwData);
		dm1->Query1->Next();
	}

	szSQL="select * from StockHandleman order by sh_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		strcpy(rwData.strCode,dm1->Query1->FieldByName("sh_code")->AsString.c_str());
		strcpy(rwData.strName,dm1->Query1->FieldByName("sh_name")->AsString.c_str());
		lstSH.Add(rwData);
		dm1->Query1->Next();
	}

	lstView->Items->Clear();
//---------周报-----------------------------------------------------------------
  if(!m_bMonth)
  {
	szSQL.Format("select * from DecideFactory,CompareFactory,AskPurchase,PurchaseDetail,materialno,Manufactur"
		" where pd_code=df_apcode"
		" and cf_apcode=pd_code"
                " and cf_mfcode=df_mfplan"                                      //new 0729找出拟购厂商
                " and df_mfplan=mf_code"
		" and ap_code=substring(pd_code,1,7)"
		" and mn_code=pd_mncode"
		" and df_apcode not in"
		"("
		"select distinct bf_apcode from BookFactory"                    //必未订购
		")"
                );
        DateTimePicker1->DateTime.DecodeDate(&year0,&month0,&day0);
        sprintf(strDate0,"%04d-%02d-%02d",year0,month0,day0);
        DateTimePicker2->DateTime.DecodeDate(&year1,&month1,&day1);
        sprintf(strDate1,"%04d-%02d-%02d",year1,month1,day1);
//		" and df_decidedate<'%s'",Time2DBDateString(tNow));
        sprintf(strTemp," and(((df_plandate+6 between '%s' and '%s') and ap_type='I') or ((df_plandate+2 between '%s' and '%s') and ap_type='N'))",strDate0,strDate1,strDate0,strDate1);    //呈核期限(ap_affirmdate+7或3)在统计范围内，则改案件被视为逾期
        szSQL+=strTemp;

	if((nSel=lstHandle->ItemIndex)>0 && nSel<m_lstHandleID.GetSize())
	{
		sprintf(strTemp," and ap_shcode='%s'",m_lstHandleID[nSel]);
		szSQL+=strTemp;
	}
	if((nSel=lstCorp->ItemIndex)>0 && nSel<m_lstCorpID.GetSize())
	{
		sprintf(strTemp," and substring(ap_reqdepart,1,2)='%s'",m_lstCorpID[nSel]);
		szSQL+=strTemp;
	}
	if((nSel=lstFactory->ItemIndex)>0 && nSel<m_lstFactID.GetSize())
	{
		sprintf(strTemp," and df_mfplan='%s'",m_lstFactID[nSel]);
		szSQL+=strTemp;
	}
	if((nSel=lstStockDepart->ItemIndex)>=0 && nSel<m_lstStockDepartID.GetSize())
	{
		sprintf(strTemp," and ap_sdcode='%s'",m_lstStockDepartID[nSel]);
		szSQL+=strTemp;
	}
	szSQL+=" order by ap_shcode,df_decidedate";
  }
//---------月报-----------------------------------------------------------------
  else
  {
	szSQL.Format("select * from DecideFactory,CompareFactory,AskPurchase,PurchaseDetail,materialno,Manufactur,BookFactory"
		" where pd_code=df_apcode"
		" and cf_apcode=pd_code"
                " and pd_code=bf_apcode"
                " and cf_mfcode=df_mfplan"                                      //new 0729找出拟购厂商
                " and df_mfplan=mf_code"                             
		" and ap_code=substring(pd_code,1,7)"
		" and mn_code=pd_mncode"
		" and df_apcode in"
		"("
		"select distinct bf_apcode from BookFactory"                    //必有订购
		")"
                " and((df_plandate+6<bf_bookdate and ap_type='I') or (df_plandate+2<bf_bookdate and ap_type='N'))"   //呈核最後限期<实际订购日
                );
        DateTimePicker1->DateTime.DecodeDate(&year0,&month0,&day0);
        sprintf(strDate0,"%04d-%02d-%02d",year0,month0,day0);
        DateTimePicker2->DateTime.DecodeDate(&year1,&month1,&day1);
        sprintf(strDate1,"%04d-%02d-%02d",year1,month1,day1);
//		" and df_decidedate<'%s'",Time2DBDateString(tNow));
        sprintf(strTemp," and(((df_plandate+6 between '%s' and '%s') and ap_type='I') or ((df_plandate+2 between '%s' and '%s') and ap_type='N'))",strDate0,strDate1,strDate0,strDate1);    //呈核期限(ap_affirmdate+7或3)在统计范围内，则改案件被视为逾期
        szSQL+=strTemp;

	if((nSel=lstHandle->ItemIndex)>0 && nSel<m_lstHandleID.GetSize())
	{
		sprintf(strTemp," and ap_shcode='%s'",m_lstHandleID[nSel]);
		szSQL+=strTemp;
	}
	if((nSel=lstCorp->ItemIndex)>0 && nSel<m_lstCorpID.GetSize())
	{
		sprintf(strTemp," and substring(ap_reqdepart,1,2)='%s'",m_lstCorpID[nSel]);
		szSQL+=strTemp;
	}
	if((nSel=lstFactory->ItemIndex)>0 && nSel<m_lstFactID.GetSize())
	{
		sprintf(strTemp," and df_mfplan='%s'",m_lstFactID[nSel]);
		szSQL+=strTemp;
	}
	if((nSel=lstStockDepart->ItemIndex)>=0 && nSel<m_lstStockDepartID.GetSize())
	{
		sprintf(strTemp," and ap_sdcode='%s'",m_lstStockDepartID[nSel]);
		szSQL+=strTemp;
	}
//	szSQL+=" order by ap_shcode,df_decidedate";
	szSQL+=" order by ap_shcode,pd_code";
  }

	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		pItem=lstView->Items->Add();
		assert(pItem!=NULL);
		strcpy(strTemp,dm1->Query1->FieldByName("ap_shcode")->AsString.c_str());
		for(i=0;i<lstSH.GetSize();i++)
		{
			if(strcmp(lstSH[i].strCode,strTemp)==0)
			{
				pItem->Caption=lstSH[i].strName;
				break;
			}
		}
//		pItem->Caption=dm1->Query1->FieldByName("sh_name")->AsString;
		strcpy(strCorp,dm1->Query1->FieldByName("ap_reqdepart")->AsString.c_str());
		strCorp[2]='\0';
		for(i=1;i<m_lstCorpID.GetSize();i++)
		{
			if(m_lstCorpID[i]==strCorp)
			{
				pItem->SubItems->Add(lstCorp->Items->Strings[i]);
				break;
			}
		}
		if(i==m_lstCorpID.GetSize())	pItem->SubItems->Add("");
		pItem->SubItems->Add(dm1->Query1->FieldByName("pd_code")->AsString);
		pItem->SubItems->Add(DateField2Text(dm1->Query1->FieldByName("ap_affirmdate")));
		pItem->SubItems->Add(dm1->Query1->FieldByName("ap_type")->AsString=="I" ? "紧急" : "普通");
		pItem->SubItems->Add(dm1->Query1->FieldByName("mn_name")->AsString);
                pItem->SubItems->Add(dm1->Query1->FieldByName("mf_shortname")->AsString);
		pItem->SubItems->Add(FloatField2String(dm1->Query1->FieldByName("cf_quotenum")));
		strcpy(strTemp,dm1->Query1->FieldByName("ap_hmcode")->AsString.c_str());
		for(i=0;i<lstHM.GetSize();i++)
		{
			if(strcmp(lstHM[i].strCode,strTemp)==0)
			{
				pItem->SubItems->Add(lstHM[i].strName);
				break;
			}
		}
		if(i==lstHM.GetSize())	pItem->SubItems->Add("");
		pItem->SubItems->Add(DateField2Text(dm1->Query1->FieldByName("df_plandate")));
                
	strcpy(strID,dm1->Query1->FieldByName("ap_sdcode")->AsString.c_str());
        strcpy(strTemp,dm1->Query1->FieldByName("mn_code")->AsString.c_str());

             if(operatorcode=="admin")
             {
                       pItem->SubItems->Add(dm1->Query1->FieldByName("cf_quoteprice")->AsString);
                       pItem->SubItems->Add(dm1->Query1->FieldByName("cf_higgleprice")->AsString);
             }
             else if(nRightSH==3)
             {
                if((dm1->Query1->FieldByName("ap_sdcode")->AsString=='2' || dm1->Query1->FieldByName("ap_sdcode")->AsString=='3') && strTemp[1]=='M')     //宏信宏纶的原料采购 //若有"采购经办间可互相查看"的权限，则经办间可以互相查看
                {
                        if(nRightRP!=3 && strcmp(strID,strSHID)!=0)
                        {
                                pItem->SubItems->Add("");
                        }
                        else
                        {
        		pItem->SubItems->Add((LPCSTR)Float2DBString(dm1->Query1->FieldByName("cf_quotenum")->AsFloat*dm1->Query1->FieldByName("cf_quoteprice")->AsFloat,2));
                        }

                }
                else
                {
                        if(strcmp(strID,strSHID)!=0)
                        {
                                pItem->SubItems->Add("");
                        }
                        else
                        {
        		pItem->SubItems->Add((LPCSTR)Float2DBString(dm1->Query1->FieldByName("cf_quotenum")->AsFloat*dm1->Query1->FieldByName("cf_quoteprice")->AsFloat,2));
                        }
                }
             }
             else
             {
                if((dm1->Query1->FieldByName("ap_sdcode")->AsString=='2' || dm1->Query1->FieldByName("ap_sdcode")->AsString=='3') && strTemp[1]=='M')                                                    //若有"采购经办间可互相查看"的权限，则经办间可以互相查看
                {
                        if(nRightRP!=3 && operatorcode!=dm1->Query1->FieldByName("ap_shcode")->AsString)
                        {
                                pItem->SubItems->Add("");
                        }
                        else
                        {
        		pItem->SubItems->Add((LPCSTR)Float2DBString(dm1->Query1->FieldByName("cf_quotenum")->AsFloat*dm1->Query1->FieldByName("cf_quoteprice")->AsFloat,2));
                        }

                }
                else
                {
                        if(operatorcode!=dm1->Query1->FieldByName("ap_shcode")->AsString)
                        {
                                pItem->SubItems->Add("");
                        }
                        else
                        {
        		pItem->SubItems->Add((LPCSTR)Float2DBString(dm1->Query1->FieldByName("cf_quotenum")->AsFloat*dm1->Query1->FieldByName("cf_quoteprice")->AsFloat,2));
                        }
                }
             }
//--------------new 0704--------------------------------------------------------
/*                strcpy(strTemp2,dm1->Query1->FieldByName("ap_sdcode")->AsString.c_str());
                if(g_theOperator.op_cpcode[0]!='E' && (strcmp(strTemp2,"2")==0 || strcmp(strTemp2,"3")==0))
                {
                        pItem->SubItems->Add("");
                }
                else
                {
        		pItem->SubItems->Add((LPCSTR)Float2DBString(dm1->Query1->FieldByName("cf_quotenum")->AsFloat*dm1->Query1->FieldByName("cf_quoteprice")->AsFloat,2));
                }       */
//------------------------------------------------------------------------------
/*		pItem=lstView->Items->Add();
		assert(pItem!=NULL);
		strcpy(strTemp,dm1->Query1->FieldByName("ap_shcode")->AsString.c_str());
		for(i=0;i<lstSH.GetSize();i++)
		{
			if(strcmp(lstSH[i].strCode,strTemp)==0)
			{
				pItem->Caption=lstSH[i].strName;
				break;
			}
		}
//		pItem->Caption=dm1->Query1->FieldByName("sh_name")->AsString;
		pItem->SubItems->Add(DateField2Text(dm1->Query1->FieldByName("df_decidedate")));
		pItem->SubItems->Add(dm1->Query1->FieldByName("ap_type")->AsString=="I" ? "紧急" : "普通");
		strcpy(strCorp,dm1->Query1->FieldByName("ap_reqdepart")->AsString.c_str());
		strCorp[2]='\0';
		for(i=1;i<m_lstCorpID.GetSize();i++)
		{
			if(m_lstCorpID[i]==strCorp)
			{
				pItem->SubItems->Add(lstCorp->Items->Strings[i]);
				break;
			}
		}
		if(i==m_lstCorpID.GetSize())	pItem->SubItems->Add("");

		pItem->SubItems->Add(dm1->Query1->FieldByName("pd_code")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("mn_name")->AsString);

		strcpy(strFact,dm1->Query1->FieldByName("df_mfplan")->AsString.c_str());
		for(i=1;i<m_lstFactID.GetSize();i++)
		{
			if(m_lstFactID[i]==strFact)
			{
				pItem->SubItems->Add(lstFactory->Items->Strings[i]);
				break;
			}
		}
		if(i==m_lstFactID.GetSize())	pItem->SubItems->Add("");

		pItem->SubItems->Add(FloatField2String(dm1->Query1->FieldByName("cf_quotenum")));
//		pItem->SubItems->Add((LPCSTR)Float2DBString(dm1->Query1->FieldByName("cf_quotenum")->AsFloat*dm1->Query1->FieldByName("cf_quoteprice")->AsFloat,2));
//--------------new 0704--------------------------------------------------------
                strcpy(strTemp2,dm1->Query1->FieldByName("ap_sdcode")->AsString.c_str());
                if(g_theOperator.op_cpcode[0]!='E' && (strcmp(strTemp2,"2")==0 || strcmp(strTemp2,"3")==0))
                {
                        pItem->SubItems->Add("");
                }
                else
                {
        		pItem->SubItems->Add((LPCSTR)Float2DBString(dm1->Query1->FieldByName("cf_quotenum")->AsFloat*dm1->Query1->FieldByName("cf_quoteprice")->AsFloat,2));
                }
//------------------------------------------------------------------------------
		strcpy(strTemp,dm1->Query1->FieldByName("ap_hmcode")->AsString.c_str());
		for(i=0;i<lstHM.GetSize();i++)
		{
			if(strcmp(lstHM[i].strCode,strTemp)==0)
			{
				pItem->SubItems->Add(lstHM[i].strName);
				break;
			}
		}
		if(i==lstHM.GetSize())	pItem->SubItems->Add("");
//		pItem->SubItems->Add(dm1->Query1->FieldByName("sh_name")->AsString);

		strcpy(strTemp,dm1->Query1->FieldByName("ap_sdcode")->AsString.c_str());
		for(i=0;i<m_lstStockDepartID.GetSize();i++)
		{
			if(m_lstStockDepartID[i]==strTemp)
			{
				pItem->SubItems->Add(lstStockDepart->Items->Strings[i]);
				break;
			}
		}
		if(i==m_lstStockDepartID.GetSize())	pItem->SubItems->Add("");
*/
		dm1->Query1->Next();
	}
}
//---------------------------------------------------------------------------
void __fastcall TSumBookNotEndForm::FormShow(TObject *Sender)
{
	CString szSQL;
	char strTemp[256],strCorp2[80];
	int i;
	bool bFind;
//------new 0704----------取得操作者公司别--------------------------------------
/*        szSQL.Format("select op_cpcode from operator where op_code='%s'",operatorcode.c_str());
	RunSQL(dm1->Query1,szSQL,true);
        strcpy(strCorp2,dm1->Query1->FieldByName("op_cpcode")->AsString.c_str());       */
//------------------------------------------------------------------------------
/*
	m_lstHandleID.Add("");
	lstHandle->Items->Add("全部");
	szSQL="select * from StockHandleman order by sh_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		m_lstHandleID.Add(dm1->Query1->FieldByName("sh_code")->AsString.c_str());
		lstHandle->Items->Add(dm1->Query1->FieldByName("sh_name")->AsString);
		dm1->Query1->Next();
	}
	lstHandle->ItemIndex=0;
*/
	m_lstCorpID.Add("");
	lstCorp->Items->Add("全部");
	szSQL="select * from DepartCorp order by dc_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		m_lstCorpID.Add(dm1->Query1->FieldByName("dc_code")->AsString.c_str());
		lstCorp->Items->Add(dm1->Query1->FieldByName("dc_name")->AsString);
		dm1->Query1->Next();
	}
	lstCorp->ItemIndex=0;

	m_lstFactID.Add("");
	lstFactory->Items->Add("全部");
	szSQL="select * from Manufactur order by mf_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		m_lstFactID.Add(dm1->Query1->FieldByName("mf_code")->AsString.c_str());
		lstFactory->Items->Add(dm1->Query1->FieldByName("mf_shortname")->AsString);
		dm1->Query1->Next();
	}
	lstFactory->ItemIndex=0;

//------new 0704----------------------------------------------------------------
/*        if(strcmp(strCorp2,"E")==0 || operatorcode=="admin")
	 {
          szSQL="select * from StockDepart order by sd_code";
         }
        else
         {
          szSQL="select * from StockDepart where sd_code<>'2' and sd_code<>'3' order by sd_code";
         }      */
//------------------------------------------------------------------------------
/*	szSQL="select * from StockDepart order by sd_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		m_lstStockDepartID.Add(dm1->Query1->FieldByName("sd_code")->AsString.c_str());
		lstStockDepart->Items->Add(dm1->Query1->FieldByName("sd_name")->AsString);
		dm1->Query1->Next();
	}
*/
 if(g_theOperator.op_cpcode[0]=='A')
      { //若用户为行政中心，自动寻找行政中心的采购部门与采购经办
                     szSQL="select * from StockDepart where sd_code='X' or sd_code='11' order by sd_code DESC";
                     RunSQL(dm1->Query1,szSQL,true);
                     while(!dm1->Query1->Eof)
                       {
                         m_lstStockDepartID.Add(dm1->Query1->FieldByName("sd_code")->AsString.c_str());
                         lstStockDepart->Items->Add(dm1->Query1->FieldByName("sd_name")->AsString);
                         dm1->Query1->Next();
                        }
//                    lstStockDepart->ItemIndex=0;
        //采购经办
                    m_lstHandleID.Add("");
                    lstHandle->Items->Add("采购处全部采购经办");
                    szSQL="select * from StockHandleman where sh_sdcode='X' or sh_sdcode='11'order by sh_code";
                    RunSQL(dm1->Query1,szSQL,true);
                    while(!dm1->Query1->Eof)
                       {
                         m_lstHandleID.Add(dm1->Query1->FieldByName("sh_code")->AsString.c_str());
                         lstHandle->Items->Add(dm1->Query1->FieldByName("sh_name")->AsString);
                         dm1->Query1->Next();
                        }
                     lstHandle->ItemIndex=0;

      }

 if(g_theOperator.op_cpcode[0]=='D')
      { //若用户为宏铭公司，自动寻找宏铭的采购部门与采购经办
              szSQL="select * from StockDepart where sd_code='Y' or sd_code='1' order by sd_code";
                     RunSQL(dm1->Query1,szSQL,true);
                     while(!dm1->Query1->Eof)
                       {
                         m_lstStockDepartID.Add(dm1->Query1->FieldByName("sd_code")->AsString.c_str());
                         lstStockDepart->Items->Add(dm1->Query1->FieldByName("sd_name")->AsString);
                         dm1->Query1->Next();
                        }
//                    lstStockDepart->ItemIndex=0;

        //采购经办
                    m_lstHandleID.Add("");
                    lstHandle->Items->Add("全部采购经办");
                    szSQL="select * from StockHandleman where sh_sdcode='Y' or sh_sdcode='1' order by sh_code";
                    RunSQL(dm1->Query1,szSQL,true);
                    while(!dm1->Query1->Eof)
                       {
                         m_lstHandleID.Add(dm1->Query1->FieldByName("sh_code")->AsString.c_str());
                         lstHandle->Items->Add(dm1->Query1->FieldByName("sh_name")->AsString);
                         dm1->Query1->Next();
                        }
                     lstHandle->ItemIndex=0;
      }
 if(g_theOperator.op_cpcode[0]=='B')
      { //若用户为宏仁公司，自动寻找宏仁的采购部门
              szSQL="select * from StockDepart where sd_code='9' order by sd_code";
                     RunSQL(dm1->Query1,szSQL,true);
                     while(!dm1->Query1->Eof)
                       {
                         m_lstStockDepartID.Add(dm1->Query1->FieldByName("sd_code")->AsString.c_str());
                         lstStockDepart->Items->Add(dm1->Query1->FieldByName("sd_name")->AsString);
                         dm1->Query1->Next();
                        }
//                    lstStockDepart->ItemIndex=0;

        //采购经办
                    m_lstHandleID.Add("");
                    lstHandle->Items->Add("全部采购经办");
                    szSQL="select * from StockHandleman where sh_sdcode='9' order by sh_code";
                    RunSQL(dm1->Query1,szSQL,true);
                    while(!dm1->Query1->Eof)
                       {
                         m_lstHandleID.Add(dm1->Query1->FieldByName("sh_code")->AsString.c_str());
                         lstHandle->Items->Add(dm1->Query1->FieldByName("sh_name")->AsString);
                         dm1->Query1->Next();
                        }
                     lstHandle->ItemIndex=0;
      }
 if(g_theOperator.op_cpcode[0]=='C')
      { //若用户为宏育公司，自动寻找宏育的采购部门
              szSQL="select * from StockDepart where sd_code='4' or sd_code='5' order by sd_code";
                     RunSQL(dm1->Query1,szSQL,true);
                     while(!dm1->Query1->Eof)
                       {
                         m_lstStockDepartID.Add(dm1->Query1->FieldByName("sd_code")->AsString.c_str());
                         lstStockDepart->Items->Add(dm1->Query1->FieldByName("sd_name")->AsString);
                         dm1->Query1->Next();
                        }
//                    lstStockDepart->ItemIndex=0;

        //采购经办
                    m_lstHandleID.Add("");
                    lstHandle->Items->Add("全部采购经办");
                    szSQL="select * from StockHandleman where sh_sdcode='4' or sh_sdcode='5' order by sh_code";
                    RunSQL(dm1->Query1,szSQL,true);
                    while(!dm1->Query1->Eof)
                       {
                         m_lstHandleID.Add(dm1->Query1->FieldByName("sh_code")->AsString.c_str());
                         lstHandle->Items->Add(dm1->Query1->FieldByName("sh_name")->AsString);
                         dm1->Query1->Next();
                        }
                     lstHandle->ItemIndex=0;
      }
 if(g_theOperator.op_cpcode[0]=='E')
      { //若用户为宏信公司，自动寻找宏信的采购部门
              szSQL="select * from StockDepart where sd_code='2' or sd_code='3' order by sd_code";
                     RunSQL(dm1->Query1,szSQL,true);
                     while(!dm1->Query1->Eof)
                       {
                         m_lstStockDepartID.Add(dm1->Query1->FieldByName("sd_code")->AsString.c_str());
                         lstStockDepart->Items->Add(dm1->Query1->FieldByName("sd_name")->AsString);
                         dm1->Query1->Next();
                        }
//                    lstStockDepart->ItemIndex=0;

        //采购经办
                    m_lstHandleID.Add("");
                    lstHandle->Items->Add("全部采购经办");
                    szSQL="select * from StockHandleman where sh_sdcode='2' or sh_sdcode='3' order by sh_code";
                    RunSQL(dm1->Query1,szSQL,true);
                    while(!dm1->Query1->Eof)
                       {
                         m_lstHandleID.Add(dm1->Query1->FieldByName("sh_code")->AsString.c_str());
                         lstHandle->Items->Add(dm1->Query1->FieldByName("sh_name")->AsString);
                         dm1->Query1->Next();
                        }
                     lstHandle->ItemIndex=0;
      }
if(g_theOperator.op_cpcode[0]=='F')
      { //若用户为宏焕公司，自动寻找宏焕的采购部门
              szSQL="select * from StockDepart where sd_code='6' or sd_code='7' or sd_code='8' order by sd_code";
                     RunSQL(dm1->Query1,szSQL,true);
                     while(!dm1->Query1->Eof)
                       {
                         m_lstStockDepartID.Add(dm1->Query1->FieldByName("sd_code")->AsString.c_str());
                         lstStockDepart->Items->Add(dm1->Query1->FieldByName("sd_name")->AsString);
                         dm1->Query1->Next();
                        }
//                    lstStockDepart->ItemIndex=0;

        //采购经办
                    m_lstHandleID.Add("");
                    lstHandle->Items->Add("全部采购经办");
                    szSQL="select * from StockHandleman where sh_sdcode='6' or sh_sdcode='7' order by sh_code";
                    RunSQL(dm1->Query1,szSQL,true);
                    while(!dm1->Query1->Eof)
                       {
                         m_lstHandleID.Add(dm1->Query1->FieldByName("sh_code")->AsString.c_str());
                         lstHandle->Items->Add(dm1->Query1->FieldByName("sh_name")->AsString);
                         dm1->Query1->Next();
                        }
                     lstHandle->ItemIndex=0;
      }
if(g_theOperator.op_cpcode[0]=='G')
      { //若用户为宏昌公司，自动寻找宏昌的采购部门
              szSQL="select * from StockDepart where sd_code='10' order by sd_code";
                     RunSQL(dm1->Query1,szSQL,true);
                     while(!dm1->Query1->Eof)
                       {
                         m_lstStockDepartID.Add(dm1->Query1->FieldByName("sd_code")->AsString.c_str());
                         lstStockDepart->Items->Add(dm1->Query1->FieldByName("sd_name")->AsString);
                         dm1->Query1->Next();
                        }
//                    lstStockDepart->ItemIndex=0;

        //采购经办
                    m_lstHandleID.Add("");
                    lstHandle->Items->Add("全部采购经办");
                    szSQL="select * from StockHandleman where sh_sdcode='10' order by sh_code";
                    RunSQL(dm1->Query1,szSQL,true);
                    while(!dm1->Query1->Eof)
                       {
                         m_lstHandleID.Add(dm1->Query1->FieldByName("sh_code")->AsString.c_str());
                         lstHandle->Items->Add(dm1->Query1->FieldByName("sh_name")->AsString);
                         dm1->Query1->Next();
                        }
                     lstHandle->ItemIndex=0;
        }

	szSQL.Format("select * from StockHandleman where sh_code='%s'",operatorcode.c_str());
	RunSQL(dm1->Query1,szSQL,true);
	bFind=false;
	if(!dm1->Query1->Eof)
	{
		strcpy(strTemp,dm1->Query1->FieldByName("sh_sdcode")->AsString.c_str());
		for(i=0;i<m_lstStockDepartID.GetSize();i++)
		{
			if(m_lstStockDepartID[i]==strTemp)
			{
				lstStockDepart->ItemIndex=i;
				bFind=true;
				break;
			}
		}
	}
	if(!bFind)	lstStockDepart->ItemIndex=0;
//	edtDays->Text="2";
}
//---------------------------------------------------------------------------
void __fastcall TSumBookNotEndForm::lstFactoryExit(TObject *Sender)
{
	HandleListboxExit(lstFactory,&m_lstFactID);
}
//---------------------------------------------------------------------------

void __fastcall TSumBookNotEndForm::RadioButton1Click(TObject *Sender)
{
        m_bMonth=false;        
}
//---------------------------------------------------------------------------

void __fastcall TSumBookNotEndForm::RadioButton2Click(TObject *Sender)
{
        m_bMonth=true;        
}
//---------------------------------------------------------------------------

