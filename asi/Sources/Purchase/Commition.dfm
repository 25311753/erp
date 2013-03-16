object CommitionForm: TCommitionForm
  Left = 247
  Top = 192
  Width = 1101
  Height = 639
  Caption = #20219#21153#31649#29702
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 304
    Width = 105
    Height = 13
    Caption = #20840#24180#32479#35745'             '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object plInput: TPanel
    Left = 2
    Top = 32
    Width = 1012
    Height = 27
    TabOrder = 0
    object Label2: TLabel
      Left = 736
      Top = 8
      Width = 14
      Height = 13
      Caption = '%  '
    end
    object Panel4: TPanel
      Left = 864
      Top = 3
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #21457#25918#26102#38388
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 0
    end
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
      TabOrder = 1
    end
    object cbbOpCodeSl: TComboBox
      Left = 193
      Top = 5
      Width = 121
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 2
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
      TabOrder = 3
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
      TabOrder = 4
    end
    object Panel3: TPanel
      Left = 313
      Top = 3
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #20219#21153#22522#25968
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 5
    end
    object edtBusiVolume: TEdit
      Left = 373
      Top = 3
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 6
      Text = 'edtBusiVolume'
    end
    object dtpGrantDate: TDateTimePicker
      Left = 926
      Top = 3
      Width = 85
      Height = 21
      CalAlignment = dtaLeft
      Date = 41041.9650162037
      Time = 41041.9650162037
      DateFormat = dfShort
      DateMode = dmComboBox
      Enabled = False
      ImeName = #35895#27468#25340#38899#36755#20837#27861' 2'
      Kind = dtkDate
      ParseInput = False
      TabOrder = 7
    end
    object Panel6: TPanel
      Left = 760
      Top = 3
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #21457#25918#23457#25209
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 8
    end
    object cbbPassed: TComboBox
      Left = 822
      Top = 3
      Width = 43
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 9
      Items.Strings = (
        #21542
        #26159)
    end
    object Panel10: TPanel
      Left = 495
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
      TabOrder = 10
    end
    object edtCntNewCli: TEdit
      Left = 555
      Top = 4
      Width = 59
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 11
      Text = 'edtCntNewCli'
    end
    object Panel11: TPanel
      Left = 624
      Top = 4
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #25552#25104#27604#20363
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 12
    end
    object cbbRatio: TComboBox
      Left = 686
      Top = 4
      Width = 49
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 13
    end
  end
  object plQuery: TPanel
    Left = 6
    Top = 0
    Width = 507
    Height = 27
    TabOrder = 1
    object Panel20: TPanel
      Left = 192
      Top = 1
      Width = 74
      Height = 21
      Alignment = taLeftJustify
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
      TabOrder = 0
      object cbIsQryByDate: TCheckBox
        Left = 58
        Top = 4
        Width = 16
        Height = 17
        Caption = 'cbIsQryByDate'
        TabOrder = 0
      end
    end
    object dtpQryDateBegin: TDateTimePicker
      Left = 267
      Top = 1
      Width = 66
      Height = 21
      CalAlignment = dtaLeft
      Date = 40894.3857962963
      Time = 40894.3857962963
      DateFormat = dfShort
      DateMode = dmComboBox
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      Kind = dtkDate
      ParseInput = False
      TabOrder = 1
    end
    object dtpQryDateEnd: TDateTimePicker
      Left = 350
      Top = 1
      Width = 66
      Height = 21
      CalAlignment = dtaLeft
      Date = 73036.3921510648
      Time = 73036.3921510648
      DateFormat = dfShort
      DateMode = dmComboBox
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      Kind = dtkDate
      ParseInput = False
      TabOrder = 2
    end
    object btnQry: TButton
      Left = 437
      Top = 0
      Width = 63
      Height = 25
      Caption = #26597#35810
      TabOrder = 3
      OnClick = btnQryClick
    end
    object Panel5: TPanel
      Left = 8
      Top = 2
      Width = 60
      Height = 21
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
      TabOrder = 4
    end
    object cbbQryOpCodeSl: TComboBox
      Left = 70
      Top = 2
      Width = 121
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 5
    end
  end
  object btnMod: TButton
    Left = 619
    Top = 0
    Width = 75
    Height = 25
    Caption = #20462#25913
    TabOrder = 2
    OnClick = btnModClick
  end
  object btnDel: TButton
    Left = 693
    Top = 0
    Width = 75
    Height = 25
    Caption = #21024#38500
    TabOrder = 3
    OnClick = btnDelClick
  end
  object btnCancel: TButton
    Left = 840
    Top = 0
    Width = 63
    Height = 25
    Caption = #21462#28040
    TabOrder = 4
    OnClick = btnCancelClick
  end
  object btnOK: TButton
    Left = 777
    Top = 0
    Width = 63
    Height = 25
    Caption = #30830#23450
    TabOrder = 5
    OnClick = btnOKClick
  end
  object lvCommition: TListView
    Left = 5
    Top = 64
    Width = 1014
    Height = 225
    Columns = <
      item
        Caption = #22995#21517
      end
      item
        Caption = #26376#24230
      end
      item
        Caption = #27611#21033
      end
      item
        Caption = #20219#21153#22522#25968
        Width = 90
      end
      item
        Caption = #26032#23458#20219#21153
        Width = 70
      end
      item
        Caption = #21097#20313#26032#23458#25968
        Width = 80
      end
      item
        Caption = #24212#21457#25552#25104
        Width = 80
      end
      item
        Caption = #23454#21457#25552#25104
        Width = 90
      end
      item
        Caption = #21457#25918#26102#38388
        Width = 100
      end
      item
        Caption = #32463#29702#23457#25209
        Width = 80
      end
      item
        Caption = #19994#21153#23436#25104#27604#20363
        Width = 100
      end
      item
        Caption = #25552#25104#27604#20363
        Width = 70
      end>
    FlatScrollBars = True
    GridLines = True
    ReadOnly = True
    RowSelect = True
    TabOrder = 6
    ViewStyle = vsReport
    OnSelectItem = lvCommitionSelectItem
  end
  object btnAdd: TButton
    Left = 546
    Top = 0
    Width = 75
    Height = 25
    Caption = #28155#21152
    TabOrder = 7
    OnClick = btnAddClick
  end
  object edtDebug: TEdit
    Left = 456
    Top = 304
    Width = 81
    Height = 21
    ImeName = #35895#27468#25340#38899#36755#20837#27861' 2'
    TabOrder = 8
    Text = 'edtDebug'
    Visible = False
  end
  object lvYearCommition: TListView
    Left = 5
    Top = 352
    Width = 936
    Height = 225
    Columns = <
      item
        Caption = #22995#21517
      end
      item
        Caption = #27611#21033
      end
      item
        Caption = #24212#21457#25552#25104
        Width = 80
      end
      item
        Caption = #23454#21457#25552#25104
        Width = 90
      end
      item
        Caption = #24453#21457#25552#25104
        Width = 100
      end
      item
        Caption = #24453#21457#25552#25104#21457#25918#26102#38388
        Width = 150
      end
      item
        Caption = #35745#21010#26032#23458#25968
        Width = 100
      end
      item
        Caption = #23454#38469#26032#23458#25968
        Width = 100
      end
      item
        Caption = #23436#25104#27604#20363
        Width = 100
      end>
    Enabled = False
    FlatScrollBars = True
    GridLines = True
    ReadOnly = True
    RowSelect = True
    TabOrder = 9
    ViewStyle = vsReport
    OnSelectItem = lvCommitionSelectItem
  end
  object Panel21: TPanel
    Left = 8
    Top = 292
    Width = 932
    Height = 7
    Color = 16349446
    TabOrder = 10
  end
  object Panel7: TPanel
    Left = 6
    Top = 320
    Width = 413
    Height = 27
    TabOrder = 11
    object btnQryYear: TButton
      Left = 341
      Top = 2
      Width = 63
      Height = 25
      Caption = #26597#35810
      TabOrder = 0
      OnClick = btnQryYearClick
    end
    object cbbYearOpCodeSl: TComboBox
      Left = 70
      Top = 2
      Width = 121
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 1
    end
    object Panel8: TPanel
      Left = 8
      Top = 2
      Width = 60
      Height = 21
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
      TabOrder = 2
    end
    object Panel9: TPanel
      Left = 192
      Top = 2
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #24180#24230
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 3
    end
    object cbbQryYear: TComboBox
      Left = 252
      Top = 3
      Width = 76
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      ItemIndex = 0
      TabOrder = 4
      Text = '2012'
      Items.Strings = (
        '2012'
        '2013'
        '2014'
        '2015'
        '2016'
        '2017'
        '2018'
        '2019'
        '2020'
        '2021'
        '2022')
    end
  end
  object Button1: TButton
    Left = 1010
    Top = 0
    Width = 75
    Height = 25
    Caption = #26368#23567#21270
    TabOrder = 12
    OnClick = Button1Click
  end
  object TrayIcon1: TTrayIcon
    Hint = 'ASI'
    Hide = True
    RestoreOn = imDoubleClick
    PopupMenuOn = imNone
    Left = 956
  end
end
