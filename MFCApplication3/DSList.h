// DSList.h : Definition of CDSList class
//

#if !defined(AFX_DSLIST_H__7517D749_96E3_11D2_BBF3_9EB4940D843C__INCLUDED_)
#define AFX_DSLIST_H__7517D749_96E3_11D2_BBF3_9EB4940D843C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DSBuffer.h"

class CDSList : virtual protected CObList
{
// Attribute
private:
	LPDIRECTSOUND	m_lpDS;			// DirectSound Object

// Construction / Destruction
public:
	CDSList();
	~CDSList();

// Methods
public:
	BOOL	Init();
	BOOL	StopAllBuffers();
	BOOL	AddNewBuffer(const char* FileName);
	BOOL	RemoveBuffer(int nBuffer);
	BOOL	PlayBuffer(int nBuffer, DWORD dwFlags);
	BOOL	StopBuffer(int nBuffer);
	LPDIRECTSOUND	GetDSObject() {return m_lpDS;}
};

#endif // !defined(AFX_DSLIST_H__7517D749_96E3_11D2_BBF3_9EB4940D843C__INCLUDED_)
