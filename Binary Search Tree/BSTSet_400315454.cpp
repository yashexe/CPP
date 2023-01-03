#include "BSTSet.h"
#include "Stack.h"
#include <iostream>
#include <vector>
using namespace std;

//TC:1, SC:1
BSTSet::BSTSet()
{
	root = NULL;														//empty tree
}

//TC:n^2, SC:n
BSTSet::BSTSet(const std::vector<int>& input)
{
	bool previous_direction = false;												//initialize direction	true is right
	if(input.size() > 0)												// if valid input
	{
		root = new TNode(input[0],NULL,NULL);							//create new node representing start of tree
		TNode* current = root;											// var. that "looks" at a tree node
		TNode* previous = root;											// var. that keeps track of previous node

		for(int i = 1; i < input.size();i++)							//for i to number of tree nodes, incr. i by 1
		{
			while(current != NULL && current->element != input[i])		//while looking at a valid tree node and element isnt the current input val
			{
				if(current->element > input[i])							//if current node is greater than current input val
				{
					previous = current;									//prev becomes current
					current = current->left;							//current looks torwards left now
					previous_direction = false;									//leftwards
				}else if(current->element < input[i])					//if lesser than input val
				{
					previous = current;									//prev is now current
					current = current-> right;							//current goes towards right side of tree
					previous_direction = true;									//rightwards dir.
				}
			}
			if(current==NULL && previous_direction)								//if no longer looking at invalid part of tree rightwards
			{
				previous->right = new TNode(input[i],NULL,NULL);		//right most node is now the input val at i
			}															// this just so happens to be the greatest val in the tree
			if(current==NULL && !previous_direction)								//if smallest # yet
			{
				previous->left = new TNode(input[i],NULL,NULL);			// left most node is now the input val at i
			}
			current = root;												//reset vals
			previous = root;
		}
	}
}//TC: n^2, SC: n

BSTSet::~BSTSet()
{

	sortTree();															//sort tree
	for (int j = findMaxVal(root); j >= findMinVal(root); j--)		//looks through tree from max value to min value
	{
		remove(j);														//removes specific element
	}
}

//TC:logn, SC:1
bool BSTSet::isIn(int v)
{
	bool a;
	if(root == NULL)													//return false if no tree
	{
		a=0;
		return a;
	}


	TNode* current_view = root;													//node representing number currently being viewed
	while (current_view != NULL)
	{
		if (v > current_view->element)											//if number is greater than one being viewed
		{
			current_view=current_view->right;											//view shifts to right number
		}
		else if (v < current_view -> element) 									//if lesser
		{
			current_view = current_view -> left;											//shifts to left number
		}
		else
		{
			a=1;
			return a;													//if right, return true
		}
	}
	a=0;
	return a;															//number isnt in tree
}

//TC:logn,SC:1
void BSTSet::add(int v)
{
	if(root == NULL)
	{
		root = new TNode(v, NULL, NULL);								//if no tree before adding element, make the element to be added the root of a new tree
	}else
	{
		TNode *current_view = root;											//current view
		TNode *previous_view = root;											//previous view
		bool isRight = false;


		while(current_view != NULL && current_view->element != v) 					//iterates through tree
		{
			if (current_view->element > v) 									//if element being viewed is greater than v
			{
				previous_view = current_view;											//prev = present
				current_view = current_view->left;									//look at left element
				isRight = false;										//to the left of view
			}else if (current_view->element < v) 								//if lesser
			{
				previous_view = current_view;											//prev = present
				current_view = current_view->right;									//look at right element
				isRight = true;											//to the right of view
			}
		}

		if (current_view == NULL && isRight)
		{
			previous_view->right = new TNode(v, NULL, NULL);					//if the element to be added is outside current bounds, it becomes new node
		}

		if (current_view == NULL && !isRight)
		{
			previous_view->left = new TNode(v, NULL, NULL);						//if the element to be added is outside current bounds, it becomes new node
		}

		current_view = root;													//reset
		previous_view = root;
	}
}

//TC:n, SC:1
int BSTSet::findMinVal(TNode* t)
{
	if (t == NULL)
	{																	//if no proper input, return false
		return NULL;
	}
	while (t->left != NULL)
	{
		t = t->left;													//while elements are still to the left, view goes leftwards
	}																	//returns last(most left) element
	return (t->element);
}

//TC:n, SC:1
int BSTSet::findMaxVal(TNode* t)
{
	if (t == NULL)
	{
		return 0;													//if improper input
	}
	while (t->right != NULL) 											//same as before but rightwards
	{
		t = t->right;
	}
	return (t->element);
}

//TC:n^2, SC:1
void BSTSet::sortTree()
{

	TNode* new_root = new TNode(findMinVal(root), NULL, NULL);				//new tree sorted version

	TNode* current_view = new_root;													//current_view root

	for (int j = findMinVal(root) + 1; j <= findMaxVal(root); j++) 		//minimum to maximum tree vals
		{
			if (isIn(j)) 												//if value is in tree
			{
			current_view->right = new TNode(j,NULL,NULL);						//put into sorted tree
			current_view = current_view->right;
			}
	}
	root = new_root;														//regular version replaced with sorted version (sortest from smallest to largest)
}

