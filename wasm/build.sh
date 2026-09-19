#!/usr/bin/env bash
set -euo pipefail

# wasi-sdk 25.0 (clang 19.1.5). Override this when the SDK lives elsewhere.
WASI_SDK="${WASI_SDK:-/c/Users/user/.local/toolchains/wasi-sdk-25.0-x86_64-windows}"
CLANG="${WASI_SDK}/bin/clang.exe"

if [[ ! -x "$CLANG" ]]; then
  echo "wasi-sdk 25.0 compiler not found: $CLANG" >&2
  echo "Set WASI_SDK to the wasi-sdk installation directory." >&2
  exit 1
fi

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
OUTPUT_DIR="$ROOT_DIR/public/wasm"
mkdir -p "$OUTPUT_DIR"

"$CLANG" --target=wasm32-unknown-unknown -nostdlib -ffreestanding -O2 \
  -Wl,--no-entry -Wl,--export-memory -Wl,--strip-all \
  -o "$OUTPUT_DIR/usb_descriptor.wasm" "$ROOT_DIR/wasm/usb_descriptor.c"

echo "Built $OUTPUT_DIR/usb_descriptor.wasm ($(wc -c < "$OUTPUT_DIR/usb_descriptor.wasm") bytes)"
