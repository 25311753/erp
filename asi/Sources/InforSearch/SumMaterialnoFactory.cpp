//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#pragma hdrstop

#include "DataModule.h"
#include "BaseCode.h"
#include "TConst.h"
#include "SumMaterialnoFactory.h"
#include "LdyInterface.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSumMnFactForm *SumMnFactForm;
//---------------------------------------------------------------------------
void SumMnFact(int nAuth)
{
	if(nAuth==AUTH_NONE)	return;         //没有权限

	TSumMnFactForm *pForm;
  pForm=new TSumMnFactForm(Application);
  assert(pForm!=NULL);
  pForm->m_nAuthor=nAuth;
  pForm->ShowModal();
  delete pForm;
}
void TSumMnFactForm::SetDefault()
{
        edtMater->Text="";
        edtMnname->Text="";
        edtStanderN->Text="";
        edtStanderP->Text="";
        edtSP->Text="";
        edtSN->Text="";
        lstSpeerFact->Text="";
        lstSpeerFact->ItemIndex=-1;
        RadioGroup1->ItemIndex=-1;
        RadioGroup2->ItemIndex=-1;
        RadioGroup3->ItemIndex=-1;
        ProgressBar1->Visible=false;
}
void TSumMnFactForm::EnableEdit()
{
        edtMater->Enabled=true;
        edtMnname->Enabled=true;
        edtStanderN->Enabled=true;
        edtStanderP->Enabled=true;
//        edtSP->Enabled=true;
//        edtSN->Enabled=true;
        lstSpeerFact->Enabled=true;
}
void TSumMnFactForm::EnableEditR()
{

}
void TSumMnFactForm::DisableEdit()
{
        edtMater->Enabled=false;
        edtMnname->Enabled=false;
        edtStanderN->Enabled=false;
        edtStanderP->Enabled=false;
        lstSpeerFact->Enabled=false;
        edtSN->Enabled=false;
        edtSP->Enabled=false;
}

