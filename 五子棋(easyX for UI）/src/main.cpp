#define _CRT_SECURE_NO_WARNINGS
#include "define.h"
#include "searchmove.h"
#include "printchessboard.h"
#include "makemove.h"
#include<ctime>


//主函数
int main()
{
	cout << "*************五子棋人机对弈AI*************" << endl;
	cout << "【规则】输入: whitefirst  电脑先手" << endl;
	cout << "【规则】输入: blackfirst  电脑后手" << endl;

	clock_t start, end;
	char cmd[15],situation[100];
	cin >> cmd;
	draw();
	if (strcmp(cmd, "whitefirst") == 0) {
		flag = 0;
		makeMove(8, 7, white);
		drawchess(8, 7, white);
		flag = 1;

		m = 8;
		n = 7;
	}
	
	//print();
	
	while (true) {
		playerturn();
		counter++;//回合数加一
		if (steps.size() >= 225) {
			strcpy(situation, "平局！");
			print_situation(situation);
			quit();
			break;
		}
		if (gameover(x, y, black)) {
			strcpy(situation, "恭喜你，打败了电脑！");
			print_situation(situation);
			Sleep(1000);
			quit();
			break;
		}
		strcpy(situation, "电脑下棋中...");
		print_situation(situation);
		
		start = clock();
		flag = 0;
		auto choice = searchMove(white);//最佳落子点
		end = clock();
		
		makeMove(choice.first, choice.second, white);
		drawchess(choice.first, choice.second, white);
		m = choice.first;
		n = choice.second;
		flag = 1;
		if (gameover(choice.first, choice.second, white)) {
			strcpy(situation, "电脑赢了哦，再接再厉！");
			print_situation(situation);
			Sleep(1000);
			quit();
			break;
		}
		if (steps.size() >= 255) {
			strcpy(situation, "平局！");
			print_situation(situation);
			Sleep(1000);
			quit();
			break;
		}
		char time[10];
		sprintf(time, "%i", end - start);
		strcpy(situation, "电脑下棋完成。(耗时");
		strcat(situation, time);
		strcat(situation, "ms)");
		print_situation(situation);
		
	}
	//strcpy(situation, "按任意键返回");
	//print_situation(situation);

	//getchar();
	//closegraph();
	return 0;
}