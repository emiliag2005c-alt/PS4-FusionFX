#include <Common.h>

/* Minimal PS4 GoldHEN bootstrap: no hooks, graphics calls, memory access,
 * worker threads, or display-mode changes. */
#define FUSIONFX_PUBLIC __attribute__((visibility("default")))
#define FUSIONFX_MODULE_HIDDEN __attribute__((weak)) __attribute__((visibility("hidden")))

FUSIONFX_PUBLIC const char *g_pluginName = "PS4-FusionFX";
FUSIONFX_PUBLIC const char *g_pluginDesc = "Experimental PS4 graphics framework (inert bootstrap)";
FUSIONFX_PUBLIC const char *g_pluginAuth = "PS4-FusionFX contributors";
FUSIONFX_PUBLIC u32 g_pluginVersion = 0x00000100;

s32 FUSIONFX_PUBLIC plugin_load(s32 argc, const char *argv[])
{
    (void)argc; (void)argv;
    return 0;
}

s32 FUSIONFX_PUBLIC plugin_unload(s32 argc, const char *argv[])
{
    (void)argc; (void)argv;
    return 0;
}

s32 FUSIONFX_MODULE_HIDDEN module_start(s64 argc, const void *args)
{
    (void)argc; (void)args;
    return 0;
}

s32 FUSIONFX_MODULE_HIDDEN module_stop(s64 argc, const void *args)
{
    (void)argc; (void)args;
    return 0;
}
