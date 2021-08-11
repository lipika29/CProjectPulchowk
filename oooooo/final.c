#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

#define width 20
#define height 20

struct score_save
{
	char score_name[50];
	int score_point;
};

struct score_save a;
int insidescoregoback;
int choose;
char username[50];
int level;
int gameover;//use easily beight universal
int x,y,frogX,frogY,score;//x and y as coordinate of frog
int flag;
int tailX[200],tailY[200];
int CountTail=0;
int gobacktohomepagefromgame;
char t;

void symbol();
void first_page();
void username_page();
void inside_newgame(); //level selection page
void setup();
void draw();
void input();
void logic();
void snakegamemainprogram();
void inside_score();
void easy_score();
void hard_score();
void easy_file(struct score_save);
void hard_file(struct score_save);
void sortandprint(struct score_save [],int);
void after_exit();
void help();

int main()
{
	homepage:
	CountTail=0;	
	first_page();
	system("cls");
	if(choose==1)
	{
		username_page();
		system("cls");
		inside_newgame();
		if(level==1||level==2)
		{
			help();
		    fflush(stdin);
			snakegamemainprogram();
			system("cls");
			symbol();
			printf("\n\n\n");
			printf("\t\t============> SCORE IS %d<=============",score);
			a.score_point=score;
			if(level==1)
			easy_file(a);
			else
			hard_file(a);
			printf("\n\n\t*****************Press 1 to go back to Home page**************\n");
            scanf("%d",&insidescoregoback);
            if(insidescoregoback==1)
            {
            	system("cls");
            	goto homepage;
			}
		
		}
		else
		{
			system("cls");
			goto homepage;
		}
	}
	else if(choose==2)
	{
		inside_score();
		if(insidescoregoback==1)
		{
			system("cls");
			goto homepage;
		}
	}
	else
	after_exit(); 
return 0; 	               	
}

void symbol()
{	
	printf("____________                                 ****      ****                  \n");
	printf("|           |                                *  *     *   *                  \n");
	printf("|    _______|                                *  *    *   *                   \n");
	printf("|   |                                        *  *   *   *                    \n");
	printf("|   |________                                *  *  *   *                     \n");
	printf("|           |  ****            ____________  *  ***   *    _____________     \n");
	printf("|________   |  *  ***********  |  ______  |  *       *     |  ________  |    \n");
	printf("         |  |  *            *  | |     |  |  *  ***   *    |  |_______| |    \n");
	printf("         |  |  *  ********  *  | |     |  |  *  *  *   *   |  __________|    \n");
	printf("_________|  |  *  *      *  *  | |_____|  |  *  *   *   *  |  |              \n");
	printf("|           |  *  *      *  *  |_______   |  *  *    *   * |  |__________    \n");
	printf("|___________|  ****      ****          |__|  ****     **** |_____________|   \n");
}

void first_page()
{
	symbol();
		printf("\n\n\n");
	printf("           ==============> 1)New Game <=============                         \n");
	printf("      ================>    2)View Scores     <============                   \n");
	printf("   ==============>         3)Exit                 <=================         \n");
	printf("\n                     Enter your choice:-");
	scanf("%d",&choose);

}

void username_page()
{   
    symbol();
    printf(" \n                          Hello player!           \n");
    printf("                   Please enter your username:\n\n\t\t\t\t");
	scanf("%s",username);
	strcpy(a.score_name,username);
}

void inside_newgame()
{
	symbol();
	printf("\n                           1)EASY");
	printf("\n                           2)HARD");
	printf("\n                           3)GO BACK");
	printf("\n\n                           Select level:-");
	scanf("%d",&level);
}

void help()
{
	system("cls");
	symbol();
	printf("\n\n\n");
	printf("\t\t\tPress a to move left\n");
	printf("\t\t\tPress d to move right\n");
	printf("\t\t\tPress w to move up\n");
	printf("\t\t\tPress s to move down\n");
	printf("\n\t\t*********PRESS ANY KEY TO START********\n\n\t\t\t\t");
	scanf("%d",&t);
}

