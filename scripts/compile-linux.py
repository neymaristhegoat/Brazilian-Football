#!/usr/bin/env python3
"""
Brazilian Football - Linux Compilation Script
Compiles the game for Linux platforms with better error handling
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
    if result.stdout:
        print(result.stdout)
    return True

def check_dependencies():
    """Check if required dependencies are installed"""
    print("Checking dependencies...")
    
    deps = {
        'cmake': 'CMake',
        'pkg-config': 'pkg-config',
        'g++': 'C++ compiler'
    }
    
    missing = []
    for cmd, name in deps.items():
        try:
            subprocess.run([cmd, '--version'], capture_output=True, check=True)
            print(f"  ✓ {name} found")
        except (subprocess.CalledProcessError, FileNotFoundError):
            print(f"  ✗ {name} not found")
            missing.append(name)
    
    # Check pkg-config packages
    pkg_deps = {
        'glfw3': 'GLFW',
        'glew': 'GLEW'
    }
    
    for pkg, name in pkg_deps.items():
        try:
            result = subprocess.run(['pkg-config', '--exists', pkg], 
                                  capture_output=True)
            if result.returncode == 0:
                print(f"  ✓ {name} found")
            else:
                print(f"  ✗ {name} not found")
                missing.append(name)
        except FileNotFoundError:
            print(f"  ✗ Cannot check {name} (pkg-config missing)")
            if name not in missing:
                missing.append(name)
    
    if missing:
        print(f"\n❌ Missing dependencies: {', '.join(missing)}")
        print("\nTo install them, run:")
        print("  ./scripts/install-dependencies.sh")
        return False
    
    print("✓ All dependencies found\n")
    return True

def compile_linux(build_type="Release", clean=False):
    """Compile the game for Linux"""
    print(f"Compiling Brazilian Football for Linux ({build_type})...\n")
    
    project_root = Path(__file__).parent.parent
    build_dir = project_root / "build" / "linux"
    
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
        f"-DCMAKE_BUILD_TYPE={build_type}",
        "-DBUILD_TESTS=ON",
        "-DBUILD_TOOLS=ON"
    ]
    
    print("Configuring with CMake...")
    if not run_command(cmake_args):
        print("\n❌ CMake configuration failed!")
        print("\nTroubleshooting:")
        print("1. Make sure dependencies are installed:")
        print("   ./scripts/install-dependencies.sh")
        print("2. Check the error messages above")
        print("3. Try a clean build:")
        print("   python3 scripts/compile-linux.py --clean")
        return False
    
    # Build
    cpu_count = os.cpu_count() or 4
    build_args = [
        "cmake",
        "--build", str(build_dir),
        "--config", build_type,
        "-j", str(cpu_count)
    ]
    
    print(f"\nBuilding with {cpu_count} parallel jobs...")
    if not run_command(build_args):
        print("\n❌ Build failed!")
        print("\nCheck the compiler errors above.")
        return False
    
    # Find the binary
    bin_locations = [
        build_dir / "bin" / "BrazilianFootball",
        project_root / "bin" / "BrazilianFootball"
    ]
    
    binary_found = False
    for bin_path in bin_locations:
        if bin_path.exists():
            print(f"\n✓ Build successful!")
            print(f"Binary location: {bin_path}")
            binary_found = True
            break
    
    if not binary_found:
        print(f"\n⚠ Build may have succeeded but binary not found at expected locations")
        print(f"Expected: {build_dir}/bin/BrazilianFootball")
    
    return True

def main():
    parser = argparse.ArgumentParser(
        description="Compile Brazilian Football for Linux",
        epilog="Example: python3 scripts/compile-linux.py --debug --clean"
    )
    parser.add_argument("--debug", action="store_true", 
                       help="Build in Debug mode (default: Release)")
    parser.add_argument("--clean", action="store_true", 
                       help="Clean build directory before building")
    parser.add_argument("--skip-deps-check", action="store_true",
                       help="Skip dependency checking (not recommended)")
    
    args = parser.parse_args()
    
    # Check dependencies unless skipped
    if not args.skip_deps_check:
        if not check_dependencies():
            sys.exit(1)
    
    build_type = "Debug" if args.debug else "Release"
    success = compile_linux(build_type, args.clean)
    
    sys.exit(0 if success else 1)

if __name__ == "__main__":
    main()
