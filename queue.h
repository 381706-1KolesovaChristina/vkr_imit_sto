/*#pragma once
#ifndef QUEUE_H
#define QUEUE_H
#include <vector>
#include "request.h"

class Que
{
public:
	std::vector<Req*> que;
	void addReqToQue(Req& a); // �������� ������ � ������� + ������� ����� ��������
	void checkQue(int time); // ��������� ��������� ������� �� ������� 
	int numbReqInQue(); // �-�� ������ � ������� 
	int timeQue(); // ����� ������������ �������

	Que();
	~Que();

private:
	void delReqFromQue(); // ������� ����������� ������ �� �������
	
};

#endif // !QUEUE_H
*/