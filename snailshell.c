/*
 18.12.2023
snailshell.c by Tarık Çelik

This software is relased under agpl3 license.

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/cdefs.h>
#include <pwd.h>
#include <time.h>

int main() {
bool exit = false;
char *command = (char *) malloc (64);
char *dir = (char *) malloc (500);
char *file = (char *) malloc (500);
char *exc = (char *) malloc (500);
char *hostname = (char *) malloc (64);

printf("\SnailShell 0.1 by Tarık Çelik \n");
printf("Write 'help' for help \n");

while (!exit) {

	printf("%s", "= ");
	scanf("%s", command);

	if (strcmp(command, "clear") == 0) {
	printf("\e[1;1H\e[2J");
	}

	else if (strcmp(command, "exit") == 0) {
	exit = true;
	}

	else if (strcmp(command, "cd") == 0) {
	scanf("%s", dir);
	chdir(dir);
	}

	else if (strcmp(command, "ls") == 0) {
    	if (access(".", R_OK) != 0) { // Check for read permission
        printf("Cannot access directory: No read permission\n");
  	  }
	else {
        DIR *dir;
        struct dirent *entry;
        dir = opendir(".");
        while ((entry = readdir(dir)) != NULL) {
            printf("%s\n", entry->d_name);
        }
        closedir(dir);
    		}
	}


	else if (strcmp(command, "mkdir") == 0) {
	scanf("%s",dir);
	mkdir(dir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	}

	else if (strcmp(command, "rmdir") == 0) {
		scanf("%s", dir);
		rmdir(dir);
	}

	else if (strcmp(command, "touch") == 0) {
		scanf("%s", file);
		FILE *File = fopen(file, "w");
		fclose(File);
	}

	else if (strcmp(command, "rm") == 0) {
                scanf("%s", file);
                remove(file);
	}

	else if (strcmp(command, "exec") == 0) {
		scanf(" %[^\n]", exc);
		system(exc);
	}

	else if (strcmp(command, "mv") == 0) {
		scanf("%s", file);
		scanf("%s", dir);
		rename(file, dir);
	}

	else if (strcmp(command, "pwd") == 0) {
		getcwd(dir, 500);
		printf("%s\n", dir);
	}

	else if (strcmp(command, "hostname") == 0) {
	        gethostname(hostname, 64);
        	printf("%s\n", hostname);
	}

	else if (strcmp(command, "whoami") == 0) {
	struct passwd *pw = getpwuid(geteuid());
	printf("%s\n", pw->pw_name);
	}

	else if (strcmp(command, "cp") == 0) {
            char *sourcefile = (char *)malloc(100);
            char *destinationfile = (char *)malloc(100);
            scanf("%s %s", sourcefile, destinationfile);
	    FILE *sourceFile = fopen(sourcefile, "rb");
            FILE *destFile = fopen(destinationfile, "wb");
	    if (sourceFile == NULL || destFile == NULL) {
                printf("Error: Unable to open files for copying.\n");
            } else {
                char *buffer = (char *)malloc(1024);
                size_t bytesRead;

                while ((bytesRead = fread(buffer, 1, sizeof(buffer), sourceFile)) > 0) {
                    fwrite(buffer, 1, bytesRead, destFile);
                }

                free(buffer);
                fclose(sourceFile);
                fclose(destFile);
            }

            free(sourcefile);
            free(destinationfile);
        }

	else if (strcmp(command, "uname") == 0) {
		system("uname");
	}


	else if (strcmp(command, "help") == 0) {

		printf("\nSnailShell 0.1 by Tarık Çelik");
		printf("\n * help for that menu");
		printf("\n * clear for clearing the screen");
		printf("\n * exit for exiting");
		printf("\n * cd <path> for entering to a directory");
		printf("\n * ls for listing contents of current directory");
		printf("\n * mkdir <dirname> for creating a directory");
		printf("\n * rmdir <dirname> for removing a directory");
		printf("\n * touch <filename> for creating files");
		printf("\n * rm <filename> for removing a file");
		printf("\n * exec <command> for executing a command");
		printf("\n * mv <filename> <new location > for moving a file");
		printf("\n * cp <filename> <newfile> for moving a file");
		printf("\n * calc <operation> for calculating");
		printf("\n * pwd for seeing current directory");
		printf("\n * hostname for seeing hostname");
		printf("\n * whoami for seeing the current user");
		printf("\n * uname for  seeing the os");
		printf("\n\n"); 

		}
	}
free(command);
free(dir);
free(exc);
free(file);
free(hostname);
return 0;
}
