// Your code here!
#include "exam.h"
#include "matrix.h"


namespace exam{
  Matrix flip_rows(const Matrix &m){
    //copy the original matrix
    Matrix result = Matrix(m);

    //iterate through all coords
    for(int row = 0; row < result.get_num_rows(); row++){
      for(int column = 0; column < result.get_num_columns(); column++){

        //check for odd row number
        if(result.get_num_rows() % 2 != 0 && row == result.get_num_rows() - 1){
          continue;
        }

        else{
          // if current row number is even(0, 2, 4,...)
          if(row % 2 == 0){
            result.set_coord(row, column, m.get_coord(row + 1, column));
          }

          // if current row number is odd(1, 3, 5,...)
          else{
            result.set_coord(row, column, m.get_coord(row - 1, column));
          }

        }
      }
    }

    return result;
  }
}
