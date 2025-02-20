#pragma once

#include "RemoteType.h"
#include "pyextpublic.h"

#include <memory>

class ExtRemoteTyped;

namespace PyExt::Remote {

	class PyFrame;
	class PyFrameObject;
	class PyInterpreterFrame;

	/// Represents a PyInterpreterState instance in the debuggee's address space.
	/// @see https://github.com/python/cpython/blob/master/Include/pystate.h
	class PYEXT_PUBLIC PyThreadState : private RemoteType
	{
	public:
		explicit PyThreadState(const RemoteType& remoteType);
		~PyThreadState();

	public: // Members of the remote type.
		auto next() const -> std::unique_ptr<PyThreadState>;
		auto currentFrame() const -> std::unique_ptr<PyFrame>;
		auto tracing() const -> long;
		auto thread_id() const -> long;

	public: // Utility functions around the members.
		/// Returns a range of all the frames in this threadState.
		auto allFrames() const -> std::vector<std::shared_ptr<PyFrame>>; //< TODO: Return generator<PyFrame>
	};

}
