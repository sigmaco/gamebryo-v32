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

#ifndef NICURVE3_H
#define NICURVE3_H

#include "NiParticleLibType.h"
#include <NiObject.h>
#include <NiPoint3.h>

/**
    The 3D curve class.

    The curve is composed of control points and knots. A method is provided for returning a
    point along the curve given a number from 0 to 1.
*/
class NIPARTICLE_ENTRY NiCurve3 : public NiObject
{
    /// @cond EMERGENT_INTERNAL

    NiDeclareRTTI;
    NiDeclareClone(NiCurve3);
    NiDeclareStream;
    NiDeclareViewerStrings;

    /// @endcond

public:
    NiCurve3();
    ~NiCurve3();

    /// Initialize the Curve
    /// @note The number of knots needs to be the number of control points plus the degree plus 1.
    void Initialize(NiUInt32 uiDegree, NiUInt32 uiNumControlPoints, NiPoint3* pkControlPoints,
        NiUInt32 uiNumKnots, float *pfKnots);

    /// Returns the point along the curve by a given distance between 0(start) and 1(end).
    NiPoint3 GetPointAlongCurve(const float fDistance);

    /// Returns the number of control points in the curve.
    inline NiUInt32 GetNumControlPoints() const;

    /// Returns a pointer to the array of control points for the curve.
    inline NiPoint3* GetControlPoints() const;

    /// Returns the point given the index in the array of control points for the curve.
    inline NiPoint3 GetControlPoint(NiUInt32 uiIndex) const;

    /// Returns the number of knots in the curve.
    inline NiUInt32 GetNumKnots() const;

    /// Returns a pointer to the array of knots for the curve.
    inline float* GetKnots() const;

    /// Returns the knot value given the index in the array of knots for the curve.
    inline float GetKnot(NiUInt32 uiIndex) const;

    /// Returns the number of spans on the curve.
    ///
    /// Spans are sections of the curve from one control point to the next.
    inline NiUInt32 GetNumSpans(void) const;

    /**
        Returns the weight on a particular Control Point at a given t value.

        @param uiCPIndex The control point to get the weight for.
        @param uiOrder The order of the operation (changes with recursive calls).
        @param fT the [0,1] The parametric position of the point.
    */
    float GetBlendFunction(NiUInt32 uiCPIndex, NiUInt32 uiOrder, float fT) const;

    /**
        Returns the index of the knot having the given t value or the index of the knot
        just before.

        @param fT The [0,1] parametric position of the point.
    */
    NiUInt32 GetKnotBeforeOrAtT(float fT) const;

//     // *** begin Emergent internal use only ***
// #ifndef __SPU__
//     // streaming
//     void LoadBinary (NiStream& kStream);
//     void SaveBinary (NiStream& kStream) const;
//
//     void GetViewerStrings (NiViewerStringsArray* pkStrings) const;
//
// #endif
//     // *** end Emergent internal use only ***

protected:

    /// @cond EMERGENT_INTERNAL

    void SetDegree(NiUInt32 uiDegree);
    void SetControlPoints(NiUInt32 uiNumControlPoints, NiPoint3* pkControlPoints);
    void SetKnots(NiUInt32 uiNumKnots, float *pfKnots);

    /// @endcond

    NiUInt32 m_uiDegree : 4;
    NiUInt32 m_uiNumControlPoints : 14;
    NiUInt32 m_uiNumKnots : 14;
    NiPoint3* m_pkControlPoints;
    float* m_pfKnots;

};

NiSmartPointer(NiCurve3);

//--------------------------------------------------------------------------------------------------
//  Inline include
#include "NiCurve3.inl"

//--------------------------------------------------------------------------------------------------

#endif  // #ifndef NICURVE3_H
