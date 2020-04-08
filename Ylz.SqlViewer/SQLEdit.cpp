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
    if (event->modifiers() == Qt::ControlModifier)
    {
        if (event->button() == Qt::LeftButton)
        {
            int i = this->blockCount();
            i++;
        }
    }
    QPlainTextEdit::mousePressEvent(event);
}
