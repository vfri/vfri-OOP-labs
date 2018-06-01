#include "stdafx.h"
#include "CCar.h"

const std::vector<std::vector<int>> AnAutomobileKit = 
{ { 0, 20 },{ 0, 150 },{ 0, 30 },{ 20, 50 },{ 30, 60 },{ 40, 90 },{ 50, 150 } };

const std::vector<std::vector<int>> OldMoskvichKit =
{ { 0, 20 },{ 0, 100 },{ 0, 30 },{ 20, 60 },{ 40, 100 } };

// класс диапазон

CDiapazon::CDiapazon()
	:m_lower(0)
	,m_upper(0)
{
}

CDiapazon::CDiapazon(int upper)
{
	m_lower = 0;
	m_upper = std::abs(upper);
}

CDiapazon::CDiapazon(int lower, int upper)
{
	m_lower = std::min(std::abs(lower), std::abs(upper));
	m_upper = std::max(std::abs(lower), std::abs(upper));
}

CDiapazon::CDiapazon(const CDiapazon& diap)
{
	m_lower = diap.m_lower;
	m_upper = diap.m_upper;
}


int CDiapazon::GetUpper() const
{
	return m_upper;
}

int CDiapazon::GetLower() const
{
	return m_lower;
}


bool CDiapazon::Below(int value) const
{
	return (value > m_upper);
}


bool CDiapazon::Over(int value) const
{
	return (value < m_lower);
}

bool CDiapazon::Contains(int value) const
{
	return (!Below(value) && !Over(value));
}

// класс коробка передач

CGearKit::CGearKit()
	:m_forwardNumber(5)
	,m_reverseDiap(CDiapazon::CDiapazon(0, 20))
	,m_neutralDiap(CDiapazon::CDiapazon(0, 150))
{
	m_forwardDiap.clear();
	m_forwardDiap.push_back(CDiapazon::CDiapazon(0, 30));
	m_forwardDiap.push_back(CDiapazon::CDiapazon(20, 50));
	m_forwardDiap.push_back(CDiapazon::CDiapazon(30, 60));
	m_forwardDiap.push_back(CDiapazon::CDiapazon(40, 90));
	m_forwardDiap.push_back(CDiapazon::CDiapazon(50, 150));
}

CGearKit::CGearKit(const CGearKit& givenKit)
{
	m_forwardNumber = givenKit.m_forwardNumber;
	CDiapazon m_reverseDiap(givenKit.m_reverseDiap);
	CDiapazon m_neutralDiap(givenKit.m_neutralDiap);
	for (size_t i = 0; i < m_forwardNumber; ++i)
	{
		m_forwardDiap.push_back(givenKit.m_forwardDiap[i]);
	}
}


CGearKit::CGearKit(const CDiapazon& revDiap, const int forNumber, const std::vector<CDiapazon>& forDiap)
{ // 
	m_forwardNumber = forNumber;
	CDiapazon m_reverseDiap(revDiap);
	bool validKit = true;
	for (size_t i = 0; i < forNumber - 1; ++i)
	{
		if (forDiap[i].Contains(forDiap[i + 1].GetLower()) && forDiap[i + 1].Contains(forDiap[i].GetUpper()))
		{
			m_forwardDiap.push_back(forDiap[i]);
		}
		else
		{
			validKit = false;
			break;
		}
	}
	if (validKit)
	{
		m_forwardDiap.push_back(forDiap[forNumber - 1]);
		CDiapazon m_neutralDiap(0, std::max(forDiap[forNumber - 1].GetUpper(), revDiap.GetUpper()));
	}
	else
	{
		CGearKit();
	}
}

int CGearKit::GetForwardNumber() const
{
	return m_forwardNumber;
}

CDiapazon CGearKit::GetReverseDiapazon() const
{
	return m_reverseDiap;
}

CDiapazon CGearKit::GetForwardDiapazon(const int gear) const
{
	return m_forwardDiap[gear - 1];
}


bool CGearKit::GearNotExists(const int gear) const
{
	return ((gear < -1) || (gear > m_forwardNumber));
}

bool CGearKit::TooFast(const int gear, const int velocity) const
{
	if (gear == -1)
	{
		return m_reverseDiap.Below(velocity);
	}
	else if (gear > 0)
	{
		return m_forwardDiap[gear - 1].Below(velocity);
	}
	return false;
}

bool CGearKit::TooSlow(const int gear, const int velocity) const
{
	if (gear > 0)
	{
			return m_forwardDiap[gear - 1].Over(velocity);
	}
	return false;
}

bool CGearKit::AppropVelocity(const int gear, const int velocity) const
{
	if (gear == -1)
	{
		return m_reverseDiap.Contains(velocity);
	}
	else if (gear > 0)
	{
		return m_forwardDiap[gear - 1].Contains(velocity);
	}
	return false;
}



