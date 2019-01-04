// Name:						Anthony Ho
// Class:						CSC 413
// Teacher:						Dr. Byrant Walley
// Project:						Project 1 Sorts
// Date:						3/22/2017 Originally Submitted
// New Date:					3/30/2017 Resubmit with errors corrected. 
// Purpose:						Purpose of this project is to learn the sorting algorithms taught in class. 
//								Purpose of the program is to let the user select a number from a list of options
//								that is presented to them. Option 1 and Option 2 lets the user pick a number and
//								write to a file using that number chosen respectively. Option 3, 4, 5, 6, 7 lets
//								the user sort the written file based on the option chosen and the sorts are
//								insertion,selection,merge,heap, and quick sort respectively. Option 8 will be to
//								use all the sorts at once. When a sort is selected, it will sort the data file
//								from option 2 and sort it and it will create a new file, named based on the sort 
//								chosen. Each sort when ran will be timed and the time will be outputted
//								with the file that is written after the sort has ran. 

// **I am assuming this is what you want when you wanted a comment header. First time taking your class. 

// Fixes I made to code based on the notes you gave me
// Minimal comment header, Minimal sort comments, no error checking, no run all sorts


//************************************************************************************
//I'm assuming I don't need to have repeat comments on each of the 5 sorting options
//I will put the comments for option 3 and assume it can be used for the next 4 options,
//aside from the sorting algorithm comments, I will still put those for each option.
//I'm assuming no need to repeat comments for the input output file operations and array creation 
//,retrieving first entry of text file, reading data into an array to be sorted 
// outputted again into "option choice"sort.txt, or the timer for each option.
//************************************************************************************

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <chrono>
#include <conio.h>
#include <iomanip>

using namespace std;
using namespace std::chrono; // Used for my timer

void display(); // Displays the descriptions/options for the user
void write(int x); // Writes my data file using the user's input

void opt3(); // Insertion Sort

void opt4(); // Selection Sort

void opt5(); // Merge Sort
void merge(int* arr, int, int, int);
void mergeSort(int* arr,int l, int r);

void opt6(); // Heap Sort
void maxHeapify(int* arr, int i, int n);
void buildmaxHeap(int* arr, int n);
void heapSort(int* arr, int n);


void opt7(); // Quick Sort
void quickSort(int* arr, int low, int high);
int partition(int* arr, int low, int high);


	
const int range = 10000; //used to generate random numbers
int max = 9999999; 
int heapsize; 

int main()
{
	int ans; // Holds the choice for which option
	int value = 0; //Holds the inputted value by the user
	int bop1 = 0; // value holder
	int bop2 = 0; // value holder 
	// bop1 and bop2 is used to make sure user has entered a number and written to a file, for the
	// 5 sorting options to work properly. 

	display(); // Display options/description

	// Code does not protect against entering anything other than an integer
	// If anything other than an integer is entered, infinite loop and or crash will occur. 


	while (1)
	{
		cout << endl << endl << "Which option will you choose: ";
		cin >> ans;

		while (cin.fail()) // My error checking, makes sure user inputs an integer
		{
			cout << "Error not a number, enter a number: ";
			cin.clear();
			cin.ignore(256, '\n');
			cin >> ans;
		}

		if (ans == 1) // Get user input
		{
			cout << "Enter a number only and that is greater than 0: " ;
			cin >> value;
			while (cin.fail()) // My error checking, makes sure user inputs an integer
			{
				cout << "Error not a number, enter a number: ";
				cin.clear();
				cin.ignore(256, '\n');
				cin >> value;
			}
			bop1 = 1; 
		}

		if (ans == 2) // Use user's input to write "Data.txt" with warning if no number chosen
		{
			if (bop1 == 1)
			{
				write(value);
				bop2 = 1;
			}

			else
				cout << "You have to choose option 1 before writing to a text file" << endl;
		}
		if (ans == 3) // Insertion sort call with warning if no number  chosen and or text file written 
		{
			if (bop1 == 1 && bop2 == 1)
				opt3();

			else
				cout << "You need to have chosen a number and or write to a text file after choosing a number" << endl;
		}
		if (ans == 4) // Selection sort call with warning if no number  chosen and or text file written 
		{
			if (bop1 == 1 && bop2 == 1)
			opt4();

			else
				cout << "You need to have chosen a number and or write to a text file after choosing a number" << endl;
		}
		if (ans == 5) // Merge sort call with warning if no number  chosen and or text file written 
		{
			if (bop1 == 1 && bop2 == 1)
			opt5();

			else
				cout << "You need to have chosen a number and or write to a text file after choosing a number" << endl;
		}
		if (ans == 6) // Heap sort call with warning if no number  chosen and or text file written 
		{
			if (bop1 == 1 && bop2 == 1)
			opt6();

			else
				cout << "You need to have chosen a number and or write to a text file after choosing a number" << endl;
		}
		if (ans == 7) // Quick sort call with warning if no number  chosen and or text file written 
		{
			if (bop1 == 1 && bop2 == 1)
				opt7();

			else
				cout << "You need to have chosen a number and or write to a text file after choosing a number" << endl;
		}

		if (ans == 8) // Run all sorts
		{

			if (bop1 == 1 && bop2 == 1)
			{
				opt3();
				opt4();
				opt5();
				opt6();
				opt7();
			}

		}


		if (ans < 0 || ans >= 9)// error checking, making sure user stays in range of options available
			cout << "Option number is invalid, Try again:  " << endl;

	}
	system("PAUSE");
	return 0;
}

