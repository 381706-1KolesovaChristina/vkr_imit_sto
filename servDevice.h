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
	std::vector<Req*> queReq; // �������
	void addReqInQue(Req* a); // ���������� ������� = ����������� ������
	int count; // ���-�� ������ ������ -�������
	std::vector<int> timeRep; // ����� ������ - ����� ������ ������������
	int getDowntime(int time); // ��������� ����� ������� 
	int getRelTime(); // ��������� ����� ������������ 
	std::vector<int> queAtTime; //���-�� ������ � ������� � ����������� ������ ������� 
	std::vector<int> timeQue; // ����� �������� ������ � �������
	void checkDev(int time); // �������� �� � ������ ������� 
	Dev();
	~Dev();
	int numbReqInQue(); // �-�� ������ � ������� 
	int getTimeQue(); // ����� ������������ �������

	
private:
	void delReqFromQue(); // ������� ����������� ������ �� �������
};

#endif // !SERVDEVICE_H
