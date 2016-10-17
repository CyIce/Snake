#include<iostream>
#include<cstdlib>
#include<conio.h>
#include<Windows.h>

HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);

int map[100][100] = { 0 };
int maxX = 40, maxY = 21;

void makeWall(int length, int breadth);      //制作游戏边界；
int direction(char ch);                      //判断键入的方向并传出方向代号；
void gotoxy(short x,short y);                //切换光标位置；

using namespace std;
int main()
{
	int i;

	makeWall(maxX-1, maxY-2);
	gotoxy(10,5);                       



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

int direction(char ch)
{
	switch (ch)
	{
		case 72:	return 1;    //上；
		case 80:	return 2;    //下；
		case 75:	return 3;    //左；
		case 77:	return 4;    //右；
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