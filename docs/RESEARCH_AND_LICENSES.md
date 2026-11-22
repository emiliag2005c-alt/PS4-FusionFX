# Research notes and license audit

This document is a working checklist, not an endorsement or compatibility claim.

## GnmScale profile collection

Repository: https://github.com/FrankBarretta/GnmScale-Game-Profiles

- Treat this as a collection of game profiles, not proof that the scaling engine is included.
- Profile labels or identifiers are not proof of official AMD FSR or NVIDIA DLSS implementation.
- Before reuse, inspect the actual engine, profile format, attribution, and license.
- Do not copy profile data until its license and provenance are clear.

## VCFG

Repository: https://github.com/Melnikoff07/vcfg

- Investigate the read-only discovery approach separately from experimental rendering features.
- Verify exact source revision, supported firmware, title/update restrictions, plugin ABI, and license before adapting.
- Do not assume optical-flow frame generation is safe or universal.
- Preserve required MIT license and copyright notices if MIT-licensed code is reused.

## XeMoFX

Repository: https://github.com/Phoenixx1202/XeMoFX

- License is custom; read the exact license text before copying or distributing code.
- Do not bundle or redistribute code until all conditions are understood and satisfied.
- Record attribution and any source-availability or non-commercial restrictions that apply.

## GoldHEN Plugins SDK

Repository: https://github.com/GoldHEN/GoldHEN_Plugins_SDK

- This is the authoritative starting point for plugin interfaces.
- Pin a specific revision before implementation.
- Verify every symbol, structure, callback, and entry point against headers and working examples.
- Do not rely on guessed API names or signatures.

## OpenOrbis PS4 Toolchain

Repository: https://github.com/OpenOrbis/OpenOrbis-PS4-Toolchain

- Pin the toolchain version.
- Record compiler/linker versions and required environment variables.
- A host compiler syntax check is not equivalent to a PS4 PRX build.

## Terminology

FusionFX does not claim DLSS support. Spatial scaling, temporal reconstruction, optical flow/frame generation, and frame pacing are distinct techniques and must be evaluated independently.

## Audit status

No third-party rendering code is currently vendored. No third-party binary is bundled. All integration work is blocked on source-level and license review.
