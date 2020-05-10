#pragma once

#include <QTableView>

class CopyableTableView : public QTableView
{
    Q_OBJECT

public:
    CopyableTableView(QWidget *parent);
    ~CopyableTableView();

private:
    //把ctrl+c的表数据拷贝到粘贴板中
    void on_copy();

protected:
    virtual void keyPressEvent(QKeyEvent *ev);
};
