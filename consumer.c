#include <stdlib.h>
#include <mqueue.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "shareddefs.h"

int main(int argv, char** argc)
{

	mqd_t mq;
	struct mq_attr mq_attr;
	struct item *itemptr;
	int n;
	char *bufptr;
	int buflen;

	int processCount = atoi(argc[1]);

	mq = mq_open(MQNAME, O_RDWR | O_CREAT, 0666, NULL);
	if (mq == -1) {
		perror("can not create msg queue\n");
		exit(1);
	}
	printf("mq created, mq id = %d\n", (int) mq);

	mq_getattr(mq, &mq_attr);
	printf("mq maximum msgsize = %d\n", (int) mq_attr.mq_msgsize);

	/* allocate large enough space for the buffer to store 
        an incoming message */
    buflen = mq_attr.mq_msgsize;
	bufptr = (char *) malloc(buflen);

	for(int i = 0; i < processCount; i++) {
		if(n != 0){
			n = fork();
		}
	}

	if(n != 0){

	}
	else if(n == 0){

	}

	while (1) {
		n = mq_receive(mq, (char *) bufptr, buflen, NULL);
		if (n == -1) {
			perror("mq_receive failed\n");
			exit(1);
		}

		printf("mq_receive success, message size = %d\n", n);

		itemptr = (struct item *) bufptr;

		printf("received item->id = %d\n", itemptr->id);
		printf("received item->astr = %s\n", itemptr->astr);
		printf("\n");
	}

	free(bufptr);
	mq_close(mq);
	return 0;
}
