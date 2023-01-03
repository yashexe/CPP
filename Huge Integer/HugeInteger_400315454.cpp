#inc#include "HugeInteger.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>

HugeInteger::HugeInteger(const std::string& val) {

	int i = 0;
	if ( val[0] == '-' ) 											//if the number is negative(first character is "-"), character
	{
		positive = false;										//gets skipped. We only need to check if magnitude is big
		i = 1;
	}
	else
	{
		positive = true;
	}


	while( val[i] != '\0' )
	{												// checks every character of string before null character

		int num = val[i] - '0';									//Number is converted into ASCII

		if( num > 9 || num < 0 )									//if the number is normal (0,1,2,3,4,5,6,7,8,9), it is skipped
		{
			throw std:: invalid_argument( "INVALID NUMBER" );				//if not, invalid argument is thrown
		}

		else
		{
			HugeInt.push_back( num );
		}

		i++;
	}


	if( val.length() == 0 )										//if no number is entered, invalid argument is thrown
	{
		throw std:: invalid_argument( "Invalid length" );
	}

}

HugeInteger::HugeInteger(int n) {

	int num = 0;
	srand( time(0) );											//time zero occurs after every repitition of the code,
													//srand will chose a random number at the start of each repitition
	positive = rand() % 2;										//positive or negative

	HugeInt.push_back(( (rand()%9) + 1 ));								//remainder of a number modulo 9. 1 is added to that number
													//ensures number is less than 2^63, and "+ 1" accounts for "9" and "0", latter we dont want
	for( int i = 1 ; i < n ; i++ )										//for loop of the amount of digits left to add
	{
		num = rand() % 10									//remainder of a number modulo 10
													//numbers after the first digit can be anything btwn 0-9
		HugeInt.push_back( num );
	}

	if (n < 1)												//if number of digits is invalid
	{
		throw std:: invalid_argument( "chose a valid amount of digits!" );	//invalid argurment is thrown
	}
}

HugeInteger HugeInteger::add(const HugeInteger& h) {//time complexity: n

	std::vector<int>num1 = HugeInt;
	std::vector<int>num2 = h.HugeInt;								//vector numbers to be added

	int len1 = HugeInt.size() - 1; 									//takes out null character
	int len2 = h.HugeInt.size() - 1;									//^^
	int sum = 0;											//sum of all numbers including carry
	int result = 0;
	int carry = 0;											//for numbers that create two digit numbers
	int int1, int2;

	std::string str_sum_result = "";									//number turned back into string
	std::string end = ""; 										//string (final result)

	if( (this->positive == false) && (h.positive == false) )						//if both numbers are negative
	{
		end += '-';										//minus sign added
	}
	else if( (this->positive == false) && (h.positive == true) )						//if only one number is negative
	{
		HugeInteger first_num = *this;								//object of HugeInteger assigned

		first_num.positive = true;								//positive

		HugeInteger first_num_neg = first_num.subtract( h );					//difference object

		if( first_num.compareTo(h) == 1 )								//makes sure object is bigger than h
		{
			first_num_neg.positive = false;							//number is negative
		}
		else if( first_num.compareTo(h) == -1 || first_num.compareTo(h) == 0 ) 			//if object isnt bigge than h, number is positive
		{
			first_num_neg.positive = true;
		}

		return first_num_neg;
	}
	else if(this-> positive == true && h.positive == false)						//if only one number is negative
	{
		HugeInteger second_num = h;								//object of HugeInteger
		second_num.positive = true;								//assigned positive

		HugeInteger second_num_neg = this-> subtract( second_num );				//difference object

		return second_num_neg;
	}

	do{
		int1 = 0;											//temporary variables set to 0
		int2 = 0;

		if (len1 >= 0) 										//if the number has a valid amount of digits
		{
			int1 = num1[ len1 ];								//temporary number becomes (digit corresponding to value of length) - 0
			len1--;										//length is decreased to add values of higher significance
		}
		if (len2 >= 0)										//if the number has a valid amount of digits
		{
			int2 = num2[ len2 ];								//temporary number becomes (digit corresponding to value of length) -0
			len2--;										//length is decreased to add values of higher significance
		}


		sum = int1+int2+carry;									//total amount of digits
		result = sum%10;									//value before carry place
		carry = sum/10;										//value of carry, to be added in next loop

		str_sum_result += std::to_string( result );							//characters converted to string

	}while( len1 >= 0 || len2 >= 0 );									//looped until procress of addition through length of digits is done


	if( carry > 0 )											//if addition results in a carry to the front of the number
	{
		str_sum_result += std::to_string( carry );							//carry is added to string number
	}

	int i = str_sum_result.size() - 1;									//position is at least significant digit."-1" accounts for null character

	while( i >= 0 )
	{
		end += str_sum_result[ i ];								//sum of huge intergers

		i--;
	}

	return HugeInteger( end );									//return sum
}

