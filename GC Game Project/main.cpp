#include <iostream>
#include <fstream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <cstdlib>
#include <string.h>
#include <windows.h>
#include <mmsystem.h>

using namespace std;

float _move1 = 0;
float _move2 = 0;
float _move3 = 0;
float _move4 = 0;
float _opCar1 = 0,_opCar2 = 1.7,_opCar3 = 2.4;
int driverCarPos = 0;
float speed = 0.02;
int carPos = 1;
int carCreate1 =0,carCreate2 = 0,carCreate3 =0;
int carOpPos[] = {0,0,0,0,0,0,0};
float _opCar[] = {0,0,0,0,0,0,0};
int nOp = 6;
int screen = 0;
char start[] = "Start";
char hScore[] = "HighScore";
char exitGame[] = "Exit";
char scoreText[] = "Score:";
char mphText[] = "MPH:";
char levelText[] = "Level:";
int score = 0;
char buffer[10];
bool collide = false;
int highScore[10] = {0,0,0,0,0,0,0,0,0,0};
int prevOpPos =0;
int timer = 25;
int mph = 50;
int level = 0;
//Print
void Sprint( float x, float y, char *st)
{
    int l,i;

    l=strlen( st );
    glColor3f(0.0,1.0,0.7);
    glRasterPos2f( x, y); // location to start printing text
    for( i=0; i < l; i++) // loop until i is greater then l
    {
       glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, st[i]);
    }
}
void writeHighScore()
{
    ofstream scoreFile;
    scoreFile.open("score.txt");
    for(int i = 0; i < 10; i++)
    {
        scoreFile << highScore[i] << endl;
    }
    scoreFile.close();
}
void readHighScore()
{
    ifstream scoreFile;
    scoreFile.open("score.txt");
    if(scoreFile.fail())
    {
        cerr << "Error: Opening File." <<endl;
        exit(1);
    }
    for(int i = 0; i < 10; i++)
    {
        scoreFile >> highScore[i];
    }
    scoreFile.close();
}
void sortHighScore()
{
    //Sorting

    for(int i = 0; i < 10;i++)
    {
        for(int j = 0; j < 10; j++)
        {
            if(highScore[j] < highScore[j + 1])
            {
                int temp = highScore[j];
                highScore[j] = highScore[j + 1];
                highScore[j + 1] = temp;
                //cout << highScore[j] << highScore[j+1];
            }
        }
    }

}
void SprintScore(char ch[],int numtext,float x, float y)//counting the score
{
    int len;
    int k,i;
    k = 0;
    len = numtext - strlen (ch);
    glLoadIdentity ();
    glRasterPos2f( x , y);
    for (i = 0; i <=numtext - 1; i++)
    {
        if ( i < len )
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,'0');
        else
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ch[k]);
            k++;
        }
    }
}

void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 27:
            if(screen == 2)
                screen = 0;
        case 'e':

            break;
        case 'x':
            speed = 0;
            break;
        case 'c':
            speed = 0.02;
            break;
        case 'a':
            if(carPos != 1)
                carPos--;
            break;
        case 'd':
            if(carPos != 3)
                carPos++;
            break;
    }
}

void mouse(int button, int state, int x, int y)
{

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if(screen == 0)
        {
            if(x > 280 && x < 517 && y > 240 && y < 320)
            {
                screen = 1;
                for(int i = 1;i <= nOp;i++)
                {
                    _opCar[i] = 0;
                }

                for(int i = 1;i <= nOp;i++)
                {
                   carOpPos[i] = 0;
                }


                float diff = 0;
                for(int i = 1;i <= nOp;i++)
                {
                    _opCar[i] += diff;
                    diff += .7;
                }
                speed = 0.02;
                score = 0;
                mph = 50;
                level = 0;
            }
            else if(x > 280 && x < 517 && y > 360 && y < 440)
            {
                readHighScore();
                screen = 2;
            }
            else if(x > 280 && x < 517 && y > 480 && y < 560)
            {
                exit(1);
            }
        }
    }
}