__fastcall TSumMnFactForm::TSumMnFactForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
#include "AskPurchaseMT.h"
void __fastcall TSumMnFactForm::btnQueryMTClick(TObject *Sender)
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
  if(edtMater->CanFocus())	edtMater->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TSumMnFactForm::btnQuitClick(TObject *Sender)
{
        Close();        
}
//---------------------------------------------------------------------------
#include "FactorySearch.h"
void __fastcall TSumMnFactForm::btnSpeerFactSearchClick(TObject *Sender)
{
	TFactorySearchForm *pForm;
  int i;

  pForm=new TFactorySearchForm(this);
  assert(pForm!=NULL);
  if(pForm->ShowModal()==mrOk && !pForm->m_szID.IsEmpty())
  {
  	for(i=0;i<m_lstSpeerFactID.GetSize();i++)
    {
    	if(m_lstSpeerFactID[i]==pForm->m_szID)
      {
      	lstSpeerFact->ItemIndex=i;
        break;
      }
    }
  }
  delete pForm;
}
//---------------------------------------------------------------------------
void __fastcall TSumMnFactForm::FormShow(TObject *Sender)
{
	CString szSQL;
        szSQL="select * from Manufactur order by mf_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		m_lstSpeerFactID.Add(dm1->Query1->FieldByName("mf_code")->AsString.c_str());
		lstSpeerFact->Items->Add(dm1->Query1->FieldByName("mf_shortname")->AsString);
		dm1->Query1->Next();
	}

 if(g_theOperator.op_cpcode[0]=='A')
      { //若用户为行政中心，自动寻找行政中心的采购部门与采购经办
                     szSQL="select * from StockDepart where sd_code='X' or sd_code='11' order by sd_code DESC";
                     RunSQL(dm1->Query1,szSQL,true);
                     while(!dm1->Query1->Eof)
                       {
                         m_lstStockDepartID.Add(dm1->Query1->FieldByName("sd_code")->AsString.c_str());
                         lstStockDepart->Items->Add(dm1->Query1->FieldByName("sd_name")->AsString);
                         dm1->Query1->Next();
                        }
                    lstStockDepart->ItemIndex=0;
      }

 if(g_theOperator.op_cpcode[0]=='D')
      { //若用户为宏铭公司，自动寻找宏铭的采购部门与采购经办
              szSQL="select * from StockDepart where sd_code='Y' or sd_code='1' order by sd_code";
                     RunSQL(dm1->Query1,szSQL,true);
                     while(!dm1->Query1->Eof)
                       {
                         m_lstStockDepartID.Add(dm1->Query1->FieldByName("sd_code")->AsString.c_str());
                         lstStockDepart->Items->Add(dm1->Query1->FieldByName("sd_name")->AsString);
                         dm1->Query1->Next();
                        }
                    lstStockDepart->ItemIndex=0;
      }
 if(g_theOperator.op_cpcode[0]=='B')
      { //若用户为宏仁公司，自动寻找宏仁的采购部门
              szSQL="select * from StockDepart where sd_code='9' order by sd_code";
                     RunSQL(dm1->Query1,szSQL,true);
                     while(!dm1->Query1->Eof)
                       {
                         m_lstStockDepartID.Add(dm1->Query1->FieldByName("sd_code")->AsString.c_str());
                         lstStockDepart->Items->Add(dm1->Query1->FieldByName("sd_name")->AsString);
                         dm1->Query1->Next();
                        }
                    lstStockDepart->ItemIndex=0;
      }
 if(g_theOperator.op_cpcode[0]=='C')
      { //若用户为宏育公司，自动寻找宏育的采购部门
              szSQL="select * from StockDepart where sd_code='4' or sd_code='5' order by sd_code";
                     RunSQL(dm1->Query1,szSQL,true);
                     while(!dm1->Query1->Eof)
                       {
                         m_lstStockDepartID.Add(dm1->Query1->FieldByName("sd_code")->AsString.c_str());
                         lstStockDepart->Items->Add(dm1->Query1->FieldByName("sd_name")->AsString);
                         dm1->Query1->Next();
                        }
                    lstStockDepart->ItemIndex=0;
      }
 if(g_theOperator.op_cpcode[0]=='E')
      { //若用户为宏信公司，自动寻找宏信的采购部门
              szSQL="select * from StockDepart where sd_code='2' or sd_code='3' order by sd_code";
                     RunSQL(dm1->Query1,szSQL,true);
                     while(!dm1->Query1->Eof)
                       {
                         m_lstStockDepartID.Add(dm1->Query1->FieldByName("sd_code")->AsString.c_str());
                         lstStockDepart->Items->Add(dm1->Query1->FieldByName("sd_name")->AsString);
                         dm1->Query1->Next();
                        }
                    lstStockDepart->ItemIndex=0;
      }
if(g_theOperator.op_cpcode[0]=='F')
      { //若用户为宏焕公司，自动寻找宏焕的采购部门
              szSQL="select * from StockDepart where sd_code='6' or sd_code='7' or sd_code='8' order by sd_code";
                     RunSQL(dm1->Query1,szSQL,true);
                     while(!dm1->Query1->Eof)
                       {
                         m_lstStockDepartID.Add(dm1->Query1->FieldByName("sd_code")->AsString.c_str());
                         lstStockDepart->Items->Add(dm1->Query1->FieldByName("sd_name")->AsString);
                         dm1->Query1->Next();
                        }
                    lstStockDepart->ItemIndex=0;
      }
if(g_theOperator.op_cpcode[0]=='G')
      { //若用户为宏昌公司，自动寻找宏昌的采购部门
              szSQL="select * from StockDepart where sd_code='10' order by sd_code";
                     RunSQL(dm1->Query1,szSQL,true);
                     while(!dm1->Query1->Eof)
                       {
                         m_lstStockDepartID.Add(dm1->Query1->FieldByName("sd_code")->AsString.c_str());
                         lstStockDepart->Items->Add(dm1->Query1->FieldByName("sd_name")->AsString);
                         dm1->Query1->Next();
                        }
                    lstStockDepart->ItemIndex=0;                        
        }
}
//---------------------------------------------------------------------------

