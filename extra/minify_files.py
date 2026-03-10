import shutil
from pathlib import Path
from subprocess import run

WEB_DIR = Path("web")
DIST_DIR = WEB_DIR / "dist"
DATA_DIR = Path("data")

ICON_SRC = WEB_DIR / "icon.svg"
ICON_DEST = DATA_DIR / "icon.svg"

print("🧠 Running webpack build...")

run(["npx", "webpack"], cwd=WEB_DIR, check=True)

print("📦 Webpack build finished")

# limpa data
if DATA_DIR.exists():
    shutil.rmtree(DATA_DIR)

DATA_DIR.mkdir(parents=True, exist_ok=True)

print("📂 Copying dist -> data")

shutil.copytree(DIST_DIR, DATA_DIR, dirs_exist_ok=True)

# copia o icon.svg
if ICON_SRC.exists():
    shutil.copy2(ICON_SRC, ICON_DEST)
    print("🖼 icon.svg copied")

print("✅ Web assets ready for PlatformIO")
