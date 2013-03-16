object ApFilePageForm: TApFilePageForm
  Left = 230
  Top = 156
  Width = 696
  Height = 480
  Caption = #24314#31435#35531#36092#21934#27284#34399#38913#34399
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 192
    Top = 16
    Width = 377
    Height = 32
    Caption = #35531#36092#21934#27284#34399#38913#34399#24314#27284'                   '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -29
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 24
    Top = 104
    Width = 80
    Height = 20
    Caption = #35531#36092#21934#34399#65306
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label3: TLabel
    Left = 24
    Top = 152
    Width = 88
    Height = 20
    Caption = #27284'          '#34399#65306
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label4: TLabel
    Left = 24
    Top = 208
    Width = 88
    Height = 20
    Caption = #38913'          '#30908#65306
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label5: TLabel
    Left = 210
    Top = 154
    Width = 37
    Height = 16
    Caption = 'GR-S-'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label6: TLabel
    Left = 28
    Top = 272
    Width = 84
    Height = 20
    Caption = #35498'         '#26126'    '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object btnQuery: TButton
    Left = 24
    Top = 376
    Width = 75
    Height = 25
    Caption = #26597'    '#35426
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    OnClick = btnQueryClick
  end
  object btnNew: TButton
    Left = 132
    Top = 376
    Width = 75
    Height = 25
    Caption = #26032'    '#22686
    TabOrder = 1
    OnClick = btnNewClick
  end
  object btnEdit: TButton
    Left = 249
    Top = 376
    Width = 75
    Height = 25
    Caption = #20462'    '#25913
    TabOrder = 2
    OnClick = btnEditClick
  end
  object btnMove: TButton
    Left = 366
    Top = 376
    Width = 75
    Height = 25
    Caption = #21034'     '#38500
    TabOrder = 3
    OnClick = btnMoveClick
  end
  object btnOK: TButton
    Left = 483
    Top = 376
    Width = 75
    Height = 25
    Caption = #30906'     '#35469
    TabOrder = 4
    OnClick = btnOKClick
  end
  object btnExit: TButton
    Left = 600
    Top = 376
    Width = 75
    Height = 25
    Caption = #36864'     '#20986
    TabOrder = 5
    OnClick = btnExitClick
  end
  object edtAPC: TEdit
    Left = 208
    Top = 104
    Width = 121
    Height = 21
    CharCase = ecUpperCase
    MaxLength = 7
    TabOrder = 6
    Text = 'EDITAPC'
  end
  object edtFC: TEdit
    Left = 249
    Top = 152
    Width = 80
    Height = 21
    CharCase = ecUpperCase
    MaxLength = 8
    TabOrder = 7
    Text = 'EDITFC'
  end
  object edtPC: TEdit
    Left = 208
    Top = 208
    Width = 121
    Height = 21
    MaxLength = 7
    TabOrder = 8
    Text = 'EDITPC'
  end
  object btnAPQuery: TButton
    Left = 344
    Top = 107
    Width = 69
    Height = 17
    Caption = #26597#30475#35531#36092#21934
    TabOrder = 9
    OnClick = btnAPQueryClick
  end
  object lstRem: TComboBox
    Left = 208
    Top = 272
    Width = 73
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 10
    Items.Strings = (
      ''
      #35036#21934
      #36864#21934
      #21462#28040)
  end
end
