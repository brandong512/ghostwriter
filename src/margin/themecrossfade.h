/*
 * SPDX-FileCopyrightText: 2026 the ghostwriter authors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef THEME_CROSSFADE_H
#define THEME_CROSSFADE_H

#include <functional>

class QWidget;

namespace ghostwriter
{

class ThemeCrossfade
{
public:
    static void run(QWidget *window, const std::function<void()> &applyNewTheme);
};

} // namespace ghostwriter

#endif
