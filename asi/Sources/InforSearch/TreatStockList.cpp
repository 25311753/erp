//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <assert.h>
#pragma hdrstop

#include "DataModule.h"
#include "BaseCode.h"
#include "TreatStockList.h"
#include "TConst.h"
#include "LdyInterface.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTreatStockListForm *TreatStockListForm;

//=========================================================================================
//合约采购列表接口，文件：TreatStockList.*
void TreatStockList(int nAuth)
{
	if(nAuth==AUTH_NONE)	return;
	CALL_FORM(TTreatStockListForm);
}
//========================================================================================

//---------------------------------------------------------------------------
__fastcall TTreatStockListForm::TTreatStockListForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

#include "AskPurchaseMT.h"
void __fastcall TTreatStockListForm::btnPickupClick(TObject *Sender)
{
	TAskPurchaseMTForm *pMT;
	pMT=new TAskPurchaseMTForm(this);
	assert(pMT!=NULL);
	pMT->m_szMaterCode=edtMater->Text;
	if(pMT->ShowModal()==mrOk)
	{
		edtMater->Text=pMT->m_szMaterCode;
	}
	delete pMT;
}
//---------------------------------------------------------------------------

void __fastcall TTreatStockListForm::btnDetailClick(TObject *Sender)
{
	TListItem *pItem;
	if((pItem=lstView->Selected)==NULL)	return;

	int nRight=GetOperatorRight(operatorcode.c_str(),"IDM_TREATSTOCK");
	//合约采购档接口，文件：TreatStock.*
	TreatStock(pItem->Caption.c_str(),nRight);
}
//---------------------------------------------------------------------------

void __fastcall TTreatStockListForm::btnToExcelClick(TObject *Sender)
{
	Variant vExcel,vSheet;
  int nRow,i;
  TListItem *pItem;
	TListView *pList;
	if(ctlPage->ActivePage==ctlCurrent)				pList=lstView;
	else if(ctlPage->ActivePage==ctlModify)		pList=lstModify;
	else if(ctlPage->ActivePage==ctlHistory)	pList=lstHistory;

  try
  {
	  nRow=1;
		if(!OpenExcel("合约采购档列表.xls",vExcel,vSheet))	return;
		ListHead2Excel(pList,vSheet,nRow++);
		for(i=0;i<pList->Items->Count;i++)
    {
    	pItem=pList->Items->Item[i];
			if(ctlPage->ActivePage==ctlModify)
			{
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
					NULL);
			}
			else
			{
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
					NULL);
			}
		}
	}
	catch(...)
	{
	}
}
//---------------------------------------------------------------------------

