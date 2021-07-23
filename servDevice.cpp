#include "servDevice.h"

void Dev::addReqInQue(Req* a) { // пополнение очереди = поступление заявки
	int _time;
	_time = getTimeQue();
	a->queTime[0] = _time;
	queReq.push_back(a);
	count++;
	timeRep.push_back(a->repairTime[0]);
	timeQue.push_back(a->queTime[0]);
}

int Dev::getDowntime(int time) { // вычислить время простоя 
	int _sum, _time = time;
	if (timeRep.size() != 0) {
		_sum = std::accumulate(timeRep.begin(), timeRep.end(), 0);
		_time = time - _sum;
	}
	if (_time < 0) { return 0; }
	return _time;
}

int Dev::getRelTime() { // вычислить время освобождения 
	
	if (queReq.size() == 0) { return 0; }
	int _time = getTimeQue() + queReq[0]->reqTime;
	return _time;
}

int Dev::getTimeQue() { // время очереди
	if (queReq.size() == 0) { return 0; }
	int sum = 0;

	for (int i = 0; i < queReq.size(); i++) {
		sum += queReq[i]->repairTime[0];
	}
	return sum;
}

void Dev::checkDev(int time) { // проверка ОУ в момент времени 
	int i = 0;
	if (queReq.size() != 0) {
		for (int k = 0; k < queReq.size() ; k++)
		{
			if ((queReq[k]->reqTime + queReq[k]->repairTime[0] + queReq[k]->queTime[0]) <= time)
			{
				i++;
			}
		}
		if (i > 0) {
			for (int j = 0; j < i; j++) { delReqFromQue(); }
		}
	}
	queAtTime.push_back(numbReqInQue());
}

int Dev::numbReqInQue() { // к-во заявок в очереди 
	if (queReq.size() > 0) { return queReq.size()/* - 1*/; }
	else { return 0; }
}

void Dev::delReqFromQue() { // удалить обслуженную заявку из очереди
	queReq[0]->isServReq();
	queReq.erase(queReq.cbegin());
}

Dev::Dev() {
	count = 0;
}

Dev::~Dev()
{
}
