object XkCSSZForm: TXkCSSZForm
  Left = -841
  Top = 278
  Width = 451
  Height = 471
  Caption = #26032#23458#31649#29702'-'#21442#25968#35774#32622
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
  object plInput: TPanel
    Left = 0
    Top = 24
    Width = 433
    Height = 27
    TabOrder = 0
    object Panel2: TPanel
      Left = 131
      Top = 3
      Width = 60
      Height = 22
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #38144#21806
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 0
    end
    object cbbOpCodeSl: TComboBox
      Left = 193
      Top = 5
      Width = 121
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 1
    end
    object dtpYearMonth: TDateTimePicker
      Left = 64
      Top = 4
      Width = 65
      Height = 21
      CalAlignment = dtaLeft
      Date = 41214.9584656366
      Time = 41214.9584656366
      DateFormat = dfShort
      DateMode = dmComboBox
      ImeName = #35895#27468#25340#38899#36755#20837#27861' 2'
      Kind = dtkDate
      ParseInput = False
      TabOrder = 2
    end
    object Panel1: TPanel
      Left = 3
      Top = 3
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #26376#20221
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 3
    end
    object Panel10: TPanel
      Left = 311
      Top = 4
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #26032#23458#20219#21153
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 4
    end
    object edtCntNewCli: TEdit
      Left = 371
      Top = 4
      Width = 59
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 5
    end
  end
  object lvXkCSSZ: TListView
    Left = 1
    Top = 52
    Width = 432
    Height = 349
    Columns = <
      item
        Caption = #22995#21517
        Width = 100
      end
      item
        Caption = #26376#24230
        Width = 100
      end
      item
        Caption = #26032#23458#20219#21153
        Width = 100
      end>
    FlatScrollBars = True
    GridLines = True
    ReadOnly = True
    RowSelect = True
    TabOrder = 1
    ViewStyle = vsReport
    OnSelectItem = lvXkCSSZSelectItem
  end
  object btnAdd: TButton
    Left = 1
    Top = 0
    Width = 75
    Height = 25
    Caption = #28155#21152
    TabOrder = 2
    OnClick = btnAddClick
  end
  object btnMod: TButton
    Left = 74
    Top = 0
    Width = 75
    Height = 25
    Caption = #20462#25913
    TabOrder = 3
    OnClick = btnModClick
  end
  object btnDel: TButton
    Left = 148
    Top = 0
    Width = 75
    Height = 25
    Caption = #21024#38500
    TabOrder = 4
    OnClick = btnDelClick
  end
  object btnOK: TButton
    Left = 232
    Top = 0
    Width = 63
    Height = 25
    Caption = #30830#23450
    TabOrder = 5
    OnClick = btnOKClick
  end
  object btnCancel: TButton
    Left = 295
    Top = 0
    Width = 63
    Height = 25
    Caption = #21462#28040
    TabOrder = 6
    OnClick = btnCancelClick
  end
  object edtDebug: TEdit
    Left = 368
    Top = 0
    Width = 53
    Height = 21
    TabOrder = 7
    Text = 'edtDebug'
    Visible = False
  end
end
