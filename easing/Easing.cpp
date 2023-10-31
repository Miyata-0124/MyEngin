#include "Easing.h"
#include<cmath>

float Easing::easeInSine(float num) {
	return 1 - std::cos((num * 3.14f) / 2);
}
float Easing::easeOutSine(float num) {
	return std::sin((num * 3.14f) / 2);
}
float Easing::easeOutBack(float num) {
	const float c1 = 1.70158f;
	const float c2 = c1 + 1;

	return 1 + c2 * pow(num - 1.0f, 3.0f) + c1 * pow(num - 1.0f, 2.0f);
}

float Easing::easeOutBounce(float x)
{
	const float n1 = 7.5625;
	const float d1 = 2.75;

	if (x < 1 / d1) {
		return n1 * x * x;
	}
	else if (x < 2.0f / d1) {
		return n1 * (x -= 1.5f / d1) * x + 0.75f;
	}
	else if (x < 2.5f / d1) {
		return n1 * (x -= 2.25f / d1) * x + 0.9375f;
	}
	else {
		return n1 * (x -= 2.625f / d1) * x + 0.984375f;
	}
}

float Easing::easeOutCubic(float x) {
	return 1 - (float)pow(1 - x, 3);
}

float Easing::easeOutQuint(float x) {
	return 1 - (float)pow(1 - x, 5);
}

float Easing::easeInBounce(float x)
{
	return 1 - easeOutBounce(1 - x);
}

float Easing::easeInOutCirc(float x) {
	return x < 0.5f
		? (1.0f - std::sqrt(1 - std::pow(2.0f * x, 2.0f))) / 2.0f
		: (std::sqrt(1.0f - std::pow(-2.0f * x + 2.0f, 2.0f)) + 1.0f) / 2.0f;
}

float Easing::easeInOutSine(float x) {
	return -(std::cos(3.14f * x) - 1.0f) / 2.0f;
}

float Easing::easeOutElastic(float x)
{
	const float c4 = (2 * 3.14f) / 3;

	return x == 0
		? 0
		: x == 1
		? 1
		: pow(2, -10 * x) * sin((x * 10 - 0.75) * c4) + 1;
}
