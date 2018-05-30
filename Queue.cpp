/*
 * Queue.cpp
 *
 */


// TODO: Student implements this class
#include <iostream>
#include <assert.h>
#include "Queue.h"

Queue::Queue()
{

	capacity = 0;
	size = 0;
	front = 0;
	back = 0;
	queue_array = NULL;

}

Queue::~Queue()
{
	delete[] queue_array;
}

// purpose: enqueue a student onto at the back of the queue
//    args: Student
//    rets: none
void Queue::enqueue(Student stu)
{
	if (size == capacity){
		expand();
	}
	queue_array[back]=stu;
	back = (back+1)%capacity;
	size++;
}
// purpose: dequeue a student from the front of the queue
//    args: none
//    rets: none
Student Queue::dequeue()
{
	assert (is_empty() == false);
	Student temp = queue_array[front];
	front = (front + 1)%capacity;
	size--;
	return temp;
}

// purpose: returns whether queue is empty or not
//    args: none
//    rets: true if there are no elements in the
//          queue, false if the queue has elements
bool Queue::is_empty(){
	if (size==0){
		return true;
	}
	return false;
}

// purpose: expand the array when size reaches capacity
//    args: none
//    rets: none
void Queue::expand()
{
	int i, j;
        Student *bigger_array = new Student[capacity *2 + 1];
        if (front > back){
		for (i = 0, j = front; j<= capacity; i++, j++){
			bigger_array[i]=queue_array[j];
		}
		for (j = 0; j<back; j++, i++){
			bigger_array[i]=queue_array[j];
		}
        }
        else if (front < back or back == 0){
        	for (i = 0, j = front; j<front+size; i++, j++){
        		bigger_array[i] = queue_array[j];
        	}
        }
        else if (front == back and front != 0){
        	for (i = 0, j = front; j<=capacity; i++, j++){
        		bigger_array[i]=queue_array[j];
        	}
        	for (j = 0; j<back; j++, i++){
        		bigger_array[i]=queue_array[j];
        	}
        }
        delete[]queue_array;
        queue_array = bigger_array;
        capacity =  capacity*2+1;
        front = 0;
        back = size;
}
