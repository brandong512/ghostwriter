/*
 * SPDX-FileCopyrightText: 2026 the ghostwriter authors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "margintheme.h"

#include <QGuiApplication>
#include <QSettings>
#include <QStyleHints>

namespace ghostwriter
{

MarginTheme MarginTheme::light()
{
    MarginTheme theme;
    theme.bg = QColor(QStringLiteral("#FBFAF7"));
    theme.frame = QColor(QStringLiteral("#E8E4DC"));
    theme.text = QColor(QStringLiteral("#1D1C1A"));
    theme.muted = QColor(QStringLiteral("#6B675F"));
    theme.faint = QColor(QStringLiteral("#B3AEA4"));
    theme.accent = QColor(QStringLiteral("#B0532A"));
    theme.blue = QColor(QStringLiteral("#2563EB"));
    theme.select = QColor(37, 99, 235, 46);
    theme.border = QColor(QStringLiteral("#E5E1D8"));
    theme.hover = QColor(QStringLiteral("#F0EDE7"));
    theme.panel = QColor(QStringLiteral("#FFFFFF"));
    theme.danger = QColor(QStringLiteral("#C42B1C"));
    return theme;
}

MarginTheme MarginTheme::dark()
{
    MarginTheme theme;
    theme.bg = QColor(QStringLiteral("#171716"));
    theme.frame = QColor(QStringLiteral("#2A2927"));
    theme.text = QColor(QStringLiteral("#ECE9E2"));
    theme.muted = QColor(QStringLiteral("#A19C92"));
    theme.faint = QColor(QStringLiteral("#5F5B54"));
    theme.accent = QColor(QStringLiteral("#E3936C"));
    theme.blue = QColor(QStringLiteral("#6EA8FE"));
    theme.select = QColor(110, 168, 254, 72);
    theme.border = QColor(QStringLiteral("#2D2C29"));
    theme.hover = QColor(QStringLiteral("#262523"));
    theme.panel = QColor(QStringLiteral("#1F1F1D"));
    theme.danger = QColor(QStringLiteral("#C42B1C"));
    return theme;
}

ColorScheme marginColorScheme(const MarginTheme &theme)
{
    ColorScheme colors;
    colors.foreground = theme.text;
    colors.background = theme.bg;
    colors.selection = theme.select;
    colors.cursor = theme.text;
    colors.link = theme.blue;
    colors.image = theme.blue;
    colors.inlineHtml = theme.muted;
    colors.headingText = theme.text;
    colors.headingMarkup = theme.faint;
    colors.emphasisText = theme.text;
    colors.emphasisMarkup = theme.faint;
    colors.blockquoteText = theme.muted;
    colors.blockquoteMarkup = theme.faint;
    colors.divider = theme.border;
    colors.listMarkup = theme.faint;
    colors.codeText = theme.text;
    colors.codeMarkup = theme.faint;
    colors.error = theme.danger;
    return colors;
}

MarginColorMode savedMarginColorMode()
{
    const QString mode = QSettings().value(QStringLiteral("margin/colorMode"), QStringLiteral("system")).toString();

    if (mode == QLatin1String("light")) {
        return MarginColorMode::Light;
    }
    if (mode == QLatin1String("dark")) {
        return MarginColorMode::Dark;
    }
    return MarginColorMode::System;
}

void storeMarginColorMode(MarginColorMode mode)
{
    QString value = QStringLiteral("system");

    if (mode == MarginColorMode::Light) {
        value = QStringLiteral("light");
    } else if (mode == MarginColorMode::Dark) {
        value = QStringLiteral("dark");
    }

    QSettings().setValue(QStringLiteral("margin/colorMode"), value);
}

bool marginIsDark(MarginColorMode mode)
{
    if (mode == MarginColorMode::Dark) {
        return true;
    }
    if (mode == MarginColorMode::Light) {
        return false;
    }
    return QGuiApplication::styleHints()->colorScheme() == Qt::ColorScheme::Dark;
}

} // namespace ghostwriter
