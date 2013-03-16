object AcceptNotPayListForm: TAcceptNotPayListForm
  Left = 619
  Top = 151
  Width = 810
  Height = 578
  Caption = #24050#25910#26009#26410#35531#27454#26126#32048
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
    Left = 280
    Top = 8
    Width = 264
    Height = 32
    Caption = #24050#25910#26009#26410#35531#27454#26126#32048
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = #27161#26999#39636
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 16
    Top = 504
    Width = 56
    Height = 13
    Caption = #20844#21496#21029#65306
  end
  object Label3: TLabel
    Left = 144
    Top = 504
    Width = 70
    Height = 13
    Caption = #25910#26009#24235#21029#65306
  end
  object Label4: TLabel
    Left = 320
    Top = 504
    Width = 42
    Height = 13
    Caption = #24288#21830#65306
  end
  object lstView: TListView
    Left = 8
    Top = 48
    Width = 777
    Height = 433
    Columns = <
      item
        Caption = #25910#26009#21934#34399
        Width = 70
      end
      item
        Caption = #25910#26009#26085#26399
        Width = 70
      end
      item
        Alignment = taRightJustify
        Caption = #25910#26009#25976#37327
        Width = 70
      end
      item
        Alignment = taRightJustify
        Caption = #21512#26684#25976#37327
        Width = 70
      end
      item
        Alignment = taRightJustify
        Caption = #37329#38989
        Width = 60
      end
      item
        Caption = #21697#21517#35215#26684
        Width = 200
      end
      item
        Caption = #24288#21830
        Width = 100
      end
      item
        Caption = #20844#21496#21029
        Width = 70
      end
      item
        Caption = #25910#26009#24235#21029
        Width = 70
      end>
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = #32048#26126#39636
    Font.Style = []
    GridLines = True
    HideSelection = False
    ReadOnly = True
    RowSelect = True
    ParentFont = False
    TabOrder = 0
    ViewStyle = vsReport
  end
  object btnExit: TButton
    Left = 712
    Top = 496
    Width = 75
    Height = 25
    Caption = #36864#12288#20986
    TabOrder = 1
    OnClick = btnExitClick
  end
  object btnToExcel: TButton
    Left = 632
    Top = 496
    Width = 75
    Height = 25
    Caption = #36681'Excel'
    TabOrder = 2
    OnClick = btnToExcelClick
  end
  object lstCorp: TComboBox
    Left = 64
    Top = 496
    Width = 73
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 3
  end
  object lstStore: TComboBox
    Left = 208
    Top = 496
    Width = 105
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 4
  end
  object btnQuery: TButton
    Left = 552
    Top = 496
    Width = 75
    Height = 25
    Caption = #26597#12288#35426
    TabOrder = 5
    OnClick = btnQueryClick
  end
  object lstFact: TComboBox
    Left = 360
    Top = 496
    Width = 137
    Height = 21
    ItemHeight = 13
    MaxLength = 60
    TabOrder = 6
    Text = 'lstFact'
    OnExit = lstFactExit
  end
  object btnFactPickup: TButton
    Left = 496
    Top = 496
    Width = 33
    Height = 19
    Caption = #26597#25214
    TabOrder = 7
    OnClick = btnFactPickupClick
  end
end
