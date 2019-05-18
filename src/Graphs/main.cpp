/*Розробка програми рішення пакету задач з використанням графів Наявність доріг та відстань між містами задані орієнтованим графом. визначити:
а) найкоротший шлях з а в б;
б) всі можливі шляхи з а в б;
в) мінімальні відстані від а до будь-якого з міст;
г) всі міста, не пов'язані між собою дорогами
*/

#include "pch.h"
#include <iostream>
#include <string>
#include "graphs.h"

using namespace std;

int main()
{
	int count_cities = -1;
	int temp;
	bool flag = true;

	while (count_cities < 0 || count_cities > 10)
	{
		cout << "Enter number of cities: ";
		cin >> count_cities;		
	}

	Matrix matrix(count_cities, vector<int>(count_cities));
	vector<string> name_city(count_cities);

	for (int i = 0; i < count_cities; ++i)
	{
		cout << "Enter name of city: ";
		cin >> name_city[i];
		
		while (checkForAlreadyExist(name_city[i], name_city, i))
		{	
			cout << "Already exist" << endl << "Try again: ";
			cin >> name_city[i];
		}
	}

	string str;

	while (flag)
	{
		cout << "1 - add city" << endl;
		cout << "2 - delete city" << endl;
		cout << "3 - add road" << endl;
		cout << "4 - delete road" << endl;
		cout << "5 - search the shortest way from a to b" << endl;
		cout << "6 - search all ways from a to b" << endl;
		cout << "7 - search the shortest ways from a to all cities" << endl;
		cout << "8 - all cities that are not connected with other cities" << endl;
		cout << "0 - end session" << endl;

		cin >> temp;

		switch (temp)
		{
		case 1:
		{
			count_cities++;
			cout << "Enter name of city: ";
			cin >> str;
			name_city.push_back(str);
			while (checkForAlreadyExist(name_city[count_cities - 1], name_city, count_cities - 1))
			{
				cout << "Already exist" << endl << "Try again: ";
				cin >> name_city[count_cities - 1];
			}
			addCity(matrix);
			break;
		}
		case 2:
		{
			cout << "Enter name of city: ";
			cin >> str;
			int number_find = searchTheNumber(name_city, str, count_cities);

			if (number_find != -1)
			{
				count_cities--;
				name_city.erase(name_city.begin() + number_find);
				delCity(matrix, number_find);
			}
			else
			{
				cout << "Not found..." << endl;
			}
			break;
		}
		case 3:
		{
			cout << "From ";
			cin >> str;
			int number_find_from = searchTheNumber(name_city, str, count_cities);

			cout << "To ";
			cin >> str;
			int number_find_to = searchTheNumber(name_city, str, count_cities);

			if ((number_find_from != -1) && (number_find_to != -1))
			{
				cout << "Enter the cost of road: ";

				int cost_road;
				while (true)
				{
					cin >> cost_road;
					if (cost_road > 0)
					{
						break;
					}
					else
					{
						cout << "Try again: ";
					}
				}

				matrix[number_find_from][number_find_to] = cost_road;
			}
			else
			{
				cout << "Not found..." << endl;
			}
			break;
		}
		case 4:
		{
			cout << "From ";
			cin >> str;
			int number_find_from = searchTheNumber(name_city, str, count_cities);

			cout << "To ";
			cin >> str;
			int number_find_to = searchTheNumber(name_city, str, count_cities);


			if ((number_find_from != -1) && (number_find_to != -1))
			{
				matrix[number_find_from][number_find_to] = 0;
			}
			else
			{
				cout << "Not found..." << endl;
			}
			break;
		}
		case 5:
		{
			cout << "From ";
			cin >> str;
			int number_find_from = searchTheNumber(name_city, str, count_cities);

			cout << "To ";
			cin >> str;
			int number_find_to = searchTheNumber(name_city, str, count_cities);

			if ((number_find_from != -1) && (number_find_to != -1))
			{
				cout << searchMinRoadFromAToB(matrix, name_city, number_find_from, number_find_to);
			}
			else
			{
				cout << "Not found..." << endl;
			}
			break;
		}
		case 6:
		{
			cout << "From ";
			cin >> str;
			int number_find_from = searchTheNumber(name_city, str, count_cities);

			cout << "To ";
			cin >> str;
			int number_find_to = searchTheNumber(name_city, str, count_cities);

			if ((number_find_from != -1) && (number_find_to != -1))
			{
				cout << searchAllRoadFromAToB(matrix, name_city, number_find_from, number_find_to);
			}
			else
			{
				cout << "Not found..." << endl;
			}
			break;
		}
		case 7:
		{
			cout << "From ";
			cin >> str;
			int number_find_from = searchTheNumber(name_city, str, count_cities);
			if (number_find_from != -1)
			{
				cout << searchMinRoadFromAToAnyCity(matrix, name_city, number_find_from);
			}
			else
			{
				cout << "Not found..." << endl;
			}
			break;
		}
		case 8:
		{
			cout << printCityThatDontHaveRoad(matrix, name_city);
			break;
		}
		case 0:
			flag = false;
			break;
		default:
			break;
		}
	}
}