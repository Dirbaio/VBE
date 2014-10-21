#ifndef STARTINGCONFIG_HPP
#define STARTINGCONFIG_HPP


///
/// \brief The ContextSettings class
///
/// Contains the settings for the OpenGL context creation used when creating a Screen.
///
class ContextSettings {
	public:
		enum ContextFlag {
			DebugContext = 0x01,
			ForwardCompatibleContext = 0x02,
			RobustAccessContext = 0x04,
			RobustIsolationContext = 0x08,
		};

		enum ProfileMask {
			CoreProfile = 0x01,
			CompatibilityProfile = 0x02,
			ESProfile = 0x04,
		};

		unsigned int versionMajor;
		unsigned int versionMinor;
		unsigned int redBits;
		unsigned int greenBits;
		unsigned int blueBits;
		unsigned int alphaBits;
		unsigned int bufferBits;
		unsigned int depthBits;
		unsigned int stencilBits;
		unsigned int accumRedBits;
		unsigned int accumGreenBits;
		unsigned int accumBlueBits;
		unsigned int accumAlphaBits;
		unsigned int multisampleBuffers;
		unsigned int multisampleSamples;
		unsigned int contextFlags;
		ProfileMask profile;
		bool doubleBuffer;
		bool acceleratedGraphics;
		bool stereo;
		bool shareContext;
		bool requestSRGB;

		ContextSettings() :
#ifndef VBE_ES2
			versionMajor(4),
			versionMinor(2),
#else
			versionMajor(2),
			versionMinor(0),
#endif
			redBits(8),
			greenBits(8),
			blueBits(8),
			alphaBits(0),
			bufferBits(0),
			depthBits(16),
			stencilBits(0),
			accumRedBits(0),
			accumGreenBits(0),
			accumBlueBits(0),
			accumAlphaBits(0),
			multisampleBuffers(0),
			multisampleSamples(0),
			contextFlags(0),
#ifndef VBE_ES2
			profile(CoreProfile),
#else
			profile(ESProfile),
#endif
			doubleBuffer(true),
			acceleratedGraphics(true),
			stereo(false),
			shareContext(false),
			requestSRGB(false) {}
};

#endif // STARTINGCONFIG_HPP