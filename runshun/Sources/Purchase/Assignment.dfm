object AssignmentForm: TAssignmentForm
  Left = 1421
  Top = -194
  Width = 1091
  Height = 775
  BorderIcons = [biSystemMenu, biMinimize]
  Caption = #21333#35777#36319#36394
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
  object plAssgin: TPanel
    Left = 0
    Top = 299
    Width = 1073
    Height = 438
    Color = clInactiveCaption
    TabOrder = 0
    object Panel1: TPanel
      Left = -1
      Top = -1
      Width = 799
      Height = 45
      Color = clSkyBlue
      TabOrder = 0
      object edtCid: TEdit
        Left = 60
        Top = 1
        Width = 121
        Height = 21
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        TabOrder = 0
        OnKeyPress = edtCidKeyPress
      end
      object edtLadingId: TEdit
        Left = 435
        Top = 1
        Width = 121
        Height = 21
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        TabOrder = 1
      end
      object cbbStatus: TComboBox
        Left = 618
        Top = 1
        Width = 78
        Height = 21
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        ItemHeight = 13
        TabOrder = 2
      end
      object btnQuery: TButton
        Left = 722
        Top = 23
        Width = 74
        Height = 20
        Caption = #26597#35810
        TabOrder = 3
        OnClick = btnQueryClick
      end
      object dtpAcceptDateBegin: TDateTimePicker
        Left = 436
        Top = 23
        Width = 89
        Height = 21
        CalAlignment = dtaLeft
        Date = 40899.2891441204
        Time = 40899.2891441204
        DateFormat = dfShort
        DateMode = dmComboBox
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        Kind = dtkDate
        ParseInput = False
        TabOrder = 4
      end
      object dtpAcceptDateEnd: TDateTimePicker
        Left = 529
        Top = 23
        Width = 89
        Height = 21
        CalAlignment = dtaLeft
        Date = 40899.2891578472
        Time = 40899.2891578472
        DateFormat = dfShort
        DateMode = dmComboBox
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        Kind = dtkDate
        ParseInput = False
        TabOrder = 5
      end
      object cbbTransport: TComboBox
        Left = 60
        Top = 22
        Width = 121
        Height = 21
        Style = csDropDownList
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        ItemHeight = 13
        TabOrder = 6
      end
      object edtOperUnit: TEdit
        Left = 241
        Top = 1
        Width = 121
        Height = 21
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        TabOrder = 7
      end
      object edtContainerNo: TEdit
        Left = 241
        Top = 22
        Width = 121
        Height = 21
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        TabOrder = 8
      end
      object Panel3: TPanel
        Left = 1
        Top = 1
        Width = 60
        Height = 21
        BevelInner = bvLowered
        BevelOuter = bvLowered
        Caption = #24037#21333#21495
        Color = clSkyBlue
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 9
      end
      object Panel5: TPanel
        Left = 182
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
        TabOrder = 10
      end
      object Panel9: TPanel
        Left = 362
        Top = 1
        Width = 74
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
        TabOrder = 11
      end
      object Panel15: TPanel
        Left = 1
        Top = 22
        Width = 60
        Height = 21
        BevelInner = bvLowered
        BevelOuter = bvLowered
        Caption = #36816#36755#24037#20855
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentColor = True
        ParentFont = False
        TabOrder = 12
      end
      object Panel19: TPanel
        Left = 182
        Top = 22
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
        TabOrder = 13
      end
      object Panel20: TPanel
        Left = 362
        Top = 23
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
        TabOrder = 14
      end
      object cbIsQryByDate: TCheckBox
        Left = 418
        Top = 26
        Width = 16
        Height = 17
        Caption = 'cbIsQryByDate'
        TabOrder = 15
      end
      object Panel2: TPanel
        Left = 558
        Top = 1
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
        TabOrder = 16
      end
      object dtpPassDate: TDateTimePicker
        Left = 624
        Top = 23
        Width = 63
        Height = 19
        CalAlignment = dtaLeft
        Date = 40957.5906902778
        Time = 40957.5906902778
        DateFormat = dfShort
        DateMode = dmComboBox
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        Kind = dtkDate
        ParseInput = False
        TabOrder = 17
        Visible = False
      end
    end
    object lstViewSH: TListView
      Left = 440
      Top = 45
      Width = 98
      Height = 344
      Columns = <
        item
          Caption = #28023#20851#23457#26680#20013
          Width = 90
        end>
      MultiSelect = True
      ReadOnly = True
      RowSelect = True
      TabOrder = 1
      ViewStyle = vsReport
    end
    object lstViewCYZ: TListView
      Left = 279
      Top = 269
      Width = 98
      Height = 153
      Columns = <
        item
          Caption = #26597#39564#20013
          Width = 90
        end>
      MultiSelect = True
      ReadOnly = True
      RowSelect = True
      TabOrder = 2
      ViewStyle = vsReport
    end
    object lstViewYFX: TListView
      Left = 616
      Top = 45
      Width = 100
      Height = 380
      Columns = <
        item
          Caption = #24050#25918#34892
          Width = 90
        end>
      MultiSelect = True
      ReadOnly = True
      RowSelect = True
      TabOrder = 3
      ViewStyle = vsReport
    end
    object btnCheck: TButton
      Left = 380
      Top = 288
      Width = 60
      Height = 25
      Caption = '<==='
      TabOrder = 4
      OnClick = btnCheckClick
    end
    object btnPass: TButton
      Left = 544
      Top = 194
      Width = 72
      Height = 25
      Caption = '===>'
      TabOrder = 5
      OnClick = btnPassClick
    end
    object btnPass1: TButton
      Left = 391
      Top = 396
      Width = 218
      Height = 15
      Caption = '               ======================>>>'
      TabOrder = 6
      OnClick = btnPass1Click
    end
    object btnYJCZ: TButton
      Left = 722
      Top = 194
      Width = 74
      Height = 25
      Caption = '===>'
      TabOrder = 7
      OnClick = btnYJCZClick
    end
    object lstViewYJCZ: TListView
      Left = 796
      Top = 45
      Width = 95
      Height = 380
      Columns = <
        item
          Caption = #24050#20132#25918#34892#26465
          Width = 90
        end>
      MultiSelect = True
      ReadOnly = True
      RowSelect = True
      TabOrder = 8
      ViewStyle = vsReport
    end
    object lstViewDZCLZ: TListView
      Left = 177
      Top = 45
      Width = 99
      Height = 380
      Columns = <
        item
          Caption = #21333#35777#22788#29702#20013
          Width = 90
        end>
      MultiSelect = True
      ReadOnly = True
      RowSelect = True
      TabOrder = 9
      ViewStyle = vsReport
    end
    object btnSH: TButton
      Left = 282
      Top = 133
      Width = 151
      Height = 25
      Caption = '===>'
      TabOrder = 10
      OnClick = btnSHClick
    end
    object btnSH2DZCLZ: TButton
      Left = 282
      Top = 157
      Width = 151
      Height = 25
      Caption = '<==='
      TabOrder = 11
      OnClick = btnSH2DZCLZClick
    end
    object btnYFX2SH: TButton
      Left = 544
      Top = 218
      Width = 72
      Height = 25
      Caption = '<==='
      TabOrder = 12
      OnClick = btnYFX2SHClick
    end
    object btnYJCZ2YFX: TButton
      Left = 722
      Top = 218
      Width = 74
      Height = 25
      Caption = '<==='
      TabOrder = 13
      OnClick = btnYJCZ2YFXClick
    end
    object btnYFX2CYZ: TButton
      Left = 392
      Top = 410
      Width = 217
      Height = 15
      BiDiMode = bdLeftToRight
      Caption = '<<<====================='
      ParentBiDiMode = False
      TabOrder = 14
      OnClick = btnYFX2CYZClick
    end
    object btnCYZ2SH: TButton
      Left = 380
      Top = 312
      Width = 60
      Height = 25
      Caption = '===>'
      TabOrder = 15
      OnClick = btnCYZ2SHClick
    end
    object lstViewYJH: TListView
      Left = 970
      Top = 45
      Width = 97
      Height = 380
      Columns = <
        item
          Caption = #24050#25171#32467#27719#32852
          Width = 90
        end>
      MultiSelect = True
      ReadOnly = True
      RowSelect = True
      TabOrder = 16
      ViewStyle = vsReport
    end
    object btnYJH: TButton
      Left = 897
      Top = 194
      Width = 74
      Height = 25
      Caption = '===>'
      TabOrder = 17
      OnClick = btnYJHClick
    end
    object btnYJH2YJCZ: TButton
      Left = 897
      Top = 218
      Width = 74
      Height = 25
      Caption = '<==='
      TabOrder = 18
      OnClick = btnYJH2YJCZClick
    end
    object lstViewYJD: TListView
      Left = 2
      Top = 48
      Width = 100
      Height = 380
      Columns = <
        item
          Caption = #24050#25509#21333
          Width = 90
        end>
      MultiSelect = True
      ReadOnly = True
      RowSelect = True
      TabOrder = 19
      ViewStyle = vsReport
    end
    object btnDZCLZ: TButton
      Left = 104
      Top = 194
      Width = 72
      Height = 25
      Caption = '===>'
      TabOrder = 20
      OnClick = btnDZCLZClick
    end
    object btnDZCLZ2YJD: TButton
      Left = 104
      Top = 218
      Width = 72
      Height = 25
      Caption = '<==='
      TabOrder = 21
      OnClick = btnDZCLZ2YJDClick
    end
  end
  object plQry: TPanel
    Left = 0
    Top = 0
    Width = 1072
    Height = 292
    Caption = 'plQry'
    Color = clInactiveCaption
    TabOrder = 1
    object Panel4: TPanel
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
      TabOrder = 0
    end
    object Panel18: TPanel
      Left = 366
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
      TabOrder = 1
    end
    object Panel6: TPanel
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
      TabOrder = 2
    end
    object Panel17: TPanel
      Left = 182
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
      TabOrder = 3
    end
    object edtQryCid: TEdit
      Left = 60
      Top = 2
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 4
      Text = 'edtQryCid'
      OnKeyPress = edtQryCidKeyPress
    end
    object cbbQryStatus: TComboBox
      Left = 60
      Top = 23
      Width = 121
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 5
      Items.Strings = (
        '')
    end
    object edtQryJZS: TEdit
      Left = 426
      Top = 1
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 6
      Text = 'edtQryJZS'
    end
    object edtQryLading: TEdit
      Left = 242
      Top = 1
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 7
      Text = 'edtQryLading'
    end
    object Panel7: TPanel
      Left = 181
      Top = 23
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
      TabOrder = 8
      object cbIsQryByDateUp: TCheckBox
        Left = 57
        Top = 2
        Width = 16
        Height = 17
        Caption = 'cbIsQryByDate'
        TabOrder = 0
      end
    end
    object dtpQryAcceptDate: TDateTimePicker
      Left = 256
      Top = 23
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
      TabOrder = 9
    end
    object dtpQryAcceptDateEnd: TDateTimePicker
      Left = 340
      Top = 23
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
      TabOrder = 10
    end
    object lstViewContainer: TListView
      Left = 796
      Top = 1
      Width = 275
      Height = 288
      Columns = <
        item
          Caption = #38598#35013#31665#21495
          Width = 130
        end
        item
          Caption = #26588#22411
          Width = 60
        end
        item
          Caption = #23553#26465#21495
          Width = 80
        end>
      GridLines = True
      ReadOnly = True
      RowSelect = True
      TabOrder = 11
      ViewStyle = vsReport
    end
    object lstView: TListView
      Left = 0
      Top = 45
      Width = 795
      Height = 244
      Columns = <
        item
          Caption = 'N'
          Width = 30
        end
        item
          Caption = #24037#21333#21495
          Width = 70
        end
        item
          Caption = #36135#29289#24615#36136
          Width = 60
        end
        item
          Caption = #32463#33829#21333#20301
          Width = 150
        end
        item
          Caption = #25552#21333#21495
          Width = 100
        end
        item
          Caption = #38598#35013#31665#21495
          Width = 100
        end
        item
          Caption = #20570#21333#20154
          Width = 60
        end
        item
          Caption = #25130#20851#26085#26399
          Width = 110
        end
        item
          Caption = #33337#20195
        end
        item
          Caption = #29366#24577
          Width = 60
        end
        item
          Caption = #22791#27880
          Width = 80
        end
        item
          Width = 1
        end>
      FlatScrollBars = True
      GridLines = True
      ReadOnly = True
      RowSelect = True
      TabOrder = 12
      ViewStyle = vsReport
      OnSelectItem = lstViewSelectItem
    end
    object btnQry: TButton
      Left = 637
      Top = 24
      Width = 75
      Height = 21
      Caption = #26597#35810
      TabOrder = 13
      OnClick = btnQryClick
    end
    object btnFlowTable: TButton
      Left = 712
      Top = 24
      Width = 85
      Height = 21
      Caption = #29983#25104#27969#31243#34920
      TabOrder = 14
      OnClick = btnFlowTableClick
    end
    object Panel47: TPanel
      Left = 425
      Top = 24
      Width = 41
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
      TabOrder = 15
    end
    object cbbShipAgent: TComboBox
      Left = 467
      Top = 24
      Width = 79
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 16
      Items.Strings = (
        '')
    end
    object edtDebug: TEdit
      Left = 592
      Top = 0
      Width = 121
      Height = 21
      TabOrder = 17
      Text = 'edtDebug'
      Visible = False
    end
  end
  object Panel45: TPanel
    Left = -30
    Top = 292
    Width = 1101
    Height = 7
    Color = 16349446
    TabOrder = 2
  end
end
