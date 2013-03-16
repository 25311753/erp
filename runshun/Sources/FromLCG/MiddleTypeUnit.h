//---------------------------------------------------------------------------

#ifndef MiddleTypeUnitH
#define MiddleTypeUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "BaseFormUnit.h"
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "TypePrtUnit.h"
//---------------------------------------------------------------------------
class TMiddleTypeForm : public TBaseForm
{
__published:	// IDE-managed Components
   TLabel *Label3;
   TComboBox *cbltype;
   TLabel *Label4;
   void __fastcall FormShow(TObject *Sender);
   void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
   void __fastcall btnokClick(TObject *Sender);
   void __fastcall btnrefClick(TObject *Sender);
   void __fastcall btnprintClick(TObject *Sender);
   void __fastcall ListView1Click(TObject *Sender);
   void __fastcall edtnameKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
   void __fastcall cbltypeChange(TObject *Sender);
   void __fastcall edtcodeExit(TObject *Sender);
   void __fastcall FormActivate(TObject *Sender);
private:	// User declarations
   TStringList  *sltype;
   TTypePrtForm *prtform;
   bool  CheckCode();
   void  LocateRow();
public:		// User declarations
   int  rights; 
   __fastcall TMiddleTypeForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMiddleTypeForm *MiddleTypeForm;
//---------------------------------------------------------------------------
#endif
