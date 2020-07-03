#include <bits/stdc++.h>
using namespace std;

#define max_mine 99
#define max_side 25
#define max_move 526 // 25*25-99

int SIDE;
int MINES;

void clear()
	{
		printf("\33[2J\33[1;1H");
	}

bool isvalid(int row,int col)
	{
		return (row>=0)&&(row<SIDE)&&(col>=0)&&(col<SIDE);
	}

bool ismine(int row,int col,char board[][max_side])
	{
		if(board[row][col]=='*')
			return (true);
		else
			return (false);
	}

void make_move(int *x,int *y)
	{
		while(true)
		{
			printf("\nEnter your move: [row] [column] -> ");
			scanf("%d %d", x, y);
            // Check values to make sure they're not larger than the board size.
			if ((*x < SIDE) && (*y < SIDE))
            {
				return;
            }
		}
	}

void printboard(char myboard[][max_side])
	{
		clear();
		printf("\n\n\t\t\t    ");

		for(int i=0;i<SIDE;i++)
		{
			if (i>9)
				printf("%d ",i/10);
			else
				printf("  ");
		}
		
		printf("\n\t\t\t    ");

		for(int i=0;i<SIDE;i++)
			printf("%d ",i%10);

		printf("\n\n");

		for(int i=0;i<SIDE;i++)
		{
			printf("\t\t\t    ");
			for(int j=0;j<SIDE;j++){
				printf("%c ",myboard[i][j]);
			}
			printf(" %2d",i);
			printf("\n");
		}
		return;
	}

int countadjacent(int row,int col,int mines[][2],char realboard[][max_side])
	{
		int count=0;

		if(isvalid(row-1,col)==true)
		{
			if(ismine(row-1,col,realboard)==true)
				count++;
		}

		if(isvalid(row+1,col)==true)
		{
			if(ismine(row+1,col,realboard)==true)
				count++;
		}

		if(isvalid(row,col+1)==true)
		{
			if(ismine(row,col+1,realboard)==true)
				count++;
		}

		if(isvalid(row,col-1)==true)
		{
			if(ismine(row,col-1,realboard)==true)
				count++;
		}

		if(isvalid(row-1,col-1)==true)
		{
			if(ismine(row-1,col-1,realboard)==true)
				count++;
		}

		if(isvalid(row-1,col+1)==true)
		{
			if(ismine(row-1,col+1,realboard)==true)
				count++;
		}

		if(isvalid(row+1,col-1)==true)
		{
			if(ismine(row+1,col-1,realboard)==true)
				count++;
		}

		if(isvalid(row+1,col+1)==true)
		{
			if(ismine(row+1,col+1,realboard)==true)
				count++;
		}

		return (count);

	}

bool playminesuntil(char myboard[][max_side],char realboard[][max_side],int mines[][2],int row,int col,int *moves_left)
	{
		if(myboard[row][col]!='-')
			return false;

		int i,j;
		if(realboard[row][col]=='*')
		{
			myboard[row][col]='*';
			for(i=0;i<MINES;i++)
					myboard[mines[i][0]][mines[i][1]]='*';
				
			printboard(myboard);
			printf ("\nYou lost!\n");
			return (true);
		}

		else
		{
			int count=countadjacent(row,col,mines,realboard);
			(*moves_left)--;

			myboard[row][col]= count+'0';

			if(!count)
			{
		
				if(isvalid(row-1,col)==true)
				{
					if(ismine(row-1,col,realboard)==false)
						playminesuntil(myboard, realboard, mines, row-1, col, moves_left);
				}


				if (isvalid (row+1, col) == true)
				{
					if (ismine (row+1, col, realboard) == false)
						playminesuntil(myboard, realboard, mines, row+1, col, moves_left);
				}

      
				if (isvalid (row, col+1) == true)
				{
					if (ismine (row, col+1, realboard) == false)
						playminesuntil(myboard, realboard, mines, row, col+1, moves_left);
				}

         
				if (isvalid (row, col-1) == true)
				{
					if (ismine (row, col-1, realboard) == false)
						playminesuntil(myboard, realboard, mines, row, col-1, moves_left);
				}

				if (isvalid (row-1, col+1) == true)
				{
					if (ismine (row-1, col+1, realboard) == false)
						playminesuntil(myboard, realboard, mines, row-1, col+1, moves_left);
				}

             
				if (isvalid (row-1, col-1) == true)
				{
					if (ismine (row-1, col-1, realboard) == false)
						playminesuntil(myboard, realboard, mines, row-1, col-1, moves_left);
				}

				if (isvalid (row+1, col+1) == true)
				{
					if (ismine (row+1, col+1, realboard) == false)
						playminesuntil(myboard, realboard, mines, row+1, col+1, moves_left);
				}
				
				if (isvalid (row+1, col-1) == true)
				{
					if (ismine (row+1, col-1, realboard) == false)
						playminesuntil(myboard, realboard, mines, row+1, col-1, moves_left);
				}

			}
			return (false);
		}
	}

