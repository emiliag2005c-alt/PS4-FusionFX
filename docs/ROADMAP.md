# Roadmap

## M0 — Research and build reproducibility
- [ ] Pin GoldHEN Plugins SDK revision.
- [ ] Pin OpenOrbis toolchain revision and compiler version.
- [ ] Verify plugin entry points and callback ABI against a known working plugin.
- [ ] Verify firmware 13.02 compatibility.
- [x] Record initial license and interface audit notes.

## M1 — Read-only discovery
- [x] Implement a host-testable wrapper around GoldHEN process-info API.
- [x] Validate fixed-size process strings and fail closed on API/data errors.
- [x] Add host C tests for valid identity and failure cases.
- [ ] Verify process-info call context on a real GoldHEN plugin.
- [ ] Implement verified plugin load/unload lifecycle.
- [ ] Build PRX with OpenOrbis and test on console.
- [ ] Provide disable/unload and recovery instructions.

## M2 — Profile system
- [x] Define conservative native-pass-through profile schema.
- [x] Validate schema and reject unknown feature flags.
- [x] Add host-side profile validator and tests.
- [ ] Match discovered title ID and game update/build to profiles at runtime.
- [ ] Keep every experimental feature disabled unless explicitly validated.

## M3 — Capability research
- [ ] Map PS4 display/scaling paths from public technical references.
- [ ] Compare existing projects without assuming compatibility.
- [ ] Separate spatial scaling, temporal reconstruction, optical flow, and frame pacing.
- [ ] Measure image quality, latency, frame pacing, and stability.

## M4 — Isolated experiments
- [ ] One backend at a time.
- [ ] Explicit per-title opt-in.
- [ ] Reversible configuration and safe fallback.
- [ ] Publish test conditions and measured results.

## Release criteria
No binary release until the exact SDK build succeeds, ABI and lifecycle are verified, firmware compatibility is documented, and recovery has been tested.
