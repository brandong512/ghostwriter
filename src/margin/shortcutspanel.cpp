/*
 * SPDX-FileCopyrightText: 2026 the ghostwriter authors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "shortcutspanel.h"

#include <QAction>
#include <QGridLayout>
#include <QLabel>

namespace ghostwriter
{
namespace
{
constexpr int panelPadding = 18;
constexpr int rowSpacing = 8;
constexpr int columnSpacing = 24;
constexpr int labelPixelSize = 13;
}

ShortcutsPanel::ShortcutsPanel(QWidget *parent)
    : QFrame(parent)
{
    setObjectName(QStringLiteral("shortcutsPanel"));
    setAttribute(Qt::WA_StyledBackground, true);

    m_grid = new QGridLayout(this);
    m_grid->setContentsMargins(panelPadding, panelPadding, panelPadding, panelPadding);
    m_grid->setHorizontalSpacing(columnSpacing);
    m_grid->setVerticalSpacing(rowSpacing);

    hide();
}

void ShortcutsPanel::setEntries(const QList<Entry> &entries)
{
    QFont labelFont(QStringLiteral("Segoe UI"));
    labelFont.setPixelSize(labelPixelSize);

    int row = 0;

    for (const Entry &entry : entries) {
        const QString keys = entry.action->shortcut().toString(QKeySequence::NativeText);

        if (keys.isEmpty()) {
            continue;
        }

        auto *label = new QLabel(entry.label, this);
        label->setObjectName(QStringLiteral("shortcutLabel"));
        label->setFont(labelFont);

        auto *shortcut = new QLabel(keys, this);
        shortcut->setObjectName(QStringLiteral("shortcutKeys"));
        shortcut->setFont(labelFont);
        shortcut->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

        m_grid->addWidget(label, row, 0);
        m_grid->addWidget(shortcut, row, 1);
        row++;
    }

    adjustSize();
}

void ShortcutsPanel::applyTheme(const MarginTheme &theme)
{
    setStyleSheet(QStringLiteral("QFrame#shortcutsPanel { background: %1; border: 1px solid %2; border-radius: 10px; }"
                                 "QLabel { background: transparent; border: 0; }"
                                 "QLabel#shortcutLabel { color: %3; }"
                                 "QLabel#shortcutKeys { color: %4; }")
                      .arg(theme.panel.name(), theme.border.name(), theme.text.name(), theme.muted.name()));
}

} // namespace ghostwriter
