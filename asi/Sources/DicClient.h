//---------------------------------------------------------------------------

#ifndef DicClientH
#define DicClientH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include "LfcString.h"
#include "trayicon.h"
//---------------------------------------------------------------------------
class TDicClientForm : public TForm
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
        TEdit *edtDebug;
        TButton *btnQry;
        TPanel *plInput;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label8;
        TLabel *Label11;
        TLabel *Label12;
        TLabel *Label13;
        TLabel *Label14;
        TLabel *Label15;
        TLabel *Label16;
        TLabel *Label17;
        TLabel *Label18;
        TLabel *Label19;
        TLabel *Label20;
        TLabel *Label21;
        TLabel *Label22;
        TLabel *Label23;
        TLabel *Label24;
        TLabel *Label25;
        TEdit *edtCid;
        TEdit *edtNameShort;
        TEdit *edtNameCh;
        TEdit *edtNameEn;
        TComboBox *cbbClientType;
        TComboBox *cbbOpType;
        TEdit *edtAddress;
        TEdit *edtTel;
        TEdit *edtFax;
        TEdit *edtLinkMan;
        TEdit *edtTelLinkMan;
        TEdit *edtQQ;
        TEdit *edtMsn;
        TEdit *edtEmail;
        TComboBox *cbbSettlementType;
        TComboBox *cbbReputation;
        TComboBox *cbbSettlementCycle;
        TEdit *edtFirstOpId;
        TDateTimePicker *dtpDate;
        TEdit *edtRemarks;
        TComboBox *cbbOpCodeSl;
        TLabel *Label1;
        TComboBox *cbbOpCodeOp;
        TTrayIcon *TrayIcon1;
        TButton *Button1;
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
        void __fastcall ListView1DrawItem(TCustomListView *Sender,
          TListItem *Item, TRect &Rect, TOwnerDrawState State);
        void __fastcall ListView1CustomDrawItem(TCustomListView *Sender,
          TListItem *Item, TCustomDrawState State, bool &DefaultDraw);
        void __fastcall btnQryClick(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
  enum { EN_IDLE,EN_ADDNEW,EN_EDIT } m_enWorkState;
//        int m_nAuthor;
public:		// User declarations
	int m_nAuthor;
        void RefreshData(CString outsideSQL="");
        void Row2Editor();
        void ResetCtrl();
        __fastcall TDicClientForm(TComponent* Owner);
        void Editor2Row(TListItem *pItem);
        void Editor2Row2(TListItem *pItem);

        void clearInput();
        //rt: true-valid
        bool checkInput();
        AnsiString getInsertedId();
};
//---------------------------------------------------------------------------
extern PACKAGE TDicClientForm *DicClientForm;
//---------------------------------------------------------------------------
#endif
