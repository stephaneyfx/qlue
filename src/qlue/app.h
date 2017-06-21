/*
Copyright (C) 2017 Stephane Raux. Distributed under the MIT license.
*/

#ifndef QLUE_APP_H
#define QLUE_APP_H

#include <clue/log.h>
#include <clue/string.h>
#include "config.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
Instantiates a Qt application suitable to use QML (currently a
\c QGuiApplication).

\param logger
    Logger to forward Qt log messages to. May be null. The logger may be called
    concurrently for as long as the Qt application lives.

\return 0 on success, non-zero on failure.

\note If successful, the application instance should be destroyed by calling
    \c qlueAppDelete.

\warning \c argc and \c argv must be valid for the lifetime of the application
    as stated in the Qt documentation (as of Qt 5.9).
*/
QLUE_API int qlueAppNew(int* argc, char** argv, ClueLogFn logger);

/**
Destroys the Qt application previously created by \c qlueAppNew.
*/
QLUE_API void qlueAppDelete();

/**
Calls the given function with the environment \c env and the name of the
application.
*/
QLUE_API void qlueAppName(void* env, void (*f)(void*, ClueStringView));

QLUE_API void qlueAppSetName(ClueStringView name);
QLUE_API int qlueAppExec();

/**
Sets the Qt QuickControls2 style.

\note The same restrictions as `QQuickStyle::setStyle` apply, i.e. the style
    must be set before loading QML components and cannot be changed afterwards.
*/
QLUE_API void qlueAppSetStyle(ClueStringView style);

#ifdef __cplusplus
}
#endif

#endif