void drawRoad()
{
    glPushMatrix();

        glColor3ub(213,222,24);
        glBegin(GL_QUADS);
            glVertex3f(-1,-1,0);
            glVertex3f(-1,1,0);
            glVertex3f(1,1,0);
            glVertex3f(1,-1,0);
        glEnd();

        glColor3ub(128,128,128);
        glBegin(GL_QUADS);
            glVertex3f(-.75,-1,0);
            glVertex3f(-.75,1,0);
            glVertex3f(.75,1,0);
            glVertex3f(.75,-1,0);
        glEnd();

            glColor3ub(255,255,255);
            glPushMatrix();
                glTranslatef(0,_move1,0);
                glBegin(GL_QUADS);
                    glVertex3f(-.30,1.70,0);
                    glVertex3f(-.30,1.10,0);
                    glVertex3f(-.20,1.10,0);
                    glVertex3f(-.20,1.70,0);
                glEnd();
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0,_move2,0);
                glBegin(GL_QUADS);
                    glVertex3f(-.30,1,0);
                    glVertex3f(-.30,.40,0);
                    glVertex3f(-.20,.40,0);
                    glVertex3f(-.20,1,0);
                glEnd();
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0,_move3,0);
                glBegin(GL_QUADS);
                    glVertex3f(-.30,.30,0);
                    glVertex3f(-.30,-.3,0);
                    glVertex3f(-.20,-.3,0);
                    glVertex3f(-.20,.30,0);
                glEnd();
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0,_move4,0);
                glBegin(GL_QUADS);
                    glVertex3f(-.30,-.40,0);
                    glVertex3f(-.30,-1,0);
                    glVertex3f(-.20,-1,0);
                    glVertex3f(-.20,-.40,0);
                glEnd();
            glPopMatrix();

            //Right white
            glPushMatrix();
                glTranslatef(0,_move1,0);
                glBegin(GL_QUADS);
                    glVertex3f(.30,1.70,0);
                    glVertex3f(.30,1.10,0);
                    glVertex3f(.20,1.10,0);
                    glVertex3f(.20,1.70,0);
                glEnd();
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0,_move2,0);
                glBegin(GL_QUADS);
                    glVertex3f(.30,1,0);
                    glVertex3f(.30,.40,0);
                    glVertex3f(.20,.40,0);
                    glVertex3f(.20,1,0);
                glEnd();
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0,_move3,0);
                glBegin(GL_QUADS);
                    glVertex3f(.30,.30,0);
                    glVertex3f(.30,-.3,0);
                    glVertex3f(.20,-.3,0);
                    glVertex3f(.20,.30,0);
                glEnd();
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0,_move4,0);
                glBegin(GL_QUADS);
                    glVertex3f(.30,-.40,0);
                    glVertex3f(.30,-1,0);
                    glVertex3f(.20,-1,0);
                    glVertex3f(.20,-.40,0);
                glEnd();
            glPopMatrix();

    glPopMatrix();
}

