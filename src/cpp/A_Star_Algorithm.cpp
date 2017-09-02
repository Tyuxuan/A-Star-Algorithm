//
// Created by George on 2017/9/2.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <conio.h>
using namespace std;

//declare variables
int x, y, startX, startY, nowX, nowY, endX, endY;
typedef struct node {
	int f,NODEX,NODEY;
	char mode;
	bool isObstacle, isCheck, isPath;
	node *parentNode;
} node;
typedef struct {
	int X, Y;
} pos;
node Matrix[100][100];
vector<pos> POS, ans;

//important functions
int F(int x, int y) {
	return abs(endX - x) + abs(endY - y) + (abs(x - startX) + abs(y - startY)) * 2;
}
bool comp(pos a, pos b) {
	return F(a.X, a.Y) < F(b.X, b.Y);
}
bool pathFinder() {
	int n = 0;
	if (nowX == endX && nowY == endY) {
		return true;
	}
	if (nowY + 1 < y && !Matrix[nowX][nowY + 1].isObstacle && !Matrix[nowX][nowY + 1].isCheck) {
		Matrix[nowX][nowY + 1].f = F(nowX, nowY + 1);
		Matrix[nowX][nowY + 1].parentNode = &Matrix[nowX][nowY];
		POS.push_back({nowX, nowY + 1});
		n++;
	}
	if (nowX + 1 < x && !Matrix[nowX + 1][nowY].isObstacle && !Matrix[nowX + 1][nowY].isCheck) {
		Matrix[nowX + 1][nowY].f = F(nowX + 1, nowY);
		Matrix[nowX + 1][nowY].parentNode = &Matrix[nowX][nowY];
		POS.push_back({nowX + 1, nowY});
		n++;
	}
	if (nowY - 1 >= 0 && !Matrix[nowX][nowY - 1].isObstacle && !Matrix[nowX][nowY - 1].isCheck) {
		Matrix[nowX][nowY - 1].f = F(nowX, nowY - 1);
		Matrix[nowX][nowY - 1].parentNode = &Matrix[nowX][nowY];
		POS.push_back({nowX, nowY - 1});
		n++;
	}
	if (nowX - 1 >= 0 && !Matrix[nowX - 1][nowY].isObstacle && !Matrix[nowX - 1][nowY].isCheck) {
		Matrix[nowX - 1][nowY].f = F(nowX - 1, nowY);
		Matrix[nowX - 1][nowY].parentNode = &Matrix[nowX][nowY];
		POS.push_back({nowX - 1, nowY});
		n++;
	}
	POS.erase(POS.begin());
	sort(POS.begin(), POS.end(), comp);
	int i = 1;
	Matrix[POS[0].X][POS[0].Y].isCheck = true;
	if (n == 0 && POS.empty())
		return false;
	nowX = POS[0].X;
	nowY = POS[0].Y;
	pathFinder();
}
void makePath() {
	pos mainNode = {endX, endY};
	Matrix[startX][startY].isPath = true;
	do {
		ans.insert(ans.begin(), {mainNode.X, mainNode.Y});
		node *parNode = Matrix[mainNode.X][mainNode.Y].parentNode;
		mainNode = {parNode->NODEX, parNode->NODEY};
	} while (mainNode.X != startX || mainNode.Y != startY);
	for (auto ANS:ans) {
		Matrix[ANS.X][ANS.Y].isPath = true;
	}
}

//other functions
void init(){
	cin >> x >> y;
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			cin >> Matrix[i][j].mode;
			Matrix[i][j].isPath = false;
			Matrix[i][j].isCheck = false;
			Matrix[i][j].isObstacle = false;
			Matrix[i][j].NODEX = i;
			Matrix[i][j].NODEY = j;
			Matrix[i][j].parentNode = NULL;
			switch (Matrix[i][j].mode) {
				case '.': {
					Matrix[i][j].isObstacle = false;
					break;
				}
				case 'S': {
					nowX = i;
					nowY = j;
					startX = i;
					startY = j;
					Matrix[i][j].isCheck = true;
					POS.push_back({nowX, nowY});
					break;
				}
				case 'E': {
					endX = i;
					endY = j;
					break;
				}
				case '#': {
					Matrix[i][j].isObstacle = true;
					break;
				}
			}
		}
	}
}
void print(){
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			if (Matrix[i][j].isPath) {
				cout << '*';
			} else {
				cout << Matrix[i][j].mode;
			}
		}
		cout << endl;
	}
}

//main function
int main() {
	//initialization
	init();

	//FindPath
	if (pathFinder())
		makePath();

	//print
	freopen("path.txt", "w", stdout);
	print();

	getch();
	return 0;
}
