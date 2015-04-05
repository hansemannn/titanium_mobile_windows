/**
 * TitaniumKit Titanium.UI.WebView
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/WebView.hpp"

namespace Titanium
{
	namespace UI
	{

		WebView::WebView(const JSContext& js_context) TITANIUM_NOEXCEPT
			: View(js_context)
		{
		}

		std::vector<std::uint8_t> WebView::getData() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("WebView::getData: Unimplemented");
			return std::vector<std::uint8_t>();
		}

		bool WebView::setData(const std::vector<std::uint8_t>& data) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("WebView::setData: Unimplemented");
			return false;
		}

		std::string WebView::getHtml() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("WebView::getHtml: Unimplemented");
			return "";
		}
		bool WebView::setHtml(const std::string& html, const std::unordered_map<std::string, std::string>& options) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("WebView::setHtml: Unimplemented");
			return false;
		}

		bool WebView::getLoading() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("WebView::getLoading: Unimplemented");
			return false;
		}

		bool WebView::setLoading(const bool& value) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("WebView::setLoading: Unimplemented");
			return false;
		}

		bool WebView::getScalesPageToFit() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("WebView::getScalesPageToFit: Unimplemented");
			return false;
		}

		bool WebView::setScalesPageToFit(const bool& value) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("WebView::setScalesPageToFit: Unimplemented");
			return false;
		}

		std::string WebView::getUrl() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("WebView::getUrl: Unimplemented");
			return "";
		}

		bool WebView::setUrl(const std::string& url) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("WebView::setUrl: Unimplemented");
			return false;
		}

		bool WebView::canGoBack() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("WebView::canGoBack: Unimplemented");
			return false;
		}

		bool WebView::canGoForward() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("WebView::canGoForward: Unimplemented");
			return false;
		}

		std::string WebView::evalJS(const std::string& code) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("WebView::evalJS: Unimplemented");
			return "";
		}

		void WebView::goBack() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("WebView::goBack: Unimplemented");
		}

		void WebView::goForward() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("WebView::goForward: Unimplemented");
		}

		void WebView::reload() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("WebView::reload: Unimplemented");
		}

		bool WebView::setBasicAuthentication(const std::string& username, const std::string& password) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("WebView::setBasicAuthentication: Unimplemented");
			return false;
		}

		void WebView::stopLoading(const bool& hardStop) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("WebView::stopLoading: Unimplemented");
		}

		void WebView::JSExportInitialize() {
			JSExport<WebView>::SetClassVersion(1);
			JSExport<WebView>::SetParent(JSExport<View>::Class());

			TITANIUM_ADD_PROPERTY_READONLY(WebView, data);
			TITANIUM_ADD_PROPERTY_READONLY(WebView, html);
			TITANIUM_ADD_PROPERTY(WebView, loading);
			TITANIUM_ADD_PROPERTY(WebView, scalesPageToFit);
			TITANIUM_ADD_PROPERTY(WebView, url);
			TITANIUM_ADD_FUNCTION(WebView, canGoBack);
			TITANIUM_ADD_FUNCTION(WebView, canGoForward);
			TITANIUM_ADD_FUNCTION(WebView, evalJS);
			TITANIUM_ADD_FUNCTION(WebView, goBack);
			TITANIUM_ADD_FUNCTION(WebView, goForward);
			TITANIUM_ADD_FUNCTION(WebView, reload);
			TITANIUM_ADD_FUNCTION(WebView, setBasicAuthentication);
			TITANIUM_ADD_FUNCTION(WebView, stopLoading);
			TITANIUM_ADD_FUNCTION(WebView, getData);
			TITANIUM_ADD_FUNCTION(WebView, setData);
			TITANIUM_ADD_FUNCTION(WebView, getHtml);
			TITANIUM_ADD_FUNCTION(WebView, setHtml);
			TITANIUM_ADD_FUNCTION(WebView, getLoading);
			TITANIUM_ADD_FUNCTION(WebView, setLoading);
			TITANIUM_ADD_FUNCTION(WebView, getScalesPageToFit);
			TITANIUM_ADD_FUNCTION(WebView, setScalesPageToFit);
			TITANIUM_ADD_FUNCTION(WebView, getUrl);
			TITANIUM_ADD_FUNCTION(WebView, setUrl);
		}

		TITANIUM_PROPERTY_GETTER(WebView, data)
		{
			// TODO Convert std::vector<unstd::uint8_t> to JSObject (Ti.Blob)
			TITANIUM_LOG_WARN("WebView.data is not implemented yet");
			return get_context().CreateUndefined();
		}

		TITANIUM_PROPERTY_GETTER(WebView, html)
		{
			return get_context().CreateString(getHtml());
		}

		TITANIUM_PROPERTY_GETTER(WebView, loading)
		{
			return get_context().CreateBoolean(getLoading());
		}

		TITANIUM_PROPERTY_SETTER(WebView, loading)
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			return setLoading(static_cast<bool>(argument));
		}

		TITANIUM_PROPERTY_GETTER(WebView, scalesPageToFit)
		{
			return get_context().CreateBoolean(getScalesPageToFit());
		}

		TITANIUM_PROPERTY_SETTER(WebView, scalesPageToFit)
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			return setScalesPageToFit(static_cast<bool>(argument));
		}

		TITANIUM_PROPERTY_GETTER(WebView, url)
		{
			return get_context().CreateString(getUrl());
		}

		TITANIUM_PROPERTY_SETTER(WebView, url)
		{
			return setUrl(static_cast<std::string>(argument));
		}

		TITANIUM_FUNCTION(WebView, setHtml)
		{
			std::unordered_map<std::string, std::string> options;
	    
			if (arguments.size() < 1) {
				return get_context().CreateUndefined();
			}
	    
			const auto _0 = arguments.at(0);
			TITANIUM_ASSERT(_0.IsObject());
			const auto html = static_cast<std::string>(_0);
	    
			if (arguments.size() >= 2) {
				const auto _1 = arguments.at(1);
				TITANIUM_ASSERT(_1.IsObject());
				const auto js_options = static_cast<JSObject>(_1);
				// extract JSObject into C++ unordered_map
				for (const auto& property_name : static_cast<std::vector<JSString>>(js_options.GetPropertyNames())) {
					options.emplace(property_name, static_cast<std::string>(js_options.GetProperty(property_name)));
				}
			}
			setHtml(html, options);
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(WebView, canGoBack)
		{
			return get_context().CreateBoolean(canGoBack());
		}

		TITANIUM_FUNCTION(WebView, canGoForward)
		{
			return get_context().CreateBoolean(canGoForward());
		}

		TITANIUM_FUNCTION(WebView, evalJS)
		{
			if (arguments.size() < 1) {
				return get_context().CreateUndefined();
			} else if (arguments.size() >= 1) {
				const auto _0 = arguments.at(0);
				TITANIUM_ASSERT(_0.IsString());
				const std::string code = static_cast<std::string>(_0);
				return get_context().CreateString(evalJS(code));
			}
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(WebView, goBack)
		{
			goBack();
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(WebView, goForward)
		{
			goForward();
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(WebView, reload)
		{
			reload();
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(WebView, setBasicAuthentication)
		{
			if (arguments.size() < 2) {
				return get_context().CreateUndefined();
			} else if (arguments.size() >= 2) {
				const auto _0 = arguments.at(0);
				const auto _1 = arguments.at(1);

				TITANIUM_ASSERT(_0.IsString());
				TITANIUM_ASSERT(_1.IsString());

				const std::string username = static_cast<std::string>(_0);
				const std::string password = static_cast<std::string>(_1);

				setBasicAuthentication(username, password);
			} else if (arguments.size() >= 1) {
				const auto _0 = arguments.at(0);
				TITANIUM_ASSERT(_0.IsString());
				const std::string username = static_cast<std::string>(_0);
				setBasicAuthentication(username, "");
			}
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(WebView, stopLoading)
		{
			if (arguments.size() < 1) {
				return get_context().CreateUndefined();
			} else if (arguments.size() >= 1) {
				const auto _0 = arguments.at(0);
				TITANIUM_ASSERT(_0.IsBoolean());
				const bool hardStop = static_cast<bool>(_0);
				stopLoading(hardStop);
			}
			stopLoading(false);
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(WebView, getData)
		{
			return js_get_data();
		}

		TITANIUM_FUNCTION(WebView, setData)
		{
			if (arguments.size() >= 1) {
				const auto _0 = arguments.at(0);
				TITANIUM_ASSERT(_0.IsObject());
				const auto data = _0;
				// TODO Convert JSObject(Ti.Blob or Ti.File) to std::vector<std::uint8_t>
				// setData(data);
			}
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(WebView, getHtml)
		{
			return get_context().CreateString(getHtml());
		}

		TITANIUM_FUNCTION(WebView, getLoading)
		{
			return get_context().CreateBoolean(getLoading());
		}

		TITANIUM_FUNCTION(WebView, setLoading)
		{
			if (arguments.size() < 1) {
				return get_context().CreateUndefined();
			} else if (arguments.size() >= 1) {
				const auto _0 = arguments.at(0);
				TITANIUM_ASSERT(_0.IsBoolean());
				const bool loading = static_cast<bool>(_0);
				setLoading(loading);
			}
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(WebView, getScalesPageToFit)
		{
			return get_context().CreateBoolean(getScalesPageToFit());
		}

		TITANIUM_FUNCTION(WebView, setScalesPageToFit)
		{
			if (arguments.size() < 1) {
				return get_context().CreateUndefined();
			} else if (arguments.size() >= 1) {
				const auto _0 = arguments.at(0);
				TITANIUM_ASSERT(_0.IsBoolean());
				const bool scalesPageToFit = static_cast<bool>(_0);
				setScalesPageToFit(scalesPageToFit);
			}
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(WebView, getUrl)
		{
			return get_context().CreateString(getUrl());
		}

		TITANIUM_FUNCTION(WebView, setUrl)
		{
			if (arguments.size() < 1) {
				return get_context().CreateUndefined();
			} else if (arguments.size() >= 1) {
				const auto _0 = arguments.at(0);
				TITANIUM_ASSERT(_0.IsString());
				const std::string url = static_cast<std::string>(_0);
				setUrl(url);
			}
			return get_context().CreateUndefined();
		}
	} // namespace UI
}  // namespace Titanium