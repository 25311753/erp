//---------------------------------------------------------------------------

#ifndef PrnInvoiceH
#define PrnInvoiceH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <QRCtrls.hpp>
#include <QuickRpt.hpp>
//---------------------------------------------------------------------------
class TPrnInvoiceForm : public TForm
{
__published:	// IDE-managed Components
        TQuickRep *PrnView;
        TQRBand *TitleBand1;
        TQRBand *DetailBand1;
        TQRBand *PageHeaderBand1;
        TQRLabel *QRLabel1;
        TQRLabel *QRLabel2;
        TQRLabel *QRLabel3;
        TQRLabel *QRLabel4;
        TQRLabel *QRLabel5;
        TQRLabel *QRLabel6;
        TQRLabel *QRLabel7;
        TQRLabel *QRLabel8;
        TQRLabel *QRLabel9;
        TQRLabel *QRLabel10;
        TQRLabel *QRLabel11;
        TQRLabel *QRLabel12;
        TQRShape *QRShape1;
        TQRShape *QRShape2;
        TQRShape *QRShape3;
        TQRShape *QRShape4;
        TQRShape *QRShape5;
        TQRLabel *QRLabel13;
        TQRLabel *QRLabel14;
        TQRLabel *QRLabel15;
        TQRLabel *QRLabel16;
        TQRLabel *QRLabel17;
        TQRLabel *QRLabel18;
        TQRLabel *QRLabel19;
        TQRLabel *QRLabel20;
        TQRLabel *QRLabel21;
        TQRLabel *QRLabel22;
        TQRShape *QRShape10;
        TQRShape *QRShape11;
        TQRShape *QRShape12;
        TQRShape *QRShape13;
        TQRDBText *qrdbtMid;
        TQRDBText *qrdbtMname;
        TQRDBText *qrdbtCount;
        TQRDBText *qrdbtUnitPrice;
        TQRDBText *qrdbtTotalPrice;
        TQRDBText *qrdbtFU;
        TQRBand *PageFooterBand1;
        TQRLabel *qrlClient;
        TQRLabel *qrlInvoice;
        TQRLabel *qrlDate;
        TQRDBText *qc;
        TQRDBText *qc2;
        TQRShape *QRShape6;
        TQRShape *QRShape7;
        TQRLabel *QRLabel27;
        TQRLabel *QRLabel28;
        TQRLabel *qrlCurrencyId;
        TQRExpr *QRExpr2;
private:	// User declarations
public:		// User declarations
        __fastcall TPrnInvoiceForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPrnInvoiceForm *PrnInvoiceForm;
//---------------------------------------------------------------------------
#endif
