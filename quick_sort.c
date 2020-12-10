/******************************************************************************

Program to sort an array using quick sort algorithm.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

// Method to swap two numbers.
void swap(int *first_number, int *second_number)
{
    int temp_number = *first_number;
    *first_number = *second_number;
    *second_number = temp_number;
}

// Partion the array and return the partitioning index.
int partition(int arr[], int low_index, int high_index)
{
    // Select first element as pivot. NOTE : We can select any number as pivot.
    int pivot = arr[low_index];
    int i = low_index;
    int j = high_index + 1;
    
    while(i < j)
    {
        // Find the number greater than pivot.
        while(((++i) < j) && (arr[i] < pivot));
        
        // Find the number smaller than pivot.
        while(((--j) > low_index) && (arr[j] > pivot));
    
        // If i and j have crossed than break the loop and don't swap elements.
        if(i >= j)
            break;
        
        // Swap the number greater than pivot with the number smaller than pivot.
        swap(&arr[i], &arr[j]);
    }
    
    if(j != low_index)
    {
        // At the end swap the pivot element with the number at position j. 
        // After this, all the numbers on left of j would be smaller than pivot 
        // and all the numbers on right of j would be larger than pivot.
        swap(&arr[j], &arr[low_index]);
    }
    
    // Return the partitioning index.
    return j;
}

// Quick sort method to be called recursively.
int quick_sort(int arr[], int low_index, int high_index)
{
    // Stores the partition index.
    int partition_index = 0;
    
    if(low_index < high_index)
    {
        // Get the partitioning index
        partition_index = partition(arr, low_index, high_index);
        
        // Sort the left half of array after partition
        quick_sort(arr, low_index, partition_index - 1);
        
        // Sort the Right half of array after partition
        quick_sort(arr, partition_index + 1, high_index);
    }
}

// Display the array elements.
void display_elements(int *arr, int length)
{
    int i = 0;
    
    for(; i < length; i++)
        printf("%d\t", *(arr + i));
}

// Driver method
int main()
{
    int length = 0;
    int *arr = NULL;
    int i = 0;
    
    printf("Enter number of elements in array : ");
    scanf("%d", &length);
    
    if(length <= 0)
    {
        printf("\nArray length can only be a positive integer.");
        return 0;
    }
    
    // Allocate memory for the array.
    arr = malloc(length * sizeof(int));
    if(arr == NULL)
    {
        printf("\nMemory allocation failed. Terminating program......");
        return 0;
    }
    
    printf("\nEnter elements of array : \n");
    for(i = 0; i < length; i++)
        scanf("%d", (arr + i));
    
    quick_sort(arr, 0, length - 1);
    
    display_elements(arr, length);

    free(arr);
    
    return 0;
}
