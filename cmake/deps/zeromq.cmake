set(WITH_PERF_TOOL OFF)
set(ZMQ_BUILD_TESTS OFF)
FetchContent_Declare(
    zeromq
	# Use master HEAD instead...
	#URL https://github.com/zeromq/libzmq/releases/download/v${ZEROMQ_TAG_VERSION}/zeromq-${ZEROMQ_TAG_VERSION}.tar.gz
	URL https://github.com/zeromq/libzmq/archive/refs/heads/master.tar.gz
)
FetchContent_MakeAvailable(zeromq)
