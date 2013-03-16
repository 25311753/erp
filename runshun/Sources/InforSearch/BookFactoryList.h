//---------------------------------------------------------------------------

#ifndef BookFactoryListH
#define BookFactoryListH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TBookFactoryListForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TListView *lstView;
	TPanel *Panel1;
	TButton *btnExit;
	TButton *btnQuery;
	TButton *btnToExcel;
	TLabel *Label2;
	TEdit *edtBookID;
	TLabel *Label3;
	TEdit *edtDate0;
	TLabel *Label4;
	TEdit *edtDate1;
	TLabel *Label5;
	TEdit *edtAskID;
	TLabel *Label6;
	TComboBox *lstRcpt;
	TLabel *Label7;
	TComboBox *lstStockType;
	TButton *btnDetail;
	TLabel *Label8;
	TComboBox *lstAccept;
	TLabel *Label9;
	TComboBox *lstDepart;
	TLabel *Label10;
	TComboBox *lstCorp;
	TLabel *Label11;
	TComboBox *lstFactory;
	TButton *btnPickFact;
	TButton *btnToAsk;
	void __fastcall btnExitClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall btnQueryClick(TObject *Sender);
	void __fastcall btnToExcelClick(TObject *Sender);
	void __fastcall lstViewSelectItem(TObject *Sender, TListItem *Item,
          bool Selected);
	void __fastcall lstViewClick(TObject *Sender);
	void __fastcall btnDetailClick(TObject *Sender);
	void __fastcall lstViewDblClick(TObject *Sender);
	void __fastcall lstFactoryExit(TObject *Sender);
	void __fastcall btnPickFactClick(TObject *Sender);
	void __fastcall btnToAskClick(TObject *Sender);
private:	// User declarations
	CStringArray m_lstRcptID;
	CStringArray m_lstFactID;
	CStringArray m_lstDepartID;
	CStringArray m_lstCorpID;

	void ResetCtrl();

public:		// User declarations
	__fastcall TBookFactoryListForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TBookFactoryListForm *BookFactoryListForm;
//---------------------------------------------------------------------------
#endif
