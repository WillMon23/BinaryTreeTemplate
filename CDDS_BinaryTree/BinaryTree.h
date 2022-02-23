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
	~BinaryTree() { delete m_root; };

	/// <summary>
	/// Returns whether or not there are any nodes in the list
	/// </summary>
	bool isEmpty() const;
	/// <summary>
	/// Creates a new node that stores the given value and places it into the tree
	/// </summary>
	/// <param name="value">The new value to add to the tree</param>
	void insert(T value);
	/// <summary>
	/// Finds the node with the given value and removes it from the tree
	/// </summary>
	/// <param name="value">The value of the node to search for in the tree</param>
	void remove(T value);
	/// <summary>
	/// Finds and returns a node with the given value in the tree
	/// </summary>
	/// <param name="value">The value of the node to search for</param>
	TreeNode<T>* find(T value);

	void draw(TreeNode<T>* selected = nullptr);

private:
	/// <summary>
	/// Finds the node that matches the value in the list
	/// </summary>
	/// <param name="searchValue">The value of the node to search for</param>
	/// <param name="nodeFound">A pointer that will store the address of the node that was found</param>
	/// <param name="nodeParent">A pointer that will store the address of the parent of the node that was found</param>
	/// <returns>Whether or not a node matching the value could be found</returns>
	bool findNode(T searchValue, TreeNode<T>*& nodeFound, TreeNode<T>*& nodeParent);

	void draw(TreeNode<T>* currentNode, int x, int y, int horizontalSpacing, TreeNode<T>* selected = nullptr);

	TreeNode<T>* m_root = nullptr;
};

#endif

template<typename T>
inline bool BinaryTree<T>::findNode(T searchValue, TreeNode<T>*& nodeFound, TreeNode<T>*& nodeParent)
{
	//Creats a new current node from the root of the tree 
	TreeNode<T>* currentNode = m_root;
	
	//Creats a parent holder node 
	TreeNode<T>* parentNode = nullptr;

	TreeNode<T>* childNode = find(searchValue);
	
	//Checks to see if a parent has been found 
	bool parentFound = false;

	//while the parent node is not found 
	while (!parentFound)
	{
		//Comparess values to see if the value that's being tried to be removed 
		//is larger or smaller then the current nodes value 
		if (currentNode->getData() > searchValue)
			currentNode = currentNode->getRight();
		else
			currentNode = currentNode->getLeft();

		if (currentNode->getLeft()->getData() == searchValue || currentNode->getLeft()->getData() == searchValue)
		{
			parentNode = currentNode;
			parentFound = true;
		}
	}

	if (childNode == nodeFound && parentNode == nodeParent)
		return true;

	return false;
}

