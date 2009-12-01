#include "UFormMain.h"
const UnicodeString
	Translate[][2] =
	{
		"Atualiza��es em ", 				  "Updates in ",                     //0
		"Selecione o Garena",			 	"Select Garena",                   //1
		"Executar Garena",					"Execute Garena",                  //2
		"Configura��es", 					  "Settings",                        //3
		"Caminho do Garena.exe:", 			"Path of Garena.exe:",             //4

		"Executar Garena com Name Spoofer",	"Execute Garena with Name Spoofer",//5
		"Hacks ativados automaticamente",	"Hacks enabled automatically",     //6
		"Digite algo em \"Name Spoofer\".",	"Field \"Name Spoofer\" empty.",   //7
		"Clique aqui para visualizar os cr�ditos",	"Click here to view the credits", //8

		"Ativar ajuda",				 		"Enable help",                     //9
		"Feito para Garena 3.0.0.1593",		"Made to Garena 3.0.0.1593", 	   //10
		"Erro",								"Error",                           //11
		"Vers�o do Garena inv�lida.",		  "Invalid Garena version.",         //12
		"",		  			"",                    //13

		"Experiencia",		  				"Experience",                      //14
		"Ping em N�meros",		  			 "Ping in Numbers",                 //15
		"Flood no Chat",		  			"Flood on Chat",                   //16
		"Rastrear Localiza��o",		  	  "Trace Location",                  //17
		"Alerta de Clan",		  			"Clan Alert",                      //18
		"Outras altera��es",		  		  "Other changes",	                 //19
		"Permitir Hacks",		  			"Bypass Hacks",                    //20
		"Sempre Jogando",		  			"Always Playing",                  //21
		//22
		"Agradecimentos:\r\nDarkSupremo,\r\nMembros do SecureGamers,\r\nMembros do d3scene,\r\nTodos os beta testers.",
		"Thanks to:\r\nDarkSupremo,\r\nSecureGamers members,\r\nd3scene members,\r\nAll beta testers.",

	},
	TranslateHint[][2] =
	{
		//0
		"Marque esta op��o se voc� deseja ajuda\r\nquando parar o mouse em cima de algo.",
		"Check this box if you want help\r\nwhen stop the mouse above something.",
		//1
		"Clique aqui para visitar o f�rum oficial.",
		"Click here to visit the official forum.",
		//2
		"Clique aqui para visitar a p�gina de downloads.",
		"Click here to visit the downloads page.",
		//3
		"Nick da sua conta no Garena.\r\n\r\nSe o nick � \"?\", voc� n�o est� logado.",
		"Your account nick on Garena.\r\n\r\nIf the nick is \"?\", you aren't logged.",
		//4
		"Selecione aqui o Garena desejado.\r\n\r\nO Garena s� ser� exibido aqui se ele\r\n foi executado pelo bot�o \"Executar Garena\".",
		"Select here the desired Garena.\r\n\r\nThe Garena will appear here only if he was\r\nexecuted by button \"Execute Garena\".",
		//5
		"Clique aqui para executar uma inst�ncia do Garena.\r\n\r\nExecutando o Garena por este bot�o, voc� poder�\r\nabrir mais de um Garena ao mesmo tempo.\r\n\r\nPara este bot�o funcionar corretamente, corrija\r\no \"Caminho do Garena.exe\" em Configura��es.\r\n\r\nO Garena s� ser� executado se ele estiver na\r\nvers�o citada na parte de baixo do programa.",
		"Click here to execute one instance of Garena.\r\n\r\nExecuting the Garena by this button, you could\r\nopen more than one Garena at the same time.\r\n\r\nFor this button works correctly, correct\r\nthe \"Path of Garena.exe\" in Settings.\r\n\r\nThe Garena will only be executed if he is in\r\nthe version said on the bottom of the program.",
		//6
		"Configure aqui o caminho do Garena.exe na\r\nvers�o citada na parte de baixo do programa.\r\n\r\nExemplo:\r\n\"C:\\Arquivos de Programas\\Garena\\Garena.exe\"",
		"Correct here the path of Garena.exe on\r\nversion said on the bottom of the program.\r\n\r\nExample:\r\n\"C:\\Program Files\\Garena\\Garena.exe\"",
		//7
		"Este programa s� ir� funcionar no Garena com a vers�o citada aqui.\r\n\r\nSe sua vers�o for menor que esta, visite www.garena.com para atualizar seu Garena.\r\n\r\nSe sua vers�o for maior que esta, aguarde alguns\r\ndias at� que a proxima vers�o do hack esteja terminada.\r\n\r\nPara saber a vers�o do seu Garena,\r\nvisite \"http://img399.imageshack.us/img399/4233/92330279pf4.png\"",
		"This program will works only on Garena with version said here.\r\n\r\nIf your version is lower than this, visit www.garena.com to update your Garena.\r\n\r\nIf your version is greater than this, wait a few days until the next version of hack is done.\r\n\r\nTo know the version of your Garena,\r\nvisit \"http://img399.imageshack.us/img399/4233/92330279pf4.png\"",
		//8
		"Com este hack voc� evoluir� sua conta mais rapido.\r\n\r\nVoc� n�o precisa estar em algum jogo, s�\r\nprecisa estar online no Garena, e DENTRO DE UMA SALA.\r\n\r\nVoc� ganhar� experi�ncia a cada 15 minutos.",
		"With this hack you will up your account more fast.\r\n\r\nYou don't need be in any game, need\r\nonly be online on Garena, and WITHIN A ROOM.\r\n\r\nYou will gain experience every 15 minutes.",
		//9
		"Exibe os pings por n�meros inv�s de barras.",
		"Show the pings by numbers instead of bars.",
		//10
		"Permite voc� floodar no chat.",
		"Allow you flood on chat.",
		//11
		"Permite rastrear a localiza��o e ver o IP de um usu�rio.",
		"Allow trace location and see IP of any user.",
		//12
		"Remove intervalo de espera entre Alertas de Clan.",
		"Remove interval wait between Clan Alerts.",
		//13
		" - Algumas mensagens e alertas retiradas (5 segundos de espera, sala cheia, level insuficiente, etc.)\r\n - Algumas propagandas removidas (sala).",//\r\n - Ping e level no Warcraft alterado de '<p:XX><l:XX>' para '(P:XX/L:XX)'.",
		" - Some messages and alerts removed (5 seconds of wait, full room, insufficient level, and more.)\r\n - Some advertisements removed (room).",//\r\n - Ping e level on Warcraft changed from '<p:XX><l:XX>' to '(P:XX/L:XX)'.",
		//14
		"Com este hack, o Garena n�o detecta\r\nALGUNS hacks, como map hack, etc.\r\n\r\n� recomendado testar com uma conta fake\r\nantes, para n�o correr risco de ban.\r\n\r\nN�O me responsabilizo por contas banidas.",
		"With this hack, the Garena not detects SOME hacks, like map hack, and more.\r\n\r\nIs recommended test with an account fake before, for no risk of ban.\r\n\r\nIf you take ban, it is their guilt.",
		//15
		"Marque esta op��o se voc� deseja jogar no Warcraft com o nick trocado.\r\n\r\nSe voc� desejar trocar o nick denovo, ter� que reabrir o Garena.\r\n\r\nOBS.: S� funciona no Warcraft.",
		"Check this box if you want play on Warcraft with changed nick.\r\n\r\nIf you want to change the nick again, need to reopen the Garena.\r\n\r\nPS.: Only works on Warcraft.",
		//16
		"Digite aqui o nick desejado para jogar no Warcraft.",
		"Write here the desired nick to play on Warcraft.",
		//17
		"Espada de \"Jogando\" sempre ativada.\r\n\r\nVoc� tambem poder� sair da sala com o Warcraft aberto.\r\n\r\nExtra:\r\nVoc� pode criar um jogo em alguma sala, depois 'trocar' de sala,\r\nque seu jogo ser� movido para a 'outra' sala, sem nenhum player cair.",
		"Sword of \"Playing\" always activated.\r\n\r\nYou also can leave the room with the Warcraft open.\r\n\r\nExtra:\r\nYou can create a game in some room, and 'change' room later,\r\nthat your game will be moved to 'other' room, and nobody in your game will fall.",
	};
