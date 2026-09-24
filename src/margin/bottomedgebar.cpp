/*
 * SPDX-FileCopyrightText: 2026 the ghostwriter authors
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "bottomedgebar.h"

#include <QHBoxLayout>
#include <QToolButton>

namespace ghostwriter
{
namespace
{
constexpr int barHeight = 44;
constexpr int sidePadding = 20;
constexpr int buttonSize = 34;
constexpr int buttonSpacing = 4;
constexpr int glyphSize = 14;

constexpr char16_t eyeGlyph = 0xE890;
constexpr char16_t editGlyph = 0xE70F;
constexpr char16_t sunGlyph = 0xE706;
constexpr char16_t moonGlyph = 0xE708;
constexpr char16_t helpGlyph = 0xE897;

QToolButton *makeBarButton(QWidget *parent)
{
    auto *button = new QToolButton(parent);
    button->setFont(marginIconFont(glyphSize));
    button->setFixedSize(buttonSize, buttonSize);
    button->setFocusPolicy(Qt::NoFocus);
    button->setAutoRaise(true);
    button->setCursor(Qt::PointingHandCursor);
    return button;
}
}

BottomEdgeBar::BottomEdgeBar(QWidget *parent)
    : FadingBar(parent)
{
    setFixedHeight(barHeight);

    m_focusModeButton = makeBarButton(this);
    m_focusModeButton->setCheckable(true);
    m_focusModeButton->setIconSize(QSize(glyphSize + 2, glyphSize + 2));
    m_focusModeButton->setToolTip(tr("Focus mode (Shift+F11)"));
    m_focusModeButton->setAccessibleName(tr("Focus mode"));
    m_renderedViewButton = makeBarButton(this);
    m_darkModeButton = makeBarButton(this);
    m_shortcutsButton = makeBarButton(this);
    m_shortcutsButton->setText(QChar(helpGlyph));
    m_shortcutsButton->setToolTip(tr("Keyboard shortcuts"));
    m_shortcutsButton->setAccessibleName(tr("Keyboard shortcuts"));

    auto *layout = new QHBoxLayout(this);
    layout->setContentsMargins(sidePadding, 0, sidePadding, 0);
    layout->setSpacing(buttonSpacing);
    layout->addStretch(1);
    layout->addWidget(m_focusModeButton);
    layout->addWidget(m_renderedViewButton);
    layout->addWidget(m_darkModeButton);
    layout->addWidget(m_shortcutsButton);

    connect(m_focusModeButton, &QToolButton::clicked, this, &BottomEdgeBar::focusModeToggled);
    connect(m_renderedViewButton, &QToolButton::clicked, this, &BottomEdgeBar::renderedViewToggled);
    connect(m_darkModeButton, &QToolButton::clicked, this, &BottomEdgeBar::darkModeToggled);
    connect(m_shortcutsButton, &QToolButton::clicked, this, &BottomEdgeBar::shortcutsToggled);

    setRenderedView(false);
    setDarkMode(false);
}

void BottomEdgeBar::applyTheme(const MarginTheme &theme)
{
    const QString style = QStringLiteral(
                              "QWidget { background: transparent; }"
                              "QToolButton { background: transparent; border: 0; border-radius: 7px; color: %1; }"
                              "QToolButton:hover, QToolButton:checked { background: %2; color: %3; }")
                              .arg(theme.muted.name(), theme.hover.name(), theme.text.name());

    setStyleSheet(style);
}

void BottomEdgeBar::setRenderedView(bool rendered)
{
    m_renderedViewButton->setText(QChar(rendered ? editGlyph : eyeGlyph));
    m_renderedViewButton->setToolTip(rendered ? tr("Edit Markdown (Ctrl+P)") : tr("Show rendered Markdown (Ctrl+P)"));
    m_renderedViewButton->setAccessibleName(rendered ? tr("Edit Markdown") : tr("Show rendered Markdown"));
}

void BottomEdgeBar::setDarkMode(bool dark)
{
    m_darkModeButton->setText(QChar(dark ? sunGlyph : moonGlyph));
    m_darkModeButton->setToolTip(dark ? tr("Light mode (Ctrl+Shift+L)") : tr("Dark mode (Ctrl+Shift+L)"));
    m_darkModeButton->setAccessibleName(dark ? tr("Light mode") : tr("Dark mode"));
}

void BottomEdgeBar::setFocusModeIcon(const QIcon &icon)
{
    m_focusModeButton->setIcon(icon);
}

void BottomEdgeBar::setFocusMode(bool enabled)
{
    m_focusModeButton->setChecked(enabled);
}

QToolButton *BottomEdgeBar::shortcutsButton() const
{
    return m_shortcutsButton;
}

} // namespace ghostwriter
