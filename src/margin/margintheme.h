/*
 * SPDX-FileCopyrightText: 2026 the ghostwriter authors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef MARGIN_THEME_H
#define MARGIN_THEME_H

#include <QColor>
#include <QString>

#include "editor/colorscheme.h"

namespace ghostwriter
{

struct MarginTheme {
    QColor bg;
    QColor frame;
    QColor text;
    QColor muted;
    QColor faint;
    QColor accent;
    QColor blue;
    QColor select;
    QColor border;
    QColor hover;
    QColor panel;
    QColor danger;

    static MarginTheme light();
    static MarginTheme dark();
};

ColorScheme marginColorScheme(const MarginTheme &theme);

enum class MarginColorMode {
    System,
    Light,
    Dark
};

MarginColorMode savedMarginColorMode();
void storeMarginColorMode(MarginColorMode mode);
bool marginIsDark(MarginColorMode mode);

} // namespace ghostwriter

#endif
