#include "FindDialog.h"
#include <QEvent>
#include <QMessageBox>

FindDialog::FindDialog(QWidget *parent, QPlainTextEdit *pText)
    : QDialog(parent), m_text(pText)
{
    ui.setupUi(this);
    initControl();
    connectSlot();
}

FindDialog::~FindDialog()
{
    m_text = nullptr;
}

bool FindDialog::event(QEvent* evt)
{
    if (evt->type() == QEvent::Close)
    {
        hide();

        return true;
    }

    return QDialog::event(evt);
}

void FindDialog::onShow()
{
    
    if (m_text != nullptr)
    {
        QString target = m_text->textCursor().selectedText();
        if (target != "")
        {
            m_findEdit.setText(target);
        }            
    }    
    

    this->show();
}

void FindDialog::initControl()
{
    m_findLbl.setText(tr("Find What:"));
    m_findBtn.setText(tr("Find Next"));
    m_closeBtn.setText(tr("Close"));
    m_matchChkBx.setText(tr("Match Case"));
    m_backwardBtn.setText(tr("Backward"));
    m_forwardBtn.setText(tr("Forward"));
    m_forwardBtn.setChecked(true);
    m_radioGrpBx.setTitle(tr("Direction"));

    m_hbLayout.addWidget(&m_forwardBtn);
    m_hbLayout.addWidget(&m_backwardBtn);

    m_radioGrpBx.setLayout(&m_hbLayout);

    m_layout.setSpacing(10);
    m_layout.addWidget(&m_findLbl, 0, 0);
    m_layout.addWidget(&m_findEdit, 0, 1);
    m_layout.addWidget(&m_findBtn, 0, 2);
    m_layout.addWidget(&m_matchChkBx, 1, 0);
    m_layout.addWidget(&m_radioGrpBx, 1, 1);
    m_layout.addWidget(&m_closeBtn, 1, 2);

    setLayout(&m_layout);
    setWindowTitle(tr("Find"));       
}

void FindDialog::connectSlot()
{
    //connect(ui.actionStart, &QAction::triggered, this, &TraceView::on_start);
    connect(&m_findBtn, &QPushButton::clicked, this, &FindDialog::on_find);
    connect(&m_closeBtn, &QPushButton::clicked, this, &FindDialog::on_close);
}

void FindDialog::setPlainTextEdit(QPlainTextEdit *text)
{
    m_text = text;
}


void FindDialog::on_find()
{
    QString target = m_findEdit.text();
    QString text = m_text->toPlainText();
    
    if ((m_text != nullptr) && (target != "") && text!="")
    {        
        QTextCursor c = m_text->textCursor();
        int index = -1;

        if (m_forwardBtn.isChecked())
        {
            index = text.indexOf(target, c.position(), m_matchChkBx.isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);

            if (index >= 0)
            {
                c.setPosition(index);
                c.setPosition(index + target.length(), QTextCursor::KeepAnchor);

                m_text->setTextCursor(c);
            }
        }

        if (m_backwardBtn.isChecked())
        {
            index = text.lastIndexOf(target, c.position() - text.length() - 1, m_matchChkBx.isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);

            if (index >= 0)
            {
                c.setPosition(index + target.length());
                c.setPosition(index, QTextCursor::KeepAnchor);

                m_text->setTextCursor(c);
            }
        }

        if (index < 0)
        {
            QMessageBox msg(this);

            msg.setWindowTitle(tr("Find"));
            msg.setText(tr("Can not find \"") + target + tr("\" any more..."));
            msg.setIcon(QMessageBox::Information);
            msg.setStandardButtons(QMessageBox::Ok);

            msg.exec();
        }
    }
    
}

void FindDialog::on_close()
{
    close();
}
