//---------------------------------------------------------------------------

#ifndef GoodsH
#define GoodsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TGoodsForm : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TEdit *edtMname;
        TButton *btnQuery;
        TListView *lstViewGoods;
        void __fastcall btnQueryClick(TObject *Sender);
        void __fastcall lstViewGoodsSelectItem(TObject *Sender,
          TListItem *Item, bool Selected);
private:	// User declarations
//        CStringArray m_lstGoods;
public:		// User declarations
        __fastcall TGoodsForm(TComponent* Owner);
        AnsiString m_szMid;
        AnsiString m_szMname;
        AnsiString m_szSpec;
        AnsiString m_szFirstmeasunit;
        AnsiString m_szSecondmeasunit;
        AnsiString m_szUnitprice;

};
//---------------------------------------------------------------------------
extern PACKAGE TGoodsForm *GoodsForm;
//---------------------------------------------------------------------------
#endif
