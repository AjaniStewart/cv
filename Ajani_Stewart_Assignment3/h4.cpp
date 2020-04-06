#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <unordered_map>
#include <stdexcept>

#include "image.h"
#include "DisjointSet.h"

using namespace ComputerVisionProjects;
using namespace std;

vector<int> split (const string& s);
bool read_voting_array_from_file(const string& filename, vector<vector<int>>& v);
vector<vector<int>> threshold_voting_array(const vector<vector<int>>& voting_array, int threshold);
DisjointSet create_equivalency_table(vector<vector<pair<int,int>>>& weighted_labeled_array,const vector<vector<int>>& voting_array);
void resolve_equivalencies(vector<vector<pair<int,int>>>& weighted_labeled_array,DisjointSet& eq_table);
vector<vector<pair<int,int>>> make_weighted_voting_array(const vector<vector<int>>& voting_array);



//step 1: store the votes and the region label in a tuple when using sequential labeling algo
//step 2: find center of area using the votes as the weighted thing
//step 3: ???
//step 4: profit
int main(int argc, char** argv) {

  // vector<vector<int>> a {{1,2,4},{4,3,1},{2,2,5}};

  // auto b = threshold_voting_array(a,3);

  vector<vector<int>> a;
  read_voting_array_from_file("t",a);
  auto b = make_weighted_voting_array(a);

  // for (const auto& v: a) {
  //   for (const auto& q : v) {
  //     cout << q << " ";
  //   }
  //   cout << "\n";
  // }

  // cout << a.size() << endl;
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
        // B = weighted_labeled_array->GetPixel(row,col-1);
        B = weighted_labeled_array.at(row).at(col-1).first;
      } catch (out_of_range& e) {
        B = 0;
      }
      int C;
      try {
        // B = weighted_labeled_array->GetPixel(row,col-1);
        C = weighted_labeled_array.at(row-1).at(col).first;
      } catch (out_of_range& e) {
        C = 0;
      }
      int D;
      try {
        // B = weighted_labeled_array->GetPixel(row,col-1);
        D = weighted_labeled_array.at(row-1).at(col-1).first;
      } catch (out_of_range& e) {
        D = 0;
      }
        if (B <= 0 && C <= 0 && D <= 0) { // Case 2
          labels.add();
          weighted_labeled_array[row][col].first = next_label++;
          // weighted_labeled_array->SetPixel(row,col,next_label++);
        } else if (D > 0) { // Case 3
          // weighted_labeled_array->SetPixel(row,col,D);
          weighted_labeled_array[row][col].first = D;
        } else if (B > 0 && (C <= 0)) { //Case 4
          // weighted_labeled_array->SetPixel(row,col,B);
          weighted_labeled_array[row][col].first = B;
        } else if (C > 0 && B <= 0) { //Case 4
          // weighted_labeled_array->SetPixel(row,col,C);
          weighted_labeled_array[row][col].first = C;
        } else if (B > 0 && C > 0 && B != C) { //Case 5
          // B-1, C-1 because region 1 is at index 0, region N at index N-1
          //have to find because
          labels.set_union(labels.find(B-1),labels.find(C-1));
          weighted_labeled_array[row][col].first = B;
        }
      } else {
        weighted_labeled_array[row][col].first = 0;
      } 
    }
  }
  // size_t num_regions = labels.num_roots();
  // std::cout << "There are " << num_regions << " objects in this image!\n";
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

vector<vector<pair<int,int>>> make_weighted_voting_array(const vector<vector<int>>& voting_array) {
  vector<vector<pair<int,int>>> weighted_labeled_array;
  DisjointSet labels = create_equivalency_table(weighted_labeled_array, voting_array);
  resolve_equivalencies(weighted_labeled_array, labels);

  return weighted_labeled_array;
}