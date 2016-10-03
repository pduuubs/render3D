#include <iostream>
#include <Eigen/Dense>

using Eigen::MatrixXd;

main(){
  MatrixXd m(2,2);
  m(0,0) = 2;
  m(1,0) = 2.5;
  m(0,1) = -1;
  m(1,1) = m(1,0) + m(0,1);
  std::cout << m << std::endl;
    return 0;
}
