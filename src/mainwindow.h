/*
 * SPDX-FileCopyrightText: 2014-2026 Megan Conkle <megan.conkle@kdemail.net>
 * SPDX-FileCopyrightText: 2026 Nate Peterson
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QAction>
#include <QLabel>
#include <QMainWindow>
#include <QMap>
#include <QPushButton>
#include <QSettings>
#include <QSplitter>
#include <QStackedWidget>
#include <QStringLiteral>
#include <QToolButton>

#include <KActionCollection>
#include <KHelpMenu>
#include <KStandardAction>

#include "preview/htmlpreview.h"
#include "settings/appsettings.h"
#include "spelling/spellcheckdecorator.h"
#include "statistics/documentstatistics.h"
#include "statistics/documentstatisticswidget.h"
#include "statistics/sessionstatistics.h"
#include "statistics/sessionstatisticswidget.h"
#include "statistics/statisticsindicator.h"
#include "theme/svgicontheme.h"
#include "theme/theme.h"
#include "theme/themerepository.h"

#include "appactions.h"
#include "bookmark.h"
#include "documentmanager.h"
#include "findreplace.h"
#include "folderviewwidget.h"
#include "margin/bottomedgebar.h"
#include "margin/margintheme.h"
#include "margin/readview.h"
#include "margin/shortcutspanel.h"
#include "margin/topedgebar.h"
#include "outlinewidget.h"
#include "sidebar.h"
#include "timelabel.h"

namespace QWK
{
class WidgetWindowAgent;
}

namespace ghostwriter
{
/**
 * Main window for the application.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(const QString &filePath = QString(), QWidget *parent = nullptr);
    virtual ~MainWindow();

protected:
    QSize sizeHint() const override;
    void resizeEvent(QResizeEvent *event) override;
    void showEvent(QShowEvent *event) override;
    void changeEvent(QEvent *event) override;
    void keyPressEvent(QKeyEvent *e) override;
    bool eventFilter(QObject *obj, QEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

private slots:
    void quitApplication();
    void changeTheme();
    void openPreferencesDialog();
    void toggleHtmlPreview(bool checked);
    void toggleHemingwayMode(bool checked);
    void toggleFocusMode(bool checked);
    void toggleFullScreen(bool checked);
    void toggleHideMenuBarInFullScreen(bool checked);
    void toggleFileHistoryEnabled(bool checked);
    void toggleFolderViewShowAllFilesEnabled(bool checked);
    void toggleDisplayTimeInFullScreen(bool checked);
    void changeEditorWidth(EditorWidth editorWidth);
    void changeInterfaceStyle(InterfaceStyle style);
    void showQuickReferenceGuide();
    void showWikiPage();
    void changeFocusMode(FocusMode focusMode);
    void applyTheme();
    void refreshRecentFiles();
    void clearRecentFileHistory();
    void changeDocumentDisplayName(const QString &displayName);
    void onOperationStarted(const QString &description);
    void onOperationFinished();
    void changeFont();
    void onFontSizeChanged(int size);
    void onSetLocale();
    void copyHtml();
    void showPreviewOptions();
    void onAboutToHideMenuBarMenu();
    void onAboutToShowMenuBarMenu();
    void onSidebarVisibilityChanged(bool visible);
    void toggleSidebarVisible(bool visible);
    void runSpellCheck();

private:
    MarkdownEditor *editor;
    SpellCheckDecorator *spelling;
    FindReplace *findReplace;
    QSplitter *previewSplitter;
    QSplitter *splitter;
    DocumentManager *documentManager;
    ThemeRepository *themeRepo;
    Theme theme;
    QString language;
    Sidebar *sidebar;
    StatisticsIndicator *statisticsIndicator;
    QLabel *statusIndicator;
    TimeLabel *timeIndicator;
    HtmlPreview *htmlPreview;
    FolderViewWidget *folderViewWidget = nullptr;
    OutlineWidget *outlineWidget;
    DocumentStatistics *documentStats;
    DocumentStatisticsWidget *documentStatsWidget;
    SessionStatistics *sessionStats;
    SessionStatisticsWidget *sessionStatsWidget;
    QListWidget *cheatSheetWidget;
    bool menuBarMenuActivated;
    bool sidebarHiddenForResize;
    bool focusModeEnabled;
    SvgIconTheme *primaryIconTheme;
    SvgIconTheme *secondaryIconTheme;

    QList<QAction *> recentFilesActions;

    QList<QWidget *> statusBarWidgets;

    AppSettings *appSettings;

    AppActions *m_actions;
    KActionCollection *m_actionCollection;

    KHelpMenu *m_helpMenu;

    TopEdgeBar *m_topEdgeBar = nullptr;
    BottomEdgeBar *m_bottomEdgeBar = nullptr;
    ReadView *m_readView = nullptr;
    ShortcutsPanel *m_shortcutsPanel = nullptr;
    QAction *m_toggleFontAction = nullptr;
    QStackedWidget *m_pages = nullptr;
    QWK::WidgetWindowAgent *m_windowAgent = nullptr;
    MarginColorMode m_colorMode = MarginColorMode::System;
    bool m_suppressEdgeBars = false;
    bool m_useSansFont = false;

    KActionCollection *actionCollection() const;

    QMenu *addMenuBarMenu(const QString &name);

    QAction *appAction(AppActions::ActionType actionType) const;

    void loadTheme();
    void setupFramelessWindow();
    void setupBottomEdgeBar();
    void applyWritingFont();
    void toggleWritingFont();
    void toggleReadView(bool rendered);
    void setupShortcutsPanel();
    void toggleShortcutsPanel();
    void placeShortcutsPanel();
    void placeEdgeBars();
    void updateEdgeBarsForPointer(const QPoint &windowPos);
    void hideEdgeBars();
    void updatePageTitle();
    QString pageTitle() const;
    MarginTheme currentMarginTheme() const;
    void setupActions();
    void setupRecentFileActions(const BookmarkList &recentFiles);
    void setupGui();
    void setupMenuBar();
    void setupStatusBar();
    void setupSidebar();

    void adjustEditor();
};
} // namespace ghostwriter

#endif
