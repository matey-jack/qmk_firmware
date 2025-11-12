# Repository Guidelines

## Project Structure & Module Organization
QMK firmware lives primarily in C under `quantum/`, `tmk_core/`, and per-keyboard folders inside `keyboards/`. Shared hardware drivers sit in `drivers/` and cross-platform hooks in `platforms/`. User-specific layouts belong in `users/<github_handle>/`, while JSON-driven community layouts are under `layouts/`. Python utilities powering the `qmk` CLI are located in `lib/python/qmk/`. Documentation updates should target `docs/`, and automated checks and fixtures are kept in `tests/`. Keep ancillary assets (images, UF2 builds, etc.) out of core directories unless they are referenced by the firmware build.

## Build, Test, and Development Commands
- `qmk compile -kb <keyboard> -km <keymap>`: one-shot build using the configured toolchain.
- `make <keyboard>:<keymap>`: legacy build path; useful when scripting matrix builds.
- `qmk flash -kb <keyboard> -km <keymap>`: compile and immediately flash the connected board.
- `qmk lint -kb <keyboard> [-km <keymap>]`: validate keyboard metadata and enforce required files.
- `qmk format-c <paths>` / `qmk format-python <paths>`: apply project formatting before committing.
- `qmk doctor`: confirm your environment before filing build issues.

## Coding Style & Naming Conventions
Match the language-specific guides in `docs/coding_conventions_c.md` and `docs/coding_conventions_python.md`. C code uses four-space indentation, mandatory braces, and `snake_case` identifiers; constants and enums stay uppercase. Keep configuration defines scoped by prefixing with the keyboard or feature name (for example, `#define CRKBD_RGB_MATRIX`). Python modules follow `snake_case` filenames and prefer docstrings over inline comments; run the provided formatters instead of hand-tweaking style.

## Testing Guidelines
Unit tests run through `./venv/bin/qmk test-c`.
For firmware, build the affected keyboard/keymap combinations locally and attach compile logs when CI cannot exercise custom hardware. Use `qmk lint` early to catch metadata regressions, and add docs or sample keymaps under `tests/` when introducing new features.

## Commit & Pull Request Guidelines
Structure commits around logical scopes and title them `<area>: <summary>` (e.g., `keyboards/crkbd: add tap dance helper`). Reference GitHub issues in the body when applicable. Before opening a PR, run `qmk compile`, `qmk lint`, and `qmk format-*` on touched paths, and note any deviations in the description. Pull requests should summarize user-facing impact, link relevant docs, and include proof of hardware testing or simulation. Screenshots or UF2 artifacts belong in the PR attachments, not the repository. Expect maintainers to request squashing if commits are noisy or unrelated.
