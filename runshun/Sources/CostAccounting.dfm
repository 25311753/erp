object CostAccountingForm: TCostAccountingForm
  Left = 1337
  Top = -92
  Width = 1265
  Height = 764
  Caption = #25104#26412#26680#31639
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
  object plQry: TPanel
    Left = -1
    Top = 25
    Width = 1245
    Height = 46
    Color = clSkyBlue
    TabOrder = 0
    object lbGoodsPerf: TLabel
      Left = 168
      Top = 304
      Width = 58
      Height = 13
      Caption = 'lbGoodsPerf'
    end
    object edtCid: TEdit
      Left = 61
      Top = 1
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 0
    end
    object edtDeclareId: TEdit
      Left = 243
      Top = 1
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 1
    end
    object edtContainerinfo: TEdit
      Left = 851
      Top = 1
      Width = 231
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 2
    end
    object edtClient: TEdit
      Left = 426
      Top = 1
      Width = 121
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 3
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
      TabOrder = 4
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
      TabOrder = 5
    end
    object Panel7: TPanel
      Left = 365
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
      TabOrder = 6
    end
    object Panel9: TPanel
      Left = 791
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
      TabOrder = 7
    end
    object Panel20: TPanel
      Left = 547
      Top = 1
      Width = 74
      Height = 21
      Alignment = taLeftJustify
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #25253#20851#26085#26399
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 8
    end
    object cbIsQryByDate: TCheckBox
      Left = 605
      Top = 3
      Width = 16
      Height = 17
      Caption = 'cbIsQryByDate'
      TabOrder = 9
    end
    object dtpQryAcceptDate: TDateTimePicker
      Left = 622
      Top = 1
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
      TabOrder = 10
    end
    object dtpQryAcceptDateEnd: TDateTimePicker
      Left = 706
      Top = 1
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
      TabOrder = 11
    end
    object Panel1: TPanel
      Left = 1
      Top = 23
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #22791#27880
      Color = clSkyBlue
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 12
    end
    object edtRemark: TEdit
      Left = 61
      Top = 23
      Width = 728
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 13
    end
    object Panel2: TPanel
      Left = 791
      Top = 23
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #24635#25910#20837
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 14
    end
    object Panel5: TPanel
      Left = 919
      Top = 23
      Width = 61
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #24635#25104#26412
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 15
    end
    object Panel6: TPanel
      Left = 1047
      Top = 23
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #24635#21033#28070
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 16
    end
    object edtIn: TEdit
      Left = 852
      Top = 23
      Width = 65
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ReadOnly = True
      TabOrder = 17
    end
    object edtBase: TEdit
      Left = 980
      Top = 23
      Width = 65
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ReadOnly = True
      TabOrder = 18
    end
    object edtPure: TEdit
      Left = 1108
      Top = 23
      Width = 65
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ReadOnly = True
      TabOrder = 19
    end
  end
  object plMod: TPanel
    Left = 0
    Top = 78
    Width = 1245
    Height = 637
    Color = clActiveBorder
    TabOrder = 1
    object cbb1: TComboBox
      Left = 1
      Top = 2
      Width = 145
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 0
    end
    object cbb2: TComboBox
      Left = 257
      Top = 2
      Width = 145
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 2
    end
    object cbb3: TComboBox
      Left = 516
      Top = 2
      Width = 145
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 4
    end
    object cbb4: TComboBox
      Left = 768
      Top = 2
      Width = 145
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 6
    end
    object cbb5: TComboBox
      Left = 1017
      Top = 2
      Width = 145
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 8
    end
    object cbb6: TComboBox
      Left = 1
      Top = 25
      Width = 144
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 10
    end
    object cbb7: TComboBox
      Left = 257
      Top = 25
      Width = 145
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 12
    end
    object cbb8: TComboBox
      Left = 516
      Top = 25
      Width = 145
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 14
    end
    object cbb9: TComboBox
      Left = 768
      Top = 25
      Width = 145
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 16
    end
    object cbb10: TComboBox
      Left = 1017
      Top = 25
      Width = 145
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 18
    end
    object edtCharge1: TEdit
      Left = 145
      Top = 2
      Width = 80
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 1
    end
    object edtCharge2: TEdit
      Left = 404
      Top = 2
      Width = 80
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 3
    end
    object edtCharge3: TEdit
      Left = 663
      Top = 2
      Width = 80
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 5
    end
    object edtCharge4: TEdit
      Left = 914
      Top = 2
      Width = 80
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 7
    end
    object edtCharge5: TEdit
      Left = 1163
      Top = 2
      Width = 80
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 9
    end
    object edtCharge6: TEdit
      Left = 146
      Top = 25
      Width = 79
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 11
    end
    object edtCharge7: TEdit
      Left = 404
      Top = 25
      Width = 80
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 13
    end
    object edtCharge8: TEdit
      Left = 662
      Top = 25
      Width = 80
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 15
    end
    object edtCharge9: TEdit
      Left = 914
      Top = 25
      Width = 80
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 17
    end
    object edtCharge10: TEdit
      Left = 1163
      Top = 25
      Width = 80
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 19
    end
    object edtBaseCost: TEdit
      Left = 1164
      Top = 51
      Width = 80
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      TabOrder = 20
    end
    object Panel10: TPanel
      Left = 1063
      Top = 51
      Width = 100
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #25253#20851#22522#26412#25104#26412
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 21
    end
    object Panel11: TPanel
      Left = -6
      Top = 75
      Width = 1251
      Height = 7
      Color = 16349446
      TabOrder = 22
    end
  end
  object btnMod: TButton
    Left = 75
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
    TabOrder = 2
    OnClick = btnModClick
  end
  object btnQuery: TButton
    Left = 0
    Top = 0
    Width = 75
    Height = 25
    Caption = #26597#35810
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 3
    OnClick = btnQueryClick
  end
  object btnDump: TButton
    Left = 431
    Top = 0
    Width = 85
    Height = 25
    Caption = #23548#20986
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 4
    Visible = False
    OnClick = btnDumpClick
  end
  object lstViewPure: TListView
    Left = 776
    Top = 4
    Width = 171
    Height = 19
    Columns = <
      item
      end
      item
      end
      item
      end
      item
      end
      item
      end
      item
      end
      item
      end
      item
      end
      item
      end
      item
      end
      item
      end
      item
      end
      item
      end
      item
      end
      item
      end
      item
      end
      item
      end
      item
      end
      item
      end
      item
      end
      item
      end
      item
      end
      item
      end
      item
      end
      item
      end
      item
      end
      item
      end
      item
      end>
    TabOrder = 5
    ViewStyle = vsReport
    Visible = False
  end
  object btnOK: TButton
    Left = 165
    Top = 0
    Width = 75
    Height = 25
    Caption = #30830#35748
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 6
    OnClick = btnOKClick
  end
  object btnCancel: TButton
    Left = 240
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
    TabOrder = 7
    OnClick = btnCancelClick
  end
  object Panel45: TPanel
    Left = -8
    Top = 72
    Width = 1251
    Height = 7
    Color = 16349446
    TabOrder = 8
  end
  object edtDebug: TEdit
    Left = 544
    Top = 2
    Width = 273
    Height = 21
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    TabOrder = 9
    Text = 'edtDebug'
    Visible = False
  end
  object edtMockDeclareid: TEdit
    Left = 960
    Top = 0
    Width = 121
    Height = 21
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    TabOrder = 10
    Text = 'edtMockDeclareid'
    Visible = False
  end
  object Button1: TButton
    Left = 340
    Top = 0
    Width = 85
    Height = 25
    Caption = #23548#20986
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 11
    OnClick = Button1Click
  end
  object lstView: TListView
    Left = 0
    Top = 160
    Width = 1244
    Height = 539
    Columns = <
      item
        Caption = #24037#21333#21495
      end
      item
        Caption = #23458#25143#24037#21333#21495
        Width = 80
      end
      item
        Caption = #25253#20851#26085#26399
        Width = 80
      end
      item
        Caption = #32463#33829#21333#20301
        Width = 70
      end
      item
        Caption = #22996#25176#23458#25143
        Width = 80
      end
      item
        Caption = #25253#20851#21333#21495
        Width = 80
      end
      item
        Caption = #25910#20837
        Width = 80
      end
      item
        Caption = #25253#20851#22522#26412#25104#26412
        Width = 100
      end
      item
        Caption = #25552#21333#21495
      end
      item
        Caption = #26588#21495
        Width = 300
      end
      item
        Caption = #22791#27880
      end
      item
      end
      item
      end
      item
      end
      item
      end
      item
      end
      item
      end
      item
      end
      item
      end
      item
      end
      item
      end
      item
      end
      item
      end
      item
      end
      item
      end
      item
      end
      item
      end
      item
      end
      item
      end
      item
      end
      item
      end
      item
      end
      item
      end
      item
      end
      item
      end
      item
      end>
    GridLines = True
    ReadOnly = True
    RowSelect = True
    TabOrder = 12
    ViewStyle = vsReport
    OnClick = lstViewClick
    OnSelectItem = lstViewSelectItem
  end
end
