//
// This file is part of the Marble Virtual Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2013      Mayank Madan <maddiemadan@gmail.com>
//

#include "KmlViewFormatTagHandler.h"

#include "GeoDataLink.h"
#include "GeoParser.h"
#include "KmlElementDictionary.h"

namespace Marble
{
namespace kml
{

KML_DEFINE_TAG_HANDLER( viewFormat )

GeoNode* KmlviewFormatTagHandler::parse( GeoParser& parser ) const
{
    Q_ASSERT( parser.isStartElement() && parser.isValidElement( kmlTag_viewFormat ) );
    GeoStackItem parentItem = parser.parentElement();
    if (parentItem.represents(kmlTag_Link)) {
        QString content = parser.readElementText().trimmed();
        parentItem.nodeAs<GeoDataLink>()->setViewFormat(content);
    }

    return 0;
}

}
}
