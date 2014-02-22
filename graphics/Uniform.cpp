#include "Uniform.hpp"
#include "Texture2D.hpp"
#include "Texture3D.hpp"
#include "Texture2DArray.hpp"

Uniform::Uniform(unsigned int count, GLenum type, GLint location) :
	dirty(true), count(count), type(type), location(location) {
	unsigned int size = 0;
	switch(type) {
		case GL_FLOAT:
			size = sizeof(GLfloat);
			break;
		case GL_FLOAT_VEC2:
			size = sizeof(GLfloat)*2;
			break;
		case GL_FLOAT_VEC3:
			size = sizeof(GLfloat)*3;
			break;
		case GL_FLOAT_VEC4:
			size = sizeof(GLfloat)*4;
			break;
		case GL_FLOAT_MAT3:
			size = sizeof(GLfloat)*12;
			break;
		case GL_FLOAT_MAT4:
			size = sizeof(GLfloat)*16;
			break;
		case GL_BOOL:
			size = sizeof(GLint);
			break;
		case GL_INT:
			size = sizeof(GLint);
			break;
		case GL_SAMPLER_2D:
		case GL_SAMPLER_2D_ARRAY:
		case GL_SAMPLER_2D_SHADOW:
		case GL_SAMPLER_3D:
			size = sizeof(GLint);
			break;
		default:
			VBE_ASSERT(false, "Unrecognised uniform type " << type); break;
	}
	size *= count;
	lastValue = std::vector<char>(size, 0);
}

Uniform::~Uniform() {
}

void Uniform::set(int val) {
	VBE_ASSERT(type == GL_INT || type == GL_BOOL || type == GL_SAMPLER_2D, "Wrong uniform type. Location " << this->location);
	setBytes((char*)&val);
}
void Uniform::set(const std::vector<int> &val) {
	VBE_ASSERT(type == GL_INT || type == GL_BOOL || type == GL_SAMPLER_2D, "Wrong uniform type. Location " << this->location);
	VBE_ASSERT(val.size() == count, "Wrong vector size. Location " << this->location);
	setBytes((char*)&val[0]);
}

void Uniform::set(bool val) {
	VBE_ASSERT(type == GL_BOOL, "Wrong uniform type. Location " << this->location);
	setBytes((char*)&val);
}

void Uniform::set(float val) {
	VBE_ASSERT(type == GL_FLOAT, "Wrong uniform type. Location " << this->location);
	setBytes((char*)&val);
}
void Uniform::set(const std::vector<float> &val) {
	VBE_ASSERT(type == GL_FLOAT, "Wrong uniform type. Location " << this->location);
	VBE_ASSERT(val.size() == count, "Wrong vector size. Location " << this->location);
	setBytes((char*)&val[0]);
}

void Uniform::set(const vec2f &val) {
	VBE_ASSERT(type == GL_FLOAT_VEC2, "Wrong uniform type. Location " << this->location);
	setBytes((char*)&val[0]);
}
void Uniform::set(const std::vector<vec2f> &val) {
	VBE_ASSERT(type == GL_FLOAT_VEC2, "Wrong uniform type. Location " << this->location);
	VBE_ASSERT(val.size() == count, "Wrong vector size. Location " << this->location);
	setBytes((char*)&val[0][0]);
}

void Uniform::set(const vec3f &val) {
	VBE_ASSERT(type == GL_FLOAT_VEC3, "Wrong uniform type. Location " << this->location);
	setBytes((char*)&val[0]);
}
void Uniform::set(const std::vector<vec3f> &val) {
	VBE_ASSERT(type == GL_FLOAT_VEC3, "Wrong uniform type. Location " << this->location);
	VBE_ASSERT(val.size() == count, "Wrong vector size. Location " << this->location);
	setBytes((char*)&val[0][0]);
}

void Uniform::set(const vec4f &val) {
	VBE_ASSERT(type == GL_FLOAT_VEC4, "Wrong uniform type. Location " << this->location);
	setBytes((char*)&val[0]);
}
void Uniform::set(const std::vector<vec4f> &val) {
	VBE_ASSERT(type == GL_FLOAT_VEC4, "Wrong uniform type. Location " << this->location);
	VBE_ASSERT(val.size() == count, "Wrong vector size. Location " << this->location);
	setBytes((char*)&val[0][0]);
}

void Uniform::set(const mat3f &val) {
	VBE_ASSERT(type == GL_FLOAT_MAT3, "Wrong uniform type. Location " << this->location);
	setBytes((char*)&val[0][0]);
}
void Uniform::set(const std::vector<mat3f> &val) {
	VBE_ASSERT(type == GL_FLOAT_MAT3, "Wrong uniform type. Location " << this->location);
	VBE_ASSERT(val.size() == count, "Wrong vector size. Location " << this->location);
	setBytes((char*)&val[0][0][0]);
}

