/*
 * SPDX-FileCopyrightText: 2026 the ghostwriter authors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "inlineimagecache.h"

#include <QDir>
#include <QFileInfo>
#include <QImageReader>
#include <QRegularExpression>
#include <QUrl>

namespace ghostwriter
{
namespace
{
constexpr int maxThumbnailHeight = 320;

const QRegularExpression imageLineExpression(QStringLiteral("^\\s*!\\[[^\\]]*\\]\\((?:<([^>]+)>|([^)\\s]+))\\)\\s*$"));
}

InlineImageCache::InlineImageCache(QObject *parent)
    : QObject(parent)
{
}

void InlineImageCache::setDocumentDirectory(const QString &directory)
{
    if (m_documentDirectory == directory) {
        return;
    }

    m_documentDirectory = directory;
    m_thumbnails.clear();
}

void InlineImageCache::setColumnWidth(int width)
{
    if (m_columnWidth == width) {
        return;
    }

    m_columnWidth = width;
    m_thumbnails.clear();
}

int InlineImageCache::extraHeight(const QTextBlock &block) const
{
    const QPixmap pixmap = thumbnail(block);
    if (pixmap.isNull()) {
        return 0;
    }

    return pixmap.height() + inlineImageTopGap;
}

QPixmap InlineImageCache::thumbnail(const QTextBlock &block) const
{
    const QString target = imageTarget(block.text());
    if (target.isEmpty() || m_columnWidth <= 0) {
        return {};
    }

    return scaledThumbnail(resolvedPath(target));
}

QString InlineImageCache::imageTarget(const QString &blockText) const
{
    const QRegularExpressionMatch match = imageLineExpression.match(blockText);
    if (!match.hasMatch()) {
        return {};
    }

    const QString bracketed = match.captured(1);
    if (!bracketed.isEmpty()) {
        return bracketed;
    }

    return match.captured(2);
}

QString InlineImageCache::resolvedPath(const QString &target) const
{
    QString path = target;
    if (path.startsWith(QStringLiteral("file:"), Qt::CaseInsensitive)) {
        path = QUrl(path).toLocalFile();
    }

    QFileInfo info(path);
    if (info.isRelative() && !m_documentDirectory.isEmpty()) {
        info.setFile(QDir(m_documentDirectory).filePath(path));
    }

    return info.absoluteFilePath();
}

QPixmap InlineImageCache::scaledThumbnail(const QString &path) const
{
    const QFileInfo info(path);
    if (!info.exists() || !info.isFile()) {
        return {};
    }

    const QString key = path + QLatin1Char('|') + QString::number(info.size()) + QLatin1Char('|') + QString::number(m_columnWidth);
    const auto cached = m_thumbnails.constFind(key);
    if (cached != m_thumbnails.cend()) {
        return cached->pixmap;
    }

    QImageReader reader(path);
    reader.setAutoTransform(true);
    const QSize sourceSize = reader.size();
    if (sourceSize.isValid() && sourceSize.width() > 0 && sourceSize.height() > 0) {
        reader.setScaledSize(sourceSize.scaled(m_columnWidth, maxThumbnailHeight, Qt::KeepAspectRatio));
    }

    const QImage image = reader.read();
    if (image.isNull()) {
        return {};
    }

    ScaledImage stored;
    stored.pixmap = QPixmap::fromImage(image);
    if (stored.pixmap.width() > m_columnWidth || stored.pixmap.height() > maxThumbnailHeight) {
        stored.pixmap = stored.pixmap.scaled(m_columnWidth, maxThumbnailHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }

    m_thumbnails.insert(key, stored);
    return stored.pixmap;
}

} // namespace ghostwriter
