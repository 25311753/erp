//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#pragma hdrstop

#include "DataModule.h"
#include "BaseCode.h"
#include "BookFactoryList.h"
#include "FactorySearch.h"
#include "TConst.h"
#include "LdyInterface.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TBookFactoryListForm *BookFactoryListForm;

//===============================================================================
//订购单列表查询接口，文件：BookFactoryList.*
void BookFactoryList(int nAuth)
{
	CALL_FORM(TBookFactoryListForm);
}
//======================================================================

//---------------------------------------------------------------------------
__fastcall TBookFactoryListForm::TBookFactoryListForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TBookFactoryListForm::btnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TBookFactoryListForm::FormShow(TObject *Sender)
{
	CString szSQL;
	int nYear,nMonth,nDay;
	char strDate0[80],strDate1[80];

	GetSysDate(nYear,nMonth,nDay,false);
	sprintf(strDate0,"%04d%02d%02d",nYear,nMonth,1);
	sprintf(strDate1,"%04d%02d%02d",nYear,nMonth,nDay);

	edtBookID	->Text="";
	edtDate0	->Text=strDate0;
	edtDate1	->Text=strDate1;
	edtAskID	->Text="";

	m_lstRcptID.Add("");
	lstRcpt->Items->Add("全部");
	szSQL="select * from RcptHandleman order by rh_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		m_lstRcptID.Add(dm1->Query1->FieldByName("rh_code")->AsString.c_str());
		lstRcpt->Items->Add(dm1->Query1->FieldByName("rh_name")->AsString);
		dm1->Query1->Next();
	}
	lstRcpt->ItemIndex=0;

	szSQL="select * from StockDepart order by sd_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		m_lstDepartID.Add(dm1->Query1->FieldByName("sd_code")->AsString.c_str());
		lstDepart->Items->Add(dm1->Query1->FieldByName("sd_name")->AsString);
		dm1->Query1->Next();
	}
	lstDepart->ItemIndex=0;

	m_lstCorpID.Add("");
	lstCorp->Items->Add("全部");
//	if(operatorcode=="admin" || g_theOperator.op_cpcode[0]=='\0')
		szSQL="select * from DepartCorp order by dc_code";
//	else
//		szSQL.Format("select * from DepartCorp where substring(dc_code,1,1)='%s' order by dc_code",
//			g_theOperator.op_cpcode);
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

	lstStockType->ItemIndex=0;  
  lstAccept->ItemIndex=0;

  ResetCtrl();
}
//---------------------------------------------------------------------------
void __fastcall TBookFactoryListForm::btnQueryClick(TObject *Sender)
{
	CString szSQL,szFilter;
	char strTemp[256],strDate0[80],strDate1[80],strCorp[80],strRMB[80],strMNCode[80],strTemp2[256];
	TListItem *pItem;
	int nSel,i;
	double fCount,fAcpt,fChk,fPrice;
	bool bFinished,bSeePrice;
	CArray<BASE2COLDATA,BASE2COLDATA>lstRMB;
	BASE2COLDATA rwData;

	szSQL="select * from diccurrency order by dc_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		strcpy(rwData.strCode,dm1->Query1->FieldByName("dc_code")->AsString.c_str());
		strcpy(rwData.strName,dm1->Query1->FieldByName("dc_name")->AsString.c_str());
		lstRMB.Add(rwData);
		dm1->Query1->Next();
	}

  lstView->Items->Clear();
  
