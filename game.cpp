//============================================================================
// Name        : .cpp
// Author      : Muhammad raffay hassan
// Copyright   : (c) Reserved
// Description : Basic 2D game of Rush Hour...
//============================================================================
#ifndef RushHour_CPP_
#define RushHour_CPP_
#include "util.h"
#include <GL/glut.h>
#include <iostream>
#include<string>
#include<cmath> // for basic math functions such as cos, sin, sqrt
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
//============================================================================
// Global variables
int xI = 0 , yI = 800 , x2 = 300 , y2 = 10 , x3 = 600, y3 = 65,x4 = 790, y4 = 410, x5 = 800 ,y5 = 810 ;
int vy2 = 4 , vx3 = 4 , vx4 = 4 , vx5 = 4 ;
int pas1_x = 50, pas1_y = 670, pas2_x = 60, pas2_y = 100, pas3_x = 500, pas3_y = 530;
int a=190,b=290,c=360,d=460,e=600,f=500,g=670,h=800,i=100,j=700,k=900,l=50,m=1000,n=590; 
int timer , timer_1 ;
int width=1020 , height=840 ;
int finalX=950 , finalY=840 ;
int counter = 0 , score = 0 , lastSpeedIncreaseScore = 0;;
int speedIncrement = 2; 
bool occupied = false , init = true , destinationReached = false;
char taxi_color = 'r';
 //*****************************************************************************************************************************
  
// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}
void loadLeaderboard(vector<pair<string, int>>& leaderboard, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < 10; ++i) {
            string name;
            int score;
            if (file >> name >> score) {
                leaderboard[i] = make_pair(name, score);
            } else {
                leaderboard[i] = make_pair("", 0);
            }
        }
        file.close();
    }
}

void saveLeaderboard(const vector<pair<string, int>>& leaderboard, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& entry : leaderboard) {
            if (!entry.first.empty()) {
                file << entry.first << " " << entry.second << endl;
            }
        }
        file.close();
    }
}

void displayLeaderboard(const vector<pair<string, int>>& leaderboard) {
    cout << "Leaderboard:" << endl;
    for (const auto& entry : leaderboard) {
        if (!entry.first.empty()) {
            cout << entry.first << ": " << entry.second << endl;
        }
    }
}

