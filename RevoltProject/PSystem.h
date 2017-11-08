#pragma once

//===================================================================
// - written by ������
// - ��ƼŬ �ý��� ���
//===================================================================

struct ST_Particle
{
	D3DXVECTOR3		_position;
	D3DXCOLOR		_color;
	//float			_size;
	static const DWORD FVF;
};

struct ST_Attribute
{
	D3DXVECTOR3 _position;			// ���� �����̽� ���� ��ƼŬ ��ġ
	D3DXVECTOR3 _velocity;			// ��ƼŬ�� �ӵ�(���� �ʴ� �̵� ������ ���)
	D3DXVECTOR3 _acceleration;		// ��ƼŬ�� ����(���� �ʴ� �̵� ������ ���)
	float		_lifeTime;			// ��ƼŬ�� �Ҹ��� ������ �����Ǵ� �ð�
	float		_age;				// ��ƼŬ�� ���� ����
	D3DXCOLOR	_color;				// ��ƼŬ�� �÷�
	D3DXCOLOR	_colorFade;			// ��ƼŬ�� �÷��� �ð��� �帧�� ���� ����ϴ� ���
	bool		_isAlive;			// ��ƼŬ�� ����Ȯ��

	ST_Attribute()
	{
		_lifeTime = 0.0f;
		_age = 0.0f;
		_isAlive = true;
	}
};


class PSystem
{
public:
	PSystem();
	virtual ~PSystem();

	virtual void Init(IDirect3DDevice9* device, char* texFileName);
	virtual void Reset();													// ��� ��ƼŬ �Ӽ� ����
	virtual void ResetParticle(ST_Attribute* attribute) = 0;				// �� ��ƼŬ �Ӽ� ����
	virtual void AddParticle();												// ��ƼŬ �߰�

	virtual void SetPosition(D3DXVECTOR3* origin) = 0;

	virtual void Update(float timeDelta) = 0;

	virtual void PreRender();						// �������� �ռ� �����ؾ� �� �ʱ� ���� ���¸� ����
	virtual void Render();
	virtual void PostRender();						// Ư�� ��ƼŬ �ý����� �������� �� �ִ� ���� ���¸� �����ϴµ� �̿�

	bool isEmpty();					// ��ƼŬ�� ���� ��� true
	bool isDead();					// ��ƼŬ�� ��� ���� ��� true ( ��ƼŬ�� ������ ��������)

	SYNTHESIZE(bool, m_isUse, IsUse);

	DWORD FtoDw(float f);

	// ���������� ����..
	float GetRandomFloat(float lowBound, float highBound);
	void GetRandomVector(D3DXVECTOR3* out, D3DXVECTOR3* min, D3DXVECTOR3* max);

protected:
	virtual void removeDeadParticles();		// ���� ��ƼŬ�� ����Ʈ���� ����

	IDirect3DDevice9*	_device;
	D3DXVECTOR3			_origin;	// ��ƼŬ�� ���۵Ǵ� ��

	float				_emitRate;	// ���ο� ��ƼŬ�� �߰��Ǵ� ����(���� �ʴ� ��ƼŬ ���� ���)
	float				_size;		// �ý��� �� ��� ��ƼŬ ũ��
	IDirect3DTexture9*	_tex;		// �ý��� �� ��� ��ƼŬ �Ӽ��� ����Ʈ
	IDirect3DVertexBuffer9* _vb;
	std::list<ST_Attribute>	_particles;
	int					_maxParticles;		// �־��� �ð����� �ý����� ������ �ִ� �ִ� ��ƼŬ�� ��

	DWORD	_vbSize;			// ���ؽ����۰� ������ �� �ִ� ��ƼŬ�� ��
	DWORD	_vbOffset;			// ���ؽ� ���ۿ��� ���縦 ������ ��ƼŬ �� ���� �ܰ���� ������
	DWORD	_vbBatchSize;		// �ϳ��� �ܰ迡 ���ǵ� ��ƼŬ�� ��
};

