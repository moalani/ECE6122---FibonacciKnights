/*
 Author: Mohammed Alani
 Class: ECE6122
 Last Date Modified: 9/2/2019
 
 Description:
 This file contains the solution to Problem 3 in HMK1 for ECE6122 2019 Fall Term. The output from the file will be utilize standard output cout format of the numerical output to the problem.
 The file contains (4) functions: (a) isFibonacciNumber, (b) isOrderOfFibonacci (c) orderOfFibonacci and (d) main. Descriptions for each function is direclty above the function.
 */

#include <iostream>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <numeric> 
#include <functional>
#include <vector>

using namespace std;

/*
 Function Name: isFibonacciNumber
 Function Objective: determines if a given number is a fibonacci number
 Input: [long <target number>]
 Output: [boolean <true if meets objective>]
 
 Function determines if a given number, n, is a fibonacci number if it is a perfect square when
 used in either of 5*n*n + 4 or 5*n*n + -4
 
 */


bool isFibonacciNumber(long n)
{
    long x = sqrt(5*n*n + 4);
    long y = sqrt(5*n*n - 4);
    
    if (x*x == 5*n*n + 4 || y*y == 5*n*n - 4 )
    {
        return true;
    }
    
    else
    {
        return false;
    }
    
    
}
/*
 Function Name: isOrderOfFibonacci
 Function Objective: determines if a vector meets knights of the order of fibonacci criteria
 Input: [vector <proposed fibonnaci order> , long<total number of knights>]
 Output: [boolean <true if meets objective>]
 
 
 */

bool isOrderOfFibonacci(vector<long> fibSequence,long k)
{
    long i = 0;
    bool flag=true;
    
    if (fibSequence.size() != k)
    {
        return false;
    }
    
    // summing every two adjacent elements and calling isFibonacciNumber function to determine if the
    // the summation adds up to a fibonacci number or not.
    
    while( i < k-1){
        if (isFibonacciNumber(fibSequence.at(i)+fibSequence.at(i+1)) == false)
        {
            flag= false; // if the summation is not a fibonacci number, we break the loop and stop
            break;
            
        }
        else{
            i++;
        }
    }
    return flag;
    
}

/*
 Function Name: orderOfFibonacci
 Function Objective: determines the ordering of given number of knights to meet the knights of order of
 fibonacci criteria
 Input: [ long<total number of knights>]
 Output: [void] -- function provides stdout of the sequence if it meets the criteria otherwise it gives a message that the criteria cannot be met
 
 Below is the primary function used to determine the order of kinghts of fiboannci. The algorithm is per
 the following:
 
 Step 1. Determine the first number in the fibonacci sequence. This number will be the highest
 possible fibonacci number in the group of numbers < n
 
 Step 2. finding the next number in the sequence. The next number will be highest possible summation
 of (n + n -1 ) that is actually a fibonacci number that the number will achieve. For example, if n = 5
 the highest next fibonacci number that is acheivable is 8. Therefore, the next number will be 8-5 = 3.
 The same procedure is applied over and over.
 
 Step 3. this step is to make sure that the chosen number has not already been chosen. This is the most
 expensive compuation in this algorithm.
 */

long orderOfFibonacci(long n)
{
    
    // step 1. finding the first term
    
    long firstTerm = n ;

    while (firstTerm<=n)
    {
        if (isFibonacciNumber(firstTerm) == true) // if we find the highest fibonacci number then we break.
        {
            break;
        }
        
        else
        {
            firstTerm -- ;
        }
    }
    
    std::vector< long > fibonacciOrder; // this vector stores the series of numbers that form the fibonacci order
    
    fibonacciOrder.push_back(firstTerm); //inserting first term
    
    //long *arr1 = new long[n];
    //arr1[0] = firstTerm;

    // step 2. finding the next term
    
    long nextNumber = n;

    std::vector<long>::iterator hasBeenChosen ; // condition we use to check if number was selected already
    while (fibonacciOrder.size()<n && nextNumber >0)
    {
        // defining an iterator to check if the number has already been chosen
        hasBeenChosen = std::find(fibonacciOrder.begin(), fibonacciOrder.end(), nextNumber);

        if ((isFibonacciNumber(nextNumber + fibonacciOrder.back()) == true) && hasBeenChosen == fibonacciOrder.end())
        {

            fibonacciOrder.push_back(nextNumber);  // if it is a fibonacci number, we push into vector
            nextNumber = n; // reset nextNumber
        }
        else if (nextNumber == 1) // if next number cannot be found, then sequence has no solution
        {
            cout<<"No solution found!"<<endl;
            break;
            //return 0;
        }
        
        else
        {
            nextNumber -- ; // if we are still looking for the next highest number, decrement nextNumber
        }
    }

    // calling isOrderOfFibonacci to make sure the vector we indentified is a fibonacci sequence
    // that meets the critera of the order of fibonacci
    
    if (isOrderOfFibonacci(fibonacciOrder,n) == true)
    {
        std::cout << "K, ";
        for (long i = 0; i < fibonacciOrder.size()-1; i++) // printing the vector elements
        {
            std::cout << fibonacciOrder.at(i) << ", ";
        }
        std::cout << fibonacciOrder.back()<<endl;
    }
    
    
    
    return 0;
}
/*
 Function Name: main()
 Function Objective: the main function takes the user input (number of knights) and then calls orderOfFibonacci function to perform the algorithms described above. In main(), the user input is also validated.
 
 */
int main()
{
    
    long n; // number of knights -- input by user
    char ch; // char input to track any input that is character and segment floating points in input
    cout <<"Please enter the number of knights: ";
    cin>> n;
    cin.get(ch);
    

    if (cin.fail()==true || ch != '\n' || n<3 ) // making sure input is valid. Per the assignement requirements, is is positive integer n>2
    {
        std::cout << "Invalid Entry! Next time enter a valid number."<<endl;
    }
    
    else
    {
        orderOfFibonacci(n); // if the input is valid, then orderOfFibonacci is called.
    }
    

    
    
    return 0;
    
}
