#pragma once

#include <cstdint>

// Created with ReClass.NET by KN4CK3R
#pragma pack(push, 1)

class INetChannel
{
public:
    char pad_0000[20];           //0x0000
    bool m_bProcessingMessages;  //0x0014
    bool m_bShouldDelete;        //0x0015
    char pad_0016[2];            //0x0016
    int32_t m_nOutSequenceNr;    //0x0018 last send outgoing sequence number
    int32_t m_nInSequenceNr;     //0x001C last received incoming sequnec number
    int32_t m_nOutSequenceNrAck; //0x0020 last received acknowledge outgoing sequnce number
    int32_t m_nOutReliableState; //0x0024 state of outgoing reliable data (0/1) flip flop used for loss detection
    int32_t m_nInReliableState;  //0x0028 state of incoming reliable data
    int32_t m_nChokedPackets;    //0x002C number of choked packets
    char pad_0030[1044];         //0x0030
}; //Size: 0x0444

class CClockDriftMgr
{
public:
    float m_ClockOffsets[16];   //0x0000
    uint32_t m_iCurClockOffset; //0x0044
    uint32_t m_nServerTick;     //0x0048
    uint32_t m_nClientTick;     //0x004C
}; //Size: 0x0050

class CEventInfo
{
public:
	uint16_t classID; //0x0000 0 implies not in use
	char pad_0002[2]; //0x0002
	float fire_delay; //0x0004 If non-zero, the delay time when the event should be fired ( fixed up on the client )
	char pad_0008[4]; //0x0008
	ClientClass *pClientClass; //0x000C
	void *pData; //0x0010 Raw event data
	char pad_0014[48]; //0x0014
}; //Size: 0x0044

// This struct is most likely wrong
// Only fields that I know to be valid are:
// - m_NetChannel
// - m_nCurrentSequence
// - m_nDeltaTick
// - m_nMaxClients
// - viewangles
class CClientState
{
public:
	void ForceFullUpdate()
	{
		iDeltaTick = -1;
	}
	std::byte        pad0[0x9C];                //0x0000
	INetChannel* pNetChannel;            //0x009C
	int                iChallengeNr;            //0x00A0
	std::byte        pad1[0x64];                //0x00A4
	int                iSignonState;            //0x0108
	std::byte        pad2[0x8];                //0x010C
	float            flNextCmdTime;            //0x0114
	int                iServerCount;            //0x0118
	int                iCurrentSequence;        //0x011C
	char _0x0120[4];
	__int32 m_iClockDriftMgr; //0x0124 
	char _0x0128[68];
	__int32 m_iServerTick; //0x016C 
	__int32 m_iClientTick; //0x0170 
	int                iDeltaTick;                //0x0174
	bool            bPaused;                //0x0178
	std::byte        pad4[0x7];                //0x0179
	int                iViewEntity;            //0x0180
	int                iPlayerSlot;            //0x0184
	char            szLevelName[260];        //0x0188
	char            szLevelNameShort[80];    //0x028C
	char            szGroupName[80];        //0x02DC
	std::byte        pad5[0x5C];                //0x032C
	int                iMaxClients;            //0x0388lt
	std::byte        pad6[0x4984];            //0x038C
	float            flLastServerTickTime;    //0x4D10
	bool            bInSimulation;            //0x4D14
	std::byte        pad7[0xB];                //0x4D15
	int                iOldTickcount;            //0x4D18
	float            flTickRemainder;        //0x4D1C
	float            flFrameTime;            //0x4D20
	int                nLastOutgoingCommand;    //0x4D38
	int                iChokedCommands;        //0x4D30
	int                nLastCommandAck;        //0x4D2C
	int                iCommandAck;            //0x4D30
	int                iSoundSequence;            //0x4D34
	std::byte        pad8[0x50];                //0x4D38
	Vector            angViewPoint;            //0x4D88
	std::byte        pad9[0xD0];                //0x4D9A
};
#pragma pack(pop)

