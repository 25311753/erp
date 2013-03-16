//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "DataModule.h"
#include "BaseCode.h"
#include "ClassRight.h"
#include "LdyInterface.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TClassRightForm *ClassRightForm;

typedef struct
{
	int nClass;
  char strMenu[80];
  int nRight;
} CLASSRIGHT;

static CArray<CLASSRIGHT,CLASSRIGHT> gtheClassRight;

//-------------------------------------------------------------------
//取得操作等级的权限
int GetClassRight(int nClass,LPCSTR lpszMenu)
{
	char strSQL[1024];

	if(gtheClassRight.GetSize()==0)
  {
  	CLASSRIGHT right;
		RunSQL("select * from ClassRight",true);
    while(!dm1->Query1->Eof)
    {
    	right.nClass=dm1->Query1->FieldByName("cr_class")->AsInteger;
      strcpy(right.strMenu,dm1->Query1->FieldByName("cr_menu")->AsString.c_str());
      right.nRight=dm1->Query1->FieldByName("cr_right")->AsInteger;
      gtheClassRight.Add(right);

      dm1->Query1->Next();
    }
  }
  int i;
  for(i=0;i<gtheClassRight.GetSize();i++)
  {
  	if(gtheClassRight[i].nClass==nClass && strcmp(gtheClassRight[i].strMenu,lpszMenu)==0)
    	return gtheClassRight[i].nRight;
  }
  return NULL_RIGHT;
/*
	sprintf(strSQL,"select * from operator,ClassRight"
		" where op_class*=cr_class"
		" and op_code='%s' and cr_menu='%s'",lpszOper,lpszMenu);
  RunSQL(strSQL,true);
  if(dm1->Query1->Eof)	return NULL_RIGHT;
  else if(dm1->Query1->FieldByName("cr_right")->IsNull)	return NULL_RIGHT;
  return dm1->Query1->FieldByName("cr_right")->AsInteger;
*/
}

//-------------------------------------------------------------------
//取得操作员的权限
int GetOperatorRight(LPCSTR	lpszOper,LPCSTR lpszMenu)
{
	char strSQL[1024];

  int nClass;
  sprintf(strSQL,"select * from operator where op_code='%s'",lpszOper);
  RunSQL(strSQL,true);
  if(dm1->Query1->Eof)	return NULL_RIGHT;
  nClass=dm1->Query1->FieldByName("op_class")->AsInteger;
  return GetClassRight(nClass,lpszMenu);
}

// ==================================================================
//等级权限设置接口，文件ClassRight.*
void ClassRight(int nAuth)
{
	if(nAuth==AUTH_NONE)	return;

  TClassRightForm *pForm;
	try
	{
  	pForm=new TClassRightForm(Application);
  }
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
    return;
	}
//  pForm->m_nAuthor=nAuth;
  pForm->ShowModal();
  delete pForm;
}
// ==================================================================

//---------------------------------------------------------------------------
__fastcall TClassRightForm::TClassRightForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TClassRightForm::FormShow(TObject *Sender)
{
	CString szSQL;

  szSQL="select * from operclass order by oc_code";
	RunSQL(szSQL,true);
  while(!dm1->Query1->Eof)
  {
  	m_lstClassID.Add(dm1->Query1->FieldByName("oc_code")->AsInteger);
  	lstClass->Items->Add(dm1->Query1->FieldByName("oc_name")->AsString);
  	dm1->Query1->Next();
  }

  szSQL="select distinct mi_grpidx,mi_grpname from MenuInform order by mi_grpidx";
  RunSQL(szSQL,true);
  while(!dm1->Query1->Eof)
  {
  	lstGrpName->Items->Add(dm1->Query1->FieldByName("mi_grpname")->AsString);
  	dm1->Query1->Next();
  }

  lstClass->ItemIndex=0;
  lstGrpName->ItemIndex=0;
	ResetRightInf();
	ResetCtrl();
}
//---------------------------------------------------------------------------
void __fastcall TClassRightForm::lstGrpNameClick(TObject *Sender)
{
	ResetRightInf();
	ResetCtrl();
}
//---------------------------------------------------------------------------

