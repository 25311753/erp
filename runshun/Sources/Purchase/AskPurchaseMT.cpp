//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#pragma hdrstop

#include "DataModule.h"
#include "BaseCode.h"
#include "AskPurchaseMT.h"
#include "TConst.h"
#include "MaterialEdit.h"
#include "LdyInterface.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAskPurchaseMTForm *AskPurchaseMTForm;

void QueryMaterialCode(int nAuth)
{
	CALL_FORM(TAskPurchaseMTForm);
}


//---------------------------------------------------------------------------
__fastcall TAskPurchaseMTForm::TAskPurchaseMTForm(TComponent* Owner)
	: TForm(Owner)
{
	m_nTreatType=0;
	m_cCurCorp	='\0';
	m_cCurLarge	='\0';
	m_enClick=EN_CLICK_NONE;
	m_pNode=NULL;
}
//---------------------------------------------------------------------------
void __fastcall TAskPurchaseMTForm::FormShow(TObject *Sender)
{
	CString szSQL;
	char strID[256];
	int i;
	TListItem *pItem;

  EnableEdit(edtSpec,false);
  edtSpec->Text="";
	edtCorp->Text="";
	edtID0->Text="";
	edtID1->Text="";

	szSQL="select * from diccorp order by cp_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		m_lstCorpID.Add(dm1->Query1->FieldByName("cp_code")->AsString.c_str());
		lstCorp->Items->Add(dm1->Query1->FieldByName("cp_name")->AsString);
		dm1->Query1->Next();
	}

	szSQL="select * from diclargetype order by lt_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		m_lstLargID.Add(dm1->Query1->FieldByName("lt_code")->AsString.c_str());
		lstLarge->Items->Add(dm1->Query1->FieldByName("lt_name")->AsString);
		dm1->Query1->Next();
	}

	lstTreatType->ItemIndex=m_nTreatType;

	if(!m_szMaterCode.IsEmpty())
	{
		memset(strID,0,sizeof(strID));
		strcpy(strID,m_szMaterCode.c_str());
		if(strID[5]!='-')
		{
			ShowMessage("不正确的材料编号，编号的第六位应该为“-”");
			return;
		}
		edtID1->Text=strID+6;	strID[5]='\0';
		edtID0->Text=strID+1;	strID[1]='\0';
		edtCorp->Text=strID;
		m_enClick=EN_CLICK_INIT;
		ResetAllUI();
		m_enClick=EN_CLICK_NONE;
		for(i=0;i<lstView->Items->Count;i++)
		{
			pItem=lstView->Items->Item[i];
			if(edtID1->Text==pItem->Caption)
			{
				edtSpec->Text=pItem->SubItems->Strings[0];
				break;
			}
		}
	}

	edtPrefixID->Text="";
  edtSearchText->Text="";
	edtID->Text="";
	edtName->Text="";
        edtUnits->Text="";
	EnableEdit(edtID,false);
	EnableEdit(edtName,false);
        EnableEdit(edtUnits,false);
}

void TAskPurchaseMTForm::ResetCorp()
{
	int i;
	for(i=0;i<m_lstCorpID.GetSize();i++)
	{
		if(m_cCurCorp==m_lstCorpID[i][0])
		{
			lstCorp->ItemIndex=i;
			break;
		}
	}
	if(i==m_lstCorpID.GetSize())	lstCorp->ItemIndex=-1;
}

void TAskPurchaseMTForm::ResetMiddle()
{
	CString szSQL;

	m_lstMidID.RemoveAll();
	lstMid->Items->Clear();
	if(m_cCurLarge=='\0')	return;
	szSQL.Format("select * from dicmiddletype where mt_code like '%c_' order by mt_code",m_cCurLarge);
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		m_lstMidID.Add(dm1->Query1->FieldByName("mt_code")->AsString.c_str());
		lstMid->Items->Add(dm1->Query1->FieldByName("mt_name")->AsString);
		dm1->Query1->Next();
	}
}

void TAskPurchaseMTForm::ResetMin()
{
	CString szSQL;

	m_lstMinID.RemoveAll();
	lstMin->Items->Clear();
	if(m_szCurMid.IsEmpty())	return;
	szSQL.Format("select * from dicsmalltype where st_code like '%s%%' order by st_code",m_szCurMid);
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		m_lstMinID.Add(dm1->Query1->FieldByName("st_code")->AsString.c_str());
		lstMin->Items->Add(dm1->Query1->FieldByName("st_name")->AsString);
		dm1->Query1->Next();
	}
}

