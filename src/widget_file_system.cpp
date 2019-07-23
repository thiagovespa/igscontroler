/****************************************************************************
** Copyright (c) 2019, Fougue Ltd. <http://www.fougue.pro>
** All rights reserved.
** See license at https://github.com/fougue/mayo/blob/master/LICENSE.txt
****************************************************************************/

#include "widget_file_system.h"

#include <QtCore/QDateTime>
#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QTreeWidget>

namespace Mayo {

namespace Internal {

static std::pair<uint64_t, QString> fileSizeQuantity(uint64_t sizeBytes)
{
    if (sizeBytes < 1024 )
        return { sizeBytes, WidgetFileSystem::tr("B") };
    else if (sizeBytes < 1024*1024)
        return { sizeBytes / 1024, WidgetFileSystem::tr("KB") };
    else
        return { sizeBytes / (1024*1024), WidgetFileSystem::tr("MB") };
}

static QString absolutePath(const QFileInfo& fi)
{
    return fi.isDir() ? fi.absoluteFilePath() : fi.absolutePath();
}

} // namespace Internal

WidgetFileSystem::WidgetFileSystem(QWidget *parent)
    : QWidget(parent),
      m_treeWidget(new QTreeWidget(this))
{
    auto layout = new QVBoxLayout;
    layout->addWidget(m_treeWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(layout);

    m_treeWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    m_treeWidget->setColumnCount(1);
    m_treeWidget->setIndentation(0);

    QObject::connect(
                m_treeWidget, &QTreeWidget::itemActivated,
                this, &WidgetFileSystem::onTreeItemActivated);
}

QFileInfo WidgetFileSystem::currentLocation() const
{
    return m_location;
}

void WidgetFileSystem::setLocation(const QFileInfo &fiLoc)
{
    const QString pathCurrLocation = Internal::absolutePath(m_location);
    const QString pathLoc = Internal::absolutePath(fiLoc);
    if (pathCurrLocation == pathLoc) {
        for (int i = 0; i < m_treeWidget->topLevelItemCount(); ++i) {
            QTreeWidgetItem* item = m_treeWidget->topLevelItem(i);
            if (item->text(0) == fiLoc.fileName()) {
                m_treeWidget->clearSelection();
                item->setSelected(true);
                break;
            }
        }
    }
    else {
        m_treeWidget->clear();
        QTreeWidgetItem* itemToBeSelected = nullptr;
        QList<QTreeWidgetItem*> listItem;
        if (fiLoc.exists()) {
            const QDir dir(pathLoc);
            const QFileInfoList listEntryFileInfo =
                    dir.entryInfoList(
                        QDir::Files | QDir::AllDirs | QDir::NoDot,
                        QDir::DirsFirst);
            for (const QFileInfo& fi : listEntryFileInfo) {
                auto item = new QTreeWidgetItem;
                if (fi.fileName() != QLatin1String(".")) {
                    item->setText(0, fi.fileName());
                    item->setIcon(0, m_fileIconProvider.icon(fi));
                    const auto sizeQty = Internal::fileSizeQuantity(fi.size());
                    const QString itemTooltip =
                            tr("%1\nSize: %2%3\nLast modified: %4")
                            .arg(QDir::toNativeSeparators(fi.absoluteFilePath()))
                            .arg(sizeQty.first).arg(sizeQty.second)
                            .arg(fi.lastModified().toString(Qt::SystemLocaleShortDate));
                    item->setToolTip(0, itemTooltip);
                    if (fi.fileName() == fiLoc.fileName())
                        itemToBeSelected = item;
                }
                listItem.push_back(item);
            }
        }
        m_treeWidget->addTopLevelItems(listItem);
        m_treeWidget->headerItem()->setText(0, fiLoc.dir().dirName());
        if (itemToBeSelected != nullptr)
            itemToBeSelected->setSelected(true);
    }
    m_location = fiLoc;
}

void WidgetFileSystem::onTreeItemActivated(QTreeWidgetItem *item, int column)
{
    if (item != nullptr && column == 0) {
        if (item->text(0) == QLatin1String("..")) {
            this->setLocation(m_location.absoluteDir().path());
        }
        else {
            const QDir dir(Internal::absolutePath(m_location));
            const QFileInfo fi(dir, item->text(0));
            if (fi.isDir())
                this->setLocation(fi);
            else
                emit this->locationActivated(fi);
        }
    }
}

} // namespace Mayo
