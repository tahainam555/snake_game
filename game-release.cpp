//============================================================================
// Name        : snake.cpp
// Author      : Muhammad Taha
// Version     :
// Copyright   : FAST 23
// Description : SNAKE GAME
//============================================================================
#ifndef TETRIS_CPP_
#define TETRIS_CPP_
#include "util.h"
#include <iostream>
#include<vector>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<string>
#include<sys/wait.h>
#include<fstream>
//#include<stdlib.h>
//#include<stdio.h>
#include<unistd.h>
#include<sstream>
#include<cmath>      // for basic math functions such as cos, sin, sqrt
using namespace std;

	//int snake_lenght = 2 ;  length
	
	int first=1;			//for snake initial position
//	int bx=250 ;
//	int by=300 ;
	int high2=0 ;
	int h1;
	int h2;
	int progress=520;
	int abc = 0 ;			//for first board Display
	int speed = 2 ;
	int rand_hurdles=1 ;
	int mode1= 0 ;
	int mode2= 0 ;
	


void SetCanvasSize(int width, int height)			//Function to set canvas size 
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); 		// set the screen, specified width and height.
	glMatrixMode( GL_MODELVIEW);
	glLoadIdentity();
}

string score ;
int scr=0 ;
//int grid[650][650];
bool over=0 ;
void Bar()
{
	DrawLine(0, 600, 640, 600, 10, colors[WHITE]);
	DrawString( 10, 630, "SCORE= ", colors[MISTY_ROSE]);
	string score2 = to_string(scr);
	DrawString( 110, 630, score2 , colors[MISTY_ROSE]);
	DrawString( 370 , 630, "PROGRESS= ", colors[MISTY_ROSE]);
	DrawLine(520, 635, 640 , 635 , 15, colors[MISTY_ROSE]);
	DrawLine(520, 635, progress , 635 , 5, colors[AQUA]);
	
	if(progress==640)
		progress=520 ;
	
}


void Board()
{
	for(int i=10; i<640 ; i+=10)
	{
		for(int j=10; j<590; j+=10)
		{
//			grid[i][j] ;
			DrawSquare( i , j , 10 , colors[MISTY_ROSE]);
		}
	}
}

void startboard()
{
	DrawSquare(0, 0, 650, colors[AQUA]) ;
	DrawString( 200, 500, "START GAME (press S)", colors[BLACK]);
	DrawString( 200, 450, "NEW GAME (press N)", colors[BLACK]);
	DrawString( 200, 400, "SLOW SPEED (press 1)", colors[BLACK]);
	DrawString( 200, 350, "MEDIUM SPEED (press 2)", colors[BLACK]);
	DrawString( 200, 300, "FAST SPEED (press 3)", colors[BLACK]);
	DrawString( 225, 250, "MODE 1 (press W)", colors[BLACK]);
	DrawString( 225, 200, "MODE 2 (press M)", colors[BLACK]);
	DrawString( 225, 150, "EXIT (press esc)", colors[BLACK]);
}


void overboard()
{
	mode1 = 0 ;
	mode2 = 0 ;
	
	DrawSquare(0, 0 , 650 , colors[RED]);
	DrawString( 225, 400, "GAME OVER!!!", colors[MISTY_ROSE]);
	string score = to_string(scr);
	DrawString( 210, 350 , " YOUR SCORE  = " , colors[MISTY_ROSE]);
	DrawString( 420, 350 , score , colors[MISTY_ROSE]);
	DrawString( 175, 250 , "Press B to go back to menu " , colors[MISTY_ROSE]);
	
	if(scr>=high2)
	{
		DrawString( 200, 300 , " SNAKE MASTERRRRR " , colors[MISTY_ROSE]);	
	}
	else
	{
		string highscore = to_string(high2);
		DrawString( 210, 300 , " HIGH SCORE  = " , colors[MISTY_ROSE]);
		DrawString( 420, 300 , highscore , colors[MISTY_ROSE]);
	}
	//exit(1);
}


