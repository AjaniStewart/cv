/*
  Author: Ajani Stewart
  File: s4.cpp
  Purpose: computes surface albedo of object from images
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <utility>
#include <fstream>

#include "image.h"

using namespace ComputerVisionProjects;
using namespace std; 


typedef vector<vector<double>> d_matrix;

void init_d_matrix(d_matrix& d, size_t n);

void getCofactor(d_matrix& A, d_matrix& temp, int p, int q, int n);

double determinant(d_matrix& A, int n);

void adjoint(d_matrix& A, d_matrix& adj);

bool inverse(d_matrix& A, d_matrix& inverse);

double dot_product(vector<double> a, vector<double> b);

vector<double> compute_surface_normal(d_matrix inverse_source_matrix, vector<double> intensities);

double compute_vector_length(const vector<double>& v);

Image* compute_albedo_in_images(Image* i1, Image* i2, Image* i3, 
          int thresh, d_matrix inverse_source_matrix);

vector<double> split (const string& s);

bool read_params_from_file(const string& filename, d_matrix& v);


int main(int argc, char** argv) 
{ 
  if (argc != 7) {
    cout << "usage: ./s3 [input_directions] [image 1] [image 2] [image 3] ";
    cout << "[threshold] [output]\n";
    exit(EXIT_SUCCESS);
  }

  d_matrix source_directions;
  if (!read_params_from_file(argv[1],source_directions)) {
    cout << "could not read from file: " << argv[1] << endl;
    exit(EXIT_FAILURE);
  }

  Image* i1 = new Image;
  if (!ReadImage(argv[2],i1)) {
    cout << "could not read from file: " << argv[2] << endl;
    exit(EXIT_FAILURE);
  }

  Image* i2 = new Image;
  if (!ReadImage(argv[3],i2)) {
    cout << "could not read from file: " << argv[3] << endl;
    exit(EXIT_FAILURE);
  }

  Image* i3 = new Image;
  if (!ReadImage(argv[4],i3)) {
    cout << "could not read from file: " << argv[4] << endl;
    exit(EXIT_FAILURE);
  }


  int threshold;
  try {
    threshold = stoi(argv[5]); 
  } catch (exception& e) {
    cout << "invalid value for threshold: " << e.what() << "\n";
    exit(EXIT_FAILURE);
  }

  d_matrix source_inverse;
  init_d_matrix(source_inverse,source_directions.size());

  inverse(source_directions,source_inverse);
  Image* out = compute_albedo_in_images(i1,i2,i3,threshold,source_inverse);
  if (!WriteImage(argv[6],*out)) {
    cout << "could not write image to: " << argv[6] << endl;
    exit(EXIT_FAILURE);
  }

  cout << "wrote image to: " << argv[6] << endl;
  exit(EXIT_SUCCESS);
} 

//code for finding the inverse of a matrix is from : https://www.geeksforgeeks.org/adjoint-inverse-matrix/

void init_d_matrix(d_matrix& d, size_t n) {
  for (size_t i = 0; i < n; ++i) {
    d.emplace_back();
    for (size_t j = 0; j < n; ++j) {
      d[i].push_back(0);
    }
  }
}

// Function to get cofactor of A[p][q] in temp[][]. n is current 
// dimension of A[][] 

void getCofactor(d_matrix& A, d_matrix& temp, int p, int q, int n) { 
	int i = 0, j = 0; 
	// Looping for each element of the matrix 
	for (int row = 0; row < n; row++) { 
		for (int col = 0; col < n; col++) { 
			// Copying into temporary matrix only those element 
			// which are not in given row and column 
			if (row != p && col != q) { 
				temp[i][j++] = A[row][col]; 
				// Row is filled, so increase row index and 
				// reset col index 
				if (j == n - 1) { 
					j = 0; 
					i++; 
				} 
			} 
		} 
	} 
} 

/* Recursive function for finding determinant of matrix. 
n is current dimension of A[][]. */
double determinant(d_matrix& A, int n) { 
	double D = 0; // Initialize result 
	// Base case : if matrix contains single element 
	if (n == 1) 
		return A[0][0]; 
	d_matrix temp; // To store cofactors 
  init_d_matrix(temp,A.size());
	int sign = 1; // To store sign multiplier 
	// Iterate for each element of first row 
	for (int f = 0; f < n; f++) { 
		// Getting Cofactor of A[0][f] 
		getCofactor(A, temp, 0, f, n); 
		D += sign * A[0][f] * determinant(temp, n - 1); 
		// terms are to be added with alternate sign 
		sign = -sign; 
	} 
	return D; 
} 

// Function to get adjoint of A[N][N] in adj[N][N]. 
void adjoint(d_matrix& A, d_matrix& adj) { 
	if (A.size() == 1) { 
		adj[0][0] = 1; 
		return; 
	} 

	// temp is used to store cofactors of A[][] 
	int sign = 1;
  d_matrix temp;
  init_d_matrix(temp,A.size()); 

	for (int i=0; i<A.size(); i++) { 
		for (int j=0; j<A.size(); j++) { 
			// Get cofactor of A[i][j] 
			getCofactor(A, temp, i, j, A.size()); 

			// sign of adj[j][i] positive if sum of row 
			// and column indexes is even. 
			sign = ((i+j)%2==0)? 1: -1; 

			// Interchanging rows and columns to get the 
			// transpose of the cofactor matrix 
			adj[j][i] = (sign)*(determinant(temp, A.size()-1)); 
		} 
	} 
} 

// Function to calculate and store inverse, returns false if 
// matrix is singular 
bool inverse(d_matrix& A, d_matrix& inverse) { 
	// Find determinant of A[][]
	int det = determinant(A, A.size()); 
	if (det == 0) { 
		cout << "Singular matrix, can't find its inverse"; 
		return false; 
	} 

	// Find adjoint 
	d_matrix adj;
  init_d_matrix(adj,A.size()); 
	adjoint(A, adj); 
	// Find Inverse using formula "inverse(A) = adj(A)/det(A)" 
	for (int i=0; i<A.size(); i++) 
		for (int j=0; j<A.size(); j++) 
			inverse[i][j] = adj[i][j]/double(det); 
	return true; 
}

double dot_product(vector<double> a, vector<double> b) {
  double tot = 0;
  for (size_t i = 0; i < a.size(); ++i) {
    tot += a[i]*b[i];
  }
  return tot;
}

vector<double> compute_surface_normal(d_matrix inverse_source_matrix, vector<double> intensities) {
  vector<double> normal;
  for (const auto& source: inverse_source_matrix) {
    normal.push_back(dot_product(source,intensities));
  }
  return normal;
}

double compute_vector_length(const vector<double>& v) {
  double length = 0;
  for (const auto& i : v) {
    length += i*i;
  }
  return sqrt(length);
}

Image* compute_albedo_in_images(Image* i1, Image* i2, Image* i3, 
          int thresh, d_matrix inverse_source_matrix) {
  Image* out = new Image(*i1);
  //store lengths with their xy pos
  //at index i, coords[i] is the pos corresponding with normals[i]
  vector<pair<int,int>> coords;
  d_matrix normals;
  double max_length = 0;
  for (size_t i = 0; i < out->num_rows(); i++) {
    for (size_t j = 0; j < out->num_columns(); j++) {
      auto i1_b = double(i1->GetPixel(i,j));
      auto i2_b = double(i2->GetPixel(i,j));
      auto i3_b = double(i3->GetPixel(i,j));
      if (i1_b > thresh && i2_b > thresh && i3_b > thresh) {
        //compute surface normal at that point
        auto normal = compute_surface_normal(inverse_source_matrix,{i1_b,i2_b,i3_b});
        coords.push_back(make_pair(i,j));
        normals.push_back(normal);
        double length = compute_vector_length(normal);
        if (length > max_length)
          max_length = length;

      } else {
        out->SetPixel(i,j,0);
      }//end if
    }//end for
  }//end for

  assert(coords.size() == normals.size());

  for (size_t i = 0; i < coords.size(); ++i) {
    auto length = (compute_vector_length(normals[i]) / max_length * 255);
    out->SetPixel(coords[i].first, coords[i].second, length);
  } // end for
  return out;
}//end compute_normals_in_images

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

bool read_params_from_file(const string& filename, d_matrix& v) {
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