/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   mandelbrot.h
 * Author: ezequiel
 *
 * Created on August 20, 2017, 12:41 PM
 */

#ifndef MANDELBROT_H
#define MANDELBROT_H

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro_color.h>
#include "allegro5/allegro5.h"

#define LIMIT 255
#define OFFSET 50
typedef struct{
    double x;
    double y;
}Cord_t;

void GetComplexNumber(Cord_t* P0, Cord_t* Pf, Cord_t* DisplayMax, Cord_t* DisplayPoint, Cord_t* result);
//Funcion que dado los dos numeros complejos que forman un plano y un punto
//del display calcula su equivalente en el plano.Recibe los puntos iniciales y finales del
//plano, la coordenada maxima del display, la coordenada del display que se desea calcular,
//y un puntero a donde se desea guardar el resultado.


void DrawMandelbrot(Cord_t* P0, Cord_t* Pf);
//Funcion que efectua la funcion de Mandelbrot sobre un punto hasta que diverga
//o hasta llegar al limite de iteraciones

double CalculatePlaneRadius(Cord_t* P0, Cord_t*Pf);
//Funcion que reciba dos numeros complejos que definen las esquinas opuestas
//de un plano y calcula el cuadrado del radio en el que esta encerrado el plano.

char* AnalyzeColor(int iteration);


#endif /* MANDELBROT_H */

