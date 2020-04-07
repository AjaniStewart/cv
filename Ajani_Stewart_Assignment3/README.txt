Ajani Stewart

Parts Completed:

Part 1:
- Creates an edge image from gray scale image using a sobel filter and squared derivative

Part 2: 
- Thresholds the edge image created in part 1 to remove weak edges
- Used code from previous assignment
- On the sample  images, the thresholds I used were 75,55, and 100 on hough_simple_1, hough_simple_2, and hough_complex_1
- hough_complex_1 was the most difficult to get a good edge image for

Part 3:
- Creates and saves to disk a hough voting array for an edge image and its corresponding visualisation

Part 4:
- reads from disk a hough voting array and uses it to draw lines on the original image
- works reasonably well on hough_simple_1 and hough_simple_2 when using a threshold of 280
- struggled on hough_complex_1, didnt find the vertical lines on the box(book?)
- best results on hough_complex_1 was using a threshold of 160
- I think it would work better using a better edge detector

Usage:

running 'make' in project directory will build the executables for all parts

usage:

running the executables without any arguments will print the usage to standard out
eg './h1'

 ./h1 [input_gray_level_image] [output_grey_level_image]
 ./h2 [input_image] [input_grey_level_threshold] [output_image]
 ./h3 [input_binary edge image] [output_grey_level_hough_image] [output_Hough-voting-array]
 ./h4 [input_gray_level_image] [input_hough_voting_array] [input_hough_threshold] [output_gray_level_image]