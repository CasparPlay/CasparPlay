#include "MainWindow.h"
#include "AboutDialog.h"
#include "HelpDialog.h"
#include "SettingsDialog.h"
#include "TextScroller.h"
#include "CGPlayout.h"
#include "ReportGenerator.h"
#include "FetchMetadata.h"

#include "Version.h"
#include "Global.h"

#include "EventManager.h"
#include "DatabaseManager.h"
#include "Events/ExportPresetEvent.h"
#include "Events/ImportPresetEvent.h"
#include "Events/SaveAsPresetEvent.h"
#include "Events/ToggleFullscreenEvent.h"
#include "Events/Rundown/CloseRundownEvent.h"
#include "Events/Rundown/EmptyRundownEvent.h"
#include "Events/Rundown/NewRundownEvent.h"
#include "Events/Rundown/OpenRundownEvent.h"
#include "Events/Rundown/SaveRundownEvent.h"
#include "Events/Rundown/SendDbRundownEvent.h"

#include "Events/Rundown/CopyItemPropertiesEvent.h"
#include "Events/Rundown/PasteItemPropertiesEvent.h"
#include "Events/Library/RefreshLibraryEvent.h"
#include "Events/Rundown/AllowRemoteTriggeringMenuEvent.h"
#include "Events/Rundown/CompactViewEvent.h"
#include "Events/Rundown/ExecutePlayoutCommandEvent.h"
#include "Events/Rundown/AllowRemoteTriggeringEvent.h"

#include <QtCore/QTimer>
#include <QtCore/QDebug>
#include <QtCore/QFileInfo>

#include <QtGui/QApplication>
#include <QtGui/QDesktopServices>
#include <QtGui/QIcon>
#include <QtGui/QMessageBox>
#include <QtGui/QMouseEvent>
#include <QtGui/QToolButton>
#include <QtGui/QFileDialog>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    setupUi(this);
    setupMenu();
    setWindowIcon(QIcon(":/Graphics/Images/CasparCG.png"));

    this->applicationTitle = this->windowTitle();

    this->widgetAction->setVisible(false);

    this->splitterHorizontal->setSizes(QList<int>() << 1 << 0);
    this->splitterVertical->setSizes(QList<int>() << 289 << 860 << 289);

    bool showPreviewPanel = (DatabaseManager::getInstance().getConfigurationByName("ShowPreviewPanel").getValue() == "true") ? true : false;
    this->widgetPreview->setVisible(showPreviewPanel);

    bool showLivePanel = (DatabaseManager::getInstance().getConfigurationByName("ShowLivePanel").getValue() == "true") ? true : false;
    this->widgetLive->setVisible(showLivePanel);

    bool showAudioLevelsPanel = (DatabaseManager::getInstance().getConfigurationByName("ShowAudioLevelsPanel").getValue() == "true") ? true : false;
    this->widgetAudioLevels->setVisible(showAudioLevelsPanel);

    bool showDurationPanel = (DatabaseManager::getInstance().getConfigurationByName("ShowDurationPanel").getValue() == "true") ? true : false;
    this->widgetDuration->setVisible(showDurationPanel);

    QObject::connect(&EventManager::getInstance(), SIGNAL(statusbar(const StatusbarEvent&)), this, SLOT(statusbar(const StatusbarEvent&)));
    QObject::connect(&EventManager::getInstance(), SIGNAL(emptyRundown(const EmptyRundownEvent&)), this, SLOT(emptyRundown(const EmptyRundownEvent&)));
    QObject::connect(&EventManager::getInstance(), SIGNAL(activeRundownChanged(const ActiveRundownChangedEvent&)), this, SLOT(activeRundownChanged(const ActiveRundownChangedEvent&)));
    QObject::connect(&EventManager::getInstance(), SIGNAL(newRundownMenu(const NewRundownMenuEvent&)), this, SLOT(newRundownMenu(const NewRundownMenuEvent&)));
    QObject::connect(&EventManager::getInstance(), SIGNAL(openRundownMenu(const OpenRundownMenuEvent&)), this, SLOT(openRundownMenu(const OpenRundownMenuEvent&)));
    QObject::connect(&EventManager::getInstance(), SIGNAL(openRundownFromUrlMenu(const OpenRundownFromUrlMenuEvent&)), this, SLOT(openRundownFromUrlMenu(const OpenRundownFromUrlMenuEvent&)));
    QObject::connect(&EventManager::getInstance(), SIGNAL(allowRemoteTriggering(const AllowRemoteTriggeringEvent&)), this, SLOT(allowRemoteTriggering(const AllowRemoteTriggeringEvent&)));
    QObject::connect(&EventManager::getInstance(), SIGNAL(repositoryRundown(const RepositoryRundownEvent&)), this, SLOT(repositoryRundown(const RepositoryRundownEvent&)));
    QObject::connect(&EventManager::getInstance(), SIGNAL(exportPresetMenu(const ExportPresetMenuEvent&)), this, SLOT(exportPresetMenu(const ExportPresetMenuEvent&)));
    QObject::connect(&EventManager::getInstance(), SIGNAL(saveAsPresetMenu(const SaveAsPresetMenuEvent&)), this, SLOT(saveAsPresetMenu(const SaveAsPresetMenuEvent&)));
    QObject::connect(&EventManager::getInstance(), SIGNAL(reloadRundownMenu(const ReloadRundownMenuEvent&)), this, SLOT(reloadRundownMenu(const ReloadRundownMenuEvent&)));
}

