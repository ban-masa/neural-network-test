#pragma once
#include <iostream>
#include <ctime>
class Neuron {
public:
    Neuron() {
        srand((unsigned)time(NULL));
        double range = std::sqrt(6)/std::sqrt(DEP + SIZE + 2);
        std::srand ((unsigned) (std::time(NULL)));

        for (int i = 0; i < DEP; i++) {
            for (int j = 0; j < SIZE + 1; j++) {
                v1[i][j] = (double)2*range*std::rand()/RAND_MAX - range;

            }
        }
        for (int i = 0; i < DEP + 1; i++) {
            v2[i] = (double)2*range*std::rand()/RAND_MAX - range;
        }
    }

    std::vector<struct pt> data;
    double v1[DEP][SIZE + 1];
    double v2[DEP + 1];

    void study(void);
    int output(double value[SIZE]);
    void show_para(void);
};
