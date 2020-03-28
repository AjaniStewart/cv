/*
Author:  Ajani Stewart
Date:    February 15,2020
File:    h2.cpp
Purpose: driver code to create a new binary image
*/


#include <iostream>
#include <exception>
#include <string>

#define CVP ComputerVisionProjects
#include "image.h"




CVP::Image* create_binary_image(CVP::Image* in_image, size_t threshold); 

int main (int argc, char** argv) {
  std::string usage_string = "usage: h2 [input_image] [input_grey_level_threshold] [output_image]\n";
  std::string invalid_threshold_string = "Error: input_grey_level_threshold is invalid\n";
  
  if (argc < 4) {
    std::cout << usage_string; 
  } else {
    CVP::Image* in_image = new CVP::Image;

    bool readFail = CVP::ReadImage(argv[1],in_image);
    if (!readFail) {
      std::cout << "could not read image\n";
      exit(1);
    }

    int threshold;
    try {
      threshold = std::stoi(argv[2]);
    } catch (std::exception& e) {
      std::cout << usage_string + invalid_threshold_string;
      exit(1);
    }

    CVP::Image* out_image = create_binary_image(in_image,threshold);

    bool writeFail = CVP::WriteImage(argv[3],*out_image);
    
    if (!writeFail) {
      std::cout << "could not create image\n";
      exit(1);
    }

    std::cout << "Created binary image: " << argv[3] << "\n";

    return 0;
  }
}

CVP::Image* create_binary_image(CVP::Image* in_image, size_t threshold) {
  CVP::Image* out_image = new CVP::Image;
  out_image->AllocateSpaceAndSetSize(in_image->num_rows(),in_image->num_columns());
  out_image->SetNumberGrayLevels(255);

  for (size_t row = 0; row < in_image->num_rows(); row++) {
    for (size_t col = 0; col < in_image->num_columns(); col++){
      if (in_image->GetPixel(row,col) > threshold) {
        out_image->SetPixel(row,col,255);
      } else {
        out_image->SetPixel(row,col,0);
      }
    }
  }

  return out_image;
}