void MainWindow::setupMenu()
{
    this->fileMenu = new QMenu(this);
    this->newRundownAction = this->fileMenu->addAction("New Rundown", this, SLOT(newRundown()), QKeySequence::fromString("Ctrl+N"));
    this->openRundownAction = this->fileMenu->addAction("Open Rundown...", this, SLOT(openRundown()), QKeySequence::fromString("Ctrl+O"));
    this->openRundownFromUrlAction = this->fileMenu->addAction("Open Rundown from repository...", this, SLOT(openRundownFromUrl()), QKeySequence::fromString("Ctrl+Shift+O"));
    this->fileMenu->addSeparator();
    this->fileMenu->addAction("Import Preset...", this, SLOT(importPreset()));
    this->exportPresetAction = this->fileMenu->addAction("Export Preset...", this, SLOT(exportPreset()));
    this->saveAsPresetAction = this->fileMenu->addAction("Save as Preset...", this, SLOT(saveAsPreset()));
    this->fileMenu->addSeparator();
    this->saveAction = this->fileMenu->addAction("Save", this, SLOT(saveRundown()), QKeySequence::fromString("Ctrl+S"));
    this->saveAsAction = this->fileMenu->addAction("Save As...", this, SLOT(saveAsRundown()), QKeySequence::fromString("Ctrl+Shift+S"));
    this->fileMenu->addSeparator();
    this->fileMenu->addAction("Prepare Rundown", this, SLOT(PrepareRundown()));
    this->fileMenu->addAction("Generate Report", this, SLOT(GenerateReport()));
    this->fileMenu->addSeparator();
    this->fileMenu->addAction("Quit", this, SLOT(close()));
    this->saveAsPresetAction->setEnabled(false);

    this->editMenu = new QMenu(this);
    this->editMenu->addAction("Settings...", this, SLOT(showSettingsDialog()));

    this->viewMenu = new QMenu(this);
    //this->viewMenu->addAction("Log...", this, SLOT(showLog()));
    //this->viewMenu->addSeparator();
    this->viewMenu->addAction("Toggle Fullscreen", this, SLOT(toggleFullscreen()), QKeySequence::fromString("Ctrl+F"));

    this->libraryMenu = new QMenu(this);
    this->libraryMenu->addAction("Refresh Library", this, SLOT(refreshLibrary()), QKeySequence::fromString("Ctrl+R"));

    this->markMenu = new QMenu(this);
    this->markMenu->setTitle("Mark Item");
    this->markMenu->addAction(/*QIcon(":/Graphics/Images/RenameRundown.png"),*/ "As Used", this, SLOT(markItemAsUsed()));
    this->markMenu->addAction(/*QIcon(":/Graphics/Images/RenameRundown.png"),*/ "As Unused", this, SLOT(markItemAsUnused()));
    this->markMenu->addAction(/*QIcon(":/Graphics/Images/RenameRundown.png"),*/ "All as Used", this, SLOT(markAllItemsAsUsed()));
    this->markMenu->addAction(/*QIcon(":/Graphics/Images/RenameRundown.png"),*/ "All as Unused", this, SLOT(markAllItemsAsUnused()));

    this->rundownMenu = new QMenu(this);
    this->rundownMenu->addMenu(this->markMenu);
    this->rundownMenu->addSeparator();
    this->rundownMenu->addAction("Copy Item Properties", this, SLOT(copyItemProperties()), QKeySequence::fromString("Shift+C"));
    this->rundownMenu->addAction("Paste Item Properties", this, SLOT(pasteItemProperties()), QKeySequence::fromString("Shift+V"));
    this->rundownMenu->addSeparator();
    this->rundownMenu->addAction("Toggle Compact View", this, SLOT(toggleCompactView()));
    this->allowRemoteTriggeringAction = this->rundownMenu->addAction(/*QIcon(":/Graphics/Images/RenameRundown.png"),*/ "Allow Remote Triggering");
    this->rundownMenu->addSeparator();
    this->insertRepositoryChangesAction = this->rundownMenu->addAction("Insert Repository Changes", this, SLOT(insertRepositoryChanges()), QKeySequence::fromString("Ins"));
    this->rundownMenu->addSeparator();
    this->reloadRundownAction = this->rundownMenu->addAction("Reload Rundown", this, SLOT(reloadRundown()), QKeySequence::fromString("Ctrl+L"));
    this->rundownMenu->addSeparator();
    this->rundownMenu->addAction("Close Rundown", this, SLOT(closeRundown()), QKeySequence::fromString("Ctrl+W"));

    // rakib inclusion
    this->rundownMenu->addSeparator();
    this->rundownMenu->addAction("Send To Database", this, SLOT(sendToDB()));

    this->allowRemoteTriggeringAction->setCheckable(true);
    QObject::connect(this->allowRemoteTriggeringAction, SIGNAL(toggled(bool)), this, SLOT(allowRemoteTriggering(bool)));
    this->insertRepositoryChangesAction->setEnabled(false);

    this->playoutMenu = new QMenu(this);
    this->playoutMenu->addAction("Stop", this, SLOT(executeStop()), QKeySequence::fromString("F1"));
    this->playoutMenu->addAction("Play", this, SLOT(executePlay()), QKeySequence::fromString("F2"));
    this->playoutMenu->addAction("Load", this, SLOT(executeLoad()), QKeySequence::fromString("F3"));
    this->playoutMenu->addAction("Pause / Resume", this, SLOT(executePause()), QKeySequence::fromString("F4"));
    this->playoutMenu->addSeparator();
    this->playoutMenu->addAction("Next", this, SLOT(executeNext()), QKeySequence::fromString("F5"));
    this->playoutMenu->addAction("Update", this, SLOT(executeUpdate()), QKeySequence::fromString("F6"));
    this->playoutMenu->addAction("Invoke", this, SLOT(executeInvoke()), QKeySequence::fromString("F7"));
    this->playoutMenu->addAction("Preview", this, SLOT(executePreview()), QKeySequence::fromString("F8"));
    this->playoutMenu->addSeparator();
    this->playoutMenu->addAction("Clear", this, SLOT(executeClear()), QKeySequence::fromString("F10"));
    this->playoutMenu->addAction("Clear Video Layer", this, SLOT(executeClearVideolayer()), QKeySequence::fromString("F11"));
    this->playoutMenu->addAction("Clear Channel", this, SLOT(executeClearChannel()), QKeySequence::fromString("F12"));
    this->playoutMenu->addSeparator();
    this->playoutMenu->addAction("Play Now", this, SLOT(executePlayNow()), QKeySequence::fromString("Shift+F2"));
    this->playoutMenu->addSeparator();
    this->playoutMenu->addAction("Text Scroller", this, SLOT(sendScrollingText()));
    this->playoutMenu->addSeparator();
    this->playoutMenu->addAction("CG Playout", this, SLOT(sendCGPlayoutCmd()));

    this->helpMenu = new QMenu(this);
    QAction* action = this->helpMenu->addAction("View Help", this, SLOT(showHelpDialog()), QKeySequence::fromString("Ctrl+H"));
    this->helpMenu->addSeparator();
    this->helpMenu->addAction("About CasparCG Client...", this, SLOT(showAboutDialog()));
    action->setEnabled(false);

    this->menuBar = new QMenuBar(this);
    this->menuBar->addMenu(this->fileMenu)->setText("File");
    this->menuBar->addMenu(this->editMenu)->setText("Edit");
    this->menuBar->addMenu(this->viewMenu)->setText("View");
    this->menuBar->addMenu(this->libraryMenu)->setText("Library");
    this->menuBar->addMenu(this->rundownMenu)->setText("Rundown");
    this->menuBar->addMenu(this->playoutMenu)->setText("Playout");
    this->menuBar->addMenu(this->helpMenu)->setText("Help");

    setMenuBar(this->menuBar);
}

