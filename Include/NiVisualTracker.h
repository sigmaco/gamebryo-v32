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
#ifndef NIVISUALTRACKER_H
#define NIVISUALTRACKER_H

#include <NiVisualTrackerLibType.h>
#include <NiRefObject.h>
#include <NiColor.h>
#include <NiObject.h>
#include <NiRect.h>
#include <NiMesh.h>
#include <NiPoint2.h>
#include <NiNode.h>
#include <NiPoint3.h>
#include <NiMeshScreenElements.h>

NiSmartPointer(NiTexture);


class NIVISUALTRACKER_ENTRY NiVisualTrackerBase : public NiRefObject
{
public:
    NiVisualTrackerBase(NiRect<float> kWindowRect,
        bool bShow,
        const char* pcName);
    virtual ~NiVisualTrackerBase();

    void SetShow(bool bShow);
    bool GetShow();

    virtual NiUInt32 Update();
    virtual void Draw();

    //*** begin Emergent internal use only
    class ScreenText : public NiMemObject
    {
    public:
        ScreenText(unsigned int uiMaxChars,
            NiMeshScreenElementsArray* pkScreenTextures,
            const NiColorA& kColor);
        ~ScreenText();

        // Will truncate the string to the pre-set max number of characters
        void SetString(const char* pcString);
        const char* GetString() const;

        // Works in screen space pixel coords: <0 - (m-1), 0 - (n-1)>,
        // where the screen size is (m,n), to set the position of the
        // upper-left edge of the text.
        void SetTextOrigin(unsigned int uiX, unsigned int uiY);
        void GetTextOrigin(unsigned int& uiX, unsigned int& uiY) const;

        void SetScrollDown(bool bDown);
        bool GetScrollDown() const;

        void SetColor(NiColorA& kNewColor);
        const NiColorA& GetColor() const;

        void SetVisible(bool bVisible);

        short GetHeight() const;
        short GetWidth() const;
        short GetCharacterSpacing() const;

        // Sets the line length for word wrapping  This should always be
        // less than the text size, or else truncation will occur.
        void SetMaxLineLength(unsigned int uiColumns);
        unsigned int GetMaxLineLength() const;

        // Will not append beyond the pre-set max number of characters.
        void AppendCharacter(char cChar);
        void DeleteLastCharacter();

        void RecreateText();

        static NiTexture* GetTexture();

    protected:
        void Init(unsigned int uiMaxChars,
            NiMeshScreenElementsArray* pkScreenTextures,
            const NiColorA& kColor);

        NiPixelData* CreateCourier16PixelData();

        NiMeshScreenElementsPtr m_spScreenElement;
        NiMeshScreenElementsArray* m_pkScreenElements;
        NiColorA m_kColor;

        unsigned int m_uiTextOriginX;
        unsigned int m_uiTextOriginY;

        char* m_pcString;
        unsigned int m_uiMaxChars;
        unsigned int m_uiNumChars;
        unsigned int m_uiMaxCols;

        unsigned int m_uiNumRects;
        unsigned int m_uiNumCurrentRows;
        unsigned int m_uiCurrentColumn;

        bool m_bScrollDown;

        static NiPixelDataPtr ms_spFontPixelData;
        static unsigned int ms_uiCharWidth;
        static unsigned int ms_uiCharHeight;
        static unsigned int ms_uiCharSpacingX;
        static unsigned int ms_uiCharSpacingY;
        static const unsigned int ms_uiCharBaseU;
        static const unsigned int ms_uiCharBaseV;
        static NiTexturePtr ms_spTextTexture;
        static const char* ms_pcTextImage;
        static const unsigned int ms_uiASCIIMin;
        static const unsigned int ms_uiASCIIMax;
        static unsigned int ms_uiASCIICols;
        static int ms_iCount;
    };
    //*** end Emergent internal use only

protected:
    NiRect<float> m_kDimensions;
    bool m_bShow;
    NiMeshScreenElementsArray m_kScreenTextures;
    char m_acName[256];
};

NiSmartPointer(NiVisualTrackerBase);


