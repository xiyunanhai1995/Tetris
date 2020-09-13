#include"brick.h"

//����
bool CBrick::ShiftLeft(CBin *bin)
{
	int posX;

	posX = GetPosX();
	SetPosX(posX-1);
	if(CheckCollision(bin) == 0)
	{
		SetPosX(posX);
		return 0;
	}

	return 1;
}
//����
bool CBrick::ShiftRight(CBin *bin)
{
	int posX;

	posX = GetPosX();
	SetPosX(posX+1);
	if(CheckCollision(bin) == 0)
	{
		SetPosX(posX);
		return 0;
	}

	return 1;
}
//����
bool CBrick::ShiftDown(CBin *bin)
{	
	int posY;

	posY = GetPosY();

	SetPosY(posY+1);
	if(CheckCollision(bin) == 0)
	{
		SetPosY(posY);
		return 0;
	}

	return 1;
}
//���䵽�ײ�
bool CBrick::ShiftLow(CBin *bin)
{	
	int posY;

	posY = GetPosY();

	while(CheckCollision(bin) != 0)
	{
		posY++;
		SetPosY(posY);
	}
	SetPosY(posY-1);

	return 1;
}
//��ת
bool CBrick::RotateClockwise(CBin *bin)
{
	unsigned int oldOrientation,Orientation;
	
	oldOrientation = Orientation = GetOrientation();

	switch(Orientation)
	{
		case angle0:
			Orientation = angle90;
			break;
		case angle90:
			Orientation = angle180;
			break;
		case angle180:
			Orientation = angle270;
			break;
		case angle270:
			Orientation = angle0;
			break;
		default: break;
	}
	SetOrientation(Orientation);
	if(CheckCollision(bin) == 0)	//�����ͻ 
	{
		SetOrientation(oldOrientation);
		return 0;
	}	

	return 1;
}
//=========================================================	������CIBrick
//��ͻ���
bool CIBrick::CheckCollision(CBin *bin)
{
	int width,height,posX,posY;
	unsigned int orientation;
	unsigned char **image=NULL;

	width = bin->GetWidth();	//�õ������
	height = bin->GetHeight();	//�õ������
	image = new unsigned char * [height];	//��������
	for(int i=0;i < height;i++)
		image[i] = new unsigned char [width];
	bin->GetImage(image);	//��ȡ��������
	orientation = GetOrientation();	//��ȡש��״̬
	posX = GetPosX();	//��ȡ����������
	posY = GetPosY();

	switch(orientation)	//����ש���Ӧ״̬���н����ͻ���
	{
		case angle0:	// ״̬ 1 
			//ש�������߽硾λ�ü�顿 
			if((posX-2 < 0)||
			   (posX+1 > width-1)||
			   (posY < 0)||
			   (posY > height-1))	
				return 0;
			//ש�����������̶�ש��
			if((image[posY][posX-2] != 0)||
			   (image[posY][posX-1] != 0)||
			   (image[posY][posX] !=0)||
			   (image[posY][posX+1] != 0))
				return 0;
			break;
		case angle90:	// ״̬ 2 
			if((posX < 0)||
			   (posX > width-1)||
			   (posY-2 < 0)||
			   (posY+1 > height-1))	
				return 0;
			if((image[posY-2][posX] != 0)||
			   (image[posY-1][posX] != 0)||
			   (image[posY][posX] !=0)||
			   (image[posY+1][posX] != 0))	//��״���
				return 0;
			break;
		case angle180:	// ״̬ 3
			if((posX-1 < 0)||
			   (posX+2 > width-1)||
			   (posY < 0)||
			   (posY > height-1))	//λ�ü��
				return 0;
			if((image[posY][posX-1] != 0)||
			   (image[posY][posX] != 0)||
			   (image[posY][posX+1] !=0)||
			   (image[posY][posX+2] != 0))	//��״���
				return 0;
			break;
		case angle270:	// ״̬ 4 
			//ש�������߽�
			if((posX < 0)||			
			   (posX > width-1)||
			   (posY-1 < 0)||
			   (posY+2 > height-1))	
				return 0;
			//ש�����������̶�ש��	
			if((image[posY-1][posX] != 0)||
			   (image[posY][posX] != 0)||
			   (image[posY+1][posX] !=0)||
			   (image[posY+2][posX] != 0))	//��״���
				return 0;
			break;
		default: break;
	}
	return 1;
}
//����ש���״̬���ڽ����������������㣬��ɫ
void CIBrick::operator>>(unsigned char **binImage)
{
	unsigned int orientation;
	int posX,posY;
	unsigned char color=1;

	posX = GetPosX();
	posY = GetPosY();
	orientation = GetOrientation();
	color = GetColor();

	switch(orientation)
	{
		case angle0:
			binImage[posY][posX-2] = color;
			binImage[posY][posX-1] = color;
			binImage[posY][posX]   = color;
			binImage[posY][posX+1] = color;
			break;
		case angle90:
			binImage[posY-2][posX] = color;
			binImage[posY-1][posX] = color;
			binImage[posY][posX]   = color;
			binImage[posY+1][posX] = color;
			break;
		case angle180:
			binImage[posY][posX-1] = color;
			binImage[posY][posX]   = color;
			binImage[posY][posX+1] = color;
			binImage[posY][posX+2] = color;
			break;
		case angle270:
			binImage[posY-1][posX] = color;
			binImage[posY][posX]   = color;
			binImage[posY+1][posX] = color;
			binImage[posY+2][posX] = color;
			break;
		default: break;
	}
}
//�����µ�������X�����״̬������������Y�����ҽ�ש����ڶ���
void CIBrick::PutAtTop(unsigned int orientation,int posX)
{
	SetPosX(posX);
	SetOrientation(orientation);
	switch(orientation)
	{
		case angle0:   SetPosY(0); break;	
		case angle90:  SetPosY(2); break;	
		case angle180: SetPosY(0); break;
		case angle270: SetPosY(1); break; 
		default :break;
	}
}

