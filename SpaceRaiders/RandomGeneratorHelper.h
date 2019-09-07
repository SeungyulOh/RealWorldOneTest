#pragma once

#include <random>

class RandomGeneratorHelper
{
public:
	//apply new seed value.
	static void Seed(uint32_t newseed);
	// get a random int number in range of from min to max.
	static int GetIntRand(int min, int max);
	// get a random float number in range of from min to max.
	static float GetFloatRand(float min, float max);
	// get a set of int values and they are all different.
	static std::vector<int> GetDifferentIntRand(int min, int max, int count);
	// get true with 50% probability
	static bool GetRandomSuccess();
};