#include "pch.h"
#include <iostream>
#include <graphs.h>

TEST(TestGraphs, AddCity)
{
	Matrix matrix(2);
	addCity(matrix);

	EXPECT_EQ(3, matrix.size());
	EXPECT_EQ(0, matrix[0].back());
	EXPECT_EQ(0, matrix[1].back());

	std::vector<int> nullVec(3);
	EXPECT_EQ(nullVec , matrix[2]);
}

TEST(TestGraphs, AddCityEmpty)
{
	Matrix matrix;
	addCity(matrix);

	EXPECT_EQ(1, matrix.size());
	std::vector<int> nullVec(1);
	EXPECT_EQ(nullVec, matrix[0]);
}

TEST(TestGraphs, CityExist)
{
	std::vector<std::string> name_city = { "1", "2", "3" };
	int i = 2;
	EXPECT_EQ(true, checkForAlreadyExist("2", name_city, i));
	EXPECT_EQ(false, checkForAlreadyExist("4", name_city, i));
}

TEST(TestGraphs, CityExistInEmptyVector)
{
	std::vector<std::string> name_city(0);
	int i = 0;
	EXPECT_EQ(false, checkForAlreadyExist("", name_city, i));
	EXPECT_EQ(false, checkForAlreadyExist("4", name_city, i));
}

TEST(TestGraphs, SearchTheNumber)
{
	std::vector<std::string> name_city = { "1", "2", "3", "4" };
	int count_cities = 4;
	EXPECT_EQ(3, searchTheNumber(name_city, "4", count_cities));
	EXPECT_EQ(1, searchTheNumber(name_city, "2", count_cities)); 
	EXPECT_EQ(-1, searchTheNumber(name_city, "5", count_cities));
}

TEST(TestGraphs, SearchTheNumberInEmptyVector)
{
	std::vector<std::string> name_city(0);
	int count_cities = 0;
	EXPECT_EQ(-1, searchTheNumber(name_city, "4", count_cities));
}

TEST(TestGraphs, DeleteCity)
{
	Matrix matrix = { {0, 1, 1}, {1, 0, 1}, {1,1,0} };
	Matrix result = { {0, 1}, {1,0} };

	delCity(matrix, 0);
	EXPECT_EQ(result, matrix);

	matrix = { {0, 1, 1}, {1, 0, 1}, {1,1,0} };

	delCity(matrix, 1);
	EXPECT_EQ(result, matrix);

	matrix = { {0, 1, 1}, {1, 0, 1}, {1,1,0} };

	delCity(matrix, 2);
	EXPECT_EQ(result, matrix);
}

TEST(TestGraphs, AlgorythmFloyda3X3)
{
	Matrix matrix = { {0, 5, 2}, {0,0,0}, {0,2,0} };
	changeMatrix(matrix);
	Matrix result = { {0,2,2}, {0,0,0}, {0,1,0} };
	EXPECT_EQ(result, matrix);
}

TEST(TestGraphs, AlgorythmFloyda4X4)
{
	Matrix matrix = { {0, 2, 4, 3}, {0, 0, 1, 2}, {0, 0, 0, 1}, { 0, 0, 0, 0 } };
	changeMatrix(matrix);
	Matrix result = { {0, 1, 1, 3}, {0, 0, 2, 3}, {0, 0, 0, 3}, {0,0,0,0} };
	EXPECT_EQ(result, matrix);
}

TEST(TestGraphs, AlgorythmFloyda0X0)
{
	Matrix matrix;
	changeMatrix(matrix);
	Matrix result;
	EXPECT_EQ(result, matrix);
}

TEST(TestGraphs, AlgorythmFloyda1X1)
{
	Matrix matrix = { {0} };
	changeMatrix(matrix);
	Matrix result = { {0} };;
	EXPECT_EQ(result, matrix);
}

TEST(TestGraphs, MinRoadFromAToB3X3)
{
	Matrix matrix = { {0, 5, 2}, {0,0,0}, {0,2,0} };
	std::vector<std::string> name_city = { "1", "2", "3" };
	std::string result = "1->3->2\n";
	
	EXPECT_EQ(result, searchMinRoadFromAToB(matrix, name_city, 0, 1));
	EXPECT_EQ("No path found\n", searchMinRoadFromAToB(matrix, name_city, 1, 0));
}

TEST(TestGraphs, MinRoadFromAToB4X4)
{
	Matrix matrix = { {0, 2, 4, 3}, {0, 0, 1, 2}, {0, 0, 0, 1}, { 0, 0, 0, 0 } };
	std::vector<std::string> name_city = { "1", "2", "3", "4"};
	std::string result = "1->2->3\n";

	EXPECT_EQ(result, searchMinRoadFromAToB(matrix, name_city, 0, 2));
	EXPECT_EQ("No path found\n", searchMinRoadFromAToB(matrix, name_city, 1, 0));
}

TEST(TestGraphs, CityThatDontHaveRoad)
{
	Matrix matrix = { {0, 5, 2}, {0,0,0}, {0,2,0} };
	std::vector<std::string> name_city = { "1", "2", "3" };
	EXPECT_EQ("From 2 to 1\nFrom 2 to 3\nFrom 3 to 1\n", printCityThatDontHaveRoad(matrix, name_city));
}

TEST(TestGraphs, AllRoadFromAToB)
{
	Matrix matrix = { {0, 5, 2}, {0,0,0}, {0,2,0} };
	std::vector<std::string> name_city = { "1", "2", "3" };
	EXPECT_EQ("1->2\n1->3->2\n",searchAllRoadFromAToB(matrix, name_city, 0, 1));
	EXPECT_EQ("Not found...\n", searchAllRoadFromAToB(matrix, name_city, 1, 0));
}

TEST(TestGraphs, MinRoadFromAToAnyCity)
{
	Matrix matrix = { {0, 5, 2}, {0,0,0}, {0,2,0} };
	std::vector<std::string> name_city = { "1", "2", "3" };
	EXPECT_EQ("From 1 to 2\n1->3->2\nFrom 1 to 3\n1->3\n", searchMinRoadFromAToAnyCity(matrix, name_city, 0));
	EXPECT_EQ("From 2 to 1\nNo path found\nFrom 2 to 3\nNo path found\n", searchMinRoadFromAToAnyCity(matrix, name_city, 1));
}

int main(int argc, char** argv) 
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

