#include "image.h"
#include "vision_funcs.h"

#include <string>
#include <iostream>

int main(int argc, char** argv) {
  std::string usage_string = "usage: p2 [input binary image] [output_label_image]\n";

  if (argc != 3) {
    std::cout << usage_string;
  }

  CVP::Image* input = new CVP::Image;
  
  if (!CVP::ReadImage(argv[1],input)) {
    std::cout << "Cannot read input: " << argv[1] << "\n";
    exit(1);
  }

  CVP::Image* output = create_labeled_image(input);

  if (!CVP::WriteImage(argv[2],*output)) {
    std::cout << "cannot create file: " << argv[2] << "\n";
    exit(1);
  }

  std::cout << "Created labeled image at: " << argv[2] << "\n";

  return 0;

}