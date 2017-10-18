#include "stdafx.h"
#include "TextManager.h"


TextManager::TextManager()
{
}


TextManager::~TextManager()
{
}

void TextManager::WriteText(std::string str, std::string key, float xDest, float yDest, D3DCOLOR color)
{
	FONT stFont;
	if (!FindFont(key, &stFont)) return;

	RECT rc = RectMake(xDest, yDest, xDest + (str.length() * stFont.fd.Width), yDest + stFont.fd.Height);
	if (stFont.font)
	{
		stFont.font->DrawTextA(
			NULL,
			str.c_str(),
			str.length(),
			&rc,
			DT_LEFT | DT_TOP | DT_NOCLIP,
			color);
	}

}

void TextManager::AddFont(LPCWSTR fontName, std::string key, int fontSize)
{
	FONT stFont;
	if (FindFont(key, &stFont)) return; // �̹� ��ϵ� ��� ����

										//LPD3DXFONT font;
										//D3DXFONT_DESC fd; //��Ʈ����ü

	ZeroMemory(&stFont.fd, sizeof(D3DXFONT_DESC));

	stFont.fd.Height = fontSize * 2; // ����
	stFont.fd.Width = fontSize;   // ����
	stFont.fd.Weight = FW_BOLD; // ����
	stFont.fd.Italic = false; // ���ڸ�
	stFont.fd.CharSet = DEFAULT_CHARSET;
	stFont.fd.OutputPrecision = OUT_DEFAULT_PRECIS;
	stFont.fd.PitchAndFamily = FF_DONTCARE;
	wcscpy_s(stFont.fd.FaceName, fontName); // �۾�ü

	D3DXCreateFontIndirect(g_pD3DDevice, &stFont.fd, &stFont.font);
	m_mapFont[key] = stFont;
}

bool TextManager::FindFont(std::string key, FONT * font)
{
	if (m_mapFont.find(key) != m_mapFont.end())
	{
		*font = m_mapFont.find(key)->second;
		return true;
	}

	return false;

}
