#include "stdafx.h"
#include "TimeManager.h"
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

TimeManager::TimeManager()
{
}

TimeManager::~TimeManager()
{
}

void TimeManager::Setup()
{
	//m_fWorldTime = 0;
	//m_fElapsedTime = 0;

	
	//���� Ÿ�̸Ӱ� �����Ǵ� CPU�� �ʴ� �и����� ���� ��(0.001��)
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&m_PeriodFrequency))
	{
		
		m_isHardware = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&m_LastTime);

		//�ʴ� �ð� ��� ����
		m_TimeScale = 1.0f / m_PeriodFrequency;
	}
	else
	{
		m_isHardware = false;

		//�и������� ������ ������ ����
		m_LastTime = timeGetTime();
		m_TimeScale = 0.001f;
	}

	m_FrameRate = 0;
	m_FPSFrameCount = 0;
	m_FPSTimeElapsed = 0;
	m_WorldTime = 0.0f;
}

void TimeManager::Update(float lockFPS/* = 0.0f*/)
{
	//DWORD dwCurrentTime = GetTickCount();
	//m_fElapsedTime = (dwCurrentTime - m_dwLastUpdateTIme) / 1000.0f;
	//m_dwLastUpdateTIme = dwCurrentTime;
	//m_fWorldTime += m_fElapsedTime;

	//����Ÿ�̸�����?
	if (m_isHardware)
	{
		//����ũ���� ������ �������� ��ġ�ϸ�
		QueryPerformanceCounter((LARGE_INTEGER*)&m_CurTime);
	}
	else
	{
		//�������� ������ ������ �ð��� �����.
		m_CurTime = timeGetTime();
	}

	//����ð��� �������ð��� ������� �����´�.
	//������ ���� 0.001�� ������
	m_TimeElapsed = (m_CurTime - m_LastTime) * m_TimeScale;

	//���� ���ָ� ���� ������ ��Ű���̶�� �θ�
	if (lockFPS > 0.0f)
	{
		//lockFPS == ������ �������� ���� ������
		while (m_TimeElapsed < (1.0f / lockFPS))
		{
			if (m_isHardware) QueryPerformanceCounter((LARGE_INTEGER*)&m_CurTime);
			else m_CurTime = timeGetTime();

			m_TimeElapsed = (m_CurTime - m_LastTime) * m_TimeScale;
		}
	}

	//�� Ÿ���� ������ ��
	m_LastTime = m_CurTime;
	m_FPSFrameCount++;
	m_FPSTimeElapsed += m_TimeElapsed;
	m_WorldTime += m_TimeElapsed;

	//1�ʰ� ������ �������ʱ�ȭ�� ���ش�.
	if (m_FPSTimeElapsed > 1.0f)
	{
		m_FrameRate = m_FPSFrameCount;
		m_FPSFrameCount = 0;
		m_FPSTimeElapsed = 0.0f;
	}
}

void TimeManager::Render()
{
	std::string FrameRate = "FrameRate   : " + std::to_string(m_FrameRate);
	std::string ElapsedTime = "ElapsedTime : " + std::to_string(m_TimeElapsed);
	std::string WorldTime = "WorldTime   : " + std::to_string(m_WorldTime);
	g_pTextManager->WriteText(FrameRate, "����ü_7", 1, 0, C_WHITE);
	g_pTextManager->WriteText(ElapsedTime, "����ü_7", 1, 12, C_WHITE);
	g_pTextManager->WriteText(WorldTime, "����ü_7", 1, 24, C_WHITE);
}

//float TimeManager::GetLastUpdateTime()
//{
//	return m_dwLastUpdateTIme / 1000.0f;
//}

unsigned long TimeManager::GetFrameRate(char * str)
{
	if (str != NULL)
	{
		
		//wsprintf(str, "FPS : %d", m_FrameRate);
	}

	return m_FrameRate;
}
