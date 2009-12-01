/*void CodeCave()
{
	HANDLE hnd;
	Stew::_BeginMemoryWork(Stew::_GetPID("Garena.exe"), hnd);

	CurrentCodeCaveHandle = hnd;
	//storing address - current place - 5

	const int
		PPopadOpcode  = 	0x61,
		PPushOpcode    = 	0x68,
		PPushEaxOpcode = 	0x50,
		PPushEbxOpcode = 	0x53,
		PPushEbpOpcode = 	0x55,
		PPopEaxOpcode = 	0x58,

   //dll

		PlstrcpyW 		  = 0x0059A374,
		PlstrcmpW 		  = 0x0059A3A0,

   //packet
		PJmpGate2 		  = 0x71a7615a,
		PRetGate2 		  = 0x71a7615f;

	int HeapSpace1 = (int)VirtualAllocEx(hnd, NULL, 255, 4096, 4),
		aux, aux2 = 0,
		PDllCmp = HeapSpace1 + 0x6f,
		PlstrcatW2 = HeapSpace1 + 0x57,
		HeapSpace2 = HeapSpace1 + 0x200,
		HeapSpace3 = HeapSpace1 + 0x300,
		PJmpGate3 = PJmpGate2 + 0x6c,
		PRetGate3 = PJmpGate3 + 5,
		PacketSize = 0x65,
		PPacketSize = HeapSpace3 - 0x20,
		PNamePacketSize = PPacketSize - 4,
		PNamePacketFilter = PNamePacketSize - 9,
		NamePacketFilter[] = { 0x45, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00 },
		NamePacketSize = 9,
		PNameHack = PNamePacketFilter - 0x10;

	WideString DllCmpName = "\\plugins\\ui\\FPSGame.dll";
	String PlstrcatW = "lstrcatW";
	String NameHack = "123456789ABCDEF";



//--------------------------------------------------------------------------------
	// jmpgate2
    aux2 = 0;

	aux = 0xE9;
	WriteProcessMemory(hnd, Pointer(PJmpGate2), &aux, 1, 0);
	aux = HeapSpace2 - PJmpGate2 - 5;
	WriteProcessMemory(hnd, Pointer(PJmpGate2 + 1), &aux, 4, 0);

	//MOV [HeapSpace2 - 3F],EAX
	aux = 0xa3;
	WriteProcessMemory(hnd, Pointer(HeapSpace2 + aux2), &aux, 1, 0);
	aux = HeapSpace2 - 0x3F;
	WriteProcessMemory(hnd, Pointer(HeapSpace2 + aux2 + 1), &aux, 4, 0);
	aux2 = aux2 + 5;

	//mov [HeapSpace2 - 3B], ECX
	int aux10[] = { 0x89, 0x0d };
	for (UINT i = 0; i < sizeof(aux10) / sizeof(aux10[0]); i++)
	{
		WriteProcessMemory(hnd, Pointer(HeapSpace2 + aux2), &aux10[i], 1, 0);
		aux2++;
	}
	aux = HeapSpace2 - 0x3B;
	WriteProcessMemory(hnd, Pointer(HeapSpace2 + aux2), &aux, 4, 0);
	aux2 = aux2 + 4;

	//mov [HeapSpace2 - 37], EDX
	int aux11[] = { 0x89, 0x15 };
	for (UINT i = 0; i < sizeof(aux11) / sizeof(aux11[0]); i++)
	{
		WriteProcessMemory(hnd, Pointer(HeapSpace2 + aux2), &aux11[i], 1, 0);
		aux2++;
	}
	aux = HeapSpace2 - 0x37;
	WriteProcessMemory(hnd, Pointer(HeapSpace2 + aux2), &aux, 4, 0);
	aux2 = aux2 + 4;

	//mov [HeapSpace2 - 33], EBX
	int aux12[] = { 0x89, 0x1d };
	for (UINT i = 0; i < sizeof(aux12) / sizeof(aux12[0]); i++)
	{
		WriteProcessMemory(hnd, Pointer(HeapSpace2 + aux2), &aux12[i], 1, 0);
		aux2++;
	}
	aux = HeapSpace2 - 0x33;
	WriteProcessMemory(hnd, Pointer(HeapSpace2 + aux2), &aux, 4, 0);
	aux2 = aux2 + 4;

	//pop eax / pop ecx / pop edx / pop ebx
	int aux9[] = { 0x58, 0x59, 0x5A, 0x5b };
	for (UINT i = 0; i < sizeof(aux9) / sizeof(aux9[0]); i++)
	{
		WriteProcessMemory(hnd, Pointer(HeapSpace2 + aux2), &aux9[i], 1, 0);
		aux2++;
	}

	//mov [HeapSpace2 - B], EDX
	for (UINT i = 0; i < sizeof(aux11) / sizeof(aux11[0]); i++)
	{
		WriteProcessMemory(hnd, Pointer(HeapSpace2 + aux2), &aux11[i], 1, 0);
		aux2++;
	}
	aux = HeapSpace2 - 0xb;
	WriteProcessMemory(hnd, Pointer(HeapSpace2 + aux2), &aux, 4, 0);
	aux2 = aux2 + 4;

	//mov [HeapSpace2 - 7], EBX
	for (UINT i = 0; i < sizeof(aux12) / sizeof(aux12[0]); i++)
	{
		WriteProcessMemory(hnd, Pointer(HeapSpace2 + aux2), &aux12[i], 1, 0);
		aux2++;
	}
	aux = HeapSpace2 - 0x7;
	WriteProcessMemory(hnd, Pointer(HeapSpace2 + aux2), &aux, 4, 0);
	aux2 = aux2 + 4;

	//push ebx / push edx / push ecx / push eax
	int aux13[] = { 0x53, 0x52, 0x51, 0x50 };
	for (UINT i = 0; i < sizeof(aux13) / sizeof(aux13[0]); i++)
	{
		WriteProcessMemory(hnd, Pointer(HeapSpace2 + aux2), &aux13[i], 1, 0);
		aux2++;
	}

	//mov ebx, [HeapSpace2 - 0x33]
	int aux14[] = { 0x8b, 0x1d };
	for (UINT i = 0; i < sizeof(aux14) / sizeof(aux14[0]); i++)
	{
		WriteProcessMemory(hnd, Pointer(HeapSpace2 + aux2), &aux14[i], 1, 0);
		aux2++;
	}
	aux = HeapSpace2 - 0x33;
	WriteProcessMemory(hnd, Pointer(HeapSpace2 + aux2), &aux, 4, 0);
	aux2 = aux2 + 4;

	//mov edx, [HeapSpace2 - 0x37]
	int aux15[] = { 0x8b, 0x15 };
	for (UINT i = 0; i < sizeof(aux15) / sizeof(aux15[0]); i++)
	{
		WriteProcessMemory(hnd, Pointer(HeapSpace2 + aux2), &aux15[i], 1, 0);
		aux2++;
	}
	aux = HeapSpace2 - 0x37;
	WriteProcessMemory(hnd, Pointer(HeapSpace2 + aux2), &aux, 4, 0);
	aux2 = aux2 + 4;

	//mov ecx, [HeapSpace2 - 0x3b]
	int aux16[] = { 0x8b, 0x0d };
	for (UINT i = 0; i < sizeof(aux16) / sizeof(aux16[0]); i++)
	{
		WriteProcessMemory(hnd, Pointer(HeapSpace2 + aux2), &aux16[i], 1, 0);
		aux2++;
	}
	aux = HeapSpace2 - 0x3b;
	WriteProcessMemory(hnd, Pointer(HeapSpace2 + aux2), &aux, 4, 0);
	aux2 = aux2 + 4;

	//MOV EAX, [HeapSpace2 - 3F]
	aux = 0xa1;
	WriteProcessMemory(hnd, Pointer(HeapSpace2 + aux2), &aux, 1, 0);
	aux = HeapSpace2 - 0x3F;
	WriteProcessMemory(hnd, Pointer(HeapSpace2 + aux2 + 1), &aux, 4, 0);
	aux2 = aux2 + 5;


	//mov edi, edi / push ebp / mov ebp, esp
	int aux8[] = { 0x8b, 0xff, 0x55, 0x8b, 0xec };
	for (UINT i = 0; i < sizeof(aux8) / sizeof(aux8[0]); i++)
	{
		WriteProcessMemory(hnd, Pointer(HeapSpace2 + aux2), &aux8[i], 1, 0);
		aux2++;
	}

	//jmp retgate2
	aux = 0xE9;
	WriteProcessMemory(hnd, Pointer(HeapSpace2 + aux2), &aux, 1, 0);
	aux = PRetGate2 - HeapSpace2 - aux2 - 5;
	WriteProcessMemory(hnd, Pointer(HeapSpace2 + aux2 + 1), &aux, 4, 0);
	aux2 = aux2 + 5;
//--------------------------------------------------------------------------------
	aux2 = -0xA;

	WriteProcessMemory(hnd, Pointer(PPacketSize), &PacketSize, 1, 0);
	WriteProcessMemory(hnd, Pointer(PNamePacketSize), &NamePacketSize, 1, 0);
	for (UINT i = 0; i < sizeof(NamePacketFilter) / sizeof(NamePacketFilter[0]); i++)
	{
		WriteProcessMemory(hnd, Pointer(PNamePacketFilter + i), &NamePacketFilter[i], 1, 0);
	}
	WriteProcessMemory(hnd, Pointer(PNameHack), NameHack.c_str(), NameHack.Length(), 0);

	//jmp jmpgate3
	aux = 0xE9;
	WriteProcessMemory(hnd, Pointer(PJmpGate3), &aux, 1, 0);
	aux = HeapSpace3 - PJmpGate3 - 5;
	WriteProcessMemory(hnd, Pointer(PJmpGate3 + 1), &aux, 4, 0);

	//CALL DWORD PTR DS:[EAX+54] / MOV ECX,ESI
	int aux17[] = { 0xff, 0x50, 0x54, 0x8b, 0xce };
	for (UINT i = 0; i < sizeof(aux17) / sizeof(aux17[0]); i++)
	{
		WriteProcessMemory(hnd, Pointer(HeapSpace3 + aux2), &aux17[i], 1, 0);
		aux2++;
	}

	//jmp retgate3
	aux = 0xE9;
	WriteProcessMemory(hnd, Pointer(HeapSpace3 + aux2), &aux, 1, 0);
	aux = PRetGate3 - HeapSpace3 - aux2 - 5;
	WriteProcessMemory(hnd, Pointer(HeapSpace3 + aux2 + 1), &aux, 4, 0);
	aux2 = aux2 + 5;

	//PUSH EAX
	WriteProcessMemory(hnd, Pointer(HeapSpace3 + aux2), &PPushEaxOpcode, 1, 0);
	aux2++;

	//MOV EAX, [PPacketSize]
	aux = 0xa1;
	WriteProcessMemory(hnd, Pointer(HeapSpace3 + aux2), &aux, 1, 0);
	WriteProcessMemory(hnd, Pointer(HeapSpace3 + aux2 + 1), &PPacketSize, 4, 0);
	aux2 = aux2 + 5;

	//CMP [HeapSpace2 - 0x7],EAX
	int aux18[] = { 0x39, 0x05 };
	for (UINT i = 0; i < sizeof(aux18) / sizeof(aux18[0]); i++)
	{
		WriteProcessMemory(hnd, Pointer(HeapSpace3 + aux2), &aux18[i], 1, 0);
		aux2++;
	}
	aux = HeapSpace2 - 0x7;
	WriteProcessMemory(hnd, Pointer(HeapSpace3 + aux2), &aux, 4, 0);
	aux2 = aux2 + 4;

	//POP EAX
	WriteProcessMemory(hnd, Pointer(HeapSpace3 + aux2), &PPopEaxOpcode, 1, 0);
	aux2++;

	//JNZ HeapSpace3 - 0xA
	int aux20[] = { 0x75, 0xe7 };
	for (UINT i = 0; i < sizeof(aux20) / sizeof(aux20[0]); i++)
	{
		WriteProcessMemory(hnd, Pointer(HeapSpace3 + aux2), &aux20[i], 1, 0);
		aux2++;
	}

	//CALL DWORD PTR DS:[EAX+54]
	int aux21[] = { 0xff, 0x50, 0x54 };
	for (UINT i = 0; i < sizeof(aux21) / sizeof(aux21[0]); i++)
	{
		WriteProcessMemory(hnd, Pointer(HeapSpace3 + aux2), &aux21[i], 1, 0);
		aux2++;
	}

	//PUSHAD
	aux = 0x60;
	WriteProcessMemory(hnd, Pointer(HeapSpace3 + aux2), &aux, 1, 0);
	aux2++;

	//mov eax, 0
	aux = 0xb8;
	WriteProcessMemory(hnd, Pointer(HeapSpace3 + aux2), &aux, 5, 0);
	aux2 = aux2 + 5;

	//MOV CL, [EAX + PNamePacketFilter]
	int aux24[] = { 0x8a, 0x88 };
	for (UINT i = 0; i < sizeof(aux24) / sizeof(aux24[0]); i++)
	{
		WriteProcessMemory(hnd, Pointer(HeapSpace3 + aux2), &aux24[i], 1, 0);
		aux2++;
	}
	WriteProcessMemory(hnd, Pointer(HeapSpace3 + aux2), &PNamePacketFilter, 4, 0);
	aux2 = aux2 + 4;

	//MOV EBX, [HeapSpace2 - 0xB]
	int aux25[] = { 0x8b, 0x1d };
	for (UINT i = 0; i < sizeof(aux25) / sizeof(aux25[0]); i++)
	{
		WriteProcessMemory(hnd, Pointer(HeapSpace3 + aux2), &aux25[i], 1, 0);
		aux2++;
	}
	aux = HeapSpace2 - 0xB;
	WriteProcessMemory(hnd, Pointer(HeapSpace3 + aux2), &aux, 4, 0);
	aux2 = aux2 + 4;

	//CMP CL, [EAX+EBX] / JNZ \/0x1c
	int aux26[] = { 0x3a, 0x0c, 0x18, 0x75, 0x1c };
	for (UINT i = 0; i < sizeof(aux26) / sizeof(aux26[0]); i++)
	{
		WriteProcessMemory(hnd, Pointer(HeapSpace3 + aux2), &aux26[i], 1, 0);
		aux2++;
	}

	//inc eax
	aux = 0x40;
	WriteProcessMemory(hnd, Pointer(HeapSpace3 + aux2), &aux, 1, 0);
	aux2++;

	//CMP [PNamePacketSize],EAX
	int aux22[] = { 0x39, 0x05 };
	for (UINT i = 0; i < sizeof(aux22) / sizeof(aux22[0]); i++)
	{
		WriteProcessMemory(hnd, Pointer(HeapSpace3 + aux2), &aux22[i], 1, 0);
		aux2++;
	}
	WriteProcessMemory(hnd, Pointer(HeapSpace3 + aux2), &PNamePacketSize, 4, 0);
	aux2 = aux2 + 4;

	//JNZ ^top loop
	int aux23[] = { 0xf, 0x85 };
	for (UINT i = 0; i < sizeof(aux23) / sizeof(aux23[0]); i++)
	{
		WriteProcessMemory(hnd, Pointer(HeapSpace3 + aux2), &aux23[i], 1, 0);
		aux2++;
	}
	aux = (HeapSpace3 + 0x19) - HeapSpace3 - aux2 - 5;
	WriteProcessMemory(hnd, Pointer(HeapSpace3 + aux2), &aux, 4, 0);
	aux2 = aux2 + 4;

	//add ebx, 0d
	int aux27[] = { 0x83, 0xc3, 0xd };
	for (UINT i = 0; i < sizeof(aux27) / sizeof(aux27[0]); i++)
	{
		WriteProcessMemory(hnd, Pointer(HeapSpace3 + aux2), &aux27[i], 1, 0);
		aux2++;
	}

	//PUSH PNameHack
	WriteProcessMemory(hnd, Pointer(HeapSpace3 + aux2), &PPushOpcode, 1, 0);
	WriteProcessMemory(hnd, Pointer(HeapSpace3 + aux2 + 1), &PNameHack, 4, 0);
	aux2 = aux2 + 5;

	//PUSH EBX
	WriteProcessMemory(hnd, Pointer(HeapSpace3 + aux2), &PPushEbxOpcode, 1, 0);
	aux2++;

	// call lstrcpyW            
	CCWriteLine(HeapSpace3 + aux2, 0x15FF, 2, aux2, true);
	WriteProcessMemory(hnd, Pointer(HeapSpace3 + aux2), &PlstrcpyW, 4, 0);
	aux2 = aux2 + 4;

	//popad
	WriteProcessMemory(hnd, Pointer(HeapSpace3 + aux2), &PPopadOpcode, 1, 0);
	aux2++;

	//JMP HeapSpace3 - 7
	aux = 0xE9;
	WriteProcessMemory(hnd, Pointer(HeapSpace3 + aux2), &aux, 1, 0);
	aux = (HeapSpace3 - 7) - HeapSpace3 - aux2 - 5;
	WriteProcessMemory(hnd, Pointer(HeapSpace3 + aux2 + 1), &aux, 4, 0);
	aux2 = aux2 + 5;
	
//--------------------------------------------------------------------------------

	CloseHandle(hnd);
}*/