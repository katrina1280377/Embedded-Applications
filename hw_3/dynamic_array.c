#include "dynamic_array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

DynamicArray** allocated_arrays = NULL;
int num_allocated_arrays = 0;

/* private functions *********************************************************/

/* Position in the buffer of the array element at position index */
static int index_to_offset ( const DynamicArray * da, int index ) {
    return index + da->origin;
}

/* Position of the element at buffer position 'offset' */
static int offset_to_index ( const DynamicArray * da, int offset ) {
    return offset - da->origin;
}

/* Non-zero if and only if offset lies ouside the buffer */
static int out_of_buffer ( DynamicArray * da, int offset ) {
    return offset < 0 || offset >= da->capacity;
}

/* Makes a new buffer that is twice the size of the old buffer,
   copies the old information into the new buffer, and deletes
   the old buffer */
static void extend_buffer ( DynamicArray * da ) {

    double * temp = (double *) calloc ( 2 * da->capacity, sizeof(double) );
    int new_origin = da->capacity - (da->end - da->origin)/2,
           new_end = new_origin + (da->end - da->origin);

    for ( int i=0; i<DynamicArray_size(da); i++ ) {
        temp[new_origin+i] = DynamicArray_get(da,i);
    }

    free(da->buffer);
    da->buffer = temp;

    da->capacity = 2 * da->capacity;
    da->origin = new_origin;
    da->end = new_end;

    return;

}

/* public functions **********************************************************/

DynamicArray * DynamicArray_new(void) {
    DynamicArray * da = (DynamicArray *) malloc(sizeof(DynamicArray));
    da->capacity = DYNAMIC_ARRAY_INITIAL_CAPACITY;    
    da->buffer = (double *) calloc ( da->capacity, sizeof(double) ); 
    da->origin = da->capacity / 2;
    da->end = da->origin;

    allocated_arrays = (DynamicArray**)realloc(allocated_arrays, sizeof(DynamicArray*) * (num_allocated_arrays + 1));
    allocated_arrays[num_allocated_arrays] = da;
    num_allocated_arrays++;
    return da;
}

void DynamicArray_destroy(DynamicArray * da) {
    free(da->buffer);
    da->buffer = NULL;
    // Find and remove da from allocated_arrays
    int index = -1;
    for (int i = 0; i < num_allocated_arrays; i++) {
        if (allocated_arrays[i] == da) {
            index = i;
            break;
        }
    }
    if (index != -1) {
        for (int i = index; i < num_allocated_arrays - 1; i++) {
            allocated_arrays[i] = allocated_arrays[i + 1];
        }
        num_allocated_arrays--;
        allocated_arrays = (DynamicArray**)realloc(allocated_arrays, sizeof(DynamicArray*) * num_allocated_arrays);
    }
}

int DynamicArray_size(const DynamicArray * da) {
    assert(da->buffer != NULL);
    return da->end - da->origin;
}

char * DynamicArray_to_string(const DynamicArray * da) {
    assert(da->buffer != NULL);
    char * str = (char *) calloc (20,DynamicArray_size(da)),
         temp[20];
    int j = 1;
    str[0] = '[';
    for ( int i=0; i < DynamicArray_size(da); i++ ) {
        if ( DynamicArray_get(da,i) == 0 ) {
            snprintf ( temp, 20, "0" );
        } else {
            snprintf ( temp, 20, "%.5lf", DynamicArray_get(da,i) ); 
        }
        if ( i < DynamicArray_size(da) - 1 ) {
            sprintf( str + j, "%s,", temp);
            j += strlen(temp) + 1;
        } else {
            sprintf( str + j, "%s", temp);
            j += strlen(temp);
        }

    }
    str[j] = ']';
    return str;
}

void DynamicArray_print_debug_info(const DynamicArray * da) {

    char * s = DynamicArray_to_string(da);
    printf ( "  %s\n", s);
    printf ( "  capacity: %d\n  origin: %d\n  end: %d\n  size: %d\n\n",
      da->capacity, 
      da->origin, 
      da->end,
      DynamicArray_size(da));

    free(s);

}

