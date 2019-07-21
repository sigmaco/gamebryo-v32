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
#ifndef NICOMMONGRAPHCALLBACKOBJECTS_H
#define NICOMMONGRAPHCALLBACKOBJECTS_H

#include <NiVisualTrackerLibType.h>
#include <NiVisualTracker.h>
#include <NiMemTracker.h>
#include <NiVisibleArray.h>

//--------------------------------------------------------------------------------------------------
// Tracks NiMemTracker::m_stPeakMemory
class NIVISUALTRACKER_ENTRY MemHighWaterMarkUpdate
    : public NiVisualTracker::GraphCallbackObject
{
public:
    MemHighWaterMarkUpdate(float fScalar, NiMemTracker* pkTracker);
    virtual float TakeSample(float fTime);

    float m_fScalar;
    NiMemTracker* m_pkTracker;
};

//--------------------------------------------------------------------------------------------------
// Tracks NiMemTracker::m_stActiveMemory
class NIVISUALTRACKER_ENTRY MemCurrentUpdate
    : public NiVisualTracker::GraphCallbackObject
{
public:

    MemCurrentUpdate(float fScalar, NiMemTracker* pkTracker);
    virtual float TakeSample(float fTime);

    float m_fScalar;
    NiMemTracker* m_pkTracker;
};

//--------------------------------------------------------------------------------------------------
// Tracks NiMemTracker::m_stActiveAllocationCount
class NIVISUALTRACKER_ENTRY MemCurrentAllocCountUpdate
    : public NiVisualTracker::GraphCallbackObject
{
public:
    MemCurrentAllocCountUpdate(float fScalar, NiMemTracker* pkTracker);
    virtual float TakeSample(float fTime);

    float m_fScalar;
    NiMemTracker* m_pkTracker;
};

//--------------------------------------------------------------------------------------------------
// Actually just returns the pointed at float without any scale
class NIVISUALTRACKER_ENTRY FrameRateUpdate
    : public NiVisualTracker::GraphCallbackObject
{
public:
    FrameRateUpdate(float *pfFrameRate);

    virtual float TakeSample(float fTime);
    float *m_pfFrameRate;
};

//--------------------------------------------------------------------------------------------------
// Tracks the size of an NiVisibleArray
class NIVISUALTRACKER_ENTRY VisibleArrayUpdate
    : public NiVisualTracker::GraphCallbackObject
{
public:
    VisibleArrayUpdate(NiVisibleArray& kVisArray);

    virtual float TakeSample(float fTime);
    NiVisibleArray& m_kVisArray;
private:
    VisibleArrayUpdate & operator=(const VisibleArrayUpdate &);
};

//--------------------------------------------------------------------------------------------------
// Tracks a float value with a scale applied
class NIVISUALTRACKER_ENTRY GenericFloatUpdate
    : public NiVisualTracker::GraphCallbackObject
{
public:

    GenericFloatUpdate(float fScalar, float* pfValue);
    virtual float TakeSample(float fTime);

    float m_fScalar;
    float* m_pfValue;
};

//--------------------------------------------------------------------------------------------------
// Tracks an unsigned integer value with a scale applied
class NIVISUALTRACKER_ENTRY GenericUnsignedIntUpdate
    : public NiVisualTracker::GraphCallbackObject
{
public:

    GenericUnsignedIntUpdate(float fScalar, unsigned int* puiValue);
    virtual float TakeSample(float fTime);

    float m_fScalar;
    unsigned int* m_puiValue;
};

//--------------------------------------------------------------------------------------------------
#endif
