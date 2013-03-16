//---------------------------------------------------------------------------

#ifndef PrnDeclareSubH
#define PrnDeclareSubH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <QRCtrls.hpp>
#include <QuickRpt.hpp>
//---------------------------------------------------------------------------
class TPrnDeclareSubForm : public TForm
{
__published:	// IDE-managed Components
        TQuickRep *PrnView;
        TQRBand *DetailBand1;
        TQRDBText *qrdbtMname;
        TQRDBText *qrdbtCount;
        TQRDBText *qrdbtFU;
        TQRDBText *qrdbtUnitPrice;
        TQRDBText *qrdbtTotal;
        TQRDBText *qrdbtCurr;
        TQRLabel *qrlZhengMianDetail;
        TQRSysData *QRSysData2;
        TQRDBText *qrdbtMid;
        TQRDBText *qrdbtTargetCountry;
        TQRDBText *QRDBText1;
        TQRDBText *qrdbtCount2;
        TQRDBText *qrdbtSU;
        TQRLabel *qrlCurrency;
        TQRBand *PageHeaderBand1;
        TQRLabel *qrlCid;
        TQRLabel *QRLabel5;
        TQRLabel *QRLabel1;
        TQRLabel *QRLabel2;
        TQRLabel *QRLabel3;
        TQRLabel *QRLabel6;
        TQRLabel *QRLabel7;
        TQRLabel *QRLabel9;
        TQRLabel *QRLabel10;
        TQRLabel *QRLabel11;
private:	// User declarations
public:		// User declarations
        __fastcall TPrnDeclareSubForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPrnDeclareSubForm *PrnDeclareSubForm;
//---------------------------------------------------------------------------
#endif
