//---------------------------------------------------------------------------

#ifndef TreatStockRecordH
#define TreatStockRecordH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TTreatStockRecordForm : public TForm
{
__published:	// IDE-managed Components
	TListView *lstView;
	TLabel *Label1;
	TPanel *Panel1;
	TButton *btnExit;
        TListView *ListView1;
        TLabel *Label3;
        TLabel *Label4;
        TButton *Button1;
        TButton *Button2;
        TButton *btnRefresh;
        TButton *btnToExcel;
        TEdit *edtID;
        TLabel *Label2;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall btnExitClick(TObject *Sender);
	void __fastcall btnToExcelClick(TObject *Sender);
	void __fastcall btnRefreshClick(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
private:	// User declarations
	CString GetMFName(LPCSTR lpszID,CArray<BASE2COLDATA,BASE2COLDATA>&lstData);
	void RefreshData();
        void RefreshDatahistory();


public:		// User declarations
	__fastcall TTreatStockRecordForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTreatStockRecordForm *TreatStockRecordForm;
//---------------------------------------------------------------------------
#endif
