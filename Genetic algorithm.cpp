// Genetic algorithm.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "Backpack.h"
#include "Initial population.h"
#include "Reproduction.h"
#include "Mutation.h"
#include "Selection.h"
#include "Random.h"

#include <iostream>

using namespace std;

void Separator()
{
	for (size_t i = 0; i < 80; ++i) cout << "-";
	cout << endl;
}

void WideSeparator()
{
	for (size_t i = 0; i < 80; ++i) cout << "/";
	cout << endl << endl;
}

void Enter(vector<size_t>& choices)
{
	size_t choice;
	cin >> choice;
	if (choice == 1 || choice == 2) choices.emplace_back(choice);
	else
	{
		cout << "Invalid input" << endl;
		Enter(choices);
	}
	cout << endl;
}

void ChooseСonfiguration(vector<size_t>& choices)
{
	cout << "Choose the option to fill the initial population:" << endl
		<< "1: Random population fill" << endl
		<< "2: Greedy algorithm" << endl;
	Enter(choices);

	cout << "Choose a crossover type:" << endl
		<< "1: Homogeneous crossover" << endl
		<< "2: Multipoint crossover" << endl;
	Enter(choices);

	cout << "Choose a mutation type:" << endl
		<< "1: Point mutation" << endl
		<< "2: Inversion mutation" << endl;
	Enter(choices);

	cout << "Choose type of selection:" << endl
		<< "1: Roulette" << endl
		<< "2: Betta tournament" << endl;
	Enter(choices);
}


int main()
{
	Backpack bag("Data.txt");
	vector<individ> population;

	const size_t limit_iterations_without_improvements = 3;
	size_t iterations_without_improvements = 0;
	size_t generation_number = 0;
	size_t best_adaption = 0;
	individ best_individ;

	size_t init_population_size;
	cout << "Enter the size of the initial population:" << endl;
	cin >> init_population_size;
	
	vector<size_t> choices;
	ChooseСonfiguration(choices);

	if (choices[0] == 1) 
		RandomPopulationFill(&population, bag, init_population_size);
	else
		GreedyAlgorithmPopulationFill(&population, bag, init_population_size);


	while (iterations_without_improvements != limit_iterations_without_improvements)
	{
		cout << "Population " << generation_number << ":" << endl << endl;
		for (const auto& el : population)
		{
			cout << el << endl;
		}

		Separator();

		vector<pair<individ, individ>> parent_couples = RandomParentsChoice(population);
		vector <individ> descendants;
		pair<individ, individ> pair_descendants;

		cout << "Reproduction:" << endl << endl;
		for (size_t i = 0; i < parent_couples.size(); ++i)
		{
			cout << "Ancestors " << i << ":" << endl
				<< parent_couples[i].first << endl << parent_couples[i].second << endl << endl;

			if (choices[1] == 1)
				pair_descendants = HomogeneousCrossover(parent_couples[i].first, parent_couples[i].second);
			else
				pair_descendants = MultipointCrossover(parent_couples[i].first, parent_couples[i].second, 4);

			descendants.emplace_back(pair_descendants.first);
			descendants.emplace_back(pair_descendants.second);

			cout << "Descendant " << i << ":" << endl
				<< pair_descendants.first << endl << pair_descendants.second << endl << endl;
		}

		Separator();

		cout << "Descendant mutation:" << endl << endl;
		for (auto& desc : descendants)
		{
			if (GetRandomNumber(1, 100) > chance_of_mutation) continue;

			cout << "Individ " << desc;

			if (choices[2] == 1) PointMutation(&desc);
			else				 InversionMutation(&desc);

			cout << " has been changed to " << desc << endl;
		}

		Separator();

		population.insert(end(population), begin(descendants), end(descendants));
		descendants.clear();

		cout << "Augmented population:" << endl << endl;
		for (const auto& el : population)
		{
			cout << el << endl;
		}

		Separator();

		cout << "Elimination non-valid individs" << endl << endl;
		vector<individ> ErasedIndivids = RemoveInvalidIndivids(&population, bag);
		for (const auto& el : ErasedIndivids)
		{
			cout << "Individ " << el << " has been removed" << endl;
		}

		Separator();

		cout << "Valid population:" << endl << endl;
		for (const auto& el : population)
		{
			cout << el << endl;
		}

		Separator();

		if (choices[3] == 1)
			population = Roulette(population, bag, init_population_size);
		else
			population = BettaTournament(population, bag, init_population_size, 3);


		cout << "New population: " << endl << endl;
		for (const auto& el : population)
		{
			cout << el << endl;
		}

		Separator();

		individ current_best_individ = GetBestIndivid(population, bag);
		size_t current_best_adaption = bag.GetAdaptationIndivid(current_best_individ);

		cout << "Best individ: " << current_best_individ << endl
			<< "With adaptation: " << current_best_adaption << endl;

		if (current_best_adaption > best_adaption)
		{
			best_adaption = current_best_adaption;
			best_individ = current_best_individ;
			iterations_without_improvements = 0;
		}
		else
			++iterations_without_improvements;

		WideSeparator();

		++generation_number;
	}

	cout << "Totally best individ: " << best_individ << endl
		<< "With adaptation: " << best_adaption;
}