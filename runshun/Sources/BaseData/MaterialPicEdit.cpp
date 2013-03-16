//---------------------------------------------------------------------------

#include <vcl.h>
#include <assert.h>
#pragma hdrstop


#include "DataModule.h"
#include "BaseCode.h"
#include "MaterialPicEdit.h"
#include "TConst.h"
#include "LdyInterface.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMnPictureForm *MnPictureForm;
//---------------------------------------------------------------------------
void MaterialPicture(int nAuth)
{
	if(nAuth==AUTH_NONE)	return;         //没有权限

	TMnPictureForm *pForm;
  pForm=new TMnPictureForm(Application);
  assert(pForm!=NULL);
  pForm->m_nAuthor=nAuth;
  pForm->ShowModal();
  delete pForm;
}

__fastcall TMnPictureForm::TMnPictureForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TMnPictureForm::FormShow(TObject *Sender)
{
	bool bIdle,bAuth;
        ADOT1->Filtered=false;
        ADOT1->Active=true;
//        btnOpenDB->Enabled=false;        
	m_enState=EN_STATE_IDLE;
	ResetCtrl();
}
//---------------------------------------------------------------------------
void TMnPictureForm::ResetCtrl()
{
	bool bIdle,bAuth;
	bIdle = m_enState==EN_STATE_IDLE;
	bAuth = m_nAuthor==AUTH_FULL;
        DBNgt->Enabled=true;
        if(bIdle)
        {//只读权限
                DBNgt->VisibleButtons=TButtonSet()<<nbFirst<<nbPrior<<nbNext<<nbLast;
        }
        if(bIdle && bAuth)
        {//读写权限
                DBNgt->VisibleButtons=TButtonSet()<<nbFirst<<nbPrior<<nbNext<<nbLast<<nbDelete<<nbEdit<<nbPost<<nbCancel;
        }
	btnQuery->Enabled = bIdle;
	btnNew	->Enabled = bIdle && bAuth;
//	btnEdit	->Enabled = bIdle && bAuth;
//	btnMove	->Enabled = bIdle && bAuth;
	btnOK	->Enabled = !bIdle;
	btnExit->Caption = bIdle ? "退    出" : "放    弃";
                
}
//---------------------------------------------------------------------------
void __fastcall TMnPictureForm::btnExitClick(TObject *Sender)
{
	int nState=m_enState;
//        btnOpenDB->Enabled=true;
        btnQueryMT->Enabled=false;
        ADOT1->Active=false;
        edtMater->Text="";
        edtMnname->Text="";

	if(m_enState==EN_STATE_IDLE && m_enState!=EN_STATE_QUERY)
        {
                Close();
        }
        else
        {
                ADOT1->Filtered=true;
                ADOT1->Active=true;
                ADOT1->Filtered=false;
                m_enState=EN_STATE_IDLE;
                ResetCtrl();
        }
}
//---------------------------------------------------------------------------

