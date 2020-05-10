#pragma once

#include <QTableView>

class CopyableTableView : public QTableView
{
    Q_OBJECT

public:
    CopyableTableView(QWidget *parent);
    ~CopyableTableView();

private:
    //��ctrl+c�ı����ݿ�����ճ������
    void on_copy();

protected:
    virtual void keyPressEvent(QKeyEvent *ev);
};
