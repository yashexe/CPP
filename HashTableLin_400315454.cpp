#include "HashTableLin.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

bool HashTableLin::prime(int n)
{
    if (n == 0) {												//zero is a prime number, false should be returned
        return false;
    }
    if(n == 1)													//one is prime, return false
    {
    	return false;
    }
    															//next set of numbers start at 2 since 0 and 1 are accounted for
    for (int prime_count = 2; prime_count <n; prime_count+= 1) {//for loop iterating until right below value of n
        if (n % prime_count == 0) {								//if remainder = 0
            return false;										//prime #, so return false
        }
    }
    return true;												//not prime number !
}
//	TC: n, SC: 1

HashTableLin::HashTableLin(int maxNum, double load)
{
																//	Initializing var.s
	size = maxNum / load;
    double size_confirm = maxNum / load;
    															//	rounds up the size var.
    if (size_confirm > size)
    {
    	size++;
    }
    while(!prime(size))											//If the size is not a prime number, increment until it is
    {
        size++;
    }

    vector<int> temporary(size);										//temp. vector var. of size "size". represents table
    table = temporary;
    maxKey = size * load;										//maximum key value is the size multiplied by the load -> size * maxNum/size => maxKey = maxNum
    maxLoad = load;
    keys = 0;
}
//	TC: n, SC: 1

void HashTableLin::insert(int n) {

    if (!isIn(n)) 												//if number n is not in the table, it is added
    {
    	keys++;
        if (maxKey < keys)  									// if n cannot be inserted normally, it is rehashed
        {
        	rehash();
        }
        int position = n % size;										//position of n
        if (table[position] == NULL) 								//if it can be inserted properly
        {
        	table[position] = n;										//n takes the place of NULL list element
        }
        else
        {
        	while (table[position] != NULL)  						//lin probing is used to find a place for n to fit in.
        	{
        		position = (position + 1) % size;							//checks if the NEXT SPOT is empty
            }
            table[position] = n;										//when one is found, n is placed there
        }
    }
}
//	TC: n^2, SC: 1

void HashTableLin::rehash()
{
    size = 2*size;												//size doubled
    maxKey = maxLoad * size;									//recalc max key value

    std::vector<int> newTable = table;							//copy table

    while (!prime(size))										//makes size a prime #
    {
        size++;
    }

    keys = 0;													//reset keys
    table.resize(0);											//reset table
    table.resize(size);											// reset table to new size


    for (int i = 0; i < newTable.size(); i++) 					//for loop that added back the elements
    {
    	if (newTable[i] != NULL) 								//if spot isnt free
    	{
    		insert(newTable[i]);								//insert element
        }

    }
}
//TC: n^3, SC: 1

bool HashTableLin::isIn(int n) {

    int check_isIn = n % size;

    while (table[check_isIn] != NULL) 							//iterates through the hash table
    {
    	if (table[check_isIn] == n) 							//check if in same pos. as check value
    	{
    		return true;
        }
        else 													//lin probing
        {
            check_isIn = (check_isIn + 1) % size;
            													//checks if every pos. has been checked. n is not in hash table
            if (check_isIn == n % size)
            {
                return false;
            }
        }
    }
    return false;
}
//TC: n, SC: 1

void HashTableLin::printKeys()
{

	for (int i = 0; i < size; i++)								//for the size of the table
    {
        if (table[i] != NULL) 									//if pos. includes an element
        {
        	printf("%d, ", table[i]);							// print for example "3, "
        }
    }
}
//TC: n, SC: 1

void HashTableLin::printKeysAndIndexes()
{
    for (int i = 0; i < size; i++)  							//for size of the table
    {
    	if (table[i] != NULL) 									//if pos. includes an element
    	{
    		printf("%d %d, ", i, table[i]);						//print for example "0 3, " \n "1 7, "
        }
    }
}
//TC: n, SC: 1

int HashTableLin::getNumKeys()
{
    int count = 0;												//count var. meant to return the number of keys

    for (int i = 0; i < size; i++) 								//for loop iterating through the size of the table
    {
    	if (table[i] != NULL)									//if position has a valid number in it
    	{
    		count++;											//incr count. This function basically counts the number of numbers in the hashtable
        }
    }
    return count;												//return count
}
//	TC: n, SC: 1

int HashTableLin::getTableSize()
{
    return size;												//return size
}
//TC/SC: 1

double HashTableLin::getMaxLoadFactor()
{
    return maxLoad;												//return maximum load
}
//TC/SC: 1
int HashTableLin::insertCount(int n) {
    int prober = 0;												//returned value represents # of times element is found/put in table

    if (!isIn(n)) 												//if n isnt in hash table
    {
        keys++;													//increase keys by 1 for the eventual addition of n
        if (maxKey < keys) 										//if num of keys is greater than the max written down
        {
            rehash();											//rehash to fix/compensate for that^
        }
        int position = n % size;										//position is the remainder of n modulo size
        if (table[position] == NULL) 								//if that position is NULL
        {
            table[position] = n;										//place in that location
            prober++;											//incr. probe
        }
        else 													//if the position is already taken
        {
            while (table[position] != NULL) 							//while position bein glooked at is taken
            {
                position = (position + 1) % size;							//incr position
                prober++;										//incr. prober
            }

            table[position] = n;										//when empty pos. found put n there
            prober++;											//incr prober
        }
    }
    return prober;												//return prober
}
//	TC: n^2, SC: 1

std::vector<double> HashTableLin::simProbeSuccess() {
	int maximum_size = 100000;									//given max size
    vector<double> result(9);									//vector variable
    double sum;													//sum
    double size_copy = 100000;									//copy of maxSize
    int List[100000];											//////////////////////////////
    int count = 0;												//////////////////////////////

    for (int i = 0; i < maximum_size; i++) 						//for loop to 100 000
    {
        int random_number;										//rand num
        bool in_table = true;									//while in has table
        while(in_table)
        {
        	in_table = false;									//immediately set to false
            random_number = (rand()*rand());					//random number

            for (int j = 0; j < i; j++) 						//for loop to i value
            {
                if (random_number == List[j]) 					//if in the list
                {
                	in_table = true;							//bln set to true
                    break;										//end loop
                    											//this prevents duplicates
                }
            }
        }
        List[i] = random_number;								//specific element location given value "random_number
    }

    for (double load_factor = 0.1; load_factor < 0.99; load_factor += 0.1)	// average probe for specific load factor
    {

        sum = 0;												//sum reset to 0 for each iteration

        for (int i = 0; i < 100; i++) 							//100 trials of probe testing
        {
            HashTableLin Hash_tester = HashTableLin(maximum_size, load_factor);	//linear hash table  made with size and load factor
            for (int k = 0; k < size_copy; k++) 				//for loop to 100 000
            {
                sum += (Hash_tester.insertCount(List[k])) / (size_copy);		//sum added with count/size
            }
        }

        result[count]=sum/100;									//result to be returned is a list that = sum/100(avg probe) at position of count
        count++;
    }
    return result;
}


std::vector<double> HashTableLin::simProbeUnsuccess()
{
    // TODO, change following code after completing this function
    vector<double> result(9);
    return result;
}
