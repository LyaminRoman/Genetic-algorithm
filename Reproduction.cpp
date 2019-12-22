#include "Reproduction.h"

std::vector<std::pair<individ, individ>> RandomParentsChoice(const std::vector<individ>& population)
{
	std::vector<std::pair<individ, individ>> formed_couples;

	std::vector<size_t> choices;
	for (size_t i = 0; i < population.size(); ++i)
		choices.emplace_back(i);

	for (size_t i = 0; i < population.size() / 2; ++i)
	{
		std::pair<individ, individ> new_pair;
		size_t choice;

		choice = GetRandomNumber(0, choices.size() - 1);
		new_pair.first = population[choices[choice]];
		choices.erase(choices.begin() + choice);

		choice = GetRandomNumber(0, choices.size() - 1);
		new_pair.second = population[choices[choice]];
		choices.erase(choices.begin() + choice);

		formed_couples.emplace_back(new_pair);
	}
	return formed_couples;
}

std::pair<individ, individ> HomogeneousCrossover(const individ& ancestor1, const individ& ancestor2)
{
	individ descendant1;
	individ descendant2;

	for (size_t i = 0; i < num_of_items; ++i)
	{
		if (ancestor1[i] == ancestor2[i])
		{
			descendant1[i] = ancestor1[i];
			descendant2[i] = ancestor1[i];
		}
		else
		{
			descendant1[i] = GetRandomNumber(0, 1);
			descendant2[i] = GetRandomNumber(0, 1);
		}
	}
	return make_pair(descendant1, descendant2);
}

std::pair<individ, individ> MultipointCrossover(const individ& ancestor1, const individ& ancestor2, size_t num_of_points)
{
	individ descendant1;
	individ descendant2;

	if (num_of_points >= num_of_items) num_of_points = num_of_items - 1;

	size_t separator = num_of_items / ++num_of_points;

	bool flag = false;
	for (size_t i = 0; i < num_of_items; ++i)
	{
		if (i % separator == 0 && num_of_points)
		{
			flag = !flag;
			if (--num_of_points < 0) num_of_points = 0;
		}

		if (flag)
		{
			descendant1[i] = ancestor1[i];
			descendant2[i] = ancestor2[i];
		}
		else
		{
			descendant1[i] = ancestor2[i];
			descendant2[i] = ancestor1[i];
		}
	}
	return std::make_pair(descendant1, descendant2);
}