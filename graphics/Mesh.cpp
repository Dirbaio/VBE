#include "Mesh.hpp"

Mesh::Mesh(const Vertex::Format& vertexFormat, unsigned int vertexCount, bool dynamic)
	: vertexFormat(vertexFormat), vertexCount(vertexCount), vertexBuffer(0), primitiveType(TRIANGLES),
	  dynamic(dynamic) {
	GLuint vbo;
	glGenBuffers(1, &vbo);
	if (glGetError()){
		outLog("Failed to create VBO for mesh");
	}

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	if (glGetError()) {
		outLog("Failed to bind VBO for mesh");
		glDeleteBuffers(1, &vbo);
	}

	glBufferData(GL_ARRAY_BUFFER, vertexFormat.vertexSize() * vertexCount, NULL, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
	if (glGetError()) {
		outLog("Failed to load VBO with vertex data");
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &vbo);
		return;
	}
	vertexBuffer = vbo;
}

const Vertex::Format& Mesh::getVertexFormat() const {
	return vertexFormat;
}

unsigned int Mesh::getVertexCount() const {
	return vertexCount;
}

unsigned int Mesh::getVertexSize() const {
	return vertexFormat.vertexSize();
}

bool Mesh::isDynamic() const {
	return dynamic;
}

GLuint Mesh::getVertexBuffer() const {
	return vertexBuffer;
}

Mesh::PrimitiveType Mesh::getPrimitiveType() const {
	return primitiveType;
}

void Mesh::setPrimitiveType(Mesh::PrimitiveType type) {
	primitiveType = type;
}

void Mesh::setVertexData(void* vertexData, unsigned int newVertexCount) {
	vertexCount = newVertexCount;
	GLint oldbuff;
	glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &oldbuff);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexFormat.vertexSize() * vertexCount, vertexData, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, oldbuff);
}
