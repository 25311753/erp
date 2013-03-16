//---------------------------------------------------------------------------

#ifndef MaterHXCompareH
#define MaterHXCompareH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TMaterHXCompareForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TListView *lstView;
	TPanel *Panel1;
	TEdit *edtTech;
	TLabel *Label2;
	TLabel *Label3;
	TEdit *edtType;
	TLabel *Label4;
	TEdit *edtMater;
	TButton *btnPickup;
	TLabel *Label5;
	TEdit *edtSpec;
	TButton *btnEdit;
	TButton *btnPrint;
	TButton *btnExit;
	TButton *btnRefresh;
	TButton *btnOK;
	void __fastcall btnExitClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall btnRefreshClick(TObject *Sender);
	void __fastcall lstViewSelectItem(TObject *Sender, TListItem *Item,
          bool Selected);
	void __fastcall lstViewClick(TObject *Sender);
	void __fastcall btnPickupClick(TObject *Sender);
	void __fastcall btnEditClick(TObject *Sender);
	void __fastcall edtMaterExit(TObject *Sender);
	void __fastcall btnOKClick(TObject *Sender);
	void __fastcall btnPrintClick(TObject *Sender);
	void __fastcall edtMaterKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
	enum { EN_STATE_EDIT,EN_STATE_IDLE } m_enState;

	void ResetCtrl();
	void RefreshData();

public:		// User declarations
	__fastcall TMaterHXCompareForm(TComponent* Owner);

	int m_nAuthor;
};
//---------------------------------------------------------------------------
extern PACKAGE TMaterHXCompareForm *MaterHXCompareForm;
//---------------------------------------------------------------------------
#endif
