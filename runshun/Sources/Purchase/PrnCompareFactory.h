//---------------------------------------------------------------------------

#ifndef PrnCompareFactoryH
#define PrnCompareFactoryH
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
class TPrnCompareFactoryForm : public TForm
{
__published:	// IDE-managed Components
	TQuickRep *PrnView;
	TQRBand *PageHeaderBand1;
	TQRLabel *QRLabel1;
	TQRLabel *QRLabel2;
	TQRLabel *ReqDep;
	TQRLabel *QRLabel4;
	TQRLabel *HandleMan;
	TQRLabel *QRLabel6;
	TQRLabel *Tel;
	TQRLabel *QRLabel8;
	TQRLabel *MainID;
	TQRLabel *QRLabel10;
	TQRLabel *Project;
	TQRLabel *QRLabel12;
	TQRLabel *EndDate;
	TQRLabel *QRLabel14;
	TQRLabel *ReqDate;
	TQRLabel *QRLabel16;
	TQRLabel *NeedDate;
	TQRBand *DetailBand1;
	TQRShape *QRShape1;
	TQRLabel *QRLabel18;
	TQRShape *QRShape2;
	TQRLabel *QRLabel19;
	TQRShape *QRShape3;
	TQRLabel *QRLabel20;
	TQRShape *QRShape4;
	TQRLabel *QRLabel21;
	TQRShape *QRShape7;
	TQRLabel *QRLabel22;
	TQRLabel *QRLabel23;
	TQRLabel *QRLabel24;
	TQRShape *QRShape10;
	TQRShape *QRShape13;
	TQRShape *QRShape16;
	TQRShape *QRShape19;
	TQRShape *QRShape22;
	TQRShape *QRShape25;
	TQRShape *QRShape26;
	TQRShape *QRShape27;
	TQRShape *QRShape29;
	TQRShape *QRShape30;
	TQRLabel *QRLabel25;
	TQRLabel *QRLabel26;
	TQRShape *QRShape31;
	TQRShape *QRShape33;
	TQRShape *QRShape35;
	TQRShape *QRShape37;
	TQRShape *QRShape39;
	TQRBand *PageFooterBand1;
	TQRLabel *QRLabel27;
	TQRLabel *QRLabel28;
	TQRLabel *QRLabel29;
	TQRLabel *QRLabel30;
	TQRLabel *QRLabel31;
	TQRLabel *QRLabel32;
	TQRLabel *QRLabel33;
	TQRLabel *QRLabel34;
	TQRLabel *QRLabel35;
	TQRLabel *FactName0;
	TQRLabel *FactName1;
	TQRLabel *FactName2;
	TQRLabel *FactName3;
	TQRLabel *FactName4;
	TQRLabel *FactCard0;
	TQRLabel *FactCard1;
	TQRLabel *FactCard2;
	TQRLabel *FactCard3;
	TQRLabel *FactCard4;
	TQRDBText *pd_code;
	TQRDBText *QRDBText3;
	TQRDBText *QRDBText4;
	TQRLabel *Delivery0;
	TQRLabel *Delivery1;
	TQRLabel *Delivery2;
	TQRLabel *Delivery3;
	TQRLabel *Delivery4;
	TQRLabel *Higgle0;
	TQRLabel *Higgle1;
	TQRLabel *Higgle2;
	TQRLabel *Higgle3;
	TQRLabel *Higgle4;
	TQRLabel *Quote0;
	TQRLabel *Quote1;
	TQRLabel *Quote2;
	TQRLabel *Quote3;
	TQRLabel *Quote4;
	TQRShape *QRShape28;
	TQRShape *QRShape41;
	TQRLabel *QRLabel3;
	TQRSysData *QRSysData1;
	TQRLabel *Tail0;
	TQRLabel *Tail1;
	TQRLabel *Tail2;
	TQRLabel *Tail3;
	TQRLabel *Tail4;
	TQRLabel *txtMNName2;
	TQRLabel *txtMNName1;
	TQRLabel *QRLabel5;
	TQRLabel *txtPM0;
	TQRLabel *txtPM1;
	TQRLabel *txtPM2;
	TQRLabel *txtPM3;
	TQRLabel *txtPM4;
	TQRLabel *QRLabel7;
	TQRLabel *txtDD0;
	TQRLabel *txtDD1;
	TQRLabel *txtDD2;
	TQRLabel *txtDD3;
	TQRLabel *txtDD4;
	TQRLabel *QRLabel9;
	TQRLabel *txtTax0;
	TQRLabel *txtTax1;
	TQRLabel *txtTax2;
	TQRLabel *txtTax3;
	TQRLabel *txtTax4;
	TQRLabel *QRLabel11;
	void __fastcall pd_codePrint(TObject *sender, AnsiString &Value);
	void __fastcall DetailBand1BeforePrint(TQRCustomBand *Sender,
          bool &PrintBand);
private:	// User declarations
	CArray<BASE2COLDATA,BASE2COLDATA>m_lstPM;
	CArray<BASE2COLDATA,BASE2COLDATA>m_lstDD;
	CArray<BASE2COLDATA,BASE2COLDATA>m_lstRMB;

public:		// User declarations
	CStringArray m_lstID;
	TQRLabel *m_pFact[5];
  TQRLabel *m_pCard[5];
  TQRLabel *m_pDays[5];
  TQRLabel *m_pQuote[5];
  TQRLabel *m_pTail[5];
  TQRLabel *m_pHiggle[5];
  TQRLabel *m_pPM[5];
  TQRLabel *m_pDD[5];
  TQRLabel *m_pTax[5];

	__fastcall TPrnCompareFactoryForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPrnCompareFactoryForm *PrnCompareFactoryForm;
//---------------------------------------------------------------------------
#endif