void drawDriver()
{
    if(carPos == 1)
    {
        glPushMatrix();
            glColor3ub(255,0,0);
            glBegin(GL_POLYGON);
                glVertex3f(-.55,-.7,0);
                glVertex3f(-.6,-.75,0);
                glVertex3f(-.6,-.85,0);
                glVertex3f(-.55,-.9,0);
                glVertex3f(-.5,-.9,0);
                glVertex3f(-.45,-.85,0);
                glVertex3f(-.45,-.75,0);
                glVertex3f(-.5,-.7,0);
            glEnd();

            glColor3ub(0,0,255);
            glBegin(GL_POLYGON);
                glVertex3f(-.6,-.75,0);
                glVertex3f(-.6,-.85,0);
                glVertex3f(-.45,-.85,0);
                glVertex3f(-.45,-.75,0);
            glEnd();

            glColor3ub(0,0,255);
            glBegin(GL_POLYGON);

                glVertex3f(-.63,-.88,0);
                glVertex3f(-.63,-.9,0);
                glVertex3f(-.42,-.9,0);
                glVertex3f(-.42,-.88,0);

            glEnd();

            glColor3ub(0,0,0);
            glPointSize(10);
            glBegin(GL_POINTS);
                glVertex3f(-.6,-.75,0);
                glVertex3f(-.6,-.85,0);
                glVertex3f(-.45,-.85,0);
                glVertex3f(-.45,-.75,0);
            glEnd();

        glPopMatrix();
    }
    else if(carPos == 2)
    {
        glPushMatrix();
            glColor3ub(255,0,0);
            glBegin(GL_POLYGON);
                glVertex3f(-.025,-.7,0);
                glVertex3f(-.075,-.75,0);
                glVertex3f(-.075,-.85,0);
                glVertex3f(-.025,-.9,0);
                glVertex3f(.025,-.9,0);
                glVertex3f(.075,-.85,0);
                glVertex3f(.075,-.75,0);
                glVertex3f(.025,-.7,0);
            glEnd();

            glColor3ub(0,0,255);
            glBegin(GL_POLYGON);
                glVertex3f(-.075,-.75,0);
                glVertex3f(-.075,-.85,0);
                glVertex3f(.075,-.85,0);
                glVertex3f(.075,-.75,0);
            glEnd();

            glColor3ub(0,0,255);
            glBegin(GL_POLYGON);
                glVertex3f(-.105,-.88,0);
                glVertex3f(-.105,-.9,0);
                glVertex3f(.105,-.9,0);
                glVertex3f(.105,-.88,0);
            glEnd();

            glColor3ub(0,0,0);
            glPointSize(10);
            glBegin(GL_POINTS);
                glVertex3f(-.075,-.75,0);
                glVertex3f(-.075,-.85,0);
                glVertex3f(.075,-.85,0);
                glVertex3f(.075,-.75,0);
            glEnd();

        glPopMatrix();
    }
    else if(carPos == 3)
    {
        glPushMatrix();
            glColor3ub(255,0,0);
            glBegin(GL_POLYGON);
                glVertex3f(.55,-.7,0);
                glVertex3f(.6,-.75,0);
                glVertex3f(.6,-.85,0);
                glVertex3f(.55,-.9,0);
                glVertex3f(.5,-.9,0);
                glVertex3f(.45,-.85,0);
                glVertex3f(.45,-.75,0);
                glVertex3f(.5,-.7,0);
            glEnd();

            glColor3ub(0,0,255);
            glBegin(GL_POLYGON);
                glVertex3f(.6,-.75,0);
                glVertex3f(.6,-.85,0);
                glVertex3f(.45,-.85,0);
                glVertex3f(.45,-.75,0);
            glEnd();

            glColor3ub(0,0,255);
            glBegin(GL_POLYGON);

                glVertex3f(.63,-.88,0);
                glVertex3f(.63,-.9,0);
                glVertex3f(.42,-.9,0);
                glVertex3f(.42,-.88,0);

            glEnd();

            glColor3ub(0,0,0);
            glPointSize(10);
            glBegin(GL_POINTS);
                glVertex3f(.6,-.75,0);
                glVertex3f(.6,-.85,0);
                glVertex3f(.45,-.85,0);
                glVertex3f(.45,-.75,0);
            glEnd();
        glPopMatrix();
    }
}

int getOpCarPos(int opCarPos)
{
    if(opCarPos == 0)
    {

        int i =1;
        int pos = rand() % 3 + 1;
        while(i)
        {
             if(pos == prevOpPos)
                pos = rand() % 3 + 1;
             else
                break;
        }

        prevOpPos = pos;
        return pos;
    }
    else
        return opCarPos;
}
void drawOpCar(int pos)
{
    if(pos == 1)
    {
        glPushMatrix();
            glColor3ub(255,127,39);
            glBegin(GL_QUADS);
                glVertex3f(-.6,.75,0);
                glVertex3f(-.6,.95,0);
                glVertex3f(-.45,.95,0);
                glVertex3f(-.45,.75,0);
            glEnd();

            glColor3ub(0,0,0);
            glPointSize(15);
            glBegin(GL_POINTS);
                glVertex3f(-.575,.72,0);
                glVertex3f(-.475,.72,0);
            glEnd();

            glColor3ub(255,0,255);
            glBegin(GL_QUADS);
                glVertex3f(-.575,.75,0);
                glVertex3f(-.575,.7,0);
                glVertex3f(-.475,.7,0);
                glVertex3f(-.475,.75,0);
            glEnd();
        glPopMatrix();
    }
    else if(pos == 2)
    {
        glPushMatrix();
            glColor3ub(255,127,39);
            glBegin(GL_QUADS);
                glVertex3f(-.075,.75,0);
                glVertex3f(-.075,.95,0);
                glVertex3f(.075,.95,0);
                glVertex3f(.075,.75,0);
            glEnd();

            glColor3ub(0,0,0);
            glPointSize(15);
            glBegin(GL_POINTS);
                glVertex3f(-.05,.72,0);
                glVertex3f(.05,.72,0);
            glEnd();

            glColor3ub(255,0,255);
            glBegin(GL_QUADS);
                glVertex3f(-.05,.75,0);
                glVertex3f(-.05,.7,0);
                glVertex3f(.05,.7,0);
                glVertex3f(.05,.75,0);
            glEnd();
        glPopMatrix();
    }
    else if(pos == 3)
    {
        glPushMatrix();
            glColor3ub(255,127,39);
            glBegin(GL_QUADS);
                glVertex3f(.6,.75,0);
                glVertex3f(.6,.95,0);
                glVertex3f(.45,.95,0);
                glVertex3f(.45,.75,0);
            glEnd();

            glColor3ub(0,0,0);
            glPointSize(15);
            glBegin(GL_POINTS);
                glVertex3f(.575,.72,0);
                glVertex3f(.475,.72,0);
            glEnd();

            glColor3ub(255,0,255);
            glBegin(GL_QUADS);
                glVertex3f(.575,.75,0);
                glVertex3f(.575,.7,0);
                glVertex3f(.475,.7,0);
                glVertex3f(.475,.75,0);
            glEnd();
        glPopMatrix();
    }
}

