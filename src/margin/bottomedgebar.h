/*
 * SPDX-FileCopyrightText: 2026 the ghostwriter authors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef BOTTOM_EDGE_BAR_H
#define BOTTOM_EDGE_BAR_H

#include <QIcon>

#include "fadingbar.h"
#include "margintheme.h"

class QToolButton;

namespace ghostwriter
{

/**
 * Bottom edge bar holding the rendered-view (eye) and dark mode toggles.
 */
class BottomEdgeBar : public FadingBar
{
    Q_OBJECT

public:
    explicit BottomEdgeBar(QWidget *parent = nullptr);

    void applyTheme(const MarginTheme &theme);
    void setRenderedView(bool rendered);
    void setDarkMode(bool dark);
    void setFocusModeIcon(const QIcon &icon);
    void setFocusMode(bool enabled);
    QToolButton *shortcutsButton() const;

signals:
    void focusModeToggled();
    void renderedViewToggled();
    void darkModeToggled();
    void shortcutsToggled();

private:
    QToolButton *m_focusModeButton;
    QToolButton *m_renderedViewButton;
    QToolButton *m_darkModeButton;
    QToolButton *m_shortcutsButton;
};

} // namespace ghostwriter

#endif
