#include<stdio.h> 
#include<GL/glut.h> 
#include<math.h> 
#include<random>

// Raed Massoud | Github.com/RaedMassoud
// 5/15/2024
// 
// Car and Pot hole Game | OpenGL | C++ | 330 lines
// LEFT MOUSE BUTTON IS USED TO PLAY THE GAME

static bool RUNNING = true; // Used to terminate recursive call of the timer function when the game ends

GLfloat roadStripLocation = 0.0; // Represents the location of the road strips
static const int FPS = 60; // FPS
static bool rightSide = true; // what side is the car on
static bool move = false; // used to know when to make changes to the car Y-AXIS for fluid motion
static double carLocation = 75; // car location ON THE Y-AXIS ( 75 or -135 )

// Pothole variables intial values
static double potholeLocationX = 2000;
static double potholeLocationY = 75;

static double potholeLocationX2 = 1700;
static double potholeLocationY2 = 75;

static double potholeLocationX3 = 1900;
static double potholeLocationY3 = 75;


// White Road Strip Func
void roadStrip() {

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
        glVertex2f(0.0,0.0);
        glVertex2f(0.0,20.0);
        glVertex2f(200.0,20.0);
        glVertex2f(200.0,0.0);
    glEnd();
}

// Main Road func
void road() {

	glColor3f(0.2, 0.2, .2);
    glBegin(GL_POLYGON);
        glVertex2f(0.0,0.0);
        glVertex2f(0.0,400.0);
        glVertex2f(1600.0,400.0);
        glVertex2f(1600.0,0.0);
    glEnd();
}

// Pothole function
void roadPotHoles () {

	glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
        glVertex2f(0.0,0.0);
        glVertex2f(0.0,75.0);
        glVertex2f(75.0,75.0);
        glVertex2f(75.0,0.0);
    glEnd();
}

// Car func
void car() {

	// Main Car Body
	glPushMatrix();
	glColor3f(0.2, 0.0, .5);
	glBegin(GL_POLYGON);
		glVertex2f(0.0,0.0);
        glVertex2f(0.0,75.0);
        glVertex2f(125.0,75.0);
        glVertex2f(125.0,0.0);
	glEnd();
	glPopMatrix();

	// Car front window
	glPushMatrix();
	glColor3f(0.95, 0.95, 0.95);
	glBegin(GL_POLYGON);
		glVertex2f(75.0,20.0);
        glVertex2f(100.0,10.0);
		glVertex2f(100.0,65.0);
        glVertex2f(75.0,55.0);
	glEnd();
	glPopMatrix();

	// Car back window
	glPushMatrix();
	glColor3f(0.95, 0.95, 0.95);
	glBegin(GL_POLYGON);
		glVertex2f(15.0,10.0);
        glVertex2f(40.0,20.0);
		glVertex2f(40.0,55.0);
        glVertex2f(15.0,65.0);
	glEnd();
	glPopMatrix();


	// Car headlights
	glPushMatrix();
	glColor3f(0.95, 0.95, 0.95);
	glTranslatef(110.0, 15, 0.0);
	glBegin(GL_TRIANGLES);
		glVertex2f(0.0, 0.0);
		glVertex2f(85.0, 20.0);
		glVertex2f(85.0, -20.0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.95, 0.95, 0.95);
	glTranslatef(110.0, 60, 0.0);
	glBegin(GL_TRIANGLES);
		glVertex2f(0.0, 0.0);
		glVertex2f(85.0, 20.0);
		glVertex2f(85.0, -20.0);
	glEnd();
	glPopMatrix();
	
}


