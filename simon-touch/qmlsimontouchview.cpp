#include "qmlsimontouchview.h"
#include <QDeclarativeContext>
#include <QGraphicsObject>
#include <QMetaObject>
#include <QDebug>
#include <QDeclarativeComponent>
#include "qmlapplicationviewer.h"
#include "simontouch.h"
#include "imagesmodel.h"
#include "musicmodel.h"
#include "videosmodel.h"
#include "contactsmodel.h"
#include "messagemodel.h"
#include "rssfeed.h"
#include "declarativeimageprovider.h"

QMLSimonTouchView::QMLSimonTouchView(SimonTouch *logic) :
    SimonTouchView(logic), viewer(QmlApplicationViewer::create())
{
    viewer->engine()->addImageProvider("images", new DeclarativeImageProvider);
    viewer->rootContext()->setContextProperty("imagesModel", logic->images());
    viewer->rootContext()->setContextProperty("musicModel", logic->music());
    viewer->rootContext()->setContextProperty("videosModel", logic->videos());
    viewer->rootContext()->setContextProperty("rssFeed", logic->rssFeed());
    viewer->rootContext()->setContextProperty("contactsModel", logic->contacts());
    viewer->rootContext()->setContextProperty("messagesModel", logic->messages());
    viewer->rootContext()->setContextProperty("simonTouch", this);

    viewer->setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer->setMainQmlFile(QLatin1String("qml/simontouch/main.qml"));
    viewer->showExpanded();
//    viewer->showFullScreen();

    connect(logic, SIGNAL(rssFeedReady()),
            viewer->rootObject()->findChild<QObject*>("MainInformationNewsFeed"), SLOT(displayFeed()));
    connect(logic, SIGNAL(rssFeedError()),
            viewer->rootObject()->findChild<QObject*>("MainInformationNewsFeed"),
            SLOT(feedFetchError()));
}
void QMLSimonTouchView::callSkype(const QString& user)
{
    qDebug() << "Calling skype: " << user;
}

void QMLSimonTouchView::callPhone(const QString& user)
{
    qDebug() << "Calling phone: " + user;
}

void QMLSimonTouchView::fetchMessages(const QString& user)
{
    qDebug() << "Fetching messages: " + user;
}

void QMLSimonTouchView::sendSMS(const QString& user, const QString& message)
{
    qDebug() << "Sending SMS: " <<  user << message;
}

void QMLSimonTouchView::sendMail(const QString& user, const QString& message)
{
    qDebug() << "Sending mail: " <<  user << message;
}

//I'm really sorry for doing this string based by I have absolutely no time at all and
//I couldn't get QML to find the enum after 30 minutes...
void QMLSimonTouchView::setState(const QString& state)
{
    if (state == "Main")
        emit enterState(SimonTouchState::Main);
    if (state == "Communication")
        emit enterState(SimonTouchState::Communication);
    if (state == "Information")
        emit enterState(SimonTouchState::Information);
    if (state == "Music")
        emit enterState(SimonTouchState::Music);
    if (state == "Images")
        emit enterState(SimonTouchState::Images);
    if (state == "Videos")
        emit enterState(SimonTouchState::Videos);
    if (state == "News")
        emit enterState(SimonTouchState::News);
    if (state == "Orders")
        emit enterState(SimonTouchState::Orders);
    if (state == "Requests")
        emit enterState(SimonTouchState::Requests);
}

QString QMLSimonTouchView::componentName(QDeclarativeItem* object)
{
    return object->metaObject()->className();
}

QMLSimonTouchView::~QMLSimonTouchView()
{
}
