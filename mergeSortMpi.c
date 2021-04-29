#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *merge(int *array_first, int array_first_size, int *array_second, int array_second_size)// merge function
{
  int i = 0, j = 0, k = 0;
  int *result_array;

  result_array = (int *)malloc((array_first_size + array_second_size) * sizeof(int)); //Sum size array_first_size and array_second_size is a size of the main array for sorting
  while(i < array_first_size && j < array_second_size) { //while we have elements in first array and second array
    if(array_first[i] < array_second[j]) 
    { //if the number of elements in first array is lower than in the second array, put it to resultand  increment  i index
      result_array[k] = array_first[i];
      i++;
    }
    else 
    { //otherwise when the number of elements in second array is lower than in first array, put it to result and increment j index
      result_array[k] = array_second[j];
      j++;
    }
    k++; //increment result k index
  }

  if(i == array_first_size) 
  {//if first array is empty
    while(j < array_second_size) 
    { //while we have elements in second array
      result_array[k] = array_second[j];//put the rest of the second array elements into result
      j++;
      k++;
    }
  }
  else 
  { //oterwise when second array is empty
    while(i < array_first_size) { //while we have elements in first array
      result_array[k] = array_first[i];//put the rest of the first array elements to result
      i++;
      k++;
    }
  }
  return result_array;
}

int my_compare (const void * a, const void * b) //helper function for sort
{
    int _a = *(int*)a;
    int _b = *(int*)b;
    if(_a < _b) return -1;
    else if(_a == _b) return 0;
    else return 1;
}

int main(int argc, char  *argv[]) {

  int numtasks, rank; //number and id of the processes
  int part_size, *part, *part2, part2_size; //thwo smaller arrays which they're part of the general array and their sizes

  int i=0;
  double arr_size; //array size
  int *arr;
  int step = 0; // merge step number
  MPI_Status status;
  clock_t begin, end, begin_sort, end_sort;
  double during_time, time_sort;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
  

  if(rank == 0) 
  {
    scanf("%lf", &arr_size);
    srand(time(NULL));

    arr = (int *)malloc(arr_size * sizeof(int));

    for(i = 0; i < arr_size; i++) 
    { //generate random data and put them into array
      *(arr + i) = rand() % (int)arr_size;
    }

    if((int)arr_size % numtasks != 0) 
    {
      printf("The number of data to sort is not divisible by the number of processes.");
      MPI_Finalize();
      exit(1);
    } 
    else 
    {
      part_size = (int)(arr_size / numtasks); //calculate part array size
    }
  }

  begin = clock();

  MPI_Bcast(&part_size, 1, MPI_INT, 0, MPI_COMM_WORLD); //broadcast part size to processes

  part = (int *)malloc(part_size * sizeof(int));

  MPI_Scatter(arr, part_size, MPI_INT, part, part_size, MPI_INT, 0, MPI_COMM_WORLD); //send array items to processes

  begin_sort = clock();

  qsort(part, part_size, sizeof(int), my_compare); //sort arrays in processes

  end_sort = clock();
  time_sort += (double)(end_sort - begin_sort) / CLOCKS_PER_SEC;

  //Merging sorted arrays
  step = 1;
  while(step < numtasks) 
  {
    
    if(rank % (2 * step) == 0) 
    {

      if(rank + step < numtasks) 
      {

        MPI_Recv(&part2_size, 1, MPI_INT, rank + step, 0, MPI_COMM_WORLD, &status); //receive array size of neighbour process using MPI
        part2 = (int *)malloc(part2_size * sizeof(int));
        MPI_Recv(part2, part2_size, MPI_INT, rank + step, 0, MPI_COMM_WORLD, &status); //receive neighbour process array using MPI
        begin_sort = clock();
        part = merge(part, part_size, part2, part2_size); //merge n process array with n-step process array
        end_sort = clock();
        time_sort += (double)(end_sort - begin_sort) / CLOCKS_PER_SEC;
        part_size = part_size + part2_size; //increase array size
      }
    }
    
    else 
    {
      int nearest_process = rank - step; //calculate nearest process to send an array
      MPI_Send(&part_size, 1, MPI_INT, nearest_process, 0, MPI_COMM_WORLD); //array size to the nearest process
      MPI_Send(part, part_size, MPI_INT, nearest_process, 0, MPI_COMM_WORLD); //array to the nearest process
      break;
    }
    step = step * 2;
  }

  if(rank == 0) 
  {

    end = clock();
    during_time = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("Parallel time: %f\n", during_time);
    printf("Parallel sorting time: %f\n", time_sort);

    begin = clock();
    qsort(arr, arr_size, sizeof(int), my_compare); //sort the same array sequentially
    end = clock();
    during_time = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("Sequential sorting time: %f\n", during_time);

    FILE *output = fopen("sorted.data", "w");

    for(i = 0; i < part_size; i++) 
    {

      fprintf(output, "%d\n", part[i]); 
    }
    fclose(output);
  }

  MPI_Finalize();
  return 0;
}