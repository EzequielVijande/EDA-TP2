/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "mandelbrot.h"

void GetComplexNumber(Cord_t* P0, Cord_t* Pf, Cord_t* DisplayMax, Cord_t* DisplayPoint, Cord_t* result)
{
    (result->x) = (DisplayPoint->x)*(((Pf->x)-(P0->x))/(DisplayMax->x))+(P0->x);
    (result->y) = (DisplayPoint->y)*(((P0->y)-(Pf->y))/(DisplayMax->y))+(Pf->y);
    
}



double CalculatePlaneRadius(Cord_t* P0, Cord_t* Pf)
{
    if((((Pf->x)-(P0->x))*((Pf->x)-(P0->x)))< (((Pf->y)-(P0->y))*((Pf->y)-(P0->y))))
    {
        return (((Pf->x)-(P0->x))*((Pf->x)-(P0->x)));
        //Si el eje x del plano es el mas grande, devuelve este como radio
    }
    else
    {
        return (((Pf->y)-(P0->y))*((Pf->y)-(P0->y)));
        //En el caso contario devuelve el eje y como radio.
    }
    
}

void DrawMandelbrot(Cord_t* P0, Cord_t* Pf)
{
    ALLEGRO_BITMAP* bitmap= al_get_target_bitmap();
    Cord_t Number={0.0,0.0}; //Numero complejo asociado a un determinado pixel
    Cord_t DisplayDot={0.0,0.0}; //representa las coordenadas de los pixels en el display
    Cord_t result={0.0,0.0};
    Cord_t DisplayMax={al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap)};
    double PreviousResultX=0.0;
    int row;
    int col;
    int iteration = 0;
    double radius = CalculatePlaneRadius(P0, Pf);
    char* color = NULL;
    al_lock_bitmap(bitmap, al_get_bitmap_format(bitmap), ALLEGRO_LOCK_WRITEONLY);
    
    for (row = 0; row < (DisplayMax.y); row++) 
    {
        for (col = 0; col < (DisplayMax.x); col++)
        {
            DisplayDot.y= row;
            DisplayDot.x= col;
            
            GetComplexNumber( P0, Pf, &DisplayMax, &DisplayDot, &Number);
            result.x=0.0;
            result.y=0.0;
            
            
            iteration = 0;
                while (( ((result.x)*(result.x)+(result.y)*(result.y) ) < radius) && (iteration < LIMIT))
                {
                    PreviousResultX= result.x;
                    result.x=(result.x)*(result.x) - (result.y)*(result.y) + (Number.x);
                    result.y= 2.0*(PreviousResultX)*(result.y) + (Number.y);
                    iteration++;
                }
            
            color= AnalyzeColor(iteration);
            al_put_pixel((DisplayDot.x), (DisplayDot.y), al_color_name(color));
             
        }
    }
    al_unlock_bitmap(bitmap);
}

char* AnalyzeColor(int iteration)
{
    if ((iteration < LIMIT)&&(iteration>(LIMIT-OFFSET)))
    {
        return "gray";
    }
    
    else if ((iteration <= (LIMIT-OFFSET))&&(iteration>(LIMIT-2*OFFSET)))
    {
        return "blue";
    }
            
    else if ((iteration <= (LIMIT-2*OFFSET))&&(iteration>(LIMIT-3*OFFSET)))
    {
        return "blueviolet";
    }
    
    else if ((iteration <= (LIMIT-3*OFFSET))&&(iteration>(LIMIT-5*OFFSET)))
    {
        return "aqua";
    }
            
    else if(iteration == LIMIT)
    {
        return "black";
    }
    
    else 
    {
        return "white";
    } 
}