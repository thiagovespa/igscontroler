/****************************************************************************
** Copyright (c) 2019, Fougue Ltd. <http://www.fougue.pro>
** All rights reserved.
** See license at https://github.com/fougue/mayo/blob/master/LICENSE.txt
****************************************************************************/

#include "theme.h"
#include "span.h"

#include <QtGui/QImage>
#include <QtGui/QPalette>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QStyleFactory>
#include <unordered_map>

namespace Mayo {

namespace Internal {

static QString cssFlatComboBox(
        const QString& urlPixDownArrow,
        const QString& urlPixDownArrowDisabled)
{
    const QPalette appPalette = qApp->palette();
    const QString css = QString(
                "QComboBox {"
                "    border-style: solid;"
                "    background: %1;"
                "    padding: 2px 15px 2px 10px;"
                "}\n"
                "QComboBox:hover {"
                "    border-style: solid;"
                "    background: %2;"
                "    padding: 2px 15px 2px 10px;"
                "}\n"
                "QComboBox::drop-down {"
                "    subcontrol-origin: padding;"
                "    subcontrol-position: top right;"
                "    width: 15px;"
                "    border-left-width: 0px;"
                "    border-top-right-radius: 3px;"
                "    border-bottom-right-radius: 3px;"
                "}\n"
                "QComboBox::down-arrow { image: url(%3); }\n"
                "QComboBox::down-arrow:disabled { image: url(%4); }\n"
                ).arg(appPalette.color(QPalette::Window).name(),
                      appPalette.color(QPalette::Window).darker(110).name(),
                      urlPixDownArrow,
                      urlPixDownArrowDisabled);
    return css;
}

static QPixmap invertedPixmap(const QPixmap& pix)
{
    QPixmap pixInv;
    QImage img = pix.toImage();
    img.invertPixels();
    return QPixmap::fromImage(img);
}

static QString iconFileName(Theme::Icon icn)
{
    switch (icn) {
    case Theme::Icon::File: return "file.svg";
    case Theme::Icon::Import: return "import.svg";
    case Theme::Icon::Edit: return "edit.svg";
    case Theme::Icon::Export: return "export.svg";
    case Theme::Icon::Expand: return "expand.svg";
    case Theme::Icon::Cross: return "cross.svg";
    case Theme::Icon::Link: return "link.svg";
    case Theme::Icon::Back: return "back.svg";
    case Theme::Icon::Next: return "next.svg";
    case Theme::Icon::Camera: return "camera.svg";
    case Theme::Icon::LeftSidebar: return "left-sidebar.svg";
    case Theme::Icon::BackSquare: return "back-square.svg";
    case Theme::Icon::IndicatorDown: return "indicator-down_8.png";
    case Theme::Icon::Stop: return "stop.svg";
    case Theme::Icon::Gear: return "gear.svg";
    case Theme::Icon::ZoomIn: return "zoom-in.svg";
    case Theme::Icon::ZoomOut: return "zoom-out.svg";
    case Theme::Icon::ClipPlane: return "clip-plane.svg";
    case Theme::Icon::View3dIso: return "view-iso.svg";
    case Theme::Icon::View3dLeft: return "view-left.svg";
    case Theme::Icon::View3dRight: return "view-right.svg";
    case Theme::Icon::View3dTop: return "view-top.svg";
    case Theme::Icon::View3dBottom: return "view-bottom.svg";
    case Theme::Icon::View3dFront: return "view-front.svg";
    case Theme::Icon::View3dBack: return "view-back.svg";
    case Theme::Icon::ItemMesh: return "item-mesh.svg";
    case Theme::Icon::ItemXde: return "item-xde.svg";
    case Theme::Icon::XdeAssembly: return "xde-assembly.svg";
    case Theme::Icon::XdeSimpleShape: return "xde-simple-shape.svg";
    }
    return QString();
}

static Span<const Theme::Icon> themeIcons()
{
    static const Theme::Icon arrayIcons[] = {
        Theme::Icon::File,
        Theme::Icon::Import,
        Theme::Icon::Edit,
        Theme::Icon::Export,
        Theme::Icon::Expand,
        Theme::Icon::Cross,
        Theme::Icon::Link,
        Theme::Icon::Back,
        Theme::Icon::Next,
        Theme::Icon::Camera,
        Theme::Icon::LeftSidebar,
        Theme::Icon::BackSquare,
        Theme::Icon::IndicatorDown,
        Theme::Icon::Stop,
        Theme::Icon::Gear,
        Theme::Icon::ZoomIn,
        Theme::Icon::ZoomOut,
        Theme::Icon::ClipPlane,
        Theme::Icon::View3dIso,
        Theme::Icon::View3dLeft,
        Theme::Icon::View3dRight,
        Theme::Icon::View3dTop,
        Theme::Icon::View3dBottom,
        Theme::Icon::View3dFront,
        Theme::Icon::View3dBack,
        Theme::Icon::ItemMesh,
        Theme::Icon::ItemXde,
        Theme::Icon::XdeAssembly,
        Theme::Icon::XdeSimpleShape
    };
    return arrayIcons;
}

static const QIcon nullQIcon = {};

class ThemeClassic : public Theme {
public:
    QColor color(Color role) const override
    {
        const QPalette appPalette = qApp->palette();
        switch (role) {
        case Theme::Color::Palette_Base:
            return appPalette.color(QPalette::Base);
        case Theme::Color::Palette_Window:
            return appPalette.color(QPalette::Window);
        case Theme::Color::Palette_Button:
        case Theme::Color::ButtonFlat_Background:
        case Theme::Color::ButtonView3d_Background:
            return appPalette.color(QPalette::Button);
        case Theme::Color::ButtonFlat_Hover:
            return appPalette.color(QPalette::Button).darker(110);
        case Theme::Color::ButtonFlat_Checked:
            return appPalette.color(QPalette::Button).darker(125);
        case Theme::Color::ButtonView3d_Hover:
        case Theme::Color::ButtonView3d_Checked:
            return QColor(65, 200, 250);
        case Theme::Color::View3d_BackgroundGradientStart:
            return QColor(128, 148, 255);
        case Theme::Color::View3d_BackgroundGradientEnd:
            return Qt::white;
        case Theme::Color::MessageIndicator_Background:
            return QColor(128, 200, 255);
        case Theme::Color::MessageIndicator_Text:
            return appPalette.color(QPalette::WindowText);
        }
        return QColor();
    }

