#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

#define MAX_INPUT_SIZE 1024
#define MAX_TOKEN_SIZE 64
#define MAX_NUM_TOKENS 64

int turtle_cd(char **tokens);
int turtle_help(char **tokens);
int turtle_exit(char **tokens);
void signal_handler(int signum);

char *builtin_commands[] = {"cd", "help", "exit"};
int (*builtin_funcs[])(char **) = {&turtle_cd, &turtle_help, &turtle_exit};

int turtle_exit(char **args) {
    return 0;
}

int turtle_help(char **args) {
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");

    int num_builtins = sizeof(builtin_commands) / sizeof(char *);
    for (int i = 0; i < num_builtins; i++) {
        printf("  %s\n", builtin_commands[i]);
    }

    printf("Use the man command for information on other programs.\n");
    return 1;
}

int turtle_cd(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "turtle: expected argument to \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("turtle");
        }
    }
    return 1;
}

int shell_execute(char **tokens) {
    if (tokens[0] == NULL) {
        return 1;
    }

    int num_builtins = sizeof(builtin_commands) / sizeof(char *);
    for (int i = 0; i < num_builtins; i++) {
        if (strcmp(tokens[0], builtin_commands[i]) == 0) {
            return (*builtin_funcs[i])(tokens);
        }
    }

    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        if (execvp(tokens[0], tokens) == -1) {
            perror("turtle");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("turtle");
    } else {
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}

char *read_line() {
    char *line = NULL;
    size_t bufsize = 0;
    ssize_t status = getline(&line, &bufsize, stdin);
    if (status == -1) {
        if (feof(stdin)) {
            exit(EXIT_SUCCESS);
        } else {
            perror("readline");
            exit(EXIT_FAILURE);
        }
    }
    return line;
}

char **tokenize(char *line) {
    char **tokens = malloc(MAX_NUM_TOKENS * sizeof(char *));
    char *token = strtok(line, " \t\n");
    int tokenNo = 0;

    while (token != NULL) {
        tokens[tokenNo] = strdup(token);
        token = strtok(NULL, " \t\n");
        tokenNo++;
    }

    tokens[tokenNo] = NULL;
    return tokens;
}

void shell_loop() {
    char *line;
    char **tokens;
    int status;
    char cwd[MAX_INPUT_SIZE];

    signal(SIGINT, signal_handler);

    do {
        getcwd(cwd, sizeof(cwd));
        printf("%s> ", cwd);
        line = read_line();
        tokens = tokenize(line);
        status = shell_execute(tokens);

        free(line);
        free(tokens);
    } while (status);
}

void signal_handler(int signum) {
    printf("\n");
    shell_loop();
}

int main() {
    shell_loop();
    return EXIT_SUCCESS;
}
