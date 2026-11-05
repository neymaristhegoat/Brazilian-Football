#!/usr/bin/env python3
"""
Brazilian Football - macOS Compilation Script
Compiles the game for macOS platforms
"""

import os
import sys
import subprocess
import argparse
from pathlib import Path

def run_command(cmd, cwd=None):
    """Run a shell command and return the result"""
    print(f"Running: {' '.join(cmd)}")
    result = subprocess.run(cmd, cwd=cwd, capture_output=True, text=True)
    if result.returncode != 0:
        print(f"Error: {result.stderr}")
        return False
    print(result.stdout)
    return True

def compile_macos(build_type="Release", clean=False):
    """Compile the game for macOS"""
    print(f"Compiling Brazilian Football for macOS ({build_type})...")
    
    project_root = Path(__file__).parent.parent
    build_dir = project_root / "build" / "macos"
    
    # Clean build directory if requested
    if clean and build_dir.exists():
        print("Cleaning build directory...")
        import shutil
        shutil.rmtree(build_dir)
    
    # Create build directory
    build_dir.mkdir(parents=True, exist_ok=True)
    
    # CMake configuration
    cmake_args = [
        "cmake",
        "-S", str(project_root),
        "-B", str(build_dir),
        "-G", "Xcode",
        f"-DCMAKE_BUILD_TYPE={build_type}",
        "-DCMAKE_OSX_ARCHITECTURES=arm64;x86_64",  # Universal binary
        "-DBUILD_TESTS=ON",
        "-DBUILD_TOOLS=ON"
    ]
    
    if not run_command(cmake_args):
        print("CMake configuration failed!")
        return False
    
    # Build
    build_args = [
        "cmake",
        "--build", str(build_dir),
        "--config", build_type,
        "-j", str(os.cpu_count())
    ]
    
    if not run_command(build_args):
        print("Build failed!")
        return False
    
    # Create .app bundle if needed
    # TODO: Bundle resources into .app
    
    print(f"\nBuild successful! Binary location: {build_dir}/bin/")
    return True

def main():
    parser = argparse.ArgumentParser(description="Compile Brazilian Football for macOS")
    parser.add_argument("--debug", action="store_true", help="Build in Debug mode")
    parser.add_argument("--clean", action="store_true", help="Clean build directory before building")
    
    args = parser.parse_args()
    
    build_type = "Debug" if args.debug else "Release"
    success = compile_macos(build_type, args.clean)
    
    sys.exit(0 if success else 1)

if __name__ == "__main__":
    main()
