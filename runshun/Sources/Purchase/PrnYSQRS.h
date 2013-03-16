//---------------------------------------------------------------------------

#ifndef PrnYSQRSH
#define PrnYSQRSH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <QRCtrls.hpp>
#include <QuickRpt.hpp>
//---------------------------------------------------------------------------
class TPrnYSQRSForm : public TForm
{
__published:	// IDE-managed Components
        TQuickRep *PrnView;
        TQRBand *TitleBand1;
        TQRLabel *QRLabel1;
        TQRLabel *QRLabel2;
        TQRLabel *QRLabel3;
        TQRLabel *QRLabel4;
        TQRLabel *QRLabel5;
        TQRLabel *qrlMname;
        TQRLabel *QRLabel10;
        TQRLabel *qrlOperUnit;
        TQRLabel *QRLabel12;
        TQRLabel *qrlSH;
        TQRLabel *qrlOperUnit2;
        TQRLabel *qrlCid;
        TQRLabel *qrlNowY;
        TQRLabel *QRLabel7;
        TQRLabel *qrlNowM;
        TQRLabel *QRLabel9;
        TQRLabel *qrlNowD;
        TQRLabel *QRLabel13;
private:	// User declarations
public:		// User declarations
        __fastcall TPrnYSQRSForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPrnYSQRSForm *PrnYSQRSForm;
//---------------------------------------------------------------------------
#endif
