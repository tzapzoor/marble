//
// This file is part of the Marble Virtual Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2010      Dennis Nienhüser <nienhueser@kde.org>
//

#ifndef MARBLE_DECLARATIVE_PLUGIN_H
#define MARBLE_DECLARATIVE_PLUGIN_H

#include "qglobal.h"

#include <QQmlExtensionPlugin>

/**
  * Registers MarbleWidget, MarbleRunnerManager and MarbleThemeManager
  * as QQml extensions for use in QML.
  */
class MarbleDeclarativePlugin : public QQmlExtensionPlugin
{
    Q_PLUGIN_METADATA( IID "org.kde.edu.marble.MarbleDeclarativePlugin" )
    Q_OBJECT
public:
    /** Overriding QQmlExtensionPlugin to register types */
    virtual void registerTypes( const char *uri );

    void initializeEngine( QQmlEngine *engine, const char *);
};

#endif