void DynamicArray_set(DynamicArray * da, int index, double value) {
    assert(da->buffer != NULL);
    assert ( index >= 0 );
    while ( out_of_buffer(da, index_to_offset(da, index) ) ) {
        extend_buffer(da);
    }
    da->buffer[index_to_offset(da, index)] = value;
    if ( index >= DynamicArray_size(da) ) {
        da->end = index_to_offset(da,index+1);
    }

}

double DynamicArray_get(const DynamicArray * da, int index) {
    assert(da->buffer != NULL);
    assert ( index >= 0 );
    if ( index >= DynamicArray_size(da) ) {
        return 0;
    } else {
        return da->buffer[index_to_offset(da,index)];
    }
}

void DynamicArray_push(DynamicArray * da, double value ) {
    DynamicArray_set(da, DynamicArray_size(da), value );
}

void DynamicArray_push_front(DynamicArray * da, double value) {
    assert(da->buffer != NULL);
    while ( da->origin == 0 ) {
        extend_buffer(da);
    }
    da->origin--;
    DynamicArray_set(da,0,value);
}

double DynamicArray_pop(DynamicArray * da) {
    assert(DynamicArray_size(da) > 0);
    double value = DynamicArray_get(da, DynamicArray_size(da)-1);
    DynamicArray_set(da, DynamicArray_size(da)-1, 0.0);
    da->end--;
    return value;
}

double DynamicArray_pop_front(DynamicArray * da) {
    assert(DynamicArray_size(da) > 0);
    double value = DynamicArray_get(da, 0);
    da->origin++;
    return value;    
}

DynamicArray * DynamicArray_map(const DynamicArray * da, double (*f) (double)) {
    assert(da->buffer != NULL);
    DynamicArray * result = DynamicArray_new();
    for ( int i=0; i<DynamicArray_size(da); i++ ) {
        DynamicArray_set(result, i, f(DynamicArray_get(da, i)));
    }
    return result;
}

DynamicArray * DynamicArray_subarray(DynamicArray * da, int a, int b) {

  assert(da->buffer != NULL);
  assert(b >= a);

  DynamicArray * result = DynamicArray_new();

  for (int i=a; i<b; i++) {
      DynamicArray_push(result,DynamicArray_get(da, i));
  }

  return result;

}

// HW_3 CODING STARTS HERE
// Part 1 - Mathematical operations
double DynamicArray_min ( const DynamicArray * da ) {
    assert(da->buffer != NULL && DynamicArray_size(da) > 0);
    double min_val = da->buffer[da->origin];
    for (int i = 1; i < DynamicArray_size(da); i++) {
        if (da->buffer[da->origin + i] < min_val) {
            min_val = da->buffer[da->origin + i];
        }
    }
    return min_val;
}

double DynamicArray_max ( const DynamicArray * da ) {
    assert(da->buffer != NULL && DynamicArray_size(da) > 0);
    double max_val = da->buffer[da->origin];
    for (int i = 1; i < DynamicArray_size(da); i++) {
        if (da->buffer[da->origin + i] > max_val) {
            max_val = da->buffer[da->origin + i];
        }
    }
    return max_val;
}

double DynamicArray_mean ( const DynamicArray * da ) {
    assert(da->buffer != NULL && DynamicArray_size(da) > 0);
    double sum = 0;
    for (int i = 0; i < DynamicArray_size(da); i++) {
        sum += da->buffer[da->origin + i];
    }
    return sum / DynamicArray_size(da);
}

double DynamicArray_median ( const DynamicArray * da ) {
    assert(da->buffer != NULL && DynamicArray_size(da) > 0);
    double* temp = (double*) malloc(DynamicArray_size(da) * sizeof(double));
    memcpy(temp, da->buffer + da->origin, DynamicArray_size(da) * sizeof(double));
    int size = DynamicArray_size(da);
    selectionSort(temp, size);
    double median;
    if (size % 2 == 0) {
        median = (temp[size / 2 - 1] + temp[size / 2]) / 2;
    } else {
        median = temp[size / 2];
    }
    free(temp);
    return median;
}

