
// ImageJ2.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CImageJ2App:
// �� Ŭ������ ������ ���ؼ��� ImageJ2.cpp�� �����Ͻʽÿ�.
//

class CImageJ2App : public CWinApp
{
public:
	CImageJ2App();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CImageJ2App theApp;