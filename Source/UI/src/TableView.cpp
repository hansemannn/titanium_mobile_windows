/**
 * Titanium.UI.TableView for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/UI/TableView.hpp"
#include "TitaniumWindows/UI/TableViewRow.hpp"
#include "Titanium/UI/TableViewSection.hpp"
#include "TitaniumWindows/UI/View.hpp"
#include "TitaniumWindows/UI/WindowsViewLayoutDelegate.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include "TitaniumWindows/WindowsMacros.hpp"

#include <collection.h>

namespace TitaniumWindows
{
	namespace UI
	{

		using namespace Platform::Collections;
		using namespace Windows::UI::Xaml;


		TableView::TableView(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::UI::TableView(js_context)
		{
			TITANIUM_LOG_DEBUG("TableView::ctor Initialize");
		}

		void TableView::resetTableDataBinding()
		{
			collectionViewSource__ = ref new Data::CollectionViewSource();
			collectionViewSource__->Source = collectionViewItems__;
			collectionViewSource__->IsSourceGrouped = true;

			auto binding = ref new Data::Binding();
			binding->Source = collectionViewSource__;
			Data::BindingOperations::SetBinding(tableview__, Controls::ListView::ItemsSourceProperty, binding);
		}

		void TableView::clearTableData() 
		{
			collectionViewItems__->Clear();
			resetTableDataBinding();
		}

		void TableView::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
		{
			Titanium::UI::TableView::postCallAsConstructor(js_context, arguments);

			tableview__ = ref new Controls::ListView();
			collectionViewItems__ = ref new Vector<Platform::Object^>();

			resetTableDataBinding();

			tableview__->IsItemClickEnabled = true;

			Titanium::UI::TableView::setLayoutDelegate<WindowsViewLayoutDelegate>();
			layoutDelegate__->set_defaultWidth(Titanium::UI::LAYOUT::FILL);
			layoutDelegate__->set_defaultHeight(Titanium::UI::LAYOUT::FILL);

			getViewLayoutDelegate<WindowsViewLayoutDelegate>()->setComponent(tableview__);
		}

		void TableView::JSExportInitialize() 
		{
			JSExport<TableView>::SetClassVersion(1);
			JSExport<TableView>::SetParent(JSExport<Titanium::UI::TableView>::Class());
		}

		void TableView::querySubmitted(const std::string& query)
		{
			// Make sure to update UI from UI thread
			TitaniumWindows::Utility::RunOnUIThread([this, query]() {
				Titanium::UI::TableView::querySubmitted(query);
			});
		}

		// unregister all rows in section from LayoutEngine
		void TableView::unregisterSectionLayoutNode(const std::shared_ptr<Titanium::UI::TableViewSection>& section)
		{
			unregisterTableViewRowAsLayoutNode(section->get_headerView());
			unregisterTableViewRowAsLayoutNode(section->get_footerView());
			for (const auto row : section->get_rows()) {
				unregisterTableViewRowAsLayoutNode(row);
			}
		}

		// unregister all rows from LayoutEngine
		void TableView::unregisterSections() 
		{
			for (const auto section : model__->get_sections()) {
				unregisterSectionLayoutNode(section);
			}
		}

		void TableView::set_data(const std::vector<JSObject>& data) TITANIUM_NOEXCEPT
		{
			unregisterSections();
			Titanium::UI::TableView::set_data(data);
			clearTableData();
			for (uint32_t i = 0; i < model__->get_sectionCount(); i++) {
				collectionViewItems__->Append(createUIElementsForSection(i));
			}
		}

		void TableView::set_sections(const std::vector<std::shared_ptr<Titanium::UI::TableViewSection>>& sections) TITANIUM_NOEXCEPT
		{
			unregisterSections();
			Titanium::UI::TableView::set_sections(sections);
			clearTableData();
			for (uint32_t i = 0; i < model__->get_sectionCount(); i++) {
				collectionViewItems__->Append(createUIElementsForSection(i));
			}
		}

		Vector<UIElement^>^ TableView::createUIElementsForSection(const std::uint32_t& sectionIndex) TITANIUM_NOEXCEPT
		{
			const auto section = model__->getSectionAtIndex(sectionIndex);
			const auto rows    = section->get_rows();
			auto group = ref new Vector<UIElement^>();

			// attach table view to this section so it receives callback
			section->attachTableView(get_object().GetPrivate<TitaniumWindows::UI::TableView>());

			// Set section header
			auto headerView = section->get_headerView();
			if (headerView != nullptr) {
				const auto view_delegate = headerView->getViewLayoutDelegate<WindowsViewLayoutDelegate>();
				if (view_delegate == nullptr) {
					TITANIUM_LOG_ERROR("TableView: headerView must be of type Titanium.UI.View");
				} else {
					group->Append(view_delegate->getComponent());
					// Add as child view to make layout engine work
					registerTableViewRowAsLayoutNode(headerView);
				}
			} else if (section->hasHeader()) {
				group->Append(createDefaultSectionHeader(section));
			}

			for (uint32_t i = 0; i < rows.size(); i++) {
				auto row = rows.at(i);
				auto view = row->get_object().GetPrivate<TitaniumWindows::UI::TableViewRow>();
				auto rowContent = view->getViewLayoutDelegate<WindowsViewLayoutDelegate>()->getComponent();
				TITANIUM_ASSERT(rowContent);
				// Add as list item
				group->Append(rowContent);
				// Add as child view to make layout engine work
				registerTableViewRowAsLayoutNode(view);
			}

			return group;
		}

		void TableView::updateSection(const uint32_t& index, const std::shared_ptr<Titanium::UI::TableViewSection>& section, const std::shared_ptr<Titanium::UI::TableViewAnimationProperties>& animation) TITANIUM_NOEXCEPT
		{
			Titanium::UI::TableView::updateSection(index, section, animation);
			unbindCollectionViewSource();
			collectionViewItems__->SetAt(index, createUIElementsForSection(index));

			// Make sure to unregister rows from LayoutEngine
			unregisterSectionLayoutNode(section);

			bindCollectionViewSource();
		}

		void TableView::appendSection(const std::vector<std::shared_ptr<Titanium::UI::TableViewSection>>& sections, const std::shared_ptr<Titanium::UI::TableViewAnimationProperties>& animation) TITANIUM_NOEXCEPT
		{
			const auto startSectionIndex = model__->get_sectionCount();

			Titanium::UI::TableView::appendSection(sections, animation);
			unbindCollectionViewSource();

			for (std::uint32_t i = 0; i < sections.size(); i++) {
				collectionViewItems__->Append(createUIElementsForSection(startSectionIndex + i));
			}

			bindCollectionViewSource();
		}

		void TableView::deleteSection(const uint32_t& sectionIndex, const std::shared_ptr<Titanium::UI::TableViewAnimationProperties>& animation) TITANIUM_NOEXCEPT
		{
			auto section = model__->getSectionAtIndex(sectionIndex);

			Titanium::UI::TableView::deleteSection(sectionIndex, animation);
			unbindCollectionViewSource();

			unregisterSectionLayoutNode(section);

			const auto views = static_cast<Vector<UIElement^>^>(collectionViewItems__->GetAt(sectionIndex));
			views->Clear();

			bindCollectionViewSource();

		}

		void TableView::insertSectionAfter(const uint32_t& index, const std::shared_ptr<Titanium::UI::TableViewSection>& section, const std::shared_ptr<Titanium::UI::TableViewAnimationProperties>& animation) TITANIUM_NOEXCEPT
		{
			Titanium::UI::TableView::insertSectionAfter(index, section, animation);
			unbindCollectionViewSource();
			collectionViewItems__->InsertAt(index + 1, createUIElementsForSection(index + 1));
			bindCollectionViewSource();
		}

		void TableView::insertSectionBefore(const uint32_t& index, const std::shared_ptr<Titanium::UI::TableViewSection>& section, const std::shared_ptr<Titanium::UI::TableViewAnimationProperties>& animation) TITANIUM_NOEXCEPT
		{
			Titanium::UI::TableView::insertSectionBefore(index, section, animation);
			unbindCollectionViewSource();
			collectionViewItems__->InsertAt(index, createUIElementsForSection(index));
			bindCollectionViewSource();
		}


		Controls::ListViewHeaderItem^ TableView::createDefaultSectionHeader(const std::shared_ptr<Titanium::UI::TableViewSection>& section) 
		{
			Controls::ListViewHeaderItem^ header = ref new Controls::ListViewHeaderItem();
			auto headerText = ref new Controls::TextBlock();
			headerText->Text = Utility::ConvertUTF8String(section->get_headerTitle());
			headerText->FontSize = 28; // Change this?
			header->Content = headerText;
			return header;
		}

		// Add as child view to make layout engine work
		void TableView::registerTableViewRowAsLayoutNode(const std::shared_ptr<Titanium::UI::View>& view)
		{
			auto layoutDelegate = getViewLayoutDelegate<WindowsViewLayoutDelegate>();
			Titanium::LayoutEngine::nodeAddChild(layoutDelegate->getLayoutNode(), view->getViewLayoutDelegate<WindowsViewLayoutDelegate>()->getLayoutNode());
		}

		// Remove child view 
		void TableView::unregisterTableViewRowAsLayoutNode(const std::shared_ptr<Titanium::UI::View>& view)
		{
			if (view == nullptr) {
				return;
			}
			const auto layout      = getViewLayoutDelegate<WindowsViewLayoutDelegate>();
			const auto view_layout = view->getViewLayoutDelegate<WindowsViewLayoutDelegate>();
			if (layout && view_layout) {
				Titanium::LayoutEngine::nodeRemoveChild(layout->getLayoutNode(), view_layout->getLayoutNode());
			}
		}

		void TableView::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			getViewLayoutDelegate<WindowsViewLayoutDelegate>()->filterEvents({ "click" });

			Titanium::UI::TableView::enableEvent(event_name);

			const JSContext ctx = this->get_context();

			if (event_name == "click") {
				click_event__ = tableview__->ItemClick += ref new Controls::ItemClickEventHandler(
					[this, ctx](Platform::Object^ sender, Controls::ItemClickEventArgs^ e) {

					if (model__->empty()) {
						TITANIUM_LOG_DEBUG("TableView is clicked but there's no data");
						return;
					}

					const auto listview = safe_cast<Controls::ListView^>(sender);

					uint32_t selectedIndex = -1;
					listview->Items->IndexOf(e->ClickedItem, &selectedIndex);
					if (selectedIndex == -1) return;

					const auto result = model__->searchRowBySelectedIndex(selectedIndex);

					if (result.found) {
						JSObject  eventArgs = ctx.CreateObject();
						eventArgs.SetProperty("sectionIndex", ctx.CreateNumber(result.sectionIndex));
						eventArgs.SetProperty("index", ctx.CreateNumber(result.rowIndex));

						const auto section = model__->getSectionAtIndex(result.sectionIndex);
						const auto row = section->get_rows().at(result.rowIndex);
						eventArgs.SetProperty("row", row->get_object());
						eventArgs.SetProperty("rowData", row->get_data());
						eventArgs.SetProperty("source", row->get_object());

						fireEvent("click", eventArgs);
					}
				});
			}
		}

		void TableView::disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			Titanium::UI::TableView::disableEvent(event_name);

			if (event_name == "click") {
				tableview__->ItemClick -= click_event__;
			}
		}

		void TableView::bindCollectionViewSource()
		{
			collectionViewSource__->Source = collectionViewItems__;
		}

		void TableView::unbindCollectionViewSource()
		{
			collectionViewSource__->Source = ref new Vector<Platform::Object^>();
		}

		std::uint32_t TableView::getRowIndexInCollectionView(const std::shared_ptr<Titanium::UI::TableViewSection>& section, const std::uint32_t& rowIndex)
		{
			return rowIndex + /* +1 to skip table header */ (hasHeader() ? 1 : 0) + /* +1 to skip section header */ (section->hasHeader() ? 1 : 0);
		}

		void TableView::fireTableViewSectionEvent(const std::string& name, const std::shared_ptr<Titanium::UI::TableViewSection>& section, const std::shared_ptr<Titanium::UI::TableViewRow>& row, const std::uint32_t& rowIndex, const std::shared_ptr<Titanium::UI::TableViewRow>& old_row)
		{
			const std::uint32_t sectionIndex = model__->getSectionIndex(section);
			TITANIUM_ASSERT(collectionViewItems__->Size > sectionIndex);

			if (name == "append") {
				unbindCollectionViewSource();
				const auto rowIndexInCollectionView = getRowIndexInCollectionView(section, rowIndex);
				const auto views = static_cast<Vector<UIElement^>^>(collectionViewItems__->GetAt(sectionIndex));
				const auto rowContent = row->getViewLayoutDelegate<WindowsViewLayoutDelegate>()->getComponent();
				TITANIUM_ASSERT(rowContent);
				if (views->Size > rowIndexInCollectionView) {
					views->InsertAt(rowIndexInCollectionView, rowContent);
				} else {
					views->Append(rowContent);
				}
				registerTableViewRowAsLayoutNode(row);
				bindCollectionViewSource();
			} else if (name == "remove") {
				unbindCollectionViewSource();
				const auto views = static_cast<Vector<UIElement^>^>(collectionViewItems__->GetAt(sectionIndex));
				views->RemoveAt(getRowIndexInCollectionView(section, rowIndex));
				unregisterTableViewRowAsLayoutNode(row);
				bindCollectionViewSource();
			} else if (name == "update") {
				TITANIUM_ASSERT(old_row != nullptr);
				unbindCollectionViewSource();
				unregisterTableViewRowAsLayoutNode(old_row);

				const auto views = static_cast<Vector<UIElement^>^>(collectionViewItems__->GetAt(sectionIndex));
				const auto rowContent = row->getViewLayoutDelegate<WindowsViewLayoutDelegate>()->getComponent();
				views->SetAt(getRowIndexInCollectionView(section, rowIndex), rowContent);
				registerTableViewRowAsLayoutNode(row);
				bindCollectionViewSource();
			} else {
				TITANIUM_LOG_WARN("TableView: Unknown TableViewSectionEvent: ", name);
			}

			Titanium::UI::TableView::fireTableViewSectionEvent(name, section, row, rowIndex, old_row);
		}

		void TableView::scrollToIndex(const uint32_t& index, const std::shared_ptr<Titanium::UI::TableViewAnimationProperties>& animation) TITANIUM_NOEXCEPT
		{
			// On Windows the top value is interpreted as a row index
			const auto result = searchRowByIndex(index);

			if (result.found) {
				auto rows = static_cast<Vector<UIElement^>^>(collectionViewItems__->GetAt(result.sectionIndex));
				tableview__->ScrollIntoView(rows->GetAt(result.rowIndex));
			} else {
				TITANIUM_LOG_WARN("TableView::scrollToIndex: Invalid row index ", index);
			}
		}

		void TableView::scrollToTop(const uint32_t& top, const std::shared_ptr<Titanium::UI::TableViewAnimationProperties>& animation) TITANIUM_NOEXCEPT
		{
			// On Windows the top value is interpreted as a row index
			scrollToIndex(top, animation);
		}

		void TableView::selectRow(const uint32_t& row) TITANIUM_NOEXCEPT
		{
			tableview__->SelectedIndex = row;
		}

		void TableView::deselectRow(const uint32_t& row) TITANIUM_NOEXCEPT
		{
			tableview__->SelectedIndex = row;
		}
	}  // namespace UI
}  // namespace TitaniumWindows