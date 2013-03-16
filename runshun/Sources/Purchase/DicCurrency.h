//---------------------------------------------------------------------------

#ifndef DicCurrencyH
#define DicCurrencyH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TDicCurrencyForm : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TLabel *msgState;
        TListView *ListView1;
        TPanel *Panel1;
        TLabel *Label3;
        TEdit *edtName;
        TButton *btnOK0;
        TButton *btnCancel0;
        TButton *btnAddNew;
        TButton *btnEdit;
        TButton *btnDelete;
        TButton *btnRefresh;
        TButton *btnExit;
        TLabel *Label2;
        TEdit *edtID;
        TImage *Image1;
        TLabel *Label4;
        void __fastcall ListView1Click(TObject *Sender);
        void __fastcall btnOK0Click(TObject *Sender);
        void __fastcall btnCancel0Click(TObject *Sender);
        void __fastcall btnAddNewClick(TObject *Sender);
        void __fastcall btnEditClick(TObject *Sender);
        void __fastcall btnDeleteClick(TObject *Sender);
        void __fastcall btnRefreshClick(TObject *Sender);
        void __fastcall btnExitClick(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormShow(TObject *Sender);
private:	// User declarations
  enum { EN_IDLE,EN_ADDNEW,EN_EDIT } m_enWorkState;
public:		// User declarations
	int m_nAuthor;
  void RefreshData();
  void Row2Editor();
  void ResetCtrl();
        __fastcall TDicCurrencyForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDicCurrencyForm *DicCurrencyForm;
//---------------------------------------------------------------------------
#endif
