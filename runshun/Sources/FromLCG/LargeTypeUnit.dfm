inherited LargeTypeForm: TLargeTypeForm
  Caption = #22823#39006#24314#27284
  FormStyle = fsStayOnTop
  OldCreateOrder = True
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  inherited Panel1: TPanel
    Caption = #22823#39006#24314#27284
  end
  inherited Panel2: TPanel
    inherited edtcode: TEdit
      MaxLength = 1
    end
    inherited edtname: TEdit
      MaxLength = 40
      OnKeyDown = edtnameKeyDown
    end
    inherited ListView1: TListView
      Columns = <
        item
          Width = 0
        end
        item
          Alignment = taCenter
          Caption = #20195#30908
          Width = 40
        end
        item
          Caption = '                  '#21517#31281
          Width = 300
        end>
      OnClick = ListView1Click
    end
  end
  inherited Panel3: TPanel
    inherited btnok: TBitBtn
      OnClick = btnokClick
    end
    inherited btnprint: TBitBtn
      OnClick = btnprintClick
    end
    inherited btnref: TBitBtn
      OnClick = btnrefClick
    end
  end
end
