//---------------------------------------------------------------------------

#ifndef MaterialRemH
#define MaterialRemH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBCtrls.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ValEdit.hpp>
//---------------------------------------------------------------------------
class TF_MaterialRem : public TForm
{
__published:	// IDE-managed Components
        TButton *btnOK;
        TButton *btnExit;
        TLabel *Label1;
        TTreeView *lstTree;
        TMemo *Memo1;
        TButton *btnEdit;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TPanel *Panel1;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label8;
        TLabel *Label9;
        TLabel *Label10;
        TButton *btnPrint123;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TTabSheet *TabSheet2;
        TMemo *Memo2;
        TMemo *Memo3;
        TLabel *Label11;
        TTabSheet *TabSheet3;
        TMemo *Memo4;
        TButton *btnPrint4;
        TPanel *Panel2;
        TLabel *Label12;
        TEdit *edtSearchText;
        TListView *lstSearchView;
        TButton *btnSearch;
        TLabel *Label13;
        TLabel *Label14;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall lstTreeClick(TObject *Sender);
        void __fastcall btnExitClick(TObject *Sender);
        void __fastcall btnOKClick(TObject *Sender);
        void __fastcall btnEditClick(TObject *Sender);
        void __fastcall btnPrint123Click(TObject *Sender);
        void __fastcall btnPrint4Click(TObject *Sender);
        void __fastcall btnSearchClick(TObject *Sender);
        void __fastcall lstSearchViewSelectItem(TObject *Sender,
          TListItem *Item, bool Selected);
private:	// User declarations

	CStringArray m_lstTreeID;
                bool m_bTreeInitialed;
                bool nodeselected;
	enum { EN_STATE_EDIT,EN_STATE_IDLE } m_enState;
        	void ResetCtrl();

public:		// User declarations
        __fastcall TF_MaterialRem(TComponent* Owner);
        int m_nAuthor;

};
//---------------------------------------------------------------------------
extern PACKAGE TF_MaterialRem *F_MaterialRem;
//---------------------------------------------------------------------------
#endif
