#include "simulCycle.h"
#include <algorithm>


int getGenRand(int raspr, int param1, int param2) {
  int p;
  switch (raspr)
  {
  case 1:
    p = getRandErlang2p(param1);
    return p;
  case 2:
    p = getRandUni(param1, param2);
    return p;
  case 3:
    p = getRandNorm(param1, param2);
  default:
    break;
  }
}

std::vector<int> getVecTimeReq(int time, int raspr, int param1, int param2) {
  int sum = 0;
  int p;
  std::vector<int> vec;
  while (sum < time) {
    p = getGenRand(raspr, param1, param2);
    if (sum + p < time)
    {
      vec.push_back(sum + p);
    }
    sum += p;
  }
  return vec;
}

int devType(Req a) {
  switch (a.repairType)
  {
  case 1:
    if ((a.queTime[0] * a.queTime[1]) == 1) { return 1; }
    else return 2;

  case 2:
    return 1;
  case 3:
    return 2;
  case 4:
    return 2;
  case 5:
    return 2;
  default:
    return 0;
  }
}

int getIndMin(std::vector<Dev> a) {
  int min1, ind1;
  min1 = INT_MAX; ind1 = -1;
  for (int k = 0; k < a.size(); k++) {
    if (min1 > a[k].getRelTime()) {
      min1 = a[k].getRelTime();
      ind1 = k;
    }
  }
  return ind1;
}

