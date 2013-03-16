//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CostAccounting.h"   
#include "DataModule.h"
#include "BaseCode.h"
#include "LdyInterface.h"

#include "OleExcelCom.h"
#include "Excel_2K_SRVR2.h"
#include <OleServer.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TCostAccountingForm *CostAccountingForm;

typedef struct
{
        int chid;
        char strChname[80];
} CHARGES1;

static CArray<CHARGES1,CHARGES1> gCHARGES1;
//加入提单号、柜号、备注、客户工单号
int charge_start_column = 6+3+1-1+1; // 费用列起始列偏移. +0 ->第一个费用； +1 第二个费用
void CostAccounting(int nAuth)
{
        CALL_FORM(TCostAccountingForm);
}
//same as financeform !!!
int GetClassRight1(LPCSTR lpszChname){
  int nRt = 0;
  for(int i=0;i<gCHARGES1.GetSize();i++)
  {
  	if(strcmp(gCHARGES1[i].strChname,lpszChname)==0)
    	return nRt = gCHARGES1[i].chid;
  }
  return nRt;
}
//---------------------------------------------------------------------------
__fastcall TCostAccountingForm::TCostAccountingForm(TComponent* Owner)
        : TForm(Owner)
{
  m_enWorkState=EN_IDLE;
//  isHasResult = false;
}
//---------------------------------------------------------------------------
void __fastcall TCostAccountingForm::FormShow(TObject *Sender)
{
        gCHARGES1.RemoveAll();
        cbb1->Items->Add("");
        cbb2->Items->Add("");
        cbb3->Items->Add("");
        cbb4->Items->Add("");
        cbb5->Items->Add("");
        cbb6->Items->Add("");
        cbb7->Items->Add("");
        cbb8->Items->Add("");
        cbb9->Items->Add("");
        cbb10->Items->Add("");
        CString szSQL;
        szSQL.Format("select * from charges order by chid");
        RunSQL(dm1->Query1,szSQL,true);
        int charge_row = 0;
        while(!dm1->Query1->Eof)
        {
                AnsiString chname = dm1->Query1->FieldByName("chname")->AsString;
                cbb1->Items->Add(chname);
                cbb2->Items->Add(chname);
                cbb3->Items->Add(chname);
                cbb4->Items->Add(chname);
                cbb5->Items->Add(chname);
                cbb6->Items->Add(chname);
                cbb7->Items->Add(chname);
                cbb8->Items->Add(chname);
                cbb9->Items->Add(chname);
                cbb10->Items->Add(chname);
                lstView->Columns->Items[charge_start_column+(++charge_row)]->Caption = chname;

                int chid = dm1->Query1->FieldByName("chid")->AsInteger;
                CHARGES1 charge;
                charge.chid = chid;
                strcpy(charge.strChname,dm1->Query1->FieldByName("chname")->AsString.c_str());
                gCHARGES1.Add(charge);
                dm1->Query1->Next();
        }
        lstView->Columns->Items[charge_start_column+(++charge_row)]->Caption = "合计";
        cbb1->ItemIndex = 1;
        cbb2->ItemIndex = 2;
        cbb3->ItemIndex = 3;
        cbb4->ItemIndex = 4;
        cbb5->ItemIndex = 5;
        cbb6->ItemIndex = 6;
        cbb7->ItemIndex = 7;
        cbb8->ItemIndex = 8;
        cbb9->ItemIndex = 9;
        cbb10->ItemIndex = 10;

        //draw lstview column tital , after "核销单号" ，list all charge type, order by chid

        TDateTime tDate=GetSysTime(false);
        dtpQryAcceptDate->DateTime=tDate;
        dtpQryAcceptDateEnd->DateTime=tDate;

        edtIn->Text = "0";
        edtBase->Text = "0";
        edtPure->Text = "0";
        m_enWorkState=EN_IDLE;
        ResetCtrl();
        
}
//---------------------------------------------------------------------------
void __fastcall TCostAccountingForm::lstViewClick(TObject *Sender)
{

      if(lstView->Selected == NULL){
//        btnAddDetail->Enabled = true;
         btnMod->Enabled = false;
                  clearQryInput();
      }        
}
//---------------------------------------------------------------------------
void __fastcall TCostAccountingForm::lstViewSelectItem(TObject *Sender,
      TListItem *Item, bool Selected)
{
        ResetCharges();
        edtCid->Text = Item->Caption;
        edtClient->Text = Item->SubItems->Strings[3];
        edtDeclareId->Text = Item->SubItems->Strings[4];
        edtBaseCost->Text = Item->SubItems->Strings[6];
        edtRemark->Text = Item->SubItems->Strings[9];
        int cbb_order = 0;
        for (int i=0; i<gCHARGES1.GetSize(); ++i){
                int pos = charge_start_column + i;
                if (Item->SubItems->Strings[pos] != ""){
                        cbb_order++;
                        TComboBox *cbb = getCbb(cbb_order);
                        TEdit *edt = getEdt(cbb_order);
                        cbb->ItemIndex = cbb->Items->IndexOf(gCHARGES1[i].strChname);
                        edt->Text = Item->SubItems->Strings[pos];
                }
        }

//        btnAddDetail->Enabled = false;
        btnMod->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TCostAccountingForm::btnModClick(TObject *Sender)
{
  m_enWorkState=EN_EDIT;
  ResetCtrl();
  return;        
}
//---------------------------------------------------------------------------
void __fastcall TCostAccountingForm::btnOKClick(TObject *Sender)
{
  char strName[80],*ptr,strTemp[80];
  int nState;

  switch(m_enWorkState)
  {
    case EN_EDIT:
      if (-1 == ModCharge())
        return;
      break;
    default:
      ShowMessage("Work State not AddNew or Edit");
      return;
  }

  m_enWorkState=EN_IDLE;
  ResetCtrl();          
}
//---------------------------------------------------------------------------
void __fastcall TCostAccountingForm::btnCancelClick(TObject *Sender)
{
  int nState;

  lstView->ItemIndex = -1;
  lstView->Selected = NULL; 
  nState=m_enWorkState;
  m_enWorkState=EN_IDLE;
  ResetCtrl();
  clearQryInput();
}
//---------------------------------------------------------------------------

void TCostAccountingForm::InsertValue(TComboBox *cbb, TEdit *edt){
        if (cbb->ItemIndex == 0) {
                return;
        } else if(edt->Text.IsEmpty()){
                ShowMessage("请填写对应费用");
                if(edt->CanFocus())
                edt->SetFocus();
                return;
        }

        char strChid[80];
   	sprintf(strChid,"%s%02d",edtCid->Text.c_str(),StrToInt(GetClassRight1(cbb->Text.c_str())));

        CString szSQL;
        szSQL = "insert into costaccounting(caid,value) values(";
        szSQL += Str2DBString(strChid);
        szSQL +=","; szSQL += Str2DBString(edt->Text.c_str());
        szSQL +=")";
        edtDebug->Text = AnsiString(szSQL);
        if(!RunSQL(dm1->Query1,szSQL))
        {
                ShowMessage("insert fail!") ;
                return;
        }
}

void TCostAccountingForm::InsertCustFreeToListView2(int row, TComboBox *pcbb,AnsiString col_value){
    if (pcbb->ItemIndex == 0){
        return;
    }

    lstView->Items->Item[row]->SubItems->Strings[charge_start_column+pcbb->ItemIndex - 1] = col_value;
}

void TCostAccountingForm::InsertCustFreeToListViewOri(int row, int pos, AnsiString col_value){
    lstView->Items->Item[row]->SubItems->Strings[pos] = col_value;
}


bool TCostAccountingForm::IsDupFree()
{

        int idx1, idx2,idx3,idx4,idx5,idx6,idx7,idx8,idx9,idx10;
        idx1 = idx2 = idx3 = idx4 = idx5 = idx6 = idx7 = idx8 = idx9 = idx10 =0;

        idx1 = cbb1->ItemIndex;
        idx2 = cbb2->ItemIndex;
        idx3 = cbb3->ItemIndex;
        idx4 = cbb4->ItemIndex;
        idx5 = cbb5->ItemIndex;
        idx6 = cbb6->ItemIndex;
        idx7 = cbb7->ItemIndex;
        idx8 = cbb8->ItemIndex;
        idx9 = cbb9->ItemIndex;
        idx10 = cbb10->ItemIndex;

        if (idx1!=0 && (idx1 == idx2 || idx1 == idx3 || idx1 == idx4 || idx1 == idx5 || idx1 == idx6 || idx1 == idx7 || idx1 == idx8 || idx1 == idx9 || idx1 == idx10) ){
             if(cbb1->CanFocus())
                cbb1->SetFocus();
             return true;
        }                                                               
        if (idx2!=0 &&(idx2 == idx3 || idx2 == idx4 || idx2 == idx5 || idx2 == idx6 || idx2 == idx7 || idx2 == idx8 || idx2 == idx9 || idx2 == idx10) ){
             if(cbb2->CanFocus())
                cbb2->SetFocus();
             return true;
        }
        if (idx3!=0 &&(idx3 == idx4 || idx3 == idx5 || idx3 == idx6 || idx3 == idx7 || idx3 == idx8 || idx3 == idx9 || idx3 == idx10)){
             if(cbb3->CanFocus())
                cbb3->SetFocus();
             return true;
        }
        if (idx4!=0 &&(idx4 == idx5 || idx4 == idx6 || idx4 == idx7 || idx4 == idx8 || idx4 == idx9 || idx4 == idx10)){
             if(cbb4->CanFocus())
                cbb4->SetFocus();
             return true;
        }
         if (idx5!=0 &&(idx5 == idx6 || idx5 == idx7 || idx5 == idx8 || idx5 == idx9 || idx5 == idx10)){
             if(cbb5->CanFocus())
                cbb5->SetFocus();
             return true;
         }
          if (idx6!=0 &&( idx6 == idx7 || idx6 == idx8 || idx6 == idx9 || idx6 == idx10)){
             if(cbb6->CanFocus())
                cbb6->SetFocus();
             return true;
          }
           if (idx7!=0 &&(idx7 == idx8 || idx7 == idx9 || idx7 == idx10)){
             if(cbb7->CanFocus())
                cbb7->SetFocus();
             return true;
           }
           if (idx8!=0 &&(idx8 == idx9 || idx8 == idx10)){
             if(cbb8->CanFocus())
                cbb8->SetFocus();
             return true;
           }
            if (idx9!=0 &&(idx9 == idx10)) {
             if(cbb9->CanFocus())
                cbb9->SetFocus();
             return true;
            }


        return false;
}
float TCostAccountingForm::getCharge(TEdit *edt)
{
        return StrToFloat(edt->Text.IsEmpty()?"0":edt->Text.c_str());
}
TComboBox *TCostAccountingForm::getCbb(int i)
{
        TComboBox *rt = NULL;
        switch(i){
                case 1:
                        rt=cbb1;
                        break;
                case 2:
                        rt=cbb2;
                        break;
                case 3:
                        rt=cbb3;
                        break;
                case 4:
                        rt=cbb4;
                        break;
                case 5:
                        rt=cbb5;
                        break;
                case 6:
                        rt=cbb6;
                        break;
                case 7:
                        rt=cbb7;
                        break;
                case 8:
                        rt=cbb8;
                        break;
                case 9:
                        rt=cbb9;
                        break;
                case 10:
                        rt=cbb10;
                        break;
                default:
                        break;

        };
        return rt;
}

TEdit *TCostAccountingForm::getEdt(int i)
{
        TEdit *rt = NULL;
        switch(i){
                case 1:
                        rt=edtCharge1;
                        break;
                case 2:
                        rt=edtCharge2;
                        break;
                case 3:
                        rt=edtCharge3;
                        break;
                case 4:
                        rt=edtCharge4;
                        break;
                case 5:
                        rt=edtCharge5;
                        break;
                case 6:
                        rt=edtCharge6;
                        break;
                case 7:
                        rt=edtCharge7;
                        break;
                case 8:
                        rt=edtCharge8;
                        break;
                case 9:
                        rt=edtCharge9;
                        break;
                case 10:
                        rt=edtCharge10;
                        break;
                default:
                        break;

        };
        return rt;
}

void TCostAccountingForm::ResetCharges(){
        cbb1->ItemIndex = 0;
        cbb2->ItemIndex = 0;
        cbb3->ItemIndex = 0;
        cbb4->ItemIndex = 0;
        cbb5->ItemIndex = 0;
        cbb6->ItemIndex =  0;
        cbb7->ItemIndex =  0;
        cbb8->ItemIndex =  0;
        cbb9->ItemIndex =  0;
        cbb10->ItemIndex =  0;

        edtCharge1->Text = "";
        edtCharge2->Text = "";
        edtCharge3->Text = "";
        edtCharge4->Text = "";
        edtCharge5->Text = "";
        edtCharge6->Text = "";
        edtCharge7->Text = "";
        edtCharge8->Text = "";
        edtCharge9->Text = "";
        edtCharge10->Text = "";
}

int TCostAccountingForm::ModCharge(){
        int rt = -1;

        if (lstView->Selected == NULL) {
                ShowMessage("未选中记录");
                return rt;
        }
        char strMsg[256],strSQL[512];
        sprintf(strMsg,"\n  确定保存上述费用吗？  \n",edtCid->Text.c_str());
        if(Application->MessageBox(strMsg,"警告",MB_YESNOCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2)!=IDYES)
                return rt;

        if (edtCid->Text.IsEmpty()){
                ShowMessage("请先填写工单号");
                return rt;
        }
        //valid check
        if (IsDupFree()) {
                ShowMessage("有重复费用项目,请检查输入");
                return rt;
        }
        //del all free
        CString szSQL;
        szSQL.Format("delete from costaccounting where caid like '%s__'",edtCid->Text.c_str());
        if(!RunSQL(dm1->Query1,szSQL))
        {
                ShowMessage("delete fail!") ;
                return rt;
        }

        //then insert new free
        InsertValue(cbb1,edtCharge1);
        InsertValue(cbb2,edtCharge2);
        InsertValue(cbb3,edtCharge3);
        InsertValue(cbb4,edtCharge4);
        InsertValue(cbb5,edtCharge5);
        InsertValue(cbb6,edtCharge6);
        InsertValue(cbb7,edtCharge7);
        InsertValue(cbb8,edtCharge8);
        InsertValue(cbb9,edtCharge9);
        InsertValue(cbb10,edtCharge10);

        //update custfree
        if (!edtBaseCost->Text.IsEmpty()) {
                szSQL.Format("update customs set basecost='%s' where cid='%s'",edtBaseCost->Text.c_str(), edtCid->Text.c_str());
                if(!RunSQL(dm1->Query1,szSQL))
                {
                        ShowMessage("update custfree fail!") ;
                        return rt;
                }
        }
        //add listview
        TListItem *pItem = lstView->Items->Add();
        pItem->Caption = edtCid->Text;
        pItem->SubItems->Add(lstView->Selected->SubItems->Strings[0]);
        pItem->SubItems->Add(lstView->Selected->SubItems->Strings[1]);
        pItem->SubItems->Add(lstView->Selected->SubItems->Strings[2]);
        pItem->SubItems->Add(lstView->Selected->SubItems->Strings[3]);
        pItem->SubItems->Add(lstView->Selected->SubItems->Strings[4]);
        pItem->SubItems->Add(lstView->Selected->SubItems->Strings[5]);
        pItem->SubItems->Add(lstView->Selected->SubItems->Strings[6]);
        pItem->SubItems->Add(lstView->Selected->SubItems->Strings[7]);
        pItem->SubItems->Add(lstView->Selected->SubItems->Strings[8]);
        pItem->SubItems->Add(lstView->Selected->SubItems->Strings[9]);



        pItem->SubItems->Add(edtBaseCost->Text);

        //init var charge column first, otherwise core in InsertCustFreeToListView2
        for(int i=0; i<gCHARGES1.GetSize(); ++i) {
                pItem->SubItems->Add("");
        }
//        pItem->SubItems->Add("");
        pItem->SubItems->Add("");

        int row = pItem->Index;        
        InsertCustFreeToListView2(row, cbb1, edtCharge1->Text);
        InsertCustFreeToListView2(row, cbb2, edtCharge2->Text);
        InsertCustFreeToListView2(row, cbb3, edtCharge3->Text);
        InsertCustFreeToListView2(row, cbb4, edtCharge4->Text);
        InsertCustFreeToListView2(row, cbb5, edtCharge5->Text);
        InsertCustFreeToListView2(row, cbb6, edtCharge6->Text);
        InsertCustFreeToListView2(row, cbb7, edtCharge7->Text);
        InsertCustFreeToListView2(row, cbb8, edtCharge8->Text);
        InsertCustFreeToListView2(row, cbb9, edtCharge9->Text);
        InsertCustFreeToListView2(row, cbb10, edtCharge10->Text);
        float total_var_charges =  getCharge(edtCharge1) + getCharge(edtCharge2) + getCharge(edtCharge3) +
            getCharge(edtCharge4) + getCharge(edtCharge5) + getCharge(edtCharge6) +
            getCharge(edtCharge7) + getCharge(edtCharge8) + getCharge(edtCharge9) +
            getCharge(edtCharge10) ;
        float total = StrToFloat(lstView->Selected->SubItems->Strings[3+1+1].c_str()) -
                        StrToFloat(lstView->Selected->SubItems->Strings[4+1+1].c_str()) -
                        total_var_charges;
                        
        lstView->Items->Item[row]->SubItems->Strings[charge_start_column+gCHARGES1.GetSize()] = FloatToStr(total);
        //delete after add
        lstView->Selected->Delete();
//        pItem->Selected = true;

        //clear input
        clearQryInput();
        lstView->ItemIndex = -1;
        lstView->Selected = NULL;
        //~
        //flush
        flushSum();
        rt = 0;
        return rt;
}

void TCostAccountingForm::ResetCtrl()
{
  if(m_enWorkState==EN_IDLE)
  {
    //lstview
    lstView->Enabled = true;
    //btn
//    btnMod->Enabled=isHasResult;
    btnMod->Enabled=false;
    btnOK->Enabled =false;
    btnCancel->Enabled=false;
    //qry panel
    for(int   i=0;i <plQry->ControlCount;i++)
    {
              plQry->Controls[i]->Enabled = true;
    }
    //charge panel
    for(int   i=0;i <plMod->ControlCount;i++)
    {
              plMod->Controls[i]->Enabled = false;
    }
  }
  else
  {
    //lstview
    lstView->Enabled = false;
    //btn
    btnMod->Enabled=false;
    btnOK->Enabled =true;
    btnCancel->Enabled=true;
    //qry panel
    for(int   i=0;i <plQry->ControlCount;i++)
    {
              plQry->Controls[i]->Enabled = false;
    }
    //charge panel
    for(int   i=0;i <plMod->ControlCount;i++)
    {
              plMod->Controls[i]->Enabled = true;
    }
  }

}
void __fastcall TCostAccountingForm::btnQueryClick(TObject *Sender)
{
        //gen date str
        unsigned short year0,month0,day0;
	dtpQryAcceptDate->DateTime.DecodeDate(&year0,&month0,&day0);
        char strDate0[80];
   	sprintf(strDate0,"%04d%02d%02d",year0,month0,day0);
        unsigned short year1,month1,day1;
	dtpQryAcceptDateEnd->DateTime.DecodeDate(&year1,&month1,&day1);
        char strDate1[80];
   	sprintf(strDate1,"%04d%02d%02d 23:59:59",year1,month1,day1);
        //~

        CString szSQL;
        //custcoms
        szSQL="select cid, cliworkid, acceptdate, client, declareid, ladingid, containerinfo, beizhu, custfree, basecost, operunit,CONVERT(varchar(10), acceptdate, 23) as ad from customs where 1=1 ";
        if (!edtCid->Text.IsEmpty()){
                szSQL +=" and cid="; szSQL += Str2DBString(edtCid->Text.c_str());
        }
        if (!edtDeclareId->Text.IsEmpty()){
                szSQL +=" and declareid="; szSQL += Str2DBString(edtDeclareId->Text.c_str());
        }
        if (!edtClient->Text.IsEmpty()){
                szSQL +=" and client like '%"; szSQL += edtClient->Text.c_str(); szSQL += "%'";
        }
        if (cbIsQryByDate->Checked) {
                szSQL += " and acceptdate between "; szSQL += Str2DBString(strDate0);
                szSQL += " and ";
                szSQL += Str2DBString(strDate1);
        }
        szSQL += " order by acceptdate";
//         edtDebug->Text =AnsiString( szSQL);
        RunSQL(dm1->Query1,szSQL,true);
        lstView->Clear();
        if (dm1->Query1->Eof){
//                isHasResult = false;
                m_enWorkState=EN_IDLE;
                ResetCtrl();
        }/* else {
                isHasResult = true;
        }     */
	while(!dm1->Query1->Eof)
	{                           
                TListItem *pItem = lstView->Items->Add();
                pItem->Caption = dm1->Query1->FieldByName("cid")->AsString;
                pItem->SubItems->Add(dm1->Query1->FieldByName("cliworkid")->AsString);
                pItem->SubItems->Add(dm1->Query1->FieldByName("ad")->AsString);
                pItem->SubItems->Add(dm1->Query1->FieldByName("operunit")->AsString);
                pItem->SubItems->Add(dm1->Query1->FieldByName("client")->AsString);
                pItem->SubItems->Add(dm1->Query1->FieldByName("declareid")->AsString);

                //qry sum_finance
                float sum_finance = 0;
                {
                        CString szSQL_Finance;
                        szSQL_Finance.Format("select sum(value) as sum_finance from finance where fid like '%s__'", dm1->Query1->FieldByName("cid")->AsString);
                        RunSQL(dm1->Query2,szSQL_Finance,true);
                        if (!dm1->Query2->Eof){
                                sum_finance = dm1->Query2->FieldByName("sum_finance")->AsFloat;
                        }
                }
                //收入 = 报关费 + 费用合计 (finance)
                float income = dm1->Query1->FieldByName("custfree")->AsFloat + sum_finance;
                //~
                pItem->SubItems->Add(FloatToStr(income));
                pItem->SubItems->Add(dm1->Query1->FieldByName("basecost")->AsString);   //报关基本成本
                pItem->SubItems->Add(dm1->Query1->FieldByName("ladingid")->AsString);
                pItem->SubItems->Add(AnsiString(getAllContainerNo(dm1->Query1->FieldByName("containerinfo")->AsString)));
                pItem->SubItems->Add(dm1->Query1->FieldByName("beizhu")->AsString);
                //init var charge column first, otherwise core in InsertCustFreeToListView2
                for(int i=0; i<gCHARGES1.GetSize(); ++i) {
                        pItem->SubItems->Add("");
                }
                pItem->SubItems->Add("");
                pItem->SubItems->Add("");

                //qry costaccounting
                int row = pItem->Index;
                //成本明细 costaccounting
                float total_costaccounting = 0;
                {
                        CString szSQL2;
                        szSQL2.Format("select  * from costaccounting, charges where chid=CAST(substring(caid, len(caid)-1,2) as int) and caid like '%s__'" \
                                        , dm1->Query1->FieldByName("cid")->AsString);
                        RunSQL(dm1->Query3,szSQL2,true);


                        for (int i=1; i<=10 && !dm1->Query3->Eof; ++i){
                                int pos = charge_start_column + cbb1->Items->IndexOf(dm1->Query3->FieldByName("chname")->AsString.c_str()) -1;  //借cbb1用
                                InsertCustFreeToListViewOri(row, pos, dm1->Query3->FieldByName("value")->AsString);
                                total_costaccounting += dm1->Query3->FieldByName("value")->AsFloat;
                                dm1->Query3->Next();
                        }
//                        lstView->Items->Item[row]->SubItems->Strings[charge_start_column+gCHARGES.GetSize()] = FloatToStr(total);

                }
                //利润 = 收入 - 报关基本成本 - 成本合计
                float total = income - dm1->Query1->FieldByName("basecost")->AsFloat - total_costaccounting;
                lstView->Items->Item[row]->SubItems->Strings[charge_start_column+gCHARGES1.GetSize()] = FloatToStr(total);
		dm1->Query1->Next();
        }
        flushSum();
        m_enWorkState=EN_IDLE;
        ResetCtrl();        
}
//---------------------------------------------------------------------------




void __fastcall TCostAccountingForm::btnDumpClick(TObject *Sender)
{
        return;
        CStringArray flg;
        for (int i=0; i<gCHARGES1.GetSize(); ++i){
                flg.Add("");
        }

        //init column header names
        int pos_pure = 0;
        for (pos_pure=0; pos_pure<charge_start_column+1-1; pos_pure++){
                lstViewPure->Columns->Items[pos_pure]->Caption = lstView->Columns->Items[pos_pure+1]->Caption;
        }
        //~
        for (int i=0; i<lstView->Items->Count; ++i) {
                for (int j=0; j<gCHARGES1.GetSize(); ++j) {
                        int pos_real = charge_start_column+j;
                    //    ShowMessage(AnsiString("[")+lstView->Items->Item[i]->SubItems->Strings[pos_real]+AnsiString("]"));
                        if (lstView->Items->Item[i]->SubItems->Strings[pos_real]!=""){
                                flg.SetAt(j, "1");
//                                lstViewPure->Columns->Items[pos_pure++]->Caption = lstView->Columns->Items[pos_real+1]->Caption;
                        }
                }
        }
       for (int j=0; j<gCHARGES1.GetSize(); ++j) {
               int pos_real = charge_start_column+j;
                if (flg.GetAt(j) == "1"){
                    lstViewPure->Columns->Items[pos_pure++]->Caption = lstView->Columns->Items[pos_real+1]->Caption;
                }
       }
        lstViewPure->Columns->Items[pos_pure++]->Caption = "合计";
        //mv data
        lstViewPure->Clear();
        edtMockDeclareid->Text = "";
        for(int i=0;i<lstView->Items->Count;i++)
        {
                 TListItem *pItem = lstViewPure->Items->Add();
//                 pItem->Caption = lstView->Items->Item[i]->Caption;
                 pItem->Caption = lstView->Items->Item[i]->SubItems->Strings[0];
//                 pItem->SubItems->Add(lstView->Items->Item[i]->SubItems->Strings[0]);
                 pItem->SubItems->Add(lstView->Items->Item[i]->SubItems->Strings[1]);
                 pItem->SubItems->Add(lstView->Items->Item[i]->SubItems->Strings[2]);
                 pItem->SubItems->Add(lstView->Items->Item[i]->SubItems->Strings[3]);
                 edtMockDeclareid->Text = lstView->Items->Item[i]->SubItems->Strings[4];
                 pItem->SubItems->Add((edtMockDeclareid->Text.Length() > 9)? edtMockDeclareid->Text.SubString(edtMockDeclareid->Text.Length()-9+1,9):edtMockDeclareid->Text);

                 pItem->SubItems->Add(lstView->Items->Item[i]->SubItems->Strings[4+1]);
                 pItem->SubItems->Add(lstView->Items->Item[i]->SubItems->Strings[5+1]);
                 pItem->SubItems->Add(lstView->Items->Item[i]->SubItems->Strings[6+1]);
                 pItem->SubItems->Add(lstView->Items->Item[i]->SubItems->Strings[7+1]);
                 pItem->SubItems->Add(lstView->Items->Item[i]->SubItems->Strings[8+1]);
//                 pItem->SubItems->Add(lstView->Items->Item[i]->SubItems->Strings[9+1]);



                 int j=0;
                 int cnt=0;
                 for (j=0; j<gCHARGES1.GetSize(); ++j) {
                         int pos_real = charge_start_column+j;
                        if (flg.GetAt(j) == ""){
                               continue;
                        }
                        pItem->SubItems->Add(lstView->Items->Item[i]->SubItems->Strings[pos_real]);
//                         lstViewPure->Items->Item[i]->SubItems->Strings[pos_real] = col_value;
                        cnt++;
                 }
                 pItem->SubItems->Add(lstView->Items->Item[i]->SubItems->Strings[charge_start_column+j]);
                 //add tail column for gen excel not to core
                 for (int t=cnt; t<26+1; ++t)
                        pItem->SubItems->Add("");
        }





  Variant vExcel,vSheet;
  int nRow,i;
  TListItem *pItem;
bool b=true;
    try
    {
	nRow=1;
        CString filename;
        filename = edtClient->Text.c_str();
        filename += "成本核算.xls";

	if(!OpenExcel(filename,vExcel,vSheet))	return;
	ListHead2Excel(lstViewPure,vSheet,nRow++);
	for(i=0;i<lstViewPure->Items->Count;i++)
        {
    	        pItem=lstViewPure->Items->Item[i];
//                if (lbGoodsPerf->Caption != "正常单"){
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
                        pItem->SubItems->Strings[14].c_str(),
                        pItem->SubItems->Strings[15].c_str(),
                        pItem->SubItems->Strings[16].c_str(),
                        pItem->SubItems->Strings[17].c_str(),
                        pItem->SubItems->Strings[18].c_str(),
                        pItem->SubItems->Strings[19].c_str(),
                        pItem->SubItems->Strings[20].c_str(),
                        pItem->SubItems->Strings[20].c_str(),
                        pItem->SubItems->Strings[21].c_str(),
                        pItem->SubItems->Strings[22].c_str(),
                        pItem->SubItems->Strings[23].c_str(),
                        pItem->SubItems->Strings[24].c_str(),
                        pItem->SubItems->Strings[25].c_str(),
                        pItem->SubItems->Strings[26].c_str(),
                        pItem->SubItems->Strings[27].c_str(),
                        pItem->SubItems->Strings[28].c_str(),
                        pItem->SubItems->Strings[29].c_str(),
                        pItem->SubItems->Strings[30].c_str(),
                        pItem->SubItems->Strings[31].c_str(),
//                        pItem->SubItems->Strings[26].c_str(),
//                        pItem->SubItems->Strings[27].c_str(),
                        NULL);


	
	}
    }
    catch(...)
    {
    }        
}
CString TCostAccountingForm::getFirstContainerNo(AnsiString c)
{
        CString rt = "";
        char cnt[10];memset(cnt,sizeof(cnt),0x00);
        char body[2048];memset(body,sizeof(body),0x00);
        sscanf(c.c_str(),"%[^|]|",cnt);
        sscanf(c.c_str(),"%*[^|]|%[^@]",body);

        char strTmp1[2048];
        memset(strTmp1,sizeof(strTmp1),0x00);
        strcpy(strTmp1,body);
        int num = StrToInt(cnt);
        for (int i =0; i<num && i<1; ++i){
                char str1[100],str2[100],str3[100],str4[100],strTmp[2048],strSealId[100];
                memset(str1,sizeof(str1),0x00);
                memset(str2,sizeof(str2),0x00);
                memset(str3,sizeof(str3),0x00);
                memset(str4,sizeof(str4),0x00);
                memset(strSealId,sizeof(strSealId),0x00);

                memset(strTmp,sizeof(strTmp),0x00);
                strcpy(strTmp,strTmp1);
                sscanf(strTmp,"%[^#]#",str1);
                sscanf(str1,"%s %s %s",str3,str4,strSealId);
                sscanf(strTmp,"%*[^#]#%[^@]",strTmp1);
//			printf("head:[%s] tail:[%s]\n", str1, strTmp1);
//			printf("bno:[%s] type:[%s]\n\n", str3, str4);
                rt = str3;
        }
        return rt;
}
//---------------------------------------------------------------------------



