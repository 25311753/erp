//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <assert.h>
#pragma hdrstop

#include "DataModule.h"
#include "BaseCode.h"
#include "UnitTreatList.h"
#include "PrnUnitTreatList.h"
#include "LdyInterface.h"
#include "TConst.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TUnitTreatListForm *UnitTreatListForm;

//--------------------------------------------------------------------------
//统购材料列表接口，文件：UnitTreatList.*
void UnitTreatList(int nAuth)
{
	CALL_FORM(TUnitTreatListForm);
}

//---------------------------------------------------------------------------
__fastcall TUnitTreatListForm::TUnitTreatListForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TUnitTreatListForm::FormShow(TObject *Sender)
{
	CString szSQL;

	szSQL="select * from diccorp order by cp_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		m_lstCorpID.Add(dm1->Query1->FieldByName("cp_code")->AsString.c_str());
		lstCorp->Items->Add(dm1->Query1->FieldByName("cp_name")->AsString);
		dm1->Query1->Next();
	}
	lstCorp->ItemIndex=0;

	m_lstLargeID.Add("");
	lstLarge->Items->Add("全部");
	szSQL="select * from diclargetype order by lt_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		m_lstLargeID.Add(dm1->Query1->FieldByName("lt_code")->AsString.c_str());
		lstLarge->Items->Add(dm1->Query1->FieldByName("lt_name")->AsString);
		dm1->Query1->Next();
	}
	lstLarge->ItemIndex=0;
}
//---------------------------------------------------------------------------
void __fastcall TUnitTreatListForm::btnQueryClick(TObject *Sender)
{
	CString szSQL,szFilter0,szFilter1,szFilter2;
	char strCorp[80],strLarge[80],strMater[80],strCorp2[80],strTemp2[256];
	int nSel,nPos;
	TListItem *pItem;
	AnsiString szDays;
	CArray<BASE2COLDATA,BASE2COLDATA>lstBook;
	BASE2COLDATA rwBase;

	strCorp[0]='\0';
	strLarge[0]='\0';

	if((nSel=lstCorp->ItemIndex)>=0 && nSel<m_lstCorpID.GetSize())
	{
		strcpy(strCorp,m_lstCorpID[nSel]);
	}
	if((nSel=lstLarge->ItemIndex)>=0 && nSel<m_lstLargeID.GetSize())
	{
		strcpy(strLarge,m_lstLargeID[nSel]);
	}
	if(strCorp[0]!='\0' || strLarge[0]!='\0')
	{
		szFilter0.Format(" and mn_code like '%s%s%%'",strCorp,strLarge);
		szFilter1.Format(" and pd_mncode like '%s%s%%'",strCorp,strLarge);
	}

//------new 0701----------------------------------------------------------------
//        strcpy(strCorp2,g_theOperator.op_cpcode[0].i_str());
/*        szSQL.Format("select op_cpcode from operator where op_code='%s'",operatorcode);
	RunSQL(dm1->Query1,szSQL,true);
        strcpy(strCorp2,dm1->Query1->FieldByName("op_cpcode")->AsString.c_str());
        szFilter0.Format(" and mn_code like '%s%s%%'",strCorp2,strLarge);
	szFilter1.Format(" and pd_mncode like '%s%s%%'",strCorp2,strLarge);     */
//------------------------------------------------------------------------------
	szSQL="select pd_mncode,count(pd_mncode) as pd_count from BookFactory,PurchaseDetail"
		" where bf_apcode=pd_code";
	szSQL+=szFilter1;
	szSQL+=" group by pd_mncode"
		" order by pd_mncode";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		strcpy(rwBase.strCode,dm1->Query1->FieldByName("pd_mncode")->AsString.c_str());
		sprintf(rwBase.strName,"%d",dm1->Query1->FieldByName("pd_count")->AsInteger);
		lstBook.Add(rwBase);
		dm1->Query1->Next();
	}

  szSQL="select * from TreatStock,DicUnits,materialno,Manufactur"
		" where ts_ducode=du_code"
		" and ts_mncode=mn_code"
		" and ts_mfcode*=mf_code";
	szSQL+=szFilter0;
	szSQL+=" order by ts_mncode";

	lstView->Items->Clear();
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		pItem=lstView->Items->Add();
		assert(pItem!=NULL);
		strcpy(strMater,dm1->Query1->FieldByName("ts_mncode")->AsString.c_str());
		pItem->Caption=dm1->Query1->FieldByName("ts_code")->AsString;
		pItem->SubItems->Add(dm1->Query1->FieldByName("ts_mncode")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("mn_name")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("mf_shortname")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("ts_mfcard")->AsString);
		pItem->SubItems->Add(DateField2Text(dm1->Query1->FieldByName("ts_inuredate")));
		pItem->SubItems->Add(dm1->Query1->FieldByName("du_name")->AsString);
