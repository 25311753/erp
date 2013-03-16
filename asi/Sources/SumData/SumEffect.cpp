//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <assert.h>
#pragma hdrstop

#include "DataModule.h"
#include "BaseCode.h"
#include "SumEffect.h"
#include "TConst.h"
#include "LdyInterface.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSumEffectForm *SumEffectForm;
//--------------------------------------------------------------------------
//日常绩效统计报表接口，文件：SumEffect*
void SumEffect(int nAuth)
{
	CALL_FORM(TSumEffectForm);
}
//---------------------------------------------------------------------------
__fastcall TSumEffectForm::TSumEffectForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TSumEffectForm::FormShow(TObject *Sender)
{
 CString szSQL;
 unsigned short year,month,day;
 int i;
 char strTemp[256];

 edtSNum->Text="";
 edtSPrice->Text="";

 m_lstHandleID.Add("");                                        //采购经办
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


 m_lstStockDepartID.Add("");                                        //采购部门
 lstStockDepart->Items->Add("全部");
 szSQL="select * from StockDepart order by sd_code";
 RunSQL(dm1->Query1,szSQL,true);
 while(!dm1->Query1->Eof)
  {
    m_lstStockDepartID.Add(dm1->Query1->FieldByName("sd_code")->AsString.c_str());
    lstStockDepart->Items->Add(dm1->Query1->FieldByName("sd_name")->AsString);
    dm1->Query1->Next();
  }
 lstStockDepart->ItemIndex=0;




/*
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
        //采购经办
                    m_lstHandleID.Add("");
                    lstHandle->Items->Add("采购处全部采购经办");
                    szSQL="select * from StockHandleman where sh_sdcode='X' or sh_sdcode='11'order by sh_code";
                    RunSQL(dm1->Query1,szSQL,true);
                    while(!dm1->Query1->Eof)
                       {
                         m_lstHandleID.Add(dm1->Query1->FieldByName("sh_code")->AsString.c_str());
                         lstHandle->Items->Add(dm1->Query1->FieldByName("sh_name")->AsString);
                         dm1->Query1->Next();
                        }
                     lstHandle->ItemIndex=0;

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

        //采购经办
                    m_lstHandleID.Add("");
                    lstHandle->Items->Add("全部采购经办");
                    szSQL="select * from StockHandleman where sh_sdcode='Y' or sh_sdcode='1' order by sh_code";
                    RunSQL(dm1->Query1,szSQL,true);
                    while(!dm1->Query1->Eof)
                       {
                         m_lstHandleID.Add(dm1->Query1->FieldByName("sh_code")->AsString.c_str());
                         lstHandle->Items->Add(dm1->Query1->FieldByName("sh_name")->AsString);
                         dm1->Query1->Next();
                        }
                     lstHandle->ItemIndex=0;
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

        //采购经办
                    m_lstHandleID.Add("");
                    lstHandle->Items->Add("全部采购经办");
                    szSQL="select * from StockHandleman where sh_sdcode='9' order by sh_code";
                    RunSQL(dm1->Query1,szSQL,true);
                    while(!dm1->Query1->Eof)
                       {
                         m_lstHandleID.Add(dm1->Query1->FieldByName("sh_code")->AsString.c_str());
                         lstHandle->Items->Add(dm1->Query1->FieldByName("sh_name")->AsString);
                         dm1->Query1->Next();
                        }
                     lstHandle->ItemIndex=0;
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

        //采购经办
                    m_lstHandleID.Add("");
                    lstHandle->Items->Add("全部采购经办");
                    szSQL="select * from StockHandleman where sh_sdcode='4' or sh_sdcode='5' order by sh_code";
                    RunSQL(dm1->Query1,szSQL,true);
                    while(!dm1->Query1->Eof)
                       {
                         m_lstHandleID.Add(dm1->Query1->FieldByName("sh_code")->AsString.c_str());
                         lstHandle->Items->Add(dm1->Query1->FieldByName("sh_name")->AsString);
                         dm1->Query1->Next();
                        }
                     lstHandle->ItemIndex=0;
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

        //采购经办
                    m_lstHandleID.Add("");
                    lstHandle->Items->Add("全部采购经办");
                    szSQL="select * from StockHandleman where sh_sdcode='2' or sh_sdcode='3' order by sh_code";
                    RunSQL(dm1->Query1,szSQL,true);
                    while(!dm1->Query1->Eof)
                       {
                         m_lstHandleID.Add(dm1->Query1->FieldByName("sh_code")->AsString.c_str());
                         lstHandle->Items->Add(dm1->Query1->FieldByName("sh_name")->AsString);
                         dm1->Query1->Next();
                        }
                     lstHandle->ItemIndex=0;
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

        //采购经办
                    m_lstHandleID.Add("");
                    lstHandle->Items->Add("全部采购经办");
                    szSQL="select * from StockHandleman where sh_sdcode='6' or sh_sdcode='7' order by sh_code";
                    RunSQL(dm1->Query1,szSQL,true);
                    while(!dm1->Query1->Eof)
                       {
                         m_lstHandleID.Add(dm1->Query1->FieldByName("sh_code")->AsString.c_str());
                         lstHandle->Items->Add(dm1->Query1->FieldByName("sh_name")->AsString);
                         dm1->Query1->Next();
                        }
                     lstHandle->ItemIndex=0;
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

        //采购经办
                    m_lstHandleID.Add("");
                    lstHandle->Items->Add("全部采购经办");
                    szSQL="select * from StockHandleman where sh_sdcode='10' order by sh_code";
                    RunSQL(dm1->Query1,szSQL,true);
                    while(!dm1->Query1->Eof)
                       {
                         m_lstHandleID.Add(dm1->Query1->FieldByName("sh_code")->AsString.c_str());
                         lstHandle->Items->Add(dm1->Query1->FieldByName("sh_name")->AsString);
                         dm1->Query1->Next();
                        }
                     lstHandle->ItemIndex=0;
      }
*/
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

 m_lstTypeID.Add("");
 lstType->Items->Add("全部");
 szSQL="select * from diclargetype where lt_code!='M' order by lt_code";        //不统计原料采购
 RunSQL(dm1->Query1,szSQL,true);
 while(!dm1->Query1->Eof)
  {
    m_lstTypeID.Add(dm1->Query1->FieldByName("lt_code")->AsString.c_str());
    lstType->Items->Add(dm1->Query1->FieldByName("lt_name")->AsString);
    dm1->Query1->Next();
  }
 lstType->ItemIndex=0;

 TDateTime tNow;
 tNow=GetSysTime(false);
 tNow.DecodeDate(&year,&month,&day);
 DateTimePicker1->Date=tNow;
 DateTimePicker2->Date=tNow;
}
//---------------------------------------------------------------------------

