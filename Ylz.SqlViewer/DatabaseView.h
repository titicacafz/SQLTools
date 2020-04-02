#pragma once

#include <QDockWidget>
#include "ui_DatabaseView.h"

class DatabaseView : public QDockWidget
{
    Q_OBJECT

public:
    DatabaseView(QWidget *parent = Q_NULLPTR);
    ~DatabaseView();

private:
    Ui::DatabaseView ui;
};
