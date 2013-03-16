object XkQryForm: TXkQryForm
  Left = 258
  Top = 172
  Width = 870
  Height = 500
  Caption = #26032#23458#31649#29702'-'#26597#35810
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
  object plQuery: TPanel
    Left = 6
    Top = 0
    Width = 683
    Height = 27
    TabOrder = 0
    object btnQry: TButton
      Left = 613
      Top = 0
      Width = 63
      Height = 25
      Caption = #26597#35810
      TabOrder = 0
      OnClick = btnQryClick
    end
    object Panel5: TPanel
      Left = 8
      Top = 2
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #19994#21153#21592
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 1
    end
    object cbbQryOpCodeSl: TComboBox
      Left = 70
      Top = 2
      Width = 121
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 2
    end
    object Panel1: TPanel
      Left = 192
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
      TabOrder = 3
    end
    object cbYear: TComboBox
      Left = 252
      Top = 2
      Width = 71
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 4
      Items.Strings = (
        ''
        '2010'
        '2011'
        '2012'
        '2013'
        '2014'
        '2015'
        '2016'
        '2017'
        '2018')
    end
    object Panel3: TPanel
      Left = 453
      Top = 2
      Width = 60
      Height = 21
      BevelInner = bvLowered
      BevelOuter = bvLowered
      Caption = #23395#24230
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 5
    end
    object cbQ: TComboBox
      Left = 513
      Top = 2
      Width = 71
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 6
      Items.Strings = (
        ''
        'Q1'
        'Q2'
        'Q3'
        'Q4')
    end
    object Panel2: TPanel
      Left = 322
      Top = 2
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
      TabOrder = 7
    end
    object cbMonth: TComboBox
      Left = 382
      Top = 2
      Width = 71
      Height = 21
      Style = csDropDownList
      ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      ItemHeight = 13
      TabOrder = 8
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
  end
  object lvQry: TListView
    Left = 8
    Top = 36
    Width = 761
    Height = 405
    Columns = <
      item
        Caption = #22995#21517
      end
      item
        Caption = #26102#38388#27573
        Width = 100
      end
      item
        Caption = #26032#23458#20010#25968
        Width = 100
      end
      item
        Caption = #30446#26631#20010#25968
        Width = 90
      end
      item
        Caption = #26159#21542#23436#25104
        Width = 70
      end
      item
        Caption = #21097#20313#20010#25968
        Width = 80
      end
      item
        Caption = #21097#20313#27604#20363
        Width = 80
      end>
    FlatScrollBars = True
    GridLines = True
    ReadOnly = True
    RowSelect = True
    TabOrder = 1
    ViewStyle = vsReport
  end
end
