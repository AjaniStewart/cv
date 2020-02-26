#include <vector>
#include <unordered_map>
#include <iostream>
#include <cmath>

#include "image.h"
#include "DisjointSet.h"
#include "vision_funcs.h"

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

/* 
  Strategy

  +---------+---------+
  |         +         |
  |    D    +    C    |
  |---------+---------|
  |         +         |
  |    B    +    A    |
  |---------+---------|

  A is pixel to be labeled
  A = (row,col)
  D = (row-1,col-1)
  C = (row-1,col)
  B = (row,col-1)

  1) If A is 0 (background), do nothing
  2) If B,C,D is 0 or -1 (corner), A is a new region
  3) If D is labeled, A = D
  4) If D is background and either B or C is labeled or B = C, A = B (if C is 0) or A = C (if B = 0)
  5) If B and C are labeled and B != C, A = B and B and C are marked as equivalent

*/

/*
  This function returns the union find data structure associated with the process of labelling image. It also labels labeled_image
*/
DisjointSet create_equivalency_table(CVP::Image* labeled_image, CVP::Image* binary_image) {
  DisjointSet labels;
  size_t next_label = 1;

  labeled_image->AllocateSpaceAndSetSize(binary_image->num_rows(), binary_image->num_columns());

  for (size_t row = 0; row < binary_image->num_rows(); row++) {
    for (size_t col = 0; col < binary_image->num_columns(); col++) {

      int A = binary_image->GetPixel(row,col);
      if (A != 0) { //case 1
      int B = labeled_image->GetPixel(row,col-1);
      int C = labeled_image->GetPixel(row-1,col);
      int D = labeled_image->GetPixel(row-1,col-1);
        if (B <= 0 && C <= 0 && D <= 0) { // Case 2
          labels.add();
          labeled_image->SetPixel(row,col,next_label++);
        } else if (D > 0) { // Case 3
          labeled_image->SetPixel(row,col,D);
        } else if (B > 0 && (C <= 0)) { //Case 4
          labeled_image->SetPixel(row,col,B);
        } else if (C > 0 && B <= 0) { //Case 4
          labeled_image->SetPixel(row,col,C);
        } else if (B > 0 && C > 0 && B != C) { //Case 5
          // B-1, C-1 because region 1 is at index 0, region N at index N-1
          //have to find because
          labels.set_union(labels.find(B-1),labels.find(C-1));
          labeled_image->SetPixel(row,col,B);
        }
      } else {
        labeled_image->SetPixel(row,col,0);
      } 
    }
  }
  size_t num_regions = labels.num_roots();
  std::cout << "There are " << num_regions << " objects in this image!\n";

  labeled_image->SetNumberGrayLevels(num_regions+1);
  return labels;
}

void resolve_equivalencies(CVP::Image *labeled_image, DisjointSet eq_table) {
  std::vector<int> regions = eq_table.root_indexes();
  std::unordered_map<int,int> map;

  for (int i = 0; i < regions.size(); i++) {
    map.emplace(regions[i],i+1);
  }

  for (size_t row = 0; row < labeled_image->num_rows(); row++) {
    for (size_t col = 0; col < labeled_image->num_columns(); col++) {
      int cur_label = labeled_image->GetPixel(row,col);
      if (cur_label != 0) {
        int root_label = eq_table.find(cur_label-1);
        int new_label = map[root_label];
        labeled_image->SetPixel(row,col,new_label);
      }
    }
  }
}

CVP::Image* create_labeled_image(CVP::Image *binary_image) {
  CVP::Image* labeled_image = new CVP::Image;
  DisjointSet labels = create_equivalency_table(labeled_image, binary_image);
  resolve_equivalencies(labeled_image, labels);

  return labeled_image;
}

double to_degrees(double angle) {
  return angle * 180.0 / M_PI;
}

double to_rad(double angle) {
  return angle * M_PI / 180.0;
}

std::vector<ObjProps> analyze_labeled_image(CVP::Image* labeled_image) {
  std::vector<ObjProps> obj_props;


  //calculate area and center of mass
  for (size_t x = 0; x < labeled_image->num_rows(); x++) {
    for (size_t y = 0; y < labeled_image->num_columns(); y++) {
      int cur_label = labeled_image->GetPixel(x,y);
      if (cur_label > 0) {
        // object i is in region i-1
        if (cur_label > obj_props.size()) {
          obj_props.push_back({cur_label,x,y,1,0,0,0,0});
        } else {
          //obj_props[cur_label-1] is the right object
          obj_props[cur_label-1].x_pos_center += x;
          obj_props[cur_label-1].y_pos_center += y;

          //update area
          obj_props[cur_label-1].area++;
        }
      }
    }
  }

  //need ref here sp we modify the actual struct, not make a copy
  for (auto& o : obj_props) {
    o.x_pos_center = o.x_pos_center / o.area;
    o.y_pos_center = o.y_pos_center / o.area;
  }
  
  //calculate orientation and axis of rotation
  for (size_t x = 0; x < labeled_image->num_rows(); x++) {
    for (size_t y = 0; y < labeled_image->num_columns(); y++) {
      int cur_label = labeled_image->GetPixel(x,y);
      if (cur_label > 0) {
        int x_prime = x - obj_props[cur_label-1].x_pos_center;
        int y_prime = y - obj_props[cur_label-1].y_pos_center;

        obj_props[cur_label-1].second_moment_a += x_prime * x_prime;
        obj_props[cur_label-1].second_moment_b += x_prime * y_prime;
        obj_props[cur_label-1].second_moment_c += y_prime * y_prime;
      }
    }
  }

  for (auto& o : obj_props) {
    o.angle_of_rotation = to_degrees(atan2(o.second_moment_b,o.second_moment_a - o.second_moment_c)) / 2;
    // E = 1/2(a+b)-1/2(a-c)cos(2ϴ)-1/2(bsin(2ϴ))
    o.min_moment_of_inertia = 0.5 * (o.second_moment_a + o.second_moment_b) 
                            - 0.5*(o.second_moment_a - o.second_moment_c)*cos(2*o.angle_of_rotation) 
                            - 0.5*o.second_moment_b*sin(2*o.angle_of_rotation);

    // CVP::DrawLine(o.x_pos_center,o.y_pos_center,o.x_pos_center + 10, (o.x_pos_center + 10)*tan(to_rad(o.angle_of_rotation)),0,labeled_image);
  }

  return obj_props;
}