#include <vcl.h>
#include <winsock.h>
#include "md5.cpp"
#pragma hdrstop
#include "UFormMain.h"
#pragma package(smart_init)
#pragma resource "*.dfm"

TFormMain* FormMain;

TStringList* BufList = new TStringList;

bool Deploy = false, EndBigExpThread = 0, SendRealBigExp = 0;

UnicodeString CurrentID, CurrentLogin, CurrentPassword;

UnicodeString RoomList[][2] =
{
	// lbd 2
	"C80009", "74.86.170.188",
	// lbd 3
	"C90009", "74.86.170.188",

	// orkut 2
	"F00001", "208.43.203.44",
	// orkut 3
	"350309", "74.86.170.188",

	// dota 16
	"960003", "67.228.162.186",
	// dota 17
	"950003", "67.228.162.186",
	// dota 18
	"940003", "67.228.162.186",
	// dota 19
	"930003", "67.228.162.186",
	// dota 20
	"8C0003", "67.228.162.186",
	// dota 21
	"2F0309", "74.86.170.188",
	// dota 22
	"2E0309", "74.86.170.188",
	// dota 23
	"320001", "208.43.203.44",
	// dota 24
	"310001", "208.43.203.44",
	// dota 25
	"300001", "208.43.203.44",
	// dota 26
	"2D0309", "74.86.170.188",
	// dota 27
	"2C0309", "74.86.170.188",
	// dota 28
	"9E0109", "74.86.170.188",
	// dota 29
	"9D0109", "74.86.170.188",
	// dota 30
	"3F000F", "218.93.127.135",
	// dota 31
	"B2FF03", "67.228.162.186",
	// dota 32
	"B1FF03", "67.228.162.186",
	// dota 33
	"B0FF03", "67.228.162.186",
	// dota 34
	"AFFF03", "67.228.162.186",
	// dota 35
	"AEFF03", "67.228.162.186",

	// rpg 2
	"9C0109", "74.86.170.188",
	// rpg 3
	"2B0309", "74.86.170.188",
	// rpg 4
	"9F0109", "74.86.170.188",
	// rpg 5
	"ADFF03", "67.228.162.186",
	// rpg 6
	"ACFF03", "67.228.162.186",
}, UserList[][3] =
{
	// rsrs
	"606092",
	"3900000027A61CF3789C4B4898C450545C54CC80041C5D181818D919194E2CCE8C01619018EB4BD697C86A181821D43B31064C009463046200BE680AEF000000000000000000000000000000", "77",
	// wtfrs
	"6DD08D", "3A000000BBB93694789CCBBDD0CB505E925654CC80008E2E0C0C8C5C8C0C27128ECF01619018EB4BD6974051842228F39825032600CA3102310036890C88000000000000000000000000000000", "78",
}, ServerList[] =
{
	// Server 1
	"208.43.54.194",
	// Server 2
	"67.228.162.187",
	// Server 3
	"74.53.215.10",
	// Server 4
	"67.228.162.189",
};

__fastcall TFormMain::TFormMain(TComponent* Owner) : TForm(Owner)
{
}

UnicodeString IntToHex2(int n)
{
	char x[] =
	{
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
	};

	UnicodeString c;

	if (n < 0)
	{
		int aux = 0xFF;
		for (int i = 0; i < 7; i++)
		{
			if (n > aux*-1 && n < aux)
			{
				n += aux + 1;
				break;
			}
			aux = aux * 0xF + aux + 0xF;
		}
	}
	while (true)
	{
		c += x[n % 16];
		if ((n = n / 16) == 0)
		{
			c = strrev(c.t_str());
			break;
		}
	}
	return c;
}

UnicodeString AsciiToHex(UnicodeString Ascii)
{
	UnicodeString Hex;
	for (int i = 1; i <= Ascii.Length(); i++)
	{
		Hex = Hex + IntToHex2((int)Ascii[i]);
	}
	return Hex;
}

void HexToAscii(UnicodeString Hex, char* Ascii)
{
	for (int i = 1; i < Hex.Length(); i++)
	{
		Ascii[i / 2] = char(strtol(AnsiString((UnicodeString)Hex[i] + (UnicodeString)Hex[i + 1]).c_str(), NULL, 16));
		i++;
	}
}

UnicodeString FillZeroHex(UnicodeString Str, int Count)
{
	UnicodeString aux = Str;
	if (Str.Length() / 2 != Count)
	{
		while (true)
		{
			aux += "00";
			if (aux.Length() / 2 == Count)
			{
				break;
			}
		}
	}
	return aux;
}