void Uniform::set(const mat4f &val) {
	VBE_ASSERT(type == GL_FLOAT_MAT4, "Wrong uniform type. Location " << this->location);
	setBytes((char*)&val[0][0]);
}
void Uniform::set(const std::vector<mat4f> &val) {
	VBE_ASSERT(type == GL_FLOAT_MAT4, "Wrong uniform type. Location " << this->location);
	VBE_ASSERT(val.size() == count, "Wrong vector size. Location " << this->location);
	setBytes((char*)&val[0][0][0]);
}

void Uniform::set(const Texture2D* val) {
	VBE_ASSERT(type == GL_SAMPLER_2D || type == GL_SAMPLER_2D_SHADOW, "Wrong uniform type. Location " << this->location);
	val->bind();
	unsigned int slot = val->getSlot();
	setBytes((char*)&slot);
}

void Uniform::set(const Texture3D* val) {
	VBE_ASSERT(type == GL_SAMPLER_3D, "Wrong uniform type. Location " << this->location);
	val->bind();
	unsigned int slot = val->getSlot();
	setBytes((char*)&slot);
}

void Uniform::set(const Texture2DArray* val) {
	VBE_ASSERT(type == GL_SAMPLER_2D_ARRAY, "Wrong uniform type. Location " << this->location);
	val->bind();
	unsigned int slot = val->getSlot();
	setBytes((char*)&slot);
}

void Uniform::ready() { //assumes program is binded already. Only to be called by ShaderProgram
	if(!dirty) return;
	dirty = false;
	switch(type) {
		case GL_FLOAT:		GL_ASSERT(glUniform1fv(location, count, (GLfloat*)&lastValue[0]), "Failed to send uniform to GPU"); break;
		case GL_FLOAT_VEC2:	GL_ASSERT(glUniform2fv(location, count, (GLfloat*)&lastValue[0]), "Failed to send uniform to GPU"); break;
		case GL_FLOAT_VEC3:	GL_ASSERT(glUniform3fv(location, count, (GLfloat*)&lastValue[0]), "Failed to send uniform to GPU"); break;
		case GL_FLOAT_VEC4:	GL_ASSERT(glUniform4fv(location, count, (GLfloat*)&lastValue[0]), "Failed to send uniform to GPU"); break;
		case GL_FLOAT_MAT3:	GL_ASSERT(glUniformMatrix3fv(location, count, GL_FALSE, (GLfloat*)&lastValue[0]), "Failed to send uniform to GPU"); break;
		case GL_FLOAT_MAT4:	GL_ASSERT(glUniformMatrix4fv(location, count, GL_FALSE, (GLfloat*)&lastValue[0]), "Failed to send uniform to GPU"); break;
		case GL_BOOL:
		case GL_INT:
		case GL_SAMPLER_2D_ARRAY:
		case GL_SAMPLER_2D_SHADOW:
		case GL_SAMPLER_3D:
		case GL_SAMPLER_2D:	GL_ASSERT(glUniform1iv(location, count, (GLint*)&lastValue[0]), "Failed to send uniform to GPU"); break;
		default:
			VBE_ASSERT(false, "Unrecognised uniform type " << type);
			break;
	}
}

void Uniform::setBytes(const char *val) {
	if(!compare(val)) {
		for(unsigned int i = 0; i < lastValue.size(); ++i)
			lastValue[i] = val[i];
		dirty = true;
	}
}

bool Uniform::compare(const char *val) const {
	for(unsigned int i = 0; i < lastValue.size(); ++i)
		if(lastValue[i] != val[i])
			return false;
	return true;
}

void Uniform::log() {
	VBE_DLOG("    Item count: "		 << count);
	VBE_DLOG("    Location: " << location);
	VBE_DLOG("    Size: " << lastValue.size()/count << " bytes per item");
	std::string s;
	switch(type) {
		case GL_FLOAT: s = "GL_FLOAT"; break;
		case GL_FLOAT_VEC2: s = "GL_FLOAT_VEC2"; break;
		case GL_FLOAT_VEC3: s = "GL_FLOAT_VEC3"; break;
		case GL_FLOAT_VEC4: s = "GL_FLOAT_VEC4"; break;
		case GL_FLOAT_MAT3: s = "GL_FLOAT_MAT3"; break;
		case GL_FLOAT_MAT4: s = "GL_FLOAT_MAT4"; break;
		case GL_BOOL:		s = "GL_BOOL"; break;
		case GL_INT:		s = "GL_INT"; break;
		case GL_SAMPLER_2D: s = "GL_SAMPLER_2D"; break;
		case GL_SAMPLER_2D_SHADOW: s = "GL_SAMPLER_2D_SHADOW"; break;
		case GL_SAMPLER_2D_ARRAY: s = "GL_SAMPLER_2D_ARRAY"; break;
		case GL_SAMPLER_3D: s = "GL_SAMPLER_3D"; break;
		default: s = "UNKNOWN_TYPE"; break;
	}
	VBE_DLOG("    Type: " << s);
}
