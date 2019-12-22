#pragma once

#include <fstream>
#include <vector>
#include <algorithm>

#include "Individ.h"



struct item
{
	size_t id, cost, weight;

	item(size_t id, size_t cost, size_t weight);
};

class Backpack
{
private:
	std::vector<item> Bag;
	size_t weight_limit;

public:
	Backpack(std::string path);

	size_t GetAdaptationIndivid(const individ& ind) const;

	size_t GetWeightIndivid(const individ& ind) const;

	std::vector<item> GetBag() const;

	size_t GetWeightLimit() const;
};