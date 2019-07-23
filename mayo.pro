TARGET = mayo
TEMPLATE = app

QT += core gui widgets

CONFIG += c++17

CONFIG(debug, debug|release) {
    CONFIG += console
} else {
    CONFIG -= console
    CONFIG += release_with_debuginfo
}

release_with_debuginfo:*msvc* {
    # https://docs.microsoft.com/en-us/cpp/build/reference/how-to-debug-a-release-build
    QMAKE_CXXFLAGS_RELEASE += /Zi
    QMAKE_LFLAGS_RELEASE += /DEBUG /INCREMENTAL:NO /OPT:REF /OPT:ICF
}

*msvc* {
    QMAKE_CXXFLAGS += /we4150 # Deletion of pointer to incomplete type 'XXXX'; no destructor called
    QMAKE_CXXFLAGS += /std:c++17
}
*g++*{
    QMAKE_CXXFLAGS += -std=c++17
}

include(version.pri)
CONFIG(debug, debug|release) {
    message(Mayo version $$MAYO_VERSION debug)
} else {
    message(Mayo version $$MAYO_VERSION release)
}

INCLUDEPATH += \
    src \
    src/3rdparty

HEADERS += \
    src/3rdparty/fougtools/occtools/occtools.h \
    src/3rdparty/fougtools/occtools/qt_utils.h \
    src/3rdparty/fougtools/qttools/core/qstring_hfunc.h \
    src/3rdparty/fougtools/qttools/gui/gui.h \
    src/3rdparty/fougtools/qttools/gui/item_view_buttons.h \
    src/3rdparty/fougtools/qttools/gui/item_view_utils.h \
    src/3rdparty/fougtools/qttools/gui/proxy_styled_item_delegate.h \
    src/3rdparty/fougtools/qttools/gui/qwidget_utils.h \
    src/ais_text.h \
    src/application.h \
    src/application_item.h \
    src/application_item_selection_model.h \
    src/bnd_utils.h \
    src/brep_utils.h \
    src/button_flat.h \
    src/caf_utils.h \
    src/dialog_about.h \
    src/dialog_export_options.h \
    src/dialog_inspect_xde.h \
    src/dialog_options.h \
    src/dialog_save_image_view.h \
    src/dialog_task_manager.h \
    src/document.h \
    src/document_item.h \
    src/gpx_document_item.h \
    src/gpx_mesh_item.h \
    src/gpx_utils.h \
    src/gpx_xde_document_item.h \
    src/gui_application.h \
    src/gui_document.h \
    src/libtree.h \
    src/mainwindow.h \
    src/math_utils.h \
    src/mesh_item.h \
    src/mesh_utils.h \
    src/occt_window.h \
    src/options.h \
    src/property.h \
    src/property_builtins.h \
    src/property_enumeration.h \
    src/qt_occ_view_controller.h \
    src/quantity.h \
    src/result.h \
    src/span.h \
    src/string_utils.h \
    src/theme.h \
    src/unit.h \
    src/unit_system.h \
    src/widget_application_tree.h \
    src/widget_clip_planes.h \
    src/widget_file_system.h \
    src/widget_gui_document.h \
    src/widget_message_indicator.h \
    src/widget_occ_view.h \
    src/widget_properties_editor.h \
    src/widget_shape_selector.h \
    src/xde_document_item.h \
    src/xde_shape_property_owner.h \
    src/gui_document_list_model.h \
    src/gpx_document_item_factory.h \
    src/v3d_view_camera_animation.h \
    src/qmeta_gp_pnt.h \
    src/qmeta_gp_trsf.h \
    src/qmeta_quantity_color.h \
    src/qmeta_tdf_label.h \
    src/qmeta_quantity.h

