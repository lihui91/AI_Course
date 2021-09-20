/*落子函数*/

#include "define.h"
#include "printchessboard.h"
bool makeMove(int x, int y, int player)
{
	if (inboard(x, y))//若在棋盘内
	{
		if (chessBoard[x][y])//若当前位置有子
		{
			return false;
		}
		chessBoard[x][y] = player;
		steps.push(make_pair(x, y));//当前位置记录入栈
		return true;
	}
	//执行落子操作（chessboard[i][j]=1 & chessboard[i][j]=2）
	return false;
}

bool unMakeMove(int x, int y)
{
	if (!chessBoard[x][y]) {//若当前位置没子
		return false;
	}
	chessBoard[x][y] = 0;
	//撤销落子操作（chessboard[i][j]=0）
	steps.pop();//出栈
	return true;
}

bool regretMove()
{
	if (steps.size() < 2)
		return false;
	auto tmp = steps.top();
	unMakeMove(tmp.first, tmp.second);
	
	tmp = steps.top();
	unMakeMove(tmp.first, tmp.second);
	if (steps.empty())
		m = n = 0;
	else
	{
		tmp = steps.top();
		m = tmp.first; n = tmp.second;
	}
	counter--;
	return true;
}

/*void move()
{
	while (1) {
		char c = _getch();
		if (c == 'a') {
			if (Y > 1) {//左
				Y--;
				system("cls");
				print();
			}
		}
		else if (c == 'd') {//右
			if (Y < 15) {
				Y++;
				system("cls");
				print();
			}

		}
		else if (c == 'w') {//上
			if (X > 1) {
				X--;
				system("cls");
				print();
			}
		}
		else if (c == 's') {//下
			if (X < 15) {
				X++;
				system("cls");
				print();
			}
		}

		else if (c == 'r')//悔棋
		{
			Regret = 1;
			if (Regret) {
				regretMove();
				system("cls");
				print();
			}
		}

		else if (c == 'b')//重新开始
		{
			for (int i = 0; i < counter; i++)
			{
				regretMove();
			}
			system("cls");
			print();
		}

		else if (c == '\r' && chessBoard[X][Y] == 0) {
			makeMove(X, Y, black);
			x = X;
			y = Y;
			system("cls");
			print();
			break;
		}
	}
}*/