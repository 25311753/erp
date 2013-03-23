object FinanceOpForm: TFinanceOpForm
  Left = 44
  Top = 28
  Width = 1176
  Height = 672
  BorderIcons = [biSystemMenu]
  Caption = #25910#20184#27454'\'#22238#25187
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
  object lvOId: TListView
    Left = 1
    Top = 112
    Width = 184
    Height = 521
    Columns = <
      item
        Caption = #21333#21495
        Width = 100
      end
      item
        Caption = ' '#21033#28070
        Width = 75
      end>
    FlatScrollBars = True
    GridLines = True
    ReadOnly = True
    RowSelect = True
    TabOrder = 0
    ViewStyle = vsReport
    OnSelectItem = lvOIdSelectItem
  end
  object plQuery: TPanel
    Left = 0
    Top = 24
    Width = 984
    Height = 88
    TabOrder = 1
    object Panel1: TPanel
      Left = 2
      Top = 2
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #24037#21333#21495
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 0
    end
    object edtQryOId: TEdit
      Left = 62
      Top = 2
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 1
      Text = 'edtQryOId'
    end
    object Panel20: TPanel
      Left = 183
      Top = 2
      Width = 74
      Height = 21
      Alignment = taLeftJustify
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #25509#21333#26085#26399
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 2
      object cbIsQryByDate: TCheckBox
        Left = 58
        Top = 4
        Width = 16
        Height = 17
        Caption = 'cbIsQryByDate'
        Checked = True
        State = cbChecked
        TabOrder = 0
      end
    end
    object dtpQryDateBegin: TDateTimePicker
      Left = 255
      Top = 2
      Width = 83
      Height = 21
      CalAlignment = dtaLeft
      Date = 40894.3857962963
      Time = 40894.3857962963
      DateFormat = dfShort
      DateMode = dmComboBox
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      Kind = dtkDate
      ParseInput = False
      TabOrder = 3
    end
    object dtpQryDateEnd: TDateTimePicker
      Left = 338
      Top = 2
      Width = 83
      Height = 21
      CalAlignment = dtaLeft
      Date = 40894.3921510648
      Time = 40894.3921510648
      DateFormat = dfShort
      DateMode = dmComboBox
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      Kind = dtkDate
      ParseInput = False
      TabOrder = 4
    end
    object Panel18: TPanel
      Left = 2
      Top = 43
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
      TabOrder = 5
    end
    object cbbQryOpCodeSl: TComboBox
      Left = 62
      Top = 43
      Width = 121
      Height = 21
      Style = csDropDownList
      Enabled = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 6
    end
    object Panel25: TPanel
      Left = 2
      Top = 22
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #25805#20316#21592
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 7
    end
    object cbbQryOpCodeOp: TComboBox
      Left = 62
      Top = 22
      Width = 121
      Height = 21
      Style = csDropDownList
      Enabled = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 8
    end
    object Panel26: TPanel
      Left = 183
      Top = 43
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #23458#25143
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 9
    end
    object cbbQryClShortName: TComboBox
      Left = 243
      Top = 43
      Width = 121
      Height = 21
      Style = csDropDownList
      Enabled = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 10
    end
    object Panel27: TPanel
      Left = 183
      Top = 22
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #36884#24452
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 11
    end
    object cbbQryWay: TComboBox
      Left = 243
      Top = 22
      Width = 121
      Height = 21
      Style = csDropDownList
      Enabled = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 12
    end
    object Panel28: TPanel
      Left = 363
      Top = 22
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #36816#21333#21495
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 13
    end
    object edtQryLoadingId: TEdit
      Left = 423
      Top = 22
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 14
      Text = 'edtQryLoadingId'
    end
    object Panel29: TPanel
      Left = 2
      Top = 65
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #20379#24212#21830
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 15
    end
    object cbbQrySupply: TComboBox
      Left = 62
      Top = 65
      Width = 121
      Height = 21
      Style = csDropDownList
      Enabled = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 16
    end
    object Panel30: TPanel
      Left = 183
      Top = 65
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #20184#27454#38134#34892
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 17
    end
    object edtQryOutBank: TEdit
      Left = 243
      Top = 65
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 18
      Text = 'edtQryOutBank'
    end
    object Panel31: TPanel
      Left = 364
      Top = 65
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #20184#27454#20154
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 19
    end
    object edtQryOutMan: TEdit
      Left = 424
      Top = 65
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 20
      Text = 'edtQryOutMan'
    end
  end
  object plInput: TPanel
    Left = 189
    Top = 112
    Width = 969
    Height = 521
    TabOrder = 2
    object Label1: TLabel
      Left = 8
      Top = 15
      Width = 63
      Height = 13
      Caption = #25910#27454#32426#24405'     '
    end
    object Label2: TLabel
      Left = 8
      Top = 239
      Width = 60
      Height = 13
      Caption = #20184#27454#32426#24405'    '
    end
    object Label3: TLabel
      Left = 11
      Top = 401
      Width = 60
      Height = 13
      Caption = #22238#25187#32426#24405'    '
    end
    object Panel21: TPanel
      Left = -91
      Top = 4
      Width = 1059
      Height = 7
      Color = 16349446
      TabOrder = 0
    end
    object Panel3: TPanel
      Left = 145
      Top = 35
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #23454#25910#37329#39069
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 1
    end
    object edtInPrice: TEdit
      Left = 205
      Top = 35
      Width = 72
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 2
      Text = 'edtInPrice'
    end
    object Panel4: TPanel
      Left = 395
      Top = 35
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #25910#27454#38134#34892
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 3
    end
    object edtInBank: TEdit
      Left = 455
      Top = 35
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 4
      Text = 'edtInBank'
    end
    object Panel5: TPanel
      Left = 576
      Top = 35
      Width = 45
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #30830#35748#20154
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 5
    end
    object edtCfmOpName: TEdit
      Left = 620
      Top = 35
      Width = 66
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 6
      Text = 'edtCfmOpName'
    end
    object Panel6: TPanel
      Left = -83
      Top = 226
      Width = 1041
      Height = 7
      Color = 16349446
      TabOrder = 7
    end
    object Panel8: TPanel
      Left = 89
      Top = 258
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #20184#27454#26085#26399
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 8
    end
    object Panel9: TPanel
      Left = 233
      Top = 258
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #20184#27454#38134#34892
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 9
    end
    object edtOutBank: TEdit
      Left = 293
      Top = 258
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 10
      Text = 'edtOutBank'
    end
    object Panel10: TPanel
      Left = 417
      Top = 258
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #20184#27454#36134#25143
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 11
    end
    object edtOutAccount: TEdit
      Left = 477
      Top = 258
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 12
      Text = 'edtOutAccount'
    end
    object Panel11: TPanel
      Left = 601
      Top = 258
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #20184#27454#20154
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 13
    end
    object edtOutMan: TEdit
      Left = 661
      Top = 258
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 14
      Text = 'edtOutMan'
    end
    object lvOut: TListView
      Left = 5
      Top = 285
      Width = 956
      Height = 100
      Columns = <
        item
          Caption = #32534#21495
        end
        item
          Caption = #24050#20184#27454
        end
        item
          Caption = #39033#30446
          Width = 100
        end
        item
          Caption = #25968#37327
          Width = 100
        end
        item
          Caption = #39033#30446#24635#39069
          Width = 100
        end
        item
          Caption = #20379#24212#21830
          Width = 100
        end
        item
          Caption = #20184#27454#26085#26399
          Width = 100
        end
        item
          Caption = #20184#27454#38134#34892
          Width = 100
        end
        item
          Caption = #20184#27454#36134#25143
          Width = 200
        end
        item
          Caption = #20184#27454#20154
          Width = 100
        end>
      FlatScrollBars = True
      GridLines = True
      ReadOnly = True
      RowSelect = True
      TabOrder = 15
      ViewStyle = vsReport
      OnSelectItem = lvOutSelectItem
    end
    object Panel14: TPanel
      Left = -83
      Top = 387
      Width = 1043
      Height = 7
      Color = 16349446
      TabOrder = 16
    end
    object Panel15: TPanel
      Left = 9
      Top = 450
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #22238#25187#37329#39069
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 17
    end
    object edtKbValue: TEdit
      Left = 69
      Top = 450
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 18
      Text = 'edtKbValue'
    end
    object Panel16: TPanel
      Left = 193
      Top = 450
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #25509#25910#20154
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 19
    end
    object edtRecipient: TEdit
      Left = 253
      Top = 450
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 20
      Text = 'edtRecipient'
    end
    object Panel17: TPanel
      Left = 377
      Top = 450
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #24320#25143#34892
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 21
    end
    object edtBank: TEdit
      Left = 437
      Top = 450
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 22
      Text = 'edtBank'
    end
    object edtBankDeposit: TEdit
      Left = 621
      Top = 450
      Width = 337
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 23
      Text = 'edtBankDeposit'
    end
    object Panel12: TPanel
      Left = 561
      Top = 450
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #38134#34892#36134#25143
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 24
    end
    object Panel13: TPanel
      Left = 560
      Top = 426
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #26159#21542#25910#40784#36816#36153
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -8
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 25
    end
    object Panel19: TPanel
      Left = 193
      Top = 474
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #20184'KB'#26085#26399
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 26
    end
    object dtpOutDate: TDateTimePicker
      Left = 151
      Top = 257
      Width = 83
      Height = 21
      CalAlignment = dtaLeft
      Date = 40894.3857962963
      Time = 40894.3857962963
      DateFormat = dfShort
      DateMode = dmComboBox
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      Kind = dtkDate
      ParseInput = False
      TabOrder = 27
    end
    object cbbIsAll: TComboBox
      Left = 621
      Top = 426
      Width = 121
      Height = 21
      Style = csDropDownList
      Enabled = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 28
      Items.Strings = (
        #26159
        #21542)
    end
    object dtpKbDate: TDateTimePicker
      Left = 255
      Top = 473
      Width = 83
      Height = 21
      CalAlignment = dtaLeft
      Date = 40894.3857962963
      Time = 40894.3857962963
      DateFormat = dfShort
      DateMode = dmComboBox
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      Kind = dtkDate
      ParseInput = False
      TabOrder = 29
    end
    object btnOKIn: TButton
      Left = 929
      Top = 12
      Width = 36
      Height = 19
      Caption = #26356#26032
      TabOrder = 30
      OnClick = btnOKInClick
    end
    object btnOkOut: TButton
      Left = 922
      Top = 235
      Width = 35
      Height = 19
      Caption = #26356#26032
      TabOrder = 31
      OnClick = btnOkOutClick
    end
    object btnOkKb: TButton
      Left = 922
      Top = 402
      Width = 36
      Height = 19
      Caption = #26356#26032
      TabOrder = 32
      OnClick = btnOkKbClick
    end
    object Panel2: TPanel
      Left = 2
      Top = 36
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #24212#25910#37329#39069
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 33
    end
    object edtShouldIn: TEdit
      Left = 62
      Top = 36
      Width = 82
      Height = 21
      Enabled = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 34
      Text = 'edtShouldIn'
    end
    object Panel22: TPanel
      Left = 278
      Top = 35
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #25910#27454#23436#25104#29575
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -9
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 35
    end
    object edtPecIn: TEdit
      Left = 338
      Top = 35
      Width = 54
      Height = 21
      Enabled = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 36
      Text = 'edtPecIn'
    end
    object Button2: TButton
      Left = 643
      Top = 234
      Width = 145
      Height = 25
      Caption = #37325#32622#25910#27454#32426#24405' - '#22238#36864
      TabOrder = 37
      Visible = False
    end
    object cbNoDelay: TCheckBox
      Left = 72
      Top = 17
      Width = 114
      Height = 17
      Caption = #26159#21542#25353#26102#20184#27454
      Enabled = False
      TabOrder = 38
    end
    object cbIsDoneIn: TCheckBox
      Left = 8
      Top = 262
      Width = 63
      Height = 17
      Caption = #24050#20184#27454
      TabOrder = 39
    end
    object Panel7: TPanel
      Left = 688
      Top = 35
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #25910#27454#26102#38388
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 40
    end
    object dtpInDate: TDateTimePicker
      Left = 747
      Top = 34
      Width = 83
      Height = 21
      CalAlignment = dtaLeft
      Date = 40894.3857962963
      Time = 40894.3857962963
      DateFormat = dfShort
      DateMode = dmComboBox
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      Kind = dtkDate
      ParseInput = False
      TabOrder = 41
    end
    object Panel23: TPanel
      Left = 830
      Top = 35
      Width = 55
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #25805#20316#26102#38388
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 42
    end
    object dtpFiDate: TDateTimePicker
      Left = 887
      Top = 34
      Width = 81
      Height = 21
      CalAlignment = dtaLeft
      Date = 40894.3857962963
      Time = 40894.3857962963
      DateFormat = dfShort
      DateMode = dmComboBox
      Enabled = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      Kind = dtkDate
      ParseInput = False
      TabOrder = 43
    end
    object Panel24: TPanel
      Left = 377
      Top = 474
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #25805#20316#26085#26399
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 44
    end
    object dtpOpDate: TDateTimePicker
      Left = 439
      Top = 473
      Width = 83
      Height = 21
      CalAlignment = dtaLeft
      Date = 40894.3857962963
      Time = 40894.3857962963
      DateFormat = dfShort
      DateMode = dmComboBox
      Enabled = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      Kind = dtkDate
      ParseInput = False
      TabOrder = 45
    end
    object Panel32: TPanel
      Left = 9
      Top = 426
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #23458#25143
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 46
    end
    object edtClShortName: TEdit
      Left = 69
      Top = 426
      Width = 121
      Height = 21
      Enabled = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 47
      Text = 'edtClShortName'
    end
    object Panel33: TPanel
      Left = 193
      Top = 426
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
      TabOrder = 48
    end
    object edtOpCodeSl: TEdit
      Left = 253
      Top = 426
      Width = 121
      Height = 21
      Enabled = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 49
      Text = 'edtOpCodeSl'
    end
    object Panel34: TPanel
      Left = 377
      Top = 426
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #26159#21542#21040#36135
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -8
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 50
    end
    object cbbIsArrival: TComboBox
      Left = 438
      Top = 426
      Width = 121
      Height = 21
      Style = csDropDownList
      Enabled = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 51
      Items.Strings = (
        #26159
        #21542)
    end
    object Panel35: TPanel
      Left = 9
      Top = 474
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #36130#21153#20195#21495
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 52
    end
    object edtOpCodeFi: TEdit
      Left = 69
      Top = 474
      Width = 121
      Height = 21
      Enabled = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 53
      Text = 'edtOpCodeFi'
    end
  end
  object edtDebug: TEdit
    Left = 232
    Top = 0
    Width = 489
    Height = 21
    ImeName = #35895#27468#25340#38899#36755#20837#27861' 2'
    TabOrder = 3
    Text = 'edtDebug'
    Visible = False
  end
  object btnCompare: TButton
    Left = 58
    Top = 0
    Width = 90
    Height = 25
    Caption = #21333#31080#23545#36134#21333
    Enabled = False
    TabOrder = 4
    OnClick = btnCompareClick
  end
  object btnTotalCompare: TButton
    Left = 147
    Top = 0
    Width = 75
    Height = 25
    Caption = #24635#36134#21333
    Enabled = False
    TabOrder = 5
    OnClick = btnTotalCompareClick
  end
  object btnQry: TButton
    Left = 0
    Top = 0
    Width = 60
    Height = 25
    Caption = #26597#35810
    TabOrder = 6
    OnClick = btnQryClick
  end
  object lvInDetail: TListView
    Left = 192
    Top = 173
    Width = 244
    Height = 156
    Columns = <
      item
        Caption = #24212#25910#39033#30446
        Width = 100
      end
      item
        Caption = #25968#37327
        Width = 70
      end
      item
        Caption = #35745#20215#26041#24335
        Width = 70
      end>
    GridLines = True
    ReadOnly = True
    RowSelect = True
    TabOrder = 7
    ViewStyle = vsReport
  end
  object Button1: TButton
    Left = 1082
    Top = 0
    Width = 75
    Height = 25
    Caption = #26368#23567#21270
    TabOrder = 8
    OnClick = Button1Click
  end
  object TrayIcon1: TTrayIcon
    Hint = 'ASI'
    Hide = True
    RestoreOn = imDoubleClick
    PopupMenuOn = imNone
    Left = 1012
  end
end
