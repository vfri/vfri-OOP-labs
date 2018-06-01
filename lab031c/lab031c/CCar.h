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

class CDiapazon
{
	public:
		CDiapazon();
		CDiapazon(int upper);
		CDiapazon(int lower, int upper);
		CDiapazon(const CDiapazon& diap);

		int GetUpper() const;
		int GetLower() const;

		bool Contains(int value) const; // value � ���������
		bool Below(int value) const;	// �������� ���� ���� value 
		bool Over(int value) const;		// �������� ���� ���� value

	private:
		int m_lower;
		int m_upper;
};

class CGearKit
{
	public:
		CGearKit();
		CGearKit(const CGearKit& givenKit);
		CGearKit(const CDiapazon& revDiap, const int forNumber, const std::vector<CDiapazon>& forDiap);

		int GetForwardNumber() const;
		CDiapazon GetReverseDiapazon() const;
		CDiapazon GetForwardDiapazon(const int gear) const;
		
		bool GearNotExists(const int gear) const;
		bool TooFast(const int gear, const int velocity) const;
		bool TooSlow(const int gear, const int velocity) const;
		bool AppropVelocity(const int gear, const int velocity) const;	

	private:
		int m_forwardNumber;
		CDiapazon m_reverseDiap;
		CDiapazon m_neutralDiap;
		std::vector<CDiapazon> m_forwardDiap;
};

class CCar
{
public:

	CCar();  

	CCar(const CGearKit& gearKit); // ����������� � �������� ���
	
	CGearKit GetGearKit() const; // �������� ��������� ���

	bool GetEngineState() const; 

	Direction GetMovingDirection() const; 

	int GetGearNum() const; 

	int GetSpeedValue() const;
	
	bool TurnOnEngine();  

	bool TurnOffEngine(); 

	bool SetGear(int gear); 

	bool SetSpeed(int speed); 

	void TellAboutError(int arg); 

private:

	bool m_engineOn; // ��������� �������
	Direction m_direction; // ����������� ��������
	DriveError m_error; // ������ ���������� �������
	std::string m_errorMess; // c�������� �� ������
	CGearKit m_gearKit; // ���������� ����� �� ��������� min � max �������� �� �������� �� -1 �� ���������)
	int m_speed; // ��������
	int m_gear;  // �������� (������ -1, �������� 0, �������� ������ 1..n)
	Direction SetDirection();
};

