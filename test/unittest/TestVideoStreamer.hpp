#ifndef TEST_VIDEOSTREAMER_H
#define TEST_VIDEOSTREAMER_H

#pragma once

#include <QTest>

namespace test {

class TestVideoStreamer: public QObject
{
    Q_OBJECT
private slots:
    void testOpenCamera();
};

} // end namespace test

#endif
