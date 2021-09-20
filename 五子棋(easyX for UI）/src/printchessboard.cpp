/*打印函数*/

#include "define.h"
#include "makemove.h"
#pragma warning(disable:4996)

/*void judge(int i, int j)
{
	if (i == 1 && j == 1)
		printf("╔ ");
	else if (i == 1 && j == 15)
		printf("╗");
	else if (i == 15 && j == 1)
		printf("╚ ");
	else if (i == 15 && j == 15)
		printf("╝");
	else if (i == 1 && j != 15 && j != 1)
		printf("┯ ");
	else if (i == 15 && j != 15 && j != 1)
		printf("┷ ");
	else if (j == 1 && i != 15 && i != 1)
		printf("┠ ");
	else if (j == 15 && i != 15 && i != 1)
		printf("┨");
	else
		printf("┼ ");
}

void print() //棋盘打印
{
	cout << "【规则】输入: w,s,a,d表示上下左右移动光标，按回车确认落子" << endl;
	cout << "【规则】★表示电脑最后一次落子位置" << endl;
	cout << "【规则】输入: 按下r可以悔棋，按下b重新开始" << endl << endl;
	for (int i = 0; i < 16; i++)
	{
		if (i == 0)
		{
			printf("  ");
			for (int j = 1; j < 16; j++)
				printf("%-2d", j);
			printf("\n");
			continue;
		}
		for (int j = 0; j < 16; j++)
		{
			if (j == 0)
			{
				printf("%2d", i);
				continue;
			}
			if (i == X && j == Y)
			{
				printf("@-");
				
			}
			
			else if (chessBoard[i][j] == 2&&(i!=m||j!=n)) //此处为白子
				printf("●");

			else if (i == m && j == n)
				printf("★");//电脑最后一步标志

			else if (chessBoard[i][j] == 1) //此处为黑子
				printf("○");
			else
			{
				judge(i, j);
			}
		}
		printf("\n");
		
	}
	cout << "当前局面得分：" << score << endl;

}*/
void draw();
void redraw();
void menu();
void CharToTchar(const char * _char, TCHAR * tchar);
void printword();
void playerturn();
void chessboard();
void drawchess(int i, int j, int player);

/*void again(int index);

int a[9][9] = { 0 };*/

void draw()

{

	initgraph(900, 800, SHOWCONSOLE);//初始化图形界面
	

	menu();

}

void CharToTchar(const char * _char, TCHAR * tchar)//为适应高版本VC，须将char转化为Tchar
{
	int iLength;

	iLength = MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, tchar, iLength);
}

void menu()//打印开始界面

{

	IMAGE img;

	setaspectratio(float(1.1), 1);

	

	TCHAR s1[10], s2[10], s3[20], s4[20];
	CharToTchar("IMAGE", s1);
	CharToTchar("tue", s2);
	CharToTchar("宋体", s3);
	CharToTchar("开始游戏", s4);

	//loadimage(&img, s1, s2, 0, 0, true);

	//putimage(-10, 0, &img, SRCPAINT);
	
	settextstyle(50, 20, s3);

	outtextxy(300, 300, s4);

	MOUSEMSG m;

	while (true)

	{

		m = GetMouseMsg();
		//开始游戏界面
		if (m.uMsg == WM_MOUSEMOVE && m.x >= 300 && m.x <= 460 && m.y >= 300 && m.y <= 350)

		{

			setlinecolor(YELLOW);

			rectangle(300, 300, 460, 350);

		}

		if (m.uMsg == WM_LBUTTONDOWN && m.x >= 300 && m.x <= 460 && m.y >= 300 && m.y <= 350)

		{

			cleardevice();

			Sleep(500);
			setfillcolor(RGB(184, 134, 11));
			fillrectangle(0, 0, 900, 800);
			printword();
			chessboard();

			break;

		}

		if (!(m.x >= 300 && m.x <= 460 && m.y >= 300 && m.y <= 350))

		{

			setlinecolor(BLACK);

			rectangle(300, 300, 460, 350);

		}

	}

}

void printword()//打印文字

{
	
	TCHAR  s1[20], s2[20], s3[20], s4[20], s5[40], s6[50];
	char str1[10], str2[50];
	TCHAR s7[10], s8[50];
	CharToTchar("悔棋", s1);
	CharToTchar("回合数: ", s2);
	CharToTchar("宋体", s3);
	CharToTchar("重新开始", s4);
	CharToTchar("当前局面得分：", s5);
	CharToTchar("鼠标左键确认落子", s6);
	

	//graphdefaults();
	setfillcolor(RGB(184,134,11));
	fillrectangle(630, 0, 900, 800);


	setlinecolor(WHITE);

	settextstyle(15, 10, s3);

	//settextcolor(RED);

	outtextxy(660, 80, s6);//规则

	//outtextxy(660, 100, s7);

	settextcolor(WHITE);
	outtextxy(660, 120, s2);
	//settextcolor(GREEN);

	outtextxy(200, 10, s1);
	outtextxy(300, 10, s4);
	outtextxy(660, 160, s5);
	
	settextcolor(YELLOW);

	sprintf(str1, "%i", counter);
	CharToTchar(str1, s7);
	outtextxy(750, 120, s7);
	sprintf(str2, "%i", score);
	CharToTchar(str2, s8);
	outtextxy(660, 180, s8);

}
void print_situation(char s[])//打印游戏结果
{
	TCHAR s1[100];
	CharToTchar(s, s1);
	setfillcolor(RGB(184, 134, 11));
	fillrectangle(0, 625, 900, 800);
	settextcolor(WHITE);
	outtextxy(250, 626, s1);
}
void chessboard()//棋盘

