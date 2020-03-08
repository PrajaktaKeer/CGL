#include <iostream>
#include<stdio.h>
#include<math.h>
#include<GL/glut.h>
using namespace std;
GLfloat chess[3][20]=
{
{50.0,50.0,100.0,100.0,150.0,150.0,200.0,200.0,250.0,250.0,50.0,250.0,50.0,250.0,50.0,250.0,50.0,250.0,50.0,250.0},{50.0,250.0,50.0,250.0,50.0,250.0,50.0,250.0,50.0,250.0,50.0,50.0,100.0,100.0,150.0,150.0,200.0,200.0,250.0,250.0},
{1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0}  };
GLfloat rot_mat[3][3]={{0},{0},{0}};
GLfloat result[3][20]={{0},{0},{0}};
GLfloat theta;
int count=0;
struct Point
{
	GLint x;
	GLint y;
};

struct Color
{
	GLfloat r;
	GLfloat g;
	GLfloat b;
};

void multiply()
{
	int i,j,l;
	for(i=0;i<3;i++)
	{
		for(j=0;j<20;j++)
		{
			result[i][j]=0;
			for(l=0;l<3;l++)
			{
				result[i][j]+=rot_mat[i][l]*chess[l][j];
			}
		}
	}
}

void drawline(int xx1,int yy1,int xx2,int yy2)
{
	float x,y,dx,dy,e,temp;
	int i,s1,s2,ex;
	dx=abs(xx2-xx1);
	dy=abs(yy2-yy1);
	x=xx1;
	y=yy1;
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
	if(xx2>xx1)
	{
		s1=1;
	}
	if(xx2==xx1)
	{
		s1=0;
	}
	if(xx2<xx1)
	{
		s1=-1;
	}
	if(yy2>yy1)
	{
		s2=1;
	}
	if(yy2==yy1)
	{
		s2=0;
	}
	if(yy2<yy1)
	{
		s2=-1;
	}
	if(dy>dx)
	{
		temp=dx;
		dx=dy;
		dy=temp;
		ex=1;
	}
	else
	{
		ex=0;
	}

	e=2*dy-dx;
	i=1;
	do
	{
		while(e>=0)
		{
			if(ex==1)
			{
				x=x+s1;
			}
			else
			{
				y=y+s2;
			}
			e=e-2*dx;
		}
		if(ex==1)
		{
			y=y+s2;
		}
		else
		{
			x=x+s1;
		}
		e=e+2*dy;
		glBegin(GL_POINTS);
		glVertex2i(x,y);
		glEnd();
		i=i+1;
	}while(i<=dx);
}

void rotate()
{
	rot_mat[0][0]=1;
	rot_mat[0][1]=0;
	rot_mat[0][2]=0;
	rot_mat[1][0]=0;
	rot_mat[1][1]=cos(theta);
	rot_mat[1][2]=50;
	rot_mat[2][0]=0;
	rot_mat[2][1]=0;
	rot_mat[2][2]=1;
	multiply();
}

void drawchess()
{
	int i;
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_POINT);
	for(i=0;i<19;i=i+2)
	{
		drawline(chess[0][i],chess[1][i],chess[0][i+1],chess[1][i+1]);
	}
	glEnd();
}

void drawrotatedchess()
{
	int i;
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_POINTS);
	for(i=0;i<19;i=i+2)
	{
		drawline(result[0][i],result[1][i],result[0][i+1],result[1][i+1]);
	}
	glEnd();

}

Color getPixelColor(GLint x,GLint y)
{
	Color color;
	glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,&color);
	return color;
}

void setPixelColor(GLint x,GLint y,Color color)
{
	color.r=0.0;
	color.g=0.0;
	color.b=0.0;
	glColor3f(color.r,color.g,color.b);
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
	glFlush();

}

void floodfill(GLint x,GLint y,Color oldColor,Color newColor)
{
	Color color;
	color=getPixelColor(x,y);
	if(color.r==oldColor.r && color.g==oldColor.g && color.b==oldColor.b)
	{
		setPixelColor(x,y,newColor);
		floodfill(x+1,y,oldColor,newColor);
		floodfill(x,y+1,oldColor,newColor);
		floodfill(x-1,y,oldColor,newColor);
		floodfill(x,y-1,oldColor,newColor);
	}
}

void mykeyboard(unsigned char key,int mouseX,int mouseY)
{
	int i,j,t;
	Color newColor={0.0f,0.0f,0.0f};
	Color oldColor={1.0f,1.0f,1.0f};
	switch(count)
	{
	case 0:
		glClear(GL_COLOR_BUFFER_BIT);
		rotate();
		drawrotatedchess();
		break;
	case 1:
		for(j=0;j<4;j++)
		{
			for(i=0;i<2;i++)
			{
				if(j%2==0)
				{
					t=0;
				}
				else
				{
					t=50;
				}
				floodfill(75+(i*100)+t,100+((50*j)*cos(theta)),oldColor,newColor);

			}
		}
		break;
	}
	count=count+1;
	glFlush();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	drawchess();
	glFlush();
}

void init()
{
	glClearColor(1.0,1.0,1.0,0.0);
	glColor3f(0.0,0.0,0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,500,0,500);
}

int main(int argc,char **argv)
{
	theta=45*3.142/180.0;
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Chess Rotation");
	glutDisplayFunc(display);
	init();
	glutKeyboardFunc(mykeyboard);
	glutMainLoop();
	return 0;
}

