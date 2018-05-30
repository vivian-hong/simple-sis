/*
 * Set.h
 *
 * This class is a Set, which holds Students.
 * The Set has the following public methods:
 * bool Set::add(Student s)
 * bool drop(Student s);
 * bool is_enrolled(Student s);
 * void print_class();
 * int size();
 *
 * You must implement this class.
 * You may (must!) add private members, but you must not change
 * the public interface.
 */

#ifndef SET_H_
#define SET_H_

#include "Student.h"

class Set {
public:
        Set();
        ~Set();

        bool add        (Student s);
        bool drop       (Student s);
        bool is_enrolled(Student s);
        void print_class();
        int size        ();

private:
        // TODO --- students choose representation
        Student *student_list;
        int capacity;
        int next_spot;
        void expand();
};

#endif /* SET_H_ */