void display (void) 
{
    glClear(GL_COLOR_BUFFER_BIT || GL_DEPTH_BUFFER_BIT); 


	// Road and Road Strips Begin
	glPushMatrix();
	glTranslatef(-800, -200, 0);
    road();
	glPopMatrix();

	// Road Strip 1
	glPushMatrix();
	glTranslatef(-800, -10, 0);
	glTranslatef(roadStripLocation, 0.0, 0.0);
	roadStrip();
	glPopMatrix();

	// Road Strip 2
	glPushMatrix();
	glTranslatef(-800, -10, 0);
	glTranslatef(roadStripLocation + 400, 0.0, 0.0);
	roadStrip();
	glPopMatrix();

	// Road Strip 3
	glPushMatrix();
	glTranslatef(-800, -10, 0);
	glTranslatef(roadStripLocation + 800, 0.0, 0.0);
	roadStrip();
	glPopMatrix();

	// Road Strip 4
	glPushMatrix();
	glTranslatef(-800, -10, 0);
	glTranslatef(roadStripLocation + 1200, 0.0, 0.0);
	roadStrip();
	glPopMatrix();

	// Road Strip 5
	glPushMatrix();
	glTranslatef(-800, -10, 0);
	glTranslatef(roadStripLocation + 1600, 0.0, 0.0);
	roadStrip();
	glPopMatrix();

	// Road and Road Strips End

	// Car 
	glPushMatrix();
	glTranslatef(-750, carLocation, 0);
	car();
	glPopMatrix();

	// Potholes
	glPushMatrix();
	glTranslatef(potholeLocationX, potholeLocationY, 0);
	roadPotHoles();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(potholeLocationX2, potholeLocationY2, 0);
	roadPotHoles();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(potholeLocationX3, potholeLocationY3, 0);
	roadPotHoles();
	glPopMatrix();

    glFlush(); 
    glutSwapBuffers();
}

// Mouse function. Active movement when mouse is clicked
void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		move = true; // This activates a code block in the timer functions
	}
}

// Timer Function
void timer(int value)
{
	// Road Strips Movement and Speed
	roadStripLocation-=10.0;

	if(roadStripLocation <= -400) {
	roadStripLocation = 0.0;
	}

		glutPostRedisplay();

	// Move car
	if(move) {

		// Change y axis depending on which side of the road the car is on
		if(rightSide) {
			carLocation -= 5;
		} else {
			carLocation += 5;
		}

		// Stop moving the car when it reaches one of its 2 locations (left or right)
		if(carLocation == -135 || carLocation == 75) {
			move = false;
			// Switch car side
			if(rightSide)
				rightSide = false;
			else
				rightSide = true;
		}
	}

	// Potholes Movement 
	potholeLocationX -= 15;
	potholeLocationX2 -= 15;
	potholeLocationX3 -= 15;

	if(potholeLocationX < -900) { // Reset x axis of pothole
		potholeLocationX = 1700;
		int x = rand() % 2; // Randomly choose left or right side for pothole
		if(x == 1)
			potholeLocationY = 75;
		else
			potholeLocationY = -135;
	}

	if(potholeLocationX2 < -900) { // Reset x axis of pothole 2
		potholeLocationX2 = 1900;
		int x = rand() % 2; // Randomly choose left or right side for pothole
		if(x == 1)
			potholeLocationY2 = 75;
		else
			potholeLocationY2 = -135;
	}

	if(potholeLocationX3 < -900) { // Reset x axis of pothole 3
		potholeLocationX3 = 2100;
		int x = rand() % 2; // Randomly choose left or right side for pothole
		if(x == 1)
			potholeLocationY3 = 75;
		else
			potholeLocationY3 = -135;
	}

	// Collision detection
	// If the pothole x coordinate overlaps with our car costant x coordinate AND the difference between 
	// the car and the pothote y coordinates is small it means the car is overlaping the pothole on both 
	// the x and y axis.
	if(-750 <= potholeLocationX && potholeLocationX <= -625  && abs(carLocation - potholeLocationY) < 25)
		RUNNING = false;

	if(-750 <= potholeLocationX2 && potholeLocationX2 <= -625  && abs(carLocation - potholeLocationY2) < 25)
		RUNNING = false;

	if(-750 <= potholeLocationX3 && potholeLocationX3 <= -625  && abs(carLocation - potholeLocationY3) < 25)
		RUNNING = false;
		

	// Break recursive call if collision is detected
	if(RUNNING) {
		glutTimerFunc(1000 / FPS, timer, value);
	}
}

// Reshape func
void reshape(GLint w, GLint h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, GLfloat(w) / GLfloat(h), 1.0, 20.0);
}

// Init Func
void Init (void) 
{ 
	glClearColor(0.0, 0.0, 0.0, 1.0); 
	glColor3f(0.0, 1.0, 0.0); 
	glPointSize(1.0); 
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	gluOrtho2D(-800, 800, -600, 600); 

} 

// Main Function
int main (int argc, char** argv) 
{ 
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 
	glutInitWindowSize(800, 600); 
	glutInitWindowPosition(0, 0); 
	glutCreateWindow("Car and Pothole Game"); 
	Init(); 
	
	glutDisplayFunc(display); 
	glutMouseFunc(mouse);
	glutTimerFunc(100,timer,0);

	glutMainLoop(); 
} 