//Draws the taxi color 
void drawCar() {
		
	if (taxi_color == 'y' || taxi_color =='Y')
	{	
	DrawRoundRect(xI,yI,60,20,colors[YELLOW],10);
	DrawCircle(xI+9,yI,10,colors[BLACK]);
	DrawCircle(xI+50,yI,10,colors[BLACK]);
	}
	if (taxi_color == 'r' || taxi_color =='R')
	{
	DrawRoundRect(xI,yI,60,20,colors[RED],10);
	DrawCircle(xI+9,yI,10,colors[BLACK]);
	DrawCircle(xI+50,yI,10,colors[BLACK]);
	}
}
void drawPinkCar() 
{
    // Draw the main body of the car
    DrawRoundRect(x2, y2, 60, 20, colors[PINK], 10);

    // Draw the wheels
    DrawCircle(x2 + 9, y2, 10, colors[BLACK]);
    DrawCircle(x2 + 50, y2, 10, colors[BLACK]);
}
void UpdatePinkCarPosition() {
    y2 += vy2;

    // Check for boundary collisions and reverse direction if necessary
    if (y2 < 10 || y2 > 300) {
        vy2 = -vy2;
    }
    // Increase speed after every 20 points
      if (score >= lastSpeedIncreaseScore + 20) {
        if (vy2 > 0) {
            vy2 += 2; 
        } else {
            vy2 -= 2; 
        }
        lastSpeedIncreaseScore = score;
    }
}
void drawIndigoCar() 
{
    // Draw the main body of the car
    DrawRoundRect(x3, y3, 60, 20, colors[INDIGO], 10);

    // Draw the wheels
    DrawCircle(x3 + 9, y3, 10, colors[BLACK]);
    DrawCircle(x3 + 50, y3, 10, colors[BLACK]);

}
void UpdateIndigoCarPosition() {
    x3 += vx3;

    // Check for boundary collisions and reverse direction if necessary
    if (x3 < 600 || x3 > 800) {
        vx3 = -vx3;
    }
  // Increase speed after every 20 points
      if (score >= lastSpeedIncreaseScore + 20) {
        if (vx3 > 0) {
            vx3 += 2; 
        } else {
            vx3 -= 2; 
        }
        lastSpeedIncreaseScore = score;
    }
}
void drawCyanCar() 
{
    // Draw the main body of the car
    DrawRoundRect(x4, y4, 60, 20, colors[DARK_CYAN], 10);

    // Draw the wheels
    DrawCircle(x4 + 9, y4, 10, colors[BLACK]);
    DrawCircle(x4 + 50, y4, 10, colors[BLACK]);

}
void UpdateCyanCarPosition() {
    x4 += vx4;

    // Check for boundary collisions and reverse direction if necessary
    if (x4 < 550 || x4 > 790) {
        vx4 = -vx4;
    }
// Increase speed after every 20 points
    if (score >= lastSpeedIncreaseScore + 20) {
        if (vx4 > 0) {
            vx4 += 2; 
        } else {
            vx4 -= 2; 
        }
        lastSpeedIncreaseScore = score;
    }
}
void drawVioletCar() 
{
    // Draw the main body of the car
    DrawRoundRect(x5, y5, 60, 20, colors[VIOLET], 10);

    // Draw the wheels
    DrawCircle(x5 + 9, y5, 10, colors[BLACK]);
    DrawCircle(x5 + 50, y5, 10, colors[BLACK]);
    
}
void UpdateVioletCarPosition() {
    x5 += vx5;

    // Check for boundary collisions and reverse direction if necessary
    if (x5 < 650 || x5 > 800) {
        vx5 = -vx5;
    }
// Increase speed after every 20 points
    if (score >= lastSpeedIncreaseScore + 20) {
        if (vx5 > 0) {
            vx5 += 2; 
        } else {
            vx5 -= 2; 
        }
        lastSpeedIncreaseScore = score;
    }
}
void drawobj() {

        DrawRoundRect(a,b,0,0,colors[RED],40);  	
	DrawRoundRect(c,d,0,0,colors[BLUE],40);  
        DrawRoundRect(e,f,0,0,colors[LIME_GREEN],40);  
        DrawRoundRect(i,j,0,0,colors[GAINSBORO],40);  
        DrawRoundRect(k,l,0,0,colors[TEAL],40);        
	DrawRoundRect(m,n,0,0,colors[BURLY_WOOD],40);
}
void drawPassengers() {
    // Draw first passenger
    DrawCircle(pas1_x, pas1_y, 10, colors[WHITE]);
    DrawLine(pas1_x, pas1_y, pas1_x, pas1_y - 50, 2, colors[WHITE]); // Body
    DrawLine(pas1_x, pas1_y - 50, pas1_x - 10, pas1_y - 70, 2, colors[WHITE]); // Left arm
    DrawLine(pas1_x, pas1_y - 50, pas1_x + 10, pas1_y - 70, 2, colors[WHITE]); // Right arm

    // Draw second passenger
    DrawCircle(pas2_x, pas2_y, 10, colors[WHITE]);
    DrawLine(pas2_x, pas2_y, pas2_x, pas2_y - 30, 2, colors[WHITE]); // Body
    DrawLine(pas2_x, pas2_y - 30, pas2_x - 10, pas2_y - 50, 2, colors[WHITE]); // Left arm
    DrawLine(pas2_x, pas2_y - 30, pas2_x + 10, pas2_y - 50, 2, colors[WHITE]); // Right arm

    // Draw third passenger
    DrawCircle(pas3_x, pas3_y, 10, colors[WHITE]);
    DrawLine(pas3_x, pas3_y, pas3_x, pas3_y - 30, 2, colors[WHITE]); // Body
    DrawLine(pas3_x, pas3_y - 30, pas3_x - 10, pas3_y - 50, 2, colors[WHITE]); // Left arm
    DrawLine(pas3_x, pas3_y - 30, pas3_x + 10, pas3_y - 50, 2, colors[WHITE]); // Right arm
}
bool isValidPosition(int x, int y) {
    // Check collision with buildings
    if ((x >= 400 && x <= 450 && y >= 20 && y <= 180) ||      // Building 1
        (x >= 400 && x <= 450 && y >= 400 && y <= 520) ||     // Building 2
        (x >= 320 && x <= 560 && y >= 350 && y <= 390) ||     // Building 3
        (x >= 700 && x <= 900 && y >= 500 && y <= 540) ||     // Building 4
        (x >= 740 && x <= 900 && y >= 500 && y <= 540) ||     // Building 5
        (x >= 200 && x <= 280 && y >= 600 && y <= 720) ||     // Building 6
        (x >= 480 && x <= 800 && y >= 700 && y <= 740) ||     // Building 7
        (x >= 720 && x <= 780 && y >= 660 && y <= 740) ||     // Building 8
        (x >= 320 && x <= 520 && y >= 350 && y <= 390) ||     // Building 9
        (x >= 100 && x <= 140 && y >= 140 && y <= 260) ||     // Building 10
        (x >= 0 && x <= 80 && y >= 0 && y <= 80) ||           // Building 11
        (x >= 700 && x <= 820 && y >= 260 && y <= 380) ||     // Building 12
        (x >= 700 && x <= 720 && y >= 100 && y <= 220) ||     // Building 13
        (x >= 40 && x <= 160 && y >= 440 && y <= 560) ||      // Building 14
        (x >= 100 && x <= 220 && y >= 0 && y <= 80)) {        // Building 15
        return false; // Invalid position due to collision with a building
    }

    // Check collision with objects
    if ((x >= a - 20 && x <= a + 20 && y >= b - 20 && y <= b + 20) || // Object 1
        (x >= c - 20 && x <= c + 20 && y >= d - 20 && y <= d + 20) || // Object 2
        (x >= e - 20 && x <= e + 20 && y >= f - 20 && y <= f + 20) || // Object 3
        (x >= i - 20 && x <= i + 20 && y >= j - 20 && y <= j + 20) || // Object 4
        (x >= k - 20 && x <= k + 20 && y >= l - 20 && y <= l + 20) || // Object 5
        (x >= m - 20 && x <= m + 20 && y >= n - 20 && y <= n + 20)) { // Object 6
        return false; // Invalid position due to collision with an object
    }

    return true; // Position is valid
}

