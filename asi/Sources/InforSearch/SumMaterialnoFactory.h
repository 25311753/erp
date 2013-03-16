//---------------------------------------------------------------------------

#ifndef SumMaterialnoFactoryH
#define SumMaterialnoFactoryH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Chart.hpp>
#include <DbChart.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <Series.hpp>
#include <TeeFunci.hpp>
//---------------------------------------------------------------------------
class TSumMnFactForm : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TPanel *Panel1;
        TButton *btnQuery;
        TButton *btntoExcel;
        TButton *btnQuit;
        TDateTimePicker *DateTimePicker1;
        TDateTimePicker *DateTimePicker2;
        TLabel *Label2;
        TLabel *Label3;
        TEdit *edtMater;
        TEdit *edtMnname;
        TLabel *Label4;
        TLabel *Label5;
        TButton *btnQueryMT;
        TLabel *Label6;
        TButton *btnSpeerFactSearch;
        TComboBox *lstSpeerFact;
        TGroupBox *GroupBox1;
        TLabel *Label7;
        TLabel *Label8;
        TEdit *edtSN;
        TEdit *edtSP;
        TLabel *Label9;
        TLabel *Label10;
        TEdit *edtStanderN;
        TEdit *edtStanderP;
        TListView *lstView1;
        TButton *btnRQuery;
        TRadioGroup *RadioGroup1;
        TRadioGroup *RadioGroup2;
        TRadioGroup *RadioGroup3;
        TProgressBar *ProgressBar1;
        TComboBox *lstStockDepart;
        TLabel *Label11;
        void __fastcall btnQueryMTClick(TObject *Sender);
        void __fastcall btnQuitClick(TObject *Sender);
        void __fastcall btnSpeerFactSearchClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall btnQueryClick(TObject *Sender);
        void __fastcall btnRQueryClick(TObject *Sender);
        void __fastcall RadioGroup1Click(TObject *Sender);
        void __fastcall RadioGroup2Click(TObject *Sender);
        void __fastcall btntoExcelClick(TObject *Sender);
        void __fastcall RadioGroup3Click(TObject *Sender);
        void __fastcall lstView1SelectItem(TObject *Sender,
          TListItem *Item, bool Selected);
        void __fastcall edtMaterExit(TObject *Sender);
private:	// User declarations
	CStringArray m_lstSpeerFactID;
	CStringArray m_lstStockDepartID;        
        void SetDefault();
        void EnableEdit();
        void EnableEditR();
        void DisableEdit();
public:		// User declarations
        __fastcall TSumMnFactForm(TComponent* Owner);
       	int m_nAuthor;
	AnsiString m_szMaterCode;
        bool IsNewCode,MnAnly,NorAnly;


};
//---------------------------------------------------------------------------
extern PACKAGE TSumMnFactForm *SumMnFactForm;
//---------------------------------------------------------------------------
#endif