//=========================================================	������CIIBrick
//��ͻ���
bool CIIBrick::CheckCollision(CBin *bin)
{
	unsigned int orientation;
	int width,height,posX,posY;
	unsigned char **image;

	width = bin->GetWidth();	//�õ������
	height = bin->GetHeight();	//�õ������
	image = new unsigned char * [height];	//��������
	for(unsigned int i=0;i < height;i++)
		image[i] = new unsigned char [width];
	bin->GetImage(image);	//��ȡ��������
	orientation = GetOrientation();	//��ȡש��״̬
	posX = GetPosX();	//��ȡ����������
	posY = GetPosY();

	if((posX < 0)||(posX+1 > width-1)||(posY < 0)||(posY+1 > height-1))	//λ�ü��
			return false;
	if((image[posY][posX] != 0)||(image[posY][posX+1] != 0)||(image[posY+1][posX] !=0)||(image[posY+1][posX+1] != 0))	//��״���
			return false;

	return true;
}
//����ש���״̬���ڽ����������������㣬��ɫ
void CIIBrick::operator>>(unsigned char **binImage)
{
	unsigned int orientation;
	int posX,posY;
	unsigned char color=1;

	posX = GetPosX();
	posY = GetPosY();
	orientation = GetOrientation();
	color = GetColor();

	binImage[posY][posX]	 = color;
	binImage[posY][posX+1]	 = color;
	binImage[posY+1][posX]   = color;
	binImage[posY+1][posX+1] = color;

}
//�����µ�������X�����״̬������������Y�����ҽ�ש����ڶ���
void CIIBrick::PutAtTop(unsigned int orientation,int posX)
{
	SetPosX(posX);
	SetOrientation(orientation);
			
	SetPosY(0);	//�ö�
}


