//---------------------------------------------------------------------------

#ifndef PrnPurchaseAfmListH
#define PrnPurchaseAfmListH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <QuickRpt.hpp>
#include <Qrctrls.hpp>
#include <QRCtrls.hpp>
//---------------------------------------------------------------------------
class TPrnPurchaseAfmListForm : public TForm
{
__published:	// IDE-managed Components
	TQuickRep *PrnView;
	TQRBand *PageHeaderBand1;
	TQRLabel *QRLabel1;
	TQRSysData *QRSysData1;
	TQRLabel *QRLabel2;
	TQRBand *DetailBand1;
	TQRShape *QRShape1;
	TQRLabel *QRLabel3;
	TQRShape *QRShape2;
	TQRLabel *QRLabel4;
	TQRShape *QRShape3;
	TQRLabel *QRLabel5;
	TQRShape *QRShape4;
	TQRLabel *QRLabel6;
	TQRShape *QRShape5;
	TQRLabel *QRLabel7;
	TQRShape *QRShape6;
	TQRLabel *QRLabel8;
	TQRShape *QRShape7;
	TQRLabel *QRLabel9;
	TQRShape *QRShape8;
	TQRLabel *QRLabel10;
	TQRShape *QRShape9;
	TQRLabel *QRLabel11;
	TQRShape *QRShape10;
	TQRShape *QRShape11;
	TQRShape *QRShape12;
	TQRShape *QRShape13;
	TQRShape *QRShape14;
	TQRShape *QRShape15;
	TQRShape *QRShape16;
	TQRShape *QRShape17;
	TQRShape *QRShape18;
	TQRDBText *QRDBText1;
	TQRDBText *QRDBText2;
	TQRDBText *QRDBText3;
	TQRDBText *QRDBText4;
	TQRShape *QRShape19;
	TQRLabel *QRLabel12;
	TQRShape *QRShape21;
	TQRDBText *QRDBText5;
	TQRDBText *QRDBText6;
	TQRDBText *QRDBText7;
	TQRShape *QRShape22;
	TQRShape *QRShape25;
	TQRLabel *QRLabel13;
	TQRDBText *QRDBText8;
	TQRDBText *QRDBText9;
	TQRDBText *QRDBText10;
	TQRDBText *QRDBText11;
        TQRLabel *QRLabel14;
        TQRLabel *QRLabel15;
private:	// User declarations
public:		// User declarations
	__fastcall TPrnPurchaseAfmListForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPrnPurchaseAfmListForm *PrnPurchaseAfmListForm;
//---------------------------------------------------------------------------
#endif
