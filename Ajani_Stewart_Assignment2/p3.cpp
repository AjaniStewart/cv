#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

#include "image.h"
#include "vision_funcs.h"

int main(int argc, char** argv) {
  if (argc != 4) {
    std::cout << "usage: p3 [input labeled image] [output database] [output image]\n";
    exit(0);
  } else {
    CVP::Image* image = new CVP::Image;
    if (!CVP::ReadImage(argv[1],image)) {
      std::cout << "error reading file: " << argv[1] << "\n";
      exit(1);
    }
    std::vector<ObjProps> obj_props = analyze_labeled_image(image);

    std::ofstream database (argv[2]);

    for (auto obj : obj_props) {
      database << obj.label << " " << obj.x_pos_center << " " 
               << obj.y_pos_center << " " << obj.area << " " 
               << obj.min_moment_of_inertia << " " << obj.max_moment_of_inertia << " " 
               << obj.angle_of_rotation << " " << obj.second_moment_a << " " 
               << obj.second_moment_b << " " << obj.second_moment_c << "\n";

      CVP::DrawLine(obj.x_pos_center, obj.y_pos_center,
                    obj.x_pos_center + 20 * cos(obj.angle_of_rotation),
                    obj.y_pos_center + 20 * sin(obj.angle_of_rotation),
                    (image->GetPixel(obj.x_pos_center,obj.y_pos_center) > 127) ? 0 : 255,
                    image);
    }
    std::cout << "Wrote database to " << argv[2] << "\n";

    if (!CVP::WriteImage(argv[3],*image)) {
      std::cout << "error writing file: " << argv[3] << "\n";
      exit(1);
    }

    std::cout << "wrote image to: " << argv[3] << "\n";
    return 0;
  }
}