#define _CRT_SECURE_NO_WARNINGS
#include "define.h"
#include "searchmove.h"
#include "printchessboard.h"
#include "makemove.h"
#include<ctime>


//������
int main()
{
	cout << "*************�������˻�����AI*************" << endl;
	cout << "����������: whitefirst  ��������" << endl;
	cout << "����������: blackfirst  ���Ժ���" << endl;

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
		counter++;//�غ�����һ
		if (steps.size() >= 225) {
			strcpy(situation, "ƽ�֣�");
			print_situation(situation);
			quit();
			break;
		}
		if (gameover(x, y, black)) {
			strcpy(situation, "��ϲ�㣬����˵��ԣ�");
			print_situation(situation);
			Sleep(1000);
			quit();
			break;
		}
		strcpy(situation, "����������...");
		print_situation(situation);
		
		start = clock();
		flag = 0;
		auto choice = searchMove(white);//������ӵ�
		end = clock();
		
		makeMove(choice.first, choice.second, white);
		drawchess(choice.first, choice.second, white);
		m = choice.first;
		n = choice.second;
		flag = 1;
		if (gameover(choice.first, choice.second, white)) {
			strcpy(situation, "����Ӯ��Ŷ���ٽ�������");
			print_situation(situation);
			Sleep(1000);
			quit();
			break;
		}
		if (steps.size() >= 255) {
			strcpy(situation, "ƽ�֣�");
			print_situation(situation);
			Sleep(1000);
			quit();
			break;
		}
		char time[10];
		sprintf(time, "%i", end - start);
		strcpy(situation, "����������ɡ�(��ʱ");
		strcat(situation, time);
		strcat(situation, "ms)");
		print_situation(situation);
		
	}
	//strcpy(situation, "�����������");
	//print_situation(situation);

	//getchar();
	//closegraph();
	return 0;
}