//	szSQL="select * from BookFactory,Manufactur,RcptHandleman,PurchaseDetail,materialno"
//		" where bf_mfcode=mf_code and bf_rhcode=rh_code"
//    " and bf_apcode=pd_code and pd_mncode=mn_code";

	edtBookID->Text=edtBookID->Text.Trim();
	if(!edtBookID->Text.IsEmpty())
	{
		sprintf(strTemp," and bf_code like '%s%%'",edtBookID->Text.c_str());
		szFilter+=strTemp;
	}
	edtDate0->Text=edtDate0->Text.Trim();
	edtDate1->Text=edtDate1->Text.Trim();
  if(!edtDate0->Text.IsEmpty())
  {
  	TDateTime tDate;
    int nYear,nMonth,nDay;

    if(edtDate0->Text.Length()!=8)
    {
    	ShowMessage("不合法的日期格式，日期格式为：yyyymmdd");
      if(edtDate0->CanFocus())	edtDate0->SetFocus();
      return;
    }
    Date2YYMMDD(edtDate0->Text.c_str(),nYear,nMonth,nDay);
    try
    {
    	tDate=TDateTime(nYear,nMonth,nDay);
    }
    catch(...)
    {
    	ShowMessage("不合法的日期格式，日期格式为：yyyymmdd");
      if(edtDate0->CanFocus())	edtDate0->SetFocus();
      return;
    }
		sprintf(strDate0,"%04d-%02d-%02d",nYear,nMonth,nDay);

    if(edtDate1->Text.IsEmpty())
    {
    	ShowMessage("当开始日期不为空时，必须输入截止日期");
      if(edtDate1->CanFocus())	edtDate1->SetFocus();
      return;
    }
    if(edtDate1->Text.Length()!=8)
    {
    	ShowMessage("不合法的日期格式，日期格式为：yyyymmdd");
      if(edtDate1->CanFocus())	edtDate1->SetFocus();
      return;
    }
    Date2YYMMDD(edtDate1->Text.c_str(),nYear,nMonth,nDay);
    try
    {
    	tDate=TDateTime(nYear,nMonth,nDay);
    }
    catch(...)
    {
    	ShowMessage("不合法的日期格式，日期格式为：yyyymmdd");
      if(edtDate1->CanFocus())	edtDate1->SetFocus();
      return;
    }
		sprintf(strDate1,"%04d-%02d-%02d",nYear,nMonth,nDay);
		sprintf(strTemp," and bf_bookdate between '%s' and '%s'",strDate0,strDate1);
		szFilter+=strTemp;
  }
	edtAskID->Text=edtAskID->Text.Trim();
	if(!edtAskID->Text.IsEmpty())
	{
		sprintf(strTemp," and bf_apcode like '%s%%'",edtAskID->Text.c_str());
		szFilter+=strTemp;
	}
	if((nSel=lstRcpt->ItemIndex)>0 && nSel<m_lstRcptID.GetSize())
	{
		sprintf(strTemp," and bf_rhcode='%s'",m_lstRcptID[nSel]);
		szFilter+=strTemp;
	}
	if((nSel=lstDepart->ItemIndex)>=0 && nSel<m_lstDepartID.GetSize())
	{
                strcpy(strTemp2,m_lstDepartID[nSel]);                           //0705 获得采购部门别
		sprintf(strTemp," and ap_sdcode='%s'",m_lstDepartID[nSel]);
                szFilter+=strTemp;
	}
	if((nSel=lstCorp->ItemIndex)>0 && nSel<m_lstCorpID.GetSize())
	{
		sprintf(strTemp," and substring(ap_reqdepart,1,2)='%s'",m_lstCorpID[nSel]);
		szFilter+=strTemp;
	}

	if((nSel=lstFactory->ItemIndex)>0 && nSel<m_lstFactID.GetSize())
	{
		sprintf(strTemp," and bf_mfcode='%s'",m_lstFactID[nSel]);
		szFilter+=strTemp;
	}

	if(lstStockType->ItemIndex==1)	szFilter+=" and substring(pd_code,1,1)='Q'";
	else	szFilter+=" and substring(pd_code,1,1)='P'";

	szSQL="select bf_code,bf_bookdate,bf_apcode,rh_name,mf_shortname,bf_mfcard,mn_code,mn_name,bf_count,bf_price,"
		"bf_dccode,ap_sdcode,ap_reqdepart,ap_shcode,bf_rem"
		",sum(am_quantity) as am_n,sum(am_checkquan) as am_chk,sum(am_defectquan) as am_def"
		" from BookFactory,Manufactur,RcptHandleman,PurchaseDetail,materialno,acceptmate,AskPurchase"
		" where bf_mfcode=mf_code and bf_rhcode=rh_code"
		" and bf_apcode=pd_code and pd_mncode=mn_code"
		" and ap_code=substring(pd_code,1,7)"
		" and bf_code*=am_bfcode"
		" and am_canceldate is null";
	szSQL+=szFilter;
	szSQL+=" and substring(pd_mncode,2,1)<>'M'";                            //不查原料单
	szSQL+=" group by bf_code,bf_bookdate,bf_apcode,rh_name,mf_shortname,bf_mfcard,mn_code,mn_name,bf_count,bf_price,"
		"bf_dccode,ap_sdcode,ap_reqdepart,ap_shcode,bf_rem";

