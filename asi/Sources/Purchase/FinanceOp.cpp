//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FinanceOp.h"
#include "LdyInterface.h"
#include "common.hpp"
#include "DataModule.h"
#include "BaseCode.h"
#include "const.h"
#include <assert>
#include "OleExcelCom.h"
#include "Excel_2K_SRVR2.h"
#include <OleServer.hpp>
#include "const.h"
#include "fun.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "trayicon"
#pragma resource "*.dfm"
TFinanceOpForm *FinanceOpForm;
//---------------------------------------------------------------------------
void FinanceOp(int nAuth)
{
//  CALL_FORM(TFinanceOpForm)
        TFinanceOpForm *pForm;
	try
	{
  	        pForm=new TFinanceOpForm(Application);
        }
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
                return;
	}
        pForm->m_nAuthor=nAuth;        
        pForm->ShowModal();
        delete pForm;
}
__fastcall TFinanceOpForm::TFinanceOpForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TFinanceOpForm::clearInput(){
        edtInPrice->Text = "";
        edtInBank->Text  = "";
        edtCfmOpName->Text = "";
        edtOutBank->Text = "";
        edtOutMan->Text = "";
        edtKbValue->Text = "";
        edtClShortName->Text = "";
        edtOpCodeSl->Text = "";
        edtRecipient->Text = "";
        edtBank->Text = "";
        edtBankDeposit->Text = "";
        cbbIsAll->Text = "";
        edtShouldIn->Text = "";
        edtPecIn->Text = "";
        edtOutAccount->Text = "";
        edtOpCodeFi->Text = "";
}

void TFinanceOpForm::ResetCtrl(){
  bool bAuth = true;
  if(m_enWorkState==EN_IDLE)
  {
    bool isSelected = (lvOId->Selected!=NULL);
    lvOId->Enabled = true;
    //btn
//    btnAdd->Enabled = true;
/*
    btnMod->Enabled = isSelected;
    btnDel->Enabled = isSelected;
    btnOK->Enabled  = false;
    btnCancel->Enabled = false;
*/
    //input area -> all false
    enablePlCtrl(plInput, false);
    //qry area -> true :: TODO
    enablePlCtrl(plQuery, true);
  }
  else
  {
    //btn
//    btnAdd->Enabled = false;
/*
    btnMod->Enabled = false;
    btnDel->Enabled = false;
    btnCancel->Enabled=true;
    btnOK->Enabled  = true;
*/
    //lstview
    lvOId->Enabled = false;
    //input area ->true
    enablePlCtrl(plInput, true);
    //some especial
//    edtOId->Enabled = m_enWorkState==EN_ADDNEW;
    //TODO: qry area ->false
    enablePlCtrl(plQuery, false);    
  }
  //sepecial
  dtpFiDate->Enabled = false;
  cbNoDelay->Enabled = false;
  edtOpCodeSl->Enabled = false;
  cbbIsAll->Enabled = false;
  dtpOpDate->Enabled = false;

}
void __fastcall TFinanceOpForm::FormShow(TObject *Sender)
{
        clearInput();
        clearQryInput();
        SetDateTimePicketNow(dtpQryDateBegin);
        SetDateTimePicketNow(dtpQryDateEnd);
        SetDateTimePicketNow(dtpFiDate);


        //data init
        //~
        lvOId->Clear();
        m_enWorkState = EN_IDLE;
//        ResetCtrl();

  bool bWrite = m_nAuthor==2;
  btnOKIn->Enabled = bWrite;
  btnOkOut->Enabled = bWrite;
  btnOkKb->Enabled = bWrite;
}
//---------------------------------------------------------------------------









