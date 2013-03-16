//---------------------------------------------------------------------------

#ifndef operpwdunitH
#define operpwdunitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class Toperpwdform : public TForm
{
__published:	// IDE-managed Components
   TBitBtn *Bok;
   TBitBtn *Bexit;
   TBitBtn *Bmodify;
   TEdit *oldpwd;
   TEdit *newpwd1;
   TEdit *newpwd2;
   TEdit *eoper;
        TImage *Image1;
        TPanel *Panel1;
        TPanel *Panel5;
        TPanel *Panel6;
        TPanel *Panel7;
        TBevel *Bevel1;
   void __fastcall FormShow(TObject *Sender);
   void __fastcall oldpwdKeyPress(TObject *Sender, char &Key);
   void __fastcall newpwd1KeyPress(TObject *Sender, char &Key);
   void __fastcall newpwd2KeyPress(TObject *Sender, char &Key);
   void __fastcall BokClick(TObject *Sender);
   void __fastcall BmodifyClick(TObject *Sender);
   void __fastcall BexitClick(TObject *Sender);
   void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
   __fastcall Toperpwdform(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Toperpwdform *operpwdform;
//---------------------------------------------------------------------------
#endif
