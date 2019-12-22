#include "Backpack.h"

item::item(size_t id, size_t cost, size_t weight) : id(id), cost(cost), weight(weight) {}


Backpack::Backpack(std::string path)
{
	weight_limit = 0;

	std::ifstream data(path);
	size_t id, cost, weight;

	if (data.is_open())
	{
		data >> weight_limit;
		while (!data.eof())
		{
			data >> id >> cost >> weight;
			Bag.push_back(item(id, cost, weight));
		}
	}
	data.close();
}


size_t Backpack::GetAdaptationIndivid(const individ& ind) const
{
	size_t cost = 0;
	for (size_t i = 0; i < num_of_items; ++i)
	{
		if (ind[i])
		{
			for (auto item : Bag)
			{
				if (item.id == i) cost += item.cost;
			}
		}
	}
	return cost;
}

size_t Backpack::GetWeightIndivid(const individ& ind) const
{
	size_t weight = 0;
	for (size_t i = 0; i < num_of_items; ++i)
	{
		if (ind[i])
		{
			for (auto item : Bag)
			{
				if (item.id == i) weight += item.weight;
			}
		}
	}
	return weight;
}

std::vector<item> Backpack::GetBag() const
{
	return Bag;
}

size_t Backpack::GetWeightLimit() const
{
	return weight_limit;
}