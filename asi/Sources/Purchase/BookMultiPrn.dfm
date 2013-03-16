object BookMultiPrnForm: TBookMultiPrnForm
  Left = 360
  Top = 77
  Width = 800
  Height = 560
  Caption = #35330#36092#21934#21015#21360
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = #32048#26126#39636
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poScreenCenter
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 88
    Top = 137
    Width = 70
    Height = 13
    Caption = #35330#36092#24288#21830#65306
  end
  object Label2: TLabel
    Left = 88
    Top = 62
    Width = 70
    Height = 13
    Caption = #38283#22987#26085#26399#65306
  end
  object Label4: TLabel
    Left = 298
    Top = 7
    Width = 165
    Height = 33
    Caption = #35330#36092#21934#21015#21360
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = #27161#26999#39636
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label3: TLabel
    Left = 88
    Top = 104
    Width = 70
    Height = 13
    Caption = #37319#36092#32147#36774#65306
  end
  object Label5: TLabel
    Left = 376
    Top = 102
    Width = 70
    Height = 13
    Caption = #35531#36092#20844#21496#65306
  end
  object Label6: TLabel
    Left = 376
    Top = 62
    Width = 70
    Height = 13
    Caption = #25130#27490#26085#26399#65306
  end
  object Label7: TLabel
    Left = 88
    Top = 171
    Width = 56
    Height = 13
    Caption = #22806#36092#24288#21830
  end
  object lstView: TListView
    Left = 8
    Top = 200
    Width = 777
    Height = 265
    Columns = <
      item
        Caption = #35330#36092#21934#34399
        Width = 70
      end
      item
        Caption = #35531#36092#21934#34399
        Width = 70
      end
      item
        Caption = #26448#26009#32232#34399
        Width = 120
      end
      item
        Caption = #21697#21517#35215#26684
        Width = 150
      end
      item
        Caption = #24288#29260
        Width = 80
      end
      item
        Caption = #21934#20301
        Width = 40
      end
      item
        Alignment = taRightJustify
        Caption = #25976#37327
        Width = 40
      end
      item
        Caption = #21934#20729
      end
      item
        Caption = #20132#26399
        Width = 40
      end
      item
        Caption = #21015#21360#26085#26399
        Width = 100
      end>
    GridLines = True
    MultiSelect = True
    ReadOnly = True
    RowSelect = True
    TabOrder = 4
    ViewStyle = vsReport
    OnDblClick = lstViewDblClick
  end
  object lstFactory: TComboBox
    Left = 160
    Top = 132
    Width = 369
    Height = 21
    ItemHeight = 13
    MaxLength = 10
    TabOrder = 0
    Text = 'lstFactory'
    OnExit = lstFactoryExit
  end
  object edtDate0: TEdit
    Left = 160
    Top = 54
    Width = 121
    Height = 21
    MaxLength = 8
    TabOrder = 1
    Text = 'edtDate0'
  end
  object btnQuery: TButton
    Left = 600
    Top = 59
    Width = 73
    Height = 22
    Caption = #26597#12288#35426
    TabOrder = 3
    OnClick = btnQueryClick
  end
  object btnPrint: TButton
    Left = 552
    Top = 480
    Width = 75
    Height = 33
    Caption = #21015#12288#21360
    TabOrder = 5
    OnClick = btnPrintClick
  end
  object btnExit: TButton
    Left = 672
    Top = 480
    Width = 75
    Height = 33
    Caption = #36864#12288#20986
    TabOrder = 6
    OnClick = btnExitClick
  end
  object btnDetail: TButton
    Left = 424
    Top = 480
    Width = 81
    Height = 33
    Caption = #35330#36092#21934#20839#23481
    TabOrder = 7
    OnClick = btnDetailClick
  end
  object lstStockHandle: TComboBox
    Left = 160
    Top = 99
    Width = 121
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 2
    OnExit = lstStockHandleExit
  end
  object lstCorp: TComboBox
    Left = 448
    Top = 99
    Width = 121
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 8
    OnExit = lstCorpExit
  end
  object btnPickup: TButton
    Left = 528
    Top = 132
    Width = 41
    Height = 20
    Caption = #26597#25214
    TabOrder = 9
    OnClick = btnPickupClick
  end
  object edtDate1: TEdit
    Left = 448
    Top = 59
    Width = 121
    Height = 21
    MaxLength = 8
    TabOrder = 10
    Text = 'edtDate0'
  end
  object ComboBox1: TComboBox
    Left = 160
    Top = 168
    Width = 369
    Height = 21
    ItemHeight = 13
    TabOrder = 11
  end
end
