static bool eigen_did_assert = false;
#define eigen_assert(X) if(!eigen_did_assert && !(X)){ std::cout << "### Assertion raised in " << __FILE__ << ":" << __LINE__ << ":\n" #X << "\n### The following would happen without assertions:\n"; eigen_did_assert = true;}

#include <iostream>
#include <Eigen/Eigen>

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif


using namespace Eigen;
using namespace std;

int main(int, char**)
{
  cout.precision(3);
// intentionally remove indentation of snippet
{
Matrix3f A;
Vector3f b;
A << 1,2,3,  4,5,6,  7,8,10;
b << 3, 3, 4;
Vector3f x = A.inverse() * b;
cout << "The solution is:" << endl << x << endl;

}
  return 0;
}
