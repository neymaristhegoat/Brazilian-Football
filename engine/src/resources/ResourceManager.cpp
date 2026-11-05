#include "resources/ResourceManager.h"
#include "core/Logger.h"

namespace bf {
namespace resources {

ResourceManager::ResourceManager()
    : m_AssetDirectory("assets/")
{
}

ResourceManager::~ResourceManager() {
    UnloadAll();
}

void ResourceManager::Initialize() {
    BF_LOG_INFO("Initializing resource manager...");
}

void ResourceManager::Shutdown() {
    BF_LOG_INFO("Shutting down resource manager...");
    UnloadAll();
}

void ResourceManager::Unload(const std::string& path) {
    auto it = m_Resources.find(path);
    if (it != m_Resources.end()) {
        it->second->Unload();
        m_Resources.erase(it);
        BF_LOG_DEBUG("Unloaded resource: {}", path);
    }
}

void ResourceManager::UnloadAll() {
    for (auto& pair : m_Resources) {
        pair.second->Unload();
    }
    m_Resources.clear();
    BF_LOG_INFO("Unloaded all resources");
}

void ResourceManager::SetAssetDirectory(const std::string& directory) {
    m_AssetDirectory = directory;
    if (!m_AssetDirectory.empty() && m_AssetDirectory.back() != '/') {
        m_AssetDirectory += '/';
    }
}

std::string ResourceManager::GetAssetPath(const std::string& relativePath) const {
    return m_AssetDirectory + relativePath;
}

} // namespace resources
} // namespace bf
