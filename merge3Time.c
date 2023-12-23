#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

void mergeSort3(int *data, int size);
void merge3(int *data, int *a1, int s1, int *a2, int s2, int *a3, int s3);

void swap(int *d, int p1, int p2);
void _merge3helper(int *arr1, int *index1, int *arr2, int *index2, int *data, int count);
int min3(int a, int b, int c);


int main(int argc, char const *argv[]) {
	FILE *fp;
	int dataSize;
	int *data;
	int i;
	struct timeval stop, start;
	
	srand(time(NULL));

	for(i = 1; i <= 10; i++){
		dataSize = i*5000;

		data = (int *)malloc(dataSize * sizeof(int));

		for(int i = 0; i < dataSize; i++){
			data[i] = rand() %10001;
		}

		gettimeofday(&start, NULL);

		mergeSort3(data, dataSize);

		gettimeofday(&stop, NULL);

		printf("%.3f\n", (float)((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec)/(float)1000000);

		free(data);
	}
	return 0;
}


void mergeSort3(int *data, int size) {
	int excess = size%3;
	int size1;
	int size2;
	int size3;
	int *start1;
	int *start2;
	int *start3;

	switch(size){
	case 3:
		if(data[0] > data[1]) swap(data, 0, 1);
		if(data[1] > data[2]) swap(data, 1, 2);
		if(data[0] > data[1]) swap(data, 0, 1);
		break;
	case 2:
		if(data[0] > data[1]) swap(data, 0, 1);
		break;
	case 1:
		break;
	default:
		size1 = (excess> 0) ? size/3+1 : size/3;
		size2 = (excess==2) ? size/3+1 : size/3;
		size3 = size/3;

		start1 = data;
		start2 = data + size1;
		start3 = data + (size1 + size2);

		mergeSort3(start1, size1);
		mergeSort3(start2, size2);
		mergeSort3(start3, size3);

		merge3(data, start1, size1, start2, size2, start3, size3);

		break;
	}

}

void swap(int *d, int p1, int p2) {
	int temp = d[p1];
	d[p1] = d[p2];
	d[p2] = temp;
}

void merge3(int* data, int *a1, int s1, int *a2, int s2, int *a3, int s3){
	int c1 = 0;
	int c2 = 0;
	int c3 = 0;
	int min;
	int temp[s1+s2+s3];

	while(c1 < s1 || c2 < s2 || c3 < s3){
		if(c1 == s1 && c2 == s2){
			temp[c1+c2+c3] = a3[c3];
			c3++;
		} else if(c2 == s2 && c3 == s3){
			temp[c1+c2+c3] = a1[c1];
			c1++;
		} else if(c3 == s3 && c1 == s1){
			temp[c1+c2+c3] = a2[c2];
			c2++;
		} else if(c1 == s1)
			_merge3helper(a2, &c2, a3, &c3, temp, c1+c2+c3);
		else if(c2 == s2)
			_merge3helper(a3, &c3, a1, &c1, temp, c1+c2+c3);
		else if(c3 == s3)
			_merge3helper(a1, &c1, a2, &c2, temp, c1+c2+c3); 
		else{
			min = min3(a1[c1], a2[c2], a3[c3]);
			if(min == a1[c1]){
				temp[c1+c2+c3] = a1[c1];
				c1++;
			} else if(min == a2[c2]){
				temp[c1+c2+c3] = a2[c2];
				c2++;
			} else if(min == a3[c3]){
				temp[c1+c2+c3] = a3[c3];
				c3++;
			}
		}
	}
	for(int i = 0; i < s1+s2+s3; i++)
		data[i] = temp[i];
}

void _merge3helper(int * arr1, int *index1, int *arr2, int *index2, int *data, int count) {
	if(arr1[*index1] < arr2[*index2]){
		data[count] = arr1[*index1];
		*index1 = *index1 + 1;
	} else {
		data[count] = arr2[*index2];
		*index2 = *index2 + 1;
	}
}

int min3(int a, int b, int c) {
	if(a <= b && a <= c) return a;
	if(b <= a && b <= c) return b;
	return c;
}