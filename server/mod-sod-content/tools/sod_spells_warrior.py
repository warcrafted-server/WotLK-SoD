#!/usr/bin/env python3
"""Warrior spell specs cloned from the highest WotLK ranks."""

from sod_dbc import *  # noqa: F401,F403  (shared WoW enum constants)


def build(idx):
    """Return Warrior spells cloned from the level-80 WotLK talent ranks."""
    return [
        {  # Devastate: retain the WotLK rank effects.
            "id": 403195, "client": True, "template": 47498,
            "skill_line": 257,
            "name": "Devastate", "inherit_server": True,
            "overrides": {"SpellLevel": 0},
        },
    ]