void TCostAccountingForm::clearQryInput(){
        edtRemark->Text = "";
        edtCid->Text = "";
        edtDeclareId->Text = "";
        edtClient->Text = "";
        cbb1->ItemIndex = -1;
        cbb2->ItemIndex = -1;
        cbb3->ItemIndex = -1;
        cbb4->ItemIndex = -1;
        cbb5->ItemIndex = -1;
        cbb6->ItemIndex = -1;
        cbb7->ItemIndex = -1;
        cbb8->ItemIndex = -1;
        cbb9->ItemIndex = -1;
        cbb10->ItemIndex = -1;
        edtCharge1->Text = "";
        edtCharge2->Text = "";
        edtCharge3->Text = "";
        edtCharge4->Text = "";
        edtCharge5->Text = "";
        edtCharge6->Text = "";
        edtCharge7->Text = "";
        edtCharge8->Text = "";
        edtCharge9->Text = "";
        edtCharge10->Text = "";
}
CString TCostAccountingForm::getAllContainerNo(AnsiString c){
        CString rt = "";
        char cnt[10];memset(cnt,sizeof(cnt),0x00);
        char body[2048];memset(body,sizeof(body),0x00);
        sscanf(c.c_str(),"%[^|]|",cnt);
        sscanf(c.c_str(),"%*[^|]|%[^@]",body);

        char strTmp1[2048];
        memset(strTmp1,sizeof(strTmp1),0x00);
        strcpy(strTmp1,body);
        int num = StrToInt(cnt);
        for (int i =0; i<num; ){
                char str1[100],str2[100],str3[100],str4[100],strTmp[2048],strSealId[100];
                memset(str1,sizeof(str1),0x00);
                memset(str2,sizeof(str2),0x00);
                memset(str3,sizeof(str3),0x00);
                memset(str4,sizeof(str4),0x00);
                memset(strSealId,sizeof(strSealId),0x00);

                memset(strTmp,sizeof(strTmp),0x00);
                strcpy(strTmp,strTmp1);
                sscanf(strTmp,"%[^#]#",str1);
                sscanf(str1,"%s %s %s",str3,str4,strSealId);
                sscanf(strTmp,"%*[^#]#%[^@]",strTmp1);
//			printf("head:[%s] tail:[%s]\n", str1, strTmp1);
//			printf("bno:[%s] type:[%s]\n\n", str3, str4);
                rt += str3;
//                rt += " | ";
                if (++i<num){
                        rt += "\r\n ";
                }
        }
        return rt;
}


