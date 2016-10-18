#include<iostream>
#include<cstdlib>
#include<conio.h>
#include<Windows.h>
#include<ctime>
using namespace std;

struct Snake
{
	int x;
	int y;
};

HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);

int map[100][100] = { 0 };
int maxX = 40, maxY = 21;                    //��ͼ��С��
int s_size=0;                                //snake�ĳ��ȣ�
bool gameStatus = true;                      //������ײ��⣻

Snake head, tail;
Snake snake[100];                            //snake������;
Snake dir;                                   //��ʾ����ķ���
Snake foodCoor;                              //���ڱ�ʾʳ������ꣻ

void makeWall(int length, int breadth);      //������Ϸ�߽磻
void direction(int ch);                      //�жϼ���ķ��򲢴���������ţ�
void gotoxy(short x,short y);                //�л����λ�ã�
void initial();                              //��ʼ��snake��
void move();						         //��snake�����ƶ���
void food();                                 //�������ʳ�
bool eat();                                  //�Ե�ʳ�

int main()
{
	srand((unsigned)time(NULL));
	int i,ch,startTime,nowTime;

	makeWall(maxX-1, maxY-2);
	gotoxy(10,5);       


	initial();
	startTime = clock()%1000;

	while (gameStatus)                                   //����Ƿ�����ײ��
	{
		nowTime = clock() % 1000;

		if (ch=_getch())
		{
			direction(ch);
		}

		if (startTime = nowTime + 1)
		{
			startTime = clock() % 1000;
			move();
		}
			
	}

	gotoxy(1, maxY+1);                               //�ƶ���굽���½ǣ�
	cout << "GameOver" << endl;                      //��ʾ��Ϸ������
	


	system("pause");
	return 0;
}

void makeWall(int length, int breadth)
{
	//����߿�
	int i,j;
	cout <<endl<<" "<< char(219);
	for (i = 1; i < length; ++i)
		cout << char(223);
	cout << char(219);
	cout << endl;
	for (i = 1; i <= breadth; ++i)
	{
		cout <<" "<< char(219);
		for (j = 1; j <= length - 1; ++j)
			cout << " ";
		cout << char(219) << endl;
	}
	cout << " ";
	for (i = 1; i <= length+1; ++i)
		cout << char(223);

	//�߽��ж���
	for (i = 1; i <= maxY; ++i)
	{
		for (j = 1; j <= maxX; ++j)
		{
			if (i == 1 || i == maxY)		map[j][i] = 1;
			else
			{
				map[1][i] = map[maxX][i] = 1;
				break;
			}
		}
	}

}

void direction(int ch)
{
	if(ch=_getch())
	switch (ch)
	{
		case 72:	dir.x = 0, dir.y = -1;  break;   //�ϣ�
		case 80:	dir.x = 0, dir.y = 1;   break;   //�£�
		case 75:	dir.x = -1, dir.y = 0;  break;   //��
		case 77:	dir.x = 1, dir.y = 0;   break;   //�ң�
		default:	break;
	}
}

void gotoxy(short x, short y)
{
	COORD coord = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo(hout, &cursor_info);                            //���ع�ꣻ

}

void initial()
{
	s_size = 3;
	snake[3].x = 10;
	snake[2].x = 11;
	snake[1].x = 12;
	snake[1].y = snake[2].y = snake[3].y = 5;

	map[snake[1].x][snake[1].y] = 1;
	map[snake[2].x][snake[2].y] = 1;
	map[snake[3].x][snake[3].y] = 1;

	head = snake[1];
	tail = snake[3];

	cout << char(002) << char(002) << char(002);

	food();                                        //�������ʳ�
}

void move()
{
	int i;
	snake[0].x = head.x + dir.x;
	snake[0].y = head.y + dir.y;
	head = snake[0];
	gotoxy(snake[0].x, snake[0].y);
	cout << char(002);
	gotoxy(tail.x, tail.y);

	if(!eat())
		cout << " ";

	for (i = s_size;i>=1;--i)
		snake[i] = snake[i - 1];

	if (map[snake[1].x][snake[1].y] == 1)
		gameStatus = false;

	map[snake[1].x][snake[1].y] = 1;
	map[tail.x][tail.y] = 0;

	tail = snake[s_size];

	if (eat())
		++s_size;
}

void food()
{
	foodCoor.x = (rand() % (maxX - 1) + 1);
	foodCoor.y = (rand() % (maxY - 1) + 1);

	gotoxy(foodCoor.x, foodCoor.y);

	cout << char(001);
}

bool eat()
{
	if (foodCoor.x == snake[1].x&&foodCoor.y == snake[1].y)
	{
		snake[s_size + 1] = snake[s_size];

		return true;
	}
	else
		return false;
}
