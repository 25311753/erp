//---------------------------------------------------------------------------

#ifndef ContainerInfoH
#define ContainerInfoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TContainerInfoForm : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TEdit *edtCaseNo;
        TEdit *edtCaseCount;
        TComboBox *cbbCaseType;
        TButton *btnAppend;
        TEdit *edtContainerInfo;
        TLabel *Label4;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall btnAppendClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TContainerInfoForm(TComponent* Owner);
        AnsiString m_szContainerInfo;
};
//---------------------------------------------------------------------------
extern PACKAGE TContainerInfoForm *ContainerInfoForm;
//---------------------------------------------------------------------------
#endif
