#include <cmath>
#include <vector>
#include <iostream>

#include "image.h"

using namespace std;
using namespace ComputerVisionProjects;

/* Dimensions of the accumalator array
  if the image is n*m and theta varies between 0 and PI
  dp = 1
  dtheta = 1

  180 x sqrt(m^2+n^2)

*/

vector<vector<int>> hough_lines(Image* image, int& max_rho, int& max_theta) {


  //number of rho samples
  int R = int(sqrt(image->num_columns() * image->num_columns() +
                 image->num_rows() * image->num_rows() ));

  //number of theta samples
  int T = 180;

  vector<vector<int>> voting_array;
  for (int i = 0; i <= T; ++i) {
    voting_array.emplace_back();
    for (int j = 0; j < R; ++j) {
      voting_array[i].push_back(0);
    }
  }

  int max_votes = 0;

  for (size_t i = 0; i < image->num_rows(); ++i) {
    for (size_t j = 0; j < image->num_columns(); ++j) {
      if (image->GetPixel(i,j) != 0) {
        for (int theta = 0; theta <= T; theta++){
          int rho = i*cos(theta*M_PI/180) + j*sin(theta*M_PI/180);
          voting_array[theta][rho] += 1;
          if (voting_array[theta][rho] > max_votes) {
            max_votes = voting_array[theta][rho];
            max_rho = rho;
            max_theta = theta;
          }
        }
      }
    }
  }
  return voting_array;
}


Image* hough_image(vector<vector<int>> voting_array, int max_votes) {
  Image* image = new Image;
  image->AllocateSpaceAndSetSize(voting_array.size(), voting_array[0].size());
  image->SetNumberGrayLevels(255);

  cout << max_votes << endl;

  //fit the votes to between 0 and 255
  for (size_t i = 0; i < voting_array.size(); ++i) {
    for (size_t j = 0; j < voting_array[0].size(); ++j) {
      image->SetPixel(i,j,(voting_array[i][j]/double(max_votes))*255);
    }
  }

  return image;
}


int main(int argc, char** argv) {
  
  if (argc != 3) {
    cout << "usage: h3 [input_binary edge image] [output_grey_level_hough_image]\n";
    exit(0);
  }
  
  Image* input = new Image;
  
  if (!ReadImage(argv[1],input)) {
    cout << "Cannot read input: " << argv[1] << "\n";
    exit(1);
  }

  int max_rho, max_theta;
  auto hough = hough_lines(input,max_rho,max_theta);
  auto output = hough_image(hough,hough[max_theta][max_rho]);

  if (!WriteImage(argv[2],*output)) {
    cout << "cannot write to file: " << argv[2] << "\n";
    exit(1);
  }

  cout << "wrote to: " << argv[2] << "\n";

  return 0;
}