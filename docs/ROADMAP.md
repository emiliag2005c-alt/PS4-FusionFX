# Roadmap

## M0 — Research and build reproducibility
- [ ] Pin GoldHEN Plugins SDK revision.
- [ ] Pin OpenOrbis toolchain revision and compiler version.
- [ ] Verify plugin entry points and callback ABI against SDK examples.
- [ ] Verify firmware 13.02 compatibility.
- [ ] Record license obligations for every reused project.

## M1 — Read-only discovery
- [ ] Plugin loads and unloads cleanly.
- [ ] Log title/process identity using documented APIs.
- [ ] No graphics hooks, GPU allocations, VideoOut changes, or game-memory writes.
- [ ] Unknown title remains untouched.
- [ ] Provide disable/unload and recovery instructions.

## M2 — Profile system
- [ ] Validate schema and reject unknown feature flags.
- [ ] Match title ID and game update/build where possible.
- [ ] Default every feature to disabled.
- [ ] Add a host-side profile validator and tests.

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
No binary release until the exact SDK build succeeds, ABI is verified, console/firmware compatibility is documented, and recovery has been tested.
