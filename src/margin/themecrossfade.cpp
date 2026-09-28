/*
 * SPDX-FileCopyrightText: 2026 the ghostwriter authors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "themecrossfade.h"

#include <QEasingCurve>
#include <QPainter>
#include <QVariantAnimation>
#include <QWidget>

namespace ghostwriter
{
namespace
{
constexpr int crossfadeMilliseconds = 420;
constexpr auto overlayName = "themeCrossfade";

class ThemeFadeOverlay : public QWidget
{
public:
    ThemeFadeOverlay(const QPixmap &snapshot, QWidget *parent)
        : QWidget(parent)
        , m_snapshot(snapshot)
        , m_opacity(1)
    {
        setObjectName(QLatin1String(overlayName));
        setAttribute(Qt::WA_TransparentForMouseEvents);
        setAttribute(Qt::WA_NoSystemBackground);
        setAttribute(Qt::WA_TranslucentBackground);
    }

    void setFadeOpacity(qreal opacity)
    {
        m_opacity = opacity;
        update();
    }

protected:
    void paintEvent(QPaintEvent *) override
    {
        QPainter painter(this);
        painter.setOpacity(m_opacity);
        painter.drawPixmap(rect(), m_snapshot);
    }

private:
    QPixmap m_snapshot;
    qreal m_opacity;
};

QPixmap snapshotOf(QWidget *window)
{
    const qreal ratio = window->devicePixelRatioF();
    QPixmap snapshot(window->size() * ratio);
    snapshot.setDevicePixelRatio(ratio);
    snapshot.fill(Qt::transparent);

    QPainter painter(&snapshot);
    window->render(&painter);
    return snapshot;
}
}

void ThemeCrossfade::run(QWidget *window, const std::function<void()> &applyNewTheme)
{
    if (!window || !window->isVisible()) {
        applyNewTheme();
        return;
    }

    if (auto *existing = window->findChild<QWidget *>(QLatin1String(overlayName))) {
        existing->hide();
        delete existing;
    }

    const QPixmap snapshot = snapshotOf(window);
    applyNewTheme();

    if (snapshot.isNull()) {
        return;
    }

    auto *overlay = new ThemeFadeOverlay(snapshot, window);
    overlay->setGeometry(window->rect());
    overlay->show();
    overlay->raise();

    auto *fade = new QVariantAnimation(overlay);
    fade->setDuration(crossfadeMilliseconds);
    fade->setStartValue(1.0);
    fade->setEndValue(0.0);
    fade->setEasingCurve(QEasingCurve::OutCubic);
    QObject::connect(fade, &QVariantAnimation::valueChanged, overlay, [overlay](const QVariant &value) {
        overlay->setFadeOpacity(value.toReal());
    });
    QObject::connect(fade, &QVariantAnimation::finished, overlay, &QObject::deleteLater);
    fade->start(QAbstractAnimation::DeleteWhenStopped);
}

} // namespace ghostwriter
