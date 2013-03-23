//---------------------------------------------------------------------------

#include <vcl.h>
#include "stdio.h"
#pragma hdrstop

#include <math.h>

#include <map>
#include "do.h"
#include "DataModule.h"
#include "BaseCode.h"
#include "LdyInterface.h"
#include "UtilString.h"
#include <assert.h>

#include "OleExcelCom.h"
#include "Excel_2K_SRVR2.h"
#include <OleServer.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "trayicon"
#pragma resource "*.dfm"
TDoForm *DoForm;
typedef struct
{
        CString strBegin;
        CString strEnd;
} PAGES;
WORD lastkey;
static CArray<PAGES,PAGES> gPAGES;
#define COL_PER_PAGE_PRN_DECLARE 5
#define COL_PER_PAGE_PRN_CONTACT 10

//单价=》总价；总价=》单价
//0-idle 1-unitprice changing 2-totalprice changing -
//为防止相互调用出现问题，采取一种排他的逻辑
static int nWhoChanging = 0;

//---------------------------------------------------------------------------
void Do(int nAuth)
{
        CALL_FORM(TDoForm);
}
__fastcall TDoForm::TDoForm(TComponent* Owner)
        : TForm(Owner)
{
        m_isSelectMname = false;
        
  m_enWorkState=EN_IDLE;
  m_enWorkStateDetail = EN_IDLE_D;
  isHasResult = false;
}
//---------------------------------------------------------------------------
static AnsiString strNowCurrency;
static AnsiString strWeightPercent = 1;
static String cstr[]={"零","壹","贰","叁","肆", "伍", "陆","柒","捌","玖"};
static String wstr[] ={ "", "", "拾", "佰", "仟", "万", "拾", "佰", "仟", "亿", "拾", "佰", "仟" };
int SplitString(TStringList *resultStringList,String splittStr,String sourceStr)
{
    resultStringList->Text = "";
    int splitterLength = splittStr.Length();
    int pos = sourceStr.Pos(splittStr);
    String tmp;
    while (pos > 0) {
        tmp = sourceStr.SubString(1, pos - 1);
        resultStringList->Add(tmp);
        sourceStr = sourceStr.SubString(pos + splitterLength, sourceStr.Length() - pos - splitterLength + 1);
        pos = sourceStr.Pos(splittStr);
    }
    resultStringList->Add(sourceStr);
    return resultStringList->Count;
}
String ConvertInt(String oldString)
{
    oldString = oldString.Trim();
    TStringList * strList = new TStringList();
    int count = SplitString(strList, ".", oldString);
    if (count == 0 || count > 2) {
        ShowMessage("数字格式不正确！");
    }
    //整数部分
    String str = strList->Strings[0];
    if (str.Length() > 12) {
        ShowMessage("数字太大，不能处理！");
    }

    //处理整数部分
    int len = str.Length();
    String tmpstr, rstr;
    rstr="";

    TReplaceFlags   rf;
    rf   <<   rfReplaceAll;
    for (int i = 1; i <= len; i++) {
        tmpstr = str.SubString(len - i + 1, 1);
        rstr = cstr[StrToInt(tmpstr)] + wstr[i] + rstr;
    }

    rstr=StringReplace(rstr, "拾零", "拾", rf);
    rstr=StringReplace(rstr, "零拾", "零", rf);
    rstr=StringReplace(rstr, "零佰", "零", rf);
    rstr=StringReplace(rstr, "零仟", "零", rf);
    rstr=StringReplace(rstr, "零万", "万", rf);
    for (int i = 1; i <= 6; i++) {
        rstr = StringReplace(rstr, "零零", "零", rf);
    }
    rstr=StringReplace(rstr, "零万", "零", rf);
    rstr = StringReplace(rstr, "零亿", "亿", rf);
    rstr=StringReplace(rstr, "零零", "零", rf);
    rstr+="圆";

        //小数部分
    if (count == 2) {
        String strXiaoshu = strList->Strings[1];
        int xiaoshuLength = strXiaoshu.Length();
        if (xiaoshuLength == 1) {
            rstr += cstr[StrToInt(strXiaoshu)] + "角";
        } else if (xiaoshuLength >= 2 ) {
            rstr += cstr[StrToInt(strXiaoshu[1])] + "角" + cstr[StrToInt(strXiaoshu[2])] + "分";;
        } else if  (xiaoshuLength == 0) {
            rstr += "整";
        }
    }
    return rstr;
}
String ConvertInt2(String oldString)
{
    oldString = oldString.Trim();
    TStringList * strList = new TStringList();
    int count = SplitString(strList, ".", oldString);
    if (count == 0 || count > 2) {
        ShowMessage("数字格式不正确！");
    }
    //整数部分
    String str = strList->Strings[0];
    if (str.Length() > 12) {
        ShowMessage("数字太大，不能处理！");
    }

    //处理整数部分
    int len = str.Length();
    String tmpstr, rstr;
    rstr="";

    TReplaceFlags   rf;
    rf   <<   rfReplaceAll;
    for (int i = 1; i <= len; i++) {
        tmpstr = str.SubString(len - i + 1, 1);
        rstr = cstr[StrToInt(tmpstr)] + wstr[i] + rstr;
    }

    rstr=StringReplace(rstr, "拾零", "拾", rf);
    rstr=StringReplace(rstr, "零拾", "零", rf);
    rstr=StringReplace(rstr, "零佰", "零", rf);
    rstr=StringReplace(rstr, "零仟", "零", rf);
    rstr=StringReplace(rstr, "零万", "万", rf);
    for (int i = 1; i <= 6; i++) {
        rstr = StringReplace(rstr, "零零", "零", rf);
    }
    rstr=StringReplace(rstr, "零万", "零", rf);
    rstr = StringReplace(rstr, "零亿", "亿", rf);
    rstr=StringReplace(rstr, "零零", "零", rf);
    return rstr;
}
CString toValidStr(CString s){
        CString rt = " ";
        if (!s.IsEmpty()){
                rt = s;
        }
        return rt;
}
#include "Goods.h"
void __fastcall TDoForm::btnInputGoodsClick(TObject *Sender)
{
/*
	TGoodsForm *pG;
	pG=new TGoodsForm(this);
	assert(pG!=NULL);
	pG->ShowModal();
        //if(pG->ShowModal()==mrOk)
	{
		cbbMname->Text = pG->m_szMname;
		edtMid->Text = pG->m_szMid;
                edtSpec->Text = pG->m_szSpec;
		edtFirstmeasunit->Text = pG->m_szFirstmeasunit;
		edtSecondmeasunit->Text = pG->m_szSecondmeasunit;
		edtUnitprice->Text = pG->m_szUnitprice;

	}
	delete pG;
*/
}
//---------------------------------------------------------------------------


void __fastcall TDoForm::FormShow(TObject *Sender)
{
        //init sh
        m_sa_sh.Add("EVEN NEGOCE CO. LTD.");
        m_sa_sh.Add("El Mohandis Paints");
        m_sa_sh.Add("FERREIRA BROS PAULO");
        m_sa_sh.Add("Huverba BV");
        m_sa_sh.Add("A&F HOLDINGS");
        m_sa_sh.Add("Firstsource En. Co., Ltd.");
        m_sa_sh.Add("ITALTILE CERAMICS LIMITED");
        m_sa_sh.Add("KWB TRADING CO.LTD.");
        m_sa_sh.Add("INTERPARK SHOPPING");
        m_sa_sh.Add("SULASINDO NIAGATAMA");
//        m_sa_sh.Add("Enterprises Holdings Co. Ltd.");
//        m_sa_sh.Add("FH INDUSTRIAL CO.LTD.");
        //
gPAGES.RemoveAll();

lstViewContainer->Clear();
m_strEndCustDate = "";
cbDoing->Checked = false;
m_strStatus = "";
g_cdid=0;

m_strShipAgent = "";
        lstView->Items->Clear();
                Label41->Caption = "";
Label42->Caption = "";
Label43->Caption = "";
Label44->Caption = "";
        //clear edtxx
        edtCid->Text = "";
        edtDeclareid->Text = "";
//return;
//        lbClient->Caption = "";
//        edtOperunit->Text = "";
        edtForwardingunit->Text = "";
        edtLicenseno->Text = "";
        edtCount->Text = "";
        cbbPack->Text = "";
        edtLoadingid->Text = "";
        m_strContainerInfo = "";
        edtBoatno->Text = "";
        edtBoatorder->Text = "";
        cbbTransport->Text = "";
        edtOutport->Text = "南沙保税";
        cbbTrade->Text = "";
        cbbZhengmian->Text = "";
        edtInnersupplyadd->Text = "广州其它";

        cbbBargain->Text = "";
        cbbTargetCountry->Text = "";
        cbbAssginPort->Text = "";
        edtCarriage->Text = "0";
        edtInsurance->Text = "0";
//        edtContractid->Text = "RT-023";
        edtContractid->Text = "";
        edtNetweight->Text = "";
        edtGrossWeight->Text = "";
        edtSum->Text = "";
        edtAttachedoc->Text = "";
        edtManufacturer->Text = "";
        edtMarks->Text = "港口区 不退税 无牌子";
        edtInvoice->Text = "广州润顺国际货运代理有限公司";
//return;
        cbbOperunit->Text = "";
        cbbSH->Text = "";
        cbbMname->Text = "";
        edtNo->Text = "";
        edtMCode->Text = "";
        edtSpec->Text = "";
        edtFirstmeasunit->Text = "";
        edtSecondmeasunit->Text = "";
        edtUnitprice->Text = "";

        //~
        cbbPack->ItemIndex = -1;
        cbbPack->Text = "";

//        cbbPkName->ItemIndex = -1;
        cbbPkName->Text = "";

        CString szSQL;
	szSQL.Format("select * from dicpack");
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{

                cbbPack->Items->Add(dm1->Query1->FieldByName("pkname")->AsString);
                m_lstPack.Add(dm1->Query1->FieldByName("pkname")->AsString.c_str());
                cbbPkName->Items->Add(dm1->Query1->FieldByName("pkname")->AsString);
		dm1->Query1->Next();
        }
//return
                 cbbPack->ItemIndex = 0;
        cbbTrade->ItemIndex = -1;
        cbbTrade->Text = "";
	szSQL.Format("select * from dictrade");
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{

                cbbTrade->Items->Add(dm1->Query1->FieldByName("trname")->AsString);
                m_lstTrade.Add(dm1->Query1->FieldByName("trname")->AsString.c_str());
		dm1->Query1->Next();
        }
            cbbTrade->ItemIndex=0;
        cbbZhengmian->ItemIndex = -1;
        cbbZhengmian->Text = "";
	szSQL.Format("select * from diczhengmian");
 	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{

                cbbZhengmian->Items->Add(dm1->Query1->FieldByName("zmname")->AsString);
                m_lstZhengmian.Add(dm1->Query1->FieldByName("zmname")->AsString.c_str());
		dm1->Query1->Next();
        }
        cbbZhengmian->ItemIndex =0;

        cbbTransport->ItemIndex = -1;
        cbbTransport->Text = "";
//return;
	szSQL.Format("select * from dictransport");
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{

                cbbTransport->Items->Add(dm1->Query1->FieldByName("tpname")->AsString);
                m_lstTransport.Add(dm1->Query1->FieldByName("tpname")->AsString.c_str());
		dm1->Query1->Next();
        }
        cbbTransport->ItemIndex=0;

        cbbBargain->ItemIndex = -1;
        cbbBargain->Text = "";
	szSQL.Format("select * from dicbargain");
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{

                cbbBargain->Items->Add(dm1->Query1->FieldByName("bgname")->AsString);
                m_lstBargain.Add(dm1->Query1->FieldByName("bgname")->AsString.c_str());
		dm1->Query1->Next();
        }
        cbbBargain->ItemIndex=0;

        cbbExcharge->ItemIndex = -1;
        cbbExcharge->Text = "";
	szSQL.Format("select * from dicexcharge");
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{

                cbbExcharge->Items->Add(dm1->Query1->FieldByName("exname")->AsString);
                m_lstExcharge.Add(dm1->Query1->FieldByName("exname")->AsString.c_str());
		dm1->Query1->Next();
        }
        cbbExcharge->ItemIndex=0;

        cbbTargetCountry->ItemIndex = -1;
        cbbTargetCountry->Text = "";
        cbbAssginPort->ItemIndex = -1;
        cbbAssginPort->Text = "";
//return;
	szSQL.Format("select * from dictargetcountry order by tcname");
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{

                cbbTargetCountry->Items->Add(dm1->Query1->FieldByName("tcname")->AsString);
                cbbAssginPort->Items->Add(dm1->Query1->FieldByName("tcport")->AsString);

		dm1->Query1->Next();
        }

        edtNetWeight1->Text = "";
        edtGrossWeight1->Text = "";
        edtCount1->Text = "";

//        cbbCurrency->ItemIndex = -1;
//        cbbCurrencyId->ItemIndex = -1;  //用于打印，某些单需要打简称，如发票
//        cbbCurrency->Text = "";
//        cbbCurrencyId->Text = "";
        szSQL.Format("select * from diccurrency order by crid");        //cny默认
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
                cbbCurrency->Items->Add(dm1->Query1->FieldByName("crname")->AsString);
                cbbCurrencyId->Items->Add(dm1->Query1->FieldByName("crid")->AsString);
		dm1->Query1->Next();
        }
        cbbCurrency->ItemIndex=0;
        cbbCurrencyId->ItemIndex=0;

        cbbMname->Text = "";
//        cbbCurrency->ItemIndex = -1;
        edtMid1->Text = "";
        edtCdid->Text = "";
          m_enWorkStateDetail=EN_IDLE_D;
          ResetCtrlDetail();
        m_enWorkState=EN_IDLE;
        ResetCtrl();


        //if not, enabled while fromshow
        btnPrnInvoice->Enabled 		 = false;
        btnPrnPackingList->Enabled = false;
        btnPrnContact->Enabled     = false;
        btnPrnDeclare->Enabled     = false;
        btnPrnAuth->Enabled        = false;
        btnModDetail->Enabled      = false;
        btnPrnOutBoat->Enabled     = false;
        btnWMZ->Enabled     = false;
        btnYSQRS->Enabled     = false;
        btnSCCK->Enabled     = false;
        btnQYCNS->Enabled = false;
        btnCIQ->Enabled = false;


}
//---------------------------------------------------------------------------


void __fastcall TDoForm::edtCidKeyPress(TObject *Sender, char &Key)
{
    if (Key==13) //enter key been pressed
    {
        Key=0;
        btnQueryUpClick(Sender);
    }
}
//---------------------------------------------------------------------------



