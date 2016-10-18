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
int maxX = 40, maxY = 21;                    //地图大小；
int s_size=0;                                //snake的长度；
int lastDir;                                 //记录上一次的运动方向；
int speed = 300;                             //表示snake运动的速度；
bool gameStatus = true;                      //用于碰撞检测；

Snake head, tail;
Snake snake[100];                            //snake的身体;
Snake dir;                                   //表示键入的方向；
Snake foodCoor;                              //用于表示食物的坐标；

void makeWall(int length, int breadth);      //制作游戏边界；
void direction(int ch);                      //判断键入的方向并传出方向代号；
void gotoxy(short x,short y);                //切换光标位置；
void initial();                              //初始化snake；
void move();						         //让snake自由移动；
void food();                                 //随机生成食物；
void addSpeed(int s);                       //加速；
bool eat();                                  //吃掉食物；


int main()
{
	int ch;

	srand((unsigned)time(NULL));

	makeWall(maxX-1, maxY-2);
	gotoxy(10,5);   



	initial();

	while (gameStatus)                                   //检测是否发生碰撞；
	{

		if (_kbhit())
		{
			ch = _getch();
			direction(ch);
		}
		else
		{
			addSpeed(300);
		}

			move();
			Sleep(speed);
			
	}

	gotoxy(1, maxY+1);                               //移动光标到左下角；
	cout << "GameOver" << endl;                      //提示游戏结束；
	


	system("pause");
	return 0;
}

void makeWall(int length, int breadth)
{
	//物理边框；
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

	//边界判定；
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
	ch = _getch();
	if (abs(ch - lastDir) == 8 || abs(ch - lastDir) == 2)
		return;
	if (ch == lastDir)
	{
		addSpeed(100);
	}
	else				 addSpeed(300);

	lastDir = ch;

	switch (ch)
	{
		case 72:	dir.x = 0, dir.y = -1;  break;   //上；
		case 80:	dir.x = 0, dir.y = 1;   break;   //下；
		case 75:	dir.x = -1, dir.y = 0;  break;   //左；
		case 77:	dir.x = 1, dir.y = 0;   break;   //右；
		default:	break;
	}
}

void gotoxy(short x, short y)
{
	COORD coord = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo(hout, &cursor_info);                            //隐藏光标；

}

void initial()
{
	dir.x = 1;
	dir.y = 0;
	lastDir = 77;

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

	food();                                        //随机生成食物；
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

	if (!eat())
		cout << " ";
	else
		++s_size;

	for (i = s_size;i>=1;--i)
		snake[i] = snake[i - 1];

	if (map[snake[1].x][snake[1].y] == 1)
		gameStatus = false;

	map[snake[1].x][snake[1].y] = 1;
	map[tail.x][tail.y] = 0;

	tail = snake[s_size];

	snake[0].x = 0;                         //重置；
	snake[0].y = 0; 
}

void food()
{
	do
	{ 
		foodCoor.x = (rand() % (maxX - 2) + 2);
		foodCoor.y = (rand() % (maxY - 2) + 2);
	} while (map[foodCoor.x][foodCoor.y] == 1);


	gotoxy(foodCoor.x, foodCoor.y);

	cout << char(001);
}

bool eat()
{
	if (foodCoor.x == snake[0].x&&foodCoor.y == snake[0].y)
	{
		snake[s_size + 1] = snake[s_size];

		food();

		return true;
	}
	else
		return false;
}

void addSpeed(int s)
{
	speed = s;
}