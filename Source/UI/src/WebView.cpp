/**
 * Titanium.UI.WebView for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/UI/WebView.hpp"
#include "Titanium/detail/TiBase.hpp"
#include "TitaniumWindows/Utility.hpp"
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>

namespace TitaniumWindows
{
	namespace UI
	{

		WebView::WebView(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
			: Titanium::UI::WebView(js_context, arguments)
		{
			TITANIUM_LOG_DEBUG("WebView::ctor Initialize");

			webview__ = ref new Windows::UI::Xaml::Controls::WebView();
			initWebViewListeners();

			setDefaultHeight(Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::FILL));
			setDefaultWidth(Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::FILL));

			setComponent(webview__);
		}

		WebView::~WebView() 
		{
			webview__->NavigationCompleted -= load_event__;
			webview__->NavigationStarting  -= beforeload_event__;
			webview__->ScriptNotify        -= script_event__;
			webview__ = nullptr;
		}

		void WebView::JSExportInitialize() 
		{
			JSExport<WebView>::SetClassVersion(1);
			JSExport<WebView>::SetParent(JSExport<Titanium::UI::WebView>::Class());
		}

		Titanium::UI::URL_ERROR WebView::getUrlError(const Windows::Web::WebErrorStatus status) const TITANIUM_NOEXCEPT
		{
			using namespace Windows::Web;
			if (status == WebErrorStatus::Unauthorized) {
				return Titanium::UI::URL_ERROR::AUTHENTICATION;
			} else if (status == WebErrorStatus::Timeout || status == WebErrorStatus::RequestTimeout || status == WebErrorStatus::GatewayTimeout) {
				return Titanium::UI::URL_ERROR::TIMEOUT;
			} else if (status == WebErrorStatus::CertificateCommonNameIsIncorrect || status == WebErrorStatus::CertificateContainsErrors || status == WebErrorStatus::CertificateExpired || status == WebErrorStatus::CertificateIsInvalid || status == WebErrorStatus::CertificateRevoked) {
				return Titanium::UI::URL_ERROR::SSL_FAILED;
			} else if (status == WebErrorStatus::RequestUriTooLong) {
				return Titanium::UI::URL_ERROR::BAD_URL;
			} else if (status == WebErrorStatus::CannotConnect || status == WebErrorStatus::ConnectionAborted || status == WebErrorStatus::ConnectionReset || status == WebErrorStatus::ConnectionReset) {
				return Titanium::UI::URL_ERROR::CONNECT;
			} else if (status == WebErrorStatus::NotFound) {
				return Titanium::UI::URL_ERROR::FILE_NOT_FOUND;
			} else if (status == WebErrorStatus::HostNameNotResolved) {
				return Titanium::UI::URL_ERROR::HOST_LOOKUP;
			} 
			return Titanium::UI::URL_ERROR::UNKNOWN;
		}

		void WebView::initWebViewListeners() TITANIUM_NOEXCEPT 
		{
			using namespace std::placeholders;
			using namespace Windows::UI::Xaml::Controls;

			load_event__ = webview__->NavigationCompleted += ref new Windows::Foundation::TypedEventHandler
				<Windows::UI::Xaml::Controls::WebView^, WebViewNavigationCompletedEventArgs^>([this](Platform::Object^ sender, WebViewNavigationCompletedEventArgs^ e) {
				navigating__ = false;
				if (e->IsSuccess && load_event_enabled__) {
					JSObject obj = get_context().CreateObject();
					obj.SetProperty("type", get_context().CreateString("load"));
					if (webview__->Source != nullptr) {
						obj.SetProperty("url", get_context().CreateString(TitaniumWindows::Utility::ConvertString(webview__->Source->ToString())));
					}
					fireEvent("load", obj);
				} else if (!e->IsSuccess && error_event_enabled__) {
					JSObject obj = get_context().CreateObject();
					obj.SetProperty("type", get_context().CreateString("error"));
					obj.SetProperty("success", get_context().CreateBoolean(false));
					obj.SetProperty("url",  get_context().CreateString(getUrl()));
					obj.SetProperty("code", get_context().CreateString(Titanium::UI::Constants::to_string(getUrlError(e->WebErrorStatus))));
					fireEvent("error", obj);
				}
			});

			beforeload_event__ = webview__->NavigationStarting += ref new Windows::Foundation::TypedEventHandler
				<Windows::UI::Xaml::Controls::WebView^, WebViewNavigationStartingEventArgs^>([this](Platform::Object^ sender, WebViewNavigationStartingEventArgs^ e) {
				navigating__ = true;
				if (beforeload_event_enabled__) {
					JSObject obj = get_context().CreateObject();
					obj.SetProperty("type", get_context().CreateString("beforeload"));
					obj.SetProperty("url",  get_context().CreateString(getUrl()));
					fireEvent("beforeload", obj);
				}
			});

			script_event__ = webview__->ScriptNotify += ref new NotifyEventHandler([this](Platform::Object^ sender, Windows::UI::Xaml::Controls::NotifyEventArgs^ e) {
				const auto value = TitaniumWindows::Utility::ConvertString(e->Value);
				std::vector<std::string> args;
	#pragma warning(push)
	#pragma warning(disable:4996)
				boost::split(args, value, boost::is_any_of(","));
	#pragma warning(pop)

				// we need at least 3 arguments
				if (args.size() < 3) {
					return;
				}

				// notify command
				const auto command = args.at(0);
				// first argument
				const auto arg1    = args.at(1);
				// rest of arguments
				const auto arg2    = value.substr(command.length() + arg1.length() + 2);

				if (command == "log") {
					// TODO: we should leverage Ti.API functions for logging
					std::clog << "[" << arg1 << "] " << arg2 << std::endl;
				} else if (command == "event") {
					// Event execution shortcut: let's do just like the way Ti Blackberry does for now
					const auto script = (boost::format("Ti.App.fireEvent('%1%', %2%);\r\n") % arg1 % arg2).str();
					get_context().JSEvaluateScript(script);
				}
			});

		}

		void WebView::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			if (event_name == "load") {
				load_event_enabled__ = true;
			} else if (event_name == "beforeload") {
				beforeload_event_enabled__ = true;
			} else if (event_name == "error") {
				error_event_enabled__ = true;
			}
		}

		void WebView::disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			if (event_name == "load") {
				load_event_enabled__ = false;
			} else if (event_name == "beforeload") {
				beforeload_event_enabled__ = false;
			} else if (event_name == "error") {
				error_event_enabled__ = false;
			}
		}

		std::string WebView::getHtml() const TITANIUM_NOEXCEPT
		{
			return "";
		}

		bool WebView::setHtml(std::string html, std::unordered_map<std::string, std::string> options) TITANIUM_NOEXCEPT
		{
			webview__->NavigateToString(TitaniumWindows::Utility::ConvertString(html));
			return true;
		}

		bool WebView::getLoading() const TITANIUM_NOEXCEPT
		{
			return navigating__;
		}

		std::string WebView::getUrl() const TITANIUM_NOEXCEPT
		{
			if (webview__->Source != nullptr) {
				return TitaniumWindows::Utility::ConvertString(webview__->Source->ToString());
			} else {
				return "";
			}
		}

		bool WebView::setUrl(std::string url) TITANIUM_NOEXCEPT
		{
			webview__->Navigate(ref new Windows::Foundation::Uri(TitaniumWindows::Utility::ConvertString(url)));
			return true;
		}

		bool WebView::canGoBack() TITANIUM_NOEXCEPT
		{
			return webview__->CanGoBack;
		}

		bool WebView::canGoForward() TITANIUM_NOEXCEPT
		{
			return webview__->CanGoForward;
		}

		void WebView::goBack() TITANIUM_NOEXCEPT
		{
			if (canGoBack()) {
				webview__->GoBack();
			}
		}

		void WebView::goForward() TITANIUM_NOEXCEPT
		{
			if (canGoForward()) {
				webview__->GoForward();
			}
		}

		void WebView::reload() TITANIUM_NOEXCEPT
		{
			webview__->Refresh();
		}

		void WebView::stopLoading(bool hardStop) TITANIUM_NOEXCEPT
		{
			webview__->Stop();
		}

		void WebView::set_bottom(const std::string& bottom) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_bottom(bottom);
			setLayoutProperty(Titanium::LayoutEngine::ValueName::Bottom, bottom);
		}

		void WebView::set_height(const std::string& height) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_height(height);
			setLayoutProperty(Titanium::LayoutEngine::ValueName::Height, height);
		}

		void WebView::set_left(const std::string& left) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_left(left);
			setLayoutProperty(Titanium::LayoutEngine::ValueName::Left, left);
		}

		void WebView::set_layout(const std::string& layout) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_layout(layout);
			setLayout(layout);
		}

		void WebView::set_right(const std::string& right) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_right(right);
			setLayoutProperty(Titanium::LayoutEngine::ValueName::Right, right);
		}

		void WebView::set_top(const std::string& top) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_top(top);
			setLayoutProperty(Titanium::LayoutEngine::ValueName::Top, top);
		}

		void WebView::set_width(const std::string& width) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_width(width);
			setLayoutProperty(Titanium::LayoutEngine::ValueName::Width, width);
		}

	} // namespace UI
}  // namespace Titanium
