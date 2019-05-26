#pragma once

using Matrix = std::vector<std::vector<int>>;

void addCity(Matrix& matrix);
bool checkForAlreadyExist(std::string cur_city, std::vector<std::string>& name_city, int i);
int searchTheNumber(const std::vector<std::string>& name_city, const std::string& str, int count_cities);
void delCity(Matrix& matrix, int number_found);
void changeMatrix(Matrix& matrix);
std::string getShortestPath(const Matrix& matrix, const std::vector<std::string>& city_names, int from, int to);
std::string searchMinRoadFromAToB(Matrix& matrix, const std::vector<std::string>& city_names, int from, int to);
std::string printCityThatDontHaveRoad(Matrix matrix, const std::vector<std::string>& name_city);
bool checkForDoubleLoop(const std::vector<int>& path, int curCity);
void createPath(const Matrix& matrix, std::vector<std::vector<int>>& paths, std::vector<int> current_path, int fromCity, int toCity);
std::string searchAllRoadFromAToB(Matrix matrix, std::vector<std::string> name_city, int number_find_from, int number_find_to);
std::string searchMinRoadFromAToAnyCity(Matrix matrix, std::vector<std::string> name_city, int number_find_from);