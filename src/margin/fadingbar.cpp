/*
 * SPDX-FileCopyrightText: 2026 the ghostwriter authors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "fadingbar.h"

#include <QFontDatabase>

namespace ghostwriter
{
namespace
{
constexpr int fadeInMs = 350;
constexpr int fadeOutMs = 250;
}

QFont marginIconFont(int pixelSize)
{
    QFont font;

    if (QFontDatabase::hasFamily(QStringLiteral("Segoe Fluent Icons"))) {
        font.setFamily(QStringLiteral("Segoe Fluent Icons"));
    } else {
        font.setFamily(QStringLiteral("Segoe MDL2 Assets"));
    }

    font.setPixelSize(pixelSize);
    return font;
}

FadingBar::FadingBar(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StyledBackground, true);
    setFocusPolicy(Qt::NoFocus);

    m_opacity = new QGraphicsOpacityEffect(this);
    m_opacity->setOpacity(0);
    setGraphicsEffect(m_opacity);

    m_fade = new QPropertyAnimation(m_opacity, "opacity", this);
}

void FadingBar::fadeIn()
{
    if (m_shown) {
        return;
    }

    m_shown = true;
    animateTo(1.0, fadeInMs, QEasingCurve::OutCubic);
}

void FadingBar::fadeOut()
{
    if (!m_shown) {
        return;
    }

    m_shown = false;
    animateTo(0.0, fadeOutMs, QEasingCurve::InCubic);
}

bool FadingBar::isShown() const
{
    return m_shown;
}

void FadingBar::animateTo(qreal opacity, int durationMs, QEasingCurve::Type easing)
{
    m_fade->stop();
    m_fade->setDuration(durationMs);
    m_fade->setEasingCurve(easing);
    m_fade->setStartValue(m_opacity->opacity());
    m_fade->setEndValue(opacity);
    m_fade->start();
}

} // namespace ghostwriter