void __fastcall TSumMnFactForm::btnQueryClick(TObject *Sender)
{
       	CString szSQL,szSQL1,szTable,szMsg;
        bool IsOldMn;
        int i,nSel;
	char strMnCode[80],strSdN[80],strSdP[80],strTemp[256],strDate0[80],strDate1[80],strItem[80];
        unsigned short year0,month0,day0,year1,month1,day1;

  TListItem *pItem;

        if(RadioGroup1->ItemIndex==-1)
        {
                ShowMessage("请选择分析类别");
                return;
        }
        if(RadioGroup2->ItemIndex==-1)
        {
                ShowMessage("请选择分析类型");
                return;
        }
        if(RadioGroup3->ItemIndex==-1)
        {
                ShowMessage("请决定是否使用标准");
                return;
        }
        if(RadioGroup1->ItemIndex==1 && RadioGroup2->ItemIndex==0 && edtMater->Text.IsEmpty())
        {
                ShowMessage("请输入材料编号");
                return;
        }
        if(RadioGroup1->ItemIndex==1 && RadioGroup2->ItemIndex==1 && lstSpeerFact->Text.IsEmpty())
        {
                ShowMessage("请输入厂商简称");
                return;
        }
        if(RadioGroup1->ItemIndex==0 && RadioGroup3->ItemIndex==1 && edtStanderN->Text.IsEmpty() && edtStanderN->Text<0)
        {
                ShowMessage("请输入合法次数");
                return;
        }
        if(RadioGroup1->ItemIndex==0 && RadioGroup3->ItemIndex==1 && edtStanderP->Text.IsEmpty() && edtStanderP->Text<0)
        {
                ShowMessage("请输入合法金额");
                return;
        }
/*
        if(!edtMater->Text.IsEmpty())                                           //判断是否围新编号
        {
        	strcpy(strMnCode,edtMater->Text.c_str());
        	szSQL.Format("select * from codecheck where cc_ncode='%s'",strMnCode);
        	RunSQL(dm1->Query1,szSQL,true);
               	if(!dm1->Query1->Eof)
                {
                        IsNewCode=true;
                }
                else
                {
                        IsNewCode=false;
                }
        }
*/
        lstStockDepart->Enabled=false;
        ProgressBar1->Visible=true;
        ProgressBar1->Position=1;
        if(!edtStanderN->Text.IsEmpty())
        {
                strcpy(strSdN,edtStanderN->Text.c_str());
        }
        if(!edtStanderP->Text.IsEmpty())
        {
                strcpy(strSdP,edtStanderP->Text.c_str());
        }
	szTable=GetTmpTableName();
	szSQL.Format("create table dbo.%s ("
                "t_pdcode varchar(8),"
                "t_pdmncode varchar(23),"
                "t_apsdcode varchar(2)"
		")",szTable);
	RunSQL(dm1->Query1,szSQL);

        ProgressBar1->Position=2;

        szSQL.Format("insert into %s"
                     " select pd_code,cc_ncode,ap_sdcode"
                     " from AskPurchase,PurchaseDetail,codecheck"
                     " where ap_code=substring(pd_code,1,7) and pd_mncode=cc_ocode",szTable);
	RunSQL(dm1->Query1,szSQL);

        ProgressBar1->Position=5;

        szSQL.Format("insert into %s"
                     " select pd_code,pd_mncode,ap_sdcode"
                     " from AskPurchase,PurchaseDetail"
                     " where ap_code=substring(pd_code,1,7) and pd_mncode not in (select cc_ocode from codecheck)",szTable);
	RunSQL(dm1->Query1,szSQL);


/*	szSQL.Format("create table dbo.%s ("
                "t_pdcode varchar(8),"
                "t_pdmncode varchar(23)"
		")",szTable);
	RunSQL(dm1->Query1,szSQL);

        ProgressBar1->Position=2;

        szSQL.Format("insert into %s"
                     " select pd_code,cc_ncode"
                     " from PurchaseDetail,codecheck"
                     " where pd_mncode=cc_ocode",szTable);
	RunSQL(dm1->Query1,szSQL);

        ProgressBar1->Position=5;

        szSQL.Format("insert into %s"
                     " select pd_code,pd_mncode"
                     " from PurchaseDetail"
                     " where pd_mncode not in (select cc_ocode from codecheck)",szTable);
	RunSQL(dm1->Query1,szSQL);
*/
        ProgressBar1->Position=15;

        if(RadioGroup2->ItemIndex==0)
        {
        	szSQL.Format("select mn_code,count(*),sum(bf_count*bf_price) from BookFactory,materialno,%s"
                             " where bf_apcode=%s.t_pdcode and %s.t_pdmncode=mn_code",szTable,szTable,szTable);
        }
        if(RadioGroup2->ItemIndex==1)
        {
        	szSQL.Format("select mf_shortname,count(*),sum(bf_count*bf_price) from BookFactory,Manufactur,%s"
                             " where bf_apcode=%s.t_pdcode and bf_mfcode=mf_code",szTable,szTable);
        }

        DateTimePicker1->DateTime.DecodeDate(&year0,&month0,&day0);
        sprintf(strDate0,"%04d-%02d-%02d",year0,month0,day0);
        DateTimePicker2->DateTime.DecodeDate(&year1,&month1,&day1);
        sprintf(strDate1,"%04d-%02d-%02d",year1,month1,day1);
        sprintf(strTemp," and bf_bookdate between '%s' and '%s'",strDate0,strDate1);
        szSQL+=strTemp;

	if((nSel=lstStockDepart->ItemIndex)>=0 && nSel<m_lstStockDepartID.GetSize())
	{//采购部门
		sprintf(strTemp," and t_apsdcode='%s'",m_lstStockDepartID[nSel]);
		szSQL+=strTemp;
	}
        if(RadioGroup1->ItemIndex==0 && RadioGroup2->ItemIndex==0 && RadioGroup3->ItemIndex==0)
        {
                sprintf(strTemp," group by mn_code");
                szSQL+=strTemp;
        }
        if(RadioGroup1->ItemIndex==0 && RadioGroup2->ItemIndex==0 && RadioGroup3->ItemIndex==1)
        {
                sprintf(strTemp," and bf_count*bf_price>'%s'",edtStanderP->Text.c_str());
                szSQL+=strTemp;
                sprintf(strTemp," group by mn_code having count(*)>'%s'",edtStanderN->Text.c_str());
                szSQL+=strTemp;
        }
        if(RadioGroup1->ItemIndex==0 && RadioGroup2->ItemIndex==1 && RadioGroup3->ItemIndex==0)
        {
                sprintf(strTemp," group by mf_shortname");
                szSQL+=strTemp;
        }
        if(RadioGroup1->ItemIndex==0 && RadioGroup2->ItemIndex==1 && RadioGroup3->ItemIndex==1)
        {
                sprintf(strTemp," and bf_count*bf_price>'%s'",edtStanderP->Text.c_str());
                szSQL+=strTemp;
                sprintf(strTemp," group by mf_shortname having count(*)>'%s'",edtStanderN->Text.c_str());
                szSQL+=strTemp;
        }
        if(RadioGroup1->ItemIndex==1 && RadioGroup2->ItemIndex==0)
        {
                sprintf(strTemp," and mn_code='%s'",edtMater->Text.c_str());
                szSQL+=strTemp;
                sprintf(strTemp," group by mn_code");
                szSQL+=strTemp;
        }
        if(RadioGroup1->ItemIndex==1 && RadioGroup2->ItemIndex==1)
        {
                sprintf(strTemp," and mf_shortname='%s'",lstSpeerFact->Text.c_str());
                szSQL+=strTemp;
                sprintf(strTemp," group by mf_shortname");
                szSQL+=strTemp;
        }
	RunSQL(dm1->Query1,szSQL,true);

        ProgressBar1->Position=20;

        lstView1->Items->Clear();

        if(RadioGroup1->ItemIndex==1 && !dm1->Query1->Eof)
        {
                edtSN->Text=dm1->Query1->Fields->Fields[1]->AsString;
                edtSP->Text=dm1->Query1->Fields->Fields[2]->AsString;
        }

        if(RadioGroup2->ItemIndex==0)
        {
                while(!dm1->Query1->Eof)
	        {
		        pItem=lstView1->Items->Add();
		        assert(pItem!=NULL);
                        pItem->Caption=dm1->Query1->FieldByName("mn_code")      ->AsString;
                        pItem->SubItems->Add("");
             	        pItem->SubItems->Add("");
		        pItem->SubItems->Add(dm1->Query1->Fields->Fields[1]     ->AsString);
		        pItem->SubItems->Add(dm1->Query1->Fields->Fields[2]     ->AsString);

		        dm1->Query1->Next();
	        }
        }
        if(RadioGroup2->ItemIndex==1)
        {
                while(!dm1->Query1->Eof)
	        {
		        pItem=lstView1->Items->Add();
		        assert(pItem!=NULL);
                        pItem->Caption="";
                        pItem->SubItems->Add("");
             	        pItem->SubItems->Add(dm1->Query1->FieldByName("mf_shortname")     ->AsString);
		        pItem->SubItems->Add(dm1->Query1->Fields->Fields[1]     ->AsString);
		        pItem->SubItems->Add(dm1->Query1->Fields->Fields[2]     ->AsString);

		        dm1->Query1->Next();
	        }
        }
        ProgressBar1->Position=25;
//	RunSQL(dm1->Query1,szSQL,true);        
/*        if(RadioGroup1->ItemIndex==1 && RadioGroup2->ItemIndex==0)
        {
                while(!dm1->Query1->Eof)
	        {
                        edtSN->Text=dm1->Query1->Fields->Fields[1]->AsString;
                        edtSP->Text=dm1->Query1->Fields->Fields[2]->AsString;
		        dm1->Query1->Next();
                }
        }
        if(RadioGroup1->ItemIndex==1 && RadioGroup2->ItemIndex==1)
        {
                while(!dm1->Query1->Eof)
	        {
                        edtSN->Text=dm1->Query1->Fields->Fields[1]->AsString;
                        edtSP->Text=dm1->Query1->Fields->Fields[2]->AsString;
		        dm1->Query1->Next();
                }
        }
*/
        ProgressBar1->Position=30;
  if(RadioGroup2->ItemIndex==0)
  {
        for(i=0;i<lstView1->Items->Count;i++)
        {
		pItem=lstView1->Items->Item[i];
                szSQL.Format("select mn_name from materialno where mn_code='%s'",pItem->Caption.c_str());
        	RunSQL(dm1->Query1,szSQL,true);
                pItem->SubItems->Strings[0]=dm1->Query1->FieldByName("mn_name")     ->AsString;
        }
  }

	szSQL.Format("drop table dbo.%s",szTable);
	RunSQL(dm1->Query1,szSQL);



        btnQuery->Enabled=false;
        btnQueryMT->Enabled=false;
        btnSpeerFactSearch->Enabled=false;
        RadioGroup1->Enabled=false;
        RadioGroup2->Enabled=false;
        RadioGroup3->Enabled=false;
        DisableEdit();
        if(RadioGroup1->ItemIndex==1)
        {
                edtSN->Enabled=true;
                edtSP->Enabled=true;
        }
        ProgressBar1->Position=35;
}
//---------------------------------------------------------------------------

