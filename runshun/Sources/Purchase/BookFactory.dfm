object BookFactoryForm: TBookFactoryForm
  Left = 257
  Top = 170
  Width = 760
  Height = 529
  Caption = #35330#36092#21934#36664#20837
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
    Left = 266
    Top = 8
    Width = 165
    Height = 32
    Caption = #35330#36092#21934#36664#20837
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = #27161#26999#39636
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label17: TLabel
    Left = 17
    Top = 400
    Width = 338
    Height = 13
    Caption = #35498#26126#65306#21482#26377#37319#36092#32147#36774#33258#24049#25165#33021#20462#25913#12289#21034#38500#35330#36092#21934#21644#26597#30475#21934#20729
  end
  object btnQuery: TButton
    Left = 17
    Top = 424
    Width = 75
    Height = 25
    Caption = #26597'    '#35426
    TabOrder = 0
    OnClick = btnQueryClick
  end
  object btnNew: TButton
    Left = 113
    Top = 424
    Width = 75
    Height = 25
    Caption = #26032'    '#22686
    TabOrder = 1
    OnClick = btnNewClick
  end
  object btnEdit: TButton
    Left = 209
    Top = 424
    Width = 75
    Height = 25
    Caption = #20462'    '#25913
    TabOrder = 2
    OnClick = btnEditClick
  end
  object btnMove: TButton
    Left = 305
    Top = 424
    Width = 75
    Height = 25
    Caption = #21034'    '#38500
    TabOrder = 3
    OnClick = btnMoveClick
  end
  object btnPrint: TButton
    Left = 401
    Top = 424
    Width = 75
    Height = 25
    Caption = #21015'    '#21360
    TabOrder = 4
    OnClick = btnPrintClick
  end
  object btnOK: TButton
    Left = 497
    Top = 424
    Width = 75
    Height = 25
    Caption = #30906'    '#35469
    TabOrder = 5
    OnClick = btnOKClick
  end
  object btnExit: TButton
    Left = 593
    Top = 424
    Width = 75
    Height = 25
    Caption = #36864'    '#20986
    TabOrder = 6
    OnClick = btnExitClick
  end
  object Panel1: TPanel
    Left = 9
    Top = 48
    Width = 665
    Height = 345
    TabOrder = 7
    object Label2: TLabel
      Left = 80
      Top = 63
      Width = 78
      Height = 13
      Caption = #35330#36092#21934#32232#34399#65306
    end
    object Label4: TLabel
      Left = 80
      Top = 95
      Width = 78
      Height = 13
      Caption = #35531#36092#21934#32232#34399#65306
    end
    object Label3: TLabel
      Left = 360
      Top = 63
      Width = 65
      Height = 13
      Caption = #35330#36092#26085#26399#65306
    end
    object Label6: TLabel
      Left = 88
      Top = 127
      Width = 65
      Height = 13
      Caption = #27770#27161#24288#21830#65306
    end
    object Label7: TLabel
      Left = 272
      Top = 159
      Width = 39
      Height = 13
      Caption = #24288#29260#65306
    end
    object Label8: TLabel
      Left = 88
      Top = 191
      Width = 65
      Height = 13
      Caption = #35330#36092#21934#20301#65306
    end
    object Label9: TLabel
      Left = 360
      Top = 191
      Width = 65
      Height = 13
      Caption = #35330#36092#25976#37327#65306
    end
    object Label10: TLabel
      Left = 88
      Top = 223
      Width = 65
      Height = 13
      Caption = #35330#36092#21934#20729#65306
    end
    object Label11: TLabel
      Left = 432
      Top = 223
      Width = 39
      Height = 13
      Caption = #20132#26399#65306
    end
    object Label12: TLabel
      Left = 528
      Top = 221
      Width = 13
      Height = 13
      Caption = #22825
    end
    object Label13: TLabel
      Left = 112
      Top = 255
      Width = 39
      Height = 13
      Caption = #20633#27880#65306
    end
    object Label14: TLabel
      Left = 248
      Top = 95
      Width = 65
      Height = 13
      Caption = #25910#36008#32147#36774#65306
    end
    object Label15: TLabel
      Left = 88
      Top = 287
      Width = 65
      Height = 13
      Caption = #30332#31080#25260#38957#65306
    end
    object Label5: TLabel
      Left = 88
      Top = 319
      Width = 65
      Height = 13
      Caption = #30332#31080#39006#22411#65306
    end
    object Label16: TLabel
      Left = 272
      Top = 223
      Width = 39
      Height = 13
      Caption = #24163#21029#65306
    end
    object Label18: TLabel
      Left = 408
      Top = 95
      Width = 52
      Height = 13
      Caption = #37319#36092#24418#24907
    end
    object Label19: TLabel
      Left = 96
      Top = 159
      Width = 52
      Height = 13
      Caption = #21576#26680#26085#65306
    end
    object Label20: TLabel
      Left = 88
      Top = 32
      Width = 65
      Height = 13
      Caption = #22806#36092#24288#21830#65306
    end
    object edtBookID: TEdit
      Left = 160
      Top = 55
      Width = 97
      Height = 21
      CharCase = ecUpperCase
      MaxLength = 8
      TabOrder = 0
      Text = 'EDTBOOKID'
    end
    object edtAPCode: TEdit
      Left = 160
      Top = 87
      Width = 81
      Height = 21
      CharCase = ecUpperCase
      MaxLength = 8
      TabOrder = 2
      Text = 'EDTAPCODE'
      OnExit = edtAPCodeExit
    end
    object edtBookDate: TEdit
      Left = 424
      Top = 55
      Width = 121
      Height = 21
      MaxLength = 8
      TabOrder = 1
      Text = 'edtBookDate'
    end
    object edtCard: TEdit
      Left = 320
      Top = 151
      Width = 225
      Height = 21
      TabOrder = 7
      Text = 'edtCard'
    end
    object edtUnit: TEdit
      Left = 160
      Top = 183
      Width = 97
      Height = 21
      TabOrder = 8
      Text = 'edtUnit'
    end
    object edtCount: TEdit
      Left = 424
      Top = 183
      Width = 121
      Height = 21
      TabOrder = 9
      Text = 'edtCount'
    end
    object edtPrice: TEdit
      Left = 160
      Top = 215
      Width = 97
      Height = 21
      TabOrder = 10
      Text = 'edtPrice'
    end
    object edtDays: TEdit
      Left = 472
      Top = 215
      Width = 54
      Height = 21
      TabOrder = 12
      Text = 'edtDays'
    end
    object edtRem: TEdit
      Left = 160
      Top = 247
      Width = 385
      Height = 21
      MaxLength = 30
      TabOrder = 13
      Text = 'edtRem'
    end
    object lstHandle: TComboBox
      Left = 312
      Top = 87
      Width = 89
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 3
    end
    object lstInvoice: TComboBox
      Left = 160
      Top = 279
      Width = 385
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 14
    end
    object lstInvoiceType: TComboBox
      Left = 160
      Top = 311
      Width = 385
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 15
      Items.Strings = (
        #26376#24213#38283#31435#30332#31080
        #38568#36008#38468#30332#31080
        #22577#38364#21934
        #36914#21475#22577#38364#21934
        #20986#21475#22577#38364#21934)
    end
    object lstFactory: TComboBox
      Left = 160
      Top = 119
      Width = 385
      Height = 21
      ItemHeight = 13
      TabOrder = 5
      OnExit = lstFactoryExit
    end
    object lstRMB: TComboBox
      Left = 312
      Top = 215
      Width = 97
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 11
    end
    object lstBuyKind: TComboBox
      Left = 464
      Top = 87
      Width = 81
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 4
      Items.Strings = (
        #19968#33324#36031#26131
        #20445#31237
        #26680#37559)
    end
    object lstShowDate: TComboBox
      Left = 160
      Top = 151
      Width = 97
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 6
      OnChange = lstShowDateChange
    end
    object wfactory: TComboBox
      Left = 160
      Top = 24
      Width = 385
      Height = 21
      Enabled = False
      ItemHeight = 13
      TabOrder = 16
    end
  end
end