int snake[500][2] ;
int length=3 ;
int snake_strtx = 250 ;
int snake_strty = 250 ;
int next_pos=0;
int h = 0 ;
int g = 0 ;
int aaa=1 ;
void Snake()				//Snake ki initial position
{		
	for(int i=0 ; i<length ; i++)
	{
		snake[i][0]=snake_strtx+next_pos;			//next pos for tail
		snake[i][1]=snake_strty;
		next_pos+=10;
	}
}	
void move()
{	
	
	DrawCircle(snake[0][0]+5, snake[0][1]+5, 5, colors[5]);
	
	for(int i=1; i<length ; i++)
	{
		DrawSquare(snake[i][0] , snake[i][1] , 10, colors[GREEN]);
		
	}
	
      if(aaa!=0)				//Snake movement 
      {
	for(int i=length-1 ; i>0 ; i--)
	{
		snake[i][0]=snake[i-1][0] ;
		snake[i][1]=snake[i-1][1] ;
	}
      }	
	if(aaa==1)
		snake[0][0]-=10;
	else if(aaa==2)
		snake[0][0]+=10;
	else if(aaa==3)
		snake[0][1]+=10;
	else if(aaa==4)
		snake[0][1]-=10;
		
	for(int i=0 ; i<length ; i++)			//Bounding snake in the canvas
	{
		if(snake[i][0]>630)
		{
			snake[i][0]=10 ;
		}
		else if(snake[i][0]<1)
		{
			snake[i][0]=630 ;
		}
		else if(snake[i][1]>580)
		{
			snake[i][1]=0 ;
		}
		else if(snake[i][1]<1)
		{
			snake[i][1]=580 ;
		}
		
	}	
		
	for(int i=1 ; i<length ; i++)			//Head and tail colission
	{
		if(snake[0][0]==snake[i][0]&&snake[0][1]==snake[i][1])
		{
			over = 1 ;
		}
	}	
	
}
int ddd=0 ;
int foodx[5] ;
int foody[5] ;
int hurdlex[25] ;
int hurdley[25] ;
int hurdlex2[25] ;
int hurdley2[25] ;
int foodpowerx ;
int foodpowery ;
int del=0 ;


void food()
{
//	glutPostRedisplay();
//	glutTimerFunc(1 / FPS , food , 0);	
	
      if(over==0)
      {				//MAKING FOOD
	for(int i=0 ; i<5 ; i++)
	{
	        
		if(ddd%100==0)
		{
			foodx[i] = 10+(rand() % 62)*10 ;
			foody[i] = 10+(rand() % 58)*10 ; 
		}
		
		if((foody[i-1]!=foody[i])||(foodx[i-1]!=foodx[i]))
		{
			DrawSquare(foodx[i] , foody[i] , 10 , colors[GREEN]);
		}
		else
			i-- ;
			
			
		if(snake[0][0]==foodx[i] && snake[0][1]==foody[i])
		{
			length++ ;
			scr+=10 ;
//			scr2=scr ;
//			DrawSquare(foodx[i] , foody[i] , 10 , colors[GREEN]);
//			ddd=0 ;
			foodx[i]=700+del ;
			del+=10 ;
			foody[i]=700+del ;
			del+=10 ;
			progress+=2 ;
			
//			glutPostRedisplay();
		}
		
		

	}
	
         if(rand_hurdles==1)
         {				//MAKING HURDLES	
	if(ddd%200==0)
	{	
		hurdlex[0]=100+(rand()%50)*10 ;
		hurdley[0]=10+(rand()%58)*10 ;
		hurdlex2[0]=10+(rand()%60)*10 ;
		hurdley2[0]=100+(rand()%48)*10 ;
		
	}	
	for(int i=0 ; i<10 ; i++)
	{
	     
		hurdlex[i+1]=hurdlex[i]-10 ;
		hurdley[i+1]=hurdley[i] ;
		hurdlex2[i+1]=hurdlex2[i] ;
		hurdley2[i+1]=hurdley2[i]-10 ;
	     
//	     if((hurdlex[i]!=snake[i][0]&&hurdley[i]!=snake[i][1])||(hurdlex2[i]!=snake[i][0]&&hurdley2[i]!=snake[i][1]))
//	     {		
		DrawSquare(hurdlex[i] , hurdley[i] , 10 , colors[RED]);
		DrawSquare(hurdlex2[i] , hurdley2[i] , 10 , colors[RED]);
//		DrawLine(hurdlex, hurdley , hurdlex+100 , hurdley , 20 , colors[RED]) ;
//		DrawLine(hurdlex2, hurdley2 , hurdlex2 , hurdley2+100 , 20 , colors[RED]) ;
//	     }	
		if((snake[0][0]==hurdlex[i]&&snake[0][1]==hurdley[i])||(snake[0][0]==hurdlex2[i]&&snake[0][1]==hurdley2[i]))
		{
//			scr=0 ;
			over = 1 ;
			

		}
	}
	
        } 
        else if(rand_hurdles==0)
        {
        	hurdlex[0] =200 ;
        	hurdley[0] =350 ;
        	hurdlex2[0]=200 ;
	hurdley2[0]=230 ;
        	
        	for(int i=0 ; i<25 ; i++)
	{
		hurdlex[i+1]=hurdlex[i]+10 ;
		hurdley[i+1]=hurdley[i] ;
		hurdlex2[i+1]=hurdlex2[i]+10 ;
		hurdley2[i+1]=hurdley2[i] ;
	     		
		DrawSquare(hurdlex[i] , hurdley[i] , 10 , colors[RED]);
		DrawSquare(hurdlex2[i] , hurdley2[i] , 10 , colors[RED]);
		
		if((snake[0][0]==hurdlex[i]&&snake[0][1]==hurdley[i])||(snake[0][0]==hurdlex2[i]&&snake[0][1]==hurdley2[i]))
		{
			over = 1 ;
		}
	
	}
        	
        	
        }
        
         ddd++;
      }
}
long int ccc=200 ;	
int powerfoodx[1];
int powerfoody[1];

				//MAKING POWER FOOD
