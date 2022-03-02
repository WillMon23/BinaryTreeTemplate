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
	/// <summary>
	/// Gets displaces the value to the tree
	/// </summary>
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

	/// <summary>
	/// Displays  the UI in cloraltion to where the node is in the tree taking in the locaction 
	/// </summary>
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
		if (!currentNode->hasLeft() || !currentNode->hasRight())
			break;
		//if the current node data was greater then the the surched value 
		if (currentNode->getData() > searchValue)
		{
			//If current has a right node 
			if (currentNode->hasRight())
				// current node would now equal the current right node 
				currentNode = currentNode->getRight();
		}
		//else 
		else
		{
			//If current has a left node 
			if (currentNode->hasLeft())
				// current node would now equal the current left node 
				currentNode = currentNode->getLeft();
		}

		//If current has a left node 
		if (currentNode->hasLeft())
		{
			//Compares the value of the current nodes left node data and the value in question 
			if (currentNode->getLeft()->getData() == searchValue)
			{
				//Set the parent to be the current node 
				parentNode = currentNode;
				//Sets parentFound to be true
				parentFound = true;
			}
		}
		//if else the current node has a right 
		else if (currentNode->hasRight())
		{
			//Compares the value of the current nodes right node data and the value in question 
			if (currentNode->getRight()->getData() == searchValue)
			{
				//Set the parent to be the current node
				parentNode = currentNode;
				//Sets parentFound to be true
				parentFound = true;

			}
		}
	}
	//If the child node equals the node found  and the parent node equals the parent in the argument 
	if (childNode == nodeFound && parentNode == nodeParent)
		//Return True
		return true;
	//Else false
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
		//. . . other wise if the new node data is less then the current node data . . . 
		else if (newNode->getData() < currentNode->getData())
		{
			//. . . if the current node does not has a left node 
			if (!currentNode->hasLeft())
			{
				//We set this current node left node new node  
				currentNode->setLeft(newNode);
				setNode = true;
			}
			else
				//Make that current node to be that current nodes left node
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
////////////////////////////////////////////////////////////////////////////////////////////////
//Deals with checking the values of the root first, In case the value im removing is the root //																						  //
////////////////////////////////////////////////////////////////////////////////////////////////
	//checks if the root is empty															  //
	if (m_root == nullptr)																	  //
		//Leaves the funtion 																  //
		return;																				  //
	//If the value is the same as the roots value and it does not have node attached 		  //
	if (m_root->getData() == value && !m_root->hasLeft() && !m_root->hasRight())			  //
	{																						  //
		//delets the node 																	  //
		delete m_root;																		  //
		//sets the root to be a nullptr 													  //
		m_root = nullptr;																	  //
		//then it leaves the function														  //
		return;																				  //
	}																						  //
																							  //
	//If the value is the same as the root but it does not have a right node				  //
	else if (m_root->getData() == value && m_root->hasLeft() && !m_root->hasRight())		  //
	{																						  //
		//																					  //
		m_root = m_root->getLeft();															  //
		return;																				  //
	}																						  //
																							  //
	else if (m_root->getData() == value && !m_root->hasLeft() && m_root->hasRight())		  //
	{																						  //
		m_root = m_root->getRight();														  //
		return;																				  //
	}																						  //																						  //
////////////////////////////////////////////////////////////////////////////////////////////////
																							  //
////////////////////////////////////////////////////////////////////////////////////////////////
	TreeNode<T>* currentNode = m_root;

	//Creats a parent holder node 
	TreeNode<T>* parentNode = nullptr;

	TreeNode<T>* childNode = find(value);

	//Checks to see if a parent has been found 
	bool parentFound = false;
	// Also check to see if the childNode is pointing to a nullptr
	if (childNode == nullptr)
		//Just leavves the function
		return;
	
//////////////////////////////////////////////////////////////////////////////////////////////
//Meant to look for the parent of the child 												//  
//////////////////////////////////////////////////////////////////////////////////////////////
	//while the parent node is not found 													//
	do																						//
	{																						//
		//if the current node has a left node												//
		if (currentNode->hasLeft())															//
		{																					//
			//if the current nodes to the left eqals the value in the argument 				//
			if (currentNode->getLeft()->getData() == value)									//
			{ 																				//
				// That'll be considered the parent 										//
				parentNode = currentNode;           										//
				//Just incase it breaks out the loop right away								//
				break;																		//
			}																				//
		}																					//
		//If the cyrrent node has a left node 												//
		if (currentNode->hasRight())														//
		{																					//
		//The current node right node data is equal to the value passed through the argument//
			if (currentNode->getRight()->getData() == value)								//
			{																				//
				// Will consider the current node to be the parent							//
				parentNode = currentNode;													//
				break;																		//
			}																				//
		} 																					//
																							//
		//Comparess values the values that are before them by checking the node 			//
		//Thats before them and if the value is greater then or lesser then the 			//
		//That'll dictate wether or not the current node will be its left noded or right 	//
		//node																				//
		//if the current node data is smaller then the value								//
		if (currentNode->getData() < value)													//
			//Current node will equal the current nodes right node							//
			currentNode = currentNode->getRight();											//
		// other wise. . .																	//
		else																				//
			//Current node will equal the current nodes left node							//
			currentNode = currentNode->getLeft();											//
		//While the current node is not pointing to null									//
	} while (currentNode != nullptr);														//
//////////////////////////////////////////////////////////////////////////////////////////////
//Checks to see if the child has no nodes attached to it 									//
//////////////////////////////////////////////////////////////////////////////////////////////
	//If the child has no left or right nodes 												//
	if (!childNode->hasLeft() && !childNode->hasRight())									//
	{																						//
		//If the parent has a left node 													//
		if (parentNode->hasLeft())															//
		{																					//
			//If the parents left node data is that of the values 							//
			if (parentNode->getLeft()->getData() == value)									//
				// Set that value to be a nullptr											//
				parentNode->setLeft(nullptr);												//
		}																					//
		//If the parent has a right node 													//
		if (parentNode->hasRight())															//
		{																					//
			//If the parents right node data is that of the values 							//
			if (parentNode->getRight()->getData() == value)									//
				// Set that value to be a nullptr											//
				parentNode->setRight(nullptr);												//
		}																					//
		//Leave the function																//
		return;																				//
	}																						//
//////////////////////////////////////////////////////////////////////////////////////////////
//Checks to see if the child has two nodes attached to it 									//		
//////////////////////////////////////////////////////////////////////////////////////////////
	//If there is left node ans a right node for the child									//
	else if (childNode->hasLeft() && childNode->hasRight())									//
	{																						//
		//Sets the currrent node to be the right node of the child							//
		currentNode = childNode->getRight();												//
																							//
		//If the current node does not have a node attached to it 							//
		if (!currentNode->hasLeft() && !currentNode->hasRight())							//
		{																					//
			//Sets the child node data to be that current nodes data 						//
			childNode->setData(currentNode->getData());										//
			//Removed that right node 														//
			childNode->setRight(nullptr);													//
			//LEaves the function															//
			return;																			//
		}																					//
																							//
		//While the current node is has aleft node 											//
		while (currentNode->hasLeft())														//
		{																					//
			//If that current node has a left node 											//
			if (currentNode->hasLeft())														//
			{																				//
				//Set the current node to be the current nodes left node 					//
				currentNode = currentNode->getLeft();										//
				//Goes through the loop from the start										//
				continue;																	//
			}																				//
			//If the current has a left 													//
			if (currentNode->hasRight())													//
			{																				//
				//Set the current node to be the current nodes right node 					//
				currentNode = currentNode->getRight();										//
			}																				//
		}																					//
																							//
		//set the child node data to be what the data in the current node is 				//
		childNode->setData(currentNode->getData());											//
		if (currentNode->hasLeft())															//
			//Sets the left node to point to nullptr										//
			currentNode->setLeft(nullptr);													//
		//If the current node has a right node 												//
		else if (currentNode->hasRight())													//
			//Set current node to point to a nullptr										//
			currentNode->setRight(nullptr);													//
		//Leaves the function 																//
		return;																				//
	}																						//
//////////////////////////////////////////////////////////////////////////////////////////////
// Once the check has gone through it checks if it only has a left node 					//
//////////////////////////////////////////////////////////////////////////////////////////////
	//If the parent node has a left node													//
	else if (parentNode->hasLeft()) 														//
	{																						//
		// the child node has a left node but not a right node 								//
		if (childNode->hasLeft() && !childNode->hasRight())									//
			//Set the parent left node to be that node from the child to the left 			//
			parentNode->setLeft(childNode->getLeft());										//
																							//
		else																				//
			//Set the parent left node to be that node from the child to the right			//
			parentNode->setLeft(childNode->getRight());										//
	}																						//
//////////////////////////////////////////////////////////////////////////////////////////////
// Once the check has gone through it checks if it only has a right node 					//
//////////////////////////////////////////////////////////////////////////////////////////////
	//If the parent node has a left node													//
	else if (parentNode->hasRight())														//
	{																						//
		// the child node has a right node but not a left node								//
		if (!childNode->hasLeft() && childNode->hasRight())									//
			//Set the parent left node to be that node from the child to the right 			//
			parentNode->setRight(childNode->getRight());									//
																							//
		else																				//
			//Set the parent left node to be that node from the child to the left			//
			parentNode->setRight(childNode->getRight());									//
	}
	
}

template<typename T>
inline TreeNode<T>* BinaryTree<T>::find(T value)
{

	//Creats a variable easly exchange from the root
	TreeNode<T>* currentNode = m_root;

	if (!currentNode->hasLeft() && !currentNode->hasRight())
			return nullptr;
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
 