//---------------------------------------------------------------------------

#ifndef SumEffectH
#define SumEffectH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "LfcArray_s.h"
//---------------------------------------------------------------------------
class TSumEffectForm : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TListView *lstView;
        TPanel *Panel1;
        TLabel *Label2;
        TComboBox *lstHandle;
        TLabel *Label3;
        TLabel *Label4;
        TComboBox *lstCorp;
        TLabel *Label5;
        TComboBox *lstType;
        TLabel *Label6;
        TLabel *Label7;
        TDateTimePicker *DateTimePicker1;
        TDateTimePicker *DateTimePicker2;
        TButton *btnQuery;
        TButton *btntoExcel;
        TButton *btnQuit;
        TComboBox *lstStockDepart;
        TRadioButton *RadioButton1;
        TRadioButton *RadioButton2;
        TRadioButton *RadioButton3;
        TRadioButton *RadioButton4;
        TLabel *Label8;
        TLabel *Label9;
        TEdit *edtSNum;
        TEdit *edtSPrice;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall btnQuitClick(TObject *Sender);
        void __fastcall btntoExcelClick(TObject *Sender);
        void __fastcall btnQueryClick(TObject *Sender);
        void __fastcall RadioButton2Click(TObject *Sender);
        void __fastcall RadioButton1Click(TObject *Sender);
        void __fastcall DateTimePicker1Change(TObject *Sender);
        void __fastcall RadioButton3Click(TObject *Sender);
        void __fastcall RadioButton4Click(TObject *Sender);
private:	// User declarations
	CStringArray m_lstTypeID;
	CStringArray m_lstCorpID;
	CStringArray m_lstHandleID;
	CStringArray m_lstStockDepartID;
public:		// User declarations
        __fastcall TSumEffectForm(TComponent* Owner);
        bool m_sType;
};
//---------------------------------------------------------------------------
extern PACKAGE TSumEffectForm *SumEffectForm;
//---------------------------------------------------------------------------
#endif
