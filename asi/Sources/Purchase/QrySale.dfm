object QrySaleForm: TQrySaleForm
  Left = 1452
  Top = -156
  Width = 961
  Height = 611
  BorderIcons = [biSystemMenu]
  Caption = #19994#21153#32508#21512#26597#35810
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
    Left = 8
    Top = 279
    Width = 33
    Height = 13
    Caption = #21512#35745'   '
  end
  object lbTotalPrize: TLabel
    Left = 214
    Top = 279
    Width = 6
    Height = 13
    Alignment = taCenter
    Caption = '0'
  end
  object Label2: TLabel
    Left = 8
    Top = 36
    Width = 39
    Height = 13
    Caption = #19994#32489'   '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label3: TLabel
    Left = 8
    Top = 305
    Width = 39
    Height = 13
    Caption = #22238#25187'   '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Panel7: TPanel
    Left = -2
    Top = 0
    Width = 608
    Height = 27
    TabOrder = 0
    object Bevel1: TBevel
      Left = 293
      Top = 1
      Width = 248
      Height = 24
    end
    object Label4: TLabel
      Left = 297
      Top = 8
      Width = 54
      Height = 13
      Caption = #22238#25187#26597#35810'  '
    end
    object btnQryYear: TButton
      Left = 543
      Top = 1
      Width = 63
      Height = 25
      Caption = #26597#35810
      TabOrder = 0
      OnClick = btnQryYearClick
    end
    object Panel9: TPanel
      Left = 3
      Top = 2
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #24180#24230
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 1
    end
    object cbbYear: TComboBox
      Left = 63
      Top = 3
      Width = 76
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      ItemIndex = 0
      TabOrder = 2
      Text = '2012'
      Items.Strings = (
        '2012'
        '2013'
        '2014'
        '2015'
        '2016'
        '2017'
        '2018'
        '2019'
        '2020'
        '2021'
        '2022')
    end
    object Panel1: TPanel
      Left = 139
      Top = 3
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #26376#20221
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 3
    end
    object cbbMonth: TComboBox
      Left = 199
      Top = 3
      Width = 76
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 4
      Items.Strings = (
        ''
        '1'
        '2'
        '3'
        '4'
        '5'
        '6'
        '7'
        '8'
        '9'
        '10'
        '11'
        '12')
    end
    object Panel3: TPanel
      Left = 356
      Top = 3
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #23458#25143
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 5
    end
    object cbbClShortName: TComboBox
      Left = 418
      Top = 3
      Width = 121
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 6
    end
  end
  object lvTask: TListView
    Left = 2
    Top = 52
    Width = 936
    Height = 225
    Columns = <
      item
        Caption = #22995#21517
      end
      item
        Caption = #27611#21033
      end
      item
        Caption = #24212#21457#25552#25104
        Width = 80
      end
      item
        Caption = #23454#21457#25552#25104
        Width = 90
      end
      item
        Caption = #24453#21457#25552#25104
        Width = 100
      end
      item
        Caption = #21457#25918#24773#20917
        Width = 80
      end
      item
        Caption = #19994#32489#23436#25104#37327
        Width = 100
      end
      item
        Caption = #23578#26410#23436#25104#37327
        Width = 100
      end
      item
        Caption = #21097#20313#27604#20363
        Width = 100
      end>
    Enabled = False
    FlatScrollBars = True
    GridLines = True
    ReadOnly = True
    RowSelect = True
    TabOrder = 1
    ViewStyle = vsReport
  end
  object Edit1: TEdit
    Left = 647
    Top = 0
    Width = 121
    Height = 21
    TabOrder = 2
    Text = 'Edit1'
    Visible = False
  end
  object Panel21: TPanel
    Left = 1
    Top = 27
    Width = 935
    Height = 7
    Color = 16349446
    TabOrder = 3
  end
  object Panel2: TPanel
    Left = 1
    Top = 296
    Width = 935
    Height = 7
    Color = 16349446
    TabOrder = 4
  end
  object lvKB: TListView
    Left = 1
    Top = 321
    Width = 936
    Height = 225
    Columns = <
      item
        Caption = #25805#20316#21333#21495
        Width = 100
      end
      item
        Caption = #26085#26399
        Width = 100
      end
      item
        Caption = #23458#25143
        Width = 60
      end
      item
        Caption = #22238#25187#37329#39069
        Width = 100
      end
      item
        Caption = #20184#22238#25187#26085#26399
        Width = 100
      end>
    Enabled = False
    FlatScrollBars = True
    GridLines = True
    ReadOnly = True
    RowSelect = True
    TabOrder = 5
    ViewStyle = vsReport
  end
  object Button1: TButton
    Left = 870
    Top = 0
    Width = 75
    Height = 25
    Caption = #26368#23567#21270
    TabOrder = 6
    OnClick = Button1Click
  end
  object TrayIcon1: TTrayIcon
    Hint = 'ASI'
    Hide = True
    RestoreOn = imDoubleClick
    PopupMenuOn = imNone
    Left = 800
  end
end
