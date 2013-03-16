//---------------------------------------------------------------------------

#ifndef SpeerMultiPrnH
#define SpeerMultiPrnH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TSpeerMultiPrnForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TLabel *Label3;
	TComboBox *lstHandle;
	TLabel *Label4;
	TLabel *Label5;
	TListView *lstView;
	TButton *btnExit;
	TButton *btnPrint;
	TButton *btnQuery;
	TLabel *Label6;
	TEdit *edtEndDate;
	TDateTimePicker *ctlDate0;
	TDateTimePicker *ctlDate1;
	TCheckBox *chkShowQuoted;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall btnQueryClick(TObject *Sender);
	void __fastcall btnExitClick(TObject *Sender);
	void __fastcall btnPrintClick(TObject *Sender);
private:	// User declarations
//	CStringArray m_lstCorpID;
	CArray<BASE2COLDATA,BASE2COLDATA>m_lstCorp;
	CStringArray m_lstHandleID;
	CString m_szHandleID;

public:		// User declarations
	__fastcall TSpeerMultiPrnForm(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TSpeerMultiPrnForm *SpeerMultiPrnForm;
//---------------------------------------------------------------------------
#endif
