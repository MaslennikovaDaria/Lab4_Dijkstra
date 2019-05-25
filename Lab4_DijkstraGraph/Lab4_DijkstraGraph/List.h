#pragma once
#include <iostream>
using namespace std;

template <class T> //template of the element of the list
class Node
{
public:
	T data;
	Node *next;
	Node *previous;
	size_t size;

	Node(T data1) //constructor
	{
		next = nullptr;
		previous = nullptr;
		data = data1;
	}

	Node() //default constructor
	{
		next = nullptr;
		previous = nullptr;
	}

	/*Node()//destrucrot
	{
	if(next)
	delete next;
	if(previous)
	delete previous;

	}*/
};

template <class T>
class List
{

public:
	Node <T> *head;
	Node <T> *tail;
	/*	~List()//destrucrot
	{
	this->clear();
	}*/
	List() :head(nullptr), tail(nullptr) {};
	friend ostream& operator<<(ostream &out, const List<T> &list)
	{
		if (list.head)
		{
			Node<T>* temp = list.head;
			do
			{
				out << temp->data;
				if (temp = temp->next)
					out << ", ";
			} while (temp);
		}
		else
		{
			out << "Empty.";
			out << '\n';
		}
		return out;
	}
	template <class T>
	inline void push_back(T data1)//adding a new element at the end of the list
	{
		Node<T>* new_element = new Node<T>;
		new_element->data = data1;
		if (head == nullptr) //if list is empty
		{
			head = tail = new_element; // new element is the head

		}
		else
		{//adding new element 
			tail->next = new_element;
			new_element->previous = tail;
			tail = new_element;
		}
	}
	//everything is alright i guess
	template <class T>
	void push_front(T data1) //adding new element at the begining of the list
	{
		Node<T>* new_element = new Node<T>;
		new_element->data = data1;
		if (head == nullptr)
		{
			head = new_element;
			tail = new_element;
		}
		else
		{
			Node<T>*tempr = head;
			head = new_element;
			new_element->next = tempr;
			tempr->previous = head;
		}
	}
	void pop_back() // delete the last element
	{// also if empty
		if (head == tail)
		{
			delete head;
			head = nullptr;
			tail = nullptr;
		}
		else
		{
			Node<T>*tempr = tail;
			tail = tail->previous;
			tail->next = nullptr;
			delete tempr;
		}

	}
	void pop_front()//delete the first element
	{
		if (head == tail)
		{
			delete head;
			head = nullptr;
			tail = nullptr;

		}
		else
		{
			Node<T>*tempr = head;
			head = head->next;

			head->previous = nullptr;
			delete tempr;
		}
	}
	template <class T>
	void insert(size_t index, T data)//adding new element at any needed place in the list
	{
		size_t i = 0;
		//checking the index
		Node<T>*tempr = head;
		while (tempr != nullptr && i != index)
		{
			tempr = tempr->next;
			i++;
		}
		if (i < index)
		{
			delete tempr; //delete unnecessery temproray element
			throw(out_of_range("Seeking element is out of range"));
		}

		Node<T>* new_element = new Node<T>;
		new_element->data = data;


		if (tempr != nullptr) //if temprorary element is in the range of  the list 
		{
			if (tempr->previous != nullptr)//if temprorary element isn't the first in the list 
				tempr->previous->next = new_element; //adding the element between previous and temprorary
			else
				head = new_element; // new element is the first in the list

			new_element->next = tempr;
			tempr->previous = new_element;
			new_element->previous = tempr->previous;
		}
		else if (head == nullptr)//if the list is empty
		{
			head = tail = new_element;//adding new head
		}
		else if (i == index) // if temprorary element is after the last element of the list
		{//new element is the new tail
			tail->next = new_element;
			new_element->previous = tail;
			tail = new_element;
		}
	}
	T at(size_t index) //getting information from any needed element of the list
	{
		size_t i = 0;
		Node <T>* tempr = head;
		while (tempr != nullptr && i != index)
		{
			tempr = tempr->next;
			i++;
		}

		if (tempr != nullptr)
			return tempr->data;
		else
			throw(out_of_range(" Seeking index is out of range\n")); // error if there is no elements in the list or there is no such element

	}
	void remove(size_t index)//delete any element
	{
		size_t i = 0;
		Node<T>*tempr = head;
		while (tempr != nullptr && i != index)
		{
			tempr = tempr->next;
			i++;
		}
		if (i < index)
		{
			delete tempr; //delete unnecessery temproray element
			throw(out_of_range("Seeking element is out of range"));
		}
		else if (tempr != nullptr)
		{
			if (tempr->next == nullptr && tempr->previous == nullptr)//if there is only one element
			{
				delete tempr;
				head = nullptr;
				tail = nullptr;
			}
			else if (tempr->next != nullptr && tempr->previous == nullptr)//delete head
			{
				head = tempr->next;
				head->previous = nullptr;
				delete tempr;
			}
			else if (tempr->next == nullptr&&tempr->previous != nullptr)//delete tail
			{
				tail = tail->previous;
				tail->next = nullptr;
				delete tempr;
			}
			else if (tempr->next != nullptr && tempr->previous != nullptr) //delete any element inside(in the middle) of the list
			{
				tempr->next->previous = tempr->previous;
				tempr->previous->next = tempr->next;
				delete tempr;
			}
		}


	}
	size_t get_size() // getting information about the size of the list
	{
		size_t i = 0;
		Node<T>*tempr = head;
		while (tempr != nullptr)
		{
			tempr = tempr->next;//error
			i++;
		}
		return i;
	}

	void clear() // delete all the list
	{
		while (head)
			pop_back();
	}

	template <class T>
	void set(size_t index, T data1) //changing the data of the needed element
	{
		//we are looking for an element and change his data
		size_t i = 0;
		Node <T>* tempr = head;
		while (tempr != nullptr && i != index)
		{
			tempr = tempr->next;
			i++;
		}

		if (tempr != nullptr)
			tempr->data = data1;
		else
			throw(out_of_range(" Seeking index is out of range\n")); // error if there is no elements in the list or there is no such element

	}


	bool isEmpty() //checking if list is empty
	{
		if (head == nullptr)
			return true;
		else
			return false;
	}
};
