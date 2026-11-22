# Profile format v1

Profiles are declarative policy, not executable patches.

Required fields:
- `schema_version`: integer, currently 1.
- `profile_id`: stable identifier.
- `title_id`: exact title ID, or `*` for native fallback.
- `enabled`: boolean.
- `mode`: currently only `native_passthrough` is accepted for the default profile.
- `features`: explicit boolean switches.
- `requirements`: firmware/update allowlists and backend identifier.

All experimental feature switches default to false. A profile must not activate an experimental backend merely because a title ID matches. Runtime capability checks and a separately verified backend are required.

Unknown fields and unsupported modes should be rejected by the validator.
