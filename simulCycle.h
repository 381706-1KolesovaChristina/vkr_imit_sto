#include <vector>
#include <iostream>
#include <limits.h>
#include "generators.h"
#include "request.h"
#include "queue.h"
#include "servDevice.h"

int getGenRand(int raspr, int param1, int param2); // выбор генератора распределения
std::vector<int> getVecTimeReq(int time, int raspr, int param1, int param2); // гененерация времен поступления заявок
int devType(Req a); // выбор типа бокса
int getIndMin(std::vector<Dev> a); // поиск мин. ожидания
std::vector<int> simulCycl(int time, int raspr, int param1, int param2, double pr_to,
  double pr_torem, double pr_r1, std::vector<int> vecDefiTime,
  std::vector<int>  vecDefiCost, int numTO, int numRem, int numUni); // основной цикл
