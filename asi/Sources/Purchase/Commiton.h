//---------------------------------------------------------------------------

#ifndef CommitonH
#define CommitonH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TCommitonForm : public TForm
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
        __fastcall TCommitonForm(TComponent* Owner);
        void clearInput();
        void checkInput();

        void onAdd();
        void onMod();
};
//---------------------------------------------------------------------------
extern PACKAGE TCommitonForm *CommitonForm;
//---------------------------------------------------------------------------
#endif
