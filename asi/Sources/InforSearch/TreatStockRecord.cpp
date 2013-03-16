//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <assert.h>
#pragma hdrstop

#include "DataModule.h"
#include "BaseCode.h"
#include "TreatStockRecord.h"
#include "LdyInterface.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTreatStockRecordForm *TreatStockRecordForm;

//===========================================================================
//合约采购记录表接口，文件：TreatStockRecord.*
void TreatStockRecord(int nAuth)
{
	if(nAuth==AUTH_NONE)	return;
	CALL_FORM(TTreatStockRecordForm);
}
//==========================================================================

//---------------------------------------------------------------------------
__fastcall TTreatStockRecordForm::TTreatStockRecordForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TTreatStockRecordForm::FormShow(TObject *Sender)
{
  edtID->Text="";

	RefreshData();
        RefreshDatahistory();
}

void TTreatStockRecordForm::RefreshData()
{
	CString szSQL,szMFName,szFilter;
	AnsiString szID;
	int nCount,nPos;
	CArray<BASE2COLDATA,BASE2COLDATA>lstMF;
        CArray<BASE2COLDATA,BASE2COLDATA>lstMF2;
	BASE2COLDATA rwMF;
        BASE2COLDATA rwMF2;
	TListItem *pItem;//,*pItem2,*pItem3;
	char strMF[256],strTemp2[256];

	if(!edtID->Text.IsEmpty())
	{
		szFilter.Format(" and ts_mncode like '%s%%'",edtID->Text.c_str());
	}

	szSQL="select distinct mf_code,mf_shortname from TreatStock,Manufactur where mf_code=ts_mfcode"
	      " order by mf_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		strcpy(rwMF.strCode,dm1->Query1->FieldByName("mf_code")->AsString.c_str());
		strcpy(rwMF.strName,dm1->Query1->FieldByName("mf_shortname")->AsString.c_str());
		lstMF.Add(rwMF);
		dm1->Query1->Next();
	}

//	szSQL="select a.ts_mncode as a_mncode,a.ts_mfcode as a_mf,a.ts_price as a_price,a.ts_inuredate as a_date,"
//		"b.ts_mfcode as b_mf,b.ts_price as b_price,b.ts_inuredate as b_date"
//		" from TreatStock as a,TreatStockHistory as b"
//		" where a.ts_mncode*=b.ts_mncode"
//		" order by a.ts_mncode,b.ts_inuredate";

	szSQL="select * from TreatStock,materialno,DicUnits where ts_mncode=mn_code and ts_ducode=du_code";
	szSQL+=szFilter;
	szSQL+=" and ts_mncode in"
		" ("
		" select distinct ts_mncode from TreatStock"
		")"
		" order by ts_mncode,ts_inuredate";
	RunSQL(dm1->Query1,szSQL,true);
	pItem=NULL;
        lstView->Clear();
	while(!dm1->Query1->Eof)
	{
		if(szID!=dm1->Query1->FieldByName("ts_mncode")->AsString)
		{
			szID=dm1->Query1->FieldByName("ts_mncode")->AsString;
			pItem=lstView->Items->Add();
			assert(pItem!=NULL);
			pItem->Caption=dm1->Query1->FieldByName("ts_mncode")->AsString;
			pItem->SubItems->Add(dm1->Query1->FieldByName("mn_name")->AsString);
			nCount=0;
		}
		else if(nCount>5)
		{
			dm1->Query1->Next();
			continue;
		}
		else
		{
			pItem=lstView->Items->Add();
			assert(pItem!=NULL);
			pItem->Caption="";
			pItem->SubItems->Add("");
			nCount++;
		}
		szMFName=GetMFName(dm1->Query1->FieldByName("ts_mfcode")->AsString.c_str(),lstMF);
		pItem->SubItems->Add((LPCSTR)szMFName);
		pItem->SubItems->Add(DateField2Text(dm1->Query1->FieldByName("ts_inuredate")));
		pItem->SubItems->Add(dm1->Query1->FieldByName("du_name")->AsString);
//		pItem->SubItems->Add(FloatField2String(dm1->Query1->FieldByName("ts_price"),2));
//----------new 0705------------------------------------------------------------
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

/*
		if(szID!=dm1->Query1->FieldByName("ts_mncode")->AsString)
		{
			szID=dm1->Query1->FieldByName("ts_mncode")->AsString;
			if(pItem!=NULL)
			{
				while(pItem->SubItems->Count<7)
				{
					pItem->SubItems->Add("");
					pItem2->SubItems->Add("");
					pItem3->SubItems->Add("");
				}
			}
			pItem=lstView->Items->Add();
			assert(pItem!=NULL);
			pItem2=lstView->Items->Add();
			assert(pItem2!=NULL);
			pItem3=lstView->Items->Add();
			assert(pItem3!=NULL);
			pItem->Caption=dm1->Query1->FieldByName("ts_mncode")->AsString;
			pItem->SubItems->Add(dm1->Query1->FieldByName("mn_name")->AsString);
			pItem2->Caption="";
			pItem2->SubItems->Add("");
			pItem3->Caption="";
			pItem3->SubItems->Add("");
		}
		if(pItem->SubItems->Count<7)
		{
			szMFName=GetMFName(dm1->Query1->FieldByName("ts_mfcode")->AsString.c_str(),lstMF);
			pItem->SubItems->Add((LPCSTR)szMFName);
			pItem2->SubItems->Add(DateField2Text(dm1->Query1->FieldByName("ts_inuredate")));
			pItem3->SubItems->Add(FloatField2String(dm1->Query1->FieldByName("ts_price"),2));
		}
*/
		dm1->Query1->Next();
	}
