object F_MaterialRem: TF_MaterialRem
  Left = 191
  Top = 93
  Width = 1066
  Height = 643
  Caption = #26448#26009#32232#34399#21407#21063
  Color = clBtnFace
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
  object Label1: TLabel
    Left = 376
    Top = 0
    Width = 337
    Height = 23
    AutoSize = False
    Caption = #26448#26009#32232#34399#21407#21063'                    '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -21
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 16
    Top = 40
    Width = 73
    Height = 13
    AutoSize = False
    Caption = #26448#26009#20998#39006#65306
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label3: TLabel
    Left = 224
    Top = 40
    Width = 66
    Height = 13
    Caption = #32232#34399#32048#21063#65306
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label4: TLabel
    Left = 392
    Top = 40
    Width = 49
    Height = 13
    AutoSize = False
    Caption = 'Label4'
  end
  object Label5: TLabel
    Left = 472
    Top = 40
    Width = 177
    Height = 13
    AutoSize = False
    Caption = 'Label5'
  end
  object Label11: TLabel
    Left = 228
    Top = 349
    Width = 69
    Height = 13
    AutoSize = False
    Caption = #38468#23660#36039#26009#65306
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label13: TLabel
    Left = 728
    Top = 40
    Width = 38
    Height = 13
    Caption = 'Label13'
  end
  object Label14: TLabel
    Left = 832
    Top = 40
    Width = 145
    Height = 13
    AutoSize = False
    Caption = 'Label14'
  end
  object btnOK: TButton
    Left = 568
    Top = 555
    Width = 75
    Height = 25
    Caption = #30906#12288#23450
    TabOrder = 0
    OnClick = btnOKClick
  end
  object btnExit: TButton
    Left = 647
    Top = 555
    Width = 75
    Height = 25
    Caption = #36864#12288#20986
    TabOrder = 1
    OnClick = btnExitClick
  end
  object lstTree: TTreeView
    Left = 16
    Top = 64
    Width = 201
    Height = 513
    BevelKind = bkSoft
    Color = clSkyBlue
    HideSelection = False
    Indent = 19
    ReadOnly = True
    TabOrder = 2
    OnClick = lstTreeClick
  end
  object Memo1: TMemo
    Left = 224
    Top = 84
    Width = 497
    Height = 258
    BevelKind = bkSoft
    Color = clSilver
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    ScrollBars = ssBoth
    TabOrder = 3
    WantTabs = True
  end
  object btnEdit: TButton
    Left = 229
    Top = 555
    Width = 75
    Height = 25
    Caption = #32232#12288#36655
    TabOrder = 4
    OnClick = btnEditClick
  end
  object Panel1: TPanel
    Left = 224
    Top = 64
    Width = 498
    Height = 20
    BevelInner = bvLowered
    BevelOuter = bvLowered
    TabOrder = 5
    object Label6: TLabel
      Left = 5
      Top = 4
      Width = 29
      Height = 13
      AutoSize = False
      Caption = #20301#25976
    end
    object Label7: TLabel
      Left = 84
      Top = 5
      Width = 44
      Height = 12
      AutoSize = False
      Caption = #21517#12288#31281
    end
    object Label8: TLabel
      Left = 154
      Top = 4
      Width = 59
      Height = 13
      AutoSize = False
      Caption = #32232#34399#21407#21063
    end
    object Label9: TLabel
      Left = 45
      Top = 4
      Width = 6
      Height = 13
      AutoSize = False
      Caption = #65372
    end
    object Label10: TLabel
      Left = 141
      Top = 4
      Width = 6
      Height = 13
      AutoSize = False
      Caption = #65372
    end
  end
  object btnPrint123: TButton
    Left = 304
    Top = 555
    Width = 75
    Height = 25
    Caption = #21015#12288#21360
    TabOrder = 6
    OnClick = btnPrint123Click
  end
  object PageControl1: TPageControl
    Left = 227
    Top = 366
    Width = 507
    Height = 183
    ActivePage = TabSheet1
    MultiLine = True
    Style = tsFlatButtons
    TabIndex = 0
    TabOrder = 7
    object TabSheet1: TTabSheet
      Caption = #38364#26044#21517#31281
      object Memo2: TMemo
        Left = 0
        Top = 0
        Width = 494
        Height = 153
        BevelKind = bkSoft
        Color = clSilver
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        ScrollBars = ssBoth
        TabOrder = 0
        WantTabs = True
      end
    end
    object TabSheet2: TTabSheet
      Caption = #38364#26044#32232#34399#21407#21063
      ImageIndex = 1
      object Memo3: TMemo
        Left = 0
        Top = 0
        Width = 495
        Height = 153
        BevelKind = bkSoft
        Color = clSilver
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        ScrollBars = ssBoth
        TabOrder = 0
        WantTabs = True
      end
    end
    object TabSheet3: TTabSheet
      Caption = #20854#23427#38468#34920
      ImageIndex = 2
      object Memo4: TMemo
        Left = 0
        Top = 0
        Width = 495
        Height = 153
        BevelKind = bkSoft
        Color = clSilver
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        ScrollBars = ssBoth
        TabOrder = 0
        WantTabs = True
      end
    end
  end
  object btnPrint4: TButton
    Left = 380
    Top = 555
    Width = 75
    Height = 25
    Caption = #21015#21360#38468#34920
    TabOrder = 8
    OnClick = btnPrint4Click
  end
  object Panel2: TPanel
    Left = 728
    Top = 64
    Width = 251
    Height = 513
    BevelInner = bvLowered
    TabOrder = 9
    object Label12: TLabel
      Left = 8
      Top = 5
      Width = 60
      Height = 13
      Caption = #25628#32034#25991#23383#65306
    end
    object edtSearchText: TEdit
      Left = 8
      Top = 21
      Width = 172
      Height = 21
      TabOrder = 0
    end
    object lstSearchView: TListView
      Left = 8
      Top = 51
      Width = 237
      Height = 430
      Color = clSkyBlue
      Columns = <
        item
          Caption = #20998#39006#32232#34399
          Width = 70
        end
        item
          Caption = #20998#39006#21517#31281
          Width = 164
        end>
      GridLines = True
      HideSelection = False
      ReadOnly = True
      RowSelect = True
      TabOrder = 1
      ViewStyle = vsReport
      OnSelectItem = lstSearchViewSelectItem
    end
    object btnSearch: TButton
      Left = 184
      Top = 21
      Width = 61
      Height = 21
      Caption = #25628'     '#32034
      TabOrder = 2
      OnClick = btnSearchClick
    end
  end
end
