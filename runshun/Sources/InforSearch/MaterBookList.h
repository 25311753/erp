//---------------------------------------------------------------------------

#ifndef MaterBookListH
#define MaterBookListH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TMaterBookListForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TListView *lstView;
	TPanel *Panel1;
	TLabel *Label2;
	TEdit *edtMNCode;
	TButton *btnPickup;
	TLabel *Label3;
	TLabel *txtName;
	TButton *btnExit;
	TButton *btnToExcel;
	TButton *btnQuery;
	TButton *btnToBook;
	TButton *btnToPurchase;
	TButton *btnPrint;
	TLabel *Label4;
	TEdit *edtDPName;
	TLabel *Label5;
	TEdit *edtFactCard;
	void __fastcall btnExitClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall btnQueryClick(TObject *Sender);
	void __fastcall btnPickupClick(TObject *Sender);
	void __fastcall btnToBookClick(TObject *Sender);
	void __fastcall btnToPurchaseClick(TObject *Sender);
	void __fastcall lstViewClick(TObject *Sender);
	void __fastcall lstViewSelectItem(TObject *Sender, TListItem *Item,
          bool Selected);
	void __fastcall btnToExcelClick(TObject *Sender);
	void __fastcall btnPrintClick(TObject *Sender);
private:	// User declarations
	void ResetCtrl();

public:		// User declarations
	__fastcall TMaterBookListForm(TComponent* Owner);

  AnsiString m_szIDFirst;
};
//---------------------------------------------------------------------------
extern PACKAGE TMaterBookListForm *MaterBookListForm;
//---------------------------------------------------------------------------
#endif
