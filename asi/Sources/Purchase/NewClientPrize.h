//---------------------------------------------------------------------------

#ifndef NewClientPrizeH
#define NewClientPrizeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "trayicon.h"
//---------------------------------------------------------------------------
class TNewClientPrizeForm : public TForm
{
__published:	// IDE-managed Components
        TButton *btnQry;
        TListView *lvNewCliPrize;
        TPanel *plQuery;
        TPanel *Panel15;
        TComboBox *cbbClShortName;
        TEdit *Edit1;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *lbTotalNewCliCnt;
        TTrayIcon *TrayIcon1;
        TButton *Button1;
        TPanel *Panel20;
        TCheckBox *cbIsQryByDate;
        TDateTimePicker *dtpQryDateBegin;
        TDateTimePicker *dtpQryDateEnd;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall btnQryClick(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        int m_nAuthor;
        __fastcall TNewClientPrizeForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TNewClientPrizeForm *NewClientPrizeForm;
//---------------------------------------------------------------------------
#endif
