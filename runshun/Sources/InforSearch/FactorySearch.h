//---------------------------------------------------------------------------

#ifndef FactorySearchH
#define FactorySearchH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <AppEvnts.hpp>
//---------------------------------------------------------------------------
class TFactorySearchForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TListView *lstView;
	TPanel *Panel1;
	TLabel *Label2;
	TEdit *edtID;
	TLabel *Label3;
	TEdit *edtShort;
	TLabel *Label4;
	TEdit *edtName;
	TButton *btnQuery;
	TButton *btnDetail;
	TButton *btnExit;
	TLabel *txtTips;
	TApplicationEvents *ApplicationEvents1;
	TButton *btnOK;
	void __fastcall btnExitClick(TObject *Sender);
	void __fastcall btnQueryClick(TObject *Sender);
	void __fastcall btnDetailClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall lstViewClick(TObject *Sender);
	void __fastcall lstViewSelectItem(TObject *Sender, TListItem *Item,
          bool Selected);
	void __fastcall ApplicationEvents1Idle(TObject *Sender, bool &Done);
	void __fastcall lstViewDblClick(TObject *Sender);
	void __fastcall btnOKClick(TObject *Sender);
private:	// User declarations
	void ResetCtrl();

public:		// User declarations
	CString m_szID;

	__fastcall TFactorySearchForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFactorySearchForm *FactorySearchForm;
//---------------------------------------------------------------------------
#endif
