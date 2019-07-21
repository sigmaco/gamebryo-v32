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
#ifndef EE_VISUALTRACKERSERVICE_H
#define EE_VISUALTRACKERSERVICE_H

#include "egmVisualTrackerLibType.h"

#include <efd/ISystemService.h>
#include <efd/MessageHandlerBase.h>
#include <efd/MessageService.h>
#include <egf/EntityManager.h>
#include <efd/ClassInfo.h>
#include <NiVisualTracker.h>
#include <NiVisualTrackerRenderClick.h>
#include <ecr/RenderService.h>
#include <ecrInput/InputService.h>
#include <ecr/ecrSystemServiceIDs.h>

NiSmartPointer(NiVisualTrackerRenderClick);

namespace egf
{
    class EntityChangeMessage;
}

namespace egmVisualTracker
{

// Forward declaration:
class PointDescription;


/**
    This service provides a graphical display for tracking performance over time or
    other statistics.  There is built-in support for tracking frame rate, memory
    allocations, entity locations and some other common metrics.

    The set of items to display is controlled by the configuration system. See the
    Configuration Options Quick Reference page for a summary.

    The VisualTrackerService depends on the ecr::RenderService service and the
    efd::MessageService service. Users may wish to configure the visual tracker using
    the ConfigService. To do this, simply create a new section, "[VisualTracker]". To adjust
    the maximum values for Performance charts, create a variable called "PerfMaxValue" and set
    to the new maximum. Similarly, users can set the maximums for Timing charts with
    "TimingMaxValue" and Memory charts with "MemMaxValue". Additionally, individual service
    timings can be captured by setting a variable named "ServiceTrackers" with the count of
    trackers. Subsequent variables like "ServiceY" should be set with the Service ID of the
    service you wish to track. The "Y" variable should be the numeric index of the service
    to track, so the first service would be "Service0". Colors may also be specified per
    service using "ServiceYColor". Again, the "Y" variable name should be the service index.

    The configuration system is also used to control the display of an entity location scatter
    plot.
*/
class EE_EGMVISUALTRACKER_ENTRY VisualTrackerService
    : public efd::ISystemService
    , public ecr::IRenderServiceDelegate
{
    /// @cond EMERGENT_INTERNAL

    EE_DECLARE_CLASS2(
        VisualTrackerService,
        efd::kCLASSID_VisualTrackerService,
        efd::ISystemService,
        ecr::IRenderServiceDelegate);
    EE_DECLARE_CONCRETE_REFCOUNT;

    /// @endcond

public:
    /**
        Constructs the VisualTracker service.
    */
    VisualTrackerService();

    /// Returns the display name, "VisualTrackerService".
    virtual const char* GetDisplayName() const;

    /**
        Sets a surface to which the tracker will be drawn.

        This function must be called for at least one surface in order to see any visual
        tracker output. Warnings will be sent to the log if it is not called before OnTick.

        Note that the tracker statistics are always pulled from the current default
        render surface as reported by the ecr::RenderService object. This function
        controls where they are rendered to.
    */
    void AddSurface(ecr::RenderSurfacePtr spSurface);

    /**
        Removes the given surface from those receiving visual tracker output.
    */
    void RemoveSurface(ecr::RenderSurfacePtr spSurface);

    /**
        Add a new page to the visual tracker output. Pages are cycled through each time the
        "VISUAL_TRACKER_ACTION" input action is triggered. Each page can have multiple charts and
        each chart can have multiple graphs. Each graph is typically a data line plotted over time
        on the chart.

        This method may be called during PreInit.

        @param pageName The name of the current page.
        @return Index of the page that was added, or -1 if the page name is in use or invalid.
    */
    efd::UInt32 AddPage(const char* pageName);

    /**
        Set the active display page using the page index.

        This method may be called during PreInit.

        @param index The page to select. This is normally a previously returned value from AddPage.
        @return True if the index is a valid page index, false otherwise.
    */
    efd::Bool SelectPage(efd::UInt32 index);

    /**
        Set the active display page using the page name.

        This method may be called during PreInit.

        @param pageName The page to select. The name is whatever name was passed to AddPage.
        @return True if the name is a valid page, false otherwise.
    */
    efd::Bool SelectPage(const char* pageName);

    /// Returns the index of the current page
    ///
    /// This method may be called during PreInit.
    inline efd::UInt32 GetCurrentPage() const;

    /**
        Add a chart to the current page.  You must have previously called AddPage before you
        call this method.

        This method may be called during PreInit.

        @param chartName The name of the current chart.  This name is displayed above the chart.
        @param dataRange The range for data points for all graphs added to this chart. For most
            GraphCallbackObject sources the integral width of this range is used as the number of
            samples to store.  The height of this range is used to clamp the source values.
        @param windowRect The region within the render surface on which to render this chart. The
            specified dataRange will be scaled to fit in the windowRect.
        @param fSamplingRate The time frequency with which all graphs added to this chart will
            update.
        @param numDecimalPlaces The number of decimal places to display for axis labels.
        @param updateOnlyWhenVisible If true, update the chart only when visible.
        @return True if the tracker was added, or false if there is no current page.
    */
    efd::Bool AddChart(
        const char* chartName,
        NiRect<float> dataRange,
        NiRect<float> windowRect,
        efd::TimeType fSamplingRate,
        efd::UInt32 numDecimalPlaces = 0,
        efd::Bool updateOnlyWhenVisible = false);

    /**
        Add a time series line graph to the current chart. Line graphs are updated over time and
        draw a line showing previous values. The number of previous values used is determined by
        the width of the dataRange for the parent chart. You must have previously called AddChart
        before you call this method.

        This method may be called during PreInit.

        @param graphName The name of the current graph. This name is displayed in the given color
            in the legend under the graph.
        @param pCallbackObject The callback object which queries the data points.  The TakeSample
            method will be called on this object at the sampling rate specified by the chart and
            the results over time will be rendered as line graph.
        @param color The color used to render the line graph on the chart and the name in the
            legend.  Every graph on the same chart should use a different color.
        @return True if a graph was added to the current chart, or false if there is no current
            chart or no current page.
    */
    efd::Bool AddLineGraph(
        const char* graphName,
        NiVisualTracker::GraphCallbackObject* pCallbackObject,
        const efd::Color& color);

    /**
        Any enumeration of the symbols that can be used for adding scatter graph points.  These
        symbols are shown at the location of each point on the graph and are moved as the points
        are updated. In addition these symbols can be used with AddLegend to shown the symbol next
        to the legend name.
    */
    enum ScatterGraphSymbols
    {
        SGS_invalid = -1,           ///< An invalid symbol value

        SGS_square_small,           ///< A small square
        SGS_square,                 ///< A medium sized hollow square
        SGS_square_big,             ///< A large hollow square
        SGS_solid,                  ///< A large solid square

        SGS_circle_hollow,          ///< A small hollow circle
        SGS_circle_solid,           ///< A small solid circle
        SGS_circle_large_hollow,    ///< A large hollow circle
        SGS_circle_large_solid,     ///< A large solid circle

        SGS_arrow_top_right,        ///< small arrow from top-right corner pointing at center
        SGS_arrow_top_left,         ///< small arrow from top-left corner pointing at center
        SGS_arrow_bottom_left,      ///< small arrow from bottom-left corner pointing at center
        SGS_arrow_bottom_right,     ///< small arrow from bottom-right corner pointing at center

        SGS_arrow_up,               ///< A large arrow pointing up
        SGS_arrow_down,             ///< A large arrow pointing down
        SGS_arrow_left,             ///< A large arrow pointing left
        SGS_arrow_right,            ///< A large arrow pointing right

        SGS_plus_hollow,            ///< An outline of a thick plus symbol
        SGS_plus_solid,             ///< A solid thick plus symbol
        SGS_plus_thin,              ///< A solid thin plus symbol
        SGS_plus_small,             ///< A small solid plus symbol

        SGS_x_hollow,               ///< An outline of a thick 'x' symbol
        SGS_x_solid,                ///< A solid thick 'x' symbol
        SGS_x_thin,                 ///< A solid thin 'x' symbol
        SGS_x_small,                ///< A small solid 'x' symbol

        SGS_minus_hollow,           ///< An outline of a thick minus symbol
        SGS_minus_soild,            ///< A solid thick minus symbol
        SGS_minus_thin,             ///< A solid thin minus symbol
        SGS_minus_small,            ///< A small solid minus symbol

        SGS_play_hollow,            ///< A hollow triage like a standard play button
        SGS_play_solid,             ///< A solid triage like a standard play button
        SGS_back_hollow,            ///< A hollow triangle like 'play' but pointing left
        SGS_back_solid,             ///< A solid triangle like 'play' but pointing left

        SGS_pause_hollow,           ///< a standard pause button symbol
        SGS_pause_solid,            ///< a standard pause button symbol
        SGS_stopsign_hollow,        ///< An outline of a large octagon
        SGS_stopsign_solid,         ///< An outline of a large octagon

        SGS_wedge_up_hollow,        ///< A hollow triangle like 'play' but pointing up
        SGS_wedge_up_solid,         ///< A solid triangle like 'play' but pointing up
        SGS_wedge_down_hollow,      ///< A hollow triangle like 'play' but pointing down
        SGS_wedge_down_solid,       ///< A solid triangle like 'play' but pointing down

        SGS_stick_man,              ///< A stick figure
        SGS_little_dude,            ///< A little alien looking person
        SGS_fido,                   ///< A critter icon that looks like a horse
        SGS_lightbulb,              ///< A light bulb icon (looks more like a key to me)

        SGS_camera,                 ///< A camera icon
    };

    /**
        Add a scatter graph point to the current chart. A scatter graph does not represent a
        connected series of data. Rather they represent individual points within the dataRange of
        the parent chart. At the update frequency for the chart each point is refreshed which
        discards all previous data. You must have previously called AddChart before you call this
        method.

        Scatter graph points consume system resources and should be used with caution on
        resource limited platforms.

        This method may be called during PreInit.

        @param pCallbackObject The callback object which queries the data points.  The TakeSample
            method will be called on this object at the sampling rate specified by the chart and
            the results over time will be rendered as line graph.
        @param color The color used to render the line graph on the chart and the name in the
            legend.  Every graph on the same chart should use a different color.
        @param symbol The index of the symbol to use when rendering this data point.
        @return True if a graph was added to the current chart, or false if there is no current
            chart or no current page.
    */
    efd::Bool AddScatterGraphPoint(
        NiVisualTracker::DataPointCallbackObject* pCallbackObject,
        const efd::Color& color,
        ScatterGraphSymbols symbol);

    /**
        Add a legend entry. AddLineGraph automatically adds a legend entry, but this can be used
        with AddScatterGraphPoint to provide labeling.

        This method may be called during PreInit.
    */
    efd::Bool AddLegend(
        const char* name,
        const efd::Color& color,
        ScatterGraphSymbols symbol = SGS_invalid);

    /**
        Sets display status of tracker graphs.
    */
    void SetShowTrackers(bool show);

    /**
        Returns true if trackers are visible.
    */
    inline bool GetShowTrackers() const;

    /**
        Toggles the visibility of the trackers.
    */
    void ToggleShowTrackers();

    /**
        Handle incoming action messages from the input service.

        The service looks for key presses of the F11 key or GamePad Right Stick, which
        toggles display.
    */
    void HandleMessage(const ecrInput::InputActionMessage* pMsg, efd::Category targetChannel);

    /**
        Handle entity discover and remove messages.

        Discovery adds the entity to any entity
        scatter plot, while removal causes the entity to be removed from the plot.
    */
    void HandleEntityMessage(const egf::EntityChangeMessage* pMsg, efd::Category);

protected:
    virtual efd::SyncResult OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar);

