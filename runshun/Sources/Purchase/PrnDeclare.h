//---------------------------------------------------------------------------

#ifndef PrnDeclareH
#define PrnDeclareH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <QuickRpt.hpp>
#include <QRCtrls.hpp>
//---------------------------------------------------------------------------
class TPrnDeclareForm : public TForm
{
__published:	// IDE-managed Components
        TQuickRep *PrnView;
        TQRBand *DetailBand1;
        TQRBand *PageHeaderBand1;
        TQRSysData *QRSysData1;
        TQRLabel *QRLabel2;
        TQRLabel *qrlOperUnit;
        TQRLabel *qrlTransport;
        TQRLabel *qrlBoatNo;
        TQRLabel *QRLabel3;
        TQRLabel *qrlBoatOrder;
        TQRLabel *qrlLadingId;
        TQRLabel *qrlTrade;
        TQRLabel *qrlZhengMian;
        TQRLabel *qrlExcharge;
        TQRLabel *qrlTargetCountry;
        TQRLabel *qrlInnersupplyadd;
        TQRLabel *qrlLicenseNo;
        TQRLabel *qrlBargain;
        TQRLabel *qrlContractId;
        TQRLabel *qrlCount;
        TQRLabel *qrlPack;
        TQRLabel *qrlNetWeight;
        TQRLabel *qrlGrossWeight;
        TQRLabel *qrlMarks;
        TQRDBText *qrdbtMname;
        TQRDBText *qrdbtCount;
        TQRDBText *qrdbtFU;
        TQRDBText *qrdbtUnitPrice;
        TQRDBText *qrdbtTotal;
        TQRDBText *qrdbtCurr;
        TQRBand *PageFooterBand1;
        TQRLabel *QRLabel4;
        TQRLabel *qrlZhengMianDetail;
        TQRDBText *qrdbtMid;
        TQRDBText *qrdbtTargetCountry;
        TQRDBText *QRDBText1;
        TQRLabel *qrlDeclareId;
        TQRLabel *qrlManufacturer;
        TQRLabel *qrlAttacheDoc;
        TQRDBText *qrdbtCount2;
        TQRDBText *qrdbtSU;
        TQRLabel *qrlContainerHead;
        TQRLabel *qrlContainerTail;
        TQRLabel *qrlCurrency;
        TQRLabel *qrlForwardingUnit;
        TQRLabel *qrlAssginPort;
        TQRLabel *qrlCarriage;
        TQRLabel *qrlInsurance;
        TQRLabel *qrlCid;
        TQRLabel *QRLabel5;
        TQRLabel *qrlCurrency2;
        TQRLabel *qrlSubFlag;
        TQRLabel *qrlTotal;
        TQRDBText *row_ord;
        void __fastcall DetailBand1BeforePrint(TQRCustomBand *Sender,
          bool &PrintBand);
private:	// User declarations
public:		// User declarations
        __fastcall TPrnDeclareForm(TComponent* Owner);
        int m_nColOrd;
        int m_nStep;
};
//---------------------------------------------------------------------------
extern PACKAGE TPrnDeclareForm *PrnDeclareForm;
//---------------------------------------------------------------------------
#endif
