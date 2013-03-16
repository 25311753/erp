object AcceptForm: TAcceptForm
  Left = 213
  Top = 122
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #25509#21333
  ClientHeight = 699
  ClientWidth = 1282
  Color = clInactiveCaption
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
  object lbdebug: TLabel
    Left = 544
    Top = 0
    Width = 38
    Height = 13
    Caption = 'lbdebug'
    Visible = False
  end
  object PanelUp: TPanel
    Left = -1
    Top = 24
    Width = 1025
    Height = 184
    Color = clInactiveCaption
    TabOrder = 5
    object edtCid: TEdit
      Left = 61
      Top = 1
      Width = 122
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 0
      Text = 'edtCid'
    end
    object cbbClient: TComboBox
      Left = 243
      Top = 1
      Width = 144
      Height = 21
      AutoDropDown = True
      Color = clHighlightText
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 1
      OnChange = cbbClientChange
      OnExit = cbbClientExit
      OnSelect = cbbClientSelect
    end
    object edtLading: TEdit
      Left = 447
      Top = 1
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 2
      Text = 'edtLading'
    end
    object edtCustfree: TEdit
      Left = 447
      Top = 22
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 11
      Text = 'edtCustfree'
    end
    object edtCliWorkid: TEdit
      Left = 61
      Top = 43
      Width = 122
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 12
      Text = 'edtCliWorkid'
    end
    object edtBeiZhu: TEdit
      Left = 61
      Top = 85
      Width = 508
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 17
      Text = 'edtBeiZhu'
    end
    object cbbGoodsPerf: TComboBox
      Left = 243
      Top = 43
      Width = 144
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 13
      Items.Strings = (
        #21253#26588
        #20080#21333
        #27491#24120#21333)
    end
    object cbbStatus: TComboBox
      Left = 450
      Top = 64
      Width = 76
      Height = 21
      Style = csDropDownList
      Enabled = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 18
      Visible = False
    end
    object dtpEndDateHHMM: TDateTimePicker
      Left = 145
      Top = 64
      Width = 68
      Height = 21
      CalAlignment = dtaLeft
      Date = 40895.4886652778
      Time = 40895.4886652778
      DateFormat = dfShort
      DateMode = dmComboBox
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      Kind = dtkTime
      ParseInput = False
      TabOrder = 16
    end
    object edtContainerNo: TEdit
      Left = 628
      Top = 1
      Width = 88
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 3
      Text = 'edtContainerNo'
    end
    object cbbContainerType: TComboBox
      Left = 745
      Top = 1
      Width = 32
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      ItemIndex = 0
      TabOrder = 4
      Text = 'S'
      Items.Strings = (
        'S'
        'L')
    end
    object btnAddContainer: TButton
      Left = 853
      Top = 23
      Width = 64
      Height = 21
      Caption = #28155#21152
      TabOrder = 6
      OnClick = btnAddContainerClick
    end
    object lstViewContainer: TListView
      Left = 568
      Top = 22
      Width = 284
      Height = 156
      Columns = <
        item
          Caption = #38598#35013#31665#21495
          Width = 147
        end
        item
          Caption = #26588#22411
          Width = 60
        end
        item
          Caption = #23553#26465#21495
          Width = 73
        end>
      GridLines = True
      ReadOnly = True
      RowSelect = True
      TabOrder = 19
      ViewStyle = vsReport
      OnSelectItem = lstViewContainerSelectItem
    end
    object btnModContainer: TButton
      Left = 853
      Top = 43
      Width = 64
      Height = 22
      Caption = #20462#25913
      TabOrder = 7
      OnClick = btnModContainerClick
    end
    object btnDelContainer: TButton
      Left = 853
      Top = 64
      Width = 64
      Height = 23
      Caption = #21024#38500
      TabOrder = 8
      OnClick = btnDelContainerClick
    end
    object edtSealId: TEdit
      Left = 819
      Top = 1
      Width = 96
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 5
      Text = 'edtSealId'
    end
    object dtpEndDateYYYYMMDD: TDateTimePicker
      Left = 61
      Top = 64
      Width = 83
      Height = 21
      CalAlignment = dtaLeft
      Date = 40894.3686127199
      Time = 40894.3686127199
      DateFormat = dfShort
      DateMode = dmComboBox
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      Kind = dtkDate
      ParseInput = False
      TabOrder = 15
    end
    object Panel2: TPanel
      Left = 183
      Top = 1
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #22996#25176#23458#25143
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 20
    end
    object Panel3: TPanel
      Left = 387
      Top = 1
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #25552#21333#21495
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 21
    end
    object Panel4: TPanel
      Left = 568
      Top = 1
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #38598#35013#31665#21495
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 22
    end
    object Panel5: TPanel
      Left = 716
      Top = 1
      Width = 30
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #26588#22411
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 23
    end
    object Panel6: TPanel
      Left = 775
      Top = 1
      Width = 45
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #23553#26465#21495
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 24
    end
    object Panel7: TPanel
      Left = 1
      Top = 22
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #33322#32534
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 25
    end
    object Panel8: TPanel
      Left = 183
      Top = 22
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #33322#27425
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 26
    end
    object Panel9: TPanel
      Left = 387
      Top = 22
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #25253#20851#36153
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 27
    end
    object Panel10: TPanel
      Left = 1
      Top = 43
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #23458#25143#24037#21333
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 28
    end
    object Panel11: TPanel
      Left = 183
      Top = 43
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #36135#29289#24615#36136
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 29
    end
    object Panel12: TPanel
      Left = 390
      Top = 64
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #29366#24577
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 30
      Visible = False
    end
    object Panel13: TPanel
      Left = 1
      Top = 64
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #25130#20851#26085#26399
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 31
    end
    object Panel14: TPanel
      Left = 1
      Top = 85
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #22791#27880
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 32
    end
    object Panel21: TPanel
      Left = 0
      Top = 109
      Width = 569
      Height = 7
      Color = 16349446
      TabOrder = 33
    end
    object Panel47: TPanel
      Left = 213
      Top = 64
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #33337#20195
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 34
    end
    object cbbShipAgent: TComboBox
      Left = 273
      Top = 64
      Width = 115
      Height = 21
      Style = csDropDownList
      Enabled = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      ItemIndex = 0
      TabOrder = 14
      Items.Strings = (
        '')
    end
    object edtBoatNo: TEdit
      Left = 61
      Top = 22
      Width = 122
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 9
      Text = 'edtBoatNo'
    end
    object edtBoatOrder: TEdit
      Left = 244
      Top = 22
      Width = 143
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 10
      Text = 'edtBoatOrder'
    end
    object Panel24: TPanel
      Left = 387
      Top = 43
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = '('#21442#32771#20540')'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 35
    end
    object cbbCustomsCharge: TComboBox
      Left = 448
      Top = 42
      Width = 121
      Height = 21
      AutoDropDown = True
      Color = clHighlightText
      Enabled = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 36
    end
  end
  object btnAdd: TButton
    Left = 1
    Top = 0
    Width = 75
    Height = 25
    Caption = #25509#21333
    TabOrder = 0
    OnClick = btnAddClick
  end
  object btnMod: TButton
    Left = 75
    Top = 0
    Width = 75
    Height = 25
    Caption = #20462#25913
    TabOrder = 1
    OnClick = btnModClick
  end
  object btnDel: TButton
    Left = 149
    Top = 0
    Width = 75
    Height = 25
    Caption = #21024#38500
    TabOrder = 2
    OnClick = btnDelClick
  end
  object PanelUpQuery: TPanel
    Left = 0
    Top = 138
    Width = 568
    Height = 68
    Color = clInactiveCaption
    TabOrder = 6
    object Label1: TLabel
      Left = 389
      Top = 50
      Width = 51
      Height = 13
      Caption = #26588#25968#21512#35745':'
    end
    object lb_sum_cnt_con: TLabel
      Left = 454
      Top = 50
      Width = 78
      Height = 13
      Caption = 'lb_sum_cnt_con'
    end
    object edtQryCid: TEdit
      Left = 60
      Top = 2
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 0
      Text = 'edtQryCid'
      OnKeyPress = edtQryCidKeyPress
    end
    object edtQryLading: TEdit
      Left = 446
      Top = 2
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 2
      Text = 'edtQryLading'
    end
    object edtQryJZS: TEdit
      Left = 242
      Top = 24
      Width = 142
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 7
      Text = 'edtQryJZS'
    end
    object cbbQryStatus: TComboBox
      Left = 61
      Top = 23
      Width = 121
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 3
      Items.Strings = (
        '')
    end
    object btnQuery: TButton
      Left = 492
      Top = 48
      Width = 75
      Height = 17
      Caption = #26597#35810
      TabOrder = 6
      OnClick = btnQueryClick
    end
    object dtpQryAcceptDate: TDateTimePicker
      Left = 75
      Top = 45
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
      TabOrder = 4
    end
    object dtpQryAcceptDateEnd: TDateTimePicker
      Left = 159
      Top = 45
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
      TabOrder = 5
    end
    object cbbQryClient: TComboBox
      Left = 241
      Top = 2
      Width = 144
      Height = 21
      AutoDropDown = True
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 1
      OnChange = cbbQryClient1Change
      OnSelect = cbbQryClient1Select
    end
    object Panel15: TPanel
      Left = 0
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
      TabOrder = 8
    end
    object Panel16: TPanel
      Left = 182
      Top = 2
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #22996#25176#23458#25143
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 9
    end
    object Panel17: TPanel
      Left = 386
      Top = 2
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #25552#21333#21495
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 10
    end
    object Panel18: TPanel
      Left = 182
      Top = 24
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #38598#35013#31665#21495
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 11
    end
    object Panel19: TPanel
      Left = 0
      Top = 23
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #29366#24577
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 12
    end
    object Panel20: TPanel
      Left = 0
      Top = 45
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
      TabOrder = 13
    end
    object cbIsQryByDate: TCheckBox
      Left = 58
      Top = 47
      Width = 16
      Height = 17
      Caption = 'cbIsQryByDate'
      TabOrder = 14
    end
    object Panel22: TPanel
      Left = 386
      Top = 24
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #26680#38144#21333#21495
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 15
    end
    object edtQryLicenseNo: TEdit
      Left = 446
      Top = 24
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 16
      Text = 'edtQryLicenseNo'
    end
    object Panel23: TPanel
      Left = 243
      Top = 46
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #36135#29289#24615#36136
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 17
    end
    object cbbGoodsPerfQry: TComboBox
      Left = 303
      Top = 45
      Width = 83
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      ItemIndex = 0
      TabOrder = 18
      Items.Strings = (
        ''
        #21253#26588
        #20080#21333
        #27491#24120#21333)
    end
  end
  object btnCancel: TButton
    Left = 360
    Top = 0
    Width = 63
    Height = 25
    Caption = #21462#28040
    TabOrder = 4
    OnClick = btnCancelClick
  end
  object btnOK: TButton
    Left = 297
    Top = 0
    Width = 63
    Height = 25
    Caption = #30830#23450
    TabOrder = 3
    OnClick = btnOKClick
  end
  object edtContainerInfo: TEdit
    Left = 608
    Top = 0
    Width = 33
    Height = 21
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    TabOrder = 7
    Text = 'edtContainerInfo'
    Visible = False
  end
  object Panel1: TPanel
    Left = 0
    Top = 25
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
    TabOrder = 8
  end
  object Panel45: TPanel
    Left = 0
    Top = 207
    Width = 1024
    Height = 7
    Color = 16349446
    TabOrder = 9
  end
  object Button1: TButton
    Left = 1203
    Top = 0
    Width = 64
    Height = 23
    Caption = #26368#23567#21270
    TabOrder = 10
    OnClick = Button1Click
  end
  object cbbBoatno: TComboBox
    Left = 653
    Top = 0
    Width = 47
    Height = 21
    Style = csDropDownList
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    ItemHeight = 13
    TabOrder = 11
    Visible = False
  end
  object cbbBoatorder: TComboBox
    Left = 707
    Top = 0
    Width = 45
    Height = 21
    Style = csDropDownList
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    ItemHeight = 13
    TabOrder = 12
    Visible = False
  end
  object lstViewDown: TListView
    Left = 1
    Top = 213
    Width = 1276
    Height = 487
    Columns = <
      item
        Caption = 'N'
        Width = 20
      end
      item
        Caption = #24037#21333#21495
        Width = 75
      end
      item
        Caption = #36135#29289#24615#36136
      end
      item
        Caption = #25509#21333#26085#26399
        Width = 65
      end
      item
        Caption = #22996#25176#23458#25143
        Width = 60
      end
      item
        Caption = #25552#21333#21495
        Width = 120
      end
      item
        Caption = #38598#35013#31665#21495
        Width = 90
      end
      item
        Caption = #26588#25968
        Width = 40
      end
      item
        Caption = #26680#38144#21333#21495
        Width = 70
      end
      item
        Caption = #33337#32534
        Width = 60
      end
      item
        Caption = #33322#27425
        Width = 70
      end
      item
        Caption = #25130#20851#26085#26399
        Width = 120
      end
      item
        Caption = #29366#24577
        Width = 70
      end
      item
        Caption = #23458#25143#24037#21333#21495
        Width = 100
      end
      item
        Caption = #25253#20851#36153
      end
      item
        Caption = #23553#26465#21495
        Width = 80
      end
      item
        Caption = #25509#21333#20154
        Width = 60
      end
      item
        Caption = #20570#21333#20154
        Width = 60
      end
      item
        Caption = #22791#27880
        Width = 40
      end
      item
        Caption = #33337#20195
      end
      item
      end>
    FlatScrollBars = True
    GridLines = True
    ReadOnly = True
    RowSelect = True
    TabOrder = 13
    ViewStyle = vsReport
    OnSelectItem = lstViewDownSelectItem
  end
  object TrayIcon1: TTrayIcon
    Hint = #28070#39034#25253#20851
    Hide = True
    RestoreOn = imDoubleClick
    PopupMenuOn = imNone
    Icons = ImageList1
    Left = 504
  end
  object ImageList1: TImageList
    Left = 920
    Bitmap = {
      494C010101000400040010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000001000000001002000000000000010
      000000000000000000000000000000000000000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FFA4ADADFF000000FF000000FF000000FF0000
      00FF000000FF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000FF000000FF000000FF0000
      00FF000000FF000000FF1F4140FF006866FF008C8AFFDFE0E0FF000000FF0000
      00FF000000FF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000FF000000FF000000FF0000
      00FFF9F9F9FF003232FF003534FF006967FF008F8DFF008C8AFF729494FF0000
      00FF000000FF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000FF000000FF000000FFB1AE
      AEFF808484FF003534FF003635FF006B6AFF00908EFF008E8CFF008A88FF939B
      94FFFEFEFEFF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000FF000000FF35201EFF5110
      09FF0D2024FF003635FF004B4AFF00CFCDFF00C5C3FF00908EFF008D8BFF1285
      27FF0C831AFFC2C7C3FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000FF250704FF280804FF5812
      0AFF0A2224FF007877FF04ABABFF2F5370FF20B7C9FF00E7E4FF00A2A0FF177B
      33FF0C861BFF0C831AFFF9F9F9FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000FF270804FF290804FF6113
      0BFF065E5EFF1F5B6BFF031617FF006765FF007574FF29526AFF0BE3E6FF1D73
      40FF0D8B1CFF0C841AFFB9C1BAFF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000FF2A0805FF64140BFF6A2E
      2FFF0D1015FF002E2EFF003635FF006A69FF009190FF008F8DFF045C59FF2F59
      6FFF16E42EFF10A621FF7B997EFF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000FF7C1B11FF1F2A37FF490F
      08FF022928FF003635FF003736FF006B69FF009291FF00918FFF008F8DFF255A
      53FF135029FF2FA465FF8EAF92FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000FF2D2624FF280804FF6916
      0DFF002F2EFF003636FF003837FF006B6AFF009492FF009290FF00908EFF2757
      5EFF0E931DFF0C7E19FFBDC0BDFF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000ADAAAAFF280804FF2A0805FF641C
      17FF003333FF003837FF003E3EFF00A5A3FF00AFADFF009492FF009190FF2558
      67FF0E961EFF0D871BFF0C841AFF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000766C6CFF290804FF2E0905FF5D21
      21FF004342FF00A09EFF00C4C2FF00BCBAFF00C2C0FF00EEEBFF00C1BEFF1E5E
      6BFF0E991FFF0D881BFF0C861BFF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000045322FFF2A0805FF490F08FFC131
      21FF4F7182FF06ABAAFF00B6B4FF00B6B4FF00B6B4FF00B6B4FF158F95FF1FA1
      46FF20D836FF0D8D1CFF0D871BFF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000470E08FF8E1C10FF8A1B0FFF8B1C
      0FFFA22012FFBC2615FFA93731FF247492FF276E65FF12BA25FF12BF26FF11B0
      23FF10AB22FF12BB25FF14D82BFFF1F1F1FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000FFD4D1D1FF86524BFF831A
      0FFF7C332AFF292E83FF0001ACFF0000B6FF0000D6FF111DD0FF246A62FF0FA1
      20FF1F9A2DFF9DB2A0FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000FF000000FF000000FF0000
      00FF000000FFA3A3B5FF17178CFF000094FF000094FF606096FFF7F7F7FF0000
      00FF000000FF000000FF000000FF000000FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000040000000100000000100010000000000800000000000000000000000
      000000000000000000000000FFFFFF00FEFF000000000000FC3F000000000000
      F01F000000000000E007000000000000C0030000000000008001000000000000
      8001000000000000800100000000000080010000000000008001000000000000
      0001000000000000000100000000000000010000000000000000000000000000
      8003000000000000F81F00000000000000000000000000000000000000000000
      000000000000}
  end
end