void setup()
{
    gameover=0;
    x=width/2;
    y=height/2;
    label1:
    frogX=rand()%20;
    if(frogX==0)
    {
        goto label1;
    }
    label2:
    frogY=rand()%20;
    if(frogY==0)
        goto label2;
    score=0;
}
void draw()
{
    int i,j,k,correction;
    system("cls");
    for(i=0;i<width;i++)
    {
        for(j=0;j<height;j++)
         {
             if(i==0||i==height-1||j==0||j==width-1)
              {
                 printf("*");
              }
             else
              {
                  if(i==x&&j==y)
                  {
                      printf("O");
                  }
                  else if(i==frogX&&j==frogY)
                  {
                      printf("$");
                  }
                  else
                  {
                  	  correction=0;
                  	  for(k=0;k<CountTail;k++)
                  	  {
                  	  	if(i==tailX[k]&&j==tailY[k])
                  	  	{
                  	  		printf("o");
                  	  		correction=1;
							}
					  }
					  if(correction==0)
                      printf(" ");
                  }

              }
         }
         printf("\n");
    }
}
void input()
{
    if(kbhit()) //this is a function under conio.h header file that returns non zero value if any key is pressed and non zero means true in c
    {
        switch(getch())//getch reads the value
        {
            //wasd as corser
            case 'a':
                flag=1;
                break;
            case 's':
                flag=2;
                break;
            case 'd':
                flag=3;
                break;
            case 'w':
                flag=4;
                break;
            case 'x':
                gameover=1;
                break;
        }
    }
}
void logic()
{
	int loop;
	int previousX=tailX[0];
	int previousY=tailY[0];
	int previous2X,previous2Y;
	tailX[0]=x;
	tailY[0]=y;
	
	for(loop=1;loop<CountTail;loop++)//for change of position of tail in each l;oop.
	{
		previous2X=tailX[loop];
		previous2Y=tailY[loop];
		tailX[loop]=previousX;
		tailY[loop]=previousY;
		previousX=previous2X;
		previousY=previous2Y;
	}
	
    switch(flag)
    {
    case 1:
        y--;//going left by "a"
        break;
    case 2:
        x++;//going down "s"
        break;
    case 3:
        y++;//going right by "d"
        break;
    case 4:
        x--;//going up by "y"
        break;
    default:
        break;
    }
    if(x<1||x>width-1||y<1||y>height-1)
    {
        gameover=1;
    }
    for(loop=0;loop<CountTail;loop++)
    {
    	if(x==tailX[loop]&&y==tailY[loop])
    	gameover=1;
	}
    if(x==frogX&&y==frogY)
    {
        label3:
    frogX=rand()%20;
    if(frogX==0)
    {
        goto label3;
    }
    label4:
    frogY=rand()%20; 
    if(frogY==0)
        goto label4;
        score+=2;
        CountTail++; //inncrease the tail no. after consuming the frog
    }
}
void snakegamemainprogram()
{
	char continuegame;
    int late,double_late;
    label5:
    setup();// should remain at its initial position;
    while(!gameover) //gameover initial value is 0 in setup, but after touch in boundary it becomes 1. so !gameover
    {
        draw();
        input();
        logic();
         printf("SCORE:%d",score);
         
      //below loop just makes the exexution slow which makes snake slow.
        if(level==1)
        {
        	for(late=0;late<20000;late++)
            {
	            for(double_late=0;double_late<1000;double_late++)
	            {	
	            }
	        }
         
		    
	    }
	
		if(level==2)
        {
        	for(late=0;late<7000;late++)
            {
	            for(double_late=0;double_late<1000;double_late++)
	            {	
	            }
            }
		}
    }
}

void easy_file(struct score_save b)
{
	FILE *fp1;
	fp1= fopen("easy_score.txt","a");
	fprintf(fp1,"%s\t%d\n",b.score_name,b.score_point);
	fclose(fp1);
}

void hard_file(struct score_save b)
{
	FILE *fp2;
	fp2= fopen("hard_score.txt","a");
	fprintf(fp2,"%s\t%d\n",b.score_name,b.score_point);
	fclose(fp2);
}

void inside_score()
{
    int h;
    symbol();
	highscore:
	printf("\n\n\n");
	printf("\t\t\t1.View HighScore of Level EASY\n");
	printf("\t\t\t2.View HighScore of Level HARD\n");
	printf("\t\t\tENTER YOUR CHOICE:");
	scanf("%d",&h);
	if(h==1)
	{
	system("cls");
	printf("================>SCORE BOARD<================\n");	
	easy_score();
	printf("\n***************Please 1 to go back to home page:*************\n");
    scanf("%d",&insidescoregoback);
    }
	else if(h==2)
	{
	system("cls");
	printf("=================>SCORE BOARD<================\n");	
	hard_score();
	printf("\n****************Please 1 to go back to Home page:*****************\n");
    scanf("%d",&insidescoregoback);
    }
	else
	goto highscore;
}

void easy_score()
{
	int n=0;
	FILE *fp1;
	struct score_save ss[50];
	fp1=fopen("easy_score.txt","r");

	while(!feof(fp1))
	{
		fscanf(fp1,"%s\t%d\n",ss[n].score_name,&ss[n].score_point);
		n++;
	}
	if(n==0)
	{
		printf("No record till date!!!");
		goto easy_exit;
	}
	sortandprint(ss,n);
	easy_exit:
	fclose(fp1);
}

void hard_score()
{
	int n=0;
	FILE *fp2;
	struct score_save ss[50];
	fp2=fopen("hard_score.txt","r");

	while(!feof(fp2))
	{
		fscanf(fp2,"%s\t%d\n",ss[n].score_name,&ss[n].score_point);
		n++;
	}
	if(n==0)
	{
		printf("No record till date!!!");
	    goto hard_exit;
	}
	sortandprint(ss,n);
	hard_exit:
	fclose(fp2);
}

void sortandprint(struct score_save ss[50],int n)
{
	char temp[50];
	int i,j,tep;
	for(i=0;i<n;i++)
	{
		for(j=i+1;j<n;j++)
		{
			if(ss[i].score_point<ss[j].score_point)
			{
				strcpy(temp,ss[i].score_name);
				strcpy(ss[i].score_name,ss[j].score_name);
				strcpy(ss[j].score_name,temp);
				tep=ss[i].score_point;
				ss[i].score_point=ss[j].score_point;
				ss[j].score_point=tep;
			}
		}
	}
	printf("NAME\tSCORE\n");
	for(i=0;i<n;i++)
	{
		printf("%s\t%d\n",ss[i].score_name,ss[i].score_point);
	}
}

void after_exit()
{
	// variables
   char str[20]={'T','h','a','n','k',' ','Y','o','u'};
   int len, place;

   // take input
  // printf("Enter a string: ");
   //scanf("%[^\n]", str);

   // find length of string
   for(len=0; str[len]!='\0'; len++);
   // actual length is length - 1
   len--;
 
   // outer loop for row
   for(int i=0; i<(2*len+1); i++)
   {
     // find the place
     if(i<len) place = i;
     else place = abs(2*len - i);

     // inner loop for column
     for(int j=0; j<=place; j++)
     printf("%c",str[j]); // print
     
     if(i==8)
     {
     	printf("\tFor playing our amazing game. ");
	 }

     printf("\n"); // next line
   }
}




