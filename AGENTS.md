# AGENT QUICKSTART (pokeemerald-expansion)

Purpose: fast orientation for coding agents before implementing features.

## 0) Mandatory pre-flight (read before writing code)

1. Confirm branch intent (`master` = bugfix/docs/tests, `upcoming` = new features).
2. Read this file, then skim:
   - `README.md`
   - `INSTALL.md`
   - `docs/SUMMARY.md`
   - `docs/STYLEGUIDE.md`
3. Identify the feature area (battle, species, items, overworld, scripts, graphics, tests).
4. Find existing patterns in adjacent files before adding new logic.
5. Decide validation scope early (build-only, targeted tests, full `make check`).

---

## 1) What this repo is

`pokeemerald-expansion` is a decompilation-based GBA ROM hack engine built on pret's `pokeemerald`.
It is a development base, not a standalone game.

Key entry docs:
- `README.md` (project overview)
- `FEATURES.md` (feature catalog)
- `docs/SUMMARY.md` (documentation index)
- `CONTRIBUTING.md` (branching + contribution expectations)

---

## 2) Build and test commands (Linux)

### Build ROM
- `make`
- Output: `pokeemerald.gba`

### Helpful variants
- `make -j$(nproc)` (parallel build)
- `make debug` (debug-oriented build)
- `make release` (release-oriented build)
- `make tidy` (remove build outputs)
- `make clean` (full cleanup, tools/assets included)

### Run automated tests
- `make check -j` (all tests)
- `make check TESTS="Spikes"` (filter test names)
- `make pokeemerald-test.elf TESTS="Spikes"` (build test ROM ELF)

References:
- `docs/tutorials/how_to_testing_system.md`
- `Makefile` (`check`, `tidy*`, `debug`, `release` targets)

---

## 3) High-level code map

- `src/` → C engine logic (battle, overworld, menus, systems)
- `include/` → headers, constants, config toggles (`include/config/*.h`)
- `data/` → scripts, map/event/text/battle script data (`.s` and include tables)
- `graphics/` → sprites/UI/background assets
- `sound/` → audio assets and songs
- `test/` → test suites (especially battle mechanics)
- `docs/tutorials/` → implementation how-tos for common feature work

Commonly touched config toggles:
- `include/config/battle.h`
- `include/config/pokemon.h`
- `include/config/item.h`
- `include/config/overworld.h`
- `include/config/general.h`
- `include/config/debug.h`
- `include/config/test.h`

---

## 4) Feature implementation playbooks

## A) Add or modify a move
Start with tutorial:
- `docs/tutorials/how_to_new_move.md`

Usual files:
- `include/constants/moves.h` (move constants)
- `src/data/moves_info.h` (move data)
- `src/data/battle_move_effects.h` (effect to script mapping)
- `data/battle_scripts_1.s` (battle scripts)
- `src/battle_script_commands.c` and `src/battle_util.c` (effect logic)
- `data/battle_anim_scripts.s` (animations)

Validation:
- run related tests under `test/battle/**`
- add/adjust targeted tests when behavior changes

## B) Add a new species / forms
Start with tutorial:
- `docs/tutorials/how_to_new_pokemon.md`

Usual files:
- `include/constants/species.h`
- `src/data/pokemon/species_info.h`
- `src/data/pokemon/` (learnsets/evolutions/forms as needed)
- `graphics/pokemon/...` (sprites/palettes/icons)

Also check:
- species toggles in `include/config/species_enabled.h`
- Pokédex and encounter integration where relevant

## C) Add or modify scripts/events
Useful references:
- `data/event_scripts.s`
- `data/scripts/`
- `data/maps/` + generated map includes
- `data/specials.inc`
- `src/field_specials.c`
- `docs/tutorials/how_to_code_entry.md`

## D) Add/adjust trainer behavior or battle AI
Useful references:
- `docs/tutorials/ai_flags.md`
- `docs/tutorials/ai_logic.md`
- `docs/tutorials/ai_dynamic_functions.md`
- `test/battle/ai/`

## E) Add tests for mechanic changes
Use:
- `docs/tutorials/how_to_testing_system.md`
- Existing pattern files in `test/battle/` for the closest mechanic

Test style is `GIVEN / WHEN / SCENE / FINALLY` with `ASSUME` guards.

---

## 5) Style and safety rules

Code style source of truth:
- `docs/STYLEGUIDE.md`

Critical reminders:
- C/H files use 4 spaces; `.s`/`.inc` use tabs.
- Match established naming (`PascalCase` funcs/types, `camelCase` vars, `CAPS` macros).
- Prefer minimal, surgical changes over broad refactors.
- Reuse existing feature patterns in nearby files before inventing new structure.
- Do not renumber persisted IDs casually (species/items/moves constants can affect save compatibility).

---

## 6) Minimal workflow before every feature

1. Read this file and the relevant tutorial in `docs/tutorials/`.
2. Locate nearest existing implementation and copy its structure.
3. Implement smallest coherent change.
4. Build (`make -j$(nproc)`) and run targeted tests.
5. If battle/mechanic behavior changed, run `make check TESTS="<feature>"` (or broader if needed).
6. Summarize changed files + why + how validated.

---

## 7) Fast navigation links

- Build/install: `INSTALL.md`
- Docs index: `docs/SUMMARY.md`
- Testing tutorial: `docs/tutorials/how_to_testing_system.md`
- Move tutorial: `docs/tutorials/how_to_new_move.md`
- Species tutorial: `docs/tutorials/how_to_new_pokemon.md`
- Coding style: `docs/STYLEGUIDE.md`
- Contribution flow: `CONTRIBUTING.md`

If unsure where to implement a feature, search in `test/` first for similar mechanics and follow the production file references used by those tests.
