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
#ifndef NIVISUALTRACKERRENDERCLICK_H
#define NIVISUALTRACKERRENDERCLICK_H

#include "NiVisualTrackerLibType.h"
#include <NiRenderClick.h>
#include "NiVisualTracker.h"

class NIVISUALTRACKER_ENTRY NiVisualTrackerRenderClick : public NiRenderClick
{
    NiDeclareRTTI;

public:
    NiVisualTrackerRenderClick();

    // Functions for reporting statistics about the most recent frame.
    virtual unsigned int GetNumObjectsDrawn() const;
    virtual float GetCullTime() const;
    virtual float GetRenderTime() const;

    // Functions for accessing visual trackers.
    inline void AppendVisualTracker(NiVisualTracker* pkVisualTracker);
    inline void PrependVisualTracker(NiVisualTracker* pkVisualTracker);
    inline void RemoveVisualTracker(NiVisualTracker* pkVisualTracker);
    inline void RemoveAllVisualTrackers();
    inline NiTPointerList<NiVisualTrackerPtr>& GetVisualTrackers();
    inline const NiTPointerList<NiVisualTrackerPtr>& GetVisualTrackers() const;

protected:
    // Function for drawing visual trackers.
    virtual void PerformRendering(unsigned int uiFrameID);

    // List of visual trackers.
    NiTPointerList<NiVisualTrackerPtr> m_kVisualTrackers;

    // Rendering statistics.
    unsigned int m_uiNumObjectsDrawn;
    float m_fRenderTime;
};

NiSmartPointer(NiVisualTrackerRenderClick);

#include "NiVisualTrackerRenderClick.inl"

#endif  // #ifndef NIVISUALTRACKERRENDERCLICK_H
