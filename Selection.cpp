#include "Selection.h"

std::vector<individ> RemoveInvalidIndivids(std::vector<individ>* population, const Backpack& bag)
{
	std::vector<individ> ErasedIndivids;

	population->erase(std::remove_if(population->begin(), population->end(),
		[&](const individ& ind)->bool
		{
			if (bag.GetWeightIndivid(ind) > bag.GetWeightLimit())
			{
				ErasedIndivids.emplace_back();
				return true;
			};
			return false;
		}), population->end());

	return ErasedIndivids;
}

individ GetBestIndivid(const std::vector<individ>& population, const Backpack& bag)
{
	size_t best_adaptation = 0;
	individ best_individ;

	for (const auto& ind : population)
	{
		size_t current_adaptation = bag.GetAdaptationIndivid(ind);
		if (current_adaptation > best_adaptation)
		{
			best_adaptation = current_adaptation;
			best_individ = ind;
		}
	}
	return best_individ;
}

std::vector<individ> Roulette(const std::vector<individ>& population, const Backpack& bag, size_t init_population_size)
{
	std::vector<individ> new_population;
	new_population.emplace_back(GetBestIndivid(population, bag));
	--init_population_size;

	size_t sum_of_adaptation = 0;
	for (const auto& ind : population)
	{
		sum_of_adaptation += bag.GetAdaptationIndivid(ind);
	}

	std::vector<size_t> segments(population.size());

	for (size_t i = 0; i < population.size(); ++i)
		for (size_t j = i; j < population.size(); ++j)
		{
			segments[j] += bag.GetAdaptationIndivid(population[i]);
		}

	size_t selected_point;

	for (size_t i = 0; i < init_population_size; ++i)
	{
		selected_point = GetRandomNumber(0, sum_of_adaptation - 1);

		for (size_t i = 0; i < segments.size(); ++i)
		{
			if (selected_point < segments[i])
			{
				new_population.emplace_back(population[i]);
				break;
			}
		}
	}
	return new_population;
}

std::vector<individ> BettaTournament(const std::vector<individ>& population, const Backpack& bag, size_t init_population_size, size_t betta)
{
	std::vector<individ> new_population;

	for (size_t i = 0; i < init_population_size; ++i)
	{
		std::vector<individ> sample(betta);
		for (size_t i = 0; i < betta; ++i)
		{
			sample.emplace_back(population[GetRandomNumber(0, population.size() - 1)]);
		}
		new_population.emplace_back(GetBestIndivid(sample, bag));
	}
	return new_population;
}