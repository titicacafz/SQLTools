#include "highlighter.h"

//! [0]
Highlighter::Highlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    keywordFormat.setForeground(Qt::darkBlue);
    keywordFormat.setFontWeight(QFont::Bold);
    const QString keywordPatterns[] = {
            QStringLiteral("\\babort\\b"),
            QStringLiteral("\\baccept\\b"),
            QStringLiteral("\\baccess\\b"),
            QStringLiteral("\\badd\\b"),
            QStringLiteral("\\ball\\b"),
            QStringLiteral("\\balter\\b"),
            QStringLiteral("\\band\\b"),
            QStringLiteral("\\bany\\b"),
            QStringLiteral("\\barray\\b"),
            QStringLiteral("\\barraylen\\b"),
            QStringLiteral("\\bas\\b"),
            QStringLiteral("\\basc\\b"),
            QStringLiteral("\\bassert\\b"),
            QStringLiteral("\\bassign\\b"),
            QStringLiteral("\\bat\\b"),
            QStringLiteral("\\baudit\\b"),
            QStringLiteral("\\bauthorization\\b"),
            QStringLiteral("\\bavg\\b"),
            QStringLiteral("\\bbase_table\\b"),
            QStringLiteral("\\bbegin\\b"),
            QStringLiteral("\\bbetween\\b"),
            QStringLiteral("\\bbinary_integer\\b"),
            QStringLiteral("\\bbody\\b"),
            QStringLiteral("\\bboolean\\b"),
            QStringLiteral("\\bby\\b"),
            QStringLiteral("\\bcase\\b"),
            QStringLiteral("\\bchar\\b"),
            QStringLiteral("\\bchar_base\\b"),
            QStringLiteral("\\bcheck\\b"),
            QStringLiteral("\\bclose\\b"),
            QStringLiteral("\\bcluster\\b"),
            QStringLiteral("\\bclusters\\b"),
            QStringLiteral("\\bcolauth\\b"),
            QStringLiteral("\\bcolumn\\b"),
            QStringLiteral("\\bcomment\\b"),
            QStringLiteral("\\bcommit\\b"),
            QStringLiteral("\\bcompress\\b"),
            QStringLiteral("\\bconnect\\b"),
            QStringLiteral("\\bconstant\\b"),
            QStringLiteral("\\bcrash\\b"),
            QStringLiteral("\\bcreate\\b"),
            QStringLiteral("\\bcurrent\\b"),
            QStringLiteral("\\bcurrval\\b"),
            QStringLiteral("\\bcursor\\b"),
            QStringLiteral("\\bcycle\\b"),
            QStringLiteral("\\bdatabase\\b"),
            QStringLiteral("\\bdata_base\\b"),
            QStringLiteral("\\bdate\\b"),
            QStringLiteral("\\bdba\\b"),
            QStringLiteral("\\bdebugoff\\b"),
            QStringLiteral("\\bdebugon\\b"),
            QStringLiteral("\\bdeclare\\b"),
            QStringLiteral("\\bdecimal\\b"),
            QStringLiteral("\\bdefault\\b"),
            QStringLiteral("\\bdefinition\\b"),
            QStringLiteral("\\bdelay\\b"),
            QStringLiteral("\\bdelete\\b"),
            QStringLiteral("\\bdesc\\b"),
            QStringLiteral("\\bdigits\\b"),
            QStringLiteral("\\bdispose\\b"),
            QStringLiteral("\\bdistinct\\b"),
            QStringLiteral("\\bdo\\b"),
            QStringLiteral("\\bdrop\\b"),
            QStringLiteral("\\belse\\b"),
            QStringLiteral("\\belsif\\b"),
            QStringLiteral("\\bend\\b"),
            QStringLiteral("\\bentry\\b"),
            QStringLiteral("\\bexception\\b"),
            QStringLiteral("\\bexception_init\\b"),
            QStringLiteral("\\bexclusive exists\\b"),
            QStringLiteral("\\bexit\\b"),
            QStringLiteral("\\bfalse\\b"),
            QStringLiteral("\\bfetch\\b"),
            QStringLiteral("\\bfile\\b"),
            QStringLiteral("\\bfloat\\b"),
            QStringLiteral("\\bfor\\b"),
            QStringLiteral("\\bform\\b"),
            QStringLiteral("\\bfrom\\b"),
            QStringLiteral("\\bfunction\\b"),
            QStringLiteral("\\bgeneric\\b"),
            QStringLiteral("\\bgoto\\b"),
            QStringLiteral("\\bgrant\\b"),
            QStringLiteral("\\bgroup\\b"),
            QStringLiteral("\\bhaving\\b"),
            QStringLiteral("\\bidentified\\b"),
            QStringLiteral("\\bif\\b"),
            QStringLiteral("\\bimmediate\\b"),
            QStringLiteral("\\bin\\b"),
            QStringLiteral("\\bincrement\\b"),
            QStringLiteral("\\bindex\\b"),
            QStringLiteral("\\bindexes\\b"),
            QStringLiteral("\\bindicator\\b"),
            QStringLiteral("\\binitial\\b"),
            QStringLiteral("\\binsert\\b"),
            QStringLiteral("\\binteger\\b"),
            QStringLiteral("\\binterface\\b"),
            QStringLiteral("\\bintersect\\b"),
            QStringLiteral("\\binto\\b"),
            QStringLiteral("\\bis\\b"),
            QStringLiteral("\\blevel\\b"),
            QStringLiteral("\\blike\\b"),
            QStringLiteral("\\blimited\\b"),
            QStringLiteral("\\block\\b"),
            QStringLiteral("\\blong\\b"),
            QStringLiteral("\\bloop\\b"),
            QStringLiteral("\\bmax\\b"),
            QStringLiteral("\\bmaxextents\\b"),
            QStringLiteral("\\bmaxvalue\\b"),
            QStringLiteral("\\bmin\\b"),
            QStringLiteral("\\bminextents\\b"),
            QStringLiteral("\\bminus\\b"),
            QStringLiteral("\\bminvalue\\b"),
            QStringLiteral("\\bmislabel\\b"),
            QStringLiteral("\\bmod\\b"),
            QStringLiteral("\\bmode\\b"),
            QStringLiteral("\\bnatural\\b"),
            QStringLiteral("\\bnaturaln\\b"),
            QStringLiteral("\\bnew\\b"),
            QStringLiteral("\\bnextval\\b"),
            QStringLiteral("\\bnoaudit\\b"),
            QStringLiteral("\\bnocompress\\b"),
            QStringLiteral("\\bnologging\\b"),
            QStringLiteral("\\bnot\\b"),
            QStringLiteral("\\bnowait\\b"),
            QStringLiteral("\\bnull\\b"),
            QStringLiteral("\\bnumber\\b"),
            QStringLiteral("\\bnumber_base\\b"),
            QStringLiteral("\\bof\\b"),
            QStringLiteral("\\boffline\\b"),
            QStringLiteral("\\bon\\b"),
            QStringLiteral("\\bonline\\b"),
            QStringLiteral("\\bopen\\b"),
            QStringLiteral("\\boption\\b"),
            QStringLiteral("\\bor\\b"),
            QStringLiteral("\\border\\b"),
            QStringLiteral("\\bothers\\b"),
            QStringLiteral("\\bout\\b"),
            QStringLiteral("\\bpackage\\b"),
            QStringLiteral("\\bpartition\\b"),
            QStringLiteral("\\bpctfree\\b"),
            QStringLiteral("\\bpctused\\b"),
            QStringLiteral("\\bpls_integer\\b"),
            QStringLiteral("\\bpositive\\b"),
            QStringLiteral("\\bpositiven\\b"),
            QStringLiteral("\\bpragma\\b"),
            QStringLiteral("\\bprior\\b"),
            QStringLiteral("\\bprivate\\b"),
            QStringLiteral("\\bprivileges\\b"),
            QStringLiteral("\\bprocedure\\b"),
            QStringLiteral("\\bpublic\\b"),
            QStringLiteral("\\braise\\b"),
            QStringLiteral("\\brange\\b"),
            QStringLiteral("\\braw\\b"),
            QStringLiteral("\\breal\\b"),
            QStringLiteral("\\brecord\\b"),
            QStringLiteral("\\bref\\b"),
            QStringLiteral("\\brelease\\b"),
            QStringLiteral("\\bremr\\b"),
            QStringLiteral("\\brename\\b"),
            QStringLiteral("\\bresource\\b"),
            QStringLiteral("\\breturn\\b"),
            QStringLiteral("\\breverse\\b"),
            QStringLiteral("\\brevoke\\b"),
            QStringLiteral("\\brollback\\b"),
            QStringLiteral("\\brow\\b"),
            QStringLiteral("\\browid\\b"),
            QStringLiteral("\\browlabel\\b"),
            QStringLiteral("\\brownum\\b"),
            QStringLiteral("\\brows\\b"),
            QStringLiteral("\\browtype\\b"),
            QStringLiteral("\\brun\\b"),
            QStringLiteral("\\bsavepoint\\b"),
            QStringLiteral("\\bschema\\b"),
            QStringLiteral("\\bselect\\b"),
            QStringLiteral("\\bseparate\\b"),
            QStringLiteral("\\bsequence\\b"),
            QStringLiteral("\\bsession\\b"),
            QStringLiteral("\\bset\\b"),
            QStringLiteral("\\bshare\\b"),
            QStringLiteral("\\bsmallint\\b"),
            QStringLiteral("\\bspace\\b"),
            QStringLiteral("\\bsql\\b"),
            QStringLiteral("\\bsqlcode\\b"),
            QStringLiteral("\\bsqlerrm\\b"),
            QStringLiteral("\\bstart\\b"),
            QStringLiteral("\\bstatement\\b"),
            QStringLiteral("\\bstddev\\b"),
            QStringLiteral("\\bsubtype\\b"),
            QStringLiteral("\\bsuccessful\\b"),
            QStringLiteral("\\bsum synonym\\b"),
            QStringLiteral("\\bsysdate\\b"),
            QStringLiteral("\\btabauth\\b"),
            QStringLiteral("\\btable\\b"),
            QStringLiteral("\\btables\\b"),
            QStringLiteral("\\btask\\b"),
            QStringLiteral("\\bterminate\\b"),
            QStringLiteral("\\bthen\\b"),
            QStringLiteral("\\bto\\b"),
            QStringLiteral("\\btrigger\\b"),
            QStringLiteral("\\btrue\\b"),
            QStringLiteral("\\btype\\b"),
            QStringLiteral("\\buid\\b"),
            QStringLiteral("\\bunion\\b"),
            QStringLiteral("\\bunique\\b"),
            QStringLiteral("\\bupdate\\b"),
            QStringLiteral("\\buse\\b"),
            QStringLiteral("\\buser\\b"),
            QStringLiteral("\\bvalidate\\b"),
            QStringLiteral("\\bvalues\\b"),
            QStringLiteral("\\bvarchar\\b"),
            QStringLiteral("\\bvarchar2\\b"),
            QStringLiteral("\\bvariance\\b"),
            QStringLiteral("\\bview\\b"),
            QStringLiteral("\\bviews\\b"),
            QStringLiteral("\\bwhen\\b"),
            QStringLiteral("\\bwhenever\\b"),
            QStringLiteral("\\bwhere\\b"),
            QStringLiteral("\\bwhile\\b"),
            QStringLiteral("\\bwith\\b"),
            QStringLiteral("\\bwork\\b"),
            QStringLiteral("\\bwrite\\b"),
            QStringLiteral("\\bbefore\\b"),
            QStringLiteral("\\beach\\b"),
            QStringLiteral("\\bfor\\b"),
            QStringLiteral("\\bkey\\b"),
            QStringLiteral("\\bprimary\\b"),
            QStringLiteral("\\bwhen\\b"),
            QStringLiteral("\\bwhere\\b"),
            QStringLiteral("\\bwhile\\b"),
            QStringLiteral("\\bxor\\b")            
    };
    for (const QString &pattern : keywordPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }
    
    singleLineCommentFormat.setForeground(Qt::green);
    rule.pattern = QRegularExpression(QStringLiteral("--[^\n]*"));
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    multiLineCommentFormat.setForeground(Qt::green);
    
    
    functionFormat.setForeground(Qt::blue);
    rule.pattern = QRegularExpression(QStringLiteral("\\b[A-Za-z0-9_]+(?=\\()"));
    rule.format = functionFormat;
    highlightingRules.append(rule);
    
    //commentStartExpression = QRegularExpression(QStringLiteral("/\\*"));
    //commentEndExpression = QRegularExpression(QStringLiteral("\\*/"));
    stringExpression = QRegularExpression(QStringLiteral("\\'"));
    
    stringFormat.setForeground(Qt::darkGreen);
    redtagFormat.setForeground(Qt::red);
}

