/**
 * Asset Baker Tool
 * Pre-processes and optimizes game assets for distribution
 */

#include <iostream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

void print_usage() {
    std::cout << "Brazilian Football Asset Baker\n";
    std::cout << "Usage: asset_baker --input [dir] --output [dir]\n";
    std::cout << "  Bakes assets for optimal runtime performance\n";
}

void bake_directory(const fs::path& input, const fs::path& output) {
    std::cout << "Baking assets from: " << input << std::endl;

    for (const auto& entry : fs::recursive_directory_iterator(input)) {
        if (entry.is_regular_file()) {
            auto ext = entry.path().extension();
            
            std::cout << "  Processing: " << entry.path().filename() << std::endl;

            // TODO: Process different file types
            if (ext == ".fbx" || ext == ".obj") {
                // Convert models
            } else if (ext == ".png" || ext == ".jpg") {
                // Compress textures
            } else if (ext == ".wav" || ext == ".ogg") {
                // Compress audio
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 5) {
        print_usage();
        return 1;
    }

    fs::path input_dir;
    fs::path output_dir;

    // Parse arguments
    for (int i = 1; i < argc; i += 2) {
        std::string arg = argv[i];
        if (arg == "--input") {
            input_dir = argv[i + 1];
        } else if (arg == "--output") {
            output_dir = argv[i + 1];
        }
    }

    if (!fs::exists(input_dir)) {
        std::cerr << "Input directory does not exist!" << std::endl;
        return 1;
    }

    fs::create_directories(output_dir);

    bake_directory(input_dir, output_dir);

    std::cout << "Asset baking complete!" << std::endl;
    return 0;
}
