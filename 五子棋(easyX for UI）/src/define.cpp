

#include "define.h"

int chessBoard[GRID_NUM][GRID_NUM];//��������
int x, y;
int X=9, Y=9;
int Regret;
int counter=0;
int m, n;
int score = 0;
bool flag = 1;
stack<pair<int, int>> steps;

/*�޶���Χ*/
bool inBound(int x, int y)//�ж������������е���Ƿ�����ϵ
{
	for (int i = -2; i <= 2; i++) {
		for (int j = -2; j <= 2; j++) {
			if (i == 0 && j == 0) continue;
			if (chessBoard[x + i][y + j] != 0)
				return true;
		}
	}
	return false;
}