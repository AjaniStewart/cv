#include <iostream>
#include <vector>
#include <fstream>

#include "image.h"

using namespace ComputerVisionProjects;
using namespace std;

vector<int> split (const string& s);
bool read_voting_array_from_file(const string& filename, vector<vector<int>>& v);
vector<vector<int>> threshold_voting_array(const vector<vector<int>>& voting_array, int threshold);


int main(int argc, char** argv) {

  // vector<vector<int>> a {{1,2,4},{4,3,1},{2,2,5}};

  // auto b = threshold_voting_array(a,3);

  vector<vector<int>> a;
  read_voting_array_from_file("v.txt",a);

  for (const auto& v: a) {
    for (const auto& q : v) {
      cout << q << " ";
    }
    cout << "\n";
  }

  cout << a.size() << endl;
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