/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "mandelbrot.h"
#include "triangle.h"
#include<math.h>
#include <allegro5/allegro_primitives.h>

#define RADIAN(x) (((x)*(M_PI))/180.0)



Cord_t CalculateCentreOfMass(Cord_t P1, Cord_t P2, Cord_t P3)
{
    Cord_t CM;
    (CM.x)= (P1.x + P2.x + P3.x)/3.0;
    (CM.y)= (P1.y + P2.y + P3.y)/3.0;
    return CM;
}

void CalculateCoordinates(Cord_t* P0, double LeftAngle, double RightAngle,double Lstart, Cord_t* P1, Cord_t* P2, Cord_t* P3)
{
    double angle_alpha = RADIAN(-LeftAngle);
    double angle_beta = RADIAN(RightAngle);     
    
    //double length1= Lstart*(1.0+ (tan(angle_alpha)*Lstart)/(tan(angle_alpha)+tan(angle_beta)));
    double length2= Lstart/(tan(angle_beta)/(tan(angle_alpha))+1.0);
    double length1= Lstart-length2;
    
    (P1->x)= (P0->x)-length1;
    (P2->x)= (P0->x)+length2; //calculo coordenadas en x de los tres vertices.
    (P3->x)= (P0->x);
    
    double height= length1*tan(angle_alpha);
    
    (P1->y)= (P0->y)+(height/3.0);
    (P2->y)= (P1->y);               //calculo coordenadas en y.
    (P3->y)= (P1->y)-height;
    
    
}



void RecursiveCentreOfMass(Cord_t P0, Cord_t P1,Cord_t P2,Cord_t P3, double lend, int* counter)
{
    double dist1= ((P2.x)-(P1.x))*((P2.x)-(P1.x))+((P2.y)-(P1.y))*((P2.y)-(P1.y)); //calculo distancias de cada linea al cuadrado
    double dist2=((P2.x)-(P3.x))*((P2.x)-(P3.x))+((P2.y)-(P3.y))*((P2.y)-(P3.y));
    double dist3=((P1.x)-(P3.x))*((P1.x)-(P3.x))+((P1.y)-(P3.y))*((P1.y)-(P3.y));
    counter++;
    if((*counter)> MAX_COUNT)
    {
        al_draw_line(P1.x,P1.y, P0.x, P0.y, al_color_name("red"), 1.0);//dibuja las lineas de union
        al_draw_line(P2.x,P2.y, P0.x, P0.y, al_color_name("red"), 1.0);//dibuja las lineas de union
        al_draw_line(P3.x,P3.y, P0.x, P0.y, al_color_name("red"), 1.0);//dibuja las lineas de union
    }
    else if((dist1<(lend*lend)) || (dist2<(lend*lend)) || (dist3<(lend*lend)))
    {
        
    }
    else
    {
        
        al_draw_line(P1.x,P1.y, P0.x, P0.y, al_color_name("red"), 1.0);//dibuja las lineas de union
        al_draw_line(P2.x,P2.y, P0.x, P0.y, al_color_name("red"), 1.0);//dibuja las lineas de union
        al_draw_line(P3.x,P3.y, P0.x, P0.y, al_color_name("red"), 1.0);//dibuja las lineas de union
        
       Cord_t CM= CalculateCentreOfMass( P1,  P2, P0);
        RecursiveCentreOfMass( CM,  P1, P2, P0,lend, counter); //calculo nuevo centro de masa y llamo de nuevo a la funcion
        
        CM= CalculateCentreOfMass(P2, P3, P0);
        RecursiveCentreOfMass(CM, P2, P3, P0, lend, counter);
        
        CM= CalculateCentreOfMass(P1, P3, P0);
        RecursiveCentreOfMass( CM, P1, P3, P0, lend, counter);
        
    }
}
    
void TriangleWrapper(void)
{
    int counter=0;
    double lend=0.2;
    Cord_t P0={350,350};
    Cord_t P1;
    Cord_t P2;
    Cord_t P3;
    CalculateCoordinates(&P0, -80.0, 60.0,100.0, &P1, &P2, &P3);
    
    al_draw_triangle(P1.x,P1.y, P2.x,P2.y, P3.x,P3.y, al_color_name("red"), 1.0);
    
    RecursiveCentreOfMass(P0, P1, P2, P3, lend, &counter);
    
           
}
   