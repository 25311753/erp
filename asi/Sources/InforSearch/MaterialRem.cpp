//---------------------------------------------------------------------------

#include <vcl.h>
#include <assert.h>
#include <stdio.h>

#pragma hdrstop

#include "DataModule.h"
#include "BaseCode.h"
#include "MaterialRem.h"
#include "LdyInterface.h"
#include "PrnRemMaterilno.h"


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TF_MaterialRem *F_MaterialRem;

void MaterialRem(int nAuth)
{
	if(nAuth==AUTH_NONE)	return;         //没有权限

	TF_MaterialRem *pForm;
  pForm=new TF_MaterialRem(Application);
  assert(pForm!=NULL);
  pForm->m_nAuthor=nAuth;
  pForm->ShowModal();
  delete pForm;
}
//---------------------------------------------------------------------------
__fastcall TF_MaterialRem::TF_MaterialRem(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TF_MaterialRem::FormShow(TObject *Sender)
{
	if(m_bTreeInitialed)	return;
	m_bTreeInitialed=true;
	CArray<BASE2COLDATA,BASE2COLDATA>lstLarge,lstMid,lstMin;
	BASE2COLDATA rwData;

  TTreeNode *pNode,*pLarge,*pMid,*pMin;
	CString szSQL,*pID;
	int i,j;
	char strID[80],strLarge[80],strMid[80];

/*	szSQL="select * from diccorp order by cp_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		m_lstTreeCorpID.Add(dm1->Query1->FieldByName("cp_code")->AsString.c_str());
	        lstTreeCorp->Items->Add(dm1->Query1->FieldByName("cp_name")->AsString);
		dm1->Query1->Next();
	}
	lstTreeCorp->ItemIndex=0;
*/
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

	szSQL="select * from dicsmalltype"                                      //专业设备不用展开到小类目录
		" where st_code in"
		"("
		"select distinct substring(mn_code,2,4) from materialno"
		")"
                " and st_code not like '0%'"
		" order by st_code";

/*	szSQL="select * from dicsmalltype"
		" where st_code in"
		"("
		"select distinct substring(mn_code,2,4) from materialno"
		")"
		" order by st_code";
*/
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

        Label4->Caption="";
        Label5->Caption="";
        Label13->Caption="";
        Label14->Caption="";
        Memo1->ReadOnly=true;
        Memo2->ReadOnly=true;
        Memo3->ReadOnly=true;
        Memo4->ReadOnly=true;        

        nodeselected=false;     //初始化　nodec
	m_enState=EN_STATE_IDLE;
        ResetCtrl();

}
//---------------------------------------------------------------------------


void __fastcall TF_MaterialRem::lstTreeClick(TObject *Sender)
{
	TTreeNode *pNode=lstTree->Selected;
  if(pNode==NULL)	return;


//        ShowMessage(lstTree->Selected->Text);
        char strID[80];
        CString szSQL1,szSQL2,szSQL3,szSQL4;

                szSQL3.Format("select mt_code from dicmiddletype where substring(mt_code,1,1)='0' and mt_name='%s'",lstTree->Selected->Text);
                szSQL1.Format("select st_code from dicsmalltype where substring(st_code,1,1)!='0' and st_name='%s'",lstTree->Selected->Text);

        RunSQL(dm1->Query3,szSQL3,true);
        RunSQL(dm1->Query1,szSQL1,true);
        if(!dm1->Query1->Eof)
        {
          Label4->Caption=dm1->Query1->FieldByName("st_code")->AsString;
          Label5->Caption=lstTree->Selected->Text;
          nodeselected=true;
        }
        else
        {//无点选专业设备外的最小分类
                if(!dm1->Query3->Eof)
                {//点选了专业类的中类，视为合法
                        Label4->Caption=dm1->Query3->FieldByName("mt_code")->AsString;
                        Label5->Caption=lstTree->Selected->Text;
                        nodeselected=true;
                }
                else
                {
                        Label4->Caption="";
                        Label5->Caption="";
                        nodeselected=false;
                }
        }
                szSQL4.Format("select * from remmaterialno where rst_code=(select mt_code from dicmiddletype where substring(mt_code,1,1)='0' and mt_name='%s')",lstTree->Selected->Text);
                szSQL2.Format("select * from remmaterialno where rst_code=(select st_code from dicsmalltype where substring(st_code,1,1)!='0' and st_name='%s')",lstTree->Selected->Text);

        RunSQL(dm1->Query4,szSQL4,true);
        RunSQL(dm1->Query2,szSQL2,true);


        if(!dm1->Query2->Eof)
        {
                 Memo1->Text=dm1->Query2->FieldByName("rst_rem")->AsString;
                 Memo2->Text=dm1->Query2->FieldByName("rst_rem1")->AsString;
                 Memo3->Text=dm1->Query2->FieldByName("rst_rem2")->AsString;
                 Memo4->Text=dm1->Query2->FieldByName("rst_rem3")->AsString;
        }
        else
        {//无点选专业设备外的最小分类
                if(!dm1->Query4->Eof)
                {//点选了专业类的中类，视为合法
                         Memo1->Text=dm1->Query4->FieldByName("rst_rem")->AsString;
                         Memo2->Text=dm1->Query4->FieldByName("rst_rem1")->AsString;
                         Memo3->Text=dm1->Query4->FieldByName("rst_rem2")->AsString;
                         Memo4->Text=dm1->Query4->FieldByName("rst_rem3")->AsString;
                }
                else
                {
                         Memo1->Text="";
                         Memo2->Text="";
                         Memo3->Text="";
                         Memo4->Text="";
                }
        }




}
//---------------------------------------------------------------------------

void __fastcall TF_MaterialRem::btnExitClick(TObject *Sender)
{
	int nState=m_enState;
	if(m_enState==EN_STATE_IDLE)
		Close();
	else
	{
		m_enState=EN_STATE_IDLE;
		ResetCtrl();
                lstTree->Enabled=true;
                Memo1->ReadOnly=true;
                Memo2->ReadOnly=true;
                Memo3->ReadOnly=true;
                Memo4->ReadOnly=true;

	}
}
//---------------------------------------------------------------------------



void __fastcall TF_MaterialRem::btnOKClick(TObject *Sender)
{
        char strTemp;
        CString szSQL,szSQL2,szSQL3;

        szSQL3.Format("select * from dicmiddletype where substring(mt_code,1,1)='0' and mt_name='%s'",lstTree->Selected->Text);
        RunSQL(dm1->Query3,szSQL3,true);

        szSQL2.Format("select * from dicsmalltype where substring(st_code,1,1)!='0' and st_name='%s'",lstTree->Selected->Text);
        RunSQL(dm1->Query2,szSQL2,true);
        if(!dm1->Query2->Eof)
        {//非专业设备
                szSQL.Format("update remmaterialno set rst_rem='%s',rst_rem1='%s',rst_rem2='%s',rst_rem3='%s'  where rst_code=(select st_code from dicsmalltype where st_name='%s')",Memo1->Text,Memo2->Text,Memo3->Text,Memo4->Text,lstTree->Selected->Text);
                RunSQL(dm1->Query1,szSQL);
        }
        else
        {
                if(!dm1->Query3->Eof)
                {
                        szSQL.Format("update remmaterialno set rst_rem='%s',rst_rem1='%s',rst_rem2='%s',rst_rem3='%s'  where rst_code=(select mt_code from dicmiddletype where mt_name='%s')",Memo1->Text,Memo2->Text,Memo3->Text,Memo4->Text,lstTree->Selected->Text);
                        RunSQL(dm1->Query1,szSQL);
                }

        }
//        szSQL.Format("update remmaterialno set rst_rem='%s',rst_rem1='%s',rst_rem2='%s',rst_rem3='%s'  where rst_code=(select st_code from dicsmalltype where st_name='%s')",Memo1->Text,Memo2->Text,Memo3->Text,Memo4->Text,lstTree->Selected->Text);
//        RunSQL(dm1->Query1,szSQL);

        lstTree->Enabled=true;
        Memo1->ReadOnly=true;
        Memo2->ReadOnly=true;
        Memo3->ReadOnly=true;
        Memo4->ReadOnly=true;
        m_enState=EN_STATE_IDLE;
        ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TF_MaterialRem::btnEditClick(TObject *Sender)
{
        if(!nodeselected)
        {
                ShowMessage("请选择材料分类！");
                return;
        }

        lstTree->Enabled=false;
        Memo1->ReadOnly=false;
        Memo2->ReadOnly=false;
        Memo3->ReadOnly=false;
        Memo4->ReadOnly=false;        

	m_enState=EN_STATE_EDIT;
        ResetCtrl();
	if(Memo1->CanFocus())	Memo1->SetFocus();

}
//---------------------------------------------------------------------------

void TF_MaterialRem::ResetCtrl()
{
	bool bIdle,bAuth;

	bIdle = m_enState==EN_STATE_IDLE;
	bAuth = m_nAuthor==AUTH_FULL;

	btnEdit	->Enabled = bIdle && bAuth;
//	btnDel	->Enabled = bIdle && bAuth;
        btnPrint123->Enabled=bIdle;
        btnPrint4->Enabled=bIdle;
	btnOK	->Enabled = !bIdle;
	btnExit->Caption = bIdle ? "退    出" : "放    弃";
}
void __fastcall TF_MaterialRem::btnPrint123Click(TObject *Sender)
{
        if(!nodeselected)
        {
                ShowMessage("请选择材料分类！");
                return;
        }
        TPrnRemMaterialno *pPrn;
	pPrn=new TPrnRemMaterialno(this);
	assert(pPrn!=NULL);

        pPrn->QRLabel2->Caption=Label4->Caption;
        pPrn->QRLabel3->Caption=Label5->Caption;
        pPrn->QRMemo1->Lines=Memo1->Lines;
        pPrn->QRMemo2->Lines=Memo2->Lines;
        pPrn->QRMemo3->Lines=Memo3->Lines;
//        pPrn->QRMemo4->Lines=Memo4->Lines;
	pPrn->QR1->PreviewModal();
	delete pPrn;
}
//---------------------------------------------------------------------------

void __fastcall TF_MaterialRem::btnPrint4Click(TObject *Sender)
{
        if(!nodeselected)
        {
                ShowMessage("请选择材料分类！");
                return;
        }
        TPrnRemMaterialno *pPrn;
	pPrn=new TPrnRemMaterialno(this);
	assert(pPrn!=NULL);
//        pPrn->QRLabel6->Caption="附表资料：";
//        pPrn->QRShape2->Height=0;
        pPrn->DetailBand1->Enabled=false;
        pPrn->QRSubDetail3->Enabled=false;
        pPrn->QRLabel7->Caption="其它附表：";
        pPrn->QRLabel2->Caption=Label4->Caption;
        pPrn->QRLabel3->Caption=Label5->Caption;
        pPrn->QRMemo2->Lines=Memo4->Lines;
	pPrn->QR1->PreviewModal();
	delete pPrn;
}
//---------------------------------------------------------------------------



void __fastcall TF_MaterialRem::btnSearchClick(TObject *Sender)
{
	CString szSQL;
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

	szSQL.Format("select * from dicsmalltype where st_name like '%%%s%%'",edtSearchText->Text.c_str());
	szSQL+=" order by st_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		pItem=lstSearchView->Items->Add();
		assert(pItem!=NULL);
		pItem->Caption=dm1->Query1->FieldByName("st_code")->AsString;
		pItem->SubItems->Add(dm1->Query1->FieldByName("st_name")->AsString);
		dm1->Query1->Next();
	}
}
//---------------------------------------------------------------------------


void __fastcall TF_MaterialRem::lstSearchViewSelectItem(TObject *Sender,
      TListItem *Item, bool Selected)
{
	TListItem *pItem;
	if(!Selected)	return;

	if((pItem=lstSearchView->Selected)==NULL)	return;
        Label13->Caption=pItem->Caption;
        Label14->Caption=pItem->SubItems->Strings[0];
}
//---------------------------------------------------------------------------


