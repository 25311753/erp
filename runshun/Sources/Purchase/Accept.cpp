//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Accept.h"
#include "DataModule.h"
#include "BaseCode.h"
#include "LdyInterface.h"
#include <assert.h>
#include "common.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "trayicon"
#pragma resource "*.dfm"
#include <cctype>

TAcceptForm *AcceptForm;
//---------------------------------------------------------------------------
void Accept(int nAuth)
{
        CALL_FORM(TAcceptForm);
}

__fastcall TAcceptForm::TAcceptForm(TComponent* Owner)
        : TForm(Owner)
{
        m_enWorkState=EN_IDLE;
}
//---------------------------------------------------------------------------

void __fastcall TAcceptForm::FormShow(TObject *Sender)
{
//        edtShipAgent->Text = "";
        lb_sum_cnt_con->Caption = "";
        edtContainerNo->Text = "";
        edtQryLicenseNo->Text = "";
        edtCid->Text = "";
        cbbGoodsPerf->Text = "";
        cbbGoodsPerfQry->Text = "";

        edtLading->Text = "";
        edtContainerInfo->Text = "";
        edtSealId->Text = "";

        edtCustfree->Text = "";
        edtCliWorkid->Text = "";
        edtBeiZhu->Text = "";
              edtQryCid->Text = "";
        edtQryLading->Text = "";
        edtQryJZS->Text = "";
         CString szSQL;

        edtBoatNo->Text = "";
/*
        cbbBoatno->ItemIndex = -1;
        cbbBoatno->Text = "";
        szSQL.Format("select * from dicboatno");
        RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
                cbbBoatno->Items->Add(dm1->Query1->FieldByName("bname")->AsString);
                m_lstBoatno.Add(dm1->Query1->FieldByName("bname")->AsString.c_str());
                dm1->Query1->Next();
        }
*/
        edtBoatOrder->Text = "";
/*
        cbbBoatorder->ItemIndex = -1;
        cbbBoatorder->Text = "";
	szSQL.Format("select * from dicboatorder");
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{

                cbbBoatorder->Items->Add(dm1->Query1->FieldByName("boname")->AsString);
                m_lstBoatorder.Add(dm1->Query1->FieldByName("boname")->AsString.c_str());
		dm1->Query1->Next();
        }
*/
        cbbQryStatus->ItemIndex = 0;
        cbbQryStatus->Text = "";
	szSQL.Format("select * from dicstatus");
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{

                cbbQryStatus->Items->Add(dm1->Query1->FieldByName("sname")->AsString);
                m_lstQryStatus.Add(dm1->Query1->FieldByName("sname")->AsString.c_str());
		dm1->Query1->Next();
        }

        cbbStatus->ItemIndex = -1;
        cbbStatus->Text = "";
	szSQL.Format("select * from dicstatus");
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{

                cbbStatus->Items->Add(dm1->Query1->FieldByName("sname")->AsString);
                m_lstStatus.Add(dm1->Query1->FieldByName("sname")->AsString.c_str());
		dm1->Query1->Next();
        }
	szSQL.Format("select * from dicshipagent");
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{

                cbbShipAgent->Items->Add(dm1->Query1->FieldByName("saname")->AsString);
		dm1->Query1->Next();
        }

        m_lstGoodsperf.Add("包柜");
        m_lstGoodsperf.Add("买单");
        m_lstGoodsperf.Add("正常单");
//        TDateTime tDate=GetSysTime(false);

//        dtpEndDateYYYYMMDD->DateTime=tDate;
//        TDateTime tDate_default;
//         tDate_default=StrToDateTime("2012-01-01 17:00:00");
//        dtpEndDateHHMM->Time=tDate_default;
        TDateTime tNow=TDateTime::CurrentDateTime();
        dtpEndDateYYYYMMDD->DateTime=tNow;
        dtpEndDateHHMM->Time = EncodeTime(17,00,00,0);
        dtpQryAcceptDate->DateTime=tNow;
        dtpQryAcceptDateEnd->DateTime=tNow;

        m_enWorkState=EN_IDLE;
        ResetCtrl();
}
//---------------------------------------------------------------------------
#include "ContainerInfo.h"
void __fastcall TAcceptForm::btnInputContanerinfoClick(TObject *Sender)
{
	TContainerInfoForm *pCI;
	pCI=new TContainerInfoForm(this);
	assert(pCI!=NULL);
	pCI->ShowModal();
        //if(pMT->ShowModal()==mrOk)
	{
		edtContainerInfo->Text = pCI->m_szContainerInfo;
	}
	delete pCI;
        
}
//---------------------------------------------------------------------------
//组装集装箱信息:“柜数|箱号 柜型 封条号#箱号 柜型 封条号#@”
CString TAcceptForm::GetContainerInfo(){
        CString szContInfo;
        szContInfo += (IntToStr(lstViewContainer->Items->Count)).c_str();
        szContInfo += '|';
        for (int i=0; i<lstViewContainer->Items->Count; ++i) {
                szContInfo += lstViewContainer->Items->Item[i]->Caption.c_str();
                szContInfo += ' ';
                szContInfo += lstViewContainer->Items->Item[i]->SubItems->Strings[0].c_str();
                szContInfo += ' ';
                szContInfo += lstViewContainer->Items->Item[i]->SubItems->Strings[1].c_str();
                szContInfo += '#';
        }
        szContInfo += '@';
        return szContInfo;
}
void __fastcall TAcceptForm::btnAddClick(TObject *Sender)
{
	ResetCtrl();
        lstViewContainer->Clear();
//        edtShipAgent->Text = "";
        edtContainerNo->Text = "";
        edtCid->Text = "";
        cbbGoodsPerf->Text = "";
        cbbGoodsPerfQry->Text = "";

        edtLading->Text = "";
        edtContainerInfo->Text = "";
        edtSealId->Text = "";
        edtCustfree->Text = "";
//        edtShipAgent->Text = "";
        edtCliWorkid->Text = "";
        edtBeiZhu->Text = "";
        edtQryCid->Text = "";
        edtQryLading->Text = "";
        edtQryJZS->Text = "";
        cbbClient->Text = "";
        cbbCustomsCharge->Text = "";

        cbbQryClient->Text = "";
//        cbbBoatno->ItemIndex = -1;
        edtBoatNo->Text = "";
//        cbbBoatorder->ItemIndex = -1;
        edtBoatOrder->Text = "";
        cbbQryStatus->ItemIndex = 0;
        cbbStatus->ItemIndex = -1;
        cbbShipAgent->ItemIndex = 0;
        if(edtCid->CanFocus())	edtCid->SetFocus();
        
        m_enWorkState=EN_ADDNEW;
        ResetCtrl();
        edtCid->SetFocus();

}
//---------------------------------------------------------------------------