void  TDoForm::flushSum()
{
        TListItem *pItem;
        double totalCount = 0;
        double totalNetWeight=0;
        float totalGrossWeight=0;
        int totalCasescnt=0;
//        int totalSum=0;
        double totalSum=0;
        int i=0;
        for(i=0;i<lstView->Items->Count;i++)
        {
                pItem=lstView->Items->Item[i];
                totalCount+=StrToFloat(pItem->SubItems->Strings[4]);
                totalNetWeight+=StrToFloat(pItem->SubItems->Strings[2]);
                totalSum+=StrToFloat(pItem->SubItems->Strings[10]);
                totalGrossWeight+=StrToFloat(pItem->SubItems->Strings[3]);
                totalCasescnt+=StrToInt(pItem->SubItems->Strings[5]);
        }
        edtCount->Text = IntToStr(totalCasescnt);
        edtNetweight->Text = totalNetWeight;
        edtGrossWeight->Text = FloatToStr(totalGrossWeight);
        edtSum->Text = FloatToStr(totalSum);
        Label41->Caption = totalNetWeight;
        Label42->Caption = FloatToStr(totalGrossWeight);
        Label43->Caption = IntToStr(totalCasescnt);
        FormatFloat("0.00", totalSum);
        Label44->Caption = FloatToStr(totalSum);        //20130308 报关单精度
/*
        //process
        int total_100=totalSum*100;
        int total_real = 0;
        if(total_100 % 100 == 0){
                total_real = total_100/100;
                Label44->Caption = IntToStr(total_real);
        }else{
                Label44->Caption = FloatToStr(totalSum);
        }
        //~
*/

}
void __fastcall TDoForm::btnModClick(TObject *Sender)
{
  m_enWorkState=EN_EDIT;
  ResetCtrl();

}

int TDoForm::ModHead(){
  int rt = -1;


        if (edtDeclareid->Text.IsEmpty() || edtDeclareid->Text.IsEmpty() || cbbOperunit->Text.IsEmpty() \
                 || cbbPack->Text.IsEmpty() || edtLoadingid->Text.IsEmpty() || cbbTransport->Text.IsEmpty()\
                  || edtOutport->Text.IsEmpty() || cbbBargain->Text.IsEmpty() || cbbZhengmian->Text.IsEmpty() || edtInnersupplyadd->Text.IsEmpty() \
                   || cbbExcharge->Text.IsEmpty() || cbbTrade->Text.IsEmpty() || cbbTargetCountry->Text.IsEmpty()     \
                    || edtMarks->Text.IsEmpty() \
                     || edtInvoice->Text.IsEmpty() || edtDeclareid->Text.IsEmpty() || edtDeclareid->Text.IsEmpty()) {
                ShowMessage("请检查输入项");

                return rt;
        }
        if (!(cbDoing->Checked)){
                char strMsg[256],strSQL[512];
                sprintf(strMsg,"\n  未勾选[单证处理中] 是否继续?\n");
                if(Application->MessageBox(strMsg,"警告",MB_YESNOCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2)!=IDYES)
                        return rt;
        }
        CString szSQL;
        szSQL;
        szSQL="update customs set /*status='已接单',*/";

szSQL +="declareid="; szSQL += Str2DBString(edtDeclareid->Text.c_str());
//发货单位默认同经营单位，但可修改
//edtForwardingunit->Text = ( edtForwardingunit->Text.IsEmpty()? edtOperunit->Text.c_str():edtForwardingunit->Text.c_str() );
edtForwardingunit->Text = ( edtForwardingunit->Text.IsEmpty()? cbbOperunit->Text.c_str():edtForwardingunit->Text.c_str() );
szSQL +=",forwardingunit="; szSQL += Str2DBString(edtForwardingunit->Text.c_str());
//szSQL +=",operunit="; szSQL += Str2DBString(edtOperunit->Text.c_str());
szSQL +=",operunit="; szSQL += Str2DBString(cbbOperunit->Text.c_str());
szSQL +=",licenseno="; szSQL += Str2DBString(edtLicenseno->Text.c_str());
szSQL +=" , pack="; szSQL += Str2DBString(cbbPack->Text.c_str());
szSQL +=" , transport="; szSQL += Str2DBString(cbbTransport->Text.c_str());
szSQL +=", outport="; szSQL += Str2DBString(edtOutport->Text.c_str());
szSQL +=" , trade="; szSQL += Str2DBString(cbbTrade->Text.c_str());
szSQL +=" , zhengmian="; szSQL += Str2DBString(cbbZhengmian->Text.c_str());
szSQL +=" , innersupplyadd="; szSQL += Str2DBString(edtInnersupplyadd->Text.c_str());
szSQL +=",excharge="; szSQL += Str2DBString(cbbExcharge->Text.c_str());
szSQL +=",bargain="; szSQL += Str2DBString(cbbBargain->Text.c_str());
szSQL +=",targetcontry="; szSQL += Str2DBString(cbbTargetCountry->Text.c_str());
//指运港默认同运抵国，但可修改
//szSQL +=",assignport="; szSQL += Str2DBString(edtAssignport->Text.IsEmpty()?cbbTargetCountry->Text.c_str():edtAssignport->Text.c_str());
szSQL +=",assignport="; szSQL += Str2DBString(cbbAssginPort->Text.c_str());
szSQL +=",carriage="; szSQL += Str2DBString(edtCarriage->Text.c_str());
szSQL +=",insurance="; szSQL += Str2DBString(edtInsurance->Text.c_str());
szSQL +=",contractid="; szSQL += Str2DBString(edtContractid->Text.c_str());
//szSQL +=",contractid="; szSQL += Str2DBString(edtCid->Text.c_str());
szSQL +=",attachedoc="; szSQL += Str2DBString(edtAttachedoc->Text.c_str());
szSQL +=",manufacturer="; szSQL += Str2DBString(edtManufacturer->Text.c_str());
szSQL +=",marks="; szSQL += Str2DBString(edtMarks->Text.c_str());
szSQL +=",invoice="; szSQL += Str2DBString(edtInvoice->Text.c_str());
szSQL +=",currency=";     szSQL += Str2DBString(cbbCurrency->Text.c_str());
szSQL +=",doer=";       szSQL += Str2DBString(g_theOperator.op_name);
szSQL +=",shanghao=";       szSQL += Str2DBString(cbbSH->Text.c_str());

szSQL += " where cid="; szSQL+=Str2DBString(edtCid->Text.c_str());
//       Edit1->Text = AnsiString(szSQL);

        if(!RunSQL(dm1->Query1,szSQL))
        {
                ShowMessage("update fail!") ;

                return rt;
        }
        ShowMessage("保存成功");
        rt = 0;
        return rt;
}
//---------------------------------------------------------------------------
void TDoForm::CleanQryInput(){
        edtNo->Text = "";
        cbbMname->Text = "";
        edtMCode->Text = "";
        edtSpec->Text = "";
        edtFirstmeasunit->Text = "";
        edtSecondmeasunit->Text = "";
        edtUnitprice->Text = "";
        edtNetWeight1->Text = "";
        edtGrossWeight1->Text = "";
        edtCount1->Text = "";
        edtCount2nd->Text = "0";
        edtCasecnt->Text = "";
        cbbPkName->Text = "";
}
void __fastcall TDoForm::btnAddDetailClick(TObject *Sender)
{
  clearInputDetail();
  m_enWorkStateDetail=EN_ADDNEW_D;
  ResetCtrlDetail();
  if(cbbMname->CanFocus()) {
        cbbMname->SetFocus();
  }
  return;

}
//---------------------------------------------------------------------------

void TDoForm::clearInputDetail(){
        edtNo->Text = "";
        cbbMname->Text = "";
        edtMCode->Text = "";
        edtSpec->Text = "";
        edtFirstmeasunit->Text = "";
        edtSecondmeasunit->Text = "";
        edtUnitprice->Text = "";
        edtNetWeight1->Text = "";
        edtGrossWeight1->Text = "";
        edtCount1->Text = "";
        edtCount2nd->Text = "";
        edtCasecnt->Text = "";
        cbbPkName->Text = "";
}


void __fastcall TDoForm::cbbBargainChange(TObject *Sender)
{
        if (cbbBargain->Text == "FOB"){
                edtCarriage->Text = 0;
                edtCarriage->Enabled = false;
                edtCarriage->Color = clScrollBar;
                edtInsurance->Text = 0;
                edtInsurance->Enabled = false;
                edtInsurance->Color = clScrollBar;
        } else if (cbbBargain->Text == "CIF") {
                edtCarriage->Text = 0;
                edtCarriage->Enabled = true;
                edtCarriage->Color = clWindow;
                edtInsurance->Text = 0;
                edtInsurance->Enabled = true;
                edtInsurance->Color = clWindow;
        }
}
//---------------------------------------------------------------------------


void __fastcall TDoForm::cbbMnameChange(TObject *Sender)
{

        AnsiString val = cbbMname->Text;
        if (cbbMname->Text.IsEmpty()) {
                return;
        }
        cbbMname->SelStart = AnsiString(cbbMname->Text).Length();
        //mark now currency
        strNowCurrency = cbbCurrency->Text;
//        cbbMname->SelStart = 254;
//        cbbMname->SelLength = 0;
//        cbbMname->Text = val;

        m_lstMid1.RemoveAll();
        m_lstMCode.RemoveAll();
        m_lstSpec.RemoveAll();
        m_lstFirstmeasunit.RemoveAll();
        m_lstSecondmeasunit.RemoveAll();
        m_lstUnitprice.RemoveAll();
        m_lstWeightPercent.RemoveAll();
        edtMid1->Text = "";
        edtMCode->Text = "";
        edtSpec->Text = "";
        edtFirstmeasunit->Text = "";
        edtSecondmeasunit->Text = "";
        edtUnitprice->Text = "";

//        cbbMname->Items->Clear();
        CString szSQL;
	szSQL.Format("select * from merchandise where mname like '%%%s%%'", cbbMname->Text.c_str());
	RunSQL(dm1->Query1,szSQL,true);
        /*
        //20121117
        //旧逻辑: 查到有记录，才清楚cbbMname列表，这是不合理的，因为如果输入错误的商品名称，但下拉确还是就数据，后面select时会有问题。
        if (!dm1->Query1->Eof){
                cbbMname->Items->Clear();
                cbbMname->SelLength = 255;
                cbbMname->SelStart = 255;
        }
        */
        //不管如何，先清理缓存。
        cbbMname->Items->Clear();
        cbbMname->SelLength = 255;
        cbbMname->SelStart = 255;

	while(!dm1->Query1->Eof)
	{
                cbbMname->Items->Add(dm1->Query1->FieldByName("mname")->AsString);
                m_lstMid1.Add(dm1->Query1->FieldByName("mid")->AsString.c_str());
                m_lstMCode.Add(dm1->Query1->FieldByName("mcode")->AsString.c_str());
                m_lstSpec.Add(dm1->Query1->FieldByName("spec")->AsString.c_str());
                AnsiString unit1 = dm1->Query1->FieldByName("firstmeasunit")->AsString;
                AnsiString unit2 = dm1->Query1->FieldByName("secondmeasunit")->AsString;
                AnsiString unitprice1 = dm1->Query1->FieldByName("unitprice1")->AsString;
                AnsiString unitprice2 = dm1->Query1->FieldByName("unitprice2")->AsString;

                m_lstFirstmeasunit.Add(unit1.c_str());
                m_lstSecondmeasunit.Add(unit2.c_str());
                AnsiString strUnitPrice = "0";
                if (strNowCurrency == dm1->Query1->FieldByName("crname1")->AsString){
                    strUnitPrice = unitprice1;
                } else if (strNowCurrency == dm1->Query1->FieldByName("crname2")->AsString){
                    strUnitPrice = unitprice2;
                }
                m_lstUnitprice.Add(strUnitPrice.c_str());
                m_lstWeightPercent.Add(dm1->Query1->FieldByName("weight_percent")->AsString.c_str());
		dm1->Query1->Next();
        }
//        cbbMname->ItemIndex = -1;
}
//---------------------------------------------------------------------------




void __fastcall TDoForm::cbbMnameSelect(TObject *Sender)
{
//        m_isSelectMname = true;
        //when change, check strNowCurrency
        if (strNowCurrency!=cbbCurrency->Text){
                ShowMessage("币制有变动,需重新输入商品名称");
                cbbMname->Clear();
                edtMCode->Text = "";
                edtSpec->Text = "";
                edtUnitprice->Text = "";
                return;
        }
        int nSel = cbbMname->ItemIndex;
        if (nSel == -1)
                return;

        edtMid1->Text = AnsiString(m_lstMid1[nSel]);
        edtMCode->Text = AnsiString(m_lstMCode[nSel]);
        edtSpec->Text = AnsiString(m_lstSpec[nSel]);
        edtFirstmeasunit->Text = AnsiString(m_lstFirstmeasunit[nSel]);
//        return;
        edtSecondmeasunit->Text = AnsiString(m_lstSecondmeasunit[nSel]);
        edtUnitprice->Text = AnsiString(m_lstUnitprice[nSel]);
        strWeightPercent =  AnsiString(m_lstWeightPercent[nSel]);

}
//---------------------------------------------------------------------------
#include "PrnInvoice.h"
void __fastcall TDoForm::btnPrnInvoiceClick(TObject *Sender)
{
        TPrnInvoiceForm *pForm;
 	pForm=new TPrnInvoiceForm(this);
        assert(pForm!=NULL);

        //header
        //商号，默认B.R.T
        pForm->qrlClient->Caption = cbbSH->Text;
        pForm->qrlInvoice->Caption = edtContractid->Text;
        pForm->qrlDate->Caption = AnsiString(GetSysDate());
        pForm->qrlCurrencyId->Caption = cbbCurrencyId->Text;
        //detali
        CString szSQL;
/*	szSQL.Format("select mname,count,firstmeasunit,cunitprice,count*cunitprice  total, '%s' as crid \
                        from customs_detail a, merchandise b where cdid like '%s__' and a.cmid=b.mid order by a.cdid ", \
                        cbbCurrencyId->Text.c_str(), edtCid->Text.c_str());
*/
	szSQL.Format("select mname,count,firstmeasunit,cunitprice,convert(numeric(10,2),count*cunitprice) as total, '%s' as crid \
                        from customs_detail a, merchandise b where cdid like '%s__' and a.cmid=b.mid order by a.cdid ", \
                        cbbCurrencyId->Text.c_str(), edtCid->Text.c_str());

	RunSQL(dm1->sqlPrint,szSQL,true);
        pForm->PrnView->PreviewModal() ;
        delete pForm;
}
//---------------------------------------------------------------------------

