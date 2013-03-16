//---------------------------------------------------------------------------

#ifndef AlarmSaleH
#define AlarmSaleH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TAlarmSaleForm : public TForm
{
__published:	// IDE-managed Components
        TListView *lvArrival;
        TListView *lvDelay;
        TListView *lvTask;
        void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TAlarmSaleForm(TComponent* Owner);
        int m_iOpType;
};
//---------------------------------------------------------------------------
extern PACKAGE TAlarmSaleForm *AlarmSaleForm;
//---------------------------------------------------------------------------
#endif