//=========================================================	������CIIIBrick
//��ͻ���
bool CIIIBrick::CheckCollision(CBin *bin)
{
	unsigned int orientation;
	int width,height,posX,posY;
	unsigned char **image;

	width = bin->GetWidth();	//�õ������
	height = bin->GetHeight();	//�õ������
	image = new unsigned char * [height];	//��������
	for(unsigned int i=0;i < height;i++)
		image[i] = new unsigned char [width];
	bin->GetImage(image);	//��ȡ��������
	orientation = GetOrientation();	//��ȡש��״̬
	posX = GetPosX();	//��ȡ����������
	posY = GetPosY();

	switch(orientation)	//����ש���Ӧ״̬���н����ͻ���
	{
		case angle0:
			if((posX-1 < 0)||(posX+1 > width-1)||(posY < 0)||(posY+1 > height-1))	//λ�ü��
				return 0;
			if((image[posY][posX] != 0)||(image[posY][posX+1] != 0)||(image[posY+1][posX-1] !=0)||(image[posY+1][posX] != 0))	//��״���
				return 0;
			break;
		case angle90:
			if((posX-1 < 0)||(posX > width-1)||(posY-1 < 0)||(posY+1 > height-1))	//λ�ü��
				return 0;
			if((image[posY-1][posX-1] != 0)||(image[posY][posX-1] != 0)||(image[posY][posX] !=0)||(image[posY+1][posX] != 0))	//��״���
				return 0;
			break;
		case angle180:
			if((posX-1 < 0)||(posX+1 > width-1)||(posY-1 < 0)||(posY > height-1))	//λ�ü��
				return 0;
			if((image[posY][posX-1] != 0)||(image[posY][posX] != 0)||(image[posY][posX+1] !=0)||(image[posY][posX+2] != 0))	//��״���
				return 0;
			break;
		case angle270:
			if((posX < 0)||(posX+1 > width-1)||(posY-1 < 0)||(posY+1 > height-1))	//λ�ü��
				return 0;
			if((image[posY-1][posX] != 0)||(image[posY][posX] != 0)||(image[posY][posX+1] !=0)||(image[posY+1][posX+1] != 0))	//��״���
				return 0;
			break;
		default: break;
	}
	return 1;
}
//����ש���״̬���ڽ����������������㣬��ɫ
void CIIIBrick::operator>>(unsigned char **binImage)
{
	unsigned int orientation;
	int posX,posY;
	unsigned char color=1;

	posX = GetPosX();
	posY = GetPosY();
	orientation = GetOrientation();
	color = GetColor();

	switch(orientation)
	{
		case angle0:
			binImage[posY][posX]	 = color;
			binImage[posY][posX+1]	 = color;
			binImage[posY+1][posX-1] = color;
			binImage[posY+1][posX]	 = color;
			break;
		case angle90:
			binImage[posY-1][posX-1]   = color;
			binImage[posY][posX-1]   = color;
			binImage[posY][posX]     = color;
			binImage[posY+1][posX]   = color;
			break;
		case angle180:
			binImage[posY-1][posX] = color;
			binImage[posY-1][posX+1]   = color;
			binImage[posY][posX-1] = color;
			binImage[posY][posX] = color;
			break;
		case angle270:
			binImage[posY-1][posX] = color;
			binImage[posY][posX]   = color;
			binImage[posY][posX+1] = color;
			binImage[posY+1][posX+1] = color;
			break;
		default: break;
	}
}
//�����µ�������X�����״̬������������Y�����ҽ�ש����ڶ���
void CIIIBrick::PutAtTop(unsigned int orientation,int posX)
{
	SetPosX(posX);
	SetOrientation(orientation);
	switch(orientation)
	{
		case angle0:
			SetPosY(0);	//�ö�
			break;
		case angle90:
			SetPosY(1);	//�ö�
			break;
		case angle180:
			SetPosY(1); //�ö�
			break;
		case angle270:
			SetPosY(1); //�ö�
			break;
		default :break;
	}
}