/// An NiVisualTracker is a single chart that can track and display multiple data sets. The
/// supported data types include time-series line graphs and scatter graphs.
class NIVISUALTRACKER_ENTRY NiVisualTracker : public NiVisualTrackerBase
{
    public:
        /** Constructor

            @param pName The name for this chart, which is displayed at the top of the chart.
            @param dataRange The expected range for data values. The vertical range effects all
                graph types, but the horizontal range is only used for scatter graphs. The range
                is in real coordinates (smaller numbers are to the lower left, larger numbers are
                to the upper right) scaled however you like. You can invert the data by swapping
                the left/right or top/bottom settings.
            @param windowRect The display coordinates for showing this chart. The point {0.0f,0.0f}
                is the upper left corner and {1.0f, 1.0f} is the bottom right corner.
            @param uiNumDecimalPlaces Number of decimal places to display on the axis
                labels.
            @param bShow True if this chart is initially visible.
            @param uiNumGraphs Number of graphs and data points you expect to add. This is not
                maximum limit, just an initial size
        */
        NiVisualTracker(
            const char* pName,
            NiRect<float> dataRange,
            NiRect<float> windowRect,
            unsigned int uiNumDecimalPlaces = 0,
            bool bShow = true,
            unsigned int uiNumGraphs = 5);

        /** Legacy constructor. Assumes a data range from 0.0 to fMax for the vertical axis and
            assumes the horizontal axis will never be used.  As a result you cannot call
            AddDataPoint on a graph created with this constructor, it only supports AddGraph.

            @param fMaxValue The maximum data value for the vertical axis. 0.0f will be used as
                the minimum data value and the horizontal range is set from 0.0f to 1.0f.
            @param uiNumDecimalPlaces Number of decimal places to display on the axis
                labels.
            @param kWindowRect The display coordinates for showing this chart. The point {0.0f,0.0f}
                is the upper left corner and {1.0f, 1.0f} is the bottom right corner.
            @param pcName The name for this chart, which is displayed at the top of the chart.
            @param bShow True if this chart is initially visible.
            @param uiNumGraphs Number of graphs and data points you expect to add. This is not
                maximum limit, just an initial size
        */
        NiVisualTracker(
            float fMaxValue,
            unsigned int uiNumDecimalPlaces,
            NiRect<float> kWindowRect,
            const char* pcName,
            bool bShow = true,
            unsigned int uiNumGraphs = 5);

        virtual ~NiVisualTracker();

        /// This is the callback object to derive from in order to implement a time series line
        /// graph.  The TakeSample method will be called at the update frequency passed to the
        /// AddGraph method and a line graph will be constructed showing current and past values.
        class NIVISUALTRACKER_ENTRY GraphCallbackObject : public NiMemObject
        {
            public:
                inline virtual ~GraphCallbackObject();

                virtual float TakeSample(float fTime) = 0;

                //*** begin Emergent internal use only
                inline virtual bool TakeSample(float fTime, float& fDataOut);
                //*** end Emergent internal use only
        };

        /// A callback for scatter graph data points. Each data point in the graph is added
        /// separately by calling AddDataPoint and each point can update its position via
        /// the TakeSample method which is called at the update frequency.  Past values are
        /// not displayed, only the most recent position.
        class NIVISUALTRACKER_ENTRY DataPointCallbackObject : public NiMemObject
        {
        public:
            inline virtual ~DataPointCallbackObject();

            /// Take a sample of the data for this point. You can optionally change your symbol
            /// as well by changing the uiSymbolInOut value.
            /// @return False to have your callback object removed.
            virtual bool TakeSample(float fTime, efd::Point2& kPointOut, efd::UInt32& uiSymbolInOut) = 0;
        };

        /// Insert a time series line graph into the chart. Returns the tracker index.
        /// @note The trackers can be rearranged so the returned index cannot be relied for
        ///     subsequent operations.
        unsigned int AddGraph(
            GraphCallbackObject* pCallbackObject,
            const char* pcName,
            const NiColor& kColor,
            unsigned int uiNumSamplesToKeep,
            float fUpdateFrequency,
            bool bShow);

        /// Insert a single data point into the chart.
        /// @return the tracker index.
        unsigned int AddDataPoint(
            DataPointCallbackObject* pObject,
            const NiColor& color,
            efd::UInt32 symbol,
            NiRect<float>& dataRange,
            float fSamplingTime,
            bool bShow);

        /// Value to pass to AddLegend to not use a symbol.
        static const efd::UInt32 k_NO_SYMBOL = (efd::UInt32)-1;