void randomizePassengerPosition(int &pas_x, int &pas_y, int width, int height) {
    int attempts = 0;
    const int max_attempts = 1000;
    do {
        pas_x = 20 + rand() % (width - 40);  // Generate random x within boundaries avoiding edges
        pas_y = 20 + rand() % (height - 40); // Generate random y within boundaries avoiding edges
        attempts++;
    } while (!isValidPosition(pas_x, pas_y) && attempts < max_attempts);

    if (attempts == max_attempts) {
        // Handle the case where a valid position was not found after many attempts
        // For simplicity, setting to a default valid position
        pas_x = 100;
        pas_y = 100;
    }
}

void PassengerFunc() {
    if (!occupied) {
        if (abs(pas1_x - xI) <= 40 && abs(pas1_y - yI) <= 40 && isValidPosition(pas1_x, pas1_y)) {
            DrawSquare(pas1_x, pas1_y, 20, colors[WHITE]);
            cout << "PASSENGER 1 PICKED" << endl;
            occupied = true; // Set occupied status
            finalX = 950; 
            finalY = 840;
           
            // Randomize passenger 1 position until a valid position is found
            randomizePassengerPosition(pas1_x, pas1_y, width, height);
        } else if (abs(pas2_x - xI) <= 40 && abs(pas2_y - yI) <= 40 && isValidPosition(pas2_x, pas2_y)) {
            DrawSquare(pas2_x, pas2_y, 20, colors[WHITE]);
            cout << "PASSENGER 2 PICKED" << endl;
            occupied = true; // Set occupied status
            finalX = 950; 
            finalY = 840;
             
            // Randomize passenger 2 position until a valid position is found
            randomizePassengerPosition(pas2_x, pas2_y, width, height);
        } else if (abs(pas3_x - xI) <= 40 && abs(pas3_y - yI) <= 40 && isValidPosition(pas3_x, pas3_y)) {
            DrawSquare(pas3_x, pas3_y, 20, colors[WHITE]);
            cout << "PASSENGER 3 PICKED" << endl;
            occupied = true; // Set occupied status
            finalX = 950; 
            finalY = 840;

            // Randomize passenger 3 position until a valid position is found
            randomizePassengerPosition(pas3_x, pas3_y, width, height);
        }
    }
}

