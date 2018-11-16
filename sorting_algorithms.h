/*******************************************************************************

*******************************************************************************/
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <chrono>
#define LEFT(i) 2*(i)+1//for the left child

using namespace std;
//VerifyOrder(const vector<Comparable> &input, Comparator less_than) function can check if a input is in order or not
//it returns true if it is in order, returns false if not.
template <typename Comparable, typename Comparator>
bool VerifyOrder(const vector<Comparable> &input, Comparator less_than)
{
	unsigned int cter=0;
	for(unsigned int i=0;i<input.size()-1;++i)
	{
		int j=i+1;
		if(less_than(input[i],input[j]))
		{
			cter++;
		}
	}
	if(cter>=input.size()-1)
	{
		return true;
	}
	else
		return false;

}
/**
 * Return median of left, center, and right.
 * Order these and hide the pivot.
 */
template <typename Comparable, typename Comparator>
const Comparable & medianThree(vector<Comparable> & a, Comparable left, Comparable right,Comparator less_than)
{
	int center =(left+right)/2;

	if(less_than(a[center],a[left]))
		swap(a[left],a[center]);
	if(less_than(a[right],a[left]))
		swap(a[left],a[right]);
	if(less_than(a[right],a[center]))
		swap(a[center],a[right]);
	// Place pivot at position right - 1
	swap(a[center],a[right-1]);
	return a[right-1];
}
//Simple insertion sort
template <typename Comparable, typename Comparator>
void insertionSort(vector<Comparable> & a,Comparable left, Comparable right, Comparator less_than)
{
	for(int i=left;i<=right;i++)
	{
		Comparable temp =a[i];
		int j=i;
		while(j>0&&less_than(temp,a[j-1]))
		{
			a[j]=a[j-1];
			j--;
		}
		a[j]=temp;
	}
}
/**
* Internal quickSort method that makes recursive calls.
* Uses median-of-three partitioning and a cutoff of 10.
* a is an array of Comparable items.
* left is the left-most index of the subarray.
* right is the right-most index of the subarray.
*/
template <typename Comparable, typename Comparator>
void quickSort(vector<Comparable> &a,Comparable left, Comparable right ,Comparator less_than)
{
	if(left+10 <= right)
	{

		//a[left]become the smallest,a[right]become the largest.
		const Comparable &pivot= medianThree(a,left,right,less_than);
		//cout<<a[right]<<endl;


		//Begin partitioning
		int i=left;
		int j=right-1;
		
		for(;;)
		{
			//while(a[++i]<pivot){}
			while(less_than(a[++i],pivot)){}
			while(less_than(pivot,a[--j])){}
			//while(pivot<a[--j]){}
			if(i<j)
			{
				swap(a[i],a[j]);
			}	
			else
				break;
		}
		swap(a[i],a[right-1]);//restore pivot
		quickSort(a,left,i-1,less_than);//sort small elements
		quickSort(a,i+1,right,less_than);//sort large elements
	}
	else
	{
		//Do an insertion sort on the subarray
		//cout<<"i"<<endl;
		//cout<<left<<"  "<<right<<endl;
		insertionSort(a,left,right,less_than);

	}
}


template <typename Comparable, typename Comparator>
void quickSort(vector<Comparable> &a, Comparator less_than)
{
	/**
 	* quickSort algorithm (driver).
 	*/
	//Set a clock to record the time it takes for the function to finish.
	const auto begin = chrono::high_resolution_clock::now();
	Comparable left=0;
	Comparable right =a.size()-1;
	quickSort(a,left,right,less_than);
	//sort(a.begin(),a.end(),less_than);

	const auto end = chrono::high_resolution_clock::now();
	cout <<"quickSort: "<<"Runtime: "<< chrono::duration_cast<chrono::nanoseconds>(end-begin).count() << "ns" << endl;

}
/*
* @param int [ in ] i is the highest index value that should be accessed
in array
* @param int [ in ] n is the index of the array element to be percolated
down
*/
template <typename Comparable, typename Comparator>
void percDown(vector<Comparable> &a,Comparable i, Comparable n, Comparator less_than)
{
	int child;
	Comparable temp;
	for(temp=a[i];LEFT(i)<n;i=child)
	{
		child=LEFT(i);
		if(child !=n-1&&less_than(a[child],a[child+1]))
			++child;
		if(less_than(temp,a[child]))
			a[i]=a[child];
		else
			break;
	}
	a[i]=temp;
}


