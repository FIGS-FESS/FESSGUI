#ifndef SETPASSWORDDIALOGTEST_H
#define SETPASSWORDDIALOGTEST_H

#include <QObject>
#include <QtTest/QtTest>
#include "setpassworddialog.h"

class SetPasswordDialogTest : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase()
    { qDebug("called before everything else"); }
    void myFirstTest()
    { QVERIFY(new SetPasswordDialog() != NULL); }
    void mySecondTest()
    { QVERIFY(1 != 2); }
    void cleanupTestCase()
    { qDebug("called after myFirstTest and mySecondTest"); }
};

#endif // SETPASSWORDDIALOGTEST_H
