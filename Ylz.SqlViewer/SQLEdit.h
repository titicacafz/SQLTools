#pragma once

#include <QPlainTextEdit>

class SQLEdit : public QPlainTextEdit
{
    Q_OBJECT

public:
    SQLEdit(QWidget *parent);
    ~SQLEdit();

protected:
    virtual void mousePressEvent(QMouseEvent *event);
};