void Highlighter::highlightBlock(const QString &text)
{
    for (const HighlightingRule &rule : qAsConst(highlightingRules)) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text.toLower());
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
    
    for (auto i=0; i <= text.size() ; i++)
    {
        auto character = text.data()[i];
        if (
            character == '<' ||
            character == '>' ||
            character == '.' ||
            character == '#' ||
            character == '.' ||
            character == '=' ||
            character == '(' ||
            character == ')' ||
            character == ',' ||
            character == '&' ||
            character == '*'
            )
        {
            setFormat(i, 1, redtagFormat);
        }
    }

    setCurrentBlockState(0);
    int startIndex = text.indexOf(stringExpression);

    while (startIndex >= 0)
    {
        int endIndex = text.indexOf(stringExpression, startIndex + 1);
        int stringLength = 0;
        if (endIndex == -1)
        {
            setCurrentBlockState(1);
            break;
        }
        else
        {
            stringLength = endIndex - startIndex + 1;
        }
        setFormat(startIndex, stringLength, stringFormat);
        startIndex = text.indexOf(stringExpression, startIndex + stringLength);
    }

    /*
    setCurrentBlockState(0);
    
    startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = text.indexOf(commentStartExpression);

    
    while (startIndex >= 0) {
        
        QRegularExpressionMatch match = commentEndExpression.match(text, startIndex);
        int endIndex = match.capturedStart();
        int commentLength = 0;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        }
        else {
            commentLength = endIndex - startIndex
                + match.capturedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = text.indexOf(commentStartExpression, startIndex + commentLength);
    }
    */
}
