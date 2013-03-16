//---------------------------------------------------------------------------

#ifndef TypePrtUnitH
#define TypePrtUnitH
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
class TTypePrtForm : public TForm
{
__published:	// IDE-managed Components
   TQuickRep *QuickRep1;
   TQRBand *DetailBand1;
   TQRDBText *QRDBText1;
   TQRDBText *QRDBText2;
   TQRBand *TitleBand1;
   TQRLabel *LabTitle;
   TQRLabel *LabCode;
   TQRLabel *LabName;
   TQRShape *QRShape1;
   TQRBand *PageFooterBand1;
   TQRShape *QRShape2;
   TQRLabel *QRLabel1;
   TQRSysData *QRSysData1;
   TQRLabel *QRLabel2;
private:	// User declarations
public:		// User declarations
   __fastcall TTypePrtForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTypePrtForm *TypePrtForm;
//---------------------------------------------------------------------------
#endif
