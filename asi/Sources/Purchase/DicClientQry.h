//---------------------------------------------------------------------------

#ifndef DicClientQryH
#define DicClientQryH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "LfcString.h"
//---------------------------------------------------------------------------
class TDicClientQryForm : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TLabel *Label1;
        TLabel *Label4;
        TLabel *Label9;
        TLabel *Label10;
        TLabel *Label26;
        TLabel *Label27;
        TLabel *Label28;
        TLabel *Label29;
        TLabel *Label30;
        TLabel *Label31;
        TLabel *Label32;
        TLabel *Label33;
        TLabel *Label34;
        TLabel *Label35;
        TLabel *Label36;
        TLabel *Label37;
        TLabel *Label38;
        TLabel *Label39;
        TLabel *Label41;
        TEdit *edtQryCid;
        TEdit *edtQryNameShort;
        TEdit *edtQryNameCh;
        TEdit *edtQryNameEn;
        TComboBox *cbbQryClientType;
        TComboBox *cbbQryOpType;
        TEdit *edtQryAddress;
        TEdit *edtQryTel;
        TEdit *edtQryFax;
        TEdit *edtQryLinkMan;
        TEdit *edtQryTelLinkMan;
        TEdit *edtQryQQ;
        TEdit *edtQryMsn;
        TEdit *edtQryEmail;
        TComboBox *cbbQrySettlementType;
        TComboBox *cbbQryReputation;
        TComboBox *cbbQrySettlementCycle;
        TDateTimePicker *dtpQryDateBegin;
        TComboBox *cbbQryOpCodeSl;
        TButton *btnExit;
        TButton *btnQry;
        TDateTimePicker *dtpQryDateEnd;
        TCheckBox *cbIsQryByDate;
        void __fastcall btnExitClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall btnQryClick(TObject *Sender);

private:	// User declarations
public:		// User declarations
        __fastcall TDicClientQryForm(TComponent* Owner);
        void clearInput();
        CString m_outsideSQL;
};
//---------------------------------------------------------------------------
extern PACKAGE TDicClientQryForm *DicClientQryForm;
//---------------------------------------------------------------------------
#endif
