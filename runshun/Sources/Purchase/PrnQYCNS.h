//---------------------------------------------------------------------------

#ifndef PrnQYCNSH
#define PrnQYCNSH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <QRCtrls.hpp>
#include <QuickRpt.hpp>
//---------------------------------------------------------------------------
class TPrnQYCNSForm : public TForm
{
__published:	// IDE-managed Components
        TQuickRep *PrnView;
        TQRBand *TitleBand1;
        TQRLabel *QRLabel1;
        TQRLabel *QRLabel2;
        TQRLabel *qrlOperUnit;
        TQRLabel *qrlNowY;
        TQRLabel *QRLabel7;
        TQRLabel *qrlNowM;
        TQRLabel *QRLabel9;
        TQRLabel *qrlNowD;
        TQRLabel *QRLabel6;
        TQRLabel *QRLabel8;
        TQRLabel *QRLabel3;
        TQRLabel *QRLabel4;
        TQRLabel *QRLabel5;
        TQRLabel *QRLabel10;
        TQRLabel *QRLabel11;
        TQRLabel *QRLabel12;
        TQRLabel *QRLabel15;
        TQRLabel *QRLabel16;
        TQRLabel *QRLabel14;
        TQRLabel *QRLabel13;
        TQRLabel *QRLabel17;
private:	// User declarations
public:		// User declarations
        __fastcall TPrnQYCNSForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPrnQYCNSForm *PrnQYCNSForm;
//---------------------------------------------------------------------------
#endif
