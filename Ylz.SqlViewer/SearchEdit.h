#pragma once

#include <QLineEdit>

class SearchEdit : public QLineEdit
{
    Q_OBJECT

public:
    SearchEdit(QWidget *parent);
    ~SearchEdit();
};
