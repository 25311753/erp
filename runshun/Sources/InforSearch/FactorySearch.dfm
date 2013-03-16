object FactorySearchForm: TFactorySearchForm
  Left = 543
  Top = 151
  Width = 480
  Height = 537
  Caption = #24288#21830#36039#26009#26597#35426
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = #26032#32048#26126#39636
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 128
    Top = 8
    Width = 198
    Height = 33
    Caption = #24288#21830#36039#26009#26597#35426
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
    Width = 457
    Height = 353
    Columns = <
      item
        Caption = #32232#34399
        Width = 80
      end
      item
        Caption = #31777#31281
        Width = 150
      end
      item
        Caption = #20840#31281
        Width = 200
      end>
    GridLines = True
    HideSelection = False
    ReadOnly = True
    RowSelect = True
    TabOrder = 0
    ViewStyle = vsReport
    OnClick = lstViewClick
    OnDblClick = lstViewDblClick
    OnSelectItem = lstViewSelectItem
  end
  object Panel1: TPanel
    Left = 8
    Top = 408
    Width = 457
    Height = 97
    TabOrder = 1
    object Label2: TLabel
      Left = 16
      Top = 8
      Width = 39
      Height = 13
      Caption = #32232#34399#65306
    end
    object Label3: TLabel
      Left = 104
      Top = 8
      Width = 39
      Height = 13
      Caption = #31777#31281#65306
    end
    object Label4: TLabel
      Left = 216
      Top = 8
      Width = 39
      Height = 13
      Caption = #20840#31281#65306
    end
    object txtTips: TLabel
      Left = 8
      Top = 80
      Width = 33
      Height = 13
      Caption = 'txtTips'
      Font.Charset = CHINESEBIG5_CHARSET
      Font.Color = clBlue
      Font.Height = -13
      Font.Name = #26032#32048#26126#39636
      Font.Style = []
      ParentFont = False
    end
    object edtID: TEdit
      Left = 16
      Top = 24
      Width = 81
      Height = 21
      CharCase = ecUpperCase
      MaxLength = 5
      TabOrder = 0
      Text = 'EDTID'
    end
    object edtShort: TEdit
      Left = 104
      Top = 24
      Width = 105
      Height = 21
      MaxLength = 20
      TabOrder = 1
      Text = 'edtShort'
    end
    object edtName: TEdit
      Left = 216
      Top = 24
      Width = 233
      Height = 21
      MaxLength = 40
      TabOrder = 2
      Text = 'edtName'
    end
    object btnQuery: TButton
      Left = 120
      Top = 48
      Width = 75
      Height = 25
      Caption = #37325#26032#26597#35426
      TabOrder = 3
      OnClick = btnQueryClick
    end
    object btnDetail: TButton
      Left = 200
      Top = 48
      Width = 75
      Height = 25
      Caption = #35443#32048#24773#27841
      TabOrder = 4
      OnClick = btnDetailClick
    end
    object btnExit: TButton
      Left = 368
      Top = 48
      Width = 75
      Height = 25
      Caption = #36864'    '#20986
      TabOrder = 5
      OnClick = btnExitClick
    end
    object btnOK: TButton
      Left = 288
      Top = 48
      Width = 75
      Height = 25
      Caption = #30906'     '#35469
      TabOrder = 6
      OnClick = btnOKClick
    end
  end
  object ApplicationEvents1: TApplicationEvents
    OnIdle = ApplicationEvents1Idle
    Left = 24
    Top = 16
  end
end
