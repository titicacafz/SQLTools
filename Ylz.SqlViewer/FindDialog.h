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
    * ����ע�⣬����ĳ�ʼ��˳�����Ҫ��m_radioGrpBx������m_hbLayout֮ǰ��������������m_radioGrpBx����ʱ�Ὣm_hbLayout��������������m_hbLayout��ջ���󣬱�delete�ͻ�����⣬һ��Ҫע�⣡����
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
