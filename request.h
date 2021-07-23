#pragma once
#ifndef REQUEST_H
#define REQUEST_H

#include "generators.h"
#include <vector>

class Req // класс заявка
{
public:
	int reqTime; // время прибытия
	int repairType; // тип обслуживания
	std::vector<int> repairTime; // время обслуживания
	std::vector<int> cost; //стоимость обслуживания
	std::vector<int> queTime; //время ожидания обслуживания
	std::vector<int> servReq; // обслужена ли заявка
	void isServReq(); // если заявка обслужена
	Req(int time, double pr_to, double pr_torem, double pr_r1, double pr_r2, 
											std::vector<int> vecDefiTime, std::vector<int> vecDefiCost);
	~Req();

private:
	int defiType(double pr_to, double pr_torem, double pr_r1, double pr_r2);// определение типа обслуживания
	std::vector<int> defiTime(std::vector<int> vecDefiTime); // время обслуживания заявки
	std::vector<int> defiCost(std::vector<int> vecDefiCost); // стоимость обслуживания
};

#endif // !REQUEST_H
