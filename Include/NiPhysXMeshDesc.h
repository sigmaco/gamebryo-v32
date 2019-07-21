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


#ifndef NIPHYSXMESHDESC_H
#define NIPHYSXMESHDESC_H

#include "NiPhysXLibType.h"

#include <NiMain.h>
#include <NiSystem.h>

#if defined(WIN32) || defined(_XENON)
#pragma warning(push)
#pragma warning(disable: 4100) // unreferenced formal parameter
#pragma warning(disable: 4512) // assignment operator could not be generated

#pragma warning(disable: 4244) // conversion from 'type' to 'type',
                               // possible loss of data

#pragma warning(disable: 4245) // conversion from 'type' to 'type',
                               // signed/unsigned mismatch

#elif defined(_PS3)
#pragma GCC system_header
#endif
#include <NxCooking.h>
#include <NxPhysics.h>
#if defined(WIN32) || defined(_XENON)
#pragma warning(pop)
#endif

/**
    NiPhysXMeshDesc objects hold mesh data for streaming.

    Applications will typically only touch these objects when working on tools
    that stream PhysX content, or when constructing NiPhysXActorDesc or
    NiPhysXClothDesc objects.

    Internally, this class stores the name of the mesh, cooked mesh data if
    it is known, and any flags for creating the mesh. The flags, paging mode
    and name properties only affect shapes when they are created for an actor -
    they do not modify shapes that have already been attached to actors.
    
    Multiple shape objects may point to the same instance of this class, in which case
    the PhysX mesh is shared amongst the using shapes.
*/
class NIPHYSX_ENTRY NiPhysXMeshDesc : public NiObject
{
    /// @cond EMERGENT_INTERNAL
    NiDeclareStream;
    NiDeclareRTTI;
    /// @endcond

public:
    /// Constructor creates an object with no name or data.
    NiPhysXMeshDesc();

    /// Destructor deletes any data.
    ~NiPhysXMeshDesc();

    /// Returns true if this object represents a cloth mesh.
    bool GetIsCloth() const;

    /// Sets this object to represent a cloth mesh.
    void SetIsCloth();

    /// Returns true if this object represents a convex mesh.
    bool GetIsConvex() const;

    /// Sets this object to represent a convex mesh.
    void SetIsConvex();

    /// Returns true if this object represents a trishape mesh.
    bool GetIsTriMesh() const;

    /// Sets this object to represent a trishape mesh.
    void SetIsTriMesh();

    /**
        Get the platform for which this mesh was cooked.

        Returns true and sets kPlatform if there is platform information
        available, or returns false and leaves kPlatform unchanged if
        there is no knowledge of the platform.
    */
    bool GetPlatform(NxPlatform& kPlatform) const;

    /// Set the target platform.
    void SetPlatform(const NxPlatform kPlatform);

    /**
        Return true if the platform on which the application is executing is
        the same as the platform for which the mesh was cooked, false
        otherwise.

        The function returns true if there is no mesh information available.
    */
    bool IsValidPlatform() const;

    /**
        Get mesh flags.

        These are the flags stored in a PhysX NxClothMeshDesc, NxConvexMeshDesc
        or NxTriangleMeshDesc object.
    */
    NxU32 GetFlags() const;

    /// Set the mesh flags.
    void SetFlags(const NxU32 uiFlags);

    /// Returns true if this mesh was cooked for PhysX hardware simulation.
    bool GetHardware() const;

    /// Set the flag indicating hardware cooking.
    void SetHardware(const bool bHardware);

    /// Get the mesh paging mode associated with the mesh.
    NxMeshPagingMode GetMeshPagingMode() const;

    /// Set the mesh paging mode associated with the mesh.
    void SetMeshPagingMode(const NxMeshPagingMode eMode);

    /// Get the name used for the mesh.
    const NiFixedString& GetName() const;

    /**
        Set the name to use for the mesh.

        The name is the file name for an extranlly streamed mesh.
    */
    void SetName(const NiFixedString& kName);

    /// Get the cooked mesh data and its size.
    void GetData(size_t& kSize, unsigned char** ppucData);

    /// Set the raw cooked mesh data.
    ///
    /// The data size must also be provided.
    void SetData(const size_t uiSize, unsigned char* pucData);

