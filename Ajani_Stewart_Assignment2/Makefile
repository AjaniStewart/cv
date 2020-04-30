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

OBJS=image.o DisjointSet.o vision_funcs.o

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
	(rm -f *.o; rm p1 p2 p3 p4; rm -f *.pgm; rm -f *Output*)


# runall:
# 	make run1
# 	make run2
# 	make run3
# 	open h4Output*

# run1:
# 	./h1 images/hough_simple_1.pgm h1Output.1.pgm
# 	./h2 h1Output.1.pgm 75 h2Output.1.pgm	
# 	./h3 h2Output.1.pgm h3Output.1.pgm h3Output.1.txt
# 	./h4 images/hough_simple_1.pgm h3Output.1.txt 280 h4Output.1.pgm

# run2:
# 	./h1 images/hough_simple_2.pgm h1Output.2.pgm
# 	./h2 h1Output.2.pgm 55 h2Output.2.pgm	
# 	./h3 h2Output.2.pgm h3Output.2.pgm h3Output.2.txt
# 	./h4 images/hough_simple_2.pgm h3Output.2.txt 280 h4Output.2.pgm

# run3:
# 	./h1 images/ims_cubes.pgm h1Output.3.pgm
# 	./h2 h1Output.3.pgm 175 h2Output.3.pgm
# 	./h3 h2Output.3.pgm h3Output.3.pgm h3Output.3.txt
# 	./h4 images/ims_cubes.pgm h3Output.3.txt 300 h4Output.3.pgm



(: