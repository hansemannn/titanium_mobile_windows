/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/ScrollView.hpp"

namespace Titanium
{
	namespace UI
	{
		ScrollView::ScrollView(const JSContext& js_context) TITANIUM_NOEXCEPT
		    : View(js_context)
		{
		}

		void ScrollView::JSExportInitialize()
		{
			JSExport<ScrollView>::SetClassVersion(1);
			JSExport<ScrollView>::SetParent(JSExport<View>::Class());
			TITANIUM_ADD_FUNCTION(ScrollView, scrollTo);
			TITANIUM_ADD_FUNCTION(ScrollView, scrollToBottom);
			TITANIUM_ADD_PROPERTY(ScrollView, contentWidth);
			TITANIUM_ADD_PROPERTY(ScrollView, contentHeight);
			TITANIUM_ADD_FUNCTION(ScrollView, setContentWidth);
			TITANIUM_ADD_FUNCTION(ScrollView, setContentHeight);
			TITANIUM_ADD_FUNCTION(ScrollView, getContentWidth);
			TITANIUM_ADD_FUNCTION(ScrollView, getContentHeight);

			TITANIUM_ADD_PROPERTY(ScrollView, scrollingEnabled);
			TITANIUM_ADD_FUNCTION(ScrollView, setScrollingEnabled);
			TITANIUM_ADD_FUNCTION(ScrollView, getScrollingEnabled);

			TITANIUM_ADD_PROPERTY(ScrollView, showHorizontalScrollIndicator);
			TITANIUM_ADD_FUNCTION(ScrollView, setShowHorizontalScrollIndicator);
			TITANIUM_ADD_FUNCTION(ScrollView, getShowHorizontalScrollIndicator);

			TITANIUM_ADD_PROPERTY(ScrollView, showVerticalScrollIndicator);
			TITANIUM_ADD_FUNCTION(ScrollView, setShowVerticalScrollIndicator);
			TITANIUM_ADD_FUNCTION(ScrollView, getShowVerticalScrollIndicator);
		}

		void ScrollView::scrollTo(double x, double y) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ScrollView::scrollTo: Unimplemented");
		}

