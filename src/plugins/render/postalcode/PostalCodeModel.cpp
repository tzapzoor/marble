//
// This file is part of the Marble Virtual Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2011      Valery Kharitonov <kharvd@gmail.com>
//

// Self
#include "PostalCodeModel.h"

// Plugin
#include "PostalCodeItem.h"

// Marble
#include "MarbleGlobal.h"
#include "MarbleModel.h"
#include "GeoDataCoordinates.h"
#include "GeoDataLatLonAltBox.h"
#include "MarbleDebug.h"
#include "Planet.h"

// Qt
#include <QString>
#include <QUrl>
#include <QScriptEngine>
#include <QScriptValue>
#include <QScriptValueIterator>

#if QT_VERSION >= 0x050000
  #include <QUrlQuery>
#endif

using namespace Marble;

PostalCodeModel::PostalCodeModel( const MarbleModel *marbleModel, QObject *parent  )
    : AbstractDataPluginModel( "postalCode", marbleModel, parent )
{
}

PostalCodeModel::~PostalCodeModel() {
}

void PostalCodeModel::getAdditionalItems( const GeoDataLatLonAltBox& box,
                                          qint32 number )
{
    if( marbleModel()->planetId() != "earth" ) {
        return;
    }

    double const lat = box.center().latitude( GeoDataCoordinates::Degree );
    double const lon = box.center().longitude( GeoDataCoordinates::Degree );
    double const radius = qMin<double>( 30.0, box.height() * marbleModel()->planet()->radius() * METER2KM );

    QUrl geonamesUrl( "http://ws.geonames.org/findNearbyPostalCodesJSON" );
#if QT_VERSION < 0x050000
    geonamesUrl.addQueryItem( "lat", QString::number( lat ) );
    geonamesUrl.addQueryItem( "lng", QString::number( lon ) );
    geonamesUrl.addQueryItem( "radius", QString::number( radius ) );
    geonamesUrl.addQueryItem( "maxRows", QString::number( number ) );
    geonamesUrl.addQueryItem( "username", "marble" );
#else
    QUrlQuery urlQuery;
    urlQuery.addQueryItem( "lat", QString::number( lat ) );
    urlQuery.addQueryItem( "lng", QString::number( lon ) );
    urlQuery.addQueryItem( "radius", QString::number( radius ) );
    urlQuery.addQueryItem( "maxRows", QString::number( number ) );
    urlQuery.addQueryItem( "username", "marble" );
    geonamesUrl.setQuery( urlQuery );
#endif

    downloadDescriptionFile( QUrl( geonamesUrl ) );
}

void PostalCodeModel::parseFile( const QByteArray& file )
{
    QScriptValue data;
    QScriptEngine engine;

    // Qt requires parentheses around json code
    data = engine.evaluate( '(' + QString::fromUtf8( file ) + ')' );

    // Parse if any result exists
    if ( data.property( "postalCodes" ).isArray() ) {
        QScriptValueIterator iterator( data.property( "postalCodes" ) );

        // Add items to the list
        QList<AbstractDataPluginItem*> items;
        while ( iterator.hasNext() ) {
            iterator.next();

            QString const placeName = iterator.value().property( "placeName" ).toString();
            QString const adminName1 = iterator.value().property( "adminName1" ).toString();
            QString const adminName2 = iterator.value().property( "adminName2" ).toString();
            QString const adminName3 = iterator.value().property( "adminName3" ).toString();
            QString const postalCode = iterator.value().property( "postalCode" ).toString();
            QString const countryCode = iterator.value().property( "countryCode" ).toString();
            double const longitude = iterator.value().property( "lng" ).toNumber();
            double const latitude = iterator.value().property( "lat" ).toNumber();

            QString const id = "postalCode_" + countryCode + postalCode;

            if ( !id.isEmpty() ) {
                QString tooltip;

                if ( !placeName.isEmpty() ) {
                    tooltip += placeName + ' ';
                }

                addLine( &tooltip, postalCode );
                addLine( &tooltip, countryCode );
                addLine( &tooltip, adminName1 );
                addLine( &tooltip, adminName2 );
                addLine( &tooltip, adminName3 );
                tooltip = tooltip.trimmed();

                if( !itemExists( id ) ) {
                    // If it does not exist, create it
                    GeoDataCoordinates coordinates( longitude, latitude, 0.0, GeoDataCoordinates::Degree );

                    PostalCodeItem *item = new PostalCodeItem( this );
                    item->setId( id );
                    item->setCoordinate( coordinates );
                    item->setToolTip( tooltip );
                    item->setText( postalCode );

                    items << item;
                }
            }
        }
        addItemsToList( items );
    }
}

void PostalCodeModel::addLine(QString *string, const QString &line)
{
    Q_ASSERT( string );
    if ( !line.isEmpty() ) {
        *string += line + '\n';
    }
}

#include "moc_PostalCodeModel.cpp"
