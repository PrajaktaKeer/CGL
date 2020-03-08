#include<GL/glut.h>
#include<iostream>
using namespace std;

void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glOrtho2D(0.0, 200.0, 0.0, 150.0);
}

void renderFunction()
{
}

int main(int argc, char **argv)
{
	glutInit(argc, &argc);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 150);
	glutInitWindowSize(400, 640);
	glutCreateWindow("BASIC CODE");
	init();
	glutDisplayFunc(renderFunction);
	glutMainLoop();
	return 0;
}
	