		void ScrollView::scrollToBottom() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ScrollView::scrollToBottom: Unimplemented");
		}

		std::string ScrollView::get_contentWidth() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ScrollView::get_contentWidth: Unimplemented");
			return "";
		}

		std::string ScrollView::get_contentHeight() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ScrollView::get_contentHeight: Unimplemented");
			return "";
		}

		bool ScrollView::set_contentWidth(const std::string& width) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ScrollView::set_contentWidth(std::string): Unimplemented");
			return false;
		}

		bool ScrollView::set_contentHeight(const std::string& height) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ScrollView::set_contentHeight(std::string): Unimplemented");
			return false;
		}

		bool ScrollView::set_contentWidth(const double& width) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ScrollView::set_contentWidth(double): Unimplemented");
			return false;
		}

		bool ScrollView::set_contentHeight(const double& height) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ScrollView::set_contentHeight(double): Unimplemented");
			return false;
		}

		bool ScrollView::get_scrollingEnabled() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ScrollView::get_scrollingEnabled: Unimplemented");
			return false;
		}

		bool ScrollView::set_scrollingEnabled(bool enabled) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ScrollView::set_scrollingEnabled: Unimplemented");
			return false;
		}

		bool ScrollView::get_showHorizontalScrollIndicator() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ScrollView::get_showHorizontalScrollIndicator: Unimplemented");
			return false;
		}

		bool ScrollView::set_showHorizontalScrollIndicator(bool enabled) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ScrollView::set_showHorizontalScrollIndicator: Unimplemented");
			return false;
		}

		bool ScrollView::get_showVerticalScrollIndicator() const TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ScrollView::get_showVerticalScrollIndicator: Unimplemented");
			return false;
		}

		bool ScrollView::set_showVerticalScrollIndicator(bool enabled) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("ScrollView::set_showVerticalScrollIndicator: Unimplemented");
			return false;
		}

		TITANIUM_FUNCTION(ScrollView, scrollTo)
		{
			if (arguments.size() < 2) {
				return get_context().CreateUndefined();
			}
			const auto _0 = arguments.at(0);
			const auto _1 = arguments.at(1);
			TITANIUM_ASSERT(_0.IsNumber());
			TITANIUM_ASSERT(_1.IsNumber());
			scrollTo(static_cast<double>(_0), static_cast<double>(_1));
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(ScrollView, scrollToBottom)
		{
			scrollToBottom();
			return get_context().CreateUndefined();
		}

		TITANIUM_PROPERTY_SETTER(ScrollView, contentWidth)
		{
			TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
			if (argument.IsNumber()) {
				set_contentWidth(static_cast<double>(argument));
			} else {
				set_contentWidth(static_cast<std::string>(argument));
			}
			return true;
		}

		TITANIUM_FUNCTION(ScrollView, setContentWidth)
		{
			if (arguments.size() == 0) {
				return get_context().CreateUndefined();
			}
			const auto _0 = arguments.at(0);
			js_set_contentWidth(_0);
			return get_context().CreateUndefined();
		}

		TITANIUM_PROPERTY_GETTER(ScrollView, contentWidth)
		{
			return get_context().CreateString(get_contentWidth());
		}

		TITANIUM_FUNCTION(ScrollView, getContentWidth)
		{
			return js_get_contentWidth();
		}

		TITANIUM_PROPERTY_SETTER(ScrollView, contentHeight)
		{
			TITANIUM_ASSERT(argument.IsString() || argument.IsNumber());
			if (argument.IsNumber()) {
				set_contentHeight(static_cast<double>(argument));
			} else {
				set_contentHeight(static_cast<std::string>(argument));
			}
			return true;
		}

		TITANIUM_FUNCTION(ScrollView, setContentHeight)
		{
			if (arguments.size() == 0) {
				return get_context().CreateUndefined();
			}
			const auto _0 = arguments.at(0);
			js_set_contentHeight(_0);
			return get_context().CreateUndefined();
		}

		TITANIUM_PROPERTY_GETTER(ScrollView, contentHeight)
		{
			return get_context().CreateString(get_contentHeight());
		}

		TITANIUM_FUNCTION(ScrollView, getContentHeight)
		{
			return js_get_contentHeight();
		}

		TITANIUM_PROPERTY_GETTER(ScrollView, scrollingEnabled)
		{
			return get_context().CreateBoolean(get_scrollingEnabled());
		}

		TITANIUM_FUNCTION(ScrollView, getScrollingEnabled)
		{
			return js_get_scrollingEnabled();
		}

		TITANIUM_PROPERTY_SETTER(ScrollView, scrollingEnabled)
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			return set_scrollingEnabled(static_cast<bool>(argument));
		}

		TITANIUM_FUNCTION(ScrollView, setScrollingEnabled)
		{
			if (arguments.size() == 0) {
				return get_context().CreateUndefined();
			}
			const auto _0 = arguments.at(0);
			js_set_scrollingEnabled(_0);
			return get_context().CreateUndefined();
		}

		TITANIUM_PROPERTY_GETTER(ScrollView, showHorizontalScrollIndicator)
		{
			return get_context().CreateBoolean(get_showHorizontalScrollIndicator());
		}

		TITANIUM_FUNCTION(ScrollView, getShowHorizontalScrollIndicator)
		{
			return js_get_showHorizontalScrollIndicator();
		}

		TITANIUM_PROPERTY_SETTER(ScrollView, showHorizontalScrollIndicator)
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			return set_showHorizontalScrollIndicator(static_cast<bool>(argument));
		}

		TITANIUM_FUNCTION(ScrollView, setShowHorizontalScrollIndicator)
		{
			if (arguments.size() == 0) {
				return get_context().CreateUndefined();
			}
			const auto _0 = arguments.at(0);
			js_set_showHorizontalScrollIndicator(_0);
			return get_context().CreateUndefined();
		}

		TITANIUM_PROPERTY_GETTER(ScrollView, showVerticalScrollIndicator)
		{
			return get_context().CreateBoolean(get_showVerticalScrollIndicator());
		}

		TITANIUM_FUNCTION(ScrollView, getShowVerticalScrollIndicator)
		{
			return js_get_showVerticalScrollIndicator();
		}

		TITANIUM_PROPERTY_SETTER(ScrollView, showVerticalScrollIndicator)
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			return set_showVerticalScrollIndicator(static_cast<bool>(argument));
		}

		TITANIUM_FUNCTION(ScrollView, setShowVerticalScrollIndicator)
		{
			if (arguments.size() == 0) {
				return get_context().CreateUndefined();
			}
			const auto _0 = arguments.at(0);
			js_set_showVerticalScrollIndicator(_0);
			return get_context().CreateUndefined();
		}
	} // namespace UI
}  // namespace Titanium