void powerfood()
{	
	if(ccc%400==0)
	{
		powerfoodx[0] = 10 +(rand()%58)*10 ;
		powerfoody[0] = 10 +(rand()%58)*10 ;
		ccc=1;
	}
	if(ccc>=100)
	{
		powerfoodx[0]=20000;
		powerfoody[0]=20000;
	}
	DrawSquare(powerfoodx[0] , powerfoody[0] , 10 , colors[BLUE]);
	
	if((snake[0][0]==powerfoodx[0])&&(snake[0][1]==powerfoody[0]))
	{
		scr+=20;
		length++;
		progress+=2;
		powerfoodx[0]=20000;
		powerfoody[0]=20000;
	}
	
		
	ccc++;
				

      
}

int max=scr ;
void highest()				//storing high score using file handling
{	

//                 cout<<" The score is " << scr << endl;
	
	ifstream file ;
	file.open("high.txt") ;
	file >> high2 ;           // Highest Before updation 
	
//	cout<<" VALUE FROM FILE IS "<< high2 << endl;
	
	file.close();   
	
	if(high2<scr)
	{
		fstream File;                       
	   	File.open("high.txt", ios::out);                
	   	if (!File) 
	   	{                            
			cout<<" Error while creating the file ";          
	  	}
	  	else 
	  	{
//			cout<<"File created and High Score written to file";    
		    	File<< scr <<" \n ";          // High Score after updation 
		        	high2=scr ;
		        	File.close();                   
		}
	}
	
    	
}


//void DrawSnake()
//{
	
//	DrawCircle(snake[0][0]+5, snake[0][1]+5, 6, colors[5]);
	
//	for(int i=1; i<length ; i++)
//	{
//		DrawSquare(snake[i][0], snake[i][1], 10, colors[GREEN]);
//	}
//}




//double startx=320,starty=400;
				//MAJOR DISPLAY FUNCTION
void Display()
{
    

	glClearColor(0/*Red Component*/, 0/*Green Component*/, 0.1/*Blue Component*/, 0 /*Alpha component*/);
	glClear(GL_COLOR_BUFFER_BIT);   //Update the colors
    
     
	if (abc==0)
	{
		startboard();
	}
	else if(over==0)
	{	     
		Bar();
		if(first==1)
		{
			Snake();
			first=2 ;
		}
		     
		Board();
		     
		move();
		food();
		powerfood();
		     
	}
	else if(over==1)
	{
	     
		highest();
		overboard();
	     	
	}
    
    
//	DrawSnake();
   
   
	glutSwapBuffers(); // do not modify this line..
}


				//NON PRINTABLE KEYS 