#include "PrnPackingList.h"
void __fastcall TDoForm::btnPrnPackingListClick(TObject *Sender)
{
        TPrnPackingListForm *pForm;
 	pForm=new TPrnPackingListForm(this);
        assert(pForm!=NULL);

        //header
        pForm->qrlSH->Caption = cbbSH->Text;
//        pForm->qrlBoat->Caption = edtBoatno->Text;
        pForm->qrlOutport->Caption = edtOutport->Text;
        pForm->qrlTargetCountry->Caption = cbbTargetCountry->Text;
        pForm->qrlDate->Caption = AnsiString(GetSysDate());
        pForm->qrlInvoice->Caption = edtContractid->Text;
        pForm->qrlContractId->Caption = edtContractid->Text;
        pForm->qrlExcharge->Caption = cbbExcharge->Text;
        pForm->qrlNetWeight->Caption = edtNetweight->Text;
        pForm->qrlGrossWeight->Caption = Label42->Caption;



        //detali
        CString szSQL;
	szSQL.Format("select mname,casescnt,count,firstmeasunit,netweight total_net,grossweight total_gross from \
                        customs_detail a, merchandise b where cdid like '%s__' and a.cmid=b.mid order by a.cdid",edtCid->Text.c_str());
	RunSQL(dm1->sqlPrint,szSQL,true);
        pForm->PrnView->PreviewModal() ;
        delete pForm;
}
//---------------------------------------------------------------------------
#include "PrnContact.h"
#include "PrnContactSub.h"
void __fastcall TDoForm::btnPrnContactClick(TObject *Sender)
{
        if (edtCid->Text.IsEmpty()){
                ShowMessage("请先输入单号");
                return;
        }
        CString szSQL;
	szSQL.Format("select top %d cdid from customs_detail where cdid like '%s__' order by cdid", COL_PER_PAGE_PRN_CONTACT, edtCid->Text.c_str());
	RunSQL(dm1->Query1,szSQL,true);

        AnsiString last_of_first_page;
	while(!dm1->Query1->Eof)
	{
                last_of_first_page = dm1->Query1->FieldByName("cdid")->AsString.c_str();
		dm1->Query1->Next();
	}

        int cnt = 0;
        bool isHasSub = false;
        szSQL.Format("select count(*) as cnt from customs_detail where cdid like '%s__'", edtCid->Text.c_str());
	RunSQL(dm1->Query1,szSQL,true);

	if(!dm1->Query1->Eof)
	{
                cnt = dm1->Query1->FieldByName("cnt")->AsInteger;
	}
        if (cnt > COL_PER_PAGE_PRN_CONTACT){
                isHasSub = true;
        }
        prnContactMain(last_of_first_page.c_str(), isHasSub);

        if (isHasSub) {
                prnContactSub(last_of_first_page.c_str());
        }
}
//---------------------------------------------------------------------------
#include "PrnDeclare.h"
#include "PrnDeclareSub.h"
void __fastcall TDoForm::btnPrnDeclareClick(TObject *Sender)
{
        //valid check
        if (edtCid->Text.IsEmpty()){
                ShowMessage("请先输入单号");
                return;
        }
        //cid split prepare
        std::map<int, CCidPage> mPages;//<page_num, CCidPage(begin_cid,end_cid)>
        mPages.clear();

        CString szSQL;
	szSQL.Format("select cdid from customs_detail where cdid like '%s__' order by cdid", edtCid->Text.c_str());
	RunSQL(dm1->Query1,szSQL,true);

        int nPageNum = 0;//1,2,3,4...
        int nCurrCnt = 0;//1,2,3,4...
 //       AnsiString begin_cid = "";
 //       AnsiString end_cid = "";
 //       AnsiString split_detail = "";
//        int nCurrPage = 0;
        CCidPage cidpage;
        AnsiString rs_cid = "";
	while(!dm1->Query1->Eof)
	{
                rs_cid = dm1->Query1->FieldByName("cdid")->AsString;
                nCurrCnt++;

                //save begin
                if (nCurrCnt % COL_PER_PAGE_PRN_DECLARE == 1){
                        cidpage.begin_cid = rs_cid;
                }
                //save end
                if (nCurrCnt % COL_PER_PAGE_PRN_DECLARE == 0){
                        cidpage.end_cid = rs_cid;
                        mPages.insert(std::make_pair(++nPageNum, cidpage));
                        cidpage.init();
                }
		dm1->Query1->Next();
	}

        //do the last page
        if (nCurrCnt % COL_PER_PAGE_PRN_DECLARE != 0){   //the same as upside

                        cidpage.end_cid = rs_cid;
                        mPages.insert(std::make_pair(++nPageNum, cidpage));
                        cidpage.init();
        }

        int nTotalPage = mPages.size();
        int nPageOrd = 0;
        for (std::map<int, CCidPage>::iterator it = mPages.begin(); it != mPages.end(); ){

                AnsiString split_detail = AnsiString("页码:") + AnsiString(nTotalPage) + "-" + AnsiString(it->first);
                prnDeclare(it->second.begin_cid, it->second.end_cid, split_detail, nPageOrd++, ++it==mPages.end()?true:false);
        }


/*
        if (edtCid->Text.IsEmpty()){
                ShowMessage("请先输入单号");
                return;
        }
        CString szSQL;
	szSQL.Format("select top %d cdid from customs_detail where cdid like '%s__' order by cdid", COL_PER_PAGE_PRN_DECLARE, edtCid->Text.c_str());
	RunSQL(dm1->Query1,szSQL,true);

        AnsiString last_of_first_page;
	while(!dm1->Query1->Eof)
	{
                last_of_first_page = dm1->Query1->FieldByName("cdid")->AsString.c_str();
		dm1->Query1->Next();
	}

        int cnt = 0;
        bool isHasSub = false;
        szSQL.Format("select count(*) as cnt from customs_detail where cdid like '%s__'", edtCid->Text.c_str());
	RunSQL(dm1->Query1,szSQL,true);

	if(!dm1->Query1->Eof)
	{
                cnt = dm1->Query1->FieldByName("cnt")->AsInteger;
	}
        if (cnt > COL_PER_PAGE_PRN_DECLARE){
                isHasSub = true;
        }
        prnDeclareMain(last_of_first_page.c_str(), isHasSub);

        if (isHasSub) {
//                prnDeclareSub(last_of_first_page.c_str());
        }
*/
}
//---------------------------------------------------------------------------
#include "PrnAuth.h"
void __fastcall TDoForm::btnPrnAuthClick(TObject *Sender)
{
        if (lstView->Items->Count == 0) {
                ShowMessage("请完善表体信息");
                return ;
        }
        TPrnAuthForm *pForm;
 	pForm=new TPrnAuthForm(this);
        assert(pForm!=NULL);

        unsigned short year0,month0,day0,year1,month1,day1;
        dtpValidDate->Date = Now();
	dtpValidDate->DateTime.DecodeDate(&year0,&month0,&day0);
        dtpValidDate->Date = Now() + 20;
        dtpValidDate->DateTime.DecodeDate(&year1,&month1,&day1);

       pForm->qrlCid->Caption = edtCid->Text;
       
        pForm->qrlValidDateYYYY->Caption = IntToStr(year1);
        pForm->qrlValidDateMM->Caption = IntToStr(month1);
        pForm->qrlValidDateDD->Caption = IntToStr(day1);

        pForm->qrlNowYYYY->Caption = IntToStr(year0);
        pForm->qrlNowMM->Caption = IntToStr(month0);
        pForm->qrlNowDD->Caption = IntToStr(day0);
        pForm->qrlNowYYYY1->Caption = IntToStr(year0);
        pForm->qrlNowMM1->Caption = IntToStr(month0);
        pForm->qrlNowDD1->Caption = IntToStr(day0);
        pForm->qrlNowYYYY2->Caption = IntToStr(year0);
        pForm->qrlNowMM2->Caption = IntToStr(month0);
        pForm->qrlNowDD2->Caption = IntToStr(day0);
        pForm->qrlNowYYYY3->Caption = IntToStr(year0);
        pForm->qrlNowMM3->Caption = IntToStr(month0);
        pForm->qrlNowDD3->Caption = IntToStr(day0);
        pForm->qrlNowYYYY4->Caption = IntToStr(year0);
        pForm->qrlNowMM4->Caption = IntToStr(month0);
        pForm->qrlNowDD4->Caption = IntToStr(day0);

//        pForm->qrlOperUnit->Caption = edtOperunit->Text;
        pForm->qrlOperUnit->Caption = cbbOperunit->Text;
        pForm->qrlLadingId->Caption = edtLoadingid->Text;
        pForm->qrlTrade->Caption = cbbTrade->Text;
        pForm->qrlInnersupplyadd->Caption = edtInnersupplyadd->Text;
//        pForm->qrlDeclareId->Caption = edtDeclareid->Text;
        pForm->qrlDeclareId->Caption = (edtDeclareid->Text.Length() > 9)? \
                                        edtDeclareid->Text.SubString(edtDeclareid->Text.Length()-9+1,9):edtDeclareid->Text;

//        pForm->qrlOperUnit->Caption = edtOperunit->Text;
        pForm->qrlOperUnit->Caption = cbbOperunit->Text;
        pForm->qrlTotal->Caption = Label44->Caption;

        pForm->qrlFirstMid->Caption = lstView->Items->Item[0]->Caption;
        pForm->qrlFirstMname->Caption = lstView->Items->Item[0]->SubItems->Strings[0];
            pForm->PrnView->PreviewModal() ;
        delete pForm;



}
//---------------------------------------------------------------------------
void TDoForm::genContainerInfo4PrnDeclare(AnsiString c){
                m_strContainerTail = "";
                int nContainerCnt = 0;
                int nSubContainerCnt = 0;
		char cnt[10];memset(cnt,sizeof(cnt),0x00);
		char body[2048];memset(body,sizeof(body),0x00);
		sscanf(c.c_str(),"%[^|]|",cnt);
		sscanf(c.c_str(),"%*[^|]|%[^@]",body);

		char strTmp1[2048];
		memset(strTmp1,sizeof(strTmp1),0x00);
		strcpy(strTmp1,body);
                nContainerCnt = StrToInt(cnt);
		for (int i =0; i<nContainerCnt; ++i){
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
/*
                        TListItem *pItem =lstViewContainer->Items->Add();
                        assert(pItem!=NULL);
                        pItem->Caption=AnsiString(str3);
                        pItem->SubItems->Add(AnsiString(str4));
                        pItem->SubItems->Add(AnsiString(strSealId));
*/
                        if (i == 0) {
                                m_strContainerHead = str3;
                        } else {
                                m_strContainerTail += str3;
                                m_strContainerTail += "   ";
                        }
                        nSubContainerCnt += ( strcmp(str4,"S") == 0?1:2 );
                }
                m_strContainerHead += " ";
                m_strContainerHead += (IntToStr(nContainerCnt)).c_str();
                m_strContainerHead += "(";
                m_strContainerHead += (IntToStr(nSubContainerCnt)).c_str();
                m_strContainerHead += ")";
}



#include "PrnOutBoat.h"
void __fastcall TDoForm::btnPrnOutBoatClick(TObject *Sender)
{
        if (lstView->Items->Count == 0) {
                ShowMessage("请完善表体信息");
                return ;
        }

        TPrnOutBoatForm *pForm;
 	pForm=new TPrnOutBoatForm(this);
        assert(pForm!=NULL);

       pForm->qrlCid->Caption = edtCid->Text;
       pForm->qrlSH->Caption = cbbSH->Text;

       pForm->qrlLadingId->Caption = edtLoadingid->Text;
//       pForm->qrlOperUnit->Caption = edtOperunit->Text;
       pForm->qrlOperUnit->Caption = cbbOperunit->Text;
       pForm->qrlOutPort->Caption = edtOutport->Text;
       pForm->qrlBoatNo->Caption = edtBoatno->Text;
       pForm->qrlBoatOrder->Caption = edtBoatorder->Text;
       pForm->qrlTargetCountry->Caption = "";
//       pForm->qrlTargetCountry->Caption = cbbTargetCountry->Text;     //del 0626 不显示
/*       if (edtDeclareid->Text.Length() > 9){//只显示最后9位
                pForm->qrlDeclareId->Caption = edtDeclareid->Text.SubString(edtDeclareid->Text.Length()-9+1,9);
        } else {
                pForm->qrlDeclareId->Caption = edtDeclareid->Text;
        }
*/        
        pForm->qrlDeclareId->Caption = (edtDeclareid->Text.Length() > 9)? \
                                        edtDeclareid->Text.SubString(edtDeclareid->Text.Length()-9+1,9):edtDeclareid->Text;

//       pForm->qrlDeclareId->Caption = edtDeclareid->Text;

       pForm->qrlCountHead->Caption = edtCount->Text;
       pForm->qrlMname->Caption = lstView->Items->Item[0]->SubItems->Strings[0];
       pForm->qrlTotalNetWeight->Caption = Label42->Caption;
       SplitSubContainer(AnsiString(m_strContainerInfo));

       pForm->qrlSubContainerInfo1->Caption = AnsiString(m_strSubConNoSealId1);
       pForm->qrlSubContainerInfo2->Caption = AnsiString(m_strSubConNoSealId2);
       pForm->qrlSubContainerInfo3->Caption = AnsiString(m_strSubConNoSealId3);
       pForm->qrlSubContainerInfo4->Caption = AnsiString(m_strSubConNoSealId4);
       pForm->qrlSubContainerInfo5->Caption = AnsiString(m_strSubConNoSealId5);
       pForm->qrlSubContainerInfo6->Caption = AnsiString(m_strSubConNoSealId6);
       pForm->qrlSubContainerInfo7->Caption = AnsiString(m_strSubConNoSealId7);
       pForm->qrlSubContainerInfo8->Caption = AnsiString(m_strSubConNoSealId8);
       pForm->qrlSubContainerInfo9->Caption = AnsiString(m_strSubConNoSealId9);
       pForm->qrlSubContainerInfo10->Caption =AnsiString( m_strSubConNoSealId10);
       pForm->qrlShipAgent->Caption = AnsiString(m_strShipAgent);

       pForm->qrlTypeInfo1->Caption =AnsiString( m_strConTypeUp);
       pForm->qrlTypeInfo2->Caption = AnsiString(m_strConTypeDown);
       pForm->qrlEndCustDate->Caption = AnsiString(m_strEndCustDate);
       pForm->qrlNum20DaXie->Caption = AnsiString(m_strConNum20DaXie);
       pForm->qrlNum40DaXie->Caption = AnsiString(m_strConNum40DaXie);
       if (m_strConNum20DaXie.IsEmpty()){
                pForm->qrl20DaXie->Caption = "";
       }
       if (m_strConNum40DaXie.IsEmpty()){
                pForm->qrl40DaXie->Caption = "";
       }

        pForm->PrnView->PreviewModal() ;
        delete pForm;
}
void TDoForm::SplitSubContainer(AnsiString c){
                int nFixLen = 18; //缩小间距
                int nCntS, nCntL;
                nCntS = nCntL = 0;
		char cnt[10];memset(cnt,sizeof(cnt),0x00);
		char body[2048];memset(body,sizeof(body),0x00);
		sscanf(c.c_str(),"%[^|]|",cnt);
		sscanf(c.c_str(),"%*[^|]|%[^@]",body);

		char strTmp1[2048];
		memset(strTmp1,sizeof(strTmp1),0x00);
		strcpy(strTmp1,body);
                int num = StrToInt(cnt);
                m_strSubConNoSealId1 = m_strSubConNoSealId2 = m_strSubConNoSealId3 =m_strSubConNoSealId4 =m_strSubConNoSealId5 = "";
                m_strSubConNoSealId6 = m_strSubConNoSealId7 = m_strSubConNoSealId8 = m_strSubConNoSealId9 = m_strSubConNoSealId10 = "";
		for (int i =0; i<num; ++i){
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

                        if (strcmp(str4,"S") == 0)      nCntS++;
                        if (strcmp(str4,"L") == 0)      nCntL++;
                        //init

                         switch(i)
                        {
                                case 0:

                                        m_strSubConNoSealId1 = str3;
                                        for ( int i = strlen(str3); i < nFixLen; ++i){
                                                m_strSubConNoSealId1 += " ";
                                        }
                                        m_strSubConNoSealId1 += " ";
                                        m_strSubConNoSealId1 += strSealId;
                                        break;
                                case 1:

                                        m_strSubConNoSealId2 = str3;
                                        for ( int i = strlen(str3); i < nFixLen; ++i){
                                                m_strSubConNoSealId2 += " ";
                                        }
                                        m_strSubConNoSealId2 += " ";
                                        m_strSubConNoSealId2 += strSealId;
                                        break;
                                case 2:
                                        m_strSubConNoSealId3 = str3;
                                        for ( int i = strlen(str3); i < nFixLen; ++i){
                                                m_strSubConNoSealId3 += " ";
                                        }
                                        m_strSubConNoSealId3 += " ";
                                        m_strSubConNoSealId3 += strSealId;
                                        break;
                                case 3:
                                        m_strSubConNoSealId4 = str3;
                                        for ( int i = strlen(str3); i < nFixLen; ++i){
                                                m_strSubConNoSealId4 += " ";
                                        }
                                        m_strSubConNoSealId4 += " ";
                                        m_strSubConNoSealId4 += strSealId;
                                        break;
                                case 4:
                                        m_strSubConNoSealId5 = str3;
                                        for ( int i = strlen(str3); i < nFixLen; ++i){
                                                m_strSubConNoSealId5 += " ";
                                        }
                                        m_strSubConNoSealId5 += " ";
                                        m_strSubConNoSealId5 += strSealId;
                                        break;
                                case 5:
                                        m_strSubConNoSealId6 = str3;
                                        for ( int i = strlen(str3); i < nFixLen; ++i){
                                                m_strSubConNoSealId6 += " ";
                                        }
                                        m_strSubConNoSealId6 += " ";
                                        m_strSubConNoSealId6 += strSealId;
                                        break;
                                case 6:
                                        m_strSubConNoSealId7 = str3;
                                        for ( int i = strlen(str3); i < nFixLen; ++i){
                                                m_strSubConNoSealId7 += " ";
                                        }
                                        m_strSubConNoSealId7 += " ";
                                        m_strSubConNoSealId7 += strSealId;
                                        break;
                                case 7:
                                        m_strSubConNoSealId8 = str3;
                                        for ( int i = strlen(str3); i < nFixLen; ++i){
                                                m_strSubConNoSealId8 += " ";
                                        }
                                        m_strSubConNoSealId8 += " ";
                                        m_strSubConNoSealId8 += strSealId;
                                        break;
                                case 8:
                                        m_strSubConNoSealId9 = str3;
                                        for ( int i = strlen(str3); i < nFixLen; ++i){
                                                m_strSubConNoSealId9 += " ";
                                        }
                                        m_strSubConNoSealId9 += " ";
                                        m_strSubConNoSealId9 += strSealId;
                                        break;
                                case 9:
                                        m_strSubConNoSealId10 = str3;
                                        for ( int i = strlen(str3); i < nFixLen; ++i){
                                                m_strSubConNoSealId10 += " ";
                                        }                                        
                                        m_strSubConNoSealId10 += " ";
                                        m_strSubConNoSealId10 += strSealId;
                                        break;

                                default:  break;
                        }


		}
                m_strConTypeUp = "";
                m_strConTypeDown = "";
                m_strConNum20DaXie = "";
                m_strConNum40DaXie = "";
                
                if (nCntS !=0) {
//                    m_strConTypeUp = "/";
                    m_strConTypeUp += (IntToStr(nCntS)).c_str();
                    m_strConTypeUp += "*20' ";
                    m_strConNum20DaXie = (ConvertInt2(IntToStr(nCntS))).c_str();

                    if (nCntL != 0) {
                        m_strConTypeDown = (IntToStr(nCntL)).c_str();
                        m_strConTypeDown += "*40' ";
                        m_strConNum40DaXie = (ConvertInt2(IntToStr(nCntL))).c_str();
                    }
                } else {
                    if (nCntL != 0) {
//                        m_strConTypeUp = "/";
                        m_strConTypeUp += (IntToStr(nCntL)).c_str();
                        m_strConTypeUp += "*40' ";
                        m_strConNum40DaXie = (ConvertInt2(IntToStr(nCntL))).c_str();
                    }
                }

}
//---------------------------------------------------------------------------

