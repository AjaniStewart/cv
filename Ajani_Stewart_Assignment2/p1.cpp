#include <iostream>
#include <exception>
#include <string>

#include "vision_funcs.h"
#include "image.h"

int main (int argc, char** argv) {
  std::string usage_string = "usage: p1 [input_image] [input_grey_level_threshold] [output_image]\n";
  std::string invalid_threshold_string = "Error: input_grey_level_threshold is valid\n";
  
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