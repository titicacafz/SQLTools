#pragma once

#include <QWidget>
#include "ui_SearchView.h"
#include "FindDialog.h"

class QNetworkAccessManager;
class QNetworkReply;


class LogSearchView : public QWidget
{
    Q_OBJECT

public:
    LogSearchView(QWidget *parent = Q_NULLPTR);
    ~LogSearchView();

private:
    Ui::SearchView ui;

    //ËÑË÷¶Ô»°¿ò
    FindDialog *m_find_dialog;

    QNetworkAccessManager * m_manager;

    void on_log_search();

    void on_update(QNetworkReply *reply);

    void on_end_time_changed(const QTime &time);

    void on_find();

    void on_save();
};