void placemines(int mines[][2],char realboard[][max_side])
	{
		bool mark[max_side*max_side];

		memset(mark,false,sizeof(mark));

		for(int i=0;i<MINES;)
		{
			int random=rand()%(SIDE*SIDE);
			int x=random/SIDE;
			int y=random%SIDE;

			if(mark[random]==false) //add mine if not present at position random
			{
				mines[i][0]=x;
				mines[i][1]=y;

				realboard[mines[i][0]][mines[i][1]]='*';
				mark[random]=true;
				i++;
			}
		}
	}


void initialise(char realboard[][max_side],char myboard[][max_side])
	{
		srand(time(NULL)); //initalising random so that same config doesn't arise

		int i,j;
		for(i=0;i<SIDE;i++)
			for(j=0;j<SIDE;j++)
			{
				myboard[i][j]=realboard[i][j]='-';
			}
			return;
	}

void cheatmines (char realboard[][max_side])
{
    printf ("The mines locations are-\n");
    printboard (realboard);
    return;
}

void replacemine(int row,int col,char board[][max_side])
		{
			for(int i=0;i<SIDE;i++)
			{
				for(int j=0;j<SIDE;j++)
				{
					if(board[i][j]!='*')
					{
						board[i][j]='*';
						board[row][col]='-';
						return;
					}
				}

			}
				
		}

void play()
	{
		bool gameover=false;

		char realboard[max_side][max_side],myboard[max_side][max_side];

		int moves_left=SIDE*SIDE-MINES;
		int x,y;
		int mines[max_mine][2]; //stores (x,y) of all mines

		initialise(realboard,myboard);

		placemines(mines,realboard);

		//if you want cheat and win 
		//cheatmines(realboard);
		int currentmoveindex=0;

		while(gameover==false)
		{
			printf ("Current Status of Board : \n");
			printboard(myboard);
			make_move(&x,&y);

			//if first move is mine
			if(currentmoveindex==0)
			{
				if(ismine(x,y,realboard)==true) //first attempt is a mine
					replacemine(x,y,realboard); //replace the mine at that location
			}

			currentmoveindex++;

			gameover = playminesuntil(myboard,realboard,mines,x,y,&moves_left);

			if((gameover==false)&&(moves_left==0))
			{
				printf ("\nYou won !\n");
				gameover=true;
			}
		}


	}


void choosedifficulty()
	{
		clear();
		cout<<"\n\t\t\t\t\t\t\t\tMINESWEEPER";
		cout<<"\n\n\t\t\t\t\t\tCHOOSE DIFFICULTY LEVEL : ";
		cout<<"\n\n\t\t\t\t\t\t0.BEGINNER\n\t\t\t\t\t\t1.INTERMMEDIATE\n\t\t\t\t\t\t2.ADVANCED";
		cout<<"\n\n\t\t\t\t\t\tENTER CHOICE (0-2) : ";
		int choice;
		cin>>choice;
		if(choice==0)
		{
			SIDE=9; 
			MINES=10;
		}
		else
		if(choice==1)
		{
			SIDE=16; 
			MINES=40;
		}
		else
		if(choice==2)
		{
			SIDE=24; 
			MINES=99;
		}
		else	
			exit(0);

	}


int main()
	{
		choosedifficulty();
		play();
		return 0;
	}
