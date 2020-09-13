#include<iostream>
#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include"bin/bin.h"
#include"brick/brick.h"

#define BRICK_TYPES			7	//砖块总类型
#define BRICK_ORIENT		4	//砖块方向 
#define CBIN_HEIGHT			20	//界面高度
#define CBIN_WIDTH			10	//界面宽度
#define DISBIN_HEIGHT		4
#define DISBIN_WIDTH		5 
#define DIFFICULTY			400	//游戏难度（砖块下落时间）

void GotoXY(int x,int y)
{
	COORD c;

	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

void Welcome(void)
{
	cout<<"[俄罗斯方块]                                                                "<<endl;  
	cout<<"                                                                            "<<endl;  
	cout<<"                                                                            "<<endl;  
	cout<<"■■■■■■■                                      ■■■                  "<<endl;  
	cout<<"■■■■■■■                ■■■                ■■■                  "<<endl;  
	cout<<"    ■■■                    ■■■                                        "<<endl;  
	cout<<"    ■■■      ■■■■■    ■■■■  ■■■  ■  ■■■    ■■■■■    "<<endl;  
	cout<<"    ■■■    ■■■■■■■  ■■■■  ■■■■■  ■■■  ■■■■■■■  "<<endl;  
	cout<<"    ■■■    ■■■  ■■■  ■■■    ■■■■■  ■■■  ■■■  ■■■  "<<endl;  
	cout<<"    ■■■    ■■■■■■■  ■■■    ■■■      ■■■  ■■■          "<<endl;  
	cout<<"    ■■■    ■■■■■■■  ■■■    ■■■      ■■■    ■■■■      "<<endl;  
	cout<<"    ■■■    ■■■          ■■■    ■■■      ■■■      ■■■■■  "<<endl;  
	cout<<"    ■■■    ■■■  ■■■  ■■■    ■■■      ■■■          ■■■  "<<endl;  
	cout<<"    ■■■    ■■■  ■■■  ■■■    ■■■      ■■■  ■■■  ■■■  "<<endl;  
	cout<<"    ■■■    ■■■■■■■  ■■■■  ■■■      ■■■  ■■■■■■■  "<<endl;  
	cout<<"    ■■■      ■■■■■    ■■■■  ■■■      ■■■    ■■■■■    "<<endl;  
	cout<<"                                                                            "<<endl;  
	cout<<"                                                                            "<<endl;  
	cout<<"                                                                            "<<endl;
	for(int i=0;i < 37;i++)
	{
		Sleep(60);
		cout<<"■";
	}
	system("cls");	//清屏
}

void InitDisplay(void)	//屏幕左上角坐标为 0,0 一个砖块占2个字符宽度 
{
	int i,j;
	
	GotoXY(0,0);
	for(i=0;i < CBIN_HEIGHT;i++)
	{
		cout<<"■";
		for(j=0;j < CBIN_WIDTH;j++)
			cout<<"  ";
		cout<<"■"<<endl;
	}
	for(j=0;j < CBIN_WIDTH+2;j++)
		cout<<"■";
	GotoXY(30,0);
	cout<<"W : 旋转";
	GotoXY(30,1);
	cout<<"S : 下落";
	GotoXY(30,2);
	cout<<"A : 左移";
	GotoXY(30,3);
	cout<<"D : 右移";
	GotoXY(30,4);
	cout<<"P : 暂停";
	
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
				cout<<"□";
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
				cout<<"□";
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
	CBin *tetrisBin=NULL;				//指向游戏面板类对象
	unsigned char **outputImage=NULL;	//用于显示缓冲，独立于CBin
	unsigned char **disImage=NULL;		//显示砖块类型
	CBrick *activeBrick=NULL;			//指向正在下落的砖块

	bool GameOver=0;			//游戏是否结束
	bool brickInFlight=0;		//砖块是否处于飞行状态
	int brickType=1;			//砖块类别
	unsigned int initOrientation=1;	//砖块初始状态
	bool notCollide=0;		//砖块是否冲突
	unsigned int emptyLine=0;		//消行数 
	int arrowKey=0;			//记录键值
	int score=0;			//记录分数
//游戏界面	
	tetrisBin = new CBin(CBIN_WIDTH,CBIN_HEIGHT);		//创建游戏面板
	outputImage = new unsigned char * [CBIN_HEIGHT];	//创建显示界面
	for(int i=0;i < CBIN_HEIGHT;i++)
	{
		outputImage[i] = new unsigned char [CBIN_WIDTH];
		for(int j=0;j < CBIN_WIDTH;j++)
			outputImage[i][j] = 0;
	}
//砖块界面	
	disImage = new unsigned char * [DISBIN_HEIGHT];
	for(int i=0;i < DISBIN_HEIGHT;i++)
	{
		disImage[i] = new unsigned char [DISBIN_WIDTH];
		for(int j=0;j < DISBIN_WIDTH;j++)
			disImage[i][j] = 0;
	}
		
	Welcome();											//显示欢迎界面
	InitDisplay();
	Display(outputImage,score,0,0);
	
	while(!GameOver)	//若游戏没有结束
	{
		if(!brickInFlight)	//如果没有砖块运动（砖块已到底），则新建一个砖块。新建的同时需要指定砖块的类型，状态和颜色
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
			activeBrick->SetColor(brickType);	//根据砖块类型设置相应的颜色
			activeBrick->PutAtTop(initOrientation,(CBIN_WIDTH/2));	//置顶
			notCollide = activeBrick->CheckCollision(tetrisBin);
			if(notCollide)	//如果没有冲突
			{
				brickInFlight = 1;	//更新为下落状态
				tetrisBin->GetImage(outputImage);	//拷贝游戏面板image到outputImage
				activeBrick->operator>>(outputImage);	//将当前砖块映射到outputImage中
			//更新砖块显示界面 
				activeBrick->oldposX = activeBrick->GetPosX();
				activeBrick->SetPosX(2);
				for(int i=0;i < DISBIN_HEIGHT;i++)
					for(int j=0;j < DISBIN_WIDTH;j++)
						disImage[i][j] = 0;
				activeBrick->operator>>(disImage);	//将当前砖块映射到outputImage中
				DisBin(disImage);
				activeBrick->SetPosX(activeBrick->oldposX);
			}
			else	//新建砖块的同时发生冲突，说明界面已满，游戏结束
			{
				GameOver = 1;
				delete activeBrick;
				brickInFlight = 0;
			}
		}
		else	//当前有砖块落下，并检测按键输入信息
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
				// 更新屏幕显示
				tetrisBin->GetImage(outputImage);		//获取面板数据至显示界面
				activeBrick->operator >>(outputImage);	//更新砖块数据到显示界面
			}
			// 砖块靠重力下落
			Sleep(DIFFICULTY);
			notCollide = activeBrick->ShiftDown(tetrisBin);
			if(notCollide)
			{
				tetrisBin->GetImage(outputImage);		//获取面板数据至显示界面
				activeBrick->operator >>(outputImage);	//更新砖块数据到显示界面
			}
			else	// 砖块落在底部或已固定的砖块上，不再下落
			{
				brickInFlight = 0;	//砖块已相对到底
				tetrisBin->GetImage(outputImage);		//获取面板数据至显示界面
				activeBrick->operator >>(outputImage);	//更新砖块数据到显示界面
				tetrisBin->SetImage(outputImage);		//每次相对到底后保存至面板
				emptyLine = tetrisBin->RemoveFullLines();//面板内消行 
				switch(emptyLine)						// 计分
				{
					case 0:  break;
					case 1: score++; break;
					case 2: score+=2; break;
					case 3: score+=3; break;
					case 4: score+=4; break;
					default : score+=10; break;
				}
				tetrisBin->GetImage(outputImage);	//消行后刷新显示界面
				tetrisBin->SetImage(outputImage);	//保存至面板 
			}
		}	
		Display(outputImage, score, activeBrick->GetBrickType(), activeBrick->GetOrientation());	//显示outputImage
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