void drawMenu()
{
    glPushMatrix();

        glColor3ub(0,0,0);
        glBegin(GL_QUADS);
            glVertex3f(-.45,.65,0);
            glVertex3f(-.45,-.65,0);
            glVertex3f(.45,-.65,0);
            glVertex3f(.45,.65,0);
        glEnd();

        glColor3ub(0,0,255);
        glBegin(GL_QUADS);
            glVertex3f(-.4,.6,0);
            glVertex3f(-.4,-.6,0);
            glVertex3f(.4,-.6,0);
            glVertex3f(.4,.6,0);
        glEnd();

        glColor3ub(0,0,0);

        glBegin(GL_QUADS);
            glVertex3f(-.31,.41,0);
            glVertex3f(-.31,.19,0);
            glVertex3f(.31,.19,0);
            glVertex3f(.31,.41,0);
        glEnd();

        glBegin(GL_QUADS);
            glVertex3f(-.31,.11,0);
            glVertex3f(-.31,-.11,0);
            glVertex3f(.31,-.11,0);
            glVertex3f(.31,.11,0);
        glEnd();

        glBegin(GL_QUADS);
            glVertex3f(-.31,-.41,0);
            glVertex3f(-.31,-.19,0);
            glVertex3f(.31,-.19,0);
            glVertex3f(.31,-.41,0);
        glEnd();

        glColor3ub(128,128,128);

        glBegin(GL_QUADS);
            glVertex3f(-.3,.4,0);
            glVertex3f(-.3,.2,0);
            glVertex3f(.3,.2,0);
            glVertex3f(.3,.4,0);
        glEnd();

        glBegin(GL_QUADS);
            glVertex3f(-.3,.1,0);
            glVertex3f(-.3,-.1,0);
            glVertex3f(.3,-.1,0);
            glVertex3f(.3,.1,0);
        glEnd();

        glBegin(GL_QUADS);
            glVertex3f(-.3,-.4,0);
            glVertex3f(-.3,-.2,0);
            glVertex3f(.3,-.2,0);
            glVertex3f(.3,-.4,0);
        glEnd();

        //text
        Sprint(-.07,.28,start);
        Sprint(-.13,-.02,hScore);
        Sprint(-.07,-.32,exitGame);


    glPopMatrix();
}
void drawHighScore()
{
    glPushMatrix();
        glColor3ub(0,0,0);
        glBegin(GL_QUADS);
            glVertex3f(-.45,.65,0);
            glVertex3f(-.45,-.65,0);
            glVertex3f(.45,-.65,0);
            glVertex3f(.45,.65,0);
        glEnd();

        glColor3ub(0,0,255);
        glBegin(GL_QUADS);
            glVertex3f(-.4,.6,0);
            glVertex3f(-.4,-.6,0);
            glVertex3f(.4,-.6,0);
            glVertex3f(.4,.6,0);
        glEnd();

        Sprint(-.13,.5,hScore);
        float scPos = .4;
        for(int i = 0; i < 10; i++)
        {
            if(highScore[i] < 10)
                highScore[i] = 0;
            itoa(highScore[i], buffer, 10);
            SprintScore(buffer,6,-.08,scPos);
            scPos -= .1;
        }


    glPopMatrix();
}

