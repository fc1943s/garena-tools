object FormMain: TFormMain
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  Caption = 'Hot Garena Tools 3.0'
  ClientHeight = 429
  ClientWidth = 597
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Button1: TButton
    Left = 25
    Top = 62
    Width = 75
    Height = 25
    Caption = 'enviar'
    TabOrder = 0
    OnClick = Button1Click
  end
  object Edit1: TEdit
    Left = 8
    Top = 8
    Width = 121
    Height = 21
    MaxLength = 15
    TabOrder = 1
  end
  object Edit2: TEdit
    Left = 8
    Top = 35
    Width = 121
    Height = 21
    MaxLength = 20
    TabOrder = 2
  end
  object Memo1: TMemo
    Left = 135
    Top = 8
    Width = 115
    Height = 221
    TabOrder = 3
  end
  object Memo2: TMemo
    Left = 256
    Top = 8
    Width = 183
    Height = 221
    TabOrder = 4
  end
  object Button2: TButton
    Left = 510
    Top = 15
    Width = 74
    Height = 25
    Caption = 'loop 16 min'
    TabOrder = 5
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 510
    Top = 76
    Width = 75
    Height = 25
    Caption = 'enviar'
    TabOrder = 6
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 25
    Top = 359
    Width = 75
    Height = 25
    Caption = 'Button4'
    TabOrder = 7
    OnClick = Button4Click
  end
  object Button5: TButton
    Left = 510
    Top = 107
    Width = 75
    Height = 25
    Caption = 'spam'
    TabOrder = 8
    OnClick = Button5Click
  end
  object Memo3: TMemo
    Left = 445
    Top = 8
    Width = 59
    Height = 221
    TabOrder = 9
  end
  object Memo4: TMemo
    Left = 135
    Top = 235
    Width = 446
    Height = 182
    ScrollBars = ssVertical
    TabOrder = 10
  end
  object Button6: TButton
    Left = 25
    Top = 390
    Width = 75
    Height = 25
    Caption = 'Button6'
    TabOrder = 11
    OnClick = Button6Click
  end
  object CheckBox1: TCheckBox
    Left = 510
    Top = 168
    Width = 72
    Height = 17
    Caption = 'hide pw'
    TabOrder = 12
    OnClick = CheckBox1Click
  end
  object Button7: TButton
    Left = 510
    Top = 137
    Width = 75
    Height = 25
    Caption = 'stop spam'
    Enabled = False
    TabOrder = 13
    OnClick = Button7Click
  end
  object Button8: TButton
    Left = 510
    Top = 46
    Width = 74
    Height = 25
    Caption = 'stop loop'
    TabOrder = 14
    OnClick = Button8Click
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 960000
    OnTimer = Timer1Timer
    Left = 503
    Top = 288
  end
  object ClientSocket1: TClientSocket
    Active = False
    ClientType = ctNonBlocking
    Host = '67.228.162.189'
    Port = 8687
    OnConnecting = ClientSocket1Connecting
    OnConnect = ClientSocket1Connect
    OnDisconnect = ClientSocket1Disconnect
    OnRead = ClientSocket1Read
    OnError = ClientSocket1Error
    Left = 508
    Top = 243
  end
end
