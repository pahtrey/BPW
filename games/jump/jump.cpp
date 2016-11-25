// jump.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

// This program takes max jump height from input and prints
// jump height for every time point with step 0.1 seconds.
// Program should print all time points when height is min and max.
//
// TODO: Fix all warnings on high warning level (/W4, -Wall -Wextra).
// TODO: Rename variables and split to several functions,
// see also https://ps-group.github.io/sfml/coding_conventions.html
// TODO: fix negative height values, fix heigh values higher than max height.

/*
��������� ��������� �� ����� ������ ��������� ������
� �������� ������ � ���������� 0.1 �������

�������� ��������� �������:
- <��������� ������> = 0
- ������� ������� ������ h(t):
h(t) == v0 * t - 0.5 * g * t * t, ���:
g = 9.8 �/�^2 (��������� ���������� �������)
t - ������ ������� � ������ ������
v0 - �������� � ��������� ������ �������
v0 = g * T
T - ����� ���������� ������������ ������

�� �����: ��������������� ����� ����� (������������ ������ ������ � ������)
�� ������:
1) ����� ���������� ������������ ������ (� ���.)
2) ���� <������ �������> <������ ���������� �������>
(��� �������� ������ � ��������� 6 ������ ����� �������)
��������� ������:
� ������ �������� ������� ������ ��������� ��������� �� ������
*/

// ��������� ��������� �� ����� ������ ��������� ������
// � �������� ������ � ���������� 0.1 �������

// ��������� ������ ���������:
//
// ����� ������������ ������ ������
// ������ � ����� ������� ���������� ������������ ������ �
// ��������� ��������� �������� v0
// ����� ��� <������ �������> <������ ���������� �������> 
// � ����� 0.1 ���. ���� ������ ������
//      * ������������� ������� ���� � ������������ �������
// ����� ���� <������ �����������> <������ 0>

using namespace std;

double const GRAVITY_POWER = 9.8;

double CalculateHeigthOfObject(double const & startingSpeed, double const & time)
{
	return startingSpeed * time - 0.5 * GRAVITY_POWER * time * time;
}

int main()
{
	double const interval = 0.1;
	int maximumJumpHeight = 0;
	
	cout << "Enter maximum jump height: ";

	if ((cin >> maximumJumpHeight) && (maximumJumpHeight <= 0))
	{
		cout << "Invalid parameter value" << endl
			<< "Expected non - negative integer number, but found: " << maximumJumpHeight << endl;

		return 1;
	}	

	double timeReachMaximumHeight = sqrt(maximumJumpHeight * 2 / GRAVITY_POWER);
	double landingTime = timeReachMaximumHeight * 2;

	cout << "Time to reach the maximum height: " << timeReachMaximumHeight << endl;
	
	// ��������� ��������� �������� startingSpeed
	double startingSpeed = GRAVITY_POWER * timeReachMaximumHeight;

	bool isMaximumHeightAchieved = false;

	// ����� ��� <������ �������> <������ ���������� �������>
	// � ����� 0.1 ���. ���� ������ ������
	for (double time = 0; time < landingTime; time += interval)
	{
		double heigthOfObject = CalculateHeigthOfObject(startingSpeed, time);

		//  *������������� ������� ���� � ������������ �������
		if (time > timeReachMaximumHeight && !isMaximumHeightAchieved)
		{
			isMaximumHeightAchieved = true;
			cout << "Max height time = " << timeReachMaximumHeight << " Height = " << heigthOfObject << endl;
		}
		
		cout << "Moment time = " << time << " Height = " << heigthOfObject << endl;
	}

	// ����� ���� <������ �����������> <������ 0>
	double heigthOfObject = CalculateHeigthOfObject(startingSpeed, landingTime);
	cout << "Landing time = " << landingTime << " Height = " << heigthOfObject << endl;

	return 0;
}