#include "pch.h"
#include "graphs.h"

void addCity(Matrix& matrix)
{
	for (size_t i = 0; i < matrix.size(); ++i)
	{
		matrix[i].push_back(0);
	}
	matrix.push_back(std::vector<int>(matrix.size() + 1));
}

bool checkForAlreadyExist(std::string cur_city, std::vector<std::string>& name_city, int i)
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

	return flag;
}

int searchTheNumber(const std::vector<std::string>& name_city, const std::string& str, int count_cities)
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

void delCity(Matrix& matrix, int number_found)
{
	for (size_t i = 0; i < matrix.size(); ++i)
	{
		matrix[i].erase(matrix[i].begin() + number_found);
	}
	matrix.erase(matrix.begin() + number_found);
}

void changeMatrix(Matrix& matrix)
{
	int count_cities = matrix.size();
	int MAX = INT_MAX / 5;

	Matrix matrix_road(count_cities, std::vector<int>(count_cities));
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

std::string getShortestPath(const Matrix& matrix, const std::vector<std::string>& city_names, int from, int to)
{
	std::string result ="";
	if (matrix[from][to] == 0)
	{
		result = "No path found\n";
		return result;
	}

	int current = from;

	while (current != to)
	{
		result += city_names[current] + "->";
		current = matrix[current][to];
	}
	result += city_names[to] + "\n";

	return result;
}

std::string searchMinRoadFromAToB(Matrix& matrix, const std::vector<std::string>& city_names, int from, int to)
{
	Matrix newMatrix = matrix;
	changeMatrix(newMatrix);

	return (getShortestPath(newMatrix, city_names, from, to));
}

std::string printCityThatDontHaveRoad(Matrix matrix, const std::vector<std::string>& name_city)
{
	changeMatrix(matrix);

	std::string result = "";
	int n = matrix.size();
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if ((i != j) && (matrix[i][j] == 0))
			{
				result += ("From " + name_city[i] + " to " + name_city[j] + "\n");
			}
		}
	}
	return result;
}

int checkForDoubleLoop(const std::vector<int>& path, int curCity)
{
	int n = path.size() - 1;
	for (int i = 0; i < n; i++)
	{
		if (curCity == path[i])
			return 1;
	}
	return 0;
}

void createPath(const Matrix& matrix, std::vector<std::vector<int>>& paths, std::vector<int> current_path, int fromCity, int toCity)
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

	std::vector<int> siblings;

	for (unsigned int i = 0; i < matrix.size(); ++i)
	{
		if (matrix[fromCity][i] != 0)
			siblings.push_back(i);
	}

	int sibSize = siblings.size();
	for (int i = 0; i < sibSize; ++i)
	{
		std::vector<int> newPath = current_path;
		newPath.push_back(siblings[i]);
		createPath(matrix, paths, newPath, siblings[i], toCity);
	}
}

std::string searchAllRoadFromAToB(Matrix matrix, std::vector<std::string> name_city, int number_find_from, int number_find_to)
{
	Matrix newMatrix = matrix;
	changeMatrix(newMatrix);

	if (newMatrix[number_find_from][number_find_to] == 0)
	{
		return "Not found...\n";
	}

	std::vector<std::vector<int>> paths;
	std::vector<int> current_path;
	createPath(matrix, paths, current_path, number_find_from, number_find_to);

	std::string result;

	for (unsigned int i = 0; i < paths.size(); ++i)
	{
		unsigned int j;
		result += name_city[number_find_from] + "->";
		for (j = 0; j < paths[i].size() - 1; ++j)
		{
			result += name_city[paths[i][j]] + "->";
		}
		result += name_city[paths[i][j]] + "\n";
	}
	return result;
}

std::string searchMinRoadFromAToAnyCity(Matrix matrix, std::vector<std::string> name_city, int number_find_from)
{
	Matrix newMatrix = matrix;
	changeMatrix(newMatrix);

	std::string result = "";

	for (unsigned int i = 0; i < matrix.size(); ++i)
	{
		if (number_find_from != i)
		{
			result += "From " + name_city[number_find_from] + " to " + name_city[i] + '\n';
			result += getShortestPath(newMatrix, name_city, number_find_from, i);
		}
	}
	return result;
}