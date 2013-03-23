//---------------------------------------------------------------------------
#include <map>
#include <vcl.h>
#pragma hdrstop

#include "Operation.h"
#include "LdyInterface.h"
#include "common.hpp"
#include "DataModule.h"
#include "BaseCode.h"
#include "const.h"
#include <assert>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "trayicon"
#pragma resource "*.dfm"
TOperationForm *OperationForm;
#define D_IN_MONEY_COLUMN 3
#define D_OUT_MONEY_COLUMN 4
#define D_NOT_ARRIVAL_DATE "2099-12-29"

//---------------------------------------------------------------------------
void Operation(int nAuth)
{
//  CALL_FORM(TOperationForm)
        TOperationForm *pForm;
	try
	{
  	        pForm=new TOperationForm(Application);
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
__fastcall TOperationForm::TOperationForm(TComponent* Owner)
        : TForm(Owner)
{
//        m_v_cl_short_names.clear();
        m_enWorkState=EN_IDLE;
        m_mInType.clear();
        m_mInDetailBefore.clear();
        m_mOutType.clear();
        m_mOutDetailBefore.clear();
}

void showmap(AnsiString info, money_t &m){
        for(money_t::iterator it = m.begin(); it!=m.end(); ++it){
                CString sz = "";
                sz.Format(" id-type-num-unit: %d-%s-%d-%s", it->second.id, it->first, it->second.num, it->second.unit.c_str());
                ShowMessage(info+AnsiString(sz));
        }
}
CString genMoneyId(AnsiString oid, int mid){
        char rt[20];
        memset(rt, 0x00, sizeof(rt));
   	sprintf(rt,"%s%02d", oid.c_str(), mid);
        return rt;
}
//---------------------------------------------------------------------------
void TOperationForm::clearInput(){
	edtOId->Text = "";
	edtInValue->Text = "";
	edtVolume->Text = "";
	edtNetWeight->Text = "";
	edtNum->Text = "";
	edtLoadingId->Text = "";
	cbbGoodsDst->Text = "";
	cbbGoodsSrc->Text = "";
	cbbWay->Text = "";
        cbbWay0->Text = "";
	cbbGoodsName->Text = "";
	cbbClShortName->Text = "";
	cbbOpCodeSl->Text = "";
	cbbInType->Text = "";
        cbbInWayCalc->Text = "";
	cbbOutType->Text = "";
        cbbOutWayCalc->Text = "";        
        cbbOutWayCalc->Text = "";
	edtOutValue->Text = "";
        cbbSpName->Text = "";
        lvInDetail->Clear();
        lvOutDetail->Clear();
        SetDateTimePicketNow(dtpArrival);
        SetDateTimePicketNow(dtpCondIn);
        SetDateTimePicketNow(dtpCondKB);


}
int TOperationForm::get_way_type(TComboBox *cbb){
        if (cbb->Text == "快递"){
                return E_WAY_QICK;
        } else if (cbb->Text == "空运"){
                return E_WAY_AIR;
        } else {
                return E_WAY_EMPTY;
        }
}
bool TOperationForm::checkInput(){
        bool rt = true;
        if (
        	edtOId->Text.IsEmpty() ||
	edtVolume->Text.IsEmpty() ||
	edtNetWeight->Text.IsEmpty() ||
	edtNum->Text.IsEmpty() ||
//	edtLoadingId->Text.IsEmpty() ||
	cbbGoodsDst->Text.IsEmpty() ||
	cbbGoodsSrc->Text.IsEmpty() ||
//	cbbWay->Text.IsEmpty() ||
        cbbWay0->Text.IsEmpty() ||
	cbbGoodsName->Text.IsEmpty() ||
	cbbClShortName->Text.IsEmpty() ||
	cbbOpCodeSl->Text.IsEmpty()
        ) {
                rt = false;
          }
//          ShowMessage(AnsiString(get_way_type(cbbWay0)));
          if (E_WAY_EMPTY != get_way_type(cbbWay0)){
                if (cbbWay->Text.IsEmpty()){
                        rt = false;
                }
          }
        if (!checkValidGoodsSrc(cbbGoodsDst->Text)){
                ShowMessage("目的地输入有误！");
                rt = false;
        }
        return rt;
}
  /*
void TOperationForm::flushCbbClShortName(const std::vector<AnsiString> &names){
        for (std::vector<AnsiString>::const_iterator it=names.begin(); it!=names.end(); ++it){
                cbbClShortName->Items->Add(*it);
        }
}
*/

void __fastcall TOperationForm::FormShow(TObject *Sender)
{
//        m_v_cl_short_names.clear();
        clearInput();
        CString szSQL = "";
        //load base data
        //slname       - 加载全部销售
        szSQL.Format("select op_code from operator where op_class='%d'", E_OPERATOR_TYPE_SALER);
        RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
                cbbOpCodeSl->Items->Add(dm1->Query1->FieldByName("op_code")->AsString);
                dm1->Query1->Next();
        }
        //cl_shortname
/*
        szSQL.Format("select short_name from client");
        RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
                cbbClShortName->Items->Add(dm1->Query1->FieldByName("short_name")->AsString);
                cbbQryClShortName->Items->Add(dm1->Query1->FieldByName("short_name")->AsString);

                dm1->Query1->Next();
        }
*/
        //add dynamic
        cbbClShortName->Clear();
        //way
        szSQL.Format("select way_name from dic_way");
        RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
                cbbWay->Items->Add(dm1->Query1->FieldByName("way_name")->AsString);
                dm1->Query1->Next();
        }
        //src
/*
        szSQL.Format("select src_name from dic_goods_src");
        RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
                cbbGoodsSrc->Items->Add(dm1->Query1->FieldByName("src_name")->AsString);
                cbbQryGoodsSrc->Items->Add(dm1->Query1->FieldByName("src_name")->AsString);

                dm1->Query1->Next();
        }
*/
        refresh_dic_goods_src();
        //dst
        szSQL.Format("select dst_name from dic_goods_dst");
        RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
                cbbGoodsDst->Items->Add(dm1->Query1->FieldByName("dst_name")->AsString);
                dm1->Query1->Next();
        }
        //m_mInType
        szSQL.Format("select itid, name, way_calc from dic_in_type");
        RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
                AnsiString name = dm1->Query1->FieldByName("name")->AsString;
                int id = dm1->Query1->FieldByName("itid")->AsInteger;
                cbbInType->Items->Add(name);
