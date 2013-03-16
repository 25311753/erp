object SumEffectForm: TSumEffectForm
  Left = 259
  Top = 171
  Width = 766
  Height = 543
  Caption = #26085#24120#32318#25928#32113#35336#22577#34920
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
    Left = 248
    Top = 4
    Width = 305
    Height = 41
    Alignment = taCenter
    AutoSize = False
    Caption = #26085#24120#32318#25928#32113#35336#22577#34920
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -35
    Font.Name = #27161#26999#39636
    Font.Style = [fsBold]
    ParentFont = False
  end
  object lstView: TListView
    Left = 8
    Top = 48
    Width = 742
    Height = 353
    Columns = <
      item
        Caption = #35531#36092#21934#32232#34399
        Width = 70
      end
      item
        Caption = #35531#36092#26085#26399
        Width = 70
      end
      item
        Caption = #20844#21496#21029
        Width = 70
      end
      item
        Caption = #26696#20214#39006#21029
      end
      item
        Caption = #21697#21517#35215#26684
        Width = 150
      end
      item
        Caption = #35696#20729#25976#37327
        Width = 60
      end
      item
        Caption = #21934#20301
        Width = 40
      end
      item
        Caption = #22577#20729#21934#20729
      end
      item
        Caption = #35696#20729#21934#20729
      end
      item
        Caption = #24163#21029
      end
      item
        Caption = #21576#26680#26085#26399
      end
      item
        Caption = #37319#36092#32147#36774
      end
      item
        Caption = #37319#36092#37096#38272
        Width = 70
      end>
    GridLines = True
    HideSelection = False
    ReadOnly = True
    RowSelect = True
    TabOrder = 0
    ViewStyle = vsReport
  end
  object Panel1: TPanel
    Left = 8
    Top = 406
    Width = 745
    Height = 110
    BevelOuter = bvLowered
    TabOrder = 1
    object Label2: TLabel
      Left = 104
      Top = 13
      Width = 75
      Height = 13
      Caption = #37319#36092#32147#36774#65306
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = #32048#26126#39636
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label3: TLabel
      Left = 365
      Top = 15
      Width = 75
      Height = 13
      Caption = #37319#36092#37096#38272#65306
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = #32048#26126#39636
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label4: TLabel
      Left = 586
      Top = 14
      Width = 60
      Height = 13
      Caption = #20844#21496#21029#65306
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = #32048#26126#39636
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label5: TLabel
      Left = 104
      Top = 52
      Width = 75
      Height = 13
      Caption = #26696#20214#39006#21029#65306
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = #32048#26126#39636
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label6: TLabel
      Left = 336
      Top = 54
      Width = 105
      Height = 13
      Caption = #21576#26680#36215#22987#26085#26399#65306
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = #32048#26126#39636
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label7: TLabel
      Left = 543
      Top = 53
      Width = 105
      Height = 13
      Caption = #21576#26680#32080#26463#26085#26399#65306
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = #32048#26126#39636
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label8: TLabel
      Left = 104
      Top = 80
      Width = 75
      Height = 13
      Caption = #32113#35336#25976#37327#65306
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = #32048#26126#39636
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label9: TLabel
      Left = 280
      Top = 80
      Width = 99
      Height = 13
      Caption = #32113#35336#37329#38989#65306'   '
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = #32048#26126#39636
      Font.Style = [fsBold]
      ParentFont = False
    end
    object lstHandle: TComboBox
      Left = 183
      Top = 8
      Width = 145
      Height = 21
      ItemHeight = 13
      TabOrder = 0
    end
    object lstCorp: TComboBox
      Left = 647
      Top = 8
      Width = 95
      Height = 21
      ItemHeight = 13
      TabOrder = 1
    end
    object lstType: TComboBox
      Left = 183
      Top = 48
      Width = 145
      Height = 21
      ItemHeight = 13
      TabOrder = 2
    end
    object DateTimePicker1: TDateTimePicker
      Left = 442
      Top = 48
      Width = 95
      Height = 21
      CalAlignment = dtaLeft
      Date = 38440.6187674421
      Time = 38440.6187674421
      DateFormat = dfShort
      DateMode = dmComboBox
      Kind = dtkDate
      ParseInput = False
      TabOrder = 3
      OnChange = DateTimePicker1Change
    end
    object DateTimePicker2: TDateTimePicker
      Left = 647
      Top = 48
      Width = 95
      Height = 21
      CalAlignment = dtaLeft
      Date = 38440.6188289352
      Time = 38440.6188289352
      DateFormat = dfShort
      DateMode = dmComboBox
      Kind = dtkDate
      ParseInput = False
      TabOrder = 4
    end
    object btnQuery: TButton
      Left = 517
      Top = 83
      Width = 75
      Height = 25
      Caption = #26597#35426
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #26032#32048#26126#39636
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 5
      OnClick = btnQueryClick
    end
    object btntoExcel: TButton
      Left = 592
      Top = 83
      Width = 75
      Height = 25
      Caption = #36681'Excel'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #26032#32048#26126#39636
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 6
      OnClick = btntoExcelClick
    end
    object btnQuit: TButton
      Left = 668
      Top = 83
      Width = 75
      Height = 25
      Caption = #36864#20986
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = #26032#32048#26126#39636
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 7
      OnClick = btnQuitClick
    end
    object lstStockDepart: TComboBox
      Left = 441
      Top = 7
      Width = 95
      Height = 21
      ItemHeight = 13
      TabOrder = 8
    end
    object RadioButton1: TRadioButton
      Left = 13
      Top = 12
      Width = 78
      Height = 17
      Caption = #32570'  '#30465
      Checked = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = #32048#26126#39636
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 9
      TabStop = True
      OnClick = RadioButton1Click
    end
    object RadioButton2: TRadioButton
      Left = 13
      Top = 33
      Width = 77
      Height = 17
      Caption = #20154#21729#21029
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = #32048#26126#39636
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 10
      OnClick = RadioButton2Click
    end
    object RadioButton3: TRadioButton
      Left = 13
      Top = 54
      Width = 76
      Height = 17
      Caption = #26696#20214#21029
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = #32048#26126#39636
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 11
      OnClick = RadioButton3Click
    end
    object RadioButton4: TRadioButton
      Left = 13
      Top = 76
      Width = 77
      Height = 17
      Caption = #20844#21496#21029
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = #32048#26126#39636
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 12
      OnClick = RadioButton4Click
    end
    object edtSNum: TEdit
      Left = 184
      Top = 80
      Width = 89
      Height = 21
      TabOrder = 13
      Text = 'edtSNum'
    end
    object edtSPrice: TEdit
      Left = 354
      Top = 80
      Width = 89
      Height = 21
      TabOrder = 14
      Text = 'edtSPrice'
    end
  end
end
