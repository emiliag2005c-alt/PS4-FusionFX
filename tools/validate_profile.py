#!/usr/bin/env python3
"""Validate conservative FusionFX JSON profiles using only the Python standard library."""
import json
import sys
from pathlib import Path

TOP_LEVEL = {
    "schema_version", "profile_id", "title_id", "enabled", "mode",
    "features", "requirements", "notes"
}
FEATURES = {
    "scaling", "temporal_reconstruction", "frame_generation", "frame_pacing"
}
REQUIREMENTS = {"firmware_allowlist", "game_update_allowlist", "backend"}


def validate(path: Path) -> list[str]:
    errors: list[str] = []
    try:
        data = json.loads(path.read_text(encoding="utf-8"))
    except (OSError, json.JSONDecodeError) as exc:
        return [f"cannot read valid JSON: {exc}"]

    if not isinstance(data, dict):
        return ["profile root must be an object"]

    unknown = set(data) - TOP_LEVEL
    if unknown:
        errors.append(f"unknown top-level keys: {sorted(unknown)}")

    if data.get("schema_version") != 1:
        errors.append("schema_version must be 1")
    for key in ("profile_id", "title_id", "mode"):
        if not isinstance(data.get(key), str) or not data[key].strip():
            errors.append(f"{key} must be a non-empty string")
    if not isinstance(data.get("enabled"), bool):
        errors.append("enabled must be boolean")

    if data.get("mode") != "native_passthrough":
        errors.append("only native_passthrough is accepted by validator v1")

    features = data.get("features")
    if not isinstance(features, dict):
        errors.append("features must be an object")
    else:
        if set(features) - FEATURES:
            errors.append(f"unknown feature keys: {sorted(set(features) - FEATURES)}")
        for key in FEATURES:
            if key not in features or not isinstance(features[key], bool):
                errors.append(f"features.{key} must be boolean")

    req = data.get("requirements")
    if not isinstance(req, dict):
        errors.append("requirements must be an object")
    else:
        if set(req) - REQUIREMENTS:
            errors.append(f"unknown requirement keys: {sorted(set(req) - REQUIREMENTS)}")
        for key in ("firmware_allowlist", "game_update_allowlist"):
            if not isinstance(req.get(key), list) or not all(isinstance(x, str) for x in req[key]):
                errors.append(f"requirements.{key} must be a list of strings")
        if req.get("backend") is not None and not isinstance(req.get("backend"), str):
            errors.append("requirements.backend must be a string or null")

    if data.get("title_id") == "*" and data.get("mode") != "native_passthrough":
        errors.append("wildcard title profile must use native_passthrough")
    return errors


def main() -> int:
    if len(sys.argv) != 2:
        print(f"usage: {Path(sys.argv[0]).name} PROFILE.json", file=sys.stderr)
        return 2
    path = Path(sys.argv[1])
    errors = validate(path)
    if errors:
        for error in errors:
            print(f"ERROR: {error}", file=sys.stderr)
        return 1
    print(f"OK: {path}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