    /**
        Initializes the service, caching pointers to other services and subscribing to messages.

        The service will fail to initialize if the Message Service or Render Service are
        unavailable.

        Keyboard bindings to show the tracker will only be available if
        the Input Service has been created at the time this function is called. The
        input actions are added to the active action map at the time OnInit is called
        (see ecrInput::InputService).
    */
    virtual efd::AsyncResult OnInit();

    /// Updates the trackers with new data samples.
    virtual efd::AsyncResult OnTick();

    /// Frees resources used by the service.
    virtual efd::AsyncResult OnShutdown();

    /// Destructor
    virtual ~VisualTrackerService();

    virtual bool CreateVisualTrackers();

    // Functions for render surface delegates
    void OnSurfaceRemoved(ecr::RenderService* pService, ecr::RenderSurface* pSurface);
    void OnRenderServiceShutdown(ecr::RenderService* pService);

    /// Helper for changing visibility for all trackers on a given page
    void SetShowPage(efd::UInt32 pageNum, bool show);

    /// An extension of NiVisualTracker to add "update only when visible" support
    class VisualTracker : public NiVisualTracker
    {
    public:
        VisualTracker(
            const char* pName,
            NiRect<float> dataRange,
            NiRect<float> windowRect,
            efd::TimeType fSamplingRate,
            efd::UInt32 numDecimalPlaces,
            efd::Bool updateOnlyWhenVisible = false);