void DropOffPassenger() {
    const int detectionRange = 50;

    // Check if the car is within the detection range of the destination
    if (occupied && abs(finalX - xI) <= detectionRange && abs(finalY - yI) <= detectionRange) {
        cout << "PASSENGER DROPPED. Score: " << score + 10 << endl;
        score += 10;
        occupied = false;
        destinationReached = true;
    } else {
        destinationReached = false;
    }
}

void DestinationReached() {
    const int detectionRange = 50;

    // Check if the car is within the detection range of the destination
    if (abs(finalX - xI) <= detectionRange && abs(finalY - yI) <= detectionRange) {
        cout << "Destination reached." << endl;
    } else {
        cout << "Destination not reached." ;
    }
}

void Collision() {
    // For detection of collision with obstacles
    if ((xI >= a - 40 && xI <= a + 40 && yI >= b - 40 && yI <= b + 40) ||
        (xI >= c - 40 && xI <= c + 40 && yI >= d - 40 && yI <= d + 40) ||
        (xI >= e - 40 && xI <= e + 40 && yI >= f - 40 && yI <= f + 40) ||
        (xI >= g - 40 && xI <= g + 40 && yI >= h - 40 && yI <= h + 40) ||
        (xI >= i - 40 && xI <= i + 40 && yI >= j - 40 && yI <= j + 40) ||
        (xI >= k - 40 && xI <= k + 40 && yI >= l - 40 && yI <= l + 40) ||
        (xI >= m - 40 && xI <= m + 40 && yI >= n - 40 && yI <= n + 40)) {
        
        xI = 0;
        yI = 800;
        score -= 1;
       //cout<<"collision happened" ;
       
    } /*else {
        cout << "No collision with obstacles" << endl;
    }*/

    // For detection of collision with passengers
     if (occupied) {
        // Calculate the center of the car
        float carCenterX = xI + 30; // Assuming the car's width is 60

        // Check for collision with each passenger
        if (abs(carCenterX - pas1_x) < 30 && abs(yI - pas1_y) < 30 ||
            abs(carCenterX - pas2_x) < 30 && abs(yI - pas2_y) < 30 ||
            abs(carCenterX - pas3_x) < 30 && abs(yI - pas3_y) < 30) {
            // Collision happened with a passenger
            xI = 0; // Reset car position
            yI = 800;
            score -= 5; // Update score
            // Additional collision handling code if needed
        }
    }

    // For detection of collision with moving cars
    if (((x2 - xI) * (x2 - xI) + (y2 - yI) * (y2 - yI) <= 3 * 3) ||
        ((x3 - xI) * (x3 - xI) + (y3 - yI) * (y3 - yI) <= 10 * 10) ||
        ((x4 - xI) * (x4 - xI) + (y4 - yI) * (y4 - yI) <= 10 * 10) ||
  
      ((x5 - xI) * (x5 - xI) + (y5 - yI) * (y5 - yI) <= 10 * 10)) {
        
        xI = 0;
        yI = 800;
        score -= 3;
        //cout<<"collision happened" ;
    }/* else {
        cout << "No collision with moving cars" << endl;
    }*/
      // For detection of collision with newly added squares
    int newSquares[][2] = {
        {400, 20}, {400, 60}, {400, 100}, {400, 140}, {400, 180},
        {400, 400}, {400, 440}, {400, 480}, {400, 520},
        {320, 350}, {360, 350}, {400, 350}, {440, 350}, {480, 350}, {520, 350},
        {700, 500}, {740, 500}, {780, 500}, {820, 500}, {860, 500}, {900, 500},
        {200, 600}, {200, 640}, {200, 680}, {200, 720},
        {480, 700}, {520, 700}, {560, 700}, {600, 700}, {640, 700}, {680, 700}, {720, 700}, {760, 700}, {800, 700},
        {720, 660}, {720, 700}, {720, 740},
        {100, 140}, {100, 180}, {100, 220}, {100, 260},
        {0, 140}, {40, 140}, {80, 140},
        {700, 260}, {740, 260}, {780, 260}, {820, 260},
        {700, 100}, {700, 140}, {700, 180}, {700, 220},
        {40, 450}, {80, 450}, {120, 450}, {160, 450},
        {100, 20}, {140, 20}, {180, 20}, {220, 20}
    };

    int squareSize = 50; // Size of the squares (assuming all squares are the same size)
    int numSquares = sizeof(newSquares) / sizeof(newSquares[0]);

  for (int i = 0; i < numSquares; i++) {
        int sqX = newSquares[i][0];
        int sqY = newSquares[i][1];

  if (xI >= sqX - squareSize + 16 && xI <= sqX + squareSize - 16 && yI >= sqY - squareSize + 16 && yI <= sqY + squareSize - 16) {
            xI = 0;
            yI = 800;
            score -= 2; // Deduct 2 points for collision
            // cout << "Collision with new square happened" << endl;
        }
    }
}
void WINorLOSE() {
 

 if (score>=100) {
         cout<<" YOU WON " ;
         }
        else{
         cout<< " YOU LOSE\nTRY AGAIN " ;
         }
}
 /*
 * Main Canvas drawing function.
 * */
