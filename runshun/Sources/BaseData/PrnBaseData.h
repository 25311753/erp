//---------------------------------------------------------------------------

#ifndef PrnBaseDataH
#define PrnBaseDataH
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
class TPrnBaseDataForm : public TForm
{
__published:	// IDE-managed Components
	TQuickRep *PrnView;
	TQRBand *PageHeaderBand1;
	TQRLabel *txtTitle;
	TQRLabel *QRLabel2;
	TQRSysData *QRSysData1;
	TQRLabel *QRLabel3;
	TQRSysData *QRSysData2;
	TQRLabel *txtText0;
	TQRLabel *txtText1;
	TQRShape *QRShape1;
	TQRLabel *txtText2;
	TQRLabel *txtText3;
	TQRBand *DetailBand1;
	TQRDBText *QRDBText1;
	TQRDBText *QRDBText2;
	TQRDBText *QRDBText3;
	TQRDBText *QRDBText4;
private:	// User declarations
public:		// User declarations
	__fastcall TPrnBaseDataForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPrnBaseDataForm *PrnBaseDataForm;
//---------------------------------------------------------------------------
#endif
