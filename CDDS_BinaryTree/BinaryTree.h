#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_

#pragma once
template<typename T>
class TreeNode;

template<typename T>
class BinaryTree
{
public:

	BinaryTree() {};
	~BinaryTree() {};

	/// <summary>
	/// Returns whether or not there are any nodes in the list
	/// </summary>
	bool isEmpty() {} const;
	/// <summary>
	/// Creates a new node that stores the given value and places it into the tree
	/// </summary>
	/// <param name="value">The new value to add to the tree</param>
	void insert(T value) {};
	/// <summary>
	/// Finds the node with the given value and removes it from the tree
	/// </summary>
	/// <param name="value">The value of the node to search for in the tree</param>
	void remove(T value) {};
	/// <summary>
	/// Finds and returns a node with the given value in the tree
	/// </summary>
	/// <param name="value">The value of the node to search for</param>
	TreeNode<T>* find(T value) {return nullptr;}

	void draw(TreeNode<T>* selected = nullptr) {}

private:
	/// <summary>
	/// Finds the node that matches the value in the list
	/// </summary>
	/// <param name="searchValue">The value of the node to search for</param>
	/// <param name="nodeFound">A pointer that will store the address of the node that was found</param>
	/// <param name="nodeParent">A pointer that will store the address of the parent of the node that was found</param>
	/// <returns>Whether or not a node matching the value could be found</returns>
	bool findNode(T searchValue, TreeNode<T>*& nodeFound, TreeNode<T>*& nodeParent) {}

	void draw(TreeNode<T>* currentNode, int x, int y, int horizontalSpacing, TreeNode<T>* selected = nullptr);

	TreeNode<T>* m_root = nullptr;
};

#endif

template<typename T>
inline void BinaryTree<T>::draw(TreeNode<T>* currentNode, int x, int y, int horizontalSpacing, TreeNode<T>* selected)
{
	//Decrease the horixontal space as the nodes draw
	horizontalSpacing /= 2;

	//Check if the current node is null
	if (currentNode)
	{
		//Draw the left thr child if this node has one
		if (currentNode->hasLeft())
		{
			//Draw a line between the left child and the current node 
			DrawLine(x, y, x - horizontalSpacing, y + 80, RED);
			//Draws the left child
			draw(currentNode->getLeft(), x - horizontalSpacing, y + 80, horizontalSpacing, selected);
		}

		//Draws the right child if this node has one
		if (currentNode->hasRight())
		{
			//Draw a line between the left child and the current node 
			DrawLine(x, y, x - horizontalSpacing, y + 80, RED);
			//Draws the right child
			draw(currentNode->getRight(), x - horizontalSpacing, y + 80, horizontalSpacing, selected);
		}

		//Draws the current the node 
		currentNode->draw(x, y, (selected == currentNode));
	}
}

template<typename T>
inline bool BinaryTree<T>::isEmpty() const
{
	//If there is no node at the root 
	if (m_root == nullptr)
		//. . . retiurns true
		return true;
	//if there are only node on the roots but none on the left or right 
	if (m_root->getLeft() == nullptr|| m_root->getRight() == nullptr)
		//. . . returns true
		return true;
	// other wise 
	return false;
}

template<typename T>
inline void BinaryTree<T>::insert(T value)
{
	//Creats a new node that is going to be inserted 
	TreeNode<T> newNode = new TreeNode<T>(value);
	
	//Creats a new current node from the root of the tree 
	TreeNode<T> currentNode = m_root;
	
	//Checks if there us a node in the root first
	//If there is nothing in the current node 
	if (currentNode == nullptr)
	{
		//Set the current node to be the node 
		m_root = newNode;
		//then is breaks out if the function 
		return;
	}

	else
	{
		//Whiel the current node does not equal nullptr
		while (currentNode != nullptr)
		{
			//if the new node data is greater then the current node data 
			if (newNode->getData() > currentNode->getData())
				//Make that current node to be that current nodes right node
				currentNode = currentNode.getRight();
			//. . . other wise 
			else
				//Make that current node to be that current nodes left node
				currentNode = currentNode.getLeft();
		}
		//Set that current node location to be the new node 
		currentNode = newNode;
	}

}

template<typename T>
inline void BinaryTree<T>::remove(T value)
{
	TreeNode<T> currentNode = m_root;

	while (currentNode.getData() != value)
	{

	}
}