//=========================================================	������CIVBrick
//��ͻ���
bool CIVBrick::CheckCollision(CBin *bin)
{
	unsigned int orientation;
	int width,height,posX,posY;
	unsigned char **image;

	width = bin->GetWidth();	//�õ������
	height = bin->GetHeight();	//�õ������
	image = new unsigned char * [height];	//��������
	for(unsigned int i=0;i < height;i++)
		image[i] = new unsigned char [width];
	bin->GetImage(image);	//��ȡ��������
	orientation = GetOrientation();	//��ȡש��״̬
	posX = GetPosX();	//��ȡ����������
	posY = GetPosY();

	switch(orientation)	//����ש���Ӧ״̬���н����ͻ���
	{
		case angle0:
			if((posX-1 < 0)||(posX+1 > width-1)||(posY < 0)||(posY+1 > height-1))	//λ�ü��
				return 0;
			if((image[posY][posX-1] != 0)||(image[posY][posX] != 0)||(image[posY+1][posX] !=0)||(image[posY+1][posX+1] != 0))	//��״���
				return 0;
			break;
		case angle90:
			if((posX-1 < 0)||(posX > width-1)||(posY-1 < 0)||(posY+1 > height-1))	//λ�ü��
				return 0;
			if((image[posY-1][posX] != 0)||(image[posY][posX-1] != 0)||(image[posY][posX] !=0)||(image[posY-1][posX-1] != 0))	//��״���
				return 0;
			break;
		case angle180:
			if((posX-1 < 0)||(posX+1 > width-1)||(posY-1 < 0)||(posY > height-1))	//λ�ü��
				return 0;
			if((image[posY-1][posX-1] != 0)||(image[posY-1][posX] != 0)||(image[posY][posX] !=0)||(image[posY][posX+1] != 0))	//��״���
				return 0;
			break;
		case angle270:
			if((posX < 0)||(posX+1 > width-1)||(posY-1 < 0)||(posY+1 > height-1))	//λ�ü��
				return 0;
			if((image[posY-1][posX+1] != 0)||(image[posY][posX] != 0)||(image[posY][posX+1] !=0)||(image[posY-1][posX] != 0))	//��״���
				return 0;
			break;
		default: break;
	}
	return 1;
}
//����ש���״̬���ڽ����������������㣬��ɫ
void CIVBrick::operator>>(unsigned char **binImage)
{
	unsigned int orientation;
	int posX,posY;
	unsigned char color=1;

	posX = GetPosX();
	posY = GetPosY();
	orientation = GetOrientation();
	color = GetColor();

	switch(orientation)
	{
		case angle0:
			binImage[posY][posX-1] = color;
			binImage[posY][posX] = color;
			binImage[posY+1][posX]   = color;
			binImage[posY+1][posX+1] = color;
			break;
		case angle90:
			binImage[posY-1][posX] = color;
			binImage[posY][posX-1] = color;
			binImage[posY][posX]   = color;
			binImage[posY+1][posX-1] = color;
			break;
		case angle180:
			binImage[posY-1][posX-1] = color;
			binImage[posY-1][posX]   = color;
			binImage[posY][posX] = color;
			binImage[posY][posX+1] = color;
			break;
		case angle270:
			binImage[posY-1][posX+1] = color;
			binImage[posY][posX]   = color;
			binImage[posY][posX+1] = color;
			binImage[posY+1][posX] = color;
			break;
		default: break;
	}
}
//�����µ�������X�����״̬������������Y�����ҽ�ש����ڶ���
void CIVBrick::PutAtTop(unsigned int orientation,int posX)
{
	SetPosX(posX);
	SetOrientation(orientation);
	switch(orientation)
	{
		case angle0:
			SetPosY(0);	
			break;
		case angle90:
			SetPosY(1);	
			break;
		case angle180:
			SetPosY(1); 
			break;
		case angle270:
			SetPosY(1); 
			break;
		default :break;
	}
}

