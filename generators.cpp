#include "generators.h"
#include <vector>
#include <random>
#include <ctime>
#include <iostream>
#include <cmath>

std::mt19937 gen(time(0));
std::uniform_real_distribution<> urd(0, 1);

double getRand() { //случайное число от 0 до 1
  double x;
  x = urd(gen);
  return x;
}

int getRandErlang2p(int a) { //распределение Эрланга 2-го порядка со средним а
  
  int x;
  double x1, x2;
  x1 = urd(gen);
  x2 = urd(gen);
  x = round(-log(x1 * x2) * a);
  return x;
}

int getRandUni(int a, int b) { //равномерное распределение
  int x;
  double x1;
  x1 = urd(gen);
  x = round(a + (b - a) * x1);
  return x;
}

int getRandNorm(int m, int q) { //нормальное распределение n=12
  int x;
  double sum=0;
  for (int i = 0; i < 12; i++) {sum += urd(gen);}
  x = round(m + q * (sum - 6));
  return x;
}

