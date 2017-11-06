#pragma once

#define g_pTimeManager TimeManager::GetInstance()

class TimeManager
{
	SINGLETONE(TimeManager);

private:
	//DWORD m_dwLastUpdateTIme;
	//float m_fElapsedTime;
	//float m_fWorldTime;

	bool m_isHardware; //���� Ÿ�̸� ������� ����
	float m_TimeScale; //�ð� �����
	float m_TimeElapsed; //������ �ð��� ����ð� ������ �����
	__int64 m_CurTime; //����ð�
	__int64 m_LastTime; //�������ð�
	__int64 m_PeriodFrequency; //������

	unsigned long m_FrameRate;
	unsigned long m_FPSFrameCount;
	float m_FPSTimeElapsed;
	float m_WorldTime;

	bool m_isDisplay;

public:
	
	void Setup();
	void Update(float lockFPS = 0.0f);
	void Render();

	inline float GetElapsedTime() {return m_TimeElapsed;}
	//float GetLastUpdateTime();
	unsigned long GetFrameRate(char* str = NULL);
	inline float GetWorldTime() { return m_WorldTime; }
};

