// lab031cCatchTests.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../lab031c/CCar.h"


void PrintCarState(CCar aCar)
{
	std::cout << "Engine: " << aCar.GetEngineState() << "  ";
	std::cout << "Moving direction: " << (int)aCar.GetMovingDirection() << "  ";
	std::cout << "Gear mode: " << aCar.GetGearNum() << "  ";
	std::cout << "Speed: " << aCar.GetSpeedValue() << std::endl;
}

TEST_CASE("Turning the engine on and off")
{
	CCar Zhiguli;
	CHECK(Zhiguli.TurnOnEngine() == true);
	CHECK(Zhiguli.TurnOnEngine() == false); // пытаемся выключить работающий двигатель
	CHECK(Zhiguli.TurnOffEngine() == true);
	CHECK(Zhiguli.TurnOffEngine() == false); // пытаемся выключить неработающий двигатель
	std::cout << "Test on engine turning on/off is Ok" << std::endl;
}

TEST_CASE("Changing gear on stop")
{
	CCar Zhiguli;
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetGear(-1) == false); // двигатель не включен -> нельзя включить реверс
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetGear(0) == false); // при выключенном двигателе передача нейтральная
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.TurnOnEngine() == true); // включаем выключенный двигатель
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetGear(-1) == true); // можно стоя на месте включить реверс
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetGear(1) == true); // а можно стоя с реверса на первую
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetGear(2) == false); // а на вторую нельзя
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetGear(0) == true); // на нейтраль, чтобы затем выключить
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.TurnOffEngine() == true); // выключаем двигатель
	PrintCarState(Zhiguli);
	std::cout << "Test on gear handling on stop is Ok" << std::endl;
}

TEST_CASE("Test on well forward moving")
{
	CCar Zhiguli;
	CHECK(Zhiguli.TurnOnEngine() == true); // включаем двигатель
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetGear(1) == true); // 1-я передача
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetSpeed(100) == true); // слишком большая скорость
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetSpeed(20) == true); // а такая скорость годится
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetGear(2) == true); // 2-я передача
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetSpeed(50) == true); // такая скорость годится
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetGear(4) == true); // 2-я передача
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetSpeed(80) == true); // такая скорость годится
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetGear(5) == true); // 2-я передача
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetSpeed(200) == true); // такая скорость недомступна машине
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetSpeed(140) == true); // такая скорость годится
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetSpeed(90) == true); // замедляемся
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetGear(4) == true); // понижаем передачу
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetSpeed(60) == true); // замедляемся
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetGear(3) == true); // понижаем передачу
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetSpeed(20) == true); // пытаемся замедлиться сверх возможного
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetSpeed(30) == true); // замедляемся
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetGear(1) == true); // понижаем передачу до 1-ой
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetSpeed(0) == true); // остановились
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.TurnOffEngine() == false); // выключили двигатель, безуспешно -- нужна нейтраль
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetGear(0) == true); // нейтраль
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.TurnOffEngine() == true); // выключили двигатель, успешно
	PrintCarState(Zhiguli);
	std::cout << "Test on moving forward is Ok" << std::endl;
}

TEST_CASE("Test with reverse moving")
{
	CCar Zhiguli;
	CHECK(Zhiguli.TurnOnEngine() == true); // включаем двигатель
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetGear(1) == true); // первая передача, стоим на месте
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetSpeed(10) == true); // первая передача, едем вперед 10
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetGear(-1) == false); // переключаемся на реверс -- безуспешно
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetGear(0) == true); // переключаемся на нейтраль, но едем вперед
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetGear(-1) == false); // переключаемся на реверс -- безуспешно
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetSpeed(0) == true); // останавливаемся на нейтрали
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetGear(1) == true); // первая передача, стоим на месте
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetGear(-1) == true); // переключаемся на реверс, стоя на месте
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetSpeed(15) == true); // едем назад 15
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetGear(1) == false); // переключаемся на первую -- безуспешно
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetGear(0) == true); // переключаемся на нейтраль, едем назад
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetGear(1) == false); // переключаемся на первую -- безуспешно
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetSpeed(0) == true); // останавливаемся
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetGear(1) == true); // переключаемся на первую
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetSpeed(20) == true); // 20 вперед
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetGear(0) == true); // переключаемся на нейтраль, едем вперед
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetGear(3) == false); // слишком высокая передача для данной скорости 20
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.SetSpeed(0) == true); // останавливаемся
	PrintCarState(Zhiguli);
	CHECK(Zhiguli.TurnOffEngine() == true); // выключаем двигатель
	PrintCarState(Zhiguli);
	std::cout << "Test on moving with reverse is Ok" << std::endl;
}
