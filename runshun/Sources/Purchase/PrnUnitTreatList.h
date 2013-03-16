//---------------------------------------------------------------------------

#ifndef PrnUnitTreatListH
#define PrnUnitTreatListH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Qrctrls.hpp>
#include <QuickRpt.hpp>
//---------------------------------------------------------------------------

#include "BaseCode.h"
#include <QRCtrls.hpp>

class TPrnUnitTreatListForm : public TForm
{
__published:	// IDE-managed Components
	TQuickRep *PrnView;
	TQRBand *PageHeaderBand1;
	TQRLabel *QRLabel1;
	TQRLabel *QRLabel2;
	TQRLabel *txtPrnDate;
	TQRLabel *QRLabel4;
	TQRSysData *QRSysData1;
	TQRSubDetail *QRSubDetail1;
	TQRShape *QRShape10;
	TQRShape *QRShape11;
	TQRShape *QRShape12;
	TQRShape *QRShape13;
	TQRShape *QRShape14;
	TQRShape *QRShape15;
	TQRShape *QRShape16;
	TQRShape *QRShape17;
	TQRShape *QRShape18;
	TQRDBText *ts_code;
	TQRDBText *QRDBText2;
	TQRDBText *QRDBText3;
	TQRDBText *QRDBText4;
	TQRDBText *QRDBText5;
	TQRDBText *QRDBText6;
	TQRDBText *QRDBText7;
	TQRDBText *QRDBText8;
	TQRDBText *QRDBText9;
	TQRLabel *QRLabel5;
	TQRLabel *txtType;
	TQRLabel *QRLabel7;
	TQRShape *QRShape1;
	TQRLabel *QRLabel8;
	TQRShape *QRShape2;
	TQRLabel *QRLabel9;
	TQRShape *QRShape3;
	TQRLabel *QRLabel10;
	TQRShape *QRShape4;
	TQRLabel *QRLabel11;
	TQRShape *QRShape5;
	TQRLabel *QRLabel12;
	TQRShape *QRShape6;
	TQRLabel *QRLabel13;
	TQRShape *QRShape7;
	TQRLabel *QRLabel14;
	TQRShape *QRShape8;
	TQRLabel *QRLabel15;
	TQRLabel *QRLabel16;
	TQRShape *QRShape9;
	TQRLabel *QRLabel3;
	TQRShape *QRShape19;
	TQRLabel *QRLabel6;
	TQRLabel *QRLabel17;
	TQRShape *QRShape20;
	TQRLabel *txtBook;
	void __fastcall QRSubDetail1BeforePrint(TQRCustomBand *Sender,
          bool &PrintBand);
	void __fastcall PageHeaderBand1BeforePrint(TQRCustomBand *Sender,
          bool &PrintBand);
	void __fastcall QRDBText9Print(TObject *sender, AnsiString &Value);
private:	// User declarations
	char  m_strPrvCode[80];
public:		// User declarations
	__fastcall TPrnUnitTreatListForm(TComponent* Owner);

	CArray<BASE2COLDATA,BASE2COLDATA>m_lstBook;
};
//---------------------------------------------------------------------------
extern PACKAGE TPrnUnitTreatListForm *PrnUnitTreatListForm;
//---------------------------------------------------------------------------
#endif
