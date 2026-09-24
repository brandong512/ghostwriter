/*
 * SPDX-FileCopyrightText: 2026 the ghostwriter authors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef READ_VIEW_H
#define READ_VIEW_H

#include <QTextBrowser>

#include "margintheme.h"

namespace ghostwriter
{

/**
 * Read-only page that shows the document's Markdown rendered.
 */
class ReadView : public QTextBrowser
{
    Q_OBJECT

public:
    explicit ReadView(QWidget *parent = nullptr);

    void showMarkdown(const QString &markdown);
    void applyTheme(const MarginTheme &theme, const QFont &bodyFont);
    void setColumnMargins(const QMargins &margins);
};

} // namespace ghostwriter

#endif
