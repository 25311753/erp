//---------------------------------------------------------------------------

#ifndef PrnPackingListH
#define PrnPackingListH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <QRCtrls.hpp>
#include <QuickRpt.hpp>
//---------------------------------------------------------------------------
class TPrnPackingListForm : public TForm
{
__published:	// IDE-managed Components
        TQuickRep *PrnView;
        TQRBand *DetailBand1;
        TQRBand *TitleBand1;
        TQRBand *PageFooterBand1;
        TQRBand *PageHeaderBand1;
        TQRLabel *QRLabel1;
        TQRLabel *QRLabel2;
        TQRLabel *QRLabel3;
        TQRLabel *QRLabel4;
        TQRLabel *QRLabel5;
        TQRLabel *QRLabel6;
        TQRLabel *QRLabel7;
        TQRLabel *QRLabel8;
        TQRLabel *QRLabel9;
        TQRLabel *QRLabel10;
        TQRLabel *QRLabel11;
        TQRLabel *QRLabel12;
        TQRLabel *QRLabel13;
        TQRLabel *QRLabel14;
        TQRLabel *QRLabel15;
        TQRLabel *QRLabel16;
        TQRLabel *QRLabel17;
        TQRLabel *QRLabel18;
        TQRShape *QRShape1;
        TQRShape *QRShape2;
        TQRShape *QRShape3;
        TQRShape *QRShape4;
        TQRShape *QRShape5;
        TQRShape *QRShape6;
        TQRShape *QRShape7;
        TQRShape *QRShape8;
        TQRShape *QRShape9;
        TQRShape *QRShape10;
        TQRShape *QRShape11;
        TQRShape *QRShape12;
        TQRShape *QRShape13;
        TQRShape *QRShape14;
        TQRLabel *QRLabel19;
        TQRLabel *QRLabel20;
        TQRDBText *qrdbtMarks;
        TQRShape *QRShape15;
        TQRShape *QRShape16;
        TQRShape *QRShape17;
        TQRShape *QRShape18;
        TQRShape *QRShape19;
        TQRShape *QRShape20;
        TQRShape *QRShape21;
        TQRShape *QRShape22;
        TQRShape *QRShape23;
        TQRLabel *qrlSH;
        TQRLabel *qrlInvoice;
        TQRLabel *qrlContractId;
        TQRLabel *qrlExcharge;
        TQRLabel *qrlDate;
        TQRDBText *qrdbtMname;
        TQRDBText *qrldbtCasesCnt;
        TQRDBText *qrdbtTC;
        TQRDBText *qrdbtFU;
        TQRDBText *qrdbtTN;
        TQRDBText *qrdbtTG;
        TQRLabel *QRLabel21;
        TQRLabel *QRLabel22;
        TQRLabel *QRLabel23;
        TQRExpr *QRExpr1;
        TQRLabel *QRLabel24;
        TQRLabel *qrlGrossWeight;
        TQRLabel *QRLabel25;
        TQRLabel *qrlNetWeight;
        TQRLabel *QRLabel26;
        TQRLabel *QRLabel27;
        TQRLabel *QRLabel28;
        TQRLabel *QRLabel29;
        TQRLabel *QRLabel30;
        TQRLabel *QRLabel31;
        TQRLabel *QRLabel32;
        TQRLabel *QRLabel33;
        TQRLabel *QRLabel34;
        TQRLabel *QRLabel35;
        TQRLabel *QRLabel36;
        TQRLabel *QRLabel37;
        TQRLabel *QRLabel38;
        TQRLabel *qrlOutport;
        TQRLabel *qrlTargetCountry;
        TQRLabel *QRLabel39;
        TQRLabel *QRLabel40;
        TQRShape *QRShape24;
        TQRShape *QRShape25;
private:	// User declarations
public:		// User declarations
        __fastcall TPrnPackingListForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPrnPackingListForm *PrnPackingListForm;
//---------------------------------------------------------------------------
#endif
