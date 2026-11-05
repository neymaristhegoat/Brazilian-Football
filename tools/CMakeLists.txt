cmake_minimum_required(VERSION 3.20)

# Development tools

# Model Converter Tool
add_executable(ModelConverter
    model_converter/main.cpp
    model_converter/ModelLoader.cpp
    model_converter/ModelExporter.cpp
)

target_link_libraries(ModelConverter PRIVATE BFEngine)

# Texture Packer Tool
add_executable(TexturePacker
    texture_packer/main.cpp
    texture_packer/TexturePacker.cpp
)

target_link_libraries(TexturePacker PRIVATE BFEngine)

# Asset Baker Tool
add_executable(AssetBaker
    asset_baker/main.cpp
    asset_baker/AssetBaker.cpp
)

target_link_libraries(AssetBaker PRIVATE BFEngine)

# Install tools
install(TARGETS ModelConverter TexturePacker AssetBaker
    RUNTIME DESTINATION tools
)
