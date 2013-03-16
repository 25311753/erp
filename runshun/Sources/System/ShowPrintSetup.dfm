object ShowPrnSetupForm: TShowPrnSetupForm
  Left = 198
  Top = 106
  Width = 350
  Height = 241
  Caption = #21576#26680#34920#25171#21360#35373#32622
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = #32048#26126#39636
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 48
    Top = 16
    Width = 231
    Height = 33
    Caption = #21576#26680#34920#25171#21360#35373#32622
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = #27161#26999#39636
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 40
    Top = 80
    Width = 70
    Height = 13
    Caption = #19978#38913#37002#36317#65306
  end
  object Label3: TLabel
    Left = 40
    Top = 144
    Width = 70
    Height = 13
    Caption = #24038#38913#37002#36317#65306
  end
  object Label4: TLabel
    Left = 248
    Top = 80
    Width = 28
    Height = 13
    Caption = #27627#31859
  end
  object Label5: TLabel
    Left = 248
    Top = 144
    Width = 28
    Height = 13
    Caption = #27627#31859
  end
  object Label6: TLabel
    Left = 40
    Top = 112
    Width = 70
    Height = 13
    Caption = #19979#38913#37002#36317#65306
  end
  object Label7: TLabel
    Left = 248
    Top = 112
    Width = 28
    Height = 13
    Caption = #27627#31859
  end
  object edtTop: TEdit
    Left = 112
    Top = 72
    Width = 121
    Height = 21
    TabOrder = 0
    Text = 'edtTop'
  end
  object edtLeft: TEdit
    Left = 112
    Top = 136
    Width = 121
    Height = 21
    TabOrder = 1
    Text = 'edtLeft'
  end
  object btnOK: TButton
    Left = 48
    Top = 176
    Width = 75
    Height = 25
    Caption = #30906#12288#35469
    TabOrder = 2
    OnClick = btnOKClick
  end
  object btnCancel: TButton
    Left = 192
    Top = 176
    Width = 75
    Height = 25
    Caption = #21462#12288#28040
    TabOrder = 3
    OnClick = btnCancelClick
  end
  object edtBottom: TEdit
    Left = 112
    Top = 104
    Width = 121
    Height = 21
    TabOrder = 4
    Text = 'edtTop'
  end
end
