//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <assert.h>
#pragma hdrstop

#include "DataModule.h"
#include "BaseCode.h"
#include "BookMultiPrn.h"
#include "TConst.h"
#include "FactorySearch.h"
#include "LdyInterface.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TBookMultiPrnForm *BookMultiPrnForm;

//===========================================================================
//订购单列印接口，文件：BookMultiPrn.*
void BookMultiPrn(int nAuth)
{
	if(nAuth==AUTH_NONE)	return;
	CALL_FORM(TBookMultiPrnForm);
}
//=============================================================================

//---------------------------------------------------------------------------
__fastcall TBookMultiPrnForm::TBookMultiPrnForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TBookMultiPrnForm::FormShow(TObject *Sender)
{
	CString szSQL;
	int nYear,nMonth,nDay,i;
	char strDate[80],strTemp[256];

	szSQL="select * from DepartCorp order by dc_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		m_lstCorpID.Add(dm1->Query1->FieldByName("dc_code")->AsString.c_str());
		lstCorp->Items->Add(dm1->Query1->FieldByName("dc_name")->AsString);
		dm1->Query1->Next();
	}
	lstCorp->ItemIndex=0;

	szSQL="select * from StockHandleman order by sh_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		m_lstHandleID.Add(dm1->Query1->FieldByName("sh_code")->AsString.c_str());
		lstStockHandle->Items->Add(dm1->Query1->FieldByName("sh_name")->AsString);
		dm1->Query1->Next();
	}
	for(i=0;i<m_lstHandleID.GetSize();i++)
	{
		if(m_lstHandleID[i]==operatorcode.c_str())
		{
			lstStockHandle->ItemIndex=i;
			break;
		}
	}
	if(i<m_lstHandleID.GetSize())	lstStockHandle->Enabled=false;
	else	lstStockHandle->ItemIndex=0;

	GetSysDate(nYear,nMonth,nDay,false);
	sprintf(strDate,"%04d%02d%02d",nYear,nMonth,nDay);
	edtDate0->Text=strDate;
	edtDate1->Text=strDate;

  GetPrivateProfileString("BOOKMULTIPRN","REQCORP","",strTemp,250,INI_FILE_NAME);
	if(strTemp[0]!='\0')
	{
		for(i=0;i<lstCorp->Items->Count;i++)
		{
			if(lstCorp->Items->Strings[i]==strTemp)
			{
				lstCorp->ItemIndex=i;
				break;
			}
		}
	}

	lstFactory->Text="";
	ResetFactList();

        if(g_theOperator.op_cpcode[0]=='C' || operatorcode=="admin")
     {
        ComboBox1->Enabled=true;
        ComboBox1->Text="";
        szSQL="select * from Manufactur where mf_code='Y001'";
        RunSQL(dm1->Query1,szSQL,true);
        while(!dm1->Query1->Eof)
         {
          m_lstFactID1.Add(dm1->Query1->FieldByName("mf_code")->AsString.c_str());
          ComboBox1->Items->Add(dm1->Query1->FieldByName("mf_name")->AsString);
          dm1->Query1->Next();
         }
        ComboBox1->ItemIndex=-1;
     }
    else
      {
       ComboBox1->Enabled=false;
      }
}
//---------------------------------------------------------------------------

void TBookMultiPrnForm::ResetFactList()
{
	int nSel;
	char strTemp[256];
	CString szSQL;

	m_lstFactID.RemoveAll();
	lstFactory->Items->Clear();

	szSQL="select * from Manufactur where mf_code in("
		" select distinct bf_mfcode from BookFactory,AskPurchase"
		" where ap_code=substring(bf_apcode,1,7)";
	if((nSel=lstStockHandle->ItemIndex)>=0 && nSel<m_lstHandleID.GetSize())
	{
		sprintf(strTemp," and ap_shcode='%s'",m_lstHandleID[nSel]);
		szSQL+=strTemp;
	}
	if((nSel=lstCorp->ItemIndex)>=0 && nSel<m_lstCorpID.GetSize())
	{
		sprintf(strTemp," and substring(ap_reqdepart,1,2)='%s'",m_lstCorpID[nSel]);
		szSQL+=strTemp;
	}
	szSQL+=")";
	szSQL+=" order by mf_code";

	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		m_lstFactID.Add(dm1->Query1->FieldByName("mf_code")->AsString.c_str());
		lstFactory->Items->Add(dm1->Query1->FieldByName("mf_shortname")->AsString);
		dm1->Query1->Next();
	}
}

