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
        TMenuItem *MBase;
        TMenuItem *MCust;
        TMenuItem *MFina;
        TMenuItem *IDM_ACCEPT;
        TMenuItem *IDM_DO;
        TMenuItem *IDM_FINANCE;
        TMenuItem *IDM_CALC;
        TMenuItem *N19;
        TMenuItem *IDM_CURRENCY;
        TMenuItem *IDM_TARGETCOUNTRY;
        TMenuItem *IDM_BARGAIN;
        TMenuItem *IDM_EXCHARGE;
        TMenuItem *IDM_ZHENGMIAN;
        TMenuItem *IDM_TRADE;
        TMenuItem *IDM_TRANSPORT;
        TMenuItem *IDM_PACK;
        TMenuItem *IDM_MERCHANDISE;
        TMenuItem *IDM_CLIENT;
        TImage *Image2;
        TTrayIcon *TrayIcon1;
        TImageList *ImageList1;
        TMenuItem *IDM_SHIPAGENT;
        TMenuItem *IDM_OPERCLASSSET;
        TMenuItem *IDM_OPERATOR;
        TMenuItem *IDM_MODPW;
        TMenuItem *IDM_OPERCLASSSET1;
        TMenuItem *IDM_OPERUNIT;
        TMenuItem *IDM_SH;
        TMenuItem *IDM_CHARGE;
        TTimer *timer_keepalive;
   void __fastcall Timer1Timer(TObject *Sender);
   void __fastcall N7Click(TObject *Sender);
   void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
   void __fastcall FormShortCut(TWMKey &Msg, bool &Handled);
   void __fastcall FormShow(TObject *Sender);
   void __fastcall IDM_OPERATORClick(TObject *Sender);
   void __fastcall IDM_MODPWClick(TObject *Sender);
   void __fastcall IDM_CLASSRIGHTClick(TObject *Sender);
   void __fastcall IDM_OPERCLASSSETClick(TObject *Sender);
	void __fastcall IDM_DICSTATUSClick(TObject *Sender);
        void __fastcall IDM_ACCEPTClick(TObject *Sender);
        void __fastcall IDM_DOClick(TObject *Sender);
        void __fastcall IDM_FINANCEClick(TObject *Sender);
        void __fastcall IDM_CALCClick(TObject *Sender);
        void __fastcall N19Click(TObject *Sender);
        void __fastcall IDM_CURRENCYClick(TObject *Sender);
        void __fastcall IDM_TARGETCOUNTRYClick(TObject *Sender);
        void __fastcall IDM_STATUSClick(TObject *Sender);
        void __fastcall IDM_BARGAINClick(TObject *Sender);
        void __fastcall IDM_EXCHARGEClick(TObject *Sender);
        void __fastcall IDM_TRADEClick(TObject *Sender);
        void __fastcall IDM_TRANSPORTClick(TObject *Sender);
        void __fastcall IDM_PACKClick(TObject *Sender);
        void __fastcall IDM_BOATNOClick(TObject *Sender);
        void __fastcall IDM_BOATORDERClick(TObject *Sender);
        void __fastcall IDM_ZHENGMIANClick(TObject *Sender);
        void __fastcall IDM_MERCHANDISEClick(TObject *Sender);
        void __fastcall IDM_CLIENTClick(TObject *Sender);
        void __fastcall IDM_SHIPAGENTClick(TObject *Sender);
        void __fastcall IDM_OPERCLASSSET1Click(TObject *Sender);
        void __fastcall IDM_SHClick(TObject *Sender);
        void __fastcall IDM_OPERUNITClick(TObject *Sender);
        void __fastcall IDM_CHARGEClick(TObject *Sender);
        void __fastcall timer_keepaliveTimer(TObject *Sender);
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
