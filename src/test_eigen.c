#include <string.h>
#include "binary_library.h"
#include "stdio.h"
#include "SEGGER_RTT.h"

void demo_MatrixXd() {
  char temp[50];
  int num = 0;
  int k=0;
  struct C_MatrixXd *matrix1, *matrix2;
  SEGGER_RTT_printf(0, "*** demo_MatrixXd ***\n");
  
  matrix1 = MatrixXd_new(2, 2);
  MatrixXd_set_zero(matrix1);
  MatrixXd_set_coeff(matrix1, 0, 0, 1.2);
  MatrixXd_set_coeff(matrix1, 0, 1, 2.5);
  MatrixXd_set_coeff(matrix1, 1, 0, 3.43);
  MatrixXd_set_coeff(matrix1, 1, 1, 4.5);

  SEGGER_RTT_printf(0, "Here is matrix1:\n");

  memset(temp, 0, sizeof(temp));
  for(int i=0;i<2;i++) {
    for(int j=0;j<2;j++) {
      num += sprintf(&temp[num], "%.1f", MatrixXd_get_coeff(matrix1, i, j));
      num += sprintf(&temp[num], "%c", ',');
    }
    num += sprintf(&temp[num], "%c", '\n');
  }

  k = 0;
  while(temp[k] != '\0') {
      SEGGER_RTT_printf(0, "%c", temp[k]);
      k++;
  }


  matrix2 = MatrixXd_new(2, 2);
  MatrixXd_set_zero(matrix2);
  MatrixXd_set_coeff(matrix2, 0, 0, 2.4);
  MatrixXd_set_coeff(matrix2, 0, 1, 2.6);
  MatrixXd_set_coeff(matrix2, 1, 0, 1.12);
  MatrixXd_set_coeff(matrix2, 1, 1, 1.1);

  SEGGER_RTT_printf(0, "Here is matrix2:\n");

  num = 0;
  memset(temp, 0, sizeof(temp));
  for(int i=0;i<2;i++) {
    for(int j=0;j<2;j++) {
      num += sprintf(&temp[num], "%.1f", MatrixXd_get_coeff(matrix2, i, j));
      num += sprintf(&temp[num], "%c", ',');
    }
    num += sprintf(&temp[num], "%c", '\n');
  }

  k = 0;
  while(temp[k] != '\0') {
      SEGGER_RTT_printf(0, "%c", temp[k]);
      k++;
  }

  // ==================================================== //

  MatrixXd_multiply(matrix1, matrix2, matrix1);

  SEGGER_RTT_printf(0, "Result:\n");

  num = 0;
  memset(temp, 0, sizeof(temp));
  for(int i=0;i<2;i++) {
    for(int j=0;j<2;j++) {
      num += sprintf(&temp[num], "%.1f", MatrixXd_get_coeff(matrix1, i, j));
      num += sprintf(&temp[num], "%c", ',');
    }
    num += sprintf(&temp[num], "%c", '\n');
  }

  k = 0;
  while(temp[k] != '\0') {
      SEGGER_RTT_printf(0, "%c", temp[k]);
      k++;
  }

  MatrixXd_delete(matrix1);
  MatrixXd_delete(matrix2);
}

// this helper function takes a plain C array and prints it in one line
void print_array(double *array, int n)
{
  struct C_Map_MatrixXd *m = Map_MatrixXd_new(array, 1, n);
  Map_MatrixXd_print(m);
  Map_MatrixXd_delete(m);
}

void demo_Map_MatrixXd()
{
  struct C_Map_MatrixXd *map;
  double array[5];
  int i;
  SEGGER_RTT_printf(0, "*** demo_Map_MatrixXd ***\n");
  
  for(i = 0; i < 5; ++i) array[i] = i;
  SEGGER_RTT_printf(0, "Initially, the array is:\n");
  print_array(array, 5);
  
  map = Map_MatrixXd_new(array, 5, 1);
  Map_MatrixXd_add(map, map, map);
  Map_MatrixXd_delete(map);

  SEGGER_RTT_printf(0, "Now the array is:\n");
  print_array(array, 5);
}
