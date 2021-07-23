#include <vector>
//#include <random>
#include <ctime>
#include <iostream>
#include <algorithm>
#include "generators.h"
#include "request.h"
#include "queue.h"
#include "servDevice.h"
#include "simulCycle.h"


int main()
{
  setlocale(LC_ALL, "Russian");
  int time, raspr, param1, param2;
 // std::vector<int> reqTime;

  time = 10080;
  raspr = 1;
  param1 = 14;
  param2 = 0;
 // std::cout << 0 << std::endl;
//  reqTime = getVecTimeReq(time, raspr, param1, param2);
//  reqTime.push_back(time);
  //std::cout << 1 << std::endl;
 // std::vector<int> timeBuff;

 // for (int i = 0; i < reqTime.size(); i++) { std::cout << reqTime[i] << std::endl; }
 // std::cout << 2 << std::endl;
  double pr_to, pr_torem, pr_r1;
  std::vector<int> vecDefiTime = { 10, 55, 12, 45, 45, 5, 80, 150 };
  std::vector<int>  vecDefiCost = { 100, 400, 50, 450, 100, 1400, 350, 2550 };

  pr_to = 0.36;
  pr_torem = 0.12; 
  pr_r1 = 0.64;

//  pr_torem *= pr_to;
//  pr_r2 = pr_r1 / 3;
//  pr_r1 = pr_to + pr_r2;
//  pr_r2 += pr_r1;

  int numTO, numRem, numUni;

  numTO = 4;
  numRem = 4;
  numUni = 0;

  std::vector<int> res = simulCycl(time, raspr, param1, param2, pr_to, pr_torem, pr_r1, vecDefiTime,
    vecDefiCost, numTO, numRem, numUni);

  for (int i = 0; i < 18; i++)
  {
    std::cout << res[i] << std::endl;
  }

/*  std::vector<Dev> devTO(numTO);
  std::vector<Dev> devRem(numRem);
  std::vector<Dev> devUni(numUni);

  std::vector<Req> allReq;
  std::vector<int> inReq;
  std::vector<int> buffReq;
  //std::vector<Req> outReq;

  for (int i = 0; i < reqTime.size() - 1; i++) {
    allReq.push_back(Req(reqTime[i], pr_to, pr_torem, pr_r1, pr_r2, vecDefiTime, vecDefiCost));
  }

  for (int i = 0; i < reqTime.size()-1; i++) {
    //allReq.push_back(Req(reqTime[i], pr_to, pr_torem, pr_r1, pr_r2, vecDefiTime, vecDefiCost));
    timeBuff.push_back(allReq[i].reqTime);
    inReq.push_back(i);
    //std::cout << 3 << std::endl;
    while (timeBuff.size() != 0) {
      

      for (int j = 0; j < numTO; j++) {
        devTO[j].checkDev(timeBuff[0]);
      }// std::cout << "que " << devTO[j].numbReqInQue() << std::endl;}
      for (int j = 0; j < numRem; j++) { devRem[j].checkDev(timeBuff[0]); }// std::cout << "que " << devRem[j].numbReqInQue() << std::endl;
      //}
      for (int j = 0; j < numUni; j++) { devUni[j].checkDev(timeBuff[0]); }// std::cout << "que " << devUni[j].numbReqInQue() << std::endl;
     // }
     // std::cout << 4 << std::endl;
      if (buffReq.size() != 0)
      {
      for (int k = 0; k < buffReq.size(); k++) {
        if ((allReq[buffReq[k]].queTime[0] == -1) & (allReq[buffReq[k]].servReq[1] == 1)) {
          inReq.push_back(buffReq[k]);
          timeBuff.push_back((allReq[buffReq[k]].reqTime + allReq[buffReq[k]].repairTime[1] + allReq[buffReq[k]].queTime[1]));
        }
        else {
          if ((allReq[buffReq[k]].servReq[0] == 1) & (allReq[buffReq[k]].servReq[1] == 1)) {
            buffReq.erase(buffReq.cbegin() + k);
          }
        }
      }
      }
     // std::cout << 5 << std::endl;
      while (inReq.size() != 0) {
        int ind1, ind2;
        switch (devType(allReq[inReq[0]]))
        {
        case 1:
          if ((devTO.size() != 0) & (devUni.size() != 0)) {
            ind1 = getIndMin(devTO);
            ind2 = getIndMin(devUni);
            if (devTO[ind1].getRelTime() <= devUni[ind2].getRelTime()) {
              devTO[ind1].addReqInQue(&allReq[inReq[0]]);
              buffReq.push_back(inReq[0]);
              inReq.erase(inReq.cbegin());
              timeBuff.erase(timeBuff.cbegin());
              break;
            }
            else {
              devUni[ind2].addReqInQue(&allReq[inReq[0]]);
              buffReq.push_back(inReq[0]);
              inReq.erase(inReq.cbegin());
              timeBuff.erase(timeBuff.cbegin());
              break;
            }
          }
          else {
            if (devTO.size() != 0) {
              ind1 = getIndMin(devTO);
              devTO[ind1].addReqInQue(&allReq[inReq[0]]);
              buffReq.push_back(inReq[0]);
              inReq.erase(inReq.cbegin());
              timeBuff.erase(timeBuff.cbegin());
              break;
            }
            else {
              ind2 = getIndMin(devUni);
              devUni[ind2].addReqInQue(&allReq[inReq[0]]);
              buffReq.push_back(inReq[0]);
              inReq.erase(inReq.cbegin());
              timeBuff.erase(timeBuff.cbegin());
              break;
            }
          }
        case 2:
          if ((devRem.size() != 0) & (devUni.size() != 0)) {
            ind1 = getIndMin(devRem);
            ind2 = getIndMin(devUni);
            if (devRem[ind1].getRelTime() <= devUni[ind2].getRelTime()) {
              devRem[ind1].addReqInQue(&allReq[inReq[0]]);
              buffReq.push_back(inReq[0]);
              inReq.erase(inReq.cbegin());
              timeBuff.erase(timeBuff.cbegin());
              break;
            }
            else {
              devUni[ind2].addReqInQue(&allReq[inReq[0]]);
              buffReq.push_back(inReq[0]);
              inReq.erase(inReq.cbegin());
              timeBuff.erase(timeBuff.cbegin());
              break;
            }
          }
          else {
            if (devRem.size() != 0) {
              ind1 = getIndMin(devRem);
              devRem[ind1].addReqInQue(&allReq[inReq[0]]);
              buffReq.push_back(inReq[0]);
              inReq.erase(inReq.cbegin());
              timeBuff.erase(timeBuff.cbegin());
              break;
            }
            else {
              ind2 = getIndMin(devUni);
              devUni[ind2].addReqInQue(&allReq[inReq[0]]);
              buffReq.push_back(inReq[0]);
              inReq.erase(inReq.cbegin());
              timeBuff.erase(timeBuff.cbegin());
              break;
            }
          }
        default:
          break;
        }
      }

    }
  }
 // std::cout << 6 << std::endl;
  for (int j = 0; j < numTO; j++) { devTO[j].checkDev(reqTime[reqTime.size()-1]); }
  for (int j = 0; j < numRem; j++) { devRem[j].checkDev(reqTime[reqTime.size()-1]); }
  for (int j = 0; j < numUni; j++) { devUni[j].checkDev(reqTime[reqTime.size()-1]); } */
  //std::cout << 7 << std::endl;
 /* for (int i = 0; i < allReq.size(); i++) {
    std::cout << allReq[i].reqTime << " ; тип " << allReq[i].repairType << " ; время обсл " << allReq[i].repairTime[0] <<
      " , " << allReq[i].repairTime[1] << " ; стоимость " << allReq[i].cost[0] << " , " << allReq[i].cost[1] <<
      " ; время в очереди " << allReq[i].queTime[0] << " , " << allReq[i].queTime[1] << " ; обслуж " << allReq[i].servReq[0] <<
      " , " << allReq[i].servReq[1] << std::endl;
  }*/

//  int maxQue = -1, srQue, count=0, sum = 0;
  //for (int i = 0; i < numTO; i++) {
  //  if (devTO[i].queAtTime.size() != 0) {
  //    int max = *std::max_element(devTO[i].queAtTime.begin(), devTO[i].queAtTime.end());
  //    sum += std::accumulate(devTO[i].queAtTime.begin(), devTO[i].queAtTime.end(), 0);
  //    count += devTO[i].queAtTime.size();
  //    if (maxQue < max)
  //    {
  //      maxQue = max;
  //    }
  //  }
  //}

  //for (int i = 0; i < numRem; i++) {
  //  if (devRem[i].queAtTime.size() != 0) {
  //    int max = *std::max_element(devRem[i].queAtTime.begin(), devRem[i].queAtTime.end());
  //    sum += std::accumulate(devRem[i].queAtTime.begin(), devRem[i].queAtTime.end(), 0);
  //    count += devRem[i].queAtTime.size();
  //    if (maxQue < max)
  //    {
  //      maxQue = max;
  //    }
  //  }
  //}

/*  for (int i = 0; i < numUni; i++) {
    if (devUni[i].queAtTime.size() != 0) {
      int max = *std::max_element(devUni[i].queAtTime.begin(), devUni[i].queAtTime.end());
      sum += std::accumulate(devUni[i].queAtTime.begin(), devUni[i].queAtTime.end(), 0);
      count += devUni[i].queAtTime.size();
      if (maxQue < max)
      {
        maxQue = max;
      }
    }
  }

  srQue = (int)(sum / count);

  std::cout << std::endl;
  std::cout <<"Максимальная очередь: "<< maxQue<< std::endl;
  std::cout << "Средняя очередь: " << srQue << std::endl;
  std::cout << std::endl;

  int maxTime = -1, srTime, countT = 0, sumT = 0; */
  //for (int i = 0; i < numTO; i++) {
  //  if (devTO[i].timeQue.size() != 0) {
  //    int max = *std::max_element(devTO[i].timeQue.begin(), devTO[i].timeQue.end());
  //    sumT += std::accumulate(devTO[i].timeQue.begin(), devTO[i].timeQue.end(), 0);
  //    countT += devTO[i].timeQue.size();
  //    if (maxTime < max)
  //    {
  //      maxTime = max;
  //    }
  //  }
  //}

  //for (int i = 0; i < numRem; i++) {
  //  if (devRem[i].timeQue.size() != 0) {
  //    int max = *std::max_element(devRem[i].timeQue.begin(), devRem[i].timeQue.end());
  //    sumT += std::accumulate(devRem[i].timeQue.begin(), devRem[i].timeQue.end(), 0);
  //    countT += devRem[i].timeQue.size();
  //    if (maxTime < max)
  //    {
  //      maxTime = max;
  //    }
  //  }
  //}

/*  for (int i = 0; i < numUni; i++) {
    if (devUni[i].timeQue.size() != 0) {
      int max = *std::max_element(devUni[i].timeQue.begin(), devUni[i].timeQue.end());
      sumT += std::accumulate(devUni[i].timeQue.begin(), devUni[i].timeQue.end(), 0);
      countT += devUni[i].timeQue.size();
      if (maxTime < max)
      {
        maxTime = max;
      }
    }
  }

  srTime = (int)(sumT / countT);

  std::cout << std::endl;
  std::cout << "Максимальное время ожидания в очереди : " << maxTime << std::endl;
  std::cout << "Среднее время ожидания в очереди : " << srTime << std::endl;
  std::cout << std::endl;

  int maxTimeD = -1, srTimeD, countD = 0, sumD = 0; */
  //for (int i = 0; i < numTO; i++) {
  //  int max = devTO[i].getDowntime(time);
  //  sumD += devTO[i].getDowntime(time);
  //  countD ++;
  //  if (maxTimeD < max)
  //  {
  //    maxTimeD = max;
  //  }
  //}

  //for (int i = 0; i < numRem; i++) {
  //  int max = devRem[i].getDowntime(time);
  //  sumD += devRem[i].getDowntime(time);
  //  countD++;
  //  if (maxTimeD < max)
  //  {
  //    maxTimeD = max;
  //  }
  //}

/*  for (int i = 0; i < numUni; i++) {
    int max = devUni[i].getDowntime(time);
   sumD += devUni[i].getDowntime(time);
   countD ++;
    if (maxTimeD < max)
    {
      maxTimeD = max;
    }
  }

  srTimeD = (int)(sumD / countD);

  std::cout << std::endl;
  std::cout << "Максимальное время простоя : " << maxTimeD << std::endl;
  std::cout << "Средняе время простоя : " << srTimeD << std::endl;
  std::cout << std::endl;*/

/*  int countReq = 0;
  int sumCost = 0;

  for (int i = 0; i < allReq.size(); i++) {
    if ((allReq[i].servReq[0] * allReq[i].servReq[1]) != 1)
    {
      countReq++;

    }
    else {
      sumCost += allReq[i].cost[0]; sumCost += allReq[i].cost[1];
    }
  }

  std::cout << "Кол-во не обслуж. заявок : " << countReq << std::endl;
  std::cout << "Кол-во заявок : " << allReq.size() << std::endl;
  std::cout << "Средний доход на 1 бокс : " << sumCost << " , " << sumCost/ (numTO + numRem + numUni);

  */
  //std::mt19937 gen(time(0));
 // std::uniform_real_distribution<> urd(0, 1);
  //std::vector<double> vec(20);
  //vec[0] = getRandErlang2p(14);
  //for (int i = 1; i < 20; i++) { vec[i] = vec[i-1] + getRandErlang2p(14); }
  //for (int i = 0; i < 20; i++) { std::cout << vec[i] << std::endl; }
  //std::cout << std::endl;
  //std::vector<int> vec1, vec2;
  //vec1 = { 10, 55, 12, 45, 45, 5, 80, 150 };
  //vec2 = { 100, 400, 50, 450, 100, 1400, 350, 2550 };
  //
  //std::vector<Req> a;
  //for (int i = 0; i < 20; i++) {
  //a.push_back(Req(vec[i], 0.0432, 0.3168, 0.530, 0.743, vec1, vec2));
  //std::cout << a[i].reqTime << " ; тип " << a[i].repairType << " ; время обсл " << a[i].repairTime[0] <<
  //  " , " << a[i].repairTime[1] << " ; стоимость " << a[i].cost[0] << " , " << a[i].cost[1] <<
  //  " ; время в очереди " << a[i].queTime[0] << " , " << a[i].queTime[1] << " ; обслуж " << a[i].servReq[0] <<
  //  " , " << a[i].servReq[1] << std::endl;
  //}
  //std::cout << std::endl;
  //Dev d;
  //for (int i = 0; i < 20; i++) {
  //  d.addReqInQue(a[i]);
  //  std::cout << a[i].reqTime << " ; тип " << a[i].repairType << " ; время обсл " << a[i].repairTime[0] <<
  //    " , " << a[i].repairTime[1] << " ; стоимость " << a[i].cost[0] << " , " << a[i].cost[1] <<
  //    " ; время в очереди " << a[i].queTime[0] << " , " << a[i].queTime[1] << " ; обслуж " << a[i].servReq[0] <<
  //    " , " << a[i].servReq[1] << std::endl;
  //}
  //std::cout << std::endl;
  //std::cout << d.count << std::endl;
  //for (int i = 0; i < d.timeRep.size(); i++) {
  //  std::cout << d.timeRep[i] << " ";
  //}
  //std::cout << std::endl;
  //d.checkDev(300);
  //for (int i = 0; i < d.queReq.que.size() ; i++) {
  //  std::cout << d.queReq.que[i]->reqTime << " ; тип " << d.queReq.que[i]->repairType << " ; время обсл " << d.queReq.que[i]->repairTime[0] <<
  //    " , " << d.queReq.que[i]->repairTime[1] << " ; стоимость " << d.queReq.que[i]->cost[0] << " , " << d.queReq.que[i]->cost[1] <<
  //    " ; время в очереди " << d.queReq.que[i]->queTime[0] << " , " << d.queReq.que[i]->queTime[1] << " ; обслуж " << d.queReq.que[i]->servReq[0] <<
  //    " , " << d.queReq.que[i]->servReq[1] << std::endl;
  //}

  /*Que q;
  for (int i = 0; i < 20; i++) {
    q.addReqToQue(a[i]);
    std::cout << q.timeQue() << "  " << q.numbReqInQue() << std::endl;
  }
  for (int i = 0; i < 20; i++) {
    std::cout << "que " << std::endl << q.que[i]->reqTime << " ; тип " << q.que[i]->repairType << " ; время обсл " << q.que[i]->repairTime[0] <<
      " , " << q.que[i]->repairTime[1] << " ; стоимость " << q.que[i]->cost[0] << " , " << q.que[i]->cost[1] <<
      " ; время в очереди " << q.que[i]->queTime[0] << " , " << q.que[i]->queTime[1] << " ; обслуж " << q.que[i]->servReq[0] <<
      " , " << q.que[i]->servReq[1] << std::endl;
  }

  for (int i = 0; i < 20; i++) {
    std::cout << a[i].reqTime << " ; тип " << a[i].repairType << " ; время обсл " << a[i].repairTime[0] <<
      " , " << a[i].repairTime[1] << " ; стоимость " << a[i].cost[0] << " , " << a[i].cost[1] <<
      " ; время в очереди " << a[i].queTime[0] << " , " << a[i].queTime[1] << " ; обслуж " << a[i].servReq[0] <<
      " , " << a[i].servReq[1] << std::endl;
  }

  q.checkQue(300);

  std::cout << " :  check time 300  " << std::endl;

  for (int i = 0; i < 20; i++) {
    std::cout << a[i].reqTime << " ; тип " << a[i].repairType << " ; время обсл " << a[i].repairTime[0] <<
      " , " << a[i].repairTime[1] << " ; стоимость " << a[i].cost[0] << " , " << a[i].cost[1] <<
      " ; время в очереди " << a[i].queTime[0] << " , " << a[i].queTime[1] << " ; обслуж " << a[i].servReq[0] <<
      " , " << a[i].servReq[1] << std::endl;
  }

  for (int i = 0; i < q.que.size(); i++) {
    std::cout << "que " << q.que[i]->reqTime << " ; тип " << q.que[i]->repairType << " ; время обсл " << q.que[i]->repairTime[0] <<
      " , " << q.que[i]->repairTime[1] << " ; стоимость " << q.que[i]->cost[0] << " , " << q.que[i]->cost[1] <<
      " ; время в очереди " << q.que[i]->queTime[0] << " , " << q.que[i]->queTime[1] << " ; обслуж " << q.que[i]->servReq[0] <<
      " , " << q.que[i]->servReq[1] << std::endl;
  }*/

  /*int reqTime; //время прибытия
  int repairType; //тип обслуживания
  std::vector<int> repairTime; // время обслуживания
  std::vector<int> cost; //стоимость обслуживания
  std::vector<int> queTime; //время ожидания обслуживания*/
  return 0;
}

