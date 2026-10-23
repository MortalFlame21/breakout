#include <string_view>

#include <miniaudio/miniaudio.h>

class AudioEngine {
public:
    static void init() {
        get();
    }

    static AudioEngine& get() {
        static AudioEngine audio_engine;
        return audio_engine;
    }

    ~AudioEngine() {
        ma_engine_uninit(&_engine);
    }

    void playSound(std::string_view path) {
        ma_engine_play_sound(&_engine, path.data(), nullptr);
    }
private:
    AudioEngine() {
        auto result{ma_engine_init(nullptr, &_engine)};
        if (result != MA_SUCCESS)
            throw std::runtime_error("Error: Failed to initialize audio engine");
    }

    ma_engine _engine{};
};