/*
 * SPDX-FileCopyrightText: 2026 the ghostwriter authors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "shortcutspanel.h"

#include <QAction>
#include <QGridLayout>
#include <QLabel>
#include <QScrollArea>
#include <QVBoxLayout>

namespace ghostwriter
{
namespace
{
constexpr int panelPadding = 18;
constexpr int rowSpacing = 8;
constexpr int columnSpacing = 24;
constexpr int labelPixelSize = 13;
constexpr int sectionPixelSize = 11;
}

ShortcutsPanel::ShortcutsPanel(QWidget *parent)
    : QFrame(parent)
{
    setObjectName(QStringLiteral("shortcutsPanel"));
    setAttribute(Qt::WA_StyledBackground, true);

    m_content = new QWidget;
    m_content->setObjectName(QStringLiteral("shortcutsContent"));

    m_grid = new QGridLayout(m_content);
    m_grid->setContentsMargins(panelPadding, panelPadding, panelPadding, panelPadding);
    m_grid->setHorizontalSpacing(columnSpacing);
    m_grid->setVerticalSpacing(rowSpacing);

    m_scroll = new QScrollArea(this);
    m_scroll->setObjectName(QStringLiteral("shortcutsScroll"));
    m_scroll->setWidget(m_content);
    m_scroll->setWidgetResizable(true);
    m_scroll->setFrameShape(QFrame::NoFrame);
    m_scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scroll->viewport()->setAutoFillBackground(false);

    auto *outer = new QVBoxLayout(this);
    outer->setContentsMargins(0, 0, 0, 0);
    outer->addWidget(m_scroll);

    hide();
}

void ShortcutsPanel::setEntries(const QList<Entry> &entries)
{
    while (QLayoutItem *item = m_grid->takeAt(0)) {
        delete item->widget();
        delete item;
    }

    QFont labelFont(QStringLiteral("Segoe UI"));
    labelFont.setPixelSize(labelPixelSize);

    QFont sectionFont(labelFont);
    sectionFont.setPixelSize(sectionPixelSize);
    sectionFont.setWeight(QFont::DemiBold);

    int row = 0;

    for (const Entry &entry : entries) {
        if (!entry.section.isEmpty()) {
            auto *section = new QLabel(entry.section, m_content);
            section->setObjectName(QStringLiteral("shortcutSection"));
            section->setFont(sectionFont);
            if (row > 0) {
                section->setContentsMargins(0, rowSpacing, 0, 0);
            }
            m_grid->addWidget(section, row, 0, 1, 2);
            row++;
        }

        if (!entry.action) {
            continue;
        }

        const QString keys = entry.action->shortcut().toString(QKeySequence::NativeText);
        if (keys.isEmpty()) {
            continue;
        }

        auto *label = new QLabel(entry.label, m_content);
        label->setObjectName(QStringLiteral("shortcutLabel"));
        label->setFont(labelFont);

        auto *shortcut = new QLabel(keys, m_content);
        shortcut->setObjectName(QStringLiteral("shortcutKeys"));
        shortcut->setFont(labelFont);
        shortcut->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        shortcut->setMinimumWidth(shortcut->sizeHint().width());

        m_grid->addWidget(label, row, 0);
        m_grid->addWidget(shortcut, row, 1);
        row++;
    }

    m_content->adjustSize();
    adjustSize();
}

void ShortcutsPanel::applyTheme(const MarginTheme &theme)
{
    setStyleSheet(QStringLiteral("QFrame#shortcutsPanel { background: %1; border: 1px solid %2; border-radius: 10px; }"
                                 "QWidget#shortcutsContent { background: transparent; }"
                                 "QLabel { background: transparent; border: 0; }"
                                 "QLabel#shortcutSection { color: %4; }"
                                 "QLabel#shortcutLabel { color: %3; }"
                                 "QLabel#shortcutKeys { color: %4; }"
                                 "QScrollBar:vertical { background: transparent; width: 8px; margin: 4px 2px 4px 0; }"
                                 "QScrollBar::handle:vertical { background: %2; border-radius: 3px; min-height: 24px; }"
                                 "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical { height: 0; }"
                                 "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical { background: transparent; }")
                      .arg(theme.panel.name(), theme.border.name(), theme.text.name(), theme.muted.name()));
}

QSize ShortcutsPanel::sizeHint() const
{
    return m_content->layout()->sizeHint();
}

} // namespace ghostwriter
