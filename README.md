# PS4-FusionFX

Experimental graphics compatibility and enhancement framework **exclusively for PlayStation 4**.

## Project status

**Research and host-testable discovery stage.** This repository does not currently provide an installable PKG or PRX, and it does not modify game rendering.

The first source module wraps GoldHEN's documented process-info API to obtain process identity metadata. An inert PS4 PRX bootstrap now exports the official GoldHEN plugin metadata and callbacks, but does not yet call graphics APIs or alter games. Both modules have host-side contract tests. Source-level audits document the official GoldHEN PRX and plugin-loader entry points; no PS4 PRX build or console runtime test has been completed.

See [the GoldHEN plugin lifecycle audit](docs/PLUGIN_LIFECYCLE_AUDIT.md) for the pinned SDK revision, official source references, and remaining runtime questions.

## Design principles

- Safe native pass-through for unknown and future titles.
- Detect title ID and relevant runtime/output characteristics before selecting a profile.
- Never stack competing scaling or frame-generation paths.
- Keep optional enhancements capability-gated and independently disableable.
- Prefer stable frame pacing and image quality over inflated FPS claims.
- No claims of NVIDIA DLSS support on PS4.

## Platform policy

- **Runtime target: PlayStation 4 only.** No Linux, Windows, Android, or desktop runtime ports are planned.
- Host-side tools and CI may run on a build machine only to validate or compile PS4-targeted artifacts; they are not product ports.

## Target

- Console: PlayStation 4 (CUH-1215A target for initial testing)
- Firmware: 13.02 (user-reported target)
- Environment: GoldHEN

Compatibility is not guaranteed. No experimental plugin should be installed until the build, exact API/ABI, firmware compatibility, and recovery procedure have been verified.

## Host checks

Run the host-side contract checks (these are not a Linux product build):

```sh
sh tools/host_check.sh
```

This compiles the process-identity wrapper against a test stub, runs C tests, validates the default profile, and runs Python profile tests. It is not a PS4 PRX build.

## Roadmap

1. Pin the SDK and toolchain; verify plugin lifecycle and ABI.
2. Build a read-only plugin that logs process/title identity without changing graphics state.
3. Validate title detection and safe unload/recovery behavior.
4. Research supported scaling and frame-pacing hooks.
5. Add opt-in per-title capabilities with native fallback.
6. Test one title at a time and document measured results.

## Repository layout

- `docs/`: architecture, research, licensing, lifecycle audit, and roadmap.
- `profiles/`: conservative per-title profile schema and defaults.
- `src/discovery/`: read-only process identity module.
- `src/plugin/`: inert PS4 PRX bootstrap.
- `tests/`: host-side C and Python tests.
- `tools/`: validation and host test helpers.
- `Makefile.ps4`: explicit PS4-only PRX build recipe.

## Safety

This project is experimental. Do not install binaries from this repository on a console until the build, ABI, firmware compatibility, and recovery procedure have been verified.
