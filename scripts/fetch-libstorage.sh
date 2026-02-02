#!/usr/bin/env bash
set -euo pipefail

LIBSTORAGE_VERSION="v0.3.1"

# --- Detect OS ---
case "$(uname -s)" in
    Linux)  OS="linux" ;;
    Darwin) OS="darwin" ;;
    *)      echo "Error: unsupported OS '$(uname -s)'" >&2; exit 1 ;;
esac

# --- Detect architecture ---
case "$(uname -m)" in
    x86_64)         ARCH="amd64" ;;
    aarch64|arm64)  ARCH="arm64" ;;
    *)              echo "Error: unsupported architecture '$(uname -m)'" >&2; exit 1 ;;
esac

# --- Check dependencies ---
for cmd in curl unzip; do
    if ! command -v "$cmd" &>/dev/null; then
        echo "Error: '$cmd' is required but not found" >&2
        exit 1
    fi
done

# --- Construct URL and destination ---
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
DEST_DIR="${SCRIPT_DIR}/../libstorage"
ZIP_NAME="libstorage-${OS}-${ARCH}-${LIBSTORAGE_VERSION}.zip"
URL="https://github.com/logos-storage/logos-storage-nim/releases/download/${LIBSTORAGE_VERSION}/${ZIP_NAME}"

echo "Fetching ${ZIP_NAME} ..."

# --- Download to temp file ---
TMPFILE="$(mktemp)"
trap 'rm -f "$TMPFILE"' EXIT

if ! curl -fSL -o "$TMPFILE" "$URL"; then
    echo "Error: failed to download ${URL}" >&2
    exit 1
fi

# --- Prepare destination ---
rm -rf "$DEST_DIR"
mkdir -p "${DEST_DIR}/library" "${DEST_DIR}/build"

# --- Extract ---
TMPDIR_EXTRACT="$(mktemp -d)"
trap 'rm -f "$TMPFILE"; rm -rf "$TMPDIR_EXTRACT"' EXIT

unzip -q -o "$TMPFILE" -d "$TMPDIR_EXTRACT"

# --- Place files into expected layout ---
# Determine shared library extension
case "$OS" in
    linux)  LIB_EXT="so" ;;
    darwin) LIB_EXT="dylib" ;;
esac

cp "${TMPDIR_EXTRACT}/libstorage.h"       "${DEST_DIR}/library/"
cp "${TMPDIR_EXTRACT}/libstorage.${LIB_EXT}" "${DEST_DIR}/build/"

echo ""
echo "libstorage ${LIBSTORAGE_VERSION} installed to: ${DEST_DIR}"
echo ""
echo "Use with cmake:"
echo "  cmake -B build -S . -DLOGOS_STORAGE_NIM_ROOT=${DEST_DIR}"
