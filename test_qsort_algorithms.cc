/*******************************************************************************


*******************************************************************************/
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <chrono>
#include <sstream>
#include "qsort_algorithm.h"

using namespace std;
/** GenerateRV(vector<int>&a, size_t size_of_vector) - generates a vector with all random numbers
	 * take a empty vector and its size as input
	 * after this function finished running, the vector is fill by all random numbers
	 */
void GenerateRV(vector<int>&a, size_t size_of_vector)
{
	a.clear();
	srand(time(0));
	for(size_t i=0; i<size_of_vector;++i)
	{
		a.push_back(rand());
	}
}
/** GenerateSV(vector<int>&a, size_t size_of_vector) - generates a vector with all sorted numbers
	 * take a empty vector and its size as input
	 * after this function finished running, the vector is fill by all sorted numbers
	 */
void GenerateSV(vector<int>&a, size_t size_of_vector)
{
	a.clear();
	for(size_t i=1;i<=size_of_vector;++i)
	{
		a.push_back(i);
	}
}


int main(int argc, char **argv)
{
	if(argc !=4)
	{
		cout<<"Usage: "<< argv[0]<<"	<input_type>	<input_size>	<comparison_type>"<<endl;
		return 0;
	}
	const string input_type(argv[1]);
	const string s_input_size(argv[2]);
	const string comparison_type(argv[3]);
	//Convert string to int type
	stringstream myInput(s_input_size);
	int input_size;
	myInput>>input_size;
	cout<<"Running sorting algorithms: "<<input_type<<", "<<s_input_size<<", "<<comparison_type<<endl;
	if(input_type=="random")
	{
		vector<int>input_vector;
		GenerateRV(input_vector,input_size);
		vector<int>input_vector1=input_vector;
		vector<int>input_vector2=input_vector;
		if(comparison_type=="greater")
		{
			//create a empty vector, fill it with input_type numbers.(input_type can be either random or sorted).
			//test the sorting algorithms with same vector, so we create two more new vectors copy everything the first vector has.
			//test the sorting algorithms with comparison type.
			quickSort_medianThree(input_vector,greater<int>());
			cout<<"Verified: "<<VerifyOrder(input_vector,greater<int>())<<endl;
			quickSort_middle(input_vector1,greater<int>());
			cout<<"Verified: "<<VerifyOrder(input_vector1,greater<int>())<<endl;
			quickSort_first(input_vector2,greater<int>());
			cout<<"Verified: "<<VerifyOrder(input_vector2,greater<int>())<<endl;
		}
		else if(comparison_type=="less")
		{
			quickSort_medianThree(input_vector,less<int>());
			cout<<"Verified: "<<VerifyOrder(input_vector,less<int>())<<endl;
			quickSort_middle(input_vector1,less<int>());
			cout<<"Verified: "<<VerifyOrder(input_vector1,less<int>())<<endl;
			quickSort_first(input_vector2,less<int>());
			cout<<"Verified: "<<VerifyOrder(input_vector2,less<int>())<<endl;

		}
		else
		{
			cout<<"Uknown comparison_type "<<comparison_type<<"(User should provide grater or less)"<<endl;
		}
	}
	else if(input_type=="sorted")
	{
		//create a empty vector, fill it with input_type numbers.(input_type can be either random or sorted).
		//test the sorting algorithms with same vector, so we create two more new vectors copy everything the first vector has.
		//test the sorting algorithms with comparison type.
		vector<int>input_vector;
		GenerateSV(input_vector,input_size);
		vector<int>input_vector1=input_vector;
		vector<int>input_vector2=input_vector;
		if(comparison_type=="greater")
		{
			quickSort_medianThree(input_vector,greater<int>());
			cout<<"Verified: "<<VerifyOrder(input_vector,greater<int>())<<endl;
			quickSort_middle(input_vector1,greater<int>());
			cout<<"Verified: "<<VerifyOrder(input_vector1,greater<int>())<<endl;
			quickSort_first(input_vector2,greater<int>());
			cout<<"Verified: "<<VerifyOrder(input_vector2,greater<int>())<<endl;
		}
		else if(comparison_type=="less")
		{
			quickSort_medianThree(input_vector,less<int>());
			cout<<"Verified: "<<VerifyOrder(input_vector,less<int>())<<endl;
			quickSort_middle(input_vector1,less<int>());
			cout<<"Verified: "<<VerifyOrder(input_vector1,less<int>())<<endl;
			quickSort_first(input_vector2,less<int>());
			cout<<"Verified: "<<VerifyOrder(input_vector2,less<int>())<<endl;
		}
		else
		{
			cout<<"Uknown comparison_type "<<comparison_type<<"(User should provide grater or less)"<<endl;
		}
	}
	else
	{
		cout<<"Uknown input_type "<<input_type<<"(User should provide random or sorted"<<endl;
	}
	return 0;

}