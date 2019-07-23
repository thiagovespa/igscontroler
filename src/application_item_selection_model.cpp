/****************************************************************************
** Copyright (c) 2019, Fougue Ltd. <http://www.fougue.pro>
** All rights reserved.
** See license at https://github.com/fougue/mayo/blob/master/LICENSE.txt
****************************************************************************/

#include "application_item_selection_model.h"

namespace Mayo {

namespace Internal {

static bool hasApplicationItem(
        Span<ApplicationItem> vec, const ApplicationItem& item)
{
    auto itFound = std::find(vec.cbegin(), vec.cend(), item);
    return itFound != vec.cend();
}

static std::vector<ApplicationItem>::iterator findApplicationItem(
        std::vector<ApplicationItem>& vec, const ApplicationItem& item)
{
    return std::find(vec.begin(), vec.end(), item);
}

} // namespace Internal

ApplicationItemSelectionModel::ApplicationItemSelectionModel(QObject *parent)
    : QObject(parent)
{
}

Span<const ApplicationItem> ApplicationItemSelectionModel::selectedItems() const
{
    return m_vecSelectedItem;
}

bool ApplicationItemSelectionModel::hasSelectedDocumentItems() const
{
    for (const ApplicationItem& item : m_vecSelectedItem) {
        if (item.isDocumentItem())
            return true;
    }
    return false;
}

std::vector<DocumentItem*> ApplicationItemSelectionModel::selectedDocumentItems() const
{
    std::vector<DocumentItem*> vecDocItem;
    vecDocItem.reserve(m_vecSelectedItem.size());
    for (const ApplicationItem& item : m_vecSelectedItem) {
        if (item.isDocumentItem())
            vecDocItem.push_back(item.documentItem());
    }
    return vecDocItem;
}

void ApplicationItemSelectionModel::add(const ApplicationItem &item)
{
    if (!Internal::hasApplicationItem(m_vecSelectedItem, item)) {
        m_vecSelectedItem.push_back(item);
        std::vector<ApplicationItem> vecItem = { item };
        emit changed(vecItem, {});
    }
}

void ApplicationItemSelectionModel::add(Span<ApplicationItem> vecItem)
{
    std::vector<ApplicationItem> signalVecItem;
    for (const ApplicationItem& item : vecItem) {
        if (!Internal::hasApplicationItem(m_vecSelectedItem, item)) {
            m_vecSelectedItem.push_back(item);
            signalVecItem.push_back(item);
        }
    }
    if (!signalVecItem.empty())
        emit changed(signalVecItem, {});
}

void ApplicationItemSelectionModel::remove(const ApplicationItem &item)
{
    auto itFound = Internal::findApplicationItem(m_vecSelectedItem, item);
    if (itFound != m_vecSelectedItem.end()) {
        m_vecSelectedItem.erase(itFound);
        std::vector<ApplicationItem> vecItem = { item };
        emit changed({}, vecItem);
    }
}

void ApplicationItemSelectionModel::remove(Span<ApplicationItem> vecItem)
{
    std::vector<ApplicationItem> signalVecItem;
    for (const ApplicationItem& item : vecItem) {
        auto itFound = Internal::findApplicationItem(m_vecSelectedItem, item);
        if (itFound != m_vecSelectedItem.end()) {
            m_vecSelectedItem.erase(itFound);
            signalVecItem.push_back(item);
        }
    }
    if (!signalVecItem.empty())
        emit changed({}, signalVecItem);
}

void ApplicationItemSelectionModel::clear()
{
    if (!m_vecSelectedItem.empty()) {
        m_vecSelectedItem.clear();
        emit cleared();
    }
}

} // namespace Mayo
