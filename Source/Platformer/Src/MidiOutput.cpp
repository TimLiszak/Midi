#include "StdAfx.h"
#include "MidiOutput.h"
#include "Render2d.h"
#include "Note.h"

#include "portmidi.h"
#include "porttime.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "assert.h"

#define INPUT_BUFFER_SIZE 100
#define OUTPUT_BUFFER_SIZE 0
#define DRIVER_INFO NULL
#define TIME_PROC ((int32_t (*)(void *)) Pt_Time)
#define TIME_INFO NULL

CMidiOutput::CMidiOutput()
{
	State = EState_Initialize;
	midi = 0;
}

void CMidiOutput::Update(const FLOAT DeltaTime)
{
	switch (State)
	{
		case EState_Initialize:
		{
			int default_out = -1;
			for (int i = 0; i < Pm_CountDevices(); i++) 
			{
				const PmDeviceInfo *info = Pm_GetDeviceInfo(i);
				string Name = info->name;
				if (info->output && Name.find("iConnect") != std::string::npos)
				{
					default_out = i;
				}
			}

			if (default_out >= 0)
			{
				Pm_OpenOutput(&midi,
					default_out,
					DRIVER_INFO,
					OUTPUT_BUFFER_SIZE,
					NULL,
					NULL,
					0);
				State = EState_Write;
			}
		}
		break;

		case EState_Write:
		{
		}
		break;
	}
}

void CMidiOutput::Render()
{
}

void CMidiOutput::HandleMidiMessage(int status, int data1, int data2)
{
	if (!midi)
		return;

	if (status == 0xf0)
		return;

	switch (status)
	{
		case 0x90:
		case 0x91:
		case 0x92:
		case 0x93:
		case 0x94:
		case 0x95:
		{
			status = 0x90;
		}
		break;
	};

	Pm_WriteShort(midi, 0, Pm_Message(status, data1, data2));
}

void CMidiOutput::ClearAll()
{
	for (int i = 0; i < 128; i++)
	{
		Pm_WriteShort(midi, 0, Pm_Message(0x80, i, 0));
	}
}