template<typename T>
inline void BinaryTree<T>::draw(TreeNode<T>* currentNode, int x, int y, int horizontalSpacing, TreeNode<T>* selected)
{

	//Decrease the horizontal space as the nodes draw
	horizontalSpacing /= 2;

	//Check if the current node is null
	if (currentNode)
	{
		//Draws the left child if this node has one
		if (currentNode->hasLeft())
		{
			//Draws a line between the left child and the current node
			DrawLine(x, y, x - horizontalSpacing, y + 80, RED);
			//Draws the left child
			draw(currentNode->getLeft(), x - horizontalSpacing, y + 80, horizontalSpacing, selected);
		}

		//Draws the right child if this node has one
		if (currentNode->hasRight())
		{
			//Draws a line between this child and the current node
			DrawLine(x, y, x + horizontalSpacing, y + 80, RED);
			//Draws the right child
			draw(currentNode->getRight(), x + horizontalSpacing, y + 80, horizontalSpacing, selected);
		}
		//Draws the current node
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
	if (m_root->hasLeft() || m_root->hasRight())
		//. . . returns true
		return true;
	// other wise 
	return false;
}

template<typename T>
inline void BinaryTree<T>::insert(T value)
{
	bool setNode = false;

	//Creats a new node that is going to be inserted 
	TreeNode<T>* newNode = new TreeNode<T>(value);
	
	//Creats a new current node from the root of the tree 
	TreeNode<T>* currentNode = m_root;

	//Checks if there us a node in the root first
	//If there is nothing in the current node 
	if (currentNode == nullptr)
	{
		//Set the current node to be the node 
		m_root = newNode;
		//then is breaks out of the function 
		return;
	}

		//While the current node does not equal nullptr
	while (!setNode)
	{
		//if the new node data is greater then the current node data 
		if (newNode->getData() > currentNode->getData())
		{
			//Checks if there is a nullptr 
			if (currentNode->getRight() == nullptr)
			{//sets the right location to be the new node 
				currentNode->setRight(newNode);
				setNode = true;

			}
			// else 
			else
				currentNode = currentNode->getRight();
		}
		//. . . other wise 
		else if (newNode->getData() < currentNode->getData())
		{
			if (currentNode->getLeft() == nullptr )
			{
				currentNode->setLeft(newNode);
				setNode = true;
			}
			//Make that current node to be that current nodes left node
			else
				currentNode = currentNode->getLeft();
		}
		
		//Checks to see if the value being passed in resambles that of the 
		//currentnodes value
		if (currentNode->getData() == value)
			//breaks out of the loops if so
			break;
	}
	
}

template<typename T>
inline void BinaryTree<T>::remove(T value)
{	

	if (m_root == nullptr)
		return;

	TreeNode<T>* currentNode = m_root;

	//Creats a parent holder node 
	TreeNode<T>* parentNode = nullptr;

	TreeNode<T>* childNode = find(value);

	//Checks to see if a parent has been found 
	bool parentFound = false;

	//while the parent node is not found 
	while (true)
	{
		

		if (m_root->getData() == value && !m_root->hasLeft() && !m_root->hasRight())
		{
			delete m_root;
			m_root = nullptr;
			return;
		}

		if (currentNode->hasLeft())
		{
			if (currentNode->getLeft()->getData() == value)
			{ 
				parentNode = currentNode;               
				break;
			}
		}

		else if (currentNode->hasRight())
		{
			if (currentNode->getRight()->getData() == value)
			{
				parentNode = currentNode;
				break;
			}
		}

		if(currentNode)

		//Comparess values to see if the value that's being tried to be removed 
		//is larger or smaller then the value nodes value 
		if (currentNode->getData() < value)
			currentNode = currentNode->getRight();
		else
			currentNode = currentNode->getLeft();
	}

	if (!childNode->hasLeft() && !childNode->hasRight())
	{
		if (parentNode->hasLeft())
		{
			if (parentNode->getLeft()->getData() == value)
				parentNode->setLeft(nullptr);
		}

		else if (parentNode->hasRight())
		{
			if (parentNode->getRight()->getData() == value)
				parentNode->setRight(nullptr);
		}
		return;
	}

	else if (childNode->hasLeft() && childNode->hasRight());
	{
		
	}

	if (parentNode->hasLeft()) {
		if (parentNode->getLeft()->getData() == value)
		{
			if (childNode->hasLeft() && !childNode->hasRight())
			{
				parentNode->setLeft(childNode->getLeft());
				return;
			}
		}
	}

	if (parentNode->hasRight())
	{
		if (parentNode->getRight()->getData() == value)
		{
			if (childNode->hasRight() && !childNode->hasLeft())
			{
				parentNode->setRight(childNode->getRight());

				return;
			}
		}
	}
}

template<typename T>
inline TreeNode<T>* BinaryTree<T>::find(T value)
{

	//Creats a variable easly exchange from the root
	TreeNode<T>* currentNode = m_root;

	//Loops until the current node has thw value that's being looked for 
	while (currentNode->getData() != value)
	{
		//If the value in the current node is greater then the value 
		if (currentNode->getData() > value)
		{
			if (currentNode->hasLeft())
				//Make that currrentNode to be that node to the left of the currnt node
				currentNode = currentNode->getLeft();
		}
		// else. . .
		else
			if (currentNode->hasRight())
				//Make that currrentNode to be that node to the right of the currnt node
				currentNode = currentNode->getRight();
	}

	return currentNode;
}

template<typename T>
inline void BinaryTree<T>::draw(TreeNode<T>* selected)
{
	draw(m_root, 400, 40, 400, selected);
}
 