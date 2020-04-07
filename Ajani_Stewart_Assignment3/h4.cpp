/*
  Author: Ajani Stewart
  File: h4.cpp
  Purpose: Reads and parses hough voting array from file to identify
           and draw lines on the original gray scale image.
*/


#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <unordered_map>
#include <stdexcept>
#include <cmath>

#include "image.h"
#include "disjointset.h"

using namespace ComputerVisionProjects;
using namespace std;

//split string where tokens are separated by spaces into a vector of ints
//ignores values that cannot be interpreted as an int
vector<int> split (const string& s);
bool read_voting_array_from_file(const string& filename, vector<vector<int>>& v);
vector<vector<int>> threshold_voting_array(const vector<vector<int>>& voting_array, int threshold);

//a part of code from previous assignment, labels hotspots and preserves weights to find center of mass
DisjointSet create_equivalency_table(vector<vector<pair<int,int>>>& weighted_labeled_array, 
  const vector<vector<int>>& voting_array);
void resolve_equivalencies(vector<vector<pair<int,int>>>& weighted_labeled_array, 
  DisjointSet& eq_table);
vector<vector<pair<int,int>>> make_weighted_voting_array(const vector<vector<int>>& voting_array, 
  int& num_regions);

//returns a vector line parameters <theta,rho> from the weighted voted array
vector<pair<double,double>> find_lines(vector<vector<pair<int,int>>> weighted_voting_array, 
  int num_regions);
void draw_lines_on_image(Image* image, const vector<pair<double,double>>& lines);

int main(int argc, char** argv) {

  if (argc != 5) {
    cout << "usage: ./h4 [input_gray_level_image] [input_hough_voting_array]";
    cout << " [input_hough_threshold] [output_gray_level_image]\n";
    exit(EXIT_SUCCESS);
  }

  Image* image = new Image;

  if (!ReadImage(argv[1], image)) {
    cout << "couldnt read from " << argv[1] << "\n";
    exit(EXIT_FAILURE);
  }

  vector<vector<int>> voting_array;

  if (!read_voting_array_from_file(argv[2],voting_array)) {
    cout << "couldnt read from " << argv[2] << "\n";
    exit(EXIT_FAILURE);
  }

  int threshold;

  try {
    threshold = stoi(argv[3]);
  } catch(exception& e) {
    cout << "could not read value for threshold\n";
    exit(EXIT_FAILURE);
  }
  voting_array = threshold_voting_array(voting_array,threshold);
  int num_weights;
  auto weighted_voting_array = make_weighted_voting_array(voting_array,num_weights);
  auto lines = find_lines(weighted_voting_array,num_weights);

  cout << "found " << lines.size() << " lines\n";
  draw_lines_on_image(image,lines);

  if (!WriteImage(argv[4], *image)) {
    cout << "couldnt write image to" << argv[4] << "\n";
    exit(EXIT_FAILURE);
  }

  return 0;
}


vector<int> split (const string& s) {
  vector<int> res;

  size_t last = 0;
  
  for (size_t i = 0; i < s.size(); i++) {
    if (s[i] == ' ' || s[i] == '\n') {
      try {
        res.push_back(stoi(s.substr(last,i-last+1)));
      } catch (exception& e) {
        //breaks when there is a " \n"
        //and ill be damned if i will fixed it
      }
      last = i + 1;
    }
  }

  return res;
}


bool read_voting_array_from_file(const string& filename, vector<vector<int>>& v) {
  ifstream file;

  try {
    file.open(filename);
  } catch (exception& e) {
    file.close();
    cout << e.what();
    return false;
  }

  string line;
  while (getline(file,line)) {
    auto s = split(line);
    v.push_back(s);
  }

  if (file.eof()) {
    file.close();
    return true;
  } else {
    file.close();
    return false;
  }
}

vector<vector<int>> threshold_voting_array(const vector<vector<int>>& voting_array, int threshold) {
  vector<vector<int>> new_array;

  for (size_t i = 0; i < voting_array.size(); ++i) {
    new_array.emplace_back();
    for (size_t j = 0;j < voting_array[0].size(); ++j) {
      if (voting_array[i][j] >= threshold)
        new_array[i].push_back(voting_array[i][j]);
      else
        new_array[i].push_back(0); 
    }
  }
  
  return new_array;
}

