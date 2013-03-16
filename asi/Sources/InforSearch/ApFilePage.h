//---------------------------------------------------------------------------

#ifndef ApFilePageH
#define ApFilePageH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TApFilePageForm : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TButton *btnQuery;
        TButton *btnNew;
        TButton *btnEdit;
        TButton *btnMove;
        TButton *btnOK;
        TButton *btnExit;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TEdit *edtAPC;
        TEdit *edtFC;
        TEdit *edtPC;
        TButton *btnAPQuery;
        TLabel *Label5;
        TLabel *Label6;
        TComboBox *lstRem;

       	void __fastcall FormShow(TObject *Sender);
        void __fastcall btnNewClick(TObject *Sender);
        void __fastcall btnEditClick(TObject *Sender);
        void __fastcall btnMoveClick(TObject *Sender);
        void __fastcall btnExitClick(TObject *Sender);
        void __fastcall btnQueryClick(TObject *Sender);
        void __fastcall btnOKClick(TObject *Sender);
        void __fastcall btnAPQueryClick(TObject *Sender);

private:	// User declarations
       	AnsiString GenerateID();

public:		// User declarations
        __fastcall TApFilePageForm(TComponent* Owner);
       	enum { EN_STATE_NEW,EN_STATE_EDIT,EN_STATE_IDLE } m_enState;

       	int m_nAuthor;
	CStringArray m_lstRemID;        

       	CString m_szActiveID;
	CStringArray m_lstReDepID;

       	void ResetCtrl();
};
//---------------------------------------------------------------------------
extern PACKAGE TApFilePageForm *ApFilePageForm;
//---------------------------------------------------------------------------
#endif
