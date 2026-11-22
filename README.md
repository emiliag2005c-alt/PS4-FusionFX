# PS4-FusionFX

Experimental graphics compatibility and enhancement framework for jailbroken PlayStation 4.

## Project status

**Early research / bootstrap stage.** This repository does not currently provide an installable PKG or PRX, and it does not yet modify game rendering.

The first milestone is a safe, read-only runtime discovery layer. Unknown or unsupported titles must remain untouched (native pass-through).

## Design principles

- Safe native pass-through for unknown and future titles.
- Detect title ID and relevant runtime/output characteristics before selecting a profile.
- Never stack competing scaling or frame-generation paths.
- Keep optional enhancements capability-gated and independently disableable.
- Prefer stable frame pacing and image quality over inflated FPS claims.
- No claims of NVIDIA DLSS support on PS4.

## Target

- Console: PlayStation 4 (CUH-1215A target for initial testing)
- Firmware: 13.02 (user-reported target)
- Environment: GoldHEN

Compatibility is not guaranteed. No experimental plugin should be installed until it has been built against the exact SDK/API and tested with a recovery path.

## Roadmap

1. Audit GoldHEN Plugins SDK and OpenOrbis toolchain interfaces.
2. Build a read-only plugin that logs process/title identity without changing graphics state.
3. Validate title detection and safe unload/recovery behavior.
4. Research supported scaling and frame-pacing hooks.
5. Add opt-in per-title capabilities with native fallback.
6. Test one title at a time and document measured results.

## Repository layout

- `docs/`: architecture, research, licensing, and roadmap.
- `profiles/`: conservative per-title profile schema and defaults.
- `src/`: plugin source (not yet production-ready).
- `tests/`: host-side validation tests.
- `tools/`: validation and build helpers.

## Safety

This project is experimental. Do not install binaries from this repository on a console until the build, ABI, firmware compatibility, and recovery procedure have been verified.
