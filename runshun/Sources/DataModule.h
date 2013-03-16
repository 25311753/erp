//---------------------------------------------------------------------------

#ifndef DataModuleH
#define DataModuleH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Db.hpp>
#include <DBTables.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------

extern AnsiString g_szODBC;
extern AnsiString g_szDBUser;
extern AnsiString g_szDBPass;

class Tdm1 : public TDataModule
{
__published:	// IDE-managed Components
   TDatabase *db1;
   TDataSource *DS1;
   TQuery *Query1;
   TQuery *Query2;
   TQuery *Query3;
   TDataSource *DSRights;
   TStoredProc *SPcomn;
   TDataSource *DSOper;
   TTable *OperTab;
   TTable *ClassRights;
   TTable *Table1;
	TQuery *sqlPrint;
	TDatabase *db2;
	TQuery *sqlElse;
        TQuery *Query4;
        TQuery *sqlPrint2;
        TQuery *sqlPrintDeclare;
private:	// User declarations
public:		// User declarations
   bool ConnectDB();

	bool OpenDatabase();
	void CloseDatabase();
	void SetupDB();
  bool OpenDatabase(TDatabase *pDB);
  void CloseDatabase(TDatabase *pDB);

   __fastcall Tdm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tdm1 *dm1;
//---------------------------------------------------------------------------
#endif