void __fastcall TBookMultiPrnForm::btnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TBookMultiPrnForm::btnQueryClick(TObject *Sender)
{
	int nSel,nYear,nMonth,nDay;
	char strDate0[80],strDate1[80],strTemp[256],strTemp2[256];
	CString szSQL,szFilter,szSH;
	TListItem *pItem;
  TDateTime tDate;

	if((nSel=lstFactory->ItemIndex)<0 || nSel>=m_lstFactID.GetSize())
	{
		ShowMessage("请选择一个有效的厂商");
		return;
	}
	m_szFactID=m_lstFactID[nSel];
	szFilter.Format(" and bf_mfcode='%s'",m_szFactID);

	if((nSel=lstStockHandle->ItemIndex)<0 || nSel>=m_lstHandleID.GetSize())
	{
		ShowMessage("请选择一个有效的采购经办");
		return;
	}
	szSH=m_lstHandleID[nSel];
	sprintf(strTemp," and ap_shcode='%s'",szSH);
	szFilter+=strTemp;

	edtDate0->Text=edtDate0->Text.Trim();
	if(edtDate0->Text.IsEmpty())
	{
		ShowMessage("请输入订购日期");
		return;
	}

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

	sprintf(strTemp," and bf_bookdate between '%s 00:00:00.000' and '%s 23:59:59.998'",strDate0,strDate1);
	szFilter+=strTemp;
	m_szDate=strDate0;

	if((nSel=lstCorp->ItemIndex)>=0 && nSel<m_lstCorpID.GetSize())
	{
		sprintf(strTemp," and substring(ap_reqdepart,1,2)='%s'",m_lstCorpID[nSel]);
		szFilter+=strTemp;
	}

	lstView->Items->Clear();

	szSQL="select * from BookFactory,PurchaseDetail,AskPurchase,materialno,DicUnits"
		" where pd_code=bf_apcode and ap_code=substring(pd_code,1,7) and mn_code=pd_mncode and bf_unit=du_code";
	szSQL+=szFilter;
	szSQL+=" order by bf_bookdate";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		pItem=lstView->Items->Add();
		assert(pItem!=NULL);
		pItem->Caption=dm1->Query1->FieldByName("bf_code")->AsString;
		pItem->SubItems->Add(dm1->Query1->FieldByName("bf_apcode")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("mn_code")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("mn_name")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("bf_mfcard")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("du_name")->AsString);
		pItem->SubItems->Add(FloatField2String(dm1->Query1->FieldByName("bf_count")));
//		pItem->SubItems->Add(FloatField2String(dm1->Query1->FieldByName("bf_price"),2));
//------new 0704----------------------------------------------------------------
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
		pItem->SubItems->Add(IntField2String(dm1->Query1->FieldByName("bf_deliverdays")));
		pItem->SubItems->Add(Field2DateString(dm1->Query1->FieldByName("bf_printdate")));

		dm1->Query1->Next();
	}
	WritePrivateProfileString("BOOKMULTIPRN","REQCORP",lstCorp->Text.c_str()	,INI_FILE_NAME);
}
//---------------------------------------------------------------------------

