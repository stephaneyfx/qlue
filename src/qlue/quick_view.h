/*
Copyright (C) 2017 Stephane Raux. Distributed under the MIT license.
*/

#ifndef QLUE_QUICK_VIEW_H
#define QLUE_QUICK_VIEW_H

#include <clue/string.h>
#include <stdint.h>
#include "config.h"

#ifdef __cplusplus
extern "C" {
#endif

struct QlueQuickViewTag {
    uintptr_t p;
};

typedef struct QlueQuickViewTag QlueQuickView;

QLUE_API QlueQuickView qlueQuickViewNew();
QLUE_API void qlueQuickViewDelete(QlueQuickView v);
QLUE_API void qlueQuickViewSetSource(QlueQuickView v, ClueStringView url);
QLUE_API void qlueQuickViewShow(QlueQuickView v);

#ifdef __cplusplus
}
#endif

#endif
