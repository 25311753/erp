//---------------------------------------------------------------------------

#ifndef OpQryInOutH
#define OpQryInOutH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TOpQryInOutForm : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TListView *lvInDetail;
        TLabel *Label2;
        TListView *lvOutDetail;
private:	// User declarations
public:		// User declarations
        __fastcall TOpQryInOutForm(TComponent* Owner);
        void show(AnsiString oid);

};
//---------------------------------------------------------------------------
extern PACKAGE TOpQryInOutForm *OpQryInOutForm;
//---------------------------------------------------------------------------
#endif
