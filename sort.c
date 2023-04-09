#include <time.h>
#include <stdlib.h>
#include <stdio.h>
//this is for extra memory
int extraMemoryAllocated;
//this is for wapping 
void swap(int arr[], int i, int j) {
  //int temp to array
    int tmp = arr[i];
  //array to array
    arr[i] = arr[j];
  //array to temp 
    arr[j] = tmp;
}
//this is heapify 
void heapify(int arr[], int n, int i) {
  //int largest 
    int largest = i;
  // left 
    int left = 2*i + 1;
  //right 
    int right = 2*i + 2;
    // if left is less than n and array to the left is larger
    if (left < n && arr[left] > arr[largest])
      //largest is left 
        largest = left;
      //if right is less than n and right is less than largest   
    if (right < n && arr[right] > arr[largest])
      //largest is right 
        largest = right;
        //if largest i not i
    if (largest != i) {
      //swap array i largest 
        swap(arr, i, largest);
      //heap array n to largest
        heapify(arr, n, largest);
    }
}
//this is heapsort 
void heapSort(int arr[], int n) {
  // for i
    int i;
  //memory allocated 
    extraMemoryAllocated = 0;
    // construction for heap
    for (i = n / 2 - 1; i >= 0; i--)
      //heapify for array n and i 
        heapify(arr, n, i);
    // standards for the heap
    for (i = n - 1; i >= 0; i--) {
        // move throughout the array
        swap(arr, 0, i);
        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}
//this is for merge 
void merge(int pData[], int l, int m, int r, int tmp[]) {
  // standards for i j and k
    int i = l, j = m+1, k = 0;
//while i is less than or equal to m and j is less thamn or equal to r 
    while (i <= m && j <= r) {
      // i is less than j 
        if (pData[i] < pData[j])
          //k plus 1 is equal to i plus 1
            tmp[k++] = pData[i++];
        else
          // all else k plus 1 is equal to j plus 1
            tmp[k++] = pData[j++];
    }
//while is is less than or equal to m
    while (i <= m)
      //temp k plua data i plua 1
        tmp[k++] = pData[i++];
//while j is less than or equal to r
    while (j <= r)
      //temp k plus 1 to j plus 1
        tmp[k++] = pData[j++];
    // copy towards to the data
    memcpy(pData + l, tmp, k * sizeof(int));
}
//this is for mergeSort
void mergeSort(int pData[], int l, int r) {
  //if 1 is less than r
    if (l < r) {
      // int m is 1 plus r minus 1 divided by 2
        int m = l + (r - l) / 2;
// mergesort for m
        mergeSort(pData, l, m);
      // mergesort for r
        mergeSort(pData, m+1, r);
        // merge the halves
        int tmp[r-l+1];
      //merge data for l m r and temp 
        merge(pData, l, m, r, tmp);
      //extra memory allocated
        extraMemoryAllocated += (r-l+1) * sizeof(int);
    }
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
  //file real and open input
	FILE* inFile = fopen(inputFileName,"r");
  //int data size ro 0
	int dataSz = 0;
  //int i n data
	int i, n, *data;
  //ppData is NULL
	*ppData = NULL;
//inFile 
	if (inFile)
	{
    //scan the files
		fscanf(inFile,"%d\n",&dataSz);
    //ppData to size amlloc
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// parse is NULL
		if (*ppData == NULL)
		{
      //print error 
			printf("Cannot allocate memory\n");
			exit(-1);
		}
    //standards
		for (i=0;i<dataSz;++i)
		{
      //scan the file
			fscanf(inFile, "%d ",&n);
      //data to Data plus i
			data = *ppData + i;
      //data to n
			*data = n;
		}
// close the file
		fclose(inFile);
	}
// return data size
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
  //int it size to data size minus 100
	int i, sz = dataSz - 100;
  //print Data 
	printf("\tData:\n\t");
  //i standards
	for (i=0;i<100;++i)
	{
    //print out the data
		printf("%d ",pData[i]);
	}
  //this print out the tab
	printf("\n\t");
// for i is size, is is less than dataS and iPlus 1
	for (i=sz;i<dataSz;++i)
	{
    //print out Data
		printf("%d ",pData[i]);
	}
  //tab down
	printf("\n\n");
}
//this is in main 
int main(void)
{
  // timer
	clock_t start, end;
 // int i 
	int i;
  //double cpu time 
    double cpu_time_used;
//imput files
	char* fileNames[] = { "input1.txt", "input2.txt", "input3.txt", "input4.txt" };
// i standards
	for (i=0;i<4;++i)
	{
    // datacopy
		int *pDataSrc, *pDataCopy;
    // data size to parseData
		int dataSz = parseData(fileNames[i], &pDataSrc);
//Data Size to 0
		if (dataSz <= 0)
      //to continue
			continue;
// copy to file size
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
//print border
		printf("---------------------------\n");
    //print Data size
		printf("Dataset Size : %d\n",dataSz);
    //border
		printf("---------------------------\n");
//print heap Sort
		printf("Heap Sort:\n");
    //copy data
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
    //extra memory allocated to 0 
		extraMemoryAllocated = 0;
    //clock
		start = clock();
    //data is copied in the heapSort
		heapSort(pDataCopy, dataSz);
    //end clock 
		end = clock();
    //cpu time used
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    //print run time 
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
    //print mmmory 
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
    //print the aeeay
		printArray(pDataCopy, dataSz);
// print Merge Sort
		printf("Merge Sort:\n");
    //copy to dataSize
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
    // memory to 0
		extraMemoryAllocated = 0;
    //start clock
		start = clock();
    //merge sort to data copy 
		mergeSort(pDataCopy, 0, dataSz - 1);
    //end the clock
		end = clock();
    //cpu time used 
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    //print runtime
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
    //print extra memory allocated
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
    //print the array that data is copied
		printArray(pDataCopy, dataSz);
//free data copy
		free(pDataCopy);
    //free the dataSrc
		free(pDataSrc);
	}

}
