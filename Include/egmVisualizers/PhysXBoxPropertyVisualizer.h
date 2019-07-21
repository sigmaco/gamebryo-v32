// EMERGENT GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Emergent Game Technologies and may not
// be copied or disclosed except in accordance with the terms of that
// agreement.
//
//      Copyright (c) 1996-2009 Emergent Game Technologies.
//      All Rights Reserved.
//
// Emergent Game Technologies, Calabasas, CA 91302
// http://www.emergent.net

#ifndef EE_PHYSXBOXPROPERTYVISUALIZER_H
#define EE_PHYSXBOXPROPERTYVISUALIZER_H

#include <egmVisualizers/IPropertyVisualizer.h>
#include <egmVisualizers/CubePropertyVisualizer.h>
#include <NiMaterialProperty.h>

namespace egmVisualizers
{

/**
    A visualizer for a PhysX box.  This is only different from the Cube visualizers in that
    the origin of the visualizer is different.

    By default, the Position, Rotation, and Dimensions properties on the entity are used to
    create the visualizer mesh.  The properties used to drive the visualizer
    can be overridden by the extra data passed to the constructor.
*/
class EE_EGMVISUALIZERS_ENTRY PhysXBoxPropertyVisualizer : public CubePropertyVisualizer
{
public:
    /// @name Construction and Destruction
    //@{
    /**
        Constructor.  The extra data can be used to override which properties drive the visualizer.
        The string value of the extra data is used to find the property.  If that entry does not
        exist or it is specified as "Default", then the default property on the entity will be used.

        "Anchor" entry overrides default position property.
        "Orientation" entry overrides default rotation property.
        "Dimensions" entry overrides default dimensions property.
        "Color" entry specifies the color of the visualizer (no default).
        "Offset" entry specifies the position offset of the visualizer (no default).
    */
    PhysXBoxPropertyVisualizer(egf::ExtraDataPtr spExtraData);
    //@}

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual PropertyChangeAction UpdateFromEntity(egf::Entity* pEntity);
};

} // namespace

#endif
