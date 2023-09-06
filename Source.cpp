#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

bool gameOver;
const int hight = 20;
const int width = 50;

int x, y, fruitX, fruitY, score;

int tailX[100], tailY[100], nTail;

enum eDirection {STOP=0, UP, DOWN, LEFT, RIGHT};
eDirection dir;

void Setup() {
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = hight / 2;

	srand(time(NULL));

	fruitX = rand() % width;
	fruitY = rand() % hight;
};
void Draw() {

	
	system("cls");

	for (int i = 0; i < width; i++) {
		cout << "#";
	} cout << endl;

	for (int i = 0; i < hight; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0 || j == width - 1) {
				cout << "#";
			}
			else if (i == y && j == x) {
				cout << "ö";
			}
			else if (i == fruitY && j == fruitX) {
				cout << "@";
			}
			else 
			{
				bool print = false;

				for (int k = 0; k < nTail; k++) {
					if (i == tailY[k] && j == tailX[k]) {
						cout << "o";
						print = true;
					}
				}if (!print) { cout << " "; }
			}
		
		}cout << endl;
	}

	for (int i = 0; i < width; i++) {
		cout << "#";
	} cout << endl;
	  cout << endl;
	  cout << "Score: " << score << endl;
};
void Input() {
	if (_kbhit()) {
		switch (_getch()) {

		case 'w':
			dir = UP;
			break;

		case 'a':
			dir = LEFT;
			break;

		case 's':
			dir = DOWN;
			break;

		case 'd':
			dir = RIGHT;
			break;

		default:
			break;

		}
	}
};
void Logic() {

	int prevX = tailX[0];
	int prevY = tailY[0];

	tailX[0] = x;
	tailY[0] = y;

	int prev2X, prev2Y;

	for (int i = 1; i < nTail; i++) {

		prev2X = tailX[i];
		prev2Y = tailY[i];

		tailX[i] = prevX;
		tailY[i] = prevY;

		prevX = prev2X;
		prevY = prev2Y;

	}


	switch (dir) {
	case UP:

		y--;
		break;

	case DOWN:
		y++;
		break;

	case LEFT:
		x--;
		break;

	case RIGHT:
		x++;
		break;

	default:
		break;

	}
	if (x<0 || x>width || y<0 || y>hight) {
		gameOver = true;
	}

	for(int i = 0; i < nTail; i++) {
		if (x == tailX[i] && y == tailY[i]) {
			gameOver = true;
		}
	}

	if (x == fruitX && y == fruitY) {
		score += 1;
		srand(time(NULL));

		fruitX = rand() % width;
		fruitY = rand() % hight;
		nTail++;
	}
};

int main() {
	Setup();
	while (!gameOver) {
		Draw();
		Input();
		Logic();
		Sleep(50);
	}
	system("cls");

	cout << "Game Over!\n";

	Sleep(2000);

	gameOver = false;

	nTail = 0;
	score = 0;

	main();
}