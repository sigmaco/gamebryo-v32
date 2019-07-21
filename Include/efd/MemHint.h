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
#ifndef EE_MEMHINT_H
#define EE_MEMHINT_H

#include <efd/efdLibType.h>

namespace efd
{

/**
    Indicates the intended usage for the memory being allocated which allows
    the allocator to optionally pick the most efficient memory type or location,
    as well as providing additional information to the memory tracker when enabled.
*/
class EE_EFD_ENTRY MemHint
{
public:

#define EE_HINTFIELD(shift, value) ((value)<<(shift))
    enum Bits
    {
        PLATFORM_NONE = EE_HINTFIELD(0, 0x00),
        /*!< Bits 7..0 are per-platform memory hints; although 00000000 is
        reserved to mean no hint was given. */

    #if defined(_PS3)
        PS3_MAIN          = EE_HINTFIELD(0, 0x20),
        PS3_RSX_LOCAL     = EE_HINTFIELD(0, 0x21),
        PS3_TRY_MAIN      = EE_HINTFIELD(0, 0x22),
        PS3_TRY_RSX_LOCAL = EE_HINTFIELD(0, 0x23),
        /*!< Note: these settings are not valid for standard allocations, they
        are only for allocations occurring through the NiPS3GPUMemoryManager. */
    #endif

        LIFETIME_APPLICATION = EE_HINTFIELD(8, 0),
        LIFETIME_LONG        = EE_HINTFIELD(8, 1),
        LIFETIME_SHORT       = EE_HINTFIELD(8, 2),
        LIFETIME_FRAME       = EE_HINTFIELD(8, 3),
        /*!< Bits 9..8 provide lifetime information. */

        COMPILER_PROVIDES_SIZE_ON_DEALLOCATE = EE_HINTFIELD(10, 1),
        SIZE_PROVIDED_ON_DEALLOCATE = EE_HINTFIELD(10, 1),
        /*!< Bit 10
        If true, the compiler will pass in the allocation size on deallocation
        or reallocation calls, or the user will call an explicit known size free,
        so it does not have to be stored explicitly. */

        ACCESS_CPU      = EE_HINTFIELD(11, 0),
        ACCESS_VOLATILE = EE_HINTFIELD(11, 1),
        ACCESS_MUTABLE  = EE_HINTFIELD(11, 2),
        ACCESS_STATIC   = EE_HINTFIELD(11, 3),
        ACCESS_GPU      = EE_HINTFIELD(11, 4),
        /*!< Bit 15..11 - Access types */

        USAGE_UNKNOWN = EE_HINTFIELD(16, 0),
        USAGE_POOL    = EE_HINTFIELD(16, 1),
        USAGE_TEXTURE = EE_HINTFIELD(16, 2),
        USAGE_AUDIO   = EE_HINTFIELD(16, 3),
        USAGE_VIDEO   = EE_HINTFIELD(16, 4),
        USAGE_INDEX   = EE_HINTFIELD(16, 5),
        USAGE_VERTEX  = EE_HINTFIELD(16, 6),
        USAGE_PHYSICS = EE_HINTFIELD(16, 7),
        /*!< Bit 21..16 - Usage hints */

        /*!< Bits 29..22 - Currently unused */

        IS_BULK = EE_HINTFIELD(30, 1),
        /*!< Bit 30 indicates that the allocation is a bulk allocation instead of
        a 'metadata' allocation (e.g., GPU visible data instead of NiTexture) */

        TYPE_GB = EE_HINTFIELD(31, 0),
        TYPE_CUSTOM = EE_HINTFIELD(31, 1),
        /*!< Bit 31 indicates how bits 30..16 behave. */

        /// @name Common combinations.
        //@{
        NONE = 0x00000000,
        /*!< Normal memory allocation. */
        TEXTURE = USAGE_TEXTURE | IS_BULK
        /*!< GPU texture allocation */
        //@}
    };
#undef EE_HINTFIELD

    /// Returns the platform-specific hint (masks all but bits 7..0).
    inline Bits GetPlatform() const;

    /// Returns the lifetime hint (masks all but bits 9..8).
    inline Bits GetLifetime() const;

    /// Returns true if the hint specifies that the compiler will provide
    /// an accurate size on deallocations (bit 10).
    inline bool CompilerProvidesSizeOnDeallocate() const;

    /// Returns the access hint (masks all but bits 15..11).
    inline Bits GetAccess() const;

    /// Returns the usage hint (masks all but bits 21..16).
    inline Bits GetUsage() const;

    /// Returns true if the hint indicated that it is a bulk allocation (bit 30).
    inline bool IsBulk() const;

    /// Returns true if the hint is a custom hint (if so, bits 30..16 are not
    /// defined and not used by the standard allocators).
    inline bool IsCustomHint() const;

    /// Returns the internal representation of the hint.
    inline unsigned int GetRaw() const;

    /// @name Construction and Destruction
    //@{
    inline MemHint();
    inline MemHint(Bits eValue);
    //@}

    /// @name Standard Operators
    //@{
    inline MemHint& operator|=(const MemHint kRhs);
    inline MemHint& operator|=(const MemHint::Bits eRhs);
    inline MemHint operator|(const MemHint kRhs) const;
    inline MemHint operator|(const MemHint::Bits eRhs) const;
    inline bool operator==(const MemHint kRhs) const;
    inline bool operator!=(const MemHint kRhs) const;
    //@}

protected:
    // Actual storage for the hint
    Bits m_eValue;
};

inline MemHint::Bits operator|(const MemHint::Bits eLhs, const MemHint::Bits eRhs);

} // namespace efd

//--------------------------------------------------------------------------------------------------

// This macro returns a 'default' hint that gives no additional information
#define EE_MEMHINT_NONE efd::MemHint()

//--------------------------------------------------------------------------------------------------

#include <efd/MemHint.inl>

#endif // #ifndef EE_MEMHINT_H