//=========================================================	������CVBrick
//��ͻ���
bool CVBrick::CheckCollision(CBin *bin)
{
	unsigned int orientation;
	int width,height,posX,posY;
	unsigned char **image;

	width = bin->GetWidth();	//�õ������
	height = bin->GetHeight();	//�õ������
	image = new unsigned char * [height];	//��������
	for(unsigned int i=0;i < height;i++)
		image[i] = new unsigned char [width];
	bin->GetImage(image);	//��ȡ��������
	orientation = GetOrientation();	//��ȡש��״̬
	posX = GetPosX();	//��ȡ����������
	posY = GetPosY();

	switch(orientation)	//����ש���Ӧ״̬���н����ͻ���
	{
		case angle0:
			if((posX-1 < 0)||(posX+1 > width-1)||(posY < 0)||(posY+1 > height-1))	//λ�ü��
				return 0;
			if((image[posY][posX-1] != 0)||(image[posY][posX] != 0)||(image[posY][posX+1] !=0)||(image[posY+1][posX+1] != 0))	//��״���
				return 0;
			break;
		case angle90:
			if((posX-1 < 0)||(posX > width-1)||(posY-1 < 0)||(posY+1 > height-1))	//λ�ü��
				return 0;
			if((image[posY-1][posX] != 0)||(image[posY][posX] != 0)||(image[posY+1][posX-1] !=0)||(image[posY+1][posX] != 0))	//��״���
				return 0;
			break;
		case angle180:
			if((posX-1 < 0)||(posX+1 > width-1)||(posY-1 < 0)||(posY > height-1))	//λ�ü��
				return 0;
			if((image[posY-1][posX-1] != 0)||(image[posY][posX-1] != 0)||(image[posY][posX] !=0)||(image[posY][posX+1] != 0))	//��״���
				return 0;
			break;
		case angle270:
			if((posX < 0)||(posX+1 > width-1)||(posY-1 < 0)||(posY+1 > height-1))	//λ�ü��
				return 0;
			if((image[posY-1][posX] != 0)||(image[posY-1][posX-1] != 0)||(image[posY][posX] !=0)||(image[posY+1][posX] != 0))	//��״���
				return 0;
			break;
		default: break;
	}
	return 1;
}
//����ש���״̬���ڽ����������������㣬��ɫ
void CVBrick::operator>>(unsigned char **binImage)
{
	unsigned int orientation;
	int posX,posY;
	unsigned char color;

	posX = GetPosX();
	posY = GetPosY();
	orientation = GetOrientation();
	color = GetColor();

	switch(orientation)
	{
		case angle0:
			binImage[posY][posX-1] = color;
			binImage[posY][posX] = color;
			binImage[posY][posX+1]   = color;
			binImage[posY+1][posX+1] = color;
			break;
		case angle90:
			binImage[posY-1][posX] = color;
			binImage[posY][posX] = color;
			binImage[posY+1][posX-1]   = color;
			binImage[posY+1][posX] = color;
			break;
		case angle180:
			binImage[posY-1][posX-1] = color;
			binImage[posY][posX-1]   = color;
			binImage[posY][posX] = color;
			binImage[posY][posX+1] = color;
			break;
		case angle270:
			binImage[posY-1][posX] = color;
			binImage[posY-1][posX-1]   = color;
			binImage[posY][posX] = color;
			binImage[posY+1][posX] = color;
			break;
		default: break;
	}
}
//�����µ�������X�����״̬������������Y�����ҽ�ש����ڶ���
void CVBrick::PutAtTop(unsigned int orientation,int posX)
{
	SetPosX(posX);
	SetOrientation(orientation);
	switch(orientation)
	{
		case angle0:
			SetPosY(0);	//�ö�
			break;
		case angle90:
			SetPosY(1);	//�ö�
			break;
		case angle180:
			SetPosY(1); //�ö�
			break;
		case angle270:
			SetPosY(1); //�ö�
			break;
		default :break;
	}
}


