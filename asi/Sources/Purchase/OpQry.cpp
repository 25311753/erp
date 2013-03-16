//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "OpQry.h"
#include "OpQryInOut.cpp"
#include "LdyInterface.h"
#include "common.hpp"
#include "DataModule.h"
#include "BaseCode.h"
#include "const.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TOpQryForm *OpQryForm;

void OpQry(int nAuth)
{
  CALL_FORM(TOpQryForm)
}
//---------------------------------------------------------------------------
__fastcall TOpQryForm::TOpQryForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TOpQryForm::FormShow(TObject *Sender)
{
        edtQryLoadingId->Text = "";
        edtQryOId->Text = "";
        cbIsQryByDate->Checked = false;
        CString szSQL = "";
        //load base data
        //slname       - 加载全部销售
        szSQL.Format("select op_code from operator where op_class='%d'", E_OPERATOR_TYPE_SALER);
        RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
                cbbQryOpCodeSl->Items->Add(dm1->Query1->FieldByName("op_code")->AsString);
                dm1->Query1->Next();
        }

        //add dynamic        
        cbbQryClShortName->Clear();
        //way
        szSQL.Format("select way_name from dic_way");
        RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
                cbbQryWay->Items->Add(dm1->Query1->FieldByName("way_name")->AsString);
                dm1->Query1->Next();
        }

        //dst
        szSQL.Format("select dst_name from dic_goods_dst");
        RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
                cbbQryGoodsDst->Items->Add(dm1->Query1->FieldByName("dst_name")->AsString);
                dm1->Query1->Next();
        }

        SetDateTimePicketNow(dtpQryDateBegin);
        SetDateTimePicketNow(dtpQryDateEnd);
        
        lvOpDetail->Clear();        
}
//---------------------------------------------------------------------------
void __fastcall TOpQryForm::cbbQryOpCodeSlChange(TObject *Sender)
{
        cbbQryClShortName->Clear();
        CString szSQL="";
        szSQL.Format("select short_name from client where op_code_sl='%s'", cbbQryOpCodeSl->Text.c_str());
        RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
                cbbQryClShortName->Items->Add(dm1->Query1->FieldByName("short_name")->AsString);
                dm1->Query1->Next();
        }
}
//---------------------------------------------------------------------------
void __fastcall TOpQryForm::btnQryClick(TObject *Sender)
{
        //operation
        CString szSQL = "";
        szSQL = "select CONVERT(varchar, acceptdate, 111) acceptdate_op_date, *, dbo.get_in_should(oid) as in_should, dbo.get_out_should(oid) as out_should \
                from operation, detail_kb, rec_in \
                where 1=1 and oid=dkoid and oid=rioid ";
        if (!edtQryOId->Text.IsEmpty()){
                szSQL += " and oid="; szSQL += Str2DBString(edtQryOId->Text.c_str());
        }
        if (g_theOperator.op_class==E_OPERATOR_TYPE_SALER){
                szSQL += " and op_code_sl="; szSQL += Str2DBString(g_theOperator.op_code);
        } else if (g_theOperator.op_class==E_OPERATOR_TYPE_OPERATOR){
                szSQL += " and op_code_op="; szSQL += Str2DBString(g_theOperator.op_code);
        } else {
               if (!cbbQryOpCodeSl->Text.IsEmpty()){
                        szSQL += " and op_code_sl="; szSQL += Str2DBString(cbbQryOpCodeSl->Text.c_str());
               }
        }
        if (!cbbQryClShortName->Text.IsEmpty()){
                szSQL += " and cl_shortname="; szSQL += Str2DBString(cbbQryClShortName->Text.c_str());
        }
        if (!edtQryLoadingId->Text.IsEmpty()){
                szSQL += " and loadingid="; szSQL += Str2DBString(edtQryLoadingId->Text.c_str());
        }
        if (!cbbQryWay0->Text.IsEmpty()){
                szSQL += " and way0="; szSQL += Str2DBString(cbbQryWay0->Text.c_str());
        }
        if (!cbbQryWay->Text.IsEmpty()){
                szSQL += " and way="; szSQL += Str2DBString(cbbQryWay->Text.c_str());
        }
        if (!cbbQryGoodsSrc->Text.IsEmpty()){
                szSQL += " and goods_src="; szSQL += Str2DBString(cbbQryGoodsSrc->Text.c_str());
        }
        if (!cbbQryGoodsDst->Text.IsEmpty()){
                szSQL += " and goods_dst="; szSQL += Str2DBString(cbbQryGoodsDst->Text.c_str());
        }
        if (cbIsQryByDate->Checked) {
                szSQL += " and acceptdate between "; szSQL += Str2DBString(GetDate(dtpQryDateBegin));
                szSQL += " and ";
                szSQL += Str2DBString(GetTimeEnd(dtpQryDateEnd));
        }
        if (!cbbIsArrival->Text.IsEmpty()){
                szSQL += " and is_arrival="; szSQL += Str2DBString(cbbIsArrival->Text=="是"?"1":"0");
        }
        szSQL += " order by acceptdate";
//        edtDebug->Text = AnsiString(szSQL);
        //run
        RunSQL(dm1->Query1, szSQL, true);
        if (dm1->Query1->Eof){
                ShowMessage("记录不存在");
        }

        lvOpDetail->Clear();
        double total_income = 0;
        double total_kb = 0;
        //show
	while(!dm1->Query1->Eof)
	{

                double in_real = dm1->Query1->FieldByName("in_price")->AsFloat;
                double in_should = dm1->Query1->FieldByName("in_should")->AsFloat;
                double out_should = dm1->Query1->FieldByName("out_should")->AsFloat;

                double lirun = in_should - out_should;

                TListItem *pItem = lvOpDetail->Items->Add();
//                pItem->Caption = dm1->Query1->FieldByName("oid")->AsString;
                pItem->Caption = dm1->Query1->FieldByName("acceptdate_op_date")->AsString;
		pItem->SubItems->Add(dm1->Query1->FieldByName("oid")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("op_code_sl")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("cl_shortname")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("goods_name")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("loadingid")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("way0")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("way")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("goods_src")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("goods_dst")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("num")->AsInteger);
		pItem->SubItems->Add(dm1->Query1->FieldByName("netweight")->AsFloat);
		pItem->SubItems->Add(dm1->Query1->FieldByName("volume")->AsFloat);
		pItem->SubItems->Add(dm1->Query1->FieldByName("op_code_op")->AsString);
                pItem->SubItems->Add(dm1->Query1->FieldByName("is_arrival")->AsInteger==1?"是":"否");
                pItem->SubItems->Add(dm1->Query1->FieldByName("date_arrival")->AsString);
                pItem->SubItems->Add(in_should);
                pItem->SubItems->Add(dm1->Query1->FieldByName("out_should")->AsFloat);
                pItem->SubItems->Add(dm1->Query1->FieldByName("kb_value")->AsFloat);
                //这里的利润直接等于应收-应付, 跟后面财务实收无关, 用途不同
                pItem->SubItems->Add(lirun);
                if (in_should!=0){
                        pItem->SubItems->Add(AnsiString(lirun/in_should * 100));
                }else{
                        pItem->SubItems->Add(0);
                }

                total_income += lirun;
                total_kb += dm1->Query1->FieldByName("kb_value")->AsFloat;
 		dm1->Query1->Next();
        }
//        lbTotalOId->Caption = lvOpDetail->Items->Count;
//        lbTotalInCome->Caption = total_income;
        lbTotalCnt->Caption = lvOpDetail->Items->Count;
        lbTotalLiRun->Caption = total_income;
        lbTotalKB->Caption = total_kb;
        
}
//---------------------------------------------------------------------------


void __fastcall TOpQryForm::N31Click(TObject *Sender)
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
                                from operation, client where oid='%s' and cl_shortname = short_name", lvOpDetail->Selected->SubItems->Strings[0]);
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
                                where doid like '%s__' and cast(substring(doid, len(doid)-1,2) as int)  = otid order by doid", lvOpDetail->Selected->SubItems->Strings[0]);
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





void __fastcall TOpQryForm::lvOpDetailMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
     if(Button == mbRight)
     {
         TListItem *selItem = lvOpDetail->GetItemAt(X,Y);
         if(selItem == NULL) {
             return;
         }
         else {
            PopupMenu1->Popup(Mouse->CursorPos.x, Mouse->CursorPos.y);
         }
     }        
}
//---------------------------------------------------------------------------

void __fastcall TOpQryForm::N21Click(TObject *Sender)
{
        TOpQryInOutForm *pForm;
	try
	{
        
  	        pForm=new TOpQryInOutForm(Application);
        }
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
                return;
	}
        pForm->show(lvOpDetail->Selected->SubItems->Strings[0]);        
        pForm->ShowModal();
        delete pForm;
}
//---------------------------------------------------------------------------

