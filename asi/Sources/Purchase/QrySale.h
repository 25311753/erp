//---------------------------------------------------------------------------

#ifndef QrySaleH
#define QrySaleH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include "trayicon.h"
//---------------------------------------------------------------------------
class TQrySaleForm : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel7;
        TButton *btnQryYear;
        TPanel *Panel9;
        TComboBox *cbbYear;
        TPanel *Panel1;
        TComboBox *cbbMonth;
        TPanel *Panel3;
        TComboBox *cbbClShortName;
        TLabel *Label1;
        TLabel *lbTotalPrize;
        TListView *lvTask;
        TEdit *Edit1;
        TPanel *Panel21;
        TLabel *Label2;
        TLabel *Label3;
        TPanel *Panel2;
        TBevel *Bevel1;
        TLabel *Label4;
        TListView *lvKB;
        TTrayIcon *TrayIcon1;
        TButton *Button1;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall btnQryYearClick(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TQrySaleForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TQrySaleForm *QrySaleForm;
//---------------------------------------------------------------------------
#endif
