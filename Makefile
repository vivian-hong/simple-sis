#
# Makefile for ISIS Course
#
CXX      = clang++
CXXFLAGS = -g -Wall -Wextra
LDFLAGS  = -g
SRCS     = IsisCourse.cpp Set.cpp Queue.cpp main.cpp
OBJS     = IsisCourse.o   Set.o   Queue.o   main.o

isis_course:  ${OBJS}
	${CXX} ${LDFLAGS} -o hw3 ${OBJS}
clean:
	rm -rf hw3 *.o *~ *.dSYM

provide:
	provide comp15 hw3 main.cpp IsisCourse.cpp IsisCourse.h \
	        Set.cpp Set.h Queue.cpp Queue.h Student.h       \
	        ReadMe.md Makefile

IsisCourse.o:  IsisCourse.cpp IsisCourse.h Student.h Set.h Queue.h
Set.o:         Set.cpp Set.h Student.h
Queue.o:       Queue.cpp Queue.h Student.h
main.o:        main.cpp Queue.h Set.h IsisCourse.h
