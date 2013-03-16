object OpQryForm: TOpQryForm
  Left = 238
  Top = 136
  Width = 1083
  Height = 512
  Caption = #25805#20316#31649#29702'-'#26597#35810
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
  object plQuery: TPanel
    Left = 2
    Top = 1
    Width = 1063
    Height = 50
    TabOrder = 0
    object Panel15: TPanel
      Left = 1
      Top = 2
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
      TabOrder = 0
    end
    object edtQryOId: TEdit
      Left = 64
      Top = 2
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 1
    end
    object Panel20: TPanel
      Left = 367
      Top = 25
      Width = 63
      Height = 21
      Alignment = taLeftJustify
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #26085#26399
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 2
      object cbIsQryByDate: TCheckBox
        Left = 45
        Top = 4
        Width = 16
        Height = 17
        Caption = 'cbIsQryByDate'
        TabOrder = 0
      end
    end
    object dtpQryDateBegin: TDateTimePicker
      Left = 429
      Top = 25
      Width = 82
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
      Left = 512
      Top = 25
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
    object Panel14: TPanel
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
      TabOrder = 5
    end
    object cbbQryGoodsSrc: TComboBox
      Left = 62
      Top = 27
      Width = 121
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 6
      Items.Strings = (
        ''
        'GZ'
        'HK'
        'SZ'
        'HP')
    end
    object Panel16: TPanel
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
      TabOrder = 7
    end
    object cbbQryGoodsDst: TComboBox
      Left = 246
      Top = 27
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 8
      Items.Strings = (
        '')
    end
    object cbbQryWay: TComboBox
      Left = 846
      Top = 3
      Width = 210
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 9
      Items.Strings = (
        '')
    end
    object Panel24: TPanel
      Left = 813
      Top = 3
      Width = 32
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
      TabOrder = 10
    end
    object cbbQryWay0: TComboBox
      Left = 763
      Top = 3
      Width = 50
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 11
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
    object Panel25: TPanel
      Left = 701
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
      TabOrder = 12
    end
    object edtQryLoadingId: TEdit
      Left = 613
      Top = 3
      Width = 88
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 13
    end
    object Panel26: TPanel
      Left = 553
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
      TabOrder = 14
    end
    object cbbQryClShortName: TComboBox
      Left = 430
      Top = 3
      Width = 121
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 15
      Items.Strings = (
        '')
    end
    object Panel28: TPanel
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
      TabOrder = 16
    end
    object cbbQryOpCodeSl: TComboBox
      Left = 246
      Top = 3
      Width = 121
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 17
      OnChange = cbbQryOpCodeSlChange
      Items.Strings = (
        '')
    end
    object Panel29: TPanel
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
      TabOrder = 18
    end
    object Panel18: TPanel
      Left = 598
      Top = 24
      Width = 62
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #21040#36135#24773#20917
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 19
    end
    object cbbIsArrival: TComboBox
      Left = 662
      Top = 24
      Width = 56
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 20
      Items.Strings = (
        ''
        #26159
        #21542)
    end
    object btnQry: TButton
      Left = 990
      Top = 24
      Width = 63
      Height = 23
      Caption = #26597#35810
      TabOrder = 21
      OnClick = btnQryClick
    end
  end
  object lvOpDetail: TListView
    Left = 1
    Top = 52
    Width = 1064
    Height = 397
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
      end>
    FlatScrollBars = True
    GridLines = True
    ReadOnly = True
    RowSelect = True
    TabOrder = 1
    ViewStyle = vsReport
    OnMouseDown = lvOpDetailMouseDown
  end
  object Panel1: TPanel
    Left = 0
    Top = 448
    Width = 1065
    Height = 25
    TabOrder = 2
    object Label1: TLabel
      Left = 8
      Top = 4
      Width = 27
      Height = 13
      Caption = #24635#35745':'
    end
    object Label2: TLabel
      Left = 40
      Top = 4
      Width = 27
      Height = 13
      Caption = #31080#25968' '
    end
    object lbTotalCnt: TLabel
      Left = 66
      Top = 4
      Width = 6
      Height = 13
      Caption = '0'
    end
    object Label4: TLabel
      Left = 128
      Top = 4
      Width = 27
      Height = 13
      Caption = #21033#28070' '
    end
    object lbTotalLiRun: TLabel
      Left = 155
      Top = 4
      Width = 6
      Height = 13
      Caption = '0'
    end
    object Label6: TLabel
      Left = 224
      Top = 4
      Width = 17
      Height = 13
      Caption = 'KB '
    end
    object lbTotalKB: TLabel
      Left = 242
      Top = 4
      Width = 6
      Height = 13
      Caption = '0'
    end
  end
  object PopupMenu1: TPopupMenu
    Left = 864
    Top = 96
    object N21: TMenuItem
      Caption = #24212#25910#24212#20184
      OnClick = N21Click
    end
    object N31: TMenuItem
      Caption = #36134#21333
      OnClick = N31Click
    end
  end
end
