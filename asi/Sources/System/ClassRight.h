//---------------------------------------------------------------------------

#ifndef ClassRightH
#define ClassRightH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TClassRightForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TComboBox *lstClass;
	TLabel *Label2;
	TListBox *lstGrpName;
	TLabel *Label3;
	TListView *lstData;
	TButton *btnDeny;
	TButton *btnRead;
	TButton *btnFull;
	TButton *btnAllDeny;
	TButton *btnAllRead;
	TButton *btnAllFull;
	TButton *btnExit;
	TButton *btnPriceRead;
        TImage *Image1;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall lstGrpNameClick(TObject *Sender);
	void __fastcall btnExitClick(TObject *Sender);
	void __fastcall lstClassClick(TObject *Sender);
	void __fastcall lstDataClick(TObject *Sender);
	void __fastcall btnDenyClick(TObject *Sender);
	void __fastcall btnReadClick(TObject *Sender);
	void __fastcall btnFullClick(TObject *Sender);
	void __fastcall btnAllDenyClick(TObject *Sender);
	void __fastcall btnAllReadClick(TObject *Sender);
	void __fastcall btnAllFullClick(TObject *Sender);
	void __fastcall btnPriceReadClick(TObject *Sender);
private:	// User declarations
	void ResetRightInf();
	void ResetCtrl();
  bool SetRight(int nClass,LPCSTR lpszMenu,int nRight);
  bool SetRight(TListItem *pItem,int nRight);

  CStringArray m_lstMenuID;
  CArray<int,int> m_lstClassID;

public:		// User declarations
	__fastcall TClassRightForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TClassRightForm *ClassRightForm;
//---------------------------------------------------------------------------
#endif
