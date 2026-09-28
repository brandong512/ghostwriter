/*
 * SPDX-FileCopyrightText: 2026 the ghostwriter authors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "inlineimagelayout.h"

#include "inlineimagecache.h"

namespace ghostwriter
{

InlineImageLayout::InlineImageLayout(QTextDocument *document, InlineImageCache *cache)
    : QPlainTextDocumentLayout(document)
    , m_cache(cache)
{
}

QRectF InlineImageLayout::blockBoundingRect(const QTextBlock &block) const
{
    QRectF rect = QPlainTextDocumentLayout::blockBoundingRect(block);
    const int extra = extraHeight(block);
    if (extra > 0) {
        rect.setHeight(rect.height() + extra);
    }
    return rect;
}

void InlineImageLayout::setDocumentDirectory(const QString &directory)
{
    m_cache->setDocumentDirectory(directory);
}

void InlineImageLayout::setColumnWidth(int width)
{
    m_cache->setColumnWidth(width);
}

int InlineImageLayout::extraHeight(const QTextBlock &block) const
{
    return m_cache->extraHeight(block);
}

QPixmap InlineImageLayout::thumbnail(const QTextBlock &block) const
{
    return m_cache->thumbnail(block);
}

} // namespace ghostwriter