void __fastcall TSumEffectForm::btnQuitClick(TObject *Sender)
{
  Close();        
}
//---------------------------------------------------------------------------

void __fastcall TSumEffectForm::btntoExcelClick(TObject *Sender)
{
  Variant vExcel,vSheet;
  int nRow,i;
  TListItem *pItem;

  try
  {
	  nRow=1;
		if(!OpenExcel("日常绩效统计报表.xls",vExcel,vSheet))	return;
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
        pItem->SubItems->Strings[8].c_str(),
        pItem->SubItems->Strings[9].c_str(),
        pItem->SubItems->Strings[10].c_str(),
        pItem->SubItems->Strings[11].c_str(),
				NULL);
    }
  }
	catch(...)
	{
	}
}
//---------------------------------------------------------------------------

void __fastcall TSumEffectForm::btnQueryClick(TObject *Sender)
{
  int nDays,nYear,nMonth,nDay;
  CString szSQL;
  TListItem *pItem;
  char strTemp[256],strSHID[256],strID[80];
  int nSel,i;
  char strDate0[80],strDate1[80],strTemp2[256];
  unsigned short year0,month0,day0,year1,month1,day1;
  int nRightSH,nRightRP;
  char sNumc[2046];
  float sNum[2046];
//---------- new 0711---取得操作者对应的采购部门别(在StockHandleman中的公司别) 与相应权限-srtSHID-------
        szSQL.Format("select * from StockHandleman where sh_code='%s'",operatorcode);
        RunSQL(dm1->Query1,szSQL,true);
        strcpy(strSHID,dm1->Query1->FieldByName("sh_sdcode")->AsString.c_str());
        nRightSH=GetOperatorRight(operatorcode.c_str(),"IDM_PRSHLPRICE");            //取得权限
        nRightRP=GetOperatorRight(operatorcode.c_str(),"IDM_RAWPRICERIGHT");            //取得权限
//------------------------------------------------------------------------------

  lstView->Items->Clear();

 szSQL.Format("select distinct * from AskPurchase,CompareFactory,DecideFactory,StockHandleman,StockDepart,"
              "diclargetype,PurchaseDetail,materialno,DepartCorp,DicDepart,diccorp,DicUnits"
              " where ap_code=substring(cf_apcode,1,7) and ap_code=substring(df_apcode,1,7)"
              " and cf_mfcode=df_mfplan and ap_shcode=sh_code and ap_sdcode=sd_code and cf_apcode=df_apcode"
              " and cf_apcode=pd_code and lt_code=substring(pd_mncode,2,1) and du_code=cf_quoteunit"
              " and pd_mncode=mn_code and cp_code=substring(ap_reqdepart,1,1)"
              " and ap_reqdepart=dd_code and dc_code=substring(ap_reqdepart,1,2)"
              );
        DateTimePicker1->DateTime.DecodeDate(&year0,&month0,&day0);
        sprintf(strDate0,"%04d-%02d-%02d",year0,month0,day0);
        DateTimePicker2->DateTime.DecodeDate(&year1,&month1,&day1);
        sprintf(strDate1,"%04d-%02d-%02d",year1,month1,day1);
        sprintf(strTemp," and df_plandate between '%s' and '%s'",strDate0,strDate1);
        szSQL+=strTemp;

 if((nSel=lstHandle->ItemIndex)>0 && nSel<m_lstHandleID.GetSize())
  {
    sprintf(strTemp," and ap_shcode='%s'",m_lstHandleID[nSel]);
    szSQL+=strTemp;
  }
// if((nSel=lstStockDepart->ItemIndex)>=0 && nSel<m_lstStockDepartID.GetSize())
 if((nSel=lstStockDepart->ItemIndex)>0 && nSel<m_lstStockDepartID.GetSize())
  {
    sprintf(strTemp," and ap_sdcode='%s'",m_lstStockDepartID[nSel]);
    szSQL+=strTemp;
  }
 if((nSel=lstCorp->ItemIndex)>0 && nSel<m_lstCorpID.GetSize())
  {
//    sprintf(strTemp," and substring(pd_mncode,1,1)='%s'",m_lstCorpID[nSel]);    //用材料编号的首位来区别公司别
    sprintf(strTemp," and substring(ap_reqdepart,1,2)='%s'",m_lstCorpID[nSel]);
    szSQL+=strTemp;
  }
  if((nSel=lstType->ItemIndex)>0 && nSel<m_lstTypeID.GetSize())
  {
    sprintf(strTemp," and substring(pd_mncode,2,1)='%s'",m_lstTypeID[nSel]);
    szSQL+=strTemp;
  }
  if(lstType->ItemIndex==0)                                                     //选择“全部”时，不查询原料采购
  {
    sprintf(strTemp," and substring(pd_mncode,2,1)!='M'");
    szSQL+=strTemp;
  }

 szSQL+=" order by cf_apcode,df_plandate";
 RunSQL(dm1->Query1,szSQL,true);
 while(!dm1->Query1->Eof)
  {
       pItem=lstView->Items->Add();
       assert(pItem!=NULL);
       pItem->Caption=dm1->Query1->FieldByName("cf_apcode")->AsString;
       pItem->SubItems->Add(DateField2Text(dm1->Query1->FieldByName("ap_reqdate")));
       pItem->SubItems->Add(dm1->Query1->FieldByName("cp_name")->AsString);
       pItem->SubItems->Add(dm1->Query1->FieldByName("lt_name")->AsString);
       pItem->SubItems->Add(dm1->Query1->FieldByName("mn_name")->AsString);
       pItem->SubItems->Add(FloatField2String(dm1->Query1->FieldByName("cf_quotenum"),2));



       pItem->SubItems->Add(dm1->Query1->FieldByName("du_name")->AsString);
//       pItem->SubItems->Add(dm1->Query1->FieldByName("cf_quoteprice")->AsString);
//       pItem->SubItems->Add(dm1->Query1->FieldByName("cf_higgleprice")->AsString);
//---new 0706----只有当操作员是本单经办时，才可查看单价-------------------------
//        strcpy(strTemp3,dm1->Query1->FieldByName("ap_shcode")->AsString.c_str());
/*若是”经办间可以查看” 则
当碰到宏信宏纶的案件且为原料采购，若原料单价为3或为同采购部门经办，则可以查看该单单价，
其余的案件(包括非宏信宏纶或非原料采购)，经办间可以查看单价，其余不可以

若不是”经办间可以查看“ 则
当碰到宏信宏纶的案件且为原料采购 则若原料单价为3或本身为该单经办，则可以查看该单单价，
其余的案件(包括非宏信宏纶或非原料采购)，要经办自己才可以查看单价
*/

	strcpy(strID,dm1->Query1->FieldByName("ap_sdcode")->AsString.c_str());
        strcpy(strTemp,dm1->Query1->FieldByName("mn_code")->AsString.c_str());

             if(operatorcode=="admin")
             {
                       pItem->SubItems->Add(dm1->Query1->FieldByName("cf_quoteprice")->AsString);
                       pItem->SubItems->Add(dm1->Query1->FieldByName("cf_higgleprice")->AsString);
             }
             else if(nRightSH==3)
             {
                if((dm1->Query1->FieldByName("ap_sdcode")->AsString=='2' || dm1->Query1->FieldByName("ap_sdcode")->AsString=='3') && strTemp[1]=='M')     //宏信宏纶的原料采购 //若有"采购经办间可互相查看"的权限，则经办间可以互相查看
                {
                        if(nRightRP!=3 && strcmp(strID,strSHID)!=0)
                        {
                                pItem->SubItems->Add("");
                                pItem->SubItems->Add("");
                        }
                        else
                        {
                               pItem->SubItems->Add(dm1->Query1->FieldByName("cf_quoteprice")->AsString);
                               pItem->SubItems->Add(dm1->Query1->FieldByName("cf_higgleprice")->AsString);
                        }

                }
                else
                {
                        if(strcmp(strID,strSHID)!=0)
                        {
                                pItem->SubItems->Add("");
                                pItem->SubItems->Add("");
                        }
                        else
                        {
                               pItem->SubItems->Add(dm1->Query1->FieldByName("cf_quoteprice")->AsString);
                               pItem->SubItems->Add(dm1->Query1->FieldByName("cf_higgleprice")->AsString);
                        }
                }
             }
             else
             {
                if((dm1->Query1->FieldByName("ap_sdcode")->AsString=='2' || dm1->Query1->FieldByName("ap_sdcode")->AsString=='3') && strTemp[1]=='M')                                                    //若有"采购经办间可互相查看"的权限，则经办间可以互相查看
                {
                        if(nRightRP!=3 && operatorcode!=dm1->Query1->FieldByName("ap_shcode")->AsString)
                        {
                                pItem->SubItems->Add("");
                                pItem->SubItems->Add("");
                        }
                        else
                        {
                               pItem->SubItems->Add(dm1->Query1->FieldByName("cf_quoteprice")->AsString);
                               pItem->SubItems->Add(dm1->Query1->FieldByName("cf_higgleprice")->AsString);
                        }

                }
                else
                {
                        if(operatorcode!=dm1->Query1->FieldByName("ap_shcode")->AsString)
                        {
                                pItem->SubItems->Add("");
                                pItem->SubItems->Add("");
                        }
                        else
                        {
                               pItem->SubItems->Add(dm1->Query1->FieldByName("cf_quoteprice")->AsString);
                               pItem->SubItems->Add(dm1->Query1->FieldByName("cf_higgleprice")->AsString);
                        }
                }
             }
/*             else
             {
                if(nRightSH==3)                                                    //若有"采购经办间可互相查看"的权限，则经办间可以互相查看
                {
                        if(strcmp(strID,strSHID)!=0)
                        {
                                pItem->SubItems->Add("");
                                pItem->SubItems->Add("");
                        }
                        else
                        {
                               pItem->SubItems->Add(dm1->Query1->FieldByName("cf_quoteprice")->AsString);
                               pItem->SubItems->Add(dm1->Query1->FieldByName("cf_higgleprice")->AsString);
                        }
                }
                else                                                               //否则，只有经办自己才可以查看
                {       //宏信与宏纶的案件
                        if(dm1->Query1->FieldByName("ap_sdcode")->AsString=='2' || dm1->Query1->FieldByName("ap_sdcode")->AsString=='3')
                        {
                                if(nRightRP!=3 && operatorcode!=dm1->Query1->FieldByName("ap_shcode")->AsString)
                                {
                                        pItem->SubItems->Add("");
                                        pItem->SubItems->Add("");
                                }
                                else
                                {
                                        pItem->SubItems->Add(dm1->Query1->FieldByName("cf_quoteprice")->AsString);
                                        pItem->SubItems->Add(dm1->Query1->FieldByName("cf_higgleprice")->AsString);
                                }
                        }
                        //其它案件如常
                        else
                        {
                                if(operatorcode!=dm1->Query1->FieldByName("ap_shcode")->AsString)
                                {
                                        pItem->SubItems->Add("");
                                        pItem->SubItems->Add("");
                                }
                                else
                                {
                                        pItem->SubItems->Add(dm1->Query1->FieldByName("cf_quoteprice")->AsString);
                                        pItem->SubItems->Add(dm1->Query1->FieldByName("cf_higgleprice")->AsString);
                                }
                        }
                }
             }
*/
//------------------------------------------------------------------------------
       pItem->SubItems->Add(dm1->Query1->FieldByName("cf_quotermb")->AsString);
       pItem->SubItems->Add(DateField2Text(dm1->Query1->FieldByName("df_plandate")));
       pItem->SubItems->Add(dm1->Query1->FieldByName("sh_name")->AsString);
       pItem->SubItems->Add(dm1->Query1->FieldByName("sd_name")->AsString);
       //pItem->SubItems->Add(FloatField2String(dm1->Query1->FieldByName("bf_count"),2));
       //pItem->SubItems->Add(dm1->Query1->FieldByName("mf_shortname")->AsString);
       //pItem->SubItems->Add(dm1->Query1->FieldByName("pd_code")->AsString);
      // pItem->SubItems->Add(dm1->Query1->FieldByName("sh_name")->AsString);
		dm1->Query1->Next();
      // strcpy(strTemp,dm1->Query1->FieldByName("ap_reqdepart")->AsString.c_str());
  }
//-----------统计数量与金额-----------------------------------------------------
 szSQL.Format("select count(*), sum(cf_higgleprice*cf_quotenum)  from AskPurchase,CompareFactory,DecideFactory,StockHandleman,StockDepart,"
              "diclargetype,PurchaseDetail,materialno,DepartCorp,DicDepart,diccorp,DicUnits"
              " where ap_code=substring(cf_apcode,1,7) and ap_code=substring(df_apcode,1,7)"
              " and cf_mfcode=df_mfplan and ap_shcode=sh_code and ap_sdcode=sd_code and cf_apcode=df_apcode"
              " and cf_apcode=pd_code and lt_code=substring(pd_mncode,2,1) and du_code=cf_quoteunit"
              " and pd_mncode=mn_code and cp_code=substring(ap_reqdepart,1,1)"
              " and ap_reqdepart=dd_code and dc_code=substring(ap_reqdepart,1,2)"
              );
        DateTimePicker1->DateTime.DecodeDate(&year0,&month0,&day0);
        sprintf(strDate0,"%04d-%02d-%02d",year0,month0,day0);
        DateTimePicker2->DateTime.DecodeDate(&year1,&month1,&day1);
        sprintf(strDate1,"%04d-%02d-%02d",year1,month1,day1);
        sprintf(strTemp," and df_plandate between '%s' and '%s'",strDate0,strDate1);
        szSQL+=strTemp;

 if((nSel=lstHandle->ItemIndex)>0 && nSel<m_lstHandleID.GetSize())
  {
    sprintf(strTemp," and ap_shcode='%s'",m_lstHandleID[nSel]);
    szSQL+=strTemp;
  }
// if((nSel=lstStockDepart->ItemIndex)>=0 && nSel<m_lstStockDepartID.GetSize())
 if((nSel=lstStockDepart->ItemIndex)>0 && nSel<m_lstStockDepartID.GetSize())
  {
    sprintf(strTemp," and ap_sdcode='%s'",m_lstStockDepartID[nSel]);
    szSQL+=strTemp;
  }
 if((nSel=lstCorp->ItemIndex)>0 && nSel<m_lstCorpID.GetSize())
  {
//    sprintf(strTemp," and substring(pd_mncode,1,1)='%s'",m_lstCorpID[nSel]);    //用材料编号的首位来区别公司别
    sprintf(strTemp," and substring(ap_reqdepart,1,2)='%s'",m_lstCorpID[nSel]);
    szSQL+=strTemp;
  }
  if((nSel=lstType->ItemIndex)>0 && nSel<m_lstTypeID.GetSize())
  {
    sprintf(strTemp," and substring(pd_mncode,2,1)='%s'",m_lstTypeID[nSel]);
    szSQL+=strTemp;
  }

 RunSQL(dm1->Query1,szSQL,true);
 while(!dm1->Query1->Eof)
  {
//                ShowMessage(FloatField2String(dm1->Query1->FieldByName("sum(cf_quotenum)"));
                edtSNum->Text=dm1->Query1->Fields->Fields[0]->AsString;
                
                edtSPrice->Text=dm1->Query1->Fields->Fields[1]->AsString;
		dm1->Query1->Next();

  }

}
//---------------------------------------------------------------------------