int TAcceptForm::add(TObject *Sender)
{
        int rt = -1;

        if(edtCid->Text.IsEmpty() || cbbClient->Text.IsEmpty() || edtLading->Text.IsEmpty() || edtBoatNo->Text.IsEmpty() || \
              edtBoatOrder->Text.IsEmpty() || /*edtCustfree->Text.IsEmpty() ||*/ cbbGoodsPerf->Text.IsEmpty() ||\
              lstViewContainer->Items->Count == 0)
        {
                ShowMessage("请检查你的输入信息");
                return rt;
        }
        if(!isNum(edtCid->Text)){
                ShowMessage("单号输入有误！");
                return rt;
        }

        char strAddSQL[256];
        sprintf(strAddSQL,"select cid as cnt from customs where cid='%s'",edtCid->Text.c_str());
//        RunSQL(strAddSQL,true);
       	RunSQL(dm1->Query1,strAddSQL,true);
	if(!dm1->Query1->Eof)
	{
                ShowMessage("数据库中已有该编号的记录!");
                return rt;
        }

        //gen date
        unsigned short year0,month0,day0,hour0,minute0,sec0,msec0;
	dtpEndDateYYYYMMDD->DateTime.DecodeDate(&year0,&month0,&day0);
     	dtpEndDateHHMM->DateTime.DecodeTime(&hour0,&minute0,&sec0,&msec0);
        char strDate0[80];
   	sprintf(strDate0,"%04d-%02d-%02d %02d:%02d",year0,month0,day0,hour0,minute0,sec0,msec0);

        CString szSQL;
        szSQL="insert into customs(cid,client,ladingid,containerinfo,sealid,bnname,boname,endcustdate,\
                        custfree,cliworkid,beizhu,goodsperf,status,acceptdate,boatno,boatorder,acceptor,shipagent)\
                        values(";
        szSQL += Str2DBString(edtCid->Text.c_str());
        szSQL +=","; szSQL += Str2DBString(cbbClient->Text.c_str());
        szSQL +=","; szSQL += Str2DBString(edtLading->Text.c_str());
        szSQL +=","; szSQL += Str2DBString(GetContainerInfo());//edtContainerInfo->Text.c_str());
//        szSQL +=","; szSQL += Str2DBString(edtSealId->Text.c_str());
        szSQL +=","; szSQL += Str2DBString(lstViewContainer->Items->Item[0]->SubItems->Strings[1].c_str());
        szSQL +=","; szSQL += Str2DBString(edtBoatNo->Text.c_str());
        szSQL +=","; szSQL += Str2DBString(edtBoatOrder->Text.c_str());
        //szSQL +=","; szSQL += Str2DBString(edtEndDate->Text.c_str());
        szSQL +=","; szSQL += Str2DBString(strDate0);
        szSQL +=","; szSQL += Text2DBFloat(edtCustfree->Text.IsEmpty()?AnsiString("0"):edtCustfree->Text,4).c_str();//Str2DBString(edtCustfree->Text.c_str());
        edtCustfree->Text = Text2DBFloat(edtCustfree->Text.IsEmpty()?AnsiString("0"):edtCustfree->Text,4).c_str();
        szSQL +=","; szSQL += Str2DBString(edtCliWorkid->Text.c_str());
        szSQL +=","; szSQL += Str2DBString(edtBeiZhu->Text.c_str());
        szSQL +=","; szSQL += Str2DBString(cbbGoodsPerf->Text.c_str());
        szSQL +=","; szSQL += Str2DBString("已接单");
//        szSQL +=","; szSQL += Str2DBString(GetSysDate());
        szSQL +=",getdate()";
        szSQL +=","; szSQL += Str2DBString(edtBoatNo->Text.c_str());
        szSQL +=","; szSQL += Str2DBString(edtBoatOrder->Text.c_str());
        szSQL +=","; szSQL += Str2DBString(g_theOperator.op_name);
        szSQL +=","; szSQL += Str2DBString(cbbShipAgent->Text.c_str());
        szSQL +=")";

//        lbdebug->Caption = AnsiString(szSQL);
        if(!RunSQL(dm1->Query1,szSQL))
        {
                ShowMessage("insert fail!") ;

                return rt;
        }

        int column_no = lstViewDown->Items->Count;
        int cnt_con = lstViewContainer->Items->Count;
        TListItem *pItem =lstViewDown->Items->Add();
        assert(pItem!=NULL);
        pItem->Caption=(column_no+1);
        pItem->SubItems->Add(edtCid->Text);
        pItem->SubItems->Add(cbbGoodsPerf->Text);
        pItem->SubItems->Add(AnsiString(GetSysDate()));
        pItem->SubItems->Add(cbbClient->Text);
        pItem->SubItems->Add(edtLading->Text);
        //pItem->SubItems->Add(AnsiString(GetContainerInfo()));
        pItem->SubItems->Add(lstViewContainer->Items->Item[0]->Caption);
        pItem->SubItems->Add(IntToStr(cnt_con));
        pItem->SubItems->Add("");
        pItem->SubItems->Add(edtBoatNo->Text);
        pItem->SubItems->Add(edtBoatOrder->Text);
        pItem->SubItems->Add(strDate0);
        pItem->SubItems->Add("已接单");
        pItem->SubItems->Add(edtCliWorkid->Text);
        pItem->SubItems->Add(edtCustfree->Text);
        pItem->SubItems->Add("");
        pItem->SubItems->Add(g_theOperator.op_name);
        pItem->SubItems->Add("");       //doer 
        pItem->SubItems->Add(edtBeiZhu->Text);
        pItem->SubItems->Add(cbbShipAgent->Text.c_str());
        pItem->SubItems->Add(AnsiString(GetContainerInfo()));
        flushSum();
        rt = 0;
        return rt;
}
void TAcceptForm::refreshAdd()
{
}
void TAcceptForm::refreshMod()
{
        unsigned short year0,month0,day0;
	dtpQryAcceptDate->DateTime.DecodeDate(&year0,&month0,&day0);
        char strDate0[80];

   	sprintf(strDate0,"%04d%02d%02d",year0,month0,day0);

        unsigned short year1,month1,day1;
	dtpQryAcceptDateEnd->DateTime.DecodeDate(&year1,&month1,&day1);
        char strDate1[80];

   	sprintf(strDate1,"%04d%02d%02d",year1,month1,day1);

        CString szSQL;
        szSQL="select *,CONVERT(varchar(10), acceptdate, 23) as ad, substring(containerinfo,0,charindex('|',containerinfo)) as cnt_con \
                from customs where 1=1 ";
        if (!edtQryCid->Text.IsEmpty()){
                szSQL +=" and cid="; szSQL += Str2DBString(edtQryCid->Text.c_str());
        }
        TListItem *pItem  = lstViewDown->Selected;
	RunSQL(dm1->Query1,szSQL,true);
//return;
	while(!dm1->Query1->Eof)
	{
//                pItem->Caption=dm1->Query1->FieldByName("cid")->AsString;
                pItem->SubItems->Strings[0] = dm1->Query1->FieldByName("cid")->AsString;
	        pItem->SubItems->Strings[1] = dm1->Query1->FieldByName("goodsperf")->AsString;
		pItem->SubItems->Strings[2] = dm1->Query1->FieldByName("ad")->AsString;
		pItem->SubItems->Strings[3] = dm1->Query1->FieldByName("client")->AsString;
		pItem->SubItems->Strings[4] = dm1->Query1->FieldByName("ladingid")->AsString;
		pItem->SubItems->Strings[5] = AnsiString(getFirstContainerNo(dm1->Query1->FieldByName("containerinfo")->AsString));
		pItem->SubItems->Strings[6] = dm1->Query1->FieldByName("cnt_con")->AsString;
		pItem->SubItems->Strings[7] = dm1->Query1->FieldByName("licenseno")->AsString;
		pItem->SubItems->Strings[8] = dm1->Query1->FieldByName("boatno")->AsString;
		pItem->SubItems->Strings[9] = dm1->Query1->FieldByName("boatorder")->AsString;
		pItem->SubItems->Strings[10] = dm1->Query1->FieldByName("endcustdate")->AsString;
		pItem->SubItems->Strings[11] = dm1->Query1->FieldByName("status")->AsString;
		pItem->SubItems->Strings[12] = dm1->Query1->FieldByName("cliworkid")->AsString;
		pItem->SubItems->Strings[13] = dm1->Query1->FieldByName("custfree")->AsString;
		pItem->SubItems->Strings[14] = dm1->Query1->FieldByName("sealid")->AsString;
		pItem->SubItems->Strings[15] = dm1->Query1->FieldByName("acceptor")->AsString;
		pItem->SubItems->Strings[16] = dm1->Query1->FieldByName("doer")->AsString;
		pItem->SubItems->Strings[17] = dm1->Query1->FieldByName("beizhu")->AsString;
                pItem->SubItems->Strings[18] = dm1->Query1->FieldByName("shipagent")->AsString;
                pItem->SubItems->Strings[19] = dm1->Query1->FieldByName("containerinfo")->AsString;
                lstViewContainer->Items->Clear();
                flushContainer(AnsiString(pItem->SubItems->Strings[19].c_str()));
		dm1->Query1->Next();
	}
        flushSum();

}
void __fastcall TAcceptForm::btnQueryClick(TObject *Sender)
{

        unsigned short year0,month0,day0;
	dtpQryAcceptDate->DateTime.DecodeDate(&year0,&month0,&day0);
        char strDate0[80];

   	sprintf(strDate0,"%04d%02d%02d",year0,month0,day0);

        unsigned short year1,month1,day1;
	dtpQryAcceptDateEnd->DateTime.DecodeDate(&year1,&month1,&day1);
        char strDate1[80];

   	sprintf(strDate1,"%04d-%02d-%02d 23:59:59",year1,month1,day1);

        CString szSQL;
        szSQL="select *,CONVERT(varchar(10), acceptdate, 23) as ad, substring(containerinfo,0,charindex('|',containerinfo)) as cnt_con \
                from customs where 1=1 ";
        if (!edtQryCid->Text.IsEmpty()){
                szSQL +=" and cid="; szSQL += Str2DBString(edtQryCid->Text.c_str());
        }
        if (!cbbQryClient->Text.IsEmpty()) {
                szSQL += " and client="; szSQL += Str2DBString(cbbQryClient->Text.c_str());
        }
        if (!edtQryLading->Text.IsEmpty())   {
                szSQL += " and ladingid="; szSQL += Str2DBString(edtQryLading->Text.c_str());
        }
        if (!cbbQryStatus->Text.IsEmpty()){
                szSQL += " and status="; szSQL += Str2DBString(cbbQryStatus->Text.c_str());
        }
        if (!edtQryJZS->Text.IsEmpty()){
                szSQL += " and containerinfo like'%"; szSQL += edtQryJZS->Text.c_str(); szSQL+="%'";
        }
        if (!edtQryLicenseNo->Text.IsEmpty()){
                szSQL += " and licenseno="; szSQL += Str2DBString(edtQryLicenseNo->Text.c_str());
        }
        if (!cbbGoodsPerfQry->Text.IsEmpty()){
                szSQL += " and goodsperf="; szSQL += Str2DBString(cbbGoodsPerfQry->Text.c_str());
        }

        if (cbIsQryByDate->Checked) {
                szSQL += " and acceptdate between "; szSQL += Str2DBString(strDate0);
                szSQL += " and ";
                szSQL += Str2DBString(strDate1);
        }
        szSQL += " order by acceptdate";

        TListItem *pItem;
        lstViewDown->Items->Clear();
	RunSQL(dm1->Query1,szSQL,true);

        if (dm1->Query1->Eof){
                ShowMessage("记录不存在");
                return;
        }

        int column_no = 0;
	while(!dm1->Query1->Eof)
	{
                column_no++;
                pItem=lstViewDown->Items->Add();
                pItem->Caption= column_no;
                pItem->SubItems->Add(dm1->Query1->FieldByName("cid")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("goodsperf")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("ad")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("client")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("ladingid")->AsString);
		//pItem->SubItems->Add(dm1->Query1->FieldByName("containerinfo")->AsString);
                pItem->SubItems->Add(AnsiString(getFirstContainerNo(dm1->Query1->FieldByName("containerinfo")->AsString)));
                pItem->SubItems->Add(dm1->Query1->FieldByName("cnt_con")->AsString);
                pItem->SubItems->Add(dm1->Query1->FieldByName("licenseno")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("boatno")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("boatorder")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("endcustdate")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("status")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("cliworkid")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("custfree")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("sealid")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("acceptor")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("doer")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("beizhu")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("shipagent")->AsString);

                pItem->SubItems->Add(dm1->Query1->FieldByName("containerinfo")->AsString);
                lstViewContainer->Items->Clear();

		dm1->Query1->Next();
	}

       	ResetCtrl();
        //clear up area
        edtQryCid->Text 				= "";
        edtCid->Text 						= "";
        cbbGoodsPerf->ItemIndex	= -1;
        cbbClient->Text					= "";
        cbbCustomsCharge->Text					= "";

//        cbbBoatno->ItemIndex		= -1;
        edtBoatNo->Text = "";
//        cbbBoatorder->ItemIndex	= -1;
        edtBoatOrder->Text = "";
        cbbStatus->ItemIndex		= -1;
        edtLading->Text 				= "";
        edtContainerInfo->Text 	= "";
        edtCliWorkid->Text 			= "";
        edtCustfree->Text 			= "";
        edtSealId->Text 				= "";
        edtBeiZhu->Text					= "";
        cbbShipAgent->ItemIndex	= -1;
        edtContainerNo->Text		= "";
        edtSealId->Text					= "";
        lstViewContainer->Clear();
        flushSum();
        //~
}
//---------------------------------------------------------------------------
void TAcceptForm::flushContainer(AnsiString c){
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


        if (lstViewContainer->Items->Count>0){
                edtContainerNo->Text = lstViewContainer->Items->Item[0]->Caption;
                cbbContainerType->ItemIndex=cbbContainerType->Items->IndexOf(lstViewContainer->Items->Item[0]->SubItems->Strings[0]);
                edtSealId->Text = lstViewContainer->Items->Item[0]->SubItems->Strings[1];
        }

}
//should be common
CString TAcceptForm::getFirstContainerNo(AnsiString c)
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
void __fastcall TAcceptForm::lstViewDownSelectItem(TObject *Sender,
      TListItem *Item, bool Selected)
{
  if(Selected!=NULL){
//        ShowMessage("lstViewDownSelectItem");
        edtQryCid->Text = Item->SubItems->Strings[0];//Item->Caption;
        edtCid->Text = Item->SubItems->Strings[0];//Item->Caption;

        cbbGoodsPerf->ItemIndex=cbbGoodsPerf->Items->IndexOf(Item->SubItems->Strings[1]);
        cbbGoodsPerfQry->ItemIndex=cbbGoodsPerf->Items->IndexOf(Item->SubItems->Strings[1]) +1;
//                ShowMessage(cbbGoodsPerfQry->ItemIndex);
        cbbClient->Text=Item->SubItems->Strings[3];
        cbbCustomsCharge->Text = AnsiString(getCustomsCharge(cbbClient->Text.c_str()));
//        cbbBoatno->ItemIndex=cbbBoatno->Items->IndexOf(Item->SubItems->Strings[6]);
        edtBoatNo->Text = Item->SubItems->Strings[8];
//        cbbBoatorder->ItemIndex=cbbBoatorder->Items->IndexOf(Item->SubItems->Strings[7]);

        edtBoatOrder->Text = Item->SubItems->Strings[9];
        cbbStatus->ItemIndex=cbbStatus->Items->IndexOf(Item->SubItems->Strings[11]);
        edtLading->Text =  Item->SubItems->Strings[4].c_str();
        edtContainerInfo->Text = Item->SubItems->Strings[17].c_str();
        edtCliWorkid->Text =   Item->SubItems->Strings[12].c_str();
        edtCustfree->Text = Item->SubItems->Strings[13].c_str();
        edtSealId->Text = Item->SubItems->Strings[14].c_str();
        edtBeiZhu->Text=Item->SubItems->Strings[17].c_str();
        cbbShipAgent->ItemIndex=cbbShipAgent->Items->IndexOf(Item->SubItems->Strings[18]);
        flushContainer(AnsiString(Item->SubItems->Strings[19].c_str()));
        TDateTime tDate;
        tDate=StrToDateTime(Item->SubItems->Strings[10].c_str());
        dtpEndDateYYYYMMDD->DateTime=tDate;
        dtpEndDateHHMM->Time=tDate;
  }
        ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TAcceptForm::btnDelClick(TObject *Sender)
{
        char strMsg[256],strSQL[512];
        sprintf(strMsg,"\n  真要删除编号为“%s”的记录吗？  \n",edtCid->Text.c_str());
        if(Application->MessageBox(strMsg,"警告",MB_YESNOCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2)!=IDYES)
                return;

        CString szSQL;
        szSQL.Format("delete customs where cid=%s", edtCid->Text);
        if(!RunSQL(dm1->Query1,szSQL))
                ShowMessage("delete fail!");
        //btnQueryClick(Sender);
        TListItem *pItem;
        pItem=lstViewDown->Selected;
        if(pItem!=NULL)
        {
                int nSel=lstViewDown->Items->IndexOf(pItem);
                lstViewDown->Items->Delete(nSel);
                lstViewDown->Selected=NULL;
                flushSum();
        }
        ShowMessage("删除成功");
}
//---------------------------------------------------------------------------

void __fastcall TAcceptForm::btnModClick(TObject *Sender)
{
  m_enWorkState=EN_EDIT;
  ResetCtrl();
//  edtCid->SetFocus();
}
//---------------------------------------------------------------------------

void TAcceptForm::mod(TObject *Sender)
{
        if (lstViewContainer->Items->Count == 0){
                ShowMessage("柜号信息不全");
                return;
        }
 char strMsg[256],strSQL[512];
  sprintf(strMsg,"\n  真要修改编号为“%s”的记录吗？  \n",edtCid->Text.c_str());
  if(Application->MessageBox(strMsg,"警告",MB_YESNOCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2)!=IDYES)
   return;

unsigned short year0,month0,day0,hour0,minute0,sec0,msec0;
	dtpEndDateYYYYMMDD->DateTime.DecodeDate(&year0,&month0,&day0);
     	dtpEndDateHHMM->DateTime.DecodeTime(&hour0,&minute0,&sec0,&msec0);
   char strDate0[80];
   	//sprintf(strDate0,"%04d%02d%02d",year0,month0,day0);
        sprintf(strDate0,"%04d-%02d-%02d %02d:%02d",year0,month0,day0,hour0,minute0,sec0,msec0);
        CString szSQL;
        szSQL="update customs set ";

szSQL +="client="; szSQL += Str2DBString(cbbClient->Text.c_str());
szSQL +=",ladingid="; szSQL += Str2DBString(edtLading->Text.c_str());
szSQL +=",containerinfo="; szSQL += Str2DBString(GetContainerInfo());
szSQL +=",sealid="; szSQL += Str2DBString(lstViewContainer->Items->Item[0]->SubItems->Strings[1].c_str());
szSQL +=" , boatno="; szSQL += Str2DBString(edtBoatNo->Text.c_str());
szSQL +=" , boatorder="; szSQL += Str2DBString(edtBoatOrder->Text.c_str());
//szSQL +=","; szSQL += Str2DBString(edtEndDate->Text.c_str());
szSQL +=", endcustdate="; szSQL += Str2DBString(strDate0);

szSQL +=" , custfree="; szSQL += Text2DBFloat(edtCustfree->Text.IsEmpty()?AnsiString("0"):edtCustfree->Text,4).c_str();
edtCustfree->Text = Text2DBFloat(edtCustfree->Text.IsEmpty()?AnsiString("0"):edtCustfree->Text,4).c_str();
szSQL +=" , cliworkid="; szSQL += Str2DBString(edtCliWorkid->Text.c_str());
szSQL +=" , beizhu="; szSQL += Str2DBString(edtBeiZhu->Text.c_str());
szSQL +=",goodsperf="; szSQL += Str2DBString(cbbGoodsPerf->Text.c_str());
szSQL +=",status="; szSQL += Str2DBString(cbbStatus->Text.c_str());
//szSQL +=",acceptdate="; szSQL += Str2DBString(GetSysDate());
//szSQL +=",acceptor="; szSQL += Str2DBString(g_theOperator.op_name);           //del 0511 取消每次修改更新接单人
szSQL +=",shipagent="; szSQL += Str2DBString(cbbShipAgent->Text.c_str());

szSQL += " where cid="; szSQL+=Str2DBString(edtCid->Text.c_str());


//        Edit1->Text = AnsiString(szSQL);
        if(!RunSQL(dm1->Query1,szSQL))
        {
                ShowMessage("update fail!") ;

                return;
        }

//        lstViewDown->Items->Clear();
//        btnQueryClick(Sender);

        ShowMessage("修改成功");
}
bool TAcceptForm::isDupContainer(AnsiString c, AnsiString &dupCid){
        CString szSQL;
        szSQL.Format("select cid from customs where containerinfo like '%%%s %%'", c);
//        ShowMessage(AnsiString(szSQL));
        RunSQL(dm1->Query1,szSQL,true);
        if (!dm1->Query1->Eof) {
                dupCid = AnsiString(dm1->Query1->FieldByName("cid")->AsString);
                return true;
        }
        return false;
}

void __fastcall TAcceptForm::btnAddContainerClick(TObject *Sender)
{
  edtContainerNo->Text = Trim(edtContainerNo->Text);
  if(edtContainerNo->Text.IsEmpty() || edtSealId->Text.IsEmpty())
  {
    ShowMessage("请输入箱号和封条号");
    if(edtContainerNo->CanFocus())	edtContainerNo->SetFocus();
    return;
  }
       //跨单重复柜号检查
       AnsiString dupCid="";
      if (isDupContainer(AnsiString(edtContainerNo->Text.c_str()), dupCid)) {
                char strMsg[256],strSQL[512];
                sprintf(strMsg,"\n  [ %s ]存在相同柜号“%s”, 确定继续添加?\n", dupCid, edtContainerNo->Text.c_str());
                if(Application->MessageBox(strMsg,"警告",MB_YESNOCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2)!=IDYES)
                return;
      }
  //本单重复柜号检查
  for(int i=0;i<lstViewContainer->Items->Count;i++) {
      TListItem *pItem;
      pItem = lstViewContainer->Items->Item[i];
      if (pItem->Caption == edtContainerNo->Text) {
                char strMsg[256],strSQL[512];
                sprintf(strMsg,"\n  真要添加重复柜号“%s”吗？  \n",edtContainerNo->Text.c_str());
                if(Application->MessageBox(strMsg,"警告",MB_YESNOCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2)!=IDYES)
                return;
      }
  }

	TListItem *pItem =lstViewContainer->Items->Add();
        assert(pItem!=NULL);
        pItem->Caption=edtContainerNo->Text;
        pItem->SubItems->Add(cbbContainerType->Text);
        pItem->SubItems->Add(edtSealId->Text);

  edtContainerNo->Text = "";
  edtSealId->Text = "";

}
//---------------------------------------------------------------------------

void __fastcall TAcceptForm::lstViewContainerSelectItem(TObject *Sender,
      TListItem *Item, bool Selected)
{
        edtContainerNo->Text = Item->Caption;
        cbbContainerType->ItemIndex=cbbContainerType->Items->IndexOf(Item->SubItems->Strings[0]);
        edtSealId->Text = Item->SubItems->Strings[1];
}
//---------------------------------------------------------------------------



void __fastcall TAcceptForm::btnModContainerClick(TObject *Sender)
{

  if(lstViewContainer->Selected == NULL)
  {
    ShowMessage("请选择记录");
    if(edtContainerNo->CanFocus())	edtContainerNo->SetFocus();
    return;
  }
  for(int i=0;i<lstViewContainer->Items->Count;i++) {
      TListItem *pItem;
      pItem = lstViewContainer->Items->Item[i];
      if (pItem!=lstViewContainer->Selected && pItem->Caption == edtContainerNo->Text) {
                char strMsg[256],strSQL[512];
                sprintf(strMsg,"\n 柜号“%s”有重复,继续修改吗？  \n",edtContainerNo->Text.c_str());
                if(Application->MessageBox(strMsg,"警告",MB_YESNOCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2)!=IDYES)
                return;
      }
  }

        TListItem *pItem;
        pItem = lstViewContainer->Selected;
        if (pItem!=NULL){
                pItem->Caption = edtContainerNo->Text;
                pItem->SubItems->Strings[0] = cbbContainerType->Text;
                pItem->SubItems->Strings[1] = edtSealId->Text;

        }
        
}
//---------------------------------------------------------------------------

void __fastcall TAcceptForm::btnDelContainerClick(TObject *Sender)
{
  if(lstViewContainer->Selected == NULL)
  {
    ShowMessage("请选择记录");
    if(edtContainerNo->CanFocus())	edtContainerNo->SetFocus();
    return;
  }
          lstViewContainer->Selected->Delete();        
}
//---------------------------------------------------------------------------



void __fastcall TAcceptForm::edtQryCidKeyPress(TObject *Sender, char &Key)
{
    if (Key==13) //enter key been pressed
    {
        Key=0;
        btnQueryClick(Sender);
    }        
}
//---------------------------------------------------------------------------




void __fastcall TAcceptForm::btnCancelClick(TObject *Sender)
{
  int nState;

  nState=m_enWorkState;
  m_enWorkState=EN_IDLE;
  ResetCtrl();
 lstViewDown->Selected=NULL;
//  Row2Editor();

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

void __fastcall TAcceptForm::btnOKClick(TObject *Sender)
{
  char strName[80],*ptr,strTemp[80];
  int nState;
  int oldState=m_enWorkState;
  switch(m_enWorkState)
  {
    case EN_ADDNEW:
      if (-1 == add(Sender))
        return;
      break;
    case EN_EDIT:
       mod(Sender);
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
        refreshMod();
  }
  m_enWorkState=EN_IDLE;
  ResetCtrl();
      btnMod->Enabled=false;
    btnDel->Enabled=false;
    if(oldState==EN_EDIT){
       lstViewDown->Selected=NULL;
    }

}
//---------------------------------------------------------------------------
void TAcceptForm::ResetCtrl(){

  //bool bAuth = m_nAuthor>=AUTH_FULL;
  bool bAuth = true;
  if(m_enWorkState==EN_IDLE)
  {
    //lstview
//    lstViewDown->Enabled=true;

    bool isSelected = (lstViewDown->Selected!=NULL);

            lstViewDown->Enabled = true;
//        lstViewDown->RowSelect=true;
//                    lstViewDown->Selected=NULL;

    //btn
    btnAdd->Enabled=true;
    btnMod->Enabled=isSelected;
    btnDel->Enabled=isSelected;
    btnOK->Enabled =false;
    btnCancel->Enabled=false;
    //edt all disable
    EnableEdit(edtCid,false);
    EnableCombo(cbbClient,false);
    EnableEdit(edtLading,false);
//    EnableCombo(cbbBoatno,false);
    EnableEdit(edtBoatNo,false);
//    EnableCombo(cbbBoatorder,false);
    EnableEdit(edtBoatOrder,false);
    EnableEdit(edtCustfree,false);
    EnableCombo(cbbShipAgent,false);
    EnableEdit(edtCliWorkid,false);
    EnableCombo(cbbGoodsPerf,false);
    dtpEndDateYYYYMMDD->Enabled = false;
    dtpEndDateHHMM->Enabled = false;
    EnableEdit(edtBeiZhu,false);
    //container all disable
    EnableEdit(edtContainerNo,false);
    EnableCombo(cbbContainerType,false);
    EnableEdit(edtSealId,false);
    btnAddContainer->Enabled=false;
    btnModContainer->Enabled=false;
    btnDelContainer->Enabled=false;
    //qry area
    btnQuery->Enabled = true;
    EnableEdit(edtQryCid,true);
    EnableCombo(cbbQryClient,true);
    EnableEdit(edtQryLading,true);
    EnableCombo(cbbQryStatus,true);
    cbIsQryByDate->Enabled = true;
    dtpQryAcceptDate->Enabled = true;
    dtpQryAcceptDateEnd->Enabled = true;
    EnableCombo(cbbGoodsPerfQry,true);



  }
  else
  {
    //btn
    btnAdd->Enabled=false;
    btnMod->Enabled=false;
    btnDel->Enabled=false;
    btnOK->Enabled =true;
    btnCancel->Enabled=true;
    //lstview
//    lstViewDown->Enabled=false;
//        lstViewDown->Selected=NULL;
        lstViewDown->Enabled=false;
//        lstViewDown->RowSelect=false;

    //edt all enable
    EnableEdit(edtCid,m_enWorkState==EN_ADDNEW);
    EnableCombo(cbbClient,true);
    EnableEdit(edtLading,true);
//    EnableCombo(cbbBoatno,true);
    EnableEdit(edtBoatNo,true);
//    EnableCombo(cbbBoatorder,true);
    EnableEdit(edtBoatOrder,true);
    EnableEdit(edtCustfree,true);
    EnableCombo(cbbShipAgent,true);
    EnableEdit(edtCliWorkid,true);
    EnableCombo(cbbGoodsPerf,true);
    dtpEndDateYYYYMMDD->Enabled = true;
    dtpEndDateHHMM->Enabled = true;
    EnableEdit(edtBeiZhu,true);
    //container all disable
    EnableEdit(edtContainerNo,true);
    EnableCombo(cbbContainerType,true);
    EnableEdit(edtSealId,true);
    btnAddContainer->Enabled=true;
    btnModContainer->Enabled=true;
    btnDelContainer->Enabled=true;
    //qry area
    btnQuery->Enabled = false;
    EnableEdit(edtQryCid,false);
    EnableCombo(cbbQryClient,false);
    EnableEdit(edtQryLading,false);
    EnableCombo(cbbQryStatus,false);
    cbIsQryByDate->Enabled = false;
    dtpQryAcceptDate->Enabled = false;
    dtpQryAcceptDateEnd->Enabled = false;
    EnableCombo(cbbGoodsPerfQry,false);
  }
}

void __fastcall TAcceptForm::cbbQryClientChange(TObject *Sender)
{
        cbbQryClient->Items->Clear();
        if (cbbQryClient->Text.IsEmpty()) {
                return;
        }
        cbbQryClient->Items->Clear();
        CString szSQL;
	szSQL.Format("select shortname from client where shortname like '%%%s%%'", cbbQryClient->Text.c_str());
//        edtDebug->Text = AnsiString(szSQL);
	RunSQL(dm1->Query1,szSQL,true);

	while(!dm1->Query1->Eof)
	{

                cbbQryClient->Items->Add(dm1->Query1->FieldByName("shortname")->AsString);
		dm1->Query1->Next();
        }
}
//---------------------------------------------------------------------------



void __fastcall TAcceptForm::cbbClientSelect(TObject *Sender)
{
        int nSel = cbbClient->ItemIndex;
        if (nSel == -1)
                return;
//        cbbCustomsCharge->ItemIndex = nSel; //move to onExit
}
//---------------------------------------------------------------------------

void __fastcall TAcceptForm::cbbQryClientSelect(TObject *Sender)
{
        int nSel = cbbQryClient->ItemIndex;
        if (nSel == -1)
                return;        
}
//---------------------------------------------------------------------------





void __fastcall TAcceptForm::cbbQryClient1Change(TObject *Sender)
{
        cbbQryClient->Items->Clear();
        if (cbbQryClient->Text.IsEmpty()) {
                return;
        }
//        cbbQryClient->Items->Clear();

        cbbQryClient->SelStart = AnsiString(cbbQryClient->Text).Length();
        CString szSQL;
	szSQL.Format("select shortname from client where shortname like '%%%s%%'", cbbQryClient->Text.c_str());
//        edtDebug->Text = AnsiString(szSQL);
	RunSQL(dm1->Query1,szSQL,true);

	while(!dm1->Query1->Eof)
	{

                cbbQryClient->Items->Add(dm1->Query1->FieldByName("shortname")->AsString);
		dm1->Query1->Next();
        }        
}
//---------------------------------------------------------------------------

void __fastcall TAcceptForm::cbbQryClient1Select(TObject *Sender)
{
        int nSel = cbbQryClient->ItemIndex;
        if (nSel == -1)
                return;
}
//---------------------------------------------------------------------------














void __fastcall TAcceptForm::Button1Click(TObject *Sender)
{
         this->TrayIcon1->Minimize();
        
}
//---------------------------------------------------------------------------

void __fastcall TAcceptForm::cbbClientChange(TObject *Sender)
{
        cbbClient->Items->Clear();
        cbbCustomsCharge->Items->Clear();

        AnsiString val = cbbClient->Text;
        if (cbbClient->Text.IsEmpty()) {
                return;
        }
        cbbClient->SelStart = AnsiString(cbbClient->Text).Length();
        CString szSQL;
	szSQL.Format("select shortname,customs_charge from client where shortname like '%%%s%%'", cbbClient->Text.c_str());
//        Edit1->Text = AnsiString(szSQL);
	RunSQL(dm1->Query1,szSQL,true);

	while(!dm1->Query1->Eof)
	{

//                cbbClient->Items->Add(dm1->Query1->FieldByName("fullname")->AsString);
                cbbClient->Items->Add(dm1->Query1->FieldByName("shortname")->AsString); //0107
                cbbCustomsCharge->Items->Add(dm1->Query1->FieldByName("customs_charge")->AsString); //0107

		dm1->Query1->Next();
        }
        
        cbbClient->Text = val;
//        cmbclass->ItemIndex=sclass->IndexOf(dm1->OperTab->FieldByName("op_class")->AsInteger);
//        cbbCustomsCharge->ItemIndex=cbbClient->Items->IndexOf(cbbClient->Text.c_str());
//        cbbCustomsCharge->ItemIndex = cbbClient->ItemIndex;
}

void  TAcceptForm::flushSum()
{
        TListItem *pItem;
        int sum_cnt_con=0;
        int i=0;
        for(i=0;i<lstViewDown->Items->Count;i++)
        {
                pItem=lstViewDown->Items->Item[i];
                sum_cnt_con += StrToInt(pItem->SubItems->Strings[6]);
        }
        lb_sum_cnt_con->Caption = IntToStr(sum_cnt_con);
}
//---------------------------------------------------------------------------






















void __fastcall TAcceptForm::cbbClientExit(TObject *Sender)
{
//cbbCustomsCharge->ItemIndex=cbbClient->Items->IndexOf(cbbClient->Text.c_str());
        cbbCustomsCharge->Text = AnsiString(getCustomsCharge(cbbClient->Text.c_str()));
}
//---------------------------------------------------------------------------
CString TAcceptForm::getCustomsCharge(CString client){
        CString rt="";
        CString szSQL;
	szSQL.Format("select customs_charge from client where shortname = '%s'", client);
	RunSQL(dm1->Query1,szSQL,true);

	if(!dm1->Query1->Eof)
	{
                rt = dm1->Query1->FieldByName("customs_charge")->AsString.c_str();
        }
        return rt;
}
