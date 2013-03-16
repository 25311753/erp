//---------------------------------------------------------------------------

#ifndef AssignmentH
#define AssignmentH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "LfcString.h"
#include <map>
//---------------------------------------------------------------------------
class TAssignmentForm : public TForm
{
__published:	// IDE-managed Components
        TListView *lstViewSH;
        TListView *lstViewCYZ;
        TListView *lstViewYFX;
        TButton *btnCheck;
        TButton *btnPass;
        TButton *btnPass1;
        TButton *btnYJCZ;
        TListView *lstViewYJCZ;
        TPanel *Panel1;
        TEdit *edtCid;
        TEdit *edtLadingId;
        TComboBox *cbbStatus;
        TButton *btnQuery;
        TDateTimePicker *dtpAcceptDateBegin;
        TDateTimePicker *dtpAcceptDateEnd;
        TComboBox *cbbTransport;
        TListView *lstViewDZCLZ;
        TButton *btnSH;
        TEdit *edtOperUnit;
        TEdit *edtContainerNo;
        TPanel *Panel3;
        TPanel *Panel5;
        TPanel *Panel9;
        TPanel *Panel15;
        TPanel *Panel19;
        TPanel *Panel20;
        TCheckBox *cbIsQryByDate;
        TPanel *Panel2;
        TButton *btnSH2DZCLZ;
        TButton *btnYFX2SH;
        TButton *btnYJCZ2YFX;
        TButton *btnYFX2CYZ;
        TButton *btnCYZ2SH;
        TPanel *plAssgin;
        TPanel *plQry;
        TPanel *Panel4;
        TPanel *Panel18;
        TPanel *Panel6;
        TPanel *Panel17;
        TEdit *edtQryCid;
        TComboBox *cbbQryStatus;
        TEdit *edtQryJZS;
        TEdit *edtQryLading;
        TPanel *Panel7;
        TDateTimePicker *dtpQryAcceptDate;
        TDateTimePicker *dtpQryAcceptDateEnd;
        TListView *lstViewContainer;
        TListView *lstView;
        TButton *btnQry;
        TCheckBox *cbIsQryByDateUp;
        TPanel *Panel45;
        TListView *lstViewYJH;
        TButton *btnYJH;
        TButton *btnYJH2YJCZ;
        TListView *lstViewYJD;
        TButton *btnDZCLZ;
        TButton *btnDZCLZ2YJD;
        TDateTimePicker *dtpPassDate;
        TButton *btnFlowTable;
        TPanel *Panel47;
        TComboBox *cbbShipAgent;
        TEdit *edtDebug;
        void __fastcall btnQueryClick(TObject *Sender);
        void __fastcall btnCheckClick(TObject *Sender);
        void __fastcall btnPassClick(TObject *Sender);
        void __fastcall btnPass1Click(TObject *Sender);
        void __fastcall btnYJCZClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall btnSHClick(TObject *Sender);
        void __fastcall btnSH2DZCLZClick(TObject *Sender);
        void __fastcall btnYFX2SHClick(TObject *Sender);
        void __fastcall btnYJCZ2YFXClick(TObject *Sender);
        void __fastcall btnYFX2CYZClick(TObject *Sender);
        void __fastcall btnCYZ2SHClick(TObject *Sender);
        void __fastcall btnQryClick(TObject *Sender);
        void __fastcall lstViewSelectItem(TObject *Sender, TListItem *Item,
          bool Selected);
        void __fastcall edtQryCidKeyPress(TObject *Sender, char &Key);
        void __fastcall edtCidKeyPress(TObject *Sender, char &Key);
        void __fastcall btnYJHClick(TObject *Sender);
        void __fastcall btnYJH2YJCZClick(TObject *Sender);
        void __fastcall btnDZCLZClick(TObject *Sender);
        void __fastcall btnDZCLZ2YJDClick(TObject *Sender);
        void __fastcall btnFlowTableClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TAssignmentForm(TComponent* Owner);
        void Load2ListView(TListView **pLstView, LPCSTR cid);
        void ChangeStatus(TListView **pOldLstView, TListView **pNewLstView, AnsiString newStatus);
        void ChangeStatusSelected(TListView **pOldLstView, TListView **pNewLstView, AnsiString newStatus);
        void ChangeStatusSelectedPass(TListView **pOldLstView, TListView **pNewLstView, AnsiString newStatus);
       void flushContainer(AnsiString c);
//        std::map<CString, std::pair<CString, CString> > genContainerInfoDetail(AnsiString c);       
};
//---------------------------------------------------------------------------
extern PACKAGE TAssignmentForm *AssignmentForm;
//---------------------------------------------------------------------------
#endif
