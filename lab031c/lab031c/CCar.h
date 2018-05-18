#pragma once
// ���������� ��� �������������� �������� (�-�, �� �������)

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

	CCar();  // ����������� �� ���������

	CCar(const std::vector<std::vector<int>>& gearKit); // ����������� � �������� ���
	
	std::vector<std::vector<int>> GetGearKit(); // �������� ��������� ���

	bool GetEngineState() const; 

	Direction GetMovingDirection() const; 

	int GetGearNum() const; 

	int GetSpeedValue() const;
	
	bool TurnOnEngine();  // �������� ���������

	bool TurnOffEngine(); // ��������� ���������

	bool SetGear(int gear); // �������� ������ ��������

	bool SetSpeed(int speed); // �������� ������ ��������

	void TellAboutError(int arg); // �������� �� ������

private:

	bool m_engineOn; // ��������� �������
	Direction m_direction; // ����������� ��������
	DriveError m_error; // ������ ���������� �������
	std::vector<std::vector<int>> m_gearKit; // ���������� ����� �� ��������� min � max �������� �� �������� �� -1 �� ���������)
	int m_speed; // ��������
	int m_gear;  // �������� (������ -1, �������� 0, �������� ������ 1..n)
};