void drawScoreBoard()
{
    glColor3ub(0,0,0);
        glBegin(GL_QUADS);
            glVertex3f(.75,.9,0);
            glVertex3f(.75,.4,0);
            glVertex3f(1,.4,0);
            glVertex3f(1,.9,0);
        glEnd();

        glColor3ub(0,0,255);
        glBegin(GL_QUADS);
            glVertex3f(.77,.88,0);
            glVertex3f(.77,.42,0);
            glVertex3f(.98,.42,0);
            glVertex3f(.98,.88,0);
        glEnd();

    Sprint(.8,.8,scoreText);
    itoa (score, buffer, 10);
    SprintScore(buffer, 6, .8,.75);

    Sprint(.8,.65,levelText);
    itoa (level, buffer, 10);
    SprintScore(buffer, 2, .85,.60);

    Sprint(.8,.5,mphText);
    itoa (mph, buffer, 10);
    SprintScore(buffer, 3, .83,.45);
}

void update(int value)
{
    //road white
     _move4 -= speed;
     _move3 -= speed;
     _move2 -= speed;
     _move1 -= speed;

    if(_move4 < -.6)
        _move4 = 2.2;
    else if(_move3 < -1.3)
        _move3 = 1.5;
    else if(_move2 < -2)
        _move2 = .8;
    else if(_move1 < -2.7)
        _move1 = .1;

    //car
    for(int i = 1; i <= nOp; i++)
    {
        if(carOpPos[i] > 0)
            _opCar[i] -= speed;

        if(nOp == i)
        {
            if(_opCar[nOp] < -3.1)
            {
                float diff =0;
                for(int i = 1; i <= nOp; i++)
                {
                    carOpPos[i] = 0;
                    _opCar[i] = diff;
                    diff += .7;
                }
            }
        }
    }

    for(int i =1; i <= nOp ; i++)
    {
        if( -1.40 >_opCar[i] && _opCar[i] > -1.8 && carPos == carOpPos[i])
        {
            if(collide)
                collide = false;
            else
                collide = true;
        }
    }

    if(collide)
    {
        if(screen == 1)
        {
            screen = 0;
            if(score > highScore[9])
                {
                    highScore[9] = score;
                    sortHighScore();
                    writeHighScore();
                    cout << highScore[9];
                }
            score = 0;
        }

        collide = false;
    }

    score++;

    if(score > 500 && score < 1000)
    {
         speed = 0.03;
         level = 2;
         mph = 60;
    }
    else if(score > 1000 && score < 1500)
    {
        speed = 0.04;
         level = 3;
         mph = 70;
    }
    else if(score > 1500 && score < 2000)
    {
        speed = 0.06;
        level = 4;
        mph += 80;
    }
    else if(speed > 2000 && score < 2500)
    {
        timer = 0.08;
        level = 5;
        mph = 90;
    }
    else if (speed > 2500)
    {
        timer = 0.1;
        level = 6;
        mph = 100;
    }

    glutPostRedisplay();
    glutTimerFunc(timer,update,0);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3b(0,0,0);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);

    if(screen == 0)
    {
        glPushMatrix();
            drawRoad();
            drawMenu();
        glPopMatrix();
    }
    else if(screen == 1)
    {
        glPushMatrix();
            drawRoad();
            drawDriver();
        glPopMatrix();

        for(int i = 1;i <= nOp;i++)
        {
            glPushMatrix();
                glTranslated(0,_opCar[i],0);
                carOpPos[i] = getOpCarPos(carOpPos[i]);
                drawOpCar(carOpPos[i]);
            glPopMatrix();
        }
        drawScoreBoard();
    }
    else if(screen == 2)
    {
        drawRoad();
        drawHighScore();
    }

    glutSwapBuffers();
}



int main (int argc, char** argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800,800);
    glutCreateWindow("Car Drive");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    //sndPlaySound("Background.wav",SND_ASYNC|SND_LOOP);
    glutTimerFunc(25, update,0);
    glutMainLoop();

    return 0;
}




