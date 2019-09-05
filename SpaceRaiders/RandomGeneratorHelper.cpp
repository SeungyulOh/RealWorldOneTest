#include "stdafx.h"
#include "RandomGeneratorHelper.h"

static std::default_random_engine rGen;
typedef std::uniform_int_distribution<int> intRand;
typedef std::uniform_real_distribution<float> floatRand;

void RandomGeneratorHelper::Seed(uint32_t newseed)
{
	rGen.seed(newseed);
}

int RandomGeneratorHelper::GetIntRand(int min, int max)
{
	intRand result(min, max);
	return result(rGen);
}

float RandomGeneratorHelper::GetFloatRand(float min, float max)
{
	floatRand result(min, max);
	return result(rGen);
}
