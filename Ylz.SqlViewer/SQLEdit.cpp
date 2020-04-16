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
    QPlainTextEdit::mousePressEvent(event);
}
