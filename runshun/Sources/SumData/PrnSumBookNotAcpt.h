//---------------------------------------------------------------------------

#ifndef PrnSumNotEndH
#define PrnSumNotEndH
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
class TPrnSumBookNotAcptForm : public TForm
{
__published:	// IDE-managed Components
	TQuickRep *PrnView;
	TQRBand *PageHeaderBand1;
	TQRLabel *txtTitle;
	TQRShape *QRShape1;
	TQRShape *QRShape2;
	TQRLabel *txtDate;
	TQRLabel *QRLabel5;
	TQRShape *QRShape5;
	TQRLabel *QRLabel6;
	TQRShape *QRShape6;
	TQRLabel *QRLabel7;
	TQRShape *QRShape7;
	TQRLabel *QRLabel8;
	TQRShape *QRShape8;
	TQRLabel *QRLabel9;
	TQRShape *QRShape9;
	TQRLabel *QRLabel10;
	TQRShape *QRShape10;
	TQRLabel *QRLabel11;
	TQRShape *QRShape11;
	TQRLabel *QRLabel12;
	TQRLabel *QRLabel13;
	TQRLabel *txtPrnTime;
	TQRBand *DetailBand1;
	TQRShape *QRShape12;
	TQRShape *QRShape13;
	TQRShape *QRShape16;
	TQRShape *QRShape17;
	TQRShape *QRShape18;
	TQRShape *QRShape19;
	TQRShape *QRShape20;
	TQRShape *QRShape21;
	TQRShape *QRShape22;
	TQRDBText *QRDBText1;
	TQRDBText *QRDBText2;
	TQRDBText *QRDBText4;
	TQRDBText *QRDBText5;
	TQRDBText *QRDBText6;
	TQRDBText *QRDBText7;
	TQRDBText *QRDBText8;
	TQRDBText *QRDBText9;
	TQRDBText *QRDBText10;
	TQRLabel *QRLabel2;
	TQRShape *QRShape23;
	TQRDBText *QRDBText3;
	TQRShape *QRShape24;
	TQRLabel *QRLabel3;
	TQRShape *QRShape3;
	TQRLabel *QRLabel4;
	TQRDBText *QRDBText11;
	TQRShape *QRShape4;
	TQRLabel *QRLabel14;
	TQRShape *QRShape14;
	TQRShape *QRShape15;
        TQRShape *QRShape25;
        TQRLabel *QRLabel1;
        TQRShape *QRShape26;
        TQRDBText *QRDBText12;
        TQRLabel *QRLabel15;
        TQRLabel *QRLabel16;
        TQRLabel *QRLabel17;
        TQRLabel *QRLabel18;
private:	// User declarations
public:		// User declarations
	__fastcall TPrnSumBookNotAcptForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPrnSumBookNotAcptForm *PrnSumBookNotAcptForm;
//---------------------------------------------------------------------------
#endif
