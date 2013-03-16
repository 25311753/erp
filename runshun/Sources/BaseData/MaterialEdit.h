//---------------------------------------------------------------------------

#ifndef MaterialEditH
#define MaterialEditH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TMaterialEditForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label5;
	TEdit *edtCorp;
	TEdit *edtID0;
	TPanel *Panel1;
	TEdit *edtID1;
	TLabel *Label6;
	TEdit *edtSpec;
	TLabel *Label1;
	TComboBox *lstCorp;
	TLabel *Label2;
	TComboBox *lstLarge;
	TLabel *Label3;
	TComboBox *lstMid;
	TLabel *Label4;
	TComboBox *lstMin;
	TListView *lstView;
	TLabel *Label7;
	TEdit *edtUsage;
	TLabel *Label8;
	TMemo *Memo1;
	TButton *btnNew;
	TButton *btnEdit;
	TButton *btnMov;
	TButton *btnOK;
	TButton *btnExit;
        TLabel *Label9;
        TEdit *edtDATE;
        TButton *btndq;
        TTimer *Timer1;
        TEdit *edtCorpNew;
        TEdit *edtID0New;
        TPanel *Panel2;
        TEdit *edtID1New;
        TButton *btnNO;
        TLabel *Label10;
        TComboBox *lstUnits;
        TDateTimePicker *DateTimePicker1;
        TDateTimePicker *DateTimePicker2;
        TRadioButton *RB1;
        TRadioButton *RB2;
        TButton *Button1;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall lstCorpClick(TObject *Sender);
	void __fastcall lstLargeClick(TObject *Sender);
	void __fastcall edtCorpChange(TObject *Sender);
	void __fastcall lstMidClick(TObject *Sender);
	void __fastcall lstMinClick(TObject *Sender);
	void __fastcall edtID0Change(TObject *Sender);
	void __fastcall edtID1Change(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
	void __fastcall lstViewSelectItem(TObject *Sender, TListItem *Item,
          bool Selected);
	void __fastcall btnExitClick(TObject *Sender);
	void __fastcall btnNewClick(TObject *Sender);
	void __fastcall btnEditClick(TObject *Sender);
	void __fastcall btnOKClick(TObject *Sender);
	void __fastcall FormKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall btnMovClick(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall btndqClick(TObject *Sender);
        void __fastcall edtID1NewChange(TObject *Sender);
        void __fastcall btnNOClick(TObject *Sender);
        void __fastcall btnQueryBatClick(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TMaterialEditForm(TComponent* Owner);

	CStringArray m_lstCorpID;
	CStringArray m_lstLargID;
	CStringArray m_lstMidID;
	CStringArray m_lstMinID;
	CStringArray m_lstTreeCorpID;
        CStringArray m_lstUnitsID;

	int m_nAuthor;

	char	m_cCurCorp;
	char	m_cCurLarge;
	CString m_szCurMid;
	CString m_szCurMin;
	TTreeNode *m_pNode;

	CStringArray m_lstTreeID;

  bool m_bTreeInitialed;

	enum { EN_CLICK_NONE,EN_CLICK_CORP,EN_CLICK_LARGE,EN_CLICK_MID,EN_CLICK_MIN,EN_CLICK_VIEW,EN_CLICK_INIT } m_enClick;
	enum { EN_STATE_IDLE,EN_STATE_NEW,EN_STATE_EDIT,EN_STATE_DATE,EN_STATE_QUERY} m_enState;

	void ResetAllUI();
	void ResetCorp();
	void ResetMiddle();
	void ResetMin();
	void ResetView();

	void ResetCtrl();
	AnsiString m_szCorp;
	AnsiString m_szID0;
	AnsiString m_szID1;

};
//---------------------------------------------------------------------------
extern PACKAGE TMaterialEditForm *MaterialEditForm;
//---------------------------------------------------------------------------
#endif
