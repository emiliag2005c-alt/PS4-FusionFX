# M1 — Process identity discovery

## Implemented in source

`src/discovery/process_identity.c` wraps the GoldHEN SDK's documented
`sys_sdk_proc_info(struct proc_info*)` interface and copies a bounded,
validated subset of the returned data into FusionFX-owned storage.

Captured fields:
- PID
- process name
- title ID
- game version
- content ID
- process base address (metadata only; not dereferenced)

## Safety properties

- No game memory reads or writes.
- No GNM/GPU hooks.
- No render-target allocations.
- No VideoOut or display-mode changes.
- No executable patching.
- API errors, malformed fixed-size strings, or missing title IDs fail closed.
- Output is cleared before querying, so stale identity data is not retained after an error.

## Verification

Run `sh tools/host_check.sh` on a host with a C compiler and Python 3.

The host test uses a stub for the GoldHEN SDK call. It verifies the wrapper's
input validation and error handling; it does not emulate GoldHEN or prove
runtime behavior on a PS4.

## Remaining before a PRX

- Pin exact GoldHEN SDK commit.
- Verify plugin lifecycle/entrypoint against a known working plugin example.
- Build with OpenOrbis PS4 Toolchain and LLVM 10+.
- Confirm process-info call context and behavior on firmware 13.02.
- Test load/unload and recovery on console.

This module is not an installable plugin by itself.
