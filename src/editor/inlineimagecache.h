/*
 * SPDX-FileCopyrightText: 2026 the ghostwriter authors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INLINE_IMAGE_CACHE_H
#define INLINE_IMAGE_CACHE_H

#include <QHash>
#include <QObject>
#include <QPixmap>
#include <QTextBlock>

namespace ghostwriter
{

constexpr int inlineImageTopGap = 6;

class InlineImageCache : public QObject
{
    Q_OBJECT

public:
    explicit InlineImageCache(QObject *parent = nullptr);

    void setDocumentDirectory(const QString &directory);
    void setColumnWidth(int width);

    int extraHeight(const QTextBlock &block) const;
    QPixmap thumbnail(const QTextBlock &block) const;

private:
    struct ScaledImage {
        QPixmap pixmap;
    };

    QString imageTarget(const QString &blockText) const;
    QString resolvedPath(const QString &target) const;
    QPixmap scaledThumbnail(const QString &path) const;

    QString m_documentDirectory;
    int m_columnWidth = 0;
    mutable QHash<QString, ScaledImage> m_thumbnails;
};

} // namespace ghostwriter

#endif
