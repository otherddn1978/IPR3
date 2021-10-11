#include "widget.h"
#include <QQmlContext>
#include <qquickitem.h>

Widget::Widget(QWidget *parent, QApplication *a) : QWidget(parent, Qt::Window), app(a)
{
    textEdit = std::unique_ptr<TextEditor>(new TextEditor(this));
    m_quickWidget = std::unique_ptr<QQuickWidget>(new QQuickWidget(this));
    vlayout = std::unique_ptr<QVBoxLayout>(new QVBoxLayout);

    resize(640, 480);
    m_quickWidget->setSource(QUrl("qrc:/main.qml"));
    QQmlContext *context = m_quickWidget->rootContext();
    context->setContextProperty("MyWindow", textEdit.get());

    QQuickItem *qItem = m_quickWidget->rootObject();
    if (qItem)
        QObject::connect(qItem, SIGNAL(quitClicked()), this, SLOT(slotQuit()));

    vlayout->setSpacing(0);
    vlayout->addWidget(m_quickWidget.get());
    vlayout->addWidget(textEdit.get());
    setLayout(vlayout.get());
}

void Widget::slotQuit()
{
    app->quit();
}
