//---------------------------------------------------------------------------

#ifndef PrnAskPurchaseH
#define PrnAskPurchaseH
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
class TPrnAskPurchaseForm : public TForm
{
__published:	// IDE-managed Components
	TQuickRep *PrnView;
	TQRBand *PageHeaderBand1;
	TQRBand *DetailBand1;
	TQRLabel *Type;
	TQRLabel *NeedYear;
	TQRLabel *NeedMonth;
	TQRLabel *NeedDay;
	TQRLabel *ReqYear;
	TQRLabel *ReqMonth;
	TQRLabel *ReqDay;
	TQRLabel *BuyType;
	TQRLabel *StockDep;
	TQRLabel *ReqCorp;
	TQRLabel *ReqDepart;
	TQRLabel *ChargeDep;
	TQRLabel *Project;
	TQRLabel *MainID;
	TQRBand *PageFooterBand1;
	TQRDBText *pd_code;
	TQRDBText *QRDBText2;
	TQRDBText *QRDBText3;
	TQRDBText *QRDBText4;
	TQRLabel *GoodsAddr;
	TQRLabel *HandleMan;
	TQRLabel *ChkSpec0;
	TQRDBText *QRDBText6;
	TQRLabel *txtSpec1;
	TQRLabel *txtCooper1;
	TQRLabel *txtUsage0;
	TQRLabel *txtUsage1;
	TQRLabel *ChkSpec1;
	TQRLabel *txtTel;
	TQRLabel *ChkFlag;
	TQRLabel *txtCooper0;
	TQRLabel *txtTreat0;
	TQRLabel *txtTreat1;
	TQRLabel *txtCoopTitle;
	TQRLabel *txtPrnRem;
	void __fastcall pd_codePrint(TObject *sender, AnsiString &Value);
	void __fastcall QRDBText6Print(TObject *sender, AnsiString &Value);
	void __fastcall DetailBand1BeforePrint(TQRCustomBand *Sender,
          bool &PrintBand);
	void __fastcall QRDBText5Print(TObject *sender, AnsiString &Value);
	void __fastcall PrnViewBeforePrint(TCustomQuickRep *Sender,
          bool &PrintReport);
	void __fastcall PageFooterBand1BeforePrint(TQRCustomBand *Sender,
          bool &PrintBand);
private:	// User declarations
public:		// User declarations
	CStringArray m_lstRemID;
  
	__fastcall TPrnAskPurchaseForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPrnAskPurchaseForm *PrnAskPurchaseForm;
//---------------------------------------------------------------------------
#endif
