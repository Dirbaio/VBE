
#if defined(ANDROID)
	#define VBE_GLES2
	#define VBE_SYSTEM_ANDROID
#else
	#define VBE_SYSTEM_SDL2
#endif

#if defined(WINDOWS)
	#define VBE_SYSTEM_WINDOWS
#else
	#define VBE_SYSTEM_UNIX
#endif


#if not defined(NDEBUG) && not defined(QT_NO_DEBUG)
	#define VBE_DEBUG
#endif
