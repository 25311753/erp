//---------------------------------------------------------------------------

#ifndef TcCSSZH
#define TcCSSZH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TTcCSSZForm : public TForm
{
__published:	// IDE-managed Components
        TPanel *plInput;
        TPanel *Panel2;
        TComboBox *cbbOpCodeSl;
        TDateTimePicker *dtpYearMonth;
        TPanel *Panel1;
        TPanel *Panel10;
        TEdit *edtBase;
        TListView *lvTcCSSZ;
        TButton *btnAdd;
        TButton *btnMod;
        TButton *btnDel;
        TButton *btnOK;
        TButton *btnCancel;
        TEdit *edtDebug;
        TPanel *Panel3;
        TComboBox *cbbRatio;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall lvTcCSSZSelectItem(TObject *Sender,
          TListItem *Item, bool Selected);
        void __fastcall btnModClick(TObject *Sender);
        void __fastcall btnOKClick(TObject *Sender);
        void __fastcall btnCancelClick(TObject *Sender);
        void __fastcall btnDelClick(TObject *Sender);
        void __fastcall btnAddClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TTcCSSZForm(TComponent* Owner);

        enum { EN_IDLE,EN_ADDNEW,EN_EDIT } m_enWorkState;
        void ResetCtrl();
        bool checkInput();
        int  onAdd();
        void onMod();

        void Editor2RowAdd(TListView *lv);
};
//---------------------------------------------------------------------------
extern PACKAGE TTcCSSZForm *TcCSSZForm;
//---------------------------------------------------------------------------
#endif
