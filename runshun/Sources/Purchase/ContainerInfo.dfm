object ContainerInfoForm: TContainerInfoForm
  Left = 273
  Top = 226
  Width = 813
  Height = 182
  Caption = #36816#36755#24037#20855#36755#20837
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
    Left = 32
    Top = 40
    Width = 54
    Height = 13
    Caption = #38598#35013#31665#21495'  '
  end
  object Label2: TLabel
    Left = 240
    Top = 35
    Width = 24
    Height = 13
    Caption = #26588#25968
  end
  object Label3: TLabel
    Left = 424
    Top = 36
    Width = 24
    Height = 13
    Caption = #26588#22411
  end
  object Label4: TLabel
    Left = 37
    Top = 68
    Width = 24
    Height = 13
    Caption = #36755#20986
  end
  object edtCaseNo: TEdit
    Left = 88
    Top = 32
    Width = 121
    Height = 21
    TabOrder = 0
    Text = 'edtCaseNo'
  end
  object edtCaseCount: TEdit
    Left = 280
    Top = 31
    Width = 121
    Height = 21
    TabOrder = 1
    Text = 'edtCaseCount'
  end
  object cbbCaseType: TComboBox
    Left = 463
    Top = 32
    Width = 145
    Height = 21
    ItemHeight = 13
    TabOrder = 2
    Text = 'cbbCaseType'
    Items.Strings = (
      '20'#39
      '40'#39
      '60'#39
      '80'#39)
  end
  object btnAppend: TButton
    Left = 624
    Top = 33
    Width = 75
    Height = 25
    Caption = #36861#21152
    TabOrder = 3
    OnClick = btnAppendClick
  end
  object edtContainerInfo: TEdit
    Left = 88
    Top = 62
    Width = 409
    Height = 21
    TabOrder = 4
    Text = 'edtContainerInfo'
  end
end
