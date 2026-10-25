#define _CRT_SECURE_NO_WARNINGS 1
#include"game.h"
//扫雷游戏,,多文件方式来组织代码
void InitBoard(char board[ROWS][COLS], int row, int col,char set)
{
	int i = 0;
	int j = 0;
	for (i = 0;i < row;i++)
	{
		for (j = 0;j < col;j++)
		{
			board[i][j] = set;
		}
	}
}


//打印
void DisplayBoard(char board[ROWS][COLS], int row, int col)
{
	int i = 0;
	int j = 0;
	printf("-----扫雷游戏-----\n");
	for (j = 0;j <= col; j++)
	{
		printf("%d ", j);
	}
	printf("\n");
	for (i = 1;i <= row;i++)
	{
		printf("%d ", i);
		for (j = 1;j <= col;j++)
		{
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
}

//布置
void SetMine(char mine[ROWS][COLS], int row, int col)
{
	int count = 10;
	while (count)
	{
		//布置
		int x = rand() % row + 1;
		int y = rand() % col + 1;
		if (mine[x][y] == '0')
		{
			mine[x][y] = '1';
			count--;
		}
	}
}

int GetMineCount(char mine[ROWS][COLS], int x, int y)
{
	//x,y坐标周围8个坐标全部-'0'相加就是周围雷的个数
	return mine[x - 1][y - 1] + mine[x][y - 1] + mine[x + 1][y - 1] +
		mine[x - 1][y] + mine[x + 1][y] +
		mine[x - 1][y + 1] + mine[x][y + 1] + mine[x + 1][y + 1] - 8 * '0';
}

//排查
void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col)
{
	int x = 0, y = 0;
	int win = 0;
	while (win<row*col- EASY_COUNT)
	{
		
		printf("请输入排查坐标:");
		if (scanf("%d%d", &x, &y) != 2)
		{
			int ch;
			printf("输入格式不对,请重新输入\n");
			while ((ch = getchar()) != '\n' && ch != EOF)
			{
				;    // 把这一行剩下的字符吃掉,别留在缓冲区里
			}
			if (ch == EOF)
			{
				return;   // 输入已经没了,直接退出这局,别空转
			}
			continue;
		}
		if (x >= 1 && x <= row && y >= 1 && y <= col)
		{
			if (show[x][y] == '*')
			{
				if (mine[x][y] != '1')
				{
					//统计周围雷的个数
					int num=GetMineCount(mine, x, y);
					show[x][y] = num + '0';
					DisplayBoard(show, ROW, COL);
					win++;
				}
				else
				{
					printf("很遗憾,你被炸死了\n");
					DisplayBoard(mine, ROW, COL);
					break;
				}
			}
			else
			{
				printf("该坐标已经被排查过了\n");
			}
		}
		else
			{
				printf("坐标非法,请重新输入");
			}
	}
	if (win == row * col - EASY_COUNT)
	{
		printf("恭喜你,排雷成功\n");
		DisplayBoard(mine, ROW, COL);
	}
}
