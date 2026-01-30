#include "easylibstorage.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    void *ctx;
} console;

typedef void (*fn)(void *, console *);

struct command {
    const char *name;
    const char *desc;
    fn command;
};

int n_commands();
static const struct command commands[];

void cmd_help(void *_, console *c) {
    printf("Commands:\n");
    for (int i = 0; i < n_commands(); i++) {
        printf(" [%s]: %s\n", commands[i].name, commands[i].desc);
    }
}

void cmd_quit(void *_, console *c) {

}

void progress_print(int total, int complete, int status) {
    if (total > 0) {
        printf("\r  %d / %d bytes", complete, total);
    } else {
        printf("\r  %d bytes", complete);
    }
    fflush(stdout);
}

void cmd_start(void *args, console *c) {

}

void cmd_stop(void *args, console *c) {

}

void cmd_upload(void *args, console *c) {

}

void cmd_download(void *args, console *c) {

}

static const struct command commands[] = {
    {"help", "prints this help message", cmd_help},
    {"quit", "quits this program", cmd_quit},
    {"start", "[API PORT] [DISC PORT] [BOOTSTRAP NODE] creates and starts a node", cmd_start},
    {"stop", "stops and destroys the node", cmd_stop},
    {"upload", "[PATH] uploads a file to the node", cmd_upload},
    {"download", "[CID] [PATH] downloads content to a file", cmd_download},
};

int n_commands() { return sizeof(commands) / sizeof(commands[0]); }

int main(void) {
    char buf[4096];
    console c;
    int i;

    c.ctx = NULL;

    while (1) {
        printf("> ");
        fflush(stdout);

        if (!fgets(buf, sizeof(buf), stdin)) {
            break;
        }
        buf[strcspn(buf, "\n")] = 0;

        char *cmd = strtok(buf, " ");
        if (cmd == NULL) {
            // user has input an empty string
            continue;
        }

        for (i = 0; i < n_commands(); i++) {
            if (strcmp(cmd, commands[i].name) == 0) {
                char *arg = strtok(NULL, " ");
                commands[i].command(arg, &c);
                break;
            }
        }

        if (i == n_commands()) {
            printf("Invalid command %s\n", buf);
        }
    }
}
