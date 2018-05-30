/*
 * IsisCourse.cpp
 *
 */

#include <iostream>
#include <exception>
#include <stdexcept>
#include <assert.h>

using std::runtime_error;

#include "IsisCourse.h"

IsisCourse::IsisCourse()
{
        class_capacity = 0; // no students allowed in yet
}

IsisCourse::IsisCourse(int init_capacity)
{
	class_capacity = init_capacity;
}

IsisCourse::~IsisCourse()
{
        // nothing to do
}

// purpose: set the capacity for the class and update enrollments as needed
//    args: int (the desired capacity)
//    rets: none-void
void IsisCourse::set_class_cap(int cap)
{
        if (cap < class_capacity)
                throw runtime_error("IsisCourse:  "
                                    "class capacity cannot be lowered");
        class_capacity = cap;
        if (roster.size() < class_capacity) {
                update_enrollments();
        }
}

// purpose: attempts to enroll a student into the class.
// 	    majors go directly into the class, and non-majors
//          go directly onto the waitlist, even if there is space
//          in the class.
//    args: Student
//    rets: ENROLLMENT_STATUS (i.e. MAJOR_WAITLIST,ENROLLED, etc)
IsisCourse::ENROLLMENT_STATUS IsisCourse::enroll_student(Student s)
{
	int roster_cap = get_class_cap();
	int roster_size = get_roster_size();
	if (s.major == true){
		if (roster_size == roster_cap){
			major_waitlist.enqueue(s);
			return MAJOR_WAITLIST;
		}
		else{
			roster.add(s);
			return ENROLLED;
		}
	}
	else{
		other_waitlist.enqueue(s);
		return OTHER_WAITLIST;
	}
}

// purpose: drop a student from the roster or one of the waitlists
//    args: Student
//    rets: boolian- if the student is not found, return false, otherwise
//	    remove student and return true
bool IsisCourse::drop_student(Student s)
{
        bool found_student = false;     // if we find the student to drop
        if(roster.drop(s)==true){
        	return true;
        }
        Queue temp_major_waitlist;
        while (major_waitlist.is_empty() == false){
        	Student temp = major_waitlist.dequeue();
        	if (temp.name == s.name){
        		found_student = true;
        		continue;
        	}
        	temp_major_waitlist.enqueue(temp);
        }
        while (temp_major_waitlist.is_empty() == false){
        	Student temp = temp_major_waitlist.dequeue();
        	major_waitlist.enqueue(temp);
        }
        Queue temp_other_waitlist;
        while (other_waitlist.is_empty() == false){
        	Student temp = other_waitlist.dequeue();
        	if (temp.name == s.name){
        		found_student = true;
        		std::cout<< temp.name<<std::endl;
        		continue;
        	}
        	temp_other_waitlist.enqueue(temp);
        }
        while (temp_other_waitlist.is_empty() == false){
        	Student temp = temp_other_waitlist.dequeue();
        	other_waitlist.enqueue(temp);
        }
        // if we dropped a student, there should be room on
        // the roster
        update_enrollments();
        return found_student;
}

// purpose: find the index of a student on the waitlist is at
//    args: ENROLLMENT_STATUS and Student
//    rets: int (the index the student is at)
int IsisCourse::waitlist_position(ENROLLMENT_STATUS status, Student s)
{
	assert (status != NONE and status != ENROLLED);
	int count = 0;
	if (status == MAJOR_WAITLIST){
		while (major_waitlist.is_empty() == false){
			Student temp = major_waitlist.dequeue();
			if (temp.name == s.name){
				return count;
			}
			count++;
		}
	}
	else if (status == OTHER_WAITLIST){
		while (other_waitlist.is_empty() == false){
			Student temp = major_waitlist.dequeue();
			if (temp.name == s.name){
				return count;
			}
			count++;
		}
	}
	return -1;
}

// purpose: return the class capacity
//    args: none
//    rets: int (class capacity)
int IsisCourse::get_class_cap()
{
	return class_capacity;
}

int IsisCourse::get_roster_size()
{
	return roster.size();
}

// purpose: return the enrollment statuts of a student
//    args: Student
//    rets: ENROLLMENT_STATUS- return NONE if student is not found
IsisCourse::ENROLLMENT_STATUS IsisCourse::status(Student s)
{
        ENROLLMENT_STATUS found_student = NONE;

        if (roster.is_enrolled(s) == true){
        	found_student = ENROLLED;
        	return found_student;
        }
        Queue temp_major_waitlist;
        while (major_waitlist.is_empty() == false){
        	Student temp = major_waitlist.dequeue();
        	if (temp.name == s.name){
        		found_student = MAJOR_WAITLIST;
        	}
        	temp_major_waitlist.enqueue(temp);
        }
        while (temp_major_waitlist.is_empty() == false){
        	Student temp = temp_major_waitlist.dequeue();
        	major_waitlist.enqueue(temp);
        }
        Queue temp_other_waitlist;
        while (other_waitlist.is_empty() == false){
        	Student temp = other_waitlist.dequeue();
        	if (temp.name == s.name){
        		found_student = OTHER_WAITLIST;
        	}
        	temp_other_waitlist.enqueue(temp);
        }
        while (temp_other_waitlist.is_empty() == false){
        	Student temp = temp_other_waitlist.dequeue();
        	other_waitlist.enqueue(temp);
        }
        return found_student;
}

// purpose: print list for the roster, major waitlist, or other waitlist
//    args: ENROLLMENT_STATUS
//    rets: none- void
void IsisCourse::print_list(ENROLLMENT_STATUS status)
{
        Queue *waitlist_queue;
        Queue  temp_queue;
        bool major = true;
        int count = 0;

        if (status == ENROLLED) {
                roster.print_class();
                return;
        }
        if (status == MAJOR_WAITLIST) {
                waitlist_queue = &major_waitlist;
        } else {
                waitlist_queue = &other_waitlist;
                major = false;
        }
        while ( waitlist_queue->is_empty() == false){
        	count++;
        	Student temp = waitlist_queue->dequeue();
        	std::cout<< count << ". " << temp.name <<std::endl;
        	temp_queue.enqueue(temp);
        }
        // don't need to delete waitlist_queue because already dequeued
        waitlist_queue = &temp_queue;
        while (waitlist_queue->is_empty() == false){
        	Student temp = waitlist_queue->dequeue();
        	if (major == true){
        		major_waitlist.enqueue(temp);
        	}
        	else{
        		other_waitlist.enqueue(temp);
        	}
        }
}

// purpose: put students from the waitlists into the course in priority
//	    (majors first, then others), up to the class capacity
//    args: none
//    rets: none
void IsisCourse::update_enrollments()
{
	while (get_roster_size() < class_capacity){
		if (major_waitlist.is_empty() == false){
			Student temp = major_waitlist.dequeue();
			roster.add(temp);
		}
		else if (other_waitlist.is_empty() == false){
			Student temp = other_waitlist.dequeue();
			roster.add(temp);
		}
		else if (major_waitlist.is_empty()==true and
				other_waitlist.is_empty()==true){
			break;
		}
	}
}