void MainWindow::reloadRundownMenu(const ReloadRundownMenuEvent& event)
{
    this->reloadRundownAction->setEnabled(event.getEnabled());
}

void MainWindow::emptyRundown(const EmptyRundownEvent& event)
{
    this->saveAsPresetAction->setEnabled(false);
}

void MainWindow::statusbar(const StatusbarEvent& event)
{
    if (this->statusBar()->currentMessage() == event.getMessage())
        return;

    this->statusBar()->showMessage(event.getMessage(), event.getTimeout());
}

void MainWindow::activeRundownChanged(const ActiveRundownChangedEvent& event)
{
    QFileInfo info(event.getPath());
    if (info.baseName() == Rundown::DEFAULT_NAME)
        this->setWindowTitle(QString("%1").arg(this->applicationTitle));
    else
        this->setWindowTitle(QString("%1 - %2").arg(this->applicationTitle).arg(event.getPath()));
}

void MainWindow::newRundownMenu(const NewRundownMenuEvent& event)
{
    this->newRundownAction->setEnabled(event.getEnabled());
}

void MainWindow::openRundownMenu(const OpenRundownMenuEvent& event)
{
    this->openRundownAction->setEnabled(event.getEnabled());
}

void MainWindow::exportPresetMenu(const ExportPresetMenuEvent& event)
{
    this->exportPresetAction->setEnabled(event.getEnabled());
}

