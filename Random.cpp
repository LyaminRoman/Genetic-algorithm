#include "Random.h"

int64_t GetRandomNumber(int64_t start, int64_t end) {
	static std::random_device rd;
	static std::mt19937 generator(rd());
	std::uniform_int_distribution<int64_t> dis(start, end);
	return dis(generator);
}