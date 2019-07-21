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
%warnfilter(389) operator[];
%warnfilter(362) operator=;
%warnfilter(383) operator++;
%warnfilter(384) operator--;
%warnfilter(361) operator!;
%warnfilter(401) ClassDesc; //Warning(401): Nothing known about base class 'MemObject'. Ignored.
%warnfilter(401) IBase; //Warning(401): Nothing known about base class 'MemObject'. Ignored.
%warnfilter(401) StreamInfo; //Warning(401): Nothing known about base class 'MemObject'. Ignored.
%warnfilter(401) DataStream; //Warning(401): Nothing known about base class 'MemObject'. Ignored.
%warnfilter(401) ClassInfo; //Warning(401): Nothing known about base class 'MemObject'. Ignored.

%warnfilter(401) efd::Point2;  //Warning(401): Nothing known about base class 'MemObject'. Ignored.
%warnfilter(401) efd::Point3;
%warnfilter(401) efd::list;
%warnfilter(401) efd::map;
%warnfilter(401) efd::Color;
%warnfilter(401) efd::ColorA;
%warnfilter(401) efd::ColorA_UInt8;
%warnfilter(401) efd::Matrix3;
%warnfilter(401) efd::utf8string;
%warnfilter(401) efd::Quaternion;
