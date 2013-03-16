//---------------------------------------------------------------------------

#ifndef PrnOutBoatH
#define PrnOutBoatH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <QuickRpt.hpp>
#include <QRCtrls.hpp>
//---------------------------------------------------------------------------
class TPrnOutBoatForm : public TForm
{
__published:	// IDE-managed Components
        TQuickRep *PrnView;
        TQRBand *TitleBand1;
        TQRLabel *QRLabel1;
        TQRLabel *qrlLadingId;
        TQRLabel *qrlOperUnit;
        TQRLabel *qrlBoatNo;
        TQRLabel *QRLabel5;
        TQRLabel *qrlBoatOrder;
        TQRLabel *qrlOutPort;
        TQRLabel *qrlTargetCountry;
        TQRLabel *qrlSubContainerInfo1;
        TQRLabel *qrlSubContainerInfo2;
        TQRLabel *qrlSubContainerInfo3;
        TQRLabel *qrlSubContainerInfo4;
        TQRLabel *qrlSubContainerInfo5;
        TQRLabel *qrlSubContainerInfo6;
        TQRLabel *qrlSubContainerInfo7;
        TQRLabel *qrlSubContainerInfo8;
        TQRLabel *qrlSubContainerInfo9;
        TQRLabel *qrlSubContainerInfo10;
        TQRLabel *qrlTypeInfo1;
        TQRLabel *qrlTypeInfo2;
        TQRLabel *qrlCountHead;
        TQRLabel *QRLabel17;
        TQRLabel *qrlMname;
        TQRLabel *qrlTotalNetWeight;
        TQRLabel *QRLabel20;
        TQRLabel *qrlDeclareId;
        TQRLabel *qrlCid;
        TQRLabel *QRLabel2;
        TQRLabel *qrlShipAgent;
        TQRLabel *qrlEndCustDate;
        TQRLabel *qrlSH;
        TQRLabel *qrl20DaXie;
        TQRLabel *qrlNum20DaXie;
        TQRLabel *qrl40DaXie;
        TQRLabel *qrlNum40DaXie;
private:	// User declarations
public:		// User declarations
        __fastcall TPrnOutBoatForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPrnOutBoatForm *PrnOutBoatForm;
//---------------------------------------------------------------------------
#endif
