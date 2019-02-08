#include <iostream>
#include <conio.h>
#include <windows.h>
#include<cstdlib>
#include<ctime>
#include<string>
using namespace std;
bool gameOver;
int n;
int life=3,count =0;
const int width = 20;
const int height = 20;

int x, y,obsticleX,obsticleY,bugX,bugY,fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirecton dir;
void Setup()
{
    life;
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	obsticleX = rand() % width;
    obsticleX = time(0) % width;
    obsticleY = rand() % height;
    obsticleY = time(0) % height;
	fruitX = rand() % width;
	fruitY = rand() % height;
	bugX = rand() % width;
	bugY = rand() % height;
	score = 0;
}
void Draw()
{
	system("cls"); //system("clear");
	for (int i = 0; i < width+2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "#";
			if (i == y && j == x)
				cout << "@";
			else if (i == fruitY && j == fruitX)
				cout << "*";
				else if(i==obsticleY && j== obsticleX)
                    cout<<"^";
                    else if(i== bugX && j == bugY)
                        cout<<"~";

			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}


			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i < width+2; i++)
		cout << "#";
	cout << endl;
	cout << "SCORE:" << score << "      FOOD: "<<count<<endl;
	cout<<"LIFE: "<<life<<endl;



}
void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 75:
			dir = LEFT;
			break;
		case 77:
			dir = RIGHT;
			break;
		case 72:
			dir = UP;
			break;
		case 80:
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
    }
};
void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	//if (x > width || x < 0 || y > height || y < 0)
		//gameOver = true;
	if (x >= width) x = 0; else if (x < 0) x = width - 1;
	if (y >= height) y = 0; else if (y < 0) y = height - 1;

	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
        {
            life--;
        }else if(life==0)
			gameOver = true;


				if(gameOver==true)
    {
        cout<<" HIGH SCORE : "<<score<<endl;
    }

	if (x == fruitX && y == fruitY )
	{
		score += 5;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
		count++;
	}


	};
	class Enemy
	{
	    public:
	    virtual void attack(){
	    }
	};
	class Bug: public Enemy
        {
        public:

            void attack()
            {
                if(x == bugX && y == bugY)
                {

	           bugX = time(0) %width;
	           bugY = time(0)% height;
	           bugX = rand()% width;
	           bugY = rand() % height;
	           score--;
	           if((x == bugX && y == bugY)>=2)
               {
                   life--;
               }
	           if(nTail>2)
	           nTail--;
                }

            }
        };
	class obsticle: public Enemy
	{
    public:
        void attack()
        {
          if(x == obsticleX && y == obsticleY && fruitX!= obsticleX && fruitY!=obsticleY  )
	      {
	           obsticleX = time(0) %width;
	           obsticleY = time(0)% height;
	           obsticleX = rand()% width;
	           obsticleY = rand() % height;
	           life--;
          }

        };


	};
/*string *MenuItems();
void gotoxy(int,int);
void ChangeCursorStatus(bool);
void play_Game();
void MenuFun2();
void MenuFun3();
void ExitOption();*/



