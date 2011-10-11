/****************************************************************************
 **
 ** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
 ** All rights reserved.
 ** Contact: Nokia Corporation (qt-info@nokia.com)
 **
 ** This file is part of the tools applications of the Qt Toolkit.
 **
 ** $QT_BEGIN_LICENSE:LGPL$
 ** GNU Lesser General Public License Usage
 ** This file may be used under the terms of the GNU Lesser General Public
 ** License version 2.1 as published by the Free Software Foundation and
 ** appearing in the file LICENSE.LGPL included in the packaging of this
 ** file. Please review the following information to ensure the GNU Lesser
 ** General Public License version 2.1 requirements will be met:
 ** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
 **
 ** In addition, as a special exception, Nokia gives you certain additional
 ** rights. These rights are described in the Nokia Qt LGPL Exception
 ** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
 **
 ** GNU General Public License Usage
 ** Alternatively, this file may be used under the terms of the GNU General
 ** Public License version 3.0 as published by the Free Software Foundation
 ** and appearing in the file LICENSE.GPL included in the packaging of this
 ** file. Please review the following information to ensure the GNU General
 ** Public License version 3.0 requirements will be met:
 ** http://www.gnu.org/copyleft/gpl.html.
 **
 ** Other Usage
 ** Alternatively, this file may be used in accordance with the terms and
 ** conditions contained in a signed written agreement between you and Nokia.
 **
 **
 **
 **
 **
 ** $QT_END_LICENSE$
 **
 ****************************************************************************/

#include <QtGui>
#include <QtDeclarative/QtDeclarative>
#include <QtUiTools/QtUiTools>

#include "accessibilityinspector.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    if (app.arguments().count() < 2) {
        qDebug() << "Usage: accessebilityInspector [ ui-file | qml-file ] [Option]";
        qDebug() << "Option:";
#ifdef QT_ACCESSIBILITY_INSPECTOR_SCENE_GRAPH
        qDebug() << "-qtquick1: Use QDeclarativeView instead of QSGView for rendering QML files";
#endif
        return 0;
    }

    QString fileName = app.arguments().at(1);
    QString mode;
    if (app.arguments().count() > 2) {
        mode = app.arguments().at(2);
    }

    QWidget *window;

    if (fileName.endsWith(".ui")) {
        QUiLoader loader;
        QFile file(fileName);
        file.open(QFile::ReadOnly);
        window = loader.load(&file, 0);
    } else if (fileName.endsWith(".qml")){
        QUrl fileUrl;
        if (fileName.startsWith(":")) { // detect resources.
            QString name = fileName;
            name.remove(0, 2); // reomve ":/"
            fileUrl.setUrl(QLatin1String("qrc:/") + name);
        } else {
            fileUrl = QUrl::fromLocalFile(fileName);
        }

#ifdef QT_ACCESSIBILITY_INSPECTOR_SCENE_GRAPH
        if (mode == QLatin1String("-qtquick1"))
#endif
        {
            QDeclarativeView * declarativeView = new QDeclarativeView();
            declarativeView->setSource(fileUrl);
            window = declarativeView;
        }
#ifdef QT_ACCESSIBILITY_INSPECTOR_SCENE_GRAPH
        else {
            QSGView * sceneGraphView = new QSGView();
            sceneGraphView->setSource(fileUrl);
            window = sceneGraphView;
        }
#endif
    } else {
        qDebug() << "Error: don't know what to do with" << fileName;
    }

    AccessibilityInspector *accessibilityInspector = new AccessibilityInspector();

    accessibilityInspector->inspectWindow(window);

    window->move(50, 50);
    window->show();

    int ret = app.exec();

    accessibilityInspector->saveWindowGeometry();
    delete accessibilityInspector;

    return ret;


}

