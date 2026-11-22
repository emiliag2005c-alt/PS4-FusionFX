import json
import tempfile
import unittest
from pathlib import Path

from tools.validate_profile import validate


VALID = {
    "schema_version": 1,
    "profile_id": "default-native",
    "title_id": "*",
    "enabled": True,
    "mode": "native_passthrough",
    "features": {
        "scaling": False,
        "temporal_reconstruction": False,
        "frame_generation": False,
        "frame_pacing": False
    },
    "requirements": {
        "firmware_allowlist": [],
        "game_update_allowlist": [],
        "backend": None
    },
    "notes": "safe fallback"
}


class ProfileValidationTests(unittest.TestCase):
    def validate_data(self, data):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "profile.json"
            path.write_text(json.dumps(data), encoding="utf-8")
            return validate(path)

    def test_accepts_native_default(self):
        self.assertEqual(self.validate_data(VALID), [])

    def test_rejects_unknown_top_level_key(self):
        data = dict(VALID, surprise=True)
        self.assertTrue(any("unknown top-level" in e for e in self.validate_data(data)))

    def test_rejects_enabled_experimental_feature(self):
        data = json.loads(json.dumps(VALID))
        data["features"]["frame_generation"] = "yes"
        self.assertTrue(any("must be boolean" in e for e in self.validate_data(data)))

    def test_rejects_unsupported_mode(self):
        data = dict(VALID, mode="experimental")
        self.assertTrue(any("only native_passthrough" in e for e in self.validate_data(data)))


if __name__ == "__main__":
    unittest.main()
