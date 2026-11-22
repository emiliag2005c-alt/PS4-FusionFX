#!/bin/sh
set -eu

ROOT="$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)"
OUT="$ROOT/tests/.process_identity_test"
trap 'rm -f "$OUT"' EXIT

CC_BIN="${CC:-cc}"
"$CC_BIN" -std=c11 -Wall -Wextra -Werror \
  -I"$ROOT/tests/stubs" -I"$ROOT/src/discovery" \
  "$ROOT/src/discovery/process_identity.c" \
  "$ROOT/tests/test_process_identity.c" \
  -o "$OUT"

"$OUT"
python3 "$ROOT/tools/validate_profile.py" "$ROOT/profiles/default.json"
python3 -m unittest discover -s "$ROOT/tests" -p 'test_*.py' -v
