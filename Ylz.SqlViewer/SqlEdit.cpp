#include "SqlEdit.h"
#include <QApplication>

SqlEdit::SqlEdit(QWidget *parent)
    : QPlainTextEdit(parent)
{
}

SqlEdit::~SqlEdit()
{
}

void SqlEdit::mousePressEvent(QMouseEvent * e)
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