bool CreateSocket(int Port, UnicodeString IP, SOCKET& Sock, sockaddr_in& sin)
{
	WSAData wsdata;
	if (WSAStartup(MAKEWORD(2, 0), &wsdata) != 0)
	{
		goto Error;
	}

	Sock = socket(AF_INET, SOCK_STREAM, 0);
	if (Sock == INVALID_SOCKET)
	{
		goto Error;
	}

	sin.sin_port = htons(Port);
	sin.sin_addr.s_addr = inet_addr(IP.t_str());
	sin.sin_family = AF_INET;

	if (connect(Sock, (sockaddr*) & sin, sizeof(sin)) == SOCKET_ERROR)
	{
		goto Error;
	}
	return true;
Error:
	WSACleanup();
	return false;
}

void SendPacket(int Port, UnicodeString IP)
{
	SOCKET Sock;
	sockaddr_in sin;
	CreateSocket(Port, IP, Sock, sin);
	char buf[700];

	for (int j = 0; j < BufList->Count; j++)
	{
		HexToAscii(BufList->Strings[j], buf);
		send(Sock, buf, BufList->Strings[j].Length() / 2, 0);
		if (j < 2)
		{
			recv(Sock, buf, sizeof(buf), 0);
		}
		if (j < 2 && BufList->Strings[j].Length() / 2 == 74)
		{
			char buf2[700];
			HexToAscii("65000000450000000001000000", buf2);
			if (Pos((UnicodeString)buf2, (UnicodeString)buf) == 1)
			{
				int BeginGet = (UnicodeString("65000000450000000001000000").Length() / 2);
				CurrentID = "";
				for (int i = 0; i < 3; i++)
				{
					UnicodeString aew = buf[BeginGet + i];
					CurrentID += AsciiToHex(aew);
				}
				BufList->Add("0600000051" + CurrentID + "0001");
				BufList->Add("05000000DC" + CurrentID + "00");
				BufList->Add("0100000004");
				BufList->Add("0700000017454E04F12D49");
				BufList->Add("030000008B656E");

				BufList->Add("0600000051" + CurrentID + "0009");

				BufList->Add("0D00000067" + CurrentID + "00C8000000E9030000");

				BufList->Add("0900000052" + CurrentID + "00AA000100");

			}
		}
	}
	closesocket(Sock);
}

void AddExp(UnicodeString Login, UnicodeString Password)
{
	CurrentLogin = FillZeroHex(AsciiToHex(Login), 15);
	CurrentPassword = AsciiToHex(MD5(Password));

	BufList->Clear();

	BufList->Add("03000000D3454E");
	BufList->Add("460000001F00000000" + CurrentLogin + "0074F1540020000000" + CurrentPassword + "0001C860C77905E900");

	SendPacket(7456, ServerList[0]);
}

void __fastcall TFormMain::Button1Click(TObject* Sender)
{
	AddExp(Edit1->Text, Edit2->Text);
}

void BigExp(int Type)
{
	char buf[700];
	UnicodeString aux;
	SOCKET Sock;
	int tt = 1;
	if (Type > 100)
	{
		Type = 1;
	}
	for (int j = 0; j < tt; j++)
	{
		Type == 1 ? tt = j + 3 : FormMain->Memo4->Lines->Add(FormatDateTime("HH:NN:SS", Now()));
		for (UINT serverloop = 0; serverloop < sizeof(ServerList) / sizeof(ServerList[0]); serverloop++)
		{
			for (int i = 0; i < FormMain->Memo1->Lines->Count; i++)
			{
				if (FormMain->Memo1->Lines->Strings[i][1] == '@')
				{
					goto Ret;
				}
				if (SendRealBigExp)
				{
					SendRealBigExp = 0;
					BigExp(0);
				}
				if (EndBigExpThread)
				{
					EndBigExpThread = 0;
					EndThread(0);
					return;
				}
				CurrentID = FormMain->Memo3->Lines->Strings[i];
				CurrentLogin = FillZeroHex(AsciiToHex(FormMain->Memo1->Lines->Strings[i]), 15);
				CurrentPassword = AsciiToHex(MD5(FormMain->Memo2->Lines->Strings[i]));

				sockaddr_in sin;
				CreateSocket(7456, ServerList[serverloop], Sock, sin);

				aux = "03000000D3454E";
				HexToAscii(aux, buf);
				send(Sock, buf, aux.Length() / 2, 0);

				aux = "460000001F00000000" + CurrentLogin + "0074F1540020000000" + CurrentPassword + "0001C860C77905E900";
				HexToAscii(aux, buf);
				send(Sock, buf, aux.Length() / 2, 0);

				if (tt == 1 || j == tt - 1)
				{
					if (Type != 2)
					{
						recv(Sock, buf, 105, 0);
					}
					tt = 0;
				}

				aux = "0600000051" + CurrentID + "0001";
				HexToAscii(aux, buf);
				send(Sock, buf, aux.Length() / 2, 0);

				aux = "05000000DC" + CurrentID + "00";
				HexToAscii(aux, buf);
				send(Sock, buf, aux.Length() / 2, 0);

				aux = "0100000004";
				HexToAscii(aux, buf);
				send(Sock, buf, aux.Length() / 2, 0);
				// 04F12D
				aux = "0700000017454EF0919B49";
				HexToAscii(aux, buf);
				send(Sock, buf, aux.Length() / 2, 0);

				aux = "030000008B656E";
				HexToAscii(aux, buf);
				send(Sock, buf, aux.Length() / 2, 0);

				aux = "0D00000067" + CurrentID + "0064000000E9030000";
				HexToAscii(aux, buf);
				send(Sock, buf, aux.Length() / 2, 0);

				/* aux = "0900000052" + CurrentID + "00AA000100";
				HexToAscii(aux, buf);
				send(Sock, buf, aux.Length() / 2, 0); */
				closesocket(Sock);
				WSACleanup();
			Ret:
			}
		}
	}
}

