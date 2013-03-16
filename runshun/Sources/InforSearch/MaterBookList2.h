//---------------------------------------------------------------------------

#ifndef MaterBookList2H
#define MaterBookList2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TMaterBookListForm2 : public TForm
{
__published:	// IDE-managed Components
        TListView *lstView;
        TLabel *Label1;
        TPanel *Panel1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *txtName;
        TLabel *Label4;
        TLabel *Label5;
        TEdit *edtMNCode;
        TButton *btnPickup;
        TButton *btnExit;
        TButton *btnToExcel;
        TButton *btnQuery;
        TButton *btnToBook;
        TButton *btnToPurchase;
        TButton *btnPrint;
        TEdit *edtDPName;
        TEdit *edtFactCard;
        void __fastcall btnQueryClick(TObject *Sender);
        void __fastcall btnExitClick(TObject *Sender);
        void __fastcall btnToPurchaseClick(TObject *Sender);
        void __fastcall lstViewClick(TObject *Sender);
        void __fastcall lstViewSelectItem(TObject *Sender, TListItem *Item,
          bool Selected);
        void __fastcall btnToBookClick(TObject *Sender);
        void __fastcall btnPrintClick(TObject *Sender);
        void __fastcall btnToExcelClick(TObject *Sender);
private:	// User declarations
	void ResetCtrl();
public:		// User declarations
        __fastcall TMaterBookListForm2(TComponent* Owner);
  AnsiString m_szIDFirst;
};
//---------------------------------------------------------------------------
extern PACKAGE TMaterBookListForm2 *MaterBookListForm2;
//---------------------------------------------------------------------------
#endif