void __fastcall TDoForm::cbbCurrencyChange(TObject *Sender)
{
        cbbCurrencyId->ItemIndex = cbbCurrency->ItemIndex;        
}
//---------------------------------------------------------------------------

void __fastcall TDoForm::lstViewSelectItem(TObject *Sender,
      TListItem *Item, bool Selected)
{
        return;
//
        btnAddDetail->Enabled = false;
        btnOkDetail->Enabled = false;
        btnCancleDetail->Enabled = false;
         btnModDetail->Enabled = true;
        btnDelDetail->Enabled = true;
        cbbMname->Text = Item->SubItems->Strings[0];
        edtMCode->Text = Item->Caption;
        edtSpec->Text = Item->SubItems->Strings[1];
        edtFirstmeasunit->Text =Item->SubItems->Strings[6];
        edtSecondmeasunit->Text =Item->SubItems->Strings[7];
        edtNetWeight1->Text =Item->SubItems->Strings[2];
        edtGrossWeight1->Text =Item->SubItems->Strings[3];
        edtCount1->Text =Item->SubItems->Strings[4];
        edtCasecnt->Text = Item->SubItems->Strings[5];
        edtCount2nd->Text = Item->SubItems->Strings[13];
        edtUnitprice->Text = Item->SubItems->Strings[9];
        cbbPkName->Text = Item->SubItems->Strings[14];
        edtCdid->Text = Item->SubItems->Strings[15];

}
//---------------------------------------------------------------------------

void __fastcall TDoForm::btnModDetailClick(TObject *Sender)
{
  m_enWorkStateDetail=EN_EDIT_D;
  ResetCtrlDetail();
  return;



}
//---------------------------------------------------------------------------

void __fastcall TDoForm::btnChangeStatusClick(TObject *Sender)
{
        CString szSQL;
        szSQL="update customs set status='已接单' ";

        szSQL += " where cid="; szSQL+=Str2DBString(edtCid->Text.c_str());
//       edtDebug->Text = AnsiString(szSQL);

        if(!RunSQL(dm1->Query1,szSQL))
        {
                ShowMessage("update fail!") ;

                return;
        }
        ShowMessage("单证处理中!");
}
//---------------------------------------------------------------------------

void __fastcall TDoForm::cbbTargetCountryChange(TObject *Sender)
{
        cbbAssginPort->ItemIndex = cbbTargetCountry->ItemIndex;          
}
//---------------------------------------------------------------------------








void __fastcall TDoForm::btnQueryUpClick(TObject *Sender)
{
        CString szSQL;

        edtCid->Text=Trim(edtCid->Text);
        if (edtCid->Text.IsEmpty()){
                ShowMessage("请输入工单号");
                isHasResult = false;
                if(edtCid->CanFocus())	edtCid->SetFocus();               
                return;
        }
        szSQL="select *,dbo.gen_prn_out_boat_enddate(endcustdate,acceptdate) prn_end_date           \
               from customs,dictargetcountry where 1=1 and targetcontry*=tcname";
        if (!edtCid->Text.IsEmpty()){
                szSQL +=" and cid="; szSQL += Str2DBString(edtCid->Text.c_str());
        }
//        edtDebug->Text = AnsiString(szSQL);
	RunSQL(dm1->Query1,szSQL,true);
        if (dm1->Query1->Eof){

                FormShow(Sender);
                ShowMessage("没有记录");
                isHasResult = false;
                //reset btn status
                m_enWorkState=EN_IDLE;
                ResetCtrl();
                return;
        }else{
                isHasResult = true;
        }
        AnsiString strCid = edtCid->Text;
	while(!dm1->Query1->Eof)
	{
                edtLoadingid->Text = dm1->Query1->FieldByName("ladingid")->AsString;
                m_strContainerInfo = dm1->Query1->FieldByName("containerinfo")->AsString.c_str();
                edtBoatno->Text = dm1->Query1->FieldByName("boatno")->AsString;
                edtBoatorder->Text = dm1->Query1->FieldByName("boatorder")->AsString;

                edtDeclareid->Text = dm1->Query1->FieldByName("declareid")->AsString;
//                lbClient->Caption = dm1->Query1->FieldByName("client")->AsString;
//               edtOperunit->Text = dm1->Query1->FieldByName("operunit")->AsString;
               cbbOperunit->Text = dm1->Query1->FieldByName("operunit")->AsString;
                edtForwardingunit->Text = dm1->Query1->FieldByName("forwardingunit")->AsString;
                edtLicenseno->Text = dm1->Query1->FieldByName("licenseno")->AsString;
                cbbPack->ItemIndex=cbbPack->Items->IndexOf(dm1->Query1->FieldByName("pack")->AsString.c_str());
                cbbTransport->ItemIndex=cbbTransport->Items->IndexOf(dm1->Query1->FieldByName("transport")->AsString.c_str());

                edtOutport->Text = dm1->Query1->FieldByName("outport")->AsString;
                cbbTrade->ItemIndex=cbbTrade->Items->IndexOf(dm1->Query1->FieldByName("trade")->AsString.c_str());
                cbbZhengmian->ItemIndex=cbbZhengmian->Items->IndexOf(dm1->Query1->FieldByName("zhengmian")->AsString.c_str());

                edtInnersupplyadd->Text = dm1->Query1->FieldByName("innersupplyadd")->AsString;
                cbbExcharge->ItemIndex=cbbExcharge->Items->IndexOf(dm1->Query1->FieldByName("excharge")->AsString.c_str());
                cbbBargain->ItemIndex=cbbBargain->Items->IndexOf(dm1->Query1->FieldByName("bargain")->AsString.c_str());

                cbbTargetCountry->ItemIndex=cbbTargetCountry->Items->IndexOf(dm1->Query1->FieldByName("targetcontry")->AsString.c_str());
//                ShowMessage(dm1->Query1->FieldByName("targetcontry")->AsString.c_str());
                int idx_curr = cbbCurrency->Items->IndexOf(dm1->Query1->FieldByName("currency")->AsString.c_str());
                if (idx_curr != -1){
                        cbbCurrency->ItemIndex = idx_curr;
                        cbbCurrencyId->ItemIndex = idx_curr;
                }
//                edtAssignport->Text = dm1->Query1->FieldByName("assignport")->AsString;
                cbbAssginPort->ItemIndex=cbbAssginPort->Items->IndexOf(dm1->Query1->FieldByName("tcport")->AsString.c_str());
                edtCarriage->Text = dm1->Query1->FieldByName("carriage")->AsString;
                edtInsurance->Text = dm1->Query1->FieldByName("insurance")->AsString;
/*
                CString strContractid=dm1->Query1->FieldByName("contractid")->AsString.c_str();
                if (strContractid==""){
                        AnsiString ss = "";
                        ss+=randStr(2);
                        ss+="-";
                        ss+=randNum(3);
                        edtContractid->Text = ss;
                }else{
                        edtContractid->Text = dm1->Query1->FieldByName("contractid")->AsString;
                }
*/
                //合同号=工单号 (可改，可能不一样0124)
                edtContractid->Text = dm1->Query1->FieldByName("contractid")->AsString;
                edtAttachedoc->Text = dm1->Query1->FieldByName("attachedoc")->AsString;
                edtManufacturer->Text = dm1->Query1->FieldByName("manufacturer")->AsString;
                edtMarks->Text = dm1->Query1->FieldByName("marks")->AsString;
                edtInvoice->Text = dm1->Query1->FieldByName("invoice")->AsString;
                cbDoing->Checked = (dm1->Query1->FieldByName("status")->AsString == "单证处理中");
//                edtShipAgent->Text = dm1->Query1->FieldByName("shipagent")->AsString;
                m_strStatus = dm1->Query1->FieldByName("status")->AsString.c_str();
//                m_strEndCustDate =  dm1->Query1->FieldByName("endcustdate")->AsString.c_str();
                m_strEndCustDate =  dm1->Query1->FieldByName("prn_end_date")->AsString.c_str();
                m_strShipAgent =  dm1->Query1->FieldByName("shipagent")->AsString.c_str();

                CString strSH=dm1->Query1->FieldByName("shanghao")->AsString.c_str();
                cbbSH->Text = AnsiString(strSH==""?m_sa_sh[StrToInt(strCid[strCid.Length()])]:strSH);

                flushContainer(dm1->Query1->FieldByName("containerinfo")->AsString);

		dm1->Query1->Next();


	}

        szSQL="select *,cast(cunitprice*count as decimal(20,2)) as total from customs_detail a, merchandise b where a.cdid like '";
        szSQL += edtCid->Text.c_str();
        szSQL += "%'";
        szSQL += " and a.cmid=b.mid order by cdid";
//        edtDebug->Text = AnsiString(szSQL);
        TListItem *pItem;
        lstView->Items->Clear();
	RunSQL(dm1->Query1,szSQL,true);
        CString tc = "";
	while(!dm1->Query1->Eof)
	{

                pItem=lstView->Items->Add();
                pItem->Caption=dm1->Query1->FieldByName("mcode")->AsString;
		pItem->SubItems->Add(dm1->Query1->FieldByName("mname")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("spec")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("netweight")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("grossweight")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("count")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("casescnt")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("firstmeasunit")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("secondmeasunit")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("targetcountry")->AsString);
                tc = dm1->Query1->FieldByName("targetcountry")->AsString.c_str();

                pItem->SubItems->Add(dm1->Query1->FieldByName("cunitprice")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("total")->AsString);
		pItem->SubItems->Add(cbbCurrency->Text);
		pItem->SubItems->Add(dm1->Query1->FieldByName("zhengmian")->AsString);
                pItem->SubItems->Add(dm1->Query1->FieldByName("count2")->AsString);
                pItem->SubItems->Add(dm1->Query1->FieldByName("pkname")->AsString);

                pItem->SubItems->Add(dm1->Query1->FieldByName("cdid")->AsString);


 		dm1->Query1->Next();
	}
        flushSum();
        if (cbbTrade->ItemIndex == -1)
                cbbTrade->ItemIndex=0;
        if (cbbPack->ItemIndex == -1)
                cbbPack->ItemIndex=0;
        if (cbbTransport->ItemIndex == -1)
                cbbTransport->ItemIndex=0;
        if (cbbBargain->ItemIndex == -1)
                cbbBargain->ItemIndex=0;
        if (cbbExcharge->ItemIndex == -1)
                cbbExcharge->ItemIndex=0;
//        if (cbbCurrency->ItemIndex == -1)
//                cbbCurrency->ItemIndex=0;
        if (cbbZhengmian->ItemIndex == -1)
                cbbZhengmian->ItemIndex=0;

        if(edtOutport->Text.IsEmpty())
             edtOutport->Text = "南沙保税";
        if(edtInnersupplyadd->Text.IsEmpty())
             edtInnersupplyadd->Text = "广州其它";
        if(edtInvoice->Text.IsEmpty())
             edtInvoice->Text = "广州润顺国际货运代理有限公司";
//        if(edtContractid->Text.IsEmpty())
//             edtContractid->Text = "RT-023";
        if(edtContractid->Text.IsEmpty()){
                edtContractid->Text = edtCid->Text;
        }
        if(edtMarks->Text.IsEmpty())
                edtMarks->Text = "港口区 不退税 无牌子";

//        cbbTargetCountry->ItemIndex=cbbTargetCountry->Items->IndexOf(AnsiString(tc));
        CleanQryInput();

        m_enWorkState=EN_IDLE;
        ResetCtrl();
}
//---------------------------------------------------------------------------










