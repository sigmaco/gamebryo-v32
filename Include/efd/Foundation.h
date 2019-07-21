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
#ifndef EE_FOUNDATION_H
#define EE_FOUNDATION_H

/*
    All headers for the Foundation library are included here.

    This header file should be used in the Precompiled Header files of other projects that used
    the foundation library.

    This header file should NOT be used in any Foundation level header or source file.

    This header is NOT recommended for use in ANY header file other than Precompiled Headers.
    Including this header is typically extreme overkill and will slow down compile times noticeably
    when used outside of the context of a precompiled header file.
*/

#include <efd/Archive.h>
#include <efd/AssertDialog.h>
#include <efd/Asserts.h>
#include <efd/AssetFactoryManager.h>
#include <efd/AssetLoaderThreadFunctor.h>
#include <efd/AssetLoadRequest.h>
#include <efd/AssetLoadResponse.h>
#include <efd/AssetLocatorService.h>
#include <efd/AtomicOperations.h>
#include <efd/BinaryLoadSave.h>
#include <efd/BinaryStream.h>
#include <efd/BinaryStreamMacro.h>
#include <efd/BitUtils.h>
#include <efd/Category.h>
#include <efd/ClassIDHelpers.h>
#include <efd/ClassInfo.h>
#include <efd/Color.h>
#include <efd/ConfigManager.h>
#include <efd/ConfigSection.h>
#include <efd/ConfigSource.h>
#include <efd/ConnectionID.h>

#ifndef __SPU__
#include <efd/CriticalSection.h>
#endif

#include <efd/customalloc.h>
#include <efd/DataStream.h>
#include <efd/DataStreamUtils.h>
#include <efd/DebugOutDestination.h>
#include <efd/DefaultInitializeMemoryLogHandler.h>
#include <efd/DefaultInitializeMemoryManager.h>
#include <efd/DynamicModule.h>
#include <efd/EEBasicString.h>
#include <efd/EEHelpers.h>
#include <efd/EEMath.h>
#include <efd/efdLibType.h>
#include <efd/efdLogIDs.h>
#include <efd/efdMessageIDs.h>
#include <efd/Endian.h>
#include <efd/ExternalMemAllocator.h>
#include <efd/File.h>
#include <efd/FileDestination.h>
#include <efd/FixedNodePool.h>
#include <efd/FixedSizeAllocator.h>
#include <efd/FixedString.h>
#include <efd/Float16.h>
#include <efd/FoundationSDM.h>
#include <efd/GenericFactory.h>
#include <efd/GlobalStringTable.h>
#include <efd/Helpers.h>
#include <efd/IAllocator.h>
#include <efd/IBase.h>
#include <efd/IConfigManager.h>
#include <efd/IConfigSection.h>
#include <efd/IConfigSource.h>
#include <efd/ID128.h>
#include <efd/IDs.h>
#include <efd/ILogDestination.h>
#include <efd/ILogger.h>
#include <efd/IMemLogHandler.h>
#include <efd/IMessage.h>
#include <efd/IntrusiveLockFreeStack.h>
#include <efd/LockFreeQueue.h>
#include <efd/LockFreeStack.h>
#include <efd/MessageHandlerBase.h>
#include <efd/INetCallback.h>
#include <efd/INetListener.h>
#include <efd/INetService.h>
#include <efd/InitOptions.h>
#include <efd/IStreamable.h>
#include <efd/ISystemService.h>
#include <efd/IUtilities.h>
#include <efd/Logger.h>
#include <efd/ecrLogIDs.h>
#include <efd/LoopedThread.h>
#include <efd/LoopedThreadProcedure.h>
#include <efd/Matrix3.h>
#include <efd/MemHint.h>
#include <efd/MemManager.h>
#include <efd/MemObject.h>
#include <efd/MemoryDefines.h>
#include <efd/MemTracker.h>
#include <efd/MessageFactory.h>
#include <efd/MessageService.h>
#include <efd/Metrics.h>
#include <efd/NetEnums.h>
#include <efd/NetMessage.h>
#include <efd/OrderedMap.h>
#include <efd/OS.h>
#include <efd/ParseHelper.h>
#include <efd/PathUtils.h>
#include <efd/Point2.h>
#include <efd/Point3.h>
#include <efd/Point4.h>
#include <efd/PrintDestination.h>
#include <efd/ProcessorAffinity.h>
#include <efd/Quaternion.h>
#include <efd/RefCount.h>
#include <efd/ReferenceCounting.h>
#include <efd/RTLib.h>
#include <efd/SDMMacros.h>
#include <efd/Semaphore.h>
#include <efd/SerializeRoutines.h>
#include <efd/SequenceNumber.h>
#include <efd/ServiceDiscoveryMessage.h>
#include <efd/ServiceManager.h>
#include <efd/SmallObjectAllocator.h>
#include <efd/SmartBuffer.h>
#include <efd/SmartPointer.h>
#include <efd/StandardAllocator.h>
#include <efd/StaticDataManager.h>
#include <efd/StdContainers.h>
#include <efd/StreamInfo.h>
#include <efd/StreamMessage.h>
#include <efd/String.h>
#include <efd/StringConverters.h>
#include <efd/StringUtilities.h>
#include <efd/SystemDesc.h>
#include <efd/SystemFrameworkEnums.h>
#include <efd/SystemLogger.h>
#include <efd/SystemUniqueIndex.h>
#include <efd/TemplateHelpers.h>
#include <efd/Thread.h>
#include <efd/ThreadFunctor.h>
#include <efd/ThreadLocal.h>
#include <efd/TimeType.h>
//#include <efd/TinyXML.h> // Avoid ripple of Include paths
#include <efd/UniversalID.h>
#include <efd/UniversalTypes.h>
#include <efd/utf8char.h>
#include <efd/utf8string.h>
#include <efd/utf8string_iterator.h>
#include <efd/Utilities.h>
//#include <efd/XMLMemLogHandler.h>


#ifndef __SPU__
#include <efd/CriticalSection.h>
#endif

#endif // EE_FOUNDATION_H

