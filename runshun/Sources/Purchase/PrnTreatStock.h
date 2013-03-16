//---------------------------------------------------------------------------

#ifndef PrnTreatStockH
#define PrnTreatStockH
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
class TPrnTreatStockForm : public TForm
{
__published:	// IDE-managed Components
	TQuickRep *PrnView;
	TQRBand *PageHeaderBand1;
	TQRLabel *QRLabel1;
	TQRBand *DetailBand1;
	TQRShape *QRShape1;
	TQRShape *QRShape2;
	TQRLabel *QRLabel2;
	TQRShape *QRShape3;
	TQRShape *QRShape4;
	TQRShape *QRShape5;
	TQRLabel *QRLabel3;
	TQRShape *QRShape6;
	TQRShape *QRShape7;
	TQRLabel *QRLabel4;
	TQRLabel *QRLabel5;
	TQRShape *QRShape8;
	TQRShape *QRShape9;
	TQRShape *QRShape10;
	TQRLabel *QRLabel6;
	TQRShape *QRShape11;
	TQRShape *QRShape12;
	TQRLabel *QRLabel7;
	TQRShape *QRShape13;
	TQRLabel *QRLabel8;
	TQRSysData *QRSysData1;
	TQRShape *QRShape14;
	TQRLabel *QRLabel9;
	TQRShape *QRShape15;
	TQRLabel *QRLabel10;
	TQRShape *QRShape16;
	TQRLabel *QRLabel11;
	TQRShape *QRShape17;
	TQRShape *QRShape18;
	TQRLabel *QRLabel12;
private:	// User declarations
public:		// User declarations
	__fastcall TPrnTreatStockForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPrnTreatStockForm *PrnTreatStockForm;
//---------------------------------------------------------------------------
#endif