#include "PrnBookFactory.h"
void __fastcall TBookMultiPrnForm::btnPrintClick(TObject *Sender)
{
	TPrnBookFactoryForm *pPrn;
  CString szSQL;
	int nSel,i,nInvoiceType;
	char strID[80],strTemp[512],strTop[25],strBottom[256],strLeft[256],chPQ;
	AnsiString szInvoice,szInvoiceType,szRcpt,szTel,szGoodAddr,szSDTel,szSHTel,szPM,szTaxType;
	TListItem *pItem;
	bool bSelected;
	CStringArray lstID;

  pPrn=new TPrnBookFactoryForm(this);
  assert(pPrn!=NULL);

        pPrn->QRLabel9->Enabled=true;
        pPrn->QRSysData1->Enabled=true;       //订购单合并列印显示列印日期

  GetPrivateProfileString("BFPRINTSETUP","TOPMARGIN" ,"",strTop ,250,INI_FILE_NAME);
  GetPrivateProfileString("BFPRINTSETUP","BOTTOMMARGIN" ,"",strBottom ,250,INI_FILE_NAME);
  GetPrivateProfileString("BFPRINTSETUP","LEFTMARGIN","",strLeft,250,INI_FILE_NAME);
	if(strTop[0]!='\0' && strLeft[0]!='\0')
  {
  	pPrn->PrnView->Page->TopMargin=atof(strTop);
  	pPrn->PrnView->Page->BottomMargin=atof(strBottom);
    pPrn->PrnView->Page->LeftMargin=atof(strLeft);
  }
       if((nSel=ComboBox1->ItemIndex)>=0 && nSel<m_lstFactID1.GetSize())
          {
           szSQL.Format("select * from Manufactur where mf_code='%s'",m_lstFactID1[nSel]);
           RunSQL(dm1->Query1,szSQL,true);
           if(!dm1->Query1->Eof)
            {
             pPrn->FactName1->Caption=dm1->Query1->FieldByName("mf_name")->AsString;
             pPrn->factname2->Caption="外购厂商全称：";
             pPrn->LinkMan1->Caption=dm1->Query1->FieldByName("mf_linkman")->AsString;
             pPrn->linkman2->Caption="联络人：";
             pPrn->Tel1->Caption=dm1->Query1->FieldByName("mf_tel")->AsString;
             pPrn->tel2->Caption="TEL：";
             pPrn->Fax1->Caption=dm1->Query1->FieldByName("mf_fax")->AsString;
             pPrn->fax2->Caption="FAX：";
            }
          }
     else
       {
             pPrn->FactName1->Caption="";
             pPrn->factname2->Caption="";
             pPrn->LinkMan1->Caption="";
             pPrn->linkman2->Caption="";
             pPrn->Tel1->Caption="";
             pPrn->tel2->Caption="";
             pPrn->Fax1->Caption="";
             pPrn->fax2->Caption="";
       }

	bSelected=false;
	nInvoiceType=-1;
	chPQ='\0';
	for(i=0;i<lstView->Items->Count;i++)
	{
		pItem=lstView->Items->Item[i];
		if(!pItem->Selected)	continue;
		lstID.Add(pItem->Caption.c_str());

		bSelected=true;

		strcpy(strTemp,pItem->SubItems->Strings[0].c_str());
		if(chPQ=='\0')	chPQ=strTemp[0];
		else if(strTemp[0]!=chPQ)
		{
			ShowMessage("一般采购与合约采购的订单请不要一起列印");
			delete pPrn;
			return;
		}

		if(chPQ=='P')
		{
   		szSQL.Format("select * from CompareFactory,DicPayment"
				" where cf_pmcode=pm_code and cf_apcode='%s' and cf_mfcode='%s'",pItem->SubItems->Strings[0].c_str(),m_szFactID);
			 RunSQL(dm1->Query1,szSQL,true);
			 if(szPM.IsEmpty())	szPM=dm1->Query1->FieldByName("pm_name")->AsString;
			 else if(szPM!=dm1->Query1->FieldByName("pm_name")->AsString)
			{
				ShowMessage("您选择的订购单付款方式不相同");
				delete pPrn;
				return;
			}
			if(szTaxType.IsEmpty())	szTaxType=dm1->Query1->FieldByName("cf_invoice")->AsString;
			else if(szTaxType!=dm1->Query1->FieldByName("cf_invoice")->AsString)
			{
				ShowMessage("您选择的订购单发票税率不相同");
				delete pPrn;
				return;
			}
			pPrn->txtTaxType->Caption=szTaxType;
		}
		else
		{
			szSQL.Format("select * from Manufactur,DicInvoice"
				" where mf_taxtype=di_code and mf_code='%s'",
				m_szFactID);
			RunSQL(dm1->Query1,szSQL,true);
			if(!dm1->Query1->Eof)
			{
				pPrn->txtTaxType->Caption=dm1->Query1->FieldByName("di_name")->AsString;
			}
			else
			{
				pPrn->txtTaxType->Caption="";
			}
		}

		szSQL.Format("select * from BookFactory where bf_code='%s'",pItem->Caption.c_str());
		RunSQL(dm1->Query1,szSQL,true);
		if(szInvoice.IsEmpty())	szInvoice=dm1->Query1->FieldByName("bf_itcode")->AsString;
		else if(szInvoice!=dm1->Query1->FieldByName("bf_itcode")->AsString)
		{
			ShowMessage("您选择的订购单发票抬头不相同");
      delete pPrn;
			return;
		}
		if(!dm1->Query1->FieldByName("bf_invoiceType")->IsNull)
		{
			if(nInvoiceType==-1)	nInvoiceType=dm1->Query1->FieldByName("bf_invoicetype")->AsInteger;
			else if(nInvoiceType!=dm1->Query1->FieldByName("bf_invoiceType")->AsInteger)
			{
				ShowMessage("您选择的订购单发票类型不相同");
        delete pPrn;
				return;
			}
		}
		if(szRcpt.IsEmpty())	szRcpt=dm1->Query1->FieldByName("bf_rhcode")->AsString;
		else if(szRcpt!=dm1->Query1->FieldByName("bf_rhcode")->AsString)
		{
			ShowMessage("您选择的订购单收料经办不相同");
      delete pPrn;
			return;
		}
		strcpy(strID,dm1->Query1->FieldByName("bf_apcode")->AsString.c_str());
		if(strID[0]=='0')	return;
		strID[strlen(strID)-1]='\0';
		szSQL.Format("select * from AskPurchase,GoodsAddr where ga_code=ap_gacode"
			" and ap_code='%s'",strID);
		RunSQL(dm1->Query2,szSQL,true);
		if(szGoodAddr.IsEmpty())
			szGoodAddr=dm1->Query2->FieldByName("ga_area")->AsString+dm1->Query2->FieldByName("ga_name")->AsString;
		else if(szGoodAddr!=dm1->Query2->FieldByName("ga_area")->AsString+dm1->Query2->FieldByName("ga_name")->AsString)
		{
			ShowMessage("您选择的订购单交货地址不相同");
      delete pPrn;
			return;
		}
    strcpy(strID,dm1->Query2->FieldByName("ap_shcode")->AsString.c_str());
		if(strID[0]!='\0')
  	{
    	szSQL.Format("select * from StockHandleman where sh_code='%s'",strID);
			RunSQL(dm1->Query2,szSQL,true);
			pPrn->StockMan->Caption=dm1->Query2->FieldByName("sh_name")->AsString;
      szSHTel=dm1->Query2->FieldByName("sh_tel")->AsString;
			if(dm1->Query2->FieldByName("sh_sdcode")->AsString!="5")
      	pPrn->txtTail->Enabled=false; //非宏育不打印补充说明      
			szSQL.Format("select * from StockDepart where sd_code='%s'",dm1->Query2->FieldByName("sh_sdcode")->AsString.c_str());
			RunSQL(dm1->Query2,szSQL,true);
      szSDTel=dm1->Query2->FieldByName("sd_tel")->AsString;
//      pPrn->txtSDTel->Caption=dm1->Query2->FieldByName("sd_tel")->AsString + " ，分机："
//        + pPrn->txtSubTel->Caption;
//      pPrn->txtSubTel->Caption="";
    }
	}
  if(!bSelected)
	{
  	ShowMessage("请选择一个或多个项次");
    delete pPrn;
    return;
  }
	if(!szInvoice.IsEmpty())
	{
		szSQL.Format("select * from InvoiceTitle where it_code='%s'",szInvoice.c_str());
		RunSQL(dm1->Query1,szSQL,true);
		szInvoice=dm1->Query1->FieldByName("it_name")->AsString;
	}
	if(!szRcpt.IsEmpty())
	{
		szSQL.Format("select * from RcptHandleman where rh_code='%s'",szRcpt.c_str());
		RunSQL(dm1->Query1,szSQL,true);
		szRcpt=dm1->Query1->FieldByName("rh_name")->AsString;
		szTel=dm1->Query1->FieldByName("rh_tel")->AsString;
	}
	if(nInvoiceType==1)				szInvoiceType="月底开立发票";
	else if(nInvoiceType==2)	szInvoiceType="随货附发票";
	else if(nInvoiceType==3)	szInvoiceType="报关单";
	else if(nInvoiceType==4)	szInvoiceType="进口报关单";
	else if(nInvoiceType==5)	szInvoiceType="出口报关单";

	szSQL.Format("select * from Manufactur where mf_code='%s'",m_szFactID);
	RunSQL(dm1->Query1,szSQL,true);
	if(!dm1->Query1->Eof)
	{
		pPrn->FactName->Caption=dm1->Query1->FieldByName("mf_name")->AsString;
		pPrn->LinkMan->Caption=dm1->Query1->FieldByName("mf_linkman")->AsString;
//		pPrn->ReqID->Caption=edtAPCode->Text;
//		pPrn->BookID->Caption=edtBookID->Text;
		pPrn->Tel->Caption=dm1->Query1->FieldByName("mf_tel")->AsString;
		pPrn->Fax->Caption=dm1->Query1->FieldByName("mf_fax")->AsString;
	}

  if(!szPM.IsEmpty())
  {
		sprintf(strTemp,"口付款方式:%s",szPM.c_str());
		pPrn->txtPayment->Caption=strTemp;
	}

	pPrn->RcptName->Caption=szRcpt;
	pPrn->RcptTel->Caption=szTel;
	pPrn->txtSubTel->Caption=szSHTel;

  pPrn->txtSDTel->Caption=szSDTel + " ，分机：" + pPrn->txtSubTel->Caption;
  pPrn->txtSubTel->Caption="";

	pPrn->Invoice->Caption=szInvoice;
  pPrn->BookDate->Caption=m_szDate;
	pPrn->txtInvoiceType->Caption=szInvoiceType;
	pPrn->GoodsAddr->Caption=szGoodAddr;
	pPrn->StockMan->Caption=lstStockHandle->Text;

	szSQL="select * from BookFactory,Manufactur,DicUnits,PurchaseDetail,materialno"
		" where bf_mfcode=mf_code and du_code=bf_unit and pd_code=bf_apcode"
		" and mn_code=pd_mncode";
	sprintf(strTemp," and bf_code in('%s'",lstID[0]);
	szSQL+=strTemp;
	for(i=1;i<lstID.GetSize();i++)
	{
		sprintf(strTemp,",'%s'",lstID[i]);
		szSQL+=strTemp;
	}
	szSQL+=")";
  szSQL+=" order by bf_code";
  
	if(!OpenQuery(dm1->sqlPrint,szSQL))	return;

  pPrn->PrnView->PreviewModal();
  delete pPrn;

	TDateTime tNow=GetSysTime(false);
	for(i=0;i<lstView->Items->Count;i++)
	{
		pItem=lstView->Items->Item[i];
		if(!pItem->Selected)	continue;

		szSQL.Format("update BookFactory set bf_printdate='%s' where bf_code='%s'",
			Time2DBTimeString(tNow),pItem->Caption.c_str());
		RunSQL(dm1->Query1,szSQL);
		pItem->SubItems->Strings[8]=(LPCSTR)Time2DBDateString(tNow);
	}
}
//---------------------------------------------------------------------------