HugeInteger HugeInteger::subtract(const HugeInteger& h) { //time complexity: n


	std::vector<int>num1 = HugeInt;									//vector numbers to find the difference of
	std::vector<int>num2 = h.HugeInt;


	std::string str_diff_result = "";									//string used in process of finding result
	std::string end = "";										//result to be returned
	int len1 = HugeInt.size() - 1;									//length of both numbers
	int len2 = h.HugeInt.size() - 1;


	if ( ( num1 == num2 ) && ( this->positive == h.positive ) )						//if numbers are the same and have the same sign
	{
		return HugeInteger( "0" );								//returns 0			eg. a = b = -3;		a-b = (-3) - (-3) = -3+3 = 0
	}

	if ( (this->positive == false) && (h.positive == false) )						//if both numbers are negative
	{

		if ( this->compareTo(h) == 1 )								//if num1 > num2
		{
			std::vector<int>num1_temp = num1;						//temporary vector number that is the same as HugeInteger "num1"
			int len1_temp = len1;								//temporary variable that is the length of HugeInteger "num1"
			num1 = num2;									//num1 becomes same as num2
			len1 = len2;
			num2 = num1_temp;								//num2 becomes num1
			len2 = len1_temp;
		}											//overall the numbers are reversed and since HugeInteger num1 is originally bigger than h
													//result of subtraction will be positive
		else if ( this->compareTo(h) == -1 )							// if num1 < num2
		{
			end += '-';									//result is a negative number
		}
	}

	else if ( (this->positive == false) && (h.positive == true) )						// if num1 is negative and num2 is positive
	{

		positive = true;										// num1 is treated as positive

		HugeInteger negative_result = this->add(h);						// numbers are added (subtracted) together and outcome is negative

		negative_result.positive = false;								// in the end the sign is added to the front of the number
		return negative_result;
	}

	else if (this->positive == true && h.positive == false)						 //if num1 is positive and num2 is negative
	{

		HugeInteger num2_temp = h;								 //temporary number for num2

		num2_temp.positive = true;								//tempnum2 set positive

		HugeInteger negative_result = this->add(num2_temp);					//result calculated

		negative_result.positive = true;								//set positive
		return negative_result;
	}

	else if (this->positive == true && h.positive == true)						// both positive
	{

		if (this->compareTo(h) == -1)								//if num1<num2
		{
			std::vector<int>num1_temp = num1;						//temporary vector number for num1
			int len1_temp = len1;								//tempoary var. given the length of 1
			num1 = num2;									//following lines switch num 1 and num2, adding a negative sign at the end
			len1 = len2;
			num2 = num1_temp;
			len2 = len1_temp;
			end += '-';
		}
	}

	while (len1 >= 0 || len2 >= 0)									//while the process of subtraction is still underway
	{

		int digit_1 = 0;
		int digit_2 = 0;
		int result = 0;


		if(len1 >= 0)										//if len1 represents a 1+ digit nunber
		{
			digit_1 = num1[len1];								//length is reduced
			len1--;
		}

		if(len2 >= 0)										//if len2 represents a 1+ digit number
		{
			digit_2 = num2[len2];								//length is reduced
			len2--;
		}

		if(digit_2 > digit_1)									//if second digit is bigger than first
		{
			result = (digit_1 + 10) - digit_2;							//result is a number with a carry subtracted by the second digit
			int j = len1;

			while (num1[j] == 0)								//while there is no valid number to subtract
			{
				j--;									//decrease j counter
			}

			num1[j]--;									//number at j is decresed

			while (num1[j + 1] == 0)								//if the number one digit up is 0
			{
				num1[j + 1] = 9;								//9 is placed at that spot;
				j++;									//eg. a=100, b=1; a-b = 100-1 = 99
			}
		}

		else
		{
			result = digit_1 - digit_2;								//if number being subtracted from is "reverse carried", then normal subtraction
		}


		str_diff_result += std::to_string(result);							//string of the result is updated
	}

	for (int i = str_diff_result.length() - 1; i >= 0; i--) 							//iterates through the digits of the result started from the most significant digit
	{
		end += str_diff_result[i];									//copied into "end"
	}


	if (end[0] == '-')											//if negative number
	{
		end.erase(0, 1);										//removes negative sign
		end.erase(0, end.find_first_not_of('0'));							//removes 0s until a number is not 0
		end.insert(0,1,'-');									//adds negative sign back into front
	}
	else if (end[0] == '0')										//if positive number
	{
		end.erase(0, end.find_first_not_of('0'));							//removes all 0s until a number is not 0
	}

	return HugeInteger(end);									//return difference
}