void TDoForm::ResetCtrl()
{
  if(m_enWorkState==EN_IDLE)
  {
    //lstview
//    lstViewDown->Enabled=true;
//    bool isSelected = (lstViewDown->Selected!=NULL);
    //btn
    btnMod->Enabled=isHasResult;
    btnOK->Enabled =false;
    btnCancel->Enabled=false;
    //table_body disable
    plDetail->Enabled = false;
      for(int   i=0;i <plDetail->ControlCount;i++)
      {
//              TControl *p=dynamic_cast<TControl*>(Panel1->Controls[i]);
//                plDetail->Controls[i]->Enabled = false;
      }
    //edt all disable
    EnableEdit(edtCid,true);
    EnableEdit(edtDeclareid,false);
//    EnableEdit(edtShipAgent,false);
//    EnableEdit(edtOperunit,false);
    EnableCombo(cbbOperunit,false);
    EnableEdit(edtForwardingunit,false);
    EnableEdit(edtLicenseno,false);
    EnableCombo(cbbSH,false);
    EnableEdit(edtOutport,false);
    EnableEdit(edtInnersupplyadd,false);
    EnableEdit(edtContractid,false);
    EnableEdit(edtAttachedoc,false);
    EnableEdit(edtManufacturer,false);
    EnableEdit(edtInvoice,false);
    EnableEdit(edtMarks,false);

    EnableCombo(cbbPack,false);
    EnableCombo(cbbTrade,false);
    EnableCombo(cbbZhengmian,false);
    EnableCombo(cbbTransport,false);
    EnableCombo(cbbTargetCountry,false);
    EnableCombo(cbbAssginPort,false);
    EnableCombo(cbbCurrency,false);
    EnableCombo(cbbBargain,false);
    EnableCombo(cbbExcharge,false);
    cbDoing->Enabled = false;
    //prn btn
    btnPrnInvoice->Enabled 		 = true;
    btnPrnPackingList->Enabled = true;
    btnPrnContact->Enabled     = true;
    btnPrnDeclare->Enabled     = true;
    btnPrnAuth->Enabled        = true;
//    btnModDetail->Enabled      = true;
    btnPrnOutBoat->Enabled     = true;
        btnWMZ->Enabled     = true;
        btnYSQRS->Enabled     = true;
        btnSCCK->Enabled     = true;
        btnQYCNS->Enabled = true;
        btnCIQ->Enabled = true;

  }
  else
  {
    //btn
    btnMod->Enabled=false;
    btnOK->Enabled =true;
    btnCancel->Enabled=true;
    //table_body btn enable
    plDetail->Enabled = true;
      for(int   i=0;i <plDetail->ControlCount;i++)
      {
//              TControl *p=dynamic_cast<TControl*>(Panel1->Controls[i]);
//                plDetail->Controls[i]->Enabled = true;
      }
//    btnAddDetail->Enabled = true;
//    lstView->Enabled = true;
    //edt all disable
    EnableEdit(edtCid,false);
    EnableEdit(edtDeclareid,true);
//    EnableEdit(edtShipAgent,true);
//    EnableEdit(edtOperunit,true);
    EnableCombo(cbbOperunit,true);
    EnableEdit(edtForwardingunit,true);
    EnableEdit(edtLicenseno,true);
    EnableCombo(cbbSH,true);
    EnableEdit(edtOutport,true);
    EnableEdit(edtInnersupplyadd,true);
    EnableEdit(edtContractid,true);
    EnableEdit(edtAttachedoc,true);
    EnableEdit(edtManufacturer,true);
    EnableEdit(edtInvoice,true);
    EnableEdit(edtMarks,true);

    EnableCombo(cbbPack,true);
    EnableCombo(cbbTrade,true);
    EnableCombo(cbbZhengmian,true);
    EnableCombo(cbbTransport,true);
    EnableCombo(cbbTargetCountry,true);
    EnableCombo(cbbAssginPort,true);
    EnableCombo(cbbCurrency,true);
    EnableCombo(cbbBargain,true);
    EnableCombo(cbbExcharge,true);
    cbDoing->Enabled = true;
    //prn btn
    btnPrnInvoice->Enabled 		 = false;
    btnPrnPackingList->Enabled = false;
    btnPrnContact->Enabled     = false;
    btnPrnDeclare->Enabled     = false;
    btnPrnAuth->Enabled        = false;
//    btnModDetail->Enabled      = false;
//    btnOkDetail->Enabled    = false;
//    btnCancleDetail->Enabled    = false;

    btnPrnOutBoat->Enabled     = false;
        btnWMZ->Enabled     = false;
        btnYSQRS->Enabled     = false;
        btnSCCK->Enabled     = false;
        btnQYCNS->Enabled = false;
        btnCIQ->Enabled = false;
        
  }

}

void __fastcall TDoForm::btnCancelClick(TObject *Sender)
{
  int nState;

  nState=m_enWorkState;
  m_enWorkState=EN_IDLE;
  ResetCtrl();
  clearInputDetail();
}
//---------------------------------------------------------------------------

void __fastcall TDoForm::btnOKClick(TObject *Sender)
{
  char strName[80],*ptr,strTemp[80];
  int nState;

  switch(m_enWorkState)
  {
    case EN_EDIT:
      if (-1 == ModHead())
        return;
      break;
    default:
      ShowMessage("Work State not AddNew or Edit");
      return;
  }

  m_enWorkState=EN_IDLE;
  ResetCtrl();
  clearInputDetail();
}
//---------------------------------------------------------------------------

void __fastcall TDoForm::cbDoingMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        CString szSQL;
        CString newStatus;
        if (cbDoing->Checked) {
                newStatus = "已接单";
        } else {
                if (m_strStatus != "已接单") {
                        ShowMessage(AnsiString("失败！当前状态: ")+AnsiString(m_strStatus));
                        return;
                }
                newStatus = "单证处理中";
        }

        szSQL.Format("update customs set status='%s' where cid='%s'", newStatus, edtCid->Text.c_str());
        if(!RunSQL(dm1->Query1,szSQL))
        {
                ShowMessage("update fail!") ;
                return;
        }
        m_strStatus =newStatus;
}
//---------------------------------------------------------------------------


void __fastcall TDoForm::lstViewClick(TObject *Sender)
{
        Row2Editor();
	ResetCtrlDetail();
        return;
      if(lstView->Selected == NULL){
//        return;

        btnAddDetail->Enabled = true;
        btnOkDetail->Enabled = false;
        btnCancleDetail->Enabled = false;
         btnModDetail->Enabled = false;
         btnDelDetail->Enabled = false;
        cbbMname->Text = "";
        edtMCode->Text = "";
        edtSpec->Text = "";
        edtFirstmeasunit->Text ="";
        edtSecondmeasunit->Text ="";
        edtNetWeight1->Text ="";
        edtGrossWeight1->Text ="";
        edtCount1->Text ="";
        edtCasecnt->Text = "";
        cbbPkName->Text  = "";
        edtCount2nd->Text = "0";
        edtUnitprice->Text ="";
        edtCdid->Text ="";

      }

}
//---------------------------------------------------------------------------
void TDoForm::flushContainer(AnsiString c){
        lstViewContainer->Items->Clear();

        char cnt[10];memset(cnt,sizeof(cnt),0x00);
        char body[2048];memset(body,sizeof(body),0x00);
        sscanf(c.c_str(),"%[^|]|",cnt);
        sscanf(c.c_str(),"%*[^|]|%[^@]",body);

        char strTmp1[2048];
        memset(strTmp1,sizeof(strTmp1),0x00);
        strcpy(strTmp1,body);
        int num = StrToInt(cnt);
        for (int i =0; i<num; ++i){
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

                TListItem *pItem =lstViewContainer->Items->Add();
                assert(pItem!=NULL);
                pItem->Caption=AnsiString(str3);
                pItem->SubItems->Add(AnsiString(str4));
                pItem->SubItems->Add(AnsiString(strSealId));
        }
}
void __fastcall TDoForm::btnDelDetailClick(TObject *Sender)
{

        if (lstView->Selected == NULL) {
                ShowMessage("请在下区选择需要修改的商品记录");
                return;
        }
        char strMsg[256];
        sprintf(strMsg,"\n  真要删除“%s”的记录吗？  \n",lstView->Selected->SubItems->Strings[0].c_str());
        if(Application->MessageBox(strMsg,"警告",MB_YESNOCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2)!=IDYES)
                return;

        CString szSQL;
        szSQL = "delete from customs_detail where cdid="; szSQL += Str2DBString(edtCdid->Text.c_str());

        if(!RunSQL(dm1->Query1,szSQL))
        {
                ShowMessage("delete fail!") ;
                return;
        }
        ShowMessage("删除成功");
//        lstView->Selected->Delete();
  TListItem *pItem;
  pItem=lstView->Selected;
  if(pItem!=NULL)
  {
  	int nSel=lstView->Items->IndexOf(pItem);
    lstView->Items->Delete(nSel);
    lstView->Selected=NULL;
  }
        flushSum();
        clearInputDetail();

  m_enWorkStateDetail=EN_IDLE_D;
  ResetCtrlDetail();

}
//---------------------------------------------------------------------------

void __fastcall TDoForm::Button1Click(TObject *Sender)
{
         this->TrayIcon1->Minimize();
}
//---------------------------------------------------------------------------
void TDoForm::ResetCtrlDetail()
{
  //对edtNo，商品资料项号，特殊处理，只允许添加时可输入。
  if (m_enWorkStateDetail == EN_ADDNEW_D){
        edtNo->Enabled = true;
        edtNo->Color = clWindow;
  }else{
        edtNo->Enabled = false;
        edtNo->Color = clScrollBar;
  }

  if(m_enWorkStateDetail==EN_IDLE_D)
  {
        cbbMname->Enabled						= false;
        edtMCode->Enabled           = false;
        edtSpec->Enabled            = false;
        edtFirstmeasunit->Enabled   = false;
        edtSecondmeasunit->Enabled  = false;
        edtUnitprice->Enabled       = false;
        edtTotalPrice->Enabled       = false;
        edtNetWeight1->Enabled      = false;
        edtGrossWeight1->Enabled    = false;
        edtCount1->Enabled          = false;
        edtCount2nd->Enabled        = false;
        edtCasecnt->Enabled         = false;
        cbbPkName->Enabled          = false;

        btnOkDetail->Enabled            = false;
        btnCancleDetail->Enabled       = false;
        btnAddDetail->Enabled           = true;
        lstView->Enabled                = true;
    if(lstView->Selected!=NULL)
    {
      btnModDetail->Enabled=true;
      btnDelDetail->Enabled=true;
    }
    else
    {
      btnModDetail->Enabled=false;
      btnDelDetail->Enabled=false;
    }
  }
  else
  {
        cbbMname->Enabled						= true;
        edtMCode->Enabled           = true;
        edtSpec->Enabled            = true;
        edtFirstmeasunit->Enabled   = true;
        edtSecondmeasunit->Enabled  = true;
        edtUnitprice->Enabled       = true;
        edtTotalPrice->Enabled       = true;
        edtNetWeight1->Enabled      = true;
        edtGrossWeight1->Enabled    = true;
        edtCount1->Enabled          = true;
        edtCount2nd->Enabled        = true;
        edtCasecnt->Enabled         = true;
        cbbPkName->Enabled          = true;
        
        btnOkDetail->Enabled            = true;
        btnCancleDetail->Enabled       = true;
        btnAddDetail->Enabled           = false;
        btnModDetail->Enabled           = false;
        btnDelDetail->Enabled           = false;
        lstView->Enabled                = false;
  }
}
void TDoForm::Row2Editor()
{
  TListItem *Item;

  Item=lstView->Selected;
  if(Item==NULL){
        edtNo->Text = "";
        cbbMname->Text = "";
        edtMCode->Text = "";
        edtSpec->Text = "";
        edtFirstmeasunit->Text ="";
        edtSecondmeasunit->Text ="";
        edtNetWeight1->Text ="";
        edtGrossWeight1->Text ="";
        edtCount1->Text ="";
        edtCasecnt->Text = "";
        cbbPkName->Text = "";
        edtCount2nd->Text = "0";
        edtUnitprice->Text ="";
        edtCdid->Text ="";
        return;
  }
        cbbMname->Text = Item->SubItems->Strings[0];
        edtMCode->Text = Item->Caption;
        edtSpec->Text = Item->SubItems->Strings[1];
        edtFirstmeasunit->Text =Item->SubItems->Strings[6];
        edtSecondmeasunit->Text =Item->SubItems->Strings[7];
        edtGrossWeight1->Text =Item->SubItems->Strings[3];
        edtCount1->Text =Item->SubItems->Strings[4];
        
        edtNetWeight1->Text =Item->SubItems->Strings[2];//20121117 一定要在count1后加载，否则会导致被count1.change逻辑覆盖
        edtCasecnt->Text = Item->SubItems->Strings[5];
        edtCount2nd->Text = Item->SubItems->Strings[13];
        edtUnitprice->Text = Item->SubItems->Strings[9];
        cbbPkName->Text =Item->SubItems->Strings[14];
        edtCdid->Text = Item->SubItems->Strings[15];}
//---------------------------------------------------------------------------








