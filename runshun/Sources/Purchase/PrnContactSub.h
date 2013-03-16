//---------------------------------------------------------------------------

#ifndef PrnContactSubH
#define PrnContactSubH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <QuickRpt.hpp>
#include <QRCtrls.hpp>
//---------------------------------------------------------------------------
class TPrnContactSubForm : public TForm
{
__published:	// IDE-managed Components
        TQuickRep *PrnView;
        TQRBand *PageHeaderBand1;
        TQRBand *DetailBand1;
        TQRLabel *QRLabel3;
        TQRLabel *QRLabel4;
        TQRLabel *QRLabel5;
        TQRLabel *QRLabel6;
        TQRLabel *QRLabel7;
        TQRLabel *QRLabel8;
        TQRLabel *QRLabel9;
        TQRLabel *QRLabel10;
        TQRLabel *QRLabel1;
        TQRDBText *qrdbtMname;
        TQRDBText *qrdbtCount;
        TQRDBText *qrdbtFU;
        TQRDBText *QRDBText1;
        TQRDBText *qrdbtUnitPrice;
        TQRDBText *QRDBText2;
        TQRDBText *qrdbtTotal;
        TQRLabel *qrlContactId;
private:	// User declarations
public:		// User declarations
        __fastcall TPrnContactSubForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPrnContactSubForm *PrnContactSubForm;
//---------------------------------------------------------------------------
#endif
