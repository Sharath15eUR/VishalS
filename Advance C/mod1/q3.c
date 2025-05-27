#include <stdio.h>
#include <stdbool.h>

bool searchMatrix(int n, int matrix[n][n], int key) {
    int row = 0;
    int col = n - 1;  // Start from the top-right corner

    while (row < n && col >= 0) {
        if (matrix[row][col] == key) {
            return true;
        } else if (matrix[row][col] > key) {
            col--;  // Move left
        } else {
            row++;  // Move down
        }
    }

    return false;
}

int main() {
    int n, key;

    printf("Enter size of matrix (n x n): ");
    scanf("%d", &n);

    int matrix[n][n];

    printf("Enter elements of the matrix (row-wise, sorted):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    printf("Enter key to search: ");
    scanf("%d", &key);

    if (searchMatrix(n, matrix, key)) {
        printf("Key %d found in the matrix.\n", key);
    } else {
        printf("Key %d not found in the matrix.\n", key);
    }

    return 0;
}
