#pragma once

#include <iostream>
#include<fstream>
#include "List.h" 
#include <stdlib.h>
#include "Map.h"
using namespace std;

//struct for treenode`s kist 
struct flights
{
	string city;
	int cost;
};
struct data_flight
{
	int label = INT_MAX; // shortest way to this city
	bool is_visited = false; // was this city processed or not
	List<flights> adjency;
};
//helping struct
struct aviation
{
	string city;
	string  to_city;
	string cost;
	string back_cost;
};
Map <string, data_flight> FileOpen()
{
	Map <string, data_flight > agency;//Map with flights
	ifstream file("data.txt");//creating  ifstream(our file)
	if (!file.is_open())
		cout << "Oops. File can not be opened. Be sure that data.txt is in a folder" << endl;
	else
	{
		while (!file.eof())//while it is not the end of the file 
		{
			aviation flight;
			flights passing;
			char symbol;//dividing line
			while ((symbol = file.get()) != ';')
				flight.city.push_back(symbol);
			while ((symbol = file.get()) != ';')
				flight.to_city.push_back(symbol);
			while ((symbol = file.get()) != ';')
				flight.cost.push_back(symbol);
			while (((symbol = file.get()) != '\n') && (!file.eof()))
				flight.back_cost.push_back(symbol);
			if (agency.find(flight.city))
			{
				if (flight.cost != "N/A") 
				{
					passing.city = flight.to_city;
					passing.cost = atoi(flight.cost.c_str());
					agency.find(flight.city)->data.adjency.push_back(passing); 
				}
				else
				{
					passing.city = flight.to_city;
					passing.cost = INT_MAX;

					agency.find(flight.city)->data.adjency.push_back(passing); 
				}
			}
			else//if found a city for the first time 
			{
				if (flight.cost != "N/A")//if we have a price 
				{
					data_flight i_d;
					passing.city = flight.to_city;
					passing.cost = atoi(flight.cost.c_str());
					i_d.adjency.push_back(passing);
					agency.insert(flight.city, i_d); // insert the city

				}
				else
				{
					data_flight i_d;
					passing.city = flight.to_city;
					passing.cost = INT_MAX;
					i_d.adjency.push_back(passing);
					agency.insert(flight.city, i_d);//insert the city
				}
			}
			//back flight
			if (agency.find(flight.to_city))
			{
				if (flight.back_cost != "N/A") 
				{
					passing.city = flight.city;
					passing.cost = atoi(flight.back_cost.c_str());
					agency.find(flight.to_city)->data.adjency.push_back(passing);
				}
				else
				{
					passing.city = flight.city;
					passing.cost = INT_MAX;

					agency.find(flight.to_city)->data.adjency.push_back(passing);
				}
			}
			else  
			{
				if (flight.back_cost != "N/A") 
				{
					data_flight i_d;
					passing.city = flight.city;
					passing.cost = atoi(flight.back_cost.c_str());
					i_d.adjency.push_back(passing);
					agency.insert(flight.to_city, i_d); 
				}
				else
				{
					data_flight i_d;
					passing.city = flight.city;
					passing.cost = INT_MAX;
					i_d.adjency.push_back(passing);
					agency.insert(flight.to_city, i_d);
				}
			}
		}
		file.close();
	}
	return agency;
}
int Find_flight_cost(string from, string to, Map<string, data_flight>* shedule)
{
	List<string> cities = shedule->get_keys();
	shedule->find(from)->data.label = 0; // nullifying main city`s label
	size_t counter = 0;
	do
	{
		for (size_t i = 0; i < shedule->find(from)->data.adjency.get_size(); i++)
		{
			flights copy = shedule->find(from)->data.adjency.at(i);
			if (shedule->find(copy.city)->data.label > shedule->find(from)->data.label + copy.cost)
			{//change the shortest way to city
				shedule->find(copy.city)->data.label = shedule->find(from)->data.label + copy.cost;
			}
		}
		shedule->find(from)->data.is_visited = true;//Marking the city
		++counter;
		int min = INT_MAX;
		for (size_t i = 0; i < cities.get_size(); i++)//search for the shortest unmarked city 
		{// find the city with the smallest way to it
			if ((min > shedule->find(cities.at(i))->data.label) && !shedule->find(cities.at(i))->data.is_visited)
			{
				from = cities.at(i);
				min = shedule->find(cities.at(i))->data.label;
			}
		}
	} while (cities.get_size() != counter);
	return shedule->find(to)->data.label;
}