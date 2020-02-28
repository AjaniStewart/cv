/*
Author:  Ajani Stewart
Date:    February 15,2020
File:    vision_funcs.h
Purpose: header file containing all the forward declarations of funcs
*/


#ifndef VISION_FUNCS_H_
#define VISION_FUNCS_H_

#define CVP ComputerVisionProjects

#include <vector>

#include "image.h"
#include "DisjointSet.h"



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


/*
  in_image is the input greyscale image, threshold to be used.
  This returns an image pointer where the image is a binary image created
  from in_image and a supplied threshold.

  All pixels above the threshold are colored black and those under is colored
  white
*/

CVP::Image* create_binary_image(CVP::Image *in_image, size_t threshold);


/* 
  This function labels labeled_image using the sequential labeling algorithm. binary_image is the 
  input binary image. It returns the equivanlency table associtated with the labelling so that the 
  equivalencies can be resolved
*/
DisjointSet create_equivalency_table(CVP::Image* labeled_image, CVP::Image* binary_image);

/*
  This resolves equivalences of labeled_image using eq_table, and putting all the objects into
  consecutive natural numbers
*/
void resolve_equivalencies(CVP::Image *labeled_image, DisjointSet eq_table);

/* This returns an image pointer to an image with labelled objects.
   The background is always labelled 0 (black).
   Each obect will be labelled with various (non-0) shades of grey and is set as continuous natural numbers.
   Binary image should only be a binary image
*/
CVP::Image* create_labeled_image(CVP::Image *binary_image);

/*
  This returns a vector of ObjProps associated with every object in the image
*/
std::vector<ObjProps> analyze_labeled_image(CVP::Image* labeled_image);

/*
  this returns a vector of object props where each ObjProp is similar to something in image_props
*/

std::vector<ObjProps> recognize_objs (std::vector<ObjProps> input_obs, std::vector<ObjProps> image_props);

// converts degrees to radians
double to_rad(double angle);

#endif  //VISION_FUNCS_H_