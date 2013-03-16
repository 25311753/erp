//---------------------------------------------------------------------------

#ifndef PrnRemMaterilnoH
#define PrnRemMaterilnoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <QuickRpt.hpp>
#include <DB.hpp>
#include <DBTables.hpp>
#include <QRCtrls.hpp>
//---------------------------------------------------------------------------
class TPrnRemMaterialno : public TForm
{
__published:	// IDE-managed Components
        TQuickRep *QR1;
        TQRBand *PageHeaderBand1;
        TQRLabel *QRLabel1;
        TQRLabel *QRLabel2;
        TQRLabel *QRLabel3;
        TQRLabel *QRLabel4;
        TQRLabel *QRLabel5;
        TQRShape *QRShape1;
        TQRBand *DetailBand1;
        TQRSubDetail *QRSubDetail3;
        TQRShape *QRShape4;
        TQRLabel *QRLabel8;
        TQRLabel *QRLabel7;
        TQRMemo *QRMemo2;
        TQRShape *QRShape3;
        TQRShape *QRShape2;
        TQRMemo *QRMemo1;
        TQRLabel *QRLabel6;
        TQRShape *QRShape5;
        TQRLabel *QRLabel9;
        TQRMemo *QRMemo3;
private:	// User declarations
public:		// User declarations
        __fastcall TPrnRemMaterialno(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPrnRemMaterialno *PrnRemMaterialno;
//---------------------------------------------------------------------------
#endif
