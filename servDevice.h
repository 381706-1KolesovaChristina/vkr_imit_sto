#pragma once
#ifndef SERVDEVICE_H
#define SERVDEVICE_H
#include <vector>
#include <numeric>
//#include "queue.h"
#include "request.h"

class Dev
{
public:
	std::vector<Req*> queReq; // очередь
	void addReqInQue(Req* a); // пополнение очереди = поступление заявки
	int count; // кол-во обслуж заявок -счетчик
	std::vector<int> timeRep; // время работы - сумма времен обслуживания
	int getDowntime(int time); // вычислить время простоя 
	int getRelTime(); // вычислить время освобождения 
	std::vector<int> queAtTime; //кол-во заявок в очереди в проверяемый момент времени 
	std::vector<int> timeQue; // время ожидания заявок в очереди
	void checkDev(int time); // проверка ОУ в момент времени 
	Dev();
	~Dev();
	int numbReqInQue(); // к-во заявок в очереди 
	int getTimeQue(); // время освобождения очереди

	
private:
	void delReqFromQue(); // удалить обслуженную заявку из очереди
};

#endif // !SERVDEVICE_H
