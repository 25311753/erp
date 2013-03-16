//---------------------------------------------------------------------------

#ifndef FinanceOpH
#define FinanceOpH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include "trayicon.h"
//---------------------------------------------------------------------------
//typedef std::map<AnsiString, int>       type_t;
class TFinanceOpForm : public TForm
{
__published:	// IDE-managed Components
        TListView *lvOId;
        TPanel *plQuery;
        TPanel *Panel1;
        TEdit *edtQryOId;
        TPanel *Panel20;
        TCheckBox *cbIsQryByDate;
        TDateTimePicker *dtpQryDateBegin;
        TDateTimePicker *dtpQryDateEnd;
        TPanel *plInput;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TPanel *Panel21;
        TPanel *Panel3;
        TEdit *edtInPrice;
        TPanel *Panel4;
        TEdit *edtInBank;
        TPanel *Panel5;
        TEdit *edtCfmOpName;
        TPanel *Panel6;
        TPanel *Panel8;
        TPanel *Panel9;
        TEdit *edtOutBank;
        TPanel *Panel10;
        TEdit *edtOutAccount;
        TPanel *Panel11;
        TEdit *edtOutMan;
        TListView *lvOut;
        TPanel *Panel14;
        TPanel *Panel15;
        TEdit *edtKbValue;
        TPanel *Panel16;
        TEdit *edtRecipient;
        TPanel *Panel17;
        TEdit *edtBank;
        TEdit *edtBankDeposit;
        TPanel *Panel12;
        TPanel *Panel13;
        TPanel *Panel19;
        TDateTimePicker *dtpOutDate;
        TComboBox *cbbIsAll;
        TDateTimePicker *dtpKbDate;
        TButton *btnOKIn;
        TButton *btnOkOut;
        TButton *btnOkKb;
        TEdit *edtDebug;
        TPanel *Panel2;
        TEdit *edtShouldIn;
        TPanel *Panel22;
        TEdit *edtPecIn;
        TButton *Button2;
        TButton *btnCompare;
        TCheckBox *cbNoDelay;
        TButton *btnTotalCompare;
        TButton *btnQry;
        TPanel *Panel18;
        TComboBox *cbbQryOpCodeSl;
        TPanel *Panel25;
        TComboBox *cbbQryOpCodeOp;
        TPanel *Panel26;
        TComboBox *cbbQryClShortName;
        TPanel *Panel27;
        TComboBox *cbbQryWay;
        TPanel *Panel28;
        TEdit *edtQryLoadingId;
        TPanel *Panel29;
        TComboBox *cbbQrySupply;
        TPanel *Panel30;
        TEdit *edtQryOutBank;
        TPanel *Panel31;
        TEdit *edtQryOutMan;
        TListView *lvInDetail;
        TCheckBox *cbIsDoneIn;
        TPanel *Panel7;
        TDateTimePicker *dtpInDate;
        TPanel *Panel23;
        TDateTimePicker *dtpFiDate;
        TPanel *Panel24;
        TDateTimePicker *dtpOpDate;
        TPanel *Panel32;
        TEdit *edtClShortName;
        TPanel *Panel33;
        TEdit *edtOpCodeSl;
        TPanel *Panel34;
        TComboBox *cbbIsArrival;
        TPanel *Panel35;
        TEdit *edtOpCodeFi;
        TTrayIcon *TrayIcon1;
        TButton *Button1;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall btnQryClick(TObject *Sender);
        void __fastcall lvOIdSelectItem(TObject *Sender, TListItem *Item,
          bool Selected);
        void __fastcall btnOKInClick(TObject *Sender);
        void __fastcall lvOutSelectItem(TObject *Sender, TListItem *Item,
          bool Selected);
        void __fastcall btnOkOutClick(TObject *Sender);
        void __fastcall btnOkKbClick(TObject *Sender);
        void __fastcall btnCompareClick(TObject *Sender);
        void __fastcall btnTotalCompareClick(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
        enum { EN_IDLE,EN_ADDNEW,EN_EDIT } m_enWorkState;

//        type_t m_mInType;
public:		// User declarations
        int m_nAuthor;
        __fastcall TFinanceOpForm(TComponent* Owner);
        void clearInput();
        void clearQryInput();
        void ResetCtrl();

        //flush
        void Editor2RowUpdateOut(TListItem *pItem);
        void Row2EditorKb(TListItem *pItem);
        void Editor2RowUpdateKb(TListItem *pItem);
        bool isInNoDelay(AnsiString settlement_cycle_type, int date_diff);        
};
//---------------------------------------------------------------------------
extern PACKAGE TFinanceOpForm *FinanceOpForm;
//---------------------------------------------------------------------------
#endif
