#ifndef LinearA
#define LinearA

#include <stdlib.h> // Provides malloc, free, and other memory functions
#include <stddef.h> // Provides NULL definition

typedef struct {
    int dimension;
    double *components;
} Vector;

// Create a new vector with specified dimension
Vector create_vector(int dimension) {
    double* vec = (double*) malloc(dimension * sizeof(double));
    Vector v;
    v.components=vec;
    return v;
}

// Free vector memory
void free_vector(Vector vec) {
  free(vec.components);
}

// Add two vectors
Vector vector_add(Vector a, Vector b) {
    Vector result = {0, NULL};
    if (a.dimension != b.dimension) return result;

    result = create_vector(a.dimension);
    for (int i = 0; i < a.dimension; i++) {
        result.components[i] = a.components[i] + b.components[i];
    }
    return result;
}

// Struct for a matrix
typedef struct {
    int column;
    int row;
    double **matrix;
} Matrix;



// Function to add two matrices
Matrix matrix_add(Matrix matrixA, Matrix matrixB) {
   // Ensure matrices have the same dimensions
    if (matrixA.row != matrixB.row || matrixA.column != matrixB.column) {
        Matrix errorMatrix = {0, 0, NULL};
        return errorMatrix; // Return an empty matrix to signal an error
    }

    // Initialize the resulting matrix
    Matrix result;
    result.row = matrixA.row;
    result.column = matrixA.column;
    result.matrix = (double **)malloc(result.row * sizeof(double *));
    if (!result.matrix) {
        Matrix errorMatrix = {0, 0, NULL};
        return errorMatrix;
    }

    for (int i = 0; i < result.row; i++) {
        result.matrix[i] = (double *)malloc(result.column * sizeof(double));
        if (!result.matrix[i]) {
            // Free previously allocated memory on failure
            for (int j = 0; j < i; j++) {
                free(result.matrix[j]);
            }
            free(result.matrix);
            Matrix errorMatrix = {0, 0, NULL};
            return errorMatrix;
        }
    }

    // Perform element-wise addition
    for (int i = 0; i < result.row; i++) {
        for (int j = 0; j < result.column; j++) {
            result.matrix[i][j] = matrixA.matrix[i][j] + matrixB.matrix[i][j];
        }
    }

    return result;
}
Matrix matrixmul(Matrix A, Matrix B) {
    // Check if matrices can be multiplied
    if (A.column != B.row) {
        Matrix errorMatrix = {0, 0, NULL};
        return errorMatrix; // Return an empty matrix if multiplication is not possible
    }

    // Initialize the resulting matrix
    Matrix result;
    result.row = A.row;
    result.column = B.column;
    result.matrix = (double **)malloc(result.row * sizeof(double *));
    if (!result.matrix) {
        Matrix errorMatrix = {0, 0, NULL};
        return errorMatrix;
    }

    // Allocate memory for each row of the result matrix
    for (int i = 0; i < result.row; i++) {
        result.matrix[i] = (double *)malloc(result.column * sizeof(double));
        if (!result.matrix[i]) {
            // Free previously allocated memory on failure
            for (int j = 0; j < i; j++) {
                free(result.matrix[j]);
            }
            free(result.matrix);
            Matrix errorMatrix = {0, 0, NULL};
            return errorMatrix;
        }
    }

    // Perform matrix multiplication
    for (int i = 0; i < result.row; i++) {
        for (int j = 0; j < result.column; j++) {
            result.matrix[i][j] = 0.0; // Initialize to zero
            for (int k = 0; k < A.column; k++) {
                result.matrix[i][j] += A.matrix[i][k] * B.matrix[k][j];
            }
        }
    }

    return result;
}
Vector eigenval(Matrix A)
{

}
#endif 

