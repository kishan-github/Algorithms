/******************************************************************************

Program to sort an array using merge sort algorithm.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

// Macro to free the allocated memory.
#define FREE(ptr)	\
	free(ptr);		\
	ptr = NULL;

// Enum to store the status returned by a method.
typedef enum status 
{
    SUCCESS,
    FAILURE
}status_t;

/* 
	Merge the two sorted arrays.

	left sorted array : low_index to mid_index
	
	right sorted array : mid_index + 1 to high_index
*/
status_t merge(int arr[], int low_index, int mid_index, int high_index)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int length_of_left_array  = mid_index - low_index + 1;
    int length_of_right_array = high_index - mid_index;
    int *left_arr  = NULL;
    int *right_arr = NULL;
    
	// Allocate memory to store the elements of left array.
    left_arr = malloc((length_of_left_array) * sizeof(int));
    if(left_arr == NULL)
    {
        printf("\nMemory allocation of left_arr failed.");
        return FAILURE;
    }
    
	// Allocate memory to store the elements of right array.
    right_arr = malloc((length_of_right_array) * sizeof(int));
    if(right_arr == NULL)
    {
        printf("\nMemory allocation of right_arr failed.");
        FREE(left_arr);
        return FAILURE;
    }
    
	// Copy the elements from given array to the temporary left array.
    for(i = 0; i < length_of_left_array; i++)
        *(left_arr + i) = arr[low_index + i];
    
	// Copy the elements from given array to the temporary right array.
    for(i = 0; i < length_of_right_array; i++)
        *(right_arr + i) = arr[mid_index + i + 1];
    
	// Compare the elements from left and right arrays and store in main array in sorted order.
    for(i = 0, j = 0, k = low_index; 
	   (i < length_of_left_array) && (j < length_of_right_array); 
	    k++)
    {
        if(*(left_arr + i) < *(right_arr + j))
        {
            arr[k] = *(left_arr + i);
            i++;
        }
        else
        {
            arr[k] = *(right_arr + j);
            j++;
        }
    }
    
	// Copy the remaining elements from left array to main array.
    while(i < length_of_left_array)
    {
        arr[k++] = *(left_arr + i);
        i++;
    }
    
	// Copy the remaining elements from right array to main array.
    while(j < length_of_right_array)
    {
        arr[k++] = *(right_arr + j);
        j++;
    }

	// Free the memory allocated to temporary arrays.
	FREE(left_arr);
	FREE(right_arr);
	
	return SUCCESS;
}

// Divide the array in two parts, sort each part and merge them in sorted order.
status_t merge_sort(int arr[], int low_index, int high_index)
{
    int mid_index = 0;
    
    if(low_index < high_index)
    {
		// Divide in two parts.
        mid_index = (low_index + high_index) / 2;
		
		// Sort left half.
        if(merge_sort(arr, low_index, mid_index) == FAILURE)
        {
            printf("Failed in merge_sort method.\n");
            return FAILURE;
        }
		
		// Sort right half.
        if(merge_sort(arr, mid_index + 1, high_index) == FAILURE)
        {
            printf("Failed in merge_sort method.\n");
            return FAILURE;
        }
		
		// Merge the sorted left and right half.
        if(merge(arr, low_index, mid_index, high_index) == FAILURE)
        {
            printf("Failed in merge method.\n");
            return FAILURE;
        }
    }
    
    return SUCCESS;
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
    
    if(merge_sort(arr, 0, length - 1) == FAILURE)
    {
        printf("Something went wrong. Terminating the program......");
        FREE(arr);
        return 0;
    }
    
    display_elements(arr, length);
	
	  FREE(arr);

    return 0;
}
