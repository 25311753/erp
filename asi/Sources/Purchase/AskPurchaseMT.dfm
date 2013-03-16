object AskPurchaseMTForm: TAskPurchaseMTForm
  Left = 393
  Top = 166
  BorderIcons = [biSystemMenu]
  BorderStyle = bsToolWindow
  Caption = #26448#26009#32232#34399#26597#35426
  ClientHeight = 466
  ClientWidth = 973
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
  object Label5: TLabel
    Left = 312
    Top = 0
    Width = 198
    Height = 32
    Caption = #26448#26009#32232#34399#26597#35426
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = #27161#26999#39636
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label8: TLabel
    Left = 2
    Top = 411
    Width = 65
    Height = 13
    Caption = #26448#26009#32232#34399#65306
  end
  object Label9: TLabel
    Left = 202
    Top = 411
    Width = 39
    Height = 13
    Caption = #21697#21517#65306
  end
  object Label14: TLabel
    Left = 194
    Top = 443
    Width = 39
    Height = 13
    Caption = #39006#21029#65306
  end
  object Label15: TLabel
    Left = 586
    Top = 411
    Width = 39
    Height = 13
    Caption = #21934#20301#65306
  end
  object ctlPage: TPageControl
    Left = 2
    Top = 35
    Width = 721
    Height = 361
    ActivePage = ctlTree
    TabIndex = 2
    TabOrder = 0
    object ctlType: TTabSheet
      Caption = #20998#39006#26597#35426
      object Label6: TLabel
        Left = 8
        Top = 48
        Width = 104
        Height = 13
        Caption = #26448#26009#21517#31281#21450#35215#26684#65306
      end
      object Label1: TLabel
        Left = 8
        Top = 72
        Width = 52
        Height = 13
        Caption = #20844#21496#21029#65306
      end
      object Label2: TLabel
        Left = 16
        Top = 96
        Width = 39
        Height = 13
        Caption = #22823#39006#65306
      end
      object Label3: TLabel
        Left = 16
        Top = 120
        Width = 39
        Height = 13
        Caption = #20013#39006#65306
      end
      object Label4: TLabel
        Left = 16
        Top = 144
        Width = 39
        Height = 13
        Caption = #23567#39006#65306
      end
      object edtCorp: TEdit
        Left = 8
        Top = 16
        Width = 25
        Height = 21
        CharCase = ecUpperCase
        MaxLength = 1
        TabOrder = 0
        Text = 'EDTCORP'
        OnChange = edtCorpChange
      end
      object edtID0: TEdit
        Left = 34
        Top = 16
        Width = 47
        Height = 21
        CharCase = ecUpperCase
        MaxLength = 4
        TabOrder = 1
        Text = 'EDTID0'
        OnChange = edtID0Change
      end
      object Panel1: TPanel
        Left = 89
        Top = 24
        Width = 14
        Height = 3
        TabOrder = 2
      end
      object edtID1: TEdit
        Left = 112
        Top = 16
        Width = 209
        Height = 21
        CharCase = ecUpperCase
        MaxLength = 15
        TabOrder = 3
        Text = 'EDIT3'
        OnChange = edtID1Change
      end
      object edtSpec: TEdit
        Left = 112
        Top = 40
        Width = 209
        Height = 21
        TabOrder = 4
        Text = 'edtSpec'
      end
      object lstCorp: TComboBox
        Left = 64
        Top = 64
        Width = 257
        Height = 21
        Style = csDropDownList
        ItemHeight = 0
        TabOrder = 5
        OnClick = lstCorpClick
      end
      object lstLarge: TComboBox
        Left = 64
        Top = 88
        Width = 257
        Height = 21
        Style = csDropDownList
        ItemHeight = 0
        TabOrder = 6
        OnClick = lstLargeClick
      end
      object lstMid: TComboBox
        Left = 64
        Top = 112
        Width = 257
        Height = 21
        Style = csDropDownList
        ItemHeight = 0
        TabOrder = 7
        OnClick = lstMidClick
      end
      object lstMin: TComboBox
        Left = 64
        Top = 136
        Width = 257
        Height = 21
        Style = csDropDownList
        ItemHeight = 0
        TabOrder = 8
        OnClick = lstMinClick
      end
      object lstView: TListView
        Left = 8
        Top = 160
        Width = 705
        Height = 169
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
            Width = 200
          end
          item
            Caption = #21934#20301
          end
          item
            Caption = #24314#27284#26085#26399
          end>
        GridLines = True
        HideSelection = False
        ReadOnly = True
        RowSelect = True
        TabOrder = 9
        ViewStyle = vsReport
        OnDblClick = lstViewDblClick
        OnSelectItem = lstViewSelectItem
      end
      object Memo1: TMemo
        Left = 344
        Top = 32
        Width = 369
        Height = 121
        Color = clBtnFace
        Enabled = False
        Lines.Strings = (
          '')
        TabOrder = 10
      end
      object btnPrintRem: TButton
        Left = 344
        Top = 0
        Width = 97
        Height = 25
        Caption = #21015#21360#26448#26009#35215#33539
        TabOrder = 11
        OnClick = btnPrintRemClick
      end
      object btnRem2Excel: TButton
        Left = 456
        Top = 0
        Width = 113
        Height = 25
        Caption = #26448#26009#35215#33539#36681'Excel'
        TabOrder = 12
        OnClick = btnRem2ExcelClick
      end
    end
    object ctlPrefix: TTabSheet
      Caption = #32232#34399#25260#38957
      ImageIndex = 3
      object Label12: TLabel
        Left = 16
        Top = 8
        Width = 182
        Height = 13
        Caption = #25552#31034#65306#35531#36664#20837#26448#26009#32232#34399#30340#21069#24190#20301
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlue
        Font.Height = -13
        Font.Name = #26032#32048#26126#39636
        Font.Style = []
        ParentFont = False
      end
      object Label13: TLabel
        Left = 16
        Top = 40
        Width = 65
        Height = 13
        Caption = #25628#32034#25991#23383#65306
      end
      object edtPrefixID: TEdit
        Left = 80
        Top = 32
        Width = 169
        Height = 21
        TabOrder = 0
        Text = 'edtSearchText'
      end
      object btnPrefixQuery: TButton
        Left = 256
        Top = 28
        Width = 75
        Height = 25
        Caption = #26597#12288#35426
        TabOrder = 1
        OnClick = btnPrefixQueryClick
      end
      object lstPrefixView: TListView
        Left = 8
        Top = 56
        Width = 705
        Height = 273
        Columns = <
          item
            Caption = #20844#21496
            Width = 40
          end
          item
            Caption = #22823#39006
          end
          item
            Caption = #20013#39006
          end
          item
            Caption = #23567#39006
          end
          item
            Caption = #26448#26009#32232#34399
            Width = 150
          end
          item
            Caption = #21697#21517#35215#26684
            Width = 200
          end
          item
            Caption = #29992#36884
            Width = 80
          end
          item
            Caption = #26448#26009#35215#33539
          end
          item
            Caption = #21934#20301
          end
          item
            Caption = #24314#27284#26085#26399
          end>
        GridLines = True
        HideSelection = False
        ReadOnly = True
        RowSelect = True
        TabOrder = 2
        ViewStyle = vsReport
        OnDblClick = lstPrefixViewDblClick
        OnSelectItem = lstPrefixViewSelectItem
      end
    end
    object ctlTree: TTabSheet
      Caption = #30446#37636#26597#35426
      ImageIndex = 1
      OnShow = ctlTreeShow
      object Label7: TLabel
        Left = 8
        Top = 16
        Width = 52
        Height = 13
        Caption = #20844#21496#21029#65306
      end
      object lstTree: TTreeView
        Left = 16
        Top = 40
        Width = 169
        Height = 297
        HideSelection = False
        Indent = 19
        ReadOnly = True
        TabOrder = 0
        OnChange = lstTreeChange
        OnClick = lstTreeClick
      end
      object lstTreeView: TListView
        Left = 208
        Top = 8
        Width = 505
        Height = 321
        Columns = <
          item
            Caption = #26448#26009#32232#34399
            Width = 120
          end
          item
            Caption = #21697#21517#35215#26684
            Width = 150
          end
          item
            Caption = #29992#36884
            Width = 120
          end
          item
            Caption = #26448#26009#35215#33539
            Width = 65
          end
          item
            Caption = #21934#20301
          end
          item
            Caption = #24314#27284#26085#26399
          end>
        GridLines = True
        HideSelection = False
        ReadOnly = True
        RowSelect = True
        TabOrder = 1
        ViewStyle = vsReport
        OnDblClick = lstTreeViewDblClick
        OnSelectItem = lstTreeViewSelectItem
      end
      object lstTreeCorp: TComboBox
        Left = 64
        Top = 8
        Width = 113
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        TabOrder = 2
        OnClick = lstTreeCorpClick
      end
    end
    object ctlSearch: TTabSheet
      Caption = #25628#32034
      ImageIndex = 2
      object Label10: TLabel
        Left = 16
        Top = 40
        Width = 65
        Height = 13
        Caption = #25628#32034#25991#23383#65306
      end
      object Label11: TLabel
        Left = 16
        Top = 8
        Width = 234
        Height = 13
        Caption = #25552#31034#65306#35531#36664#20837#26448#26009#35215#26684#21517#31281#20013#21253#21547#30340#25991#23383
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlue
        Font.Height = -13
        Font.Name = #26032#32048#26126#39636
        Font.Style = []
        ParentFont = False
      end
      object labCorp: TLabel
        Left = 320
        Top = 0
        Width = 38
        Height = 13
        Caption = 'labCorp'
        Visible = False
      end
      object labID0: TLabel
        Left = 376
        Top = 0
        Width = 33
        Height = 13
        Caption = 'labID0'
        Visible = False
      end
      object labID1: TLabel
        Left = 424
        Top = 0
        Width = 33
        Height = 13
        Caption = 'labID1'
        Visible = False
      end
      object edtSearchText: TEdit
        Left = 80
        Top = 32
        Width = 225
        Height = 21
        TabOrder = 0
        Text = 'edtSearchText'
      end
      object lstSearchView: TListView
        Left = 8
        Top = 56
        Width = 705
        Height = 273
        Columns = <
          item
            Caption = #26448#26009#32232#34399
            Width = 150
          end
          item
            Caption = #21697#21517#35215#26684
            Width = 200
          end
          item
            Caption = #29992#36884
            Width = 150
          end
          item
            Caption = #26448#26009#35215#33539
            Width = 150
          end
          item
            Caption = #21934#20301
          end
          item
            Caption = #24314#27284#26085#26399
          end>
        GridLines = True
        HideSelection = False
        ReadOnly = True
        RowSelect = True
        TabOrder = 1
        ViewStyle = vsReport
        OnDblClick = lstSearchViewDblClick
        OnSelectItem = lstSearchViewSelectItem
      end
      object btnSearch: TButton
        Left = 312
        Top = 28
        Width = 75
        Height = 25
        Caption = #25628#12288#32034
        TabOrder = 2
        OnClick = btnSearchClick
      end
      object btnDetail: TButton
        Left = 392
        Top = 28
        Width = 75
        Height = 25
        Caption = #35443#32048#24773#27841
        TabOrder = 3
        OnClick = btnDetailClick
      end
    end
  end
  object btnToExcel: TButton
    Left = 378
    Top = 435
    Width = 65
    Height = 25
    Caption = #36681'Excel'
    TabOrder = 1
    OnClick = btnToExcelClick
  end
  object btnOK: TButton
    Left = 450
    Top = 435
    Width = 65
    Height = 25
    Caption = #30906'    '#35469
    TabOrder = 2
    OnClick = btnOKClick
  end
  object btnCancel: TButton
    Left = 522
    Top = 435
    Width = 65
    Height = 25
    Caption = #21462'    '#28040
    ModalResult = 2
    TabOrder = 3
  end
  object edtID: TEdit
    Left = 66
    Top = 403
    Width = 129
    Height = 21
    TabOrder = 4
    Text = 'edtID'
  end
  object edtName: TEdit
    Left = 242
    Top = 403
    Width = 329
    Height = 21
    TabOrder = 5
    Text = 'edtName'
  end
  object lstTreatType: TComboBox
    Left = 234
    Top = 435
    Width = 129
    Height = 21
    Style = csDropDownList
    ItemHeight = 13
    TabOrder = 6
    OnClick = lstTreatTypeClick
    Items.Strings = (
      #20840#37096
      #19968#33324#37319#36092
      #21512#32004#37319#36092)
  end
  object edtUnits: TEdit
    Left = 623
    Top = 403
    Width = 46
    Height = 21
    TabOrder = 7
    Text = 'edtUnits'
  end
  object GroupBox1: TGroupBox
    Left = 729
    Top = 38
    Width = 241
    Height = 358
    Caption = #29986#21697#22806#35264
    TabOrder = 8
    object DBImage1: TDBImage
      Left = 8
      Top = 18
      Width = 225
      Height = 333
      BorderStyle = bsNone
      Color = clSilver
      DataField = 'ml_image'
      DataSource = DSMnPic
      TabOrder = 0
    end
  end
  object DSMnPic: TDataSource
    DataSet = ADOT1
    Left = 8
  end
  object ADOC1: TADOConnection
    ConnectionString = 
      'Provider=SQLOLEDB.1;Password=capitaluser;Persist Security Info=T' +
      'rue;User ID=capitaluser;Initial Catalog=capitaldb;Data Source=19' +
      '2.10.10.206;Use Procedure for Prepare=1;Auto Translate=True;Pack' +
      'et Size=4096;Workstation ID=U107532;Use Encryption for Data=Fals' +
      'e;Tag with column collation when possible=False'
    LoginPrompt = False
    Provider = 'SQLOLEDB.1'
    Left = 48
  end
  object ADOT1: TADOTable
    Connection = ADOC1
    TableName = 'materiallook'
    Left = 88
  end
end
