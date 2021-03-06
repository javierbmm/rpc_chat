/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "rpcchat.h"
#include <stdio.h>
#include <stdlib.h>

static const char* FILEPATH = "../resources/chat.txt";

status *
write_0_svc(char **argp, struct svc_req *rqstp)
{
	static status  result;
    FILE *fptr;

    fptr = fopen(FILEPATH,"a");

    if(fptr == NULL) {
        //printf("Error!");
        result = _ERROR;
        return &result;
    }
    printf("Writing: %s", *argp);
    fflush(stdout);
    fprintf(fptr,"%s", *argp);
	result = _OK;

	fclose(fptr);
	return &result;
}

char **
getchat_0_svc(void *argp, struct svc_req *rqstp)
{
	static char * chat = 0;
	FILE *fptr;

    fptr = fopen(FILEPATH,"rb");
    if(fptr == NULL) {
        //printf("Error!");
        return 0;
    }

    fseek (fptr, 0, SEEK_END); // Beginning
    int length = ftell (fptr) ;
    // Verifying length in case it's too big, using a max value of 100
    const int MAX_LENGTH = 1000;
    if(length >= MAX_LENGTH) { // Reading the last 100 characters instead
        length = MAX_LENGTH;
        fseek (fptr, -length, SEEK_END);
    } else
        fseek (fptr, 0, SEEK_SET);

    chat = malloc (length+1);
    if (chat) {
        fread (chat, length, 1, fptr);
    }
    printf("chat:\n%s", chat);
    fclose (fptr);
    chat[length] = 0;

	return &chat;
}

