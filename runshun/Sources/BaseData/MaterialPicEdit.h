//---------------------------------------------------------------------------

#ifndef MaterialPicEditH
#define MaterialPicEditH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DBCtrls.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
//---------------------------------------------------------------------------
class TMnPictureForm : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TDBGrid *DBGrid1;
        TDataSource *DSMnPic;
        TADOConnection *ADOC1;
        TADOTable *ADOT1;
        TOpenPictureDialog *PicDlg;
        TButton *btnOpenDB;
        TButton *btnExit;
        TButton *btnQueryMT;
        TEdit *edtMater;
        TLabel *Label2;
        TEdit *edtMnname;
        TLabel *Label3;
        TButton *btnOK;
        TButton *btnQuery;
        TGroupBox *GroupBox2;
        TDBImage *DBImage1;
        TButton *btnNew;
        TDBNavigator *DBNgt;
        TLabel *Label1;
        TADOQuery *ADOQ1;
        TGroupBox *GroupBox3;
        TButton *btnOpenPic;
        TButton *btnSaveP;
        TImage *Image1;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall btnExitClick(TObject *Sender);
        void __fastcall btnOpenDBClick(TObject *Sender);
        void __fastcall btnCloseDBClick(TObject *Sender);
        void __fastcall ADOT1BeforePost(TDataSet *DataSet);
        void __fastcall btnQueryMTClick(TObject *Sender);
        void __fastcall btnOKClick(TObject *Sender);
        void __fastcall btnQueryClick(TObject *Sender);
        void __fastcall btnNewClick(TObject *Sender);
        void __fastcall btnEditClick(TObject *Sender);
        void __fastcall btnMoveClick(TObject *Sender);
//        void __fastcall btnOpenPicClick(TObject *Sender);
//        void __fastcall btnSavePClick(TObject *Sender);
private:	// User declarations
	enum { EN_STATE_NEW,EN_STATE_EDIT,EN_STATE_IDLE,EN_STATE_QUERY,EN_STATE_Move }m_enState;
	void ResetCtrl();
public:		// User declarations
	int m_nAuthor;
	CString m_szActiveID;
        __fastcall TMnPictureForm(TComponent* Owner);
        String openname,extension;
};
//---------------------------------------------------------------------------
extern PACKAGE TMnPictureForm *MnPictureForm;
//---------------------------------------------------------------------------
#endif
