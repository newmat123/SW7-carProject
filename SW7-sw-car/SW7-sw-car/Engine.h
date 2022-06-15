/*
 * Motor.h
 *
 * Created: 09/05/2022 10.53
 *  Author: nicklas
 */ 

#pragma once

#include <stdbool.h>

//Functions
void initEngine();
void pwmEngine(unsigned char speed);
void direction(bool fwd);
void pwmAcceleration(unsigned char num);
bool changingSpeed();

//test
void testEngine();