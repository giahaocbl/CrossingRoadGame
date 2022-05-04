#pragma once
#ifndef _TRAFFIC_LIGHT_H_
#define _TRAFFIC_LIGHT_H_

enum Light { red, green };

class TrafficLight
{
private:
	Light _color;
	int _time;
public:
	TrafficLight();
	Light getLight();
	int getTime();
	void set(Light, int);
	void changeLight();
	void updateTime();
};


#endif // !TRAFFIC_LIGHT_H_