void __fastcall TSumMnFactForm::btnRQueryClick(TObject *Sender)
{
        lstView1->Items->Clear();
        btnQuery->Enabled=true;
        btnQueryMT->Enabled=false;
        btnSpeerFactSearch->Enabled=false;
        lstStockDepart->Enabled=true;        
        edtSN->Enabled=false;
        edtSP->Enabled=false;
        RadioGroup1->Enabled=true;
        RadioGroup2->Enabled=false;
        RadioGroup3->Enabled=false;
        ProgressBar1->Position=0;
        SetDefault();
        DisableEdit();
}
//---------------------------------------------------------------------------



void __fastcall TSumMnFactForm::RadioGroup1Click(TObject *Sender)
{
        if(RadioGroup1->ItemIndex==0)
        {
                edtMater->Text="";
                edtMnname->Text="";
                edtStanderN->Text="";
                edtStanderP->Text="";
                lstSpeerFact->Text="";
                lstSpeerFact->ItemIndex=-1;
                edtSP->Text="";
                edtSN->Text="";
                NorAnly=true;
                edtMater->Enabled=false;
                edtMnname->Enabled=false;
                lstSpeerFact->Enabled=false;
                RadioGroup1->Enabled=false;
                RadioGroup2->Enabled=true;
//                RadioGroup3->Enabled=true;
        }
        if(RadioGroup1->ItemIndex==1)
        {
                edtMater->Text="";
                edtMnname->Text="";
                edtStanderN->Text="";
                edtStanderP->Text="";
                edtSP->Text="";
                edtSN->Text="";
                lstSpeerFact->Text="";                
                RadioGroup3->ItemIndex=0;
                NorAnly=false;
//                edtMater->Enabled=true;
//                edtMnname->Enabled=true;
//                lstSpeerFact->Enabled=true;
                RadioGroup1->Enabled=false;
                RadioGroup2->Enabled=true;
//                RadioGroup3->Enabled=false;
        }
}
//---------------------------------------------------------------------------