void __fastcall TFinanceOpForm::btnQryClick(TObject *Sender)
{
        //operation
        CString szSQL = "";
        szSQL = "select oid from operation where 1=1 ";
        if (!edtQryOId->Text.IsEmpty()){
                szSQL += "and oid="; szSQL += Str2DBString(edtQryOId->Text.c_str());
        }
        if (cbIsQryByDate->Checked) {
                szSQL += " and acceptdate between "; szSQL += Str2DBString(GetDate(dtpQryDateBegin));
                szSQL += " and ";
                szSQL += Str2DBString(GetTimeEnd(dtpQryDateEnd));
        }
        szSQL += " order by acceptdate";
        edtDebug->Text = AnsiString(szSQL);
        //run
        RunSQL(dm1->Query1, szSQL, true);
        if (dm1->Query1->Eof){
                ShowMessage("记录不存在");
        }
        //clear
//        clearInput();
        lvOId->Clear();

        //show
	while(!dm1->Query1->Eof)
	{
                TListItem *pItem = lvOId->Items->Add();
                pItem->Caption = dm1->Query1->FieldByName("oid")->AsString;
		dm1->Query1->Next();
        }
        //点击具体记录是，才刷新in_detail(out_detail);
//       	ResetCtrl();
}
//---------------------------------------------------------------------------
//toimp others
bool TFinanceOpForm::isInNoDelay(AnsiString settlement_cycle_type, int date_diff){
        bool rt = false;
//        ShowMessage(settlement_cycle_type + AnsiString(" ") + AnsiString(date_diff));
        if (settlement_cycle_type == D_SETTLEMENT_CYCLE_MONTH){
                rt = date_diff<30;
        }
        return rt;
}

void __fastcall TFinanceOpForm::lvOIdSelectItem(TObject *Sender,
      TListItem *Item, bool Selected)
{
        if(Selected==NULL){
                btnCompare->Enabled = false;
                btnTotalCompare->Enabled = false;
                return;
        }
        btnCompare->Enabled = true;
        btnTotalCompare->Enabled = true;
        //edt
        edtQryOId->Text = Item->Caption;
        //qry in out kb everytime :: TODO
        ////////////////////////////////////////////////////////////////////////////////////////////
        //in
        CString szSQL = "";
        //get should_in first: unit_price*cnt
        double should_in = 0;
        szSQL.Format("select sum(unitprice*cnt) as should_in \
                        from detail_in, dic_in_type \
                        where diid like '%s__'   \
                        and cast(substring(diid, len(diid)-1,2) as int)=itid", Item->Caption, Item->Caption);
        RunSQL(dm1->Query1, szSQL, true);
        if (!dm1->Query1->Eof){
                should_in = dm1->Query1->FieldByName("should_in")->AsFloat;
        }
        //in xxx
        szSQL.Format("select * from rec_in where rioid='%s'", Item->Caption);        //触发器实现记录自动生成
        //run
        RunSQL(dm1->Query1, szSQL, true);

        //show - remind:only one record!
	if(!dm1->Query1->Eof)
	{
//                TListItem *pItem = lvIn->Items->Add();
                edtShouldIn->Text = should_in;
                double in_price =  dm1->Query1->FieldByName("in_price")->AsFloat;
                edtInPrice->Text = in_price;
                edtPecIn->Text = AnsiString(in_price/should_in * 100) + "%";
                SetDateTimePicker(dtpInDate, dm1->Query1->FieldByName("in_date")->AsString);
                edtInBank->Text = dm1->Query1->FieldByName("in_bank")->AsString;
                edtCfmOpName->Text = dm1->Query1->FieldByName("cfm_opname")->AsString;
                SetDateTimePicker(dtpFiDate, dm1->Query1->FieldByName("date_fi")->AsString);
        }
        //detail_in
        lvInDetail->Clear();
        szSQL.Format("select name, cnt, way_calc \
                        from detail_in, dic_in_type \
                        where diid like '%s__' and cast(substring(diid, len(diid)-1,2) as int)  = itid", \
                        Item->Caption);
        RunSQL(szSQL, true);
        while (!dm1->Query1->Eof){
                TListItem *pItem = lvInDetail->Items->Add();
                if (pItem==NULL){
                        return;
                }
                pItem->Caption = dm1->Query1->FieldByName("name")->AsString;
        	pItem->SubItems->Add(dm1->Query1->FieldByName("cnt")->AsString);
                pItem->SubItems->Add(dm1->Query1->FieldByName("way_calc")->AsString);
                dm1->Query1->Next();
        }
        //IS DELAY
        //client.settlement_cycle
        AnsiString settlement_cycle="";
        szSQL.Format("select settlement_cycle from client, operation where oid='%s' and cl_shortname=short_name", Item->Caption);
        RunSQL(szSQL, true);
        if (!dm1->Query1->Eof){
                settlement_cycle = dm1->Query1->FieldByName("settlement_cycle")->AsString;
        }
        //
        int date_diff = 0;
        szSQL.Format("select datediff(D, date_fi, in_date) date_diff \
                        from rec_in \
                        where rioid='%s'", Item->Caption);
        RunSQL(szSQL, true);
        if (!dm1->Query1->Eof){
                date_diff = dm1->Query1->FieldByName("date_diff")->AsInteger;
        }

        cbNoDelay->Checked = isInNoDelay(settlement_cycle, date_diff);

        ////////////////////////////////////////////////////////////////////////////////////////////
        //out
        szSQL.Format("select *,cnt*unitprice as total from detail_out, dic_out_type where doid like '%s__' and cast(substring(doid, len(doid)-1,2) as int)  = otid", \
                        Item->Caption);
       //run
        RunSQL(dm1->Query1, szSQL, true);
        //clear
//        clearInput();
        lvOut->Clear();

        //show
	while(!dm1->Query1->Eof)
	{
                TListItem *pItem = lvOut->Items->Add();
                pItem->Caption = dm1->Query1->FieldByName("doid")->AsString;
		pItem->SubItems->Add(dm1->Query1->FieldByName("is_done")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("name")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("cnt")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("total")->AsFloat);
		pItem->SubItems->Add(dm1->Query1->FieldByName("spid")->AsString);       //TODO
		pItem->SubItems->Add(dm1->Query1->FieldByName("out_date")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("out_bank")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("out_account")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("out_man")->AsString);
		dm1->Query1->Next();
        }
        /////////////////////////////////////////////////////////////////////////////////////////
        //kb - triger4initValue
        szSQL.Format("select * \
                        from detail_kb, operation \
                        where dkoid='%s' and dkoid=oid", Item->Caption);        //触发器实现记录自动生成
        //run
        RunSQL(dm1->Query1, szSQL, true);
        //clear
//        clearInput();

        //show
	if(!dm1->Query1->Eof)
	{

                edtKbValue->Text = dm1->Query1->FieldByName("kb_value")->AsString;
                edtRecipient->Text = dm1->Query1->FieldByName("recipient")->AsString;
                edtBank->Text = dm1->Query1->FieldByName("bank")->AsString;
                edtBankDeposit->Text = dm1->Query1->FieldByName("bank_deposit")->AsString;
                locateCbbByValue(cbbIsAll, edtPecIn->Text=="100%"?"是":"否");
                SetDateTimePicker(dtpKbDate, dm1->Query1->FieldByName("date")->AsString);
                SetDateTimePicker(dtpOpDate, dm1->Query1->FieldByName("date_op")->AsString);                
                edtClShortName->Text = dm1->Query1->FieldByName("cl_shortname")->AsString;
                edtOpCodeSl->Text = dm1->Query1->FieldByName("op_code_sl")->AsString;
                edtOpCodeFi->Text = dm1->Query1->FieldByName("op_code_fi")->AsString;

                locateCbbByValue(cbbIsArrival,dm1->Query1->FieldByName("is_arrival")->AsInteger==1?"是":"否" );
		dm1->Query1->Next();
        }

}
//---------------------------------------------------------------------------






