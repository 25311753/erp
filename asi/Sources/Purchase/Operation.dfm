object OperationForm: TOperationForm
  Left = 142
  Top = 14
  Width = 1066
  Height = 735
  BorderIcons = [biSystemMenu]
  Caption = #25805#20316#31649#29702'-'#26356#26032
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
  object btnAdd: TButton
    Left = 246
    Top = 0
    Width = 75
    Height = 25
    Caption = #24405#20837
    TabOrder = 0
    OnClick = btnAddClick
  end
  object btnMod: TButton
    Left = 320
    Top = 0
    Width = 75
    Height = 25
    Caption = #20462#25913
    TabOrder = 1
    OnClick = btnModClick
  end
  object btnDel: TButton
    Left = 394
    Top = 0
    Width = 75
    Height = 25
    Caption = #21024#38500
    TabOrder = 2
    OnClick = btnDelClick
  end
  object btnCancel: TButton
    Left = 542
    Top = 0
    Width = 63
    Height = 25
    Caption = #21462#28040
    TabOrder = 3
    OnClick = btnCancelClick
  end
  object btnOK: TButton
    Left = 479
    Top = 0
    Width = 63
    Height = 25
    Caption = #30830#23450
    TabOrder = 4
    OnClick = btnOKClick
  end
  object Panel22: TPanel
    Left = 0
    Top = 462
    Width = 1049
    Height = 0
    Color = 16349446
    TabOrder = 5
  end
  object lvOpDetail: TListView
    Left = 2
    Top = 384
    Width = 1047
    Height = 305
    Columns = <
      item
        Caption = #25805#20316#26085#26399
        Width = 100
      end
      item
        Caption = #21333#21495
      end
      item
        Caption = #38144#21806
      end
      item
        Caption = #23458#25143
      end
      item
        Caption = #36135#29289#21517#31216
        Width = 200
      end
      item
        Caption = #36816#21333#21495
      end
      item
        Caption = #26041#24335
      end
      item
        Caption = #36884#24452
      end
      item
        Caption = #21457#36135#22320
        Width = 100
      end
      item
        Caption = #30446#30340#22320
        Width = 100
      end
      item
        Caption = #20214#25968
      end
      item
        Caption = #23454#37325
      end
      item
        Caption = #20307#31215
      end
      item
        Caption = #25805#20316#21592
      end
      item
        Caption = #26159#21542#21040#36135
        Width = 70
      end
      item
        Caption = #21040#36135#26085#26399
        Width = 100
      end
      item
        Caption = #24212#25910
      end
      item
        Caption = #24212#20184
      end
      item
        Caption = 'KB'
      end
      item
        Caption = #21033#28070
      end
      item
        Caption = #21033#28070#29575
      end
      item
        Caption = #20184#27454
      end
      item
        Caption = #20184#27454#26085#26399
        Width = 90
      end
      item
        Caption = #20184#27454#38134#34892
        Width = 200
      end
      item
        Caption = #22238#25187
      end
      item
        Caption = #22238#25187#26085#26399
      end
      item
        Caption = #22238#25187#38134#34892
      end>
    FlatScrollBars = True
    GridLines = True
    ReadOnly = True
    RowSelect = True
    TabOrder = 6
    ViewStyle = vsReport
    OnSelectItem = lvOpDetailSelectItem
  end
  object plInput: TPanel
    Left = 1
    Top = 30
    Width = 1046
    Height = 348
    TabOrder = 7
    object Label1: TLabel
      Left = 3
      Top = 100
      Width = 63
      Height = 13
      Caption = #24212#25910#36134#21333'     '
    end
    object Label2: TLabel
      Left = 410
      Top = 101
      Width = 60
      Height = 13
      Caption = #24212#20184#36134#21333'    '
    end
    object edtInValue: TEdit
      Left = 106
      Top = 118
      Width = 70
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 0
    end
    object cbbInType: TComboBox
      Left = 4
      Top = 118
      Width = 103
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 15
      OnChange = cbbInTypeChange
    end
    object lvInDetail: TListView
      Left = 4
      Top = 140
      Width = 397
      Height = 163
      Columns = <
        item
          Caption = #39033#30446
          Width = 100
        end
        item
          Caption = #25968#37327
          Width = 70
        end
        item
          Caption = #21333#20215
          Width = 70
        end
        item
          Caption = #35745#20215#21333#20301
          Width = 80
        end
        item
          Caption = #37329#39069
          Width = 70
        end>
      GridLines = True
      ReadOnly = True
      RowSelect = True
      TabOrder = 16
      ViewStyle = vsReport
      OnSelectItem = lvInDetailSelectItem
    end
    object lvOutDetail: TListView
      Left = 410
      Top = 139
      Width = 503
      Height = 162
      Columns = <
        item
          Caption = #39033#30446
          Width = 100
        end
        item
          Caption = #25968#37327
          Width = 70
        end
        item
          Caption = #21333#20215
          Width = 70
        end
        item
          Caption = #20379#24212#21830
          Width = 90
        end
        item
          Caption = #35745#20215#21333#20301
          Width = 80
        end
        item
          Caption = #37329#39069
          Width = 80
        end>
      FlatScrollBars = True
      GridLines = True
      ReadOnly = True
      RowSelect = True
      TabOrder = 17
      ViewStyle = vsReport
      OnSelectItem = lvOutDetailSelectItem
    end
    object cbbOutType: TComboBox
      Left = 411
      Top = 119
      Width = 102
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 18
      OnChange = cbbOutTypeChange
    end
    object edtOutValue: TEdit
      Left = 511
      Top = 119
      Width = 71
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 19
    end
    object btnInAdd: TButton
      Left = 61
      Top = 96
      Width = 64
      Height = 21
      Caption = #28155#21152
      TabOrder = 20
      OnClick = btnInAddClick
    end
    object btnInMod: TButton
      Left = 125
      Top = 95
      Width = 64
      Height = 22
      Caption = #20462#25913
      TabOrder = 21
      OnClick = btnInModClick
    end
    object btnInDel: TButton
      Left = 189
      Top = 94
      Width = 64
      Height = 23
      Caption = #21024#38500
      TabOrder = 22
      OnClick = btnInDelClick
    end
    object btnOutAdd: TButton
      Left = 466
      Top = 96
      Width = 63
      Height = 21
      Caption = #28155#21152
      TabOrder = 23
      OnClick = btnOutAddClick
    end
    object btnOutMod: TButton
      Left = 530
      Top = 95
      Width = 63
      Height = 22
      Caption = #20462#25913
      TabOrder = 24
      OnClick = btnOutModClick
    end
    object btnOutDel: TButton
      Left = 594
      Top = 95
      Width = 63
      Height = 23
      Caption = #21024#38500
      TabOrder = 25
      OnClick = btnOutDelClick
    end
    object cbbSpName: TComboBox
      Left = 651
      Top = 119
      Width = 91
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 26
    end
    object cbbInWayCalc: TComboBox
      Left = 246
      Top = 118
      Width = 82
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 27
      Items.Strings = (
        'kg'
        'cbm'
        'bill')
    end
    object cbbOutWayCalc: TComboBox
      Left = 740
      Top = 119
      Width = 83
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 28
      Items.Strings = (
        'kg'
        'cbm'
        'bill')
    end
    object dtpArrival: TDateTimePicker
      Left = 246
      Top = 49
      Width = 120
      Height = 21
      CalAlignment = dtaLeft
      Date = 40894.3857962963
      Time = 40894.3857962963
      DateFormat = dfShort
      DateMode = dmComboBox
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      Kind = dtkDate
      ParseInput = False
      TabOrder = 14
    end
    object cbbGoodsSrc: TComboBox
      Left = 62
      Top = 27
      Width = 121
      Height = 21
      Enabled = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 8
    end
    object Panel7: TPanel
      Left = 0
      Top = 27
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #21457#36135#22320
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 29
    end
    object Panel1: TPanel
      Left = 1
      Top = 3
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #21333#21495
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 30
    end
    object edtOId: TEdit
      Left = 61
      Top = 3
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 1
      Text = 'edtOId'
    end
    object Panel8: TPanel
      Left = 184
      Top = 27
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #30446#30340#22320
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 31
    end
    object Panel2: TPanel
      Left = 184
      Top = 3
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
      TabOrder = 32
    end
    object cbbOpCodeSl: TComboBox
      Left = 246
      Top = 3
      Width = 121
      Height = 21
      Style = csDropDownList
      Enabled = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 2
      OnChange = cbbOpCodeSlChange
    end
    object cbbGoodsDst: TComboBox
      Left = 246
      Top = 27
      Width = 121
      Height = 21
      Enabled = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 9
      OnChange = cbbGoodsDstChange
      OnSelect = cbbGoodsDstSelect
    end
    object Panel9: TPanel
      Left = 368
      Top = 27
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #20214#25968
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 33
    end
    object Panel3: TPanel
      Left = 368
      Top = 3
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
      TabOrder = 34
    end
    object cbbClShortName: TComboBox
      Left = 430
      Top = 3
      Width = 121
      Height = 21
      Style = csDropDownList
      Enabled = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 3
    end
    object edtNum: TEdit
      Left = 430
      Top = 27
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 10
      Text = 'edtNum'
    end
    object Panel10: TPanel
      Left = 552
      Top = 27
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #23454#37325
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 35
    end
    object Panel4: TPanel
      Left = 552
      Top = 3
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #36135#29289#21517#31216
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 36
    end
    object cbbGoodsName: TComboBox
      Left = 614
      Top = 3
      Width = 121
      Height = 21
      Enabled = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 4
    end
    object edtNetWeight: TEdit
      Left = 613
      Top = 27
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 11
      Text = 'edtNetWeight'
    end
    object Panel11: TPanel
      Left = 737
      Top = 27
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #20307#31215
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 37
    end
    object Panel5: TPanel
      Left = 737
      Top = 3
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
      TabOrder = 38
    end
    object edtLoadingId: TEdit
      Left = 797
      Top = 3
      Width = 88
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 5
      Text = 'edtLoadingId'
    end
    object edtVolume: TEdit
      Left = 797
      Top = 27
      Width = 88
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 12
      Text = 'edtVolume'
    end
    object Panel13: TPanel
      Left = 885
      Top = 3
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #26041#24335
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 39
    end
    object cbbWay0: TComboBox
      Left = 947
      Top = 3
      Width = 88
      Height = 21
      Style = csDropDownList
      Enabled = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 6
      OnChange = cbbWay0Change
      Items.Strings = (
        ''
        #31354#36816
        #24555#36882
        #25955#36135
        #26588#36135
        #36827#21475
        #25302#36710
        #25253#20851
        #20854#20182)
    end
    object Panel6: TPanel
      Left = 885
      Top = 26
      Width = 31
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
      TabOrder = 40
    end
    object cbbWay: TComboBox
      Left = 916
      Top = 26
      Width = 119
      Height = 21
      Style = csDropDownList
      Enabled = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 7
    end
    object Panel19: TPanel
      Left = 314
      Top = 305
      Width = 175
      Height = 39
      TabOrder = 41
      object Label12: TLabel
        Left = 103
        Top = 20
        Width = 45
        Height = 13
        Caption = #21033#28070#29575'   '
      end
      object lbGrossPect: TLabel
        Left = 149
        Top = 20
        Width = 6
        Height = 13
        Caption = '0'
      end
      object Label10: TLabel
        Left = 7
        Top = 21
        Width = 30
        Height = 13
        Caption = #21033#28070'  '
      end
      object lbGross: TLabel
        Left = 51
        Top = 21
        Width = 6
        Height = 13
        Caption = '0'
      end
      object Label11: TLabel
        Left = 8
        Top = 3
        Width = 63
        Height = 13
        Caption = #24212#25910#24635#39069':    '
      end
      object lbSumIn: TLabel
        Left = 65
        Top = 3
        Width = 6
        Height = 13
        Alignment = taCenter
        Caption = '0'
      end
      object Label6: TLabel
        Left = 104
        Top = 3
        Width = 63
        Height = 13
        Caption = #24212#20184#24635#39069':    '
      end
      object lbSumOut: TLabel
        Left = 161
        Top = 3
        Width = 6
        Height = 13
        Alignment = taCenter
        Caption = '0'
      end
    end
    object edtInUnitPrice: TEdit
      Left = 176
      Top = 118
      Width = 70
      Height = 21
      ImeName = #35895#27468#25340#38899#36755#20837#27861' 2'
      TabOrder = 42
    end
    object edtOutUnitPrice: TEdit
      Left = 580
      Top = 119
      Width = 70
      Height = 21
      ImeName = #35895#27468#25340#38899#36755#20837#27861' 2'
      TabOrder = 43
    end
    object Panel30: TPanel
      Left = 886
      Top = 51
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #20854#20182#36884#24452
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 44
    end
    object edtWayOther: TEdit
      Left = 947
      Top = 51
      Width = 88
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 13
    end
    object Panel14: TPanel
      Left = 0
      Top = 50
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #26159#21542#21040#36135
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 45
    end
    object cbbIsArrival: TComboBox
      Left = 62
      Top = 50
      Width = 121
      Height = 21
      Style = csDropDownList
      Enabled = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      ItemIndex = 0
      TabOrder = 46
      Text = 'N'
      OnChange = cbbOpCodeSlChange
      Items.Strings = (
        'N'
        'Y')
    end
    object Panel15: TPanel
      Left = 184
      Top = 50
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #21040#36135#26085#26399
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 47
    end
  end
  object edtDebug: TEdit
    Left = 704
    Top = 0
    Width = 65
    Height = 21
    ImeName = #35895#27468#25340#38899#36755#20837#27861' 2'
    TabOrder = 8
    Text = 'ed'
    Visible = False
  end
  object Button1: TButton
    Left = 960
    Top = 0
    Width = 75
    Height = 25
    Caption = #26368#23567#21270
    TabOrder = 9
    OnClick = Button1Click
  end
  object btnQry: TButton
    Left = 0
    Top = 0
    Width = 63
    Height = 25
    Caption = #26597#35810
    TabOrder = 10
    OnClick = btnQryClick
  end
  object Panel21: TPanel
    Left = 0
    Top = 378
    Width = 1041
    Height = 7
    Color = 16349446
    TabOrder = 11
  end
  object Panel17: TPanel
    Left = 0
    Top = 24
    Width = 1043
    Height = 7
    Color = 16349446
    TabOrder = 12
  end
  object edtQryOId: TEdit
    Left = 64
    Top = 2
    Width = 120
    Height = 21
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    TabOrder = 13
    Text = 'edtQryOId'
  end
  object Panel12: TPanel
    Left = 2
    Top = 102
    Width = 60
    Height = 21
    BevelInner = bvLowered
    BevelOuter = bvLowered
    Caption = #25910#27454#24773#20917
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentColor = True
    ParentFont = False
    TabOrder = 14
  end
  object cbbCondIn: TComboBox
    Left = 64
    Top = 102
    Width = 121
    Height = 21
    Style = csDropDownList
    Enabled = False
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    ItemHeight = 13
    ItemIndex = 0
    TabOrder = 15
    Text = 'N'
    OnChange = cbbOpCodeSlChange
    Items.Strings = (
      'N'
      'Y')
  end
  object Panel16: TPanel
    Left = 186
    Top = 102
    Width = 60
    Height = 21
    BevelInner = bvLowered
    BevelOuter = bvLowered
    Caption = #25910#27454#26085#26399
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentColor = True
    ParentFont = False
    TabOrder = 16
  end
  object dtpCondIn: TDateTimePicker
    Left = 248
    Top = 101
    Width = 120
    Height = 21
    CalAlignment = dtaLeft
    Date = 40894.3857962963
    Time = 40894.3857962963
    DateFormat = dfShort
    DateMode = dmComboBox
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    Kind = dtkDate
    ParseInput = False
    TabOrder = 17
  end
  object Panel18: TPanel
    Left = 371
    Top = 102
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
    TabOrder = 18
  end
  object cbbInBank: TComboBox
    Left = 433
    Top = 102
    Width = 90
    Height = 21
    Style = csDropDownList
    Enabled = False
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    ItemHeight = 13
    TabOrder = 19
    OnChange = cbbOpCodeSlChange
    Items.Strings = (
      #20013#34892
      #20892#34892
      #24037#34892
      #25307#34892)
  end
  object Panel20: TPanel
    Left = 522
    Top = 102
    Width = 60
    Height = 21
    BevelInner = bvLowered
    BevelOuter = bvLowered
    Caption = #22238#25187#24773#20917
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentColor = True
    ParentFont = False
    TabOrder = 20
  end
  object cbbCondKB: TComboBox
    Left = 584
    Top = 102
    Width = 121
    Height = 21
    Style = csDropDownList
    Enabled = False
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    ItemHeight = 13
    ItemIndex = 0
    TabOrder = 21
    Text = 'N'
    OnChange = cbbOpCodeSlChange
    Items.Strings = (
      'N'
      'Y')
  end
  object Panel23: TPanel
    Left = 706
    Top = 102
    Width = 60
    Height = 21
    BevelInner = bvLowered
    BevelOuter = bvLowered
    Caption = #25903#20184#26085#26399
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentColor = True
    ParentFont = False
    TabOrder = 22
  end
  object dtpCondKB: TDateTimePicker
    Left = 768
    Top = 101
    Width = 120
    Height = 21
    CalAlignment = dtaLeft
    Date = 40894.3857962963
    Time = 40894.3857962963
    DateFormat = dfShort
    DateMode = dmComboBox
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    Kind = dtkDate
    ParseInput = False
    TabOrder = 23
  end
  object Panel24: TPanel
    Left = 891
    Top = 102
    Width = 60
    Height = 21
    BevelInner = bvLowered
    BevelOuter = bvLowered
    Caption = #25903#20184#38134#34892
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentColor = True
    ParentFont = False
    TabOrder = 24
  end
  object cbbKBBank: TComboBox
    Left = 953
    Top = 102
    Width = 84
    Height = 21
    Style = csDropDownList
    Enabled = False
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    ItemHeight = 13
    TabOrder = 25
    OnChange = cbbOpCodeSlChange
    Items.Strings = (
      #20013#34892
      #20892#34892
      #24037#34892
      #25307#34892)
  end
  object TrayIcon1: TTrayIcon
    Hint = 'ASI'
    Hide = True
    RestoreOn = imDoubleClick
    PopupMenuOn = imNone
    Left = 648
    Top = 65530
  end
end
