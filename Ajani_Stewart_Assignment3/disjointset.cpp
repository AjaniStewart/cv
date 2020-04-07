/* 
  Author:  Ajani Stewart
  Date:    February 15,2020
  File:    disjointSet.cpp
  Purpose: implements DisjointSet class
  
  The code is from the Disjoint Set lecture from Mark Allen Weiss
  (Data Structures & Algorithm Analysis in C++, 4th Edition. Mark Allen Weiss. Pearson, New York. ISBN:013284737x)
  Slightly adpated to make it more dynamic
*/


#include "DisjointSet.h"

#include <algorithm>
#include <iostream>
/* 
  Each index represents a parent tree
  if the value at some index is negative, it means that it is a root and the maginitude represents the size
  if positive, it represents the index of the root of the parent
*/


DisjointSet::DisjointSet() {

}

void DisjointSet::add() {
  set.push_back(-1);
}

//ASSUME THAT region 1 and region 2 are DISTINCT and are ROOTS
void DisjointSet::set_union( int region1, int region2 ) {
  if (region1 != region2) {
    if (set[region2] < set[region1]){
      set[region2] += set[region1];
      set[region1] = region2;
    } else {
      set[region1] += set[region2];
      set[region2] = region1;
    }
  }
}

//implements path compression

int DisjointSet::find(int region) {
  if (set[region] < 0) {
    return region;
  } else {
    return set[region] = find(set[region]);
  }
}

size_t DisjointSet::num_roots() const {
  return std::count_if(set.begin(),set.end(), [](int i) {
    return i < 0;
  });
}

std::vector<int> DisjointSet::root_indexes() const {
  std::vector<int> r;
  for (int i = 0; i < set.size(); i++) {
    if (set[i] < 0) {
      r.push_back(i);
    }
  }
  return r;
}

void DisjointSet::print() const {
  for (int i = 0; i < set.size(); ++i) {
    std::cout << set[i] << " ";
  }
  std::cout << "\n";
}