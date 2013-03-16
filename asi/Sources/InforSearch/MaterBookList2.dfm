object MaterBookListForm2: TMaterBookListForm2
  Left = 310
  Top = 78
  Width = 912
  Height = 566
  Caption = #37319#36092#32000#37636#27169#31946#25628#32034
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 256
    Top = 8
    Width = 272
    Height = 33
    AutoSize = False
    Caption = #37319#36092#32000#37636#27169#31946#25628#32034
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = #27161#26999#39636
    Font.Style = [fsBold]
    ParentFont = False
  end
  object lstView: TListView
    Left = 7
    Top = 61
    Width = 890
    Height = 401
    Columns = <
      item
        Caption = #35330#36092#26085
        Width = 70
      end
      item
        Caption = #35330#36092#21934#34399
        Width = 70
      end
      item
        Caption = #35531#36092#21934#34399
        Width = 70
      end
      item
        Caption = #24288#21830#21517#31281
        Width = 150
      end
      item
        Caption = #24288#29260
        Width = 150
      end
      item
        Alignment = taRightJustify
        Caption = #25976#37327
        Width = 70
      end
      item
        Alignment = taRightJustify
        Caption = #21934#20729
        Width = 70
      end
      item
        Caption = #21697#21517#35215#26684
        Width = 100
      end
      item
        Caption = #26448#26009#32232#34399
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
  object Panel1: TPanel
    Left = 8
    Top = 466
    Width = 889
    Height = 73
    BevelInner = bvLowered
    BevelOuter = bvLowered
    TabOrder = 1
    object Label2: TLabel
      Left = 196
      Top = 16
      Width = 60
      Height = 13
      Caption = #26448#26009#32232#34399#65306
    end
    object Label3: TLabel
      Left = 440
      Top = 16
      Width = 60
      Height = 13
      Caption = #26448#26009#21517#31281#65306
    end
    object txtName: TLabel
      Left = 499
      Top = 16
      Width = 383
      Height = 13
      AutoSize = False
      Caption = 'txtName'
    end
    object Label4: TLabel
      Left = 16
      Top = 18
      Width = 55
      Height = 13
      AutoSize = False
      Caption = #21697#21517#35215#26684
    end
    object Label5: TLabel
      Left = 16
      Top = 48
      Width = 24
      Height = 13
      Caption = #24288#29260
      Visible = False
    end
    object edtMNCode: TEdit
      Left = 268
      Top = 8
      Width = 137
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      MaxLength = 21
      TabOrder = 0
      Text = 'EDTMNCODE'
    end
    object btnPickup: TButton
      Left = 404
      Top = 8
      Width = 33
      Height = 22
      Caption = #26597#25214
      TabOrder = 1
      Visible = False
    end
    object btnExit: TButton
      Left = 696
      Top = 40
      Width = 75
      Height = 25
      Caption = #36864'    '#20986
      TabOrder = 2
      OnClick = btnExitClick
    end
    object btnToExcel: TButton
      Left = 597
      Top = 40
      Width = 75
      Height = 25
      Caption = #36681'Excel'
      TabOrder = 3
      OnClick = btnToExcelClick
    end
    object btnQuery: TButton
      Left = 269
      Top = 40
      Width = 75
      Height = 25
      Caption = #26597'    '#35426
      TabOrder = 4
      OnClick = btnQueryClick
    end
    object btnToBook: TButton
      Left = 432
      Top = 40
      Width = 75
      Height = 25
      Caption = #23519#30475#35330#36092#21934
      TabOrder = 5
      OnClick = btnToBookClick
    end
    object btnToPurchase: TButton
      Left = 514
      Top = 40
      Width = 75
      Height = 25
      Caption = #23519#30475#35531#36092#21934
      TabOrder = 6
      OnClick = btnToPurchaseClick
    end
    object btnPrint: TButton
      Left = 352
      Top = 40
      Width = 75
      Height = 25
      Caption = #21015#12288#21360
      TabOrder = 7
      OnClick = btnPrintClick
    end
    object edtDPName: TEdit
      Left = 72
      Top = 10
      Width = 121
      Height = 21
      TabOrder = 8
    end
    object edtFactCard: TEdit
      Left = 48
      Top = 40
      Width = 121
      Height = 21
      TabOrder = 9
      Visible = False
    end
  end
end