void __fastcall TDoForm::btnOkDetailClick(TObject *Sender)
{
  //task work
  if(m_enWorkStateDetail==EN_ADDNEW_D)
  {
        if (-1 == addDetail())
        {
                return ;
        }
  }
  else if(m_enWorkStateDetail==EN_EDIT_D)
  {
        if (-1 == modDetail())
        {
                return ;
        }
  }

  //flush data
  TListItem *pItem;
  if(m_enWorkStateDetail==EN_ADDNEW_D)
  {
        //do inside  for new_cdid
/*
        pItem=lstView->Items->Add();
        assert(pItem!=NULL);
        pItem->Caption=edtMCode->Text;
        pItem->SubItems->Add(cbbMname->Text);
        pItem->SubItems->Add(edtSpec->Text);
        pItem->SubItems->Add(edtNetWeight1->Text);
        pItem->SubItems->Add(edtGrossWeight1->Text);
        pItem->SubItems->Add(edtCount1->Text);
        pItem->SubItems->Add(edtCasecnt->Text);
        pItem->SubItems->Add(edtFirstmeasunit->Text);
        pItem->SubItems->Add(edtSecondmeasunit->Text);
        pItem->SubItems->Add(cbbTargetCountry->Text);
        pItem->SubItems->Add(edtUnitprice->Text);
        double total_w = StrToFloat(edtUnitprice->Text.c_str()) * StrToFloat(edtCount1->Text.c_str());
//        pItem->SubItems->Add(StrToInt(edtUnitprice->Text.c_str()) * StrToInt(edtCount1->Text.c_str()));
        pItem->SubItems->Add(total_w);
        pItem->SubItems->Add(cbbCurrency->Text);
        pItem->SubItems->Add(cbbZhengmian->Text);
        pItem->SubItems->Add(edtCount2nd->Text);
        pItem->SubItems->Add(strDate0);

        flushSum();
        clearInputDetail();
        lstView->Selected=pItem;
*/
  }
  else if(m_enWorkStateDetail==EN_EDIT_D)
  {
  	pItem=lstView->Selected;
    if(pItem!=NULL)
    {
        char strDate0[80];
   	sprintf(strDate0,"%s", pItem->SubItems->Strings[15]);
        double totalPrice = StrToFloat(edtUnitprice->Text.c_str()) * StrToFloat(edtCount1->Text.c_str());
	pItem->Caption                          = edtMCode->Text;
	pItem->SubItems->Strings[0]  = cbbMname->Text;
	pItem->SubItems->Strings[1]  = edtSpec->Text;
	pItem->SubItems->Strings[2]  = edtNetWeight1->Text;
	pItem->SubItems->Strings[3]  = edtGrossWeight1->Text;
	pItem->SubItems->Strings[4]  = edtCount1->Text;
	pItem->SubItems->Strings[5]  = edtCasecnt->Text;
	pItem->SubItems->Strings[6]  = edtFirstmeasunit->Text;
	pItem->SubItems->Strings[7]  = edtSecondmeasunit->Text;
	pItem->SubItems->Strings[8]  = cbbTargetCountry->Text;
	pItem->SubItems->Strings[9]  =  edtUnitprice->Text;
	pItem->SubItems->Strings[10]  = totalPrice;
	pItem->SubItems->Strings[11]  =  cbbCurrency->Text;
	pItem->SubItems->Strings[12]  =  cbbZhengmian->Text;
	pItem->SubItems->Strings[13]  =  edtCount2nd->Text;
        pItem->SubItems->Strings[14]  =  cbbPkName->Text;

	pItem->SubItems->Strings[15]  =  strDate0;
//        lstView->Selected = NULL;
//        lstViewClick(Sender);
        flushSum();
        clearInputDetail();
    }
  }


  m_enWorkStateDetail=EN_IDLE_D;
  ResetCtrlDetail();

}
//---------------------------------------------------------------------------

void __fastcall TDoForm::btnCancleDetailClick(TObject *Sender)
{
  m_enWorkStateDetail=EN_IDLE_D;
  ResetCtrlDetail();
  Row2Editor();
  edtNo->Text = "";
}
//---------------------------------------------------------------------------

int TDoForm::addDetail()
{
  if (edtNetWeight1->Text.IsEmpty()){
        if (!edtGrossWeight1->Text.IsEmpty() && !edtCasecnt->Text.IsEmpty()){
         float gw = StrToFloat(edtGrossWeight1->Text);
         float cn = StrToFloat(edtCasecnt->Text);
          if (gw < cn){
             ShowMessage("毛重应大于箱数");
              return -1;
            }
            float default_nw = gw-cn;
           edtNetWeight1->Text = FloatToStr(default_nw);
        }
  }
  if(edtCid->Text.IsEmpty()||edtMCode->Text.IsEmpty()||cbbMname->Text.IsEmpty()||\
        edtFirstmeasunit->Text.IsEmpty()||edtUnitprice->Text.IsEmpty()||\
        edtNetWeight1->Text.IsEmpty()||edtGrossWeight1->Text.IsEmpty()||edtCount1->Text.IsEmpty()||edtCasecnt->Text.IsEmpty()||cbbPkName->Text.IsEmpty())
  {
  	ShowMessage("请输入信息");
    if(cbbMname->CanFocus())	cbbMname->SetFocus();
    return -1;
  }
  if (cbbTargetCountry->Text.IsEmpty()) {
        ShowMessage("请输入运抵国");
    return -1;
  }
  if (edtFirstmeasunit->Text == "KG" ){
     if (edtCount1->Text != edtNetWeight1->Text){
        ShowMessage("第一数量与净重不符");
        return -1;
     }
  }
  if ( edtSecondmeasunit->Text == "KG" ) {
     if (edtCount2nd->Text != edtNetWeight1->Text){
        ShowMessage("第二数量与净重不符");
        return -1;
     }

  }
      CString szSQL;
      szSQL.Format("select * from customs_detail  where cdid like '%s__' and cmid='%s'", edtCid->Text.c_str(), edtMid1->Text.c_str());
      RunSQL(szSQL,true);
      if(dm1->Query1->RecordCount>0)
      {
        ShowMessage("表体已有该商品的记录!");
        return -1;
      }
      //gen new cdid
      szSQL.Format("select isnull((cast(substring(max(cdid),11,2) as decimal) +1),1) as new_cdid  from customs_detail where cdid like '%s__'", edtCid->Text.c_str());
      RunSQL(szSQL,true);
      int new_cdid = 1;
      if(!dm1->Query1->Eof)
      {
        new_cdid = dm1->Query1->FieldByName("new_cdid")->AsInteger;

      }      //qry max cdid for gen new cdid
//        Edit1->Text = AnsiString(szSQL);
      //~

  //毛重>净重
  if  (StrToFloat(edtNetWeight1->Text.c_str()) > StrToFloat(edtGrossWeight1->Text.c_str()) ) {
        ShowMessage("毛重必须大于净重");
        return -1;
  }

        char strDate0[80];
//   	sprintf(strDate0,"%s%02d",edtCid->Text.c_str(),lstView->Items->Count+1);
   	sprintf(strDate0,"%s%02d",edtCid->Text.c_str(), new_cdid);
        szSQL="insert into customs_detail(cdid,cmid,netweight,grossweight,\
                                        count,count2,casescnt,targetcountry,\
                                        cunitprice,zhengmian,pkname) values(";
        szSQL += Str2DBString(strDate0);
szSQL +=","; szSQL += Str2DBString(edtMid1->Text.c_str());
szSQL +=","; szSQL += Str2DBString(edtNetWeight1->Text.c_str());
szSQL +=","; szSQL += Str2DBString(edtGrossWeight1->Text.c_str());
szSQL +=","; szSQL += Str2DBString(edtCount1->Text.c_str());
edtCount2nd->Text = (edtCount2nd->Text.IsEmpty()?"0":edtCount2nd->Text.c_str());
//szSQL +=","; szSQL += Str2DBString(edtCount2nd->Text.IsEmpty()?0:edtCount2nd->Text.c_str());
szSQL +=","; szSQL += Str2DBString(edtCount2nd->Text.c_str());
szSQL +=","; szSQL += Str2DBString(edtCasecnt->Text.c_str());
szSQL +=","; szSQL += Str2DBString(cbbTargetCountry->Text.c_str());
szSQL +=","; szSQL += Str2DBString(edtUnitprice->Text.c_str());
szSQL +=","; szSQL += Str2DBString(cbbZhengmian->Text.c_str());
szSQL +=","; szSQL += Str2DBString(cbbPkName->Text.c_str());
szSQL +=")";

//        Edit1->Text = AnsiString(szSQL);
        if(!RunSQL(dm1->Query1,szSQL))
        {
                ShowMessage("insert fail!") ;
                return -1;
        }

//        btnQueryUpClick(Sender);    //del 0106
        //data refresh, should be done outside!!
 
        TListItem *pItem =lstView->Items->Add();
        assert(pItem!=NULL);
        pItem->Caption=edtMCode->Text;
        pItem->SubItems->Add(cbbMname->Text);
        pItem->SubItems->Add(edtSpec->Text);
        pItem->SubItems->Add(edtNetWeight1->Text);
        pItem->SubItems->Add(edtGrossWeight1->Text);
        pItem->SubItems->Add(edtCount1->Text);
        pItem->SubItems->Add(edtCasecnt->Text);
        pItem->SubItems->Add(edtFirstmeasunit->Text);
        pItem->SubItems->Add(edtSecondmeasunit->Text);
        pItem->SubItems->Add(cbbTargetCountry->Text);
        pItem->SubItems->Add(edtUnitprice->Text);
        double total_w = StrToFloat(edtUnitprice->Text.c_str()) * StrToFloat(edtCount1->Text.c_str());
//        pItem->SubItems->Add(StrToInt(edtUnitprice->Text.c_str()) * StrToInt(edtCount1->Text.c_str()));
        pItem->SubItems->Add(total_w);
        pItem->SubItems->Add(cbbCurrency->Text);
        pItem->SubItems->Add(cbbZhengmian->Text);
        pItem->SubItems->Add(edtCount2nd->Text);
        pItem->SubItems->Add(cbbPkName->Text);
        pItem->SubItems->Add(strDate0);
        lstView->Selected=pItem;

        flushSum();
        clearInputDetail();

        ShowMessage("添加成功");
        return 0;
}

int TDoForm::modDetail(){

       if (lstView->Selected == NULL) {
                ShowMessage("请在下区选择需要修改的商品记录");
                return -1;
        }

  if (edtNetWeight1->Text.IsEmpty()){
        if (!edtGrossWeight1->Text.IsEmpty() && !edtCasecnt->Text.IsEmpty()){
         double gw = StrToFloat(edtGrossWeight1->Text);
          double cn = StrToFloat(edtCasecnt->Text);
          if (gw < cn){
             ShowMessage("毛重应大于箱数");
              return -1;
            }
            double default_nw = gw-cn;
           edtNetWeight1->Text = default_nw;// IntToStr(default_nw);
        }
  }
  //毛重>净重
  if  (StrToFloat(edtNetWeight1->Text.c_str()) > StrToFloat(edtGrossWeight1->Text.c_str()) ) {
        ShowMessage("毛重必须大于净重");
        return -1;
  }
  if (edtFirstmeasunit->Text == "KG" ){
     if (edtCount1->Text != edtNetWeight1->Text){
        ShowMessage("第一数量与净重不符");
        return -1;
     }
  }
  //20120718
  if ( edtSecondmeasunit->Text == "KG" ) {
     if (edtCount2nd->Text != edtNetWeight1->Text){
        ShowMessage("第二数量与净重不符");
        return -1;
     }

  }

        char strDate0[80];
//   	sprintf(strDate0,"%s%02d",edtCid->Text.c_str(),lstView->Items->Count+1);
   	sprintf(strDate0,"%s", lstView->Selected->SubItems->Strings[15]);

        CString szSQL;
        szSQL = "update customs_detail set ";
//        szSQL += Str2DBString(strDate0);
szSQL +="netweight="; szSQL += Str2DBString(edtNetWeight1->Text.c_str());
szSQL +=",grossweight="; szSQL += Str2DBString(edtGrossWeight1->Text.c_str());
szSQL +=",count="; szSQL += Str2DBString(edtCount1->Text.c_str());
edtCount2nd->Text = (edtCount2nd->Text.IsEmpty()?"0":edtCount2nd->Text.c_str());
szSQL +=",count2="; szSQL += Str2DBString(edtCount2nd->Text.c_str());
szSQL +=",casescnt="; szSQL += Str2DBString(edtCasecnt->Text.c_str());
szSQL +=",cunitprice="; szSQL += edtUnitprice->Text.c_str();
szSQL +=",pkname="; szSQL += Str2DBString(cbbPkName->Text.c_str());
szSQL +=",targetcountry="; szSQL += Str2DBString(cbbTargetCountry->Text.c_str());


if (!cbbMname->Text.IsEmpty()){           //20121214
        szSQL += ",cmid=(select mid from merchandise where mname = ";
        szSQL += Str2DBString(cbbMname->Text.c_str());
        szSQL += ")";
}
szSQL +=" where cdid ="; szSQL+=  Str2DBString(strDate0);
//szSQL += " and cmid="; szSQL+= Str2DBString(edtMid1->Text.c_str());

        Edit1->Text = AnsiString(szSQL);
        if(!RunSQL(dm1->Query1,szSQL))
        {
                ShowMessage("update fail!") ;

                return -1;
        }
        ShowMessage("修改成功");
//        btnQueryUpClick(Sender);
/*
        TListItem *pItem =lstView->Items->Add();
        assert(pItem!=NULL);
        pItem->Caption=edtMCode->Text;
        pItem->SubItems->Add(cbbMname->Text);
        pItem->SubItems->Add(edtSpec->Text);
        pItem->SubItems->Add(edtNetWeight1->Text);
        pItem->SubItems->Add(edtGrossWeight1->Text);
        pItem->SubItems->Add(edtCount1->Text);
        pItem->SubItems->Add(edtCasecnt->Text);
        pItem->SubItems->Add(edtFirstmeasunit->Text);
        pItem->SubItems->Add(edtSecondmeasunit->Text);
        pItem->SubItems->Add(cbbTargetCountry->Text);
        pItem->SubItems->Add(edtUnitprice->Text);
//        pItem->SubItems->Add(StrToInt(edtUnitprice->Text.c_str()) * StrToInt(edtCount1->Text.c_str()));
        double totalPrice = StrToFloat(edtUnitprice->Text.c_str()) * StrToInt(edtCount1->Text.c_str());
        pItem->SubItems->Add(totalPrice);//0131
        pItem->SubItems->Add(cbbCurrency->Text);
        pItem->SubItems->Add(cbbZhengmian->Text);
        pItem->SubItems->Add(edtCount2nd->Text);
        pItem->SubItems->Add(strDate0);

        lstView->Selected->Delete();
*/

//flush data, done outside
/*
//        double totalPrice = StrToFloat(edtUnitprice->Text.c_str()) * StrToInt(edtCount1->Text.c_str());
        double totalPrice = StrToFloat(edtUnitprice->Text.c_str()) * StrToFloat(edtCount1->Text.c_str());
lstView->Selected->Caption                          = edtMCode->Text;
lstView->Selected->SubItems->Strings[0]  = cbbMname->Text;
lstView->Selected->SubItems->Strings[1]  = edtSpec->Text;
lstView->Selected->SubItems->Strings[2]  = edtNetWeight1->Text;
lstView->Selected->SubItems->Strings[3]  = edtGrossWeight1->Text;
lstView->Selected->SubItems->Strings[4]  = edtCount1->Text;
lstView->Selected->SubItems->Strings[5]  = edtCasecnt->Text;
lstView->Selected->SubItems->Strings[6]  = edtFirstmeasunit->Text;
lstView->Selected->SubItems->Strings[7]  = edtSecondmeasunit->Text;
lstView->Selected->SubItems->Strings[8]  = cbbTargetCountry->Text;
lstView->Selected->SubItems->Strings[9]  =  edtUnitprice->Text;
lstView->Selected->SubItems->Strings[10]  = totalPrice;
lstView->Selected->SubItems->Strings[11]  =  cbbCurrency->Text;
lstView->Selected->SubItems->Strings[12]  =  cbbZhengmian->Text;
lstView->Selected->SubItems->Strings[13]  =  edtCount2nd->Text;
lstView->Selected->SubItems->Strings[14]  =  strDate0;


//        lstView->Selected = NULL;
        lstViewClick(Sender);
        flushSum();
        clearInputDetail();
*/
}
void TDoForm::prnContactMain(CString last_cdid, bool isHasSub){
        TPrnContactForm *pForm;
 	pForm=new TPrnContactForm(this);
        assert(pForm!=NULL);

        //header
        pForm->qrlSubFlag->Caption = isHasSub?"有附页":"";
        pForm->qrlSubFlag2->Caption = isHasSub?"(详见清单)":"";
//        pForm->qrlOperUnit->Caption = edtOperunit->Text;

        CString szSQLOperunit;
	szSQLOperunit.Format("select * from DicOperunit where name = '%s'", cbbOperunit->Text.c_str());
	RunSQL(dm1->Query1,szSQLOperunit,true);

	while(!dm1->Query1->Eof)
	{
                pForm->qrlOperUnit->Caption = dm1->Query1->FieldByName("name")->AsString;
                pForm->qrlOperUnitAddress->Caption = dm1->Query1->FieldByName("address")->AsString;
                pForm->qrlOperUnitTel->Caption = dm1->Query1->FieldByName("tel")->AsString;

		dm1->Query1->Next();
        }

        pForm->qrlContactId->Caption = edtContractid->Text;
        pForm->qrlBargain->Caption = cbbBargain->Text;
 //       pForm->qrlForwardingUnit->Caption = edtForwardingunit->Text;
        //日期 = 打印日期 - 30天
        unsigned short year1,month1,day1;
        dtpValidDate->Date = Now() - 20;
        dtpValidDate->DateTime.DecodeDate(&year1,&month1,&day1);
        pForm->qrlY->Caption = IntToStr(year1);
        pForm->qrlM->Caption = IntToStr(month1);
        pForm->qrlD->Caption = IntToStr(day1);
//        pForm->qrlSH->Caption = cbbSH->Text;

        CString szSQLSH;
	szSQLSH.Format("select * from DicSH where name = '%s'", cbbSH->Text.c_str());
	RunSQL(dm1->Query1,szSQLSH,true);

	while(!dm1->Query1->Eof)
	{
                pForm->qrlSH->Caption = dm1->Query1->FieldByName("name")->AsString;
                pForm->qrlSHAddress->Caption = dm1->Query1->FieldByName("address")->AsString;
                pForm->qrlSHTel->Caption = dm1->Query1->FieldByName("tel")->AsString;

		dm1->Query1->Next();
        }

        pForm->qrlPack->Caption = cbbPack->Text;

        pForm->qrlOutport->Caption = edtOutport->Text;

        pForm->qrlTargetCountry->Caption = cbbTargetCountry->Text;
        pForm->qrlExcharge->Caption = cbbExcharge->Text;
        pForm->qrlTotal->Caption = Label44->Caption;
        pForm->qrlTotalDaXie->Caption = ConvertInt(Label44->Caption);



        //detali
        CString szSQL;
	szSQL.Format("select mname,count,firstmeasunit FU,cunitprice, convert(numeric(10,2),count*cunitprice) total , '%s' as currency from \
                        customs_detail a, merchandise b where cdid like '%s__' and cdid <= '%s' and a.cmid=b.mid order by a.cdid", \
                        cbbCurrencyId->Text.c_str(),edtCid->Text.c_str(), last_cdid);
	RunSQL(dm1->sqlPrint,szSQL,true);
        pForm->PrnView->PreviewModal() ;
        delete pForm;

}

