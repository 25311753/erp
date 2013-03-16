object OpQryInOutForm: TOpQryInOutForm
  Left = -1043
  Top = 175
  Width = 937
  Height = 226
  Caption = #25805#20316#31649#29702'-'#26597#35810'-'#24212#25910#24212#20184#26126#32454
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 3
    Top = 4
    Width = 39
    Height = 13
    Caption = #24212#25910'     '
  end
  object Label2: TLabel
    Left = 410
    Top = 5
    Width = 36
    Height = 13
    Caption = #24212#20184'    '
  end
  object lvInDetail: TListView
    Left = 4
    Top = 22
    Width = 397
    Height = 163
    Columns = <
      item
        Caption = #39033#30446
        Width = 100
      end
      item
        Caption = #25968#37327
        Width = 70
      end
      item
        Caption = #21333#20215
        Width = 70
      end
      item
        Caption = #35745#20215#21333#20301
        Width = 80
      end
      item
        Caption = #37329#39069
        Width = 70
      end>
    GridLines = True
    ReadOnly = True
    RowSelect = True
    TabOrder = 0
    ViewStyle = vsReport
  end
  object lvOutDetail: TListView
    Left = 410
    Top = 21
    Width = 503
    Height = 162
    Columns = <
      item
        Caption = #39033#30446
        Width = 100
      end
      item
        Caption = #25968#37327
        Width = 70
      end
      item
        Caption = #21333#20215
        Width = 70
      end
      item
        Caption = #20379#24212#21830
        Width = 90
      end
      item
        Caption = #35745#20215#21333#20301
        Width = 80
      end
      item
        Caption = #37329#39069
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
