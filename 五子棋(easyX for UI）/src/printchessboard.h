#ifndef _PRINTCHESSBOARD_
#define _PRINTCHESSBOARD_

//void print();//¥Ú”°∆Â≈Ã
void draw();
void redraw();
void menu();
void CharToTchar(const char * _char, TCHAR * tchar);
void printword();
void playerturn();
void chessbord();
void drawchess(int i, int j, int player);
void print_situation(char s[]);
bool quit();
#endif
