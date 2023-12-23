#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

void stoogeCall(int *data, int size);
void stoogeSort(int *data, int size);
void swap(int *d, int p1, int p2);

int main(int argc, char const *argv[]) {
	int dataSize;
	int *data;
	struct timeval stop, start;

	srand(time(NULL));

	for(int i = 1; i <= 10; i++){
		dataSize = i*5000;

		data = (int *)malloc(dataSize * sizeof(int));

		for(int i = 0; i < dataSize; i++){
			data[i] = rand() %10001;
		}

		gettimeofday(&start, NULL);

		stoogeSort(data, dataSize);

		gettimeofday(&stop, NULL);

		printf("%lu\n", (stop.tv_sec-start.tv_sec)*(int)1e6 + stop.tv_usec-start.tv_usec);
	
		free(data);
	}
	return 0;
}

void stoogeSort(int *data, int size){
	if(data[0] > data[size-1]) swap(data, 0, size-1);
	if(size < 3) return;
	stoogeSort(data, (2*size+2)/3);
	stoogeSort(data + (size/3), (2*size+2)/3);
	stoogeSort(data, (2*size+2)/3);
}

void swap(int *d, int p1, int p2) {
	int temp = d[p1];
	d[p1] = d[p2];
	d[p2] = temp;
}