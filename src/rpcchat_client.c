/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */
#define _GNU_SOURCE
#include <ncurses.h>

#include "rpcchat.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

/* Global variables */
WINDOW *output_win, *input_win;
CLIENT *clnt;
/* End of Global variables */
enum _MyBool {_false=0, _true=1};

int get_option() {
    printf("\nSelect one option:\n\t1- Write\n\t2- Read chat\n\t3- Exit\n");
    int option;

    scanf("%d", &option);

    return option;
}

enum _MyBool invalid_option(int option) {
    enum _MyBool invalid = (option > 3 || option < 1);

    return invalid;
}

void write_chat(CLIENT* clnt, char * line) {
    status  *result_1;
     char * write_0_arg = NULL;
    size_t len = 0;
    char aux;

    printf("%s\n", line);
    int line_size = sizeof(line);
    write_0_arg = (char*) malloc(sizeof(char*) * (line_size+1));
    strcpy(write_0_arg, line);
    strcat(write_0_arg, "\n");
    //    write_0_arg[line_size+1] = '\0';
//    write_0_arg[line_size+2] = '\0';
    printf("size: %d, formated: %s\n", line_size, write_0_arg);
    result_1 = write_0(&write_0_arg, clnt);
    if (result_1 == (status *) NULL) {
        clnt_perror (clnt, "call failed");
    }

     free(write_0_arg);
}

char* read_chat(CLIENT* clnt) {
    char * *result_2;
    char *getchat_0_arg;

    result_2 = getchat_0((void*)&getchat_0_arg, clnt);
    if (result_2 == (char **) NULL) {
        clnt_perror (clnt, "call failed");
    }

    return *result_2;
}

void exit_chat(CLIENT* clnt) {

}

WINDOW *create_newwin(int height, int width, int starty, int startx)
{
    WINDOW *local_win;
    local_win = newwin(height, width, starty, startx);
    box(local_win, 0 , 0);		/* 0, 0 gives default characters
					   for the vertical and horizontal
					    lines			*/
    wrefresh(local_win);		/* Show that box 		*/
    return local_win;
}

void draw_chat() ;
void chat() ;
void *print_output(void *vargp);
void *get_input(void *vargp);

void
rpcchat_0(char *host)
{
#ifndef	DEBUG
	clnt = clnt_create (host, rpcchat, rpcchat_version, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

    int option = 1;

    printf("hi\n");
    char hola[] = "holahola";
    write_chat(clnt, hola);
    getchar();
    draw_chat();
    chat(clnt);
    getch();
    endwin();

//    while(option != 3) {
//        option = get_option();
//        if(invalid_option(option))
//            continue;
//
//        (*menu[option-1])(clnt);
//    }


#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}

int
main (int argc, char *argv[])
{
	char *host;
	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}

	// NCURSES TEST
    // chat();
//    draw_chat();
//    chat();
//	getch();
//	endwin();
//    return 0;


    host = argv[1];
    rpcchat_0 (host);
    exit (0);
}

//
//WINDOW *my_win;
//char mesg[]="Just a string";            /* message to be appeared on the screen */
//int startx, starty, width, height;
//
//initscr();                              /* start the curses mode */
//
//getmaxyx(stdscr,height, width);
//height +=1;
//width -= 1;
////printw("height: %d, width: %d\n", height, width);
//starty = 0;	/* Calculating for a center placement */
//startx = 0;	/* of the window		*/
////    printw("Press F2 to exit");
//refresh();
//
//my_win = create_newwin(height*2/3, width, starty, startx);
//
//getch();
//endwin();

void draw_chat() {
    char mesg[]="Just a string";            /* message to be appeared on the screen */
    int startx, starty, width, height;

    initscr();                              /* start the curses mode */

    getmaxyx(stdscr,height, width);
//    height +=1;
//    width -= 1;

    starty = 0;	/* Calculating for a center placement */
    startx = 0;	/* of the window		*/
    refresh();

    // Output window
    output_win = create_newwin(height-2, width, starty, startx);
    input_win  = newwin(2, width, height-1, startx);
}

void chat(CLIENT* clnt) {
    char buf[100] = {0}, chat[100] = {0}, *s = buf;
    int ch, cnt = 0, n = 1;
    WINDOW *w;

    if ((w = initscr()) == NULL) {
        fprintf(stderr, "Error: initscr()\n");
        exit(EXIT_FAILURE);
    }
    keypad(stdscr, TRUE);
    //noecho();
    //cbreak();      // disable line-buffering
    timeout(100);  // wait 100 milliseconds for input
    pthread_t output_thread_id;
    printf("Before Thread\n");
    pthread_create(&output_thread_id, NULL, print_output, NULL);

    while (n != 0) {
        // refreshing the chat:
        werase(input_win);
        werase(output_win);
        draw_chat();
        mvwprintw(output_win, 2, 2, "chat: %s", chat);
        wprintw(input_win, "buf: %s", buf);
        wrefresh(output_win);
        wrefresh(input_win);

        // getch (with cbreak and timeout as above)
        // waits 100ms and returns ERR if it doesn't read anything.
        if ((ch = getch()) != ERR) {
            if (ch == '\n') {
                getch();
                mvwprintw(output_win,3, 3, "writing %s", buf);
                wrefresh(output_win);
                getch();
                *s = 0;
                sscanf(buf, " %[^\n]s", chat);
                write_chat(clnt, chat);
                s = buf;
                *s = 0;
            }
            else if (ch == KEY_BACKSPACE) {
                if (s > buf)
                    *--s = 0;
            }
            else if (s - buf < (long)sizeof buf - 1) {
                *s++ = ch;
                *s = 0;
            }
        }
    }

    delwin(w);
    endwin();
    return;
}

void *print_output(void* vargp) {
    char * chat = 0;
    int it = 0;
    while(it < 3){
        sleep(1);
        chat = read_chat(clnt);
        werase(output_win);
        draw_chat();
        mvwprintw(output_win, 2, 2, "chat: %s", chat);
        wrefresh(output_win);
        it++;
    }

}