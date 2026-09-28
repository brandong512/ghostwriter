/*
 * SPDX-FileCopyrightText: 2026 the ghostwriter authors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INLINE_IMAGE_LAYOUT_H
#define INLINE_IMAGE_LAYOUT_H

#include <QPixmap>
#include <QPlainTextDocumentLayout>

namespace ghostwriter
{

class InlineImageCache;

class InlineImageLayout : public QPlainTextDocumentLayout
{
    Q_OBJECT

public:
    InlineImageLayout(QTextDocument *document, InlineImageCache *cache);

    QRectF blockBoundingRect(const QTextBlock &block) const override;

    void setDocumentDirectory(const QString &directory);
    void setColumnWidth(int width);
    int extraHeight(const QTextBlock &block) const;
    QPixmap thumbnail(const QTextBlock &block) const;

private:
    InlineImageCache *m_cache;
};

} // namespace ghostwriter

#endif
