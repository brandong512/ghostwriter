/*
 * SPDX-FileCopyrightText: 2026 the ghostwriter authors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef SHORTCUTS_PANEL_H
#define SHORTCUTS_PANEL_H

#include <QFrame>
#include <QList>

#include "margintheme.h"

class QAction;
class QGridLayout;

namespace ghostwriter
{

/**
 * Small floating panel that lists keyboard shortcuts.
 */
class ShortcutsPanel : public QFrame
{
    Q_OBJECT

public:
    struct Entry {
        QString label;
        QAction *action;
    };

    explicit ShortcutsPanel(QWidget *parent = nullptr);

    void setEntries(const QList<Entry> &entries);
    void applyTheme(const MarginTheme &theme);

private:
    QGridLayout *m_grid;
};

} // namespace ghostwriter

#endif
