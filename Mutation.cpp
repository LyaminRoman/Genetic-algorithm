#include "Mutation.h"

void PointMutation(individ* ind)
{
	size_t choice = GetRandomNumber(0, num_of_items - 1);
	(*ind)[choice].flip();
}

void InversionMutation(individ* ind)
{
	size_t degree_of_change = GetRandomNumber(0, num_of_items - 1);
	size_t position = GetRandomNumber(0, num_of_items - degree_of_change - 1);;

	for (size_t i = 0; i < degree_of_change; ++i)
	{
		(*ind)[i + position].flip();
	}
}