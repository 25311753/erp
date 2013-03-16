object DBSetupForm: TDBSetupForm
  Left = 271
  Top = 167
  Width = 442
  Height = 310
  Caption = #25976#25818#24235#35373#32622
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = #26032#32048#26126#39636
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poScreenCenter
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 136
    Top = 16
    Width = 160
    Height = 32
    Caption = #25976#25818#24235#35373#32622
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = #27161#26999#39636
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 128
    Top = 80
    Width = 37
    Height = 13
    Caption = 'ODBC:'
  end
  object Label3: TLabel
    Left = 128
    Top = 112
    Width = 39
    Height = 13
    Caption = #24115#34399#65306
  end
  object Label4: TLabel
    Left = 128
    Top = 144
    Width = 39
    Height = 13
    Caption = #23494#30908#65306
  end
  object Label5: TLabel
    Left = 104
    Top = 176
    Width = 65
    Height = 13
    Caption = #30906#35469#23494#30908#65306
  end
  object edtODBC: TEdit
    Left = 176
    Top = 72
    Width = 121
    Height = 21
    MaxLength = 40
    TabOrder = 0
    Text = 'edtODBC'
  end
  object edtUID: TEdit
    Left = 176
    Top = 104
    Width = 121
    Height = 21
    MaxLength = 40
    TabOrder = 1
    Text = 'edtUID'
  end
  object edtPwd: TEdit
    Left = 176
    Top = 136
    Width = 121
    Height = 21
    MaxLength = 20
    PasswordChar = '*'
    TabOrder = 2
    Text = 'edtPwd'
  end
  object edtPwd2: TEdit
    Left = 176
    Top = 168
    Width = 121
    Height = 21
    MaxLength = 20
    PasswordChar = '*'
    TabOrder = 3
    Text = 'edtPwd2'
  end
  object btnTest: TButton
    Left = 48
    Top = 216
    Width = 75
    Height = 25
    Caption = #28204'    '#35430
    TabOrder = 4
    OnClick = btnTestClick
  end
  object btnOK: TButton
    Left = 184
    Top = 216
    Width = 75
    Height = 25
    Caption = #30906'    '#35469
    TabOrder = 5
    OnClick = btnOKClick
  end
  object btnCancel: TButton
    Left = 320
    Top = 216
    Width = 75
    Height = 25
    Caption = #21462'    '#28040
    TabOrder = 6
    OnClick = btnCancelClick
  end
end
