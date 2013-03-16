//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <assert.h>
#pragma hdrstop

#include "DataModule.h"
#include "BaseCode.h"
#include "BookFactory.h"
#include "TConst.h"
#include "LdyInterface.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TBookFactoryForm *BookFactoryForm;

//==================================================================
//订购单输入接口，文件：BookFactory.*
void BookFactory(int nAuth)
{
	BookFactory(NULL,nAuth);
}
void BookFactory(LPCSTR lpszID,int nAuth)
{
	if(nAuth==AUTH_NONE)	return;

  TBookFactoryForm *pForm;
	pForm=new TBookFactoryForm(Application);
	assert(pForm!=NULL);
	if(lpszID!=NULL)	pForm->m_szIDFirst=lpszID;
	pForm->m_nAuthor=nAuth;
	pForm->ShowModal();
	delete pForm;
}

//---------------------------------------------------------------------------
__fastcall TBookFactoryForm::TBookFactoryForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TBookFactoryForm::FormShow(TObject *Sender)
{
	CString szSQL;
	int i,nSel;
        char strTemp[256];
	BASE4COLDATA rwBase4;

    if(g_theOperator.op_cpcode[0]=='C' || operatorcode=="admin")
     {
        wfactory->Enabled=true;
        wfactory->Text="";
        szSQL="select * from Manufactur where mf_code='Y001'";
        RunSQL(dm1->Query1,szSQL,true);
        while(!dm1->Query1->Eof)
         {
          m_lstFactID1.Add(dm1->Query1->FieldByName("mf_code")->AsString.c_str());
          wfactory->Items->Add(dm1->Query1->FieldByName("mf_name")->AsString);
          dm1->Query1->Next();
         }
        wfactory->ItemIndex=-1;
     }
    else
      {
       wfactory->Enabled=false;
      }
	
	szSQL="select * from RcptHandleman order by rh_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		strcpy(rwBase4.strCode,dm1->Query1->FieldByName("rh_code")->AsString.c_str());
		strcpy(rwBase4.strName,dm1->Query1->FieldByName("rh_name")->AsString.c_str());
		strcpy(rwBase4.strCol2,dm1->Query1->FieldByName("rh_cpcode")->AsString.c_str());
		m_lstRcptAll.Add(rwBase4);
		dm1->Query1->Next();
	}
	ResetRcptHandle();
	lstHandle->Text="";
	lstHandle->ItemIndex=-1;

	szSQL="select * from Manufactur order by mf_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		m_lstFactID.Add(dm1->Query1->FieldByName("mf_code")->AsString.c_str());
		lstFactory->Items->Add(dm1->Query1->FieldByName("mf_shortname")->AsString);
		dm1->Query1->Next();
	}

	szSQL="select * from InvoiceTitle order by it_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		m_lstInvoiceID.Add(dm1->Query1->FieldByName("it_code")->AsString.c_str());
		lstInvoice->Items->Add(dm1->Query1->FieldByName("it_name")->AsString);
		dm1->Query1->Next();
	}
	lstInvoice->Text="";
	lstInvoice->ItemIndex=-1;
	lstInvoiceType->ItemIndex=0;

	szSQL="select * from diccurrency order by dc_code";
	RunSQL(dm1->Query1,szSQL,true);
	i=0;
	nSel=0;
	while(!dm1->Query1->Eof)
	{
		m_lstRMBID.Add(dm1->Query1->FieldByName("dc_code")->AsString.c_str());
		if(dm1->Query1->FieldByName("dc_code")->AsString=="RMB")	nSel=i;
		lstRMB->Items->Add(dm1->Query1->FieldByName("dc_name")->AsString);
		dm1->Query1->Next();
		i++;
	}
	lstRMB->ItemIndex=nSel;

	edtBookID		->Text="";
	edtAPCode		->Text="";
	edtBookDate	->Text="";
//	edtFactory	->Text="";
	lstFactory	->ItemIndex=-1;
	edtCard			->Text="";
	edtUnit			->Text="";
	edtCount		->Text="";
	edtPrice		->Text="";
	edtDays			->Text="";
  edtRem			->Text="";

	m_enState=EN_STATE_IDLE;
	ResetCtrl();

	if(!m_szIDFirst.IsEmpty())
	{
		edtBookID->Text=m_szIDFirst;
		btnQueryClick(Sender);
	}
}
//---------------------------------------------------------------------------

void TBookFactoryForm::ResetCtrl()
{
	bool bIdle,bAuth,bSHMyself;
  char strAPCode[80];

	bSHMyself = m_szSHCode==operatorcode || operatorcode=="admin";
	bIdle = m_enState==EN_STATE_IDLE;
	bAuth = m_nAuthor==AUTH_FULL;
	EnableEdit(edtBookID		,m_enState!=EN_STATE_EDIT);
	EnableEdit(edtBookDate	,!bIdle);
	EnableEdit(edtAPCode		,!bIdle);
//  btnAPCode->Enabled=edtAPCode->Enabled;
	EnableCombo(lstHandle		,!bIdle);
//	EnableEdit(edtFactory		,false);
  strcpy(strAPCode,edtAPCode->Text.c_str());
  if(strAPCode[0]=='Q')
	{
		EnableCombo(lstFactory	,false);
		EnableCombo(lstShowDate	,false);
	}
  else
	{
		EnableCombo(lstFactory	,!bIdle);
		EnableCombo(lstShowDate	,!bIdle);
	}
	EnableEdit(edtCard			,!bIdle);
	EnableEdit(edtUnit			,false);
	EnableEdit(edtCount			,!bIdle);
	EnableEdit(edtPrice			,false);
//	EnableEdit(edtPrice			,m_enState==EN_STATE_EDIT && strAPCode[0]=='Q' && bSHMyself && operatorcode=="admin");
	EnableEdit(edtDays			,false);
	EnableEdit(edtRem				,!bIdle);
	EnableCombo(lstInvoice	,!bIdle);
	EnableCombo(lstInvoiceType,!bIdle);
	EnableCombo(lstRMB			,false);
  EnableCombo(lstBuyKind	,!bIdle);

	btnQuery	->Enabled = bIdle;
	btnNew		->Enabled = bIdle && bAuth;
	btnEdit		->Enabled = bIdle && bAuth && !m_szActiveID.IsEmpty() && bSHMyself;
	btnMove		->Enabled = bIdle && bAuth && !m_szActiveID.IsEmpty() && bSHMyself;
	btnPrint	->Enabled = bIdle;
	btnOK			->Enabled = !bIdle;
	btnExit	->Caption = bIdle ? "退    出" : "放    弃";
}

void __fastcall TBookFactoryForm::btnExitClick(TObject *Sender)
{
	if(m_enState==EN_STATE_IDLE)
		Close();	
	else
	{
		m_enState=EN_STATE_IDLE;
		ResetCtrl();
	}
}
//---------------------------------------------------------------------------

