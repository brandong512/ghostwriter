/*
 * SPDX-FileCopyrightText: 2026 the ghostwriter authors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef TOP_EDGE_BAR_H
#define TOP_EDGE_BAR_H

#include "fadingbar.h"
#include "margintheme.h"

class QLabel;
class QToolButton;

namespace ghostwriter
{

class TopEdgeBar : public FadingBar
{
    Q_OBJECT

public:
    explicit TopEdgeBar(QWidget *parent = nullptr);

    void setDocumentTitle(const QString &title);
    void applyTheme(const MarginTheme &theme);
    void setMaximized(bool maximized);

    QToolButton *minimizeButton() const;
    QToolButton *maximizeButton() const;
    QToolButton *closeButton() const;

private:
    QLabel *m_title;
    QToolButton *m_minimize;
    QToolButton *m_maximize;
    QToolButton *m_close;
};

} // namespace ghostwriter

#endif