void __fastcall TFinanceOpForm::btnOKInClick(TObject *Sender)
{
        if (edtQryOId->Text.IsEmpty()){
                ShowMessage("未选中相应单号");
                return;
        }
        char strMsg[256],strSQL[512];
        sprintf(strMsg,"\n  确定修改[ %s ]的应收记录记录吗？  \n", edtQryOId->Text.c_str());
        if(Application->MessageBox(strMsg,"警告",MB_YESNOCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2)!=IDYES)
                return;

        //TODO:valid check
        CString szSQL = "";
        szSQL.Format("update rec_in set in_price='%s', in_date='%s', in_bank='%s', cfm_opname='%s', date_fi=getdate() \
                        where rioid='%s'", \
                        getByEdt(edtInPrice).c_str(), GetDate(dtpInDate), getByEdt(edtInBank).c_str(), getByEdt(edtCfmOpName).c_str(), \
                        edtQryOId->Text.c_str());
        edtDebug->Text = AnsiString(szSQL);
        if(!RunSQL(dm1->Query1,szSQL))
        {
                ShowMessage("更新应收记录失败!") ;
                return;
        }
        //flush new_cli_prize
        ExecProc("pr_new_cli_prize", edtQryOId->Text);

}
//---------------------------------------------------------------------------



void __fastcall TFinanceOpForm::lvOutSelectItem(TObject *Sender,
      TListItem *Item, bool Selected)
{
        if(Selected==NULL ||Item==NULL) {
                edtOutBank->Text = "";
                edtOutAccount->Text = "";
                edtOutMan->Text = "";
                return;
        }

        int i = 0;
        cbIsDoneIn->Checked = Item->SubItems->Strings[0] == "是";
        SetDateTimePicker(dtpOutDate, Item->SubItems->Strings[4+1]);
        edtOutBank->Text = Item->SubItems->Strings[5+1];
        edtOutAccount->Text = Item->SubItems->Strings[6+1];
        edtOutMan->Text = Item->SubItems->Strings[7+1];

//        flushFinanceDetail(lvOId->Selected->Caption, lvInDetail, lvOutDetail);

}
//---------------------------------------------------------------------------


