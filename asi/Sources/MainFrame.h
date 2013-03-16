//---------------------------------------------------------------------------

#ifndef MainFrameH
#define MainFrameH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
#include "trayicon.h"
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
   TPanel *Panel1;
   TImage *Image1;
   TStatusBar *StatusBar1;
   TTimer *Timer1;
   TMainMenu *MainMenu1;
   TMenuItem *N7;
        TMenuItem *IDM_BASE;
        TImage *Image2;
        TTrayIcon *TrayIcon1;
        TImageList *ImageList1;
        TMenuItem *IDM_OPERCLASSSET;
        TMenuItem *IDM_OPERATOR;
        TMenuItem *IDM_MODPW;
        TMenuItem *IDM_OPERCLASSSET1;
        TMenuItem *IDM_CLIENT;
        TMenuItem *IDM_SUPPLIER;
        TMenuItem *IDM_OPERATION;
        TMenuItem *IDM_FINANCE;
        TMenuItem *IDM_COMMITION;
        TMenuItem *N3;
        TMenuItem *N4;
        TMenuItem *N5;
        TMenuItem *N6;
        TMenuItem *N8;
        TMenuItem *IDM_NEW_CLI_PRIZE;
        TMenuItem *IDM_SALE;
        TMenuItem *IDM_SALE_QRY;
        TMenuItem *IDM_TC;
        TMenuItem *IDM_XK;
        TMenuItem *IDM_YJ;
        TMenuItem *IDM_YJ_CSSZ;
        TMenuItem *IDM_YJ_QRY;
        TMenuItem *IDM_TC_CSSZ;
        TMenuItem *IDM_TC_QRY;
        TMenuItem *IDM_XK_CSSZ;
        TMenuItem *IDM_XK_QRY;
        TMenuItem *IDM_OP_MOD;
        TMenuItem *IDM_OP_QRY;
   void __fastcall Timer1Timer(TObject *Sender);
   void __fastcall N7Click(TObject *Sender);
   void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
   void __fastcall FormShortCut(TWMKey &Msg, bool &Handled);
   void __fastcall FormShow(TObject *Sender);
   void __fastcall IDM_OPERATORClick(TObject *Sender);
   void __fastcall IDM_MODPWClick(TObject *Sender);
   void __fastcall IDM_CLASSRIGHTClick(TObject *Sender);
   void __fastcall IDM_OPERCLASSSETClick(TObject *Sender);

//        void __fastcall N19Click(TObject *Sender);
        void __fastcall IDM_OPERCLASSSET1Click(TObject *Sender);
        void __fastcall IDM_CLIENTClick(TObject *Sender);
        void __fastcall IDM_SUPPLIERClick(TObject *Sender);
        void __fastcall IDM_OPERATIONClick(TObject *Sender);
        void __fastcall N3Click(TObject *Sender);
        void __fastcall IDM_COMMITIONClick(TObject *Sender);
        void __fastcall N4Click(TObject *Sender);
        void __fastcall N6Click(TObject *Sender);
        void __fastcall N8Click(TObject *Sender);
        void __fastcall IDM_NEW_CLI_PRIZEClick(TObject *Sender);
        void __fastcall IDM_SALE_QRYClick(TObject *Sender);
        void __fastcall IDM_YJ_QRYClick(TObject *Sender);
        void __fastcall IDM_TC_QRYClick(TObject *Sender);
        void __fastcall IDM_XK_QRYClick(TObject *Sender);
        void __fastcall IDM_OP_QRYClick(TObject *Sender);
        void __fastcall IDM_XK_CSSZClick(TObject *Sender);
        void __fastcall IDM_TC_CSSZClick(TObject *Sender);
        void __fastcall IDM_YJ_CSSZClick(TObject *Sender);
private:	// User declarations
	void ResetMenu(TMenuItem *pMenu);

   void __fastcall GetTime();
  
public:		// User declarations
   void __fastcall SetModule();
   __fastcall TMainForm(TComponent* Owner);
//        void   __fastcall   WndProc(TMessage&   Message);

};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
