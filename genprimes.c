#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h> 
#include <stdbool.h> 
#include <omp.h>


	

int main (int argc, char *argv[]) {
	double tstart = 0.0, tend = 0.0, ttaken;
	//read input from the command line
	char * fileName = argv[1];
	int N = atoi(argv[1]);
	int t = atoi(argv[2]);
	//creating a table of of numbers: 2,...,N
	int result[N-1];
	for (int i = 0 ; i < N-1 ; i++) {
		result[i] = i + 2;
	}

	tstart = omp_get_wtime();
	//generate prime numbers
	#pragma omp parallel for num_threads(t) \
		schedule(static, 1)
		for (int i = 0 ; i < N-1 ; i ++) {
			for (int j = 0 ; j < N-1 ; j ++) {
				if (result[i] != -1 && result[j] != -1) {
					if(result[i] < result[j] && result[j]%result[i]==0) {
						#pragma omp critical
						result[j] = -1;
					}
				}
			}
		}


	ttaken = omp_get_wtime() - tstart;
	printf("Time taken for the main part: %f\n", ttaken);


	//write output file and exit
    char * newfileName = strcat(fileName, ".txt");
	FILE * fptr;
	fptr = fopen(newfileName , "w");
	if (fptr == NULL) {
		printf("FIle did not open.\n");
	}
	int order = 1;
	int prev = 2;
	int diff = 0;
	for (int i = 0 ; i < N-1; i ++){
		int curr = result[i];
		if (curr != -1) {
			//printf("%d ", curr);
			diff = curr - prev;
			fprintf(fptr, "%d, %d, %d\n", order, curr, diff);
			order += 1;
			prev = curr;
		}
	}
	fclose(fptr);








}