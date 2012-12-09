// A application I made to test if egienvectors was as I thought they were. 
// Warning for ugly codeing. 
//
// How to use:
// + - to change 'eigen value'
// rightclick to pan
// middle to zoom
//
// how to make
// c++ -o linalg linAlg.cpp -O3 -lglut -lGL -lGLU -lX11 -larmadillo
// install libarmadillo-dev freeglut3-dev
// (c) Johan Källström 2010
// 

//#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <sstream>
#include <string.h>
#include <iomanip>
#include <armadillo>


using std::stringstream;
using std::cout;
using std::cin;
using std::endl;
using std::ends;
using std::string;
using namespace arma;
using namespace std;

struct matrisStruct {
  float vektorer[4][4];
  string name;
} ;


void mouseCB(int button, int stat, int x, int y);
void mouseMotionCB(int x, int y);
void drawString3D(const char *str, float pos[3], float color[4], void *font);
void showInfo();
void drawString(const char *str, int x, int y, float color[4], void *font);
void drawVektors(matrisStruct drawMatrix, bool egenVarde, bool text);
void drawPlane(matrisStruct drawMatrix, bool egenVarde, bool text);

void *font = GLUT_BITMAP_8_BY_13;


bool mouseLeftDown;
bool mouseRightDown;
bool mouseMiddleDown;
float mouseX, mouseY;
float cameraAngleX;
float cameraAngleY;
float cameraDistance =-3;
int t = 1;
float egen = 0;
matrisStruct egenvektormatris;
matrisStruct matris2;
matrisStruct matris3;



mat matris(3,3);
cx_vec egenVarde;
cx_mat egenVektor;


void drawEbase(){
   // glTranslatef(0, 0, 0);
glBegin(GL_LINES);
    glColor3f(1,1,1);
    glVertex3f(0,0,0);
    glVertex3f(t,0,0);

    glColor3f(1,1,1);
    glVertex3f(0,0,0);
    glVertex3f(0,t,0);

    glColor3f(1,1,1);
    glVertex3f(0,0,0);
    glVertex3f(0,0,t);

glEnd();

float pos[4] = {0,0,0};
float color[4] = {1,1,1,1};
pos[0] = t;
drawString3D("e1", pos, color, font);
pos[0] = 0;
pos[1] = t;
drawString3D("e2", pos, color, font);
pos[0] = 0;
pos[1] = 0;
pos[2] = t;
drawString3D("e3", pos, color, font);
}


void drawVektors(matrisStruct drawMatrix, bool egenVarde, bool text){
  // glTranslatef(0, 0, 0);
float tempEgen = 0;
float pos[4] = {0,0,0};
float color[4] = {1,1,1,1};

if(egenVarde)
{
	tempEgen = egen;
}

glBegin(GL_LINES);
	for(int k = 0; k < 3; k++){
		//cout << "Vektor " << k << ": (";
		for(int r = 0; r < 3; r++){
			pos[r] = drawMatrix.vektorer[k][r];
			if(r == k)
			pos[r] = drawMatrix.vektorer[k][r]-tempEgen;
		}
		glColor3f(1,0,0);
	    	glVertex3f(0,0,0);
	    	glVertex3f(pos[0],pos[1],pos[2]);

	} 
glEnd();


if(text){
	stringstream ss;//start string stream
	ss << std::fixed << std::setprecision(3);

	//vektor1
	ss << drawMatrix.name << " 1" << ends;
	pos[0] = drawMatrix.vektorer[0][0]-tempEgen;
	pos[1] = drawMatrix.vektorer[0][1];
	pos[2] = drawMatrix.vektorer[0][2];
	drawString3D(ss.str().c_str(), pos, color, font);
	ss.str("");

	//vektor2
	ss << drawMatrix.name << " 3" << ends;
	pos[0] = drawMatrix.vektorer[1][0];
	pos[1] = drawMatrix.vektorer[1][1]-tempEgen;
	pos[2] = drawMatrix.vektorer[1][2];
	drawString3D(ss.str().c_str(), pos, color, font);
	ss.str("");

	//vektor3
	ss << drawMatrix.name << " 3" << ends;
	pos[0] = drawMatrix.vektorer[2][0];
	pos[1] = drawMatrix.vektorer[2][1];
	pos[2] = drawMatrix.vektorer[2][2]-tempEgen;
	drawString3D(ss.str().c_str(), pos, color, font);
	ss.str("");
}

}

