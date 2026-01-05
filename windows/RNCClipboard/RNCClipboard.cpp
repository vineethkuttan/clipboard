#include "pch.h"

#include "RNCClipboard.h"
#include <Windows.h>
#include <string>
#include <vector>

namespace winrt::RNCClipboard
{

    void RNCClipboard::Initialize(React::ReactContext const& reactContext) noexcept {
        m_context = reactContext;
    }

    void RNCClipboard::getString(::React::ReactPromise<std::string>&& result) noexcept {
        std::string text;
        
        if (OpenClipboard(nullptr)) {
            HANDLE hData = GetClipboardData(CF_UNICODETEXT);
            if (hData != nullptr) {
                wchar_t* pszText = static_cast<wchar_t*>(GlobalLock(hData));
                if (pszText != nullptr) {
                    // Convert wide string to UTF-8
                    int size = WideCharToMultiByte(CP_UTF8, 0, pszText, -1, nullptr, 0, nullptr, nullptr);
                    if (size > 0) {
                        text.resize(size - 1);
                        WideCharToMultiByte(CP_UTF8, 0, pszText, -1, &text[0], size, nullptr, nullptr);
                    }
                    GlobalUnlock(hData);
                }
            }
            CloseClipboard();
        }
        
        result.Resolve(text);
    }

    void RNCClipboard::setString(std::string content) noexcept {
        if (OpenClipboard(nullptr)) {
            EmptyClipboard();
            
            // Convert UTF-8 to wide string
            int wideSize = MultiByteToWideChar(CP_UTF8, 0, content.c_str(), -1, nullptr, 0);
            if (wideSize > 0) {
                HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, wideSize * sizeof(wchar_t));
                if (hGlobal != nullptr) {
                    wchar_t* pszDest = static_cast<wchar_t*>(GlobalLock(hGlobal));
                    if (pszDest != nullptr) {
                        MultiByteToWideChar(CP_UTF8, 0, content.c_str(), -1, pszDest, wideSize);
                        GlobalUnlock(hGlobal);
                        SetClipboardData(CF_UNICODETEXT, hGlobal);
                    }
                }
            }
            
            CloseClipboard();
        }
    }

    // Stub implementations

    void RNCClipboard::getStrings(::React::ReactPromise<std::vector<std::string>>&& result) noexcept {
        result.Resolve(std::vector<std::string>());
    }

    void RNCClipboard::getImagePNG(::React::ReactPromise<std::string>&& result) noexcept {
        result.Resolve("");
    }

    void RNCClipboard::getImageJPG(::React::ReactPromise<std::string>&& result) noexcept {
        result.Resolve("");
    }

    void RNCClipboard::setImage(std::string content, ::React::ReactPromise<void>&& result) noexcept {
        result.Resolve();
    }

    void RNCClipboard::getImage(::React::ReactPromise<std::string>&& result) noexcept {
        result.Resolve("");
    }

    void RNCClipboard::setStrings(std::vector<std::string> const& content) noexcept {
        // No-op
    }

    void RNCClipboard::hasString(::React::ReactPromise<bool>&& result) noexcept {
        result.Resolve(false);
    }

    void RNCClipboard::hasImage(::React::ReactPromise<bool>&& result) noexcept {
        result.Resolve(false);
    }

    void RNCClipboard::hasURL(::React::ReactPromise<bool>&& result) noexcept {
        result.Resolve(false);
    }

    void RNCClipboard::hasNumber(::React::ReactPromise<bool>&& result) noexcept {
        result.Resolve(false);
    }

    void RNCClipboard::hasWebURL(::React::ReactPromise<bool>&& result) noexcept {
        result.Resolve(false);
    }

    void RNCClipboard::setListener() noexcept {
        // No-op
    }

    void RNCClipboard::removeListener() noexcept {
        // No-op
    }

    void RNCClipboard::addListener(std::string eventName) noexcept {
        // No-op
    }

    void RNCClipboard::removeListeners(int count) noexcept {
        // No-op
    }

} // namespace winrt::RNCClipboard