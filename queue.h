/*#pragma once
#ifndef QUEUE_H
#define QUEUE_H
#include <vector>
#include "request.h"

class Que
{
public:
	std::vector<Req*> que;
	void addReqToQue(Req& a); // добавить заявку в очередь + вернуть время ожидания
	void checkQue(int time); // проверить состояние очереди по времени 
	int numbReqInQue(); // к-во заявок в очереди 
	int timeQue(); // время освобождения очереди

	Que();
	~Que();

private:
	void delReqFromQue(); // удалить обслуженную заявку из очереди
	
};

#endif // !QUEUE_H
*/