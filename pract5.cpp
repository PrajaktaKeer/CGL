/* ROLL NO : 23269
BATCH : H10
PROBLEM STATEMENT : Implement Cohen Sutherland algorithm to clip any given Line/polygon. Provide the vertices of the Line/polygon to be clipped and pattern of clipping interactively.  */

#include<GL/glut.h>
#include<iostream>
using namespace std;

int x1, y1, x2, y2, l1x, l1y, l2x, l2y;

void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

class clipping
{
	int xmin, ymin, xmax, ymax, p1x, p1y, p2x, p2y, i1x, i1y, i2x, i2y;
	float m;
	bool p1[4], p2[4], lAnd[4];
	public:
	clipping(int x1, int y1, int x2, int y2, int l1, int l2, int l3, int l4)
	{
		xmin = x1;
		ymin = y1;
		xmax = x2;
		ymax = y2;
		p1x = l1;
		p1y = l2;
		p2x = l3;
		p2y = l4;
		for(int i = 0; i <= 3; i++)
			p1[i] = p2[i] = false;
		m = (p2y - p1y) / (p2x - p1x);
	}
	void display(int, int, int, int);
	void outcode();
	void cohen();
	void int_above();
	void int_below();
	void int_right();
	void int_left();
};

void clipping :: display(int p1, int p2, int p3, int p4)
{
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINES);
			glVertex2i(xmin, ymin);
			glVertex2i(xmin, ymax);
			glVertex2i(xmin, ymax);
			glVertex2i(xmax, ymax);
			glVertex2i(xmax, ymax);
			glVertex2i(xmax, ymin);
			glVertex2i(xmax, ymin);
			glVertex2i(xmin, ymin);
			
			glColor3f(0.0, 1.0, 0.0);
			glVertex2i(p1, p2);
			glVertex2i(p3, p4);
		glEnd();
		glFlush();
}

void clipping :: outcode()
{
		if(p1x < xmin)
			p1[3] = true;
		if(p1x > xmax)
			p1[2] = true;
		if(p1y < ymin)
			p1[1] = true;
		if(p1y > ymax)
			p1[0] = true;
			
		if(p2x < xmin)
			p2[3] = true;
		if(p2x > xmax)
			p2[2] = true;
		if(p2y < ymin)
			p2[1] = true;
		if(p2y > ymax)
			p2[0] = true;
		
		int i, j;
		for(i = 0; i <= 3; i++)
		{
			if(p1[i] == false)
				continue;
			else
				break;
		}
			
		for(j = 0; j <= 3; j++)
		{
			if(p2[j] == false)
				continue;
			else
				break;
		}
		
		if(i > 3 && j > 3)
		{
			display(p1x, p1y, p2x, p2y);
			return;
		}
		else
			cohen();
}

void clipping :: cohen()
{
	int i;
	for(i = 0; i <= 3; i++)
	{
		if((p1[i] && p2[i]) == false)
			continue;
		else
			break;
	}
	if(i < 3)
	{
		display(0, 0, 0, 0);
		return;
	}
	
	if(p1[0] == true || p2[0] == true)
		int_above();
	if(p1[1] == true || p2[1] == true)
		int_below();
	if(p1[2] == true || p2[2] == true)
		int_right();
	if(p1[3] == true || p2[3] == true)
		int_left();
	display(i1x, i1y, i2x, i2y);	
}

void clipping :: int_above()
{
 	i1x = p1x;
 	i1y = p1y;
 	i2x = p2x;
	i2y = p2y;
	if(p1[0] == true)
	{
		i1x = p1x + (ymax - p1y) / m;
		i1y = ymax;
	}
	if(p2[0] == true)
	{
		i2x = p2x + (ymax - p2y) / m;
		i2y = ymax;
	}	
}

void clipping :: int_below()
{
 	i1x = p1x;
 	i1y = p1y;
 	i2x = p2x;
	i2y = p2y;
	if(p1[1] == true)
	{
		i1x = p1x + (ymin - p1y) / m;
		i1y = ymin;
	}
	if(p2[1] == true)
	{
		i2x = p2x + (ymin - p2y) / m;
		i2y = ymin;
	}	
}

void clipping :: int_right()
{
 	i1x = p1x;
 	i1y = p1y;
 	i2x = p2x;
	i2y = p2y;
	if(p1[2] == true)
	{
		i1x = xmax;
		i1y = p1y + m * (xmax - p1x);
	}
	if(p2[2] == true)
	{
		i2x = xmax;
		i2y = p2y + m * (xmax - p2x);
	}	
}

void clipping :: int_left()
{
 	i1x = p1x;
 	i1y = p1y;
 	i2x = p2x;
	i2y = p2y;
	if(p1[3] == true)
	{
		i1x = xmin;
		i1y = p1y + m * (xmin - p1x);
	}
	if(p2[3] == true)
	{
		i2x = xmin;
		i2y = p2y + m * (xmin - p2x);
	}	
}

void temp()
{
	clipping c(x1, y1, x2, y2, l1x, l1y, l2x, l2y);
	c.outcode();
}

int main(int argc, char **argv)
{
	cout<<"\nEnter the co-ordinates of clipping window.";
	cout<<"\nXmin = ";
	cin>>x1;
	cout<<"\nYmin = ";
	cin>>y1;
	cout<<"\nXmax = ";
	cin>>x2;
	cout<<"\nYmax = ";
	cin>>y2;
	cout<<"\nEnter the co-ordinates of end points of the line.";
	cout<<"\nX1 = ";
	cin>>l1x;
	cout<<"\nY1 = ";
	cin>>l1y;
	cout<<"\nX2 = ";
	cin>>l2x;
	cout<<"\nY2 = ";
	cin>>l2y;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 150);
	glutInitWindowSize(500, 500);
	glutCreateWindow("BASIC CODE");
	init();
	glutDisplayFunc(temp);
	glutMainLoop();
	return 0;
}

/*x_min = 4, y_min = 4, x_max = 10, y_max = 8
A set of lines (Defined by two corner coordinates)
Line1: x1 = 5, y1 = 5, x2 = 7, y2 = 7
Line 2: x1 = 7, y1 = 9, x2 = 11, y2
Line 3: x1 = 1, y1 = 5, x2 = 4, y2 = 1
OUTPUT:
OUTPUT for Cohen-sutherland Algorithm
Line 1: Accepted from (5, 5) to (7, 7)
Line 2: Accepted from (7.8, 8) to (10, 5.25)
Line 3: Rejected*/