void TDoForm::prnContactSub(CString last_page_last_cdid){
       TPrnContactSubForm *pForm;
 	pForm=new TPrnContactSubForm(this);
        assert(pForm!=NULL);
        //detali
        pForm->qrlContactId->Caption = edtContractid->Text;        
        CString szSQL;
	szSQL.Format("select mname,count,firstmeasunit FU,cunitprice, convert(numeric(10,2),count*cunitprice) total , '%s' as currency from \
                        customs_detail a, merchandise b where cdid like '%s__' and cdid >'%s' and a.cmid=b.mid order by a.cdid", \
                        cbbCurrencyId->Text.c_str(),edtCid->Text.c_str(), last_page_last_cdid);
	RunSQL(dm1->sqlPrint,szSQL,true);
        pForm->PrnView->PreviewModal() ;
        delete pForm;
}
void TDoForm::prnDeclare(AnsiString begin_cid, AnsiString end_cid, AnsiString split_detail, int page_ord, bool isTail){
        TPrnDeclareForm *pForm;
 	pForm=new TPrnDeclareForm(this);
        assert(pForm!=NULL);
        pForm->m_nStep = page_ord * COL_PER_PAGE_PRN_DECLARE;
        pForm->qrlCid->Caption = edtCid->Text;
        pForm->qrlSubFlag->Caption = split_detail;//isHasSub?"有附页":"";
//        pForm->qrlSubFlag2->Caption = pForm->qrlSubFlag->Caption;
        pForm->qrlDeclareId->Caption = edtDeclareid->Text;
        //只显示最后9位
        pForm->qrlDeclareId->Caption = (edtDeclareid->Text.Length() > 9)? \
                                        edtDeclareid->Text.SubString(edtDeclareid->Text.Length()-9+1,9):edtDeclareid->Text;


//        pForm->qrlOperUnit->Caption = edtOperunit->Text;
        pForm->qrlOperUnit->Caption = cbbOperunit->Text;
        pForm->qrlForwardingUnit->Caption = edtForwardingunit->Text;

        pForm->qrlForwardingUnit->Caption = edtForwardingunit->Text;
        pForm->qrlManufacturer->Caption = edtManufacturer->Text;
        pForm->qrlAttacheDoc->Caption = edtAttachedoc->Text;

        pForm->qrlTransport->Caption = cbbTransport->Text;
        pForm->qrlBoatNo->Caption = edtBoatno->Text;
        pForm->qrlBoatOrder->Caption = edtBoatorder->Text;
        pForm->qrlLadingId->Caption = edtLoadingid->Text;
        pForm->qrlTrade->Caption = cbbTrade->Text;
        pForm->qrlExcharge->Caption = cbbExcharge->Text;
        pForm->qrlTargetCountry->Caption = cbbTargetCountry->Text;
        pForm->qrlAssginPort->Caption = cbbAssginPort->Text;
        pForm->qrlInnersupplyadd->Caption = edtInnersupplyadd->Text;
        pForm->qrlLicenseNo->Caption = edtLicenseno->Text;
        pForm->qrlBargain->Caption = cbbBargain->Text;
        pForm->qrlContractId->Caption = edtContractid->Text;
        pForm->qrlCount->Caption = edtCount->Text;
        pForm->qrlPack->Caption = cbbPack->Text;
        pForm->qrlNetWeight->Caption = edtNetweight->Text;
        pForm->qrlGrossWeight->Caption = Label42->Caption;
        pForm->qrlMarks->Caption = edtMarks->Text;
        pForm->qrlZhengMian->Caption = cbbZhengmian->Text;
        pForm->qrlCarriage->Caption = edtCarriage->Text;
        pForm->qrlInsurance->Caption = edtInsurance->Text;

        //生成箱号打印格式
        genContainerInfo4PrnDeclare(AnsiString(m_strContainerInfo));
        pForm->qrlContainerHead->Caption = AnsiString(m_strContainerHead);
        pForm->qrlContainerTail->Caption = AnsiString(m_strContainerTail);

        pForm->qrlCurrency->Caption = cbbCurrencyId->Text;
        pForm->qrlCurrency2->Caption = cbbCurrencyId->Text;
        //total
        pForm->qrlTotal->Caption = Label44->Caption.c_str();
        //main-detail show logic
        if (!isTail){
                pForm->QRLabel4->Caption = "";
                pForm->qrlCurrency2->Caption = "";
                pForm->qrlTotal->Caption = "";
        }
        //detali
         CString szSQL;
/*	szSQL.Format("select targetcountry ,spec,cdid, mcode,mname,count,firstmeasunit FU, \
        dbo.cut_count(count2) as cnt2, \
        case count2 when 0 then '' else secondmeasunit  end as SU,cunitprice,\
        dbo.cut_total(count*cunitprice) as total \
         from customs_detail a,merchandise b \
         where a.cdid like '%s__' and '%s' <= a.cdid and a.cdid <= '%s' and a.cmid=b.mid order by cdid", edtCid->Text.c_str(), begin_cid, end_cid);

*/
	szSQL.Format("select (select count(*)+1 from customs_detail aa \
        where aa.cdid like '%s__' and aa.cdid < a.cdid ) as row_ord, targetcountry ,spec,cdid, mcode,mname,count,firstmeasunit FU, \
        dbo.cut_count(count2) as cnt2, \
        case count2 when 0 then '' else secondmeasunit  end as SU,cunitprice,\
        dbo.cut_total(count*cunitprice) as total \
         from customs_detail a,merchandise b \
         where a.cdid like '%s__' and '%s' <= a.cdid and a.cdid <= '%s' and a.cmid=b.mid order by cdid", edtCid->Text.c_str(), edtCid->Text.c_str(), begin_cid, end_cid);

	RunSQL(dm1->sqlPrintDeclare,szSQL,true);

        pForm->PrnView->PreviewModal() ;
//        pForm->PrnView->NewPage();
        delete pForm;
}
void TDoForm::prnDeclareMain(CString last_cdid, bool isHasSub){
       TPrnDeclareForm *pForm;
 	pForm=new TPrnDeclareForm(this);
        assert(pForm!=NULL);

       pForm->qrlCid->Caption = edtCid->Text;
        pForm->qrlSubFlag->Caption = isHasSub?"有附页":"";
        pForm->qrlDeclareId->Caption = edtDeclareid->Text;
        //只显示最后9位
        pForm->qrlDeclareId->Caption = (edtDeclareid->Text.Length() > 9)? \
                                        edtDeclareid->Text.SubString(edtDeclareid->Text.Length()-9+1,9):edtDeclareid->Text;


//        pForm->qrlOperUnit->Caption = edtOperunit->Text;
        pForm->qrlOperUnit->Caption = cbbOperunit->Text;
        pForm->qrlForwardingUnit->Caption = edtForwardingunit->Text;

        pForm->qrlForwardingUnit->Caption = edtForwardingunit->Text;
        pForm->qrlManufacturer->Caption = edtManufacturer->Text;
        pForm->qrlAttacheDoc->Caption = edtAttachedoc->Text;

        pForm->qrlTransport->Caption = cbbTransport->Text;
        pForm->qrlBoatNo->Caption = edtBoatno->Text;
        pForm->qrlBoatOrder->Caption = edtBoatorder->Text;
        pForm->qrlLadingId->Caption = edtLoadingid->Text;
        pForm->qrlTrade->Caption = cbbTrade->Text;
        pForm->qrlExcharge->Caption = cbbExcharge->Text;
        pForm->qrlTargetCountry->Caption = cbbTargetCountry->Text;
        pForm->qrlAssginPort->Caption = cbbAssginPort->Text;
        pForm->qrlInnersupplyadd->Caption = edtInnersupplyadd->Text;
        pForm->qrlLicenseNo->Caption = edtLicenseno->Text;
        pForm->qrlBargain->Caption = cbbBargain->Text;
        pForm->qrlContractId->Caption = edtContractid->Text;
        pForm->qrlCount->Caption = edtCount->Text;
        pForm->qrlPack->Caption = cbbPack->Text;
        pForm->qrlNetWeight->Caption = edtNetweight->Text;
        pForm->qrlGrossWeight->Caption = Label42->Caption;
        pForm->qrlMarks->Caption = edtMarks->Text;
        pForm->qrlZhengMian->Caption = cbbZhengmian->Text;
        pForm->qrlCarriage->Caption = edtCarriage->Text;
        pForm->qrlInsurance->Caption = edtInsurance->Text;
//ShowMessage(AnsiString(m_strContainerInfo));
        //生成箱号打印格式
        genContainerInfo4PrnDeclare(AnsiString(m_strContainerInfo));
        pForm->qrlContainerHead->Caption = AnsiString(m_strContainerHead);
        pForm->qrlContainerTail->Caption = AnsiString(m_strContainerTail);

        pForm->qrlCurrency->Caption = cbbCurrencyId->Text;
        pForm->qrlCurrency2->Caption = cbbCurrencyId->Text;
        //total
        pForm->qrlTotal->Caption = Label44->Caption.c_str();

        //detali
         CString szSQL;
/*
	szSQL.Format("select targetcountry ,spec,cdid, mcode,mname,count,firstmeasunit FU,\
        case count2 when 0 then '' else cast(count2 as varchar(10)) end as cnt2,\
        case count2 when 0 then '' else secondmeasunit  end as SU,cunitprice,\
         cast(count*cunitprice as decimal(10,2)) as total \
         from customs_detail a,merchandise b \
         where a.cdid like '%s__' and a.cdid <= '%s' and a.cmid=b.mid order by cdid", edtCid->Text.c_str(), last_cdid);
*/

	szSQL.Format("select targetcountry ,spec,cdid, mcode,mname,count,firstmeasunit FU, \
        dbo.cut_count(count2) as cnt2, \
        case count2 when 0 then '' else secondmeasunit  end as SU,cunitprice,\
        dbo.cut_total(count*cunitprice) as total \
         from customs_detail a,merchandise b \
         where a.cdid like '%s__' and a.cdid <= '%s' and a.cmid=b.mid order by cdid", edtCid->Text.c_str(), last_cdid);
//Edit1->Text = AnsiString(szSQL);
	RunSQL(dm1->sqlPrint,szSQL,true);

        pForm->PrnView->PreviewModal() ;
        delete pForm;

}

void TDoForm::prnDeclareSub(CString last_page_last_cdid){
       TPrnDeclareSubForm *pForm;
 	pForm=new TPrnDeclareSubForm(this);
        assert(pForm!=NULL);

        pForm->qrlCid->Caption = edtCid->Text;
        pForm->qrlCurrency->Caption = cbbCurrencyId->Text;
        //detali
        CString szSQL;
	szSQL.Format("select targetcountry ,spec,cdid, mcode,mname,count,firstmeasunit FU,\
        dbo.cut_count(count2) as cnt2, \
        case count2 when 0 then '' else secondmeasunit  end as SU,cunitprice,\
        dbo.cut_total(count*cunitprice) as total \
         from customs_detail a,merchandise b \
         where a.cdid like '%s__' and a.cdid > '%s' and a.cmid=b.mid order by cdid", edtCid->Text.c_str(), last_page_last_cdid);

	RunSQL(dm1->sqlPrint,szSQL,true);
        pForm->PrnView->PreviewModal() ;
        delete pForm;
}















void __fastcall TDoForm::edtCount1Change(TObject *Sender)
{
        if (edtCount1->Text.IsEmpty()) {
                return;
        }
        edtUnitpriceChange(Sender);
//        int cnt1 = StrToInt(edtCount1->Text.c_str());
        //20121128 输入小数弹窗口问题
        double cnt1 = StrToFloat(edtCount1->Text.c_str());
        edtCount2nd->Text = FloatToStr( cnt1*StrToFloat(strWeightPercent.c_str()) );

        //净重=单位为KG的数量
        AnsiString strNetWeight=  "0";
        if (edtFirstmeasunit->Text == "KG"){
            strNetWeight = edtCount1->Text;
        }else if (edtSecondmeasunit->Text == "KG"){
             strNetWeight = edtCount2nd->Text;
        }
        edtNetWeight1->Text = strNetWeight;
}
//---------------------------------------------------------------------------

