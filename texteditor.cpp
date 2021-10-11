#include "texteditor.h"
#include <QAbstractItemView>
#include <QCompleter>
#include <QKeyEvent>
#include <QMessageBox>
#include <QScrollBar>
#include <QTextStream>
#include <QUrl>
#include <QtGui>

void TextEditor::fileOpen(QString fileName)
{
    QUrl url(fileName);
    QFile file(url.toLocalFile());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox msgBox;
        msgBox.setText("Error open file.");
        msgBox.exec();
        return;
    }

    QTextStream in(&file);
    QString line;
    while (!in.atEnd()) {
        line += in.readLine();
        line += "\n";
    }

    setText(line);
}

void TextEditor::fileSave(QString fileName)
{
    QUrl url(fileName);
    QFile file(url.toLocalFile());
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox msgBox;
        msgBox.setText("Error open file.");
        msgBox.exec();
        return;
    }

    if (file.write(toPlainText().toStdString().c_str()) == -1) {
        QMessageBox msgBox;
        msgBox.setText("Error write in file.");
        msgBox.exec();
        return;
    }
}

TextEditor::TextEditor(QWidget *parent) : QTextEdit(parent)
{
    comp = new QCompleter(this);
    comp->setModel(modelForCompleter());
    comp->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    comp->setCaseSensitivity(Qt::CaseInsensitive);
    comp->setWrapAround(false);

    comp->setWidget(this);
    comp->setCompletionMode(QCompleter::PopupCompletion);
    comp->setCaseSensitivity(Qt::CaseInsensitive);
    QObject::connect(comp, SIGNAL(activated(QString)), this, SLOT(insertCompletion(QString)));
}

TextEditor::~TextEditor()
{
}

QCompleter *TextEditor::completer() const
{
    return comp;
}

void TextEditor::insertCompletion(const QString &completion)
{
    if (comp->widget() != this)
        return;

    QTextCursor tc = textCursor();
    int extra = completion.length() - comp->completionPrefix().length();
    tc.movePosition(QTextCursor::Left);
    tc.movePosition(QTextCursor::EndOfWord);
    tc.insertText(completion.right(extra));
    setTextCursor(tc);
}

void TextEditor::focusInEvent(QFocusEvent *e)
{
    comp->setWidget(this);
    QTextEdit::focusInEvent(e);
}

void TextEditor::keyPressEvent(QKeyEvent *e)
{
    if (comp->popup()->isVisible()) {
        // Следующие коды клавиш перенаправляются дополнителем виджету
        switch (e->key()) {
        case Qt::Key_Enter:
        case Qt::Key_Return:
        case Qt::Key_Escape:
        case Qt::Key_Tab:
        case Qt::Key_Backtab: e->ignore(); return; // позволим дополнителю поведение по умолчанию
        default: break;
        }
    }

    QTextEdit::keyPressEvent(e);

    QTextCursor tc = textCursor();
    tc.select(QTextCursor::WordUnderCursor);
    QString completionPrefix = tc.selectedText();

    if (completionPrefix.length() < 3) {
        comp->popup()->hide();
        return;
    }

    if (completionPrefix != comp->completionPrefix()) {
        comp->setCompletionPrefix(completionPrefix);
        comp->popup()->setCurrentIndex(comp->completionModel()->index(0, 0));
    }

    QRect cr = cursorRect();
    cr.setWidth(comp->popup()->sizeHintForColumn(0)
                + comp->popup()->verticalScrollBar()->sizeHint().width());
    comp->complete(cr); // выталкиваем его вверх!
}

QAbstractItemModel *TextEditor::modelForCompleter()
{
    QStringList words;

    words << "booking"
          << "booking123"
          << "fullpath"
          << "fullpath456"
          << "widget"
          << "string";
    return new QStringListModel(words, comp);
}
