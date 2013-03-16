//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <assert.h>
#pragma hdrstop

#include "DataModule.h"
#include "BaseCode.h"
#include "Book4Times.h"
#include "TConst.h"
#include "LdyInterface.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TBook4TimesForm *Book4TimesForm;

//---------------------------------------------------------------------------
//订购超过4次汇总表接口，文件：Book4Times.*
void Book4Times(int nAuth)
{
	CALL_FORM(TBook4TimesForm);
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
__fastcall TBook4TimesForm::TBook4TimesForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TBook4TimesForm::btnExitClick(TObject *Sender)
{
	Close();	
}
//---------------------------------------------------------------------------
void __fastcall TBook4TimesForm::btnToExcelClick(TObject *Sender)
{
	Variant vExcel,vSheet;
  int nRow,i;
  TListItem *pItem;

  try
  {
	  nRow=1;
		if(!OpenExcel("请购单列表.xls",vExcel,vSheet))	return;
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
				NULL);
		}
	}
	catch(...)
	{
	}
}
//---------------------------------------------------------------------------
void __fastcall TBook4TimesForm::btnQueryClick(TObject *Sender)
{
//------m_szSHCode=dm1->Query2->FieldByName("ap_shcode")->AsString
/*	if(operatorcode==m_szSHCode || operatorcode=="admin")                   //只有采购经办才能查询单价
	{
		if(strMN[0]=='E' && strMN[1]=='M')
			edtPrice->Text=FloatField2String(dm1->Query1->FieldByName("bf_price"),6);
		else
			edtPrice->Text=FloatField2String(dm1->Query1->FieldByName("bf_price"),4);
	}
	else
		edtPrice->Text="";                                    */

//	strcpy(strID,dm1->Query1->FieldByName("ts_sdcode")->AsString.c_str());                
//----new 0630----经办自己可以查看自己开的单的单价，可能是其它公司的.只有同一公司的经办才可以查看单价
/*        if(strcmp(strID,strSHID)!=0 && operatorcode!=dm1->Query1->FieldByName("ts_shcode")->AsString.c_str() && operatorcode!="admin" && operatorcode!="108557")
        {
               	pItem->SubItems->Add("");
        }
        else
		pItem->SubItems->Add(FloatField2String(dm1->Query1->FieldByName("bf_price"),2));
*/

//-------------------------------------------------------------------------------
	char strDate0[80],strDate1[80],strTemp[256],strID[4],strSHID[4],strSH[256],strTemp2[256];
	CString szSQL,szTable;
	TListItem *pItem;
	int i,nSel,nTimes;
//--------new 0630--------------------------------------------------------------
/*        szSQL.Format("select * from StockHandleman where sh_code='%s'",operatorcode);
        RunSQL(dm1->Query1,szSQL,true);
        strcpy(strSHID,dm1->Query1->FieldByName("sh_sdcode")->AsString.c_str());        */
//------------------------------------------------------------------------------

	lstView->Items->Clear();

  nTimes=atoi(edtTimes->Text.c_str());
  if(nTimes<=0)
  {
  	ShowMessage("次数请输入大於0的整数");
    if(edtTimes->CanFocus())	edtTimes->SetFocus();
    return;
  }

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
  }

	szTable=GetTmpTableName();
	szSQL.Format("create table dbo.%s ("
//#ifdef _DEBUG
		"m_code  varchar(80) COLLATE Chinese_Taiwan_Stroke_CS_AS,"
//#else
//		"m_code  varchar(80),"
//#endif
		"m_times int"
		")",szTable);
	if(!RunSQL(dm1->Query1,szSQL))	return;

	szSQL.Format("insert into %s"
		" select pd_mncode,count(*) as m_count from BookFactory,PurchaseDetail"
		" where pd_code=bf_apcode"
		" and pd_mncode not in"
		"("
		" select distinct ts_mncode from TreatStock"
		")"
		" and bf_bookdate between '%s' and '%s'"
		" group by pd_mncode",szTable,strDate0,strDate1);
	if(!RunSQL(dm1->Query1,szSQL))	goto DROP_TABLE;

	szSQL.Format("select * from BookFactory,PurchaseDetail,%s,materialno,Manufactur,AskPurchase"
		" where pd_code=bf_apcode"
		" and pd_mncode=m_code"
		" and ap_code=substring(pd_code,1,7)"
		" and mf_code=bf_mfcode"
		" and mn_code=pd_mncode"
                " and pd_mncode not like 'EM%%'"
		" and m_times>=%d"
		" and (bf_bookdate between '%s' and '%s')",szTable,nTimes,strDate0,strDate1);
