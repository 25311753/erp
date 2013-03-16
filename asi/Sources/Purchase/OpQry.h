//---------------------------------------------------------------------------

#ifndef OpQryH
#define OpQryH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TOpQryForm : public TForm
{
__published:	// IDE-managed Components
        TPanel *plQuery;
        TPanel *Panel15;
        TEdit *edtQryOId;
        TPanel *Panel20;
        TCheckBox *cbIsQryByDate;
        TDateTimePicker *dtpQryDateBegin;
        TDateTimePicker *dtpQryDateEnd;
        TPanel *Panel14;
        TComboBox *cbbQryGoodsSrc;
        TPanel *Panel16;
        TComboBox *cbbQryGoodsDst;
        TComboBox *cbbQryWay;
        TPanel *Panel24;
        TComboBox *cbbQryWay0;
        TPanel *Panel25;
        TEdit *edtQryLoadingId;
        TPanel *Panel26;
        TComboBox *cbbQryClShortName;
        TPanel *Panel28;
        TComboBox *cbbQryOpCodeSl;
        TPanel *Panel29;
        TPanel *Panel18;
        TComboBox *cbbIsArrival;
        TButton *btnQry;
        TListView *lvOpDetail;
        TPanel *Panel1;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *lbTotalCnt;
        TLabel *Label4;
        TLabel *lbTotalLiRun;
        TLabel *Label6;
        TLabel *lbTotalKB;
        TPopupMenu *PopupMenu1;
        TMenuItem *N21;
        TMenuItem *N31;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall cbbQryOpCodeSlChange(TObject *Sender);
        void __fastcall btnQryClick(TObject *Sender);
        void __fastcall N31Click(TObject *Sender);
        void __fastcall lvOpDetailMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall N21Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TOpQryForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TOpQryForm *OpQryForm;
//---------------------------------------------------------------------------
#endif
