#pragma once

#include "Backpack.h"
#include "Random.h"

std::vector<individ> RemoveInvalidIndivids(std::vector<individ>* population, const Backpack& bag);

individ GetBestIndivid(const std::vector<individ>& population, const Backpack& bag);

std::vector<individ> Roulette(const std::vector<individ>& population, const Backpack& bag, size_t init_population_size);

std::vector<individ> BettaTournament(const std::vector<individ>& population, const Backpack& bag, size_t init_population_size, size_t betta);