//---------------------------------------------------------------------------

#ifndef PrnBookFactoryH
#define PrnBookFactoryH
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
class TPrnBookFactoryForm : public TForm
{
__published:	// IDE-managed Components
	TQuickRep *PrnView;
	TQRBand *PageHeaderBand1;
	TQRShape *QRShape32;
	TQRShape *QRShape30;
	TQRShape *QRShape9;
	TQRLabel *QRLabel1;
	TQRLabel *QRLabel2;
	TQRLabel *QRLabel3;
	TQRLabel *FactName;
	TQRLabel *QRLabel5;
	TQRLabel *LinkMan;
	TQRLabel *QRLabel11;
	TQRLabel *Tel;
	TQRLabel *QRLabel13;
	TQRLabel *Fax;
	TQRLabel *QRLabel15;
	TQRLabel *BookDate;
	TQRLabel *QRLabel17;
	TQRShape *QRShape1;
	TQRLabel *QRLabel18;
	TQRShape *QRShape2;
	TQRLabel *QRLabel19;
	TQRShape *QRShape3;
	TQRLabel *QRLabel20;
	TQRShape *QRShape4;
	TQRLabel *QRLabel21;
	TQRShape *QRShape5;
	TQRLabel *QRLabel22;
	TQRShape *QRShape6;
	TQRLabel *QRLabel23;
	TQRShape *QRShape7;
	TQRLabel *QRLabel24;
	TQRShape *QRShape8;
	TQRLabel *QRLabel25;
	TQRLabel *QRLabel26;
	TQRLabel *txtSDAddr;
	TQRLabel *txtSubTel;
	TQRLabel *QRLabel10;
	TQRLabel *QRLabel7;
	TQRLabel *txtSDTel;
	TQRLabel *QRLabel8;
	TQRLabel *txtTail;
	TQRShape *QRShape34;
	TQRLabel *QRLabel16;
	TQRLabel *QRLabel32;
	TQRBand *DetailBand1;
	TQRShape *QRShape31;
	TQRShape *QRShape18;
	TQRShape *QRShape10;
	TQRShape *QRShape11;
	TQRShape *QRShape12;
	TQRShape *QRShape13;
	TQRShape *QRShape14;
	TQRShape *QRShape15;
	TQRShape *QRShape16;
	TQRShape *QRShape17;
	TQRDBText *bf_code;
	TQRDBText *QRDBText2;
	TQRDBText *QRDBText3;
	TQRDBText *QRDBText4;
	TQRDBText *QRDBText5;
	TQRDBText *bf_price;
	TQRDBText *QRDBText7;
	TQRLabel *BookMoney;
	TQRDBText *QRDBText1;
	TQRLabel *txtRMB;
	TQRShape *QRShape33;
	TQRDBText *QRDBText8;
	TQRLabel *txtName2;
	TQRShape *QRShape35;
	TQRLabel *txtKind0;
	TQRLabel *txtKind1;
	TQRBand *PageFooterBand1;
	TQRShape *QRShape19;
	TQRLabel *QRLabel27;
	TQRLabel *QRLabel28;
	TQRShape *QRShape20;
	TQRLabel *QRLabel29;
	TQRLabel *QRLabel30;
	TQRLabel *QRLabel31;
	TQRLabel *RcptName;
	TQRLabel *QRLabel33;
	TQRLabel *RcptTel;
	TQRLabel *QRLabel35;
	TQRLabel *Invoice;
	TQRShape *QRShape21;
	TQRLabel *QRLabel37;
	TQRShape *QRShape22;
	TQRShape *QRShape23;
	TQRLabel *QRLabel38;
	TQRShape *QRShape24;
	TQRShape *QRShape25;
	TQRLabel *QRLabel39;
	TQRLabel *QRLabel40;
	TQRShape *QRShape26;
	TQRLabel *QRLabel41;
	TQRLabel *QRLabel42;
	TQRLabel *QRLabel43;
	TQRLabel *QRLabel44;
	TQRLabel *txtTaxType;
	TQRShape *QRShape27;
	TQRLabel *QRLabel50;
	TQRLabel *QRLabel51;
	TQRLabel *QRLabel52;
	TQRLabel *QRLabel53;
	TQRShape *QRShape28;
	TQRLabel *QRLabel54;
	TQRShape *QRShape29;
	TQRLabel *QRLabel55;
	TQRLabel *QRLabel57;
	TQRLabel *QRLabel58;
	TQRLabel *QRLabel59;
	TQRLabel *StockMan;
	TQRLabel *GoodsAddr;
	TQRLabel *txtInvoiceType;
	TQRLabel *QRLabel4;
	TQRLabel *QRLabel6;
	TQRLabel *txtPayment;
        TQRLabel *factname2;
        TQRLabel *FactName1;
        TQRLabel *linkman2;
        TQRLabel *LinkMan1;
        TQRLabel *tel2;
        TQRLabel *Tel1;
        TQRLabel *fax2;
        TQRLabel *Fax1;
        TQRLabel *QRLabel9;
        TQRSysData *QRSysData1;
	void __fastcall bf_codePrint(TObject *sender, AnsiString &Value);
	void __fastcall DetailBand1BeforePrint(TQRCustomBand *Sender,
          bool &PrintBand);
	void __fastcall QRDBText2Print(TObject *sender, AnsiString &Value);
private:	// User declarations
public:		// User declarations
	__fastcall TPrnBookFactoryForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPrnBookFactoryForm *PrnBookFactoryForm;
//---------------------------------------------------------------------------
#endif
