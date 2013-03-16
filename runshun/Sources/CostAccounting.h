//---------------------------------------------------------------------------

#ifndef CostAccountingH
#define CostAccountingH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "BaseCode/LfcArray_s.h"
//---------------------------------------------------------------------------
class TCostAccountingForm : public TForm
{
__published:	// IDE-managed Components
        TPanel *plQry;
        TLabel *lbGoodsPerf;
        TEdit *edtCid;
        TEdit *edtDeclareId;
        TEdit *edtContainerinfo;
        TEdit *edtClient;
        TPanel *Panel3;
        TPanel *Panel4;
        TPanel *Panel7;
        TPanel *Panel9;
        TPanel *Panel20;
        TCheckBox *cbIsQryByDate;
        TDateTimePicker *dtpQryAcceptDate;
        TDateTimePicker *dtpQryAcceptDateEnd;
        TPanel *plMod;
        TComboBox *cbb1;
        TComboBox *cbb2;
        TComboBox *cbb3;
        TComboBox *cbb4;
        TComboBox *cbb5;
        TComboBox *cbb6;
        TComboBox *cbb7;
        TComboBox *cbb8;
        TComboBox *cbb9;
        TComboBox *cbb10;
        TEdit *edtCharge1;
        TEdit *edtCharge2;
        TEdit *edtCharge3;
        TEdit *edtCharge4;
        TEdit *edtCharge5;
        TEdit *edtCharge6;
        TEdit *edtCharge7;
        TEdit *edtCharge8;
        TEdit *edtCharge9;
        TEdit *edtCharge10;
        TEdit *edtBaseCost;
        TPanel *Panel10;
        TPanel *Panel11;
        TButton *btnMod;
        TButton *btnQuery;
        TButton *btnDump;
        TListView *lstViewPure;
        TButton *btnOK;
        TButton *btnCancel;
        TPanel *Panel45;
        TEdit *edtDebug;
        TEdit *edtMockDeclareid;
        TPanel *Panel1;
        TEdit *edtRemark;
        TButton *Button1;
        TListView *lstView;
        TPanel *Panel2;
        TPanel *Panel5;
        TPanel *Panel6;
        TEdit *edtIn;
        TEdit *edtBase;
        TEdit *edtPure;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall lstViewClick(TObject *Sender);
        void __fastcall lstViewSelectItem(TObject *Sender, TListItem *Item,
          bool Selected);
        void __fastcall btnModClick(TObject *Sender);
        void __fastcall btnOKClick(TObject *Sender);
        void __fastcall btnCancelClick(TObject *Sender);
        void __fastcall btnQueryClick(TObject *Sender);
        void __fastcall btnDumpClick(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
        enum { EN_IDLE,/*EN_ADDNEW,*/EN_EDIT } m_enWorkState; //状态
//        bool isHasResult;
public:		// User declarations
        __fastcall TCostAccountingForm(TComponent* Owner);
        void InsertValue(TComboBox *cbb, TEdit *edt);
        void InsertCustFreeToListView2(int row, TComboBox *pcbb, AnsiString col_value);
        void InsertCustFreeToListViewOri(int row, int pos, AnsiString col_value);
        bool IsDupFree(); // 判断费用列表是否有重复项
        float getCharge(TEdit *edt);
        TComboBox *getCbb(int i);
        TEdit *getEdt(int i);
        void ResetCharges();

        int ModCharge();
        void flushSum();
        void ResetCtrl();
        CString getFirstContainerNo(AnsiString c);
        void clearQryInput();
        CString getAllContainerNo(AnsiString c);        // get all conno , join by ","        
};
//---------------------------------------------------------------------------
extern PACKAGE TCostAccountingForm *CostAccountingForm;
//---------------------------------------------------------------------------
#endif