int main()
{
   /* ChangeCursorStatus(false);
    typedef void(*TMenuOption)();

     int ItemCount=4;
     int MenuChoice=1;//holds the position of the cursor
     char key;
      TMenuOption *MenuOption=new
TMenuOption[ItemCount];
      MenuOption[0]=play_Game;
      MenuOption[1]=MenuFun2;
      MenuOption[2]=MenuFun3;
      MenuOption[3]=ExitOption;

           while(1)//infinite loop
           {
               for(int i=0; i<ItemCount;i++)
               {
                   gotoxy(25,7+i);
                   (MenuChoice==i+1)? cout<<"-> ":cout<<"   ";
                   cout<<MenuItems()[i]<<endl;
               }
               key=getch();
               switch(key)
               {
                   case '\r':try
                   {
                       (*MenuOption[MenuChoice-1])();
                   }catch(...)
                   {}
                   break;
                   case 'p':
                        MenuChoice++;
                        if(MenuChoice>ItemCount)
                            MenuChoice=1;
                        break;
                   case 'H': // same but with 'down arrow' and decrement the cursor.
			              MenuChoice--;
			                 if (MenuChoice<1)
				                 MenuChoice=ItemCount;
			             break;
                   case 27: //asscii for escape key
                    try
                    {
                        (*MenuOption[ItemCount-1])();
                    }catch(...){}
                    break;
                   default:
                    if(key>='1'&& key <=char(ItemCount+'0'))//check the rage
                      {
                           try
                           {
                               (*MenuOption[int(key)-'0'-1])();
                           }catch(...){}
                      }
                    }
               }
               delete MenuOption;
        }*/
    obsticle o;
    Bug s;

    Enemy *e1 = &o;
    Enemy *e2 =&s;
    string b;
    o.attack();
    s.attack();
    int p;
    for(int i=0; i<10; i++)
    {
        cout<<"*";
    }
    cout<<"PLEASE ENTER YOUR NAME";
     for(int i=0; i<10; i++)
    {
        cout<<"*";
    }
     cout<<endl<<"NAME: ";
        cin>>b;
        cout<<endl;
        for(int k=0; k<20; k++)
        cout<<"=";
        cout<<endl<<endl;
        cout<<"CHOOSE NUMBER"<<endl<<endl;
        cout<<"1.guidlines\n\n2.PLAY GAME\n"<<endl;
        for(int k=0; k<20; k++)
        cout<<"=";
        cout<<endl<<endl;
        cin>>p;
        switch(p)
        {
        case 1:
            {
                for(int k=0; k<80; k++)
        cout<<"=";
        cout<<endl<<endl;

               cout<<"INFO\n\nThis is a simple 2D snake game with two obstcles\n\nGUIDLINE\n1.The food is the asteric '*'\n\n2.Try not to eat this ^ ~\n\n-This '^' decreases life by -1\n\n-This '~' decreases the tail and score also life if eatten more than twice"<<endl<<endl;
             cout<<"KEYS\n\nUP = arrow key up\nDOWN = arrow key down\nLEFT = arrow key left\nRIGHT = right arrow key\nEXIT = x"<<endl;

             for(int k=0; k<80; k++)
        cout<<"=";
        cout<<endl<<endl;
              break;
            }

        case 2:
            {
                Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(1); //speed;
		e1->attack();
		e2-> attack();


	}

            }


	for(int k=0; k<70; k++)
        cout<<"=";
        cout<<endl<<endl;
        try
        {
            if(gameOver)
            {
               cout<<"      GAMEOVER   "<<b<<endl;
            }
        }catch(...){}

    cout<<endl;
    for(int k=0; k<20; k++)
    {
         cout<<"=";
    }
   cout<<"(c)Vincent  (*_^) ";
    for(int k=0; k<20; k++)
    {
         cout<<"=";
    }
    cout<<endl<<endl;


	return 0;


        }
}
string * MenuItems()
{
    string *item=new string[4];
    item[0]="1.Menu Option";
    item[1]="2.Menu Option";
    item[2]="3.Menu Option";
    item[3]="4.Exit";
    return item;
}
void gotoxy(int xpos, int ypos)
{
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
       scrn.X= xpos; scrn.Y =ypos;
    SetConsoleCursorPosition(hOuput,scrn);
}
void play_Game()
{
    system("cls");
    gotoxy(25,10);
    cout<<"You have selected 1st Menu Option"<<endl;
    getch();
    system("cls");
}
void MenuFun2()
{
    system("cls");
    gotoxy(25,10);
    cout<<"You have selected 2nd Menu Option"<<endl;
    getch();
    system("cls");
}
void MenuFun3()
{
    system("cls");
    gotoxy(25,10);
    cout<<"You have selected 3rd Menu Option"<<endl;
    getch();
    system("cls");
}
void ExitOption()
{
    gotoxy(30,15);
    cout<<"Exiting..."<<endl;
    getch();
    exit(0);
}
void ChangeCursorStatus(bool Visible)
{
	CONSOLE_CURSOR_INFO *c=new CONSOLE_CURSOR_INFO;
	HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);

	if (Visible)
	{
		c->bVisible=TRUE;
		c->dwSize=0;//(0) is invild so the default value is set
	}
	else
	{
		c->bVisible=FALSE;
		c->dwSize=1;//it must be assigned to a valid value
	}

	SetConsoleCursorInfo(h,c);
}
//Created by VINCENT
