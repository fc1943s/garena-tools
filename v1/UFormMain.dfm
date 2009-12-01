object FormMain: TFormMain
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  ClientHeight = 543
  ClientWidth = 294
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Trebuchet MS'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesigned
  ShowHint = True
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 16
  object lblTitle: TLabel
    Left = 0
    Top = 8
    Width = 300
    Height = 18
    Alignment = taCenter
    AutoSize = False
    Caption = '{Title} {Version}'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -13
    Font.Name = 'Trebuchet MS'
    Font.Style = []
    ParentFont = False
  end
  object lblForumLink: TLabel
    Left = 0
    Top = 41
    Width = 300
    Height = 16
    Cursor = crHandPoint
    Alignment = taCenter
    AutoSize = False
    Caption = '{ForumLink}'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -11
    Font.Name = 'Trebuchet MS'
    Font.Style = [fsUnderline]
    ParentFont = False
    OnClick = OpenForum
  end
  object lblStew: TLabel
    Left = 0
    Top = 25
    Width = 300
    Height = 16
    Cursor = crHandPoint
    Alignment = taCenter
    AutoSize = False
    Caption = 'by Stew UnknowN'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -11
    Font.Name = 'Trebuchet MS'
    Font.Style = [fsUnderline]
    ParentFont = False
    OnClick = OpenForum
  end
  object lblUpdates: TLabel
    Left = 0
    Top = 342
    Width = 300
    Height = 16
    Cursor = crHandPoint
    Alignment = taCenter
    AutoSize = False
    Caption = 'Atualiza'#231#245'es em {DownloadLink}'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -11
    Font.Name = 'Trebuchet MS'
    Font.Style = [fsUnderline]
    ParentFont = False
    OnClick = OpenForum
  end
  object lblGarenaVersion: TLabel
    Left = 0
    Top = 322
    Width = 300
    Height = 16
    Alignment = taCenter
    AutoSize = False
    Caption = 'Feito para Garena XXX'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -11
    Font.Name = 'Trebuchet MS'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object gbxLegend: TGroupBox
    Left = 7
    Top = 235
    Width = 281
    Height = 47
    Caption = 'Legenda'
    TabOrder = 0
    object gbxLegend_imgUnavailable: TImage
      Left = 19
      Top = 18
      Width = 17
      Height = 17
    end
    object gbxLegend_lblUnavailable: TLabel
      Left = 42
      Top = 20
      Width = 59
      Height = 16
      Caption = 'Indispon'#237'vel'
    end
    object gbxLegend_lblDisabled: TLabel
      Left = 137
      Top = 20
      Width = 36
      Height = 16
      Caption = 'Inativo'
    end
    object gbxLegend_imgDisabled: TImage
      Left = 114
      Top = 18
      Width = 17
      Height = 17
    end
    object gbxLegend_imgEnabled: TImage
      Left = 207
      Top = 18
      Width = 17
      Height = 17
    end
    object gbxLegend_lblEnabled: TLabel
      Left = 230
      Top = 20
      Width = 26
      Height = 16
      Caption = 'Ativo'
    end
  end
  object gbxHacks: TGroupBox
    Left = 7
    Top = 288
    Width = 281
    Height = 28
    Caption = 'Hacks'
    TabOrder = 1
  end
  object rgpLanguage: TRadioGroup
    Left = 7
    Top = 63
    Width = 122
    Height = 53
    Caption = 'Idioma/Language'
    ItemIndex = 0
    Items.Strings = (
      'Portugu'#234's'
      'English')
    TabOrder = 2
    OnClick = rgpLanguageClick
  end
  object gbxSelectGarena: TGroupBox
    Left = 135
    Top = 63
    Width = 153
    Height = 77
    Caption = 'Selecione o Garena'
    TabOrder = 3
    object gbxSelectGarena_lblAccountID: TLabel
      Left = 9
      Top = 19
      Width = 71
      Height = 16
      Caption = 'ID da conta: 0'
    end
    object gbxSelectGarena_cbbCurrentGarena: TComboBox
      Left = 8
      Top = 42
      Width = 136
      Height = 24
      Style = csDropDownList
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Trebuchet MS'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnChange = gbxSelectGarena_cbbCurrentGarenaChange
    end
  end
  object gbxSettings: TGroupBox
    Left = 5
    Top = 146
    Width = 281
    Height = 83
    Caption = 'Configura'#231#245'es'
    TabOrder = 4
    object gbxSettings_lblCustomGarenaPath: TLabel
      Left = 9
      Top = 17
      Width = 133
      Height = 16
      Caption = 'Caminho do Garena.exe:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Trebuchet MS'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object gbxSettings_edtCustomGarenaPath: TEdit
      Left = 9
      Top = 34
      Width = 264
      Height = 19
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -9
      Font.Name = 'Small Fonts'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
    end
    object gbxSettings_chbEnableHelp: TCheckBox
      Left = 9
      Top = 59
      Width = 97
      Height = 17
      Caption = 'Ativar ajuda'
      Checked = True
      ParentShowHint = False
      ShowHint = True
      State = cbChecked
      TabOrder = 1
      OnClick = gbxSettings_chbEnableHelpClick
    end
  end
  object btnRunGarena: TButton
    Left = 8
    Top = 122
    Width = 121
    Height = 18
    Caption = 'Executar Garena'
    TabOrder = 5
    OnClick = btnRunGarenaClick
  end
  object tmrMain: TTimer
    Interval = 200
    OnTimer = tmrMainTimer
    Left = 10
    Top = 6
  end
  object imlMain: TImageList
    Left = 53
    Top = 6
    Bitmap = {
      494C010103000400040010001000FFFFFFFFFF00FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000001000000001002000000000000010
      0000000000000000000000000000000000006B6B6BFF6B6B6BFF6B6B6BFF6B6B
      6BFF6B6B6BFF6B6B6BFF6B6B6BFF6B6B6BFF6B6B6BFF6B6B6BFF6B6B6BFF6B6B
      6BFF6B6B6BFF6B6B6BFF6B6B6BFF6B6B6BFFB0B0B091B0B0B091B0B0B0FFB0B0
      B0FFB0B0B0FFB0B0B0FFB0B0B0FFB0B0B0FFB0B0B0FFB0B0B0FFB0B0B0FFB0B0
      B0FFB0B0B0FFB0B0B0FFB0B0B0FFB0B0B091B0B0B091B0B0B091B0B0B0FFB0B0
      B0FFB0B0B0FFB0B0B0FFB0B0B0FFB0B0B0FFB0B0B0FFB0B0B0FFB0B0B0FFB0B0
      B0FFB0B0B0FFB0B0B0FFB0B0B0FFB0B0B0910000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000006F6F6FFF6F6F6FFF6F6F6FFF0D0D
      0DFF0F0F0FFF111111FF131313FF141414FF171717FF1A1A1AFF1C1C1CFF1C1C
      1CFF1A1A1AFF151515FF6F6F6FFF6F6F6FFFB7B7B7FFB7B7B7FFB7B7B7FF0000
      2AFF000034FF00003AFF000041FF000048FF000052FF00005AFF000061FF0000
      5FFF000059FF000049FFB7B7B7FFB7B7B7FFB7B7B7FFB7B7B7FFB7B7B7FF021B
      02FF022202FF032703FF042B04FF053005FF063606FF073C07FF084108FF0840
      08FF083C08FF063106FFB7B7B7FFB7B7B7FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000747474FF747474FF0F0F0FFF1212
      12FF131313FF151515FF191919FF1D1D1DFF222222FF252525FF282828FF2929
      29FF282828FF252525FF191919FF747474FFBFBFBFFFBFBFBFFF000031FF0000
      3BFF000043FF00004BFF000057FF000065FF000074FF00007FFF000087FF0000
      89FF000088FF000080FF00005AFFBFBFBFFFBFBFBFFFBFBFBFFF022002FF0427
      04FF052D05FF073307FF083A08FF094409FF0B4D0BFF0C550CFF0D5B0DFF0D5D
      0DFF0D5C0DFF0B570BFF093D09FFBFBFBFFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000787878FF787878FF131313FF1616
      16FF191919FF1D1D1DFF232323FF272727FF2C2C2CFF2F2F2FFF323232FF3333
      33FF343434FF323232FF2A2A2AFF787878FFC7C7C7FFC7C7C7FF000040FF0000
      4CFF000057FF000066FF000077FF000088FF000096FF0000A2FF0000ABFF0000
      AFFF0000AFFF0000ABFF000091FFC7C7C7FFC7C7C7FFC7C7C7FF052A05FF0732
      07FF073A07FF094509FF0B500BFF0D5C0DFF0F660FFF116E11FF127412FF1277
      12FF127712FF117411FF0F630FFFC7C7C7FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000007C7C7CFF7C7C7CFF161616FF1B1B
      1BFF202020FF252525FF2B2B2BFF303030FF353535FF393939FF3C3C3CFF3D3D
      3DFF3E3E3EFF3D3D3DFF383838FF7C7C7CFFCFCFCFFFCFCFCFFF000050FF0000
      5EFF00006DFF000081FF000094FF0000A6FF0000B4FF0000C1FF0000CCFF0000
      D0FF0000D2FF0000D0FF0000BEFFCFCFCFFFCFCFCFFFCFCFCFFF073507FF093F
      09FF0A4A0AFF0C580CFF0E640EFF107110FF137B13FF138313FF148914FF158D
      15FF158E15FF158C15FF138113FFCFCFCFFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000828282FF828282FF1B1B1BFF2121
      21FF282828FF2E2E2EFF343434FF393939FF3E3E3EFF424242FF454545FF4646
      46FF474747FF464646FF434343FF828282FFD4D4D4FFD4D4D4FF00005FFF0000
      72FF000085FF00009CFF0000AFFF0000C1FF0000D1FF0000DFFF0101E9FF0101
      EDFF0000EFFF0000EEFF0000E5FFD4D4D4FFD4D4D4FFD4D4D4FF084008FF0A4D
      0AFF0D5B0DFF0F6A0FFF117711FF138413FF158E15FF179617FF189E18FF19A2
      19FF19A419FF18A218FF179B17FFD4D4D4FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000888888FF888888FF212121FF2727
      27FF2F2F2FFF353535FF3B3B3BFF414141FF464646FF4A4A4AFF4E4E4EFF4F4F
      4FFF4E4E4EFF4B4B4BFF494949FF888888FFD6D6D6FFD6D6D6FF000070FF0000
      86FF00009DFF0000B4FF0000CAFF0000DEFF0101EAFF0404F3FF0808F8FF0808
      F9FF0606FAFF0202F9FF0101F6FFD6D6D6FFD6D6D6FFD6D6D6FF0A4B0AFF0D5B
      0DFF106C10FF127B12FF148914FF179617FF1AA31AFF1DB01DFF20BB20FF21C0
      21FF21C121FF1EBA1EFF1CB11CFFD6D6D6FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000909090FF909090FF252525FF2D2D
      2DFF353535FF3D3D3DFF454545FF4E4E4EFF555555FF5C5C5CFF656565FF6666
      66FF636363FF565656FF4F4F4FFF909090FFD9D9D9FFD9D9D9FF000080FF0000
      99FF0000B3FF0101CCFF0505E0FF0A0AF1FF1111F9FF1919FEFF2424FFFF2626
      FFFF2020FFFF0F0FFFFF0606FFFFD9D9D9FFD9D9D9FFD9D9D9FF0C560CFF0F68
      0FFF137B13FF158C15FF1A9E1AFF20B020FF25C125FF2BCF2BFF33DB33FF34DF
      34FF33DE33FF29D529FF22C822FFD9D9D9FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000009C9C9CFF9C9C9CFF2A2A2AFF3232
      32FF3B3B3BFF454545FF525252FF606060FF6A6A6AFF797979FF898989FF8D8D
      8DFF848484FF686868FF565656FF9C9C9CFFDDDDDDFFDDDDDDFF00008FFF0000
      ABFF0101C8FF0404E3FF0E0EF3FF1C1CFEFF2D2DFFFF4141FFFF5959FFFF5D5D
      FFFF5151FFFF2727FFFF0F0FFFFFDDDDDDFFDDDDDDFFDDDDDDFF0D600DFF1174
      11FF148814FF1A9D1AFF22B722FF2DD42DFF37E737FF42F442FF50FB50FF53FD
      53FF4EFA4EFF39F139FF2ADE2AFFDDDDDDFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000A7A7A7FFA7A7A7FF2D2D2DFF3636
      36FF414141FF4E4E4EFF626262FF797979FF8B8B8BFF9F9F9FFFB1B1B1FFB1B1
      B1FFA1A1A1FF747474FF5A5A5AFFA7A7A7FFE1E1E1FFE1E1E1FF00009AFF0000
      B9FF0202D7FF0B0BF0FF2222FBFF4242FFFF5C5CFFFF7777FFFF9191FFFF9191
      FFFF7A7AFFFF3939FFFF1515FFFFE1E1E1FFE1E1E1FFE1E1E1FF0F680FFF137D
      13FF179317FF1FAF1FFF2FD02FFF41EE41FF50F650FF5FFC5FFF6EFF6EFF6FFF
      6FFF64FE64FF44FA44FF2FE82FFFE1E1E1FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000B2B2B2FFB2B2B2FF2F2F2FFF3A3A
      3AFF454545FF545454FF6C6C6CFF898989FF9E9E9EFFB1B1B1FFC0C0C0FFBDBD
      BDFFA8A8A8FF767676FF5A5A5AFFB2B2B2FFE5E5E5FFE5E5E5FF0000A2FF0000
      C4FF0303E3FF0F0FF8FF2E2EFFFF5858FFFF7777FFFF9292FFFFA8A8FFFFA1A1
      FFFF8484FFFF3C3CFFFF1515FCFFE5E5E5FFE5E5E5FFE5E5E5FF106E10FF1385
      13FF199D19FF23BD23FF37E037FF4EFF4EFF60FF60FF6FFF6FFF7BFF7BFF79FF
      79FF6BFF6BFF47FF47FF30EB30FFE5E5E5FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000BDBDBDFFBDBDBDFF313131FF3C3C
      3CFF474747FF525252FF696969FF838383FF949494FF9E9E9EFFA1A1A1FF9797
      97FF858585FF636363FF505050FFBDBDBDFFE8E8E8FFE8E8E8FF0000A6FF0000
      CCFF0202EAFF0D0DFAFF2929FFFF5050FFFF6868FFFF7676FFFF7979FFFF6B6B
      FFFF5252FFFF2020FFFF0B0BF5FFE8E8E8FFE8E8E8FFE8E8E8FF117111FF148A
      14FF19A319FF23C223FF35E235FF4CFF4CFF5AFF5AFF63FF63FF66FF66FF5FFF
      5FFF53FF53FF3AFD3AFF2AE22AFFE8E8E8FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000C9C9C9FFC9C9C9FF2D2D2DFF3B3B
      3BFF474747FF4F4F4FFF5C5C5CFF6C6C6CFF757575FF797979FF777777FF7070
      70FF656565FF555555FF414141FFC9C9C9FFECECECFFECECECFF00009AFF0000
      C9FF0101EDFF0707FAFF1717FFFF2E2EFFFF3B3BFFFF4040FFFF3D3DFFFF3333
      FFFF2424FFFF0E0EFFFF0404D3FFECECECFFECECECFFECECECFF106910FF1488
      14FF19A519FF21BD21FF2CD82CFF3BF33BFF44F844FF49FC49FF49FD49FF44FE
      44FF3CFD3CFF30F730FF21BF21FFECECECFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000D1D1D1FFD1D1D1FF242424FF3636
      36FF444444FF4A4A4AFF4E4E4EFF525252FF555555FF545454FF505050FF4D4D
      4DFF494949FF464646FFD1D1D1FFD1D1D1FFEFEFEFFFEFEFEFFF030382FF0000
      B8FF0000E6FF0101F8FF0505FEFF0B0BFFFF0D0DFFFF0D0DFFFF0707FFFF0404
      FCFF0101F7FF0000EDFFEFEFEFFFEFEFEFFFEFEFEFFFEFEFEFFF105A10FF137D
      13FF189E18FF1DB41DFF22CC22FF28E228FF2DEE2DFF2EF52EFF2DF92DFF2BF6
      2BFF28EF28FF25DE25FFEFEFEFFFEFEFEFFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000D8D8D8B90606066CD8D8D8FFD8D8
      D8FFD8D8D8FFD8D8D8FFD8D8D8FFD8D8D8FFD8D8D8FFD8D8D8FFD8D8D8FFD8D8
      D8FFD8D8D8FFD8D8D8FFD8D8D8FFD8D8D8B9F1F1F1D178788D81F1F1F1FFF1F1
      F1FFF1F1F1FFF1F1F1FFF1F1F1FFF1F1F1FFF1F1F1FFF1F1F1FFF1F1F1FFF1F1
      F1FFF1F1F1FFF1F1F1FFF1F1F1FFF1F1F1D1F1F1F1D17A867A78F1F1F1FFF1F1
      F1FFF1F1F1FFF1F1F1FFF1F1F1FFF1F1F1FFF1F1F1FFF1F1F1FFF1F1F1FFF1F1
      F1FFF1F1F1FFF1F1F1FFF1F1F1FFF1F1F1D10000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000DEDEDEBFDEDEDEFFDEDE
      DEFFDEDEDEFFDEDEDEFFDEDEDEFFDEDEDEFFDEDEDEFFDEDEDEFFDEDEDEFFDEDE
      DEFFDEDEDEFFDEDEDEFFDEDEDEFFDEDEDEBF00000000F3F3F3D3F3F3F3FFF3F3
      F3FFF3F3F3FFF3F3F3FFF3F3F3FFF3F3F3FFF3F3F3FFF3F3F3FFF3F3F3FFF3F3
      F3FFF3F3F3FFF3F3F3FFF3F3F3FFF3F3F3D300000000F3F3F3D3F3F3F3FFF3F3
      F3FFF3F3F3FFF3F3F3FFF3F3F3FFF3F3F3FFF3F3F3FFF3F3F3FFF3F3F3FFF3F3
      F3FFF3F3F3FFF3F3F3FFF3F3F3FFF3F3F3D30000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000040000000100000000100010000000000800000000000000000000000
      000000000000000000000000FFFFFF0000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000008000800080000000}
  end
end