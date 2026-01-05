#pragma once

#include "pch.h"
#include "resource.h"

#include "codegen/NativeClipboardModuleSpec.g.h"

#include "NativeModules.h"
#include <Windows.h>

namespace winrt::RNCClipboard
{

	// See https://microsoft.github.io/react-native-windows/docs/native-platform for help writing native modules

	REACT_MODULE(RNCClipboard)
		struct RNCClipboard
	{
		using ModuleSpec = RNCClipboardCodegen::ClipboardModuleSpec;

		REACT_INIT(Initialize)
			void Initialize(React::ReactContext const& reactContext) noexcept;

		// Clipboard methods
		REACT_METHOD(getString)
			void getString(::React::ReactPromise<std::string>&& result) noexcept;

		REACT_METHOD(getStrings)
			void getStrings(::React::ReactPromise<std::vector<std::string>>&& result) noexcept;

		REACT_METHOD(getImagePNG)
			void getImagePNG(::React::ReactPromise<std::string>&& result) noexcept;

		REACT_METHOD(getImageJPG)
			void getImageJPG(::React::ReactPromise<std::string>&& result) noexcept;

		REACT_METHOD(setImage)
			void setImage(std::string content, ::React::ReactPromise<void>&& result) noexcept;

		REACT_METHOD(getImage)
			void getImage(::React::ReactPromise<std::string>&& result) noexcept;

		REACT_METHOD(setString)
			void setString(std::string content) noexcept;

		REACT_METHOD(setStrings)
			void setStrings(std::vector<std::string> const& content) noexcept;

		REACT_METHOD(hasString)
			void hasString(::React::ReactPromise<bool>&& result) noexcept;

		REACT_METHOD(hasImage)
			void hasImage(::React::ReactPromise<bool>&& result) noexcept;

		REACT_METHOD(hasURL)
			void hasURL(::React::ReactPromise<bool>&& result) noexcept;

		REACT_METHOD(hasNumber)
			void hasNumber(::React::ReactPromise<bool>&& result) noexcept;

		REACT_METHOD(hasWebURL)
			void hasWebURL(::React::ReactPromise<bool>&& result) noexcept;

		REACT_METHOD(setListener)
			void setListener() noexcept;

		REACT_METHOD(removeListener)
			void removeListener() noexcept;

		REACT_METHOD(addListener)
			void addListener(std::string eventName) noexcept;

		REACT_METHOD(removeListeners)
			void removeListeners(int count) noexcept;

	private:
		React::ReactContext m_context;
	};

} // namespace winrt::RNCClipboard