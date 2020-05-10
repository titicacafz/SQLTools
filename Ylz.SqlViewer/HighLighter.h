#pragma once

//pl/sql�������ʵ��
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

    //ע�Ϳ�ʼ
    //QRegularExpression commentStartExpression;
    //ע�ͽ���
    //QRegularExpression commentEndExpression;

    //�ؼ��ֱ�����
    QTextCharFormat keywordFormat;

    //����ע��
    QTextCharFormat singleLineCommentFormat;
    //����ע��
    QTextCharFormat multiLineCommentFormat;    

    //����
    QTextCharFormat functionFormat;

    //����
    QTextCharFormat redtagFormat;

    //�ַ�����ʽ
    QTextCharFormat stringFormat;
    //�ַ�����ʶ
    QRegularExpression stringExpression;
};