void __fastcall TMnPictureForm::btnOpenDBClick(TObject *Sender)
{
        ADOT1->Filtered=false;
        ADOT1->Active=true;
//        btnOpenDB->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TMnPictureForm::btnCloseDBClick(TObject *Sender)
{
        ADOT1->Active=false;          
}
//---------------------------------------------------------------------------

void __fastcall TMnPictureForm::ADOT1BeforePost(TDataSet *DataSet)
{
        if(PicDlg->Execute())
                ((TBlobField*)ADOT1->FieldByName("ml_image"))->LoadFromFile(PicDlg->FileName);
}
//---------------------------------------------------------------------------






#include "AskPurchaseMT.h"
void __fastcall TMnPictureForm::btnQueryMTClick(TObject *Sender)
{
	char strName[256];
	CString szSQL;
	TAskPurchaseMTForm *pMT;
	pMT=new TAskPurchaseMTForm(this);
	assert(pMT!=NULL);
	pMT->m_szMaterCode=edtMater->Text;
	if(pMT->ShowModal()==mrOk)
	{
		edtMater->Text=pMT->m_szMaterCode;
        	edtMater->Text=edtMater->Text.Trim();
	        strName[0]='\0';
        	if(!edtMater->Text.IsEmpty())
	        {
        		szSQL.Format("select * from materialno where mn_code='%s'",edtMater->Text.c_str());
	        	RunSQL(dm1->Query1,szSQL,true);
		        if(!dm1->Query1->Eof)
        		{
	        		strcpy(strName,dm1->Query1->FieldByName("mn_name")->AsString.c_str());
		        }
        	}
	        edtMnname->Text=strName;
	}
	delete pMT;
  if(edtMater->CanFocus())	edtMater->SetFocus();
}
//---------------------------------------------------------------------------


void __fastcall TMnPictureForm::btnOKClick(TObject *Sender)
{
        bool bIdle;

        int nState;

        nState=m_enState;

        if(edtMater->Text.IsEmpty())
        {
                ShowMessage("请输入材料编号");
                return;
        }

  if(m_enState==EN_STATE_QUERY)
  {
        ADOQ1->Active=false;
        ADOQ1->SQL->Clear();
        String strTemp;
        strTemp="select * from materiallook where ml_mncode='"+edtMater->Text+"'";
        ADOQ1->SQL->Add(strTemp);
        ADOQ1->Open();
        if(ADOQ1->RecordCount==0)
        {
                ShowMessage("没有该材料的图片资料");
                return;
        }

        ADOT1->Filtered=true;
        ADOT1->Active=true;
        ADOT1->Filtered=false;
//        ADOT1->Filter="t_id="+QuotedStr("+edtMater->Text+")";
        ADOT1->Filter=AnsiString("ml_mncode='")+edtMater->Text+"'";
        ADOT1->Filtered=true;
        ADOT1->FindFirst();
        ADOT1->Active=true;

        DBNgt->Enabled=true;
        btnQueryMT->Enabled=false;
        btnOK->Enabled=false;

        btnExit->Caption="返　回";
  }
  if(m_enState==EN_STATE_NEW)
  {
        ADOQ1->Active=false;
        ADOQ1->SQL->Clear();
        String strTemp;
        strTemp="select * from materiallook where ml_mncode='"+edtMater->Text+"'";
        ADOQ1->SQL->Add(strTemp);
        ADOQ1->Open();
        if(ADOQ1->RecordCount!=0)
        {
                ADOT1->Filtered=true;
                ADOT1->Filtered=false;
                ADOT1->Filter=AnsiString("ml_mncode='")+edtMater->Text+"'";
                ADOT1->Filtered=true;
                ADOT1->FindFirst();
                ShowMessage("该材料编号已有图片资料");
                return;
        }

        ADOT1->Active=true;
        ADOC1->Connected=true;
        ADOT1->Append();
        ADOT1->FieldByName("ml_mncode")->AsString=edtMater->Text;
        ADOT1->FieldByName("ml_mnname")->AsString=edtMnname->Text;

        ADOT1->Post();

        ADOT1->Filtered=true;
        ADOT1->Filtered=false;
        ADOT1->Filter=AnsiString("ml_mncode='")+edtMater->Text+"'";
        ADOT1->Filtered=true;
        ADOT1->FindFirst();
        DBNgt->Enabled=true;
        btnOK->Enabled=false;
        btnExit->Caption="返　回";
  }

/*        TLocateOptions Opts;
        Opts.Clear();
        Opts<<loPartialKey;
        Variant locvalues[1];
        locvalues[0]=Variant("A081L-00");//edtMater->Text;
        ADOT1->Locate("ml_mncode",VarArrayOf(locvalues,0),Opts);
*/
//用於返回所选编号
//            edtMater->Text=ADOT1->FieldByName("ml_mncode")->AsString;

}
//---------------------------------------------------------------------------


void __fastcall TMnPictureForm::btnQueryClick(TObject *Sender)
{
        btnQueryMT->Enabled=true;
//	m_szActiveID="";

//        btnOpenDB->Enabled=false;
        btnNew->Enabled=false;
//        btnEdit->Enabled=false;
//        btnMove->Enabled=false;
        btnOK->Enabled=true;
	btnExit->Caption ="放    弃";
        btnQuery->Enabled=false;
        m_enState=EN_STATE_QUERY;
        DBNgt->Enabled=false;

}
//---------------------------------------------------------------------------


void __fastcall TMnPictureForm::btnNewClick(TObject *Sender)
{
        btnQueryMT->Enabled=true;
	m_enState=EN_STATE_NEW;
//        btnOpenDB->Enabled=false;
        btnQuery->Enabled=false;
//        btnEdit->Enabled=false;
//        btnMove->Enabled=false;
        btnOK->Enabled=true;
	btnExit->Caption ="放    弃";
        ResetCtrl();
        DBNgt->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TMnPictureForm::btnEditClick(TObject *Sender)
{
        m_enState=EN_STATE_EDIT;
//        btnOpenDB->Enabled=false;
        btnQuery->Enabled=false;
//        btnEdit->Enabled=false;
//        btnMove->Enabled=false;
        btnOK->Enabled=true;
	btnExit->Caption ="放    弃";
        ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TMnPictureForm::btnMoveClick(TObject *Sender)
{
        m_enState=EN_STATE_Move;
//        btnOpenDB->Enabled=false;
        btnQuery->Enabled=false;
//        btnEdit->Enabled=false;
//        btnMove->Enabled=false;
        btnOK->Enabled=true;
	btnExit->Caption ="放    弃";
        ResetCtrl();
}
//---------------------------------------------------------------------------
/* 图片转换

//String openname,extension;
#include <jpeg.hpp>
void __fastcall TMnPictureForm::btnOpenPicClick(TObject *Sender)
{
        if(PicDlgJ2B->Execute())
        {
                openname=PicDlgJ2B->FileName;
                extension=openname.SubString(openname.Length() -2,3);
                Image1->Picture->LoadFromFile(openname);
        }
}
//---------------------------------------------------------------------------

void __fastcall TMnPictureForm::btnSavePClick(TObject *Sender)
{
        Graphics::TBitmap *bitmap1;
        bitmap1=new Graphics::TBitmap;
        TJPEGImage *jpg1;
        jpg1=new TJPEGImage;
        if(PicSav->Execute())
        {
                String savename=PicSav->FileName;
                String exten=savename.SubString(savename.Length() -2,3);
                if((UpperCase(exten)=="BMP")&&(UpperCase(extension)=="JPEG"||UpperCase(extension)=="JPG"))
                {
                        bitmap1->Assign(Image1->Picture->Graphic);
                        bitmap1->SaveToFile(savename);
                }
        }
}
*/
//---------------------------------------------------------------------------





