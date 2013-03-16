//---------------------------------------------------------------------------

#ifndef CommitionH
#define CommitionH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "trayicon.h"
//---------------------------------------------------------------------------
class TCommitionForm : public TForm
{
__published:	// IDE-managed Components
        TPanel *plInput;
        TPanel *Panel4;
        TPanel *Panel2;
        TComboBox *cbbOpCodeSl;
        TDateTimePicker *dtpYearMonth;
        TPanel *Panel1;
        TPanel *Panel3;
        TEdit *edtBusiVolume;
        TDateTimePicker *dtpGrantDate;
        TPanel *plQuery;
        TPanel *Panel20;
        TCheckBox *cbIsQryByDate;
        TDateTimePicker *dtpQryDateBegin;
        TDateTimePicker *dtpQryDateEnd;
        TButton *btnQry;
        TPanel *Panel5;
        TComboBox *cbbQryOpCodeSl;
        TButton *btnMod;
        TButton *btnDel;
        TButton *btnCancel;
        TButton *btnOK;
        TListView *lvCommition;
        TButton *btnAdd;
        TEdit *edtDebug;
        TPanel *Panel6;
        TComboBox *cbbPassed;
        TListView *lvYearCommition;
        TLabel *Label1;
        TPanel *Panel21;
        TPanel *Panel7;
        TButton *btnQryYear;
        TComboBox *cbbYearOpCodeSl;
        TPanel *Panel8;
        TPanel *Panel9;
        TComboBox *cbbQryYear;
        TPanel *Panel10;
        TEdit *edtCntNewCli;
        TPanel *Panel11;
        TComboBox *cbbRatio;
        TLabel *Label2;
        TTrayIcon *TrayIcon1;
        TButton *Button1;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall btnOKClick(TObject *Sender);
        void __fastcall btnQryClick(TObject *Sender);
        void __fastcall lvCommitionSelectItem(TObject *Sender,
          TListItem *Item, bool Selected);
        void __fastcall btnDelClick(TObject *Sender);
        void __fastcall btnModClick(TObject *Sender);
        void __fastcall btnAddClick(TObject *Sender);
        void __fastcall btnCancelClick(TObject *Sender);
        void __fastcall btnQryYearClick(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        enum { EN_IDLE,EN_ADDNEW,EN_EDIT } m_enWorkState;

        void ResetCtrl();        
        __fastcall TCommitionForm(TComponent* Owner);
        void clearInput();
        bool checkInput();

        int onAdd();
        void onMod();

        //flush
        void Editor2RowAdd(TListView *lv);
           
};
//---------------------------------------------------------------------------
extern PACKAGE TCommitionForm *CommitionForm;
//---------------------------------------------------------------------------
#endif
