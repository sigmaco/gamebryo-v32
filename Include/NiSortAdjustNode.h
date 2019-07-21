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
#ifndef NISORTSWITCHNODE_H
#define NISORTSWITCHNODE_H

#include "NiNode.h"

class NIMAIN_ENTRY NiSortAdjustNode : public NiNode
{
    NiDeclareRTTI;
    NiDeclareClone(NiSortAdjustNode);
    NiDeclareStream;

public:
    NiSortAdjustNode();
    virtual ~NiSortAdjustNode();

    enum SortingMode
    {
        SORTING_INHERIT,
        SORTING_OFF,
        SORTING_MAX
    };

    inline void SetSortingMode(SortingMode eMode);
    SortingMode GetSortingMode() const;

    virtual void OnVisible(NiCullingProcess& kCuller);

    // *** begin Emergent internal use only ***
    virtual void ProcessClone(NiCloningProcess& kCloning);
    // *** end Emergent internal use only ***

protected:
    SortingMode m_eSortingMode;
};


typedef efd::SmartPointer<NiSortAdjustNode> NiSortAdjustNodePtr;

//------------------------------------------------------------------------------------------------
//  Inline include
#include "NiSortAdjustNode.inl"


#endif