void __fastcall TFinanceOpForm::btnOkOutClick(TObject *Sender)
{
        if (lvOut->Selected == NULL){
                ShowMessage("未选中相应项目");
                return;
        }
        AnsiString oid = lvOut->Selected->Caption;
        char strMsg[256],strSQL[512];
        sprintf(strMsg,"\n  确定修改[ %s ]应付记录记录吗？  \n", oid);
        if(Application->MessageBox(strMsg,"警告",MB_YESNOCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2)!=IDYES)
                return;
        CString szSQL = "";
        szSQL.Format("update detail_out set out_date='%s', out_bank='%s', out_account='%s', out_man='%s', \
                        is_done='%s' \
                        where doid='%s'", \
                        GetDate(dtpOutDate), getByEdt(edtOutBank).c_str(), getByEdt(edtOutAccount).c_str(), getByEdt(edtOutMan).c_str(), \
                        cbIsDoneIn->Checked?"是":"否",
                        oid);
        edtDebug->Text = AnsiString(szSQL);
        if(!RunSQL(dm1->Query1,szSQL))
        {
                ShowMessage("更新应付记录失败!") ;
                return;
        }

        //flush
        Editor2RowUpdateOut(lvOut->Selected);

        //flush new cli prize
        
}
//---------------------------------------------------------------------------
void TFinanceOpForm::Editor2RowUpdateOut(TListItem *pItem){
        if(pItem==NULL)
                return;
        
	pItem->SubItems->Strings[0] = AnsiString(cbIsDoneIn->Checked?"是":"否");
	pItem->SubItems->Strings[4+1] = AnsiString(GetDate(dtpOutDate));
	pItem->SubItems->Strings[5+1] = edtOutBank->Text;
	pItem->SubItems->Strings[6+1] = edtOutAccount->Text;
	pItem->SubItems->Strings[7+1] = edtOutMan->Text;
}
void TFinanceOpForm::Row2EditorKb(TListItem *pItem){

        if(pItem==NULL)
                return;

        int i = 0;
        edtKbValue->Text = pItem->Caption;
        edtRecipient->Text = pItem->SubItems->Strings[0];
        edtBank->Text = pItem->SubItems->Strings[2];
        edtBankDeposit->Text = pItem->SubItems->Strings[3];
	locateCbbByValue(cbbIsAll, pItem->SubItems->Strings[5]);
        SetDateTimePicker(dtpKbDate, pItem->SubItems->Strings[4]);
}
void TFinanceOpForm::Editor2RowUpdateKb(TListItem *pItem){
        if(pItem==NULL)
                return;
        int pos=0;
        pItem->Caption              = edtKbValue->Text;
	pItem->SubItems->Strings[pos++] = edtRecipient->Text;
        pItem->SubItems->Strings[pos++] ;//= edtRecipent->Text;
        pItem->SubItems->Strings[pos++] = edtBank->Text;
        pItem->SubItems->Strings[pos++] = edtBankDeposit->Text;
        pItem->SubItems->Strings[pos++] = AnsiString(GetDate(dtpKbDate));
        pItem->SubItems->Strings[pos++] = cbbIsAll->Text;
}


