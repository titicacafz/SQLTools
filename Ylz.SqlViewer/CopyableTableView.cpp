#include "CopyableTableView.h"
#include <QKeyEvent>
#include <QKeySequence>
#include <QApplication>
#include <QClipboard>

CopyableTableView::CopyableTableView(QWidget *parent)
    : QTableView(parent)
{
}

CopyableTableView::~CopyableTableView()
{
}

void CopyableTableView::on_copy()
{
    QString copied_text;
    QModelIndexList current_selected_indexs = this->selectedIndexes();
    if (current_selected_indexs.size() < 1)
    {
        return;
    }
    int current_row = current_selected_indexs.at(0).row();
    for (int i = 0; i < current_selected_indexs.count(); i++) {
        if (current_row != current_selected_indexs.at(i).row()) {
            current_row = current_selected_indexs.at(i).row();
            copied_text.append("\n");
            copied_text.append(current_selected_indexs.at(i).data().toString());
            continue;
        }
        if (0 != i) {
            copied_text.append("\t");
        }
        copied_text.append(current_selected_indexs.at(i).data().toString());
    }
    copied_text.append("\n");
    QApplication::clipboard()->setText(copied_text);
}

void CopyableTableView::keyPressEvent(QKeyEvent * ev)
{
    if (ev->matches(QKeySequence::Copy))
    {
        on_copy();
    }
    QTableView::keyPressEvent(ev);
}