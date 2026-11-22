# M1 — Minimal PS4 PRX bootstrap

**Status: source scaffold and host contract tests pass; PS4-targeted CI build has been added. No console load test is claimed.**

This milestone adds the smallest GoldHEN plugin bootstrap for the PS4 target. It intentionally performs no graphics operations, hooks, process-memory access, worker-thread creation, or VideoOut changes.

## Verified upstream implementation pattern

The source and build layout follow the official GoldHEN plugin template:

- Official plugin template source: https://github.com/GoldHEN/GoldHEN_Plugins_Repository/blob/998fe03fe0275b59310511187ba8550ed475a003/plugin_src/plugin_template/source/main.c
- Official plugin template Makefile: https://github.com/GoldHEN/GoldHEN_Plugins_Repository/blob/998fe03fe0275b59310511187ba8550ed475a003/plugin_src/plugin_template/Makefile
- Official plugin metadata/visibility macros: https://github.com/GoldHEN/GoldHEN_Plugins_Repository/blob/998fe03fe0275b59310511187ba8550ed475a003/common/plugin_common.h
- Pinned SDK CRT: https://github.com/GoldHEN/GoldHEN_Plugins_SDK/blob/bcea3c7ef01dac6d7f9f49ebf9e90fe66d86f5f7/crt/crtprx.c
- Pinned SDK Makefile: https://github.com/GoldHEN/GoldHEN_Plugins_SDK/blob/bcea3c7ef01dac6d7f9f49ebf9e90fe66d86f5f7/Makefile

The plugin exports g_pluginName, g_pluginDesc, g_pluginAuth, g_pluginVersion, plugin_load, and plugin_unload. It also defines weak, hidden module_start and module_stop callbacks. The SDK CRT supplies _init/_fini wrappers that call those module callbacks.

## Reproducible toolchain candidate

- OpenOrbis PS4 Toolchain v0.5.4.
- Release asset: toolchain-llvm-18.tar.gz.
- SHA-256: 3c7cd5bb593ca74fa1c13fd59f3938dc0fc07985167f7275063019e63abe4526.
- GoldHEN Plugins SDK commit: bcea3c7ef01dac6d7f9f49ebf9e90fe66d86f5f7.

The OpenOrbis version is a pinned candidate. A successful PS4 CI build is required before calling this toolchain/SDK pair validated.

## Build locally

Set the toolchain and SDK paths:

```sh
export OO_PS4_TOOLCHAIN=/absolute/path/to/OpenOrbis/PS4Toolchain
export GOLDHEN_SDK=/absolute/path/to/GoldHEN_Plugins_SDK
make -f Makefile.ps4 sdk-crt
make -f Makefile.ps4
```

On Linux, PS4_CREATE_FSELF defaults to $OO_PS4_TOOLCHAIN/bin/linux/create-fself. Override it if the toolchain is installed with a different host binary path.

Expected output: dist/ps4/PS4-FusionFX.prx.

The Makefile follows the official GoldHEN sample's two-stage output: create-fself writes an intermediate OELF and the final library path is supplied through --lib. This is a PRX candidate, not a PKG. Do not install it until the CI artifact has been inspected and the target-console lifecycle test is ready.

## Verification gates

1. Build using the pinned OpenOrbis release and pinned GoldHEN SDK revision.
2. Verify required public plugin exports in the ELF and inspect the generated PRX.
3. Load/unload on the target PS4 with GoldHEN and verify game launch/exit behavior.
4. Verify behavior specifically on firmware 13.02 and the CUH-1215A target.
5. Only after lifecycle stability, add read-only process discovery to the plugin runtime.

A successful host test is not evidence of a PS4 build or firmware compatibility.