void drawPlane(matrisStruct drawMatrix, bool egenVarde, bool text){

float transparency = 0.6;
float tempEgen = 0;
float pos[4] = {0,0,0};
float color[4] = {1,1,1,1};

if(egenVarde)
{
	tempEgen = egen;
}


glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//enable transparancy
glEnable(GL_BLEND);

glBegin(GL_TRIANGLES);
//drawPlane.vektorer[k][r];
	//first triang e1-e2
    glColor4f(0,0,1,transparency);
    glVertex3f(drawMatrix.vektorer[0][0]-tempEgen,drawMatrix.vektorer[0][1],drawMatrix.vektorer[0][2]);//vektor 1
    glColor4f(0,1,0,transparency);
    glVertex3f(0,0,0);
    glColor4f(1,0,0,transparency);
    glVertex3f(drawMatrix.vektorer[1][0],drawMatrix.vektorer[1][1]-tempEgen,drawMatrix.vektorer[1][2]);//vektor 2

	//sec triang e2-e3
    glColor4f(1,0,0,transparency);
    glVertex3f(drawMatrix.vektorer[1][0],drawMatrix.vektorer[1][1]-tempEgen,drawMatrix.vektorer[1][2]);//vektor 2
    glColor4f(0,1,0,transparency);   
    glVertex3f(0,0,0);
    glColor4f(0,1,1,transparency);
    glVertex3f(drawMatrix.vektorer[2][0],drawMatrix.vektorer[2][1],drawMatrix.vektorer[2][2]-tempEgen);//vektor 3

	//third triang e3-e1
    glColor4f(0,1,1,transparency);
    glVertex3f(drawMatrix.vektorer[2][0],drawMatrix.vektorer[2][1],drawMatrix.vektorer[2][2]-tempEgen);//vektor 3
    glColor4f(0,1,0,transparency);
    glVertex3f(0,0,0);
    glColor4f(0,0,1,transparency);
    glVertex3f(drawMatrix.vektorer[0][0]-tempEgen,drawMatrix.vektorer[0][1],drawMatrix.vektorer[0][2]);//vektor 1

glEnd();

//text
stringstream ss;//start stringstream
ss << std::fixed << std::setprecision(3);
//first vektor
ss << drawMatrix.name << " 1" << ends;
pos[0] = drawMatrix.vektorer[0][0]-tempEgen;
pos[1] = drawMatrix.vektorer[0][1];
pos[2] = drawMatrix.vektorer[0][2];
drawString3D(ss.str().c_str(), pos, color, font);
ss.str("");

//vektor 2
ss << std::fixed << std::setprecision(3);
ss << drawMatrix.name << " 2" << ends;
pos[0] = drawMatrix.vektorer[1][0];
pos[1] = drawMatrix.vektorer[1][1]-tempEgen;
pos[2] = drawMatrix.vektorer[1][2];
drawString3D(ss.str().c_str(), pos, color, font);
ss.str("");

//vektor 3
ss << std::fixed << std::setprecision(3);
ss << drawMatrix.name << " 3" << ends;
pos[0] = drawMatrix.vektorer[2][0];
pos[1] = drawMatrix.vektorer[2][1];
pos[2] = drawMatrix.vektorer[2][2]-tempEgen;
drawString3D(ss.str().c_str(), pos, color, font);
ss.str("");

}


void idle(){
    glutPostRedisplay();
}


