//---------------------------------------------------------------------------

#ifndef DicSupplierH
#define DicSupplierH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include "trayicon.h"
//---------------------------------------------------------------------------
class TDicSupplierForm : public TForm
{
__published:	// IDE-managed Components
        TLabel *msgState;
        TListView *ListView1;
        TButton *btnAddNew;
        TButton *btnDelete;
        TButton *btnEdit;
        TButton *btnExit;
        TButton *btnRefresh;
        TButton *btnOK0;
        TButton *btnCancel0;
        TPanel *plQry;
        TLabel *Label9;
        TLabel *Label10;
        TEdit *edtQryNameCh;
        TButton *btnQry;
        TPanel *plInput;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label12;
        TLabel *Label13;
        TLabel *Label14;
        TLabel *Label15;
        TLabel *Label20;
        TLabel *Label21;
        TLabel *Label22;
        TLabel *Label23;
        TLabel *Label1;
        TLabel *Label4;
        TEdit *edtSpId;
        TEdit *edtName;
        TEdit *edtTel;
        TEdit *edtFax;
        TEdit *edtChargeMan;
        TEdit *edtTelLinkMan;
        TComboBox *cbbSettlementType;
        TComboBox *cbbReputation;
        TComboBox *cbbLicense;
        TEdit *edtBankAccount;
        TEdit *edtAddress;
        TEdit *edtBank;
        TTrayIcon *TrayIcon1;
        TButton *Button1;
        TLabel *Label5;
        TEdit *edtHuMing;
        void __fastcall ListView1Click(TObject *Sender);
        void __fastcall btnRefreshClick(TObject *Sender);
        void __fastcall btnExitClick(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall btnOK0Click(TObject *Sender);
        void __fastcall btnCancel0Click(TObject *Sender);
        void __fastcall btnAddNewClick(TObject *Sender);
        void __fastcall btnEditClick(TObject *Sender);
        void __fastcall btnDeleteClick(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
  enum { EN_IDLE,EN_ADDNEW,EN_EDIT } m_enWorkState ;
public:		// User declarations
        __fastcall TDicSupplierForm(TComponent* Owner);
	int m_nAuthor;
        void RefreshData();
        void Row2Editor();
        void ResetCtrl();
        void Editor2RowUpdate(TListItem *pItem);
        void Editor2RowAdd(TListItem *pItem);
        void clearInput();
        //rt: true-valid
        bool checkInput();       
};
//---------------------------------------------------------------------------
extern PACKAGE TDicSupplierForm *DicSupplierForm;
//---------------------------------------------------------------------------
#endif
