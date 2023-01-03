#include "HashTableQuad.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

bool HashTableQuad::prime(int n)
{
    if (n == 0) {												//zero is a prime number, false should be returned
        return false;
    }
    if(n == 1)													//one is prime, return false
    {
    	return false;											//return false
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

HashTableQuad::HashTableQuad(int maxNum, double load)
{
																//	Initializing var.s
	size = maxNum / load;
    double size_confirm = maxNum / load;						//same as size
    															//	rounds up the size var.
    if (size_confirm > size)
    {
    	size++;
    }
    while(!prime(size))											//If the size is not a prime number, increment until it is
    {
        size++;
    }

    vector<int> temp(size);										//temp. vector var. of size "size". represents table
    table = temp;
    maxKey = size * load;										//maximum key value is the size multiplied by the load -> size * maxNum/size => maxKey = maxNum
    maxLoad = load;
    keys = 0;
}
//	TC: n, SC: 1

void HashTableQuad::insert(int n)
{
	//	Initialized variable
    int probe_squared = 1;										//i^2 value that allows for probing "quadratically"

    if (!isIn(n)) 												//if n is not in table
    	{
    	int position = n % size;										//linearly probe to look for spot for n

        if (table[position] == NULL) 								//if empty place found,
        {
        	table[position] = n;										//put n there
            keys++;												//incr. num of spots taken
        }
        else
        {
            while (table[position] != NULL) 							//if linear probe doesnt work
            {
                position = (n % size + (probe_squared * probe_squared)) % size;			//quadratic probe time

                if (probe_squared == size) 						//if not found
                {
                    return;										//return
                }
                probe_squared++;								//increment the value to be squared
            }
            table[position] = n;										//if or when an empty space is found, make that position hold n
            keys++;												//incr. keys
        }

        if (maxKey < keys) {									// if there isnt space
        	rehash();											//table is rehashed to allocate more space, probing process is repeated
        }
    }
}
//TC: n^2, SC: 1

void HashTableQuad::rehash()
{
    size = 2*size;												//size doubled
    maxKey = maxLoad * size;									//recalc max key value

    std::vector<int> newTable = table;							//copy table

    while (!prime(size))										//makes size a prime #
    {
        size+=1;												//size incr. by one each time
    }

    keys = 0;													//reset keys
    table.resize(0);											//reset table to 0
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

bool HashTableQuad::isIn(int n)
{

    int probe_squared = 1;										//for probing eqn. size + i^2
    int check_isIn = n % size;									//initialize var.s

    while (table[check_isIn] != NULL) 							//while looking through not empty places
    {
        if (table[check_isIn] == n) 							//if found return true
        {

        	return true;
        }
        else
        {
            check_isIn = (n % size+(probe_squared*probe_squared) ) % size;	// checks through table "quadratically"

            if (probe_squared==size) 										//if all places have been checked(at this point n is still not found), return false
            {
            	return false;
            }
            probe_squared+=1;												//next iteration
        }
    }
    return false;															//return false
}
//TC: n, SC: 1

void HashTableQuad::printKeys()
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

void HashTableQuad::printKeysAndIndexes()
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

int HashTableQuad::getNumKeys()
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

int HashTableQuad::getTableSize()
{
    return size;												//return size
}
//TC/SC: 1

double HashTableQuad::getMaxLoadFactor()
{
    return maxLoad;												//return maximum load
}
//TC/SC: 1
int HashTableQuad::insertCount(int n)
{
    int probe_count = 0;
    int probe_squared = 1;
    if (!isIn(n))												//if n not in table
    {
        int position = n % size;										//linear probing to  find space
        if (table[position] == NULL)									//if found
        {
            table[position] = n;										//n placed there
            keys+=1;											//num spots taken incr.
            probe_count+=1;										//probe count incr.
        }
        else
        {
            while (table[position] != NULL)							//if lin prob doesnt work
            {
                position = (n % size + (probe_squared * probe_squared)) % size;// quad. probing time
                probe_count++;											//incr. probe count
                if (probe_squared == size)								//if no empty spaces found
                {
                    return 0;											//return 0
                }
                probe_squared+=1;										//increment value to be squared
            }
            table[position] = n;												//if or when a empty space is found, put n there
            keys++;														//incr. num spots taken
            probe_count+=1;												//incr probe count
        }
        if (maxKey < keys)												//if it exceeds num of keys accessible
        {
            rehash();													//rehash table to allocate space
        }
    }
    return probe_count;													//return probe count
}
//TC: n^2, SC: 1

std::vector<double> HashTableQuad::simProbeSuccess() {
	//	Intialized variables
	int maximum_size = 100000;											//initialize var.s ... max size
    vector<double> result(9);											//vector variable that holds average probe
    double sum, size_copy = 100000;										//sum and copy of max size
    int List[100000];													//list
    int count = 0;
    for (int i = 0; i < maximum_size; i++) 								//random number list of 100 000
    {
    	int random_number;												//value of randnum
        bool isIn = true;
        while (isIn) {
            isIn = false;
            random_number = (rand() * rand());							//random number

            for (int j = 0; j < i; j++) {								//dup check so numbers arent repeated
                if (random_number == List[j]) {
                    isIn = true;										//confirmd to be true
                    break;												//break loop
                }
            }
        }
        List[i] = random_number;										//put num in list
    }

    for (double load_factor = 0.1; load_factor < 0.99; load_factor += 0.1) //for loop for the average probe value of each iteration
    {
    	sum = 0;														//sum reset for each probe

        for (int i = 0; i < 100; i++)									//100 trials of probing
        {
            HashTableQuad testHash = HashTableQuad(maximum_size, load_factor);//new hash table with its own load vals

            for (int j = 0; j < size_copy; j++)							//probe loop until success (its assured cuz the for loop spans the size of the table
            {
                sum += (testHash.insertCount(List[j])) / (size_copy);	//insert func repeated and sum incremented each time
            }
        }
        result[count] = sum / 100;										//average probing
        count+=1;														//increment count
    }
    return result;
}
