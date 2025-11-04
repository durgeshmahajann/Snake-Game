#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>




#define TR 15
#define TC 75
#define LEN 10
#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'

char array[TR][TC];
int foodx,foody,score;
char moovingDirection = RIGHT;

struct node
{
  int x;
  int y;
  struct node* next;
};
struct node* head;
struct node* tail;


void displayArray()
{
 int i,j;
 printf("\t\t\t\t    SNAKE GAME \n");
 for(i=0;i<TR;i++)
 {
	printf("  ");
	for(j=0;j<TC;j++)
	{
		printf("%c",array[i][j]);
	}
 printf("\n");
 }
}
void initializedArray()
{
	int i,j;
	for(i=0;i<TR;i++)
	for(j=0;j<TC;j++)
	array[i][j] = ' ';

	//set the border.
	for(i=0;i<TC;i++)
	{
		array[0][i] = '*';//top
		array[TR-1][i] = '*';//bottom
	}
	for(i=0;i<TR;i++)
	{
		array[i][0] = '*';//left
		array[i][TC-1] = '*';//right
	}

}
void insert(int x,int y)
{
struct node *temp;
	temp = (struct node*) malloc(sizeof(struct node));
	temp->x = x;
	temp->y = y;
	array[temp->x][temp->y] = '=';
	temp->next = NULL;

	if(head == NULL)
	{
		head = temp;
		tail = temp;
		return;
	}
	tail->next = temp;
	tail = temp;
}
void insertFood()
{
	struct node *t;
	t = (struct node*) malloc(sizeof(struct node));
	switch(moovingDirection)
	{
	case UP   : t->x = head->x-1;
		    t->y = head->y;
		    break;
	case DOWN : t->x = head->x+1;
		    t->y = head->y;
		    break;
	case RIGHT : t->x = head->x;
		     t->y = head->y+1;
		     break;
	case LEFT : t->x = head->x;
		    t->y = head->y-1;
		    break;
	}
	array[t->x][t->y] = '=';
	t->next = head;
	head = t;
}

void resetSnake()
{
	int i;
	struct node *temp;
	head = NULL;
	tail = NULL;
	initializedArray();

	foodx=0;
	foody=0;
	score=0;
	for(i=LEN-1;i>=0;i--)
	{
		insert(TR/2,(TC/2)-(LEN/2)+i);
	}
}

void updateSnake()
{
	struct node *p;
	insertFood();
	p=head;
	while(p->next->next != NULL)
	{
		p = p->next;
	}
	p->next = NULL;
	array[tail->x][tail->y] = ' ';
	tail = p;
}

int isCollision()
{
	struct node *p;
	p=head->next;
	while(p!=NULL)
	{
		if(p->x == head->x && p->y==head->y)
		return 1;
		p=p->next;
	}
	if(head->x == 0 || head->x == TR-1 || head->y == 0 || head->y == TC-1)
		return 1;
	else
		return 0;
}
int getRandomNumber()
{
	srand(time(0));
	return rand();
}
void generateFood()
{
	if(foodx == 0 && foody==0)
	array[foodx][foody] = '*';
	else
	array[foodx][foody] = '=';
	do
	{
		foodx = getRandomNumber()%TR;
		foody = getRandomNumber()%TC;
	}while(foody==0 || foody==TC-1 || foodx==0 || foodx==TR-1);

	array[foodx][foody] = '@';
}

void displayMenu()
{
	printf("         _____                               \n");
	printf("        |     |                                             _______________\n");
	printf("        |  w  |                                            |  SCORE : %4d |\n",score);
	printf("   _____|_____|_____                                       |_______________|\n");
	printf("  |     |     |     |                                        ______________\n");
	printf("  |  a  |  s  |  d  |                                       |  Q : QUIT    |\n");
	printf("  |_____|_____|_____|                                       |______________|\n");
	printf("Enter Choice:- ");

}

void play()
{
char t;

	clrscr();
	//set initial position of snake
	resetSnake();

	displayArray();
	moovingDirection = RIGHT;
	generateFood();
	do
	{
		while(!kbhit() && isCollision()!=1)
		{
			delay(500);
			if(head->x==foodx && head->y==foody)
			{
				score += 100;
				insertFood();
				generateFood();
			}
			updateSnake();
			clrscr();
			displayArray();
			displayMenu();
		}
		if(isCollision()==1)
		{
			break;
		}
		scanf("%c",&t);
		if(moovingDirection==UP && t==DOWN||
		   moovingDirection==DOWN && t==UP||
		   moovingDirection==RIGHT && t==LEFT||
		   moovingDirection==LEFT && t==RIGHT)
		   {}
		else
		moovingDirection = t;

	}while(moovingDirection != 'q');
	clrscr();
	displayArray();
	printf("\t\t\t\t ____________\n");
	printf("\t\t\t\t| Game Over. |\n");
	printf("\t\t\t\t|____________|\n");
	printf("\t\t\t\t ______________\n");
	printf("\t\t\t\t| Score = %4d |\n",score);
	printf("\t\t\t\t|______________|\n\n");
	printf("\t\t\t\tPress Any Key To Continue...\n");
	getch();

}
void main()
{
int choice;
	do
	{
		clrscr();
		printf("\t\t\t =====================================\n");
		printf("\t\t\t =                                   =\n");
		printf("\t\t\t =    Welcome to the Snake Game.     =\n");
		printf("\t\t\t =   ----------------------------    =\n");
		printf("\t\t\t =====================================\n\n");

	       printf("\t\t\t ==========\n");
	       printf("\t\t\t = 1.Play =\n");
	       printf("\t\t\t ==========\n\n");
	       printf("\t\t\t ==========\n");
	       printf("\t\t\t = 2.Exit =\n");
	       printf("\t\t\t ==========\n\n");
	       printf("\t\t\tEnter Your Choice:-\n");
	       scanf("%d",&choice);

	       switch(choice)
	       {
	       case 1:play();
	       break;
	       case 2:
	       break;
	       default:printf("ERROR : Invalid Choice.\n");
	       }
	}while(choice != 2);
	getch();
}
