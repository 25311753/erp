//---------------------------------------------------------------------------

#ifndef SmallTypeUnitH
#define SmallTypeUnitH
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
class TSmallTypeForm : public TBaseForm
{
__published:	// IDE-managed Components
   TLabel *Label4;
   TLabel *Label3;
   TComboBox *cbmtype;
   void __fastcall FormShow(TObject *Sender);
   void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
   void __fastcall btnokClick(TObject *Sender);
   void __fastcall btnrefClick(TObject *Sender);
   void __fastcall btnprintClick(TObject *Sender);
   void __fastcall ListView1Click(TObject *Sender);
   void __fastcall edtnameKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
   void __fastcall cbmtypeChange(TObject *Sender);
   void __fastcall edtcodeExit(TObject *Sender);
   void __fastcall btncanClick(TObject *Sender);
   void __fastcall FormActivate(TObject *Sender);
private:	// User declarations
   TStringList  *smtype;
   TTypePrtForm *prtform;
   bool  CheckCode();
   void  LocateRow();
public:		// User declarations
   int  rights; 
   __fastcall TSmallTypeForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSmallTypeForm *SmallTypeForm;
//---------------------------------------------------------------------------
#endif