void MainWindow::saveAsPresetMenu(const SaveAsPresetMenuEvent& event)
{
    this->saveAsPresetAction->setEnabled(event.getEnabled());
}

void MainWindow::openRundownFromUrlMenu(const OpenRundownFromUrlMenuEvent& event)
{
    this->openRundownFromUrlAction->setEnabled(event.getEnabled());
}

void MainWindow::allowRemoteTriggering(const AllowRemoteTriggeringEvent& event)
{
    // We do not want to trigger check changed event.
    this->allowRemoteTriggeringAction->blockSignals(true);
    this->allowRemoteTriggeringAction->setChecked(event.getEnabled());
    this->allowRemoteTriggeringAction->blockSignals(false);
}

void MainWindow::repositoryRundown(const RepositoryRundownEvent& event)
{
    this->saveAction->setEnabled(!event.getRepositoryRundown());
    this->saveAsAction->setEnabled(!event.getRepositoryRundown());
    this->allowRemoteTriggeringAction->setEnabled(!event.getRepositoryRundown());
    this->insertRepositoryChangesAction->setEnabled(event.getRepositoryRundown());
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    if (this->widgetRundown->checkForSaveBeforeQuit())
    {
        EventManager::getInstance().fireCloseApplicationEvent(CloseApplicationEvent());

        event->accept();
    }
    else
        event->ignore();
}