void __fastcall TSumMnFactForm::RadioGroup2Click(TObject *Sender)
{
        if(RadioGroup2->ItemIndex==0)
        {
                lstSpeerFact->Text="";
                lstSpeerFact->ItemIndex=-1;
                if(RadioGroup1->ItemIndex==0)
                {
                        RadioGroup3->Enabled=true;
                }
                else
                {
                        edtMater->Enabled=true;
                        edtMnname->Enabled=true;
                        btnQueryMT->Enabled=true;
        		if(btnQueryMT->CanFocus())	btnQueryMT->SetFocus();
                }
                MnAnly=true;
                RadioGroup2->Enabled=false;
        }
        if(RadioGroup2->ItemIndex==1)
        {
                edtMater->Text="";
                edtMnname->Text="";

                if(RadioGroup1->ItemIndex==0)
                {
                        RadioGroup3->Enabled=true;
                }
                else
                {
                        btnSpeerFactSearch->Enabled=true;
                        lstSpeerFact->Enabled=true;
        		if(btnSpeerFactSearch->CanFocus())	btnSpeerFactSearch->SetFocus();
                }
                MnAnly=false;
                RadioGroup2->Enabled=false;
        }
}
//---------------------------------------------------------------------------

void __fastcall TSumMnFactForm::btntoExcelClick(TObject *Sender)
{
  Variant vExcel,vSheet;
  int nRow,i;
  TListItem *pItem;

  try
  {
	  nRow=1;
		if(!OpenExcel("材料与厂商订购统计报表.xls",vExcel,vSheet))	return;
		ListHead2Excel(lstView1,vSheet,nRow++);
		for(i=0;i<lstView1->Items->Count;i++)
    {
    	pItem=lstView1->Items->Item[i];
      InsertExcelItem(vSheet,nRow++,
      	pItem->Caption.c_str(),
        pItem->SubItems->Strings[0].c_str(),
        pItem->SubItems->Strings[1].c_str(),
        pItem->SubItems->Strings[2].c_str(),
        pItem->SubItems->Strings[3].c_str(),
				NULL);
    }
  }
	catch(...)
	{
	}
}
//---------------------------------------------------------------------------