void __fastcall TFinanceOpForm::btnOkKbClick(TObject *Sender)
{
        if (edtQryOId->Text.IsEmpty()){
                ShowMessage("未选中相应单号");
                return;
        }
        char strMsg[256],strSQL[512];
        sprintf(strMsg,"\n  确定修改[ %s ]回扣纪录记录吗？  \n", edtQryOId->Text.c_str());
        if(Application->MessageBox(strMsg,"警告",MB_YESNOCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2)!=IDYES)
                return;
        CString szSQL = "";
        szSQL.Format("update detail_kb \
                        set kb_value='%s', recipient='%s', bank='%s', bank_deposit='%s', date='%s', \
                        op_code_fi='%s', date_op=getdate() \
                        where dkoid='%s'", \
                        edtKbValue->Text.IsEmpty()?AnsiString("0"):edtKbValue->Text, getByEdt2(edtRecipient), getByEdt2(edtBank), getByEdt2(edtBankDeposit), GetDate(dtpKbDate), \
                        g_theOperator.op_code,\
                        getByEdt2(edtQryOId));
        edtDebug->Text = AnsiString(szSQL);
        if(!RunSQL(dm1->Query1,szSQL))
        {
                ShowMessage("更新回扣记录失败!") ;
                return;
        }

        //flush
//        Editor2RowUpdateKb(lvKb->Selected);        
}
//---------------------------------------------------------------------------