//                cbbInWayCalc->Items->Add(dm1->Query1->FieldByName("way_calc")->AsString);
                m_mInType.insert(std::make_pair(name, id));
                dm1->Query1->Next();
        }
        //m_mOutType
        szSQL.Format("select otid, name, way_calc from dic_out_type");
        RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
                AnsiString name = dm1->Query1->FieldByName("name")->AsString;
                int id = dm1->Query1->FieldByName("otid")->AsInteger; 
//                cbbOutWayCalc->Items->Add(dm1->Query1->FieldByName("way_calc")->AsString);
                cbbOutType->Items->Add(name);
                m_mOutType.insert(std::make_pair(name, id));
                dm1->Query1->Next();
        }
        //supplier
        szSQL.Format("select name from supplier");
        RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
                cbbSpName->Items->Add(dm1->Query1->FieldByName("name")->AsString);
                dm1->Query1->Next();
        }
        //goods
        refresh_goods();

        
        //qry area
/*
        TDateTime tNow=TDateTime::CurrentDateTime();
        dtpQryDateBegin->DateTime=tNow;
        dtpQryDateEnd->DateTime=tNow;
*/

        SetDateTimePicketNow(dtpCondIn);
        SetDateTimePicketNow(dtpCondKB);
        SetDateTimePicketNow(dtpArrival);
        //~
        lvOpDetail->Clear();
        m_enWorkState = EN_IDLE;
        ResetCtrl();

}
//---------------------------------------------------------------------------

void TOperationForm::ResetCtrl(){
  bool bAuth = m_nAuthor>=AUTH_FULL;
  if(m_enWorkState==EN_IDLE)
  {
    bool isSelected = (lvOpDetail->Selected!=NULL);
//    lvOpDetail->Enabled = true;
    lvOpDetail->RowSelect = true;
    //btn
    btnAdd->Enabled = true && bAuth;
    btnMod->Enabled = isSelected && bAuth;
    btnDel->Enabled = isSelected && bAuth;
    btnOK->Enabled  = false;
    btnCancel->Enabled = false;
    //input area -> all false
    enablePlCtrl(plInput, false);
    //qry area -> true :: TODO
//    enablePlCtrl(plQuery, true);
    btnQry->Enabled = true;
  }
  else
  {
    //btn
    btnAdd->Enabled = false;
    btnMod->Enabled = false;
    btnDel->Enabled = false;
    btnCancel->Enabled=true;
    btnOK->Enabled  = true;
    //lstview
//    lvOpDetail->Enabled = false;
    lvOpDetail->RowSelect = false;      //not allow select, but enable, can see all informations
    //input area ->true
    enablePlCtrl(plInput, true);
    //some especial
    edtOId->Enabled = m_enWorkState==EN_ADDNEW;
    //TODO: qry area ->false
//    enablePlCtrl(plQuery, false);
    btnQry->Enabled = false;
  }
  //special
//  cbbInWayCalc->Enabled = false;
//  cbbOutWayCalc->Enabled = false;

}

void __fastcall TOperationForm::lvInDetailSelectItem(TObject *Sender,
      TListItem *Item, bool Selected)
{
        cbbInType->ItemIndex = cbbInType->Items->IndexOf(Item->Caption);
        cbbInWayCalc->ItemIndex = cbbInWayCalc->Items->IndexOf(Item->SubItems->Strings[2]);        
//        cbbInTypeChange(Sender);
        edtInValue->Text     = Item->SubItems->Strings[0];
        edtInUnitPrice->Text     = Item->SubItems->Strings[1];

}
//---------------------------------------------------------------------------