void __fastcall TSumMnFactForm::RadioGroup3Click(TObject *Sender)
{
        if(RadioGroup3->ItemIndex==0)
        {
                edtStanderN->Text="";
                edtStanderP->Text="";
        }
        if(RadioGroup3->ItemIndex==1)
        {
                edtStanderN->Text="";
                edtStanderP->Text="";
                edtStanderN->Enabled=true;
                edtStanderP->Enabled=true;
		if(edtStanderN->CanFocus())	edtStanderN->SetFocus();
        }
}
//---------------------------------------------------------------------------

void __fastcall TSumMnFactForm::lstView1SelectItem(TObject *Sender,
      TListItem *Item, bool Selected)
{
	TListItem *pItem;
	if(!Selected || lstView1->Selected==NULL)	return;
	pItem=lstView1->Selected;
        edtMater->Text=pItem->Caption;
        edtMnname->Text=pItem->SubItems->Strings[0];
        lstSpeerFact->Text=pItem->SubItems->Strings[1];
        edtSN->Text=pItem->SubItems->Strings[2];
        edtSP->Text=pItem->SubItems->Strings[3];
}
//---------------------------------------------------------------------------


void __fastcall TSumMnFactForm::edtMaterExit(TObject *Sender)
{
	char strName[256];
	CString szSQL;

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
//---------------------------------------------------------------------------

