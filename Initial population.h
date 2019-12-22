#pragma once

#include "Random.h"
#include "Backpack.h"

void RandomPopulationFill(std::vector<individ>* population, const Backpack& bag, size_t init_population_size);

void GreedyAlgorithmPopulationFill(std::vector<individ>* population, const Backpack& bag, size_t init_population_size);