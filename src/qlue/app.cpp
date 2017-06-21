// Copyright (C) 2017 Stephane Raux. Distributed under the MIT license.

#include <clue/helpers/string.hpp>
#include <cstdlib>
#include <exception>
#include <QtCore/QtDebug>
#include <QtCore/QtGlobal>
#include <QtCore/QString>
#include <QtGui/QGuiApplication>
#include <QtQuickControls2/QQuickStyle>
#include "app.h"
#include "helpers/string.hpp"

namespace {
ClueLogFn logFn = nullptr;

ClueLogLevel toLogLevel(QtMsgType t) {
    switch (t) {
    case QtDebugMsg: return ClueLogLevelDebug;
    case QtInfoMsg: return ClueLogLevelInfo;
    case QtWarningMsg: return ClueLogLevelWarn;
    case QtCriticalMsg: return ClueLogLevelError;
    case QtFatalMsg: return ClueLogLevelError;
    }
    return ClueLogLevelError;
}

void forwardQtLogMessages(QtMsgType type, const QMessageLogContext& ctx,
        const QString& msg) {
    auto msgUtf8 = msg.toUtf8();
    auto level = toLogLevel(type);
    logFn(level, qlue::toStringView(msgUtf8), clue::toStringView(ctx.file),
        static_cast<std::size_t>(ctx.line), clue::toStringView("qt"));
    if (type == QtFatalMsg) {
        std::abort();
    }
}

void uninstallLogHandler() noexcept {
    if (!logFn) {return;}
    try {
        qInstallMessageHandler(nullptr);
    } catch (const std::exception& e) {
        qFatal("Failed to uninstall Qt message handler: %s", e.what());
    }
    logFn = nullptr;
}

int newApp(int* argc, char** argv, ClueLogFn logger) noexcept {
    try {
        if (logger) {
            logFn = logger;
            qInstallMessageHandler(forwardQtLogMessages);
        }
        new QGuiApplication(*argc, argv);
        return 0;
    } catch (const std::exception& e) {
        qCritical() << "Failed to create Qt app:"
            << QString::fromUtf8(e.what());
        uninstallLogHandler();
        return 1;
    }
}

void deleteApp() noexcept {
    try {
        delete QGuiApplication::instance();
    } catch (const std::exception& e) {
        qFatal("Failed to delete Qt app: %s", e.what());
    }
    uninstallLogHandler();
}

void appName(void* env, void (*f)(void*, ClueStringView)) noexcept {
    try {
        auto name = QCoreApplication::applicationName().toUtf8();
        f(env, qlue::toStringView(name));
    } catch (const std::exception& e) {
        qCritical() << "Failed to get Qt app name:"
            << QString::fromUtf8(e.what());
    }
}

void setAppName(ClueStringView name) noexcept {
    try {
        QCoreApplication::setApplicationName(qlue::toString(name));
    } catch (const std::exception& e) {
        qCritical() << "Failed to set Qt app name:"
            << QString::fromUtf8(e.what());
    }
}

int execApp() noexcept {
    try {
        return QGuiApplication::exec();
    } catch (const std::exception& e) {
        qCritical() << "Qt app event loop exited with an exception:"
            << QString::fromUtf8(e.what());
        return -1;
    }
}

void setAppStyle(ClueStringView style) noexcept {
    try {
        QQuickStyle::setStyle(qlue::toString(style));
    } catch (const std::exception& e) {
        qCritical() << "Failed to set Qt Quick style:"
            << QString::fromUtf8(e.what());
    }
}
}

int qlueAppNew(int* argc, char** argv, ClueLogFn logger) {
    return newApp(argc, argv, logger);
}

void qlueAppDelete() {
    deleteApp();
}

void qlueAppName(void* env, void (*f)(void*, ClueStringView)) {
    appName(env, f);
}

void qlueAppSetName(ClueStringView name) {
    setAppName(name);
}

int qlueAppExec() {
    return execApp();
}

void qlueAppSetStyle(ClueStringView style) {
    setAppStyle(style);
}
