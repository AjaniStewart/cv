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