#include "process_identity.h"

#include <stddef.h>
#include <string.h>

/*
 * GoldHEN SDK interface. The SDK's include/GoldHEN.h defines proc_info
 * and sys_sdk_proc_info(). Keep this dependency isolated to this file.
 */
#include "GoldHEN.h"

static int has_terminator(const char *value, size_t capacity)
{
    return value != NULL && memchr(value, '\0', capacity) != NULL;
}

static void copy_bounded(char *destination, size_t destination_size,
                         const char *source, size_t source_size)
{
    size_t length = 0;

    if (destination == NULL || destination_size == 0)
        return;

    destination[0] = '\0';
    if (source == NULL)
        return;

    while (length < source_size && source[length] != '\0')
        ++length;

    if (length >= destination_size)
        length = destination_size - 1;

    if (length != 0)
        memcpy(destination, source, length);

    destination[length] = '\0';
}

int fusionfx_get_process_identity(fusionfx_process_identity *out_identity)
{
    struct proc_info raw;

    if (out_identity == NULL)
        return -1;

    memset(out_identity, 0, sizeof(*out_identity));
    memset(&raw, 0, sizeof(raw));

    if (sys_sdk_proc_info(&raw) != 0)
        return -2;

    /*
     * Fixed-size SDK fields must contain a terminator before they are
     * copied or interpreted as strings.
     */
    if (raw.pid <= 0 ||
        !has_terminator(raw.name, sizeof(raw.name)) ||
        !has_terminator(raw.titleid, sizeof(raw.titleid)) ||
        !has_terminator(raw.version, sizeof(raw.version)) ||
        !has_terminator(raw.contentid, sizeof(raw.contentid)) ||
        raw.titleid[0] == '\0')
        return -3;

    out_identity->pid = raw.pid;
    out_identity->base_address = raw.base_address;
    copy_bounded(out_identity->process_name, sizeof(out_identity->process_name),
                 raw.name, sizeof(raw.name));
    copy_bounded(out_identity->title_id, sizeof(out_identity->title_id),
                 raw.titleid, sizeof(raw.titleid));
    copy_bounded(out_identity->game_version, sizeof(out_identity->game_version),
                 raw.version, sizeof(raw.version));
    copy_bounded(out_identity->content_id, sizeof(out_identity->content_id),
                 raw.contentid, sizeof(raw.contentid));

    return 0;
}
