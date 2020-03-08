#include<stdio.h> 
  #include<GL/glut.h> 
  #include<math.h> 
  int ww=1200, wh=800; 
  int xi, yi, xf, yf, r;
  float theta=2.0933;

 void putpixel(int x,int y) 
  { 
       glBegin(GL_POINTS); 
       glVertex2i(x,y); 
       glEnd(); 
       glFlush(); 
  } 
  double round(double n) 
  { 
       return (n>=0)?(int)(n+0.5):(int)(n-0.5); 
  } 
  void Bresenham_circle(int xc, int yc, int xr) 
  { 
        int x=0,y=xr;
        int d=3-2*y;
        while(x<=y){ 
        putpixel(x+xc, y+yc); 
        putpixel(xc+y, yc+x); 
        putpixel(xc-x, yc+y); 
        putpixel(xc-x, yc-y); 
        putpixel(xc-y, yc+x); 
        putpixel(xc-y, yc-x); 
        putpixel(xc+y, yc-x); 
        putpixel(xc+x, yc-y); 
            if(d<0) 
                 d=d+(4*x)+6; 
            else{ 
                 d=d+(4*(x-y))+10; 
                 y--; 
            } 
            x++; 
       } 
  } 

 void display() 
  { 
        glClearColor(0.4,0.7,0.2,1.0); 
        glColor3f(0.5,0.3,0.0); 
        glClear(GL_COLOR_BUFFER_BIT); 
        glutSwapBuffers();
        Bresenham_circle(xi,yi,r);
        Bresenham_circle(xi + ((3*r)/4), yi, r / 4);
        Bresenham_circle(xi + (3 * r /( 4* 1.414)) , yi + (3 * r /( 4* 1.414)), r / 4);
        Bresenham_circle(xi , yi + ((3*r)/4), r / 4);
          Bresenham_circle(xi - (3 * r /( 4* 1.414)) , yi -(3 * r /( 4* 1.414)), r / 4);
          
          
            Bresenham_circle(xi + (3 * r /( 4* 1.414)) , (yi -(3 * r /( 4* 1.414))), r / 4);
              Bresenham_circle((xi - (3 * r /( 4* 1.414))) , yi + (3 * r /( 4* 1.414)), r / 4);
            Bresenham_circle(xi , yi - ((3*r)/4), r / 4);
           Bresenham_circle(xi -((3*r)/4), yi, r / 4);
          
          
        Bresenham_circle(xi, yi ,r / 2);
         Bresenham_circle(xi, yi ,(r /2 -(r/8)));
         Bresenham_circle(xi, yi ,(r+(r/8)));
        glFlush(); 
  } 
 

  void myinit() 
  { 
        glViewport(0,0,ww,wh); 
        glMatrixMode(GL_PROJECTION); 
        glLoadIdentity(); 
        gluOrtho2D(0.0,(GLdouble)ww,0.0,(GLdouble)wh); 
        glMatrixMode(GL_MODELVIEW); 
  } 
  int main(int argc,char** argv) 
  { 
    printf("enter centre of the circle");
    scanf("%d%d",&xi,&yi);
    printf("\nenter radius of circle");
    scanf("%d",&r);      
    glutInit(&argc,argv); 
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
    glutInitWindowSize(ww,wh); 
    glutCreateWindow("Bresenham-Circle"); 
    myinit();
    glutDisplayFunc(display); 
    glutMainLoop(); 
    return 0; 
  } 
