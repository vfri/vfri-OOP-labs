#include "stdafx.h"
#include "CCar.h"

const std::vector<std::vector<int>> AnAutomobileKit = 
{ { 0, 20 },{ 0, 150 },{ 0, 30 },{ 20, 50 },{ 30, 60 },{ 40, 90 },{ 50, 150 } };

const std::vector<std::vector<int>> OldMoskvichKit =
{ { 0, 20 },{ 0, 100 },{ 0, 30 },{ 20, 60 },{ 40, 100 } };

CCar::CCar()
	:m_engineOn(false)
	,m_direction(Direction::Stop)
	,m_error(DriveError::NoError)
	,m_gearKit(AnAutomobileKit)
	,m_gear(0)
	,m_speed(0)
{
}

CCar::CCar(const std::vector<std::vector<int>>& gearKit) 
{
	m_engineOn = false;
	m_direction = Direction::Stop;
	m_error = DriveError::NoError;
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


std::vector<std::vector<int>> CCar::GetGearKit()
{
	return m_gearKit;
}

// получить элементы состояния car

bool CCar::GetEngineState() const 
{
	return m_engineOn;
}

Direction CCar::GetMovingDirection() const 
{
	return m_direction;
}

int CCar::GetGearNum() const 
{
	return m_gear;
}

int CCar::GetSpeedValue() const 
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

void CCar::TellAboutError(int arg)
{
	switch (m_error)
	{
	case DriveError::GearOutOfRange:
		std::cout << "There only gear modes from -1 to " << m_gearKit.size() - 2 << 
			" are available!" << std::endl;
		break;
	case DriveError::TurningOnPresentGear:
		std::cout << "Such the gear is already setted!" << std::endl;
		break;
	case DriveError::GearOnStanding:
		std::cout << "You can use only neutral gear then engine is off!" << std::endl;
		break;
	case DriveError::UnpossibleReverse:
		std::cout << "You must stop before use reverse gear!" << std::endl;
		break;
	case DriveError::IllGearOnBackwardMoving:
		std::cout << "The car is moving backward. Do stop before use such the gear!" << std::endl; 
		break;
	case DriveError::TooSlowForNewGear:
		std::cout << "Too low speed for moving on " << arg << " gear!" << std::endl;
		break;
	case DriveError::TooFastForNewGear:
		std::cout << "Too high speed for moving on " << arg << " gear!" << std::endl;
		break;
	case DriveError::NegativeSpeed:
		std::cout << "Speed must be nonnegative!" << std::endl;
		break;
	case DriveError::AccelerOnNeutralAttempt:
		std::cout << "To increase the speed use nonneutral gear!" << std::endl;
		break;
	case DriveError::TooSlowForPresentGear:
		std::cout << "Too high speed for moving on " << m_gear << " gear. Speed achieved is " << m_gearKit[m_gear + 1][1] << std::endl;
		break;
	case DriveError::TooFastForPresentGear:
		std::cout << "Too low speed for moving on " << m_gear << " gear. Speed achieved is " << m_gearKit[m_gear + 1][0] << std::endl;
		break;
	}
}

bool CCar::SetGear(int gear) // включить данную передачу
{
	if (!(gear + 2 > 0) || !(gear  +  1 < m_gearKit.size()))
	{
		m_error = DriveError::GearOutOfRange;
		return false;
	}
	if (gear == m_gear)
	{
		m_error = DriveError::TurningOnPresentGear;
		return false;
	}
	if (!m_engineOn)
	{
		if (gear != 0)
		{
			m_error = DriveError::GearOnStanding;
			return false;
		}
	}
	else
	{
		if (gear == -1)
		{
			if (m_direction != Direction::Stop)
			{
				m_error = DriveError::UnpossibleReverse;
				return false;
			}
		}
		if (gear > 0)
		{
			if (m_direction == Direction::Backward)
			{
				m_error = DriveError::IllGearOnBackwardMoving;
				return false;
			}
			if (m_speed < m_gearKit[gear + 1][0]) 
			{
				m_error = DriveError::TooSlowForNewGear;
				return false;
			}
			if (m_speed > m_gearKit[gear + 1][1])
			{
				m_error = DriveError::TooFastForNewGear;
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
		m_error = DriveError::NegativeSpeed;
		return false;
	}
	if ((m_direction == Direction::Backward) && (speed > m_gearKit[0][1]))
	{
		m_error = DriveError::TooFastForPresentGear;
		return false;
	}
	if ((m_gear == 0) && (speed > m_speed))
	{
		m_error = DriveError::AccelerOnNeutralAttempt;
		return false;
	}
	if (speed > m_gearKit[m_gear + 1][1])
	{
		m_error = DriveError::TooFastForPresentGear;
		m_speed = m_gearKit[m_gear + 1][1];
		return true;
	}
	if (speed < m_gearKit[m_gear + 1][0])
	{
		m_error = DriveError::TooSlowForPresentGear;
		m_speed = m_gearKit[m_gear + 1][0];
		return true;
	}
	m_speed = speed;
	if (m_speed == 0)
	{
		m_direction = Direction::Stop;
	}
	else
	{
		if (m_gear != 0)
		{
			m_direction = (m_gear == -1) ? Direction::Backward : Direction::Forward;
		}
	}
	return true;
}