void TAskPurchaseMTForm::ResetView()
{
	CString szSQL,szSQL1;
	TListItem *pItem;
	char strID[80];

	lstView->Items->Clear();
  if(m_cCurCorp=='\0')	return;
	if(m_szCurMin.IsEmpty())	return;
	if(m_szCurMin.GetLength()!=4)	return;

	szSQL.Format("select * from materialno where mn_code like '%c%s%%'",m_cCurCorp,m_szCurMin);
	if(lstTreatType->ItemIndex==1)
		szSQL+=" and mn_code not in (select distinct ts_mncode from TreatStock)";
	else if(lstTreatType->ItemIndex==2)
		szSQL+=" and mn_code in (select distinct ts_mncode from TreatStock)";
  szSQL+=" and mn_code not in (select cc_ocode from codecheck)";
  szSQL+=" order by mn_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		memset(strID,0,sizeof(strID));
		strcpy(strID,dm1->Query1->FieldByName("mn_code")->AsString.c_str());
		pItem=lstView->Items->Add();
		assert(pItem!=NULL);
		pItem->Caption=strID+6;
		pItem->SubItems->Add(dm1->Query1->FieldByName("mn_name")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("mn_usage")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("mn_rem")->AsString);
                if(!dm1->Query1->FieldByName("mn_ducode")->IsNull)
                {
                      	szSQL1.Format("select * from DicUnits where du_code='%s'",dm1->Query1->FieldByName("mn_ducode")->AsString);
                       	RunSQL(dm1->Query2,szSQL1,true);
                        pItem->SubItems->Add(dm1->Query2->FieldByName("du_name")		->AsString);
                }
                else
	        pItem->SubItems->Add("");
		pItem->SubItems->Add(dm1->Query1->FieldByName("mn_date")->AsString);                

		dm1->Query1->Next();
	}
}

