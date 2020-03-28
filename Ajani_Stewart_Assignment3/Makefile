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
	make h1
	make h2
	make h3
	# make h4

h1: h1.o $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC_DIR)/$@ $(OBJS) h1.o $(INCLUDES) $(LIBS_ALL)

h2: h2.o $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC_DIR)/$@ $(OBJS) h2.o $(INCLUDES) $(LIBS_ALL)

h3: h3.o $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC_DIR)/$@ $(OBJS) h3.o $(INCLUDES) $(LIBS_ALL)

# h4: h4.o $(OBJS)
# 	$(CXX) $(CXXFLAGS) -o $(EXEC_DIR)/$@ $(OBJS) h4.o $(INCLUDES) $(LIBS_ALL)

.PHONY: cleanall clean

clean:
	(rm -f *.o; rm h1 h2 h3)

(: