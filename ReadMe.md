# ReadMe for COMP 15 HW3
## ISIS Course Roster and Waitlists

Purpose:

The purpose of this program is to be able to add students to a course. If a 
student is within the major and there is space in the class, they are enrolled. 
If the student is in another major they are automatically put on the other
major waitlist. If a student is a major but there is no space left, then the 
student will go on the major waitlist. Students should be able to drop off the
various lists as well, and as soon as a space opens on the roster, major 
waitlist students fill up the spaces, then other major waitlist students until
capacity is reached. 

List of files:

IsisCourse.cpp -- contains functions that can manipulate the roster and 
                  waitlists, including adding and dropping students, returning 
                  the enrollment status, and printing the lists
IsisCourse.h -- contains the header for IsisCourse.cpp
main.cpp -- calls functions from IsisCourse.cpp and contains print functions
	    and a test for the drop function
Queue.cpp -- contains functions that deal with the queue arrays (used in
             IsisCourse for the waitlists) including enqueuing, dequeuing, 
             expanding, etc. 
Queue.h -- contains the header for Queue.cpp
Set.cpp -- contains functions that deal with dynamic arrays used in IsisCourse
           for the roster) including adding, dropping, expanding etc.
Set.h -- contains the header for Set.cpp
Student.h -- contains Student struct

How to compile:

Use included Makefile.

Outline of data structure

There is a IsisCourse class that holds instances of the Queue and Set classes. 
The Queue class is used for the two waitlists and contains functions to enqueue
and dequeue students onto and off of the lists. The Set class is used for the 
roster and uses a normal dynamic array. Both of the Queue and Set classes
contain arrays of the Student struct and are manipulated by the IsisCourse
class which can add and drop students from the roster or waitlists.

Outline of algorithm

There are a few interesting algorithms implemented in this program. The Queue
class follows FIFO rules, where the first item enqueued is also the first item
dequeued. The Queue class also uses a circular buffer, meaning that there is
a circular array with variables front and back so that the most efficient use
of space is possible with the enqueuing and dequeuing approach. 


