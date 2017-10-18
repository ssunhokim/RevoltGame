#pragma once
class Image
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE,	//���ҽ� ���� pk3, pak
		LOAD_FILE,		//BMP����
		LOAD_EMPTY,		//�� ��Ʈ�� ����
		LOAD_END
	};

	typedef struct tagImageInfo
	{
		DWORD	resID;
		HDC		hMemDC;
		HBITMAP hBit;
		HBITMAP hOBit;
		float	x;
		float	y;
		int		width;
		int		height;
		int		currentFrameX;	//���� ������ X(���° ��)
		int		currentFrameY;	//���� ������ Y(���° ��)
		int		maxFrameX;		//�ִ� ������ X(���° ��)
		int		maxFrameY;		//�ʴ� ������ Y(���° ��)
		int		frameWidth;		//������ �̹��� ����ũ��
		int		frameHeight;	//������ �̹��� ����ũ��
		BYTE	loadType;

		tagImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			x = 0;
			y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;
		}
		//���� ����ü���� ����ü ������ �����Ҵ������� �����ϱ����� ������ LongPointerIMAGE_INFO
	}IMAGE_INFO, *LPIMAGE_INFO;
private:
	LPIMAGE_INFO		_imageInfo;		//�̹��� ����ü
	CHAR*				_fileName;		//�����̸�
	BOOL				_trans;			//RGB �÷� �������� ����
	COLORREF			_transColor;	//�����ٸ� � �÷���

	BLENDFUNCTION		_blendFunc;		//���ĺ��带 ���Ű���� ����
	LPIMAGE_INFO		_blendImage;	//���ĺ��带 ����� �̹���
public:
	Image();
	~Image();
	//�ʱ�ȭ �Լ� == �� ��Ʈ�� ��
	HRESULT init(int width, int height);
	//�ʱ�ȭ �Լ� == ���ҽ� ���� ��
	HRESULT init(const DWORD resID, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = FALSE);
	//�ʱ�ȭ �Լ� == BMP���� ��
	HRESULT init(const char* fileName, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = FALSE);
	HRESULT init(const char* fileName, float x, float y, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = FALSE, int transSize = 0);

	//������ �̹��� init()
	HRESULT init(const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor);
	HRESULT init(const char* fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor);


	void release(void);
	//���߿� Ʈ���� �÷� �ٲܶ��� ���� ����� �Ծ�
	void setTransColor(BOOL trans, COLORREF transColor);

	void render(HDC hdc);
	//����(�׷��ִ¿�) hdc, �Ѹ� ��X(left), �Ѹ� ��Y(top)
	void render(HDC hdc, int destX, int destY);
	//����					 �Ѹ���X    �Ѹ���Y     �ѷ��ð�X  �ѷ��ð�Y    �ѷ��ð���ũ��  �ѷ��� ����ũ��
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	//��������(�̹��� �����)
	void loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY);

	//������ ����
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	//�޸� DC Getter(������)
	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }

	//===============================
	// �̹��� ���� Getter, Setter
	//===============================

	inline void setX(float x) { _imageInfo->x = x; }
	inline float getX() { return _imageInfo->x; }

	inline void setY(float y) { _imageInfo->y = y; }
	inline float getY() { return _imageInfo->y; }

	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	//���� X
	inline float getCenterX()
	{
		return _imageInfo->maxFrameX <= 0 ?
			_imageInfo->x + (_imageInfo->width / 2) :
			_imageInfo->x + (_imageInfo->frameWidth / 2);
	}

	//���� Y
	inline float getCenterY()
	{
		return _imageInfo->maxFrameY <= 0 ?
			_imageInfo->y + (_imageInfo->height / 2) :
			_imageInfo->y + (_imageInfo->frameHeight / 2);
	}

	//�̹��� ����
	inline int getWidth(void) { return _imageInfo->width; }

	//�̹��� ����
	inline int getHeight(void) { return _imageInfo->height; }

	//������ ���� getter setter
	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX) _imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}

	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY) _imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY(void) { return _imageInfo->maxFrameY; }

	inline int getFrameX(void) { return _imageInfo->currentFrameX; }
	inline int getFrameY(void) { return _imageInfo->currentFrameY; }

	inline int getFrameWidth(void) { return _imageInfo->frameWidth; }
	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }

};

