//---------------------------------------------------------------------------

#ifndef PrnWuMuZhiH
#define PrnWuMuZhiH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <QRCtrls.hpp>
#include <QuickRpt.hpp>
//---------------------------------------------------------------------------
class TPrnWuMuZhiForm : public TForm
{
__published:	// IDE-managed Components
        TQuickRep *PrnView;
        TQRBand *TitleBand1;
        TQRLabel *QRLabel1;
        TQRLabel *QRLabel2;
        TQRLabel *QRLabel3;
        TQRLabel *QRLabel4;
        TQRLabel *QRLabel5;
        TQRLabel *qrlTargetCountry;
        TQRLabel *qrlCountHead;
        TQRLabel *qrlTotalNetWeight;
        TQRLabel *QRLabel6;
        TQRLabel *QRLabel7;
        TQRLabel *QRLabel8;
        TQRLabel *QRLabel9;
        TQRLabel *qrlMname;
        TQRLabel *QRLabel10;
        TQRLabel *qrlOperUnit;
        TQRLabel *QRLabel11;
        TQRSysData *QRSysData1;
        TQRLabel *QRLabel12;
private:	// User declarations
public:		// User declarations
        __fastcall TPrnWuMuZhiForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPrnWuMuZhiForm *PrnWuMuZhiForm;
//---------------------------------------------------------------------------
#endif
