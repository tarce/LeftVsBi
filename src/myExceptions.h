/*
 * myExceptions.h
 *
 *  Created on: Apr 3, 2014
 *      Author: terek
 */

#ifndef MYEXCEPTIONS_H_
#define MYEXCEPTIONS_H_



// exception classes for various error types

#include <string>
#include <iostream>

using namespace std;

// illegal parameter value
class illegalParameterValue
{
   public:
      illegalParameterValue(string theMessage = "Illegal parameter value")
            {message = theMessage;}
      void outputMessage() {cout << message << endl;}
   private:
      string message;
};

// illegal input data
class illegalInputData
{
   public:
      illegalInputData(string theMessage = "Illegal data input")
            {message = theMessage;}
      void outputMessage() {cout << message << endl;}
   private:
      string message;
};

// illegal index
class illegalIndex
{
   public:
      illegalIndex(string theMessage = "Illegal index")
            {message = theMessage;}
      void outputMessage() {cout << message << endl;}
   private:
      string message;
};

// queue Empty
class queueEmpty
{
   public:
      queueEmpty(string theMessage =
                   "Invalid operation on empty queue")
            {message = theMessage;}
      void outputMessage() {cout << message << endl;}
   private:
      string message;
};

#endif /* MYEXCEPTIONS_H_ */