    /**
        Fill the contents of a PhysX cloth mesh descriptor object.

        If the mesh has previously been created (that is, it is shared), then the existing
        mesh is used. Otherwise, this function takes the cooked data and calls
        NxPhysicsSDK::createClothMesh. If no mesh data is present, then the
        mesh name is used to look for a file containing the mesh data
        (see NiPhysXClothMesh for details on loading external meshes).
        
        If bKeepsMesh is false, the mesh data is deleted after the mesh is created.
    */
    virtual void ToClothDesc(
        NxClothDesc& kClothDesc,
        const bool bKeepData,
        const bool bCheckPlatform = false);

    /**
        Fill the contents of a PhysX convex mesh descriptor object.

        If the mesh has previously been created (that is, it is shared), then the existing
        mesh is used. Otherwise, this function takes the cooked data and calls
        NxPhysicsSDK::createConvexMesh. If no mesh data is present, then the
        mesh name is used to look for a file containing the mesh data
        (see NiPhysXConvexMesh for details on loading external meshes).

        If bKeepsMesh is false, the mesh data is deleted after the mesh is created.
    */
    virtual void ToConvexDesc(
        NxConvexShapeDesc& kConvexDesc,
        const bool bKeepData,
        const bool bCheckPlatform = false);

    /**
        Fill the contents of a PhysX triangle mesh descriptor object.

        If the mesh has previously been created (that is, it is shared), then the existing
        mesh is used. Otherwise, this function takes the cooked data and calls
        NxPhysicsSDK::createTriangleMesh. If no mesh data is present, then the
        mesh name is used to look for a file containing the mesh data
        (see NiPhysXTriangleMesh for details on loading external meshes).

        If bKeepsMesh is false, the mesh data is deleted after the mesh is created.
    */
    virtual void ToTriMeshDesc(
        NxTriangleMeshShapeDesc& kTriMeshDesc,
        const bool bKeepData,
        const bool bCheckPlatform = false);

    /// @name Mesh Search Directory Functions
    //@{
    /**
        Get the platform specific directory in which to search for meshes.

        PhysX meshes may have different cooked formats on different platforms,
        and these functions allow applications to more easily manage loading
        the appropriate resources. This is modeled after the NiImageConverter
        class's methods for accessing textures, and functions in the same way.
        It is used when loading a NIF file that contains references to
        externally stored meshes.
    */
    static const char* GetPlatformSpecificSubdirectory();

    /// Set the platform specific directory in which to search for meshes.
    ///
    /// The string is copied.
    static void SetPlatformSpecificSubdirectory(const char* pcSubDir);

    /**
        Convert a given file name in a platform specific file.

        This is modeled after the NiImageConverter class's methods for
        accessing textures, and functions in the same way.
    */
    static char* ConvertFilenameToPlatformSpecific(const char* pcPath);

    /**
        Convert a given file name in a platform specific file.

        This is modeled after the NiImageConverter class's methods for
        accessing textures, and functions in the same way.
    */
    static void ConvertFilenameToPlatformSpecific(const NiFixedString& kPath,
        NiFixedString& kPlatformSpecificPath);
    //@}

    /// @cond EMERGENT_INTERNAL

    inline void GetBackCompatVertexMap(NiUInt16& usSize, const NiUInt16*& pusMap);

    virtual bool StreamCanSkip();

    static void SDMInit();
    static void SDMShutdown();

    /// @endcond

protected:
    NxU32 m_uiMeshFlags;
    NiFixedString m_kMeshName;
    size_t m_uiMeshSize;
    unsigned char* m_pucMeshData;
    NxMeshPagingMode m_eMeshPagingMode;

    union {
        NxClothMesh* m_pkClothMesh;
        NxConvexMesh* m_pkConvexMesh;
        NxTriangleMesh* m_pkTriangleMesh;
    };

    // Mesh vertex index map, only used in loading older files.
    NiUInt16 m_usBackCompatVertexMapSize;
    NiUInt16* m_pusBackCompatVertexMap;

    // Gamebryo flags
    enum {
        IS_CONVEX_MASK = 0x01,
        IS_CLOTH_MASK  = 0x02,
        HARDWARE_MASK  = 0x04,
        COOKED_FOR_WIN32_MASK = 0x08,
        COOKED_FOR_PS3_MASK = 0x10,
        COOKED_FOR_XENON_MASK = 0x20
    };

    // Mesh directory.
    static char* ms_pcPlatformSubDir;

    NiDeclareFlags(unsigned char);
};

NiSmartPointer(NiPhysXMeshDesc);

#include "NiPhysXMeshDesc.inl"

#endif // NIPHYSXMESHDESC_H

