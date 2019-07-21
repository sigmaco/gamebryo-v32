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
#ifndef EE_ATTACHNIFDATA_H
#define EE_ATTACHNIFDATA_H

#include "ecrLibType.h"

#include <efd/SmartPointer.h>
#include <efd/utf8string.h>
#include <efd/ParseHelper.h>
#include <efd/AssetID.h>
#include <efd/Serialize.h>

#include <ecr/ecrClassIDs.h>

#include <NiFixedString.h>

namespace efd
{
    class Archive;
}

namespace ecr
{

/**
    The AttachNifData class holds property data for the AttachedNifAsset property type.

    Each object holds the name of the attachment point in the scene graph (as an NiFixedString
    object) and the name of the Nif file asset to attach at that point. An empty Nif asset name
    indicates that no asset is attached. A transformation is also available to be applied to the
    attached object at the point of attachment.

    The Set methods are declared virtual so that inheriting classes can customize the actions
    taken when the property values are set (for example, by caching derived values).
*/
class EE_ECR_ENTRY AttachNifData : public efd::IBase
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(AttachNifData, efd::kCLASSID_AttachNifData, efd::IBase);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond
public:
    /**
        Default constructor

        The name of the attachment point and the attachment point are set to the empty string.
    */
    AttachNifData();

    /// Constructor
    ///
    /// The name of the attachment point and the Nif asset name must be provided.
    AttachNifData(const efd::utf8string& attachPoint, const efd::AssetID& nifAsset);

    /// Destructor
    virtual ~AttachNifData();

    /// Get the property type for this property. In this case kCLASSID_AttachNifData.
    virtual efd::ClassID GetPropertyType() const;

    /// Equality
    // @note these operators are required by the tProperty template.
    virtual bool operator==(const AttachNifData& other) const;
    virtual bool operator!=(const AttachNifData& other) const;

    /// Get the name of the attachment point.
    inline const efd::utf8string& GetAttachPoint() const;

    /// Set the name of the attachment point.
    inline virtual void SetAttachPoint(const efd::utf8string& attachPoint);

    /// Get the name of the attached Nif asset.
    inline efd::AssetID GetNifAsset() const;

    /// Set the name of the attached Nif asset.
    inline virtual void SetNifAsset(const efd::AssetID& nifAsset);

    /// Get the translation of the attached asset.
    inline efd::Point3 GetTranslation() const;

    /// Set the translation of the attached asset.
    inline virtual void SetTranslation(const efd::Point3& translation);

    /// Get the translation of the attached asset.
    inline efd::Point3 GetRotation() const;

    /// Set the translation of the attached asset.
    inline virtual void SetRotation(const efd::Point3& rotation);

    /// Get the translation of the attached asset.
    inline efd::Float32 GetScale() const;

    /// Set the translation of the attached asset.
    inline virtual void SetScale(const efd::Float32 scale);

    /// @name Methods Required for egf::TProperty
    //@{
    /// Convert a string to the property data
    virtual bool FromString(const efd::utf8string& stringValue);

    /// Convert the property data to a string
    virtual efd::utf8string ToString() const;
    //@}

#if !defined(SWIG)

    /// Serialization
    void Serialize(efd::Archive& ar);

protected:
    efd::utf8string m_attachPoint;
    efd::AssetID m_nifAsset;
    efd::Point3 m_translation;
    efd::Point3 m_rotation;
    efd::Float32 m_scale;

#endif // !defined(SWIG)

};

#if !defined(SWIG)

typedef efd::SmartPointer<AttachNifData> AttachNifDataPtr;

#endif // !defined(SWIG)

} // end namespace ecr


#if !defined(SWIG)

namespace efd
{
    template<>
    struct ParseHelper<ecr::AttachNifData>
    {
        static inline bool FromString(const utf8string& value, ecr::AttachNifData& result);
        static inline bool ToString(const ecr::AttachNifData& value, utf8string& result);
        static inline const char* GetNameOfType();
    };
} // end namespace efd

#endif

#include "AttachNifData.inl"

#endif // EE_ATTACHNIFDATA_H
