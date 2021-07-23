#pragma once
#ifndef REQUEST_H
#define REQUEST_H

#include "generators.h"
#include <vector>

class Req // ����� ������
{
public:
	int reqTime; // ����� ��������
	int repairType; // ��� ������������
	std::vector<int> repairTime; // ����� ������������
	std::vector<int> cost; //��������� ������������
	std::vector<int> queTime; //����� �������� ������������
	std::vector<int> servReq; // ��������� �� ������
	void isServReq(); // ���� ������ ���������
	Req(int time, double pr_to, double pr_torem, double pr_r1, double pr_r2, 
											std::vector<int> vecDefiTime, std::vector<int> vecDefiCost);
	~Req();

private:
	int defiType(double pr_to, double pr_torem, double pr_r1, double pr_r2);// ����������� ���� ������������
	std::vector<int> defiTime(std::vector<int> vecDefiTime); // ����� ������������ ������
	std::vector<int> defiCost(std::vector<int> vecDefiCost); // ��������� ������������
};

#endif // !REQUEST_H
