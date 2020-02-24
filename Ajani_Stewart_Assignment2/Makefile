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
	$(CXX) $(CXXFLAGS) $(INCLUDES)  -c $< -o $@


#Including
INCLUDES=  -I. 

#-->All libraries (without LEDA)
LIBS_ALL =  -L/usr/lib -L/usr/local/lib 


#First Program (ListTest)
#DisjointSet.o

OBJS=image.o vision_funcs.o DisjointSet.o p2.o

PROGRAM_NAME=p2

$(PROGRAM_NAME): $(OBJS)
	g++ $(CXXFLAG) -o $(EXEC_DIR)/$@ $(OBJS) $(INCLUDES) $(LIBS_ALL)


all: 
	make $(PROGRAM_NAME) 


clean:
	(rm -f *.o; rm $(PROGRAM_NAME))

(:
