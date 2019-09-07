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

std::vector<int> RandomGeneratorHelper::GetDifferentIntRand(int min, int max, int count)
{
	std::vector<int> out;

	while (true)
	{
		if (out.size() == count)
			break;

		int value = GetIntRand(min, max);
		if (out.size() != 0 && out.back() == value)
			continue;

		out.push_back(value);
	}

	return out;
}

bool RandomGeneratorHelper::GetRandomSuccess()
{
	floatRand result(0.f, 100.f);
	return result(rGen) >= 50.f;
}
