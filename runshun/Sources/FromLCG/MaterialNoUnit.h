//---------------------------------------------------------------------------

#ifndef MaterialNoUnitH
#define MaterialNoUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "MaterialPrtUnit.h"
//---------------------------------------------------------------------------
class TMaterialNoForm : public TForm
{
__published:	// IDE-managed Components
   TPanel *Panel1;
   TPanel *Panel2;
   TLabel *Label1;
   TLabel *Label2;
   TLabel *Label3;
   TLabel *Label4;
   TLabel *Label5;
   TShape *Shape1;
   TEdit *edtcode;
   TEdit *edtname;
   TListView *ListView1;
   TComboBox *cbltype;
   TComboBox *cbmtype;
   TEdit *edtscode;
   TEdit *edtlcode;
   TEdit *edtmcode;
   TPanel *Panel3;
   TBitBtn *btnadd;
   TBitBtn *btnmod;
   TBitBtn *btndel;
   TBitBtn *btnok;
   TBitBtn *btncan;
   TBitBtn *btnprint;
   TBitBtn *btnref;
   TBitBtn *btnexit;
   TPanel *PanelHint;
   TEdit *edtstype;
   TComboBox *cbstype;
   TEdit *edtcorp;
   TLabel *Label6;
   TBitBtn *btnclear;
   TBitBtn *btnfind;
   TLabel *Label7;
   TEdit *edtusage;
   void __fastcall FormShow(TObject *Sender);
   void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
   void __fastcall btnaddClick(TObject *Sender);
   void __fastcall btnmodClick(TObject *Sender);
   void __fastcall btnokClick(TObject *Sender);
   void __fastcall btndelClick(TObject *Sender);
   void __fastcall btnprintClick(TObject *Sender);
   void __fastcall ListView1Click(TObject *Sender);
   void __fastcall cbltypeChange(TObject *Sender);
   void __fastcall cbmtypeChange(TObject *Sender);
   void __fastcall btncanClick(TObject *Sender);
   void __fastcall btnexitClick(TObject *Sender);
   void __fastcall FormShortCut(TWMKey &Msg, bool &Handled);
   void __fastcall btnclearClick(TObject *Sender);
   void __fastcall edtlcodeKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
   void __fastcall edtmcodeKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
   void __fastcall edtstypeKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
   void __fastcall cbstypeChange(TObject *Sender);
   void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
   void __fastcall btnrefClick(TObject *Sender);
   void __fastcall edtscodeExit(TObject *Sender);
   void __fastcall btnfindClick(TObject *Sender);
   void __fastcall edtusageKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
   TStringList  *sltype;
   TStringList  *smtype;
   TStringList  *sstype;
   TMaterialPrtForm *prtform;
   AnsiString  strsql,info;
   char  btnidx;//0-btnadd,1-btnref,2-btnmod,3-btndel,4-btnok,5-btncan,
   bool  CheckEdit();
   bool  CheckCode();
   void  LocateRow(AnsiString str);
   void  ClearEdit();
   void  SetButton(bool v0, bool v1, bool v2, bool v3, bool v4, bool v5, bool v6);
   void  SetEdits(bool v0,bool v1,bool v2,bool v3,bool v4,bool v5,bool v6,bool v7,bool v8,bool v9);
   void  SetDefault();
   bool  GetMiddleType();
   bool  GetSmallType();
   int   DoSelect(bool closeds, bool addtolv);
public:		// User declarations
   __fastcall TMaterialNoForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMaterialNoForm *MaterialNoForm;
//---------------------------------------------------------------------------
#endif
