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
Программа вычисляет на какой высоте находится объект
в процессе прыжка с интервалом 0.1 секунда

Исходное состояние системы:
- <начальная высота> = 0
- Формула расчёта высоты h(t):
h(t) == v0 * t - 0.5 * g * t * t, где:
g = 9.8 м/с^2 (ускорение свободного падения)
t - момент времени с начала прыжка
v0 - скорость в начальный момент времени
v0 = g * T
T - время достижения максимальной высоты

На входе: неотрицательное целое число (максимальная высота прыжка в метрах)
На выходе:
1) время достижения максимальной высоты (в сек.)
2) пары <момент времени> <высота нахождения объекта>
(все выходные данные с точностью 6 знаков после запятой)
Обработка ошибок:
в случае неверных входных данных выводится сообщение об ошибке
*/

// Программа вычисляет на какой высоте находится объект
// в процессе прыжка с интервалом 0.1 секунда

// Псевдокод работы программы:
//
// Задаём максимальную высоту прыжка
// Расчёт и вывод времени достижения максимальной высоты Т
// Вычисляем начальную скорость v0
// Вывод пар <момент времени> <высота нахождения объекта> 
// с шагом 0.1 сек. пока длится прыжок
//      * Дополнительно выводим пару с максимальной высотой
// Вывод пары <момент приземления> <высота 0>

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
	
	// Вычисляем начальную скорость startingSpeed
	double startingSpeed = GRAVITY_POWER * timeReachMaximumHeight;

	bool isMaximumHeightAchieved = false;

	// Вывод пар <момент времени> <высота нахождения объекта>
	// с шагом 0.1 сек. пока длится прыжок
	for (double time = 0; time < landingTime; time += interval)
	{
		double heigthOfObject = CalculateHeigthOfObject(startingSpeed, time);

		//  *Дополнительно выводим пару с максимальной высотой
		if (time > timeReachMaximumHeight && !isMaximumHeightAchieved)
		{
			isMaximumHeightAchieved = true;
			cout << "Max height time = " << timeReachMaximumHeight << " Height = " << heigthOfObject << endl;
		}
		
		cout << "Moment time = " << time << " Height = " << heigthOfObject << endl;
	}

	// Вывод пары <момент приземления> <высота 0>
	double heigthOfObject = CalculateHeigthOfObject(startingSpeed, landingTime);
	cout << "Landing time = " << landingTime << " Height = " << heigthOfObject << endl;

	return 0;
}