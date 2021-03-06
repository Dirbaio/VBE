#include <fstream>

#include <VBE/system/sdl2/StorageImpl.hpp>
#include <VBE/system/Log.hpp>

// static
std::unique_ptr<std::istream> StorageImpl::openAsset(const std::string& filename) {
	// Open in binary mode so Windows doesn't change LF to CRLF,
	// which will corrupt binary files such as images.
	std::ifstream* stream = new std::ifstream("assets/"+filename, std::ios::binary);

	VBE_ASSERT(stream->good(), "Could not open asset: "+filename);
	return std::unique_ptr<std::istream>(stream);
}