void display(){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //glTranslatef(0,0,-3);

    // tramsform camera
    glTranslatef(0, 0, cameraDistance);
    glRotatef(cameraAngleX, 1, 0, 0);   // pitch
    glRotatef(cameraAngleY, 0, 1, 0);   // heading


	glLineWidth(5.0);
	drawEbase();//e1-e3
	drawVektors(matris2, false, true);//egenvekort=false, showtext=true
	drawVektors(matris3, false, true);//egenvekort=false, showtext=true

	//placed last bacause of trans
	drawVektors(egenvektormatris, true, false);//egenvekort=true, showtext=false
	drawPlane(egenvektormatris, true, true);//egenvekort=true, showtext=true

	showInfo();
	glutSwapBuffers();
}

void reshape(int width,int height){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0,0,width,height);

    float fovy = 60;
    float aspect_ratio = float(width) / height;
    float near_clip = 0.01;
    float far_clip = 100;

    gluPerspective(fovy, aspect_ratio, near_clip, far_clip );

    glMatrixMode(GL_MODELVIEW);
}

void key(unsigned char key,int x,int y){
    if(key == 27){//esc
        exit(0);}
    if(key == '+'){
	egen += 0.1;
    }
	if(key == '-'){
	egen -= 0.1;
    }
}

void init(){
    glutInitWindowSize(800,600);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Lin Alg.");

    glutIdleFunc(idle);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(key);
    glutMouseFunc(mouseCB);
    glutMotionFunc(mouseMotionCB);

    glEnable(GL_DEPTH_TEST);
}

int main(int argc, char ** argv){
	
	cout << "Skriv A-matrisen nedan.\n";
	cout << "Enter title: ";
  	getline (cin,egenvektormatris.name);
	for(int k = 0; k < 3; k++){
		cout << "Vektor " << k << ": \n";
		for(int r = 0; r < 3; r++){
			cout << "R" << r << ": ";
			cin >> egenvektormatris.vektorer[k][r];

		}
	}
	//matris2
	cin.ignore(1000, '\n');
	cout << "Skriv vektorer nedan.\n";
	cout << "Enter title: ";
  	getline (cin,matris2.name);
	for(int k = 0; k < 3; k++){
		cout << "Vektor " << k << ": \n";
		for(int r = 0; r < 3; r++){
			cout << "R" << r << ": ";
			cin >> matris2.vektorer[k][r];

		}
	}
	//matris3
	cin.ignore(1000, '\n');
	cout << "Skriv vektorer nedan.\n";
	cout << "Enter title: ";
  	getline (cin,matris3.name);
	cout << "Skriv vektorer nedan.\n";
	for(int k = 0; k < 3; k++){
		cout << "Vektor " << k << ": \n";
		for(int r = 0; r < 3; r++){
			cout << "R" << r << ": ";
			cin >> matris3.vektorer[k][r];

		}
	}
	for(int k = 0; k < 3; k++){
		cout << "Vektor " << k << ": (";
		for(int r = 0; r < 3; r++){
			cout << egenvektormatris.vektorer[k][r];
			matris(r,k) = egenvektormatris.vektorer[k][r];
			if(r < 2)
			cout << ", ";
		}
		cout << ")\n";
	}
	cout << matris;
	eig_gen(egenVarde, egenVektor, matris);
	cout << "Egenvärde: \n" << egenVarde << "EgenVektor: \n" << egenVektor << endl;

	glutInit(&argc, argv);
    init();

    glutMainLoop();
	
    return 0;


}
void mouseMotionCB(int x, int y)
{
    if(mouseLeftDown)
    {
        cameraAngleY += (x - mouseX);
        cameraAngleX += (y - mouseY);
        mouseX = x;
        mouseY = y;
    }
    if(mouseMiddleDown)
    {
        cameraDistance += (y - mouseY) * 0.2f;
        mouseY = y;
    }

    glutPostRedisplay();
}
void mouseCB(int button, int state, int x, int y)
{
    mouseX = x;
    mouseY = y;

    if(button == GLUT_LEFT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            mouseLeftDown = true;
        }
        else if(state == GLUT_UP)
            mouseLeftDown = false;
    }

    else if(button == GLUT_RIGHT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            mouseRightDown = true;
        }
        else if(state == GLUT_UP)
            mouseRightDown = false;
    }

    else if(button == GLUT_MIDDLE_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            mouseMiddleDown = true;
        }
        else if(state == GLUT_UP)
            mouseMiddleDown = false;
    }
}

