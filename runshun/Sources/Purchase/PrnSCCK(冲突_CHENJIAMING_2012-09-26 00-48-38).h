//---------------------------------------------------------------------------

#ifndef PrnSCCKH
#define PrnSCCKH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <QRCtrls.hpp>
#include <QuickRpt.hpp>
//---------------------------------------------------------------------------
class TPrnSCCKForm : public TForm
{
__published:	// IDE-managed Components
        TQuickRep *PrnView;
        TQRBand *DetailBand1;
        TQRBand *TitleBand1;
        TQRShape *QRShape7;
        TQRShape *QRShape9;
        TQRShape *QRShape11;
        TQRShape *QRShape12;
        TQRLabel *QRLabel29;
        TQRLabel *QRLabel31;
        TQRLabel *QRLabel37;
        TQRBand *PageHeaderBand1;
        TQRBand *SummaryBand1;
        TQRLabel *QRLabel2;
        TQRShape *QRShape8;
        TQRShape *QRShape10;
        TQRShape *QRShape13;
        TQRShape *QRShape15;
        TQRShape *QRShape17;
        TQRShape *QRShape22;
        TQRShape *QRShape6;
        TQRShape *QRShape24;
        TQRShape *QRShape25;
        TQRShape *QRShape14;
        TQRShape *QRShape18;
        TQRShape *QRShape19;
        TQRShape *QRShape20;
        TQRShape *QRShape21;
        TQRShape *QRShape26;
        TQRDBText *qrdbtMname;
        TQRDBText *QRDBText1;
        TQRDBText *qrdbtTC;
        TQRDBText *qrdbtFU;
        TQRShape *QRShape2;
        TQRShape *QRShape3;
        TQRShape *QRShape4;
        TQRLabel *qrlSH;
        TQRLabel *QRLabel1;
        TQRLabel *QRLabel3;
        TQRLabel *QRLabel5;
        TQRLabel *QRLabel6;
        TQRLabel *QRLabel7;
        TQRLabel *QRLabel8;
        TQRLabel *QRLabel9;
        TQRLabel *QRLabel10;
        TQRLabel *QRLabel11;
        TQRLabel *QRLabel12;
        TQRLabel *QRLabel13;
        TQRLabel *QRLabel14;
        TQRLabel *qrlTargetCountry;
        TQRLabel *QRLabel15;
        TQRLabel *qrlForwardingunit;
        TQRLabel *QRLabel16;
        TQRShape *QRShape1;
        TQRShape *QRShape5;
        TQRLabel *QRLabel4;
        TQRLabel *QRLabel17;
        TQRLabel *QRLabel18;
private:	// User declarations
public:		// User declarations
        __fastcall TPrnSCCKForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPrnSCCKForm *PrnSCCKForm;
//---------------------------------------------------------------------------
#endif
