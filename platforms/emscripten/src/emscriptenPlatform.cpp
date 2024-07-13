#include "emscriptenPlatform.h"
#include "gl/hardware.h"
#include "log.h"
#include <stdio.h>
#include <stdarg.h>

#include <GLFW/glfw3.h>

#define DEFAULT "res/fonts/NotoSans-Regular.ttf"
#define FONT_AR "res/fonts/NotoNaskh-Regular.ttf"
#define FONT_HE "res/fonts/NotoSansHebrew-Regular.ttf"
#define FONT_JA "res/fonts/DroidSansJapanese.ttf"
#define FALLBACK "res/fonts/DroidSansFallback.ttf"

namespace Tangram {

void logMsg(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
}

EmscriptenPlatform::EmscriptenPlatform() {}

// EmscriptenPlatform::EmscriptenPlatform(UrlClient::Options urlClientOptions) :
    // m_urlClient(std::make_unique<UrlClient>(urlClientOptions)) {
// }

EmscriptenPlatform::~EmscriptenPlatform() {}

void EmscriptenPlatform::shutdown() {
    // Stop all UrlWorker threads
    // m_urlClient.reset();

    Platform::shutdown();
}

void EmscriptenPlatform::requestRender() const {
    if (m_shutdown) { return; }
    glfwPostEmptyEvent();
}

std::vector<FontSourceHandle> EmscriptenPlatform::systemFontFallbacksHandle() const {
    std::vector<FontSourceHandle> handles;

    handles.emplace_back(Url(DEFAULT));
    handles.emplace_back(Url(FONT_AR));
    handles.emplace_back(Url(FONT_HE));
    handles.emplace_back(Url(FONT_JA));
    handles.emplace_back(Url(FALLBACK));

    return handles;
}

bool EmscriptenPlatform::startUrlRequestImpl(const Url& _url, const UrlRequestHandle _request, UrlRequestId& _id) {
    auto onURLResponse = [this, _request](UrlResponse&& response) {
        onUrlResponse(_request, std::move(response));
    };
    // _id = m_urlClient->addRequest(_url.string(), onURLResponse);
    return false;
}

void EmscriptenPlatform::cancelUrlRequestImpl(const UrlRequestId _id) {
    // if (m_urlClient) {
    //     m_urlClient->cancelRequest(_id);
    // }
}

void setCurrentThreadPriority(int priority) {}

void initGLExtensions() {
    Tangram::Hardware::supportsMapBuffer = true;
}

} // namespace Tangram
