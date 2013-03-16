object MnPictureForm: TMnPictureForm
  Left = 452
  Top = 111
  Width = 696
  Height = 532
  Caption = #26448#26009#22806#35264#23637#31034
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
  object Label2: TLabel
    Left = 9
    Top = 429
    Width = 51
    Height = 13
    Caption = #26448#26009#32232#34399' '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label3: TLabel
    Left = 168
    Top = 429
    Width = 51
    Height = 13
    Caption = #21697#21517#35215#26684' '
  end
  object Label1: TLabel
    Left = 235
    Top = 4
    Width = 198
    Height = 32
    Caption = #26448#26009#22806#35264#23637#31034
    Font.Charset = CHINESEBIG5_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = #27161#26999#39636
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Image1: TImage
    Left = 58
    Top = 473
    Width = 57
    Height = 26
    Visible = False
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 43
    Width = 289
    Height = 377
    Caption = #26448#26009#20449#24687
    TabOrder = 0
    object DBGrid1: TDBGrid
      Left = 8
      Top = 16
      Width = 273
      Height = 353
      BiDiMode = bdLeftToRight
      Color = clSilver
      DataSource = DSMnPic
      ParentBiDiMode = False
      TabOrder = 0
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -11
      TitleFont.Name = 'MS Sans Serif'
      TitleFont.Style = []
      Columns = <
        item
          Color = clMedGray
          Expanded = False
          FieldName = 'ml_mncode'
          ReadOnly = True
          Title.Caption = #26448#26009#32232#34399
          Width = 150
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'ml_mnname'
          ReadOnly = True
          Title.Caption = #21697#21517#35215#26684
          Visible = True
        end>
    end
  end
  object btnOpenDB: TButton
    Left = 618
    Top = 7
    Width = 53
    Height = 20
    Caption = #28687#35261#20840#37096
    Enabled = False
    TabOrder = 1
    Visible = False
    OnClick = btnOpenDBClick
  end
  object btnQueryMT: TButton
    Left = 74
    Top = 426
    Width = 87
    Height = 16
    Caption = #26448#26009#32232#34399#25552#21462
    Enabled = False
    TabOrder = 2
    OnClick = btnQueryMTClick
  end
  object btnExit: TButton
    Left = 607
    Top = 475
    Width = 75
    Height = 25
    Caption = #36864#12288#20986
    TabOrder = 3
    OnClick = btnExitClick
  end
  object edtMater: TEdit
    Left = 9
    Top = 445
    Width = 152
    Height = 21
    CharCase = ecUpperCase
    Color = clSilver
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 4
  end
  object edtMnname: TEdit
    Left = 168
    Top = 445
    Width = 129
    Height = 21
    Color = clSilver
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 5
  end
  object btnOK: TButton
    Left = 532
    Top = 475
    Width = 75
    Height = 25
    Caption = #30906#23450
    Enabled = False
    TabOrder = 6
    OnClick = btnOKClick
  end
  object btnQuery: TButton
    Left = 382
    Top = 475
    Width = 75
    Height = 25
    Caption = #26597#12288#35426
    TabOrder = 7
    OnClick = btnQueryClick
  end
  object GroupBox2: TGroupBox
    Left = 305
    Top = 44
    Width = 377
    Height = 427
    Caption = #26448#26009#22806#35264
    TabOrder = 8
    object DBImage1: TDBImage
      Left = 7
      Top = 15
      Width = 360
      Height = 353
      BorderStyle = bsNone
      Color = clSilver
      DataField = 'ml_image'
      DataSource = DSMnPic
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = False
      TabOrder = 0
    end
    object DBNgt: TDBNavigator
      Left = 127
      Top = 396
      Width = 240
      Height = 25
      DataSource = DSMnPic
      Flat = True
      TabOrder = 1
    end
    object GroupBox3: TGroupBox
      Left = 7
      Top = 370
      Width = 117
      Height = 53
      Caption = #22294#29255#36681#25563#27231
      Enabled = False
      TabOrder = 2
      Visible = False
      object btnOpenPic: TButton
        Left = 10
        Top = 20
        Width = 48
        Height = 29
        Caption = #25171#12288#38283
        TabOrder = 0
      end
      object btnSaveP: TButton
        Left = 63
        Top = 20
        Width = 51
        Height = 29
        Caption = #20445#12288#23384
        TabOrder = 1
      end
    end
  end
  object btnNew: TButton
    Left = 457
    Top = 475
    Width = 75
    Height = 25
    Caption = #26032#12288#22686
    Enabled = False
    TabOrder = 9
    OnClick = btnNewClick
  end
  object DSMnPic: TDataSource
    DataSet = ADOT1
    Left = 456
    Top = 65535
  end
  object ADOC1: TADOConnection
    Connected = True
    ConnectionString = 
      'Provider=SQLOLEDB.1;Password=capitaluser;Persist Security Info=T' +
      'rue;User ID=capitaluser;Initial Catalog=capitaldb;Data Source=19' +
      '2.10.10.206;Use Procedure for Prepare=1;Auto Translate=True;Pack' +
      'et Size=4096;Workstation ID=U107532;Use Encryption for Data=Fals' +
      'e;Tag with column collation when possible=False'
    LoginPrompt = False
    Provider = 'SQLOLEDB.1'
    Left = 488
  end
  object ADOT1: TADOTable
    Connection = ADOC1
    BeforePost = ADOT1BeforePost
    TableName = 'materiallook'
    Left = 520
  end
  object PicDlg: TOpenPictureDialog
    Filter = 'Bitmaps (*.bmp)|*.bmp'
    Left = 584
  end
  object ADOQ1: TADOQuery
    Connection = ADOC1
    DataSource = DSMnPic
    Parameters = <>
    Left = 552
  end
end
