#pragma once

#include <QPlainTextEdit>

class SqlEdit : public QPlainTextEdit
{
    Q_OBJECT

public:
    SqlEdit(QWidget *parent);
    ~SqlEdit();

protected:
    virtual void mousePressEvent(QMouseEvent *event);
};