//	szSQL="select bf_code,bf_bookdate,bf_apcode,rh_name,mf_shortname,mn_code,mn_name"
//		" from BookFactory,Manufactur,RcptHandleman,PurchaseDetail,materialno"
//		" where bf_mfcode=mf_code and bf_rhcode=rh_code"
//		" and bf_apcode=pd_code and pd_mncode=mn_code";
//	szSQL+=szFilter;
//	szSQL+=" union";
//	szSQL+=" select bf_code,bf_bookdate,bf_apcode,rh_name,mf_shortname,mn_code,mn_name"
//		" from BookFactory,Manufactur,RcptHandleman,TreatStock,materialno"
//		" where bf_mfcode=mf_code and bf_rhcode=rh_code"
//		" and bf_apcode=ts_code and ts_mncode=mn_code";
//	szSQL+=szFilter;
	szSQL+=" order by bf_bookdate,bf_code";

	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		if(lstAccept->ItemIndex>0)
		{
			if(lstAccept->ItemIndex==1 && !dm1->Query1->FieldByName("am_n")->IsNull)	
				goto CONTINUE_LOOP;
			else if(lstAccept->ItemIndex>1 && dm1->Query1->FieldByName("am_n")->IsNull)	
				goto CONTINUE_LOOP;

			fCount=dm1->Query1->FieldByName("bf_count")->AsFloat;
			if(dm1->Query1->FieldByName("am_n")->IsNull)
				fAcpt=0;
			else
				fAcpt=dm1->Query1->FieldByName("am_n")->AsFloat;
			if(dm1->Query1->FieldByName("am_chk")->IsNull)
				fChk=0;
			else
				fChk=dm1->Query1->FieldByName("am_chk")->AsFloat;
//			if(dm1->Query1->FieldByName("am_def")->IsNull)
//				fDef=0;
//			else
//				fDef=dm1->Query1->FieldByName("am_def")->AsFloat;

			bFinished = fabs(fCount-fAcpt)<1e-6 && fabs(fCount-fChk)<1e-6;
			if(lstAccept->ItemIndex==2 && bFinished)				goto CONTINUE_LOOP;
			else if(lstAccept->ItemIndex==3 && !bFinished)	goto CONTINUE_LOOP;
		}

		pItem=lstView->Items->Add();
		assert(pItem!=NULL);
		pItem->Caption=dm1->Query1->FieldByName("bf_code")->AsString;
		pItem->SubItems->Add(DateField2Text(dm1->Query1->FieldByName("bf_bookdate")));
		pItem->SubItems->Add(dm1->Query1->FieldByName("bf_apcode")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("rh_name")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("mf_shortname")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("bf_mfcard")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("mn_code")->AsString);
                pItem->SubItems->Add(dm1->Query1->FieldByName("mn_name")->AsString);

		strcpy(strMNCode,dm1->Query1->FieldByName("mn_code")->AsString.c_str());

		fCount=dm1->Query1->FieldByName("bf_count")->AsFloat;
		fPrice=dm1->Query1->FieldByName("bf_price")->AsFloat;

		pItem->SubItems->Add(FloatField2String(dm1->Query1->FieldByName("bf_count"),2));
