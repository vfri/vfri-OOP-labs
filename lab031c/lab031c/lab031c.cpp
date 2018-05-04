// lab031c.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "CCar.h"
#include <assert.h>


void PrintCarState(CCar aCar)
{
	std::cout << "Engine: " << aCar.GetEngineState() << "  ";
	std::cout << "Moving direction: " << aCar.GetMovingDirection() << "  ";
	std::cout << "Gear mode: " << aCar.GetGearNum() << "  ";
	std::cout << "Speed: " << aCar.GetSpeedValue() << std::endl;
}

void TestTurnOnOffEngine()
{
	CCar Zhiguli;
	assert(Zhiguli.TurnOnEngine() == true);
	assert(Zhiguli.TurnOnEngine() == false); // пытаемся выключить работающий двигатель
	assert(Zhiguli.TurnOffEngine() == true);
	assert(Zhiguli.TurnOffEngine() == false); // пытаемся выключить неработающий двигатель
	std::cout << "Test on engine turning on/off is Ok" << std::endl;
}

void TestSwitchGearOnStop()
{
	CCar Zhiguli;
	PrintCarState(Zhiguli);
	assert(Zhiguli.SetGear(-1) == false); // двигатель не включен -> нельзя включить реверс
	PrintCarState(Zhiguli);
	assert(Zhiguli.SetGear(0) == true); // при выключенном двигателе передача нейтральная
	PrintCarState(Zhiguli);
	assert(Zhiguli.TurnOnEngine() == true); // включаем выключенный двигатель
	PrintCarState(Zhiguli);
	assert(Zhiguli.SetGear(-1) == true); // можно стоя на месте включить реверс
	PrintCarState(Zhiguli);
	assert(Zhiguli.SetGear(1) == true); // а можно стоя с реверса на первую
	PrintCarState(Zhiguli);
	assert(Zhiguli.SetGear(2) == false); // а на вторую нельзя
	PrintCarState(Zhiguli);
	assert(Zhiguli.SetGear(0) == true); // на нейтраль, чтобы затем выключить
	PrintCarState(Zhiguli);
	assert(Zhiguli.TurnOffEngine() == true); // выключаем двигатель
	PrintCarState(Zhiguli);
	std::cout << "Test on gear handling on stop is Ok" << std::endl;
}

void TestForWellForwardMoving()
{
	CCar Zhiguli;
	assert(Zhiguli.TurnOnEngine() == true); // выключаем двигатель
	PrintCarState(Zhiguli);
	assert(Zhiguli.SetGear(1) == true); // 1-я передача
	PrintCarState(Zhiguli);
	assert(Zhiguli.SetSpeed(100) == true); // слишком большая скорость
	PrintCarState(Zhiguli);
	assert(Zhiguli.SetSpeed(20) == true); // а такая скорость годится
	PrintCarState(Zhiguli);
	assert(Zhiguli.SetGear(2) == true); // 2-я передача
	PrintCarState(Zhiguli);
	assert(Zhiguli.SetSpeed(50) == true); // такая скорость годится
	PrintCarState(Zhiguli);
	assert(Zhiguli.SetGear(4) == true); // 2-я передача
	PrintCarState(Zhiguli);
	assert(Zhiguli.SetSpeed(80) == true); // такая скорость годится
	PrintCarState(Zhiguli);
	assert(Zhiguli.SetGear(5) == true); // 2-я передача
	PrintCarState(Zhiguli);
	assert(Zhiguli.SetSpeed(200) == true); // такая скорость недомступна машине
	PrintCarState(Zhiguli);
	assert(Zhiguli.SetSpeed(140) == true); // такая скорость годится
	PrintCarState(Zhiguli);
	assert(Zhiguli.SetSpeed(90) == true); // замедляемся
	PrintCarState(Zhiguli);
	assert(Zhiguli.SetGear(4) == true); // понижаем передачу
	PrintCarState(Zhiguli);
	assert(Zhiguli.SetSpeed(60) == true); // замедляемся
	PrintCarState(Zhiguli);
	assert(Zhiguli.SetGear(3) == true); // понижаем передачу
	PrintCarState(Zhiguli);
	assert(Zhiguli.SetSpeed(20) == true); // пытаемся замедлиться сверх возможного
	PrintCarState(Zhiguli);
	assert(Zhiguli.SetSpeed(30) == true); // замедляемся
	PrintCarState(Zhiguli);
	assert(Zhiguli.SetGear(1) == true); // понижаем передачу до 1-ой
	PrintCarState(Zhiguli);
	assert(Zhiguli.SetSpeed(0) == true); // остановились
	PrintCarState(Zhiguli);
	assert(Zhiguli.TurnOffEngine() == false); // выключили двигатель, безуспешно -- нужна нейтраль
	PrintCarState(Zhiguli);
	assert(Zhiguli.SetGear(0) == true); // нейтраль
	PrintCarState(Zhiguli);
	assert(Zhiguli.TurnOffEngine() == true); // выключили двигатель, успешно
	PrintCarState(Zhiguli);
	std::cout << "Test on moving forward is Ok" << std::endl;
}

