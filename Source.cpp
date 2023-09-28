#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

bool gameOver;

const int height = 20;
const int width = 50;
const int KEY_UP = 72;
const int KEY_DOWN = 80;
const int KEY_LEFT = 75;
const int KEY_RIGHT = 77;
const int GAME_TICK = 50;

int x, y, fruitX, fruitY, score, tailX[width * height], tailY[width * height], nTail;

int main() {
    // Set Up Gamestate
    {
        gameOver = false;
        x = width / 2;
        y = height / 2;

        srand(time(NULL));

        fruitX = rand() % width;
        fruitY = rand() % height;
    }
    // Gameplay Loop
    gameplay:
    {
        // Draw Current Gamestate to Screen
        {
            system("cls");

            for (int i = 0; i < width; i++) {
                cout << "#";
            }
            cout << endl;
            int j;
            
            for (int i = 0; i < height * width; i++) {
                j = i % height;
                // Check for Player-Player Collision
                if (x == tailX[i] && y == tailY[i]) {
                    gameOver = true;
                }
                if (j == 0 || j == width - 1) {
                    cout << "#";
                }
                else if (i == y && j == x) {
                    cout << "ö";
                }
                else if (i == fruitY && j == fruitX) {
                    cout << "@";
                }
                else {
                    bool print = false;

                    for (int k = 0; k < nTail; k++) {
                        if (i == tailY[k] && j == tailX[k]) {
                            cout << "o";
                            print = true;
                        }
                    }
                    if (!print) { cout << " "; }
                }
                cout << endl;
            }

            for (int i = 0; i < width; i++) {
                cout << "#";
            }
            cout << endl;
            cout << endl;
            cout << "Score: " << score << endl;
        }
        // Run Game Logic
        {
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

            // Get Player Input
            if (_kbhit()) { switch (_getch()) {
                case 'w':
                case KEY_UP:
                    --y;
                break;

                case 'a':
                case KEY_LEFT:
                    --x;
                break;

                case 's':
                case KEY_DOWN:
                    ++y;
                break;

                case 'd':
                case KEY_RIGHT:
                    ++x;
                break;
            }}
            // Check for Player-Wall Collision
            if (x < 0 || x > width || y < 0 || y > height) {
                gameOver = true;
            }

            if (x == fruitX && y == fruitY) {
                score += 1;
                srand(time(NULL));

                fruitX = rand() % width;
                fruitY = rand() % height;
                nTail++;
            }
        }
        // Wait One Game Tick
        Sleep(GAME_TICK);
    }
    if(!gameOver) {
        goto gameplay;
    }
    //Reset Gamestate
    {
        system("cls");
        cout << "Game Over!\n";
        gameOver = false;
        nTail = 0;
        score = 0;
    }
    main();
}
