#include "TrafficLight.h"

TrafficLight::TrafficLight()
{
	_color = red;
	_time = 0;
}

void TrafficLight::set(Light color, int time)
{
	_color = color;
	_time = time;
}

int TrafficLight::getTime()
{
	return _time;
}

Light TrafficLight::getLight()
{
	return _color;
}

void TrafficLight::changeLight()
{
	_color = _color == green ? red : green;
}

void TrafficLight::updateTime()
{
	_time++;
	if (_time == 13)
	{
		changeLight();
		_time = 0;
	}
}