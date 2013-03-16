//---------------------------------------------------------------------------

#ifndef InputCorpUnitH
#define InputCorpUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "BaseFormUnit.h"
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "TypePrt2Unit.h"
//---------------------------------------------------------------------------
class TInputCorpForm : public TBaseForm
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
   void  LocateRow();
   TTypePrt2Form *prtform;
public:		// User declarations
   __fastcall TInputCorpForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TInputCorpForm *InputCorpForm;
//---------------------------------------------------------------------------
#endif