void __fastcall TOperationForm::btnAddClick(TObject *Sender)
{
        lvOpDetail->Clear();
        clearInput();
        refresh_goods();
        refresh_dic_goods_src();        
        loadBeforeMap();
        if(edtOId->CanFocus()) {
                edtOId->SetFocus();
        }
        m_enWorkState = EN_ADDNEW;
        ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TOperationForm::btnModClick(TObject *Sender)
{
  m_enWorkState = EN_EDIT;
  loadBeforeMap();
  ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TOperationForm::btnDelClick(TObject *Sender)
{
        char strMsg[256],strSQL[512];
        sprintf(strMsg,"\n  真要删除编号为“%s”的记录吗？  \n", edtOId->Text.c_str());
        if(Application->MessageBox(strMsg,"警告",MB_YESNOCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2)!=IDYES)
                return;
        //construct sqls
        CString szSQL = "";
        sql_t sqls;
        sqls.clear();
        //opeartion
        szSQL.Format("delete operation where oid='%s'", edtOId->Text);
        sqls.push_back(szSQL);
        //in&out
        szSQL.Format("delete detail_in where diid like '%s__'", edtOId->Text);
        sqls.push_back(szSQL);
        szSQL.Format("delete detail_out where doid like '%s__'", edtOId->Text);
        sqls.push_back(szSQL);
        //run
        int rt = batchRunSQL(sqls);
        if (rt == -1){
                ShowMessage("删除失败");
                return ;
        }
        //refresh
        TListItem *pItem = lvOpDetail->Selected;
        if(pItem!=NULL)
        {
                int nSel = lvOpDetail->Items->IndexOf(pItem);
                lvOpDetail->Items->Delete(nSel);
                lvOpDetail->Selected = NULL;
        }
        clearInput();
}
//---------------------------------------------------------------------------

void __fastcall TOperationForm::btnOKClick(TObject *Sender)
{
  char strName[80],*ptr,strTemp[80];
  int nState;
  int oldState = m_enWorkState;
  switch(m_enWorkState)
  {
    case EN_ADDNEW:
      if (-1 == onAdd(Sender))
        return;
      break;
    case EN_EDIT:
       onMod(Sender);
      break;
    default:
      ShowMessage("Work State not AddNew or Edit");
      return;
  }
  TListItem *pItem;
  if(m_enWorkState==EN_ADDNEW)
  {
//     pItem=lstViewdown->Items->Add();
//    pItem->Caption=edtName->Text;
//    lstViewdown->Selected=pItem;
  }
  else if(m_enWorkState==EN_EDIT)
  {
//        refreshMod();
  }
  m_enWorkState = EN_IDLE;
  ResetCtrl();
  btnMod->Enabled=false;
  btnDel->Enabled=false;
  if(oldState==EN_EDIT){
    lvOpDetail->Selected=NULL;
  }

}
//---------------------------------------------------------------------------
void TOperationForm::onMod(TObject *Sender){
        //valid check(empty check)
        if (!checkInput())
        {
                ShowMessage("输入信息不全");
                return ;
        }
        //comfirm
        char strMsg[256],strSQL[512];
        sprintf(strMsg,"\n  真要修改编号为“%s”的记录吗？  \n", edtOId->Text.c_str());
        if(Application->MessageBox(strMsg,"警告",MB_YESNOCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2)!=IDYES){
                return;
        }
        if (!addDicGoodsSrc(cbbGoodsSrc->Text)){
                return;
        }        
        //construct sqls
        CString szSQL = "";
        sql_t sqls;
        sqls.clear();
        //operation
        szSQL.Format("update operation set \
                        op_code_sl='%s',  cl_shortname='%s',  goods_name='%s',  \
                        loadingid='%s',  way='%s', way0='%s', goods_src='%s',  goods_dst='%s',  num='%s',  \
                        netweight='%s',  volume='%s', is_arrival=%d, date_arrival='%s' where oid='%s'", \
                     cbbOpCodeSl->Text,   cbbClShortName->Text, cbbGoodsName->Text,\
                     (getByEdt(edtLoadingId)).c_str(), /*cbbWay->Text*/ get_way_type(cbbWay0)!=E_WAY_EMPTY ? cbbWay->Text.c_str():getByEdt(edtWayOther).c_str(), cbbWay0->Text, cbbGoodsSrc->Text, cbbGoodsDst->Text, edtNum->Text, \
                     edtNetWeight->Text, edtVolume->Text, cbbIsArrival->Text=="Y"?1:0, GetDate(dtpArrival), edtOId->Text);
        sqls.push_back(szSQL);
        //in&out
        genMoneySql(sqls, edtOId->Text);
        //run
        if (-1 == batchRunSQL(sqls)){
                ShowMessage("修改失败");
                return;
        }
        //refresh
        TListItem *pItem  = lvOpDetail->Selected;
        Editor2RowUpdate(pItem);
        refresh_dic_goods_src();        
        return;
}
void TOperationForm::Editor2RowAdd(TListItem *pItem){
        if(pItem==NULL)
                return;
//        pItem->Caption = edtOId->Text;
        pItem->Caption = DateToStr(Now());
	pItem->SubItems->Add(edtOId->Text);
	pItem->SubItems->Add(cbbOpCodeSl->Text);
	pItem->SubItems->Add(cbbClShortName->Text);
	pItem->SubItems->Add(cbbGoodsName->Text);
	pItem->SubItems->Add(edtLoadingId->Text); ;
	pItem->SubItems->Add(cbbWay0->Text);
	pItem->SubItems->Add(cbbWay->Text);
	pItem->SubItems->Add(cbbGoodsSrc->Text);
	pItem->SubItems->Add(cbbGoodsDst->Text);
	pItem->SubItems->Add(edtNum->Text);
	pItem->SubItems->Add(edtNetWeight->Text);
	pItem->SubItems->Add(edtVolume->Text);
        pItem->SubItems->Add(g_theOperator.op_code);
        pItem->SubItems->Add(cbbIsArrival->Text);
        pItem->SubItems->Add(cbbIsArrival->Text=="Y"?AnsiString(GetDate(dtpArrival)):AnsiString(D_NOT_ARRIVAL_DATE));
        pItem->SubItems->Add("");
        pItem->SubItems->Add("");
        pItem->SubItems->Add("");
        pItem->SubItems->Add("");
        pItem->SubItems->Add("");
        pItem->SubItems->Add("");
        pItem->SubItems->Add("");
        pItem->SubItems->Add("");


}
void TOperationForm::Editor2RowUpdate(TListItem *pItem){
        if(pItem==NULL)
                return;
//        pItem->Caption = ;    //操作日期=接单日期，不改
        int i = 0;
	pItem->SubItems->Strings[i++] = edtOId->Text;
	pItem->SubItems->Strings[i++] = cbbOpCodeSl->Text;
	pItem->SubItems->Strings[i++] = cbbClShortName->Text;
	pItem->SubItems->Strings[i++] = cbbGoodsName->Text;
	pItem->SubItems->Strings[i++] = edtLoadingId->Text;
	pItem->SubItems->Strings[i++] = cbbWay0->Text;
        if (E_WAY_EMPTY!=get_way_type(cbbWay0)){
        	pItem->SubItems->Strings[i++] = cbbWay->Text;
        }else{
        	pItem->SubItems->Strings[i++] = edtWayOther->Text;
        }
//	pItem->SubItems->Strings[i++] = cbbWay->Text;
	pItem->SubItems->Strings[i++] = cbbGoodsSrc->Text;
	pItem->SubItems->Strings[i++] = cbbGoodsDst->Text;
	pItem->SubItems->Strings[i++] = edtNum->Text;
	pItem->SubItems->Strings[i++] = edtNetWeight->Text;
	pItem->SubItems->Strings[i++] = edtVolume->Text;
        i++;
        pItem->SubItems->Strings[i++] = cbbIsArrival->Text;
        pItem->SubItems->Strings[i++] = AnsiString(GetDate(dtpArrival));

        pItem->SubItems->Strings[18] = lbGross->Caption;
        pItem->SubItems->Strings[19] = lbGrossPect->Caption;

}



void __fastcall TOperationForm::btnCancelClick(TObject *Sender)
{
  int nState;

  nState = m_enWorkState;
  m_enWorkState = EN_IDLE;
  ResetCtrl();
  lvOpDetail->Selected=NULL;

  switch(nState)
  { //设置确定後的光标位置
    case EN_ADDNEW:
        if (btnAdd->CanFocus())
                btnAdd->SetFocus();
        break;
    case EN_EDIT:
        if (btnMod->CanFocus())
                btnMod->SetFocus();
        break;
    default:  break;
  }
    btnMod->Enabled=false;
    btnDel->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TOperationForm::lvOpDetailSelectItem(TObject *Sender,
      TListItem *Item, bool Selected)
{
        if (Selected!=NULL){
                Row2Editor(Item);
        }
        ResetCtrl();        
}
//---------------------------------------------------------------------------
void TOperationForm::flushMoneyDetail(AnsiString OId){
        CString szSQL = "";
        //in
/*
        szSQL.Format("select name, \
                        cnt, unitprice, \
                        way_calc \
                        from detail_in, dic_in_type \
                        where diid like '%s__' and cast(substring(diid, len(diid)-1,2) as int)  = itid", OId);
*/
        szSQL.Format("select name, \
                        cnt, unitprice, unit\
                        from detail_in, dic_in_type \
                        where diid like '%s__' and cast(substring(diid, len(diid)-1,2) as int)  = itid", OId);
        RunSQL(dm1->Query1, szSQL, true);

        lvInDetail->Clear();
        while (!dm1->Query1->Eof){
                TListItem *pItem = lvInDetail->Items->Add();
                if (pItem==NULL){
                        return;
                }
                pItem->Caption = dm1->Query1->FieldByName("name")->AsString;
        	pItem->SubItems->Add(dm1->Query1->FieldByName("cnt")->AsString);
        	pItem->SubItems->Add(dm1->Query1->FieldByName("unitprice")->AsString);
//                pItem->SubItems->Add(dm1->Query1->FieldByName("way_calc")->AsString);
                pItem->SubItems->Add(dm1->Query1->FieldByName("unit")->AsString);
                float total = StrToFloat(dm1->Query1->FieldByName("cnt")->AsString)*StrToFloat(dm1->Query1->FieldByName("unitprice")->AsString);
                pItem->SubItems->Add(total);
                dm1->Query1->Next();
        }
        lbSumIn->Caption = genSumMomey(lvInDetail, D_IN_MONEY_COLUMN);
        //out
        szSQL.Format("select name, \
                        cnt, \
                        unitprice, \
                        spid, \
                        unit \
                        from detail_out, dic_out_type where doid like '%s__' and cast(substring(doid, len(doid)-1,2) as int)  = otid", OId);
        RunSQL(dm1->Query1, szSQL, true);

        lvOutDetail->Clear();
        while (!dm1->Query1->Eof){
                TListItem *pItem = lvOutDetail->Items->Add();
                if (pItem==NULL){
                        return;
                }
                pItem->Caption = dm1->Query1->FieldByName("name")->AsString;
        	pItem->SubItems->Add(dm1->Query1->FieldByName("cnt")->AsString);
        	pItem->SubItems->Add(dm1->Query1->FieldByName("unitprice")->AsString);                
                AnsiString spid = (g_theOperator.op_class==E_OPERATOR_TYPE_SALER)?AnsiString(""):dm1->Query1->FieldByName("spid")->AsString;//业务员不能看 《应付账单-供应商》
                pItem->SubItems->Add(spid);
                pItem->SubItems->Add(dm1->Query1->FieldByName("unit")->AsString);
                float total = StrToFloat(dm1->Query1->FieldByName("cnt")->AsString)*StrToFloat(dm1->Query1->FieldByName("unitprice")->AsString);
                pItem->SubItems->Add(total);
                dm1->Query1->Next();
        }                                     
        lbSumOut->Caption = genSumMomey(lvOutDetail, D_OUT_MONEY_COLUMN);
}

void TOperationForm::Row2Editor(TListItem *pItem){

        if(pItem==NULL)
                return;

        int i = 0;
//        edtOId->Text = pItem->Caption;
        edtOId->Text = pItem->SubItems->Strings[i++];
	locateCbbByValue(cbbOpCodeSl, pItem->SubItems->Strings[i++]);
//flush clname first
        flushCbbClShortName(cbbOpCodeSl->Text);
//~
	locateCbbByValue(cbbClShortName, pItem->SubItems->Strings[i++]);
	locateCbbByValue(cbbGoodsName, pItem->SubItems->Strings[i++]);
	edtLoadingId->Text    = pItem->SubItems->Strings[i++];
        AnsiString way_type = pItem->SubItems->Strings[i++];
        AnsiString way = pItem->SubItems->Strings[i++];
        //load type first
        locateCbbByValue(cbbWay0, way_type);
        if (E_WAY_EMPTY!=get_way_type(cbbWay0)){
        	locateCbbByValue(cbbWay, way);
        }else{
                edtWayOther->Text = way;
        }
        //then way
//	locateCbbByValue(cbbWay0, pItem->SubItems->Strings[i++]);
//	locateCbbByValue(cbbWay, pItem->SubItems->Strings[i++]);
	locateCbbByValue(cbbGoodsSrc, pItem->SubItems->Strings[i++]);
	locateCbbByValue(cbbGoodsDst, pItem->SubItems->Strings[i++]);
	edtNum->Text          = pItem->SubItems->Strings[i++];
	edtNetWeight->Text    = pItem->SubItems->Strings[i++];
	edtVolume->Text       = pItem->SubItems->Strings[i++];
//        edtOpCodeOp->Text      = pItem->SubItems->Strings[i++];
        i++;
        cbbIsArrival->Text  = pItem->SubItems->Strings[i++];
        setDtp(dtpArrival, pItem->SubItems->Strings[i++]);
        //to indetail\outdetail TODO: load every time??? (imp by cache)
        flushMoneyDetail(edtOId->Text);
        i+=3;
        lbGross->Caption = pItem->SubItems->Strings[i++];
        lbGrossPect->Caption = pItem->SubItems->Strings[i++];



}
void __fastcall TOperationForm::btnInAddClick(TObject *Sender)
{
        //valid check
        if (cbbInType->Text.IsEmpty() || edtInValue->Text.IsEmpty()|| edtInUnitPrice->Text.IsEmpty()){
                ShowMessage("请检查输入信息");
                return;
        }
        //重复费用检查
        for(int i=0; i<lvInDetail->Items->Count; i++) {
                TListItem *pItem = lvInDetail->Items->Item[i];
                if (pItem->Caption == cbbInType->Text) {
                        ShowMessage("费用已添加,请检查输入.");
                        return;
                }
        }
        //flush
	TListItem *pItem = lvInDetail->Items->Add();
        assert(pItem!=NULL);
        pItem->Caption = cbbInType->Text;
        pItem->SubItems->Add(edtInValue->Text);
        pItem->SubItems->Add(edtInUnitPrice->Text);
        pItem->SubItems->Add(cbbInWayCalc->Text);
        float total = StrToFloat(edtInValue->Text)*StrToFloat(edtInUnitPrice->Text);
        pItem->SubItems->Add(total);

        edtInValue->Text = "";
        lbSumIn->Caption = genSumMomey(lvInDetail, D_IN_MONEY_COLUMN);
        flush_lirun();        
}
//---------------------------------------------------------------------------
//只能修改金额
void __fastcall TOperationForm::btnInModClick(TObject *Sender)
{
        if(lvInDetail->Selected == NULL)
        {
                ShowMessage("请选择记录");
                return;
        }
        TListItem *pItem = lvInDetail->Selected;
        if (pItem!=NULL){
//                pItem->Caption = cbbInType->Text;
                locateCbbByValue(cbbInType, pItem->Caption);
                pItem->SubItems->Strings[0] = edtInValue->Text;
                pItem->SubItems->Strings[1] = edtInUnitPrice->Text;
                pItem->SubItems->Strings[2] = cbbInWayCalc->Text;
                float total = StrToFloat(edtInValue->Text)*StrToFloat(edtInUnitPrice->Text);
                pItem->SubItems->Strings[3] = total;
        }
        lbSumIn->Caption = genSumMomey(lvInDetail, D_IN_MONEY_COLUMN);
        flush_lirun();            
}
//---------------------------------------------------------------------------
float TOperationForm::genSumMomey(TListView *lv, int column){
        float rt = 0;
        for(int i=0; i<lv->Items->Count; i++) {
                TListItem *pItem = lv->Items->Item[i];
                rt += StrToFloat(pItem->SubItems->Strings[column]);
        }
        return rt;
}
void __fastcall TOperationForm::btnInDelClick(TObject *Sender)
{
        if(lvInDetail->Selected == NULL)
        {
                ShowMessage("请选择记录");
                return;
        }
        lvInDetail->Selected->Delete();
        lbSumIn->Caption = genSumMomey(lvInDetail, D_IN_MONEY_COLUMN);
        flush_lirun();        
}
//---------------------------------------------------------------------------
void TOperationForm::flush_lirun(){
         float lirun = StrToFloat(lbSumIn->Caption) - StrToFloat(lbSumOut->Caption);
         float in = StrToFloat(lbSumIn->Caption);
         lbGross->Caption = AnsiString(lirun);
         lbGrossPect->Caption = AnsiString(100* lirun/in);
}
void __fastcall TOperationForm::btnOutAddClick(TObject *Sender)
{
        //valid check
        if (cbbOutType->Text.IsEmpty() || edtOutValue->Text.IsEmpty() || cbbSpName->Text.IsEmpty() || edtOutUnitPrice->Text.IsEmpty()){
                ShowMessage("请检查输入信息");
                return;
        }
        //重复费用检查
        for(int i=0; i<lvOutDetail->Items->Count; i++) {
                TListItem *pItem = lvOutDetail->Items->Item[i];
                if (pItem->Caption == cbbOutType->Text) {
                        ShowMessage("费用已添加,请检查输入.");
                        return;
                }
        }
        //flush
	TListItem *pItem = lvOutDetail->Items->Add();
        assert(pItem!=NULL);
        pItem->Caption = cbbOutType->Text;
        pItem->SubItems->Add(edtOutValue->Text);
        pItem->SubItems->Add(edtOutUnitPrice->Text);
        pItem->SubItems->Add(cbbSpName->Text);
        pItem->SubItems->Add(cbbOutWayCalc->Text);

        float total = StrToFloat(edtOutValue->Text)*StrToFloat(edtOutUnitPrice->Text);
        pItem->SubItems->Add(total);
        lbSumOut->Caption = genSumMomey(lvOutDetail, D_OUT_MONEY_COLUMN);

        edtOutValue->Text = "";
        flush_lirun();
}
//---------------------------------------------------------------------------

void __fastcall TOperationForm::btnOutModClick(TObject *Sender)
{
        if(lvOutDetail->Selected == NULL)
        {
                ShowMessage("请选择记录");
                return;
        }
        TListItem *pItem = lvOutDetail->Selected;
        if (pItem!=NULL){
//                pItem->Caption = cbbInType->Text;
                locateCbbByValue(cbbOutType, pItem->Caption);
                pItem->SubItems->Strings[0] = edtOutValue->Text;
                pItem->SubItems->Strings[1] = edtOutUnitPrice->Text;
                pItem->SubItems->Strings[2] = cbbSpName->Text;
                pItem->SubItems->Strings[3] = cbbOutWayCalc->Text;
                float total = StrToFloat(edtOutValue->Text)*StrToFloat(edtOutUnitPrice->Text);
                pItem->SubItems->Strings[D_OUT_MONEY_COLUMN] = total;
        }

        lbSumOut->Caption = genSumMomey(lvOutDetail, D_OUT_MONEY_COLUMN);
        flush_lirun();       
}
//---------------------------------------------------------------------------
void __fastcall TOperationForm::btnOutDelClick(TObject *Sender)
{
        if(lvOutDetail->Selected == NULL)
        {
                ShowMessage("请选择记录");
                return;
        }
        lvOutDetail->Selected->Delete();
        lbSumOut->Caption = genSumMomey(lvOutDetail, D_OUT_MONEY_COLUMN);
        flush_lirun();
}
//---------------------------------------------------------------------------
money_t TOperationForm::loadDetail2map(E_TYPE et, TListView *v){
        TListView *lv = et==E_TYPE_IN?lvInDetail:lvOutDetail;
        money_t rt;
        rt.clear();

        for(int i=0; i<lv->Items->Count; i++) {
                TListItem *pItem = lv->Items->Item[i];
                AnsiString type = pItem->Caption;
                CIdNum c;
                c.id = getIdByType(et, type);
                if (c.id == 0){
                        continue;
                }
                c.num = StrToInt(pItem->SubItems->Strings[0]);
                c.unitprice = StrToFloat(pItem->SubItems->Strings[1]);
                c.spname = et==E_TYPE_IN?AnsiString(""):pItem->SubItems->Strings[2];        //只有out时才有spname概念
                c.unit = et==E_TYPE_IN?pItem->SubItems->Strings[2]:pItem->SubItems->Strings[3];
                rt.insert(std::make_pair(type, c));
        }
        return rt;

}
int TOperationForm::getIdByType(E_TYPE et, AnsiString type){
        type_t &mt = et==E_TYPE_IN?m_mInType:m_mOutType;
        int rt = 0;
        type_t::iterator fit = mt.find(type);
        if (fit != m_mInType.end()){
                rt = fit->second;
        }

        return rt;
}
bool TOperationForm::checkValidGoodsSrc(AnsiString src){
        CString szSQL;
        //goods check - not exist , insert first
        szSQL.Format("select 1 from dic_goods_dst where dst_name='%s'", src.c_str());
        return checkDataExist(szSQL);
}


bool TOperationForm::addDicGoodsSrc(AnsiString src){
        CString szSQL;
        //goods check - not exist , insert first
        szSQL.Format("select 1 from dic_goods_src where src_name='%s'", src.c_str());
        if (!checkDataExist(szSQL)){
             szSQL.Format("insert into dic_goods_src(src_name) values('%s')", src.c_str());
             if (!RunSQL(dm1->Query1,szSQL)){
                ShowMessage("添加新发货地失败!");
                return false;
             }
        }
        return true;
}

int TOperationForm::onAdd(TObject *Sender){
        int rt = -1;
        //valid check (empty check)
        if (!checkInput())
        {
                ShowMessage("输入信息不全");
                return rt;
        }
        //key check
        CString szSQL;
        szSQL = "";
        szSQL.Format("select 1 from operation where oid='%s'", edtOId->Text);
        if (checkDataExist(szSQL)){
                ShowMessage("数据库中已有该编号的记录");
                return rt;
        }
        //goods check - not exist , insert first
        szSQL.Format("select 1 from goods where mname='%s'", cbbGoodsName->Text);
        if (!checkDataExist(szSQL)){
             szSQL.Format("insert into goods(mname) values('%s')", cbbGoodsName->Text);
             if (!RunSQL(dm1->Query1,szSQL)){
                ShowMessage("添加新货物名称失败!");
                return rt;
             }
        }
        if (!addDicGoodsSrc(cbbGoodsSrc->Text)){
                return rt;
        }
        //construct sqls
        sql_t sqls;
        sqls.clear();
        //operation
        szSQL.Format("insert into operation(\
                        oid, op_code_sl, acceptdate, cl_shortname, goods_name, \
                        loadingid, way, way0, goods_src, goods_dst, \
                        num, netweight, volume, status, op_code_op, \
                        is_arrival, date_arrival)\
                     values('%s', '%s', getdate(), '%s', '%s', \
                     '%s', '%s', '%s', '%s', '%s', \
                     '%s', '%s', '%s', '已接单', '%s', \
                     '%d', '%s')", \
                     edtOId->Text, cbbOpCodeSl->Text,   cbbClShortName->Text, cbbGoodsName->Text,\
                     (getByEdt(edtLoadingId)).c_str(), /*cbbWay->Text*/ get_way_type(cbbWay0)!=E_WAY_EMPTY ? cbbWay->Text.c_str():getByEdt(edtWayOther).c_str(), cbbWay0->Text, cbbGoodsSrc->Text.c_str(), cbbGoodsDst->Text.c_str(), edtNum->Text, \
                     edtNetWeight->Text, edtVolume->Text, g_theOperator.op_code, cbbIsArrival->Text, cbbIsArrival->Text=="Y"?GetDate(dtpArrival):CString(D_NOT_ARRIVAL_DATE));
        sqls.push_back(szSQL);
        edtDebug->Text = AnsiString(szSQL);
        //in & out
        genMoneySql(sqls, edtOId->Text);
        //run
        if (-1 == batchRunSQL(sqls)){ 
                ShowMessage("添加失败");
                return rt;
        }
        //flush show data
        TListItem *pItem = lvOpDetail->Items->Add();
        Editor2RowAdd(pItem);
        rt = 0;
        refresh_goods();
        refresh_dic_goods_src();    
        return rt;

}
void TOperationForm::genDiffMaps(money_t &mbefore, money_t &mafter, \
                                money_t &beinsert, money_t &beupdate, money_t &bedelete){
        beinsert.clear();
        beupdate.clear();
        bedelete.clear();
        //find update - maybe do nothing
        for (money_t::iterator it=mbefore.begin(); it!=mbefore.end(); ++it){
                money_t::iterator fit_update = mafter.find(it->first);
                if (fit_update != mafter.end()){
                        //maybe update
                        if (!(it->second == fit_update->second)){
                                beupdate.insert(*fit_update);
                        }

                }else{
                        //delete
                        bedelete.insert(*it);
                }
        }
        for (money_t::iterator it=mafter.begin(); it!=mafter.end(); ++it){
                money_t::iterator fit_insert = mbefore.find(it->first);
                if (fit_insert == mbefore.end()){
                        beinsert.insert(*it);
                }
        }
//        showmap("i", beinsert);
//        showmap("u", beupdate);
//        showmap("d", bedelete);
        //find insert

}


void TOperationForm::loadBeforeMap(){
        m_mInDetailBefore = loadDetail2map(E_TYPE_IN, lvInDetail);
        m_mOutDetailBefore = loadDetail2map(E_TYPE_OUT, lvOutDetail);
}
void TOperationForm::genMoneySql(sql_t &rt, AnsiString oid){
        CString szsql="";
        //in~
        //load after map
        money_t mInDetailAfter = loadDetail2map(E_TYPE_IN, lvInDetail);
        //diff
        money_t mInInsert, mInUpdate, mInDelete;
        mInInsert.clear();
        mInUpdate.clear();
        mInDelete.clear();
        genDiffMaps(m_mInDetailBefore, mInDetailAfter, mInInsert, mInUpdate, mInDelete);
        //gensql
        //      insert
        for (money_t::iterator it=mInInsert.begin(); it!=mInInsert.end(); ++it){
                szsql.Format("insert into detail_in(diid, cnt, unitprice, unit) values('%s', %d, '%s', '%s')", \
                        genMoneyId(oid, it->second.id), it->second.num, FloatToStr(it->second.unitprice), it->second.unit.c_str());
                rt.push_back(szsql);
//                ShowMessage(AnsiString(szsql));
        }
        //      delete
        for (money_t::iterator it=mInDelete.begin(); it!=mInDelete.end(); ++it){
                szsql.Format("delete detail_in where diid='%s'", genMoneyId(oid, it->second.id));
                rt.push_back(szsql);
//                ShowMessage(AnsiString(szsql));
        }
        //      update
        for (money_t::iterator it=mInUpdate.begin(); it!=mInUpdate.end(); ++it){
                szsql.Format("update detail_in set cnt=%d, unitprice='%s', unit='%s' where diid='%s'", \
                        it->second.num, FloatToStr(it->second.unitprice), it->second.unit.c_str(), genMoneyId(oid, it->second.id));
                rt.push_back(szsql);
//                ShowMessage(AnsiString(szsql));
        }
        //out~
        //load after map
        money_t mOutDetailAfter = loadDetail2map(E_TYPE_OUT, lvOutDetail);
        //diff
        money_t mOutInsert, mOutUpdate, mOutDelete;
        mOutInsert.clear();
        mOutUpdate.clear();
        mOutDelete.clear();
        genDiffMaps(m_mOutDetailBefore, mOutDetailAfter, mOutInsert, mOutUpdate, mOutDelete);
        //gensql
        //      insert
        for (money_t::iterator it=mOutInsert.begin(); it!=mOutInsert.end(); ++it){
                szsql.Format("insert into detail_out(doid, cnt, unitprice, spid, unit) values('%s', %d, '%s', '%s', '%s')", \
                                genMoneyId(oid, it->second.id), it->second.num, FloatToStr(it->second.unitprice), it->second.spname.c_str(), it->second.unit.c_str());
                rt.push_back(szsql);
//                ShowMessage(AnsiString(szsql));
        }
        //      delete
        for (money_t::iterator it=mOutDelete.begin(); it!=mOutDelete.end(); ++it){
                szsql.Format("delete detail_out where doid='%s'", genMoneyId(oid, it->second.id));
                rt.push_back(szsql);
//                ShowMessage(AnsiString(szsql));
        }
        //      update
        for (money_t::iterator it=mOutUpdate.begin(); it!=mOutUpdate.end(); ++it){
                szsql.Format("update detail_out set cnt=%d, unitprice='%s', spid='%s', unit='%s' where doid='%s'", \
                                it->second.num, FloatToStr(it->second.unitprice), it->second.spname.c_str(), it->second.unit.c_str(), genMoneyId(oid, it->second.id));
                rt.push_back(szsql);
//                ShowMessage(AnsiString(szsql));
        }
}




void __fastcall TOperationForm::btnQryClick(TObject *Sender)
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
        } 
        szSQL += " order by acceptdate";
        edtDebug->Text = AnsiString(szSQL);
        //run
        RunSQL(dm1->Query1, szSQL, true);
        if (dm1->Query1->Eof){
                ShowMessage("记录不存在");
        }
        //clear
        clearInput();
        lvOpDetail->Clear();
        double total_income = 0;
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

/*                pItem->SubItems->Add(in_real);//实收from rec_in
                if (in_should!=0){
                        pItem->SubItems->Add(AnsiString(in_real/in_should * 100));
                }else{
                        pItem->SubItems->Add(0);
                }
                total_income += in_real;
*/
                total_income += lirun;
 		dm1->Query1->Next();
        }
        //点击具体记录是，才刷新in_detail(out_detail);
       	ResetCtrl();
}
//---------------------------------------------------------------------------



