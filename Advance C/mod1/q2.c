#include <stdio.h>
#include <stdlib.h>

void rearrangeEvenOdd(int *arr, int size) {
    int *temp = (int *)malloc(size * sizeof(int));
    int *evenPtr = temp;
    int *oddPtr = temp;

    int evenCount = 0;

    for (int i = 0; i < size; i++) {
        if (*(arr + i) % 2 == 0) {
            *(evenPtr + evenCount) = *(arr + i);
            evenCount++;
        }
    }

    int oddCount = evenCount;

    for (int i = 0; i < size; i++) {
        if (*(arr + i) % 2 != 0) {
            *(oddPtr + oddCount) = *(arr + i);
            oddCount++;
        }
    }

    for (int i = 0; i < size; i++) {
        *(arr + i) = *(temp + i);
    }

    free(temp);
}

int main() {
    int arr[] = {1, 2, 4, 7, 6, 3, 8};
    int size = sizeof(arr) / sizeof(arr[0]);

    rearrangeEvenOdd(arr, size);

    for (int i = 0; i < size; i++) {
        printf("%d ", *(arr + i));
    }

    return 0;
}
