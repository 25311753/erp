//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <assert.h>
#pragma hdrstop

#include "DataModule.h"
#include "BaseCode.h"
#include "AcceptNotPayList.h"
#include "LdyInterface.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAcceptNotPayListForm *AcceptNotPayListForm;

//---------------------------------------------------------------------------
//已收料未请款明细接口，文件：AcceptNotPayList.*
void AcceptNotPayList(int nAuth)
{
	CALL_FORM(TAcceptNotPayListForm);
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
__fastcall TAcceptNotPayListForm::TAcceptNotPayListForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TAcceptNotPayListForm::FormShow(TObject *Sender)
{
	CString szSQL;

	m_lstFactID.Add("");
	lstFact->Items->Add("全部");
	szSQL="select * from Manufactur where mf_code in "
		"( select distinct bf_mfcode from BookFactory)"
		" order by mf_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		m_lstFactID.Add(dm1->Query1->FieldByName("mf_code")->AsString.c_str());
		lstFact->Items->Add(dm1->Query1->FieldByName("mf_shortname")->AsString);

		dm1->Query1->Next();
	}
	lstFact->ItemIndex=0;

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

	m_lstStoreID.Add("");
	lstStore->Items->Add("全部");
	szSQL="select * from dicstoreno order by sn_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		m_lstStoreID.Add(dm1->Query1->FieldByName("sn_code")->AsString.c_str());
		lstStore->Items->Add(dm1->Query1->FieldByName("sn_name")->AsString);

		dm1->Query1->Next();
	}
	lstStore->ItemIndex=0;
}
//---------------------------------------------------------------------------

void __fastcall TAcceptNotPayListForm::btnToExcelClick(TObject *Sender)
{
	Variant vExcel,vSheet;
  int nRow,i;
  TListItem *pItem;

  try
  {
	  nRow=1;
		if(!OpenExcel("已收料未请款明细.xls",vExcel,vSheet))	return;
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
				NULL);
		}
	}
	catch(...)
	{
	}
}
//---------------------------------------------------------------------------

void __fastcall TAcceptNotPayListForm::btnExitClick(TObject *Sender)
{
	Close();	
}
//---------------------------------------------------------------------------

void __fastcall TAcceptNotPayListForm::btnQueryClick(TObject *Sender)
{
	CString szSQL;
	int i,nSel;
	char strCorp[80],strStore[80],strTemp[256],strTemp2[256],strTemp3[256];
	TListItem *pItem;

	lstView->Items->Clear();

	szSQL="select * from acceptmate,PurchaseDetail,materialno,BookFactory,Manufactur,AskPurchase"
		" where am_canceldate is null"
		" and substring(pd_mncode,2,1)<>'M'"
		" and pd_code=am_pdcode"
		" and ap_code=substring(pd_code,1,7)"
		" and mn_code=pd_mncode"
		" and bf_code=am_bfcode"
		" and mf_code=bf_mfcode";
	if((nSel=lstCorp->ItemIndex)>0 && nSel<m_lstCorpID.GetSize())
	{
		sprintf(strTemp," and substring(ap_reqdepart,1,2)='%s'",m_lstCorpID[nSel]);
		szSQL+=strTemp;
	}
	if((nSel=lstFact ->ItemIndex)>0 && nSel<m_lstFactID.GetSize())
	{
		sprintf(strTemp," and bf_mfcode='%s'",m_lstFactID[nSel]);
		szSQL+=strTemp;
	}
	if((nSel=lstStore->ItemIndex)>0 && nSel<m_lstStoreID.GetSize())
	{
		sprintf(strTemp," and substring(am_storekey,1,2)='%s'",m_lstStoreID[nSel]);
		szSQL+=strTemp;
	}
	szSQL+=" and am_code not in"
		"("
		"select distinct(pmd_amcode) from paymentdetail"
		")"
		" order by am_indate";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		pItem=lstView->Items->Add();
		assert(pItem!=NULL);
		pItem->Caption=dm1->Query1->FieldByName("am_code")->AsString;
		pItem->SubItems->Add(DateField2Text(dm1->Query1->FieldByName("am_indate")));
		pItem->SubItems->Add(FloatField2String(dm1->Query1->FieldByName("am_quantity"),2));
		pItem->SubItems->Add(FloatField2String(dm1->Query1->FieldByName("am_checkquan"),2));
//		pItem->SubItems->Add(FloatField2String(dm1->Query1->FieldByName("am_money"),2));
//-------new 0705---------------------------------------------------------------
                strcpy(strTemp2,dm1->Query1->FieldByName("ap_sdcode")->AsString.c_str());
		strcpy(strTemp3,dm1->Query1->FieldByName("am_storekey")->AsString.c_str());
                if(g_theOperator.op_cpcode[0]!='E' && (strcmp(strTemp2,"2")==0 || strcmp(strTemp2,"3")==0 || strcmp(strTemp3,"E")))
                {
                        pItem->SubItems->Add("");
                }
                else
                {
		pItem->SubItems->Add(FloatField2String(dm1->Query1->FieldByName("am_money"),2));
                }
//------------------------------------------------------------------------------
		pItem->SubItems->Add(dm1->Query1->FieldByName("mn_name")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("mf_shortname")->AsString);

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

		strcpy(strStore,dm1->Query1->FieldByName("am_storekey")->AsString.c_str());
		strStore[2]='\0';
		for(i=1;i<m_lstStoreID.GetSize();i++)
		{
			if(m_lstStoreID[i]==strStore)
			{
				pItem->SubItems->Add(lstStore->Items->Strings[i]);
				break;
			}
		}
		if(i==m_lstStoreID.GetSize())	pItem->SubItems->Add("");

		dm1->Query1->Next();
	}
}
//---------------------------------------------------------------------------

#include "FactorySearch.h"
void __fastcall TAcceptNotPayListForm::btnFactPickupClick(TObject *Sender)
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
      	lstFact->ItemIndex=i;
        break;
      }
    }
  }
  delete pForm;
}
//---------------------------------------------------------------------------

void __fastcall TAcceptNotPayListForm::lstFactExit(TObject *Sender)
{
	HandleListboxExit(lstFact,&m_lstFactID);
}
//---------------------------------------------------------------------------