void __fastcall TOperationForm::lvOutDetailSelectItem(TObject *Sender,
      TListItem *Item, bool Selected)
{
        locateCbbByValue(cbbOutType, Item->Caption);
        edtOutValue->Text     = Item->SubItems->Strings[0];
        edtOutUnitPrice->Text     = Item->SubItems->Strings[1];
        locateCbbByValue(cbbSpName, Item->SubItems->Strings[2]);
        locateCbbByValue(cbbOutWayCalc, Item->SubItems->Strings[3]);

        cbbOutTypeChange(Sender);        
}
//---------------------------------------------------------------------------








void TOperationForm::flushCbbClShortName(const AnsiString &op_code_sl){
/*
        if (g_theOperator.op_class<=E_OPERATOR_TYPE_MANAGER){
                return;
        }
*/
        cbbClShortName->Clear();
        CString szSQL="";
        szSQL.Format("select short_name from client where op_code_sl='%s'", op_code_sl.c_str());
        RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
                cbbClShortName->Items->Add(dm1->Query1->FieldByName("short_name")->AsString);
//                m_v_cl_short_names.push_back(dm1->Query1->FieldByName("short_name")->AsString);
                dm1->Query1->Next();
        }
}


void __fastcall TOperationForm::cbbOpCodeSlChange(TObject *Sender)
{
        flushCbbClShortName(cbbOpCodeSl->Text);
}
//---------------------------------------------------------------------------