//--------------new 0705--------------------------------------------------------
/*                if(g_theOperator.op_cpcode[0]!='E' && (strcmp(strTemp2,"2")==0 || strcmp(strTemp2,"3")==0))
                {
                        pItem->SubItems->Add("");
                }
                else
                {
		pItem->SubItems->Add((LPCSTR)Float2DBString(dm1->Query1->FieldByName("cf_quotenum")->AsFloat*dm1->Query1->FieldByName("cf_quoteprice")->AsFloat,2));
                }       */
//------------------------------------------------------------------------------
//------new 0706----------------------------------------------------------------
		if(operatorcode!="admin" && dm1->Query1->FieldByName("ap_shcode")->AsString!=operatorcode && operatorcode!="108557")
			bSeePrice=false;
		else	bSeePrice=true; 
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/*		if(strMNCode[1]=='M' && operatorcode!="admin" && dm1->Query1->FieldByName("ap_shcode")->AsString!=operatorcode)
			bSeePrice=false;
		else	bSeePrice=true; */
//------------------------------------------------------------------------------
		if(!bSeePrice)
			pItem->SubItems->Add(""); //只有采购经办自己才能看到原料单价
		else
			pItem->SubItems->Add((LPCSTR)Float2DBString(fPrice,3));
		strcpy(strRMB,dm1->Query1->FieldByName("bf_dccode")->AsString.c_str());
		for(i=0;i<lstRMB.GetSize();i++)
		{
			if(strcmp(lstRMB[i].strCode,strRMB)==0)
			{
				pItem->SubItems->Add(lstRMB[i].strName);
				break;
			}
		}
		if(i==lstRMB.GetSize())	pItem->SubItems->Add("");
		if(!bSeePrice)
			pItem->SubItems->Add(""); //只有采购经办自己才能看到原料单价
		else
			pItem->SubItems->Add((LPCSTR)Float2DBString(fPrice*fCount,2));

		pItem->SubItems->Add(FloatField2String(dm1->Query1->FieldByName("am_n"),2));
		pItem->SubItems->Add(FloatField2String(dm1->Query1->FieldByName("am_chk"),2));
		pItem->SubItems->Add(FloatField2String(dm1->Query1->FieldByName("am_def"),2));

    if(dm1->Query1->FieldByName("am_n")->IsNull)
    	pItem->SubItems->Add("");
    else
		{
			if(!bSeePrice)
				pItem->SubItems->Add(""); //只有采购经办自己才能看到原料单价
			else
				pItem->SubItems->Add((LPCSTR)Float2DBString(fPrice*dm1->Query1->FieldByName("am_chk")->AsFloat,2));
		}
		for(i=0;i<m_lstDepartID.GetSize();i++)
		{
			if(m_lstDepartID[i]==dm1->Query1->FieldByName("ap_sdcode")->AsString.c_str())
			{
				pItem->SubItems->Add(lstDepart->Items->Strings[i]);
				break;
			}
		}
		if(i==m_lstDepartID.GetSize())	pItem->SubItems->Add("");

		strcpy(strCorp,dm1->Query1->FieldByName("ap_reqdepart")->AsString.c_str());
		strCorp[2]='\0';
		for(i=0;i<m_lstCorpID.GetSize();i++)
		{
			if(m_lstCorpID[i]==strCorp)
			{
				pItem->SubItems->Add(lstCorp->Items->Strings[i]);
				break;
			}
		}
		if(i==m_lstCorpID.GetSize())	pItem->SubItems->Add("");

    pItem->SubItems->Add(dm1->Query1->FieldByName("bf_rem")->AsString);

