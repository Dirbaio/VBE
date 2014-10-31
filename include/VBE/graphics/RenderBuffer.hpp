#ifndef RENDERBUFFER_HPP
#define RENDERBUFFER_HPP

#include <VBE/graphics/OpenGL.hpp>
#include <VBE/graphics/TextureFormat.hpp>

class RenderBuffer {
	public:
		RenderBuffer(vec2ui size, TextureFormat::Format format);
		~RenderBuffer();

		void resize(vec2ui size);
		vec2ui getSize() const;
		void bind() const;
		GLuint getHandle() const;
	private:
		vec2ui size;
		TextureFormat::Format format;
		GLuint handle;
};

#endif // RENDERBUFFER_HPP