void __fastcall TOperationForm::cbbInTypeChange(TObject *Sender)
{
//        cbbInWayCalc->ItemIndex = cbbInType->ItemIndex;
}
//---------------------------------------------------------------------------

void __fastcall TOperationForm::cbbOutTypeChange(TObject *Sender)
{
//        cbbOutWayCalc->ItemIndex = cbbOutType->ItemIndex;        
}
//---------------------------------------------------------------------------






void __fastcall TOperationForm::Button1Click(TObject *Sender)
{
         this->TrayIcon1->Minimize();        
}
//---------------------------------------------------------------------------

void TOperationForm::refresh_goods(){
        CString szSQL = "";
        szSQL.Format("select mname from goods");
        RunSQL(szSQL,true);
        cbbGoodsName->Clear();

	while(!dm1->Query1->Eof)
	{
                cbbGoodsName->Items->Add(dm1->Query1->FieldByName("mname")->AsString);
                dm1->Query1->Next();
        }
}

void TOperationForm::refresh_dic_goods_src(){
        CString szSQL = "";
        szSQL.Format("select src_name from dic_goods_src");
        RunSQL(szSQL,true);
        cbbGoodsSrc->Clear();
        cbbGoodsSrc->Items->Add("GZ");
        cbbGoodsSrc->Items->Add("HK");
        cbbGoodsSrc->Items->Add("SZ");
        cbbGoodsSrc->Items->Add("HP");

	while(!dm1->Query1->Eof)
	{
                cbbGoodsSrc->Items->Add(dm1->Query1->FieldByName("src_name")->AsString);
                dm1->Query1->Next();
        }
}