/*
	if(pItem!=NULL)
	{
		while(pItem->SubItems->Count<7)
		{
			pItem->SubItems->Add("");
			pItem2->SubItems->Add("");
			pItem3->SubItems->Add("");
		}
	}
*/
}
void TTreatStockRecordForm::RefreshDatahistory()
{
        CString szSQL,szMFName,szFilter;
	AnsiString szID;
	int nCount,nPos;
        CArray<BASE2COLDATA,BASE2COLDATA>lstMF2;
        BASE2COLDATA rwMF2;
	TListItem *pItem;//,*pItem2,*pItem3;
	char strMF[256],strTemp2[256];
	if(!edtID->Text.IsEmpty())
	{
  	  szFilter.Format(" and ts_mncode like '%s%%'",edtID->Text.c_str());
	}

	szSQL="select distinct mf_code,mf_shortname from TreatStockHistory,Manufactur where mf_code=ts_mfcode"
	" order by mf_code";
	RunSQL(dm1->Query4,szSQL,true);
	while(!dm1->Query4->Eof)
	{
		strcpy(rwMF2.strCode,dm1->Query4->FieldByName("mf_code")->AsString.c_str());
		strcpy(rwMF2.strName,dm1->Query4->FieldByName("mf_shortname")->AsString.c_str());
		lstMF2.Add(rwMF2);
		dm1->Query4->Next();
	}

	szSQL="select * from TreatStockHistory,materialno,DicUnits where ts_mncode=mn_code and ts_ducode=du_code";
	szSQL+=szFilter;
        	szSQL+=" and ts_mncode in"
		" ("
		" select distinct ts_mncode from TreatStockHistory"
		")"
		" order by ts_mncode,ts_inuredate";
	RunSQL(dm1->Query4,szSQL,true);
	pItem=NULL;
        ListView1->Clear();
	while(!dm1->Query4->Eof)
	{
		if(szID!=dm1->Query4->FieldByName("ts_mncode")->AsString)
		{
			szID=dm1->Query4->FieldByName("ts_mncode")->AsString;
			pItem=ListView1->Items->Add();
			assert(pItem!=NULL);
			pItem->Caption=dm1->Query4->FieldByName("ts_mncode")->AsString;
			pItem->SubItems->Add(dm1->Query4->FieldByName("mn_name")->AsString);
			nCount=0;
		}
		else if(nCount>5)
		{
			dm1->Query4->Next();
			continue;
		}
		else
		{
			pItem=ListView1->Items->Add();
			assert(pItem!=NULL);
			pItem->Caption="";
			pItem->SubItems->Add("");
			nCount++;
		}
		szMFName=GetMFName(dm1->Query4->FieldByName("ts_mfcode")->AsString.c_str(),lstMF2);
		pItem->SubItems->Add((LPCSTR)szMFName);
		pItem->SubItems->Add(DateField2Text(dm1->Query4->FieldByName("ts_inuredate")));
		pItem->SubItems->Add(dm1->Query4->FieldByName("du_name")->AsString);
//		pItem->SubItems->Add(FloatField2String(dm1->Query4->FieldByName("ts_price"),2));
//----------new 0705------------------------------------------------------------
                strcpy(strTemp2,dm1->Query4->FieldByName("ts_sdcode")->AsString.c_str());
                if(g_theOperator.op_cpcode[0]!='E' && (strcmp(strTemp2,"2")==0 || strcmp(strTemp2,"3")==0))
                {
                        pItem->SubItems->Add("");
                }
                else
                {
		pItem->SubItems->Add(FloatField2String(dm1->Query4->FieldByName("ts_price"),2));
                }
//------------------------------------------------------------------------------

		dm1->Query4->Next();
	}




}
//---------------------------------------------------------------------------

