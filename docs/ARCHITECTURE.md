# FusionFX architecture

## Goal

Provide a modular, conservative graphics compatibility layer for jailbroken PS4 systems. The framework must never assume that every title exposes the same rendering path.

## Runtime pipeline

1. **Bootstrap** — initialize logging and read configuration.
2. **Identity discovery** — identify the running title/process using documented SDK interfaces.
3. **Capability discovery** — determine only the capabilities that can be safely observed on this firmware and runtime.
4. **Profile selection** — match a profile by title ID and, where available, update/build identity.
5. **Policy gate** — reject unsupported, conflicting, or unverified features.
6. **Backend** — optional, isolated implementation for a verified title/runtime combination.
7. **Fallback** — if any step is uncertain, leave the game graphics path unchanged.

## Non-negotiable safety rules

- Unknown title => native pass-through.
- Unknown firmware/API => disable graphics hooks.
- No writes to game-owned render targets until a backend is proven safe.
- No patching executable code in the discovery milestone.
- No simultaneous activation of competing scaling or frame-generation implementations.
- Configuration errors must fail closed, not enable experimental features.
- Logging must not block the game thread.

## Module boundaries

- `core/`: lifecycle, configuration, title identity, policy decisions.
- `discovery/`: read-only observations.
- `profiles/`: declarative per-title metadata.
- `backends/`: isolated experimental rendering integrations.
- `platform/ps4/`: GoldHEN/OpenOrbis integration.

## Future-title support

Future titles are supported only in the safe sense: they are detected and run unchanged unless a compatible profile/backend is explicitly validated. Universal enhancement of arbitrary future rendering engines cannot be promised.

## First milestone

The first plugin must only report lifecycle and title identity. It must not intercept GNM command submission, allocate GPU resources, rewrite VideoOut, change display modes, or alter frame timing.