#include "PrnWuMuZhi.h"
void __fastcall TDoForm::btnWMZClick(TObject *Sender)
{
        if (lstView->Items->Count == 0) {
                ShowMessage("请完善表体信息");
                return ;
        }

        TPrnWuMuZhiForm *pForm;
 	pForm=new TPrnWuMuZhiForm(this);
        assert(pForm!=NULL);

//       pForm->qrlOperUnit->Caption = edtOperunit->Text;
       pForm->qrlOperUnit->Caption = cbbOperunit->Text;
       pForm->qrlTargetCountry->Caption = cbbTargetCountry->Text;
       pForm->qrlMname->Caption = lstView->Items->Item[0]->SubItems->Strings[0];
       pForm->qrlTotalNetWeight->Caption = Label42->Caption;
       pForm->qrlCountHead->Caption = edtCount->Text;
       
        pForm->PrnView->PreviewModal() ;
        delete pForm;
}
//---------------------------------------------------------------------------
               
#include "PrnYSQRS.h"
void __fastcall TDoForm::btnYSQRSClick(TObject *Sender)
{
        if (lstView->Items->Count == 0) {
                ShowMessage("请完善表体信息");
                return ;
        }

        TPrnYSQRSForm *pForm;
 	pForm=new TPrnYSQRSForm(this);
        assert(pForm!=NULL);

//       pForm->qrlOperUnit->Caption = edtOperunit->Text;
       pForm->qrlOperUnit->Caption = cbbOperunit->Text;
//       pForm->qrlOperUnit2->Caption = edtOperunit->Text;
       pForm->qrlOperUnit2->Caption = cbbOperunit->Text;
       pForm->qrlMname->Caption = lstView->Items->Item[0]->SubItems->Strings[0];
       pForm->qrlCid->Caption = edtCid->Text;
       pForm->qrlSH->Caption = cbbSH->Text;


        unsigned short year0,month0,day0;
        dtpValidDate->Date = Now();
	dtpValidDate->DateTime.DecodeDate(&year0,&month0,&day0);
        dtpValidDate->Date = Now() + 20;
        pForm->qrlNowY->Caption = IntToStr(year0);
        pForm->qrlNowM->Caption = IntToStr(month0);
        pForm->qrlNowD->Caption = IntToStr(day0);

        pForm->PrnView->PreviewModal() ;
        delete pForm;        
}
//---------------------------------------------------------------------------

#include "PrnSCCK.h"
void __fastcall TDoForm::btnSCCKClick(TObject *Sender)
{
        TPrnSCCKForm *pForm;
 	pForm=new TPrnSCCKForm(this);
        assert(pForm!=NULL);

        //header
        pForm->qrlSH->Caption = cbbSH->Text;
        pForm->qrlTargetCountry->Caption = cbbTargetCountry->Text;
        pForm->qrlForwardingunit->Caption = edtForwardingunit->Text;

        //detali
        CString szSQL;
	szSQL.Format("select mcode,mname,count,firstmeasunit,  convert(numeric(10,2),count*cunitprice) as price from \
                        customs_detail a, merchandise b where cdid like '%s__' and a.cmid=b.mid order by a.cdid",edtCid->Text.c_str());
	RunSQL(dm1->sqlPrint,szSQL,true);
        pForm->PrnView->PreviewModal() ;
        delete pForm;
}
//---------------------------------------------------------------------------

void __fastcall TDoForm::btnCIQClick(TObject *Sender)
{
//select mcode, mname, pkname, count, firstmeasunit, grossweight, netweight,cunitprice,cunitprice*count totalprice  from customs_detail a, merchandise b where cdid like '2022010101%' and a.cmid=b.mid

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
//                vSheet.OlePropertyGet("Rows",++iRows).OlePropertySet("RowHeight",72);//设置指定行的高度为28
                vSheet.OlePropertyGet("Cells").OlePropertySet("WrapText", true);//设置所有单元格的文本自动换行
                vSheet.OlePropertyGet("Columns").OlePropertySet("ColumnWidth",15);//设置所有列的列宽为28
                vSheet.OlePropertyGet("Rows",++iRows).OlePropertyGet("Font").OlePropertySet("Bold",true);//设置第一行第一列单元格的字体为粗体字

                vSheet.OlePropertyGet("Cells").OlePropertySet("RowHeight",22);//设置指定行的高度为28
                //表头
//                ++iRows;
                {
                        int icol=1;
                        vSheet.OlePropertyGet("Cells",iRows,icol++).OlePropertySet("Value","商品HS编码");
                        vSheet.OlePropertyGet("Cells",iRows,icol++).OlePropertySet("Value","商品中英文名称");
                        vSheet.OlePropertyGet("Cells",iRows,icol++).OlePropertySet("Value","生产厂家");
                        vSheet.OlePropertyGet("Cells",iRows,icol++).OlePropertySet("Value","商品材质");
                        vSheet.OlePropertyGet("Cells",iRows,icol++).OlePropertySet("Value","规格型号");
                        vSheet.OlePropertyGet("Cells",iRows,icol++).OlePropertySet("Value","包装方式");
                        vSheet.OlePropertyGet("Cells",iRows,icol++).OlePropertySet("Value","商品数量");
                        vSheet.OlePropertyGet("Cells",iRows,icol++).OlePropertySet("Value","计量单位");
                        vSheet.OlePropertyGet("Cells",iRows,icol++).OlePropertySet("Value","第二数量");
                        vSheet.OlePropertyGet("Cells",iRows,icol++).OlePropertySet("Value","第二数量单位");
                        vSheet.OlePropertyGet("Cells",iRows,icol++).OlePropertySet("Value","总净重KG");
                        vSheet.OlePropertyGet("Cells",iRows,icol++).OlePropertySet("Value","总毛重KG");
                        vSheet.OlePropertyGet("Cells",iRows,icol++).OlePropertySet("Value","成交方式");
                        vSheet.OlePropertyGet("Cells",iRows,icol++).OlePropertySet("Value","单价(CNY)");
                        vSheet.OlePropertyGet("Cells",iRows,icol++).OlePropertySet("Value","总价(CNY)");
                        vSheet.OlePropertyGet("Cells",iRows,icol++).OlePropertySet("Value","备注");

                        
                }
                //data

        CString szSQL;
	szSQL.Format("select casescnt, mcode, mname, pkname, count, firstmeasunit, count2, secondmeasunit, grossweight, netweight,cunitprice,cunitprice*count totalprice  \
                from customs_detail a, merchandise b \
                where cdid like '%%%s%%' and a.cmid=b.mid order by cdid", edtCid->Text.c_str());
	RunSQL(dm1->Query1,szSQL,true);


	while(!dm1->Query1->Eof)
	{
                ++iRows;
                iCols = 0;
                vSheet.OlePropertyGet("Cells",iRows,++iCols).OlePropertySet("Value",dm1->Query1->FieldByName("mcode")->AsString.c_str());
                vSheet.OlePropertyGet("Cells",iRows,++iCols).OlePropertySet("Value",dm1->Query1->FieldByName("mname")->AsString.c_str());
                vSheet.OlePropertyGet("Cells",iRows,++iCols).OlePropertySet("Value","");
                vSheet.OlePropertyGet("Cells",iRows,++iCols).OlePropertySet("Value","");
                vSheet.OlePropertyGet("Cells",iRows,++iCols).OlePropertySet("Value","");
                vSheet.OlePropertyGet("Cells",iRows,++iCols).OlePropertySet("Value",dm1->Query1->FieldByName("pkname")->AsString.c_str());
                vSheet.OlePropertyGet("Cells",iRows,++iCols).OlePropertySet("Value",dm1->Query1->FieldByName("count")->AsString.c_str());
                vSheet.OlePropertyGet("Cells",iRows,++iCols).OlePropertySet("Value",dm1->Query1->FieldByName("firstmeasunit")->AsString.c_str());
                vSheet.OlePropertyGet("Cells",iRows,++iCols).OlePropertySet("Value",dm1->Query1->FieldByName("casescnt")->AsString.c_str());//20121214
                vSheet.OlePropertyGet("Cells",iRows,++iCols).OlePropertySet("Value",dm1->Query1->FieldByName("secondmeasunit")->AsString.c_str());
                vSheet.OlePropertyGet("Cells",iRows,++iCols).OlePropertySet("Value",dm1->Query1->FieldByName("netweight")->AsString.c_str());
                vSheet.OlePropertyGet("Cells",iRows,++iCols).OlePropertySet("Value",dm1->Query1->FieldByName("grossweight")->AsString.c_str());
                vSheet.OlePropertyGet("Cells",iRows,++iCols).OlePropertySet("Value","FOB");
                vSheet.OlePropertyGet("Cells",iRows,++iCols).OlePropertySet("Value",dm1->Query1->FieldByName("cunitprice")->AsString.c_str());
                vSheet.OlePropertyGet("Cells",iRows,++iCols).OlePropertySet("Value",dm1->Query1->FieldByName("totalprice")->AsString.c_str());
//                vSheet.OlePropertyGet("Cells",iRows,++iCols).OlePropertySet("Value",edtMarks->Text.c_str());
                vSheet.OlePropertyGet("Cells",iRows,++iCols).OlePropertySet("Value","");

		dm1->Query1->Next();
        }
                //加框
//                AnsiString strRange = "A"+IntToStr(2)+":"+AnsiString(NumbertoString(lstViewPure->Columns->Count+1))+IntToStr(iRows);
                AnsiString strRange = "A1:P"+IntToStr(iRows);
                vRange = vSheet.OlePropertyGet("Range",strRange.c_str());
                vRange.OlePropertySet("VerticalAlignment", 3);
                vRange.OlePropertySet("HorizontalAlignment", 3);
                vBorders = vRange.OlePropertyGet("Borders");
                vBorders.OlePropertySet("linestyle",xlContinuous);
                vBorders.OlePropertySet("weight",xlThin);
                vBorders.OlePropertySet("colorindex",xlAutomatic);

        } catch(...){

        }
}
//---------------------------------------------------------------------------

#include "PrnQYCNS.h"
void __fastcall TDoForm::btnQYCNSClick(TObject *Sender)
{
 if (lstView->Items->Count == 0) {
                ShowMessage("请完善表体信息");
                return ;
        }

        TPrnQYCNSForm *pForm;
 	pForm=new TPrnQYCNSForm(this);
        assert(pForm!=NULL);

//       pForm->qrlOperUnit->Caption = edtOperunit->Text;
       pForm->qrlOperUnit->Caption = cbbOperunit->Text;

        unsigned short year0,month0,day0;
        dtpValidDate->Date = Now();
	dtpValidDate->DateTime.DecodeDate(&year0,&month0,&day0);
        dtpValidDate->Date = Now() + 20;
        pForm->qrlNowY->Caption = IntToStr(year0);
        pForm->qrlNowM->Caption = IntToStr(month0);
        pForm->qrlNowD->Caption = IntToStr(day0);

        pForm->PrnView->PreviewModal() ;
        delete pForm;
}
//---------------------------------------------------------------------------








void __fastcall TDoForm::cbbOperunitChange(TObject *Sender)
{
       AnsiString val = cbbOperunit->Text;
        if (cbbOperunit->Text.IsEmpty()) {
                return;
        }
        cbbOperunit->SelStart = AnsiString(cbbOperunit->Text).Length();

        CString szSQL;
	szSQL.Format("select name from DicOperunit where name like '%%%s%%'", cbbOperunit->Text.c_str());
	RunSQL(dm1->Query1,szSQL,true);

        //不管如何，先清理缓存。
        cbbOperunit->Items->Clear();
        cbbOperunit->SelLength = 255;
        cbbOperunit->SelStart = 255;

	while(!dm1->Query1->Eof)
	{
                cbbOperunit->Items->Add(dm1->Query1->FieldByName("name")->AsString);
		dm1->Query1->Next();
        }
}
//---------------------------------------------------------------------------

void __fastcall TDoForm::cbbOperunitSelect(TObject *Sender)
{
        int nSel = cbbOperunit->ItemIndex;
        if (nSel == -1)
                return;
}
//---------------------------------------------------------------------------





void __fastcall TDoForm::cbbSHSelect(TObject *Sender)
{
        int nSel = cbbSH->ItemIndex;
        if (nSel == -1)
                return;
}
//---------------------------------------------------------------------------


void __fastcall TDoForm::cbbSHChange(TObject *Sender)
{
       AnsiString val = cbbSH->Text;
        if (cbbSH->Text.IsEmpty()) {
                return;
        }
        cbbSH->SelStart = AnsiString(cbbSH->Text).Length();

        CString szSQL;
	szSQL.Format("select name from dicsh where name like '%%%s%%'", cbbSH->Text.c_str());
	RunSQL(dm1->Query1,szSQL,true);

        //不管如何，先清理缓存。
        cbbSH->Items->Clear();
        cbbSH->SelLength = 255;
        cbbSH->SelStart = 255;

	while(!dm1->Query1->Eof)
	{
                cbbSH->Items->Add(dm1->Query1->FieldByName("name")->AsString);
		dm1->Query1->Next();
         }       
}
//---------------------------------------------------------------------------

void __fastcall TDoForm::edtNoChange(TObject *Sender)
{
        AnsiString val = edtNo->Text;
        if (edtNo->Text.IsEmpty()) {
                return;
        }
        edtNo->SelStart = AnsiString(edtNo->Text).Length();

        CString szSQL;
	szSQL.Format("select * from merchandise where no = '%s'", edtNo->Text.c_str());
	RunSQL(dm1->Query1,szSQL,true);

//        edtNo->SelLength = 255;
//        edtNo->SelStart = 255;

	if(!dm1->Query1->Eof)
	{
                cbbMname->Text = dm1->Query1->FieldByName("mname")->AsString;
//		dm1->Query1->Next();
                cbbMnameChange(Sender);
                cbbMname->ItemIndex=cbbMname->Items->IndexOf(cbbMname->Text);
                cbbMnameSelect(Sender);
        }else{
                cbbMname->Text = "";
                cbbMname->Clear();
        }
}
//---------------------------------------------------------------------------


void __fastcall TDoForm::edtUnitpriceChange(TObject *Sender)
{
        if (nWhoChanging==2){
                return;
        }
        nWhoChanging = 1;
        if (edtUnitprice->Text == ""){
                edtTotalPrice->Text = "";    
                nWhoChanging = 0;
                return;
        }
        if (edtCount1->Text !="" && edtUnitprice->Text != ""){
                double totalPrice = StrToFloat(edtUnitprice->Text)*StrToFloat(edtCount1->Text);
                totalPrice = (floor(totalPrice*100+0.5))/100.0;
                edtTotalPrice->Text = FloatToStr(totalPrice);
        }
        nWhoChanging = 0;
}
//---------------------------------------------------------------------------

void __fastcall TDoForm::edtTotalPriceChange(TObject *Sender)
{
        if (nWhoChanging==1){
                return;
        }
        nWhoChanging = 2;
        if (edtTotalPrice->Text == ""){
                edtUnitprice->Text = "";                
                nWhoChanging = 0;
                return;
        }

        if (edtCount1->Text !="" && edtTotalPrice->Text != ""){
                double unitPrice = StrToFloat(edtTotalPrice->Text)/StrToFloat(edtCount1->Text);
                unitPrice = (floor(unitPrice*10000+0.5))/10000.0;
                edtUnitprice->Text = FloatToStr(unitPrice);
        }
        nWhoChanging = 0;
}
//---------------------------------------------------------------------------











