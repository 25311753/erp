object Book4TimesForm: TBook4TimesForm
  Left = 205
  Top = 132
  Width = 800
  Height = 560
  Caption = #35330#36092#36229#36942'4'#27425#21295#32317#34920
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = #32048#26126#39636
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poScreenCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 280
    Top = 8
    Width = 281
    Height = 33
    Caption = #35330#36092#36229#36942'4'#27425#21295#32317#34920
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = #27161#26999#39636
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 8
    Top = 480
    Width = 98
    Height = 13
    Caption = #35330#36092#38283#22987#26085#26399#65306
  end
  object Label3: TLabel
    Left = 128
    Top = 480
    Width = 98
    Height = 13
    Caption = #35330#36092#25130#27490#26085#26399#65306
  end
  object Label4: TLabel
    Left = 240
    Top = 480
    Width = 56
    Height = 13
    Caption = #20844#21496#21029#65306
  end
  object Label5: TLabel
    Left = 336
    Top = 480
    Width = 70
    Height = 13
    Caption = #37319#36092#37096#38272#65306
  end
  object Label6: TLabel
    Left = 456
    Top = 480
    Width = 42
    Height = 13
    Caption = #27425#25976#65306
  end
  object lstView: TListView
    Left = 8
    Top = 48
    Width = 777
    Height = 417
    Columns = <
      item
        Caption = #26448#26009#32232#34399
        Width = 150
      end
      item
        Caption = #21697#21517#35215#26684
        Width = 150
      end
      item
        Caption = #35330#36092#21934#34399
        Width = 70
      end
      item
        Caption = #35330#36092#26085#26399
        Width = 70
      end
      item
        Caption = #21934#20729
        Width = 70
      end
      item
        Caption = #24288#21830
        Width = 100
      end
      item
        Caption = #20844#21496
      end
      item
        Caption = #37319#36092#37096#38272
        Width = 70
      end>
    GridLines = True
    HideSelection = False
    ReadOnly = True
    RowSelect = True
    TabOrder = 0
    ViewStyle = vsReport
  end
  object edtDate0: TEdit
    Left = 16
    Top = 496
    Width = 89
    Height = 21
    TabOrder = 1
    Text = 'edtDate0'
  end
  object edtDate1: TEdit
    Left = 120
    Top = 496
    Width = 105
    Height = 21
    TabOrder = 2
    Text = 'edtDate1'
  end
  object btnQuery: TButton
    Left = 544
    Top = 493
    Width = 75
    Height = 25
    Caption = #26597#12288#35426
    TabOrder = 3
    OnClick = btnQueryClick
  end
  object btnToExcel: TButton
    Left = 624
    Top = 493
    Width = 75
    Height = 25
    Caption = #36681'Excel'
    TabOrder = 4
    OnClick = btnToExcelClick
  end
  object btnExit: TButton
    Left = 704
    Top = 493
    Width = 75
    Height = 25
    Caption = #36864#12288#20986
    TabOrder = 5
    OnClick = btnExitClick
  end
  object lstCorp: TComboBox
    Left = 240
    Top = 496
    Width = 73
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 6
  end
  object lstDepart: TComboBox
    Left = 328
    Top = 496
    Width = 113
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 7
  end
  object edtTimes: TEdit
    Left = 448
    Top = 496
    Width = 49
    Height = 21
    MaxLength = 2
    TabOrder = 8
    Text = 'edtTimes'
  end
end
