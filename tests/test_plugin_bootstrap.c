#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef int32_t s32;
typedef int64_t s64;
typedef uint32_t u32;

extern const char *g_pluginName;
extern const char *g_pluginDesc;
extern const char *g_pluginAuth;
extern u32 g_pluginVersion;

s32 plugin_load(s32 argc, const char *argv[]);
s32 plugin_unload(s32 argc, const char *argv[]);
s32 module_start(s64 argc, const void *args);
s32 module_stop(s64 argc, const void *args);

int main(void)
{
    assert(strcmp(g_pluginName, "PS4-FusionFX") == 0);
    assert(g_pluginDesc != NULL && g_pluginDesc[0] != '\0');
    assert(g_pluginAuth != NULL && g_pluginAuth[0] != '\0');
    assert(g_pluginVersion == 0x00000100u);

    assert(module_start(0, NULL) == 0);
    assert(plugin_load(0, NULL) == 0);
    assert(plugin_unload(0, NULL) == 0);
    assert(module_stop(0, NULL) == 0);

    puts("PASS: inert PS4 plugin bootstrap exports");
    return 0;
}
