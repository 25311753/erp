object DoForm: TDoForm
  Left = -1246
  Top = -103
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #20570#21333
  ClientHeight = 686
  ClientWidth = 1198
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
  object Panel1: TPanel
    Left = -1
    Top = 25
    Width = 1197
    Height = 161
    Color = clSkyBlue
    TabOrder = 0
    object edtCid: TEdit
      Left = 61
      Top = 1
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 0
      Text = 'edtCid'
      OnKeyPress = edtCidKeyPress
    end
    object edtDeclareid: TEdit
      Left = 243
      Top = 1
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 1
      Text = 'edtDeclareid'
    end
    object edtForwardingunit: TEdit
      Left = 607
      Top = 1
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 10
      Text = 'edtForwardingunit'
    end
    object edtLicenseno: TEdit
      Left = 243
      Top = 23
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 4
      Text = 'edtLicenseno'
    end
    object edtCount: TEdit
      Left = 61
      Top = 89
      Width = 121
      Height = 21
      Color = clScrollBar
      Enabled = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 16
      Text = 'edtCount'
    end
    object cbbPack: TComboBox
      Left = 789
      Top = 1
      Width = 121
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 2
    end
    object edtLoadingid: TEdit
      Left = 61
      Top = 23
      Width = 121
      Height = 21
      Color = clScrollBar
      Enabled = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 3
      Text = 'edtLoadingid'
    end
    object edtBoatno: TEdit
      Left = 61
      Top = 45
      Width = 121
      Height = 21
      Color = clScrollBar
      Enabled = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ReadOnly = True
      TabOrder = 7
      Text = 'edtBoatno'
    end
    object edtBoatorder: TEdit
      Left = 243
      Top = 45
      Width = 121
      Height = 21
      Color = clScrollBar
      Enabled = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ReadOnly = True
      TabOrder = 59
      Text = 'edtBoatorder'
    end
    object cbbTransport: TComboBox
      Left = 425
      Top = 45
      Width = 121
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 8
    end
    object edtInnersupplyadd: TEdit
      Left = 243
      Top = 67
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 60
      Text = 'edtInnersupplyadd'
    end
    object cbbTrade: TComboBox
      Left = 425
      Top = 23
      Width = 121
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 5
    end
    object cbbZhengmian: TComboBox
      Left = 607
      Top = 23
      Width = 88
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 6
    end
    object edtOutport: TEdit
      Left = 61
      Top = 67
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 11
      Text = 'edtOutport'
    end
    object cbbBargain: TComboBox
      Left = 61
      Top = 111
      Width = 121
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 21
      OnChange = cbbBargainChange
    end
    object edtCarriage: TEdit
      Left = 243
      Top = 111
      Width = 121
      Height = 21
      Color = clScrollBar
      Enabled = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 24
      Text = 'edtCarriage'
    end
    object edtInsurance: TEdit
      Left = 425
      Top = 111
      Width = 121
      Height = 21
      Color = clScrollBar
      Enabled = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 25
      Text = 'edtInsurance'
    end
    object edtContractid: TEdit
      Left = 607
      Top = 67
      Width = 121
      Height = 21
      Enabled = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 14
      Text = 'edtContractid'
    end
    object edtNetweight: TEdit
      Left = 243
      Top = 89
      Width = 121
      Height = 21
      Color = clScrollBar
      Enabled = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 17
      Text = 'edtNetweight'
    end
    object edtSum: TEdit
      Left = 607
      Top = 89
      Width = 121
      Height = 21
      Color = clScrollBar
      Enabled = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 18
      Text = 'edtSum'
    end
    object edtAttachedoc: TEdit
      Left = 789
      Top = 67
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 15
      Text = 'edtAttachedoc'
    end
    object edtManufacturer: TEdit
      Left = 789
      Top = 89
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 20
      Text = 'edtManufacturer'
    end
    object edtMarks: TEdit
      Left = 470
      Top = 133
      Width = 259
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 23
      Text = 'edtMarks'
    end
    object edtInvoice: TEdit
      Left = 61
      Top = 133
      Width = 304
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 22
      Text = 'edtInvoice'
    end
    object cbbExcharge: TComboBox
      Left = 425
      Top = 67
      Width = 121
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 13
    end
    object cbbTargetCountry: TComboBox
      Left = 607
      Top = 45
      Width = 123
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 9
      OnChange = cbbTargetCountryChange
    end
    object cbbCurrency: TComboBox
      Left = 607
      Top = 111
      Width = 121
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 19
      OnChange = cbbCurrencyChange
    end
    object cbbAssginPort: TComboBox
      Left = 789
      Top = 45
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 12
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
      TabOrder = 26
    end
    object Panel4: TPanel
      Left = 183
      Top = 1
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #25253#20851#21333#21495
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 27
    end
    object Panel5: TPanel
      Left = 365
      Top = 1
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #32463#33829#21333#20301
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 28
    end
    object Panel6: TPanel
      Left = 547
      Top = 1
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #21457#36135#21333#20301
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 29
    end
    object Panel7: TPanel
      Left = 1
      Top = 89
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #24635#31665#25968
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 30
    end
    object Panel8: TPanel
      Left = 729
      Top = 1
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #21253#35013#26041#24335
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 31
    end
    object Panel9: TPanel
      Left = 1
      Top = 23
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
      TabOrder = 32
    end
    object Panel10: TPanel
      Left = 183
      Top = 23
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #25209#20934#25991#21495
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 33
    end
    object Panel11: TPanel
      Left = 183
      Top = 89
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #24635#20928#37325
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 34
    end
    object Panel12: TPanel
      Left = 547
      Top = 89
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #21512#35745#37329#39069
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 35
    end
    object Panel13: TPanel
      Left = 1
      Top = 45
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #33337#32534
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 36
    end
    object Panel14: TPanel
      Left = 183
      Top = 45
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
      TabOrder = 37
    end
    object Panel15: TPanel
      Left = 365
      Top = 45
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #36816#36755#26041#24335
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 38
    end
    object Panel16: TPanel
      Left = 547
      Top = 45
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #36816#25269#22269
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 39
    end
    object Panel17: TPanel
      Left = 729
      Top = 45
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #25351#36816#28207
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 40
    end
    object Panel18: TPanel
      Left = 365
      Top = 23
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #36152#26131#26041#24335
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 41
    end
    object Panel19: TPanel
      Left = 547
      Top = 23
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #24449#20813#24615#36136
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 42
    end
    object Panel20: TPanel
      Left = 695
      Top = 23
      Width = 34
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #21830#21495
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 43
    end
    object Panel21: TPanel
      Left = 1
      Top = 67
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #20986#21475#21475#23736
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 44
    end
    object Panel22: TPanel
      Left = 183
      Top = 67
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #22659#20869#36135#28304#22320
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -9
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 45
    end
    object Panel23: TPanel
      Left = 365
      Top = 67
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #32467#27719#26041#24335
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 46
    end
    object Panel24: TPanel
      Left = 547
      Top = 67
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #21512#21516#21327#35758#21495
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -9
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 47
    end
    object Panel25: TPanel
      Left = 547
      Top = 111
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #24065#21046
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 48
    end
    object Panel26: TPanel
      Left = 1
      Top = 111
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #25104#20132#26041#24335
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 49
    end
    object Panel27: TPanel
      Left = 183
      Top = 111
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #36816#36153
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 50
    end
    object Panel28: TPanel
      Left = 365
      Top = 111
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #20445#36153
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 51
    end
    object Panel29: TPanel
      Left = 729
      Top = 67
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #38543#38468#21333#35777
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 52
    end
    object Panel30: TPanel
      Left = 729
      Top = 89
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #29983#20135#21378#23478
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 53
    end
    object Panel31: TPanel
      Left = 1
      Top = 133
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #21457#31080#25260#22836
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 54
    end
    object Panel32: TPanel
      Left = 366
      Top = 133
      Width = 104
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #26631#35760#21787#30721#21450#22791#27880
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 55
    end
    object Panel2: TPanel
      Left = 365
      Top = 89
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #24635#27611#37325
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 56
    end
    object edtGrossWeight: TEdit
      Left = 425
      Top = 89
      Width = 121
      Height = 21
      Color = clScrollBar
      Enabled = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 57
      Text = 'edtGrossWeight'
    end
    object lstViewContainer: TListView
      Left = 910
      Top = 1
      Width = 284
      Height = 152
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
      Enabled = False
      GridLines = True
      ReadOnly = True
      RowSelect = True
      TabOrder = 58
      ViewStyle = vsReport
    end
    object cbbOperunit: TComboBox
      Left = 425
      Top = 1
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 61
      OnChange = cbbOperunitChange
      OnSelect = cbbOperunitSelect
    end
    object cbbSH: TComboBox
      Left = 729
      Top = 23
      Width = 181
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 62
      OnChange = cbbSHChange
      OnSelect = cbbSHSelect
    end
  end
  object btnPrnInvoice: TButton
    Left = 0
    Top = 659
    Width = 75
    Height = 25
    Caption = #21457#31080
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 1
    OnClick = btnPrnInvoiceClick
  end
  object btnPrnPackingList: TButton
    Left = 75
    Top = 659
    Width = 75
    Height = 25
    Caption = #35013#31665#21333
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 2
    OnClick = btnPrnPackingListClick
  end
  object btnPrnContact: TButton
    Left = 150
    Top = 659
    Width = 75
    Height = 25
    Caption = #21512#21516
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 3
    OnClick = btnPrnContactClick
  end
  object btnPrnDeclare: TButton
    Left = 225
    Top = 660
    Width = 75
    Height = 24
    Caption = #25253#20851#21333
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 4
    OnClick = btnPrnDeclareClick
  end
  object dtpValidDate: TDateTimePicker
    Left = 1016
    Top = 661
    Width = 33
    Height = 21
    CalAlignment = dtaLeft
    Date = 40898.9535460995
    Time = 40898.9535460995
    DateFormat = dfShort
    DateMode = dmComboBox
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    Kind = dtkDate
    ParseInput = False
    TabOrder = 5
    Visible = False
  end
  object btnPrnAuth: TButton
    Left = 300
    Top = 659
    Width = 75
    Height = 25
    Caption = #22996#25176#20070
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 6
    OnClick = btnPrnAuthClick
  end
  object btnPrnOutBoat: TButton
    Left = 375
    Top = 659
    Width = 75
    Height = 25
    Caption = #33337#32440
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 7
    OnClick = btnPrnOutBoatClick
  end
  object btnChangeStatus: TButton
    Left = 935
    Top = 659
    Width = 75
    Height = 25
    Caption = #20570#21333#23436#27605
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 8
    Visible = False
    OnClick = btnChangeStatusClick
  end
  object btnInputGoods: TButton
    Left = 1048
    Top = 660
    Width = 75
    Height = 25
    Caption = #28155#21152#21830#21697
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 9
    Visible = False
    OnClick = btnInputGoodsClick
  end
  object Panel45: TPanel
    Left = 0
    Top = 179
    Width = 1193
    Height = 7
    Color = 16349446
    TabOrder = 10
  end
  object cbDoing: TCheckBox
    Left = 730
    Top = 159
    Width = 179
    Height = 20
    Caption = #21333#35777#22788#29702#20013
    Color = clScrollBar
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlue
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
    TabOrder = 11
    OnMouseDown = cbDoingMouseDown
  end
  object btnCancel: TButton
    Left = 257
    Top = 0
    Width = 75
    Height = 25
    Caption = #25918#24323
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 12
    OnClick = btnCancelClick
  end
  object btnMod: TButton
    Left = 107
    Top = 0
    Width = 75
    Height = 25
    Caption = #20462#25913
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 14
    OnClick = btnModClick
  end
  object btnOK: TButton
    Left = 182
    Top = 0
    Width = 75
    Height = 25
    Caption = #30830#23450
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 15
    OnClick = btnOKClick
  end
  object plDetail: TPanel
    Left = -2
    Top = 186
    Width = 1198
    Height = 474
    Caption = 'plDetail'
    TabOrder = 16
    object lstView: TListView
      Left = 0
      Top = 72
      Width = 1198
      Height = 384
      Columns = <
        item
          Caption = #21830#21697#32534#21495
          Width = 100
        end
        item
          Caption = #21830#21697#21517#31216
          Width = 130
        end
        item
          Caption = #35268#26684#22411#21495
          Width = 100
        end
        item
          Caption = #20928#37325
          Width = 80
        end
        item
          Caption = #27611#37325
          Width = 60
        end
        item
          Caption = #25968#37327
          Width = 60
        end
        item
          Caption = #31665#25968
          Width = 70
        end
        item
          Caption = #21333#20301'1'
        end
        item
          Caption = #21333#20301'2'
        end
        item
          Caption = #26368#32456#30446#30340#22269
          Width = 100
        end
        item
          Caption = #21333#20215
          Width = 70
        end
        item
          Caption = #24635#20215
          Width = 80
        end
        item
          Caption = #24065#21046
        end
        item
          Caption = #24449#20813
          Width = 70
        end
        item
          Caption = #31532#20108#25968#37327
          Width = 70
        end
        item
          Caption = #21253#35013#26041#24335
          Width = 60
        end
        item
          Caption = 'cdid'
          Width = 3
        end>
      FlatScrollBars = True
      GridLines = True
      ReadOnly = True
      RowSelect = True
      TabOrder = 0
      ViewStyle = vsReport
      OnClick = lstViewClick
      OnSelectItem = lstViewSelectItem
    end
    object Panel44: TPanel
      Left = 1
      Top = 453
      Width = 1195
      Height = 20
      BevelInner = bvLowered
      BevelOuter = bvSpace
      Color = clGradientActiveCaption
      TabOrder = 1
      object Label1: TLabel
        Left = 17
        Top = 4
        Width = 39
        Height = 13
        Caption = #21512#35745' '#65306
      end
      object Label44: TLabel
        Left = 915
        Top = 4
        Width = 38
        Height = 13
        Caption = 'Label44'
      end
      object Label43: TLabel
        Left = 575
        Top = 4
        Width = 38
        Height = 13
        Caption = 'Label43'
      end
      object Label42: TLabel
        Left = 411
        Top = 4
        Width = 38
        Height = 13
        Caption = 'Label42'
      end
      object Label41: TLabel
        Left = 334
        Top = 4
        Width = 38
        Height = 13
        Caption = 'Label41'
      end
    end
    object Panel46: TPanel
      Left = 2
      Top = 64
      Width = 1194
      Height = 7
      Color = 16349446
      TabOrder = 2
    end
    object btnAddDetail: TButton
      Left = 913
      Top = 1
      Width = 56
      Height = 23
      Caption = #28155#21152
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 3
      OnClick = btnAddDetailClick
    end
    object Panel33: TPanel
      Left = 183
      Top = 1
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #21830#21697#21517#31216
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 4
    end
    object cbbMname: TComboBox
      Left = 243
      Top = 1
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 5
      Text = 'cbbMname'
      OnChange = cbbMnameChange
      OnSelect = cbbMnameSelect
    end
    object Panel39: TPanel
      Left = 548
      Top = 43
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #27611#37325
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 19
    end
    object edtNetWeight1: TEdit
      Left = 62
      Top = 43
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 9
      Text = 'edtNetWeight1'
    end
    object Panel40: TPanel
      Left = 2
      Top = 22
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #31532#19968#25968#37327
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 20
    end
    object Panel34: TPanel
      Left = 365
      Top = 1
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #21830#21697#32534#21495
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 21
    end
    object edtMCode: TEdit
      Left = 426
      Top = 1
      Width = 121
      Height = 21
      Color = clScrollBar
      Enabled = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ReadOnly = True
      TabOrder = 15
      Text = 'edtMCode'
    end
    object edtGrossWeight1: TEdit
      Left = 608
      Top = 43
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 12
      Text = 'edtGrossWeight1'
    end
    object Panel41: TPanel
      Left = 183
      Top = 43
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #31665#25968
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 22
    end
    object Panel35: TPanel
      Left = 548
      Top = 1
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #35268#26684#22411#21495
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 23
    end
    object edtSpec: TEdit
      Left = 608
      Top = 1
      Width = 121
      Height = 21
      Color = clScrollBar
      Enabled = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ReadOnly = True
      TabOrder = 16
      Text = 'edtSpec'
    end
    object edtCount1: TEdit
      Left = 62
      Top = 22
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 7
      Text = 'edtCount1'
      OnChange = edtCount1Change
    end
    object Panel42: TPanel
      Left = 365
      Top = 21
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #31532#20108#25968#37327
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 24
    end
    object edtCount2nd: TEdit
      Left = 426
      Top = 21
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 8
      Text = '0'
    end
    object Panel36: TPanel
      Left = 183
      Top = 22
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #21333#20301'1'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 25
    end
    object edtFirstmeasunit: TEdit
      Left = 243
      Top = 22
      Width = 121
      Height = 21
      Color = clScrollBar
      Enabled = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ReadOnly = True
      TabOrder = 17
      Text = 'edtFirstmeasunit'
    end
    object Panel43: TPanel
      Left = 2
      Top = 43
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #20928#37325
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 26
    end
    object edtCasecnt: TEdit
      Left = 243
      Top = 43
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 10
    end
    object Panel37: TPanel
      Left = 548
      Top = 22
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #21333#20301'2'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 27
    end
    object edtSecondmeasunit: TEdit
      Left = 608
      Top = 22
      Width = 121
      Height = 21
      Color = clScrollBar
      Enabled = False
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ReadOnly = True
      TabOrder = 18
      Text = 'edtSecondmeasunit'
    end
    object edtCdid: TEdit
      Left = 902
      Top = 0
      Width = 11
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 28
      Text = 'edtCdid'
      Visible = False
    end
    object edtMid1: TEdit
      Left = 900
      Top = 0
      Width = 11
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 29
      Text = 'edtMid1'
      Visible = False
    end
    object Panel38: TPanel
      Left = 730
      Top = 1
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #21333#20215
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 30
    end
    object edtUnitprice: TEdit
      Left = 791
      Top = 1
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 6
      Text = 'edtUnitprice'
      OnChange = edtUnitpriceChange
    end
    object btnModDetail: TButton
      Left = 969
      Top = 1
      Width = 56
      Height = 23
      Caption = #20462#25913
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 31
      OnClick = btnModDetailClick
    end
    object btnDelDetail: TButton
      Left = 1025
      Top = 1
      Width = 56
      Height = 23
      Caption = #21024#38500
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 32
      OnClick = btnDelDetailClick
    end
    object edtDebug: TEdit
      Left = 904
      Top = -1
      Width = 7
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 33
      Text = 'edtDebug'
      Visible = False
    end
    object btnOkDetail: TButton
      Left = 1084
      Top = 1
      Width = 56
      Height = 23
      Caption = #30830#23450
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 13
      OnClick = btnOkDetailClick
    end
    object btnCancleDetail: TButton
      Left = 1141
      Top = 1
      Width = 56
      Height = 23
      Caption = #25918#24323
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 14
      OnClick = btnCancleDetailClick
    end
    object Panel47: TPanel
      Left = 365
      Top = 43
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #21253#35013#26041#24335
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 34
    end
    object cbbPkName: TComboBox
      Left = 426
      Top = 43
      Width = 121
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 11
    end
    object Panel48: TPanel
      Left = 2
      Top = 0
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #39033#21495
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 35
    end
    object edtNo: TEdit
      Left = 62
      Top = 0
      Width = 121
      Height = 21
      Color = clScrollBar
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 36
      OnChange = edtNoChange
    end
  end
  object btnQueryUp: TButton
    Left = 0
    Top = 0
    Width = 75
    Height = 25
    Caption = #26597'   '#35810
    Font.Charset = DEFAULT_CHARSET
    Font.Color = 4227327
    Font.Height = -12
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 17
    OnClick = btnQueryUpClick
  end
  object cbbCurrencyId: TComboBox
    Left = 334
    Top = -1
    Width = 27
    Height = 21
    Enabled = False
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    ItemHeight = 13
    TabOrder = 18
    Text = 'cbbCurrencyId'
    Visible = False
  end
  object Button1: TButton
    Left = 1129
    Top = 1
    Width = 64
    Height = 23
    Caption = #26368#23567#21270
    TabOrder = 19
    OnClick = Button1Click
  end
  object btnWMZ: TButton
    Left = 463
    Top = 659
    Width = 75
    Height = 25
    Caption = #26080#26408#36136#22768#26126
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 20
    OnClick = btnWMZClick
  end
  object btnYSQRS: TButton
    Left = 539
    Top = 659
    Width = 75
    Height = 25
    Caption = #39564#25910#30830#35748#20070
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 21
    OnClick = btnYSQRSClick
  end
  object btnSCCK: TButton
    Left = 614
    Top = 659
    Width = 126
    Height = 25
    Caption = #24066#22330#37319#36141#31526#21512#24615#22768#26126
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 22
    OnClick = btnSCCKClick
  end
  object btnCIQ: TButton
    Left = 855
    Top = 660
    Width = 75
    Height = 25
    Caption = #23548#20986'CIQ'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 23
    OnClick = btnCIQClick
  end
  object btnQYCNS: TButton
    Left = 740
    Top = 659
    Width = 75
    Height = 25
    Caption = #20225#19994#25215#35834#20070
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 24
    OnClick = btnQYCNSClick
  end
  object Edit1: TEdit
    Left = 968
    Top = 0
    Width = 121
    Height = 21
    ImeName = #35895#27468#25340#38899#36755#20837#27861' 2'
    TabOrder = 25
    Text = 'Edit1'
    Visible = False
  end
  object edtOperunitAddress: TEdit
    Left = 380
    Top = 1
    Width = 21
    Height = 21
    Color = clScrollBar
    Enabled = False
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    ReadOnly = True
    TabOrder = 26
    Visible = False
  end
  object edtOperunitTel: TEdit
    Left = 404
    Top = 1
    Width = 21
    Height = 21
    Color = clScrollBar
    Enabled = False
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    ReadOnly = True
    TabOrder = 27
    Visible = False
  end
  object edtSHAddress: TEdit
    Left = 428
    Top = 1
    Width = 21
    Height = 21
    Color = clScrollBar
    Enabled = False
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    ReadOnly = True
    TabOrder = 28
    Visible = False
  end
  object edtSHTel: TEdit
    Left = 452
    Top = 1
    Width = 21
    Height = 21
    Color = clScrollBar
    Enabled = False
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    ReadOnly = True
    TabOrder = 29
    Visible = False
  end
  object Panel49: TPanel
    Left = 728
    Top = 209
    Width = 60
    Height = 21
    BevelInner = bvLowered
    BevelOuter = bvLowered
    Caption = #24635#20215
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 30
  end
  object edtTotalPrice: TEdit
    Left = 789
    Top = 209
    Width = 121
    Height = 21
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    TabOrder = 13
    OnChange = edtTotalPriceChange
  end
  object TrayIcon1: TTrayIcon
    Hide = True
    RestoreOn = imDoubleClick
    PopupMenuOn = imNone
    Left = 1096
  end
end
