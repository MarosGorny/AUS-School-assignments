#include "vector.h"
#include "../utils.h"
#include <cstdlib>
#include <cstring>

namespace structures
{
	Vector::Vector(size_t size) :
		memory_(std::calloc(size, 1)),	//vytvorenie pamati inicializacia na same 0 
		size_(size)
	{	
	}

	Vector::Vector(Vector& other) :
		Vector(other.size_)
	{
		//destination, z kade, velkost
		std::memcpy(this->memory_, other.memory_, this->size_);
	}

	Vector::~Vector()
	{
		free(this->memory_);
		this->memory_ = nullptr;
		this->size_ = 0;

	}

	size_t Vector::size()
	{
		return this->size_;
	}

	Structure& Vector::assign(Structure& other)
		//Struc& other ----> pracujeme s odkazom, teda s originalom
		//Netvori sa lokalna kopia objektu
	{
		//pretypovanie objektu, nova premenna mi nevznika
		Vector& otherVector = dynamic_cast<Vector&>(other);
		if (this != &other) {
			this->size_ = otherVector.size_;
			this->memory_ = std::realloc(this->memory_, this->size_);
			std::memcpy(this->memory_, otherVector.memory_, this->size_);
		}

		return *this;
	}

	bool Vector::equals(Structure& other)
	{
		//pretypovanie objektu, a vznika aj nova premenna, bola donho ulozena adresa
		Vector* otherVector = dynamic_cast<Vector*>(&other);
		if (otherVector == nullptr) {
			return false;
		}
		return this->size_ == otherVector->size_ &&
			std::memcmp(this->memory_, otherVector->memory_, this->size_) == 0;
	}

	byte& Vector::operator[](int index)
	{
		return at(index);
	}

	byte& Vector::at(int index)
	{
		return *this->getBytePointer(index);
	}

	void Vector::copy(Vector& src, int srcStartIndex, Vector& dest, int destStartIndex, int length)
	{
		if (length > 0) {
			if (srcStartIndex < 0 || srcStartIndex >= src.size()) {
				throw std::out_of_range(" Vector::copy: invalid srcStartIndex index.");
			}

			if (srcStartIndex + length < 0 || srcStartIndex + length - 1 >= src.size()) {
				throw std::out_of_range(" Vector::copy: invalid srcStartIndexindex + length - 1.");
			}

			if (destStartIndex < 0 || destStartIndex >= dest.size()) {
				throw std::out_of_range(" Vector::copy: invalid destStartIndex index.");
			}

			if (destStartIndex + length < 0 || destStartIndex + length - 1 >= dest.size()) {
				throw std::out_of_range(" Vector::copy: invalid destStartIndex + length - 1.");
			}
		}

		if (&src == &dest && 
			(srcStartIndex >= destStartIndex && srcStartIndex <= destStartIndex + length -1 ||
			destStartIndex >= srcStartIndex && destStartIndex <= srcStartIndex + length -1)) {
			std::memmove(dest.getBytePointer(destStartIndex), src.getBytePointer(srcStartIndex), length);
		}
		else {
			std::memcpy(dest.getBytePointer(destStartIndex), src.getBytePointer(srcStartIndex), length);
		}
		
	}

	byte* Vector::getBytePointer(int index)
	{
		if (index < 0 || index >= this->size_) {
			throw std::out_of_range("Vector::getBytePointer: invalid index.");
		}
		//Musim pretypovat, lebo neviem po akej velkosti mam skakat
		//Ak chcem pretypovat void pointer--> reinterperte
		return reinterpret_cast<byte*>(this->memory_) + index;
	}
}