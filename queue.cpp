/*#include "queue.h"

void Que::addReqToQue(Req& a) { // добавить заявку в очередь + вернуть время ожидания
	int _time;
	_time = timeQue();
	a.queTime[0] = _time;
	que.push_back(&a);

	//return _time;
}

void Que::checkQue(int time) {// проверить состояние очереди по времени 
	int i = -1;
	if (que.size() != 0) {
		for (int k = -1; k < que.size()-1; k++)
		{
			if ((que[k + 1]->reqTime + que[k + 1]->repairTime[0] + que[k + 1]->queTime[0]) <= time)
			{
				i++;
			}
		}
		if (i > -1) {
			for (int j = 0; j <= i; j++) { delReqFromQue(); }
		}
	}
}

int Que::numbReqInQue() { // к-во заявок в очереди 
	if (que.size() > /*1*//*0) { return que.size()/* - 1*//*; }
	else { return 0; }
}

int Que::timeQue() { // время освобождения очереди
	if (que.size() == 0) { return 0; }
	int sum = que[0]->reqTime;
	for (int i = 0; i < que.size(); i++) {
		sum += que[i]->repairTime[0];
	}
	return sum;
}

Que::Que()
{
}

Que::~Que()
{
}

void Que::delReqFromQue() { // удалить обслуженную заявку из очереди
	que[0]->isServReq();
	que.erase(que.cbegin());
}
*/