CString TTreatStockRecordForm::GetMFName(LPCSTR lpszID,CArray<BASE2COLDATA,BASE2COLDATA>&lstData)
{
	int nPos;
	CString szRes;

	//利用二分法快速查找
	nPos=SearchBaseDataPos(lpszID,lstData);
	if(nPos>=0 && nPos<lstData.GetSize())
		szRes=lstData[nPos].strName;
	return szRes;
}
void __fastcall TTreatStockRecordForm::btnExitClick(TObject *Sender)
{
	Close();	
}
//---------------------------------------------------------------------------
void __fastcall TTreatStockRecordForm::btnToExcelClick(TObject *Sender)
{
	Variant vExcel,vSheet;
  int nRow,i;
  TListItem *pItem;

  try
  {
	  nRow=1;
		if(!OpenExcel("合约采购记录表.xls",vExcel,vSheet))	return;
		ListHead2Excel(ListView1,vSheet,nRow++);
		for(i=0;i<ListView1->Items->Count;i++)
    {
    	pItem=ListView1->Items->Item[i];
        InsertExcelItem(vSheet,nRow++,
      	pItem->Caption.c_str(),
        pItem->SubItems->Strings[0].c_str(),
        pItem->SubItems->Strings[1].c_str(),
        pItem->SubItems->Strings[2].c_str(),
        pItem->SubItems->Strings[3].c_str(),
        pItem->SubItems->Strings[4].c_str(),
				NULL);
		}
	}
	catch(...)
	{
	}
}
//---------------------------------------------------------------------------

void __fastcall TTreatStockRecordForm::btnRefreshClick(TObject *Sender)
{
    RefreshDatahistory();
}
//---------------------------------------------------------------------------


void __fastcall TTreatStockRecordForm::Button1Click(TObject *Sender)
{
    RefreshData();
}
//---------------------------------------------------------------------------

void __fastcall TTreatStockRecordForm::Button2Click(TObject *Sender)
{
 Variant vExcel,vSheet;
  int nRow,i;
  TListItem *pItem;

  try
  {
	  nRow=1;
		if(!OpenExcel("合约采购记录表.xls",vExcel,vSheet))	return;
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
				NULL);
		}
	}
	catch(...)
	{
	}
}
//---------------------------------------------------------------------------

