object GoodsForm: TGoodsForm
  Left = 230
  Top = 129
  Width = 870
  Height = 500
  Caption = #21830#21697#20449#24687
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 32
    Top = 48
    Width = 51
    Height = 13
    Caption = #21830#21697#21517#31216' '
  end
  object edtMname: TEdit
    Left = 88
    Top = 48
    Width = 121
    Height = 21
    TabOrder = 0
    Text = 'edtMname'
  end
  object btnQuery: TButton
    Left = 248
    Top = 40
    Width = 75
    Height = 25
    Caption = 'btnQuery'
    TabOrder = 1
    OnClick = btnQueryClick
  end
  object lstViewGoods: TListView
    Left = 40
    Top = 96
    Width = 753
    Height = 305
    Columns = <
      item
        Caption = #21830#21697#32534#21495
      end
      item
        Caption = #21830#21697#21517#31216
      end
      item
        Caption = #35268#26684#22411#21495
      end
      item
        Caption = #31532#19968#35745#37327#21333#20301
      end
      item
        Caption = #31532#20108#35745#37327#21333#20301
      end
      item
        Caption = #21333#20215
      end>
    RowSelect = True
    TabOrder = 2
    ViewStyle = vsReport
    OnSelectItem = lstViewGoodsSelectItem
  end
end
