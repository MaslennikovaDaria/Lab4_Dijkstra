#pragma once

#include "List.h"

template <typename Tk, typename Td>
class Map
{
private:
	//template <typename Tk, typename Td>
	class TreeNode
	{
	public:
		bool color_red;
		Tk key;
		Td data;
		TreeNode*left;
		TreeNode*right;
		TreeNode*parent;
		TreeNode() {};
		TreeNode(Tk key, Td data, TreeNode*left = nullptr, TreeNode*right = nullptr)//consructor
		{
			this->data = data;
			this->key = key;
			this->parent = nullptr;
			this->left = left;
			this->right = right;
			this->color_red = true;
		}

	};
	TreeNode*root;

	int size;
	//void clearPrivate(TreeNode*);
	List<Tk> get_key(List<Tk> head, TreeNode* tempr)
	{
		if (tempr != nullptr)
		{

			head = get_key(head, tempr->left);
			head = get_key(head, tempr->right);
			head.push_back(tempr->key);
		}
		return head;
	}
	List<Td> get_data(List<Td> head, TreeNode* tempr)
	{
		if (tempr != nullptr)
		{
			head = get_data(head, tempr->left);
			head = get_data(head, tempr->right);
			head.push_back(tempr->data);
		}
		return head;
	}
public:
	Map() :size(0), root(nullptr) {}; //constructor
									  //	~Map();//destructor
	void insert(Tk, Td);
	void rotL(TreeNode*);//private
	void rotR(TreeNode*);//private
	void InsertBalance(TreeNode*);//private
	void clear();
	TreeNode* find(Tk);
	List<Tk> get_keys();
	List<Td> get_values();
	int get_size();
	void remove(Tk);
	void RemoveBalance(TreeNode*);//private
};



template <typename Tk, typename Td>
List<Tk> Map<Tk, Td>::get_keys()
{
	List<Tk> head;
	TreeNode* tempr = root;
	head = get_key(head, tempr);
	return head;
}
template <typename Tk, typename Td>
List<Td> Map<Tk, Td>::get_values()
{
	List<Td> head;
	TreeNode* tempr = root;
	head = get_data(head, tempr);
	return head;
}
//
//template <typename Tk, typename Td> //destructor 
//Map <Tk, Td>::~Map()
//{
//	clearPrivate(root);
//}
template <typename Tk, typename Td>
void Map <Tk, Td>::insert(Tk key, Td data)
{
	TreeNode *tempr = nullptr;
	TreeNode *previous = nullptr;
	TreeNode *current = new TreeNode(key, data);
	tempr = root;
	if (root == nullptr)//if there is no tree
	{
		root = current;//new node is a root
		root->parent = nullptr;
	}
	else //if tree is not empty
	{
		while (tempr != nullptr)
		{
			previous = tempr;
			if (tempr->key < current->key) //going left
				tempr = tempr->right;
			else
				tempr = tempr->left;// going right
		}
		current->parent = previous;//
		if (previous->key < current->key)//if current key less than previous, it's a left son
			previous->right = current;
		else
			previous->left = current;// otherwise it's a right son

	}
	InsertBalance(current);//balance
	size++;//changing the amount of nodes
};

template <typename Tk, typename Td>
void Map <Tk, Td>::rotL(TreeNode* current)
{
	if (current->right == nullptr)
		return;
	else
	{
		TreeNode*child = current->right;
		if (child->left != nullptr)
		{
			current->right = child->left;
			child->left->parent = current;
		}
		else
		{
			current->right = nullptr;
		}
		if (current->parent != nullptr)
			child->parent = current->parent;
		if (current->parent == nullptr)
			root = child;
		else
		{
			if (current == current->parent->left)
				current->parent->left = child;
			else
				current->parent->right = child;
		}
		child->left = current;
		current->parent = child;
	}
}

template <typename Tk, typename Td>
typename Map<Tk, Td>::TreeNode* Map<Tk, Td>::find(Tk key)
{
	TreeNode*temp = root;
	while (temp)
	{
		if (key < temp->key)
			temp = temp->left;
		else if (key > temp->key)
			temp = temp->right;
		else if (key == temp->key)
			break;
	}
	return temp;
}

template <typename Tk, typename Td>
void Map <Tk, Td>::rotR(TreeNode*current)
{
	if (current->left == nullptr)
		return;
	else
	{
		TreeNode*child = current->left;
		if (child->right != nullptr)
		{
			current->left = child->right;
			child->right->parent = current;
		}
		else
			current->left = nullptr;
		if (current->parent != nullptr)
			child->parent = current->parent;
		if (current->parent == nullptr)
			root = child;
		else
		{
			if (current == current->parent->left)
				current->parent->left = child;
			else
				current->parent->right = child;
		}
		child->right = current;
		current->parent = child;
	}
}

