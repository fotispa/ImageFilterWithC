#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "bitmap.h"
#include <fcntl.h>
#include <sys/stat.h>

#define ERROR_MESSAGE "Warning: one or more filter had an error, so the output image may not be correct.\n"
#define SUCCESS_MESSAGE "Image transformed successfully!\n"


/*
 * Check whether the given command is a valid image filter, and if so,
 * run the process.
 *
 * We've given you this function to illustrate the expected command-line
 * arguments for image_filter. No further error-checking is required for
 * the child processes.
 */
void run_command(const char *cmd) {
    if (strcmp(cmd, "copy") == 0 || strcmp(cmd, "./copy") == 0 ||
        strcmp(cmd, "greyscale") == 0 || strcmp(cmd, "./greyscale") == 0 ||
        strcmp(cmd, "gaussian_blur") == 0 || strcmp(cmd, "./gaussian_blur") == 0 ||
        strcmp(cmd, "edge_detection") == 0 || strcmp(cmd, "./edge_detection") == 0) {
        execl(cmd, cmd, NULL);
    } else if (strncmp(cmd, "scale", 5) == 0) {
        // Note: the numeric argument starts at cmd[6]
        execl("scale", "scale", cmd + 6, NULL);
    } else if (strncmp(cmd, "./scale", 7) == 0) {
        // Note: the numeric argument starts at cmd[8]
        execl("./scale", "./scale", cmd + 8, NULL);
    } else {
        fprintf(stderr, "Invalid command '%s'\n", cmd);
        exit(1);
    }
}


// TODO: Complete this function.
int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Usage: image_filter input output [filter ...]\n");
        exit(1);
    }
    int fd[argc - 2][2];
    for (int i =0; i< argc-2; i++) {
        pipe(fd[i]);
    }
    for (int j=0; j < argc-1; j++) {
        int n = fork();
        if (n == 0) {
            if (j == 0) {
                int input_file = open(argv[1], O_RDONLY);
                dup2(input_file, fileno(stdin));
                dup2(fd[j][1], fileno(stdout));
                run_command("copy");
                close(input_file);
                close(fd[j][1]);
             } else if (j != argc-2) {
                dup2(fd[j-1][0], fileno(stdin));
                dup2(fd[j][1], fileno(stdout));
                run_command(argv[j+2]);
                close(fd[j-1][0]);
                close(fd[j][1]);
             } else {
                int output_file = open(argv[2], O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
                dup2(fd[j-1][0], fileno(stdin));
                dup2(output_file, fileno(stdout));
                run_command("copy");
                close(fd[j-1][0]);
                close(output_file);
             }
        }else if (n < 0) {
             perror("fork");
             exit(1);
        }        
    }
    int status;
    if (wait(&status) != -1) {
        if (WIFEXITED(status)) {
            if (WEXITSTATUS(status) == 0) {
                printf(SUCCESS_MESSAGE);
            } else if (WEXITSTATUS(status) == 1) {
                printf(ERROR_MESSAGE);
            } else {
                perror("error");
                exit(1);
            }
        }
    }  
 
    return 0;
}
