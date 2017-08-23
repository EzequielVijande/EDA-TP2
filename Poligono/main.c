
/* 
 * File:   main.c
 * Author: tom
 *
 * Created on August 20, 2017, 9:26 PM
 */

#include <math.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro_color.h>
#include "allegro5/allegro5.h"
#include <time.h>

typedef struct
{
	double x;
	double y;
} Cord_t;

void poligono_fractal(double lstart, double lend, int ladosPoligono, Cord_t centro, double lconstant, char color);
			//Devuelve si se pudo efctuar el dibujo, 0 si no se logro


int main(void)
{
    ALLEGRO_DISPLAY *  display = NULL;
    
    if(!al_init())
    {
		fprintf(stderr, "Failed to initialize allegro!\n");
		return -1;
	}
    
	if(!al_init_primitives_addon())
    {
        fprintf(stderr, "Failed to initialize primitives addon\n");
        return -1;
    }
        
	display = al_create_display(700,700); // Intenta crear display de 500x500 de fallar devuelve NULL
	if(!display)
    {
		fprintf(stderr, "No se logro crear el display\n");
		return -1;
	}
    
	char color = 'm';
	
	al_set_target_backbuffer(display);
    Cord_t coord1 = {350.0, 350.0};
	poligono_fractal(100.0, 1.5, 5, coord1, 0.4, color);
		
	al_flip_display();
    sleep(10);
    al_destroy_display(display); //cierra el display y libera la memoria del mismo.
     
        
    return 0;
}


void poligono_fractal(double lstart, double lend, int ladosPoligono, Cord_t centro, double lconstant, char color)
{
	int k;
	
	int numeroColor;
	
	switch(color)
	{
		case 'r': numeroColor = 0; break;
		case 'g': numeroColor = 1; break;
		case 'b': numeroColor = 2; break;
		case 'c': numeroColor = 3; break;
		case 'm': numeroColor = 4; break;
		case 'y': numeroColor = 5; break;
		default: numeroColor = 0; break;
	}
		
	char * coloresTabla [] = {"red","green","blue","green","blue","cyan","magenta","yellow"};

	double radio = lstart/(2.0*sin(M_PI / ladosPoligono));

	Cord_t vertice1 = {0.0, 0.0};								//radio*(sqrt(2) / 2)*((exp(I*(M_PI / (ladosPoligono * 4))));			//	M_PI*(1 + 8K) / 4*n
	Cord_t vertice2 = {0.0, 0.0};								//radio*(sqrt(2) / 2)*((exp(I*((M_PI * 9) / (ladosPoligono * 4)))));

	if (lstart >= lend)
	{
		for (k = 0; k < ladosPoligono; k++)
		{
			vertice1.x = (sin(k/((double)ladosPoligono) *2.0* (double)M_PI ) * radio) + (centro.x);			//M_PI*(1 + 8*K) / 4 * n
			vertice1.y = (cos(k/((double)ladosPoligono) *2.0* (double)M_PI ) * radio) + (centro.y);	
                       
	        vertice2.x = (sin((k+1)/((double)ladosPoligono) *2.0* (double)M_PI ) * radio) + (centro.x);			//M_PI*(1 + 8*K) / 4 * n
			vertice2.y = (cos((k+1)/((double)ladosPoligono) *2.0* (double)M_PI ) * radio) + (centro.y);
                        
		    poligono_fractal(lstart*lconstant, lend, ladosPoligono, vertice2, lconstant, color);	//Eligo como nuevo centro el ultimo vertice de la linea
																									//y dibujo un poligono de orden n centrad en el mismo.
		   
			al_draw_line(vertice1.x,vertice1.y , vertice2.x, vertice2.y , al_color_name(coloresTabla[numeroColor]),1.0); //dibujo la linea entre dos vertices
		}
	}
}