#include<iostream>
#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include"bin/bin.h"
#include"brick/brick.h"

#define BRICK_TYPES			7	//ש��������
#define BRICK_ORIENT		4	//ש�鷽�� 
#define CBIN_HEIGHT			20	//����߶�
#define CBIN_WIDTH			10	//������
#define DISBIN_HEIGHT		4
#define DISBIN_WIDTH		5 
#define DIFFICULTY			400	//��Ϸ�Ѷȣ�ש������ʱ�䣩

void GotoXY(int x,int y)
{
	COORD c;

	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

void Welcome(void)
{
	cout<<"[����˹����]                                                                "<<endl;  
	cout<<"                                                                            "<<endl;  
	cout<<"                                                                            "<<endl;  
	cout<<"��������������                                      ������                  "<<endl;  
	cout<<"��������������                ������                ������                  "<<endl;  
	cout<<"    ������                    ������                                        "<<endl;  
	cout<<"    ������      ����������    ��������  ������  ��  ������    ����������    "<<endl;  
	cout<<"    ������    ��������������  ��������  ����������  ������  ��������������  "<<endl;  
	cout<<"    ������    ������  ������  ������    ����������  ������  ������  ������  "<<endl;  
	cout<<"    ������    ��������������  ������    ������      ������  ������          "<<endl;  
	cout<<"    ������    ��������������  ������    ������      ������    ��������      "<<endl;  
	cout<<"    ������    ������          ������    ������      ������      ����������  "<<endl;  
	cout<<"    ������    ������  ������  ������    ������      ������          ������  "<<endl;  
	cout<<"    ������    ������  ������  ������    ������      ������  ������  ������  "<<endl;  
	cout<<"    ������    ��������������  ��������  ������      ������  ��������������  "<<endl;  
	cout<<"    ������      ����������    ��������  ������      ������    ����������    "<<endl;  
	cout<<"                                                                            "<<endl;  
	cout<<"                                                                            "<<endl;  
	cout<<"                                                                            "<<endl;
	for(int i=0;i < 37;i++)
	{
		Sleep(60);
		cout<<"��";
	}
	system("cls");	//����
}

void InitDisplay(void)	//��Ļ���Ͻ�����Ϊ 0,0 һ��ש��ռ2���ַ���� 
{
	int i,j;
	
	GotoXY(0,0);
	for(i=0;i < CBIN_HEIGHT;i++)
	{
		cout<<"��";
		for(j=0;j < CBIN_WIDTH;j++)
			cout<<"  ";
		cout<<"��"<<endl;
	}
	for(j=0;j < CBIN_WIDTH+2;j++)
		cout<<"��";
	GotoXY(30,0);
	cout<<"W : ��ת";
	GotoXY(30,1);
	cout<<"S : ����";
	GotoXY(30,2);
	cout<<"A : ����";
	GotoXY(30,3);
	cout<<"D : ����";
	GotoXY(30,4);
	cout<<"P : ��ͣ";
	
	GotoXY(30,6);
	cout<<"Type :  ";
	GotoXY(30,10);
	cout<<"Orient: ";	
	GotoXY(30,12);
	cout<<"SCORE:  ";

}

void Display(unsigned char **image,int score,unsigned int type,unsigned int orient)
{
	for(int i=0;i < CBIN_HEIGHT;i++)
	{
		GotoXY(2,i);
		for(int j=0;j < CBIN_WIDTH;j++)
		{
			if(image[i][j] == 0)
				cout<<"  ";
			else
				cout<<"��";
		}
		cout<<'\n';
	}
	GotoXY(38,10);
	cout<< orient;
	GotoXY(38,12);
	cout<< score;
}

void DisBin(unsigned char **image)
{
	for(int i=0;i < DISBIN_HEIGHT;i++)
	{
		GotoXY(38,6+i);
		for(int j=0;j < DISBIN_WIDTH;j++)
		{
			if(image[i][j] == 0)
				cout<<"  ";
			else
				cout<<"��";
		}
		cout<<'\n';
	}
}

void Pause(void)
{
	char c;

	GotoXY(30,13);	cout<<"Pause !";
	do
	{
		c = getch();
	}while(c != 'p');
	GotoXY(30,13);	cout<<"       ";
}

int main(void)
{
	CBin *tetrisBin=NULL;				//ָ����Ϸ��������
	unsigned char **outputImage=NULL;	//������ʾ���壬������CBin
	unsigned char **disImage=NULL;		//��ʾש������
	CBrick *activeBrick=NULL;			//ָ�����������ש��

	bool GameOver=0;			//��Ϸ�Ƿ����
	bool brickInFlight=0;		//ש���Ƿ��ڷ���״̬
	int brickType=1;			//ש�����
	unsigned int initOrientation=1;	//ש���ʼ״̬
	bool notCollide=0;		//ש���Ƿ��ͻ
	unsigned int emptyLine=0;		//������ 
	int arrowKey=0;			//��¼��ֵ
	int score=0;			//��¼����
//��Ϸ����	
	tetrisBin = new CBin(CBIN_WIDTH,CBIN_HEIGHT);		//������Ϸ���
	outputImage = new unsigned char * [CBIN_HEIGHT];	//������ʾ����
	for(int i=0;i < CBIN_HEIGHT;i++)
	{
		outputImage[i] = new unsigned char [CBIN_WIDTH];
		for(int j=0;j < CBIN_WIDTH;j++)
			outputImage[i][j] = 0;
	}
//ש�����	
	disImage = new unsigned char * [DISBIN_HEIGHT];
	for(int i=0;i < DISBIN_HEIGHT;i++)
	{
		disImage[i] = new unsigned char [DISBIN_WIDTH];
		for(int j=0;j < DISBIN_WIDTH;j++)
			disImage[i][j] = 0;
	}
		
	Welcome();											//��ʾ��ӭ����
	InitDisplay();
	Display(outputImage,score,0,0);
	
	while(!GameOver)	//����Ϸû�н���
	{
		if(!brickInFlight)	//���û��ש���˶���ש���ѵ��ף������½�һ��ש�顣�½���ͬʱ��Ҫָ��ש������ͣ�״̬����ɫ
		{
			brickType = (rand() % BRICK_TYPES) + 1;
			initOrientation = (unsigned int)((rand() % BRICK_ORIENT) + 1);
			switch(brickType)
			{
				case 1: activeBrick = new CIBrick; break;
				case 2: activeBrick = new CIIBrick; break;
				case 3: activeBrick = new CIIIBrick; break;
				case 4: activeBrick = new CIVBrick; break;
				case 5: activeBrick = new CVBrick; break;
				case 6: activeBrick = new CVIBrick; break;
				case 7: activeBrick = new CVIIBrick; break;
				default: GameOver = 1; break;
			}
			activeBrick->SetBrickType(brickType);
			activeBrick->SetColor(brickType);	//����ש������������Ӧ����ɫ
			activeBrick->PutAtTop(initOrientation,(CBIN_WIDTH/2));	//�ö�
			notCollide = activeBrick->CheckCollision(tetrisBin);
			if(notCollide)	//���û�г�ͻ
			{
				brickInFlight = 1;	//����Ϊ����״̬
				tetrisBin->GetImage(outputImage);	//������Ϸ���image��outputImage
				activeBrick->operator>>(outputImage);	//����ǰש��ӳ�䵽outputImage��
			//����ש����ʾ���� 
				activeBrick->oldposX = activeBrick->GetPosX();
				activeBrick->SetPosX(2);
				for(int i=0;i < DISBIN_HEIGHT;i++)
					for(int j=0;j < DISBIN_WIDTH;j++)
						disImage[i][j] = 0;
				activeBrick->operator>>(disImage);	//����ǰש��ӳ�䵽outputImage��
				DisBin(disImage);
				activeBrick->SetPosX(activeBrick->oldposX);
			}
			else	//�½�ש���ͬʱ������ͻ��˵��������������Ϸ����
			{
				GameOver = 1;
				delete activeBrick;
				brickInFlight = 0;
			}
		}
		else	//��ǰ��ש�����£�����ⰴ��������Ϣ
		{
			if(kbhit())
			{
				arrowKey = getch();
				if(arrowKey=='d' || arrowKey=='D')
					activeBrick->ShiftRight(tetrisBin);
				else if(arrowKey=='a' || arrowKey=='A')
					activeBrick->ShiftLeft(tetrisBin);
				else if(arrowKey=='w' || arrowKey=='W')
					activeBrick->RotateClockwise(tetrisBin);
				else if(arrowKey=='s' || arrowKey=='S')
					activeBrick->ShiftLow(tetrisBin);
				else if(arrowKey=='p' || arrowKey=='P')
					Pause();
				// ������Ļ��ʾ
				tetrisBin->GetImage(outputImage);		//��ȡ�����������ʾ����
				activeBrick->operator >>(outputImage);	//����ש�����ݵ���ʾ����
			}
			// ש�鿿��������
			Sleep(DIFFICULTY);
			notCollide = activeBrick->ShiftDown(tetrisBin);
			if(notCollide)
			{
				tetrisBin->GetImage(outputImage);		//��ȡ�����������ʾ����
				activeBrick->operator >>(outputImage);	//����ש�����ݵ���ʾ����
			}
			else	// ש�����ڵײ����ѹ̶���ש���ϣ���������
			{
				brickInFlight = 0;	//ש������Ե���
				tetrisBin->GetImage(outputImage);		//��ȡ�����������ʾ����
				activeBrick->operator >>(outputImage);	//����ש�����ݵ���ʾ����
				tetrisBin->SetImage(outputImage);		//ÿ����Ե��׺󱣴������
				emptyLine = tetrisBin->RemoveFullLines();//��������� 
				switch(emptyLine)						// �Ʒ�
				{
					case 0:  break;
					case 1: score++; break;
					case 2: score+=2; break;
					case 3: score+=3; break;
					case 4: score+=4; break;
					default : score+=10; break;
				}
				tetrisBin->GetImage(outputImage);	//���к�ˢ����ʾ����
				tetrisBin->SetImage(outputImage);	//��������� 
			}
		}	
		Display(outputImage, score, activeBrick->GetBrickType(), activeBrick->GetOrientation());	//��ʾoutputImage
	}
	
	GotoXY(8,24);
	cout<<"GameOver !";
	getch();
	for(int i=0;i < CBIN_HEIGHT;i++)
		delete[] outputImage[i];
	delete[] outputImage;
	for(int i=0;i < DISBIN_HEIGHT;i++)
		delete[] disImage[i];
	delete[] disImage;

	return 0;
}