//=========================================================	������CVIBrick
//��ͻ���
bool CVIBrick::CheckCollision(CBin *bin)
{
	unsigned int orientation;
	int width,height,posX,posY;
	unsigned char **image;

	width = bin->GetWidth();	//�õ������
	height = bin->GetHeight();	//�õ������
	image = new unsigned char * [height];	//��������
	for(unsigned int i=0;i < height;i++)
		image[i] = new unsigned char [width];
	bin->GetImage(image);	//��ȡ��������
	orientation = GetOrientation();	//��ȡש��״̬
	posX = GetPosX();	//��ȡ����������
	posY = GetPosY();

	switch(orientation)	//����ש���Ӧ״̬���н����ͻ���
	{
		case angle0:
			if((posX-1 < 0)||(posX+1 > width-1)||(posY < 0)||(posY+1 > height-1))	//λ�ü��
				return 0;
			if((image[posY][posX-1] != 0)||(image[posY][posX] != 0)||(image[posY][posX+1] !=0)||(image[posY+1][posX-1] != 0))	//��״���
				return 0;
			break;
		case angle90:
			if((posX-1 < 0)||(posX > width-1)||(posY-1 < 0)||(posY+1 > height-1))	//λ�ü��
				return 0;
			if((image[posY-1][posX-1] != 0)||(image[posY-1][posX] != 0)||(image[posY][posX] !=0)||(image[posY+1][posX] != 0))	//��״���
				return 0;
			break;
		case angle180:
			if((posX-1 < 0)||(posX+1 > width-1)||(posY-1 < 0)||(posY > height-1))	//λ�ü��
				return 0;
			if((image[posY-1][posX+1] != 0)||(image[posY][posX-1] != 0)||(image[posY][posX] !=0)||(image[posY][posX+1] != 0))	//��״���
				return 0;
			break;
		case angle270:
			if((posX < 0)||(posX+1 > width-1)||(posY-1 < 0)||(posY+1 > height-1))	//λ�ü��
				return 0;
			if((image[posY-1][posX] != 0)||(image[posY][posX] != 0)||(image[posY+1][posX] !=0)||(image[posY+1][posX+1] != 0))	//��״���
				return 0;
			break;
		default: break;
	}
	return 1;
}
//����ש���״̬���ڽ����������������㣬��ɫ
void CVIBrick::operator>>(unsigned char **binImage)
{
	unsigned int orientation;
	int posX,posY;
	unsigned char color;

	posX = GetPosX();
	posY = GetPosY();
	orientation = GetOrientation();
	color = GetColor();

	switch(orientation)
	{
		case angle0:
			binImage[posY][posX-1] = color;
			binImage[posY][posX] = color;
			binImage[posY][posX+1]   = color;
			binImage[posY+1][posX-1] = color;
			break;
		case angle90:
			binImage[posY-1][posX-1] = color;
			binImage[posY-1][posX] = color;
			binImage[posY][posX]   = color;
			binImage[posY+1][posX] = color;
			break;
		case angle180:
			binImage[posY-1][posX+1] = color;
			binImage[posY][posX-1]   = color;
			binImage[posY][posX] = color;
			binImage[posY][posX+1] = color;
			break;
		case angle270:
			binImage[posY-1][posX] = color;
			binImage[posY][posX]   = color;
			binImage[posY+1][posX] = color;
			binImage[posY+1][posX+1] = color;
			break;
		default: break;
	}
}
//�����µ�������X�����״̬������������Y�����ҽ�ש����ڶ���
void CVIBrick::PutAtTop(unsigned int orientation,int posX)
{
	SetPosX(posX);
	SetOrientation(orientation);
	switch(orientation)
	{
		case angle0:
			SetPosY(0);	//�ö�
			break;
		case angle90:
			SetPosY(1);	//�ö�
			break;
		case angle180:
			SetPosY(1); //�ö�
			break;
		case angle270:
			SetPosY(1); //�ö�
			break;
		default :break;
	}
}

