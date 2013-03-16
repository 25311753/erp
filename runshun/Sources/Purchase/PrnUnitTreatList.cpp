//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <assert.h>
#pragma hdrstop

#include "DataModule.h"
#include "BaseCode.h"
#include "PrnUnitTreatList.h"
#include "LdyInterface.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPrnUnitTreatListForm *PrnUnitTreatListForm;

//----------------------------------------------------------------------
//统购材料清单接口，文件：PrnUnitTreatList
void PrnUnitTreatList(int nAuth)
{
	TPrnUnitTreatListForm *pForm;
  CString szSQL;
  TDateTime tNow;

  tNow=GetSysTime(false);

  szSQL="select * from TreatStock,DicUnits,materialno,Manufactur"
		" where ts_ducode=du_code"
		" and ts_mncode=mn_code"
		" and ts_mfcode*=mf_code"
		" and mn_code like 'A%'"
    " order by ts_mncode";
	if(!OpenQuery(dm1->sqlPrint,szSQL))	return;

  pForm=new TPrnUnitTreatListForm(Application);
  assert(pForm!=NULL);
  pForm->txtPrnDate->Caption=(LPCSTR)Time2DBDateString(tNow);
  pForm->PrnView->PreviewModal();
  delete pForm;
}

//---------------------------------------------------------------------------
__fastcall TPrnUnitTreatListForm::TPrnUnitTreatListForm(TComponent* Owner)
	: TForm(Owner)
{
	m_strPrvCode[0]='\0';
}
//---------------------------------------------------------------------------

void __fastcall TPrnUnitTreatListForm::QRSubDetail1BeforePrint(
      TQRCustomBand *Sender, bool &PrintBand)
{
	char strCode[80],strMater[80];
  int nPos;

	strcpy(strCode,ts_code->DataSet->FieldByName("ts_mncode")->AsString.c_str());
	strCode[5]='\0';
  if(strcmp(strCode,m_strPrvCode)!=0 && m_strPrvCode[0]!='\0')
	{
  	PrnView->NewPage();
	}
  strcpy(m_strPrvCode,strCode);

	strcpy(strMater,ts_code->DataSet->FieldByName("ts_mncode")->AsString.c_str());
	//利用二分法快速查找
	nPos=SearchBaseDataPos(strMater,m_lstBook);
	if(nPos>=0 && nPos<m_lstBook.GetSize())	txtBook->Caption=m_lstBook[nPos].strName;
	else txtBook->Caption="";

}
//---------------------------------------------------------------------------


void __fastcall TPrnUnitTreatListForm::PageHeaderBand1BeforePrint(
      TQRCustomBand *Sender, bool &PrintBand)
{
	char strCode[256];
  AnsiString szTitle;
  CString szSQL;

  strcpy(strCode,ts_code->DataSet->FieldByName("ts_mncode")->AsString.c_str());
  if(strlen(strCode)<5)	return;
  strCode[5]='\0';

  szSQL.Format("select * from diclargetype,dicmiddletype,dicsmalltype"
		" where lt_code='%c' and mt_code='%c%c' and st_code='%s'",
    strCode[1],strCode[1],strCode[2],strCode+1);
  RunSQL(dm1->Query1,szSQL,true);
  if(dm1->Query1->Eof)	return;
  szTitle=dm1->Query1->FieldByName("lt_name")->AsString
  	+ " --> "
    + dm1->Query1->FieldByName("mt_name")->AsString
    + " --> "
    + dm1->Query1->FieldByName("st_name")->AsString;
  txtType->Caption=szTitle;
}
//---------------------------------------------------------------------------

void __fastcall TPrnUnitTreatListForm::QRDBText9Print(TObject *sender,
      AnsiString &Value)
{
	if(ts_code->DataSet->FieldByName("ts_afmdate")->IsNull)	Value+="#";
  if(ts_code->DataSet->FieldByName("ts_afmdate2")->IsNull)	Value+="*";
}
//---------------------------------------------------------------------------

