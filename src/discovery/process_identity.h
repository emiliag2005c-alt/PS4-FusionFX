#ifndef FUSIONFX_PROCESS_IDENTITY_H
#define FUSIONFX_PROCESS_IDENTITY_H

#include <stdint.h>

#define FFX_PROCESS_NAME_MAX 40
#define FFX_TITLE_ID_MAX 16
#define FFX_GAME_VERSION_MAX 6
#define FFX_CONTENT_ID_MAX 64

typedef struct fusionfx_process_identity {
    int32_t pid;
    char process_name[FFX_PROCESS_NAME_MAX];
    char title_id[FFX_TITLE_ID_MAX];
    char game_version[FFX_GAME_VERSION_MAX];
    char content_id[FFX_CONTENT_ID_MAX];
    uint64_t base_address;
} fusionfx_process_identity;

/*
 * Queries GoldHEN's process-info interface for the calling process.
 * Returns 0 only when a minimally valid identity was received.
 * This function does not read/write game memory or touch graphics state.
 */
int fusionfx_get_process_identity(fusionfx_process_identity *out_identity);

#endif