template <typename Comparable, typename Comparator>
void heapSort(vector<Comparable> &a, Comparator less_than)
{
	const auto begin = chrono::high_resolution_clock::now();
	for(int i=a.size()/2-1;i>=0;--i)
	{
		int k=a.size();
		// percolate down in a max heap stopping if we reach N -1
		percDown(a,i,k,less_than);
	}
	// A is now a heap
	// Now repeatedly swap the max element with the last element in the heap
	for(int j=a.size()-1;j>0;--j)
	{
		swap(a[0],a[j]);
		percDown(a,0,j,less_than);
	}


	const auto end = chrono::high_resolution_clock::now();
	cout <<"heapSort: "<<"Runtime: "<< chrono::duration_cast<chrono::nanoseconds>(end-begin).count() << "ns" << endl;
}
/**
* Internal method that merges two sorted halves of a subarray.
* a is an array of Comparable items.
* tmpArray is an array to place the merged result.
* leftPos is the left-most index of the subarray.
* rightPos is the index of the start of the second half.
* rightEnd is the right-most index of the subarray.
*/
template <typename Comparable, typename Comparator>
void merge(vector<Comparable> &a,vector<Comparable> &b,Comparable leftpos,Comparable rightpos,Comparable rightend, Comparator less_than)
{
	Comparable leftend=rightpos-1;
	Comparable temp_pos=leftpos;
	Comparable num_elements=rightend-leftpos+1;

	//main loop
	while(leftpos<=leftend&&rightpos<=rightend)
	{
		if(less_than(a[leftpos],a[rightpos]))
		{
			b[temp_pos++]=a[leftpos++];
		}
		else
		{
			b[temp_pos++]=a[rightpos++];
		}
	}
	while(leftpos<=leftend)//copy rest of first half
	{
		b[temp_pos++]=a[leftpos++];
	}
	while(rightpos<=rightend)//copy rest of right half
	{
		b[temp_pos++]=a[rightpos++];
	}
	//copy tmparray back
	for(int i=0;i<num_elements;++i,--rightend)
	{
		a[rightend]=b[rightend];
	}
}
/**
* Internal method that makes recursive calls.
* a is an array of Comparable items.
* tmpArray is an array to place the merged result.
* left is the left-most index of the subarray.
* right is the right-most index of the subarray.
*/
template <typename Comparable, typename Comparator>
void mergeSort(vector<Comparable> &a,vector<Comparable> &b,Comparable left,Comparable right, Comparator less_than)
{
	if(left<right)
	{
		Comparable center=(left+right)/2;
		mergeSort(a,b,left,center,less_than);
		mergeSort(a,b,center+1,right,less_than);
		merge(a,b,left,center+1,right,less_than);
	}
}
template <typename Comparable, typename Comparator>
void mergeSort(vector<Comparable> &a, Comparator less_than)
{
	/**
 * mergeSort algorithm (driver).
 */
	const auto begin = chrono::high_resolution_clock::now();
	vector<Comparable>b(a.size());
	Comparable c=a.size()-1;
	mergeSort(a,b,0,c,less_than);


	const auto end = chrono::high_resolution_clock::now();
	cout <<"mergeSort: "<<"Runtime: "<< chrono::duration_cast<chrono::nanoseconds>(end-begin).count() << "ns" << endl;
}
