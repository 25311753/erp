object AlarmSaleForm: TAlarmSaleForm
  Left = 314
  Top = 34
  Width = 651
  Height = 732
  Caption = #30331#38470#25552#31034'-'#19994#21153
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
  object lvArrival: TListView
    Left = 0
    Top = 0
    Width = 625
    Height = 229
    Color = clRed
    Columns = <
      item
        Caption = #26410#21040#36135' - '#25805#20316#21333#21495
        Width = 120
      end
      item
        Caption = #25509#21333#26085#26399
        Width = 100
      end
      item
        Caption = #23458#25143
        Width = 100
      end>
    FlatScrollBars = True
    GridLines = True
    ReadOnly = True
    RowSelect = True
    TabOrder = 0
    ViewStyle = vsReport
  end
  object lvDelay: TListView
    Left = 0
    Top = 232
    Width = 625
    Height = 229
    Color = clRed
    Columns = <
      item
        Caption = #36229#20184#27454#26399#38480' - '#25805#20316#21333#21495
        Width = 150
      end
      item
        Caption = #25509#21333#26085#26399
        Width = 100
      end
      item
        Caption = #23458#25143
        Width = 100
      end
      item
        Caption = #20184#27454#26041#24335
        Width = 70
      end
      item
        Caption = #20184#27454#26085#26399
        Width = 100
      end>
    FlatScrollBars = True
    GridLines = True
    ReadOnly = True
    RowSelect = True
    TabOrder = 1
    ViewStyle = vsReport
  end
  object lvTask: TListView
    Left = 0
    Top = 464
    Width = 625
    Height = 229
    Color = clRed
    Columns = <
      item
        Caption = #20219#21153#24773#20917' - '#24180#26376
        Width = 150
      end
      item
        Caption = #21097#20313#20219#21153#37327
        Width = 100
      end
      item
        Caption = #21097#20313#26032#23458#25968
        Width = 100
      end>
    FlatScrollBars = True
    GridLines = True
    ReadOnly = True
    RowSelect = True
    TabOrder = 2
    ViewStyle = vsReport
  end
end
