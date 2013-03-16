//---------------------------------------------------------------------------

#ifndef operatorunitH
#define operatorunitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <DBCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Mask.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class Toperatorform : public TForm
{
__published:	// IDE-managed Components
   TDBEdit *dbedoptcode;
   TDBEdit *dbedoptname;
   TComboBox *cmbclass;
   TEdit *confirmpass;
   TEdit *dbedpassword;
   TBitBtn *btnadd;
   TBitBtn *btnedit;
   TBitBtn *btndelete;
   TBitBtn *btnsave;
   TBitBtn *btncancel;
   TBitBtn *btnclose;
   TBitBtn *btnfirst;
   TBitBtn *btnprior;
   TBitBtn *btnnext;
   TBitBtn *btnlast;
   TBitBtn *btnquery;
   TDBEdit *dbepwd;
   TDBEdit *dbecorp;
        TPanel *Panel1;
        TPanel *Panel5;
        TPanel *Panel6;
        TPanel *Panel7;
        TPanel *Panel8;
        TImage *Image1;
        TBevel *Bevel1;
        TBevel *Bevel2;
   void __fastcall btnaddClick(TObject *Sender);
   void __fastcall btneditClick(TObject *Sender);
   void __fastcall btndeleteClick(TObject *Sender);
   void __fastcall btnsaveClick(TObject *Sender);
   void __fastcall btncancelClick(TObject *Sender);
   void __fastcall btnfirstClick(TObject *Sender);
   void __fastcall btnpriorClick(TObject *Sender);
   void __fastcall btnnextClick(TObject *Sender);
   void __fastcall btnlastClick(TObject *Sender);
   void __fastcall btnqueryClick(TObject *Sender);
   void __fastcall FormShow(TObject *Sender);
   void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
   void __fastcall dbedoptnameKeyPress(TObject *Sender, char &Key);
   void __fastcall dbedoptcodeKeyPress(TObject *Sender, char &Key);
   void __fastcall dbedpasswordKeyPress(TObject *Sender, char &Key);
   void __fastcall confirmpassKeyPress(TObject *Sender, char &Key);
   void __fastcall cmbclassKeyPress(TObject *Sender, char &Key);
private:	// User declarations
   void  SetDBedit(bool btnvalue);
   void  SetButton(bool btnstate);
   AnsiString  DecodePwd();
   TStringList *sclass;
   int   rank;
public:		// User declarations
   __fastcall Toperatorform(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Toperatorform *operatorform;
//---------------------------------------------------------------------------
#endif
