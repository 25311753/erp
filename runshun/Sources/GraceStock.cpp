//---------------------------------------------------------------------------

#include <vcl.h>

#include "MainFrame.h"
#include "UserLogin.h"
#include "DBSetup.h"
#include "ComVar.h"
#include "DataModule.h"
#include "BaseCode.h"
#include "GlobalConst.h"

#pragma hdrstop

USEFORM("DataModule.cpp", dm1); /* TDataModule: File Type */
USEFORM("System\UserLogin.cpp", UserLoginForm);
USEFORM("FromLCG\BaseFormUnit.cpp", BaseForm);
USEFORM("System\DBSetup.cpp", DBSetupForm);
USEFORM("FromLCG\operpwdunit.cpp", operpwdform);
USEFORM("FromLCG\operatorunit.cpp", operatorform);
USEFORM("BaseData\PrnBaseData.cpp", PrnBaseDataForm);
USEFORM("BaseData\DicDepart.cpp", DicDepartForm);
USEFORM("BaseData\DicStatus.cpp", DicStatusForm);
USEFORM("BaseData\PrnFactory.cpp", PrnFactoryForm);
USEFORM("BaseData\DepartCorp.cpp", DepartCorpForm);
USEFORM("FromLCG\calsssetunit.cpp", classsetform);
USEFORM("System\ClassRight.cpp", ClassRightForm);
USEFORM("BaseData\DicPayment.cpp", DicPaymentForm);
USEFORM("System\ApPrintSetup.cpp", ApPrnSetupForm);
USEFORM("BaseData\DicDelivery.cpp", DicDeliveryForm);
USEFORM("BaseData\DicInvoice.cpp", DicInvoiceForm);
USEFORM("System\ShowPrintSetup.cpp", ShowPrnSetupForm);
USEFORM("MainFrame.cpp", MainForm);
USEFORM("InforSearch\ApFilePage.cpp", ApFilePageForm);
USEFORM("tmpForm\TmpFormUnit.cpp", TestForm);
USEFORM("Purchase\Accept.cpp", AcceptForm);
USEFORM("Purchase\do.cpp", DoForm);
USEFORM("Purchase\ContainerInfo.cpp", ContainerInfoForm);
USEFORM("Purchase\Goods.cpp", GoodsForm);
USEFORM("Purchase\Finance.cpp", FinanceForm);
USEFORM("Purchase\Calc.cpp", CalcForm);
USEFORM("Purchase\Unit2.cpp", Form2);
USEFORM("Purchase\Assignment.cpp", AssignmentForm);
USEFORM("Purchase\PrnInvoice.cpp", PrnInvoiceForm);
USEFORM("Purchase\PrnPackingList.cpp", PrnPackingListForm);
USEFORM("Purchase\PrnContact.cpp", PrnContactForm);
USEFORM("Purchase\PrnDeclare.cpp", PrnDeclareForm);
USEFORM("Purchase\PrnAuth.cpp", PrnAuthForm);
USEFORM("Purchase\DicBoatNo.cpp", DicBoatNoForm);
USEFORM("Purchase\DicBoatOrder.cpp", DicBoatOrderForm);
USEFORM("Purchase\DicPack.cpp", DicPackForm);
USEFORM("Purchase\DicTransport.cpp", DicTransportForm);
USEFORM("Purchase\DicTrade.cpp", DicTradeForm);
USEFORM("Purchase\DicZhengMian.cpp", DicZhengMianForm);
USEFORM("Purchase\DicExcharge.cpp", DicExchargeForm);
USEFORM("Purchase\DicBargain.cpp", DicBargainForm);
USEFORM("Purchase\DicStatus1.cpp", DicStatus1Form);
USEFORM("Purchase\DicTargetCountry.cpp", DicTargetCountryForm);
USEFORM("Purchase\DicCurrency.cpp", DicCurrencyForm);
USEFORM("DicMerchandise.cpp", DicMerchandiseForm);
USEFORM("PrnOutBoat.cpp", PrnOutBoatForm);
USEFORM("DicClient.cpp", DicClientForm);
USEFORM("Purchase\DicSA.cpp", DicShipAgent);
USEFORM("CostAccounting.cpp", CostAccountingForm);
USEFORM("Purchase\PrnDeclareSub.cpp", PrnDeclareSubForm);
USEFORM("Purchase\PrnContactSub.cpp", PrnContactSubForm);
USEFORM("Purchase\PrnWuMuZhi.cpp", PrnWuMuZhiForm);
USEFORM("Purchase\PrnYSQRS.cpp", PrnYSQRSForm);
USEFORM("Purchase\PrnSCCK.cpp", PrnSCCKForm);
USEFORM("Purchase\PrnQYCNS.cpp", PrnQYCNSForm);
USEFORM("Purchase\DicSH.cpp", DicSHForm);
USEFORM("Purchase\DicOperUnit.cpp", DicOperUnitForm);
USEFORM("Purchase\DicCharge.cpp", DicChargeForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

	CString szSQL;

	try
	{
    Application->Initialize();
    Application->Title = "润顺报关系统";
    Application->CreateForm(__classid(Tdm1), &dm1);
#ifdef _DEBUG
	operatorcode="root";
  operatorname="root";
  operator_class="1";
#else

		InitialODBC();

		TUserLoginForm *pLogin;
		pLogin=new TUserLoginForm(Application);
		pLogin->ShowModal();

		int nLogin;
		nLogin=pLogin->ModalResult;
		delete pLogin;
		if(nLogin==mrCancel)
		{
			Application->Terminate();
			return 0;
		}
#endif
		szSQL.Format("select * from operator where op_code='%s'",operatorcode.c_str());
		RunSQL(dm1->Query1,szSQL,true);
		if(!dm1->Query1->Eof)
		{
			strcpy(g_theOperator.op_code,dm1->Query1->FieldByName("op_code")->AsString.c_str());
			strcpy(g_theOperator.op_name,dm1->Query1->FieldByName("op_name")->AsString.c_str());
			g_theOperator.op_class=dm1->Query1->FieldByName("op_class")->AsInteger;
			strcpy(g_theOperator.op_dept,dm1->Query1->FieldByName("op_dept")->AsString.c_str());
			strcpy(g_theOperator.op_cpcode,dm1->Query1->FieldByName("op_cpcode")->AsString.c_str());
		}

		Screen->Cursor=crHourGlass;
//		Application->CreateForm(__classid(TTestForm), &TestForm);                
		Application->CreateForm(__classid(TMainForm), &MainForm);
		Screen->Cursor=crDefault;
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
  return 1;
/*
	CString szSQL;

	try
	{
    Application->Initialize();
    Application->Title = "润顺报关系统";
    Application->CreateForm(__classid(Tdm1), &dm1);
#ifdef _DEBUG
	operatorcode="root";
  operatorname="root";
  operator_class="1";
#else

		InitialODBC();

		TUserLoginForm *pLogin;
		pLogin=new TUserLoginForm(Application);
		pLogin->ShowModal();

		int nLogin;
		nLogin=pLogin->ModalResult;
		delete pLogin;
		if(nLogin==mrCancel)
		{
			Application->Terminate();
			return 0;
		}
#endif
		szSQL.Format("select * from operator where op_code='%s'",operatorcode.c_str());
		RunSQL(dm1->Query1,szSQL,true);
		if(!dm1->Query1->Eof)
		{
			strcpy(g_theOperator.op_code,dm1->Query1->FieldByName("op_code")->AsString.c_str());
			strcpy(g_theOperator.op_name,dm1->Query1->FieldByName("op_name")->AsString.c_str());
			g_theOperator.op_class=dm1->Query1->FieldByName("op_class")->AsInteger;
			strcpy(g_theOperator.op_dept,dm1->Query1->FieldByName("op_dept")->AsString.c_str());
			strcpy(g_theOperator.op_cpcode,dm1->Query1->FieldByName("op_cpcode")->AsString.c_str());
		}

		Screen->Cursor=crHourGlass;
//		Application->CreateForm(__classid(TTestForm), &TestForm);                
		Application->CreateForm(__classid(TMainForm), &MainForm);
		Screen->Cursor=crDefault;
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
  return 1;
*/
}
//---------------------------------------------------------------------------





