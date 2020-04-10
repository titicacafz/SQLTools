#pragma once

#include <QPlainTextEdit>

class ErrorEdit : public QPlainTextEdit
{
    Q_OBJECT

public:
    ErrorEdit(QWidget *parent);
    ~ErrorEdit();
};