void __fastcall TFormMain::Timer1Timer(TObject* Sender)
{
	SendRealBigExp = 1;
}

void __fastcall TFormMain::Button2Click(TObject* Sender)
{
	Timer1->Enabled = true;
}

void __fastcall TFormMain::Button3Click(TObject* Sender)
{
	BigExp(0);
}

void __fastcall TFormMain::Button4Click(TObject* Sender)
{
	char buf[700];
	UnicodeString txt[][3] =
	{
		"3101", "2401",
		"0A0051007500650072002000750070006100720020006100200063006F006E00740061002000730065006D0020006A006F006700610072003F002000540072006F0063006100720020006F0020006E00690063006B0020006E006F00200077006100720033003F00200046006C006F006F006400610072002000650020006D00740020006D006100690073003F000A0048006F007400200047006100720065006E006100200054006F006F006C007300200032002E0030000A0068007400740070003A002F002F0064006F0077006E006C006F006100640073002E0068006F0074006300680065006100740073002E006F00720067000A0049006E0066006F0072006D006100E700F5006500730020006E006F002000730069007400650021000A000A00", "3501",
		"2801", "0A005400650073007400610064006F002000650020006100700072006F007600610064006F002000700065006C006F002000640033007300630065006E0065003A000A0068007400740070003A002F002F007700770077002E00640033007300630065006E0065002E0063006F006D002F0066006F00720075006D002F00770061007200630072006100660074002D0033002D006800610063006B0073002F00320030003800360039002D0068006F0074002D0067006100720065006E0061002D0074006F006F006C0073002D0031002D0030002D0067006100720065006E0061002D0033002D0030002D0030002D0031003500390033002D0062006500730074002D006800610063006B002D0067006100720065006E0061002E00680074006D006C000A000A00", "3101", "2401", "0A0051007500650072002000750070006100720020006100200063006F006E00740061002000730065006D0020006A006F006700610072003F002000540072006F0063006100720020006F0020006E00690063006B0020006E006F00200077006100720033003F00200046006C006F006F006400610072002000650020006D00740020006D006100690073003F000A0048006F007400200047006100720065006E006100200054006F006F006C007300200032002E0030000A0068007400740070003A002F002F0064006F0077006E006C006F006100640073002E0068006F0074006300680065006100740073002E006F00720067000A0049006E0066006F0072006D006100E700F5006500730020006E006F00200073006900740065000A000A000A00",
		// "1700", "0A00", "74006500730074006500",
		// "1700", "0A00", "74006500720072006200",
		"4B00", "3E00", "68007400740070003A002F002F0064006F0077006E006C006F006100640073002E0068006F0074006300680065006100740073002E006F00720067002F00",
	};

	int UserNumber = 1;

Ret:

	for (UINT x = 0; x < sizeof(RoomList) / sizeof(RoomList[0]); x++)
	{
		SOCKET Sock2;
		sockaddr_in sin;
		if (CreateSocket(8687, RoomList[x][1], Sock2, sin))
		{
			BufList->Clear();
			BufList->Add(UserList[UserNumber][2] + "00000022" + RoomList[x][0] + "0000000000" + UserList[UserNumber][1] + AsciiToHex
				("a8f5f167f44f4964e6c998dee827110c") + "0000");
			// for(int rs = 0; rs < 4; rs++)
			for (UINT i = 0; i < sizeof(txt) / sizeof(txt[0]); i++)
			{
				BufList->Add(txt[i][0] + "000025" + RoomList[x][0] + "00" + UserList[UserNumber][0] + "00" + txt[i][1] + "0000" + txt[i][2]);
			}
			BufList->Add("0500000023" + UserList[UserNumber][0] + "00");

			for (int j = 0; j < BufList->Count; j++)
			{
				HexToAscii(BufList->Strings[j], buf);

				// int len = sizeof(sin);
				send(Sock2, buf, BufList->Strings[j].Length() / 2, 0);
				Sleep(1000);
				// listen(Sock2, SOMAXCONN);
				// SOCKET Sock3 = accept(Sock2, (sockaddr*)&sin, &len);
				// char b2[10000];
				// recv(Sock2, b2, sizeof(b2), 0);
			}
			closesocket(Sock2);
			WSACleanup();
		}
	}
	goto Ret;

}

