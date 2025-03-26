#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include <stdio.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<time.h>
#ifdef _WIN32
#include<io.h>
#define access _access
#define F_OK 0
#define W_OK 2
#define R_OK 4
#else
#include <unistd.h>
#endif
void createFile(char* nume);
void write_to_file(char*nume, char* text);
void read_from_file(char* nume);
void delete_file(char* nume);
int check_file_exists(char* nume);
void log_error(char* message,char* nume);
void file_check_permission(char *nume);
void file_backup(char* nume);
void ensure_backup(const char* path);
#endif