void display() // Displays description and options
{

	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "Hello there! This is a sorting program that offers you multiple sorting options. " << endl;
	cout << "This program will generate a text file with a number of your choice and sort it based on your sorting choice and also time it. " << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << endl << endl;

	cout << "Your current options to choose from, select the option by entering it's option number given. " << endl;
	cout << "(For example you will type in the number 3 and press enter for option 3 or 1 for option 1)" << endl << endl;

	cout << "Option 1: Choose a number of your choice, must be a whole number. " << endl << endl;

	cout << "Option 2: Write to a data file, with your chosen number. Your number will generate and write " << endl;
	cout << "a certain amount of numbers randomly based on your choice to a text file unsorted. " << endl << endl ;

	cout << "Option 3: Sort the file using insertion sort. The numbers generated will be sorted with this method and written to another file. " << endl << endl;

	cout << "Option 4: Sort the file using selection sort. The numbers generated will be sorted with this method and written to another file. " << endl << endl;

	cout << "Option 5: Sort the file using merge sort. The numbers generated will be sorted with this method and written to another file. " << endl << endl;

	cout << "Option 6: Sort the file using heap sort. The numbers generated will be sorted with this method and written to another file. " << endl << endl;

	cout << "Option 7: Sort the file using quick sort. The numbers generated will be sorted with this method and written to another file. " << endl << endl;

	cout << "Option 8: Sort the file using all the sorts. " << endl << endl;

	cout << "In order to run program properly, you must select option 1 first and then option 2 afterwards for sorting options to work. " << endl;

}

void write(int x) // function to write a data file using rand to generate random numbers
{
	int value; // value holder
	value = x; // stores value of x 
	int *arr = new int[value]; // create array based on value's size

	ofstream outFile;// used for outputting

	outFile.open("Data.txt");// create data.txt

	outFile << value << endl;// size for data.txt

	for (int i = 0; i < value; i++) 
	{
		outFile << rand() % range << endl; // input rand numbers into data.txt
		arr[i] = rand() % range; // input rand numbers into array
	}

	cout << "Data has been outputted/written to Data.txt. "; // cout statement to show success of output

	outFile.close(); // close the file

}





void opt3() // Insertion Sort algorithm and function 
{
	cout << "insertion sort completed. " << endl; // Lets user know insertion sort has ran and completed

	ifstream inFile; //input function to open file

	inFile.open("Data.txt"); // open data.txt

	ofstream outFile; // output function to create file

	outFile.open("InsertionSorted.txt"); // create sort.txt

	


	string num; // value holder
	int data; // holder
	getline(inFile, num);//get first data entry
	data = atoi(num.c_str());// get value as an int

	int length = data + 1; //store the first num from file into length
	int *arr = new int[length];	 // create array using length's size
	int  j;// variable
	int key = 0; // variable
	

	for (int i = 0; i < length; i++) // put data.txt's data into array , changed 1 to 0
	{
		arr[i] = 0;
		inFile >> arr[i];
	
	}

	high_resolution_clock::time_point t1 = high_resolution_clock::now(); //timer starts now

	// Insertion Sort Algorithm
	for (int i = 1; i < length; i++) //loops though all numbers
	{

		key = arr[i];// select a value to be used as key
		j = i - 1; //for selecting position for value to be inserted

		//check if previous number is larger than value to be inserted
		while (j >= 0 && arr[j] > key)  
		{
			arr[j + 1] = arr[j]; 
			j = j - 1; 
		}
		//insert at position
		arr[j + 1] = key; 
	}

	high_resolution_clock::time_point t2 = high_resolution_clock::now(); // timer ends now

	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);//gets the time from calculations


	outFile << "Time: " << time_span.count() << " seconds. " << endl;// outputs the time from calculations

		for (int i = 1; i < length; i++)// output the sorted data into sort.txt
		{
			outFile << arr[i] << endl;
		}

		outFile.close(); //close operations
		inFile.close(); // close operations

		delete[] arr; //deleting for safety

}

