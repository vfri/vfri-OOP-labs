#pragma once
// ���������� ��� �������������� �������� (�-�, �� �������)

class CCar
{
public:

	CCar();  // ����������� �� ���������

	CCar(std::vector<std::vector<int>> gearKit); // ����������� � �������� ���
	
	~CCar();  // ����������

	std::vector<std::vector<int>> GetGearKit(); // �������� ��������� ���

	bool GetEngineState(); // ��������� ��������� ���������

	int GetMovingDirection(); // ��������� ����������� ��������

	int GetGearNum(); // ��������� ����� ��������

	int GetSpeedValue(); // ��������� �������� ��������
	
	bool TurnOnEngine();  // �������� ���������

	bool TurnOffEngine(); // ��������� ���������

	bool SetGear(int gear); // �������� ������ ��������

	bool SetSpeed(int speed); // �������� ������ ��������

private:

	bool m_engineOn; // ��������� �������
	enum {Backward = -1, Stop, Forward} m_direction; // ����������� ��������
	std::vector<std::vector<int>> m_gearKit; // ���������� ����� �� ��������� min � max �������� �� �������� �� -1 �� ���������)
	int m_speed; // ��������
	int m_gear;  // �������� (������ -1, �������� 0, �������� ������ 1..n)
};

