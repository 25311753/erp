object TreatStockForm: TTreatStockForm
  Left = 322
  Top = 128
  Width = 721
  Height = 494
  Caption = #21512#32004#37319#36092#27284
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = #26032#32048#26126#39636
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poScreenCenter
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 295
    Top = 7
    Width = 165
    Height = 32
    Caption = #21512#32004#37319#36092#27284
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = #27161#26999#39636
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 20
    Top = 138
    Width = 65
    Height = 13
    Caption = #26448#26009#32232#34399#65306
  end
  object Label3: TLabel
    Left = 44
    Top = 170
    Width = 39
    Height = 13
    Caption = #24288#21830#65306
  end
  object Label4: TLabel
    Left = 292
    Top = 138
    Width = 65
    Height = 13
    Caption = #21697#21517#35215#26684#65306
  end
  object Label5: TLabel
    Left = 316
    Top = 170
    Width = 39
    Height = 13
    Caption = #24288#29260#65306
  end
  object Label6: TLabel
    Left = 20
    Top = 202
    Width = 65
    Height = 13
    Caption = #21512#32004#21934#20301#65306
  end
  object Label7: TLabel
    Left = 292
    Top = 202
    Width = 65
    Height = 13
    Caption = #21512#32004#21934#20729#65306
  end
  object Label8: TLabel
    Left = 524
    Top = 202
    Width = 39
    Height = 13
    Caption = #20132#26399#65306
  end
  object Label9: TLabel
    Left = 28
    Top = 234
    Width = 52
    Height = 13
    Caption = #32147#36774#20154#65306
  end
  object Label10: TLabel
    Left = 20
    Top = 266
    Width = 65
    Height = 13
    Caption = #36664#20837#26085#26399#65306
  end
  object Label11: TLabel
    Left = 228
    Top = 266
    Width = 65
    Height = 13
    Caption = #20462#25913#26085#26399#65306
  end
  object Label12: TLabel
    Left = 500
    Top = 170
    Width = 65
    Height = 13
    Caption = #29983#25928#26085#26399#65306
  end
  object Label13: TLabel
    Left = 20
    Top = 106
    Width = 65
    Height = 13
    Caption = #21512#32004#32232#34399#65306
  end
  object Label14: TLabel
    Left = 292
    Top = 234
    Width = 65
    Height = 13
    Caption = #37319#36092#37096#38272#65306
  end
  object Label15: TLabel
    Left = 20
    Top = 298
    Width = 65
    Height = 13
    Caption = #30906#35469#26085#26399#65306
  end
  object Label16: TLabel
    Left = 228
    Top = 298
    Width = 91
    Height = 13
    Caption = #26371#35336#30906#35469#26085#26399#65306
  end
  object Label17: TLabel
    Left = 24
    Top = 360
    Width = 276
    Height = 13
    Caption = #35498#26126#65306' '#21482#26377#32147#36774#21644#26412#21934#30340#25805#20316#32773#25165#21487#20197#26597#30475#21934#20729
  end
  object edtMater: TEdit
    Left = 84
    Top = 130
    Width = 161
    Height = 21
    TabOrder = 1
    Text = 'edtMater'
    OnExit = edtMaterExit
  end
  object btnPickup: TButton
    Left = 244
    Top = 130
    Width = 33
    Height = 21
    Caption = #26597#25214
    TabOrder = 15
    OnClick = btnPickupClick
  end
  object lstFact: TComboBox
    Left = 84
    Top = 162
    Width = 161
    Height = 21
    ItemHeight = 13
    MaxLength = 10
    TabOrder = 2
    Text = 'lstFact'
    OnExit = lstFactExit
  end
  object edtSpec: TEdit
    Left = 356
    Top = 130
    Width = 337
    Height = 21
    TabOrder = 16
    Text = 'edtSpec'
  end
  object edtCard: TEdit
    Left = 356
    Top = 162
    Width = 137
    Height = 21
    TabOrder = 3
    Text = 'edtCard'
  end
  object lstUnit: TComboBox
    Left = 84
    Top = 194
    Width = 193
    Height = 21
    ItemHeight = 13
    MaxLength = 4
    TabOrder = 5
    Text = 'lstUnit'
    OnExit = lstUnitExit
  end
  object edtPrice: TEdit
    Left = 356
    Top = 194
    Width = 137
    Height = 21
    TabOrder = 6
    Text = 'edtPrice'
  end
  object edtDays: TEdit
    Left = 572
    Top = 194
    Width = 121
    Height = 21
    TabOrder = 7
    Text = 'edtDays'
  end
  object lstHandle: TComboBox
    Left = 84
    Top = 226
    Width = 193
    Height = 21
    ItemHeight = 13
    MaxLength = 6
    TabOrder = 8
    Text = 'lstHandle'
    OnExit = lstHandleExit
  end
  object edtInpdate: TEdit
    Left = 84
    Top = 258
    Width = 121
    Height = 21
    TabOrder = 17
    Text = 'edtInpdate'
  end
  object edtEditdate: TEdit
    Left = 300
    Top = 258
    Width = 121
    Height = 21
    TabOrder = 18
    Text = 'edtEditdate'
  end
  object btnQuery: TButton
    Left = 51
    Top = 410
    Width = 75
    Height = 25
    Caption = #26597'    '#35426
    TabOrder = 9
    OnClick = btnQueryClick
  end
  object btnNew: TButton
    Left = 155
    Top = 410
    Width = 75
    Height = 25
    Caption = #26032'    '#22686
    TabOrder = 10
    OnClick = btnNewClick
  end
  object btnEdit: TButton
    Left = 259
    Top = 410
    Width = 75
    Height = 25
    Caption = #20462'    '#25913
    TabOrder = 11
    OnClick = btnEditClick
  end
  object btnMove: TButton
    Left = 363
    Top = 410
    Width = 75
    Height = 25
    Caption = #21034'    '#38500
    TabOrder = 12
    OnClick = btnMoveClick
  end
  object btnOK: TButton
    Left = 467
    Top = 410
    Width = 75
    Height = 25
    Caption = #30906'    '#35469
    TabOrder = 13
    OnClick = btnOKClick
  end
  object btnExit: TButton
    Left = 579
    Top = 410
    Width = 75
    Height = 25
    Caption = #36864'    '#20986
    TabOrder = 14
    OnClick = btnExitClick
  end
  object edtInuredate: TEdit
    Left = 572
    Top = 162
    Width = 121
    Height = 21
    TabOrder = 4
    Text = 'edtInuredate'
  end
  object edtID: TEdit
    Left = 84
    Top = 98
    Width = 153
    Height = 21
    CharCase = ecUpperCase
    MaxLength = 8
    TabOrder = 0
    Text = 'EDTID'
  end
  object lstDepart: TComboBox
    Left = 356
    Top = 226
    Width = 137
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 19
  end
  object edtAfmDate: TEdit
    Left = 84
    Top = 290
    Width = 121
    Height = 21
    TabOrder = 20
    Text = 'edtAfmDate'
  end
  object edtAfmDate2: TEdit
    Left = 324
    Top = 290
    Width = 121
    Height = 21
    TabOrder = 21
    Text = 'edtAfmDate2'
  end
  object btnPickFact: TButton
    Left = 244
    Top = 162
    Width = 33
    Height = 21
    Caption = #26597#25214
    TabOrder = 22
    OnClick = btnPickFactClick
  end
end
