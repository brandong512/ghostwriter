/*
 * SPDX-FileCopyrightText: 2026 the ghostwriter authors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "topedgebar.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QToolButton>

namespace ghostwriter
{
namespace
{
constexpr int barHeight = 40;
constexpr int captionWidth = 46;
constexpr int captionHeight = 40;
constexpr int leftSpacerWidth = 180;
constexpr int glyphSize = 10;
constexpr int titlePixelSize = 13;

QToolButton *makeCaptionButton(const QString &name, QChar glyph, QWidget *parent)
{
    auto *button = new QToolButton(parent);
    button->setObjectName(name);
    button->setText(glyph);
    button->setFont(marginIconFont(glyphSize));
    button->setFixedSize(captionWidth, captionHeight);
    button->setFocusPolicy(Qt::NoFocus);
    button->setAutoRaise(true);
    return button;
}
}

TopEdgeBar::TopEdgeBar(QWidget *parent)
    : FadingBar(parent)
{
    setFixedHeight(barHeight);

    m_title = new QLabel(tr("Untitled"), this);
    m_title->setAlignment(Qt::AlignCenter);
    m_title->setFocusPolicy(Qt::NoFocus);

    QFont titleFont(QStringLiteral("Segoe UI"));
    titleFont.setPixelSize(titlePixelSize);
    m_title->setFont(titleFont);

    m_minimize = makeCaptionButton(QStringLiteral("minimize"), QChar(0xE921), this);
    m_minimize->setAccessibleName(tr("Minimize"));
    m_maximize = makeCaptionButton(QStringLiteral("maximize"), QChar(0xE922), this);
    m_maximize->setAccessibleName(tr("Maximize"));
    m_close = makeCaptionButton(QStringLiteral("close"), QChar(0xE8BB), this);
    m_close->setAccessibleName(tr("Close"));

    auto *leftSpacer = new QWidget(this);
    leftSpacer->setFixedWidth(leftSpacerWidth);
    leftSpacer->setAttribute(Qt::WA_TransparentForMouseEvents);

    auto *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(leftSpacer);
    layout->addWidget(m_title, 1);
    layout->addWidget(m_minimize);
    layout->addWidget(m_maximize);
    layout->addWidget(m_close);
}

void TopEdgeBar::setDocumentTitle(const QString &title)
{
    m_title->setText(title);
}

void TopEdgeBar::applyTheme(const MarginTheme &theme)
{
    const QString style = QStringLiteral(
                              "QWidget { background: transparent; }"
                              "QLabel { color: %1; background: transparent; }"
                              "QToolButton { background: transparent; border: 0; color: %1; }"
                              "QToolButton:hover { background: %2; color: %3; }"
                              "QToolButton#close:hover { background: %4; color: #FFFFFF; }")
                              .arg(theme.muted.name(), theme.hover.name(), theme.text.name(), theme.danger.name());

    setStyleSheet(style);
}

void TopEdgeBar::setMaximized(bool maximized)
{
    m_maximize->setText(QChar(maximized ? 0xE923 : 0xE922));
    m_maximize->setAccessibleName(maximized ? tr("Restore") : tr("Maximize"));
}

QToolButton *TopEdgeBar::minimizeButton() const
{
    return m_minimize;
}

QToolButton *TopEdgeBar::maximizeButton() const
{
    return m_maximize;
}

QToolButton *TopEdgeBar::closeButton() const
{
    return m_close;
}

} // namespace ghostwriter
