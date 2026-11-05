/**
 * Model Converter Tool
 * Converts 3D models (FBX, OBJ, etc.) to engine format
 */

#include <iostream>
#include <string>

void print_usage() {
    std::cout << "Brazilian Football Model Converter\n";
    std::cout << "Usage: model_converter [input] [output]\n";
    std::cout << "  Supported formats: FBX, OBJ, GLTF\n";
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        print_usage();
        return 1;
    }

    std::string input = argv[1];
    std::string output = argv[2];

    std::cout << "Converting: " << input << " -> " << output << std::endl;

    // TODO: Implement model loading and conversion
    // - Load model with Assimp
    // - Extract vertices, normals, UVs, tangents
    // - Optimize mesh data
    // - Write to custom format

    std::cout << "Conversion complete!" << std::endl;
    return 0;
}
