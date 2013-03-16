object SumMnFactForm: TSumMnFactForm
  Left = 242
  Top = 173
  Width = 633
  Height = 563
  Caption = #26448#26009#33287#24288#21830#35330#36092#32113#35336
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
  object Label1: TLabel
    Left = 104
    Top = 4
    Width = 363
    Height = 33
    Caption = #26448#26009#33287#24288#21830#35330#36092#32113#35336#26597#35426
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = #27161#26999#39636
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Panel1: TPanel
    Left = 1
    Top = 365
    Width = 616
    Height = 162
    BevelOuter = bvLowered
    TabOrder = 0
    object Label2: TLabel
      Left = 11
      Top = 63
      Width = 57
      Height = 13
      Caption = #32113#35336#36215#40670'   '
    end
    object Label3: TLabel
      Left = 167
      Top = 63
      Width = 60
      Height = 13
      Caption = #32113#35336#32066#40670'    '
    end
    object Label4: TLabel
      Left = 11
      Top = 9
      Width = 57
      Height = 13
      Caption = #26448#26009#32232#34399'   '
    end
    object Label5: TLabel
      Left = 167
      Top = 9
      Width = 60
      Height = 13
      Caption = #21697#21517#35215#26684'    '
    end
    object Label6: TLabel
      Left = 465
      Top = 9
      Width = 57
      Height = 13
      Caption = #24288#21830#31777#31281'   '
    end
    object Label9: TLabel
      Left = 10
      Top = 91
      Width = 60
      Height = 13
      Caption = #35330#36092#27425#25976'    '
    end
    object Label10: TLabel
      Left = 167
      Top = 91
      Width = 60
      Height = 13
      Caption = #26412#21934#37329#38989'    '
    end
    object Label11: TLabel
      Left = 383
      Top = 9
      Width = 48
      Height = 13
      Caption = #37319#36092#37096#38272
    end
    object btnQuery: TButton
      Left = 305
      Top = 133
      Width = 75
      Height = 25
      Caption = #26597'     '#35426
      TabOrder = 0
      OnClick = btnQueryClick
    end
    object btntoExcel: TButton
      Left = 459
      Top = 133
      Width = 75
      Height = 25
      Caption = #36681'Excel'
      TabOrder = 1
      OnClick = btntoExcelClick
    end
    object btnQuit: TButton
      Left = 536
      Top = 133
      Width = 75
      Height = 25
      Caption = #36864#20986
      TabOrder = 2
      OnClick = btnQuitClick
    end
    object DateTimePicker1: TDateTimePicker
      Left = 70
      Top = 55
      Width = 93
      Height = 21
      CalAlignment = dtaLeft
      Date = 38581.691412037
      Time = 38581.691412037
      DateFormat = dfShort
      DateMode = dmComboBox
      Kind = dtkDate
      ParseInput = False
      TabOrder = 3
    end
    object DateTimePicker2: TDateTimePicker
      Left = 230
      Top = 55
      Width = 104
      Height = 21
      CalAlignment = dtaLeft
      Date = 38581.6914183565
      Time = 38581.6914183565
      DateFormat = dfShort
      DateMode = dmComboBox
      Kind = dtkDate
      ParseInput = False
      TabOrder = 4
    end
    object edtMater: TEdit
      Left = 10
      Top = 25
      Width = 154
      Height = 21
      CharCase = ecUpperCase
      Enabled = False
      TabOrder = 5
      OnExit = edtMaterExit
    end
    object edtMnname: TEdit
      Left = 166
      Top = 25
      Width = 168
      Height = 21
      Enabled = False
      TabOrder = 6
    end
    object btnQueryMT: TButton
      Left = 107
      Top = 8
      Width = 55
      Height = 15
      Caption = #32232#34399#25552#21462
      Enabled = False
      TabOrder = 7
      OnClick = btnQueryMTClick
    end
    object btnSpeerFactSearch: TButton
      Left = 522
      Top = 8
      Width = 62
      Height = 15
      Caption = #24288#21830#25552#21462
      Enabled = False
      TabOrder = 8
      OnClick = btnSpeerFactSearchClick
    end
    object lstSpeerFact: TComboBox
      Left = 465
      Top = 25
      Width = 121
      Height = 21
      Enabled = False
      ItemHeight = 13
      TabOrder = 9
    end
    object edtStanderN: TEdit
      Left = 70
      Top = 83
      Width = 57
      Height = 21
      Enabled = False
      TabOrder = 10
    end
    object edtStanderP: TEdit
      Left = 230
      Top = 83
      Width = 103
      Height = 21
      Enabled = False
      TabOrder = 11
    end
    object btnRQuery: TButton
      Left = 382
      Top = 133
      Width = 75
      Height = 25
      Caption = #37325'    '#26597
      TabOrder = 12
      OnClick = btnRQueryClick
    end
    object RadioGroup1: TRadioGroup
      Left = 10
      Top = 108
      Width = 88
      Height = 50
      Caption = #20998#26512#39006#21029
      Items.Strings = (
        #19968#33324#20998#26512
        #20491#21029#20998#26512)
      TabOrder = 13
      OnClick = RadioGroup1Click
    end
    object RadioGroup2: TRadioGroup
      Left = 104
      Top = 108
      Width = 87
      Height = 50
      Caption = #20998#26512#39006#22411
      Enabled = False
      Items.Strings = (
        #25353#26448#26009
        #25353#24288#21830)
      TabOrder = 14
      OnClick = RadioGroup2Click
    end
    object RadioGroup3: TRadioGroup
      Left = 195
      Top = 108
      Width = 90
      Height = 50
      Caption = #27161#20934#36984#25799
      Enabled = False
      Items.Strings = (
        #32570'       '#30465
        #25351#23450#27161#20934)
      TabOrder = 15
      OnClick = RadioGroup3Click
    end
    object ProgressBar1: TProgressBar
      Left = 592
      Top = 8
      Width = 17
      Height = 121
      Min = 0
      Max = 35
      Orientation = pbVertical
      TabOrder = 16
      Visible = False
    end
    object lstStockDepart: TComboBox
      Left = 380
      Top = 25
      Width = 83
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 17
    end
  end
  object GroupBox1: TGroupBox
    Left = 381
    Top = 415
    Width = 206
    Height = 77
    Caption = #32113#35336#25976#23383
    TabOrder = 1
    object Label7: TLabel
      Left = 20
      Top = 28
      Width = 51
      Height = 13
      Caption = #35330#36092#27425#25976' '
    end
    object Label8: TLabel
      Left = 19
      Top = 57
      Width = 51
      Height = 13
      Caption = #35330#36092#32317#38989' '
    end
    object edtSN: TEdit
      Left = 86
      Top = 20
      Width = 103
      Height = 21
      Enabled = False
      TabOrder = 0
    end
    object edtSP: TEdit
      Left = 87
      Top = 52
      Width = 102
      Height = 21
      Enabled = False
      TabOrder = 1
    end
  end
  object lstView1: TListView
    Left = 8
    Top = 46
    Width = 609
    Height = 313
    Columns = <
      item
        Caption = #26448#26009#32232#34399
        Width = 120
      end
      item
        Caption = #21697#21517#35215#26684
        Width = 250
      end
      item
        Caption = #24288#21830#31777#31281
        Width = 80
      end
      item
        Caption = #35330#36092#27425#25976
        Width = 65
      end
      item
        Caption = #35330#36092#32317#38989
        Width = 80
      end>
    GridLines = True
    HideSelection = False
    ReadOnly = True
    RowSelect = True
    TabOrder = 2
    ViewStyle = vsReport
    OnSelectItem = lstView1SelectItem
  end
end