template <typename Tk, typename Td> //
void Map <Tk, Td>::InsertBalance(TreeNode*tempr)
{
	TreeNode* uncle;
	if (root == tempr)//change the color of root
	{
		tempr->color_red = false;
		return;
	}

	while (tempr->parent != nullptr &&tempr->parent->color_red == true) //while current has a red father
	{
		TreeNode*grandparent = tempr->parent->parent;
		if (grandparent->left == tempr->parent)
		{
			if (grandparent->right != nullptr)
			{
				uncle = grandparent->right;
				if (uncle->color_red = true)
				{ //if uncle is red, grandparent is red & parent and uncle are black
					tempr->parent->color_red = false;
					uncle->color_red = false;
					grandparent->color_red = true;
					tempr = grandparent;
				}

			}
			else
			{
				if (tempr->parent->right == tempr)
				{
					tempr = tempr->parent;
					rotL(tempr);
				}
				tempr->parent->color_red = false;
				grandparent->color_red = true;
				rotR(grandparent);
			}
		}
		else
		{
			if (grandparent->left != nullptr)
			{
				uncle = grandparent->left;
				if (uncle->color_red = true)
				{
					tempr->parent->color_red = false;
					uncle->color_red = false;
					grandparent->color_red = true;
					tempr = grandparent;
				}
			}
			else
			{
				if (tempr->parent->left == tempr)
				{
					tempr = tempr->parent;
					rotR(tempr);
				}
				tempr->parent->color_red = false;
				grandparent->color_red = true;
				rotL(grandparent);
			}
		}
		root->color_red = false;
	}

}


//template <typename Tk, typename Td>
//void Map <Tk, Td>::clearPrivate(TreeNode*tempr)
//{
//	if (tempr != nullptr)
//	{
//		if (tempr->right != nullptr)
//			clearPrivate(tempr->right);
//		if (tempr->left != nullptr)
//			clearPrivate(tempr->left);
//		size--;
//		delete tempr;
//		tempr = nullptr;
//	}
//}

template <typename Tk, typename Td>
int Map <Tk, Td>::get_size()//function for tests 
{
	return size;

}
template <typename Tk, typename Td>
void Map <Tk, Td>::remove(Tk key)
{
	if (root == nullptr) //if tree is empty u don't have to do anything, just relax
	{
		return;
	}

	TreeNode* deleting = find(key);
	if (deleting == nullptr) //if we don't have this element, we do not delete anything
		return;


	TreeNode* moving;
	TreeNode* temp;

	if (deleting->left == nullptr || deleting->right == nullptr)
		moving = deleting;
	else //has 2 children
	{
		if (deleting->left != nullptr)//if deleting has a left child
		{
			temp = deleting->left;
			while (temp->right != nullptr)
				temp = temp->right;
		}
		else
		{
			temp = deleting->right;
			while (temp->left != nullptr)
				temp = temp->left;
		}
		moving = temp; //find node without left child
	}
	if (moving->left != nullptr)
		temp = moving->left;
	else
	{
		if (moving->right != nullptr)
			temp = moving->right;
		else
			temp = nullptr;
	}
	if (temp != nullptr)
		temp->parent = moving->parent;

	if (moving->parent == nullptr)
		root = temp;
	else
	{
		if (moving == moving->parent->left)
			moving->parent->left = temp;
		else
			moving->parent->right = temp;
	}

	if (moving != deleting)
	{
		deleting->color_red = moving->color_red;
		deleting->key = moving->key;
		deleting->data = moving->data;
	}

	if (moving->color_red == false)
		RemoveBalance(temp);
	size--;
}

template <typename Tk, typename Td>
void Map <Tk, Td>::RemoveBalance(TreeNode* current)
{
	if (current != nullptr)
	{
		TreeNode* temp;
		while (current != root && !current->color_red)
		{

			if (current->parent->left == current) //if node is a left child
			{
				temp = current->parent->right;
				if (temp->color_red) //if brother is red
				{
					temp->color_red = false; //brother = black
					current->parent->color_red = true; //parent = red
					rotL(current->parent);
					temp = current->parent->right;
				}
				if (!temp->right->color_red && !temp->left->color_red) // if both children  are black
				{
					temp->color_red = true;
					current = current->parent;
				}
				else
				{
					if (!temp->right->color_red) //if right is black

					{
						temp->left->color_red = false;
						temp->color_red = true;
						rotR(temp);
						temp = current->parent->right;
					}
					temp->color_red = current->parent->color_red;
					current->parent->color_red = false;
					temp->right->color_red = false;
					rotL(current->parent);
					current = root;
				}
			}
			else //if node is a right child
			{
				temp = current->parent->left;
				if (temp->color_red) //brother is red
				{
					temp->color_red = true;
					current->parent->color_red = true;
					rotR(current->parent);
					temp = current->parent->left;
				}
				if (!temp->left->color_red && !temp->right->color_red) // both child are black
				{
					temp->color_red = true;
					current = current->parent;
				}
				else
				{
					if (!temp->left->color_red) //if left is black

					{
						temp->right->color_red = false;
						temp->color_red = true;
						rotL(temp);
						temp = current->parent->left;
					}

					temp->color_red = current->parent->color_red;

					current->parent->color_red = false;

					temp->left->color_red = false;

					rotR(current->parent);

					current = root;
				}
			}

		}
		current->color_red = false;

		root->color_red = false;
	}
}

template <typename Tk, typename Td>
void Map <Tk, Td>::clear()
{
	clearPrivate(root);
	root = nullptr;
}
