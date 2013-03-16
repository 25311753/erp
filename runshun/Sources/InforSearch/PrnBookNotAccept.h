//---------------------------------------------------------------------------

#ifndef PrnBookNotAcceptH
#define PrnBookNotAcceptH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Qrctrls.hpp>
#include <QuickRpt.hpp>
#include <QRCtrls.hpp>
//---------------------------------------------------------------------------
class TPrnBookNotAcceptForm : public TForm
{
__published:	// IDE-managed Components
	TQuickRep *PrnView;
	TQRBand *PageHeaderBand1;
	TQRLabel *QRLabel1;
	TQRShape *QRShape1;
	TQRLabel *QRLabel2;
	TQRShape *QRShape2;
	TQRLabel *QRLabel3;
	TQRShape *QRShape3;
	TQRLabel *QRLabel4;
	TQRShape *QRShape4;
	TQRLabel *QRLabel5;
	TQRShape *QRShape5;
	TQRLabel *QRLabel6;
	TQRShape *QRShape6;
	TQRLabel *QRLabel7;
	TQRShape *QRShape7;
	TQRLabel *QRLabel8;
	TQRShape *QRShape8;
	TQRLabel *QRLabel9;
	TQRLabel *QRLabel10;
        TQRLabel *txtPrnTime;
        TQRBand *DetailBand1;
        TQRShape *QRShape9;
        TQRShape *QRShape10;
        TQRShape *QRShape11;
        TQRShape *QRShape12;
        TQRShape *QRShape13;
        TQRShape *QRShape14;
        TQRShape *QRShape15;
        TQRShape *QRShape16;
        TQRDBText *QRDBText1;
        TQRDBText *QRDBText2;
        TQRDBText *QRDBText3;
        TQRDBText *QRDBText4;
        TQRDBText *QRDBText5;
        TQRDBText *QRDBText6;
        TQRDBText *QRDBText7;
private:	// User declarations
public:		// User declarations
	__fastcall TPrnBookNotAcceptForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPrnBookNotAcceptForm *PrnBookNotAcceptForm;
//---------------------------------------------------------------------------
#endif
