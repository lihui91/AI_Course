/*���Ӻ���*/

#include "define.h"
#include "printchessboard.h"
bool makeMove(int x, int y, int player)
{
	if (inboard(x, y))//����������
	{
		if (chessBoard[x][y])//����ǰλ������
		{
			return false;
		}
		chessBoard[x][y] = player;
		steps.push(make_pair(x, y));//��ǰλ�ü�¼��ջ
		return true;
	}
	//ִ�����Ӳ�����chessboard[i][j]=1 & chessboard[i][j]=2��
	return false;
}

bool unMakeMove(int x, int y)
{
	if (!chessBoard[x][y]) {//����ǰλ��û��
		return false;
	}
	chessBoard[x][y] = 0;
	//�������Ӳ�����chessboard[i][j]=0��
	steps.pop();//��ջ
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
			if (Y > 1) {//��
				Y--;
				system("cls");
				print();
			}
		}
		else if (c == 'd') {//��
			if (Y < 15) {
				Y++;
				system("cls");
				print();
			}

		}
		else if (c == 'w') {//��
			if (X > 1) {
				X--;
				system("cls");
				print();
			}
		}
		else if (c == 's') {//��
			if (X < 15) {
				X++;
				system("cls");
				print();
			}
		}

		else if (c == 'r')//����
		{
			Regret = 1;
			if (Regret) {
				regretMove();
				system("cls");
				print();
			}
		}

		else if (c == 'b')//���¿�ʼ
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