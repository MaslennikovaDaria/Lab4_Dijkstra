// Lab4_DijkstraGraph.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include"Dijkstra.h"
#include<string>


int main()
{
	cout << "List of cities: " << "Berlin, Moscow, Tokyo, Stambul, Volgograd" << endl;
	string from = "Berlin";
	string to = "Tokyo";
	Map<string, data_flight>Map=FileOpen();
	cout << "the cheapest price from " << from << " to " << to << " is ";
	cout<<Find_flight_cost(from, to, &Map);
	system("pause");
	return 0;
}

