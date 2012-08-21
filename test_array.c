

#include <stdlib.h>
#include <stdio.h>
#include "array.h"

struct client_t {
	int id;
	char name;
	void * data;
	float digits[3];
};

int
main(int argc, char **argv) {

	int i, *data;
	array_t * arr;
	
	int ntest, nfailure;
	ntest = 0;
	nfailure = 0;

	/* test 1: test for array_create */
	ntest++;
	arr = array_create(5,sizeof(int));
	if (arr == NULL) nfailure++;
	for (i = 0; i < 10000; i++) {
		data = (int*)array_push(arr);
		*data = i;
		fprintf(stdout, "insert %d, \
				current length of array is %d\n",
				*(int*)array_at(arr,i), array_len(arr));
	}
	array_free(arr);

	/* test 2: test for array_create which size is equal to 0 */
	ntest++;
	arr = array_create(0,sizeof(double));
	if (arr == NULL) nfailure++;
	array_free(arr);

	/* test 3: test for array operations in term of struct */
	ntest++;
	struct client_t *pclient, *at;
	arr = array_create(2,sizeof(struct client_t));
	if (arr == NULL) nfailure++;
	for (i = 0; i < 7; i++) {
		pclient = (struct client_t *)array_push(arr);
		pclient->id = i;
		pclient->name = 'a'+(char)i;
		pclient->digits[0] = pclient->digits[1] = pclient->digits[2] = 1.23f + i;
		at = (struct client_t*)array_at(arr,i);
		fprintf(stdout, "id:%d, name:%c, digit1:%.2f, digit2:%.2f, digit:%.2f\n",
				at->id, at->name, at->digits[0], at->digits[1], at->digits[2]);
	}
	array_free(arr);

	/* test 4: test for array_push_n */
	ntest++;
	int j;
	arr = array_create(2,sizeof(struct client_t));
	if (arr == NULL) nfailure++;
	for (i = 0; i < 5; i++) {
		pclient = (struct client_t *)array_push_n(arr,(uint32_t)(i+1));
		for (j=0;j<i+1;j++) {
			(pclient+j)->id = i+j;
			(pclient+j)->name = 'a'+(char)i;
			(pclient+j)->digits[0] = (pclient+j)->digits[1] = (pclient+j)->digits[2] = 1.23f + i;
		}
	}
	for (i = 0; i < array_len(arr); i++){
		at = (struct client_t*)array_at(arr,i);
		fprintf(stdout, "id:%d, name:%c, digit1:%.2f, digit2:%.2f, digit:%.2f\n",
				at->id, at->name, at->digits[0], at->digits[1], at->digits[2]);
	}
	array_free(arr);


	fprintf(stdout,"\n");
	fprintf(stdout,"Test completed, tested in total :%d, failed :%d\n", ntest, nfailure);

	exit(0);
}