void opt4() // Selection Sort algorithm and function 
{

	cout << "Selection sort completed. " << endl;

	ifstream inFile;

	inFile.open("Data.txt");

	ofstream outFile;

	outFile.open("SelectionSorted.txt");

	
	string num;
	int data;
	getline(inFile, num);
	data = atoi(num.c_str());

	int length = data + 1;
	int *arr = new int[length];	
	int  temp, min;

	

	for (int i = 1; i < length; i++)
	{
		arr[i] = 0;
		inFile >> arr[i];
	
	}



	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	// Selection Sort Algorithm
	for (int i = 0; i < length - 1; i++)
	{
		min = i; //holds lowest value, set current element as min

		for (int j = i + 1; j < length; j++)
		{
			if (arr[j] < arr[min])
				min = j;		// update/check min
		}
		if (min != i)
		{
			temp = arr[i]; // swap min element with current
			arr[i] = arr[min];
			arr[min] = temp;
		}
	}

	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

	outFile << "Time: " << time_span.count() << " seconds. " << endl;

	for (int i = 1; i < length; i++)
	{
		outFile << arr[i] << endl;
	}

	outFile.close();
	inFile.close();


	delete[] arr;



}


void merge(int *arr, int p, int q, int r) // part of opt5() and merge algorithm
{
	//variables for counting, etc
	int i, j, k;

	//values needed to create arrays, arrL and arrR
	int n1 = q - p + 1;
	int n2 = r - q;
	
	//created arrays or temp arrays , arrL left index, arrR right index
	int *arrL = new int[n1];
	int *arrR = new int[n2];

	//put data into the temp array
	for (i = 0; i < n1; i++)
	{
		arrL[i] = arr[p + i];
	}
	for (j = 0; j < n2; j++)
	{
		arrR[j] = arr[q + 1 + j];
	}
	
	//L[n1] = 9999999; // infinity
	//R[n2] = 9999999; // infinity

	//just setting variables to 0, iniitial index of first and second arrays for i and j respectively
	i = 0;
	j = 0; 

	//giving k the value of p, initial index of merged array
	k = p; 

	while (i < n1 && j < n2)
	{
		if (arrL[i] <= arrR[j])
		{
			arr[k] = arrL[i];
			i++;
		}
		else
		{
			arr[k] = arrR[j];
			j++;
		}
		k++;
	}

	//copy reminainig elements of arrL
	while (i < n1)
	{
		arr[k] = arrL[i];
		i++;
		k++;
	}
	//copy remaining elements of arrR
	while (j < n2) 
	{
		arr[k] = arrR[j];
		j++;
		k++;
	}

	//delete for safety measures
	delete[] arrL;
	delete[] arrR;
}




void mergeSort(int* arr,int p,int r) // part of opt5() and mergeSort algorithm
{


	if (p < r)//check base case
	{ 
		int q = (p + r) / 2; //divide

		mergeSort(arr, p, q); // conquer, sort
		mergeSort(arr, q + 1, r); // conquer, sort
		merge(arr, p, q, r); // combine

		//referenced to divide and conquer technique
	}


}

void opt5() // Merge Sort function 
{

	cout << "Merge sort completed. " << endl;

	ifstream inFile;

	inFile.open("Data.txt");

	ofstream outFile;

	outFile.open("MergeSorted.txt");


	string num;
	int data;
	getline(inFile, num);
	data = atoi(num.c_str());

	int length = data + 1;
	int *arr = new int[length];
	//int  j, temp;



	if (length > 0)
	{
		for (int i = 1; i < length; i++)
		{
			arr[i] = 0;
			inFile >> arr[i];
		}
		inFile.close();
	}

	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	mergeSort(arr, 0, length - 1);// merge sort call

	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);


	outFile << "Time: " << time_span.count() << " seconds. " << endl;

	for (int i = 1; i < length; i++)
	{
		outFile << arr[i] << endl;
	}

	outFile.close();
	inFile.close();

	delete[] arr;

}

