//---------------------------------------------------------------------------

#include <vcl.h>

#include "MainFrame.h"
#include "UserLogin.h"
#include "DBSetup.h"
#include "ComVar.h"
#include "DataModule.h"
#include "BaseCode.h"
#include "GlobalConst.h"
#include "const.h"
#include "AlarmSale.h"
#pragma hdrstop

USEFORM("DataModule.cpp", dm1); /* TDataModule: File Type */
USEFORM("System\UserLogin.cpp", UserLoginForm);
USEFORM("FromLCG\BaseFormUnit.cpp", BaseForm);
USEFORM("System\DBSetup.cpp", DBSetupForm);
USEFORM("FromLCG\operpwdunit.cpp", operpwdform);
USEFORM("FromLCG\operatorunit.cpp", operatorform);
USEFORM("FromLCG\calsssetunit.cpp", classsetform);
USEFORM("System\ClassRight.cpp", ClassRightForm);
USEFORM("System\ShowPrintSetup.cpp", ShowPrnSetupForm);
USEFORM("MainFrame.cpp", MainForm);
USEFORM("DicClient.cpp", DicClientForm);
USEFORM("Purchase\DicSupplier.cpp", DicSupplierForm);
USEFORM("Purchase\Operation.cpp", OperationForm);
USEFORM("Purchase\FinanceOp.cpp", FinanceOpForm);
USEFORM("Purchase\Commition.cpp", CommitionForm);
USEFORM("Purchase\DicClientQry.cpp", DicClientQryForm);
USEFORM("Purchase\NewClientPrize.cpp", NewClientPrizeForm);
USEFORM("Purchase\QrySale.cpp", QrySaleForm);
USEFORM("Purchase\AlarmSale.cpp", AlarmSaleForm);
USEFORM("Purchase\YjQry.cpp", YjQryForm);
USEFORM("Purchase\Tc.cpp", TcForm);
USEFORM("Purchase\XkQry.cpp", XkQryForm);
USEFORM("Purchase\OpQry.cpp", OpQryForm);
USEFORM("Purchase\XkCSSZ.cpp", XkCSSZForm);
USEFORM("Purchase\TcCSSZ.cpp", TcCSSZForm);
USEFORM("Purchase\YjCSSZ.cpp", YjCSSZForm);
USEFORM("Purchase\OpQryInOut.cpp", OpQryInOutForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	CString szSQL;

	try
	{
    Application->Initialize();
    Application->Title = "地平线物流管理系统";
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
    Application->Title = "地平线物流管理系统";
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




