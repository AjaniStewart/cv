########################################
##
## Makefile
## LINUX compilation 
##
##############################################


#FLAGS
CXX=g++

CXXFLAGS = -g -std=c++11

MATH_LIBS = -lm

EXEC_DIR=.


.cc.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@


#Including
INCLUDES=  -I. 

#-->All libraries (without LEDA)
LIBS_ALL =  -L/usr/lib -L/usr/local/lib 

OBJS=image.o 

all: 
	make s1
	make s2
	make s3
	make s4

s1: s1.o $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC_DIR)/$@ $(OBJS) s1.o $(INCLUDES) $(LIBS_ALL)

s2: s2.o $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC_DIR)/$@ $(OBJS) s2.o $(INCLUDES) $(LIBS_ALL)

s3: s3.o $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC_DIR)/$@ $(OBJS) s3.o $(INCLUDES) $(LIBS_ALL)

s4: s4.o $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC_DIR)/$@ $(OBJS) s4.o $(INCLUDES) $(LIBS_ALL)

.PHONY: cleanall clean


clean:
	(rm -f *.o; rm s1 s2 s3 s4; rm -f *.pgm;)

(: