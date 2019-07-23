/****************************************************************************
** Copyright (c) 2019, Fougue Ltd. <http://www.fougue.pro>
** All rights reserved.
** See license at https://github.com/fougue/mayo/blob/master/LICENSE.txt
****************************************************************************/

#pragma once

#include <QtCore/QObject>
#include <QtTest/QtTest>

namespace Mayo {

class Test : public QObject {
    Q_OBJECT

private slots:
    void BRepUtils_test();
    void CafUtils_test();
    void Quantity_test();
    void Result_test();
    void UnitSystem_test();

    void LibTree_test();
};

} // namespace Mayo