double DynamicArray_sum ( const DynamicArray * da ) {
    assert(da->buffer != NULL);
    double sum = 0;
    for (int i = 0; i < DynamicArray_size(da); i++) {
        sum += da->buffer[da->origin + i];
    }
    return sum;
}

void selectionSort(double* arr, int n) {
    int i, j, min_idx;
    double min_val;
    for (i = 0; i < n-1; i++) {
        min_idx = i;
        min_val = arr[i];
        for (j = i+1; j < n; j++) {
            if (arr[j] < min_val) {
                min_idx = j;
                min_val = arr[j];
            }
        }
        if (min_idx != i) {
            arr[min_idx] = arr[i];
            arr[i] = min_val;
        }
    }
}

// Part 2 - Write the methods _last and _first return the value at the end 
// or beginning of the array respectively.
double DynamicArray_last ( const DynamicArray * da ) {
    assert(da->buffer != NULL && DynamicArray_size(da) > 0);
    return da->buffer[da->origin + DynamicArray_size(da) - 1];
}

double DynamicArray_first ( const DynamicArray * da ) {
    assert(da->buffer != NULL && DynamicArray_size(da) > 0);
    return da->buffer[da->origin];
}

// Part 3 - Write a _copy method that produces a copy of an array.
DynamicArray * DynamicArray_copy ( const DynamicArray * da ) {
    assert(da->buffer != NULL);
    DynamicArray * copy = DynamicArray_new();
    for (int i = 0; i < DynamicArray_size(da); i++) {
        DynamicArray_push(copy, DynamicArray_get(da, i));
    }
    return copy;
}

// Part 4- Write a method called _range that creates a new dynamic array with values as follows.
DynamicArray * DynamicArray_range(double a, double b, double step) {
    DynamicArray * da = DynamicArray_new();
    int steps = round((b - a) / step);
    for (int i = 0; i <= steps; i++) {
        double value = a + i * step;
        DynamicArray_push(da, value);
    }
    return da;
}

// Part 5- Implement the method _concat, which concatenates two arrays to produce a new array.
DynamicArray * DynamicArray_concat(const DynamicArray * a, const DynamicArray * b) {
    assert(a->buffer != NULL && b->buffer != NULL);
    DynamicArray * concat = DynamicArray_new();
    for (int i = 0; i < DynamicArray_size(a); i++) {
        DynamicArray_push(concat, DynamicArray_get(a, i));
    }
    for (int i = 0; i < DynamicArray_size(b); i++) {
        DynamicArray_push(concat, DynamicArray_get(b, i));
    }
    return concat;
}

// Part 6 - Implement a method called _take that returns a sub-array of n elements.
DynamicArray * DynamicArray_take(const DynamicArray * da, int n) {
    assert(da->buffer != NULL);
    DynamicArray * result = DynamicArray_new();
    int size = DynamicArray_size(da);
    int count = abs(n);
    if (n > 0) {
        for (int i = 0; i < count; i++) {
            if (i < size) {
                DynamicArray_push(result, DynamicArray_get(da, i));
            } else {
                DynamicArray_push(result, 0);
            }
        }
    } else {
        int start = size - count > 0 ? size - count : 0;
        for (int i = start; i < start + count; i++) {
            if (i < size) {
                DynamicArray_push(result, DynamicArray_get(da, i));
            } else {
                DynamicArray_push(result, 0);
            }
        }
    }
    return result;
}

// Part 7 - Create a method _is_valid that determines whether an array has been deallocated or not.
int DynamicArray_num_arrays() {
    return num_allocated_arrays;
}

void DynamicArray_destroy_all() {
    for (int i = 0; i < num_allocated_arrays; i++) {
        DynamicArray_destroy(allocated_arrays[i]);
    }
    free(allocated_arrays);
    allocated_arrays = NULL;
    num_allocated_arrays = 0;
}

int DynamicArray_is_valid(const DynamicArray * da) {
    return da->buffer != NULL;
}