///////////////////////////////////////////////////////////////////////////////
// display info messages
///////////////////////////////////////////////////////////////////////////////
void showInfo()
{
    // backup current model-view matrix
    glPushMatrix();                     // save current modelview matrix
    glLoadIdentity();                   // reset modelview matrix

    // set to 2D orthogonal projection
    glMatrixMode(GL_PROJECTION);        // switch to projection matrix
    glPushMatrix();                     // save current projection matrix
    glLoadIdentity();                   // reset projection matrix
    gluOrtho2D(0, 400, 0, 300);         // set to orthogonal projection

    float color[4] = {1, 1, 1, 1};

    stringstream ss;
    ss << std::fixed << std::setprecision(3);

    ss << "Egen: " << egen << ends;
    drawString(ss.str().c_str(), 1, 286, color, font);
    ss.str("");

    for(int k = 0; k < 3; k++){
		ss << "(";
		for(int r = 0; r < 3; r++){
			ss << egenvektormatris.vektorer[k][r];
			if(r < 2)
			ss << ", ";
		}
		if(k < 2)
		ss << "), ";
	}
ss << ends;
    drawString(ss.str().c_str(), 1, 272, color, font);
    ss.str("");


ss << "Egenvärde: " << egenVarde << ends;
    drawString(ss.str().c_str(), 1, 264, color, font);
    ss.str("");

ss  << "EgenVektor: " << egenVektor << ends;
    drawString(ss.str().c_str(), 1, 256, color, font);
    ss.str("");

    /*ss << "Max Elements Indices: " << maxIndices << ends;
    drawString(ss.str().c_str(), 1, 272, color, font);
    ss.str("");*/

    // unset floating format
    ss << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);

    // restore projection matrix
    glPopMatrix();                   // restore to previous projection matrix

    // restore modelview matrix
    glMatrixMode(GL_MODELVIEW);      // switch to modelview matrix
    glPopMatrix();                   // restore to previous modelview matrix
}

///////////////////////////////////////////////////////////////////////////////
// set camera position and lookat direction
///////////////////////////////////////////////////////////////////////////////
void setCamera(float posX, float posY, float posZ, float targetX, float targetY, float targetZ)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(posX, posY, posZ, targetX, targetY, targetZ, 0, 1, 0); // eye(x,y,z), focal(x,y,z), up(x,y,z)
}
///////////////////////////////////////////////////////////////////////////////
// draw a string in 3D space
///////////////////////////////////////////////////////////////////////////////
void drawString3D(const char *str, float pos[3], float color[4], void *font)
{
    glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT); // lighting and color mask
    glDisable(GL_LIGHTING);     // need to disable lighting for proper text color

    glColor4fv(color);          // set text color
    glRasterPos3fv(pos);        // place text position

    // loop all characters in the string
    while(*str)
    {
        glutBitmapCharacter(font, *str);
        ++str;
    }

    glEnable(GL_LIGHTING);
    glPopAttrib();
}
///////////////////////////////////////////////////////////////////////////////
// write 2d text using GLUT
// The projection matrix must be set to orthogonal before call this function.
///////////////////////////////////////////////////////////////////////////////
void drawString(const char *str, int x, int y, float color[4], void *font)
{
    glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT); // lighting and color mask
    glDisable(GL_LIGHTING);     // need to disable lighting for proper text color

    glColor4fv(color);          // set text color
    glRasterPos2i(x, y);        // place text position

    // loop all characters in the string
    while(*str)
    {
        glutBitmapCharacter(font, *str);
        ++str;
    }

    glEnable(GL_LIGHTING);
    glPopAttrib();
}


