#ifndef HASHTABLEQUAD_H_
#define HASHTABLEQUAD_H_

#include <vector>

class HashTableQuad
{
private:
	// must contain this private field
	std::vector<int> table;
	// define other private fields to store:
	//
	int size;
	int keys;
	int maxKey;
	// 3. the maximum load factor allowed
	double maxLoad;

public:
	// required constructor
	HashTableQuad(int maxNum, double load);

	// required methods
	bool prime(int n);														//prime fn.
	int insertCount(int n);													//insert fn.

	void insert(int n);
	bool isIn(int n);
	void printKeys();
	void printKeysAndIndexes();
	int getNumKeys();
	int getTableSize();
	double getMaxLoadFactor();
	static std::vector<double> simProbeSuccess();

	// used for testing
	std::vector<int> getTable() {
		return table;
	};

private:
	// required methods
	void rehash();
};

#endif /* HASHTABLEQUAD_H_ */
