//---------------------------------------------------------------------------

#ifndef BaseFormUnitH
#define BaseFormUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TBaseForm : public TForm
{
__published:	// IDE-managed Components
   TPanel *Panel1;
   TPanel *Panel2;
   TPanel *Panel3;
   TLabel *Label1;
   TEdit *edtcode;
   TLabel *Label2;
   TEdit *edtname;
   TListView *ListView1;
   TBitBtn *btnadd;
   TBitBtn *btnfind;
   TBitBtn *btnmod;
   TBitBtn *btndel;
   TBitBtn *btnok;
   TBitBtn *btncan;
   TBitBtn *btnprint;
   TBitBtn *btnref;
   TBitBtn *btnexit;
   TPanel *PanelHint;
   void __fastcall FormShortCut(TWMKey &Msg, bool &Handled);
   void __fastcall btnaddClick(TObject *Sender);
   void __fastcall btnmodClick(TObject *Sender);
   void __fastcall btndelClick(TObject *Sender);
   void __fastcall btncanClick(TObject *Sender);
   void __fastcall btnexitClick(TObject *Sender);
   void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
   void __fastcall btnfindClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
   AnsiString  strsql;
   char  btnidx;//0-btnadd,1-btnfind,2-btnmod,3-btndel,4-btnok,5-btncan
   virtual bool  CheckEdit();    //ºÏ≤È «∑Ò ‰»Î
   virtual void  ClearEdit();
   virtual void  SetDefault();
   virtual void  LocateRow()=0;
   void  SetButton(bool v0, bool v1, bool v2, bool v3, bool v4, bool v5, bool v6, bool v7);
   __fastcall TBaseForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TBaseForm *BaseForm;
//---------------------------------------------------------------------------
#endif
