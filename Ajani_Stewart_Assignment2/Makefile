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


#############################
###### VARIABLES
#############################

# ### FLAGS 
# CXX 		:= g++ 
# STANDARD 	:= -std=c++11 $(CXXFLAGS) -g -O0 # -fsanitize=address,undefined
# #WARNINGS 	:= -Wall -Wextra #-fdiagnostics-color=always


# MATH_LIBS = -lm

# EXEC_DIR=.

# #Including
# INCLUDES=  -I. 


# #-->All libraries (without LEDA)
# LIBS_ALL =  -L/usr/lib -L/usr/local/lib 


# ### Files

# P1 := p1.o
# OBJSP1 := image.o $(P1) funcsP1.o
# EXECP1 := prob1

# P2 := p2.o
# OBJSP2 := image.o $(P2) funcsP2.o EqTable.o
# EXECP2 := prob2

# P3 := p3.o
# OBJSP3 := image.o $(P3) funcsP3.o 
# EXECP3 := prob3

# P4 := p4.o
# OBJSP4 := image.o $(P4) funcsP4.o funcsP3.o
# EXECP4 := prob4

# #############################
# ###### COMPILING  
# #############################

# .cc.o:
# 	@echo "Compiling -> $@"
# 	@g++ $(STANDARD) $(INCLUDES) -c $< -o $@

# $(EXECP1): $(OBJSP1) 
# 	@$(CXX) $(STANDARD) -o $(EXEC_DIR)/$@ $(OBJSP1) $(INCLUDES) $(LIBS_ALL)
# 	@echo "Successfully finished compiling p1!"

# $(EXECP2): $(OBJSP2) 
# 	@$(CXX) $(STANDARD) -o $(EXEC_DIR)/$@ $(OBJSP2) $(INCLUDES) $(LIBS_ALL)
# 	@echo "Successfully finished compiling p2!"

# $(EXECP3): $(OBJSP3) 
# 	@$(CXX) $(STANDARD) -o $(EXEC_DIR)/$@ $(OBJSP3) $(INCLUDES) $(LIBS_ALL)
# 	@echo "Successfully finished compiling p3!"

# $(EXECP4): $(OBJSP4) 
# 	@$(CXX) $(STANDARD) -o $(EXEC_DIR)/$@ $(OBJSP4) $(INCLUDES) $(LIBS_ALL)
# 	@echo "Successfully finished compiling p4!"

# all: $(EXECP1) $(EXECP2) $(EXECP3) $(EXECP4)

# #############################
# ###### RUNNING & TESTING
# #############################

# exec:
# 	@echo "Executing all tasks..."
# 	make p1
# 	make p2
# 	make p3
# 	make p4


# p1: 
# 	@echo "Creating binary image..."
# 	@./$(EXECP1) PgmImages/two_objects.pgm 122 binary.pgm
# 	@./$(EXECP1) PgmImages/many_objects_1.pgm 122 binary2.pgm
# 	@./$(EXECP1) PgmImages/many_objects_2.pgm 122 binary3.pgm
# 	@echo "View file 'binary.pgm' 'binary1.pgm' 'binary2.pgm' to see results"

# p2:
# 	@echo "Labeling binary image..."
# 	@./$(EXECP2) binary.pgm  labeled.pgm
# 	@./$(EXECP2) binary2.pgm many_objects1.pgm
# 	@./$(EXECP2) binary3.pgm many_objects2.pgm
# 	@echo "View files 'labeled.pgm' 'many_objects1.pgm' 'many_objects2.pgm' to see results"

# p3: 
# 	@echo "Computing object attributes and generating database..."
# 	@./$(EXECP3) labeled.pgm data.txt data.pgm
# 	@echo "View file 'data.pgm' and 'data.txt' to see results"

# p4: 
# 	@echo "Investigating objects from database"
# 	@./$(EXECP4) many_objects1.pgm data.txt output.pgm
# 	@./$(EXECP4) many_objects2.pgm data.txt output2.pgm
# 	@echo "View file 'output.pgm' to see results"

# #############################
# ###### CLEANING
# #############################

# .PHONY: cleanall clean

# cleanall:
# 	@echo "Removing executables and objects..."
# 	@$(RM) -r *.o $(EXEC) $(EXECP1) $(EXECP2) $(EXECP3) $(EXECP4)
# 	@echo "Removing images..."
# 	@$(RM) -r binary.pgm labeled.pgm data.txt output.pgm output2.pgm binary2.pgm binary3.pgm data.pgm many_objects1.pgm many_objects2.pgm
# 	@echo "finished cleaning"

# clean:
# 	@echo "cleaning objects and executable..."
# 	@$(RM) -r *.o $(EXEC) $(EXECP1) $(EXECP2) $(EXECP3) $(EXECP4)
# 	@echo "finishing cleaning"
# Type a message, @name...


