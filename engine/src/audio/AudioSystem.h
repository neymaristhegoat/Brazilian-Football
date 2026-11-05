#pragma once

#include <string>
#include <memory>
#include <vector>

namespace bf {
namespace audio {

enum class AudioFormat {
    Mono8,
    Mono16,
    Stereo8,
    Stereo16
};

class AudioBuffer {
public:
    AudioBuffer();
    ~AudioBuffer();

    bool LoadFromFile(const std::string& filepath);
    bool LoadFromMemory(const void* data, size_t size, AudioFormat format, int sampleRate);

    uint32_t GetID() const { return m_BufferID; }

private:
    uint32_t m_BufferID;
};

class AudioSource {
public:
    AudioSource();
    ~AudioSource();

    void SetBuffer(const AudioBuffer* buffer);
    void Play();
    void Pause();
    void Stop();

    void SetLooping(bool loop);
    void SetVolume(float volume);
    void SetPitch(float pitch);
    void SetPosition(float x, float y, float z);
    void SetVelocity(float x, float y, float z);

    bool IsPlaying() const;

private:
    uint32_t m_SourceID;
};

class AudioListener {
public:
    static void SetPosition(float x, float y, float z);
    static void SetVelocity(float x, float y, float z);
    static void SetOrientation(float forwardX, float forwardY, float forwardZ,
                              float upX, float upY, float upZ);
    static void SetGain(float gain);
};

class AudioSystem {
public:
    AudioSystem();
    ~AudioSystem();

    bool Initialize();
    void Shutdown();
    void Update(float deltaTime);

    std::shared_ptr<AudioBuffer> LoadSound(const std::string& filepath);
    std::shared_ptr<AudioSource> CreateSource();

    void SetMasterVolume(float volume);
    float GetMasterVolume() const { return m_MasterVolume; }

private:
    void* m_Device;
    void* m_Context;
    float m_MasterVolume;
    
    std::vector<std::shared_ptr<AudioBuffer>> m_Buffers;
    std::vector<std::shared_ptr<AudioSource>> m_Sources;
};

} // namespace audio
} // namespace bf
