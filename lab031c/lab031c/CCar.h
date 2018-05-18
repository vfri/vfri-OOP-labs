#pragma once
// автомобиль для прямолинейного движения (н-р, по рельсам)

enum class Direction 
{ 
	Backward = - 1, Stop, Forward 
};

enum class DriveError
{
	NoError, GearOutOfRange, TurningOnPresentGear, GearOnStanding, UnpossibleReverse,
	IllGearOnBackwardMoving, TooSlowForNewGear, TooFastForNewGear, NegativeSpeed, AccelerOnNeutralAttempt, 
	TooSlowForPresentGear, TooFastForPresentGear
};

class CCar
{
public:

	CCar();  // конструктор по умолчанию

	CCar(const std::vector<std::vector<int>>& gearKit); // конструктор с заданной КПП
	
	std::vector<std::vector<int>> GetGearKit(); // передать параметры КПП

	bool GetEngineState() const; 

	Direction GetMovingDirection() const; 

	int GetGearNum() const; 

	int GetSpeedValue() const;
	
	bool TurnOnEngine();  // включить двигатель

	bool TurnOffEngine(); // выключить двигатель

	bool SetGear(int gear); // включить данную передачу

	bool SetSpeed(int speed); // добиться данной скорости

	void TellAboutError(int arg); // сообщить об ошибке

private:

	bool m_engineOn; // двигатель включен
	Direction m_direction; // направление движения
	DriveError m_error; // ошибка управления машиной
	std::vector<std::vector<int>> m_gearKit; // скоростной режим на передачах min и max скорость на передаче от -1 до наивысшей)
	int m_speed; // скорость
	int m_gear;  // передача (реверс -1, нейтраль 0, движение вперед 1..n)
};

