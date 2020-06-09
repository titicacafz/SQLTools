#pragma once

//pl/sql代码高亮实现
#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QRegularExpression>

QT_BEGIN_NAMESPACE
class QTextDocument;
QT_END_NAMESPACE

//! [0]
class Highlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    Highlighter(QTextDocument *parent = 0);

protected:
    void highlightBlock(const QString &text) override;

private:
    struct HighlightingRule
    {
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;

    //注释开始
    //QRegularExpression commentStartExpression;
    //注释结束
    //QRegularExpression commentEndExpression;

    //关键字保留字
    QTextCharFormat keywordFormat;

    //单行注释
    QTextCharFormat singleLineCommentFormat;
    //多行注释
    QTextCharFormat multiLineCommentFormat;

    //函数
    QTextCharFormat functionFormat;

    //符号
    QTextCharFormat redtagFormat;

    //字符串格式
    QTextCharFormat stringFormat;
    //字符串标识
    QRegularExpression stringExpression;
};