void __fastcall TFormMain::Button5Click(TObject* Sender)
{
	Button5->Enabled = false;
	Button7->Enabled = true;
	UINT ThreadId;
	BeginThread(NULL, 0, (TThreadFunc) & BigExp, NULL, 0, ThreadId);
}

void __fastcall TFormMain::ClientSocket1Connect(TObject* Sender, TCustomWinSocket* Socket)
{
	Memo4->Lines->Add("Conectado");
}

void __fastcall TFormMain::ClientSocket1Connecting(TObject* Sender, TCustomWinSocket* Socket)
{
	Memo4->Lines->Add("Conectando");
}

void __fastcall TFormMain::ClientSocket1Disconnect(TObject* Sender, TCustomWinSocket* Socket)
{
	Memo4->Lines->Add("Desconectado");
}

void __fastcall TFormMain::ClientSocket1Error(TObject* Sender, TCustomWinSocket* Socket, TErrorEvent ErrorEvent, int& ErrorCode)
{
	Memo4->Lines->Add("Erro");
}

void __fastcall TFormMain::ClientSocket1Read(TObject* Sender, TCustomWinSocket* Socket)
{
	char buf[700];
	Socket->ReceiveBuf(buf, sizeof(buf));
	UnicodeString aux;
	for (UINT i = 0; i < sizeof(buf) - 1; i++)
	{
		UnicodeString aew = buf[i];
		UnicodeString aew2 = AsciiToHex(aew);
		aux += strtol(aew2.t_str(), NULL, 16) < 16 ? "0" + aew2 : aew2;
	}
	UnicodeString check = "4100000022";
	for (int i = 1; i <= check.Length(); i++)
	{
		if (check[i] != aux[i])
		{
			return;
		}
	}

	UnicodeString tst;
	for (int i = 19; i < 50; i++)
	{
		tst += aux[i];
	}
	char rss[30];
	HexToAscii(tst, rss);
	Memo4->Lines->Add(rss);

	int UserNumber = 1;
	int x = 1;

	UnicodeString arr = (UnicodeString)rss + " entrou na sala.";
	UnicodeString buf2;

	for (int i = 1; i <= arr.Length(); i++)
	{
		buf2 += AsciiToHex(arr[i]);
		buf2 += "00";
	}

	aux = FillZeroHex(IntToHex2((arr.Length() * 2) + 0xD), 2) + "000025" + RoomList[x][0] + "00" + UserList[UserNumber][0] + "00" + FillZeroHex
		(IntToHex2(arr.Length() * 2), 2) + "0000" + buf2;
	HexToAscii(aux, buf);
	ClientSocket1->Socket->SendBuf(buf, aux.Length() / 2);
}

void __fastcall TFormMain::Button6Click(TObject* Sender)
{
	UnicodeString txt[][3] =
	{
		"1700", "0A00", "74006500730074006500",
	};

	char buf[700];
	UnicodeString aux;
	int UserNumber = 1;
	int x = 1;

	ClientSocket1->Host = RoomList[x][1];
	ClientSocket1->Active = true;

	aux = UserList[UserNumber][2] + "00000022" + RoomList[x][0] + "0000000000" + UserList[UserNumber][1] + AsciiToHex("a8f5f167f44f4964e6c998dee827110c") + "0000";
	HexToAscii(aux, buf);
	ClientSocket1->Socket->SendBuf(buf, aux.Length() / 2);

	/* aux = txt[i][0] + "000025" + RoomList[x][0] + "00" + UserList[UserNumber][0] + "00" + txt[i][1] + "0000" + txt[i][2];
	HexToAscii(aux, buf);
	ClientSocket1->Socket->SendBuf(buf, aux.Length() / 2);
	/*
	aux = "0500000023" + UserList[UserNumber][0] + "00";
	HexToAscii(aux, buf);
	ClientSocket1->Socket->SendBuf(buf, aux.Length() / 2); */
}

void __fastcall TFormMain::CheckBox1Click(TObject* Sender)
{
	Memo2->Width = CheckBox1->Checked ? 0 : 183;
}

void __fastcall TFormMain::Button7Click(TObject* Sender)
{
	Button5->Enabled = true;
	Button7->Enabled = false;
	EndBigExpThread = 1;
}

void __fastcall TFormMain::Button8Click(TObject* Sender)
{
	Timer1->Enabled = false;
}
