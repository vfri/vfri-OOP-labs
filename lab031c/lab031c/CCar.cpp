#include "stdafx.h"
#include "CCar.h"

const std::vector<std::vector<int>> AnAutomobileKit = 
{ { 0, 20 },{ 0, 150 },{ 0, 30 },{ 20, 50 },{ 30, 60 },{ 40, 90 },{ 50, 150 } };

const std::vector<std::vector<int>> OldMoskvichKit =
{ { 0, 20 },{ 0, 100 },{ 0, 30 },{ 20, 60 },{ 40, 100 } };

CCar::CCar()
	:m_engineOn(false)
	,m_direction(Stop)
	,m_gearKit(AnAutomobileKit)
	,m_gear(0)
	,m_speed(0)
{
}

CCar::CCar(std::vector<std::vector<int>> gearKit) 
{
	m_engineOn = false;
	m_direction = Stop;
	m_gear = 0;
	m_speed = 0;
	std::vector<std::vector<int>> probKit;
	bool valid = true;
	for (size_t i = 0; i < gearKit.size(); ++i)
	{
		if (i <= 2)
		{
			probKit[i][0] = 0;
		}
		if (gearKit[i].size() != 2)
		{
			valid = false;
			break;
		}
		else if ((gearKit[i][0] < 0) || (gearKit[i][0] >= gearKit[i][1]))
		{
			valid = false;
			break;
		}
		else if ((i > 2) && ((gearKit[i][0] <= gearKit[i - 1][0]) || (gearKit[i][1] <= gearKit[i - 1][1])))
		{
			valid = false;
			break;
		}
		else
		{
			probKit[i][0] = gearKit[i][0];
			probKit[i][1] = gearKit[i][1];
		}
	}
	if (valid) // данный набор скоростей пригоден в качестве параметров КПП
	{
		probKit[1][1] = probKit[gearKit.size() - 1][1];
		m_gearKit = probKit;
	}
	else
	{
		m_gearKit = AnAutomobileKit;
	}
}

CCar::~CCar()
{
}

std::vector<std::vector<int>> CCar::GetGearKit()
{
	return m_gearKit;
}

bool CCar::GetEngineState() // проверить состояние двигателя
{
	return m_engineOn;
}

int CCar::GetMovingDirection() // проверить направление движения
{
	return (int)m_direction;
}

int CCar::GetGearNum()  // проверить номер передачи
{
	return m_gear;
}

int CCar::GetSpeedValue() // проверить значение скорости
{
	return m_speed;
}

bool CCar::TurnOnEngine()  // включить двигатель; если двигатель включен, возвращает false 
{
	return (!m_engineOn) ? (m_engineOn = true) : false;
}

bool CCar::TurnOffEngine() // выключить двигатель; если двигатель нельзя выключить 
{	// (выключен, или передача не нейтральная, или скорость не нулевая), то возвращает false
	return (m_engineOn && (m_gear == 0) && (m_speed == 0)) ? !(m_engineOn = false) : false;
}

bool CCar::SetGear(int gear) // включить данную передачу
{
	if (!(gear + 2 > 0) || !(gear  +  1 < m_gearKit.size()))
	{
		std::cout << "There only gear modes from -1 to " << m_gearKit.size() - 2 << " are available!" << (gear  + 2 > 0) << std::endl;
		return false;
	}
	if (gear == m_gear)
	{
		std::cout << "Such the gear is already setted!" << std::endl;
		return true;
	}
	if (!m_engineOn)
	{
		if (gear != 0)
		{
			std::cout << "You can use only neutral gear then engine is off!" << std::endl;
			return false;
		}
	}
	else
	{
		if (gear == -1)
		{
			if (m_direction != Stop)
			{
				std::cout << "You must stop before use reverse gear!" << std::endl;
				return false;
			}
		}
		if (gear > 0)
		{
			if (m_direction == Backward)
			{
				std::cout << "The car is moving backward. Do stop before use such the gear!" << std::endl;
				return false;
			}
			if (m_speed < m_gearKit[gear + 1][0]) 
			{
				std::cout << "Too low speed for moving on " << gear << " gear!" << std::endl;
				return false;
			}
			if (m_speed > m_gearKit[gear + 1][1])
			{
				std::cout << "Too high speed for moving on " << gear << " gear!" << std::endl;
				return false;
			}
		}
	}
	m_gear = gear; // если выполнение оказалось здесь -- можно включать передачу
	return true;
}

bool CCar::SetSpeed(int speed) // добиться данной скорости
{
	if (speed < 0)
	{
		std::cout << "Speed must be nonnegative!" << std::endl;
		return false;
	}
	if ((m_direction == Backward) && (speed > m_gearKit[0][1]))
	{
		std::cout << "Too high speed for moving on reverse!" << std::endl;
		return false;
	}
	if ((m_gear == 0) && (speed > m_speed))
	{
		std::cout << "To increase the speed use nonneutral gear!" << std::endl;
		return false;
	}
	if (speed > m_gearKit[m_gear + 1][1])
	{
		std::cout << "Too high speed for moving on " << m_gear << " gear. Speed achieved is " << m_gearKit[m_gear + 1][1] << std::endl;
		std::cout << "Maybe upshift gear is the way to reach " << speed << std::endl;
		m_speed = m_gearKit[m_gear + 1][1];
		return true;
	}
	if (speed < m_gearKit[m_gear + 1][0])
	{
		std::cout << "Too low speed for moving on " << m_gear << " gear. Speed achieved is " << m_gearKit[m_gear + 1][0] << std::endl;
		std::cout << "Maybe downshift gear is the way to reach " << speed << std::endl;
		m_speed = m_gearKit[m_gear + 1][0];
		return true;
	}
	m_speed = speed;
	if (m_speed == 0)
	{
		m_direction = Stop;
	}
	else
	{
		if (m_gear != 0)
		{
			m_direction = (m_gear == -1) ? Backward : Forward;
		}
	}
	return true;
}