void NonPrintableKeys(int key, int x, int y) 
{
	if (key == GLUT_KEY_LEFT  ) 
	{
			
	//	snake_strtx-=10 ;
	//	h-=10;
		if(aaa!=2)
			aaa=1;
	      
	} 
	else if (key == GLUT_KEY_RIGHT  ) 
	{	
	//	h+=10 ;
	//	snake_strtx+=10 ;
	    	if(aaa!=1)
	    		aaa=2 ;
	} 
	else if (key == GLUT_KEY_UP)  
	{
	//	snake_strty+=10 ;
	//	g+=10 ;
		if(aaa!=4)
			aaa=3 ;
	}
	else if (key == GLUT_KEY_DOWN) 
	{
	//	snake_strty-=10 ;
	//	g-=10 ;	
		if(aaa!=3)
			aaa=4 ;
	}
	    

	    // This function calls the Display function to redo the drawing. 
	     glutPostRedisplay();

}

				//Printable key function
void PrintableKeys(unsigned char key, int x, int y) 
{
	if (key == KEY_ESC) 
	{
        		exit(1); 
    	}
    	if (key == 'S' || key=='s') 
    	{
		if(over==0)
			abc=1 ;
	}
	
    	if (key == 'P' || key=='p') 
   	{
		abc = 0 ;
		aaa = 0;
    	}
    	
    	if (key == 'M' || key=='m') 
    	{
		if(mode1!=1)
		{
			rand_hurdles=0 ;
			mode2=1 ;
		}	
	
    	}
    	
    	if (key == 'W' || key=='w') 
    	{
		if(mode2!=1)
		{
			rand_hurdles=1 ;
			mode1=1 ;
		}	
	
    	}
    
    	if (key == 'B' || key=='b') 
    	{
		abc = 0 ;
    	}
    
     	if (key == 'N' || key=='n') 
     	{
		first=1;
		progress=520;
		abc = 1 ;			//for first board Display
		speed = 2 ;
		scr=0 ;
		length=3 ;
		snake_strtx = 250 ;
		snake_strty = 250 ;
		next_pos=0;
		h = 0 ;
		g = 0 ;
		aaa=1 ;
		over = 0 ;
		ddd = 0 ;
		ccc = 200 ;
    	}
    
    	if (key == '1') 
    	{
		speed=1;
    	}
    	
    	else if (key == '2') 
    	{
		speed=2;
    	}
    	
    	else if (key == '3')
    	{
		speed=3;
    	}	
    
    
    	glutPostRedisplay();
}

				//Timer Function

void Timer(int m) {

	glutPostRedisplay();

    
	    if(speed==1)
	    	glutTimerFunc(700 / FPS , Timer , 0);
	    else if(speed==2)
	    	glutTimerFunc(500 / FPS , Timer , 0);
	    else if(speed==3)
	    	glutTimerFunc(300 / FPS , Timer , 0);		
	//    else if(scr>=500)
	//    	glutTimerFunc(400 / FPS , Timer , 0);		
    	    
}

				//Main Function
int main(int argc, char*argv[]) {
    srand(time(0));
    //h1=rand()%650;
    //h2=rand()%650;
    foodpowerx=2000 ;
    foodpowery=2000 ;
//    ccc=200 ;
    
    int width = 650, height = 650; // window size to be 650 x 650
    InitRandomizer(); // random number generator...
    glutInit(&argc, argv); // graphics library...

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); //color display mode
    glutInitWindowPosition(50, 50); // initial position of our window
    glutInitWindowSize(width, height); // size of our window
    glutCreateWindow("Taha's Snake"); // the title of our game 
    SetCanvasSize(width, height); // number of pixels
    
    

    glutDisplayFunc(Display); // Calling the display function
    glutSpecialFunc(NonPrintableKeys); // call for non-printable ASCII characters
    glutKeyboardFunc(PrintableKeys); // call for printable ASCII characters
// call our Timer function after 1000.0/FPS milliseconds
    glutTimerFunc(5.0 / FPS, Timer, 0);
//    glutTimerFunc(50000 / FPS, food , 0);
	       


    glutMainLoop();
    return 1;
}
#endif /* Snake Game */