std::vector<int> simulCycl(int time, int raspr, int param1, int param2, double pr_to, 
  double pr_torem, double pr_r1, std::vector<int> vecDefiTime, 
  std::vector<int>  vecDefiCost, int numTO, int numRem, int numUni) {
  
  std::vector<int> reqTime;
  reqTime = getVecTimeReq(time, raspr, param1, param2);
  reqTime.push_back(time);

  std::vector<int> timeBuff;
  double pr_r2;
  pr_torem *= pr_to;
  pr_r2 = pr_r1 / 3;
  pr_r1 = pr_to + pr_r2;
  pr_r2 += pr_r1;

  std::vector<Dev> devTO(numTO);
  std::vector<Dev> devRem(numRem);
  std::vector<Dev> devUni(numUni);

  std::vector<Req> allReq;
  std::vector<int> inReq;
  std::vector<int> buffReq;

  for (int i = 0; i < reqTime.size() - 1; i++) {
    allReq.push_back(Req(reqTime[i], pr_to, pr_torem, pr_r1, pr_r2, vecDefiTime, vecDefiCost));
  }

  for (int i = 0; i < reqTime.size() - 1; i++) {
    timeBuff.push_back(allReq[i].reqTime);
    inReq.push_back(i);
    while (timeBuff.size() != 0) {


      for (int j = 0; j < numTO; j++) { devTO[j].checkDev(timeBuff[0]); }
      for (int j = 0; j < numRem; j++) { devRem[j].checkDev(timeBuff[0]); }
      for (int j = 0; j < numUni; j++) { devUni[j].checkDev(timeBuff[0]); }

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

  for (int j = 0; j < numTO; j++) { devTO[j].checkDev(reqTime[reqTime.size() - 1]); }
  for (int j = 0; j < numRem; j++) { devRem[j].checkDev(reqTime[reqTime.size() - 1]); }
  for (int j = 0; j < numUni; j++) { devUni[j].checkDev(reqTime[reqTime.size() - 1]); }

  std::vector<int> res(18);
  res[0] = allReq.size();
  int to = 0 , prr = 0 , srr = 0 , slr = 0;
  int tto = 0, tprr = 0, tsrr = 0, tslr = 0;
  for (int i = 0; i < allReq.size(); i++) {
    switch (allReq[i].repairType)
    {
    case 1: 
      to++; srr++; tto += allReq[i].repairTime[1]; tsrr += allReq[i].repairTime[0]; break;
    case 2:
      to++; tto += allReq[i].repairTime[0]; break;
    case 3: 
      prr++; tprr += allReq[i].repairTime[0]; break;
    case 4:
      srr++; tsrr += allReq[i].repairTime[0]; break;
    case 5:
      slr++; tslr += allReq[i].repairTime[0]; break;
    default:
      break;
    }
  }
  
  res[1] = to; res[2] = prr; res[3] = srr; res[4] = slr;
  res[5] = (int)((tto + tprr + tsrr + tslr) / allReq.size());
  tto = (int)(tto / to); tprr = (int)(tprr / prr);
  tsrr = (int)(tsrr / srr); tslr = (int)(tslr / slr);
  res[6] = tto; res[7] = tprr; res[8] = tsrr; res[9] = tslr;



 int maxQue = -1, srQue, count=0, sum = 0;
 if (numTO != 0) {
    for (int i = 0; i < numTO; i++) {
      if (devTO[i].queAtTime.size() != 0) {
      int max = *std::max_element(devTO[i].queAtTime.begin(), devTO[i].queAtTime.end());
      sum += std::accumulate(devTO[i].queAtTime.begin(), devTO[i].queAtTime.end(), 0);
      count += devTO[i].queAtTime.size();
      if (maxQue < max)
      {
        maxQue = max;
      }
    }
  }
 }

 if (numRem != 0) {
   for (int i = 0; i < numRem; i++) {
     if (devRem[i].queAtTime.size() != 0) {
      int max = *std::max_element(devRem[i].queAtTime.begin(), devRem[i].queAtTime.end());
      sum += std::accumulate(devRem[i].queAtTime.begin(), devRem[i].queAtTime.end(), 0);
      count += devRem[i].queAtTime.size();
      if (maxQue < max)
      {
        maxQue = max;
      }
    }
  }
 }
 if (numUni != 0) {
  for (int i = 0; i < numUni; i++) {
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
 }


  srQue = (int)(sum / count);

  res[10] = maxQue; res[11] = srQue; //макс очередь и ср очередь 

  int maxTime = -1, srTime, countT = 0, sumT = 0; 
  if (numTO != 0) {
    for (int i = 0; i < numTO; i++) {
      if (devTO[i].timeQue.size() != 0) {
        int max = *std::max_element(devTO[i].timeQue.begin(), devTO[i].timeQue.end());
        sumT += std::accumulate(devTO[i].timeQue.begin(), devTO[i].timeQue.end(), 0);
        countT += devTO[i].timeQue.size();
        if (maxTime < max)
        {
          maxTime = max;
        }
      }
    }
  }

  if (numRem != 0) {
    for (int i = 0; i < numRem; i++) {
      if (devRem[i].timeQue.size() != 0) {
        int max = *std::max_element(devRem[i].timeQue.begin(), devRem[i].timeQue.end());
        sumT += std::accumulate(devRem[i].timeQue.begin(), devRem[i].timeQue.end(), 0);
        countT += devRem[i].timeQue.size();
        if (maxTime < max)
        {
          maxTime = max;
        }
      }
    }
  }

  if (numUni != 0) {
    for (int i = 0; i < numUni; i++) {
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
  }
  srTime = (int)(sumT / countT);

  res[12] = maxTime; res[13] = srTime; //макс и ср время ожидания в очереди

  int maxTimeD = -1, srTimeD, countD = 0, sumD = 0; 
  if (numTO != 0) {
    for (int i = 0; i < numTO; i++) {
      int max = devTO[i].getDowntime(time);
      sumD += devTO[i].getDowntime(time);
      countD++;
      if (maxTimeD < max)
      {
        maxTimeD = max;
      }
    }
  }

  if (numRem != 0) {
    for (int i = 0; i < numRem; i++) {
      int max = devRem[i].getDowntime(time);
      sumD += devRem[i].getDowntime(time);
      countD++;
      if (maxTimeD < max)
      {
        maxTimeD = max;
      }
    }
  }

  if (numUni != 0) {
    for (int i = 0; i < numUni; i++) {
      int max = devUni[i].getDowntime(time);
      sumD += devUni[i].getDowntime(time);
      countD++;
      if (maxTimeD < max)
      {
        maxTimeD = max;
      }
    }
  }
    srTimeD = (int)(sumD / countD);

    res[14] = maxTimeD; res[15] = srTimeD;

    int countReq = 0;
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
    res[16] = countReq; res[17] = sumCost;

    return res;
}