DisjointSet create_equivalency_table(vector<vector<pair<int,int>>>& weighted_labeled_array,const vector<vector<int>>& voting_array) {
  DisjointSet labels;
  size_t next_label = 1;


  for (size_t row = 0; row < voting_array.size(); row++) {
    weighted_labeled_array.emplace_back();
    for (size_t col = 0; col < voting_array[0].size(); col++) {
      weighted_labeled_array[row].emplace_back();
      int A = voting_array[row][col];
      weighted_labeled_array[row][col].second = A;
      if (A != 0) { //case 1
      int B;
      try {
        B = weighted_labeled_array.at(row).at(col-1).first;
      } catch (out_of_range& e) {
        B = 0;
      }
      int C;
      try {
        C = weighted_labeled_array.at(row-1).at(col).first;
      } catch (out_of_range& e) {
        C = 0;
      }
      int D;
      try {
        D = weighted_labeled_array.at(row-1).at(col-1).first;
      } catch (out_of_range& e) {
        D = 0;
      }
        if (B <= 0 && C <= 0 && D <= 0) { // Case 2
          labels.add();
          weighted_labeled_array[row][col].first = next_label++;
        } else if (D > 0) { // Case 3
          weighted_labeled_array[row][col].first = D;
        } else if (B > 0 && (C <= 0)) { //Case 4
          weighted_labeled_array[row][col].first = B;
        } else if (C > 0 && B <= 0) { //Case 4
          weighted_labeled_array[row][col].first = C;
        } else if (B > 0 && C > 0 && B != C) { //Case 5
          labels.set_union(labels.find(B-1),labels.find(C-1));
          weighted_labeled_array[row][col].first = B;
        }
      } else {
        weighted_labeled_array[row][col].first = 0;
      } 
    }
  }
  return labels;
}

void resolve_equivalencies(vector<vector<pair<int,int>>>& weighted_labeled_array,DisjointSet& eq_table) {
  vector<int> regions = eq_table.root_indexes();
  unordered_map<int,int> map;

  for (int i = 0; i < regions.size(); i++) {
    map.emplace(regions[i],i+1);
  }

  for (size_t row = 0; row < weighted_labeled_array.size(); row++) {
    for (size_t col = 0; col < weighted_labeled_array[0].size(); col++) {
      auto cur_label = weighted_labeled_array[row][col].first;
      if (cur_label != 0) {
        auto root_label = eq_table.find(cur_label-1);
        auto new_label = map[root_label];
        weighted_labeled_array[row][col].first = new_label;
      }
    }
  }
}

vector<vector<pair<int,int>>> make_weighted_voting_array(const vector<vector<int>>& voting_array, int& num_regions) {
  vector<vector<pair<int,int>>> weighted_labeled_array;
  DisjointSet labels = create_equivalency_table(weighted_labeled_array, voting_array);
  num_regions = labels.num_roots();
  resolve_equivalencies(weighted_labeled_array, labels);

  return weighted_labeled_array;
}

vector<pair<double,double>> find_lines(vector<vector<pair<int,int>>> weighted_voting_array, int num_regions) {
  vector<pair<double,double>> line_params;
  vector<int> weights;

  for (int i = 0; i < num_regions; ++i) {
    weights.push_back(0);
    line_params.emplace_back(0,0);
  }
  //weight i is in region i-1
  for (size_t theta = 0; theta < weighted_voting_array.size(); ++theta) {
    for (size_t rho = 0; rho < weighted_voting_array[0].size(); ++rho) {
      weights[weighted_voting_array[theta][rho].first-1] += weighted_voting_array[theta][rho].second;
    }
  }

  for (size_t theta = 0; theta < weighted_voting_array.size(); ++theta) {
    for (size_t rho = 0; rho < weighted_voting_array[0].size(); ++rho) {
      auto label = weighted_voting_array[theta][rho].first;
      if (label > 0) {
        auto total_votes = weights[label-1];
        line_params[label-1].first += weighted_voting_array[theta][rho].second / double(total_votes) * theta;
        line_params[label-1].second += weighted_voting_array[theta][rho].second / double(total_votes) * rho;
      }
    }
  }
  return line_params;
}

void draw_lines_on_image(Image* image, const vector<pair<double,double>>& lines) {
  for (const auto& line : lines) {
    auto theta = line.first;
    auto rho = line.second;

    int y0 = 0;
    int y1 = image->num_columns();

    int x0 = (rho - y0*sin(theta*M_PI / 180))/cos(theta*M_PI / 180);
    int x1 = (rho - y1*sin(theta*M_PI / 180))/cos(theta*M_PI / 180);

    DrawLine(x0,y0,x1,y1,255,image,true);
  }
}
