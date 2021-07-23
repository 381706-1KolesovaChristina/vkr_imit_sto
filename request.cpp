#include "request.h"

Req::Req(int time, double pr_to, double pr_torem, double pr_r1, double pr_r2,
	std::vector<int> vecDefiTime, std::vector<int> vecDefiCost) {
	// �������� ������
	reqTime = time;
	repairType = defiType(pr_torem, pr_to, pr_r1, pr_r2);
	repairTime = defiTime(vecDefiTime);
	cost = defiCost(vecDefiCost);
	queTime = { -1, -1 };
	if (repairType != 1) { servReq = { 0, 1 }; }
	else { servReq = { 0, 0 }; }
}

Req::~Req()
{
}

int Req::defiType(double pr_torem, double pr_to, double pr_r1, double pr_r2) {
	// ����������� ���� ������������
	double x = getRand();
	if (x <= pr_torem) { return 1; } // �� + ��. ���.
	else if ((x > pr_torem) & (x <= pr_to)) { return 2; } // ��
	else if ((x > pr_to) & (x <= pr_r1)) { return 3; } // ��. ���.
	else if ((x > pr_r1) & (x <= pr_r2)) { return 4; } // ��. ���.
	else { return 5; } // ����. ���.
}

std::vector<int> Req::defiTime(std::vector<int> vecDefiTime) {
	// ����� ������������ ������
	std::vector<int> x = { 0, 0 };
	switch (repairType)
	{
	case 1:
		x[0] = getRandUni(vecDefiTime[0], vecDefiTime[1]);
		x[1] = getRandNorm(vecDefiTime[4], vecDefiTime[5]);
		return x;
	case 2:
		x[0] = getRandUni(vecDefiTime[0], vecDefiTime[1]);
		return x;
	case 3:
		x[0] = getRandUni(vecDefiTime[2], vecDefiTime[3]);
		return x;
	case 4:
		x[0] = getRandNorm(vecDefiTime[4], vecDefiTime[5]);
		return x;
	case 5:
		x[0] = getRandUni(vecDefiTime[6], vecDefiTime[7]);
		return x;
	default:
		return x;
	}
}

std::vector<int> Req::defiCost(std::vector<int> vecDefiCost) {
	// ��������� ������������
	std::vector<int> x = { 0, 0 };
	switch (repairType)
	{
	case 1:
		x[0] = getRandUni(vecDefiCost[0], vecDefiCost[1]);
		x[1] = getRandUni(vecDefiCost[4], vecDefiCost[5]);
		return x;
	case 2:
		x[0] = getRandUni(vecDefiCost[0], vecDefiCost[1]);
		return x;
	case 3:
		x[0] = getRandUni(vecDefiCost[2], vecDefiCost[3]);
		return x;
	case 4:
		x[0] = getRandUni(vecDefiCost[4], vecDefiCost[5]);
		return x;
	case 5:
		x[0] = getRandUni(vecDefiCost[6], vecDefiCost[7]);
		return x;
	default:
		return x;
	}
}

void Req::isServReq() { // ���� ������ ���������
	std::swap( repairTime[0], repairTime[1]); // ����� ������������
	std::swap( cost[0], cost[1]); //��������� ������������
	std::swap( queTime[0], queTime[1]); //����� �������� ������������
	servReq[0] = 1;
	std::swap(servReq[0], servReq[1]);
}