        efd::UInt32 AddGraph(
            const char* pGraphName,
            NiVisualTracker::GraphCallbackObject* pCallbackObject,
            const efd::Color& color,
            bool bShow = true);

        efd::UInt32 AddDataPoint(
            NiVisualTracker::DataPointCallbackObject* pCallbackObject,
            const efd::Color& color,
            efd::UInt32 symbol,
            bool bShow = true);

        // Override the Update method so that we can track entity removal
        virtual efd::UInt32 Update();

        // Increments the number to remove count, returns the new count
        efd::UInt32 IncrementNumToRemove();

        // Update rate to use for graphs added to this tracker
        efd::TimeType m_updateRate;

        // A count of entities we need to remove - we update until they are removed, regardless
        // of the visibility of the page.
        efd::UInt32 m_numToRemove;

        // For non-time series charts it make little sense to update them when they are not on the
        // current page.  This defaults to false.
        efd::Bool m_updateOnlyWhenVisible;
    };

    /// We support multiple pages of visualizers.  Each page is a render click added to our
    /// render step, but typically we only display one page at a time and all the other clicks
    /// are set to do nothing when rendered.
    efd::vector<NiVisualTrackerRenderClickPtr> m_pages;

    /// A boolean for whether or not we should be displaying trackers
    bool m_showTrackers;

    /// The page to display if we are currently showing trackers
    efd::UInt32 m_curPageIndex;

    /// If new pages are added at runtime this lets us know that we need to add their render clicks
    /// to our render step.
    efd::UInt32 m_nextClickToAdd;

    // Application control over visual tracker graph maximums
    float m_performanceMax;
    float m_memoryMax;
    float m_timeMax;

    ecr::RenderService* m_pRenderService;

    float m_frameRate;
    float m_lastTime;

    // Additional metrics
    unsigned int m_numObjectsDrawn;
    float m_frameTime;
    unsigned int m_numServices;
    efd::ClassID* m_serviceIDs;
    float* m_serviceTimings;
};

/// SmartPointer for reference counting the VisualTrackerService class
typedef efd::SmartPointer<VisualTrackerService> VisualTrackerServicePtr;

} // end namespace egmVisualTracker

#include "VisualTrackerService.inl"

#endif //EE_VISUALTRACKERSERVICE_H
