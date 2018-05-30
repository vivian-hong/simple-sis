/*
 * Set.cpp
 *
 * Add your code below.  Do not change the print function.
 *
 */

#include <iostream>
#include "Set.h"

using namespace std;

Set::Set()
{
	student_list = NULL;
	capacity = 0;
	next_spot = 0;
}

Set::~Set(){

	delete[] student_list;
}

// purpose: add a student to the roster
//    args: Student
//    rets: boolian- true if the student was added
bool Set::add(Student s)
{
	if (next_spot == capacity){
		expand();
	}
	student_list[next_spot]=s;
	next_spot++;
	return true;
}

// purpose: drop a student from the roster
//    args: Student
//    rets: boolian- true if dropped student, false if student was not found
bool Set::drop(Student s)
{
	if (next_spot == 0){
		return false;
	}
	for(int i=0; i<next_spot; i++){
		if(student_list[i].name == s.name){
			while (i<next_spot-1){
				student_list[i]=student_list[i+1];
				i++;
			}
			next_spot--;
			return true;
		}
	}
	return false;
}

// purpose: finds if student is enrolled or not
//    args: Student
//    rets: boolian- true if student is on the roster, false if not
bool Set::is_enrolled(Student s)
{
	if (next_spot == 0){
		return false;
	}
	for (int i=0; i<next_spot; i++){
		if(student_list[i].name == s.name){
			return true;
		}
	}
	return false;
}

// purpose: return the size the array
//    args: none
//    rets: int next_spot (size)
int Set::size()
{
	return next_spot;
}

// purpose: prints the students on the roster and whether or not their
//          majoring in the course subject
//    args: none
//    rets: none
void Set::print_class()
{
        for (int i = 0; i < next_spot; i++) {
                Student s = student_list[i];
                cout << s.name << ", "
                                << (s.major ? "Major" : "Non-Major")
                                << "\n";
        }
}

// purpose: expands the array when the size equals the capacity
//    args: none
//    rets: none
void Set::expand()
{
	Student *bigger_array = new Student[capacity*2+1];
	for (int i = 0; i<next_spot; i++){
		bigger_array[i]=student_list[i];
	}
	delete[]student_list;
	student_list = bigger_array;
	capacity = capacity*2+1;
}