// класс CCar

CCar::CCar()
	:m_engineOn(false)
	,m_direction(Direction::Stop)
	,m_errorMess(std::string(""))
	,m_gearKit(CGearKit())
	,m_gear(0)
	,m_speed(0)
{
}

CCar::CCar(const CGearKit& gearKit) 
{
	m_engineOn = false;
	m_direction = Direction::Stop;
	m_errorMess = std::string("");
	m_gear = 0;
	m_speed = 0;
	CGearKit m_gearKit(gearKit);
}


CGearKit CCar::GetGearKit() const
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

std::string CCar::GetErrorMessage() const
{
	return m_errorMess;
}

bool CCar::TurnOnEngine()  // включить двигатель; если двигатель включен, возвращает false 
{
	m_errorMess.clear();
	if (m_engineOn)
	{
		m_errorMess = std::string("Engine is already works!");
		return false;
	}
	else
	{
		return (m_engineOn = true);
	}
}

bool CCar::TurnOffEngine() // выключить двигатель; если двигатель нельзя выключить 
{	// (выключен, или передача не нейтральная, или скорость не нулевая), то возвращает false
	m_errorMess.clear();
	if (!(m_engineOn && (m_gear == 0) && (m_speed == 0)))
	{
		m_errorMess = std::string("You can turn engine off only if engine turned on and gear set neutral and car not moving");
		return false;
	}
	else
	{
		return !(m_engineOn = false);
	}
}



bool CCar::SetGear(int gear) // включить данную передачу
{
	m_errorMess.clear();

	if (m_gear == gear)
	{
		return true;
	}
	if (m_gearKit.GearNotExists(gear))
	{
		m_errorMess = std::string("There only gear modes from -1 to ") + 
			std::to_string(m_gearKit.GetForwardNumber()) + std::string(" are available!");
		return false;
	}
	if (!m_engineOn && (gear != 0))
	{
		m_errorMess = std::string("You can use only neutral gear then engine is off!");
		return false;
	}
	if (m_engineOn)
	{
		if ((gear == -1) && ( m_direction != Direction::Stop))
		{
			m_errorMess = std::string("You must stop before use reverse gear!");
			return false;
		}
		if (gear > 0)
		{
			if (m_direction == Direction::Backward)
			{
				m_errorMess = std::string("The car is moving backward. Do stop before use such the gear!");
				return false;
			}
			if (m_gearKit.TooSlow(gear, m_speed)) 
			{
				m_errorMess = std::string("Too low speed for moving on ") + 
					std::to_string(gear) + std::string(" gear!");
				return false;
			}
			if (m_gearKit.TooFast(gear, m_speed))
			{
				m_errorMess = std::string("Too high speed for moving on ") +
					std::to_string(gear) + std::string(" gear!");
				return false;
			}
		}
	}
	m_gear = gear; // если выполнение оказалось здесь -- можно включать передачу
	return true;
}

Direction SetDirection(const int gear, const int speed)
{
	Direction dir = Direction::Stop;
	if ((speed != 0) && (gear != 0))
	{
		dir = (gear == -1) ? Direction::Backward : Direction::Forward;
	}
	return dir;
}

bool CCar::SetSpeed(int speed) // добиться данной скорости
{
	m_errorMess.clear();

	if (speed < 0)
	{
		m_errorMess = std::string("Speed must be nonnegative!");
		return false;
	}
	if ((m_gear == 0) && (speed > m_speed))
	{
		m_errorMess = std::string("To increase the speed use nonneutral gear!");
		return false;
	}
	if ((m_direction == Direction::Backward) && (m_gearKit.TooFast(-1, speed)))
	{
		m_speed = m_gearKit.GetReverseDiapazon().GetUpper();
		m_errorMess = std::string("Too high speed for moving on reverse gear. Speed achieved is ") +
			std::to_string(m_speed);
		return false;
	}
	if (m_gearKit.TooFast(m_gear, speed))
	{
		m_speed = m_gearKit.GetForwardDiapazon(m_gear).GetUpper();
		m_errorMess = std::string("Too high speed for moving on ") + std::to_string(m_gear) +
			std::string(" gear. Speed achieved is ") + std::to_string(m_speed);
		return false;
	}
	if (m_gearKit.TooSlow(m_gear, speed))
	{
		m_speed = m_gearKit.GetForwardDiapazon(m_gear).GetLower();
		m_errorMess = std::string("Too low speed for moving on ") + std::to_string(m_gear) +
			std::string(" gear. Speed achieved is ") + std::to_string(m_speed);
		return false;
	}
	m_speed = speed;
	m_direction = SetDirection(m_gear, m_speed);

	return true;
}