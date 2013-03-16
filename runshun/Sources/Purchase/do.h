//---------------------------------------------------------------------------

#ifndef doH
#define doH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include "BaseCode/LfcArray_s.h"
#include <Buttons.hpp>
#include "trayicon.h"
#include <Mask.hpp>
//---------------------------------------------------------------------------
class CCidPage{
public:
        CCidPage(){
                init();
        }
        void init(){
                begin_cid = end_cid = page_num_detail = "";
        }
//private:        
        AnsiString begin_cid;
        AnsiString end_cid;
        AnsiString page_num_detail;     //total_page-curr_page
};
class TDoForm : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TEdit *edtCid;
        TEdit *edtDeclareid;
        TEdit *edtForwardingunit;
        TEdit *edtLicenseno;
        TEdit *edtCount;
        TComboBox *cbbPack;
        TEdit *edtLoadingid;
        TEdit *edtBoatno;
        TEdit *edtBoatorder;
        TComboBox *cbbTransport;
        TEdit *edtInnersupplyadd;
        TComboBox *cbbTrade;
        TComboBox *cbbZhengmian;
        TEdit *edtOutport;
        TComboBox *cbbBargain;
        TEdit *edtCarriage;
        TEdit *edtInsurance;
        TEdit *edtContractid;
        TEdit *edtNetweight;
        TEdit *edtSum;
        TEdit *edtAttachedoc;
        TEdit *edtManufacturer;
        TEdit *edtMarks;
        TEdit *edtInvoice;
        TListView *lstView;
        TButton *btnInputGoods;
        TEdit *edtMCode;
        TEdit *edtSpec;
        TEdit *edtFirstmeasunit;
        TEdit *edtSecondmeasunit;
        TEdit *edtUnitprice;
        TButton *btnAddDetail;
        TEdit *edtNetWeight1;
        TEdit *edtGrossWeight1;
        TEdit *edtCount1;
        TButton *btnMod;
        TComboBox *cbbExcharge;
        TEdit *edtCasecnt;
        TLabel *Label41;
        TLabel *Label42;
        TLabel *Label43;
        TLabel *Label44;
        TComboBox *cbbTargetCountry;
        TComboBox *cbbMname;
        TButton *btnPrnInvoice;
        TButton *btnPrnPackingList;
        TButton *btnPrnContact;
        TButton *btnPrnDeclare;
        TDateTimePicker *dtpValidDate;
        TButton *btnPrnAuth;
        TButton *btnModDetail;
        TButton *btnPrnOutBoat;
        TComboBox *cbbCurrency;
        TComboBox *cbbCurrencyId;
        TEdit *edtCount2nd;
        TButton *btnChangeStatus;
        TComboBox *cbbAssginPort;
        TEdit *edtMid1;
        TEdit *edtCdid;
        TPanel *Panel3;
        TPanel *Panel4;
        TPanel *Panel5;
        TPanel *Panel6;
        TPanel *Panel7;
        TPanel *Panel8;
        TPanel *Panel9;
        TPanel *Panel10;
        TPanel *Panel11;
        TPanel *Panel12;
        TPanel *Panel13;
        TPanel *Panel14;
        TPanel *Panel15;
        TPanel *Panel16;
        TPanel *Panel17;
        TPanel *Panel18;
        TPanel *Panel19;
        TPanel *Panel20;
        TPanel *Panel21;
        TPanel *Panel22;
        TPanel *Panel23;
        TPanel *Panel24;
        TPanel *Panel25;
        TPanel *Panel26;
        TPanel *Panel27;
        TPanel *Panel28;
        TPanel *Panel29;
        TPanel *Panel30;
        TPanel *Panel31;
        TPanel *Panel32;
        TPanel *Panel33;
        TPanel *Panel34;
        TPanel *Panel35;
        TPanel *Panel36;
        TPanel *Panel37;
        TPanel *Panel38;
        TPanel *Panel39;
        TPanel *Panel40;
        TPanel *Panel41;
        TPanel *Panel42;
        TPanel *Panel43;
        TPanel *Panel44;
        TLabel *Label1;
        TPanel *Panel45;
        TPanel *Panel46;
        TButton *btnQueryUp;
        TCheckBox *cbDoing;
        TButton *btnOK;
        TButton *btnCancel;
        TPanel *plDetail;
        TPanel *Panel2;
        TEdit *edtGrossWeight;
        TListView *lstViewContainer;
        TButton *btnDelDetail;
        TTrayIcon *TrayIcon1;
        TButton *Button1;
        TEdit *edtDebug;
        TButton *btnOkDetail;
        TButton *btnCancleDetail;
        TButton *btnWMZ;
        TButton *btnYSQRS;
        TButton *btnSCCK;
        TPanel *Panel47;
        TComboBox *cbbPkName;
        TButton *btnCIQ;
        TButton *btnQYCNS;
        TEdit *Edit1;
        TEdit *edtOperunitAddress;
        TEdit *edtOperunitTel;
        TEdit *edtSHAddress;
        TEdit *edtSHTel;
        TComboBox *cbbOperunit;
        TComboBox *cbbSH;
        TPanel *Panel48;
        TEdit *edtNo;
        TPanel *Panel49;
        TEdit *edtTotalPrice;
        void __fastcall btnInputGoodsClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall edtCidKeyPress(TObject *Sender, char &Key);
        void __fastcall btnModClick(TObject *Sender);
        void __fastcall btnAddDetailClick(TObject *Sender);
        void __fastcall cbbBargainChange(TObject *Sender);
        void __fastcall cbbMnameChange(TObject *Sender);
        void __fastcall cbbMnameSelect(TObject *Sender);
        void __fastcall btnPrnInvoiceClick(TObject *Sender);
        void __fastcall btnPrnPackingListClick(TObject *Sender);
        void __fastcall btnPrnContactClick(TObject *Sender);
        void __fastcall btnPrnDeclareClick(TObject *Sender);
        void __fastcall btnPrnAuthClick(TObject *Sender);
        void __fastcall btnPrnOutBoatClick(TObject *Sender);
        void __fastcall cbbCurrencyChange(TObject *Sender);
        void __fastcall lstViewSelectItem(TObject *Sender, TListItem *Item,
          bool Selected);
        void __fastcall btnModDetailClick(TObject *Sender);
        void __fastcall btnChangeStatusClick(TObject *Sender);
        void __fastcall cbbTargetCountryChange(TObject *Sender);
        void __fastcall btnQueryUpClick(TObject *Sender);
        void __fastcall btnCancelClick(TObject *Sender);
        void __fastcall btnOKClick(TObject *Sender);
        void __fastcall cbDoingMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall lstViewClick(TObject *Sender);
        void __fastcall btnDelDetailClick(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall btnOkDetailClick(TObject *Sender);
        void __fastcall btnCancleDetailClick(TObject *Sender);
        void __fastcall edtCount1Change(TObject *Sender);
        void __fastcall btnWMZClick(TObject *Sender);
        void __fastcall btnYSQRSClick(TObject *Sender);
        void __fastcall btnSCCKClick(TObject *Sender);
        void __fastcall btnCIQClick(TObject *Sender);
        void __fastcall btnQYCNSClick(TObject *Sender);
        void __fastcall cbbOperunitChange(TObject *Sender);
        void __fastcall cbbOperunitSelect(TObject *Sender);
        void __fastcall cbbSHSelect(TObject *Sender);
        void __fastcall cbbSHChange(TObject *Sender);
        void __fastcall edtNoChange(TObject *Sender);
        void __fastcall edtUnitpriceChange(TObject *Sender);
        void __fastcall edtTotalPriceChange(TObject *Sender);
private:	// User declarations
        CStringArray m_lstPack;
        CStringArray m_lstTrade;
        CStringArray m_lstZhengmian;
        CStringArray m_lstTransport;
        CStringArray m_lstBargain;
       CStringArray m_lstExcharge;
       bool m_isSelectMname;
       CStringArray m_lstMid1;
       CStringArray m_lstMCode;
       CStringArray m_lstSpec;
       CStringArray m_lstFirstmeasunit;
       CStringArray m_lstSecondmeasunit;
       CStringArray m_lstUnitprice;
       CStringArray m_lstWeightPercent;

       CString m_strContainerHead; //"第一个箱号 总柜数(总子柜数)" -- 总子柜数 = n(S)+2*n(L)
       CString m_strContainerTail;//"其他箱号 其他箱号 ..."
       //
       CString m_strSubConNoSealId1;
       CString m_strSubConNoSealId2;
       CString m_strSubConNoSealId3;
       CString m_strSubConNoSealId4;
       CString m_strSubConNoSealId5;
       CString m_strSubConNoSealId6;
       CString m_strSubConNoSealId7;
       CString m_strSubConNoSealId8;
       CString m_strSubConNoSealId9;
       CString m_strSubConNoSealId10;
       CString m_strConTypeUp;
       CString m_strConTypeDown;
       CString m_strConNum20DaXie;
       CString m_strConNum40DaXie;

       enum { EN_IDLE,/*EN_ADDNEW,*/EN_EDIT } m_enWorkState; //状态
         enum { EN_IDLE_D,EN_ADDNEW_D,EN_EDIT_D } m_enWorkStateDetail;
       bool isHasResult;
       CString m_strStatus;
       CString m_strContainerInfo;
       CString m_strEndCustDate;
       CString m_strShipAgent;
       CStringArray m_sa_sh;    //商号仓库，按单号末位取，保证不同

public:		// User declarations
        __fastcall TDoForm(TComponent* Owner);
        int g_cdid;
        void flushSum();
        void genContainerInfo4PrnDeclare(AnsiString c);
        void SplitSubContainer(AnsiString c);
        void CleanQryInput();
        void ResetCtrl();
        void ResetCtrlDetail();
        void Row2Editor();
        int ModHead();
        void flushContainer(AnsiString c);
        //clear input of detail
        void clearInputDetail();
        //rt 0:ok -1:fail
        int addDetail();
        int modDetail();
        //打印helper
        void prnDeclareMain(CString last_cdid, bool isHasSub);
        void prnDeclareSub(CString last_page_last_cdid);
        void prnContactMain(CString last_cdid, bool isHasSub);
        void prnContactSub(CString last_page_last_cdid);
        //打印[begin_cid, end_cid]之间的报关单分页，split_detail：总页数-本页序号, 最后一页才打印总价        
        void prnDeclare(AnsiString begin_cid, AnsiString end_cid, AnsiString split_detail, int page_ord, bool isTail=false);
//        void prnDeclareSub(AnsiString cdid);

 
};
//---------------------------------------------------------------------------
extern PACKAGE TDoForm *DoForm;
//---------------------------------------------------------------------------
#endif
