#pragma once

#include <utility>
#include <vector>

#include "Individ.h"
#include "Random.h"

std::vector<std::pair<individ, individ>> RandomParentsChoice(const std::vector<individ>& population);

std::pair<individ, individ> HomogeneousCrossover(const individ& ancestor1, const individ& ancestor2);

std::pair<individ, individ> MultipointCrossover(const individ& ancestor1, const individ& ancestor2, size_t num_of_points);