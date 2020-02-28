/*
Author:  Ajani Stewart
Date:    February 15,2020
File:    vision_funcs.h
Purpose: header_file containing all the forward declarations of funcs
*/


#ifndef VISION_FUNCS_H_
#define VISION_FUNCS_H_

#define CVP ComputerVisionProjects

#include <vector>

#include "image.h"
#include "DisjointSet.h"

/*
  This returns an image pointer where the image is a binary image created
  from in_image and a supplied threshold.

  All pixels above the threshold are colored black and those under is colored
  white
*/

typedef struct {
  int label;
  double x_pos_center;
  double y_pos_center;
  size_t area;
  double min_moment_of_inertia;
  double max_moment_of_inertia;
  double angle_of_rotation;
  double roundness;
  double second_moment_a;
  double second_moment_b;
  double second_moment_c;
} ObjProps;

void print_obj_props(const ObjProps& op);

CVP::Image* create_binary_image(CVP::Image *in_image, size_t threshold);


/* This returns an image pointer to an image with labelled objects.
   The background is always labelled 0 (black).
   Each obect will be labelled with various (non-0) shades of grey.
   Binary image should only be a binary image
*/
DisjointSet create_equivalency_table(CVP::Image* labeled_image, CVP::Image* binary_image);
void resolve_equivalencies(CVP::Image *labeled_image, DisjointSet eq_table);
CVP::Image* create_labeled_image(CVP::Image *binary_image);

std::vector<ObjProps> analyze_labeled_image(CVP::Image* labeled_image);

std::vector<ObjProps> recognize_objs (std::vector<ObjProps> input_obs, std::vector<ObjProps> image_props);

double to_rad(double angle);

#endif  //VISION_FUNCS_H_