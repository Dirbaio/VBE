#ifndef OBJLOADER_HPP
#define OBJLOADER_HPP

#include <string>
#include <iostream>

#include <VBE/graphics/MeshSeparate.hpp>

class OBJLoader {
	public:
		static MeshSeparate* loadFromOBJStandard(std::unique_ptr<std::istream> in, Mesh::BufferType bufferType);
		static MeshSeparate* loadFromOBJTangents(std::unique_ptr<std::istream> in, Mesh::BufferType bufferType);
	private:
		OBJLoader();
		~OBJLoader();
};

#endif //OBJLOADER_HPP
