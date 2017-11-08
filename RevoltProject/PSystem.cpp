#include "stdafx.h"
#include "PSystem.h"

//===================================================================
// - written by ������
// - ��ƼŬ �ý��� ���
//===================================================================


const DWORD ST_Particle::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_PSIZE;

PSystem::PSystem()
	:m_isUse(false)
{
	_device = 0;
	_vb = 0;
	_tex = 0;
}


PSystem::~PSystem()
{
	SAFE_RELEASE(_vb);
	SAFE_RELEASE(_tex);
}

void PSystem::Init(IDirect3DDevice9 * device, char* texFileName)
{
	_device = device;

	device->CreateVertexBuffer(_vbSize * sizeof(ST_Particle),
									D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
									ST_Particle::FVF,
									D3DPOOL_DEFAULT,
									&_vb,
									0);

	D3DXCreateTextureFromFileA(device, texFileName, &_tex);
}

void PSystem::Reset()
{
	std::list<ST_Attribute>::iterator i;
	for (i = _particles.begin(); i != _particles.end(); i++)
	{
		ResetParticle(&(*i));
	}
}

void PSystem::AddParticle()
{
	ST_Attribute attribute;
	ResetParticle(&attribute);
	_particles.push_back(attribute);
}

void PSystem::PreRender()
{
	_device->SetRenderState(D3DRS_LIGHTING, false);
	_device->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	_device->SetRenderState(D3DRS_POINTSCALEENABLE, true);
	_device->SetRenderState(D3DRS_POINTSIZE, FtoDw(32.0f));
	_device->SetRenderState(D3DRS_POINTSIZE_MIN, FtoDw(0.0f));

	// �Ÿ��� ���� ũ�� ����
	_device->SetRenderState(D3DRS_POINTSCALE_A, FtoDw(0.0f));
	_device->SetRenderState(D3DRS_POINTSCALE_B, FtoDw(0.0f));
	_device->SetRenderState(D3DRS_POINTSCALE_C, FtoDw(1.0f));

	// �ؽ�ó�� ���� �̿�
	_device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	_device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	
	_device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

void PSystem::Render()
{
	if (!_particles.empty())
	{
		D3DXMATRIXA16 matWorld;
		D3DXMatrixIdentity(&matWorld);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

		PreRender();

		_device->SetTexture(0, _tex);
		_device->SetFVF(ST_Particle::FVF);
		_device->SetStreamSource(0, _vb, 0, sizeof(ST_Particle));

		if (_vbOffset >= _vbSize)	// ���ؽ� ���۸� ��� ��� ó������ ����
			_vbOffset = 0;

		ST_Particle* v = 0;

		_vb->Lock(_vbOffset * sizeof(ST_Particle),
			_vbBatchSize * sizeof(ST_Particle),
			(void**)&v,
			_vbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

		DWORD numParticlesInBatch = 0;

		// ��� ��ƼŬ�� �������� ������

		std::list<ST_Attribute>::iterator i;
		for (i = _particles.begin(); i != _particles.end(); i++)
		{
			if (i->_isAlive)
			{
				// �� �ܰ��� ������ ��ƼŬ�� ���� ���ؽ� ���� ���׸�Ʈ�� ����
				v->_position = i->_position;
				v->_color = (D3DCOLOR)i->_color;
				v++;
				numParticlesInBatch++;	// �ܰ� ī���� ����

				if (numParticlesInBatch == _vbBatchSize) // ���� �ܰ谡 ��� ä��������
				{
					// ���ؽ� ���۷� ����� ������ �ܰ��� ��ƼŬ�� �׸�
					_vb->Unlock();

					_device->DrawPrimitive(D3DPT_POINTLIST, _vbOffset, _vbBatchSize);

					// �ܰ谡 �׷����� ���� ���� �ܰ踦 ��ƼŬ�� ä���

					// ���� �ܰ��� ó�� ���������� �̵��Ѵ�.
					_vbOffset += _vbBatchSize;

					if (_vbOffset >= _vbSize)	// ��踦 ������ ó������ ����
						_vbOffset = 0;

					_vb->Lock(_vbOffset * sizeof(ST_Particle),
						_vbBatchSize * sizeof(ST_Particle),
						(void**)&v,
						_vbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

					numParticlesInBatch = 0;
				} // << end if
			} // << end if
		} // << end for

		_vb->Unlock();

		// �Ϻθ� ä���� �ܰ� ������
		if (numParticlesInBatch)
		{
			_device->DrawPrimitive(D3DPT_POINTLIST, _vbOffset, numParticlesInBatch);
		}

		_vbOffset += _vbBatchSize;

		PostRender();

	} // << end if
}

void PSystem::PostRender()
{
	_device->SetRenderState(D3DRS_LIGHTING, true);
	_device->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	_device->SetRenderState(D3DRS_POINTSCALEENABLE, false);
	_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

bool PSystem::isEmpty()
{
	return _particles.empty();
}

bool PSystem::isDead()
{
	std::list<ST_Attribute>::iterator i;
	i = _particles.begin();

	while (i != _particles.end())
	{
		if (i->_isAlive == true)
			return false;
		i++;
	}

	return true;
}

DWORD PSystem::FtoDw(float f)
{
	return *((DWORD*)&f);
}

float PSystem::GetRandomFloat(float lowBound, float highBound)
{
	if (lowBound >= highBound)	// �߸��� �Է�
		return lowBound;

	// [0, 1] ������ ���� float�� ��´�
	float f = (rand() % 10000) * 0.0001f;
	return (f * (highBound - lowBound) + lowBound);
}

void PSystem::GetRandomVector(D3DXVECTOR3* out, D3DXVECTOR3* min, D3DXVECTOR3* max)
{
	out->x = GetRandomFloat(min->x, max->x);
	out->y = GetRandomFloat(min->y, max->y);
	out->z = GetRandomFloat(min->z, max->z);
}

void PSystem::removeDeadParticles()
{
	std::list<ST_Attribute>::iterator i;
	i = _particles.begin();

	while (i != _particles.end())
	{
		if (i->_isAlive == false)
		{
			i = _particles.erase(i);
		}
		else
		{
			i++;
		}
	}
}