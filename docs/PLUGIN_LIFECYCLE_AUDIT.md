# GoldHEN Plugin Lifecycle Audit

**Status: source-level lifecycle verified; PS4 runtime and firmware 13.02 remain unverified.**

## Pinned SDK reference

- Repository: https://github.com/GoldHEN/GoldHEN_Plugins_SDK
- Audited revision: `bcea3c7ef01dac6d7f9f49ebf9e90fe66d86f5f7`
- SDK license: MIT (see the upstream repository).
- Relevant files at that exact revision:
  - [`crt/crtprx.c`](https://github.com/GoldHEN/GoldHEN_Plugins_SDK/blob/bcea3c7ef01dac6d7f9f49ebf9e90fe66d86f5f7/crt/crtprx.c)
  - [`Makefile`](https://github.com/GoldHEN/GoldHEN_Plugins_SDK/blob/bcea3c7ef01dac6d7f9f49ebf9e90fe66d86f5f7/Makefile)
  - [`include/GoldHEN.h`](https://github.com/GoldHEN/GoldHEN_Plugins_SDK/blob/bcea3c7ef01dac6d7f9f49ebf9e90fe66d86f5f7/include/GoldHEN.h)

The SDK README requires the OpenOrbis PS4 Toolchain and LLVM 10+.

## Two distinct lifecycle layers

The source shows that a GoldHEN plugin has two related but separate entry-point layers. They must not be conflated.

### 1. PRX / system module layer

The SDK's `crt/crtprx.c` declares:

- `module_start(size_t args, const void *argp)`
- `module_stop(size_t args, const void *argp)`

Its CRT wrapper implements:

- `_init(args, argp)` → calls `module_start(args, argp)`
- `_fini(args, argp)` → calls `module_stop(args, argp)`

The CRT also emits `_sceProcessParam` and the SDK metadata globals. The SDK Makefile links a PIE using `-e _init` and includes the CRT object. FusionFX must use the SDK's build conventions rather than inventing its own PRX entry point.

### 2. GoldHEN plugin-loader layer

The official [GoldHEN Plugins Repository](https://github.com/GoldHEN/GoldHEN_Plugins_Repository) contains working source examples. Its [plugin loader source](https://github.com/GoldHEN/GoldHEN_Plugins_Repository/blob/main/plugin_src/plugin_loader/source/main.c) demonstrates this sequence:

1. The loader calls `sceKernelLoadStartModule(...)` for the configured PRX.
2. It resolves the exported `g_pluginName` symbol.
3. It resolves exported `plugin_load` and `plugin_unload` symbols using `sceKernelDlsym`.
4. It invokes `plugin_load(argc, argv)` and counts a plugin as loaded when it returns zero.
5. In the inspected code path, if `plugin_load` returns non-zero, the loader calls `plugin_unload` as cleanup.

The official [fliprate_remover sample](https://github.com/GoldHEN/GoldHEN_Plugins_Repository/blob/main/plugin_src/fliprate_remover/source/main.c) exports `plugin_load(s32 argc, const char* argv[])` and `plugin_unload(s32 argc, const char* argv[])`, and also defines hidden `module_start` / `module_stop` functions. The sample's module callbacks return immediately; plugin-specific setup and cleanup are in the GoldHEN callbacks.

**Important limitation:** the inspected loader source proves its load path and failure-cleanup call. It does not, by itself, prove when or whether a normal successful plugin receives `plugin_unload` during game exit or system shutdown. Do not assume that it does. FusionFX must avoid relying on a cleanup callback until this is verified against the actual GoldHEN runtime.

## Consequences for FusionFX

- Keep `module_start` / `module_stop` minimal and side-effect-free at first.
- Put plugin initialization behind the verified GoldHEN `plugin_load` export.
- Make initialization idempotent and fail closed: no graphics hooks, GPU work, memory patching, or output-mode changes in the first PRX.
- Export both `plugin_load` and `plugin_unload`, as the official loader resolves both.
- Treat `plugin_unload` as best-effort cleanup, not as a guaranteed normal-shutdown notification until proven.
- Do not start persistent worker threads in the first read-only build.
- Do not mark firmware 13.02 compatible based solely on SDK source. The exact build and runtime behavior still need console verification.

## What is verified vs. open

| Item | Status |
|---|---|
| SDK CRT maps `_init` to `module_start` | Verified in pinned SDK source |
| SDK CRT maps `_fini` to `module_stop` | Verified in pinned SDK source |
| SDK Makefile uses PIE and `-e _init` | Verified in pinned SDK source |
| GoldHEN loader resolves `plugin_load` and `plugin_unload` | Verified in official loader source |
| Official sample exports both callbacks | Verified in official sample |
| Normal successful-plugin unload timing | Not established by inspected source |
| Process-info API is safe in each callback context | Not established |
| Build with pinned toolchain | Not yet performed |
| Firmware 13.02 compatibility | Not yet tested on console |

## Next engineering gate

Before adding any graphics-related code:

1. Pin an OpenOrbis toolchain release/commit and compiler version.
2. Add a minimal PRX using the official SDK CRT and exact callback signatures.
3. Build it in CI with the actual PS4 toolchain.
4. Keep its only runtime behavior to bounded, read-only process identity logging.
5. Verify load, game launch, exit, and recovery on the target PS4 / GoldHEN build.
6. Only then consider any graphics-facing experiment.

This audit is source research, not a claim that FusionFX is already an installable or tested PRX.
