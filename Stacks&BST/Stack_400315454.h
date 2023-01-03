#ifndef Stack_H_
#define Stack_H_

#include "TNode.h"
#include "Stack.h"
#include "SNode.h"
#include <vector>
#include <stddef.h>

class MyStack
{
private:
    SNode* root = NULL;
public:
    MyStack();
    bool isEmpty();
    void push(TNode* v);
    TNode* pop();
};
#endif /* MyStack_H_ */
