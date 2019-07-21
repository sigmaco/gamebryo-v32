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

#pragma once
#ifndef EE_ISTREAMABLE_H
#define EE_ISTREAMABLE_H

#include <efd/efdLibType.h>
#include <efd/IBase.h>
#include <efd/efdClassIDs.h>

namespace efd
{
// forward declarations
class DataStream;
class Archive;


/**
    The interface class for all polymorphic objects that support serialization.
*/
class EE_EFD_ENTRY IStreamable : public efd::IBase
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_INTERFACE1(IStreamable, efd::kCLASSID_IStreamable, efd::IBase)
    /// @endcond

public:
    /**
        Serialize a polymorphic type to or from an Archive. This method must be overridden, but if
        your streamable object has no data the override can be an empty function. A typical
        implementation of this method will make one call to efd::Serializer::SerializeObject for
        each member of the class. If you are derived from another streamable class you should be
        sure to call to parent implementation of this method as well; it is recommended that the
        parent class be serialized first before adding the data for the derived class. If your class
        contains complex data such as STL-style contianers or pointers to allocated data then you
        can simplify the implementation of Serialize by using the templated helper functions in
        <efd/SerializeRoutines.h>; these can serialize even the most complex data structures
        with a single method call and will reduce the chance of making common mistakes (which could
        introduce security vulnerabilities if marshalling data from untrusted sources).

        @param io_ar The Archive to serialize to or from.
    */
    virtual void Serialize(efd::Archive& io_ar) = 0;

private:
    /**
        Refactoring aid.

        The method 'void ToStream(efd::DataStream &strm) const' was removed from IStreamable. To
        assist in finding the code that must be refactored an incompatible method was added to this
        class so that any legacy implementations will become compile errors (rather than runtime
        errors). You should convert ToStream and FromStream into Serialize, see the Lightspeed
        3.2 conversion documentation for details.
    */
    virtual efd::UInt32 ToStream(efd::DataStream&) const {return 0;}

    /**
        Refactoring aid.

        The method 'bool FromStream(const efd::DataStream &strm)' was removed from IStreamable. To
        assist in finding the code that must be refactored an incompatible method was added to this
        class so that any legacy implementations will become compile errors (rather than runtime
        errors). You should convert ToStream and FromStream into Serialize, see the Lightspeed
        3.2 conversion documentation for details.
    */
    virtual efd::UInt32 FromStream(const efd::DataStream&) {return 0;}
};

///A smart pointer (reference counting, self deleting pointer) for the IStreamable class.
typedef efd::SmartPointer<IStreamable> IStreamablePtr;

} // end namespace efd

#endif // EE_ISTREAMABLE_H
