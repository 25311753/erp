//---------------------------------------------------------------------------

#ifndef calsssetunitH
#define calsssetunitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class Tclasssetform : public TForm
{
__published:	// IDE-managed Components
   TPanel *Panel1;
   TPanel *Panel2;
   TBitBtn *btnclose;
   TBitBtn *btnmodify;
   TPanel *Panel3;
   TLabel *Label1;
   TEdit *edtclass;
   TListBox *lbclass;
   TBitBtn *btnadd;
   TBitBtn *btndelete;
   void __fastcall btnmodifyClick(TObject *Sender);
   void __fastcall btnaddClick(TObject *Sender);
   void __fastcall FormShow(TObject *Sender);
   void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
   void __fastcall btndeleteClick(TObject *Sender);
   void __fastcall lbclassClick(TObject *Sender);
private:	// User declarations
   TStringList *sclass;
   void   DoSelect();
   bool   FindRank();
public:		// User declarations
   __fastcall Tclasssetform(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tclasssetform *classsetform;
//---------------------------------------------------------------------------
#endif
