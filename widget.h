#ifndef WIDGET_H
#define WIDGET_H

#include "texteditor.h"
#include <QApplication>
#include <QQuickWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <memory>

class Widget : public QWidget
{
    Q_OBJECT

public slots:
    void slotQuit();

public:
    explicit Widget(QWidget *parent, QApplication *a);

private:
    std::unique_ptr<QQuickWidget> m_quickWidget;
    std::unique_ptr<TextEditor> textEdit;
    std::unique_ptr<QVBoxLayout> vlayout;
    QApplication *app;
};

#endif // WIDGET_H
