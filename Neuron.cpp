#include "lib.h"

#define MAX 1000
#define FLAG 0
const double K = 0.3;

double random_float(double min, double max)
{
    return min + ((max - min)*rand())/RAND_MAX;
}

double sigmoid(double x)
{
    return 1./(1. + std::exp(-x));
}

void Neuron::study(void)
{
    int count = 0;
    while (count < MAX) {
        int success = 0;
        for (std::vector<struct pt>::iterator it = this->data.begin(); it != this->data.end(); it++) {
            double hidden[DEP] = {0.0};
            for (int i = 0; i < DEP; i++) {
                for (int j = 0; j < SIZE; j++) {
                    hidden[i] += it->val[j]*v1[i][j];
                }
                hidden[i] += this->v1[i][SIZE];
                hidden[i] = sigmoid(hidden[i]);
            }
            double result = 0.0;
            for (int i = 0; i < DEP; i++) {
                result += hidden[i]*this->v2[i];
            }
            result += v2[DEP];
            result = sigmoid(result);

            if (FLAG) {
                if ((result > 0.5 && it->type == 1.0)||(result <= 0.5 && it->type == 0.0)) {
                    std::cout << it->val[0] << " " << it->val[1] << " " << result << std::endl;
                    success++;
                }
            }
            for (int i = 0; i < DEP; i++) {
                double p = hidden[i]*(it->type - result)*result*(1.0 - result);
                for (int j = 0; j < SIZE; j++) {
                    this->v1[i][j] += it->val[j]*p*this->v2[i]*hidden[i]*(1.0 - hidden[i])*K;
                }
                this->v1[i][SIZE] += p*this->v2[i]*hidden[i]*(1.0 - hidden[i])*K;
                this->v2[i] += K*p;
            }
            this->v2[DEP] += K*(it->type - result)*result*(1.0 - result);
        }
        if (FLAG) {
            std::cout << success << std::endl;
            std::cout << ((double)success/(double)this->data.size())*100.0 << "%" << std::endl;
        }
        count++;
    }
    std::cout << "finish" << std::endl;
}

int Neuron::output(double value[SIZE])
{
    if (FLAG) std::cout << std::endl;
    double hidden[DEP] = {0.0};
    for (int i = 0; i < DEP; i++) {
        for (int j = 0; j < SIZE; j++) {
            hidden[i] += value[j]*this->v1[i][j];
        }
        hidden[i] += this->v1[i][SIZE];
        hidden[i] = sigmoid(hidden[i]);
        if (FLAG) std::cout << hidden[i] << " ";
    }
    if (FLAG) std::cout << std::endl;
    double result = 0.0;
    for (int i = 0; i < DEP; i++) {
        result += hidden[i]*this->v2[i];
    }
    result += this->v2[DEP];
    result = sigmoid(result);
    if (FLAG) {
        for (int i = 0; i < SIZE; i++) {
            std::cout << value[i] << " ";
        }
        std::cout << std::endl;
        std::cout << result << std::endl;
    }
    if (result > 0.5) return 1;
    else return 0;
}

void Neuron::show_para(void)
{
    std::cout << std::endl;
    std::cout << "v1" << std::endl;
    for (int i = 0; i < DEP; i++) {
        for (int j = 0; j < SIZE + 1; j++) {
            std::cout << v1[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "v2" << std::endl;
    for (int i = 0; i < DEP + 1; i++) {
        std::cout << v2[i] << " ";
    }
    std::cout << std::endl;
}