        /// Add an entry to the legend. Note that AddGraph automatically creates legend entries
        /// using the name and color of the graph line so you only need to call this when you are
        /// creating scatter graphs using AddDataPoint.
        bool AddLegend(const char* pLegendName,
            const NiColor& color,
            efd::UInt32 symbol = k_NO_SYMBOL);

        /// Remove a tracker by name.  Only works for line-graph style graphs that have names.
        void RemoveGraph(const char* pcName);

        /// Remove all trackers. This is the only way to remove scatter-graph points.
        void RemoveAll();

        /// Get the name of this chart
        const char* GetName();

        /// Get the number of trackers in the chart.  Each line graph or scatter graph data point
        /// is a separate tracker, so each call to AddGraph or AddDataPoint increases this value.
        unsigned int GetGraphCount();

        /// Set the name of a callback. For Graph-style data this is the name displayed in the
        /// legend, other types of callbacks might not have a name.
        /// @return True if the name was set, false if that graph item has no name.
        bool SetName(const char* pcName, unsigned int uiWhichGraph);

        /// Get the name of the graph at the given index. Note that this will be an empty string
        /// for data types such as scatter graph DataPoints which have no name.
        const char* GetName(unsigned int uiWhichGraph);
        unsigned int GetGraphIndexByName(const char* pcName);

        /// Toggle the visibility of a line graph. This determines if the tracker is currently
        /// visible, but does not affect its sampling. This only effects line-graph style data
        /// trackers.
        inline void ShowGraph(bool bShow, unsigned int uiWhichGraph);
        inline bool GetGraphShow(unsigned int uiWhichGraph);

        virtual void ResetTimeCounters();

        /**
            Update all of our callbacks.
            
            Internally each callback enforces the update interval so this only takes a new
            sample if enough time has passed.
            
            @return The number of callback objects removed during this update.
        */
        virtual NiUInt32 Update();

        /// Calls Draw on each callback which is used to immediately render any data that needs
        /// to be rendered.
        virtual void Draw();

    protected:
        /// Helper called during constructor
        void Setup(efd::UInt32 uiNumTrackers, efd::UInt32 uiNumDecimalPlaces);

        class SymbolScreenElement : public NiMeshScreenElements
        {
        public:
            SymbolScreenElement(efd::UInt32 symbol, const NiColor& color);
            ~SymbolScreenElement();

            inline efd::UInt32 GetSymbol() { return m_symbol; }
            void SetSymbol(efd::UInt32 symbol);

            // set location in 0.0 to 1.0 window coordinates
            void SetLocationInWindow(float x, float y);
            // set location in pixel coordinates
            void SetLocationOnScreen(efd::UInt32 x, efd::UInt32 y);

        protected:
            efd::UInt32 m_symbol;

            // Creates the ms_spSymboPixelData pixel data used to create the ms_spSymbolTexture
            // texture which we use to draw graph points.
            NiPixelData* CreateSymbolPixelData();
            static NiPixelDataPtr ms_spSymbolPixelData;
            static NiTexturePtr ms_spSymbolTexture;
            static efd::UInt32 ms_textureRefCount;

            // Set texture coordinates based on the selected symbol
            void SelectSymbol();
        };
        typedef efd::SmartPointer<SymbolScreenElement> SymbolScreenElementPtr;


        /// Any entry in the legend under the graph. Line-Graph style trackers automatically
        /// add a legend entry for their graph name.
        class LegendEntry : public efd::RefCount
        {
        public:
            LegendEntry(const char* pName, const NiColor& color, efd::UInt32 symbol,
                unsigned int& io_uiLegendX, unsigned int& io_uiLegendY,
                NiMeshScreenElementsArray& kTextures);
            ~LegendEntry();

            const char* GetName();
            void SetName(const char* pcName);

            void AdjustLegend(int iX, int iY);
            unsigned int GetLegendWidth();

        protected:
            char m_acName[256];
            ScreenText* m_pText;
            SymbolScreenElementPtr m_spSymbol;
            NiMeshScreenElementsArray* m_pkScreenElements;
        };
        typedef efd::SmartPointer<LegendEntry> LegendEntryPtr;

        /// Base class for all graph data updates
        class CallbackObjectData : public NiMemObject
        {
        public:
            CallbackObjectData(
                LegendEntry* legend,        //< Null if I have no legend entry
                float fSamplingTime,
                bool bShow,
                const NiRect<float>& dimensions);
            virtual ~CallbackObjectData();