void opt6() // Heap sort function
{
	cout << "Heap sort completed. " << endl;

	ifstream inFile;

	inFile.open("Data.txt");

	ofstream outFile;

	outFile.open("HeapSorted.txt");


	string num;
	int data;
	getline(inFile, num);
	data = atoi(num.c_str());

	int length = data + 1;
	int *arr = new int[length];
          

	if (length > 0)
	{
		for (int i = 1; i < length; i++)
		{
			arr[i] = 0;
			inFile >> arr[i];
		}
		inFile.close();
	}

	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	
	heapSort(arr, length); // heap sort call

	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);


	outFile << "Time: " << time_span.count() << " seconds. " << endl;

	for (int i = 2; i < length+ 1; i++)//LALALALALLAL
	{
		outFile << arr[i] << endl;
	}

	outFile.close();
	inFile.close();

	//delete[] arr;
}

void maxHeapify(int* arr, int i, int n)
{
	int largest, temp;//variable, value holder
	int heapsize = n; // heap size variable instead of n

	int l = 2 * i; // left
	int r = (2 * i + 1); // right

	//if left child is bigger than the root
	if (l <= heapsize && arr[l] > arr[i])
		largest = l;

	else
		largest = i;
	// if right child is bigger than the root
	if (r <= heapsize && arr[r]>arr[largest])
		largest = r;
	                
	//if largest is not root
	if (largest != i)
	{
		//swapping arr[i] with arr[largest] 
		temp = arr[i];
		arr[i] = arr[largest];
		arr[largest] = temp;

		//recursive call the altered sub tree
		maxHeapify(arr, largest, heapsize);
	}
}
void buildmaxHeap(int* arr, int n)
{
	//convverting arr into max heap
	for (int i = n / 2; i >= 1; i--)
	{
		maxHeapify(arr, i, n);
	}
}

void heapSort(int* arr, int n)
{
	//call buildmapHeap
	buildmaxHeap(arr, n);

	//retrieve data from heap and get sorted array
	int i, temp;
	for (i = n; i >= 2; i--)
	{
		// move top element to end element
		temp = arr[i];
		arr[i] = arr[1];
		arr[1] = temp;
		//call maxHeapify on reduced heap
		maxHeapify(arr, 1, i - 1);
	}
}

void opt7() // Quick Sort function
{
	cout << "Quick sort completed" << endl;

	ifstream inFile;

	inFile.open("Data.txt");

	ofstream outFile;

	outFile.open("QuickSorted.txt");


	string num;
	int data;
	getline(inFile, num);
	data = atoi(num.c_str());

	int length = data + 1;
	int *arr = new int[length];


	if (length > 0)
	{
		for (int i = 1; i < length; i++)
		{
			arr[i] = 0;
			inFile >> arr[i];
		}
		inFile.close();
	}

	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	quickSort(arr, 0, length);// quick sort call

	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);


	outFile << "Time: " << time_span.count() << " seconds. " << endl;

	for (int i = 2; i < length + 1; i++)
	{
		outFile << arr[i] << endl;
	}

	outFile.close();
	inFile.close();

	//delete[] arr;


}

void quickSort(int* arr, int p, int r) // quick sort algorithm
{
	if (p < r)
	{
		//q is index after partition call
		int q = partition(arr, p, r);

		//recursive call to sort elements of left and right of the pivot
		quickSort(arr, p, q - 1);
		quickSort(arr, q + 1, r);
	}

}

int partition(int* arr, int p, int r)
{
	int temp;//used for swapping
	int temp2;// used for swapping
	int pivot = arr[r];   //pivot element
	int i = (p - 1);  

	for (int j = p; j <= r - 1; j++)// p = start, r =end
	{
	//if elemtn is smaller than or equal to pivot, do a swap and increment
		if (arr[j] <= pivot)
		{
			i++;    
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}

	//swap pivot with index location
	temp2 = arr[i + 1];
	arr[i + 1] = arr[r];
	arr[r] = temp2; 

	return (i + 1);
}