    const QIcon& icon(Icon icn) const override
    {
        auto it = m_mapIcon.find(icn);
        return it != m_mapIcon.cend() ? it->second : nullQIcon;
    }

    void setup() override
    {
        const QString icnBasePath = ":/images/themes/classic/";
        for (const Icon icn : themeIcons()) {
            const QString icnFileName = iconFileName(icn);
            m_mapIcon.emplace(icn, QIcon(QPixmap(icnBasePath + icnFileName)));
        }
    }

    void setupHeaderComboBox(QComboBox* cb)
    {
        const QString urlDown(":/images/themes/classic/indicator-down_8.png");
        const QString urlDownDisabled(":/images/themes/classic/indicator-down-disabled_8.png");
        cb->setStyleSheet(cssFlatComboBox(urlDown, urlDownDisabled));
    }

private:
    std::unordered_map<Theme::Icon, QIcon> m_mapIcon;
};

class ThemeDark : public Theme {
public:
    QColor color(Color role) const override
    {
        const QPalette appPalette = qApp->palette();
        switch (role) {
        case Theme::Color::Palette_Base:
            return appPalette.color(QPalette::Base);
        case Theme::Color::Palette_Window:
            return appPalette.color(QPalette::Window);
        case Theme::Color::Palette_Button:
        case Theme::Color::ButtonFlat_Background:
            return appPalette.color(QPalette::Button);
        case Theme::Color::ButtonFlat_Hover:
            return appPalette.color(QPalette::Button).darker(110);
        case Theme::Color::ButtonFlat_Checked:
            return appPalette.color(QPalette::Button).darker(125);
        case Theme::Color::ButtonView3d_Background:
            return appPalette.color(QPalette::Button).lighter(125);
        case Theme::Color::ButtonView3d_Hover:
        case Theme::Color::ButtonView3d_Checked:
            return appPalette.color(QPalette::Button).lighter(160);
        case Theme::Color::View3d_BackgroundGradientStart:
            return QColor(100, 100, 100);
        case Theme::Color::View3d_BackgroundGradientEnd:
            return QColor(200, 200, 200);
        case Theme::Color::MessageIndicator_Background:
            return appPalette.color(QPalette::Highlight).lighter(125);
        case Theme::Color::MessageIndicator_Text:
            return appPalette.color(QPalette::WindowText);
        }
        return QColor();
    }

