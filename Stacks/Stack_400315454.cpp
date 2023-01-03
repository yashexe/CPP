#include "Stack.h"
#include <iostream>
#include <vector>
using namespace std;

//TC:1, SC:1
MyStack::MyStack()
{
    root = NULL;												//empty tree created for the purpose of adding to a stack
}

//TC:1, SC:1
bool MyStack::isEmpty()
{
	return(root == NULL);										//if root is actually equal to NULL, 1(true) is returned. Otherwise, 0(false)
}

//TC:1, SC:1
void MyStack::push(TNode* v)
{
    root = new SNode(v, root);									//creates a new node based on value V from tree
}

//TC:1, SC:1
TNode* MyStack::pop()
{

    if (isEmpty()) {											//if the stack is empty
        throw std::underflow_error("The stack's empty!");		//throws undeflow error indicating that the stack is empty
    }

    else {
        SNode* current_view = root;								//looks at root of tree
        TNode* previous_view = root->element;					//looks at val of root
        root = root->next;										//looks at next node of tree
        delete current_view;									//deleting current(NOW previous) view
        return previous_view;									//returns node that was being looked at
    }
}