//---------------------------------------------------------------------------
void __fastcall TAskPurchaseMTForm::FormKeyDown(TObject *Sender, WORD &Key,TShiftState Shift)
{
	if(Key==VK_RETURN)
		KeyReturnHandle(ActiveControl);
}
//---------------------------------------------------------------------------
void __fastcall TAskPurchaseMTForm::lstCorpClick(TObject *Sender)
{
	int nSel;
	if((nSel=lstCorp->ItemIndex)<0 || nSel>=m_lstCorpID.GetSize())	return;
	m_enClick=EN_CLICK_CORP;
	edtCorp->Text=(LPCSTR)m_lstCorpID[nSel];
	ResetAllUI();
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseMTForm::lstLargeClick(TObject *Sender)
{
	int nSel;
	char strTemp[80],strID[80];

	if((nSel=lstLarge->ItemIndex)<0 || nSel>=m_lstLargID.GetSize())	return;
	m_enClick=EN_CLICK_LARGE;
	strcpy(strTemp,m_lstLargID[nSel]);
	memset(strID,0,sizeof(strID));
	strcpy(strID,edtID0->Text.c_str());
	strID[0]=strTemp[0];
	edtID0->Text=strID;
	ResetAllUI();
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseMTForm::lstMidClick(TObject *Sender)
{
	int nSel;
	char strTemp[80],strID[80];

	if((nSel=lstMid->ItemIndex)<0 || nSel>=m_lstMidID.GetSize())	return;
	m_enClick=EN_CLICK_MID;
	strcpy(strTemp,m_lstMidID[nSel]);
	memset(strID,0,sizeof(strID));
	strcpy(strID,edtID0->Text.c_str());
	strID[1]=strTemp[1];
	edtID0->Text=strID;
	ResetAllUI();
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseMTForm::lstMinClick(TObject *Sender)
{
	int nSel;
	char strTemp[80],strID[80];

	if((nSel=lstMin->ItemIndex)<0 || nSel>=m_lstMinID.GetSize())	return;
	m_enClick=EN_CLICK_MIN;
	edtID0->Text=(LPCSTR)m_lstMinID[nSel];
	ResetAllUI();
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseMTForm::edtID0Change(TObject *Sender)
{
	if(m_enClick!=EN_CLICK_NONE)	return;

	ResetAllUI();
}

void TAskPurchaseMTForm::ResetAllUI()
{
	char strMid[80];
	CString szSQL;
	int i,nSel;
	bool bCorp,bLarge,bMid;
	char strTemp[80],strID[80]={0};
	char cCorp;

	strcpy(strTemp,edtCorp->Text.c_str());
	cCorp=strTemp[0];
	strcpy(strID,edtID0->Text.c_str());

	bCorp=bLarge=bMid=false;
	if(cCorp!=m_cCurCorp)
	{
		bCorp=true;
		m_cCurCorp=cCorp;
		ResetCorp();
	}
	if(bCorp || strID[0]!=m_cCurLarge)
	{
		bLarge=true;
		m_cCurLarge=strID[0];
		for(i=0;i<m_lstLargID.GetSize();i++)
		{
			if(strID[0]==m_lstLargID[i][0])
			{
				lstLarge->ItemIndex=i;
				break;
			}
		}
		if(i==m_lstLargID.GetSize())	lstLarge->ItemIndex=-1;
		ResetMiddle();
	}
	strcpy(strMid,strID);
	strMid[2]='\0';
	if(bLarge || m_szCurMid!=strMid)
	{
		m_szCurMid=strMid;
		bMid=true;
		for(i=0;i<m_lstMidID.GetSize();i++)
		{
			if(m_lstMidID[i]==strMid)
			{
				lstMid->ItemIndex=i;
				break;
			}
		}
		if(i==m_lstMidID.GetSize())	lstMid->ItemIndex=-1;
		ResetMin();
	}
	if(bMid || m_szCurMin!=strID)
	{
		m_szCurMin=strID;
		for(i=0;i<m_lstMinID.GetSize();i++)
		{
			if(m_lstMinID[i]==strID)
			{
				lstMin->ItemIndex=i;
				break;
			}
		}
		if(i==m_lstMinID.GetSize())	lstMin->ItemIndex=-1;
		ResetView();
	}
	m_enClick=EN_CLICK_NONE;
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseMTForm::edtCorpChange(TObject *Sender)
{
	if(m_enClick!=EN_CLICK_NONE)	return;
  ResetAllUI();	
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseMTForm::edtID1Change(TObject *Sender)
{
	int i;
	TListItem *pItem;

	if(m_enClick!=EN_CLICK_NONE)	return;
	for(i=0;i<lstView->Items->Count;i++)
	{
		pItem=lstView->Items->Item[i];
		if(pItem->Caption==edtID1->Text)
		{
			lstView->Selected=pItem;
			break;
		}
	}
	if(i==lstView->Items->Count)	edtSpec->Text="";
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseMTForm::lstViewSelectItem(TObject *Sender,TListItem *Item, bool Selected)
{
	TListItem *pItem;
        CString szSQL1;
	if(!Selected || lstView->Selected==NULL)	return;
	pItem=lstView->Selected;
	m_enClick=EN_CLICK_VIEW;
	edtID1->Text=pItem->Caption;
	edtSpec->Text=pItem->SubItems->Strings[0];
        Memo1->Text=pItem->SubItems->Strings[2];

        edtID->Text=pItem->Caption;
        edtName->Text=pItem->SubItems->Strings[0];
        edtUnits->Text=pItem->SubItems->Strings[3];

	m_enClick=EN_CLICK_NONE;

        szSQL1.Format("select * from materialno where mn_code='%s%s-%s'",
                edtCorp->Text.c_str(),edtID0->Text.c_str(),edtID1->Text.c_str());
        RunSQL(dm1->Query1,szSQL1,true);
//        dm1->Query1->FieldByName("mn_code")->AsString;

//显示产品外观
        ADOT1->Filtered=false;
        ADOT1->Active=true;
        ADOT1->Filtered=false;
        ADOT1->Filter=AnsiString("ml_mncode='")+dm1->Query1->FieldByName("mn_code")->AsString+"'";
        ADOT1->Filtered=true;
        ADOT1->FindFirst();
        ADOT1->Active=true;

}

//----------------new 0526------------------------------------------------------

void __fastcall TAskPurchaseMTForm::btnOKClick(TObject *Sender)
{
	CString szSQL;

  if(ctlPage->ActivePage==ctlType)                                              //分类查询
  {
		if(edtCorp->Text.IsEmpty() || edtID0->Text.IsEmpty() || edtID1->Text.IsEmpty())
		{
			ShowMessage("请输入完整的材料编号");
			return;
		}

                
		szSQL.Format("select * from materialno where mn_code='%s%s-%s'",
			edtCorp->Text.c_str(),edtID0->Text.c_str(),edtID1->Text.c_str());
		RunSQL(dm1->Query1,szSQL,true);
		if(dm1->Query1->Eof)
		{
			ShowMessage("没有该材料编号");
			return;
		}
		m_szMaterCode=dm1->Query1->FieldByName("mn_code")->AsString;
	}
	else if(ctlPage->ActivePage==ctlTree || ctlPage->ActivePage==ctlSearch) //目录查询或者搜索
	{
		if(edtID->Text.IsEmpty())
		{
			ShowMessage("请选择一个材料编号");
			return;
		}
		m_szMaterCode=edtID->Text;
	}
	ModalResult=mrOk;
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
/*
void __fastcall TAskPurchaseMTForm::btnOKClick(TObject *Sender)
{
	CString szSQL;

  if(ctlPage->ActivePage==ctlType)                                              //分类查询
  {
		if(edtCorp->Text.IsEmpty() || edtID0->Text.IsEmpty() || edtID1->Text.IsEmpty())
		{
			ShowMessage("请输入完整的材料编号");
			return;
		}
		szSQL.Format("select * from materialno where mn_code='%s%s-%s'",
			edtCorp->Text.c_str(),edtID0->Text.c_str(),edtID1->Text.c_str());
		RunSQL(dm1->Query1,szSQL,true);
		if(dm1->Query1->Eof)
		{
			ShowMessage("没有该材料编号");
			return;
		}
		m_szMaterCode=dm1->Query1->FieldByName("mn_code")->AsString;
	}
	else if(ctlPage->ActivePage==ctlTree || ctlPage->ActivePage==ctlSearch) //目录查询或者搜索
	{
		if(edtID->Text.IsEmpty())
		{
			ShowMessage("请选择一个材料编号");
			return;
		}
		m_szMaterCode=edtID->Text;
	}
	ModalResult=mrOk;
}
*/
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseMTForm::btnToExcelClick(TObject *Sender)
{
	Variant vExcel,vSheet;
  int nRow,i,nSel;
  TListItem *pItem;
	char strCode[80];
	CString szSQL;

	if(ctlPage->ActivePage==ctlType)
	{
		try
		{
			nRow=1;
			if(!OpenExcel("请购单列表.xls",vExcel,vSheet))	return;
			InsertExcelItem(vSheet,nRow++,"公司","大类","中类","小类","材料编号","品名规格","用途","单位","建档日期",NULL);
			for(i=0;i<lstView->Items->Count;i++)
			{
    		pItem=lstView->Items->Item[i];
				sprintf(strCode,"%s%s-%s",edtCorp->Text.c_str(),edtID0->Text.c_str(),pItem->Caption.c_str());
				InsertExcelItem(vSheet,nRow++,
					lstCorp->Text.c_str(),
					lstLarge->Text.c_str(),
					lstMid->Text.c_str(),
					lstMin->Text.c_str(),
					strCode,
					pItem->SubItems->Strings[0].c_str(),
					pItem->SubItems->Strings[1].c_str(),
					pItem->SubItems->Strings[3].c_str(),
					pItem->SubItems->Strings[4].c_str(),                                        
					NULL);
			}
		}
		catch(...)
		{
		}
	}
	else if(ctlPage->ActivePage==ctlTree)
	{
		char strCorp[80],strLarge[80],strMid[80],strMin[80];
		TTreeNode *pNode;

		if(lstTreeView->Items->Count==0)
		{
			ShowMessage("列表中没有材料编号的详细资料");
			return;
		}
		if((pNode=lstTree->Selected)==NULL)	return;
		nSel=(int)pNode->Data;
		if(m_lstTreeID[nSel].GetLength()!=4)	return;

		strcpy(strCorp,lstTreeCorp->Text.c_str());
		strcpy(strMin,pNode->Text.c_str());
		if((pNode=pNode->Parent)==NULL)	return;
		strcpy(strMid,pNode->Text.c_str());
		if((pNode=pNode->Parent)==NULL)	return;
		strcpy(strLarge,pNode->Text.c_str());

		try
		{
			nRow=1;
			if(!OpenExcel("请购单列表.xls",vExcel,vSheet))	return;
			InsertExcelItem(vSheet,nRow++,"公司","大类","中类","小类","材料编号","品名规格","用途","单位","建档日期",NULL);
			for(i=0;i<lstTreeView->Items->Count;i++)
			{
    		pItem=lstTreeView->Items->Item[i];
				InsertExcelItem(vSheet,nRow++,
					strCorp,
					strLarge,
					strMid,
					strMin,
					pItem->Caption.c_str(),
					pItem->SubItems->Strings[0].c_str(),
					pItem->SubItems->Strings[1].c_str(),
					pItem->SubItems->Strings[3].c_str(),
					pItem->SubItems->Strings[4].c_str(),
					NULL);
			}
		}
		catch(...)
		{
		}
	}
  else if(ctlPage->ActivePage==ctlSearch)
	{
		try
		{
			nRow=1;
			if(!OpenExcel("请购单列表.xls",vExcel,vSheet))	return;
			InsertExcelItem(vSheet,nRow++,"公司","大类","中类","小类","材料编号","品名规格","用途","单位","建档日期",NULL);
			for(i=0;i<lstSearchView->Items->Count;i++)
			{
    		pItem=lstSearchView->Items->Item[i];
				strcpy(strCode,pItem->Caption.c_str());
				strCode[5]='\0';
				szSQL.Format("select * from diccorp,diclargetype,dicmiddletype,dicsmalltype"
					" where cp_code='%c' and lt_code='%c' and mt_code='%c%c' and st_code='%s'",
					strCode[0],strCode[1],strCode[1],strCode[2],strCode+1);
				RunSQL(dm1->Query1,szSQL,true);
				if(!dm1->Query1->Eof)
				{
					InsertExcelItem(vSheet,nRow++,
						dm1->Query1->FieldByName("cp_name")->AsString.c_str(),
						dm1->Query1->FieldByName("lt_name")->AsString.c_str(),
						dm1->Query1->FieldByName("mt_name")->AsString.c_str(),
						dm1->Query1->FieldByName("st_name")->AsString.c_str(),
						pItem->Caption.c_str(),
						pItem->SubItems->Strings[0].c_str(),
						pItem->SubItems->Strings[1].c_str(),
						pItem->SubItems->Strings[3].c_str(),
						pItem->SubItems->Strings[4].c_str(),
						NULL);
				}
			}
		}
		catch(...)
		{
		}
  }
  else if(ctlPage->ActivePage==ctlPrefix)
	{
		try
		{
			nRow=1;
			if(!OpenExcel("请购单列表.xls",vExcel,vSheet))	return;
			InsertExcelItem(vSheet,nRow++,"公司","大类","中类","小类","材料编号","品名规格","用途","单位","将档日期",NULL);
			for(i=0;i<lstPrefixView->Items->Count;i++)
			{
    		pItem=lstPrefixView->Items->Item[i];
				InsertExcelItem(vSheet,nRow++,
					pItem->Caption.c_str(),
					pItem->SubItems->Strings[0].c_str(),
					pItem->SubItems->Strings[1].c_str(),
					pItem->SubItems->Strings[2].c_str(),
					pItem->SubItems->Strings[3].c_str(),
					pItem->SubItems->Strings[4].c_str(),
					pItem->SubItems->Strings[5].c_str(),
					pItem->SubItems->Strings[7].c_str(),
					pItem->SubItems->Strings[8].c_str(),                                        
					NULL);
			}
		}
		catch(...)
		{
		}
  }
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseMTForm::ctlTreeShow(TObject *Sender)
{
	if(m_bTreeInitialed)	return;
	m_bTreeInitialed=true;
	CArray<BASE2COLDATA,BASE2COLDATA>lstLarge,lstMid,lstMin;
	BASE2COLDATA rwData;

  TTreeNode *pNode,*pLarge,*pMid,*pMin;
	CString szSQL,*pID;
	int i,j;
	char strID[80],strLarge[80],strMid[80];

	szSQL="select * from diccorp order by cp_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		m_lstTreeCorpID.Add(dm1->Query1->FieldByName("cp_code")->AsString.c_str());
	  lstTreeCorp->Items->Add(dm1->Query1->FieldByName("cp_name")->AsString);
		dm1->Query1->Next();
	}
	lstTreeCorp->ItemIndex=0;

	szSQL="select * from diclargetype order by lt_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		m_lstTreeID.Add(dm1->Query1->FieldByName("lt_code")->AsString.c_str());
	  pNode=lstTree->Items->AddChild(NULL,dm1->Query1->FieldByName("lt_name")->AsString);
		pNode->Data=(void*)(m_lstTreeID.GetSize()-1);
		dm1->Query1->Next();
	}

	pLarge=lstTree->Items->Item[0];
	strcpy(strLarge,m_lstTreeID[(int)pLarge->Data]);
	szSQL="select * from dicmiddletype"
		" where mt_code in"
		"("
		"select distinct substring(mn_code,2,2) from materialno"
		")"
		" order by mt_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		strcpy(strID,dm1->Query1->FieldByName("mt_code")->AsString.c_str());
		if(strLarge[0]!=strID[0])
		{
			while(1)
			{
				pLarge=pLarge->getNextSibling();
				if(pLarge==NULL)	break;
				strcpy(strLarge,m_lstTreeID[(int)pLarge->Data]);
				if(strLarge[0]==strID[0])	break;
			}
		}
		if(pLarge==NULL)	break;

		m_lstTreeID.Add(dm1->Query1->FieldByName("mt_code")->AsString.c_str());
	  pNode=lstTree->Items->AddChild(pLarge,dm1->Query1->FieldByName("mt_name")->AsString);
		pNode->Data=(void*)(m_lstTreeID.GetSize()-1);

		dm1->Query1->Next();
	}

	pLarge=lstTree->Items->Item[0];
	strcpy(strLarge,m_lstTreeID[(int)pLarge->Data]);
	pMid=pLarge->getFirstChild();
	if(pMid!=NULL)	strcpy(strMid,m_lstTreeID[(int)pMid->Data]);

	szSQL="select * from dicsmalltype"
		" where st_code in"
		"("
		"select distinct substring(mn_code,2,4) from materialno"
		")"
		" order by st_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		strcpy(strID,dm1->Query1->FieldByName("st_code")->AsString.c_str());
		if(strLarge[0]!=strID[0])
		{
			while(1)
			{
				pLarge=pLarge->getNextSibling();
				if(pLarge==NULL)	break;
				strcpy(strLarge,m_lstTreeID[(int)pLarge->Data]);
				if(strLarge[0]==strID[0])	break;
			}
		}
		if(pLarge==NULL)	break;

		if(strMid[0]!=strID[0] || strMid[1]!=strID[1])
		{
			pMid=pLarge->getFirstChild();
			while(1)
			{
				if(pMid==NULL)	break;
				strcpy(strMid,m_lstTreeID[(int)pMid->Data]);
				if(strMid[0]==strID[0] && strMid[1]==strID[1])	break;
				pMid=pLarge->GetNextChild(pMid);
			}
		}
		if(pMid!=NULL)
		{
			m_lstTreeID.Add(dm1->Query1->FieldByName("st_code")->AsString.c_str());
			pNode=lstTree->Items->AddChild(pMid,dm1->Query1->FieldByName("st_name")->AsString);
			pNode->Data=(void*)(m_lstTreeID.GetSize()-1);
		}
		dm1->Query1->Next();
	}
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseMTForm::lstTreeClick(TObject *Sender)
{
	TTreeNode *pNode=lstTree->Selected;
  if(pNode==NULL)	return;
	int nSel,nCorp;
	TListItem *pItem;
	CString szSQL,szSQL1;
	
	if(pNode==m_pNode)	return;
	nSel=(int)pNode->Data;
	if(nSel<0 || nSel>=m_lstTreeID.GetSize())	return;

	lstTreeView->Items->Clear();
//	if(m_lstTreeID[nSel].GetLength()!=4)	return;

	if((nCorp=lstTreeCorp->ItemIndex)<0 || nCorp>=m_lstTreeCorpID.GetSize())	return;

	szSQL.Format("select * from materialno where mn_code like '%s%s-%%'",m_lstTreeCorpID[nCorp],m_lstTreeID[nSel]);
	if(lstTreatType->ItemIndex==1)
		szSQL+=" and mn_code not in (select distinct ts_mncode from TreatStock)";
	else if(lstTreatType->ItemIndex==2)
		szSQL+=" and mn_code in (select distinct ts_mncode from TreatStock)";
	szSQL+=" and mn_code not in (select cc_ocode from codecheck)";

	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		pItem=lstTreeView->Items->Add();
		assert(pItem!=NULL);
		pItem->Caption=dm1->Query1->FieldByName("mn_code")->AsString;
		pItem->SubItems->Add(dm1->Query1->FieldByName("mn_name")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("mn_usage")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("mn_rem")->AsString);
                if(!dm1->Query1->FieldByName("mn_ducode")->IsNull)
                {
                        szSQL1.Format("select * from DicUnits where du_code='%s'",dm1->Query1->FieldByName("mn_ducode")->AsString);
                        RunSQL(dm1->Query2,szSQL1,true);
                        pItem->SubItems->Add(dm1->Query2->FieldByName("du_name")		->AsString);
                }
                else
                pItem->SubItems->Add("");
		pItem->SubItems->Add(dm1->Query1->FieldByName("mn_date")->AsString);                
		dm1->Query1->Next();
	}
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseMTForm::lstTreeChange(TObject *Sender,TTreeNode *Node)
{
	lstTreeClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseMTForm::lstTreeViewSelectItem(TObject *Sender,
      TListItem *Item, bool Selected)
{
	TListItem *pItem;
	if(!Selected)	return;

	if((pItem=lstTreeView->Selected)==NULL)	return;
  edtID->Text=pItem->Caption;
  edtName->Text=pItem->SubItems->Strings[0];
  edtUnits->Text=pItem->SubItems->Strings[3];

        ADOT1->Filtered=false;
        ADOT1->Active=true;
        ADOT1->Filtered=false;
        ADOT1->Filter=AnsiString("ml_mncode='")+edtID->Text+"'";
        ADOT1->Filtered=true;
        ADOT1->FindFirst();
        ADOT1->Active=true;

}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseMTForm::lstTreeCorpClick(TObject *Sender)
{
	lstTreeClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseMTForm::lstSearchViewSelectItem(
      TObject *Sender, TListItem *Item, bool Selected)
{
	TListItem *pItem;
	if(!Selected)	return;

	if((pItem=lstSearchView->Selected)==NULL)	return;
  edtID->Text=pItem->Caption;
  edtName->Text=pItem->SubItems->Strings[0];
  edtUnits->Text=pItem->SubItems->Strings[3];

        ADOT1->Filtered=false;
        ADOT1->Active=true;
        ADOT1->Filtered=false;
        ADOT1->Filter=AnsiString("ml_mncode='")+edtID->Text+"'";
        ADOT1->Filtered=true;
        ADOT1->FindFirst();
        ADOT1->Active=true;

}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseMTForm::btnSearchClick(TObject *Sender)
{
	CString szSQL,szSQL1;
	TListItem *pItem;

	edtSearchText->Text=edtSearchText->Text.Trim();
	if(edtSearchText->Text.IsEmpty())
	{
		ShowMessage("请输入搜索条件");
		if(edtSearchText->CanFocus())	edtSearchText->SetFocus();
		return;
	}
	if(strchr(edtSearchText->Text.c_str(),'\'')!=NULL)
	{
		ShowMessage("搜索条件中请不要包含单引号");
		if(edtSearchText->CanFocus())	edtSearchText->SetFocus();
		return;
	}

	lstSearchView->Items->Clear();

	szSQL.Format("select * from materialno where mn_name like '%%%s%%'",edtSearchText->Text.c_str());
	if(lstTreatType->ItemIndex==1)
		szSQL+=" and mn_code not in (select distinct ts_mncode from TreatStock)";
	else if(lstTreatType->ItemIndex==2)
		szSQL+=" and mn_code in (select distinct ts_mncode from TreatStock)";
	szSQL+=" and mn_code not in (select cc_ocode from codecheck)";
	szSQL+=" order by mn_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		pItem=lstSearchView->Items->Add();
		assert(pItem!=NULL);
		pItem->Caption=dm1->Query1->FieldByName("mn_code")->AsString;
		pItem->SubItems->Add(dm1->Query1->FieldByName("mn_name")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("mn_usage")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("mn_rem")->AsString);
                if(!dm1->Query1->FieldByName("mn_ducode")->IsNull)
                {
                        szSQL1.Format("select * from DicUnits where du_code='%s'",dm1->Query1->FieldByName("mn_ducode")->AsString);
                        RunSQL(dm1->Query2,szSQL1,true);
                        pItem->SubItems->Add(dm1->Query2->FieldByName("du_name")		->AsString);
                }
                else
	        pItem->SubItems->Add("");
		pItem->SubItems->Add(dm1->Query1->FieldByName("mn_date")->AsString);                
		dm1->Query1->Next();
	}
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseMTForm::btnPrefixQueryClick(TObject *Sender)
{
	CString szSQL,szSQL1;
	TListItem *pItem;

	edtPrefixID->Text=edtPrefixID->Text.Trim();
	if(edtPrefixID->Text.IsEmpty())
	{
		ShowMessage("请输入材料编号的前几位");
		if(edtPrefixID->CanFocus())	edtPrefixID->SetFocus();
		return;
	}
	edtPrefixID->Text=edtPrefixID->Text.UpperCase();

	szSQL.Format("select * from materialno,diccorp,diclargetype,dicmiddletype,dicsmalltype"
		" where cp_code=substring(mn_code,1,1)"
		" and lt_code=substring(mn_code,2,1)"
		" and mt_code=substring(mn_code,2,2)"
		" and st_code=substring(mn_code,2,4)"
		" and mn_code like '%s%%'",edtPrefixID->Text.c_str());
	if(lstTreatType->ItemIndex==1)
		szSQL+=" and mn_code not in (select distinct ts_mncode from TreatStock)";
	else if(lstTreatType->ItemIndex==2)
		szSQL+=" and mn_code in (select distinct ts_mncode from TreatStock)";
        szSQL+=" and mn_code not in (select cc_ocode from codecheck)";
	szSQL+=" order by mn_code";

	lstPrefixView->Items->Clear();
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		pItem=lstPrefixView->Items->Add();
		assert(pItem!=NULL);
		pItem->Caption=dm1->Query1->FieldByName("cp_name")->AsString;
		pItem->SubItems->Add(dm1->Query1->FieldByName("lt_name")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("mt_name")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("st_name")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("mn_code")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("mn_name")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("mn_usage")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("mn_rem")->AsString);
                if(!dm1->Query1->FieldByName("mn_ducode")->IsNull)
                {
                        szSQL1.Format("select * from DicUnits where du_code='%s'",dm1->Query1->FieldByName("mn_ducode")->AsString);
                        RunSQL(dm1->Query2,szSQL1,true);
                        pItem->SubItems->Add(dm1->Query2->FieldByName("du_name")		->AsString);
                }
                else
	        pItem->SubItems->Add("");
		pItem->SubItems->Add(dm1->Query1->FieldByName("mn_date")->AsString);
		dm1->Query1->Next();
	}
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseMTForm::lstPrefixViewSelectItem(
      TObject *Sender, TListItem *Item, bool Selected)
{
	TListItem *pItem;

	if(!Selected)	return;
	if((pItem=lstPrefixView->Selected)==NULL)	return;
  edtID->Text=pItem->SubItems->Strings[3];
  edtName->Text=pItem->SubItems->Strings[4];
  edtUnits->Text=pItem->SubItems->Strings[7];

  m_szMaterCode=edtID->Text;

//显示产品外观
        ADOT1->Filtered=false;
        ADOT1->Active=true;
        ADOT1->Filtered=false;
        ADOT1->Filter=AnsiString("ml_mncode='")+edtID->Text+"'";
        ADOT1->Filtered=true;
        ADOT1->FindFirst();
        ADOT1->Active=true;
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseMTForm::lstTreatTypeClick(TObject *Sender)
{
	if(ctlPage->ActivePage==ctlType)
		lstMinClick(Sender);
  else if(ctlPage->ActivePage==ctlPrefix)
		btnPrefixQueryClick(Sender);
  else if(ctlPage->ActivePage==ctlTree)
		lstTreeClick(Sender);
  else if(ctlPage->ActivePage==ctlSearch)
  {
		edtSearchText->Text=edtSearchText->Text.Trim();
		if(edtSearchText->Text.IsEmpty())	return;
		btnSearchClick(Sender);
  }
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseMTForm::lstViewDblClick(TObject *Sender)
{
	btnOKClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseMTForm::lstPrefixViewDblClick(TObject *Sender)
{
	btnOKClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseMTForm::lstTreeViewDblClick(TObject *Sender)
{
	btnOKClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseMTForm::lstSearchViewDblClick(TObject *Sender)
{
	btnOKClick(Sender);
}
//---------------------------------------------------------------------------


void __fastcall TAskPurchaseMTForm::btnRem2ExcelClick(TObject *Sender)
{
	Variant vExcel,vSheet;
  int nRow,i;

  try
  {
	  nRow=1;
		if(!OpenExcel("列表.xls",vExcel,vSheet))	return;
//		ListHead2Excel(lstView,vSheet,nRow++);
    InsertExcelItem(vSheet,nRow++,Memo1->Text.c_str(),NULL);
	}
	catch(...)
	{
	}
}
//---------------------------------------------------------------------------

#include "PrnMaterial.h"

void __fastcall TAskPurchaseMTForm::btnPrintRemClick(TObject *Sender)
{
	CString szSQL,szSQL1;
  TListItem *pItem;
  char strTemp[256];

  if((pItem=lstView->Selected)==NULL)
  {
  	ShowMessage("请选择一个材料编号");
    return;
  }
        szSQL1.Format("select * from materialno,DicUnits"
                " where mn_ducode=du_code"
                " and mn_code='%s%s-%s'",edtCorp->Text.c_str(),edtID0->Text.c_str(),pItem->Caption.c_str());
	RunSQL(dm1->Query2,szSQL1,true);
        if(dm1->Query2->Eof)
        {
	szSQL="select * from materialno,diccorp,diclargetype,dicmiddletype,dicsmalltype"
		" where substring(mn_code,1,1)=cp_code"
		" and substring(mn_code,2,1)=lt_code"
		" and substring(mn_code,2,2)=mt_code"
		" and substring(mn_code,2,4)=st_code";
        }
        else
        {
	szSQL="select * from materialno,diccorp,diclargetype,dicmiddletype,dicsmalltype,DicUnits"
		" where substring(mn_code,1,1)=cp_code"
		" and substring(mn_code,2,1)=lt_code"
		" and substring(mn_code,2,2)=mt_code"
		" and substring(mn_code,2,4)=st_code"
                " and mn_ducode=du_code";
        }


  sprintf(strTemp," and mn_code='%s%s-%s'",
  	edtCorp->Text.c_str(),
    edtID0->Text.c_str(),
    pItem->Caption.c_str());
  szSQL+=strTemp;


  TPrnMaterialForm *pPrn=new TPrnMaterialForm(this);
  assert(pPrn!=NULL);
	if(OpenQuery(dm1->sqlPrint,szSQL))
  {
	  pPrn->PrnView->PreviewModal();
  }
  delete pPrn;
}
//---------------------------------------------------------------------------








void MaterialEdit(LPCSTR lpszCorp,LPCSTR lpszID0,LPCSTR lpszID1,int nAuth);







void __fastcall TAskPurchaseMTForm::btnDetailClick(TObject *Sender)
{
	TListItem *pItem;

	if((pItem=lstSearchView->Selected)==NULL)
        {
                ShowMessage("情选择材料信息!");
                return;
        }

        CString szSQL;
        szSQL.Format("select substring(mn_code,1,1),substring(mn_code,2,4),substring(mn_code,7,18) from materialno where mn_name='%s'",pItem->SubItems->Strings[0]);
        RunSQL(dm1->Query1,szSQL,true);
        if(!dm1->Query1->Eof)
        {
                labCorp->Caption=dm1->Query1->Fields->Fields[0]->AsString;
                labID0->Caption=dm1->Query1->Fields->Fields[1]->AsString;
                labID1->Caption=dm1->Query1->Fields->Fields[2]->AsString;

                int nRight=GetOperatorRight(operatorcode.c_str(),"IDM_MNCODE");
                MaterialEdit(labCorp->Caption.c_str(),labID0->Caption.c_str(),labID1->Caption.c_str(),nRight);
        }
        else
                return;



//	MaterialEdit(pItem->Caption.c_str(),nRight);


/*
        CString szSQL;
        szSQL.Format("select substring(mn_code,1,1),substring(mn_code,2,4),substring(mn_code,7,18) from materialno where mn_name='%s'",pItem->SubItems->Strings[0]);
        RunSQL(dm1->Query1,szSQL,true);
        if(!dm1->Query1->Eof)
        {
                edtCorp->Text=dm1->Query1->Fields->Fields[0]->AsString;
                edtID0->Text=dm1->Query1->Fields->Fields[1]->AsString;
                edtID1->Text=dm1->Query1->Fields->Fields[2]->AsString;
                ShowMessage("dddd");
        }
*/        
}
//---------------------------------------------------------------------------

