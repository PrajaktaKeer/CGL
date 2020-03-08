#include<stdio.h> 
  #include<GL/glut.h> 
  #include<math.h> 
  int ww=1200,wh=800; 
  int xi,yi,xf,yf,r;
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

 void bresenhamAlg (int x0, int y0, int x1, int y1) 
  { 
  int dx = abs (x1 - x0); 
  int dy = abs (y1 - y0); 
  int x, y; 
  if (dx >= dy) 
  { 
   int d = 2*dy-dx; 
   int ds = 2*dy; 
   int dt = 2*(dy-dx); 
       if (x0 < x1)  
       { 
            x = x0; 
            y = y0; 
       } 
        else 
        {  
             x = x1; 
             y = y1; 
             x1 = x0; 
             y1 = y0; 
        } 
       putpixel (x, y); 
   while (x < x1) 
   { 
        if (d < 0) 
        d += ds; 
        else { 
             if (y < y1) { 
              y++; 
              d += dt; 
             }  
             else { 
              y--; 
              d += dt; 
             } 
            } 
   x++; 
        putpixel (x, y); 
       }  }
       else {  
             int d = 2*dx-dy; 
             int ds = 2*dx; 
             int dt = 2*(dx-dy); 
             if (y0 < y1) { 
             x = x0; 
             y = y0; 
             } 
             else {  
             x = x1; 
             y = y1; 
             y1 = y0; 
             x1 = x0; 
             } 
            putpixel (x, y);  
        while (y < y1) 
        { 
              if (d < 0) 
                 d += ds; 
              else { 
                      if (x > x1){ 
                      x--; 
                      d += dt; 
                 } else { 
                      x++; 
                      d += dt; 
                   } 
              } 
              y++;
              putpixel (x, y); 
        } 
       } 
  } 
 void triangle (int ix , int iy)
 {
    int x=ix, y=iy,x1,x2,y1,y2;
    x1=xi+(x-xi)*cos(theta)-(y-yi)*sin(theta);
    y1=yi-r/2;
    x2=xi+(x-xi)*cos(theta)+(y-yi)*sin(theta);
    y2=yi-r/2;;
    bresenhamAlg (x, y, x1, y1);
    bresenhamAlg (x, y, x2, y2);
    bresenhamAlg (x1, y1, x2, y2);
 }
 void display() 
  { 
        glClearColor(0.4,0.7,0.2,1.0); 
        glColor3f(0.5,0.3,0.0); 
        glClear(GL_COLOR_BUFFER_BIT); 
        glutSwapBuffers();
        Bresenham_circle(xi,yi,r);
        Bresenham_circle(xi,yi,r/2);
        triangle(xi,(yi+r));
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
