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

OBJS=image.o vision_funcs.o DisjointSet.o

all: 
	make p1
	make p2
	make p3
	make p4

p1: p1.o $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC_DIR)/$@ $(OBJS) p1.o $(INCLUDES) $(LIBS_ALL)

p2: p2.o $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC_DIR)/$@ $(OBJS) p2.o $(INCLUDES) $(LIBS_ALL)

p3: p3.o $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC_DIR)/$@ $(OBJS) p3.o $(INCLUDES) $(LIBS_ALL)

p4: p4.o $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC_DIR)/$@ $(OBJS) p4.o $(INCLUDES) $(LIBS_ALL)

.PHONY: cleanall clean

clean:
	(rm -f *.o; rm p1 p2 p3 p4)

(: