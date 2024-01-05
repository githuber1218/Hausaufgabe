#include <iostream>
#include <cmath>
#include <vector>
#include <string>

using namespace std;

#include <vector>
using namespace std;

vector<vector<double>> matrix_multiply_complete(const vector<vector<double>> &A, const vector<vector<double>> &B) {
    int rows = A.size();
    int cols = B[0].size();
    int temp = B.size(); 
    vector<vector<double>> result(rows, vector<double>(cols, 0));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            for (int k = 0; k < temp; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return result;
}

vector<vector<double>> matrix_pwr(const vector<vector<double>> &A, int n) {
    int size = A.size();
    vector<vector<double>> result(size, vector<double>(size, 0));

    for (int i = 0; i < size; i++) {
        result[i][i] = 1;
    }

    for (int i = 0; i < n; i++) {
        result = matrix_multiply_complete(result, A);
    }

    return result;
}

/** This function returns the matrix multiplication for
* two matrices with order m X n, and n X 1
*/
vector<double>  matrix_multiply(const vector<vector <double> > &A,const vector <double> &B)
{
    //TODO: Enter your code here
    int rows = A.size();    
    int cols = A[0].size(); 

    if (cols != B.size()) {
        throw "Not Correspond";
    }

    vector<double> result(rows, 0);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i] += A[i][j] * B[j];
        }
    }

    return result;
}

// Determinant of a matrix of size n

double matrix_determinant(const vector<vector<double> > &A,int n)
{
    double det = 0;
    vector<vector<double>> submatrix(n,vector<double>(n));
    if (n == 2)
      return ((A[0][0] * A[1][1]) - (A[1][0] * A[0][1]));
    else {
      for (int x = 0; x < n; x++) {
            int subi = 0;
            for (int i = 1; i < n; i++) {
               int subj = 0;
               for (int j = 0; j < n; j++) {
                  if (j == x)
                  continue;
                  submatrix[subi][subj] = A[i][j];
                  subj++;
               }
               subi++;
            }
            det = det + (pow(-1, x) * A[0][x] * matrix_determinant(submatrix,n-1));
      }
   }
   return det;
}

/** System class containing:
 * Matrix A (order n X n)
 * Vector B (order n X 1)
 * Function controllability_check()
 * */
class System{
    public:
    System(int n): A(n,vector<double>(n)){}

    vector< vector<double> > A; // Row-major ordered system matrix
    vector<double> B; // Input vector

    public:
    /** Function to check for system's controllability using above functions:
    * return string "System is controllable" or string "System is not controllable"
    */
    string controllability_check(){
        // TODO: Enter your code here instead of current implementation
        int n = A.size();
        vector<vector<double>> Q(n, vector<double>(n, 0)); // 初始化Q矩阵

        vector<double> temp = B;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                Q[j][i] = temp[j];
            }
            temp = matrix_multiply(A, temp);  // 确保matrix_multiply正确实现
        }

        double det = matrix_determinant(Q, n);  // 确保matrix_determinant正确实现
        return det != 0 ? "Is Controllable" : "Uncontrollable";
    }
};

int main()
{   
    /* ======================
     *      part one
     * ======================
     */
    
    //System 1
    System System1(2);             // Number of state variables for System 1
    System1.A= {{1, 2}, {3, 4}};   // System Matrix for System 1
    System1.B= {1, 2};             // Input vector for System 1

    //System 2
    System System2(2);
    System2.A={{-2, 0}, {0, -1}};
    System2.B={2, 0};

    //System 3
    System System3(6);
    System3.A={{5,5,5,5,5,5},   {0, 5,5,5,5,5}, {0,0,5,5,5,5},{0,0,0,5,5,5 }, {0,0,0,0,5,5},{0,0,0,0,0,5}  };
    System3.B={2, 2, 2, 2,2,2};
    
    // System 4
    const double s = 5.0e-10; // constant
    
    System System4(6);
    System4.A={{1.0e-10,s,s,s,s,s},   {0, s,s,s,s,s}, {0,0,s,s,s,s},{0,0,0,s,s,s }, {0,0,0,0,s,s},{0,0,0,0,0,s}  };
    System4.B={2, 2, 2, 2,2,2};
    
    //System 5
    System System5(3);
    System5.A={{-1, 0, 0}, {0, -2, 0},{0, 1, 3}};
    System5.B={4, 0, 0};

    // System 6
    System System6(4);
    System6.A={{1, 5, 3, 3}, {2, 6, 4, 5}, {3, 7, 5, 6}, {4, 8, 6, 7}};
    System6.B={5, 6, 7, 8};

    
    
   
    
    // Output with the test cases:
    cout << "System 1 is controllable. Your result: " << System1.controllability_check() << endl;
    cout << "System 2 is not controllable. Your result: " << System2.controllability_check() << endl;
    cout << "System 3 is controllable. Your result: " << System3.controllability_check() << endl;
    cout << "System 4 is controllable. Your result: " << System4.controllability_check() << endl;
    cout << "System 5 is not controllable. Your result: " << System5.controllability_check() << endl;
    cout << "System 6 is not controllable. Your result: " << System6.controllability_check() << endl;
    
    // Use systems 1-6 to validate your implementation of controllability_check()
    
    /* ======================
     *      part two
     * ======================
     */
    
    // ============================= transformation matrix for later =============================
    
    vector<vector<double>> T = {{1,0,0,0,0,0}, {0,1,0,0,0,0},{0,-2,1,-1,0,0},{0,0,0,1,0,0},{0,0,0,0,1,0},{0,0,0,0,0,1}}; 
    vector<vector<double>> invT = {{1,0,0,0,0,0},{0,1,0,0,0,0},{0,2,1,1,0,0},{0,0,0,1,0,0},{0,0,0,0,1,0},{0,0,0,0,0,1}};
    
    // ============================= first example =============================
     // System 7a
    // x' = Ax + B*u
     double c = 5.123456789;  // arbitrary constant
     double b = 2.3456789; // arbitrary constant
     double a = 2.123456789; // arbitrary constant
 
    System System7a(6);
    System7a.A={{a,c,c,c,c,c}, {0,0,c,c,c,c},  {a, c,3*c,4*c,4*c,4*c}, {0,0,0,c,c,c }, {0,0,0,0,c,c},{0,0,0,0,0,c}  };
    System7a.B={b,b,4*b,b,b,b};
    
    //System 7b 
    // System 7b is derived from System 7a using z = T*x and therefore z' = T*A*invT z+ T*B*u
    System System7b(6);
    // this is T*A*invT

    System7b.A={{a,3*c,c,2*c,c,c}, {0,2*c,c,2*c,c,c},  {a, 3*c,c,2*c,c,c}, {0,0,0,c,c,c }, {0,0,0,0,c,c},{0,0,0,0,0,c}  }; // this is T*A
    System7b.B={b,b,b,b,b,b};
    

     // ============================= second example =============================
    
    
    // System 8a: check for other values
    // x' = Ax + B*u
      c = 3.141593;  // arbitrary constant: pi
      b = 2.718281; // arbitrary constant: euler's number
      a = 0.577216; // arbitrary constant: euler-mascheroni constant
 
    System System8a(6);
    System8a.A={{a,c,c,c,c,c}, {0,0,c,c,c,c},  {a, c,3*c,4*c,4*c,4*c}, {0,0,0,c,c,c }, {0,0,0,0,c,c},{0,0,0,0,0,c}  };
    System8a.B={b,b,4*b,b,b,b};
    
    
    // System 8b is derived from System 8a using z = T*x and therefore z' = T*A*invT z+ T*B*u with same T and invT as above.
    System System8b(6);
    
    // this is T*A*invT
    System8b.A={{a,3*c,c,2*c,c,c}, {0,2*c,c,2*c,c,c},  {a, 3*c,c,2*c,c,c}, {0,0,0,c,c,c }, {0,0,0,0,c,c},{0,0,0,0,0,c}  }; // this is T*A
    
    //this is T*B
    System8b.B={b,b,b,b,b,b};
    
    
    
    
    
    
    
    // ============================= third example =============================
    // System 9a: check for other values
    // x' = Ax + B*u
      c = 2.0;  // arbitrary constant
      b = 3.0; // arbitrary constant
      a = 1.0; // arbitrary constant
 
    System System9a(6);
    System9a.A={{a,c,c,c,c,c}, {0,0,c,c,c,c},  {a, c,3*c,4*c,4*c,4*c}, {0,0,0,c,c,c }, {0,0,0,0,c,c},{0,0,0,0,0,c}  };
    System9a.B={b,b,4*b,b,b,b};
    
    
    // System 9b is derived from System 9a using z = T*x and therefore z' = T*A*invT z+ T*B*u with same T and invT as above.
    System System9b(6);
    
    // this is T*A*invT
    System9b.A={{a,3*c,c,2*c,c,c}, {0,2*c,c,2*c,c,c},  {a, 3*c,c,2*c,c,c}, {0,0,0,c,c,c }, {0,0,0,0,c,c},{0,0,0,0,0,c}  }; // this is T*A
    
    //this is T*B
    System9b.B={b,b,b,b,b,b};
    
    
    
    
    cout << "System 7a -- Your result: " << System7a.controllability_check() << endl;
    cout << "System 7b -- Your result: " << System7b.controllability_check() << endl;
    cout << "System 8a -- Your result: " << System8a.controllability_check() << endl;
    cout << "System 8b -- Your result: " << System8b.controllability_check() << endl;
    cout << "System 9a -- Your result: " << System9a.controllability_check() << endl;
    cout << "System 9b -- Your result: " << System9b.controllability_check() << endl;
    
    
    // Take a break and think about whether the results for the systems 7a-9b make sense or not. Depending on how you chose to implement the controllability_check(), this may not be the case. Because we only expect you to put finite amound of work and time into this task, it is sufficient if your algorithm is basically correct and works correctly for the systems 1-6. However, if your algorithm doesn't seem to work correctly for the systems 7a-9b, you need to give an explanation why your algorithm fails to do so.
    
    /* TODO:Enter your explanation here
     * 
     */
    
    
    // Your suggestion how to overcome this problem
    /* Optional TODO: Enter your suggestion here
     * 
     */
}
