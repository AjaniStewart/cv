/*
  Name: Ajani Stewart
  File: h1.cpp
  Purpose: Creates an edge image from gray scale image using a sobel filter and squared derivative
*/
#include <cmath>
#include <iostream>

#include "image.h"

using namespace std;
using namespace ComputerVisionProjects;

int convolve(Image* image, int x, int y, int mask[3][3], int dim); 
Image* squared_gradient(Image* image);

int main(int argc, char** argv) {

  if (argc != 3) {
    cout << "usage: h1 [input_gray_level_image] [output_grey_level_image]\n";
    exit(0);
  }
  
  Image* input = new Image;
  
  if (!ReadImage(argv[1],input)) {
    cout << "Cannot read input: " << argv[1] << "\n";
    exit(1);
  }

  Image* edges = squared_gradient(input);

  if (!WriteImage(argv[2],*edges)) {
    cout << "Cannot write to: " << argv[2] << "\n";
    exit(1);
  }

  cout << "wrote to: " << argv[2] << "\n";

  return 0;
}

int convolve(Image* image, int x, int y, int mask[3][3], int dim) {
  int res = 0;
  for (int i = 0; i < dim; ++i) {
    for (int j = 0; j < dim; ++j) {
      res += image->GetPixel(x+i-2,y+j-2) * mask[i][j];
    }
  }
  return res;
}


Image* squared_gradient(Image* image) {
  Image* result = new Image;
  result->AllocateSpaceAndSetSize(image->num_rows(),image->num_columns());
  result->SetNumberGrayLevels(255);

  //masks
  int x_grad[3][3] {{-1,0,1},{-2,0,2},{-1,0,1}};
  int y_grad[3][3] {{1,2,1},{0,0,0},{-1,-2,-1}};


  for (size_t i = 0; i < image->num_rows(); ++i) {
    for (size_t j = 0; j < image->num_columns(); ++j) {
      int dx = convolve(image,i,j,x_grad,3);
      int dy = convolve(image,i,j,y_grad,3);

      int squared = dx*dx + dy*dy;
      result->SetPixel(i,j, sqrt(squared));
    }
  }
  return result; 
}