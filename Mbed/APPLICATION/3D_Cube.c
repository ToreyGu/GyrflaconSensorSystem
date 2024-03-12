#include "3D_Cube.h"

#include "mymath.h"
#include "ssd1306.h"
#include "mpu6050.h"


float xx,xy,xz;
float yx,yy,yz;
float zx,zy,zz;
 
 
float fact;
 
 
int Xan,Yan;
 
 
int Xoff;
int Yoff;
int Zoff;
 

int LinestoRender;
int OldLinestoRender;


struct Line3d Lines[12];
struct Line2d Render[12];
struct Line2d ORender[12];


void SetVars(void)
{
    float Xan2,Yan2;
    float s1,s2,c1,c2;

    Xan2 = Xan / fact;
    Yan2 = Yan / fact;

    s1 = my_sin(Yan2);
    s2 = my_sin(Xan2);

    c1 = my_cos(Yan2);
    c2 = my_cos(Xan2);

    xx = c1;
    xy = 0;
    xz = -s1;

    yx = (s1 * s2);
    yy = c2;
    yz = (c1 * s2);

    zx = (s1 * c2);
    zy = -s2;
    zz = (c1 * c2);
}





void ProcessLine(struct Line2d *ret,struct Line3d vec)
{
    float zvt1;
    int xv1,yv1,zv1;

    float zvt2;
    int xv2,yv2,zv2;

    int rx1,ry1;
    int rx2,ry2;
    int x1;
    int y1;
    int z1;

    int x2;
    int y2;
    int z2;

    int Ok;

    x1=vec.p0.x;
    y1=vec.p0.y;
    z1=vec.p0.z;

    x2=vec.p1.x;
    y2=vec.p1.y;
    z2=vec.p1.z;

    // defaults to not OK
    Ok=0; 

    xv1 = (x1 * xx) + (y1 * xy) + (z1 * xz);
    yv1 = (x1 * yx) + (y1 * yy) + (z1 * yz);
    zv1 = (x1 * zx) + (y1 * zy) + (z1 * zz);

    zvt1 = zv1 - Zoff;


    if( zvt1 < -5){
    rx1 = 256 * (xv1 / zvt1) + Xoff;
    ry1 = 256 * (yv1 / zvt1) + Yoff;
    // ok we are alright for point 1.
    Ok=1;
    }


    xv2 = (x2 * xx) + (y2 * xy) + (z2 * xz);
    yv2 = (x2 * yx) + (y2 * yy) + (z2 * yz);
    zv2 = (x2 * zx) + (y2 * zy) + (z2 * zz);

    zvt2 = zv2 - Zoff;


    if( zvt2 < -5){
    rx2 = 256 * (xv2 / zvt2) + Xoff;
    ry2 = 256 * (yv2 / zvt2) + Yoff;
    } else
    {
    Ok=0;
    }

    if(Ok==1){
    ret->p0.x=rx1;
    ret->p0.y=ry1;

    ret->p1.x=rx2;
    ret->p1.y=ry2;
    }
}



void RenderImage(void)
{
    for (int i=0; i<OldLinestoRender; i++ )
    {
        OLED_Draw_Line(ORender[i].p0.x,ORender[i].p0.y,ORender[i].p1.x,ORender[i].p1.y, 0);
    }


    for (int i=0; i<LinestoRender; i++ )
    {
        OLED_Draw_Line(Render[i].p0.x,Render[i].p0.y,Render[i].p1.x,Render[i].p1.y, 1);
    }
    OldLinestoRender=LinestoRender;
    
    OLED_Refresh_Gram();
}



void CubeInit(void)
{
    fact = 180 / 3.14159265358979323846264338327950;
    
    Xoff = 90;
    
    Yoff = 32;
    
    Zoff = 750; 
    
    Lines[0].p0.x=-50;
    Lines[0].p0.y=-50;
    Lines[0].p0.z=50;
    Lines[0].p1.x=50;
    Lines[0].p1.y=-50;
    Lines[0].p1.z=50;

    Lines[1].p0.x=50;
    Lines[1].p0.y=-50;
    Lines[1].p0.z=50;
    Lines[1].p1.x=50;
    Lines[1].p1.y=50;
    Lines[1].p1.z=50;

    Lines[2].p0.x=50;
    Lines[2].p0.y=50;
    Lines[2].p0.z=50;
    Lines[2].p1.x=-50;
    Lines[2].p1.y=50;
    Lines[2].p1.z=50;

    Lines[3].p0.x=-50;
    Lines[3].p0.y=50;
    Lines[3].p0.z=50;
    Lines[3].p1.x=-50;
    Lines[3].p1.y=-50;
    Lines[3].p1.z=50;


    //back face.

    Lines[4].p0.x=-50;
    Lines[4].p0.y=-50;
    Lines[4].p0.z=-50;
    Lines[4].p1.x=50;
    Lines[4].p1.y=-50;
    Lines[4].p1.z=-50;

    Lines[5].p0.x=50;
    Lines[5].p0.y=-50;
    Lines[5].p0.z=-50;
    Lines[5].p1.x=50;
    Lines[5].p1.y=50;
    Lines[5].p1.z=-50;

    Lines[6].p0.x=50;
    Lines[6].p0.y=50;
    Lines[6].p0.z=-50;
    Lines[6].p1.x=-50;
    Lines[6].p1.y=50;
    Lines[6].p1.z=-50;

    Lines[7].p0.x=-50;
    Lines[7].p0.y=50;
    Lines[7].p0.z=-50;
    Lines[7].p1.x=-50;
    Lines[7].p1.y=-50;
    Lines[7].p1.z=-50;

    // now the 4 edge lines.

    Lines[8].p0.x=-50;
    Lines[8].p0.y=-50;
    Lines[8].p0.z=50;
    Lines[8].p1.x=-50;
    Lines[8].p1.y=-50;
    Lines[8].p1.z=-50;

    Lines[9].p0.x=50;
    Lines[9].p0.y=-50;
    Lines[9].p0.z=50;
    Lines[9].p1.x=50;
    Lines[9].p1.y=-50;
    Lines[9].p1.z=-50;

    Lines[10].p0.x=-50;
    Lines[10].p0.y=50;
    Lines[10].p0.z=50;
    Lines[10].p1.x=-50;
    Lines[10].p1.y=50;
    Lines[10].p1.z=-50;

    Lines[11].p0.x=50;
    Lines[11].p0.y=50;
    Lines[11].p0.z=50;
    Lines[11].p1.x=50;
    Lines[11].p1.y=50;
    Lines[11].p1.z=-50;
    
    LinestoRender=12;
    OldLinestoRender=LinestoRender;

}



void DrawCube(void)
{
    int xOut=0;
    int yOut=0;

    xOut = map(mpu6050.Acc.x,-4096,4096,-50,50);
    yOut = map(mpu6050.Acc.x,-4096,4096,-50,50);

    Xan+=xOut;
    Yan+=yOut;
    
    Yan=Yan % 360;
    Xan=Xan % 360;
    
    SetVars();
    
    for(int i=0; i<LinestoRender ; i++)
    {
        // stores the old line segment so we can delete it later.
        ORender[i]=Render[i];
        // converts the 3d line segments to 2d.
        ProcessLine(&Render[i],Lines[i]); 
    }

    RenderImage(); 
}