void TClassRightForm::ResetRightInf()
{
	int nIdx;
  CString szSQL;
  TListItem *pItem;

  lstData->Items->Clear();
  m_lstMenuID.RemoveAll();
  if((nIdx=lstGrpName->ItemIndex)==-1)	return;

	szSQL.Format("select * from MenuInform,ClassRight"
		" where mi_menu*=cr_menu"
		" and cr_class=%d"
		" and  mi_grpname='%s'"
		" order by mi_menu",
    m_lstClassID[lstClass->ItemIndex],
    lstGrpName->Items->Strings[nIdx].c_str());

//  szSQL.Format("select * from MenuInform where mi_grpname='%s' order by mi_menu",
//		lstGrpName->Items->Strings[nIdx].c_str());
  RunSQL(szSQL,true);
	while(!dm1->Query1->Eof)
  {
  	m_lstMenuID.Add(dm1->Query1->FieldByName("mi_menu")->AsString.c_str());
  	pItem=lstData->Items->Add();
    pItem->Caption=dm1->Query1->FieldByName("mi_name")->AsString;
    if(dm1->Query1->FieldByName("cr_right")->IsNull)
    	pItem->SubItems->Add(IntToStr(NULL_RIGHT));
    else
    	pItem->SubItems->Add(IntToStr(dm1->Query1->FieldByName("cr_right")->AsInteger));

  	dm1->Query1->Next();
  }
}

void __fastcall TClassRightForm::btnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TClassRightForm::lstClassClick(TObject *Sender)
{
	ResetRightInf();
	ResetCtrl();
}
//---------------------------------------------------------------------------
void __fastcall TClassRightForm::lstDataClick(TObject *Sender)
{
	ResetCtrl();
}
//---------------------------------------------------------------------------

void TClassRightForm::ResetCtrl()
{
  bool bSelected,bAdmin;
	bAdmin = lstClass->Text=="总管理员";
  bSelected=lstData->Selected!=NULL;
  btnDeny->Enabled=bSelected && !bAdmin;
  btnRead->Enabled=bSelected && !bAdmin;

  btnPriceRead->Enabled=bSelected;
  btnFull->Enabled=bSelected;

	btnAllDeny->Enabled=!bAdmin;
	btnAllRead->Enabled=!bAdmin;
//	btnAllFull->Enabled=!bAdmin;
}

bool TClassRightForm::SetRight(int nClass,LPCSTR lpszMenu,int nRight)
{
	char strSQL[1024];
  sprintf(strSQL,"select * from ClassRight where cr_class=%d and cr_menu='%s'",
		nClass,lpszMenu);
  RunSQL(strSQL,true);
  if(dm1->Query1->Eof)
	{ //还没有该条权限记录
  	sprintf(strSQL,"insert ClassRight values(%d,'%s',%d)",
    	nClass,lpszMenu,nRight);
  }
  else
  {
  	sprintf(strSQL,"update ClassRight set cr_right=%d where cr_class=%d and cr_menu='%s'",
    	nRight,nClass,lpszMenu);
  }
  return RunSQL(strSQL);
}

bool TClassRightForm::SetRight(TListItem *pItem,int nRight)
{
	int nIdx;

  if(pItem==NULL)	return false;
  nIdx=lstData->Items->IndexOf(pItem);
  if(nIdx<0 || nIdx>=m_lstMenuID.GetSize())	return false;
	if(SetRight(m_lstClassID[lstClass->ItemIndex],m_lstMenuID[nIdx],nRight))
	{
		pItem->SubItems->Strings[0]=IntToStr(nRight);
  	return true;
  }
  return false;
}

void __fastcall TClassRightForm::btnDenyClick(TObject *Sender)
{
  SetRight(lstData->Selected,0);
}
//---------------------------------------------------------------------------

void __fastcall TClassRightForm::btnReadClick(TObject *Sender)
{
  SetRight(lstData->Selected,1);
}
//---------------------------------------------------------------------------

void __fastcall TClassRightForm::btnFullClick(TObject *Sender)
{
  SetRight(lstData->Selected,2);
}
//---------------------------------------------------------------------------

void __fastcall TClassRightForm::btnAllDenyClick(TObject *Sender)
{
	int i;
  for(i=0;i<lstData->Items->Count;i++)
  	SetRight(lstData->Items->Item[i],0);
}
//---------------------------------------------------------------------------

void __fastcall TClassRightForm::btnAllReadClick(TObject *Sender)
{
	int i;
  for(i=0;i<lstData->Items->Count;i++)
  	SetRight(lstData->Items->Item[i],1);
}
//---------------------------------------------------------------------------

void __fastcall TClassRightForm::btnAllFullClick(TObject *Sender)
{
	int i;
  for(i=0;i<lstData->Items->Count;i++)
  	SetRight(lstData->Items->Item[i],2);
}
//---------------------------------------------------------------------------

void __fastcall TClassRightForm::btnPriceReadClick(TObject *Sender)
{
  SetRight(lstData->Selected,3);
}
//---------------------------------------------------------------------------