    const QIcon& icon(Icon icn) const override
    {
        auto it = m_mapIcon.find(icn);
        return it != m_mapIcon.cend() ? it->second : nullQIcon;
    }

    void setup() override
    {
        const QString icnBasePath = ":/images/themes/dark/";
        for (const Icon icn : themeIcons()) {
            const QString icnFileName = iconFileName(icn);
            QPixmap pix(icnBasePath + icnFileName);
            if (icn != Icon::Stop)
                pix = invertedPixmap(pix);
            m_mapIcon.emplace(icn, pix);
        }

        qApp->setStyle(QStyleFactory::create("Fusion"));
        QPalette p = qApp->palette();
        p.setColor(QPalette::Base, QColor(80, 80, 80));
        p.setColor(QPalette::Window, QColor(53, 53, 53));
        p.setColor(QPalette::Button, QColor(73, 73, 73));
        p.setColor(QPalette::Highlight, QColor(110, 110, 110));
        p.setColor(QPalette::Text, Qt::white);
        p.setColor(QPalette::ButtonText, Qt::white);
        p.setColor(QPalette::WindowText, Qt::white);
        const QColor linkColor(115, 131, 191);
        p.setColor(QPalette::Link, linkColor);
        p.setColor(QPalette::LinkVisited, linkColor);

        const QColor disabledGray(40, 40, 40);
        const QColor disabledTextGray(128, 128, 128);
        p.setColor(QPalette::Disabled, QPalette::Window, disabledGray);
        p.setColor(QPalette::Disabled, QPalette::Base, disabledGray);
        p.setColor(QPalette::Disabled, QPalette::AlternateBase, disabledGray);
        p.setColor(QPalette::Disabled, QPalette::Button, disabledGray);
        p.setColor(QPalette::Disabled, QPalette::Text, disabledTextGray);
        p.setColor(QPalette::Disabled, QPalette::ButtonText, disabledTextGray);
        p.setColor(QPalette::Disabled, QPalette::WindowText, disabledTextGray);
        qApp->setPalette(p);

        const QString css =
                "QFrame[frameShape=\"5\"] { color: gray; margin-top: 2px; margin-bottom: 2px; } "
                "QAbstractItemView { background: #505050; } "
                "QAbstractItemView::item:hover { background: #606060; }"
                "QLineEdit { background: #505050; }"
                "QMenu { background: #505050; border: 1px solid rgb(100,100,100); }"
                "QMenu::item:selected { background: rgb(110,110,110); }"
                "QTextEdit { background: #505050; }"
                "QSpinBox  { background: #505050; }"
                "QDoubleSpinBox { background: #505050; }"
                "QToolButton:checked { background: #383838; }"
                "QToolButton:pressed { background: #383838; }"
                "QComboBox { background: #505050; } "
                "QGroupBox { border: 1px solid #808080; margin-top: 4ex; } "
                "QFileDialog { background: #505050; } "
                "QComboBox:editable { background: #505050; } "
                "QComboBox::disabled { background: rgb(40,40,40); } "
                "QProgressBar { background: #505050; }";
        qApp->setStyleSheet(css);
    }

    void setupHeaderComboBox(QComboBox* cb)
    {
        const QString urlDown(":/images/themes/dark/indicator-down_8.png");
        const QString urlDownDisabled(":/images/themes/classic/indicator-down-disabled_8.png");
        cb->setStyleSheet(cssFlatComboBox(urlDown, urlDownDisabled));
    }

private:
    std::unordered_map<Theme::Icon, QIcon> m_mapIcon;
};

} // namespace Internal

Theme* createTheme(const QString& key)
{
    if (key == "classic")
        return new Internal::ThemeClassic;
    if (key == "dark")
        return new Internal::ThemeDark;
    return nullptr;
}

} // namespace Mayo