//		pItem->SubItems->Add(FloatField2String(dm1->Query1->FieldByName("ts_price"),2));
//--------new 0704--------------------------------------------------------------
                strcpy(strTemp2,dm1->Query1->FieldByName("ts_sdcode")->AsString.c_str());
                if(g_theOperator.op_cpcode[0]!='E' && (strcmp(strTemp2,"2")==0 || strcmp(strTemp2,"3")==0))
                {
                        pItem->SubItems->Add("");
                }
                else
                {
		pItem->SubItems->Add(FloatField2String(dm1->Query1->FieldByName("ts_price"),2));
                }
//------------------------------------------------------------------------------
		szDays=IntField2String(dm1->Query1->FieldByName("ts_days"));
		if(dm1->Query1->FieldByName("ts_afmdate")->IsNull)	szDays+="#";
		if(dm1->Query1->FieldByName("ts_afmdate2")->IsNull)	szDays+="*";
		pItem->SubItems->Add(szDays);

		//利用二分法快速查找
		nPos=SearchBaseDataPos(strMater,lstBook);
		if(nPos>=0 && nPos<lstBook.GetSize())	pItem->SubItems->Add(lstBook[nPos].strName);
		else	pItem->SubItems->Add("");

		dm1->Query1->Next();
	}
}
//---------------------------------------------------------------------------
void __fastcall TUnitTreatListForm::btnPrintClick(TObject *Sender)
{
	CString szSQL,szFilter0,szFilter1;
	char strCorp[80],strLarge[80],strTemp[80];
	int nSel;
	TListItem *pItem;
	AnsiString szDays;
	BASE2COLDATA rwBase;
	TPrnUnitTreatListForm *pForm;
  TDateTime tNow;

  pForm=new TPrnUnitTreatListForm(Application);
  assert(pForm!=NULL);

	strCorp[0]='\0';
	strLarge[0]='\0';
	if((nSel=lstCorp->ItemIndex)>=0 && nSel<m_lstCorpID.GetSize())
	{
		strcpy(strCorp,m_lstCorpID[nSel]);
	}
	if((nSel=lstLarge->ItemIndex)>=0 && nSel<m_lstLargeID.GetSize())
	{
		strcpy(strLarge,m_lstLargeID[nSel]);
	}
	if(strCorp[0]!='\0' || strLarge[0]!='\0')
	{
		szFilter0.Format(" and mn_code like '%s%s%%'",strCorp,strLarge);
		szFilter1.Format(" and pd_mncode like '%s%s%%'",strCorp,strLarge);
	}

	szSQL="select pd_mncode,count(pd_mncode) as pd_count from BookFactory,PurchaseDetail"
		" where bf_apcode=pd_code";
	szSQL+=szFilter1;
	szSQL+=" group by pd_mncode"
		" order by pd_mncode";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		strcpy(rwBase.strCode,dm1->Query1->FieldByName("pd_mncode")->AsString.c_str());
		sprintf(rwBase.strName,"%d",dm1->Query1->FieldByName("pd_count")->AsInteger);
		pForm->m_lstBook.Add(rwBase);
		dm1->Query1->Next();
	}

  szSQL="select * from TreatStock,DicUnits,materialno,Manufactur"
		" where ts_ducode=du_code"
		" and ts_mncode=mn_code"
		" and ts_mfcode*=mf_code";
	szSQL+=szFilter0;
	szSQL+=" order by ts_mncode";

  tNow=GetSysTime(false);

	if(!OpenQuery(dm1->sqlPrint,szSQL))	return;

  pForm->txtPrnDate->Caption=(LPCSTR)Time2DBDateString(tNow);
  pForm->PrnView->PreviewModal();
  delete pForm;

}
//---------------------------------------------------------------------------
void __fastcall TUnitTreatListForm::btnToExcelClick(TObject *Sender)
{
	Variant vExcel,vSheet;
  int nRow,i;
  TListItem *pItem;
  char strBook[80];

  try
  {
	  nRow=1;
		if(!OpenExcel("订购单列表.xls",vExcel,vSheet))	return;
		ListHead2Excel(lstView,vSheet,nRow++);
		for(i=0;i<lstView->Items->Count;i++)
    {
    	pItem=lstView->Items->Item[i];
      sprintf(strBook,"%d",atoi(pItem->SubItems->Strings[8].c_str()));
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
        strBook,
				NULL);
		}
	}
	catch(...)
	{
	}
}
//---------------------------------------------------------------------------
void __fastcall TUnitTreatListForm::btnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------


