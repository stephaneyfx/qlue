/*
Copyright (C) 2017 Stephane Raux. Distributed under the MIT license.
*/

#include <cstdint>
#include <exception>
#include <qlue/helpers/string.hpp>
#include <QtCore/QtGlobal>
#include <QtQuick/QQuickView>
#include "quick_view.h"

namespace {
    QQuickView& get_view(QlueQuickView v) noexcept {
        return *reinterpret_cast<QQuickView*>(v.p);
    }

    QlueQuickView newView() noexcept {
        try {
            auto v = new QQuickView;
            return QlueQuickView {reinterpret_cast<std::uintptr_t>(v)};
        } catch (const std::exception& e) {
            qFatal("Failed to create QQuickView: %s", e.what());
            return QlueQuickView {};
        }
    }

    void deleteView(QlueQuickView v) noexcept {
        try {
            delete &get_view(v);
        } catch (const std::exception& e) {
            qFatal("Failed to destroy QQuickView: %s", e.what());
        }
    }

    void setViewSource(QlueQuickView view, ClueStringView url) noexcept {
        try {
            get_view(view).setSource(qlue::toString(url));
        } catch (const std::exception& e) {
            qFatal("Failed to set QQuickView source: %s", e.what());
        }
    }

    void showView(QlueQuickView view) noexcept {
        try {
            get_view(view).show();
        } catch (const std::exception& e) {
            qFatal("Failed to show QQuickView: %s", e.what());
        }
    }
}

QlueQuickView qlueQuickViewNew() {
    return newView();
}

void qlueQuickViewDelete(QlueQuickView v) {
    deleteView(v);
}

void qlueQuickViewSetSource(QlueQuickView v, ClueStringView url) {
    setViewSource(v, url);
}

void qlueQuickViewShow(QlueQuickView v) {
    showView(v);
}