void TestWithReverseMoving()
{
	CCar Zhiguli;
	assert(Zhiguli.TurnOnEngine() == true); // выключаем двигатель
	PrintCarState(Zhiguli);
	assert(Zhiguli.SetGear(1) == true); // первая передача, стоим на месте
	PrintCarState(Zhiguli);
	assert(Zhiguli.SetSpeed(10) == true); // первая передача, едем вперед 10
	PrintCarState(Zhiguli);
	assert(Zhiguli.SetGear(-1) == false); // переключаемся на реверс -- безуспешно
	PrintCarState(Zhiguli);
	assert(Zhiguli.SetGear(0) == true); // переключаемся на нейтраль, но едем вперед
	PrintCarState(Zhiguli);
	assert(Zhiguli.SetGear(-1) == false); // переключаемся на реверс -- безуспешно
	PrintCarState(Zhiguli);
	assert(Zhiguli.SetSpeed(0) == true); // останавливаемся на нейтрали
	PrintCarState(Zhiguli);
	assert(Zhiguli.SetGear(1) == true); // первая передача, стоим на месте
	PrintCarState(Zhiguli);
	assert(Zhiguli.SetGear(-1) == true); // переключаемся на реверс, стоя на месте
	PrintCarState(Zhiguli);
	assert(Zhiguli.SetSpeed(15) == true); // едем назад 15
	PrintCarState(Zhiguli);
	assert(Zhiguli.SetGear(1) == false); // переключаемся на первую -- безуспешно
	PrintCarState(Zhiguli);
	assert(Zhiguli.SetGear(0) == true); // переключаемся на нейтраль, едем назад
	PrintCarState(Zhiguli);
	assert(Zhiguli.SetGear(1) == false); // переключаемся на первую -- безуспешно
	PrintCarState(Zhiguli);
	assert(Zhiguli.SetSpeed(0) == true); // останавливаемся
	PrintCarState(Zhiguli);
	assert(Zhiguli.SetGear(1) == true); // переключаемся на первую
	PrintCarState(Zhiguli);
	assert(Zhiguli.SetSpeed(20) == true); // 20 вперед
	PrintCarState(Zhiguli);
	assert(Zhiguli.SetGear(0) == true); // переключаемся на нейтраль, едем вперед
	PrintCarState(Zhiguli);
	assert(Zhiguli.SetGear(3) == false); // слишком высокая передача для данной скорости 20
	PrintCarState(Zhiguli);
	assert(Zhiguli.SetSpeed(0) == true); // останавливаемся
	PrintCarState(Zhiguli);
	assert(Zhiguli.TurnOffEngine() == true); // выключаем двигатель
	PrintCarState(Zhiguli);
	std::cout << "Test on moving with reverse is Ok" << std::endl;
}

void PrintHelp()
{
	std::cout << "Drive the car. Enter \"EngineOn\" to turn on the engine, \"EngineOff\" to turn off the engine." << std::endl;
	std::cout << "Enter \"SetGear<2018>\" to use 2018-th gear (-1 is reverse, 0 is neutral)." << std::endl;
	std::cout << "Enter \"SetSpeed<100>\" to try reach speed of 100." << std::endl;
	std::cout << "Enter \"Info\" to see car parameters state" << std::endl;
	std::cout << "Enter \"Exit\" to finish driving." << std::endl;

}

std::vector<std::string> Commands(CCar aCar)
{
	std::vector<std::string> result = 
	{ std::string("Exit"), std::string("Info"), std::string("EngineOn"), std::string("EngineOff") };
	return result;
}

int WhatOperation(CCar aCar)
{
	return 0;
}

int main(int argc, char* argv[])
{
	TestTurnOnOffEngine();
	TestSwitchGearOnStop();
	TestForWellForwardMoving();
	TestWithReverseMoving();

		
	return 0;
}