void __fastcall TOperationForm::cbbGoodsDstChange(TObject *Sender)
{
     AnsiString val = cbbGoodsDst->Text;
        if (cbbGoodsDst->Text.IsEmpty()) {
                return;
        }
        cbbGoodsDst->SelStart = AnsiString(cbbGoodsDst->Text).Length();

        CString szSQL;
	szSQL.Format("select * from dic_goods_dst where dst_name like '%%%s%%'", cbbGoodsDst->Text.c_str());
	RunSQL(dm1->Query1,szSQL,true);
        if (!dm1->Query1->Eof){
                cbbGoodsDst->Items->Clear();
                cbbGoodsDst->SelLength = 255;
                cbbGoodsDst->SelStart = 255;
        }
	while(!dm1->Query1->Eof)
	{

                cbbGoodsDst->Items->Add(dm1->Query1->FieldByName("dst_name")->AsString);
		dm1->Query1->Next();
        }
}
//---------------------------------------------------------------------------

void __fastcall TOperationForm::cbbGoodsDstSelect(TObject *Sender)
{
        int nSel = cbbGoodsDst->ItemIndex;
        if (nSel == -1)
                return;        
}
//---------------------------------------------------------------------------







void __fastcall TOperationForm::cbbWay0Change(TObject *Sender)
{
        cbbWay->Clear();
        int e_way_type;
        if (cbbWay0->Text == "快递"){
              e_way_type = E_WAY_QICK;
        } else if (cbbWay0->Text == "空运"){
              e_way_type = E_WAY_AIR;
        } else {
               return ;
        }

        CString szSQL="";
        szSQL.Format("select way_name \
                from dic_way \
                where type=%d", \
                e_way_type);
        edtDebug->Text = AnsiString(szSQL);
        RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
                cbbWay->Items->Add(dm1->Query1->FieldByName("way_name")->AsString);
                dm1->Query1->Next();
        }
}
//---------------------------------------------------------------------------











