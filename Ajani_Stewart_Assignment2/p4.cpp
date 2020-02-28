#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#include "image.h"
#include "vision_funcs.h"


std::vector<std::string> split (const std::string& s) {
  std::vector<std::string> res;

  size_t last = 0;
  for (size_t i = 0; i < s.size(); i++) {
    if (s[i] == ' ' || s[i] == '\n') {
      res.push_back(s.substr(last,i-last+1));
      last = i + 1;
    }
  }

  return res;
}

std::vector<ObjProps> parse_database(std::ifstream& database_file) {
  std::vector<ObjProps> res;
  while (!database_file.eof()) {
    char buffer[256];
    database_file.getline(buffer,256);
    std::string line (buffer);
    auto args = split(line);

    res.push_back(
      {
        std::stoi(args[0]),
        std::stod(args[1]),
        std::stod(args[2]),
        std::stod(args[3]),
        std::stod(args[4]),
        std::stod(args[5]),
        std::stod(args[6]),
        std::stod(args[7]),
        std::stod(args[8]),
      }
    );
  }

  return res;
}

int main(int argc, char** argv) {
  if (argc != 4) {
    std::cout << "usage: p4 [input labeled image] [input database] [output image]\n";
    exit(0);
  } else {
    CVP::Image* image = new CVP::Image;
    
    if (!CVP::ReadImage(argv[1],image)) {
      std::cout << "could not open image: " << argv[1] << "\n";
      exit(1);
    }

    std::ifstream database_file (argv[2]);
    if (database_file.fail()) {
      std::cout << "coutd not open file: " << argv[2] << "\n";
      exit(1);
    }
    auto input_objs = parse_database(database_file);
    auto reference_objs = analyze_labeled_image(image);

    auto matched_objs = recognize_objs(input_objs,reference_objs,image);

    for (const auto& obj : matched_objs) {
      CVP::DrawLine(obj.x_pos_center, obj.y_pos_center,
                  obj.x_pos_center + 20 * cos(obj.angle_of_rotation),
                  obj.y_pos_center + 20 * sin(obj.angle_of_rotation),
                  (image->GetPixel(obj.x_pos_center,obj.y_pos_center) > 127) ? 0 : 255,
                  image);
    }

    if (!CVP::WriteImage(argv[3],*image)) {
      std::cout << "error writing to image: " << argv[3] << "\n";
      exit(1);
    }

    std::cout << "wrote output to: " << argv[4] << "\n";
    return 0;
  }
}