void __fastcall TTreatStockListForm::btnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TTreatStockListForm::lstViewClick(TObject *Sender)
{
	if(lstView->Selected==NULL)	ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TTreatStockListForm::FormShow(TObject *Sender)
{
	CString szSQL;

	edtID		->Text="";
	edtMater->Text="";
	
	m_lstFactID.Add("");
	lstFact->Items->Add("全部");
	szSQL="select * from Manufactur order by mf_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		m_lstFactID.Add(dm1->Query1->FieldByName("mf_code")->AsString.c_str());
		lstFact->Items->Add(dm1->Query1->FieldByName("mf_shortname")->AsString);
		dm1->Query1->Next();
	}
	lstFact->ItemIndex=0;

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

	lstDateType->ItemIndex=0;
	edtDate->Text="";

	ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TTreatStockListForm::btnQueryClick(TObject *Sender)
{
	CString szSQL;
	char strTemp[256],strDepart[80],strDate[80],strSHID[4],strTemp2[256];
	int nSel,i;
	TListItem *pItem;
//--------new 0630--------------------------------------------------------------
/*        szSQL.Format("select * from StockHandleman where sh_code='%s'",operatorcode);
        RunSQL(dm1->Query1,szSQL,true);
        strcpy(strSHID,dm1->Query1->FieldByName("sh_sdcode")->AsString.c_str());        */
//------------------------------------------------------------------------------
//--------new 0630--------只能看自己公司别的合约单------------------------------
/*	if(ctlPage->ActivePage==ctlCurrent)
	{
		szSQL.Format("select * from TreatStock,Manufactur,materialno,DicUnits,StockHandleman where ts_mfcode=mf_code and ts_mncode=mn_code and ts_ducode=du_code and ts_shcode=sh_code and ts_sdcode='%s'",strSHID);
	}       */
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
	if(ctlPage->ActivePage==ctlCurrent)
	{
		szSQL="select * from TreatStock,Manufactur,materialno,DicUnits,StockHandleman"
			" where ts_mfcode=mf_code and ts_mncode=mn_code and ts_ducode=du_code and ts_shcode=sh_code";
	}
//------------------------------------------------------------------------------
//------new 0630----------------------------------------------------------------
/*	else if(ctlPage->ActivePage==ctlModify)
	{
		szSQL.Format("select * from TreatStockModify,Manufactur,materialno,DicUnits,StockHandleman,operator where ts_mfcode=mf_code and ts_mncode=mn_code and ts_ducode=du_code and ts_shcode=sh_code and ts_operator=op_code and ts_sdcode='%s'",strSHID);
	}       */
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
	else if(ctlPage->ActivePage==ctlModify)
	{
		szSQL="select * from TreatStockModify,Manufactur,materialno,DicUnits,StockHandleman,operator"
			" where ts_mfcode=mf_code and ts_mncode=mn_code and ts_ducode=du_code and ts_shcode=sh_code"
			" and ts_operator=op_code";
	}
//------------------------------------------------------------------------------
//------new 0630----------------------------------------------------------------
/*	else if(ctlPage->ActivePage==ctlHistory)
	{
		szSQL.Format("select * from TreatStockHistory,Manufactur,materialno,DicUnits,StockHandleman,operator where ts_mfcode=mf_code and ts_mncode=mn_code and ts_ducode=du_code and ts_shcode=sh_code and ts_operator=op_code and ts_sdcode='%s'",strSHID);
	}       */
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
	else if(ctlPage->ActivePage==ctlHistory)
	{
		szSQL="select * from TreatStockHistory,Manufactur,materialno,DicUnits,StockHandleman"
			" where ts_mfcode=mf_code and ts_mncode=mn_code and ts_ducode=du_code and ts_shcode=sh_code";
	}       
//------------------------------------------------------------------------------
	if(!edtID->Text.IsEmpty())
	{
		sprintf(strTemp," and ts_code like '%s%%'",edtID->Text.c_str());
		szSQL+=strTemp;
	}
	if(!edtMater->Text.IsEmpty())
	{
		sprintf(strTemp," and ts_mncode like '%%%s%%'",edtMater->Text.c_str());
		szSQL+=strTemp;
	}
	if((nSel=lstFact->ItemIndex)>0 && nSel<m_lstFactID.GetSize())
	{
		sprintf(strTemp," and ts_mfcode='%s'",m_lstFactID[nSel]);
		szSQL+=strTemp;
	}
	if((nSel=lstHandle->ItemIndex)>0 && nSel<m_lstHandleID.GetSize())
	{
		sprintf(strTemp," and ts_shcode='%s'",m_lstHandleID[nSel]);
		szSQL+=strTemp;
	}
	if((nSel=lstDepart->ItemIndex)>0 && nSel<m_lstDepartID.GetSize())
	{
		sprintf(strTemp," and ts_sdcode='%s'",m_lstDepartID[nSel]);
		szSQL+=strTemp;
	}
	edtDate->Text=edtDate->Text.Trim();
	if(!edtDate->Text.IsEmpty())
	{
		if(!CheckDateEditor(edtDate))	return;
		Date2Dbdate(edtDate->Text.c_str(),strDate);
		sprintf(strTemp," and ts_inputdate%s'%s'",lstDateType->Text.c_str(),strDate);
		szSQL+=strTemp;
	}
//-----new 0630----------经办可以查看自己的单，可能是其它公司的-----------------
/*	if(ctlPage->ActivePage==ctlCurrent)
	{
                sprintf(strTemp," union select * from TreatStock,Manufactur,materialno,DicUnits,StockHandleman where ts_mfcode=mf_code and ts_mncode=mn_code and ts_ducode=du_code and ts_shcode=sh_code and ts_shcode='%s'",operatorcode);
		szSQL+=strTemp;
	}       */
//------------------------------------------------------------------------------
//------new 0630--------经办可以查自己的单(已修改)， 同公司的可查自己公司的单(已修改) ，修改人都可以查看自己修改的单-
/*	else if(ctlPage->ActivePage==ctlModify)
	{
                sprintf(strTemp," union select * from TreatStockModify,Manufactur,materialno,DicUnits,StockHandleman,operator where ts_mfcode=mf_code and ts_mncode=mn_code and ts_ducode=du_code and ts_shcode=sh_code and ts_operator=op_code and ts_shcode='%s'",operatorcode);
                szSQL+=strTemp;
                sprintf(strTemp," union select * from TreatStockModify,Manufactur,materialno,DicUnits,StockHandleman,operator where ts_mfcode=mf_code and ts_mncode=mn_code and ts_ducode=du_code and ts_shcode=sh_code and ts_operator=op_code and ts_operator='%s'",operatorcode);
                szSQL+=strTemp;
	}       */
//------------------------------------------------------------------------------
//------new 0630----------------------------------------------------------------
/*	else if(ctlPage->ActivePage==ctlHistory)
	{
                sprintf(strTemp," union select * from TreatStockHistory,Manufactur,materialno,DicUnits,StockHandleman,operator where ts_mfcode=mf_code and ts_mncode=mn_code and ts_ducode=du_code and ts_shcode=sh_code and ts_operator=op_code and ts_shcode='%s'",operatorcode);
                szSQL+=strTemp;
                sprintf(strTemp," union select * from TreatStockHistory,Manufactur,materialno,DicUnits,StockHandleman,operator where ts_mfcode=mf_code and ts_mncode=mn_code and ts_ducode=du_code and ts_shcode=sh_code and ts_operator=op_code and ts_operator='%s'",operatorcode);
                szSQL+=strTemp;
	}       */
//------------------------------------------------------------------------------

	TListView *pList;
	if(ctlPage->ActivePage==ctlCurrent)		pList=lstView;
	else if(ctlPage->ActivePage==ctlModify)		pList=lstModify;
	else if(ctlPage->ActivePage==ctlHistory)	pList=lstHistory;

	pList->Items->Clear();
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		pItem=pList->Items->Add();
		assert(pItem!=NULL);

		strDepart[0]='\0';
		for(i=1;i<m_lstDepartID.GetSize();i++)
		{
			if(m_lstDepartID[i]==dm1->Query1->FieldByName("ts_sdcode")->AsString.c_str())
			{
				strcpy(strDepart,lstDepart->Items->Strings[i].c_str());
				break;
			}
		}
		pItem->Caption=dm1->Query1->FieldByName("ts_code")->AsString;
		pItem->SubItems->Add(dm1->Query1->FieldByName("ts_mncode")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("mn_name")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("mf_shortname")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("ts_mfcard")->AsString);
		pItem->SubItems->Add(DateField2Text(dm1->Query1->FieldByName("ts_inuredate")));
		pItem->SubItems->Add(dm1->Query1->FieldByName("du_name")->AsString);
//		pItem->SubItems->Add(FloatField2String(dm1->Query1->FieldByName("ts_price"),2));
//-----new 0704-----------------------------------------------------------------
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
		pItem->SubItems->Add(dm1->Query1->FieldByName("sh_name")->AsString);
		pItem->SubItems->Add(strDepart);
		pItem->SubItems->Add(IntField2Text(dm1->Query1->FieldByName("ts_days")));

		if(ctlPage->ActivePage==ctlModify)
		{
			pItem->SubItems->Add(dm1->Query1->FieldByName("op_name")->AsString.c_str());
			pItem->SubItems->Add(Field2TimeString(dm1->Query1->FieldByName("ts_opertime")));
			strcpy(strTemp,dm1->Query1->FieldByName("ts_modflag")->AsString.c_str());
			if(strTemp[0]=='E')				pItem->SubItems->Add("更正");
			else if(strTemp[0]=='D')	pItem->SubItems->Add("删除");
		}

   	pItem->SubItems->Add(DateField2Text(dm1->Query1->FieldByName("ts_inputdate")));
        if(ctlPage->ActivePage==ctlHistory)pItem->SubItems->Add(DateField2Text(dm1->Query1->FieldByName("ts_deledate")));

		dm1->Query1->Next();
	}

	ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TTreatStockListForm::lstViewSelectItem(TObject *Sender,
      TListItem *Item, bool Selected)
{
	if(!Selected)	return;
  ResetCtrl();	
}
//---------------------------------------------------------------------------

void TTreatStockListForm::ResetCtrl()
{
	btnDetail->Enabled=lstView->Selected!=NULL;
}
void __fastcall TTreatStockListForm::lstViewDblClick(TObject *Sender)
{
	btnDetailClick(Sender);	
}
//---------------------------------------------------------------------------
void __fastcall TTreatStockListForm::lstFactExit(TObject *Sender)
{
	int nSel,i;

	lstFact->Text=lstFact->Text.Trim();
	if((nSel=lstFact->Items->IndexOf(lstFact->Text))<=0 || nSel>=m_lstFactID.GetSize())
	{
		lstFact->Text=lstFact->Text.UpperCase();
		for(i=0;i<m_lstFactID.GetSize();i++)
		{
			if(m_lstFactID[i]==lstFact->Text.c_str())
			{
				lstFact->ItemIndex=i;
				break;
			}
		}
		if(i==m_lstFactID.GetSize())	lstFact->ItemIndex=-1;
	}
}
//---------------------------------------------------------------------------

void __fastcall TTreatStockListForm::lstHandleExit(TObject *Sender)
{
	int nSel,i;

	lstHandle->Text=lstHandle->Text.Trim();
	if((nSel=lstHandle->Items->IndexOf(lstHandle->Text))<=0 || nSel>=m_lstHandleID.GetSize())
	{
		lstHandle->Text=lstHandle->Text.UpperCase();
		for(i=0;i<m_lstHandleID.GetSize();i++)
		{
			if(m_lstHandleID[i]==lstHandle->Text.c_str())
			{
				lstHandle->ItemIndex=i;
				break;
			}
		}
		if(i==m_lstHandleID.GetSize())	lstHandle->ItemIndex=-1;
	}
}
//---------------------------------------------------------------------------

#include "FactorySearch.h"
void __fastcall TTreatStockListForm::btnFactPickupClick(TObject *Sender)
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

void __fastcall TTreatStockListForm::ctlCurrentShow(TObject *Sender)
{
	CString szSQL;
  int nSel;

  szSQL="select * from Manufactur where mf_code in"
  	" (select distinct ts_mfcode from TreatStock)"
    " order by mf_code";
  lstFact->Items->Clear();
  m_lstFactID.RemoveAll();

	m_lstFactID.Add("");
	lstFact->Items->Add("全部");

  RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		m_lstFactID.Add(dm1->Query1->FieldByName("mf_code")->AsString.c_str());
		lstFact->Items->Add(dm1->Query1->FieldByName("mf_shortname")->AsString);
  	dm1->Query1->Next();
  }
  if((nSel=lstFact->Items->IndexOf(lstFact->Text))>=0)	lstFact->ItemIndex=nSel;
	else	lstFact->ItemIndex=0;
}
//---------------------------------------------------------------------------

