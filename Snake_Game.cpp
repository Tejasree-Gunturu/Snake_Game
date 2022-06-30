#include <iostream>
#include <conio.h> 
#include <windows.h>
using  namespace std;

// Declaring global variables
const int row = 20;
const int col = 20;
int x, y, fruitX, fruitY, score;
enum edirection { STOP=0, LEFT, RIGHT , UP, DOWN };
edirection dir;
bool gameOver;
int tailX[100], tailY[100];
int nTail;

void setup()
{
    gameOver = false;
    x = row/2; 
    y = col/2; 
    fruitX = rand() % row; // Random fruit generation
    fruitY = rand() % col;
    score = 0;
    dir = STOP;

} 

void draw()
{
    system ("cls"); // CLears the screen terminal
    
    if ( fruitX == 0)
       fruitX = fruitX + 1;

    if ( fruitY == 0)
       fruitY = fruitY + 1;
    
    if ( fruitX == row)
       fruitX = fruitX - 1;

    if ( fruitY == col)
       fruitY = fruitY - 1;
    
    int i, j;
    for (i=0; i<row; i++)
    {
        for (j=0; j<col; j++)
        {
            if ( i==0 || i==row-1 || j==0 || j==col-1)
                cout<<"#";
                
            else if ( i==x && j==y)  // Head of the snake is placed at the middle
                cout<<"O";           

            else if( i==fruitX && j==fruitY) // Random fruit generation
                cout<<"F"; 
              
            else
            {
                bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == i && tailY[k] == j)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
            }
                     
        }
        cout<<endl;
    }
    cout<< "Score : "<<score;
}

void input()
{
    if ( _kbhit() ) // Checks if any of the keys is pressed. If not pressed, void returns zero.
    {
        switch ( _getch() ) // Gets the ACSII value of the chaacter entered

		{
		case 'h':
			dir = LEFT;
			break;
		case 'k':
			dir = RIGHT;
			break;
		case 'u':
			dir = UP;
			break;
		case 'j':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
    }
}

void logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prevX2, prevY2;
    tailX[0] = x; 
    tailY[0] = y;

    for ( int i=1; i<nTail; i++)
    {
        prevX2 = tailX[i];
        prevY2 = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prevX2;
        prevY = prevY2;
    }


    switch (dir)
    {
    case LEFT:
        y--;
        break;
    case RIGHT:
        y++;
        break;
    case UP:
        x--;
        break;
    case DOWN:
        x++;
        break;
    default:
        break;
    }

    if ( x<0 || x>row || y<=0 || y>=col)
    {
        gameOver = true;
    }

    for ( int i =0; i<nTail; i++)
    {
        if ( tailX[i]==x && tailY[i]==y)
           gameOver = true;
    }

    if ( x==fruitX && y==fruitY)
    {
        score += 10;
        fruitX = rand() % row; // Random fruit generation again
        fruitY = rand() % col;
        nTail++; 
    }
}

int main()
{

    setup();
   //Designing the game

    while(!gameOver)
    {
       draw ();
       input();
       logic();
       Sleep(300);
    }

    return 0;
}