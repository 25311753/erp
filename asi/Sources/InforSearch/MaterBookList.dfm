object MaterBookListForm: TMaterBookListForm
  Left = 263
  Top = 127
  Width = 800
  Height = 570
  Caption = #37319#36092#35352#37636#34920
  Color = clBtnFace
  Font.Charset = CHINESEBIG5_CHARSET
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
    Width = 165
    Height = 33
    Caption = #37319#36092#35352#37636#34920
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
        Caption = #21697#21517#35215#26684
        Width = 100
      end>
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = #26032#32048#26126#39636
    Font.Style = []
    GridLines = True
    HideSelection = False
    ReadOnly = True
    RowSelect = True
    ParentFont = False
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
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = #26032#32048#26126#39636
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    object Label2: TLabel
      Left = 8
      Top = 16
      Width = 65
      Height = 13
      Caption = #26448#26009#32232#34399#65306
    end
    object Label3: TLabel
      Left = 8
      Top = 40
      Width = 65
      Height = 13
      Caption = #26448#26009#21517#31281#65306
    end
    object txtName: TLabel
      Left = 80
      Top = 40
      Width = 41
      Height = 13
      Caption = 'txtName'
    end
    object Label4: TLabel
      Left = 264
      Top = 16
      Width = 52
      Height = 13
      Caption = #21697#21517#35215#26684
    end
    object Label5: TLabel
      Left = 448
      Top = 16
      Width = 26
      Height = 13
      Caption = #24288#29260
    end
    object edtMNCode: TEdit
      Left = 80
      Top = 8
      Width = 137
      Height = 21
      CharCase = ecUpperCase
      MaxLength = 21
      TabOrder = 0
      Text = 'EDTMNCODE'
    end
    object btnPickup: TButton
      Left = 216
      Top = 8
      Width = 33
      Height = 22
      Caption = #26597#25214
      TabOrder = 1
      OnClick = btnPickupClick
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
      Left = 613
      Top = 40
      Width = 75
      Height = 25
      Caption = #36681'Excel'
      TabOrder = 3
      OnClick = btnToExcelClick
    end
    object btnQuery: TButton
      Left = 613
      Top = 8
      Width = 75
      Height = 25
      Caption = #26597'    '#35426
      TabOrder = 4
      OnClick = btnQueryClick
    end
    object btnToBook: TButton
      Left = 448
      Top = 40
      Width = 75
      Height = 25
      Caption = #23519#30475#35330#36092#21934
      TabOrder = 5
      OnClick = btnToBookClick
    end
    object btnToPurchase: TButton
      Left = 530
      Top = 40
      Width = 75
      Height = 25
      Caption = #23519#30475#35531#36092#21934
      TabOrder = 6
      OnClick = btnToPurchaseClick
    end
    object btnPrint: TButton
      Left = 696
      Top = 8
      Width = 75
      Height = 25
      Caption = #21015#12288#21360
      TabOrder = 7
      OnClick = btnPrintClick
    end
    object edtDPName: TEdit
      Left = 320
      Top = 8
      Width = 121
      Height = 21
      TabOrder = 8
    end
    object edtFactCard: TEdit
      Left = 480
      Top = 8
      Width = 121
      Height = 21
      TabOrder = 9
    end
  end
end
