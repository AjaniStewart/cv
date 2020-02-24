#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#include <vector>

class  DisjointSet {
  public:
    DisjointSet();
    void  set_union(int label_1, int label_2);
    int  find(int label);
    void add();
    size_t size() { return set.size(); };
    size_t num_roots() const;
    std::vector<int> root_indexes() const;
    void print() const;

    
    
  private:
    std::vector <int> set;
};

#endif //DISJOINT_SET_H