void __fastcall TBookFactoryForm::btnQueryClick(TObject *Sender)
{
	CString szSQL;
	char strID[80],strTemp[256],strMN[80];
	int i;

	edtBookID->Text=edtBookID->Text.Trim();
	if(edtBookID->Text.IsEmpty())
	{
		ShowMessage("请输入编号");
		if(edtBookID->CanFocus())	edtBookID->SetFocus();
		return;
	}
	szSQL.Format("select * from BookFactory,DicUnits,PurchaseDetail"
		" where bf_apcode=pd_code and bf_unit=du_code and bf_code='%s'",edtBookID->Text.c_str());
	RunSQL(dm1->Query1,szSQL,true);
	if(dm1->Query1->Eof)
	{
		ShowMessage("没有该编号的数据");
		m_szActiveID="";
		ResetCtrl();
		if(edtBookID->CanFocus())	edtBookID->SetFocus();
		return;
	}
	strcpy(strMN,dm1->Query1->FieldByName("pd_mncode")->AsString.c_str());
	edtBookDate->Text=DateField2Text(dm1->Query1->FieldByName("bf_bookdate"));
	edtAPCode->Text=dm1->Query1->FieldByName("bf_apcode")->AsString;
	strcpy(strID,dm1->Query1->FieldByName("bf_rhcode")->AsString.c_str());
  strcpy(strTemp,dm1->Query1->FieldByName("bf_buykind")->AsString.c_str());

	ResetAPData(edtAPCode->Text.c_str());

  switch(strTemp[0])
	{
  	case 'A':	lstBuyKind->ItemIndex=0;	break;
    case 'B':	lstBuyKind->ItemIndex=1;	break;
    case 'C':	lstBuyKind->ItemIndex=2;	break;
    default:	lstBuyKind->ItemIndex=-1;	break;
  }
	for(i=0;i<m_lstHandleID.GetSize();i++)
	{
		if(m_lstHandleID[i]==strID)
		{
			lstHandle->ItemIndex=i;
			break;
		}
	}
	if(i==m_lstHandleID.GetSize())	lstHandle->ItemIndex=-1;

	strcpy(strID,dm1->Query1->FieldByName("bf_itcode")->AsString.c_str());
	for(i=0;i<m_lstInvoiceID.GetSize();i++)
	{
		if(m_lstInvoiceID[i]==strID)
		{
			lstInvoice->ItemIndex=i;
			break;
		}
	}
	if(i==m_lstInvoiceID.GetSize())	lstInvoice->ItemIndex=-1;

	strcpy(strTemp,edtAPCode->Text.c_str());
	strTemp[7]='\0';
	szSQL.Format("select * from AskPurchase where ap_code='%s'",strTemp);
	RunSQL(dm1->Query2,szSQL,true);
	m_szSHCode=dm1->Query2->FieldByName("ap_shcode")->AsString;

	edtCard->Text=dm1->Query1->FieldByName("bf_mfcard")->AsString;
	m_szUnitID=dm1->Query1->FieldByName("bf_unit")->AsString;
	edtUnit->Text=dm1->Query1->FieldByName("du_name")->AsString;
	edtCount->Text=FloatField2String(dm1->Query1->FieldByName("bf_count"),2);

	if(operatorcode==m_szSHCode || operatorcode=="admin" || operatorcode=="108557")                   //本单的经办才可查看单价   0704
	{
		if(strMN[0]=='E' && strMN[1]=='M')
			edtPrice->Text=FloatField2String(dm1->Query1->FieldByName("bf_price"),6);
		else
//			edtPrice->Text=FloatField2String(dm1->Query1->FieldByName("bf_price"),4);
                        if (strTemp[0]=='P')
                        {//一般采购
        			edtPrice->Text=FloatField2String(dm1->Query1->FieldByName("bf_price"),4);
                        }
                        else if (strTemp[0]=='Q')
                        {
			        edtPrice->Text=FloatField2String(dm1->Query1->FieldByName("bf_price"),8);        //提高精度
                        }
	}
	else
		edtPrice->Text="";

	for(i=0;i<m_lstRMBID.GetSize();i++)
	{
		if(m_lstRMBID[i]==dm1->Query1->FieldByName("bf_dccode")->AsString.c_str())
		{
			lstRMB->ItemIndex=i;
			break;
		}
	}
	if(i==m_lstRMBID.GetSize())	lstRMB->ItemIndex=-1;

	edtDays->Text=IntField2String(dm1->Query1->FieldByName("bf_deliverdays"));
	edtRem->Text=dm1->Query1->FieldByName("bf_rem")->AsString;
	if(dm1->Query1->FieldByName("bf_invoicetype")->IsNull)
		lstInvoiceType->ItemIndex=-1;
//	else if(dm1->Query1->FieldByName("bf_invoiceType")->AsInteger==1)	lstInvoiceType->ItemIndex=0;
//	else	lstInvoiceType->ItemIndex=1;
  lstInvoiceType->ItemIndex=dm1->Query1->FieldByName("bf_invoiceType")->AsInteger-1;

	m_szFactID=dm1->Query1->FieldByName("bf_mfcode")->AsString;
//	szSQL.Format("select * from Manufactur where mf_code='%s'",m_szFactID.c_str());
//	RunSQL(dm1->Query1,szSQL,true);
//	if(dm1->Query1->Eof)
//		edtFactory->Text="";
//	else	edtFactory->Text=dm1->Query1->FieldByName("mf_shortname")->AsString;

	for(i=0;i<m_lstFactID.GetSize();i++)
	{
		if(m_lstFactID[i]==m_szFactID.c_str())
		{
			lstFactory->ItemIndex=i;
			break;
		}
	}
	if(i==m_lstFactID.GetSize())
  {
  	lstFactory->ItemIndex=-1;
    lstFactory->Text=m_szFactID;
//	else	edtFactory->Text=dm1->Query1->FieldByName("mf_shortname")->AsString;
	}
  ResetShowDate();
	lstShowDate->ItemIndex=lstShowDate->Items->IndexOf(DateField2Text(dm1->Query1->FieldByName("bf_showdate")));

	m_szActiveID=edtBookID->Text.c_str();
	ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TBookFactoryForm::btnNewClick(TObject *Sender)
{
	int nYear,nMonth,nDay,i;
	char strDate[80];

	m_enState=EN_STATE_NEW;
	ResetCtrl();
	edtBookID->Text=(LPCSTR)GenerateID();
	GetSysDate(nYear,nMonth,nDay,false);
	sprintf(strDate,"%04d%02d%02d",nYear,nMonth,nDay);
	edtBookDate->Text=strDate;

	for(i=0;i<m_lstRMBID.GetSize();i++)
	{
		if(m_lstRMBID[i]=="RMB")
		{
			lstRMB->ItemIndex=i;
			break;
		}
	}
	if(i==m_lstRMBID.GetSize())	lstRMB->ItemIndex=0;

  lstBuyKind->ItemIndex=0; //采购形态缺省为"一般贸易"
	if(edtBookID->CanFocus())	edtBookID->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TBookFactoryForm::btnEditClick(TObject *Sender)
{
	if(m_szActiveID.IsEmpty())	return;
	edtBookID->Text=edtBookID->Text.Trim();
  if(m_szActiveID!=edtBookID->Text.c_str())
  {
  	ShowMessage("您输入的编号与正在查询的编号不同");
    return;
  }
	if(!CanModify())	return;

	m_enState=EN_STATE_EDIT;
	ResetCtrl();
	if(edtBookDate->CanFocus())	edtBookDate->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TBookFactoryForm::btnMoveClick(TObject *Sender)
{
	CString szSQL;
	char strTemp[80];

	if(m_szActiveID.IsEmpty())	return;
	if(m_szActiveID!=edtBookID->Text.c_str())
	{
		ShowMessage("您输入的编号与正在查询的不同");
		return;
	}

	szSQL.Format("select * from BookFactory where bf_code='%s'",m_szActiveID);
	RunSQL(dm1->Query1,szSQL,true);
	if(dm1->Query1->Eof)
	{
		ShowMessage("没有该编号的数据");
		return;
	}

	strcpy(strTemp,edtAPCode->Text.c_str());
	strTemp[7]='\0';
	szSQL.Format("select * from AskPurchase where ap_code='%s'",strTemp);
	RunSQL(dm1->Query1,szSQL,true);
	if(dm1->Query1->Eof)
	{
		ShowMessage("该请购单不存在，可能是被其他人删除了");
		return;
	}
	if(operatorcode!=dm1->Query1->FieldByName("ap_shcode")->AsString && operatorcode!="admin" && operatorcode!="108557")
	{
		ShowMessage("只有admin和采购经办自己才能新增、删除或修改请购单的订购内容");
		return;
	}

	if(!CanModify())	return;

	if(Application->MessageBox("真要删除选定的编号吗","警告",MB_YESNOCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2)!=IDYES)	return;
	szSQL.Format("delete BookFactory where bf_code='%s'",m_szActiveID);
	if(!RunSQL(dm1->Query1,szSQL))	return;
	m_szActiveID="";
	ResetCtrl();
	edtAPCode		->Text="";
	edtBookDate	->Text="";
//	edtFactory	->Text="";
	lstFactory	->ItemIndex=-1;
	edtCard			->Text="";
	edtUnit			->Text="";
	edtCount		->Text="";
	edtPrice		->Text="";
	edtDays			->Text="";
	ShowMessage("已成功删除了该编号的订购单");
}
//---------------------------------------------------------------------------

#include "PrnBookFactory.h"
void __fastcall TBookFactoryForm::btnPrintClick(TObject *Sender)
{
	TPrnBookFactoryForm *pPrn;
  CString szSQL;
	int nSel;
	char strID[80],strTemp[256],strTop[256],strBottom[256],strLeft[256];
  TDateTime tNow;

  if(m_szActiveID.IsEmpty())	return;
  pPrn=new TPrnBookFactoryForm(this);
  assert(pPrn!=NULL);

        pPrn->QRLabel15->Enabled=true;
        pPrn->BookDate->Enabled=true;       //订购单合并列印显示订购日期  

  GetPrivateProfileString("BFPRINTSETUP","TOPMARGIN" ,"",strTop ,250,INI_FILE_NAME);
  GetPrivateProfileString("BFPRINTSETUP","BOTTOMMARGIN" ,"",strBottom ,250,INI_FILE_NAME);
  GetPrivateProfileString("BFPRINTSETUP","LEFTMARGIN","",strLeft,250,INI_FILE_NAME);
	if(strTop[0]!='\0' && strLeft[0]!='\0')
  {
  	pPrn->PrnView->Page->TopMargin=atof(strTop);
  	pPrn->PrnView->Page->BottomMargin=atof(strBottom);
    pPrn->PrnView->Page->LeftMargin=atof(strLeft);
  }

	if(!m_szFactID.IsEmpty())
	{
		szSQL.Format("select * from Manufactur where mf_code='%s'",m_szFactID.c_str());
		RunSQL(dm1->Query1,szSQL,true);
		if(!dm1->Query1->Eof)
		{
			pPrn->FactName->Caption=dm1->Query1->FieldByName("mf_name")->AsString;
			pPrn->LinkMan->Caption=dm1->Query1->FieldByName("mf_linkman")->AsString;
//			pPrn->ReqID->Caption=edtAPCode->Text;
//			pPrn->BookID->Caption=edtBookID->Text;
			pPrn->Tel->Caption=dm1->Query1->FieldByName("mf_tel")->AsString;
			pPrn->Fax->Caption=dm1->Query1->FieldByName("mf_fax")->AsString;
		}
	}

     if((nSel=wfactory->ItemIndex)>=0 && nSel<m_lstFactID1.GetSize())
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

	if((nSel=lstHandle->ItemIndex)>=0 && nSel<m_lstHandleID.GetSize())
	{
		szSQL.Format("select * from RcptHandleman where rh_code='%s'",m_lstHandleID[nSel]);
		RunSQL(dm1->Query1,szSQL,true);
		if(!dm1->Query1->Eof)
		{
			pPrn->RcptName->Caption=dm1->Query1->FieldByName("rh_name")->AsString;
			pPrn->RcptTel->Caption=dm1->Query1->FieldByName("rh_tel")->AsString;
		}
	}
	pPrn->Invoice->Caption=lstInvoice->Text;
  pPrn->BookDate->Caption=edtBookDate->Text;

//	if(lstInvoiceType->ItemIndex==0)			pPrn->txtInvoiceType->Caption="月底开立发票";
//	else if(lstInvoiceType->ItemIndex==1)	pPrn->txtInvoiceType->Caption="随货附发票";
//	else pPrn->txtInvoiceType->Caption="";
  pPrn->txtInvoiceType->Caption=lstInvoiceType->Text;

  strcpy(strID,edtAPCode->Text.c_str());
	if(strID[0]!='\0' && !m_szFactID.IsEmpty())
	{
		if(strID[0]=='P')
		{
   		szSQL.Format("select * from CompareFactory,DicPayment"
				" where cf_pmcode=pm_code and cf_apcode='%s' and cf_mfcode='%s'",strID,m_szFactID.c_str());
			RunSQL(dm1->Query1,szSQL,true);
			if(!dm1->Query1->Eof)
   		{
				sprintf(strTemp,"口付款方式:%s",dm1->Query1->FieldByName("pm_name")->AsString.c_str());
				pPrn->txtPayment->Caption=strTemp;
				pPrn->txtTaxType->Caption=dm1->Query1->FieldByName("cf_invoice")->AsString;
			}
			else
			{
    		pPrn->txtTaxType->Caption="";
			}
		}
		else
		{
			szSQL.Format("select * from Manufactur,DicInvoice where mf_taxtype=di_code and mf_code='%s'",
				m_szFactID.c_str());
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

		strID[strlen(strID)-1]='\0';
		szSQL.Format("select * from AskPurchase,GoodsAddr where ga_code=ap_gacode"
			" and ap_code='%s'",strID);
		RunSQL(dm1->Query1,szSQL,true);
		if(!dm1->Query1->Eof)
		{
			pPrn->GoodsAddr->Caption=dm1->Query1->FieldByName("ga_area")->AsString
				+dm1->Query1->FieldByName("ga_name")->AsString;
		}
    strcpy(strID,dm1->Query1->FieldByName("ap_shcode")->AsString.c_str());
		if(strID[0]!='\0')
  	{
    	szSQL.Format("select * from StockHandleman where sh_code='%s'",strID);
			RunSQL(dm1->Query1,szSQL,true);
			pPrn->StockMan->Caption=dm1->Query1->FieldByName("sh_name")->AsString;
			pPrn->txtSubTel->Caption=dm1->Query1->FieldByName("sh_tel")->AsString;
			if(dm1->Query1->FieldByName("sh_sdcode")->AsString!="5")
      	pPrn->txtTail->Enabled=false; //非宏育不打印补充说明      
			szSQL.Format("select * from StockDepart where sd_code='%s'",dm1->Query1->FieldByName("sh_sdcode")->AsString.c_str());
			RunSQL(dm1->Query1,szSQL,true);
      pPrn->txtSDTel->Caption=dm1->Query1->FieldByName("sd_address")->AsString + "  "
				+ dm1->Query1->FieldByName("sd_tel")->AsString + " ，分机："
        + pPrn->txtSubTel->Caption;
      pPrn->txtSubTel->Caption="";
    }
	}

	szSQL.Format("select * from BookFactory,Manufactur,DicUnits,PurchaseDetail,materialno"
		" where bf_mfcode=mf_code and du_code=bf_unit and pd_code=bf_apcode"
		" and mn_code=pd_mncode"
		" and bf_code='%s'",m_szActiveID);
	if(!OpenQuery(dm1->sqlPrint,szSQL))	return;

  pPrn->PrnView->PreviewModal();
  delete pPrn;

  tNow=GetSysTime(false);
  szSQL.Format("update BookFactory set bf_printdate='%s' where bf_code='%s'",
  	Time2DBTimeString(tNow),m_szActiveID);
  RunSQL(dm1->Query1,szSQL);
}
//---------------------------------------------------------------------------

void __fastcall TBookFactoryForm::btnOKClick(TObject *Sender)
{
	CString szSQL;
	int nInvoiceType;
	char strTemp[80],strMN[80],strApcode[80];

	if(!CheckEditor())	return;

	szSQL.Format("select * from PurchaseDetail where pd_code='%s'",edtAPCode->Text.c_str());
	RunSQL(dm1->Query1,szSQL,true);
	if(dm1->Query1->Eof)	return;
	strcpy(strMN,dm1->Query1->FieldByName("pd_mncode")->AsString.c_str());
        strcpy(strApcode,edtAPCode->Text.c_str());
        	
	nInvoiceType=lstInvoiceType->ItemIndex+1;

	if(m_enState==EN_STATE_NEW)
	{
		szSQL="insert into BookFactory (bf_code,bf_bookdate,bf_apcode,bf_mfcode,bf_showdate,bf_mfcard,"
			"bf_unit,bf_count,bf_price,bf_dccode,bf_deliverdays,bf_rhcode,bf_itcode,"
                        "bf_invoicetype,bf_rem,bf_buykind"
                        ") values(";
		szSQL+=Str2DBString(edtBookID->Text.c_str());
		szSQL+=",";	szSQL+=Text2DBDate(edtBookDate->Text).c_str();
		szSQL+=",";	szSQL+=Str2DBString(edtAPCode->Text.c_str());
		szSQL+=",";	szSQL+=Str2DBString(m_szFactID.c_str());
                szSQL+=",";	szSQL+=Text2DBDate(lstShowDate->Text).c_str();
		szSQL+=",";	szSQL+=Str2DBString(edtCard->Text.c_str());
		szSQL+=",";	szSQL+=Str2DBString(m_szUnitID.c_str());
		szSQL+=",";	szSQL+=Text2DBFloat(edtCount->Text,2).c_str();
		if(strMN[0]=='E' && strMN[1]=='M')
                {
			szSQL+=",";	szSQL+=Text2DBFloat(edtPrice->Text,6).c_str();
                }
		else
                {
//			szSQL+=",";	szSQL+=Text2DBFloat(edtPrice->Text,4).c_str();
                        if (strApcode[0]=='P')
                        {//一般采购
                                szSQL+=",";	szSQL+=Text2DBFloat(edtPrice->Text,4).c_str();
                        }
                        else if (strApcode[0]=='Q')
                        {//统购
			        szSQL+=",";	szSQL+=Text2DBFloat(edtPrice->Text,8).c_str();  //提高精度
                        }
                }
		szSQL+=",";	szSQL+=Str2DBString(m_lstRMBID[lstRMB->ItemIndex]);
		szSQL+=",";	szSQL+=Text2DBInt(edtDays->Text).c_str();
		szSQL+=",";	szSQL+=Str2DBString(m_lstHandleID[lstHandle->ItemIndex]);
		szSQL+=",";	szSQL+=Str2DBString(m_lstInvoiceID[lstInvoice->ItemIndex]);
		szSQL+=",";	szSQL+=Int2DBString(nInvoiceType);
		szSQL+=",";	szSQL+=Str2DBString(edtRem->Text.c_str());
    if(lstBuyKind->ItemIndex<0)	strTemp[0]='\0';
    else	sprintf(strTemp,"%c",'A'+lstBuyKind->ItemIndex);
    szSQL+=",";	szSQL+=Str2DBString(strTemp);
		szSQL+=")";
		if(!RunSQL(dm1->Query1,szSQL))	return;

		m_szActiveID=edtBookID->Text.c_str();
		m_enState=EN_STATE_IDLE;
		ResetCtrl();
	}
	else if(m_enState==EN_STATE_EDIT)
	{
		szSQL="update BookFactory set";
		szSQL+=" bf_bookdate=";		szSQL+=Text2DBDate(edtBookDate->Text).c_str();
		szSQL+=",bf_apcode=";			szSQL+=Str2DBString(edtAPCode->Text.c_str());
		szSQL+=",bf_mfcode=";			szSQL+=Str2DBString(m_szFactID.c_str());
                szSQL+=",bf_showdate=";		szSQL+=Text2DBDate(lstShowDate->Text).c_str();
		szSQL+=",bf_mfcard=";			szSQL+=Str2DBString(edtCard->Text.c_str());
		szSQL+=",bf_unit=";				szSQL+=Str2DBString(m_szUnitID.c_str());
		szSQL+=",bf_count=";			szSQL+=Text2DBFloat(edtCount->Text,2).c_str();
		if(strMN[0]=='E' && strMN[1]=='M')
                {
			szSQL+=",bf_price=";			szSQL+=Text2DBFloat(edtPrice->Text,6).c_str();
                }
		else
                {
//			szSQL+=",bf_price=";			szSQL+=Text2DBFloat(edtPrice->Text,4).c_str();
                        if (strApcode[0]=='P')
                        {//一般采购
                                szSQL+=",bf_price=";			szSQL+=Text2DBFloat(edtPrice->Text,4).c_str();
                        }
                        else if (strApcode[0]=='Q')
                        {//统购
			        szSQL+=",bf_price=";			szSQL+=Text2DBFloat(edtPrice->Text,8).c_str(); //提高精度
                        }
                }
		szSQL+=",bf_dccode=";			szSQL+=Str2DBString(m_lstRMBID[lstRMB->ItemIndex]);
		szSQL+=",bf_deliverdays=";szSQL+=Text2DBInt(edtDays->Text).c_str();
		szSQL+=",bf_rhcode=";			szSQL+=Str2DBString(m_lstHandleID[lstHandle->ItemIndex]);
		szSQL+=",bf_itcode=";			szSQL+=Str2DBString(m_lstInvoiceID[lstInvoice->ItemIndex]);
		szSQL+=",bf_invoicetype=";szSQL+=Int2DBString(nInvoiceType);
		szSQL+=",bf_rem=";				szSQL+=Str2DBString(edtRem->Text.c_str());
                if(lstBuyKind->ItemIndex<0)	strTemp[0]='\0';
                else	sprintf(strTemp,"%c",'A'+lstBuyKind->ItemIndex);
                szSQL+=",bf_buykind=";		szSQL+=Str2DBString(strTemp);
		szSQL+=" where bf_code=";	szSQL+=Str2DBString(edtBookID->Text.c_str());
		if(!RunSQL(dm1->Query1,szSQL))	return;

		m_enState=EN_STATE_IDLE;
		ResetCtrl();
	}
}

bool TBookFactoryForm::CheckEditor()
{
	CString szSQL;
	int nSel;
	char strAP[80],strTemp[80],strSHCode[80];

	if(m_enState==EN_STATE_NEW)
	{
		edtBookID->Text=edtBookID->Text.Trim();
		if(edtBookID->Text.Length()!=8)
		{
			ShowMessage("请输入8位编号");
			if(edtBookID->CanFocus())	edtBookID->SetFocus();
			return false;
		}
		szSQL.Format("select * from BookFactory where bf_code='%s'",edtBookID->Text.c_str());
		RunSQL(dm1->Query1,szSQL,true);
		if(!dm1->Query1->Eof)
		{
			ShowMessage("数据库中已有该编号");
			if(edtBookID->CanFocus())	edtBookID->SetFocus();
			return false;
		}
	}
	else
	{
		if(m_szActiveID.IsEmpty())	return false;

		szSQL.Format("select * from BookFactory where bf_code='%s'",edtBookID->Text.c_str());
		RunSQL(dm1->Query1,szSQL,true);
		if(dm1->Query1->Eof)
		{
			ShowMessage("数据库中没有该编号的数据");
			return false;
		}
	}
	if(lstInvoiceType->ItemIndex<0)
	{
		ShowMessage("请选择一个有效的发票类型");
		return false;
	}
	if(!CheckDateEditor(edtBookDate))	return false;
	edtAPCode->Text=edtAPCode->Text.Trim();
	if(edtAPCode->Text.IsEmpty())
	{
		ShowMessage("请输入请购单编号");
		if(edtAPCode->CanFocus())	edtAPCode->SetFocus();
		return false;
	}
	strcpy(strAP,edtAPCode->Text.c_str());
//	if(strAP[0]=='P' || strAP[0]=='Q')
	{
		szSQL.Format("select * from PurchaseDetail where pd_code='%s'",edtAPCode->Text.c_str());
		RunSQL(dm1->Query1,szSQL,true);
		if(dm1->Query1->Eof)
		{
			ShowMessage("没有该请购单编号");
			if(edtAPCode->CanFocus())	edtAPCode->SetFocus();
			return false;
		}
		strcpy(strTemp,strAP);
		strTemp[7]='\0';

		szSQL.Format("select * from AskPurchase where ap_code='%s'",strTemp);
		RunSQL(dm1->Query1,szSQL,true);
		if(dm1->Query1->Eof)
		{
			ShowMessage("该请购单不存在，可能是被其他人删除了");
			return false;
		}
		if(dm1->Query1->FieldByName("ap_affirmdate")->IsNull)
		{
			ShowMessage("该请购单还没有接案");
			if(edtAPCode->CanFocus())	edtAPCode->SetFocus();
			return false;
		}
		if(dm1->Query1->FieldByName("ap_shcode")->IsNull)
		{
			ShowMessage("该请购单还没有指定采购经办");
			if(edtAPCode->CanFocus())	edtAPCode->SetFocus();
			return false;
		}

		strcpy(strSHCode,dm1->Query1->FieldByName("ap_shcode")->AsString.c_str());
		if(operatorcode!=strSHCode && operatorcode!="admin" && operatorcode!="108557")
		{
			ShowMessage("只有admin和采购经办自己才能新增、删除或修改请购单的订购内容");
			return false;
		}
	}
	if(m_enState==EN_STATE_NEW)
	{
		if(strAP[0]=='P')
		{
			szSQL.Format("select * from BookFactory where bf_apcode='%s'",strAP);
			RunSQL(dm1->Query1,szSQL,true);
			if(!dm1->Query1->Eof)
			{
				if(Application->MessageBox("该请购单已有其他的订购单，确定要新增吗","提示",
					MB_YESNOCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2)!=IDYES)	return false;
			}
		}
	}
	if((nSel=lstHandle->ItemIndex)<0 || nSel>=m_lstHandleID.GetSize())
	{
		ShowMessage("请选择一个有效的订购经办");
		return false;
	}
//	if(edtFactory->Text.IsEmpty() || m_szFactID.IsEmpty())
//	{
//		ShowMessage("没有厂商的数据，请检查请购过程中的决购数据");
//		return false;
//	}
	if((nSel=lstRMB->ItemIndex)<0 || nSel>=m_lstRMBID.GetSize())
	{
		ShowMessage("请选择一个有效的币别");
		return false;
	}
	if((nSel=lstFactory->ItemIndex)<0 || nSel>=m_lstFactID.GetSize())
	{
		ShowMessage("请选择一个有效的厂商");
		return false;
	}
	m_szFactID=(LPCSTR)m_lstFactID[nSel];
	if(edtUnit->Text.IsEmpty() || m_szUnitID.IsEmpty())
	{
		ShowMessage("没有订购单位的数据，请检查请购过程中的决购数据");
		return false;
	}
	if(!CheckFloatEditor(edtCount))	return false;
	if((nSel=lstInvoice->ItemIndex)<0 || nSel>=m_lstInvoiceID.GetSize())
	{
		ShowMessage("请选择一个有效的发票抬头");
		return false;
	}
	if(m_enState==EN_STATE_NEW)
	{
		m_szSHCode=strSHCode;
	}
  if(lstBuyKind->ItemIndex<0)
  {
  	ShowMessage("请选择一个有效的采购形态");
    return false;
  }

	return true;
}
//---------------------------------------------------------------------------

//根据输入的数据、系统时间以及流水号生成编号
CString TBookFactoryForm::GenerateID()
{ //编号格式：PymXXXXX
	int nYear,nMonth,nDay,nFlow;
  char strID[80],chMon,strSQL[1024],strKey[80];

  if(!dm1->OpenDatabase())	return "";
	GetSysDate(nYear,nMonth,nDay,false);

	if(nMonth<10)	chMon=(char)('0'+nMonth);
  else chMon=(char)('A'-10+nMonth);

  //查看该月是否已经有流水号
  sprintf(strKey,"BookFactory_%04d%02d",nYear,nMonth);
  sprintf(strSQL,"select * from RuntimeData where rd_key='%s'",strKey);
	RunSQL(strSQL,true);
  if(dm1->Query1->Eof)
  { //该月还没有流水号，初始化该月流水号
  	sprintf(strSQL,"insert into RuntimeData values('%s',1,NULL,'订购单%d年%d月流水号')",
    	strKey,nYear,nMonth);
    RunSQL(strSQL);
    nFlow=1;
  }
  else
  {
  	nFlow=dm1->Query1->FieldByName("rd_int")->AsInteger;
  }

  while(1)
  {
    sprintf(strID,"O%d%c%05d",nYear%10,chMon,nFlow);
    sprintf(strSQL,"select * from BookFactory where bf_code='%s'",strID);
    RunSQL(strSQL,true);
    if(dm1->Query1->Eof)	break;
    nFlow++;
  }
  sprintf(strSQL,"update RuntimeData set rd_int=%d where rd_key='%s'",nFlow,strKey);
  RunSQL(strSQL);

  return CString(strID);
}

//根据请购单号重设收货经办
void TBookFactoryForm::ResetRcptHandle()
{
	CString szAPCode,szSQL;
	int i;
	char cCorp,strAP[80],strTemp[256];

	strcpy(strAP,edtAPCode->Text.Trim().c_str());
	if(strAP[0]!='\0')	strAP[strlen(strAP)-1]='\0';

	m_lstHandleID.RemoveAll();
	lstHandle->Items->Clear();
	cCorp='\0';
	if(strAP[0]!='\0' && m_enState!=EN_STATE_IDLE)	
	{ //提取请购单的请购部门，首位就是公司别
		szSQL.Format("select * from AskPurchase where ap_code='%s'",strAP);
		RunSQL(dm1->Query1,szSQL,true);
		if(!dm1->Query1->Eof)
		{
			strcpy(strTemp,dm1->Query1->FieldByName("ap_reqdepart")->AsString.c_str());
			cCorp=strTemp[0];
		}
	}
	//根据公司别重设收货经办
	for(i=0;i<m_lstRcptAll.GetSize();i++)
	{
		if(cCorp=='\0' || cCorp==m_lstRcptAll[i].strCol2[0])
		{
			m_lstHandleID.Add(m_lstRcptAll[i].strCode);
			lstHandle->Items->Add(m_lstRcptAll[i].strName);
		}
	}
	if(lstHandle->ItemIndex==-1 && m_lstHandleID.GetSize()>0)	lstHandle->ItemIndex=0;
	else
	{
		for(i=0;i<lstHandle->Items->Count;i++)
		{
			if(lstHandle->Text==lstHandle->Items->Strings[i])
      {
      	lstHandle->ItemIndex=i;
        break;
      }
    }
	}
}

void __fastcall TBookFactoryForm::edtAPCodeExit(TObject *Sender)
{
	CString szSQL;
	char strAP[80],strTemp[256],strMN[80];
	int i;
  AnsiString szCard,szDays;

	edtAPCode->Text=edtAPCode->Text.Trim();
	if(edtAPCode->Text.IsEmpty())	goto EMPTY_FACT;
	ResetAPData(edtAPCode->Text.c_str());

  ResetRMBCode();

	strcpy(strAP,edtAPCode->Text.c_str());
  strAP[7]='\0';
  szSQL.Format("select * from AskPurchase,InvoiceTitle where ap_code='%s'"
  	" and it_dccode=substring(ap_reqdepart,1,2)",strAP);
  RunSQL(dm1->Query1,szSQL,true);
  if(!dm1->Query1->Eof)
  {
		strcpy(strTemp,dm1->Query1->FieldByName("it_code")->AsString.c_str());
    for(i=0;i<m_lstInvoiceID.GetSize();i++)
    {
    	if(m_lstInvoiceID[i]==strTemp)
      {
      	lstInvoice->ItemIndex=i;
        break;
      }
    }
  }

  ResetCtrl();

	return;

EMPTY_FACT:
	m_szFactID="";
	m_szUnitID="";
//	edtFactory->Text="";
	lstFactory->ItemIndex=-1;
	edtCard		->Text="";
	edtUnit		->Text="";
	edtPrice	->Text="";
	edtDays		->Text="";

/*
	CString szSQL;
	char strAP[80],strTemp[256],strMN[80];
	int i;
  AnsiString szCard,szDays;

	edtAPCode->Text=edtAPCode->Text.Trim();
	ResetRcptHandle();

	if(edtAPCode->Text.IsEmpty())	goto EMPTY_FACT;

	strcpy(strAP,edtAPCode->Text.c_str());
	if(strAP[0]=='P')
	{
		szSQL.Format("select * from DecideFactory,Manufactur,DicUnits,PurchaseDetail"
			" where mf_code=df_mfdecide and du_code=df_unit and df_apcode=pd_code"
			" and df_apcode='%s'",edtAPCode->Text.c_str());
		RunSQL(dm1->Query1,szSQL,true);
		if(dm1->Query1->Eof)	goto EMPTY_FACT;

		strcpy(strMN,dm1->Query1->FieldByName("pd_mncode")->AsString.c_str());

		m_szFactID=dm1->Query1->FieldByName("mf_code")->AsString;
//		edtFactory->Text=dm1->Query1->FieldByName("mf_shortname")->AsString;
		m_szUnitID=dm1->Query1->FieldByName("du_code")->AsString;
		edtUnit->Text=dm1->Query1->FieldByName("du_name")->AsString;
		edtCount->Text=FloatField2String(dm1->Query1->FieldByName("df_count"),2);
		if(strMN[0]=='E' && strMN[1]=='M')
			edtPrice->Text=FloatField2String(dm1->Query1->FieldByName("df_price"),6);
		else
			edtPrice->Text=FloatField2String(dm1->Query1->FieldByName("df_price"),4);
    lstFactory->Items->Clear();
    m_lstFactID.RemoveAll();
		while(!dm1->Query1->Eof)
		{
			m_lstFactID.Add(dm1->Query1->FieldByName("mf_code")->AsString.c_str());
			lstFactory->Items->Add(dm1->Query1->FieldByName("mf_shortname")->AsString);
			dm1->Query1->Next();
		}

		szSQL.Format("select * from CompareFactory where cf_apcode='%s'",edtAPCode->Text.c_str());
		RunSQL(dm1->Query1,szSQL,true);
		if(dm1->Query1->Eof)
		{
			edtCard->Text="";
			edtDays->Text="";
		}
		else
		{
    	szCard=dm1->Query1->FieldByName("cf_card")->AsString;
      szDays=IntField2Text(dm1->Query1->FieldByName("cf_deliverday"));
      szSQL.Format("select * from CompareFactory,DecideFactory"
      	" where cf_apcode=df_apcode and cf_mfcode=df_mfdecide"
        " and cf_apcode='%s'",edtAPCode->Text.c_str());
      RunSQL(dm1->Query1,szSQL,true);
      if(dm1->Query1->Eof)
      {
				edtCard->Text=szCard;
				edtDays->Text=szDays;
      }
      else
    	{
	    	edtCard->Text=dm1->Query1->FieldByName("cf_card")->AsString;
  	    edtDays->Text=IntField2Text(dm1->Query1->FieldByName("cf_deliverday"));
    	}
		}
	}
	else if(strAP[0]=='Q')
	{
		szSQL.Format("select * from PurchaseDetail,TreatStock,Manufactur,DicUnits"
			" where ts_mfcode=mf_code and ts_ducode=du_code"
			" and pd_tscode=ts_code"
      " and pd_code='%s'",strAP);
		RunSQL(dm1->Query1,szSQL,true);
		if(dm1->Query1->Eof)	goto EMPTY_FACT;
		strcpy(strMN,dm1->Query1->FieldByName("pd_mncode")->AsString.c_str());

		m_szFactID=dm1->Query1->FieldByName("mf_code")->AsString;
		m_szUnitID=dm1->Query1->FieldByName("du_code")->AsString;
		edtUnit->Text=dm1->Query1->FieldByName("du_name")->AsString;
		if(strMN[0]=='E' && strMN[1]=='M')
			edtPrice->Text=FloatField2String(dm1->Query1->FieldByName("ts_price"),6);
		else
			edtPrice->Text=FloatField2String(dm1->Query1->FieldByName("ts_price"),4);
		edtCard->Text=dm1->Query1->FieldByName("ts_mfcard")->AsString;
		edtDays->Text=IntField2Text(dm1->Query1->FieldByName("ts_days"));

    lstFactory->Items->Clear();
    m_lstFactID.RemoveAll();
		while(!dm1->Query1->Eof)
		{
			m_lstFactID.Add(dm1->Query1->FieldByName("mf_code")->AsString.c_str());
			lstFactory->Items->Add(dm1->Query1->FieldByName("mf_shortname")->AsString);
			dm1->Query1->Next();
		}

		for(i=0;i<m_lstRMBID.GetSize();i++)
		{
			if(m_lstRMBID[i]=="RMB")
			{
				lstRMB->ItemIndex=i;
				break;
			}
		}
	}
	for(i=0;i<m_lstFactID.GetSize();i++)
	{
		if(m_lstFactID[i]==m_szFactID.c_str())
		{
			lstFactory->ItemIndex=i;
			break;
		}
	}
	if(i==m_lstFactID.GetSize())	lstFactory->ItemIndex=-1;

  strAP[7]='\0';
  szSQL.Format("select * from AskPurchase,InvoiceTitle where ap_code='%s'"
  	" and it_dccode=substring(ap_reqdepart,1,2)",strAP);
  RunSQL(dm1->Query1,szSQL,true);
  if(!dm1->Query1->Eof)
  {
		strcpy(strTemp,dm1->Query1->FieldByName("it_code")->AsString.c_str());
    for(i=0;i<m_lstInvoiceID.GetSize();i++)
    {
    	if(m_lstInvoiceID[i]==strTemp)
      {
      	lstInvoice->ItemIndex=i;
        break;
      }
    }
  }

  ResetRMBCode();
  ResetCtrl();

	return;

EMPTY_FACT:
	m_szFactID="";
	m_szUnitID="";
//	edtFactory->Text="";
	lstFactory->ItemIndex=-1;
	edtCard		->Text="";
	edtUnit		->Text="";
	edtPrice	->Text="";
	edtDays		->Text="";
*/
}
//---------------------------------------------------------------------------

void __fastcall TBookFactoryForm::lstHandleExit(TObject *Sender)
{
	int nSel,i;

  lstHandle->Text=lstHandle->Text.Trim();
  lstHandle->Text=lstHandle->Text.UpperCase();
	if((nSel=lstHandle->Items->IndexOf(lstHandle->Text))<0 || nSel>=m_lstHandleID.GetSize())
	{
		for(i=0;i<m_lstHandleID.GetSize();i++)
		{
			if(m_lstHandleID[i]==lstHandle->Text.c_str())
			{
				lstHandle->ItemIndex=i;
				break;
			}
		}
	}
}
//---------------------------------------------------------------------------

bool TBookFactoryForm::CanModify()
{
	CString szSQL;

	if(m_szActiveID.IsEmpty())	return false;
	szSQL.Format("select * from acceptmate where am_bfcode='%s'",m_szActiveID);
	RunSQL(dm1->Query1,szSQL,true);
	if(!dm1->Query1->Eof)
	{
		ShowMessage("该订购单已有收料数据，不能修改和删除");
		return false;
	}

	return true;
}


void __fastcall TBookFactoryForm::lstFactoryExit(TObject *Sender)
{
	HandleListboxExit(lstFactory,&m_lstFactID);
	ResetShowDate();
  ResetBookData();
  ResetRMBCode();
}
//---------------------------------------------------------------------------

void __fastcall TBookFactoryForm::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
	if(Key!=VK_RETURN)	return;
  if(ActiveControl==edtBookID && m_enState==EN_STATE_IDLE)
  {
  	if(btnQuery->CanFocus())	btnQuery->SetFocus();
    return;
  }
  else if(ActiveControl==lstInvoiceType)
  {
  	if(btnOK->CanFocus())	btnOK->SetFocus();
  }
  else
	{
		KeyReturnHandle(ActiveControl);
  }
}
//---------------------------------------------------------------------------

void TBookFactoryForm::ResetPurchaseData()
{
	char strAP[80],strBuff[256];
	int i;
	CString szSQL;
	strcpy(strAP,edtAPCode->Text.c_str());
	if(strAP[0]=='\0')	return;

	//收货经办
	m_lstHandleID.RemoveAll();
	lstHandle->Items->Clear();

//	CStringArray m_lstInvoiceID;
	m_lstFactID.RemoveAll();
  lstFactory->Items->Clear();
  
	if(m_enState==EN_STATE_IDLE)
	{
		for(i=0;i<m_lstFactAll.GetSize();i++)
		{
			m_lstFactID.Add(m_lstFactAll[i].strCode);
			lstFactory->Items->Add(m_lstFactAll[i].strName);
		}
//		lstHandle->Items->Add(dm1->Query1->FieldByName("rh_name")->AsString);
	}
	else
	{
		szSQL.Format("select df_mfplan,df_mfdecide,mf_shortname"
			" from DecideFactory,Manufactur"
			" where df_mfplan=mf_code"
			" df_apcode='%s' order by df_mfplan",strAP);
		RunSQL(dm1->Query1,szSQL,true);
		strBuff[0]='\0';
		while(!dm1->Query1->Eof)
		{
			m_lstFactID.Add(dm1->Query1->FieldByName("df_mfplan")->AsString.c_str());
			lstFactory->Items->Add(dm1->Query1->FieldByName("mf_shortname")->AsString);
			if(dm1->Query1->FieldByName("df_mfplan")->AsString==dm1->Query1->FieldByName("df_mfdecide")->AsString)
				strcpy(strBuff,dm1->Query1->FieldByName("df_mfplan")->AsString.c_str());
			dm1->Query1->Next();
		}
		if(strBuff[0]!='\0')	lstFactory->ItemIndex=lstFactory->Items->IndexOf(strBuff);
	}
}

void TBookFactoryForm::ResetRMBCode()
{
	char strAP[80],strRMB[80];
  int nSel,i;
  CString szSQL;

	strcpy(strAP,edtAPCode->Text.Trim().c_str());
  if(strAP[0]=='\0')	return;

	strcpy(strRMB,"RMB");
	if(strAP[0]=='P')
	{
		if((nSel=lstFactory->ItemIndex)<0 || nSel>=m_lstFactID.GetSize())	return;
		szSQL.Format("select * from CompareFactory where cf_apcode='%s' and cf_mfcode='%s'",
  		strAP,m_lstFactID[nSel]);
		RunSQL(dm1->Query1,szSQL,true);
		if(!dm1->Query1->Eof)
		{
			strcpy(strRMB,dm1->Query1->FieldByName("cf_quotermb")->AsString.c_str());
		}
	}
	for(i=0;i<m_lstRMBID.GetSize();i++)
	{
		if(m_lstRMBID[i]==strRMB)
		{
			lstRMB->ItemIndex=i;
			break;
		}
	}
	if(i==m_lstRMBID.GetSize())	lstRMB->ItemIndex=-1;
}

void TBookFactoryForm::ResetShowDate()
{
	char strAP[80],strMF[80];
	CString szSQL;
	int nSel;

	if(edtAPCode->Text.IsEmpty())	return;
	strcpy(strAP,edtAPCode->Text.c_str());
	if((nSel=lstFactory->ItemIndex)<0 || nSel>=m_lstFactID.GetSize())	return;
	strcpy(strMF,m_lstFactID[nSel]);
	lstShowDate->Items->Clear();
	if(strAP[0]=='P')
	{
		szSQL.Format("select df_plandate from DecideFactory where df_apcode=%s and df_mfdecide=%s order by df_plandate desc",
			Str2DBString(strAP),Str2DBString(strMF));
		RunSQL(dm1->Query3,szSQL,true);
		while(!dm1->Query3->Eof)
		{
			lstShowDate->Items->Add(DateField2Text(dm1->Query3->FieldByName("df_plandate")));
			dm1->Query3->Next();
		}
		if(lstShowDate->Items->Count==1)	lstShowDate->ItemIndex=0;
		else
		{
			if((nSel=lstShowDate->Items->IndexOf(lstShowDate->Text))>=0)	lstShowDate->ItemIndex=nSel;
			else	lstShowDate->ItemIndex=0;
		}
		EnableCombo(lstShowDate,m_enState!=EN_STATE_IDLE);
	}
	else
	{
		lstShowDate->ItemIndex=-1;
		EnableCombo(lstShowDate,false);
	}
}

void TBookFactoryForm::ResetBookData()
{
	CString szSQL;
	char strAP[80],strTemp[256],strMN[80],strMF[80],strShowDate[80];
	int i,nSel;
  AnsiString szCard,szDays;

	if(edtAPCode->Text.IsEmpty())	return;
	strcpy(strAP,edtAPCode->Text.c_str());
	if((nSel=lstFactory->ItemIndex)<0 || nSel>=m_lstFactID.GetSize())	return;
	strcpy(strMF,m_lstFactID[nSel]);

	if(strAP[0]=='P')
	{
		szSQL.Format("select * from DecideFactory,Manufactur,DicUnits,PurchaseDetail"
			" where mf_code=df_mfdecide and du_code=df_unit and df_apcode=pd_code"
			" and df_apcode='%s' and df_mfdecide='%s' and df_plandate=%s",strAP,strMF,Text2DBDate(lstShowDate->Text.c_str()));
		RunSQL(dm1->Query3,szSQL,true);
		if(dm1->Query3->Eof)	return;

		strcpy(strMN,dm1->Query3->FieldByName("pd_mncode")->AsString.c_str());

		m_szFactID=dm1->Query3->FieldByName("mf_code")->AsString;
		m_szUnitID=dm1->Query3->FieldByName("du_code")->AsString;
		edtUnit->Text=dm1->Query3->FieldByName("du_name")->AsString;
		edtCount->Text=FloatField2String(dm1->Query3->FieldByName("df_count"),2);
		if(strMN[0]=='E' && strMN[1]=='M')
			edtPrice->Text=FloatField2String(dm1->Query3->FieldByName("df_price"),6);
		else
			edtPrice->Text=FloatField2String(dm1->Query3->FieldByName("df_price"),4);

    szSQL.Format("select * from CompareFactory,DecideFactory"
      " where cf_apcode=df_apcode and cf_mfcode=df_mfdecide"
      " and cf_apcode='%s' and cf_mfcode='%s'",strAP,strMF);
    RunSQL(dm1->Query3,szSQL,true);
    if(dm1->Query3->Eof)
    {
			edtCard->Text=szCard;
			edtDays->Text=szDays;
    }
    else
    {
			szCard=dm1->Query3->FieldByName("cf_card")->AsString;
			szDays=IntField2Text(dm1->Query3->FieldByName("cf_deliverday"));
	    edtCard->Text=dm1->Query3->FieldByName("cf_card")->AsString;
  	  edtDays->Text=IntField2Text(dm1->Query3->FieldByName("cf_deliverday"));
    }
	}
	else if(strAP[0]=='Q')
	{
		szSQL.Format("select * from PurchaseDetail,TreatStock,Manufactur,DicUnits"
			" where ts_mfcode=mf_code and ts_ducode=du_code"
			" and pd_tscode=ts_code"
                        " and pd_code='%s'",strAP);
		RunSQL(dm1->Query3,szSQL,true);
		if(dm1->Query3->Eof)	return;
		strcpy(strMN,dm1->Query3->FieldByName("pd_mncode")->AsString.c_str());

		m_szFactID=dm1->Query3->FieldByName("mf_code")->AsString;
		m_szUnitID=dm1->Query3->FieldByName("du_code")->AsString;
		edtUnit->Text=dm1->Query3->FieldByName("du_name")->AsString;
		if(strMN[0]=='E' && strMN[1]=='M')
			edtPrice->Text=FloatField2String(dm1->Query3->FieldByName("ts_price"),6);
		else
//			edtPrice->Text=FloatField2String(dm1->Query3->FieldByName("ts_price"),4);
			edtPrice->Text=FloatField2String(dm1->Query3->FieldByName("ts_price"),8);
		edtCard->Text=dm1->Query3->FieldByName("ts_mfcard")->AsString;
		edtDays->Text=IntField2Text(dm1->Query3->FieldByName("ts_days"));

		for(i=0;i<m_lstRMBID.GetSize();i++)
		{
			if(m_lstRMBID[i]=="RMB")
			{
				lstRMB->ItemIndex=i;
				break;
			}
		}
	}
}

void TBookFactoryForm::ResetFactory()
{
	CString szSQL;
	char strAP[80],strTemp[256],strMN[80];
	int i,nSel;
  AnsiString szCard,szDays;

	edtAPCode->Text=edtAPCode->Text.Trim();
//	ResetRcptHandle();

	if(edtAPCode->Text.IsEmpty())	return;

	strcpy(strAP,edtAPCode->Text.c_str());
	if(strAP[0]=='P')
	{
		szSQL.Format("select * from DecideFactory,Manufactur"
			" where mf_code=df_mfdecide"
			" and df_apcode='%s'",edtAPCode->Text.c_str());
		RunSQL(dm1->Query1,szSQL,true);

    lstFactory->Items->Clear();
    m_lstFactID.RemoveAll();
		while(!dm1->Query1->Eof)
		{
			m_lstFactID.Add(dm1->Query1->FieldByName("mf_code")->AsString.c_str());
			lstFactory->Items->Add(dm1->Query1->FieldByName("mf_shortname")->AsString);
			dm1->Query1->Next();
		}
	}
	else if(strAP[0]=='Q')
	{
		szSQL.Format("select * from PurchaseDetail,TreatStock,Manufactur"
			" where ts_mfcode=mf_code"
			" and pd_tscode=ts_code"
      " and pd_code='%s'",strAP);
		RunSQL(dm1->Query1,szSQL,true);
		if(dm1->Query1->Eof)	return;

    lstFactory->Items->Clear();
    m_lstFactID.RemoveAll();
		while(!dm1->Query1->Eof)
		{
			m_lstFactID.Add(dm1->Query1->FieldByName("mf_code")->AsString.c_str());
			lstFactory->Items->Add(dm1->Query1->FieldByName("mf_shortname")->AsString);
			dm1->Query1->Next();
		}
	}
	if((nSel=lstFactory->Items->IndexOf(lstFactory->Text))>=0)	lstFactory->ItemIndex=nSel;
}

void TBookFactoryForm::ResetAPData(LPCSTR lpszAP)
{
	CString szSQL;
	char strAP[80],strTemp[256],strMN[80];
	int i,nSel;
  AnsiString szCard,szDays;

	if(lpszAP[0]=='\0')	return;
	ResetRcptHandle(lpszAP);
	strcpy(strAP,lpszAP);

  lstFactory->Items->Clear();
  m_lstFactID.RemoveAll();
	if(strAP[0]=='P')
	{
		szSQL.Format("select mf_code,mf_shortname"
			" from DecideFactory,Manufactur"
			" where mf_code=df_mfdecide"
			" and df_apcode='%s'",strAP);
		RunSQL(dm1->Query3,szSQL,true);
	}
	else if(strAP[0]=='Q')
	{
		szSQL.Format("select mf_code,mf_shortname"
			" from PurchaseDetail,TreatStock,Manufactur"
			" where ts_mfcode=mf_code"
			" and pd_tscode=ts_code"
      " and pd_code='%s'",strAP);
		RunSQL(dm1->Query3,szSQL,true);
	}
	while(!dm1->Query3->Eof)
	{
		m_lstFactID.Add(dm1->Query3->FieldByName("mf_code")->AsString.c_str());
		lstFactory->Items->Add(dm1->Query3->FieldByName("mf_shortname")->AsString);
		dm1->Query3->Next();
	}
	if((nSel=lstFactory->Items->IndexOf(lstFactory->Text))>=0)	lstFactory->ItemIndex=nSel;
  else lstFactory->ItemIndex=0;

	ResetShowDate();
  ResetBookData();
}

//根据请购单号重设收货经办
void TBookFactoryForm::ResetRcptHandle(LPCSTR lpszAP)
{
	CString szAPCode,szSQL;
	int i;
	char cCorp,strAP[80],strTemp[256];

	strcpy(strAP,lpszAP);
	if(strAP[0]=='\0')	return;
	if(strAP[1]!='\0')	strAP[strlen(strAP)-1]='\0';

	m_lstHandleID.RemoveAll();
	lstHandle->Items->Clear();
	cCorp='\0';
	if(strAP[0]!='\0' && m_enState!=EN_STATE_IDLE)	
	{ //提取请购单的请购部门，首位就是公司别
		szSQL.Format("select ap_reqdepart from AskPurchase where ap_code='%s'",strAP);
		RunSQL(dm1->Query3,szSQL,true);
		if(!dm1->Query3->Eof)
		{
			strcpy(strTemp,dm1->Query3->FieldByName("ap_reqdepart")->AsString.c_str());
			cCorp=strTemp[0];
		}
	}
	//根据公司别重设收货经办
	for(i=0;i<m_lstRcptAll.GetSize();i++)
	{
		if(cCorp=='\0' || cCorp==m_lstRcptAll[i].strCol2[0])
		{
			m_lstHandleID.Add(m_lstRcptAll[i].strCode);
			lstHandle->Items->Add(m_lstRcptAll[i].strName);
		}
	}
	if(lstHandle->ItemIndex==-1 && m_lstHandleID.GetSize()>0)	lstHandle->ItemIndex=0;
	else
	{
		for(i=0;i<lstHandle->Items->Count;i++)
		{
			if(lstHandle->Text==lstHandle->Items->Strings[i])
      {
      	lstHandle->ItemIndex=i;
        break;
      }
    }
	}
}


void __fastcall TBookFactoryForm::lstShowDateChange(TObject *Sender)
{
	ResetBookData();	
}
//---------------------------------------------------------------------------


