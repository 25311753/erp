//---------------------------------------------------------------------------

#ifndef PrnAuthH
#define PrnAuthH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <QRCtrls.hpp>
#include <QuickRpt.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TPrnAuthForm : public TForm
{
__published:	// IDE-managed Components
        TQuickRep *PrnView;
        TQRLabel *QRLabel1;
        TQRLabel *qrlValidDateYYYY;
        TQRLabel *qrlValidDateMM;
        TQRLabel *qrlValidDateDD;
        TQRLabel *qrlNowDD;
        TQRLabel *qrlNowMM;
        TQRLabel *qrlNowYYYY;
        TQRLabel *qrlOperUnit;
        TQRLabel *qrlFirstMname;
        TQRLabel *qrlFirstMid;
        TQRLabel *qrlNowYYYY1;
        TQRLabel *qrlNowMM1;
        TQRLabel *qrlNowDD1;
        TQRLabel *qrlLadingId;
        TQRLabel *qrlTrade;
        TQRLabel *qrlInnersupplyadd;
        TQRLabel *QRLabel2;
        TQRLabel *qrlDeclareId;
        TQRLabel *qrlNowYYYY2;
        TQRLabel *qrlNowMM2;
        TQRLabel *qrlNowDD2;
        TQRLabel *qrlNowYYYY3;
        TQRLabel *qrlNowMM3;
        TQRLabel *qrlNowDD3;
        TQRLabel *qrlNowYYYY4;
        TQRLabel *qrlNowMM4;
        TQRLabel *qrlNowDD4;
        TQRLabel *QRLabel3;
        TQRLabel *qrlTotal;
        TQRBand *TitleBand1;
        TQRLabel *qrlCid;
        TQRLabel *QRLabel4;
private:	// User declarations
public:		// User declarations
        __fastcall TPrnAuthForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPrnAuthForm *PrnAuthForm;
//---------------------------------------------------------------------------
#endif