void __fastcall TFinanceOpForm::btnCompareClick(TObject *Sender)
{
        Variant vExcel,vWorkBook,vSheet,vRange,vBorders, vPicture;
        int iCols,iRows;
        iCols = iRows = 0;
        try{
                vExcel = Variant::CreateObject("Excel.Application");      //打开excel
                vExcel.OlePropertyGet("Workbooks").OleFunction("Add", 1); // 新增工作区
                vSheet = vExcel.OlePropertyGet("ActiveWorkbook").OlePropertyGet("Sheets", 1);//操作这个工作表
                //公共属性设置
                vExcel.OlePropertySet("Visible",true);
                vSheet.OlePropertyGet("Cells").OlePropertySet("WrapText", true);//设置所有单元格的文本自动换行
                vSheet.OlePropertyGet("Columns").OlePropertySet("ColumnWidth",15);//设置所有列的列宽为28
                //pic
                vPicture = vSheet.OlePropertyGet( "Pictures").OleFunction( "Insert","d:\\asi_tital1.jpg");
                vPicture.OlePropertySet("Left", 10);
                vPicture.OlePropertySet("Top", 5);
                vPicture = vSheet.OlePropertyGet( "Pictures").OleFunction( "Insert","d:\\asi_tital2.jpg");
                vPicture.OlePropertySet("Left", 600);
                vPicture.OlePropertySet("Top", 5);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //query head data
        AnsiString cl_shortname, link_man, tel_lk, goods_src, goods_dst, today, op_code_sl, way, num;
        CString szSQL = "";
        szSQL.Format("select cl_shortname, link_man, tel_lk, goods_src, goods_dst, \
                                getdate() today, operation.op_code_sl, way, num \
                                from operation, client where oid='%s' and cl_shortname = short_name", lvOId->Selected->Caption);
        RunSQL(dm1->Query1, szSQL, true);
        if (!dm1->Query1->Eof){
                cl_shortname = dm1->Query1->FieldByName("cl_shortname")->AsString;
                link_man = dm1->Query1->FieldByName("link_man")->AsString;
                tel_lk = dm1->Query1->FieldByName("tel_lk")->AsString;
                goods_src = dm1->Query1->FieldByName("goods_src")->AsString;
                goods_dst = dm1->Query1->FieldByName("goods_dst")->AsString;
                today = dm1->Query1->FieldByName("today")->AsString;
                op_code_sl = dm1->Query1->FieldByName("op_code_sl")->AsString;
                way = dm1->Query1->FieldByName("way")->AsString;
                num = dm1->Query1->FieldByName("num")->AsString;
        }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                OleHelper ole_helper_raw(vSheet);

                //tital 1
                ++iRows;
                {
                        OleHelper ole_helper(vSheet, "A", iRows, "H", iRows);
                        ole_helper.merge().set_row_height(30).set_font_type("楷体_GB2312").\
                                           set_font_style("加粗").set_font_size(24).set_alignment(3).\
                                           write("广州地平线货运代理有限公司");
                }

                //tital 2
                ++iRows;
                {
                        OleHelper ole_helper(vSheet, "A", iRows, "H", iRows);
                        ole_helper.merge().set_row_height(30).set_font_type("Arial Black").\
                                           set_font_style("加粗").set_font_size(14).set_alignment(3).\
                                           write("ASI  LOGISTICS CO., LTD");
                }
                //tital 3
                ++iRows;
                {
                        OleHelper ole_helper(vSheet, "A", iRows, "H", iRows);
                        ole_helper.merge().set_font_type("楷体_GB2312").\
                                           set_font_style("加粗").set_font_size(14).set_alignment(3).\
                                           write("地址：广州市白云区齐富路云逸苑E座803室  电话：020-36210305 传真：020-36210707");
                }

                //tital 4
                iRows+=2;
                {
                        OleHelper ole_helper(vSheet, "A", iRows, "H", iRows);
                        ole_helper.merge().set_row_height(30).set_font_type("Times New Roman").\
                                           set_font_style("加粗").set_font_size(14).set_alignment(3).\
                                           write("DEBIT    NOTE(对账单)");
                }

                ++iRows;
                AnsiString strValue = "DN/NO:" + edtQryOId->Text;
                ole_helper_raw.write(strValue, iRows, 5);
                {
                        OleHelper ole_helper(vSheet, "A", iRows, "H", iRows);
                        ole_helper.write_under_line();
                }
                ++iRows;
                {
                        OleHelper ole_helper(vSheet, "A", iRows, "H", iRows+5);
                        ole_helper.set_font_type("Times New Roman");
                }

                //write tag
                ole_helper_raw.write("TO:", iRows, 1);
                ole_helper_raw.write("FROM:", iRows, 5);
                ole_helper_raw.write("TEL:", iRows+1, 1);
                ole_helper_raw.write("TEL:", iRows+1, 5);
                ole_helper_raw.write("MAWB NO:", iRows+2, 1);
                ole_helper_raw.write("运输途径:", iRows+2, 5);
                ole_helper_raw.write("FROM/TO:", iRows+3, 1);
                ole_helper_raw.write("NO.OF.PKG::", iRows+3, 5);
                ole_helper_raw.write("G.W.:", iRows+4, 1);
                ole_helper_raw.write("V.W:", iRows+4, 5);
                ole_helper_raw.write("DATE:", iRows+5, 1);
                ole_helper_raw.write("C.W(计费重量):", iRows+5, 5);

                //write tag's values
                ole_helper_raw.write(cl_shortname+AnsiString(" ")+link_man, iRows, 1+1);
                ole_helper_raw.write(AnsiString("ASI/")+op_code_sl, iRows, 5+1);
                ole_helper_raw.write(tel_lk, iRows+1, 1+1);
                ole_helper_raw.write(AnsiString("    020-36210305"), iRows+1, 5+1);
//                ole_helper_raw.write("MAWB NO:", iRows+2, 1);
                ole_helper_raw.write(way, iRows+2, 5+1);
                ole_helper_raw.write(goods_src+AnsiString("-")+goods_dst, iRows+3, 1+1);
                ole_helper_raw.write(num+AnsiString("CTNS"), iRows+3, 5+1);
//                ole_helper_raw.write("G.W.:", iRows+4, 1);
//                ole_helper_raw.write(volume, iRows+4, 5+1);
                ole_helper_raw.write(today, iRows+5, 1+1);
//                ole_helper_raw.write("C.W(计费重量):", iRows+5, 5);


                iRows+=6;
                {
                        OleHelper ole_helper(vSheet, "A", iRows, "H", iRows);
                        ole_helper.write_under_line();
                }



                iRows+=2;
                //write out detail
                szSQL.Format("select name, unitprice, cnt, cnt*unitprice as total from detail_out, dic_out_type \
                                where doid like '%s__' and cast(substring(doid, len(doid)-1,2) as int)  = otid order by doid", lvOId->Selected->Caption);
                RunSQL(dm1->Query1, szSQL, true);
                int row_cnt = dm1->Query1->RecordCount;                
                for (int p=0; p<row_cnt+1; ++p){

                        {
                                OleHelper ole_helper(vSheet, "B", iRows+p, "C", iRows+p);
                                ole_helper.merge();
                        }
                        {
                                OleHelper ole_helper(vSheet, "E", iRows+p, "G", iRows+p);
                                ole_helper.merge();
                        }
                }

                {
                        OleHelper ole_helper(vSheet, "A", iRows, "H", iRows+row_cnt);
                        ole_helper.set_alignment(3).write_box();
                }
                //add title

                ole_helper_raw.write("ITEM", iRows, 1);
                ole_helper_raw.write("CHARGE DESCRIPTION", iRows, 2);
                ole_helper_raw.write("UNIT PRICE", iRows, 4);
                ole_helper_raw.write("计费数量", iRows, 5);
                ole_helper_raw.write("AMOUNT(RMB)", iRows, 8);
                iRows++;

                int pos=0;
                double sum_total = 0;
                while(!dm1->Query1->Eof){
                        ole_helper_raw.write(AnsiString(++pos), iRows, 1);
                        ole_helper_raw.write(dm1->Query1->FieldByName("name")->AsString, iRows, 2);
                        ole_helper_raw.write(dm1->Query1->FieldByName("unitprice")->AsString, iRows, 4);
                        ole_helper_raw.write(dm1->Query1->FieldByName("cnt")->AsString, iRows, 5);
                        ole_helper_raw.write(dm1->Query1->FieldByName("total")->AsString, iRows, 8);
                        sum_total += dm1->Query1->FieldByName("total")->AsFloat;
        		dm1->Query1->Next();
                        iRows++;
                }
                iRows++;
                ole_helper_raw.write("TOTAL", iRows, 1);
                ole_helper_raw.write(AnsiString(sum_total), iRows, 8);

                iRows+=2;
                {
                        OleHelper ole_helper(vSheet, "A", iRows, "H", iRows);
                        ole_helper.merge();
                }

                iRows++;
                ole_helper_raw.write("费用合计", iRows, 1).set_font_style("加粗", iRows, 1);
                ole_helper_raw.write(ConvertBigInt(sum_total), iRows, 2).set_font_style("加粗", iRows, 2);

                iRows+=4;
                {
                        OleHelper ole_helper(vSheet, "A", iRows, "C", iRows);
                        ole_helper.merge().set_font_style("加粗").write_under_line().set_alignment(xlRight).write("(签名或签章)");
                }
                iRows++;
                {
                        OleHelper ole_helper(vSheet, "A", iRows, "D", iRows);
                        ole_helper.merge().set_font_style("加粗").write("请确认以上账单信息，并承诺在约定付款期限内付款.");
                }
                {
                        OleHelper ole_helper(vSheet, "F", iRows, "H", iRows);
                        ole_helper.merge().write("FOR & ON BEHALF OF");
                }
                iRows++;
                {
                        OleHelper ole_helper(vSheet, "A", iRows, "D", iRows);
                        ole_helper.merge().write("签名或签章后回传我司：FAX:020-36210707");
                }
                {
                        OleHelper ole_helper(vSheet, "F", iRows, "H", iRows);
                        ole_helper.merge().write("广州地平线货运代理有限公司");
                }

                //

                //
                iRows+=6;
                {
                        OleHelper ole_helper(vSheet, "F", iRows, "H", iRows);
                        ole_helper.merge().write_under_line();
                }
                iRows++;
                {
                        OleHelper ole_helper(vSheet, "F", iRows, "H", iRows);
                        ole_helper.merge().write("AUTHORIZED SIGNATURE");
                }
/*
                vPicture = vSheet.OlePropertyGet( "Pictures").OleFunction( "Insert","d:\\asi_sign.jpg");
                vPicture.OlePropertySet("Left", 600);
                vPicture.OlePropertySet("Top", 500);
*/
        } catch(...){
        }
}
//---------------------------------------------------------------------------



















void __fastcall TFinanceOpForm::btnTotalCompareClick(TObject *Sender)
{
        ShowMessage("下个版本提供");
        return;        
}
//---------------------------------------------------------------------------

void  TFinanceOpForm::clearQryInput(){
        edtQryOId->Text = "";
        edtQryLoadingId->Text = "";
        edtQryOutBank->Text = "";
        edtQryOutMan->Text = "";
        cbbQryOpCodeOp->ItemIndex = -1;
        cbbQryWay->ItemIndex = -1;
        cbbQryOpCodeSl->ItemIndex = -1;
        cbbQryClShortName->ItemIndex = -1;
        cbbQrySupply->ItemIndex = -1;
        lvOId->Clear();
        lvInDetail->Clear();
//        lvOutDetail->Clear();
}





void __fastcall TFinanceOpForm::Button1Click(TObject *Sender)
{
         this->TrayIcon1->Minimize();                   
}
//---------------------------------------------------------------------------

