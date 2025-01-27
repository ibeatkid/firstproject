#include <windows.h>
#include <stdio.h>

typedef struct {
    double m[3][3];
} Matrix3;

// Thread argument structure
typedef struct {
    Matrix3* A;
    Matrix3* B;
    Matrix3* result;
    int start_row;
    int end_row;
} ThreadArg;

// Thread function to compute part of the matrix
DWORD WINAPI thread_function(LPVOID arg) {
    ThreadArg* data = (ThreadArg*)arg;
    Matrix3* A = data->A;
    Matrix3* B = data->B;
    Matrix3* result = data->result;

    for (int i = data->start_row; i < data->end_row; i++) {
        for (int j = 0; j < 3; j++) {
            result->m[i][j] = 0.0;
            for (int k = 0; k < 3; k++) {
                result->m[i][j] += A->m[i][k] * B->m[k][j];
            }
        }
    }

    return 0;
}

int main() {
    // Fetch number of cores
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    int num_cores = sysinfo.dwNumberOfProcessors;
    printf("Number of cores: %d\n", num_cores);

    // Matrices for multiplication
    Matrix3 A = { .m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}} };
    Matrix3 B = { .m = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}} };
    Matrix3 result = {0};

    // Create threads
    HANDLE* threads = (HANDLE*)malloc(num_cores * sizeof(HANDLE));
    ThreadArg* thread_args = (ThreadArg*)malloc(num_cores * sizeof(ThreadArg));

    int rows_per_thread = 3 / num_cores;
    int extra_rows = 3 % num_cores;

    int current_row = 0;
    for (int i = 0; i < num_cores; i++) {
        thread_args[i].A = &A;
        thread_args[i].B = &B;
        thread_args[i].result = &result;
        thread_args[i].start_row = current_row;
        thread_args[i].end_row = current_row + rows_per_thread + (i < extra_rows ? 1 : 0);
        current_row = thread_args[i].end_row;

        threads[i] = CreateThread(
            NULL, 0, thread_function, &thread_args[i], 0, NULL
        );

        if (threads[i] == NULL) {
            printf("Error creating thread %d\n", i + 1);
            return 1;
        }
    }

    // Wait for all threads to finish
    WaitForMultipleObjects(num_cores, threads, TRUE, INFINITE);

    // Close thread handles
    for (int i = 0; i < num_cores; i++) {
        CloseHandle(threads[i]);
    }

    // Print the result matrix
    printf("Resultant Matrix:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%9.3f ", result.m[i][j]);
        }
        printf("\n");
    }

    // Free resources
    free(threads);
    free(thread_args);

    return 0;
}