//TC:n
//SC:1
bool BSTSet::remove(int v)
{
	bool a;
	if (root == NULL || isIn(v) == 0)									//if tree if empty/v isnt in tree return false
	{
		a=0;
		return a;
	}


	sortTree();															//sort tree


	if (root->element == v) 											//if v is the root of the tree
	{
		root = root->right;												//new root is now the right element and true is returned
		a=1;
		return a;
	}

	TNode* current_view = root;												//current_view nodes
	TNode* previous_view = root;


	while (current_view->element != v) 										//until v is found
	{
		previous_view = current_view;
		current_view = current_view->right;
	}


	if (current_view->right == NULL) 											//if v is a leaf-type node, remove it
	{
		previous_view->right = NULL;
		free(current_view);
	}


	else
	{
		previous_view->right = current_view->right; 									//if not leaf, change the child of the node to a leaf
	}
	a=1;
    return a;															//return true
}

//TC:nlogn, SC:1
void BSTSet::Union(const BSTSet& s)
{
	BSTSet s_copy = s;														//copy of s
	for (int j = findMinVal(s.root); j <= findMaxVal(s.root); j++) {	//looks through tree

		if (s_copy.isIn(j)) {												//if element is in s2
			add(j);														//add element
		}
	}
}

//TC:n, SC:1
void BSTSet::intersection(const BSTSet& s)
{
	sortTree();															//sort tree

	BSTSet s_copy = s;														//copy of s

	TNode* current_view = root;													//current_view node tree

	while (current_view != NULL) 												//looking through the nodes of the tree
	{

		if (!s_copy.isIn(current_view->element)) 									//if s2 does not have the element that current_view has
		{
			remove(current_view->element);										//remove the element that current_view has
		}

		current_view = current_view->right;												//current_view looks at rightward element
	}
}

//TC:n, SC:1
void BSTSet::difference(const BSTSet& s)
{

	BSTSet s_copy = s;														//copy of s

	s_copy.sortTree();														//sort tree

	TNode* current_view = s_copy.root;												//variable that represents a current_view copy of s2.root


	while (current_view != NULL) 												//while looking through the numbers of the tree
	{
		if (s_copy.isIn(current_view->element)) 									//if s2 and temp have an element
		{
			remove(current_view->element);										//element is removed
		}

		current_view = current_view->right;												//looks rightward of current element
	}
}

//TC: n^2, SC: n
int BSTSet::size()														//determines size of tree
{

	if (root == NULL) 	 												//if root doesnt exist return false
	{
		return 0;
	}


	sortTree();															//sort tree
	TNode* current_view = root;											//temp copy of tree

	int j = 0;															//counter
	while (current_view != NULL) {												//while looking through tree
		j++;															//counter goes up
		current_view = current_view->right;												//look rightwards of current element
	}
	return j;															//return counter
}

//TC:n^2, SC:n
int BSTSet::height()													//determines height of tree
{

	if (root == NULL) {													//if no tree
		return -1;														//return -1
	}


	int tree_height = 0;															//intialize the height of the BST


	for (int j = findMinVal(root); j <= findMaxVal(root); j++) 		//looking through all values of tree
		{
		if (tree_height < depth(j)) 												//if looking at a new, greater depth
		{
			tree_height = depth(j);												//height is now equal to depth
		}
	}
	return tree_height;															//return height
}

//TC: n, SC: n
int BSTSet::depth(int i)
{
	bool a;																		//for returning
	TNode* current_view = root;													//initialize var.s
	int count = 0;																//counter for depth


	while (current_view != NULL) 												//while looking through the tree
	{
		if (i < current_view->element)											//if depth is less then the current element
		{
			current_view = current_view->left;											//look leftwards
		}

		else if (i > current_view->element)										//if depth is greater then the current element
		{
			current_view = current_view->right;											//look rightwards
		}

		else															//else
		{
			return count;													//return count
		}
		count++;															//count increment
	}
	a=0;
	return a;															//return false;
}

//TC:n, SC:n
void BSTSet::printNonRec()
{
	MyStack stack = MyStack();											//Creates a MyStack function
	TNode* current_view = root;													//current_vieworary copy of tree

	while (current_view != NULL || !stack.isEmpty()) 							//while the stack isnt empty and the tree isnt empty
	{
		if (current_view != NULL) 												//if tree element is valid
		{
			stack.push(current_view);											//push element to stack
			current_view = current_view->left;											//look leftwards in tree
		}
		if(current_view == NULL) 												//If current node is NULL
			{
			current_view = stack.pop();											//pop the stack
			cout << current_view->element << ",";								//prints for eg. "2,"
			current_view = current_view->right;											//look rightwards
		}
	}
}

// Do not modify following provided methods

void BSTSet::printBSTSet()
{
    if (root == NULL)
        std::cout << "";
    else {
        printBSTSet(root);
    }
}

void BSTSet::printBSTSet(TNode* t)
{
    if (t != NULL) {
        printBSTSet(t->left);
        std::cout << t->element << ",";
        printBSTSet(t->right);
    }
}
