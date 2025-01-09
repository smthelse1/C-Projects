#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int error = OK;

  if (rows <= 0 || columns <= 0) {
    error = INCORRECT_MATRIX;
  } else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)calloc(rows, sizeof(double *));
  }

  if (result->matrix == NULL) {
    error = INCORRECT_MATRIX;
  }
  for (int i = 0; i < rows; i++) {
    result->matrix[i] = (double *)calloc(columns, sizeof(double));
    if (result->matrix[i] == NULL) {
      error = INCORRECT_MATRIX;
      for (int j = 0; j < i; j++) {
        free(result->matrix[j]);
      }
      free(result->matrix);
      break;
    }
  }
  return error;
}

void s21_remove_matrix(matrix_t *A) {
  if (A->matrix != NULL) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
  }
  A->matrix = NULL;
  A->rows = 0;
  A->columns = 0;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int error = SUCCESS;
  if (!A || !B || (A->rows != B->rows) || (A->columns != B->columns))
    error = FAILURE;
  else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-07) {
          error = FAILURE;
          break;
        }
      }
    }
  }
  return error;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = OK;
  if (!s21_correct_matrix(A) && !s21_correct_matrix(B)) {
    if (A->columns == B->columns && A->rows == B->rows) {
      if (!s21_create_matrix(A->rows, A->columns, result))
        for (int i = 0; i < result->rows; i++) {
          for (int j = 0; j < result->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
          }
        }
      else
        error = CALCULATION_ERROR;
    } else
      error = INCORRECT_MATRIX;
  } else
    error = INCORRECT_MATRIX;
  return error;
}
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = OK;
  if (!s21_correct_matrix(A) && !s21_correct_matrix(B)) {
    if (A->columns == B->columns && A->rows == B->rows) {
      if (!s21_create_matrix(A->rows, A->columns, result))
        for (int i = 0; i < result->rows; i++) {
          for (int j = 0; j < result->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
          }
        }
      else
        error = CALCULATION_ERROR;
    } else
      error = INCORRECT_MATRIX;
  } else
    error = INCORRECT_MATRIX;
  return error;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int error = OK;
  if (!s21_correct_matrix(A)) {
    if (!s21_create_matrix(A->rows, A->columns, result))
      for (int i = 0; i < result->rows; i++) {
        for (int j = 0; j < result->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] * number;
        }
      }
    else
      error = CALCULATION_ERROR;
  } else
    error = INCORRECT_MATRIX;
  return error;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = OK;
  if (!s21_correct_matrix(A) && !s21_correct_matrix(B)) {
    if (A->columns == B->rows) {
      if (!s21_create_matrix(A->rows, B->columns, result)) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < B->columns; j++) {
            result->matrix[i][j] = 0;
            for (int k = 0; k < A->columns; k++) {
              result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
            }
          }
        }
      } else
        error = CALCULATION_ERROR;
    } else
      error = INCORRECT_MATRIX;
  } else
    error = INCORRECT_MATRIX;
  return error;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int error = OK;
  if (!s21_correct_matrix(A)) {
    if (!s21_create_matrix(A->columns, A->rows, result))
      for (int i = 0; i < result->rows; i++) {
        for (int j = 0; j < result->columns; j++) {
          result->matrix[j][i] = A->matrix[i][j];
        }
      }
    else
      error = CALCULATION_ERROR;
  } else
    error = INCORRECT_MATRIX;
  return error;
}

int s21_determinant(matrix_t *A, double *result) {
  int error = OK;
  if (error == OK) {
    if (A->rows == A->columns) {
      *result = s21_get_determinant(A);
    } else {
      error = CALCULATION_ERROR;
    }
  }
  return error;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int error = OK;
  if (error == OK) {
    if (A->rows == A->columns) {
      s21_create_matrix(A->columns, A->rows, result);
      matrix_t minor;
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
          s21_get_minor(A, &minor, i, j);
          double minor_det = s21_get_determinant(&minor);
          result->matrix[i][j] = pow(-1, i + j) * minor_det;
          s21_remove_matrix(&minor);
        }
      }
    } else
      error = INCORRECT_MATRIX;
  } else
    error = CALCULATION_ERROR;
  return error;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int error = OK;
  if (!A || (A->rows < 1) || (A->columns < 1) || !result)
    error = INCORRECT_MATRIX;
  else if (A->rows != A->columns)
    error = CALCULATION_ERROR;
  else {
    double det = 0.0;
    s21_determinant(A, &det);
    if (fabs(det) < 1e-07)
      error = CALCULATION_ERROR;
    else if (A->rows == 1) {
      s21_create_matrix(1, 1, result);
      result->matrix[0][0] = (1 / det);
    } else {
      matrix_t complements, transposed;
      s21_calc_complements(A, &complements);
      s21_transpose(&complements, &transposed);
      s21_remove_matrix(&complements);
      s21_mult_number(&transposed, (1.0 / det), result);
      s21_remove_matrix(&transposed);
    }
  }
  return error;
}

// HELP_FUNC
int s21_correct_matrix(matrix_t *A) {
  int error = OK;
  if (A == NULL || A->matrix == NULL || A->columns == 0 || A->rows == 0)
    error = INCORRECT_MATRIX;
  return error;
}

double s21_get_determinant(matrix_t *A) {
  double det = 0.0;
  int rows = A->rows;

  if (rows == 1) {
    det = A->matrix[0][0];
  } else if (rows == 2) {
    det = A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  } else {
    for (int p = 0; p < rows; p++) {
      matrix_t minor;
      s21_create_matrix(rows - 1, rows - 1, &minor);
      s21_get_minor(A, &minor, 0, p);
      double minor_det = s21_get_determinant(&minor);
      det += A->matrix[0][p] * minor_det * ((p % 2 == 0) ? 1 : -1);
      s21_remove_matrix(&minor);
    }
  }

  return det;
}

void s21_get_minor(matrix_t *A, matrix_t *minor, int row, int col) {
  int minor_i = 0, minor_j = 0;
  for (int i = 0; i < A->rows; i++) {
    if (i == row) continue;
    minor_j = 0;
    for (int j = 0; j < A->columns; j++) {
      if (j == col) continue;
      minor->matrix[minor_i][minor_j] = A->matrix[i][j];
      minor_j++;
    }
    minor_i++;
  }
}