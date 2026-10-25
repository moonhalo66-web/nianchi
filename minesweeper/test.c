#define _CRT_SECURE_NO_WARNINGS 1
#include"game.h"
void menu()
{
	printf("--------------------\n");
	printf("--------1.play------\n");
	printf("--------0.exit------\n");
	printf("--------------------\n");
}

//完成游戏的逻辑
void game()
{
	char mine[ROWS][COLS];//布置
	char show[ROWS][COLS];//排查
	//初始化
	InitBoard(mine, ROWS, COLS,'0');
	InitBoard(show, ROWS, COLS,'*');

	//先打印一下内容
	DisplayBoard(show, ROW, COL);
	//布置
	SetMine(mine,ROW,COL);
	//排除
	FindMine(mine,show,ROW,COL);
}
int main()
{
	srand((unsigned int)time(NULL));
	int input;
	do
	{
		menu();//打印菜单
		printf("请选择:>");
		if (scanf("%d", &input) != 1)
		{
			printf("输入错误,请重新选择\n");
			while (getchar() != '\n')
			{
				;
			}
			input=0;
			continue;
		}
		switch(input)
		{
			case 1:
				game();
				break;
			case 0:
				printf("退出游戏\n");
				break;
			default:
				printf("选择错误,请重新选择\n");
				break;
		}
	} while (input);
	return 0;
}
