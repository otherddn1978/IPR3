#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QTextEdit>

class QAbstractItemModel;
class QCompleter;

class TextEditor : public QTextEdit
{
    Q_OBJECT

public:
    TextEditor(QWidget *parent = 0);
    ~TextEditor();

    QCompleter *completer() const;

    Q_INVOKABLE void fileOpen(QString fileName);
    Q_INVOKABLE void fileSave(QString fileName);

protected:
    void keyPressEvent(QKeyEvent *e);
    void focusInEvent(QFocusEvent *e);

private slots:
    void insertCompletion(const QString &completion);
    QAbstractItemModel *modelForCompleter();

private:
    QCompleter *comp;
};

#endif // TEXTEDITOR_H
