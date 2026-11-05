cmake_minimum_required(VERSION 3.20)

# Development tools - only build if source files exist

# Model Converter Tool
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/model_converter/main.cpp)
    add_executable(ModelConverter
        model_converter/main.cpp
    )
    target_link_libraries(ModelConverter PRIVATE BFEngine)
    
    install(TARGETS ModelConverter
        RUNTIME DESTINATION tools
    )
    message(STATUS "ModelConverter will be built")
else()
    message(STATUS "ModelConverter source not found, skipping")
endif()

# Texture Packer Tool
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/texture_packer/main.cpp)
    add_executable(TexturePacker
        texture_packer/main.cpp
    )
    target_link_libraries(TexturePacker PRIVATE BFEngine)
    
    install(TARGETS TexturePacker
        RUNTIME DESTINATION tools
    )
    message(STATUS "TexturePacker will be built")
else()
    message(STATUS "TexturePacker source not found, skipping")
endif()

# Asset Baker Tool
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/asset_baker/main.cpp)
    add_executable(AssetBaker
        asset_baker/main.cpp
    )
    target_link_libraries(AssetBaker PRIVATE BFEngine)
    
    install(TARGETS AssetBaker
        RUNTIME DESTINATION tools
    )
    message(STATUS "AssetBaker will be built")
else()
    message(STATUS "AssetBaker source not found, skipping")
endif()
