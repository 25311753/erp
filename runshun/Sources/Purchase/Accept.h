//---------------------------------------------------------------------------

#ifndef AcceptH
#define AcceptH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "BaseCode/LfcArray_s.h"
#include <Mask.hpp>
#include "trayicon.h"
#include <ImgList.hpp>

//---------------------------------------------------------------------------
class TAcceptForm : public TForm
{
__published:	// IDE-managed Components
        TPanel *PanelUp;
        TListView *lstViewDown;
        TPanel *PanelUpQuery;
        TEdit *edtCid;
        TComboBox *cbbClient;
        TEdit *edtLading;
        TEdit *edtContainerInfo;
        TEdit *edtCustfree;
        TEdit *edtCliWorkid;
        TEdit *edtBeiZhu;
        TComboBox *cbbGoodsPerf;
        TComboBox *cbbBoatno;
        TComboBox *cbbBoatorder;
        TEdit *edtQryCid;
        TEdit *edtQryLading;
        TEdit *edtQryJZS;
        TComboBox *cbbQryStatus;
        TButton *btnQuery;
        TButton *btnAdd;
        TButton *btnMod;
        TButton *btnDel;
        TDateTimePicker *dtpEndDateYYYYMMDD;
        TDateTimePicker *dtpQryAcceptDate;
        TDateTimePicker *dtpQryAcceptDateEnd;
        TComboBox *cbbStatus;
        TDateTimePicker *dtpEndDateHHMM;
        TEdit *edtContainerNo;
        TComboBox *cbbContainerType;
        TButton *btnAddContainer;
        TListView *lstViewContainer;
        TButton *btnModContainer;
        TButton *btnDelContainer;
        TEdit *edtSealId;
        TButton *btnOK;
        TButton *btnCancel;
        TComboBox *cbbQryClient;
        TPanel *Panel1;
        TPanel *Panel2;
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
        TLabel *lbdebug;
        TPanel *Panel15;
        TPanel *Panel16;
        TPanel *Panel17;
        TPanel *Panel18;
        TPanel *Panel19;
        TPanel *Panel20;
        TPanel *Panel45;
        TPanel *Panel21;
        TCheckBox *cbIsQryByDate;
        TPanel *Panel22;
        TEdit *edtQryLicenseNo;
        TTrayIcon *TrayIcon1;
        TButton *Button1;
        TImageList *ImageList1;
        TPanel *Panel47;
        TComboBox *cbbShipAgent;
        TEdit *edtBoatNo;
        TEdit *edtBoatOrder;
        TPanel *Panel23;
        TComboBox *cbbGoodsPerfQry;
        TLabel *Label1;
        TLabel *lb_sum_cnt_con;
        TPanel *Panel24;
        TComboBox *cbbCustomsCharge;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall btnInputContanerinfoClick(TObject *Sender);
        void __fastcall btnAddClick(TObject *Sender);
        void __fastcall btnQueryClick(TObject *Sender);
        void __fastcall lstViewDownSelectItem(TObject *Sender,
          TListItem *Item, bool Selected);
        void __fastcall btnDelClick(TObject *Sender);
        void __fastcall btnModClick(TObject *Sender);
        void __fastcall btnAddContainerClick(TObject *Sender);
        void __fastcall lstViewContainerSelectItem(TObject *Sender,
          TListItem *Item, bool Selected);
        void __fastcall btnModContainerClick(TObject *Sender);
        void __fastcall btnDelContainerClick(TObject *Sender);
        void __fastcall edtQryCidKeyPress(TObject *Sender, char &Key);
        void __fastcall btnCancelClick(TObject *Sender);
        void __fastcall btnOKClick(TObject *Sender);
        void __fastcall cbbQryClientChange(TObject *Sender);
        void __fastcall cbbClientSelect(TObject *Sender);
        void __fastcall cbbQryClientSelect(TObject *Sender);
        void __fastcall cbbQryClient1Change(TObject *Sender);
        void __fastcall cbbQryClient1Select(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall cbbClientChange(TObject *Sender);
        void __fastcall cbbClientExit(TObject *Sender);

                       
private:	// User declarations
        CStringArray m_lstClient;
        CStringArray m_lstQryClient;
        CStringArray m_lstBoatno;
        CStringArray m_lstStatus;
        CStringArray m_lstBoatorder;
        CStringArray m_lstQryStatus;
        CStringArray m_lstGoodsperf;
        enum { EN_IDLE,EN_ADDNEW,EN_EDIT } m_enWorkState; //接单上区状态
public:		// User declarations
        __fastcall TAcceptForm(TComponent* Owner);
        CString TAcceptForm::GetContainerInfo();
        void flushContainer(AnsiString c);
        void ResetCtrl();
        //return: -1 失败，0 正确
        int add(TObject *Sender);
        void mod(TObject *Sender);
        void refreshMod();
        void refreshAdd();
        CString TAcceptForm::getFirstContainerNo(AnsiString c);
        CString getCustomsCharge(CString client);

        void  flushSum();
        bool isDupContainer(AnsiString c, AnsiString &dupCid);      //跨单重复柜号检查

};
//---------------------------------------------------------------------------
extern PACKAGE TAcceptForm *AcceptForm;
//---------------------------------------------------------------------------
#endif
