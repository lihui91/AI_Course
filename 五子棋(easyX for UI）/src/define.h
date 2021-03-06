#ifndef _DEFINE_
#define _DEFINE_
//全局变量定义

#include <stdio.h>
#include <string.h>
#include <string>
#include <math.h>
#include<conio.h>
#include <iostream>
#include <algorithm>
#include <ctime>
#include<stack>
#include<graphics.h>


using namespace std;

#define blank 0		//空白点
#define black 1		//黑方
#define white 2		//白方
#define inf 1000000		
#define inboard(a,b) (a>=0 && a<=15 && b>=0 && b<=15)		//用于检验招法是否在棋盘上

#define GRID_NUM 16	//棋盘规模	
#define MOVES_AVAILABLE 30 //每次最多搜索走法集个数
extern int chessBoard[GRID_NUM][GRID_NUM]; //棋盘
bool gameover(int x, int y, int player); //判断是否游戏结束
extern stack<pair<int, int>> steps;
bool inBound(int, int);
extern int X, Y;//光标坐标
extern int x, y;//落子坐标
extern int Regret;//悔棋标志
extern int counter;//记录回合数
extern int m, n;//记录电脑最后落子位置
extern int score;//记录局面得分
extern bool flag;//判断是否轮到玩家下子
#endif