void __fastcall TTreatStockListForm::ctlModifyShow(TObject *Sender)
{
	CString szSQL;
  int nSel;

  szSQL="select * from Manufactur where mf_code in"
  	" (select distinct ts_mfcode from TreatStockModify)"
    " order by mf_code";
  lstFact->Items->Clear();
  m_lstFactID.RemoveAll();

	m_lstFactID.Add("");
	lstFact->Items->Add("全部");

  RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		m_lstFactID.Add(dm1->Query1->FieldByName("mf_code")->AsString.c_str());
		lstFact->Items->Add(dm1->Query1->FieldByName("mf_shortname")->AsString);
  	dm1->Query1->Next();
  }
  if((nSel=lstFact->Items->IndexOf(lstFact->Text))>=0)	lstFact->ItemIndex=nSel;
	else	lstFact->ItemIndex=0;
}
//---------------------------------------------------------------------------

void __fastcall TTreatStockListForm::ctlHistoryShow(TObject *Sender)
{
	CString szSQL;
  int nSel;

  szSQL="select * from Manufactur where mf_code in"
  	" (select distinct ts_mfcode from TreatStockHistory)"
    " order by mf_code";
  lstFact->Items->Clear();
  m_lstFactID.RemoveAll();

	m_lstFactID.Add("");
	lstFact->Items->Add("全部");

  RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		m_lstFactID.Add(dm1->Query1->FieldByName("mf_code")->AsString.c_str());
		lstFact->Items->Add(dm1->Query1->FieldByName("mf_shortname")->AsString);
  	dm1->Query1->Next();
  }
  if((nSel=lstFact->Items->IndexOf(lstFact->Text))>=0)	lstFact->ItemIndex=nSel;
	else	lstFact->ItemIndex=0;
}
//---------------------------------------------------------------------------

