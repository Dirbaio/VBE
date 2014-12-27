#include <VBE/config.hpp>

//OpenGL (Open Graphics Library)
#if defined(VBE_GLES2)
	#include "GLES2/gl2.h"
#else
	#define GLEW_STATIC
	#include "GL/glew.h"
#endif
