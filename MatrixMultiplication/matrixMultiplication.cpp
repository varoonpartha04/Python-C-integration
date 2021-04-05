extern "C" // required when using C++ compiler
int* matrixMultiplication(int* array1, int* array2, int length1, int length2, int length3) {
  int* res = new int[length1*length2];
  for (int row = 0; row<length1; row++) {
    for(int column=0 ; column<length2 ; column++){
      res[row*length2 + column] = 0;
      for(int traverse=0; traverse<length3 ; traverse++){
        res[row*length2 + column] += array1[row*length3+traverse]* array2[column + traverse*length3];
      }
    }
  }
  return res;
}
