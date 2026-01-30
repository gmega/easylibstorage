#ifndef STORAGECONSOLE_EASYLIBSTORAGE_H
#define STORAGECONSOLE_EASYLIBSTORAGE_H

#include <stdio.h>

#define STORAGE_NODE void *
#define CID char *

enum log_level {
    WARN,
    INFO,
    DEBUG,
};

typedef struct {
    int api_port;
    int disc_port;
    char *data_dir;
    char *log_level;
    char *bootstrap_node;
} node_config;

typedef void (*progress_callback)(int total, int complete, int status);

STORAGE_NODE e_storage_new(node_config config);
int e_storage_start(STORAGE_NODE node);
int e_storage_stop(STORAGE_NODE node);
int e_storage_destroy(STORAGE_NODE node);
CID e_storage_upload(STORAGE_NODE node, FILE *input, progress_callback cb);
STORAGE_NODE e_storage_download(STORAGE_NODE node, CID cid, FILE *output, progress_callback cb);

#endif // STORAGECONSOLE_EASYLIBSTORAGE_H
