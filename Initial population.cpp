#include "Initial population.h"

void RandomPopulationFill(std::vector<individ>* population, const Backpack& bag, size_t init_population_size)
{
	individ ind;

	while (init_population_size)
	{
		for (size_t i = 0; i < num_of_items; ++i)
		{
			ind[i] = GetRandomNumber(0, 1);
		}

		if (bag.GetWeightIndivid(ind) <= bag.GetWeightLimit())
		{
			population->emplace_back(ind);
			--init_population_size;
		}
	}
}

void GreedyAlgorithmPopulationFill(std::vector<individ>* population, const Backpack& bag, size_t init_population_size)
{
	std::vector<item> Bag = bag.GetBag();

	sort(Bag.begin(), Bag.end(), [](const item& i1, const item& i2)
		{return (double)i1.cost / i1.weight > (double)i2.cost / i2.weight; });

	individ last_individ;
	std::vector<size_t> amendatory;
	amendatory.emplace_back(0);

	for (size_t i = 0; i < init_population_size; ++i)
	{
		individ Taken_items;
		size_t cur_weight = 0;

		for (size_t j = 0; j < Bag.size() && cur_weight + Bag[j].weight < bag.GetWeightLimit(); ++j)
		{
			if (find(amendatory.begin(), amendatory.end(), j) != amendatory.end()) continue;
			Taken_items[Bag[j].id] = 1;
			cur_weight += Bag[j].weight;

			if (j == Bag.size() - 1) { amendatory.clear(); amendatory.emplace_back(0); }
		}

		if (last_individ == Taken_items)
		{
			for (size_t j = 0; j < amendatory.size(); ++j)
			{
				amendatory[j] = j;
			}
			amendatory.emplace_back(amendatory.size());
		}
		else
		{
			++amendatory[amendatory.size() - 1];
		}
		last_individ = Taken_items;

		population->emplace_back(Taken_items);
	}
}
