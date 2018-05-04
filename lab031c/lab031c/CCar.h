#pragma once
// автомобиль дл€ пр€молинейного движени€ (н-р, по рельсам)

class CCar
{
public:

	CCar();  // конструктор по умолчанию

	CCar(std::vector<std::vector<int>> gearKit); // конструктор с заданной  ѕѕ
	
	~CCar();  // деструктор

	std::vector<std::vector<int>> GetGearKit(); // передать параметры  ѕѕ

	bool GetEngineState(); // проверить состо€ние двигател€

	int GetMovingDirection(); // проверить направление движени€

	int GetGearNum(); // проверить номер передачи

	int GetSpeedValue(); // проверить значение скорости
	
	bool TurnOnEngine();  // включить двигатель

	bool TurnOffEngine(); // выключить двигатель

	bool SetGear(int gear); // включить данную передачу

	bool SetSpeed(int speed); // добитьс€ данной скорости

private:

	bool m_engineOn; // двигатель включен
	enum {Backward = -1, Stop, Forward} m_direction; // направление движени€
	std::vector<std::vector<int>> m_gearKit; // скоростной режим на передачах min и max скорость на передаче от -1 до наивысшей)
	int m_speed; // скорость
	int m_gear;  // передача (реверс -1, нейтраль 0, движение вперед 1..n)
};

