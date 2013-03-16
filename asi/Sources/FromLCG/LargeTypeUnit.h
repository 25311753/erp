//---------------------------------------------------------------------------

#ifndef LargeTypeUnitH
#define LargeTypeUnitH
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
class TLargeTypeForm : public TBaseForm
{
__published:	// IDE-managed Components
   void __fastcall FormShow(TObject *Sender);
   void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
   void __fastcall btnokClick(TObject *Sender);
   void __fastcall btnrefClick(TObject *Sender);
   void __fastcall btnprintClick(TObject *Sender);
   void __fastcall ListView1Click(TObject *Sender);
   void __fastcall edtnameKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
   TTypePrtForm *prtform;
   void  LocateRow();
public:		// User declarations
   int  rights; 
   __fastcall TLargeTypeForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLargeTypeForm *LargeTypeForm;
//---------------------------------------------------------------------------
#endif
