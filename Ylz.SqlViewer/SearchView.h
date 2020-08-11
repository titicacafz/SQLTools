#pragma once

#include <QWidget>
#include "ui_SearchView.h"

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


    QNetworkAccessManager * m_manager;

    void on_log_search();

    void on_update(QNetworkReply *reply);
};