HugeInteger HugeInteger::multiply(const HugeInteger& h) { //time complexity: n^2


	std::vector<int>num1 = HugeInt;									//vector numbers to find the difference of
	std::vector<int>num2 = h.HugeInt;


	int len1 = HugeInt.size();										//length of said vector numbers
	int len2 = h.HugeInt.size();


	std::vector<int>product(len1 + len2, 0);								//vector that is size of maximum # of digits that two specific numbers can be
													//eg. a = 100, b = 100
													//both are 3 digit #s; 100*100 = 10000..... a 5 digit #, 999*999 = 998001.... a 6 digit number
	int num1_i = 0;											//intializing variables that will iterate through multiplier/multiplicand
	int num2_i = 0;


	std::string end = "";										//end result in string

	if (len1 == 0 || len2 == 0 || num1[0] == 0 || num2[0] == 0)	//a*0 = 0; 0*b = 0
	{
		return HugeInteger("0");
	}


	for (int i = len1 - 1; i >= 0; i--) 									//iterate through multiplier
	{

		num2_i = 0;
		int carry = 0;

		int digit_1 = num1[i];									 //digit becomes ith digit of num1


		for (int j = len2 - 1; j >= 0; j--) 								//iterate through multiplicand
		{

			int digit_2 = num2[j];								//digit becomes jth digit of num2

			int sum_of_digits = digit_1*digit_2 + product[num1_i + num2_i] + carry;		 //performs multiplication and adds carry if neccessary

			product[num1_i + num2_i] = sum_of_digits % 10;	//finds remainder

			carry = sum_of_digits/10;	//finds carry for next iteration

			//Increment num2_i
			num2_i++;									//increment
		}


		if (carry > 0)										//if there is a carry
		{
			product[num1_i + num2_i] += carry;						//added to sum
	    }


		num1_i++;										//increment
	}


	if ((this->positive == true && h.positive == false) || (this->positive == false && h.positive == true) )	// if one of the values are negative
	{
		end += '-';										//result is negative
	}


	for (int i = product.size() - 1; i >= 0; i--)								//iterates through product
	{
		end += std::to_string(product[i]);								//copied into "end"

	}


	if (end[0] == '-')											//if negative
	{
		end.erase( 0,1 );										//negative sign removed
		end.erase( 0, end.find_first_not_of('0') );							//zeros before first non-zero value removed
		end.insert( 0,1,'-' );									//negative sign added
	}
	else if ( end[0] == '0' )										//if positive
	{
		end.erase( 0, end.find_first_not_of('0') );							//zeros before first non-zero value removed
	}

	return HugeInteger(end);									//return product
}

int HugeInteger::compareTo(const HugeInteger& h) { //time complexity: n

	std::vector<int>num1 = HugeInt;									//vector numbers to be compared
	std::vector<int>num2 = h.HugeInt;


	int len1 = HugeInt.size();										//size of vectors
	int len2 = h.HugeInt.size();


	int check = 0;


	if (this->positive == true && h.positive == false) 							//if num1 positive and num2 negative
	{
		return 1;										//num1>num2
	}

	else if(this->positive == false && h.positive == true) 						//if num1 negative and num2 positive
	{
		return -1;										//num2>num1
	}


	if (this->positive == false && h.positive == false) 							//if both negative
	{
		std::vector<int>num1_temp = num1;							//temporary vector for num1
		int len1_temp = len1;									//temporary length var. for num1
		num1 = num2;										//switches values for num1 and num2
		len1 = len2;
		num2 = num1_temp;
		len2 = len1_temp;
	}


	if (len2 > len1) 											//if num2 has more digits than num1
	{
		return -1;										//num2>num1
	}

	else if(len1 > len2) 										//if num1 has more digits than num2
	{
		return 1;										//num1>num2

	}
	else if (len1 == len2)  										//if they have the same number of digits
	{
		for(int i = 0; i < len1; i++) 									//iterate through num1
		{
			if ((num1[i]) > (num2[i])) 								//if the digit in the ith position of num1 is greater than the ith position of num2
			{
				check = 1;								//check = 1, representing "true"
				return 1;
			}
			else if ((num2[i]) > (num1[i])) 							//if the digit in the ith position of num2 is greater than the ith position of num1
			{
				check = 1;								//check = 1
				return -1;
			}
		}
		if (check == 0) 										//if check has not changed at all
		{
			return 0;									//they are the same value and sign
		}
	}


	return 0;
}

std::string HugeInteger::toString() {									//n

	std::string end = "";										//end result of a operation

	if( positive == false )
	{												//if a number is negative
		end+= '-' ;										//"-" added to number
	}

	for(auto i = HugeInt.begin(); i != HugeInt.end();i++){						//automatically iterates through HugeInt...
		end+= std::to_string(*i);									//...converting digits to string... 123 => "123"
	}


	return end;											//return result
}

