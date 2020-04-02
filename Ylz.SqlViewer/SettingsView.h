#pragma once

#include <QDockWidget>
#include "ui_SettingsView.h"

class SettingsView : public QDockWidget
{
    Q_OBJECT

public:
    SettingsView(QWidget *parent = Q_NULLPTR);
    ~SettingsView();

private:
    Ui::SettingsView ui;


    void load();

    void onSave();
};