void __fastcall TCostAccountingForm::Button1Click(TObject *Sender)
{
        CStringArray flg;
        for (int i=0; i<gCHARGES1.GetSize(); ++i){
                flg.Add("");
        }
        //init column header names
        int pos_pure = 0;
        lstViewPure->Columns->Items[0]->Caption = "序号";        
        for (pos_pure=0; pos_pure<charge_start_column-1; pos_pure++){//备注放最后
                lstViewPure->Columns->Items[1+pos_pure]->Caption = lstView->Columns->Items[pos_pure+1]->Caption;
        }        
        for (int i=0; i<lstView->Items->Count; ++i) {
                for (int j=0; j<gCHARGES1.GetSize(); ++j) {
                        int pos_real = charge_start_column+j;
                    //    ShowMessage(AnsiString("[")+lstView->Items->Item[i]->SubItems->Strings[pos_real]+AnsiString("]"));
                        if (lstView->Items->Item[i]->SubItems->Strings[pos_real]!=""){
                                flg.SetAt(j, "1");
//                                lstViewPure->Columns->Items[pos_pure++]->Caption = lstView->Columns->Items[pos_real+1]->Caption;
                        }
                }
        }
       for (int j=0; j<gCHARGES1.GetSize(); ++j) {
               int pos_real = charge_start_column+j;
                if (flg.GetAt(j) == "1"){
                    lstViewPure->Columns->Items[1+pos_pure++]->Caption = lstView->Columns->Items[pos_real+1]->Caption;
                }
       }
        lstViewPure->Columns->Items[1+pos_pure++]->Caption = "合计";
        lstViewPure->Columns->Items[1+pos_pure++]->Caption = "备注";
        
        //mv data
        lstViewPure->Clear();
        edtMockDeclareid->Text = "";
        for(int i=0;i<lstView->Items->Count;i++)
        {
                 TListItem *pItem = lstViewPure->Items->Add();
//                 pItem->Caption = lstView->Items->Item[i]->Caption;
                 pItem->Caption = AnsiString(i+1);
                 pItem->SubItems->Add(lstView->Items->Item[i]->SubItems->Strings[0]);
                 pItem->SubItems->Add(lstView->Items->Item[i]->SubItems->Strings[1]);
                 pItem->SubItems->Add(lstView->Items->Item[i]->SubItems->Strings[2]);
                 pItem->SubItems->Add(lstView->Items->Item[i]->SubItems->Strings[3]);
                 edtMockDeclareid->Text = lstView->Items->Item[i]->SubItems->Strings[4];
                 pItem->SubItems->Add((edtMockDeclareid->Text.Length() > 9)? edtMockDeclareid->Text.SubString(edtMockDeclareid->Text.Length()-9+1,9):edtMockDeclareid->Text);

                 pItem->SubItems->Add(lstView->Items->Item[i]->SubItems->Strings[4+1]);
                 pItem->SubItems->Add(lstView->Items->Item[i]->SubItems->Strings[5+1]);
                 pItem->SubItems->Add(lstView->Items->Item[i]->SubItems->Strings[6+1]);
                 pItem->SubItems->Add(lstView->Items->Item[i]->SubItems->Strings[7+1]);
                 int j=0;
                 int cnt=0;
                 for (j=0; j<gCHARGES1.GetSize(); ++j) {
                         int pos_real = charge_start_column+j;
                        if (flg.GetAt(j) == ""){
                               continue;
                        }
                        pItem->SubItems->Add(lstView->Items->Item[i]->SubItems->Strings[pos_real]);
//                         lstViewPure->Items->Item[i]->SubItems->Strings[pos_real] = col_value;
                        cnt++;
                 }
                 pItem->SubItems->Add(lstView->Items->Item[i]->SubItems->Strings[charge_start_column+j]);
								 pItem->SubItems->Add(lstView->Items->Item[i]->SubItems->Strings[8+1]);
                 //add tail column for gen excel not to core
                 for (int t=cnt; t<26+1; ++t)
                        pItem->SubItems->Add("");
        }                 
       //gen excel
        Variant vExcel,vWorkBook,vSheet,vRange,vBorders, vPicture;
        int iCols,iRows;
        iCols = iRows = 0;
        try{

                vExcel = Variant::CreateObject("Excel.Application");      //打开excel
                vExcel.OlePropertyGet("Workbooks").OleFunction("Add", 1); // 新增工作区
                vSheet = vExcel.OlePropertyGet("ActiveWorkbook").OlePropertyGet("Sheets", 1);//操作这个工作表
                //属性设置
                vExcel.OlePropertySet("Visible",true);
                vSheet.OlePropertyGet("Rows",++iRows).OlePropertySet("RowHeight",72);//设置指定行的高度为28
                vSheet.OlePropertyGet("Cells").OlePropertySet("WrapText", true);//设置所有单元格的文本自动换行
                vSheet.OlePropertyGet("Columns").OlePropertySet("ColumnWidth",15);//设置所有列的列宽为28


                //添加表体图片
                AnsiString strPic = "d:\\p1.jpg";
                vPicture = vSheet.OlePropertyGet( "Pictures").OleFunction( "Insert",strPic.c_str());
                vPicture.OlePropertySet("Left", 50);
                vPicture.OlePropertySet("Top", 10);
                
                //列名
//                Insert2Excel(vSheet, ++iRows, );
                ++iRows;
                for (int i=0; i<lstViewPure->Columns->Count; ++i){
                //lstViewPure->Columns->Items[i]->Caption
                        vSheet.OlePropertyGet("Cells",iRows,i+1).OlePropertySet("Value",lstViewPure->Columns->Items[i]->Caption.c_str());
                }                        

                //数据
            TListItem *pItem;
            for(int i=0;i<lstViewPure->Items->Count;i++)
            {
                ++iRows;
                iCols = 0;
    	        	pItem=lstViewPure->Items->Item[i];
//                if (lbGoodsPerf->Caption != "正常单"){					
                vSheet.OlePropertyGet("Cells",iRows,1).OlePropertySet("Value",pItem->Caption.c_str());
                for (int i=1; i<lstViewPure->Columns->Count; ++i){
                        vSheet.OlePropertyGet("Cells",iRows,i+1).OlePropertySet("Value",pItem->SubItems->Strings[i-1].c_str());
                }
           }        
                //加框
//                AnsiString strRange = "A"+IntToStr(2)+":"+AnsiString(NumbertoString(lstViewPure->Columns->Count+1))+IntToStr(iRows);
                AnsiString strRange = "A"+IntToStr(2)+":"+AnsiString(NumbertoString(1+pos_pure))+IntToStr(iRows);
                vRange = vSheet.OlePropertyGet("Range",strRange.c_str());
                vRange.OlePropertySet("VerticalAlignment", 3);
                vRange.OlePropertySet("HorizontalAlignment", 3);
                vBorders = vRange.OlePropertyGet("Borders");
                vBorders.OlePropertySet("linestyle",xlContinuous);
                vBorders.OlePropertySet("weight",xlThin);
                vBorders.OlePropertySet("colorindex",xlAutomatic);

                //账号信息
                /////////////////////////////////////////////////////////////////////////////////////
                ++iRows;
                ++iRows;

                AnsiString strRange1="A"+AnsiString(iRows)+":D"+AnsiString(iRows);
                vRange=vSheet.OlePropertyGet( "Range", strRange1.c_str());
                vRange.OleProcedure("Select");
                vRange.OleFunction( "Merge",   true);
                 vSheet.OlePropertyGet("Rows",iRows).OlePropertySet("RowHeight",72);//设置指定行的高度为28
                AnsiString strAccount1 = "账号：4758 5020 1880 8049 23\r\n \
开户行：中国银行广州市茶窖支行\r\n \
户名：邱亚才";

                vSheet.OlePropertyGet("Cells",iRows,1).OlePropertySet("Value",strAccount1.c_str());
                /////////////////////////////////////////////////////////////////////////////////////
                ++iRows;
                ++iRows;

                strRange1="A"+AnsiString(iRows)+":D"+AnsiString(iRows);
                vRange=vSheet.OlePropertyGet( "Range", strRange1.c_str());
                vRange.OleProcedure("Select");
                vRange.OleFunction( "Merge",   true);
                 vSheet.OlePropertyGet("Rows",iRows).OlePropertySet("RowHeight",72);//设置指定行的高度为28
                strAccount1 = "账号：6228 4800 8389 9556 910\r\n \
开户行：农行番禺德安支行\r\n \
户名：屈艳仟";
                vSheet.OlePropertyGet("Cells",iRows,1).OlePropertySet("Value",strAccount1.c_str());
                
                /////////////////////////////////////////////////////////////////////////////////////
                ++iRows;
                ++iRows;

                strRange1="A"+AnsiString(iRows)+":D"+AnsiString(iRows);
                vRange=vSheet.OlePropertyGet( "Range", strRange1.c_str());
                vRange.OleProcedure("Select");
                vRange.OleFunction( "Merge",   true);
                 vSheet.OlePropertyGet("Rows",iRows).OlePropertySet("RowHeight",72);//设置指定行的高度为28
                strAccount1 ="账号：3602 0242 0100 0738 803\r\n \
开户行：工行万丰支行 \r\n \
户名：蒙赤勇";
                vSheet.OlePropertyGet("Cells",iRows,1).OlePropertySet("Value",strAccount1.c_str());
                /////////////////////////////////////////////////////////////////////////////////////


        }catch(...){
        }           
                                
}
//---------------------------------------------------------------------------

void TCostAccountingForm::flushSum(){
      TListItem *pItem;
        double totalIn = 0;
        double totalBase=0;
        double totalPure=0;

        int i=0;
        for(i=0;i<lstView->Items->Count;i++)
        {
                pItem=lstView->Items->Item[i];
                totalIn += StrToFloat(pItem->SubItems->Strings[5]);
//                totalBase += StrToFloat(pItem->SubItems->Strings[6]);
                totalPure += StrToFloat(pItem->SubItems->Strings[lstView->Columns->Count-2]);
        }

        edtIn->Text = totalIn;
        edtBase->Text = totalIn -totalPure;
        edtPure->Text = totalPure;
}





