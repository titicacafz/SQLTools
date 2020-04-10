#include "ErrorEdit.h"

ErrorEdit::ErrorEdit(QWidget *parent)
    : QPlainTextEdit(parent)
{
    setStyleSheet("color:#FF0000;");
}

ErrorEdit::~ErrorEdit()
{
}
