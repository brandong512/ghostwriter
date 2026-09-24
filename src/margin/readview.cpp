/*
 * SPDX-FileCopyrightText: 2026 the ghostwriter authors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "readview.h"

#include <QTextDocument>

namespace ghostwriter
{

ReadView::ReadView(QWidget *parent)
    : QTextBrowser(parent)
{
    setFrameStyle(QFrame::NoFrame);
    setOpenExternalLinks(true);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void ReadView::showMarkdown(const QString &markdown)
{
    document()->setMarkdown(markdown, QTextDocument::MarkdownDialectGitHub);
}

void ReadView::applyTheme(const MarginTheme &theme, const QFont &bodyFont)
{
    setFont(bodyFont);
    document()->setDefaultFont(bodyFont);
    document()->setDefaultStyleSheet(QStringLiteral("a { color: %1; }"
                                                    "h1, h2, h3, h4, h5, h6, b, strong { font-weight: 600; }"
                                                    "blockquote { color: %2; font-style: italic; }")
                                         .arg(theme.blue.name(), theme.muted.name()));

    setStyleSheet(QStringLiteral("QTextBrowser { background: %1; color: %2; border: 0;"
                                 " selection-background-color: %3; selection-color: %2; }")
                      .arg(theme.bg.name(), theme.text.name(), theme.select.name(QColor::HexArgb)));
}

void ReadView::setColumnMargins(const QMargins &margins)
{
    setViewportMargins(margins);
}

} // namespace ghostwriter
