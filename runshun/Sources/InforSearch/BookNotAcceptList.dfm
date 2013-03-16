object BookNotAcceptListForm: TBookNotAcceptListForm
  Left = 368
  Top = 214
  Width = 800
  Height = 559
  Caption = #24050#35330#36092#26410#25910#26009#26126#32048
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = #32048#26126#39636
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 264
    Top = 8
    Width = 264
    Height = 33
    Caption = #24050#35330#36092#26410#25910#26009#26126#32048
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = #27161#26999#39636
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 4
    Top = 510
    Width = 70
    Height = 13
    Caption = #23532#25918#22825#25976#65306
  end
  object Label3: TLabel
    Left = 6
    Top = 480
    Width = 56
    Height = 13
    Caption = #20844#21496#21029#65306
  end
  object Label4: TLabel
    Left = 138
    Top = 480
    Width = 70
    Height = 13
    Caption = #37319#36092#37096#38272#65306
  end
  object Label5: TLabel
    Left = 552
    Top = 480
    Width = 42
    Height = 13
    Caption = #24288#21830#65306
  end
  object Label6: TLabel
    Left = 309
    Top = 480
    Width = 70
    Height = 13
    Caption = #35531#36092#37096#38272#65306
  end
  object Label7: TLabel
    Left = 121
    Top = 509
    Width = 98
    Height = 13
    Caption = #35330#36092#36215#22987#26085#26399#65306
  end
  object Label8: TLabel
    Left = 324
    Top = 509
    Width = 98
    Height = 13
    Caption = #35330#36092#32080#26463#26085#26399#65306
  end
  object lstView: TListView
    Left = 8
    Top = 48
    Width = 777
    Height = 417
    Columns = <
      item
        Caption = #35330#36092#21934#34399
        Width = 70
      end
      item
        Caption = #35330#36092#26085#26399
        Width = 70
      end
      item
        Caption = #20132#26399
        Width = 40
      end
      item
        Caption = #26448#26009#32232#34399
        Width = 120
      end
      item
        Caption = #21697#21517#35215#26684
        Width = 150
      end
      item
        Caption = #20844#21496#21029
        Width = 55
      end
      item
        Caption = #35531#36092#37096#38272
        Width = 100
      end
      item
        Caption = #37319#36092#37096#38272
        Width = 70
      end
      item
        Alignment = taRightJustify
        Caption = #35330#36092#25976#37327
        Width = 70
      end
      item
        Caption = #35330#36092#24288#21830
        Width = 200
      end
      item
        Caption = #35531#36092#21934#34399
        Width = 70
      end
      item
        Caption = #37319#36092#32147#36774
      end>
    GridLines = True
    HideSelection = False
    ReadOnly = True
    RowSelect = True
    TabOrder = 0
    ViewStyle = vsReport
  end
  object edtDays: TEdit
    Left = 76
    Top = 502
    Width = 41
    Height = 21
    TabOrder = 1
    Text = 'edtDays'
  end
  object btnQuery: TButton
    Left = 526
    Top = 501
    Width = 67
    Height = 25
    Caption = #26597#12288#35426
    TabOrder = 2
    OnClick = btnQueryClick
  end
  object btnToExcel: TButton
    Left = 592
    Top = 501
    Width = 67
    Height = 25
    Caption = #36681'Eexcel'
    TabOrder = 3
    OnClick = btnToExcelClick
  end
  object btnExit: TButton
    Left = 724
    Top = 501
    Width = 59
    Height = 25
    Caption = #36864#12288#20986
    TabOrder = 4
    OnClick = btnExitClick
  end
  object lstCorp: TComboBox
    Left = 57
    Top = 472
    Width = 73
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 5
  end
  object lstDepart: TComboBox
    Left = 202
    Top = 472
    Width = 97
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 6
  end
  object lstFact: TComboBox
    Left = 592
    Top = 472
    Width = 153
    Height = 21
    ItemHeight = 13
    MaxLength = 80
    TabOrder = 8
    Text = 'lstFact'
  end
  object btnFactPickup: TButton
    Left = 744
    Top = 472
    Width = 33
    Height = 20
    Caption = #26597#25214
    TabOrder = 9
    OnClick = btnFactPickupClick
  end
  object lstAskDep: TComboBox
    Left = 373
    Top = 472
    Width = 169
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 7
  end
  object DateTimePicker1: TDateTimePicker
    Left = 216
    Top = 503
    Width = 105
    Height = 21
    CalAlignment = dtaLeft
    Date = 38350.608273831
    Time = 38350.608273831
    DateFormat = dfShort
    DateMode = dmComboBox
    Kind = dtkDate
    ParseInput = False
    TabOrder = 10
  end
  object DateTimePicker2: TDateTimePicker
    Left = 416
    Top = 502
    Width = 105
    Height = 21
    CalAlignment = dtaLeft
    Date = 38350.6084136227
    Time = 38350.6084136227
    DateFormat = dfShort
    DateMode = dmComboBox
    Kind = dtkDate
    ParseInput = False
    TabOrder = 11
  end
  object btnprint: TButton
    Left = 659
    Top = 501
    Width = 65
    Height = 25
    Caption = #21015'  '#21360
    TabOrder = 12
    OnClick = btnprintClick
  end
end
