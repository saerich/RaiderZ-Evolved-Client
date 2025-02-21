/*
* Copyright 2010 Autodesk, Inc.  All rights reserved.
* Use of this software is subject to the terms of the Autodesk license agreement provided at the time of installation or download, 
* or which otherwise accompanies this software in either electronic or hard copy form.
*/

	


/*!	\file 
	\ingroup kyruntime_debugger */

// primary contact: ? - secondary contact: NOBODY
#ifndef KYDEBUGGERSHAREDLOG_H
#define KYDEBUGGERSHAREDLOG_H

#include <kypathdata/generic/basetypes.h>
#include <kypathdata/generic/memory.h>
#include <kypathdata/containers/kystring.h>

namespace Kaim
{
	namespace Debugger
	{
		namespace Shared
		{
			/*!	This structure stores a list of text messages. The RemoteDebugging service uses an instance
				of this structure to store a list of debug messages, including all debug messages generated by
				\SDKName components. This list is sent at each frame to the visual %Debugger interface.
				\ingroup kyruntime_debugger */
			struct Log
			{
				typedef char ValueType;
				typedef KyInt32 SizeType;
				typedef KyString BufferType;

				/*!	Sets up the Log for initial use. For internal use. */
				void Initialize()
				{
					Clear();
				}

				/*!	Adds a new message to the Log.
					\param buffer			A pointer to a memory buffer that contains your message.
					\param size				The size of the memory buffer. */
				void Write(const ValueType* buffer, const SizeType size)
				{
					static bool guard = false;
					if (guard == false)
					{
						guard = true;
						m_buffer.Append(buffer, size);
						guard = false;
					}
				}

				/*!	Empties all messages from the Log. */
				void Clear()
				{
					m_buffer.Clear();
				}

				/*!	Destroys the log when no longer needed. For internal use. */
				void Terminate()
				{
					m_buffer.Terminate();
				}

				/*!	Retrieves a buffer that contains all messages added to the Log
					since the last time it was cleared. For internal use. */
				const BufferType& Buffer() const
				{
					return m_buffer;
				}

			protected:
				BufferType m_buffer;
			};

			/*!	Adds the specified string to the Log. \ingroup kyruntime_debugger */
			Kaim::Debugger::Shared::Log& operator<<(Kaim::Debugger::Shared::Log& buffer, const char* value);
		}
	}
}


#endif // KYDEBUGGERSHAREDLOG_H
