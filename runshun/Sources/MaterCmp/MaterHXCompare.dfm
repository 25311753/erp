object MaterHXCompareForm: TMaterHXCompareForm
  Left = 321
  Top = 105
  Width = 800
  Height = 546
  Caption = #23439#20449#25216#34899#20195#34399#33287#26448#26009#32232#34399#23565#29031#34920
  Color = clBtnFace
  Font.Charset = CHINESEBIG5_CHARSET
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
    Left = 176
    Top = 8
    Width = 462
    Height = 33
    Caption = #23439#20449#25216#34899#20195#34399#33287#26448#26009#32232#34399#23565#29031#34920
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
    Height = 321
    Columns = <
      item
        Caption = #25216#34899#20195#34399
        Width = 70
      end
      item
        Caption = #39006#22411#21517#31281
        Width = 150
      end
      item
        Caption = #26448#26009#32232#34399
        Width = 200
      end
      item
        Caption = #21697#21517#35215#26684
        Width = 300
      end>
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = #32048#26126#39636
    Font.Style = []
    GridLines = True
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
    Top = 376
    Width = 777
    Height = 137
    BevelOuter = bvLowered
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = #32048#26126#39636
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    object Label2: TLabel
      Left = 16
      Top = 32
      Width = 70
      Height = 13
      Caption = #25216#34899#20195#34399#65306
    end
    object Label3: TLabel
      Left = 304
      Top = 32
      Width = 70
      Height = 13
      Caption = #39006#22411#21517#31281#65306
    end
    object Label4: TLabel
      Left = 16
      Top = 64
      Width = 70
      Height = 13
      Caption = #26448#26009#32232#34399#65306
    end
    object Label5: TLabel
      Left = 304
      Top = 64
      Width = 70
      Height = 13
      Caption = #21697#21517#35215#26684#65306
    end
    object edtTech: TEdit
      Left = 88
      Top = 24
      Width = 169
      Height = 21
      CharCase = ecUpperCase
      MaxLength = 12
      TabOrder = 0
      Text = 'EDTTECH'
    end
    object edtType: TEdit
      Left = 376
      Top = 24
      Width = 385
      Height = 21
      TabOrder = 1
      Text = 'edtType'
    end
    object edtMater: TEdit
      Left = 88
      Top = 56
      Width = 169
      Height = 21
      CharCase = ecUpperCase
      MaxLength = 21
      TabOrder = 2
      Text = 'EDTMATER'
      OnExit = edtMaterExit
      OnKeyUp = edtMaterKeyUp
    end
    object btnPickup: TButton
      Left = 256
      Top = 57
      Width = 33
      Height = 20
      Caption = #26597#25214
      TabOrder = 3
      OnClick = btnPickupClick
    end
    object edtSpec: TEdit
      Left = 376
      Top = 56
      Width = 385
      Height = 21
      TabOrder = 4
      Text = 'edtSpec'
    end
    object btnEdit: TButton
      Left = 255
      Top = 100
      Width = 75
      Height = 25
      Caption = #20462#12288#25913
      TabOrder = 5
      OnClick = btnEditClick
    end
    object btnPrint: TButton
      Left = 359
      Top = 100
      Width = 75
      Height = 25
      Caption = #21015#12288#21360
      TabOrder = 6
      OnClick = btnPrintClick
    end
    object btnExit: TButton
      Left = 559
      Top = 100
      Width = 75
      Height = 25
      Caption = #36864#12288#20986
      TabOrder = 7
      OnClick = btnExitClick
    end
    object btnRefresh: TButton
      Left = 151
      Top = 100
      Width = 75
      Height = 25
      Caption = #21047#12288#26032
      TabOrder = 8
      OnClick = btnRefreshClick
    end
    object btnOK: TButton
      Left = 463
      Top = 100
      Width = 75
      Height = 25
      Caption = #30906#12288#35469
      TabOrder = 9
      OnClick = btnOKClick
    end
  end
end