void __fastcall TSumEffectForm::RadioButton2Click(TObject *Sender)
{
        m_sType=true;
        lstHandle->Enabled=true;
        DateTimePicker2->Enabled=false;
        lstStockDepart->Enabled=false;
        lstStockDepart->ItemIndex=0;
        lstCorp->Enabled=false;
        lstCorp->ItemIndex=0;
        lstType->Enabled=false;
        lstType->ItemIndex=0;
}
//---------------------------------------------------------------------------

void __fastcall TSumEffectForm::RadioButton1Click(TObject *Sender)
{
        m_sType=false;
        DateTimePicker2->Enabled=true;
        lstHandle->Enabled=true;
        lstStockDepart->Enabled=true;
        lstCorp->Enabled=true;
        lstType->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TSumEffectForm::DateTimePicker1Change(TObject *Sender)
{
        if(m_sType)
        DateTimePicker2->Date=DateTimePicker1->Date;             
}
//---------------------------------------------------------------------------

void __fastcall TSumEffectForm::RadioButton3Click(TObject *Sender)
{
        m_sType=true;
        lstHandle->Enabled=false;
        lstHandle->ItemIndex=0;
        DateTimePicker2->Enabled=false;
        lstStockDepart->Enabled=false;
        lstStockDepart->ItemIndex=0;
        lstCorp->Enabled=false;
        lstCorp->ItemIndex=0;
        lstType->Enabled=true;
}
//---------------------------------------------------------------------------


void __fastcall TSumEffectForm::RadioButton4Click(TObject *Sender)
{
        m_sType=true;
        lstHandle->Enabled=false;
        lstHandle->ItemIndex=0;
        DateTimePicker2->Enabled=false;
        lstStockDepart->Enabled=false;
        lstStockDepart->ItemIndex=0;
        lstCorp->Enabled=true;
        lstType->Enabled=false;
        lstType->ItemIndex=0;
}
//---------------------------------------------------------------------------