CONTINUE_LOOP:
		dm1->Query1->Next();    

	}
}
//---------------------------------------------------------------------------
void __fastcall TBookFactoryListForm::btnToExcelClick(TObject *Sender)
{
	Variant vExcel,vSheet;
  int nRow,i;
  TListItem *pItem;

  try
  {
	  nRow=1;
		if(!OpenExcel("订购单列表.xls",vExcel,vSheet))	return;
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
        pItem->SubItems->Strings[10].c_str(),
        pItem->SubItems->Strings[11].c_str(),
        pItem->SubItems->Strings[12].c_str(),
        pItem->SubItems->Strings[13].c_str(),
        pItem->SubItems->Strings[14].c_str(),
        pItem->SubItems->Strings[15].c_str(),
        pItem->SubItems->Strings[16].c_str(),
				NULL);
		}
	}
	catch(...)
	{
	}
}
//---------------------------------------------------------------------------
void __fastcall TBookFactoryListForm::lstViewSelectItem(TObject *Sender,TListItem *Item, bool Selected)
{
	if(!Selected)	return;

	ResetCtrl();
}
//---------------------------------------------------------------------------
void __fastcall TBookFactoryListForm::lstViewClick(TObject *Sender)
{
	if(lstView->Selected==NULL)	ResetCtrl();
}

void TBookFactoryListForm::ResetCtrl()
{
	btnDetail->Enabled = lstView->Selected!=NULL;
}

//---------------------------------------------------------------------------

void __fastcall TBookFactoryListForm::btnDetailClick(TObject *Sender)
{
	TListItem *pItem;

	if((pItem=lstView->Selected)==NULL)	return;

	int nRight=GetOperatorRight(operatorcode.c_str(),"IDM_BOOKFACTORY");
	//订购单输入接口，文件：BookFactory.*
	BookFactory(pItem->Caption.c_str(),nRight);
}
//---------------------------------------------------------------------------

void __fastcall TBookFactoryListForm::lstViewDblClick(TObject *Sender)
{
	if(btnDetail->Enabled)	btnDetailClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TBookFactoryListForm::lstFactoryExit(TObject *Sender)
{
	int nSel,i;

	lstFactory->Text=lstFactory->Text.UpperCase().Trim();
	if((nSel=lstFactory->Items->IndexOf(lstFactory->Text))<0 || nSel>=m_lstFactID.GetSize())
	{
		for(i=1;i<m_lstFactID.GetSize();i++)
		{
			if(m_lstFactID[i]==lstFactory->Text.c_str())
			{
				lstFactory->ItemIndex=i;
				break;
			}
		}
		if(i==m_lstFactID.GetSize())
		{
			ShowMessage("没有该厂商");
			return;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TBookFactoryListForm::btnPickFactClick(TObject *Sender)
{
	TFactorySearchForm *pForm;
  int i;

  pForm=new TFactorySearchForm(this);
  assert(pForm!=NULL);
  if(pForm->ShowModal()==mrOk && !pForm->m_szID.IsEmpty())
  {
  	for(i=0;i<m_lstFactID.GetSize();i++)
    {
    	if(m_lstFactID[i]==pForm->m_szID)
      {
      	lstFactory->ItemIndex=i;
        break;
      }
    }
  }
  delete pForm;
}
//---------------------------------------------------------------------------

void __fastcall TBookFactoryListForm::btnToAskClick(TObject *Sender)
{
	TListItem *pItem;
  char strAsk[80];

	if((pItem=lstView->Selected)==NULL)	return;
	strcpy(strAsk,pItem->SubItems->Strings[1].c_str());
  if(strlen(strAsk)<2) return;
  strAsk[strlen(strAsk)-1]='\0';
	int nRight=GetOperatorRight(operatorcode.c_str(),"IDM_ASKPURCHASE");
	//请购单输入接口，文件：AskPurchase.*
	AskPurchase(strAsk,nRight);
}
//---------------------------------------------------------------------------

