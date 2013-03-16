//---------------------------------------------------------------------------

#ifndef MaterialPrtUnitH
#define MaterialPrtUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Qrctrls.hpp>
#include <QuickRpt.hpp>
//---------------------------------------------------------------------------
class TMaterialPrtForm : public TForm
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
   TQRBand *PageFooterBand1;
   TQRLabel *QRLabel1;
   TQRSysData *QRSysData1;
   TQRLabel *QRLabel2;
   TQRShape *QRShape3;
   TQRShape *QRShape1;
   TQRShape *QRShape2;
   TQRLabel *QRLabel3;
   TQRDBText *QRDBText3;
private:	// User declarations
public:		// User declarations
   __fastcall TMaterialPrtForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMaterialPrtForm *MaterialPrtForm;
//---------------------------------------------------------------------------
#endif
