#include <Common.h>

/*
 * PS4-only GoldHEN plugin entry points.
 *
 * This first PRX milestone deliberately performs no hooks, graphics work,
 * process-memory access, thread creation, or output-mode changes.
 */

#define FUSIONFX_EXPORT __attribute__((visibility("default")))
#define FUSIONFX_HIDDEN __attribute__((visibility("hidden")))

FUSIONFX_EXPORT const char *g_pluginName = "PS4-FusionFX";
FUSIONFX_EXPORT const char *g_pluginDesc =
    "Experimental PS4 graphics framework (read-only bootstrap)";
FUSIONFX_EXPORT const char *g_pluginAuth = "PS4-FusionFX contributors";
FUSIONFX_EXPORT u32 g_pluginVersion = 0x00000100; /* 1.00 */

FUSIONFX_EXPORT s32 plugin_load(s32 argc, const char *argv[])
{
    (void)argc;
    (void)argv;

    /* Keep bootstrap inert until console lifecycle tests are complete. */
    return 0;
}

FUSIONFX_EXPORT s32 plugin_unload(s32 argc, const char *argv[])
{
    (void)argc;
    (void)argv;

    /* No resources are acquired by this minimal bootstrap. */
    return 0;
}

/* The GoldHEN sample plugins use these hidden PRX module callbacks. */
FUSIONFX_HIDDEN s32 module_start(s64 argc, const void *args)
{
    (void)argc;
    (void)args;
    return 0;
}

FUSIONFX_HIDDEN s32 module_stop(s64 argc, const void *args)
{
    (void)argc;
    (void)args;
    return 0;
}
