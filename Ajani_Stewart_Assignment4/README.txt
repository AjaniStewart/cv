Ajani Stewart

Parts completed: s1, s2, s3, s4

Run 'make' to build all executables
To find a usage of a program, run the program without any arguments

example: ./s1

s1:
This program locates the center of a sphere and calculates the radius
Used a threshold of 110
Writes the x-coordinate, y-coordinate, and the radius to a file as numbers separated by a space

Input file was sphere0
usage: ./s1 [input-original-image] [input-threshold-value] [output params file]


s2:
This program caluclates the light source directions
To do so, three images are Used
The formula for the calulating the normal vector is N = <(x-x0)/(sqrt(r^2-(x-x0)^2-(y-y0)^2),(y-y0)/(sqrt(r^2-(x-x0)^2-(y-y0)^2)),1>
where x0 and y0 are the x and y coords of the sphere's center and r is the radius of the sphere.
The brightest pixel in each image was used to find the direction and intensity
We can do this since the sphere was a Lambertian surface, and the surface radiance (intensity) depends on only the source direction and not the viewing direction.

usage: ./s2 [input params file] [image1] [image2] [image3] [output directions file]

s3: 
This program computes the surface normals on the object using 3 images
The matrix inversion code was adapted from https://www.geeksforgeeks.org/adjoint-inverse-matrix/
A threshold of 80 was used with a step of 10

usage: ./s3 [input_directions] [image 1] [image 2] [image 3] [step] [threshold] [output]

[input_directions] is the output of s2

s4:
This program computes the albedo of the object using three images
This program uses the same equations as the ones in s3
A threshold of 80 was used

usage: ./s3 [input_directions] [image 1] [image 2] [image 3] [threshold] [output]