void __fastcall TTreatStockListForm::Button1Click(TObject *Sender)
{TListItem  *ListItem;
 ListItem=lstView->Selected;
 if(ListItem==NULL)
 { Application->MessageBox("请选择你所需终止合约!","系统信息",MB_OK);
  return;
  }
 dm1->Query4->Close();
 dm1->Query4->SQL->Clear();
 dm1->Query4->SQL->Add(" Select * from TreatStock where (ts_code=:t1)and(ts_shcode=:t2) ");
 dm1->Query4->ParamByName("t1")->AsString=ListItem->Caption;
 dm1->Query4->ParamByName("t2")->AsString=operatorcode;
 dm1->Query4->Open();
 dm1->Query4->First();
 if(dm1->Query4->Eof)
  {
  Application->MessageBox("你不是此合约经办人，无权终止!","系统信息",MB_OK);
  return;
  }
 if (Application->MessageBox("真的想终止此合约吗?","系统信息",MB_YESNO) == IDYES)
 {
 dm1->Query4->Close();
 dm1->Query4->SQL->Clear();
 dm1->Query4->SQL->Add(" Delete from TreatStock where ts_code=:t1 ");
 dm1->Query4->ParamByName("t1")->AsString=ListItem->Caption;
 dm1->Query4->ExecSQL();
 ListItem->Delete();
 }
}
//---------------------------------------------------------------------------