            // Return false to have this data object removed
            virtual bool Update(float fTime) = 0;
            virtual void Draw() = 0;

            inline void ResetLastSampleTime();

            bool GetShow();
            void SetShow(bool bShow);

            /// The legend entry corresponding to this callback, or 0 if this callback has no
            /// entry in the legend.
            LegendEntry* GetLegendEntry();

        protected:
            /// An optional pointer to an entry in the legend for this callback.
            LegendEntryPtr m_spLegendEntry;

            /// The update frequency for calling the callback
            float m_fSamplingTime;

            /// Whether this graph is currently being displayed. Individual graphs in a chart can
            /// be shown or hidden via NiVisualTracker::ShowGraph.
            bool m_bShow;

            NiRect<float> m_kDimensions;
            float m_fLastTime;
        };

        class GraphCallbackObjectData : public CallbackObjectData
        {
        public:
            GraphCallbackObjectData(GraphCallbackObject* pCallbackObject,
                LegendEntry* legend,
                const NiColor& color,
                unsigned int uiNumSamplesToKeep,
                float fMinValue,
                float fMaxValue,
                float fSamplingTime,
                bool bShow,
                const NiRect<float>& kDimensions,
                NiNode* pkParentNode);

            ~GraphCallbackObjectData();

            virtual bool Update(float fTime);
            virtual void Draw();

            static NiMeshPtr CreateLines(
                unsigned int uiNumVertices,
                const NiColor& color,
                const NiRect<float>& dimensions);

        protected:

            // BUFFER_COUNT dictates the number of times the
            // GraphCallbackObjectData mesh data will be duplicated. The
            // duplicated buffers are updated and rendered in a round robin
            // fashion where the rendered mesh is always one frame behind.
            // This prevents any GPU stalling that may occur from trying to
            // update a mesh that we are currently rendering.
            enum
            {
                BUFFER_COUNT  = 3
            };

            GraphCallbackObject* m_pkCallbackObj;
            unsigned int m_uiNumSamplesToKeep;
            NiMeshPtr m_aspLines[BUFFER_COUNT];
            float m_afPrevFramesValues[BUFFER_COUNT];
            float m_fMinValue;
            float m_fMaxValue;
            unsigned int m_uiNextVertex;
            unsigned int m_uiBufferID;
        };

        class PointCallbackObjectData : public CallbackObjectData
        {
        public:
            PointCallbackObjectData(
                DataPointCallbackObject* pCallbackObject,
                const NiColor& color,
                efd::UInt32 whichSymbol,
                float fSamplingTime,
                bool bShow,
                const NiRect<float>& dataDimensions,
                const NiRect<float>& windowDimensions,
                NiMeshScreenElementsArray& textures);

            ~PointCallbackObjectData();

            virtual bool Update(float fTime);
            virtual void Draw();

        protected:
            DataPointCallbackObject* m_pCallbackObj;
            NiRect<float> m_dataRange;
            efd::UInt32 m_symbol;
            efd::Point2 m_lastPoint;

            SymbolScreenElementPtr m_spSymbol;
            NiMeshScreenElementsArray* m_pkScreenElements;
        };

        NiTPrimitiveArray<CallbackObjectData*> m_callbackData;

        typedef efd::list<LegendEntryPtr> LegendList;
        LegendList m_legendData;

        void AddLegend(LegendEntry* pLegend);
        void AdjustLegend(LegendEntry* pLegend, const char* pcName);
        void RemoveLegend(LegendEntry* pLegend);
        void AdjustRemainingLegends(LegendList::iterator iter, int iXAdjust);

        NiRect<float> m_dataRange;
        NiRect<float> m_graphLineDimensions;
        NiNodePtr m_spWindowRoot;
        NiMeshPtr m_spBorders;

        ScreenText* m_pTextTitle;
        ScreenText* m_pTextZero;
        ScreenText* m_pTextTwentyFive;
        ScreenText* m_pTextFifty;
        ScreenText* m_pTextSeventyFive;
        ScreenText* m_pTextOneHundred;

        unsigned int m_uiLegendX;
        unsigned int m_uiLegendY;
};

NiSmartPointer(NiVisualTracker);

#include "NiVisualTracker.inl"

#endif