//=========================================================	������CVIIBrick
//��ͻ���
bool CVIIBrick::CheckCollision(CBin *bin)
{
	unsigned int orientation;
	int width,height,posX,posY;
	unsigned char **image;

	width = bin->GetWidth();	//�õ������
	height = bin->GetHeight();	//�õ������
	image = new unsigned char * [height];	//��������
	for(unsigned int i=0;i < height;i++)
		image[i] = new unsigned char [width];
	bin->GetImage(image);	//��ȡ��������
	orientation = GetOrientation();	//��ȡש��״̬
	posX = GetPosX();	//��ȡ����������
	posY = GetPosY();

	switch(orientation)	//����ש���Ӧ״̬���н����ͻ���
	{
		case angle0:
			if((posX-1 < 0)||(posX+1 > width-1)||(posY < 0)||(posY+1 > height-1))	//λ�ü��
				return 0;
			if((image[posY][posX-1] != 0)||(image[posY][posX] != 0)||(image[posY][posX+1] !=0)||(image[posY+1][posX] != 0))	//��״���
				return 0;
			break;
		case angle90:
			if((posX-1 < 0)||(posX > width-1)||(posY-1 < 0)||(posY+1 > height-1))	//λ�ü��
				return 0;
			if((image[posY-1][posX] != 0)||(image[posY][posX-1] != 0)||(image[posY][posX] !=0)||(image[posY+1][posX] != 0))	//��״���
				return 0;
			break;
		case angle180:
			if((posX-1 < 0)||(posX+1 > width-1)||(posY-1 < 0)||(posY > height-1))	//λ�ü��
				return 0;
			if((image[posY-1][posX] != 0)||(image[posY][posX-1] != 0)||(image[posY][posX] !=0)||(image[posY][posX+1] != 0))	//��״���
				return 0;
			break;
		case angle270:
			if((posX < 0)||(posX+1 > width-1)||(posY-1 < 0)||(posY+1 > height-1))	//λ�ü��
				return 0;
			if((image[posY-1][posX] != 0)||(image[posY][posX] != 0)||(image[posY][posX+1] !=0)||(image[posY+1][posX] != 0))	//��״���
				return 0;
			break;
		default: break;
	}
	return 1;
}
//����ש���״̬���ڽ����������������㣬��ɫ
void CVIIBrick::operator>>(unsigned char **binImage)
{
	unsigned int orientation;
	int posX,posY;
	unsigned char color;

	posX = GetPosX();
	posY = GetPosY();
	orientation = GetOrientation();
	color = GetColor();

	switch(orientation)
	{
		case angle0:
			binImage[posY][posX-1] = color;
			binImage[posY][posX] = color;
			binImage[posY][posX+1]   = color;
			binImage[posY+1][posX] = color;
			break;
		case angle90:
			binImage[posY-1][posX] = color;
			binImage[posY][posX-1] = color;
			binImage[posY][posX]   = color;
			binImage[posY+1][posX] = color;
			break;
		case angle180:
			binImage[posY-1][posX] = color;
			binImage[posY][posX-1]   = color;
			binImage[posY][posX] = color;
			binImage[posY][posX+1] = color;
			break;
		case angle270:
			binImage[posY-1][posX] = color;
			binImage[posY][posX]   = color;
			binImage[posY][posX+1] = color;
			binImage[posY+1][posX] = color;
			break;
		default: break;
	}
}
//�����µ�������X�����״̬������������Y�����ҽ�ש����ڶ���
void CVIIBrick::PutAtTop(unsigned int orientation,int posX)
{
	SetPosX(posX);
	SetOrientation(orientation);
	switch(orientation)
	{
		case angle0:
			SetPosY(0);	//�ö�
			break;
		case angle90:
			SetPosY(1);	//�ö�
			break;
		case angle180:
			SetPosY(1); //�ö�
			break;
		case angle270:
			SetPosY(1); //�ö�
			break;
		default :break;
	}
}