void MainWindow::importPreset()
{
    EventManager::getInstance().fireImportPresetEvent(ImportPresetEvent());
}

void MainWindow::exportPreset()
{
    EventManager::getInstance().fireExportPresetEvent(ExportPresetEvent());
}

void MainWindow::saveAsPreset()
{
    EventManager::getInstance().fireSaveAsPresetEvent(SaveAsPresetEvent());
}

void MainWindow::newRundown()
{
    EventManager::getInstance().fireNewRundownEvent(NewRundownEvent());
}

void MainWindow::openRundown()
{
    EventManager::getInstance().fireOpenRundownEvent(OpenRundownEvent());
}

void MainWindow::openRundownFromUrl()
{
    EventManager::getInstance().fireOpenRundownFromUrlEvent(OpenRundownFromUrlEvent());
}

void MainWindow::saveRundown()
{
    EventManager::getInstance().fireSaveRundownEvent(SaveRundownEvent(false));
}

void MainWindow::saveAsRundown()
{
    EventManager::getInstance().fireSaveRundownEvent(SaveRundownEvent(true));
}

void MainWindow::copyItemProperties()
{
    EventManager::getInstance().fireCopyItemPropertiesEvent(CopyItemPropertiesEvent());
}

void MainWindow::pasteItemProperties()
{
    EventManager::getInstance().firePasteItemPropertiesEvent(PasteItemPropertiesEvent());
}

void MainWindow::executeStop()
{
    EventManager::getInstance().fireExecutePlayoutCommandEvent(ExecutePlayoutCommandEvent(QEvent::KeyPress, Qt::Key_F1, Qt::NoModifier));
}

void MainWindow::executePlay()
{
    EventManager::getInstance().fireExecutePlayoutCommandEvent(ExecutePlayoutCommandEvent(QEvent::KeyPress, Qt::Key_F2, Qt::NoModifier));
}

void MainWindow::executePlayNow()
{
    EventManager::getInstance().fireExecutePlayoutCommandEvent(ExecutePlayoutCommandEvent(QEvent::KeyPress, Qt::Key_F2, Qt::ShiftModifier));
}

void MainWindow::executeLoad()
{
    EventManager::getInstance().fireExecutePlayoutCommandEvent(ExecutePlayoutCommandEvent(QEvent::KeyPress, Qt::Key_F3, Qt::NoModifier));
}

void MainWindow::executePause()
{
    EventManager::getInstance().fireExecutePlayoutCommandEvent(ExecutePlayoutCommandEvent(QEvent::KeyPress, Qt::Key_F4, Qt::NoModifier));
}

void MainWindow::executeNext()
{
    EventManager::getInstance().fireExecutePlayoutCommandEvent(ExecutePlayoutCommandEvent(QEvent::KeyPress, Qt::Key_F5, Qt::NoModifier));
}

void MainWindow::executeUpdate()
{
    EventManager::getInstance().fireExecutePlayoutCommandEvent(ExecutePlayoutCommandEvent(QEvent::KeyPress, Qt::Key_F6, Qt::NoModifier));
}

void MainWindow::executeInvoke()
{
    EventManager::getInstance().fireExecutePlayoutCommandEvent(ExecutePlayoutCommandEvent(QEvent::KeyPress, Qt::Key_F7, Qt::NoModifier));
}

void MainWindow::executePreview()
{
    EventManager::getInstance().fireExecutePlayoutCommandEvent(ExecutePlayoutCommandEvent(QEvent::KeyPress, Qt::Key_F8, Qt::NoModifier));
}

void MainWindow::executeClear()
{
    EventManager::getInstance().fireExecutePlayoutCommandEvent(ExecutePlayoutCommandEvent(QEvent::KeyPress, Qt::Key_F10, Qt::NoModifier));
}

