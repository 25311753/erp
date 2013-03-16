//---------------------------------------------------------------------------

#ifndef PrnContactH
#define PrnContactH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <QuickRpt.hpp>
#include <QRCtrls.hpp>
//---------------------------------------------------------------------------
class TPrnContactForm : public TForm
{
__published:	// IDE-managed Components
        TQuickRep *PrnView;
        TQRBand *DetailBand1;
        TQRBand *PageHeaderBand1;
        TQRBand *TitleBand1;
        TQRShape *QRShape1;
        TQRShape *QRShape2;
        TQRShape *QRShape3;
        TQRShape *QRShape4;
        TQRLabel *QRLabel1;
        TQRLabel *QRLabel2;
        TQRDBText *qrdbtMname;
        TQRDBText *qrdbtCount;
        TQRDBText *qrdbtFU;
        TQRDBText *qrdbtUnitPrice;
        TQRDBText *qrdbtTotal;
        TQRLabel *qrlBargain;
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
        TQRLabel *QRLabel19;
        TQRLabel *QRLabel20;
        TQRLabel *QRLabel21;
        TQRLabel *QRLabel22;
        TQRLabel *QRLabel23;
        TQRLabel *QRLabel25;
        TQRLabel *QRLabel34;
        TQRLabel *QRLabel35;
        TQRShape *QRShape9;
        TQRShape *QRShape10;
        TQRShape *QRShape11;
        TQRLabel *QRLabel27;
        TQRLabel *QRLabel24;
        TQRShape *QRShape15;
        TQRShape *QRShape16;
        TQRShape *QRShape17;
        TQRLabel *QRLabel39;
        TQRLabel *QRLabel40;
        TQRLabel *QRLabel41;
        TQRLabel *QRLabel42;
        TQRLabel *QRLabel43;
        TQRLabel *QRLabel44;
        TQRLabel *QRLabel45;
        TQRLabel *QRLabel46;
        TQRLabel *QRLabel47;
        TQRLabel *QRLabel48;
        TQRLabel *QRLabel49;
        TQRLabel *QRLabel50;
        TQRLabel *QRLabel51;
        TQRLabel *QRLabel52;
        TQRLabel *QRLabel53;
        TQRLabel *QRLabel54;
        TQRLabel *QRLabel55;
        TQRLabel *QRLabel56;
        TQRLabel *QRLabel57;
        TQRLabel *QRLabel58;
        TQRLabel *QRLabel59;
        TQRLabel *QRLabel60;
        TQRLabel *QRLabel63;
        TQRLabel *qrlContactId;
        TQRLabel *QRLabel61;
        TQRLabel *QRLabel62;
        TQRShape *QRShape18;
        TQRLabel *qrlPack;
        TQRLabel *qrlOutport;
        TQRLabel *QRLabel65;
        TQRLabel *qrlTargetCountry;
        TQRLabel *qrlExcharge;
        TQRLabel *qrlY;
        TQRLabel *qrlM;
        TQRLabel *qrlD;
        TQRLabel *QRLabel75;
        TQRLabel *QRLabel76;
        TQRDBText *QRDBText1;
        TQRDBText *QRDBText2;
        TQRDBText *QRDBText3;
        TQRShape *QRShape12;
        TQRShape *QRShape13;
        TQRShape *QRShape14;
        TQRLabel *QRLabel26;
        TQRLabel *QRLabel28;
        TQRLabel *QRLabel29;
        TQRLabel *QRLabel30;
        TQRLabel *QRLabel31;
        TQRLabel *QRLabel32;
        TQRLabel *QRLabel33;
        TQRLabel *QRLabel36;
        TQRLabel *QRLabel37;
        TQRLabel *QRLabel38;
        TQRLabel *qrlSH;
        TQRLabel *qrlOperUnit;
        TQRLabel *qrlTotalDaXie;
        TQRShape *QRShape7;
        TQRShape *QRShape27;
        TQRShape *QRShape5;
        TQRShape *QRShape8;
        TQRShape *QRShape20;
        TQRShape *QRShape24;
        TQRShape *QRShape25;
        TQRShape *QRShape6;
        TQRLabel *qrlSubFlag;
        TQRLabel *qrlTotal;
        TQRLabel *qrlSubFlag2;
        TQRLabel *qrlOperUnitAddress;
        TQRLabel *qrlOperUnitTel;
        TQRLabel *qrlSHAddress;
        TQRLabel *qrlSHTel;
private:	// User declarations
public:		// User declarations
        __fastcall TPrnContactForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPrnContactForm *PrnContactForm;
//---------------------------------------------------------------------------
#endif
