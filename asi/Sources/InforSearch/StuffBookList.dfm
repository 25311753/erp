object StuffBookListForm: TStuffBookListForm
  Left = 213
  Top = 140
  Width = 800
  Height = 564
  Caption = #21407#26009#37319#36092#35352#37636#34920
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = #26032#32048#26126#39636
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poScreenCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 320
    Top = 8
    Width = 231
    Height = 33
    Caption = #21407#26009#37319#36092#35352#37636#34920
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = #27161#26999#39636
    Font.Style = [fsBold]
    ParentFont = False
  end
  object lstView: TListView
    Left = 8
    Top = 48
    Width = 777
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
        Caption = #26448#26009#32232#34399
        Width = 120
      end
      item
        Caption = #21697#21517#35215#26684
        Width = 150
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
    Top = 456
    Width = 777
    Height = 73
    TabOrder = 1
    object Label2: TLabel
      Left = 8
      Top = 16
      Width = 65
      Height = 13
      Caption = #38283#22987#26085#26399#65306
    end
    object Label3: TLabel
      Left = 160
      Top = 16
      Width = 65
      Height = 13
      Caption = #25130#27490#26085#26399#65306
    end
    object Label4: TLabel
      Left = 320
      Top = 16
      Width = 65
      Height = 13
      Caption = #26448#26009#32232#34399#65306
    end
    object Label5: TLabel
      Left = 560
      Top = 16
      Width = 65
      Height = 13
      Caption = #21697#21517#35215#26684#65306
    end
    object Label6: TLabel
      Left = 8
      Top = 48
      Width = 39
      Height = 13
      Caption = #24288#29260#65306
    end
    object btnExit: TButton
      Left = 703
      Top = 40
      Width = 67
      Height = 25
      Caption = #36864'    '#20986
      TabOrder = 0
      OnClick = btnExitClick
    end
    object btnToExcel: TButton
      Left = 624
      Top = 40
      Width = 67
      Height = 25
      Caption = #36681'Excel'
      TabOrder = 1
      OnClick = btnToExcelClick
    end
    object btnQuery: TButton
      Left = 545
      Top = 40
      Width = 67
      Height = 25
      Caption = #26597'    '#35426
      TabOrder = 2
      OnClick = btnQueryClick
    end
    object btnToBook: TButton
      Left = 291
      Top = 40
      Width = 75
      Height = 25
      Caption = #23519#30475#35330#36092#21934
      TabOrder = 3
      OnClick = btnToBookClick
    end
    object btnToPurchase: TButton
      Left = 379
      Top = 40
      Width = 75
      Height = 25
      Caption = #23519#30475#35531#36092#21934
      TabOrder = 4
      OnClick = btnToPurchaseClick
    end
    object btnPrint: TButton
      Left = 466
      Top = 40
      Width = 67
      Height = 25
      Caption = #21015#12288#21360
      TabOrder = 5
      OnClick = btnPrintClick
    end
    object edtDate0: TEdit
      Left = 72
      Top = 8
      Width = 81
      Height = 21
      MaxLength = 8
      TabOrder = 6
      Text = 'edtDate0'
    end
    object edtDate1: TEdit
      Left = 224
      Top = 8
      Width = 81
      Height = 21
      MaxLength = 8
      TabOrder = 7
      Text = 'edtDate1'
    end
    object edtMNCode: TEdit
      Left = 384
      Top = 8
      Width = 137
      Height = 21
      CharCase = ecUpperCase
      MaxLength = 21
      TabOrder = 8
      Text = 'EDTMNCODE'
    end
    object btnPickup: TButton
      Left = 520
      Top = 8
      Width = 33
      Height = 22
      Caption = #26597#25214
      TabOrder = 9
      OnClick = btnPickupClick
    end
    object edtDPName: TEdit
      Left = 624
      Top = 8
      Width = 145
      Height = 21
      TabOrder = 10
    end
    object edtFactCard: TEdit
      Left = 43
      Top = 40
      Width = 153
      Height = 21
      TabOrder = 11
    end
  end
end
