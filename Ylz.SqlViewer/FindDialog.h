#pragma once

#include <QDialog>
#include <QGroupBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QRadioButton>
#include <QPlainTextEdit>
#include "ui_FindDialog.h"

class FindDialog : public QDialog
{
    Q_OBJECT
protected:
    /*
    * 必须注意，这里的初始化顺序很重要，m_radioGrpBx必须在m_hbLayout之前声明，如果在其后m_radioGrpBx析构时会将m_hbLayout进行析构，但是m_hbLayout是栈对象，被delete就会出问题，一定要注意！！！
    */
    QGroupBox m_radioGrpBx;

    QGridLayout m_layout;
    QHBoxLayout m_hbLayout;

    QLabel m_findLbl;
    QLineEdit m_findEdit;
    QPushButton m_findBtn;
    QPushButton m_closeBtn;
    QCheckBox m_matchChkBx;
    QRadioButton m_forwardBtn;
    QRadioButton m_backwardBtn;

    QPlainTextEdit *m_text;
    
public:
    explicit FindDialog(QWidget *parent = Q_NULLPTR, QPlainTextEdit *pText = Q_NULLPTR);
    ~FindDialog();

    bool event(QEvent* evt); 

    void onShow();

private:
    Ui::FindDialog ui;

    void initControl();
    void connectSlot();
    void setPlainTextEdit(QPlainTextEdit* text);

    void on_find();
    void on_close();
};
