#include <VBE/config.hpp>
#include <VBE/graphics/Mesh.hpp>
#include <VBE/graphics/OpenGL.hpp>
#include <VBE/graphics/ShaderBinding.hpp>
#include <VBE/graphics/ShaderProgram.hpp>
#include <VBE/system/Log.hpp>

#ifdef SHADERBINDING_USE_VAO
#endif

ShaderBinding::ShaderBinding(const ShaderProgram* program, const Mesh* mesh) :
		program(program), mesh(mesh) {
	VBE_DLOG("* New shaderbinding between program with pointer " << program << " and mesh with pointer " << mesh );
#ifdef SHADERBINDING_USE_VAO
	GL_ASSERT(glGenVertexArrays(1, &vertexArrayObject));
	GL_ASSERT(glBindVertexArray(vertexArrayObject));
	enableAttributes();
#endif
}

ShaderBinding::~ShaderBinding() {
#ifdef SHADERBINDING_USE_VAO
	GL_ASSERT(glDeleteVertexArrays(1, &vertexArrayObject));
#endif
}

const ShaderBinding* ShaderBinding::currentBind = nullptr;

void ShaderBinding::bind(const ShaderBinding* binding) {
	if(binding == currentBind) return;

#ifdef SHADERBINDING_USE_VAO
	if(binding != nullptr)
		GL_ASSERT(glBindVertexArray(binding->vertexArrayObject));
	else
		GL_ASSERT(glBindVertexArray(0));
#else
	if(currentBind != nullptr)
		currentBind->disableAttributes();
	if(bind != nullptr)
		currentBind->enableAttributes();
#endif
	currentBind = binding;
}


void ShaderBinding::enableAttributes() const {
	VBE_ASSERT(mesh->getVertexBuffer() != 0, "mesh vertex buffer is null");
	GL_ASSERT(glBindBuffer(GL_ARRAY_BUFFER, mesh->getVertexBuffer()));
	if(mesh->isIndexed()) {
		VBE_ASSERT(mesh->getIndexBuffer() != 0, "mesh index buffer is null");
		GL_ASSERT(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->getIndexBuffer()));
	}

	const Vertex::Format format = mesh->getVertexFormat();
	for(std::map<std::string, GLint>::const_iterator it = program->attributes.begin(); it != program->attributes.end(); ++it) {
		for(unsigned int i = 0; i < format.elementCount(); ++i) {
			const Vertex::Element* current = &format.element(i);
			if(current->attr.hasName(it->first)) {
				GL_ASSERT(glEnableVertexAttribArray(it->second));
#ifndef VBE_GLES2
                if(current->conv == Vertex::Element::ConvertToInt)
                    GL_ASSERT(glVertexAttribIPointer(it->second,
                                                     current->size,
                                                     current->type,
                                                     format.vertexSize(),
                                                     (GLvoid*)long(format.offset(i))));
                else
#endif
					GL_ASSERT(glVertexAttribPointer(it->second,
													current->size,
													current->type, current->conv == Vertex::Element::ConvertToFloatNormalized ? GL_TRUE : GL_FALSE,
													format.vertexSize(),
													(GLvoid*)long(format.offset(i))));
			}
		}
	}
}

void ShaderBinding::disableAttributes() const {
	const Vertex::Format format = mesh->getVertexFormat();
	for(std::map<std::string, GLint>::const_iterator it = program->attributes.begin(); it != program->attributes.end(); ++it) {
		for(unsigned int i = 0; i < format.elementCount(); ++i) {
			const Vertex::Element* current = &format.element(i);
			if(current->attr.hasName(it->first)) {
				GL_ASSERT(glDisableVertexAttribArray(it->second));
			}
		}
	}
}