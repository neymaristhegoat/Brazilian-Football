#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <typeindex>

namespace bf {
namespace resources {

enum class ResourceType {
    Texture,
    Mesh,
    Shader,
    Material,
    Audio,
    Font,
    Animation,
    Prefab,
    Scene
};

class Resource {
public:
    Resource(const std::string& path, ResourceType type)
        : m_Path(path), m_Type(type), m_Loaded(false) {}
    virtual ~Resource() = default;

    virtual bool Load() = 0;
    virtual void Unload() = 0;

    const std::string& GetPath() const { return m_Path; }
    ResourceType GetType() const { return m_Type; }
    bool IsLoaded() const { return m_Loaded; }

protected:
    std::string m_Path;
    ResourceType m_Type;
    bool m_Loaded;
};

class ResourceManager {
public:
    ResourceManager();
    ~ResourceManager();

    void Initialize();
    void Shutdown();

    template<typename T>
    std::shared_ptr<T> Load(const std::string& path);

    template<typename T>
    std::shared_ptr<T> Get(const std::string& path);

    void Unload(const std::string& path);
    void UnloadAll();

    void SetAssetDirectory(const std::string& directory);
    std::string GetAssetPath(const std::string& relativePath) const;

private:
    std::string m_AssetDirectory;
    std::unordered_map<std::string, std::shared_ptr<Resource>> m_Resources;
};

} // namespace resources
} // namespace bf
