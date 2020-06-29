/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Then, this project's includes, alphabetically ordered */
#include "array_helpers.h"

/* Maximum allowed length of the array */
static const unsigned int MAX_SIZE = 100000u;

void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n"
           "Save an array given in a file in disk.\n"
           "\n"
           "The input file must have the following format:\n"
           " * The first line must contain only a positive integer,"
           " which is the length of the array.\n"
           " * The second line must contain the members of the array"
           " separated by one or more spaces. Each member must be an integer."
           "\n\n"
           "In other words, the file format is:\n"
           "<amount of array elements>\n"
           "<array elem 1> <array elem 2> ... <array elem N>\n\n",
           program_name);
}

//auxiliary function that checks the existence of the peak (if sorted)
bool has_peak(int a[],int length,int peak)
{   
    int A = true;
    //is increasing?
    for (int i = 0; i < peak; i++){
        if (a[i] >= a[i+1]){
            return false;
        }
    }
    //is decreasing?
    for (int j = (length-1); j > peak; j--){
        if (a[j] >= a[j-1]){
            return false;
        }
    }

 return A; 

} 

// Ej 1: Funtion that finds the peak on the array, if it does not exist, return -1
int array_peak_sequential(int a[], int length){
  int peak=0, max=0;
  for (int i = 0; i < length; i++)
  {
         if (a[i] > max){
			  max = a[i];
		      peak = i;
        }
  }

  if ((has_peak(a,length,peak)) && (length>1)) //one or no element, has no peak 
  {
      return peak; //if has peak, returns the peak index
  } else
  {
      return -1;
  }
}

//auxiliary function that gets the peak recursively
int binary_search_rec(int a[], int lft, int rgt)
{   
    int mid = 0;
    if(lft > rgt){
        return -1;
    }
    else if(lft == rgt){
        return rgt;
    }
    else if(lft < rgt){   
        mid = (lft+rgt)/2;
        
        if ((a[mid] > a[mid-1]) && (a[mid] > a[mid+1]))
        {   
            return mid;
        }
        if(a[mid]<a[mid+1] )
        {
            return binary_search_rec(a, mid, rgt);
        }
        if(a[mid]<a[mid-1])
        {
            return binary_search_rec(a, lft, mid);
        } 
    }
    return -1;
}

// Ej 2: Funtion that finds the peak on the array, if it does not exist, return -1
int array_peak_binary(int a[], int length) {
    int i = binary_search_rec(a, 0, length);

    if ((has_peak(a,length,i)) && (length>1)) //one or no element, has no peak 
    {
        return i; //if has peak, returns the peak index
    } else
    {
        return -1;
    }
}

char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;

    if (argc < 2) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return (result);
}

int main(int argc, char *argv[]) {
  char *filepath = NULL;

  /* parse the filepath given in command line arguments */
  filepath = parse_filepath(argc, argv);

  /* create an array of MAX_SIZE elements */
  int array[MAX_SIZE];

  /* parse the file to fill the array and obtain the actual length */
  unsigned int length = array_from_file(array, MAX_SIZE, filepath);

  /* show the ordered array in the screen */
  array_dump(array, length);

  int this_is_the_peak = array_peak_sequential(array, length);
  printf("The peak is: %d\n", this_is_the_peak);

  //TODO: Uncomment this to do part b
  int this_is_the_binary_peak = array_peak_binary(array, length);
  printf("The peak (by binary search) is: %d\n", this_is_the_binary_peak);

  return (1);
}
