#include "SQLEdit.h"

SQLEdit::SQLEdit(QWidget *parent)
    : QPlainTextEdit(parent)
{
}

SQLEdit::~SQLEdit()
{
}

void SQLEdit::mousePressEvent(QMouseEvent * event)
{
    //ctrl+���������
    if (event->modifiers() == Qt::ControlModifier)
    {
        if (event->button() == Qt::LeftButton)
        {
            ;
        }
    }
    QPlainTextEdit::mousePressEvent(event);
}