void __fastcall TBookMultiPrnForm::btnDetailClick(TObject *Sender)
{
	TListItem *pItem;
	if((pItem=lstView->Selected)==NULL)	return;

	int nRight=GetOperatorRight(operatorcode.c_str(),"IDM_BOOKFACTORY");
	//订购单输入接口，文件：BookFactory.*
	BookFactory(pItem->Caption.c_str(),nRight);
}
//---------------------------------------------------------------------------

void __fastcall TBookMultiPrnForm::lstFactoryExit(TObject *Sender)
{
	HandleListboxExit(lstFactory,&m_lstFactID);
}
//---------------------------------------------------------------------------

void __fastcall TBookMultiPrnForm::lstViewDblClick(TObject *Sender)
{
	btnDetailClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TBookMultiPrnForm::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
	if(Key==VK_RETURN)	KeyReturnHandle(ActiveControl);
}
//---------------------------------------------------------------------------

void __fastcall TBookMultiPrnForm::btnPickupClick(TObject *Sender)
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

void __fastcall TBookMultiPrnForm::lstStockHandleExit(TObject *Sender)
{
	ResetFactList();
}
//---------------------------------------------------------------------------

void __fastcall TBookMultiPrnForm::lstCorpExit(TObject *Sender)
{
	ResetFactList();
}
//---------------------------------------------------------------------------