void GameDisplay()
{
// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
	//glClear (GL_DEPTH_BUFFER_BIT);
	
	//Draw roads
	
      for (int i = 50; i < 1021; i += 50) {
        DrawLine( 0 , i ,  1020 , i , 2 , colors[DARK_SLATE_GRAY] );
        }
      
        
	// Draw lines 
	
	DrawLine( 0   , 0 , 0   ,1000 , 2 , colors[BLACK] );
	DrawLine( 50  , 0 , 50  ,1000 , 2 , colors[BLACK] );	
	DrawLine( 100 , 0 , 100 ,1000 , 2 , colors[BLACK] );	
	DrawLine( 150 , 0 , 150 ,1000 , 2 , colors[BLACK] );	
	DrawLine( 200 , 0 , 200 ,1000 , 2 , colors[BLACK] );	
	DrawLine( 250 , 0 , 250 ,1000 , 2 , colors[BLACK] );	
	DrawLine( 300 , 0 , 300 ,1000 , 2 , colors[BLACK] );
	DrawLine( 350 , 0 , 350 ,1000 , 2 , colors[BLACK] );
	DrawLine( 400 , 0 , 400 ,1000 , 2 , colors[BLACK] );
	DrawLine( 450 , 0 , 450 ,1000 , 2 , colors[BLACK] );
	DrawLine( 500 , 0 , 500 ,1000 , 2 , colors[BLACK] );
	DrawLine( 550 , 0 , 550 ,1000 , 2 , colors[BLACK] );
	DrawLine( 600 , 0 , 600 ,1000 , 2 , colors[BLACK] );
	DrawLine( 650 , 0 , 650 ,1000 , 2 , colors[BLACK] );
	DrawLine( 700 , 0 , 700 ,1000 , 2 , colors[BLACK] );
	DrawLine( 750 , 0 , 750 ,1000 , 2 , colors[BLACK] );
	DrawLine( 800 , 0 , 800 ,1000 , 2 , colors[BLACK] );
	DrawLine( 850 , 0 , 850 ,1000 , 2 , colors[BLACK] );
	DrawLine( 900 , 0 , 900 ,1000 , 2 , colors[BLACK] );
	DrawLine( 950 , 0 , 950 ,1000 , 2 , colors[BLACK] );
	DrawLine( 1000, 0 , 1000,1000 , 2 , colors[BLACK] );
	
	
	//Draw Buildings
        for(int i=20; i<181; i=i+40)
        {
	 DrawSquare(400, i, 50, colors[IVORY]);
	}
	
	for(int i=400; i<521; i=i+40)
        {
	DrawSquare(400, i, 50, colors[IVORY]);
	}
	
	for(int i=320; i<561; i=i+40)
        {
      	DrawSquare(i, 350, 50, colors[IVORY]);
	}
	
	for(int i=700; i<901; i=i+40)
        {
	DrawSquare(i, 500, 50, colors[IVORY]);
	}
	
	for(int i=740; i<901; i=i+40)
        {
	DrawSquare(i, 500, 50, colors[IVORY]);
	}
	
	for(int i=600; i<721; i=i+40)
        {
	DrawSquare(200, i, 50, colors[IVORY]);
	}
	for(int i=480; i<801; i=i+40)
        {
	DrawSquare(i, 700, 50, colors[IVORY]);
	}
	
	for(int i=660; i<741; i=i+40)
	{
	DrawSquare(720, i, 60, colors[IVORY]);
	}
	
	for(int i=320; i<521; i=i+40)
        {
	DrawSquare(i, 350, 50, colors[IVORY]);
	}
	
	for(int i=140; i<261; i=i+40)
        {
	DrawSquare(100, i, 50, colors[IVORY]);
	}
	
	for(int i=0; i<81; i=i+40)
        {
	DrawSquare(i, 140, 50, colors[IVORY]);
	}
	
	for(int i=700; i<821; i=i+40)
        {
	DrawSquare(i, 260, 50, colors[IVORY]);
	}
	
	for(int i=100; i<221; i=i+40)
        {
	DrawSquare(700, i, 50, colors[IVORY]);
        }
	
	for(int i=40; i<161; i=i+40)
        {
	DrawSquare(i, 450, 50, colors[IVORY]);
	}
	
	for(int i=100; i<221; i=i+40)
        {	
	DrawSquare(i, 20, 50, colors[IVORY]);
	}
	

	
       //DESTINATION
       
	DrawCircle( finalX , finalY , 50 ,colors[CHOCOLATE]);
	
	// score	
	DrawString( 50, 800, "Score = " + to_string(score) , colors[WHITE]); 
	DrawString( 500 ,800 ,"Time = ", colors[WHITE]);
	DrawString( 600 ,800 ,to_string(timer), colors[WHITE]);
	
 	Collision(); 
 	
	drawCar();
	
	drawPinkCar();
	
	drawIndigoCar();
	
	drawCyanCar();
	
	drawVioletCar() ;
	
	drawobj() ;
	
	drawPassengers() ;
	
	PassengerFunc() ;
	
	DropOffPassenger() ;
	
       DestinationReached() ;
       
        glutSwapBuffers(); // do not modify this line..
        glutPostRedisplay();
	}



