Name: Ajani Stewart

All parts of the project was completed


PgmImages contains exmaple greyscale images to use

Code that creates binary images from greyscale images, labels individual objects within the image, computes values associated
with the objects and writes them to a file, and use that file to attempt to identify objects in another image.

image.* : Image class (2-D array of integers, along with size, number of colors)
                      (For our purposes the number of colors is 256)

vision_funcs.* : Functions related to image processesing. Also contains the definition of the struct, ObjProps, which represents the
                properties related to the objects. properties are label, x and y coords of center of mass, min and max momemt of inertia,
                angle of orientation, roundness, a,b,c values to calculate moment of inertia
                create_binary_image,
                create_equivalency_table, resolve_equivalencies -> used together to label an image
                create_labeled_image
                analyze_labeled_image -> computes values in ObjProps

DisjointSet.* : Disjoint set class for union-find functionality. Taken from Mark Allen Weiss 
                (Data Structures & Algorithm Analysis in C++, 4th Edition. Mark Allen Weiss. Pearson, New York. ISBN:013284737x)

p1.cpp : Driver program to create a binary image

p2.cpp : Driver program to label an image

p3.cpp : Driver program to compute object props in label image

p4.cpp : Driver program to recognize objects

----------------------
To compile in Linux:
----------
 
   make all

To run:
---------

this will open input_image, set the grey threshold to input_grey_level_threshold for binarization, and save the output to output_image
./p1 [input_image] [input_grey_level_threshold] [output_image]

this will open input_binary_image, label it, and save the result to output_label_image
./p2 [input_binary_image] [output_label_image]

this will open input_labeled_image, compute the object props for all objects in the image, 
output a text version of the props to output_database, and draw lines on the image to represent the orientation and save the result to output_image
./p3 [input_labeled_image] [output_database] [output_image]

this will open input_labeled_image and input_database, parse the database into a set of object props, 
and attempt to match the object props to the objects in the image
./p4 [input_labeled_image] [input_database] [output_image]

all images should be .pgm and using a program with an inappropriate image will result in undefined behavior

other than a few segmentation faults, there were no major bugs encountered
-----------

To view .pgm files you can use the open source program gimp:

https://www.gimp.org/
