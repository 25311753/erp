object MaterialEditForm: TMaterialEditForm
  Left = 376
  Top = 217
  Width = 750
  Height = 511
  Caption = #26448#26009#32232#34399#24314#27284
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poScreenCenter
  OnKeyDown = FormKeyDown
  OnKeyUp = FormKeyUp
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label5: TLabel
    Left = 248
    Top = 0
    Width = 198
    Height = 33
    Caption = #26448#26009#32232#34399#24314#27284
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = #27161#26999#39636
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label6: TLabel
    Left = 5
    Top = 149
    Width = 73
    Height = 13
    Alignment = taCenter
    AutoSize = False
    Caption = #21697#21517#35215#26684#65306
  end
  object Label1: TLabel
    Left = 11
    Top = 104
    Width = 56
    Height = 13
    AutoSize = False
    Caption = #20844#21496#21029#65306
  end
  object Label2: TLabel
    Left = 344
    Top = 101
    Width = 36
    Height = 13
    Caption = #22823#39006#65306
  end
  object Label3: TLabel
    Left = 15
    Top = 125
    Width = 36
    Height = 13
    Caption = #20013#39006#65306
  end
  object Label4: TLabel
    Left = 344
    Top = 123
    Width = 36
    Height = 13
    Caption = #23567#39006#65306
  end
  object Label7: TLabel
    Left = 6
    Top = 173
    Width = 73
    Height = 13
    AutoSize = False
    Caption = #29992#36884#35498#26126#65306
  end
  object Label8: TLabel
    Left = 6
    Top = 198
    Width = 73
    Height = 13
    AutoSize = False
    Caption = #29986#21697#35215#33539#65306
  end
  object Label9: TLabel
    Left = 344
    Top = 80
    Width = 36
    Height = 13
    Caption = #26085#26399#65306
  end
  object Label10: TLabel
    Left = 560
    Top = 172
    Width = 36
    Height = 13
    Caption = #21934#20301#65306
  end
  object TLabel
    Left = 88
    Top = 24
    Width = 3
    Height = 13
  end
  object edtCorp: TEdit
    Left = 16
    Top = 72
    Width = 25
    Height = 21
    CharCase = ecUpperCase
    MaxLength = 1
    TabOrder = 0
    Text = 'EDTCORP'
    OnChange = edtCorpChange
  end
  object edtID0: TEdit
    Left = 42
    Top = 72
    Width = 47
    Height = 21
    CharCase = ecUpperCase
    MaxLength = 4
    TabOrder = 1
    Text = 'EDTID0'
    OnChange = edtID0Change
  end
  object Panel1: TPanel
    Left = 97
    Top = 80
    Width = 14
    Height = 3
    TabOrder = 11
  end
  object edtID1: TEdit
    Left = 120
    Top = 72
    Width = 209
    Height = 21
    CharCase = ecUpperCase
    MaxLength = 15
    TabOrder = 2
    Text = 'EDIT1'
    OnChange = edtID1Change
  end
  object edtSpec: TEdit
    Left = 72
    Top = 144
    Width = 577
    Height = 21
    MaxLength = 60
    TabOrder = 3
  end
  object lstCorp: TComboBox
    Left = 72
    Top = 96
    Width = 257
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 12
    OnClick = lstCorpClick
  end
  object lstLarge: TComboBox
    Left = 392
    Top = 96
    Width = 257
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 13
    OnClick = lstLargeClick
  end
  object lstMid: TComboBox
    Left = 72
    Top = 120
    Width = 257
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 14
    OnClick = lstMidClick
  end
  object lstMin: TComboBox
    Left = 392
    Top = 120
    Width = 257
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 15
    OnClick = lstMinClick
  end
  object lstView: TListView
    Left = 8
    Top = 304
    Width = 732
    Height = 177
    Columns = <
      item
        Caption = #26448#26009#32232#34399
        Width = 150
      end
      item
        Caption = #21517#31281#21450#21697#21517#35215#26684
        Width = 200
      end
      item
        Caption = #29992#36884
        Width = 100
      end
      item
        Caption = #29986#21697#35215#33539
        Width = 140
      end
      item
        Caption = #21934#20301
        Width = 40
      end
      item
        Caption = #24314#27284#26085#26399
        Width = 70
      end>
    GridLines = True
    HideSelection = False
    ReadOnly = True
    RowSelect = True
    TabOrder = 16
    ViewStyle = vsReport
    OnSelectItem = lstViewSelectItem
  end
  object edtUsage: TEdit
    Left = 72
    Top = 168
    Width = 484
    Height = 21
    MaxLength = 60
    TabOrder = 4
  end
  object Memo1: TMemo
    Left = 72
    Top = 192
    Width = 577
    Height = 73
    Lines.Strings = (
      '')
    MaxLength = 600
    TabOrder = 5
  end
  object btnNew: TButton
    Left = 40
    Top = 40
    Width = 75
    Height = 25
    Caption = #26032'  '#22686
    TabOrder = 6
    OnClick = btnNewClick
  end
  object btnEdit: TButton
    Left = 136
    Top = 40
    Width = 75
    Height = 25
    Caption = #20462'  '#25913
    TabOrder = 7
    OnClick = btnEditClick
  end
  object btnMov: TButton
    Left = 328
    Top = 40
    Width = 75
    Height = 25
    Caption = #21034#38500
    TabOrder = 8
    OnClick = btnMovClick
  end
  object btnOK: TButton
    Left = 520
    Top = 40
    Width = 75
    Height = 25
    Caption = #30906#35469
    TabOrder = 9
    OnClick = btnOKClick
  end
  object btnExit: TButton
    Left = 616
    Top = 40
    Width = 75
    Height = 25
    Caption = #36820#22238
    TabOrder = 10
    OnClick = btnExitClick
  end
  object edtDATE: TEdit
    Left = 392
    Top = 72
    Width = 161
    Height = 21
    TabOrder = 17
  end
  object btndq: TButton
    Left = 576
    Top = 72
    Width = 75
    Height = 17
    Caption = #25353#26085#26399#26597#35426
    TabOrder = 18
    OnClick = btndqClick
  end
  object edtCorpNew: TEdit
    Left = 8
    Top = 272
    Width = 25
    Height = 21
    CharCase = ecUpperCase
    MaxLength = 1
    TabOrder = 19
    OnChange = edtCorpChange
  end
  object edtID0New: TEdit
    Left = 34
    Top = 272
    Width = 47
    Height = 21
    CharCase = ecUpperCase
    MaxLength = 4
    TabOrder = 20
    OnChange = edtID0Change
  end
  object Panel2: TPanel
    Left = 89
    Top = 280
    Width = 14
    Height = 3
    TabOrder = 22
  end
  object edtID1New: TEdit
    Left = 112
    Top = 272
    Width = 209
    Height = 21
    CharCase = ecUpperCase
    MaxLength = 15
    TabOrder = 21
    OnChange = edtID1NewChange
  end
  object btnNO: TButton
    Left = 232
    Top = 40
    Width = 75
    Height = 25
    Caption = #26032#33290#26597#35426
    TabOrder = 23
    OnClick = btnNOClick
  end
  object lstUnits: TComboBox
    Left = 600
    Top = 168
    Width = 51
    Height = 21
    ItemHeight = 13
    TabOrder = 24
  end
  object DateTimePicker1: TDateTimePicker
    Left = 658
    Top = 120
    Width = 82
    Height = 21
    CalAlignment = dtaLeft
    Date = 38637.7161617477
    Time = 38637.7161617477
    DateFormat = dfShort
    DateMode = dmComboBox
    Kind = dtkDate
    ParseInput = False
    TabOrder = 25
  end
  object DateTimePicker2: TDateTimePicker
    Left = 658
    Top = 144
    Width = 82
    Height = 21
    CalAlignment = dtaLeft
    Date = 38637.7161753009
    Time = 38637.7161753009
    DateFormat = dfShort
    DateMode = dmComboBox
    Kind = dtkDate
    ParseInput = False
    TabOrder = 26
  end
  object RB1: TRadioButton
    Left = 656
    Top = 73
    Width = 72
    Height = 17
    Caption = #21934#26085#26597#35426
    TabOrder = 27
  end
  object RB2: TRadioButton
    Left = 656
    Top = 96
    Width = 72
    Height = 17
    Caption = #36328#26085#26597#35426
    TabOrder = 28
  end
  object Button1: TButton
    Left = 424
    Top = 40
    Width = 75
    Height = 25
    Caption = #36681'Excel'
    TabOrder = 29
    OnClick = Button1Click
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 600
  end
end
