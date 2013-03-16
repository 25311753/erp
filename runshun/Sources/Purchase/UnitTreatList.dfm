object UnitTreatListForm: TUnitTreatListForm
  Left = 210
  Top = 275
  Width = 800
  Height = 560
  Caption = #32113#36092#26448#26009#21015#34920
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = #32048#26126#39636
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 312
    Top = 8
    Width = 198
    Height = 33
    Caption = #32113#36092#26448#26009#21015#34920
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = #27161#26999#39636
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 8
    Top = 504
    Width = 42
    Height = 13
    Caption = #20844#21496#65306
  end
  object Label3: TLabel
    Left = 192
    Top = 504
    Width = 42
    Height = 13
    Caption = #22823#39006#65306
  end
  object Label4: TLabel
    Left = 16
    Top = 48
    Width = 378
    Height = 13
    Caption = #35498#26126#65306#20132#26399#24460#24118#8220'#'#8221#34920#31034#23578#26410#37319#36092#30906#35469#65292#24118#8220'*'#8221#26410#26371#35336#30906#35469
  end
  object lstView: TListView
    Left = 8
    Top = 64
    Width = 777
    Height = 425
    Columns = <
      item
        Caption = #21512#32004#32232#34399
        Width = 70
      end
      item
        Caption = #26448#26009#32232#34399
        Width = 120
      end
      item
        Caption = #21697#21517#35215#26684
        Width = 180
      end
      item
        Caption = #24288#21830#31777#31281
        Width = 100
      end
      item
        Caption = #24288#29260
        Width = 70
      end
      item
        Caption = #29983#25928#26085#26399
        Width = 70
      end
      item
        Caption = #21934#20301
        Width = 40
      end
      item
        Alignment = taRightJustify
        Caption = #21934#20729
      end
      item
        Caption = #20132#26399
        Width = 40
      end
      item
        Caption = #35330#36092#27425#25976
      end>
    GridLines = True
    HideSelection = False
    ReadOnly = True
    RowSelect = True
    TabOrder = 0
    ViewStyle = vsReport
  end
  object lstCorp: TComboBox
    Left = 56
    Top = 496
    Width = 113
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 1
  end
  object lstLarge: TComboBox
    Left = 240
    Top = 496
    Width = 113
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 2
  end
  object btnExit: TButton
    Left = 696
    Top = 496
    Width = 75
    Height = 25
    Caption = #36864'  '#20986
    TabOrder = 3
    OnClick = btnExitClick
  end
  object btnToExcel: TButton
    Left = 608
    Top = 496
    Width = 75
    Height = 25
    Caption = #36681'Excel'
    TabOrder = 4
    OnClick = btnToExcelClick
  end
  object btnPrint: TButton
    Left = 520
    Top = 496
    Width = 75
    Height = 25
    Caption = #21015'  '#21360
    TabOrder = 5
    OnClick = btnPrintClick
  end
  object btnQuery: TButton
    Left = 432
    Top = 496
    Width = 75
    Height = 25
    Caption = #26597'  '#35426
    TabOrder = 6
    OnClick = btnQueryClick
  end
end
