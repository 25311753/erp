//---------------------------------------------------------------------------

#ifndef DicMerchandiseH
#define DicMerchandiseH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TDicMerchandiseForm : public TForm
{
__published:	// IDE-managed Components
        TLabel *msgState;
        TListView *ListView1;
        TEdit *edtMCode;
        TButton *btnOK0;
        TButton *btnCancel0;
        TButton *btnAddNew;
        TButton *btnEdit;
        TButton *btnDelete;
        TButton *btnRefresh;
        TButton *btnExit;
        TEdit *edtMname;
        TLabel *Label4;
        TEdit *edtSpec;
        TEdit *edtFU;
        TEdit *edtSU;
        TEdit *edtUnitPrice;
        TImage *Image1;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label8;
        TPanel *plQry;
        TLabel *Label9;
        TEdit *edtQryMname;
        TButton *btnQry;
        TLabel *Label10;
        TLabel *Label11;
        TLabel *Label12;
        TLabel *Label13;
        TLabel *Label14;
        TComboBox *cbbCrName1;
        TComboBox *cbbCrName2;
        TEdit *edtUnitPrice2;
        TEdit *edtUnitPrice1;
        TEdit *edtWeightPercent;
        TEdit *edtDebug;
        TLabel *Label15;
        TEdit *edtNo;
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall ListView1Click(TObject *Sender);
        void __fastcall btnOK0Click(TObject *Sender);
        void __fastcall btnCancel0Click(TObject *Sender);
        void __fastcall btnAddNewClick(TObject *Sender);
        void __fastcall btnEditClick(TObject *Sender);
        void __fastcall btnDeleteClick(TObject *Sender);
        void __fastcall btnRefreshClick(TObject *Sender);
        void __fastcall btnExitClick(TObject *Sender);
        void __fastcall btnQryClick(TObject *Sender);
        void __fastcall edtQryMnameKeyPress(TObject *Sender, char &Key);
private:	// User declarations
  enum { EN_IDLE,EN_ADDNEW,EN_EDIT } m_enWorkState;
public:		// User declarations
	int m_nAuthor;
        void RefreshData();
        void Row2Editor();
        void ResetCtrl();
        __fastcall TDicMerchandiseForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDicMerchandiseForm *DicMerchandiseForm;
//---------------------------------------------------------------------------
#endif
