#pragma once

#include "Shared.h"
#include "ui_SettingsDialog.h"

#include "Global.h"

#include <QtGui/QDialog>
#include <QtGui/QWidget>

class WIDGETS_EXPORT SettingsDialog : public QDialog, Ui::SettingsDialog
{
    Q_OBJECT

    public:
        explicit SettingsDialog(QWidget* parent = 0);

        Q_SIGNAL void gpiBindingChanged(int, Playout::PlayoutType::Type);

    private:
        QString stylesheet;

        void loadGpi();
        void loadDevice();
        void loadTriCasterProduct();
        void loadTriCasterDevice();
        void loadAtemDevice();
        void loadOscOutput();
        void checkEmptyDeviceList();
        void checkEmptyTriCasterDeviceList();
        void checkEmptyAtemDeviceList();
        void checkEmptyOscOutputList();
        void updateGpi(int gpi, const QComboBox* voltage, const QComboBox* action);
        void updateGpo(int gpo, const QComboBox* voltage, const QSpinBox* pulseLength);
        void updateGpiDevice();
        void blockAllSignals(bool block);
        void loadRazunaInfo();  // razuna integration

        Q_SLOT void showRazunaDialog();
        Q_SLOT void removeDevice();
        Q_SLOT void removeTriCasterDevice();
        Q_SLOT void removeAtemDevice();
        Q_SLOT void showAddDeviceDialog();
        Q_SLOT void showAddTriCasterDeviceDialog();
        Q_SLOT void showAddAtemDeviceDialog();
        Q_SLOT void startFullscreenChanged(int);
        Q_SLOT void fontSizeChanged(int);
        Q_SLOT void autoSynchronizeChanged(int);
        Q_SLOT void synchronizeIntervalChanged(int);
        Q_SLOT void showThumbnailTooltipChanged(int);
        Q_SLOT void enableOscInputChanged(int);
        Q_SLOT void disableInAndOutPointsChanged(int);
        Q_SLOT void reverseOscTimeChanged(int);
        Q_SLOT void deviceItemDoubleClicked(QTreeWidgetItem*, int);
        Q_SLOT void tricasterDeviceItemDoubleClicked(QTreeWidgetItem*, int);
        Q_SLOT void atemDeviceItemDoubleClicked(QTreeWidgetItem*, int);
        Q_SLOT void gpi1Changed();
        Q_SLOT void gpi2Changed();
        Q_SLOT void gpi3Changed();
        Q_SLOT void gpi4Changed();
        Q_SLOT void gpi5Changed();
        Q_SLOT void gpi6Changed();
        Q_SLOT void gpi7Changed();
        Q_SLOT void gpi8Changed();
        Q_SLOT void gpo1Changed();
        Q_SLOT void gpo2Changed();
        Q_SLOT void gpo3Changed();
        Q_SLOT void gpo4Changed();
        Q_SLOT void gpo5Changed();
        Q_SLOT void gpo6Changed();
        Q_SLOT void gpo7Changed();
        Q_SLOT void gpo8Changed();
        Q_SLOT void serialPortChanged();
        Q_SLOT void baudRateChanged(QString);
        Q_SLOT void oscPortChanged();
        Q_SLOT void repositoryPortChanged();
        Q_SLOT void showImportDeviceDialog();
        Q_SLOT void showImportTriCasterDeviceDialog();
        Q_SLOT void showImportAtemDeviceDialog();
        Q_SLOT void showAddOscOutputDialog();
        Q_SLOT void removeOscOutput();
        Q_SLOT void oscOutputItemDoubleClicked(QTreeWidgetItem*, int);
        Q_SLOT void delayTypeChanged(QString);
        Q_SLOT void tricasterProductChanged(QString);
        Q_SLOT void themeChanged(QString);
        Q_SLOT void rundownRepositoryChanged();
        Q_SLOT void previewOnAutoStepChanged(int);
        Q_SLOT void clearDelayedCommandsOnAutoStepChanged(int);
        Q_SLOT void deleteThumbnails();
        Q_SLOT void storeThumbnailsInDatabaseChanged(int);
        Q_SLOT void markUsedItemsChanged(int);
        Q_SLOT void showAudioLevelsChanged(int);
        Q_SLOT void showPreviewChanged(int);
        Q_SLOT void showLiveChanged(int);
        Q_SLOT void disableAudioInStreamChanged(int);
        Q_SLOT void networkCacheChanged(int);
        Q_SLOT void streamQualityChanged(int);
        Q_SLOT void showDurationChanged(int);
        Q_SLOT void useFreezeOnLoadChanged(int);
        Q_SLOT void DeleteRazunaApiKey();
};
