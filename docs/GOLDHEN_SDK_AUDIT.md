# GoldHEN SDK interface audit

Audit date: 2026-11-21
Upstream: https://github.com/GoldHEN/GoldHEN_Plugins_SDK
Inspected upstream files on branch `main`:
- `include/GoldHEN.h`
- `include/Common.h`
- `source/GoldHEN.c`
- `Makefile`
- `README.md`

## Verified from the inspected header/source

The SDK declares:

- `struct proc_info` with `pid`, `name[40]`, `path[64]`, `titleid[16]`, `contentid[64]`, `version[6]`, and `base_address`.
- `int sys_sdk_proc_info(struct proc_info* info)`.
- The implementation dispatches `GOLDHEN_SDK_CMD_PROCESS_INFO` through `sys_sdk_cmd`.
- The SDK README says it requires the OpenOrbis PS4 Toolchain and LLVM 10+.

This verifies the process-info data structure and helper declaration in the inspected upstream revision. It does **not** prove that calling it from an arbitrary plugin lifecycle callback is safe or that the current FusionFX source is buildable.

## Still unverified

- Exact GoldHEN plugin load/unload entrypoint and lifecycle contract for the target GoldHEN release.
- Whether process-info returns the intended current process in the plugin's execution context.
- Error handling and thread-safety requirements.
- Firmware 13.02 runtime compatibility.
- A reproducible PRX build and console test.

## Implementation rule

Do not add speculative entrypoint macros, callbacks, or guessed APIs. Before writing the first PRX source, pin the SDK commit and locate a known-working plugin example that uses the same plugin lifecycle. The initial discovery plugin must only log validated process identity and must not touch graphics state.
