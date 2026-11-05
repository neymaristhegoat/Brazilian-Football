/**
 * Texture Packer Tool
 * Packs multiple textures into texture atlases
 */

#include <iostream>
#include <string>
#include <vector>

void print_usage() {
    std::cout << "Brazilian Football Texture Packer\n";
    std::cout << "Usage: texture_packer --input [dir] --output [file]\n";
    std::cout << "  Packs textures from directory into a single atlas\n";
}

int main(int argc, char* argv[]) {
    if (argc < 5) {
        print_usage();
        return 1;
    }

    std::string input_dir;
    std::string output_file;

    // Parse arguments
    for (int i = 1; i < argc; i += 2) {
        std::string arg = argv[i];
        if (arg == "--input") {
            input_dir = argv[i + 1];
        } else if (arg == "--output") {
            output_file = argv[i + 1];
        }
    }

    std::cout << "Packing textures from: " << input_dir << std::endl;
    std::cout << "Output: " << output_file << std::endl;

    // TODO: Implement texture packing
    // - Scan directory for images
    // - Pack using rectangle bin packing algorithm
    // - Generate UV coordinates
    // - Write atlas and metadata

    std::cout << "Packing complete!" << std::endl;
    return 0;
}
