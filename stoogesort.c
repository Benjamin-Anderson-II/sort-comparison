#include <stdio.h>
#include <stdlib.h>

void stoogeCall(int *data, int size);
void stoogeSort(int *data, int size);
void swap(int *d, int p1, int p2);

int main(int argc, char const *argv[]) {
	FILE *fp;
	int dataSize;
	int *data;

	fp = fopen("./data.txt", "r");

	while(1){
		fscanf(fp, "%d", &dataSize);
		if(feof(fp)) break;
		data = (int *)malloc(dataSize * sizeof(int));

		for(int i = 0; i < dataSize; i++)
			fscanf(fp, " %d", &data[i]);

		stoogeSort(data, dataSize);

		for(int i = 0; i < dataSize; i++) printf("%d ", data[i]);
		printf("\n");
	
		free(data);
	}
	fclose(fp);
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