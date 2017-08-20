/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: ezequiel
 *
 * Created on August 20,/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: ezequiel
 *
 * Created on August 19, 2017, 3:51 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro_color.h>
#include "allegro5/allegro5.h"
#include <time.h>
#include "mandelbrot.h"





/*
 * 
 */
int main(int argc, char** argv) 
{
    
    ALLEGRO_DISPLAY *  display = NULL;
    
    if(!al_init())
        {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}
    
    
        
        
	display = al_create_display(700, 700); // Intenta crear display de 500x500 de fallar devuelve NULL
	if(!display)
        {
		fprintf(stderr, "no se logro crear el display\n");
		return -1;
	}
        al_set_target_backbuffer(display);
        
        Cord_t DisplayMax={700.0,700.0};
        Cord_t P0={-2.0,-2.0};
        Cord_t Pf={2.0,2.0};
        
        DrawMandelbrot(&P0, &Pf);
        al_flip_display();
        sleep(10);
        al_destroy_display(display); //cierra el display y libera la memoria del mismo.
	return 0;
        
        
    return (EXIT_SUCCESS);
}









