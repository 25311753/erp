//---------------------------------------------------------------------------

#ifndef PrnMaterialH
#define PrnMaterialH
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
class TPrnMaterialForm : public TForm
{
__published:	// IDE-managed Components
	TQuickRep *PrnView;
	TQRBand *PageHeaderBand1;
	TQRBand *DetailBand1;
	TQRLabel *QRLabel2;
	TQRDBText *cp_name;
	TQRLabel *QRLabel4;
	TQRDBText *QRDBText3;
	TQRLabel *QRLabel6;
	TQRDBText *QRDBText5;
	TQRLabel *QRLabel7;
	TQRDBText *QRDBText6;
	TQRLabel *QRLabel8;
	TQRDBText *QRDBText7;
	TQRLabel *QRLabel9;
	TQRMemo *QRMemo1;
	TQRLabel *QRLabel5;
	TQRLabel *QRLabel3;
	TQRDBText *QRDBText2;
	TQRDBText *QRDBText4;
	TQRLabel *QRLabel12;
	TQRShape *QRShape1;
        TQRLabel *QRLabel1;
        TQRDBText *QRDBText1;
	void __fastcall QRSubDetail1BeforePrint(TQRCustomBand *Sender,
          bool &PrintBand);
	void __fastcall DetailBand1BeforePrint(TQRCustomBand *Sender,
          bool &PrintBand);
private:	// User declarations
public:		// User declarations
	__fastcall TPrnMaterialForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPrnMaterialForm *PrnMaterialForm;
//---------------------------------------------------------------------------
#endif
