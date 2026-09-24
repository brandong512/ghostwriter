/*
 * SPDX-FileCopyrightText: 2026 the ghostwriter authors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef FADING_BAR_H
#define FADING_BAR_H

#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QWidget>

namespace ghostwriter
{

/**
 * Returns the Windows icon font (Segoe Fluent Icons, or Segoe MDL2 Assets on
 * Windows 10) at the given pixel size.
 */
QFont marginIconFont(int pixelSize);

/**
 * Edge bar that is invisible at rest and fades in on request.
 */
class FadingBar : public QWidget
{
    Q_OBJECT

public:
    explicit FadingBar(QWidget *parent = nullptr);

    void fadeIn();
    void fadeOut();
    bool isShown() const;

private:
    QGraphicsOpacityEffect *m_opacity;
    QPropertyAnimation *m_fade;
    bool m_shown = false;

    void animateTo(qreal opacity, int durationMs, QEasingCurve::Type easing);
};

} // namespace ghostwriter

#endif
