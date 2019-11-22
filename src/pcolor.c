/**
Filename: pcolor.c (implementation of pcolor.h)
Description: Print character with some color in terminal
Prepared by: Asisten IF2110
Created at: 17/10/2019
**/

#include <stdio.h>
#include "pcolor.h"

/* Char */
void print_red(char c) {
    printf("%s%c", RED, c);
    printf("%s", NORMAL);
}

void print_green(char c) {
    printf("%s%c", GREEN, c);
    printf("%s", NORMAL);
}

void print_yellow(char c) {
    printf("%s%c", YELLOW, c);
    printf("%s", NORMAL);
}

void print_blue(char c) {
    printf("%s%c", BLUE, c);
    printf("%s", NORMAL);
}

void print_magenta(char c) {
    printf("%s%c", MAGENTA, c);
    printf("%s", NORMAL);
}

void print_cyan(char c) {
    printf("%s%c", CYAN, c);
    printf("%s", NORMAL);
}

void print_red_s(char * c) {
    printf("%s%s", RED, c);
    printf("%s", NORMAL);
}

/* String */
void print_green_s(char * c) {
    printf("%s%s", GREEN, c);
    printf("%s", NORMAL);
}

void print_yellow_s(char * c) {
    printf("%s%s", YELLOW, c);
    printf("%s", NORMAL);
}

void print_blue_s(char * c) {
    printf("%s%s", BLUE, c);
    printf("%s", NORMAL);
}

void print_magenta_s(char * c) {
    printf("%s%s", MAGENTA, c);
    printf("%s", NORMAL);
}

void print_cyan_s(char * c) {
    printf("%s%s", CYAN, c);
    printf("%s", NORMAL);
}
