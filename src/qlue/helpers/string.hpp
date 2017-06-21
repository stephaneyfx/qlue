// Copyright (C) 2017 Stephane Raux. Distributed under the MIT license.

#ifndef QLUE_HELPERS_STRING_HPP
#define QLUE_HELPERS_STRING_HPP

#include <clue/string.h>
#include <QtCore/QByteArray>
#include <QtCore/QString>

namespace qlue {
inline QByteArray toByteArray(ClueStringView s) {
    return QByteArray(s.s, static_cast<int>(s.len));
}

inline QString toString(ClueStringView s) {
    return QString::fromUtf8(s.s, static_cast<int>(s.len));
}

inline ClueStringView toStringView(const QByteArray& s) {
    return ClueStringView {s.constData(), static_cast<size_t>(s.size())};
}
}

#endif
