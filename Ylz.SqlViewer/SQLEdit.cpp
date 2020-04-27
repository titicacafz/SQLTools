#include "SQLEdit.h"
#include <QApplication>

SQLEdit::SQLEdit(QWidget *parent)
    : QPlainTextEdit(parent)
{
}

SQLEdit::~SQLEdit()
{
}

void SQLEdit::mousePressEvent(QMouseEvent * e)
{        
    if (QApplication::keyboardModifiers() == Qt::ControlModifier &&
        e->button() == Qt::LeftButton)
    {
        //
        QString selectedText = this->textCursor().selectedText();
        if (!selectedText.trimmed().isEmpty())
        {
            //œ‘ æDDL
            ;
        }
    }
    QPlainTextEdit::mousePressEvent(e);
}
