//---------------------------------------------------------------------------

#ifndef PrnMaterBookListH
#define PrnMaterBookListH
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
class TPrnStuffBookListForm : public TForm
{
__published:	// IDE-managed Components
	TQuickRep *PrnView;
	TQRBand *PageHeaderBand1;
	TQRLabel *QRLabel1;
	TQRShape *QRShape1;
	TQRLabel *QRLabel6;
	TQRShape *QRShape2;
	TQRLabel *QRLabel7;
	TQRShape *QRShape3;
	TQRLabel *QRLabel8;
	TQRShape *QRShape4;
	TQRLabel *QRLabel9;
	TQRShape *QRShape5;
	TQRLabel *QRLabel10;
	TQRShape *QRShape6;
	TQRLabel *QRLabel11;
	TQRBand *DetailBand1;
	TQRShape *QRShape7;
	TQRShape *QRShape8;
	TQRShape *QRShape9;
	TQRShape *QRShape10;
	TQRShape *QRShape11;
	TQRShape *QRShape12;
	TQRDBText *QRDBText1;
	TQRDBText *QRDBText2;
	TQRDBText *QRDBText3;
	TQRDBText *QRDBText4;
	TQRDBText *QRDBText5;
	TQRDBText *QRDBText6;
	TQRLabel *QRLabel2;
	TQRShape *QRShape13;
	TQRLabel *QRLabel3;
	TQRShape *QRShape14;
	TQRDBText *QRDBText7;
	TQRShape *QRShape16;
	TQRDBText *QRDBText8;
	TQRShape *QRShape17;
	TQRDBText *QRDBText9;
	TQRLabel *txtName2;
	void __fastcall QRDBText9Print(TObject *sender, AnsiString &Value);
private:	// User declarations
public:		// User declarations
	__fastcall TPrnStuffBookListForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPrnStuffBookListForm *PrnStuffBookListForm;
//---------------------------------------------------------------------------
#endif