//------0630把权限全部收掉------------------------------------------------------

	if((nSel=lstCorp->ItemIndex)>0 && nSel<m_lstCorpID.GetSize())
	{
		sprintf(strTemp," and substring(ap_reqdepart,1,2)='%s'",m_lstCorpID[nSel]);
		szSQL+=strTemp;
	}
	if((nSel=lstDepart->ItemIndex)>0 && nSel<m_lstDepartID.GetSize())
	{
		sprintf(strTemp," and ap_sdcode='%s'",m_lstDepartID[nSel]);
		szSQL+=strTemp;
	}       
//------------------------------------------------------------------------------
//------new 0630----------------------------------------------------------------
/*        szSQL+=" and ";
        szSQL+="(";
        sprintf(strTemp," ap_shcode='%s'",operatorcode);
        szSQL+=strTemp;

        sprintf(strTemp," or ap_sdcode='%s'",strSHID);
        szSQL+=strTemp;

        sprintf(strTemp," or ap_hmcode='%s'",operatorcode);
        szSQL+=strTemp;
        szSQL+=")";

*/
//------------------------------------------------------------------------------
	szSQL+=" order by mn_code,bf_bookdate,bf_price";
	if(!RunSQL(dm1->Query1,szSQL,true))	goto DROP_TABLE;



	while(!dm1->Query1->Eof)
	{
		pItem=lstView->Items->Add();
		assert(pItem!=NULL);
		pItem->Caption=dm1->Query1->FieldByName("mn_code")->AsString;
		pItem->SubItems->Add(dm1->Query1->FieldByName("mn_name")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("bf_code")->AsString);
		pItem->SubItems->Add(DateField2Text(dm1->Query1->FieldByName("bf_bookdate")));
//		pItem->SubItems->Add(FloatField2String(dm1->Query1->FieldByName("bf_price"),2));
//---------NEW 0704 ------------------------------------------------------------
                strcpy(strTemp2,dm1->Query1->FieldByName("ap_sdcode")->AsString.c_str());
                if(g_theOperator.op_cpcode[0]!='E' && (strcmp(strTemp2,"2")==0 || strcmp(strTemp2,"3")==0))
                {
                        pItem->SubItems->Add("");
                }
                else
                {
		pItem->SubItems->Add(FloatField2String(dm1->Query1->FieldByName("bf_price"),2));
                }
//------------------------------------------------------------------------------
		pItem->SubItems->Add(dm1->Query1->FieldByName("mf_shortname")->AsString);

		strcpy(strTemp,dm1->Query1->FieldByName("ap_reqdepart")->AsString.c_str());
		strTemp[2]='\0';
		for(i=1;i<m_lstCorpID.GetSize();i++)
		{
			if(m_lstCorpID[i]==strTemp)
			{
				pItem->SubItems->Add(lstCorp->Items->Strings[i]);
				break;
			}
		}
		if(i==m_lstCorpID.GetSize())	pItem->SubItems->Add("");

		for(i=1;i<m_lstDepartID.GetSize();i++)
		{
			if(m_lstDepartID[i]==dm1->Query1->FieldByName("ap_sdcode")->AsString.c_str())
			{
				pItem->SubItems->Add(lstDepart->Items->Strings[i]);
				break;
			}
		}
		if(i==m_lstDepartID.GetSize())	pItem->SubItems->Add("");

		dm1->Query1->Next();
	}

DROP_TABLE:
	szSQL.Format("drop table %s",szTable);
	RunSQL(dm1->Query1,szSQL);
}
//---------------------------------------------------------------------------
void __fastcall TBook4TimesForm::FormShow(TObject *Sender)
{
	int nYear,nMonth,nDay;
	char strDate0[80],strDate1[80];
  CString szSQL;

  edtTimes->Text="4";
	GetSysDate(nYear,nMonth,nDay,false);
	sprintf(strDate0,"%04d%02d%02d",nYear,nMonth,1);
	sprintf(strDate1,"%04d%02d%02d",nYear,nMonth,nDay);
	edtDate0->Text=strDate0;
	edtDate1->Text=strDate1;

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

	m_lstDepartID.Add("");
	lstDepart->Items->Add("全部");
	szSQL="select * from StockDepart order by sd_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		m_lstDepartID.Add(dm1->Query1->FieldByName("sd_code")->AsString.c_str());
		lstDepart->Items->Add(dm1->Query1->FieldByName("sd_name")->AsString);
		dm1->Query1->Next();
	}
	lstDepart->ItemIndex=0;
}
//---------------------------------------------------------------------------

