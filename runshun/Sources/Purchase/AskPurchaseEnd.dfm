object AskPurchaseEndForm: TAskPurchaseEndForm
  Left = 333
  Top = 165
  Width = 467
  Height = 442
  Caption = #35531#36092#21934#32080#26696
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = #26032#32048#26126#39636
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poScreenCenter
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object txtTitle: TLabel
    Left = 144
    Top = 8
    Width = 165
    Height = 33
    Caption = #35531#36092#21934#32080#26696
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = #27161#26999#39636
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 328
    Top = 170
    Width = 65
    Height = 13
    Caption = #35531#36092#21934#34399#65306
  end
  object Label1: TLabel
    Left = 328
    Top = 56
    Width = 91
    Height = 13
    Caption = #35531#36092#21934#21069#19977#20301#65306
  end
  object lstView: TListView
    Left = 8
    Top = 48
    Width = 305
    Height = 345
    Columns = <
      item
        Caption = #35531#36092#21934#34399
        Width = 70
      end
      item
        Caption = #32080#26696
        Width = 70
      end>
    GridLines = True
    HideSelection = False
    ReadOnly = True
    RowSelect = True
    TabOrder = 0
    ViewStyle = vsReport
    OnClick = lstViewClick
    OnSelectItem = lstViewSelectItem
  end
  object edtID: TEdit
    Left = 328
    Top = 186
    Width = 89
    Height = 21
    CharCase = ecUpperCase
    MaxLength = 8
    TabOrder = 1
    OnKeyDown = edtIDKeyDown
  end
  object btnRefresh: TButton
    Left = 328
    Top = 112
    Width = 89
    Height = 25
    Caption = #21047'    '#26032
    TabOrder = 2
    OnClick = btnRefreshClick
  end
  object btnAfm: TButton
    Left = 328
    Top = 271
    Width = 89
    Height = 25
    Caption = #32080'    '#26696
    TabOrder = 3
    OnClick = btnAfmClick
  end
  object btnDeafm: TButton
    Left = 328
    Top = 319
    Width = 89
    Height = 25
    Caption = #35299#38500#32080#26696
    TabOrder = 4
    OnClick = btnDeafmClick
  end
  object btnExit: TButton
    Left = 328
    Top = 367
    Width = 89
    Height = 25
    Caption = #36864'    '#20986
    TabOrder = 5
    OnClick = btnExitClick
  end
  object btnDetail: TButton
    Left = 328
    Top = 223
    Width = 89
    Height = 25
    Caption = #35443#32048#36039#26009
    TabOrder = 6
    OnClick = btnDetailClick
  end
  object edtH3ApC: TEdit
    Left = 328
    Top = 80
    Width = 88
    Height = 21
    CharCase = ecUpperCase
    MaxLength = 3
    TabOrder = 7
    OnKeyDown = edtH3ApCKeyDown
  end
end
