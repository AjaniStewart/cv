/*
  Author: Ajani Stewart
  File: s1.cpp
  Purpose: Computes the location of center and radius of a sphere.
*/


#include <iostream>
#include <fstream>
#include <string>

#include "image.h"

using namespace ComputerVisionProjects;
using namespace std;


Image* create_binary_image(Image* in_image, size_t threshold);

void get_sphere_info(Image* image, double& x_center, double& y_center, double& radius);

void write_items_to_file(string filename, double x, double y, double r);


int main(int argc, char** argv) {
  if (argc != 4) {
    cout << "usage: ./s1 [input-original-image] [input-threshold-value] [output params file]\n";
    return EXIT_SUCCESS;
  }

  Image* input_image = new Image;
  if (!ReadImage(argv[1], input_image)) {
    cout << "could not read image: " << argv[1] << "\n";
    return EXIT_FAILURE;
  }
  int threshold;
  try {
    threshold = stoi(argv[2]);
  } catch (exception& e) {
    cout << "invalid value entered for threshold: " << e.what() << "\n";
    return EXIT_FAILURE;
  }
  Image* binary_image = create_binary_image(input_image,threshold);
  double x_center, y_center, radius;
  get_sphere_info(binary_image,x_center,y_center,radius);
  write_items_to_file(argv[3],x_center,y_center,radius);

  cout << "wrote sphere paramaters to file: " << argv[3] << "\n";
  return EXIT_SUCCESS;
  
} // end main


Image* create_binary_image(Image* in_image, size_t threshold) {
  Image* out_image = new Image;
  out_image->AllocateSpaceAndSetSize(in_image->num_rows(),in_image->num_columns());
  out_image->SetNumberGrayLevels(255);

  for (size_t row = 0; row < in_image->num_rows(); row++) {
    for (size_t col = 0; col < in_image->num_columns(); col++){
      if (in_image->GetPixel(row,col) > threshold) {
        out_image->SetPixel(row,col,255);
      } else {
        out_image->SetPixel(row,col,0);
      } // end if 
    } //end for
  } //end for

  return out_image;
} // end create_binary_image


void get_sphere_info(Image* image, double& x_center, double& y_center, double& radius) {
  //find center then radius
  size_t area = 0;
  for (size_t i = 0; i < image->num_rows(); ++i) {
    for (size_t j = 0; j < image->num_columns(); ++j) {
      if (image->GetPixel(i,j)) {
        x_center += j;
        y_center += i;
        area++;
      } //end if
    }//end for
  }// end for
  x_center = x_center / area;
  y_center = y_center / area;

  // cout << "x: " << x_center << " y: " << y_center <<endl;

  //for radius, average the distances from the top, bottom, left, right points on circumferences
  radius = 0;
  //right
  auto cur = x_center;
  while (image->GetPixel(y_center,cur)) {
    cur++;
  } // end while
  radius += (cur - x_center);

  //left

  cur = x_center;
  while (image->GetPixel(y_center,cur)) {
    cur--;
  } // end while
  radius += (x_center - cur);

  //top
  cur = y_center;
  while (image->GetPixel(cur, x_center)) {
    cur++;
  } // end while
  radius += (cur - y_center);

  //bottom

  cur = y_center;
  while (image->GetPixel(cur, x_center)) {
    cur--;
  } // end while
  radius += (y_center - cur);

  radius /= 4;
} // end get_sphere_info

void write_items_to_file(string filename, double x, double y, double r) {
  ofstream f (filename);
  f << x << " " << y << " " << r << "\n";
  f.close();
}