SOURCES += \
    src/3rdparty/fougtools/occtools/qt_utils.cpp \
    src/3rdparty/fougtools/qttools/gui/item_view_buttons.cpp \
    src/3rdparty/fougtools/qttools/gui/item_view_utils.cpp \
    src/3rdparty/fougtools/qttools/gui/proxy_styled_item_delegate.cpp \
    src/3rdparty/fougtools/qttools/gui/qwidget_utils.cpp \
    src/ais_text.cpp \
    src/application.cpp \
    src/application_item.cpp \
    src/application_item_selection_model.cpp \
    src/bnd_utils.cpp \
    src/brep_utils.cpp \
    src/button_flat.cpp \
    src/caf_utils.cpp \
    src/dialog_about.cpp \
    src/dialog_export_options.cpp \
    src/dialog_inspect_xde.cpp \
    src/dialog_options.cpp \
    src/dialog_save_image_view.cpp \
    src/dialog_task_manager.cpp \
    src/document.cpp \
    src/document_item.cpp \
    src/gpx_document_item.cpp \
    src/gpx_mesh_item.cpp \
    src/gpx_utils.cpp \
    src/gpx_xde_document_item.cpp \
    src/gui_application.cpp \
    src/gui_document.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/math_utils.cpp \
    src/mesh_item.cpp \
    src/mesh_utils.cpp \
    src/occt_window.cpp \
    src/options.cpp \
    src/property.cpp \
    src/property_builtins.cpp \
    src/property_enumeration.cpp \
    src/qt_occ_view_controller.cpp \
    src/quantity.cpp \
    src/result.cpp \
    src/string_utils.cpp \
    src/theme.cpp \
    src/unit.cpp \
    src/unit_system.cpp \
    src/widget_application_tree.cpp \
    src/widget_clip_planes.cpp \
    src/widget_file_system.cpp \
    src/widget_gui_document.cpp \
    src/widget_message_indicator.cpp \
    src/widget_occ_view.cpp \
    src/widget_properties_editor.cpp \
    src/widget_shape_selector.cpp \
    src/xde_document_item.cpp \
    src/xde_shape_property_owner.cpp \
    src/gui_document_list_model.cpp \
    src/gpx_document_item_factory.cpp \
    src/v3d_view_camera_animation.cpp

include(src/3rdparty/fougtools/qttools/task/qttools_task.pri)

FORMS += \
    src/dialog_about.ui \
    src/dialog_export_options.ui \
    src/dialog_inspect_xde.ui \
    src/dialog_options.ui \
    src/dialog_save_image_view.ui \
    src/dialog_task_manager.ui \
    src/mainwindow.ui \
    src/widget_application_tree.ui \
    src/widget_clip_planes.ui \
    src/widget_properties_editor.ui \

RESOURCES += mayo.qrc
RC_ICONS = images/appicon.ico

OTHER_FILES += \
    README.md \
    images/credits.txt

# gmio
isEmpty(GMIO_ROOT) {
    message(gmio OFF)
} else {
    message(gmio ON)
    CONFIG(debug, debug|release) {
        GMIO_BIN_SUFFIX = d
    } else {
        GMIO_BIN_SUFFIX =
    }
    INCLUDEPATH += $$GMIO_ROOT/include
    LIBS += -L$$GMIO_ROOT/lib -lgmio_static$$GMIO_BIN_SUFFIX
    SOURCES += \
        $$GMIO_ROOT/src/gmio_support/stl_occ_brep.cpp \
        $$GMIO_ROOT/src/gmio_support/stl_occ_polytri.cpp \
        $$GMIO_ROOT/src/gmio_support/stream_qt.cpp
    DEFINES += HAVE_GMIO
}

# OpenCascade
include(opencascade.pri)
LIBS += -lTKernel -lTKMath -lTKTopAlgo -lTKV3d -lTKOpenGl -lTKService
LIBS += -lTKG2d
LIBS += -lTKBRep -lTKSTL
LIBS += -lTKXSBase -lTKIGES -lTKSTEP -lTKXDESTEP -lTKXDEIGES
LIBS += -lTKMeshVS -lTKXSDRAW
LIBS += -lTKLCAF -lTKXCAF -lTKCAF
LIBS += -lTKG3d
LIBS += -lTKGeomBase
