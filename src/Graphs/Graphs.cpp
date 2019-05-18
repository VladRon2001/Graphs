/*Розробка програми рішення пакету задач з використанням графів Наявність доріг та відстань між містами задані орієнтованим графом. визначити:
а) найкоротший шлях з а в б;
б) всі можливі шляхи з а в б;
в) мінімальні відстані від а до будь-якого з міст;
г) всі міста, не пов'язані між собою дорогами
*/

#include "pch.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

using Matrix = vector<vector<int>>;


void changeMatrix(Matrix& matrix)
{
	int count_cities = matrix.size();
	int MAX = INT_MAX/5;
	
	Matrix matrix_road(count_cities, vector<int>(count_cities));
	for (int i = 0; i < count_cities; ++i)
	{
		for (int j = 0; j < count_cities; j++)
		{
			if (matrix[i][j] == 0)
			{
				matrix[i][j] = MAX;
			}
			else
			{
				matrix_road[i][j] = j;
			}
		}
	}

	for (int k = 0; k < count_cities; ++k)
	{
		for (int i = 0; i < count_cities; ++i)
		{
			for (int j = 0; j < count_cities; ++j)
			{
				if (((matrix[i][k] + matrix[k][j]) < matrix[i][j]))
				{
					matrix[i][j] = matrix[i][k] + matrix[k][j];
					matrix_road[i][j] = matrix_road[i][k];
				}
			}
		}
	}

	for (int i = 0; i < count_cities; ++i)
	{
		for (int j = 0; j < count_cities; j++)
		{
			if ((matrix_road[i][j] == MAX) || (i = j))
				matrix_road[i][j] = 0;
		}
	}

	matrix = matrix_road;
}

void getShortestPath(Matrix matrix, vector<string> city_names, int from, int to)
{
	if (matrix[from][to] == 0)
	{
		cout << "No path found" << endl;
		return;
	}

	int current = from;

	while (current != to)
	{
		cout << city_names[current] << " -> ";
		current = matrix[current][to];
	}
	cout << city_names[to] << endl;
}

void searchMinRoadFromAToB(Matrix matrix, vector<string> city_names, int from, int to)
{
	Matrix newMatrix = matrix;
	changeMatrix(newMatrix);
	
	getShortestPath(newMatrix, city_names, from, to);
}

void addCity(Matrix& matrix)
{
	for (size_t i = 0; i < matrix.size(); ++i)
	{
		matrix[i].push_back(0);
	}
	matrix.push_back(vector<int>(matrix.size() + 1));
}

void delCity(Matrix& matrix, int number_found)
{
	for (size_t i = 0; i < matrix.size(); ++i)
	{
		matrix[i].erase(matrix[i].begin() + number_found);
	}
	matrix.erase(matrix.begin() + number_found);
}

int searchTheNumber(vector<string> name_city, string str, int count_cities)
{
	for (int i = 0; i < count_cities; ++i)
	{
		if (str.compare(name_city[i]) == 0)
		{
			return i;
		}
	}
	return -1;
}

void printCityThatDontHaveRoad(Matrix matrix, vector<string> name_city)
{
	int n = matrix.size();
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if ((i != j) && (matrix[i][j] == 0))
			{
				cout << "From " << name_city[i] << " to " << name_city[j] << endl;
			}
		}
	}
}

void searchMinRoadFromAToAnyCity(Matrix matrix, vector<string> name_city, int number_find_from)
{
	Matrix newMatrix = matrix;
	changeMatrix(newMatrix);
	
	for (unsigned int i = 0; i < matrix.size(); ++i)
	{
		if (number_find_from != i)
		{
			cout << "From " << name_city[number_find_from] << " to " << name_city[i] << endl;
			getShortestPath(newMatrix, name_city, number_find_from, i);
		}
	}	
}

int checkForDoubleLoop(vector<int> path, int curCity)
{
	int n = path.size() - 1;
	for (int i = 0; i < n; i++)
	{
		if (curCity == path[i])
			return 1;
	}
	return 0;
}

void createPath(const Matrix& matrix, vector<vector<int>>& paths, vector<int> current_path, int fromCity, int toCity)
{
	if (fromCity == toCity)
	{
		paths.push_back(current_path);
		return;
	}

	if (checkForDoubleLoop(current_path, fromCity) == 1)
	{
		return;
	}

	vector<int> siblings;

	for (unsigned int i = 0; i < matrix.size(); ++i)
	{
		if (matrix[fromCity][i] != 0)
			siblings.push_back(i);
	}

	int sibSize = siblings.size();
	for (int i = 0; i < sibSize; ++i)
	{
		vector<int> newPath = current_path;
		newPath.push_back(siblings[i]);
		createPath(matrix, paths, newPath, siblings[i], toCity);
	}
}

void searchAllRoadFromAToB(Matrix matrix, vector<string> name_city, int number_find_from, int number_find_to)
{
	Matrix newMatrix = matrix;
	changeMatrix(newMatrix);

	if (newMatrix[number_find_from][number_find_to] == 0)
	{
		cout << "Not found..." << endl;
		return;
	}

	vector<vector<int>> paths;
	vector<int> current_path;
	createPath(matrix, paths, current_path, number_find_from, number_find_to);

	for (unsigned int i = 0; i < paths.size(); ++i)
	{
		unsigned int j;
		cout << name_city[number_find_from] << " -> ";
		for (j = 0; j < paths[i].size() - 1; ++j)
		{
			cout << name_city[paths[i][j]] << " -> ";
		}
		cout << name_city[paths[i][j]] << endl;
	}
}

void checkForAlreadyExist(string cur_city, vector<string>& name_city, int i)
{
	int flag = false;
	for (int j = 0; j < i; ++j)
	{
		if (name_city[j] == cur_city)
		{
			flag = true;
			break;
		}
	}

	if (flag)
	{
		cout << "Already exist" << endl << "Try again: ";
		cin >> cur_city;
		checkForAlreadyExist(cur_city, name_city, i);
	}
	else
	{
		name_city[i] = cur_city;
	}
}

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
		checkForAlreadyExist(name_city[i], name_city, i);
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
			checkForAlreadyExist(str, name_city, count_cities - 1);
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
				cin >> cost_road;
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
				searchMinRoadFromAToB(matrix, name_city, number_find_from, number_find_to);
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
				searchAllRoadFromAToB(matrix, name_city, number_find_from, number_find_to);
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
				searchMinRoadFromAToAnyCity(matrix, name_city, number_find_from);
			}
			else
			{
				cout << "Not found..." << endl;
			}
			break;
		}
		case 8:
		{
			printCityThatDontHaveRoad(matrix, name_city);
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