{
	//int err=0;考虑线宽造成的误差
	setlinestyle(PS_SOLID, 1);
	for (int i = 40; i <= 600; i += 40)

	{
		line(i, 40, i, 600);

		line(40, i, 600, i);
		//err+=3;
	}

	//playerturn();

}
void playerturn()//玩家落子（人)

{

	int i = 0, j = 0;
	//char situation[100];
	MOUSEMSG msg;

	while (flag && !gameover(x, y, black))

	{
		FlushMouseMsgBuffer();
		msg = GetMouseMsg();
		if ((msg.x >= 190 && msg.x <= 260 && msg.y >= 0 && msg.y <= 30))//悔棋

		{
			setlinecolor(RED);

			rectangle(190, 5, 260, 30);

		}
		else if ((msg.x >= 290 && msg.x <= 400 && msg.y >= 0 && msg.y <= 30))//重来

		{
			setlinecolor(RED);

			rectangle(290, 5, 400, 30);

		}
		else 
		{
			setlinecolor(RGB(184, 134, 11));

			rectangle(190, 5, 260, 30);
			rectangle(290, 5, 400, 30);

		}
		if (msg.uMsg == WM_LBUTTONDOWN)

		{//>3 -10
			i = (msg.x + 15) / 40-2;
  			//i = i <= 3&& msg.x<220 ? i + 1 : i;
			j = (msg.y+15) / 40-1;
			int k = 40, err = 0,count = 0;
			for(;k<=600&&count<2;k+=40,err+=3){
				if (msg.x > k - 20 + err-3 && msg.x < k + 20 + err)
				{
					i = k / 40 - 1;
					count++;
				}
			/*	if (msg.y > k - 20 + err-3 && msg.y < k + 19 + err)
				{
					j = k / 40 - 1;
					count++;
				}*/
			}
			if ((msg.x >= 190 && msg.x <= 260 && msg.y >= 0 && msg.y <= 30))//悔棋
			{
				Regret = 1;
				if (Regret) {
					regretMove();
					redraw();
				}

			}

			else if ((msg.x >= 290 && msg.x <= 400 && msg.y >= 0 && msg.y <= 30))//重新开始
			{
				int t=counter;
				for (int i = 0; i < t; i++)
				{
					regretMove();
				}
				redraw();
			}
			else{
				if (makeMove(i, j, black))
				{
					drawchess(i, j, black);
					flag = 0;
					x = i; y = j;
				}
			}
		}
	}
}
void drawchess(int i, int j,int player)//画棋子,更新得分
	{
	if (player == black)
	{
		if (m*n)
		{
			setfillcolor(WHITE);
			solidcircle((m+1) * 40, (n + 1) * 40,20);
		}
		setfillcolor(BLACK);
		solidcircle((i+1) * 40, (j + 1) * 40,20);//
	}
	else
	{
		setfillcolor(WHITE);
		
		solidcircle((i+1) * 40, (j + 1) * 40,20);
		Sleep(500);
		if(m*n)
		{ 
		setfillcolor(BLUE);
		solidcircle((i+1) * 40, (j + 1) * 40,20);
		//solidcircle(m * 40, (n + 1) * 40, 20);
		}
	}
	
	printword();
		
	}
void redraw()
{
	setfillcolor(RGB(184, 134, 11));
	fillrectangle(0, 0, 900, 800);
	printword();
	chessboard();
	for (int i =0; i <= 15; i++)
		for (int j =0; j <= 15; j++)
			if (chessBoard[i][j] == 2 && (i != m || j != n)) //此处为白子
			{
				setfillcolor(WHITE);
				if (i > 4)
				    solidcircle(i * 40, (j + 1) * 40,20);
				else
					solidcircle((i + 1) * 40, (j + 1) * 40,20);
				//Sleep(500);
			}
			else if (chessBoard[i][j] == 1) //此处为黑子
			{
				setfillcolor(BLACK);
				if (i > 4)
					solidcircle((i) * 40, (j + 1) * 40,20);
				else
					solidcircle((i + 1) * 40, (j + 1) * 40,20);
			}
	setfillcolor(BLUE);
	//solidcircle(i * 40, (j + 1) * 40, 20);
	if(m*n)
		solidcircle(m * 40, (n + 1) * 40,20);
	flag = 1;
	playerturn();
}
bool quit()
{
	TCHAR s6[20], s3[10],s5[50];
	//CharToTchar("？", s2);
	CharToTchar("宋体", s3);
	
	CharToTchar("欢迎下次再来", s5);
	CharToTchar("五子棋", s6);
	int quit = MessageBox(NULL, s5, s6, MB_OK| MB_SYSTEMMODAL);

	if (quit== IDOK)
	{

		cleardevice();

		settextstyle(50, 30, s3);

		settextcolor(YELLOW);

		outtextxy(200, 300, s5);

		Sleep(1000);

		return 1;

	}
	return 0;
}
