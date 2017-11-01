#include "stdafx.h"
#include "cImpact.h"


cImpact::cImpact()
	: m_isUse(false)
{
}

cImpact::~cImpact()
{
	SAFE_RELEASE(VB);
}

void cImpact::Setup()
{
	m_vecParticleVertex.resize(1000);
	for (int i = 0; i < m_vecParticleVertex.size(); ++i)
	{
		float fRadius = rand() % 100 / 10.0f;

		// >>
		fRadius = 0.3f;
		// <<

		m_vecParticleVertex[i].p = D3DXVECTOR3(0, 0, fRadius);


		//����� �ٲܼ��ִ�.
		D3DXVECTOR3 vAngle = D3DXVECTOR3(
			D3DXToRadian(rand() % 3600 / 10.0f),
			D3DXToRadian(rand() % 3600 / 10.0f),
			D3DXToRadian(rand() % 3600 / 10.0f));

		D3DXMATRIX matRX, matRY, matRZ, matWorld;
		D3DXMatrixRotationX(&matRX, vAngle.x);
		D3DXMatrixRotationY(&matRY, vAngle.y);
		D3DXMatrixRotationZ(&matRZ, vAngle.z);
		matWorld = matRX * matRY * matRZ;

		D3DXVec3TransformCoord(
			&m_vecParticleVertex[i].p,
			&m_vecParticleVertex[i].p,
			&matWorld);

		m_vecParticleVertex[i].c = D3DCOLOR_ARGB(255, 180, 70, 20); // : �ؿ� ���������� ���� ����ؼ� �����Ұ�
																	//m_vecParticle[i]->m_pVertex = &m_vecParticleVertex[i];
	}

	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALEENABLE, true);	/// >> : ����Ʈ Ȯ�� ���� 

	g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE, FtoDw(1.f));	/// >> : ����Ʈ ������ ���� 

																/// : �⺻ ������ ���� �Ÿ� �������� ���Ҹ� ���� , ����Ʈ �����ϸ� Factor�� ����
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_A, FtoDw(0.0f));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_B, FtoDw(0.0f));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_C, FtoDw(3.0f));	/// : vs 10.0f check 

	g_pD3DDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, true); /// : ����Ʈ�� �ؽ��ĸ� ���� �� �ְ� ����
	g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE_MIN, FtoDw(0.0f));	/// : ����Ʈ �ּ� ũ��
	g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE_MAX, FtoDw(3.0f));	/// : ����Ʈ �ִ� ũ�� vs 10.0f check 

																	// �ؽ��� ���� �ɼ� ����
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	// ���ĺ��� ��� ����.
	g_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
}

void cImpact::Update()
{
	if (m_isUse)
	{
		for (int i = 0; i < m_vecParticleVertex.size(); ++i)
		{
			if (i % 2)
				continue;
			m_vecParticleVertex[i].c = D3DCOLOR_ARGB(nAlpha, 107, 102, 255); /// : ���İ��� ����
		}
	}

	nAlpha -= nDelta;
	if (nAlpha < 0)
	{
		m_isUse = false;
	}
}

void cImpact::Render()
{
	if (m_isUse)
	{
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
		g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
		D3DXMatrixIdentity(&m_matWorld);
		m_matWorld._41 = m_itemPos.x;
		m_matWorld._42 = m_itemPos.y;
		m_matWorld._43 = m_itemPos.z;
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
		g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
		g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture("Objects/gravityball/Envstill.bmp"));
		//g_pD3DDevice->DrawPrimitive(D3DPT_POINTLIST, 0, 100);
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_POINTLIST,
			m_vecParticleVertex.size(),
			&m_vecParticleVertex[0],
			sizeof(ST_PC_VERTEX));

		g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
		g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	}
}