void MainWindow::executeClearVideolayer()
{
    EventManager::getInstance().fireExecutePlayoutCommandEvent(ExecutePlayoutCommandEvent(QEvent::KeyPress, Qt::Key_F11, Qt::NoModifier));
}

void MainWindow::executeClearChannel()
{
    EventManager::getInstance().fireExecutePlayoutCommandEvent(ExecutePlayoutCommandEvent(QEvent::KeyPress, Qt::Key_F12, Qt::NoModifier));
}

void MainWindow::markItemAsUsed()
{
    EventManager::getInstance().fireMarkItemAsUsedEvent(MarkItemAsUsedEvent());
}

void MainWindow::markItemAsUnused()
{
    EventManager::getInstance().fireMarkItemAsUnusedEvent(MarkItemAsUnusedEvent());
}

void MainWindow::markAllItemsAsUsed()
{
    EventManager::getInstance().fireMarkAllItemsAsUsedEvent(MarkAllItemsAsUsedEvent());
}

void MainWindow::markAllItemsAsUnused()
{
    EventManager::getInstance().fireMarkAllItemsAsUnusedEvent(MarkAllItemsAsUnusedEvent());
}

void MainWindow::toggleCompactView()
{
    EventManager::getInstance().fireToggleCompactViewEvent(CompactViewEvent());
}

void MainWindow::allowRemoteTriggering(bool enabled)
{
    EventManager::getInstance().fireAllowRemoteTriggeringEvent(AllowRemoteTriggeringEvent(enabled));
}

void MainWindow::closeRundown()
{
    EventManager::getInstance().fireCloseRundownEvent(CloseRundownEvent());
}

void MainWindow::insertRepositoryChanges()
{
    EventManager::getInstance().fireInsertRepositoryChangesEvent(InsertRepositoryChangesEvent());
}

void MainWindow::reloadRundown()
{
    EventManager::getInstance().fireReloadRundownEvent(ReloadRundownEvent());
}

void MainWindow::FetchRazunaMetadata()
{
    FetchMetadata *metadata = new FetchMetadata();
    metadata->exec();
}

// rakib inclusion
void MainWindow::PrepareRundown()
{
   this->FetchRazunaMetadata();
}

void MainWindow::sendScrollingText()
{
    TextScroller *scroller = new TextScroller(this);
    scroller->exec();
}

void MainWindow::sendCGPlayoutCmd()
{
    CGPlayout *cgplayout = new CGPlayout(this);
    cgplayout->exec();
}

void MainWindow::GenerateReport()
{
    qDebug() << QString("Lets Generate Report\n");
    ReportGenerator *rpg = new ReportGenerator(this);
    rpg->exec();
}

void MainWindow::sendToDB()
{
    this->widgetRundown->InsertIntoDB();
    EventManager::getInstance().firesendToDbRundownEvent(SendDbRundownEvent());
}

void MainWindow::showAboutDialog()
{
    AboutDialog* dialog = new AboutDialog(this);
    dialog->exec();
}

void MainWindow::showHelpDialog()
{
    HelpDialog* dialog = new HelpDialog(this);
    dialog->exec();
}

void MainWindow::showSettingsDialog()
{
    // Reset inspector panel.
    EventManager::getInstance().fireEmptyRundownEvent(EmptyRundownEvent());

    SettingsDialog* dialog = new SettingsDialog(this);
    QObject::connect(dialog, SIGNAL(gpiBindingChanged(int, Playout::PlayoutType::Type)), this->widgetRundown, SLOT(gpiBindingChanged(int, Playout::PlayoutType::Type)));

    dialog->exec();
}

void MainWindow::toggleFullscreen()
{
    isFullScreen() ? setWindowState(Qt::WindowNoState) : setWindowState(Qt::WindowFullScreen);

    EventManager::getInstance().fireToggleFullscreenEvent(ToggleFullscreenEvent());
}

void MainWindow::refreshLibrary()
{
    EventManager::getInstance().fireRefreshLibraryEvent(RefreshLibraryEvent());
}
