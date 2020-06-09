#include "SearchEdit.h"
#include <QHBoxLayout>
#include <QPushButton>

SearchEdit::SearchEdit(QWidget *parent)
    : QLineEdit(parent)
{
    QHBoxLayout *mainLayout = new QHBoxLayout;
    QPushButton *searchBtn = new QPushButton;
    searchBtn->setFixedSize(16, 16);
    searchBtn->setCursor(Qt::PointingHandCursor);
    searchBtn->setToolTip(tr("Search"));
    searchBtn->setStyleSheet("QPushButton{border-image:url(:/YlzSqlViewer/Resources/search.ico);"
        "background:transparent;cursor:pointer;}");
    setPlaceholderText(tr("Search"));
    mainLayout->addWidget(searchBtn);
    mainLayout->addStretch();
    mainLayout->setContentsMargins(8, 0, 0, 0);
    setTextMargins(16 + 8 + 2, 0, 0, 0);
    setContentsMargins(0, 0, 0, 0);
    setLayout(mainLayout);
    setStyleSheet("height:40px;border:1px solid #eaeaea;border-radius:16px;");
}

SearchEdit::~SearchEdit()
{
}