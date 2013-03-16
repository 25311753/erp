object PurchaseRoadForm: TPurchaseRoadForm
  Left = 311
  Top = 105
  Width = 772
  Height = 574
  Caption = 'PurchaseRoadForm'
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
    Left = 264
    Top = 8
    Width = 132
    Height = 32
    Caption = #37319#36092#36942#31243
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = #27161#26999#39636
    Font.Style = [fsBold]
    ParentFont = False
  end
  object ctlPage: TPageControl
    Left = 32
    Top = 136
    Width = 705
    Height = 345
    ActivePage = ctlBook
    TabIndex = 6
    TabOrder = 0
    OnChanging = ctlPageChanging
    object ctlStockList: TTabSheet
      Caption = #37319#36092#35352#37636
      ImageIndex = 6
      OnShow = ctlStockListShow
      object lstStockList: TListView
        Left = 8
        Top = 24
        Width = 201
        Height = 265
        Columns = <
          item
            Caption = #38917#27425
            Width = 40
          end>
        GridLines = True
        HideSelection = False
        ReadOnly = True
        RowSelect = True
        TabOrder = 0
        ViewStyle = vsReport
        OnSelectItem = lstShowViewSelectItem
      end
      object btnListStock: TButton
        Left = 224
        Top = 256
        Width = 75
        Height = 25
        Caption = #37319#36092#35352#37636#34920
        TabOrder = 1
        OnClick = btnListStockClick
      end
    end
    object ctlSpeer: TTabSheet
      Caption = #35426#20729#21934
      OnShow = ctlSpeerShow
      object Label3: TLabel
        Left = 128
        Top = 24
        Width = 78
        Height = 13
        Caption = #22577#20729#25130#27490#26085#65306
      end
      object Label4: TLabel
        Left = 336
        Top = 24
        Width = 65
        Height = 13
        Caption = #21015#21360#26085#26399#65306
      end
      object Label5: TLabel
        Left = 128
        Top = 56
        Width = 39
        Height = 13
        Caption = #24288#21830#65306
      end
      object edtSpeerEndDate: TEdit
        Left = 208
        Top = 16
        Width = 89
        Height = 21
        TabOrder = 0
        Text = 'e'
      end
      object edtSpeerPrnDate: TEdit
        Left = 400
        Top = 16
        Width = 121
        Height = 21
        TabOrder = 1
        Text = 'edtSpeerPrnDate'
      end
      object lstSpeerFact: TComboBox
        Left = 168
        Top = 48
        Width = 353
        Height = 21
        ItemHeight = 13
        MaxLength = 20
        TabOrder = 2
        Text = 'lstSpeerFact'
        OnExit = lstSpeerFactExit
      end
      object lstSpeerView: TListBox
        Left = 128
        Top = 72
        Width = 393
        Height = 209
        ItemHeight = 13
        TabOrder = 3
        OnClick = lstSpeerViewClick
      end
      object btnSpeerFactInf: TButton
        Left = 368
        Top = 288
        Width = 75
        Height = 25
        Caption = #24288#21830#36039#26009
        TabOrder = 4
        OnClick = btnSpeerFactInfClick
      end
      object btnSpeerPrn: TButton
        Left = 288
        Top = 288
        Width = 75
        Height = 25
        Caption = #21015'    '#21360
        TabOrder = 5
        OnClick = btnSpeerPrnClick
      end
      object btnSpeerFactSearch: TButton
        Left = 448
        Top = 288
        Width = 75
        Height = 25
        Caption = #24288#21830#26597#35426
        TabOrder = 6
        OnClick = btnSpeerFactSearchClick
      end
    end
    object ctlQuote: TTabSheet
      Caption = #22577#20729
      ImageIndex = 1
      OnShow = ctlQuoteShow
      object lstQuoteView: TListView
        Left = 8
        Top = 16
        Width = 217
        Height = 281
        Columns = <
          item
            Caption = #38917#27425
            Width = 40
          end
          item
            Caption = #24288#21830
            Width = 150
          end>
        GridLines = True
        HideSelection = False
        ReadOnly = True
        RowSelect = True
        TabOrder = 0
        ViewStyle = vsReport
        OnClick = lstQuoteViewClick
        OnSelectItem = lstQuoteViewSelectItem
      end
      object Panel1: TPanel
        Left = 232
        Top = 16
        Width = 449
        Height = 281
        TabOrder = 1
        object Label6: TLabel
          Left = 16
          Top = 16
          Width = 39
          Height = 13
          Caption = #38917#27425#65306
        end
        object Label7: TLabel
          Left = 136
          Top = 16
          Width = 39
          Height = 13
          Caption = #24288#21830#65306
        end
        object Label8: TLabel
          Left = 16
          Top = 48
          Width = 39
          Height = 13
          Caption = #24288#29260#65306
        end
        object Label9: TLabel
          Left = 16
          Top = 80
          Width = 65
          Height = 13
          Caption = #35531#36092#21934#20301#65306
        end
        object Label10: TLabel
          Left = 184
          Top = 80
          Width = 65
          Height = 13
          Caption = #35531#36092#25976#37327#65306
        end
        object Label11: TLabel
          Left = 16
          Top = 112
          Width = 65
          Height = 13
          Caption = #22577#20729#21934#20301#65306
        end
        object Label12: TLabel
          Left = 184
          Top = 112
          Width = 65
          Height = 13
          Caption = #22577#20729#25976#37327#65306
        end
        object Label13: TLabel
          Left = 16
          Top = 144
          Width = 65
          Height = 13
          Caption = #22577#20729#21934#20729#65306
        end
        object Label14: TLabel
          Left = 16
          Top = 176
          Width = 39
          Height = 13
          Caption = #20132#26399#65306
        end
        object Label15: TLabel
          Left = 144
          Top = 176
          Width = 13
          Height = 13
          Caption = #22825
        end
        object Label16: TLabel
          Left = 184
          Top = 176
          Width = 65
          Height = 13
          Caption = #20184#27454#26041#24335#65306
        end
        object Label17: TLabel
          Left = 16
          Top = 208
          Width = 39
          Height = 13
          Caption = #31237#29575#65306
        end
        object Label18: TLabel
          Left = 184
          Top = 208
          Width = 78
          Height = 13
          Caption = #22577#20729#36664#20837#26085#65306
        end
        object Label43: TLabel
          Left = 208
          Top = 144
          Width = 39
          Height = 13
          Caption = #24163#21029#65306
        end
        object Label45: TLabel
          Left = 16
          Top = 240
          Width = 65
          Height = 13
          Caption = #20132#36008#26781#20214#65306
        end
        object edtQuoteItem: TEdit
          Left = 56
          Top = 8
          Width = 41
          Height = 21
          CharCase = ecUpperCase
          MaxLength = 1
          TabOrder = 0
          Text = 'EDTQUOTEITEM'
          OnExit = edtQuoteItemExit
        end
        object lstQuoteFact: TComboBox
          Left = 176
          Top = 8
          Width = 257
          Height = 21
          Style = csDropDownList
          ItemHeight = 13
          MaxLength = 20
          TabOrder = 1
          OnChange = lstQuoteFactChange
          OnExit = lstQuoteFactExit
        end
        object edtQuoteFactCard: TEdit
          Left = 56
          Top = 40
          Width = 377
          Height = 21
          MaxLength = 14
          TabOrder = 2
          Text = 'edtQuoteFactCard'
        end
        object edtQuoteReqUnit: TEdit
          Left = 80
          Top = 72
          Width = 81
          Height = 21
          TabOrder = 3
          Text = 'edtQuoteReqUnit'
        end
        object edtQuoteReqNum: TEdit
          Left = 248
          Top = 72
          Width = 81
          Height = 21
          TabOrder = 4
          Text = 'edtQuoteReqNum'
        end
        object lstQuoteUnit: TComboBox
          Left = 80
          Top = 104
          Width = 81
          Height = 21
          ItemHeight = 13
          TabOrder = 5
          OnEnter = lstQuoteUnitEnter
          OnExit = lstQuoteUnitExit
        end
        object edtQuoteNum: TEdit
          Left = 248
          Top = 104
          Width = 81
          Height = 21
          MaxLength = 10
          TabOrder = 6
          Text = 'edtQuoteNum'
          OnEnter = edtQuoteNumEnter
        end
        object edtQuotePrice: TEdit
          Left = 80
          Top = 136
          Width = 81
          Height = 21
          MaxLength = 20
          TabOrder = 7
          Text = 'edtQuotePrice'
        end
        object edtQuoteDelDays: TEdit
          Left = 56
          Top = 168
          Width = 81
          Height = 21
          MaxLength = 3
          TabOrder = 9
          Text = 'edtQuoteDelDays'
        end
        object lstQuotePay: TComboBox
          Left = 248
          Top = 168
          Width = 169
          Height = 21
          Style = csDropDownList
          ItemHeight = 13
          TabOrder = 10
        end
        object edtQuoteInpDate: TEdit
          Left = 264
          Top = 200
          Width = 89
          Height = 21
          MaxLength = 8
          TabOrder = 12
          Text = 'edtQuoteInpDate'
        end
        object btnQuotePrint: TButton
          Left = 328
          Top = 240
          Width = 75
          Height = 25
          Caption = #21015'    '#21360
          TabOrder = 14
          OnClick = btnQuotePrintClick
        end
        object lstQuoteRMB: TComboBox
          Left = 248
          Top = 136
          Width = 169
          Height = 21
          Style = csDropDownList
          ItemHeight = 13
          TabOrder = 8
        end
        object lstQuoteDelivery: TComboBox
          Left = 80
          Top = 232
          Width = 169
          Height = 19
          Style = csOwnerDrawFixed
          ItemHeight = 13
          MaxLength = 20
          TabOrder = 13
          OnExit = lstQuoteDeliveryExit
        end
        object lstQuoteTax: TComboBox
          Left = 56
          Top = 200
          Width = 113
          Height = 21
          Style = csDropDownList
          ItemHeight = 13
          MaxLength = 40
          TabOrder = 11
          OnExit = lstQuoteTaxExit
        end
      end
    end
    object ctlHiggle: TTabSheet
      Caption = #35696#20729
      ImageIndex = 2
      OnShow = ctlHiggleShow
      object Label19: TLabel
        Left = 256
        Top = 24
        Width = 65
        Height = 13
        Caption = #35696#20729#21934#20729#65306
      end
      object Label20: TLabel
        Left = 256
        Top = 56
        Width = 78
        Height = 13
        Caption = #35696#20729#36664#20837#26085#65306
      end
      object Label44: TLabel
        Left = 448
        Top = 24
        Width = 39
        Height = 13
        Caption = #24163#21029#65306
      end
      object lstHiggleView: TListView
        Left = 8
        Top = 16
        Width = 217
        Height = 265
        Columns = <
          item
            Caption = #38917#27425
            Width = 40
          end
          item
            Caption = #24288#21830
            Width = 150
          end>
        GridLines = True
        HideSelection = False
        ReadOnly = True
        RowSelect = True
        TabOrder = 3
        ViewStyle = vsReport
        OnClick = lstHiggleViewClick
        OnSelectItem = lstHiggleViewSelectItem
      end
      object edtHigglePrice: TEdit
        Left = 336
        Top = 16
        Width = 89
        Height = 21
        TabOrder = 0
        Text = 'edtHigglePrice'
      end
      object edtHiggleDate: TEdit
        Left = 336
        Top = 48
        Width = 89
        Height = 21
        MaxLength = 8
        TabOrder = 2
        Text = 'edtHiggleDate'
      end
      object btnHigglePrint: TButton
        Left = 256
        Top = 240
        Width = 75
        Height = 25
        Caption = #21015'    '#21360
        TabOrder = 4
        OnClick = btnHigglePrintClick
      end
      object edtHiggleRMB: TEdit
        Left = 488
        Top = 16
        Width = 73
        Height = 21
        TabOrder = 1
        Text = 'edtHiggleRMB'
      end
    end
    object ctlShow: TTabSheet
      Caption = #21576#26680
      ImageIndex = 3
      OnShow = ctlShowShow
      object Label21: TLabel
        Left = 104
        Top = 16
        Width = 65
        Height = 13
        Caption = #25836#36092#24288#21830#65306
      end
      object Label22: TLabel
        Left = 544
        Top = 16
        Width = 52
        Height = 13
        Caption = #21576#26680#26085#65306
      end
      object Label32: TLabel
        Left = 8
        Top = 16
        Width = 39
        Height = 13
        Caption = #38917#27425#65306
      end
      object Label41: TLabel
        Left = 184
        Top = 48
        Width = 78
        Height = 13
        Caption = #25836#37319#36092#35498#26126#65306
      end
      object Label42: TLabel
        Left = 8
        Top = 48
        Width = 91
        Height = 13
        Caption = #22577#20729#26377#25928#26085#26399#65306
      end
      object Label46: TLabel
        Left = 32
        Top = 72
        Width = 65
        Height = 13
        Caption = #20729#26684#36264#21218#65306
      end
      object Label48: TLabel
        Left = 392
        Top = 16
        Width = 52
        Height = 13
        Caption = #25836#36092#25976#37327
      end
      object lstShowView: TListView
        Left = 8
        Top = 112
        Width = 457
        Height = 177
        Columns = <
          item
            Caption = #38917#27425
            Width = 40
          end
          item
            Caption = #24288#21830
            Width = 300
          end
          item
            Caption = #21576#26680#26085
            Width = 100
          end>
        GridLines = True
        HideSelection = False
        ReadOnly = True
        RowSelect = True
        TabOrder = 7
        ViewStyle = vsReport
        OnClick = lstShowViewClick
        OnSelectItem = lstShowViewSelectItem
      end
      object lstShowFact: TComboBox
        Left = 168
        Top = 8
        Width = 217
        Height = 21
        ItemHeight = 13
        MaxLength = 20
        TabOrder = 1
        OnExit = lstShowFactExit
      end
      object edtShowDate: TEdit
        Left = 600
        Top = 8
        Width = 89
        Height = 21
        MaxLength = 8
        TabOrder = 3
        Text = 'edtShowDate'
      end
      object edtShowItem: TEdit
        Left = 48
        Top = 8
        Width = 49
        Height = 21
        CharCase = ecUpperCase
        MaxLength = 1
        TabOrder = 0
        Text = 'EDTSHOWITEM'
      end
      object btnShowPrint: TButton
        Left = 504
        Top = 248
        Width = 75
        Height = 25
        Caption = #21015'    '#21360
        TabOrder = 8
        OnClick = btnShowPrintClick
      end
      object edtShowRem: TEdit
        Left = 264
        Top = 40
        Width = 425
        Height = 21
        MaxLength = 120
        TabOrder = 5
        Text = 'edtShowRem'
      end
      object edtValidDate: TEdit
        Left = 96
        Top = 40
        Width = 81
        Height = 21
        MaxLength = 8
        TabOrder = 4
        Text = 'edtValidDate'
      end
      object btnStockRecord: TButton
        Left = 504
        Top = 200
        Width = 75
        Height = 25
        Caption = #37319#36092#35352#37636#34920
        TabOrder = 9
        OnClick = btnStockRecordClick
      end
      object lstPriceRT: TComboBox
        Left = 96
        Top = 64
        Width = 169
        Height = 21
        ItemHeight = 13
        TabOrder = 6
        Text = 'lstPriceRT'
        Items.Strings = (
          #20729#26684#21516#21069#25209
          #20729#26684#19978#28466
          #20729#26684#19979#38477)
      end
      object edtShowNum: TEdit
        Left = 448
        Top = 8
        Width = 81
        Height = 21
        TabOrder = 2
        Text = 'edtShowNum'
      end
    end
    object ctlDecide: TTabSheet
      Caption = #27770#27161
      ImageIndex = 4
      OnShow = ctlDecideShow
      object Label23: TLabel
        Left = 8
        Top = 40
        Width = 65
        Height = 13
        Caption = #27770#27161#24288#21830#65306
      end
      object Label24: TLabel
        Left = 256
        Top = 40
        Width = 78
        Height = 13
        Caption = #27770#27161#36664#20837#26085#65306
      end
      object Label33: TLabel
        Left = 8
        Top = 16
        Width = 39
        Height = 13
        Caption = #38917#27425#65306
      end
      object Label34: TLabel
        Left = 8
        Top = 64
        Width = 65
        Height = 13
        Caption = #27770#27161#25976#37327#65306
      end
      object Label35: TLabel
        Left = 160
        Top = 64
        Width = 65
        Height = 13
        Caption = #27770#27161#21934#20301#65306
      end
      object Label36: TLabel
        Left = 304
        Top = 64
        Width = 65
        Height = 13
        Caption = #27770#27161#21934#20729#65306
      end
      object Label37: TLabel
        Left = 88
        Top = 16
        Width = 65
        Height = 13
        Caption = #25836#36092#24288#21830#65306
      end
      object Label47: TLabel
        Left = 336
        Top = 16
        Width = 39
        Height = 13
        Caption = #21576#26680#26085
      end
      object lstDecideView: TListView
        Left = 8
        Top = 88
        Width = 537
        Height = 217
        Columns = <
          item
            Caption = #38917#27425
            Width = 40
          end
          item
            Caption = #25836#37319#36092#24288#21830
            Width = 150
          end
          item
            Caption = #21576#26680#26085
            Width = 100
          end
          item
            Caption = #27770#27161#24288#21830
            Width = 200
          end>
        GridLines = True
        HideSelection = False
        ReadOnly = True
        RowSelect = True
        TabOrder = 7
        ViewStyle = vsReport
        OnClick = lstDecideViewClick
        OnSelectItem = lstDecideViewSelectItem
      end
      object lstDecideFact: TComboBox
        Left = 80
        Top = 32
        Width = 161
        Height = 21
        ItemHeight = 13
        MaxLength = 20
        TabOrder = 2
        Text = 'lstDecideFact'
        OnExit = lstDecideFactExit
      end
      object edtDecideDate: TEdit
        Left = 336
        Top = 32
        Width = 121
        Height = 21
        MaxLength = 8
        TabOrder = 3
        Text = 'edtDecideDate'
      end
      object edtDecideItem: TEdit
        Left = 48
        Top = 8
        Width = 33
        Height = 21
        TabOrder = 0
        Text = 'edtDecideItem'
      end
      object edtDecideNum: TEdit
        Left = 72
        Top = 56
        Width = 81
        Height = 21
        MaxLength = 10
        TabOrder = 4
        Text = 'edtDecideNum'
      end
      object lstDecideUnit: TComboBox
        Left = 224
        Top = 56
        Width = 73
        Height = 21
        ItemHeight = 13
        TabOrder = 5
        OnExit = lstDecideUnitExit
      end
      object edtDecidePrice: TEdit
        Left = 368
        Top = 56
        Width = 89
        Height = 21
        MaxLength = 20
        TabOrder = 6
        Text = 'edtDecidePrice'
      end
      object edtDecideFact0: TEdit
        Left = 152
        Top = 8
        Width = 169
        Height = 21
        TabOrder = 1
        Text = 'edtDecideFact0'
      end
      object edtDfShowDate: TEdit
        Left = 376
        Top = 8
        Width = 97
        Height = 21
        TabOrder = 8
        Text = 'edtDfShowDate'
      end
    end
    object ctlBook: TTabSheet
      Caption = #35330#36092
      ImageIndex = 5
      OnShow = ctlBookShow
      object lstBookView: TListView
        Left = 8
        Top = 16
        Width = 217
        Height = 265
        Columns = <
          item
            Caption = #38917#27425
            Width = 40
          end
          item
            Caption = #35330#36092#21934#34399
            Width = 150
          end>
        GridLines = True
        HideSelection = False
        ReadOnly = True
        RowSelect = True
        TabOrder = 0
        ViewStyle = vsReport
        OnDblClick = lstBookViewDblClick
      end
      object btnToBook: TButton
        Left = 240
        Top = 256
        Width = 75
        Height = 25
        Caption = #26597#30475#35330#36092#21934
        TabOrder = 1
        OnClick = btnToBookClick
      end
      object btnToMutBook: TButton
        Left = 328
        Top = 256
        Width = 233
        Height = 25
        Caption = #35330#36092#21934#21015#34920#21015#21360'('#29579#38283#35201#27714#65292#20808#23631#34109#20043')'
        TabOrder = 2
        Visible = False
        OnClick = btnToMutBookClick
      end
    end
  end
  object Panel2: TPanel
    Left = 32
    Top = 48
    Width = 705
    Height = 89
    TabOrder = 1
    object Label2: TLabel
      Left = 8
      Top = 16
      Width = 65
      Height = 13
      Caption = #35531#36092#21934#34399#65306
    end
    object Label25: TLabel
      Left = 160
      Top = 16
      Width = 52
      Height = 13
      Caption = #38656#35201#26085#65306
    end
    object Label26: TLabel
      Left = 288
      Top = 16
      Width = 65
      Height = 13
      Caption = #26696#20214#39006#21029#65306
    end
    object Label27: TLabel
      Left = 416
      Top = 16
      Width = 65
      Height = 13
      Caption = #35531#36092#26085#26399#65306
    end
    object Label28: TLabel
      Left = 560
      Top = 16
      Width = 52
      Height = 13
      Caption = #37319#36092#21029#65306
    end
    object Label29: TLabel
      Left = 8
      Top = 40
      Width = 65
      Height = 13
      Caption = #35531#36092#37096#38272#65306
    end
    object Label30: TLabel
      Left = 224
      Top = 40
      Width = 65
      Height = 13
      Caption = #37319#36092#37096#38272#65306
    end
    object Label38: TLabel
      Left = 8
      Top = 64
      Width = 65
      Height = 13
      Caption = #37319#36092#32147#36774#65306
    end
    object Label39: TLabel
      Left = 296
      Top = 64
      Width = 65
      Height = 13
      Caption = #24037#31243#32232#34399#65306
    end
    object Label40: TLabel
      Left = 176
      Top = 64
      Width = 39
      Height = 13
      Caption = #20998#27231#65306
    end
    object Label31: TLabel
      Left = 416
      Top = 40
      Width = 65
      Height = 13
      Caption = #25509#26696#26085#26399#65306
    end
    object edtMainID: TEdit
      Left = 72
      Top = 8
      Width = 73
      Height = 21
      CharCase = ecUpperCase
      MaxLength = 7
      TabOrder = 0
      Text = 'EDTMAINID'
      OnChange = edtMainIDChange
    end
    object edtNeedDate: TEdit
      Left = 208
      Top = 8
      Width = 73
      Height = 21
      MaxLength = 8
      TabOrder = 1
      Text = 'edtNeedDate'
    end
    object edtAskDate: TEdit
      Left = 480
      Top = 8
      Width = 73
      Height = 21
      MaxLength = 8
      TabOrder = 2
      Text = 'edtAskDate'
    end
    object edtBuyType: TEdit
      Left = 608
      Top = 8
      Width = 57
      Height = 21
      TabOrder = 3
      Text = 'edtBuyType'
    end
    object edtType: TEdit
      Left = 352
      Top = 8
      Width = 57
      Height = 21
      TabOrder = 4
      Text = 'edtType'
    end
    object edtAskDepart: TEdit
      Left = 72
      Top = 32
      Width = 137
      Height = 21
      TabOrder = 5
      Text = 'edtAskDepart'
    end
    object edtStockDep: TEdit
      Left = 288
      Top = 32
      Width = 121
      Height = 21
      TabOrder = 6
      Text = 'edtStockDep'
    end
    object edtStockMan: TEdit
      Left = 72
      Top = 56
      Width = 89
      Height = 21
      TabOrder = 7
      Text = 'edtStockMan'
    end
    object edtProject: TEdit
      Left = 368
      Top = 56
      Width = 297
      Height = 21
      TabOrder = 8
      Text = 'edtProject'
    end
    object edtTel: TEdit
      Left = 216
      Top = 56
      Width = 73
      Height = 21
      TabOrder = 9
      Text = 'edtTel'
    end
    object edtAfmDate: TEdit
      Left = 480
      Top = 32
      Width = 73
      Height = 21
      TabOrder = 10
      Text = 'edtAfmDate'
    end
  end
  object Panel3: TPanel
    Left = 32
    Top = 482
    Width = 705
    Height = 41
    TabOrder = 2
    object btnQuery: TButton
      Left = 16
      Top = 8
      Width = 75
      Height = 25
      Caption = #26597'    '#35426
      TabOrder = 0
      OnClick = btnQueryClick
    end
    object btnNew: TButton
      Left = 116
      Top = 8
      Width = 75
      Height = 25
      Caption = #26032'    '#22686
      TabOrder = 1
      OnClick = btnNewClick
    end
    object btnEdit: TButton
      Left = 216
      Top = 8
      Width = 75
      Height = 25
      Caption = #20462'     '#25913
      TabOrder = 2
      OnClick = btnEditClick
    end
    object btnMove: TButton
      Left = 316
      Top = 8
      Width = 75
      Height = 25
      Caption = #21034'    '#38500
      TabOrder = 3
      OnClick = btnMoveClick
    end
    object btnDetail: TButton
      Left = 416
      Top = 8
      Width = 75
      Height = 25
      Caption = #23519#30475#35531#36092#21934
      TabOrder = 4
      OnClick = btnDetailClick
    end
    object btnOK: TButton
      Left = 516
      Top = 8
      Width = 75
      Height = 25
      Caption = #30906'     '#35469
      TabOrder = 5
      OnClick = btnOKClick
    end
    object btnExit: TButton
      Left = 616
      Top = 8
      Width = 75
      Height = 25
      Caption = #36864'    '#20986
      TabOrder = 6
      OnClick = btnExitClick
    end
  end
end
