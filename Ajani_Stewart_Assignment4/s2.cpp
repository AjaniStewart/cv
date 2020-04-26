/*
  Author: Ajani Stewart
  File: s2.cpp
  Purpose: computes light source directions from three images and writes them to disk
*/


#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>

#include "image.h"

using namespace ComputerVisionProjects;
using namespace std;

typedef struct {
  double x;
  double y;
  double z;
} n_vec;

void find_brightest_spot(Image* image, int& bx, int& by);

n_vec find_source_direction(Image* image, int x, int y, int x_center, int y_center, double radius);

vector<double> split (const string& s);

void read_params_from_file (string filename, vector<double>& params);

void write_directions_to_file(string filename, const vector<n_vec>& normals);

int main(int argc, char** argv) {
  if (argc != 6) {
    cout << "usage: ./s2 [input params file] [image1] [image2] [image3] [output directions file]\n";
    return EXIT_SUCCESS;
  }

  vector<double> params;
  read_params_from_file(argv[1], params);
  Image* image1 = new Image;
  Image* image2 = new Image;
  Image* image3 = new Image;

  if (!ReadImage(argv[2], image1)) {
    cout << "could not read file: " << argv[2] << "\n";
    return EXIT_FAILURE;
  }

  if (!ReadImage(argv[3],image2)) {
    cout << "could not read file: " << argv[3] << "\n";
    return EXIT_FAILURE;
  }

  if (!ReadImage(argv[4],image3)) {
    cout << "could not read file: " << argv[4] << "\n";
    return EXIT_FAILURE;
  }

  vector<Image*> images { image1, image2, image3 };
  vector<n_vec> normals;
  for (const auto& image : images) {
    int bx, by;
    find_brightest_spot(image,bx,by);
    auto normal = find_source_direction(image,bx,by,params[0],params[1],params[2]);
    normals.push_back(normal);
  }

  write_directions_to_file(argv[5],normals);

  cout << "wrote source directions to: " << argv[5] << "\n";
  return EXIT_SUCCESS;
}// end main


void find_brightest_spot(Image* image, int& bx, int& by) {
  bx = 0, by = 0;
  // rows are y, cols are x

  for (size_t i = 0; i < image->num_rows(); ++i) {
    for (size_t j = 0; j < image->num_columns(); ++j) {
      if (image->GetPixel(i,j) > image->GetPixel(by,bx)) {
        bx = j;
        by = i;
      } //end if
    } // end for
  } //end for
} //end find_brightest_spot


n_vec find_source_direction(Image* image, int x, int y, int x_center, int y_center, double radius) {

  n_vec n;
  x -= x_center;
  y -= y_center;

  n.x = x/(sqrt(radius*radius-x*x-y*y));
  n.y = y/(sqrt(radius*radius-x*x-y*y));
  n.z = 1;


  //normalize
  n.x = n.x/(sqrt(n.x*n.x+n.y*n.y+1));
  n.y = n.y/(sqrt(n.x*n.x+n.y*n.y+1));
  n.z = n.z/(sqrt(n.x*n.x+n.y*n.y+1));


  //scale
  n.x = n.x * image->GetPixel(y+y_center,x+x_center);
  //flipped to obey right hand rule
  n.y = n.y * image->GetPixel(y+y_center,x+x_center) * -1;
  n.z = n.z * image->GetPixel(y+y_center,x+x_center);
  return n;
} // end find_source_direction

vector<double> split (const string& s) {
  vector<double> res;

  size_t last = 0;
  
  for (size_t i = 0; i < s.size(); i++) {
    if (s[i] == ' ' || s[i] == '\n') {
      try {
        res.push_back(stod(s.substr(last,i-last+1)));
      } catch (exception& e) {
        //breaks when there is a " \n"
        //and ill be damned if i will fixed it
      }
      last = i + 1;
    }
  }

  res.push_back(stod(s.substr(last,s.size()-last+1)));

  return res;
}

void read_params_from_file (string filename, vector<double>& params) {
  ifstream file(filename);
  string line;
  getline(file,line);
  params = split(line);
  file.close();
}

void write_directions_to_file(string filename, const vector<n_vec>& normals) {
  ofstream file(filename);
  for (const auto& normal : normals) {
    file << normal.x << " " << normal.y << " " << normal.z << "\n";
  }
  file.close();
}