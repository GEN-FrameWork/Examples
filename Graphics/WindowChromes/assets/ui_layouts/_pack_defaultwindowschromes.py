#!/usr/bin/env python3
"""Rebuild defaultwindowschromes.zip from the source folder and copy to GEN examples."""

import os
import shutil
import zipfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[4]  # Examples/Graphics/WindowChromes/assets/ui_layouts -> GEN_FrameWork
# parents: ui_layouts=0, assets=1, WindowChromes=2, Graphics=3, Examples=4 — need GEN_FrameWork = parents[5]
ROOT = Path(__file__).resolve().parents[5]

SRC = Path(__file__).resolve().parent / "defaultwindowschromes"

TARGETS = [
    ROOT / "Examples/Graphics/WindowChromes/assets/ui_layouts/defaultwindowschromes.zip",
    ROOT / "Examples/Graphics/UI_System/assets/ui_layouts/defaultwindowschromes.zip",
    ROOT / "Examples/Graphics/UI_Options/assets/ui_layouts/defaultwindowschromes.zip",
    ROOT / "Examples/Graphics/Canvas2D/assets/ui_layouts/defaultwindowschromes.zip",
]


def build_zip(zip_path: Path) -> None:
    if zip_path.exists():
        zip_path.unlink()

    with zipfile.ZipFile(zip_path, "w", compression=zipfile.ZIP_DEFLATED) as zf:
        for root, dirs, files in os.walk(SRC):
            dirs[:] = [d for d in dirs if d not in ("__MACOSX", ".git")]
            for name in files:
                if name.startswith("."):
                    continue
                full = Path(root) / name
                rel = full.relative_to(SRC).as_posix()
                zf.write(full, rel)

    with zipfile.ZipFile(zip_path) as zf:
        names = zf.namelist()
        xml = zf.read("defaultwindowschromes.xml").decode("utf-8")

    if 'width="1024"' in xml:
        raise SystemExit(f"ERROR: {zip_path} still contains hardcoded width=1024")
    if 'role="caption"' not in xml:
        raise SystemExit(f"ERROR: {zip_path} missing role=caption")

    fonts = [n for n in names if n.startswith("fonts/")]
    print(f"OK {zip_path}  ({len(names)} entries, {zip_path.stat().st_size} bytes)")
    print(f"   fonts: {fonts}")


def main() -> None:
    if not SRC.is_dir():
        raise SystemExit(f"Source folder missing: {SRC}")

    for target in TARGETS:
        target.parent.mkdir(parents=True, exist_ok=True)
        build_zip(target)

    print("All defaultwindowschromes.zip targets updated.")


if __name__ == "__main__":
    main()
