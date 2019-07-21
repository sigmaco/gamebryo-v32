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
#ifndef NSBOBJECTTABLE_H
#define NSBOBJECTTABLE_H

#include "NSBShaderLibLibType.h"
#include <NiShaderAttributeDesc.h>
#include <NiTListBase.h>
#include <NiTPointerList.h>

class NSBSHADERLIB_ENTRY NSBObjectTable : public NiMemObject
{
public:
    class ObjectDesc : public NiMemObject
    {
    public:
        ObjectDesc(const char* pcName,
            NiShaderAttributeDesc::ObjectType eType, unsigned int uiIndex);
        ~ObjectDesc();

        inline const char* GetName() const;
        void SetName(const char* pcName);

        inline NiShaderAttributeDesc::ObjectType GetType() const;
        inline void SetType(NiShaderAttributeDesc::ObjectType eType);

        inline unsigned int GetIndex() const;
        inline void SetIndex(unsigned int uiIndex);

    private:
        char* m_pcName;
        NiShaderAttributeDesc::ObjectType m_eType;
        unsigned int m_uiIndex;
    };

    ~NSBObjectTable();

    bool AddObject(const char* pcName,
        NiShaderAttributeDesc::ObjectType eType, unsigned int uiIndex);

    inline unsigned int GetObjectCount() const;
    inline ObjectDesc* GetFirstObject(NiTListIterator& kIter);
    inline ObjectDesc* GetNextObject(NiTListIterator& kIter);
    ObjectDesc* GetObjectByName(const char* pcName);

private:
    NiTPointerList<ObjectDesc*> m_kObjectList;
};

#include "NSBObjectTable.inl"

#endif  // #ifndef NSBOBJECTTABLE_H
