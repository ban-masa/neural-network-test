#pragma once

#define SIZE 2
#define DEP 3

#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>
double random_float(double min, double max);
#include "Neuron.h"


struct pt {
    double val[SIZE];
    double type;
};

