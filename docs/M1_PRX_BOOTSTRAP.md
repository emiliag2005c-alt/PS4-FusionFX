# M1 — Minimal PS4 PRX bootstrap

**Status: source scaffold added; no PRX build or console test claimed.**

This milestone adds the smallest GoldHEN plugin bootstrap for the PS4 target. It intentionally performs no graphics operations, hooks, process-memory access, worker-thread creation, or VideoOut changes.

## Source basis

The callback names and exported metadata follow the official GoldHEN plugin sample:

- [GoldHEN plugin sample source](https://github.com/GoldHEN/GoldHEN_Plugins_Repository/blob/main/plugin_src/fliprate_remover/source/main.c)
- [GoldHEN plugin sample Makefile](https://github.com/GoldHEN/GoldHEN_Plugins_Repository/blob/main/plugin_src/fliprate_remover/Makefile)
- [Pinned SDK CRT](https://github.com/GoldHEN/GoldHEN_Plugins_SDK/blob/bcea3c7ef01dac6d7f9f49ebf9e90fe66d86f5f7/crt/crtprx.c)

The sample exports `g_pluginName`, `g_pluginDesc`, `g_pluginAuth`, `g_pluginVersion`, `plugin_load`, and `plugin_unload`. It also defines hidden `module_start` and `module_stop` callbacks. The SDK CRT maps its own `_init` and `_fini` wrappers to the module callbacks.

## Files

- `src/plugin/main.c`: inert PS4 plugin exports and callbacks.
- `Makefile.ps4`: PS4 PRX build recipe; no Linux/desktop runtime target.
- `tests/test_plugin_bootstrap.c`: host-side contract test for exported metadata and no-op callback behavior.
- `tests/stubs/Common.h`: minimal host test types only.

## Build prerequisites

- OpenOrbis PS4 Toolchain v0.5.4 (candidate pin documented in `PLUGIN_LIFECYCLE_AUDIT.md`).
- GoldHEN Plugins SDK at the audited revision.
- Clang, LLD, and the toolchain's `create-fself` utility.
- GoldHEN SDK CRT object at `$GOLDHEN_SDK/build/crtprx.o`.

The build is deliberately explicit about the `create-fself` executable path because its host-specific location can differ by package layout. Set `PS4_CREATE_FSELF` to that exact executable.

Example:

```sh
make -f Makefile.ps4 sdk-crt \
  OO_PS4_TOOLCHAIN=/path/to/OpenOrbis-PS4-Toolchain \
  GOLDHEN_SDK=/path/to/GoldHEN_Plugins_SDK

make -f Makefile.ps4 \
  OO_PS4_TOOLCHAIN=/path/to/OpenOrbis-PS4-Toolchain \
  GOLDHEN_SDK=/path/to/GoldHEN_Plugins_SDK \
  PS4_CREATE_FSELF=/path/to/create-fself
```

The resulting artifact, if the build succeeds, is `dist/ps4/PS4-FusionFX.prx`. It is not a PKG and is not ready for console installation until validated.

## Verification gates still open

- Build against the exact pinned SDK/toolchain pair.
- Inspect PRX exports and metadata in the generated artifact.
- Verify GoldHEN loads and unloads it on the target console.
- Verify process-info API use only after callback context is established.
- Test game launch/exit and recovery on the target PS4 with firmware 13.02.

Do not install an unverified build. This source scaffold is not evidence of firmware compatibility.
