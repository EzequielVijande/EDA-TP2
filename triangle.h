/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   trinalge.h
 * Author: ezequiel
 *
 * Created on August 24, 2017, 7:31 AM
 */

#ifndef TRINALGE_H
#define TRINALGE_H

#include "mandelbrot.h"
#include<math.h>
#include <allegro5/allegro_primitives.h>

#define RADIAN(x) (((x)*(M_PI))/180.0)
#define MAX_COUNT 200


Cord_t CalculateCentreOfMass(Cord_t P1, Cord_t P2, Cord_t P3);

void CalculateCoordinates(Cord_t *P0, double LeftAngle, double RightAngle,double Lstart, Cord_t* P1, Cord_t* P2, Cord_t* P3);


void TriangleWrapper(void);

void RecursiveCentreOfMass(Cord_t P0, Cord_t P1,Cord_t P2,Cord_t P3, double lend, int* counter);
//Dibuja las lineas entre vertices y nuevos centros de masa

#endif /* TRINALGE_H */