/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
*/

    /* This function calls the Display function to redo the drawing. 
     * Whenever you need to redraw just call this function */
void NonPrintableKeys(int key, int x, int y) {
const int red_speed = 5, yellow_speed =10;

	// AS YELLOW TAXI MOVES FASTER

	if(taxi_color == 'y' || taxi_color == 'Y'){	
	if (key == GLUT_KEY_LEFT ) {
		if (counter>=2)
		{xI -= 2*yellow_speed;}
		else
		{xI -= 1*yellow_speed;}
		 
		

	} else if (key
			== GLUT_KEY_RIGHT ) {
		if (counter>=2)
		{ xI += 2*yellow_speed;}
		else
		{xI += 1*yellow_speed;}
		 
	} else if (key
			== GLUT_KEY_UP) {
		if (counter>=2)
		{ yI += 2*yellow_speed;}
		else
		{yI += 1*yellow_speed;}
		 
	}

	else if (key
			== GLUT_KEY_DOWN){
		if(counter>=2)
		{ yI -= 2*yellow_speed;}
		else
		{yI -= 1*yellow_speed;}
		 
	}
	
}		
						


	// AS RED TAXI MOVES SLOWER

	if(taxi_color == 'r' || taxi_color == 'R'){	
	if (key
			== GLUT_KEY_LEFT ) {
		if (counter>=2)
		{ xI -= 2*red_speed;}
		else
		{xI -= 1*red_speed;}
		 		
                

	} else if (key
			== GLUT_KEY_RIGHT ) {
		if (counter>=2)
		{ xI += 2*red_speed;}
		else
		{xI += 1*red_speed;}
		 		
	} else if (key
			== GLUT_KEY_UP) {
		if (counter>=2)
		{ yI += 2*red_speed;}
		else
		{yI += 1*red_speed;}
		 		
	}

	else if (key
			== GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {
		if (counter>=2)
		{ yI -= 2*red_speed;}
		else
		{yI -= 1*red_speed;}
			
	}
}

    const int moveDistance = 10; // Distance to move the car

    switch (key) {
        case GLUT_KEY_LEFT:
            xI -= moveDistance;
           
            break;
        case GLUT_KEY_RIGHT:
            xI += moveDistance;
         
            break;
        case GLUT_KEY_UP:
            yI += moveDistance;
           
            break;
        case GLUT_KEY_DOWN:
            yI -= moveDistance;
           
            break;
        default:

            break;
    }

    glutPostRedisplay();
}


	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/
	 
	 
	 

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */

void PrintableKeys(unsigned char key, int x, int y) 
{
	if (key == 27/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}
	
	   //when enter is pressed passenger is picked && passenger is dropped as well
       if ( key == 10 ) {
       
        PassengerFunc(); 
        DropOffPassenger() ;
            }
	glutPostRedisplay(); 
}


/*
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m)
{
   UpdatePinkCarPosition() ;
   UpdateIndigoCarPosition(); 
   UpdateCyanCarPosition() ;
   UpdateVioletCarPosition() ;
timer_1++;
	if ( timer_1 %10 == 0)
	timer++;
	if ( timer == 180 )
	exit(1);
	
// implement your functionality here
	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(100, Timer, 0);
}

/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y) 
{
	cout << x << " " << y << endl;
	glutPostRedisplay();
}
void MouseMoved(int x, int y) {
	cout << x << " " << y << endl;
	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
			{
		cout << GLUT_DOWN << " " << GLUT_UP << endl;
		
	} else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
			{
			cout<<"Right Button Pressed"<<endl;
	}
	glutPostRedisplay();
}
/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) 
{

    int width = 1020, height = 840; // i have set my window size to be 800 x 600
    
          const string filename = "highscores.txt";
    vector<pair<string, int>> leaderboard(10);
    loadLeaderboard(leaderboard, filename);

    bool running = true;
    while (running) {
        cout << "1. Start Game" << endl;
        cout << "2. View Leaderboard" << endl;
        cout << "3. Exit" << endl;
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                // Start the game
                cout << "Enter your name: ";
                string playerName;
                cin >> playerName;

                // Assuming score is managed elsewhere and updated in the leaderboard

                saveLeaderboard(leaderboard, filename);
                break;
            }

            case 2:
                // View leaderboard
                displayLeaderboard(leaderboard);
                break;

            case 3:
                // Exit
                running = false;
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }

       char name ;
       cout <<"Enter your name:";
       
      // char taxi_color = 'r'; 
        cout <<"Which taxi you want to play with i.e (red or yellow)" << endl <<"Press 'r' for red  OR 'y' for yellow : " ;
	cin  >> taxi_color;
	
        cout<<"Use arrowkeys to play"<<endl;
        
         //sleep(180);
        WINorLOSE();

       // DestinationReached() ;
        
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("Rush Hour by raffay hassan"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.

	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
	

}
#endif /* RushHour_CPP_ */
