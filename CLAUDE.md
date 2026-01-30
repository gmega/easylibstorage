# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

storageconsole is a C11 interactive CLI application for managing a distributed storage node. It wraps an external `libstorage` library (Nim-based) through a command dispatch console.

## Build

Requires the `LOGOS_STORAGE_NIM_ROOT` environment variable pointing to the external storage library root (contains `library/libstorage.h` and platform-specific shared library).

```sh
cmake -B build -S .
cmake --build build
```

The build output is an executable named `storageconsole`.

## Architecture

- **main.c** — Entry point and interactive console. Implements a command dispatch loop using a static table of `command` structs mapping names to function pointers. The `console` struct holds an opaque `void *ctx` pointer to the storage node instance.
- **easylibstorage.h** — High-level wrapper API declarations over `libstorage`. Defines `STORAGE_NODE` (opaque pointer), `node_config`, `progress_callback`, and functions for node lifecycle (`e_storage_new/start/stop/destroy`) and data operations (`e_storage_upload/download`). These are declared but not all wired into console commands yet.
- **External dependency**: `libstorage` (platform-specific `.so`/`.dylib`/`.dll`) found via `LOGOS_STORAGE_NIM_ROOT`. Currently only `sync_start()` from `libstorage.h` is called directly.

## Code Style

Formatting is enforced via `.clang-format` (LLVM-based, 4-space indent, 120-char column limit).
