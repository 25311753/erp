//---------------------------------------------------------------------------

#ifndef PrnSpeerFactoryH
#define PrnSpeerFactoryH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Qrctrls.hpp>
#include <QuickRpt.hpp>
#include <QRCtrls.hpp>
//---------------------------------------------------------------------------
class TPrnSpeerFactoryForm : public TForm
{
__published:	// IDE-managed Components
	TQuickRep *PrnView;
	TQRBand *PageHeaderBand1;
	TQRLabel *QRLabel1;
	TQRSubDetail *QRSubDetail1;
	TQRShape *QRShape11;
	TQRDBText *pd_code;
	TQRShape *QRShape12;
	TQRShape *QRShape13;
	TQRDBText *QRDBText5;
	TQRDBText *QRDBText6;
	TQRShape *QRShape14;
	TQRShape *QRShape15;
	TQRShape *QRShape16;
	TQRShape *QRShape17;
	TQRBand *PageFooterBand1;
	TQRShape *QRShape18;
	TQRShape *QRShape19;
	TQRLabel *QRLabel15;
	TQRLabel *QRLabel16;
	TQRLabel *QRLabel17;
	TQRLabel *QRLabel20;
	TQRLabel *QRLabel21;
	TQRLabel *QRLabel22;
	TQRLabel *QRLabel24;
	TQRLabel *QRLabel25;
	TQRLabel *txtSDTel;
	TQRLabel *txtSHName;
	TQRLabel *txtSHTel;
	TQRLabel *QRLabel27;
	TQRLabel *QRLabel28;
	TQRLabel *QRLabel29;
	TQRLabel *QRLabel30;
	TQRLabel *QRLabel31;
	TQRLabel *QRLabel32;
	TQRLabel *QRLabel33;
	TQRLabel *QRLabel34;
	TQRLabel *QRLabel35;
	TQRLabel *PrnDate;
	TQRLabel *EndDate;
	TQRLabel *txtSDAddr;
	TQRLabel *QRLabel18;
	TQRShape *QRShape21;
	TQRLabel *txtName1;
	TQRLabel *txtName0;
	TQRLabel *txtSpeerTax;
        TQRLabel *QRLabel23;
        TQRDBText *QRDBText1;
        TQRLabel *QRLabel39;
        TQRDBText *QRDBText8;
        TQRLabel *QRLabel40;
        TQRLabel *QRLabel41;
        TQRDBText *QRDBText9;
        TQRLabel *QRLabel42;
        TQRDBText *QRDBText10;
        TQRDBText *QRDBText2;
        TQRLabel *QRLabel43;
        TQRShape *QRShape22;
        TQRShape *QRShape23;
        TQRShape *QRShape24;
        TQRShape *QRShape25;
        TQRShape *QRShape26;
        TQRShape *QRShape27;
        TQRShape *QRShape28;
        TQRShape *QRShape29;
        TQRShape *QRShape30;
        TQRShape *QRShape31;
        TQRShape *QRShape32;
        TQRLabel *QRLabel44;
        TQRLabel *QRLabel45;
        TQRLabel *QRLabel46;
        TQRLabel *QRLabel47;
        TQRLabel *QRLabel48;
        TQRLabel *QRLabel49;
        TQRLabel *QRLabel50;
        TQRLabel *QRLabel51;
        TQRLabel *QRLabel52;
        TQRLabel *QRLabel53;
        TQRLabel *QRLabel54;
	void __fastcall pd_codePrint(TObject *sender, AnsiString &Value);
	void __fastcall QRSubDetail1BeforePrint(TQRCustomBand *Sender,
          bool &PrintBand);
private:	// User declarations
public:		// User declarations
	__fastcall TPrnSpeerFactoryForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPrnSpeerFactoryForm *PrnSpeerFactoryForm;
//---------------------------------------------------------------------------
#endif
