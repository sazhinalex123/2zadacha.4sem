#include <cassert>
#include <algorithm>
#include "CRatVector.h"

CRationalNumber::CRationalNumber(int div, int den) {
	this->div = div;
	if (den != 0) {
		this->den = den;
	}
	else {
		this->den = 1;
	}
	normalize();
}

void CRationalNumber::normalize()
{
	for (int i = 2; i < den; i++) {
		while (div % i == 0 && den % i == 0) {
			div /= i;
			den /= i;
		}
	}
}

CRationalNumber& CRationalNumber::operator+=(const CRationalNumber& right) {
	div = div * right.den + right.div * den;
	den = den * right.den;
	normalize();
	return *this;
}

CRationalNumber CRationalNumber::operator+(const CRationalNumber& right) const {
	CRationalNumber a = *this;
	a += right;
	return a;
}

CRationalNumber& CRationalNumber::operator-=(const CRationalNumber& right) {
	div = div * right.den - right.div * den;
	den = den * right.den;
	normalize();
	return *this;
}

CRationalNumber CRationalNumber::operator-(const CRationalNumber& right) const {
	CRationalNumber a = *this;
	a -= right;
	return a;
}

CRationalNumber& CRationalNumber::operator*=(const CRationalNumber& right) {
	div *= right.div;
	den *= right.den;
	normalize();
	return *this;
}

CRationalNumber CRationalNumber::operator*(const CRationalNumber& right) const {
	CRationalNumber a = *this;
	a *= right;
	return a;
}

CRationalNumber& CRationalNumber::operator/=(const CRationalNumber& right) {
	div *= right.den;
	den *= right.div;
	normalize();
	return *this;
}

CRationalNumber CRationalNumber::operator/(const CRationalNumber& right) const {
	CRationalNumber a = *this;
	a /= right;
	return a;
}

CRatVector::CRatVector(int size) {
	this->vecsize = size;
	data.resize(size);
}

CRatVector::CRatVector(const CRatVector &other) {
	this->vecsize = other.vecsize;
	this->data.resize(vecsize);
	std::copy(other.data.begin(), other.data.end(), this->data.begin());
}

CRatVector::CRatVector(CRatVector &&other) noexcept {
	this->vecsize = other.vecsize;
	this->data = other.data;
	other.vecsize = 0;
	other.data.clear();
}

CRatVector::~CRatVector() {
	this->FileName.clear();
	this->data.clear();
}

int CRatVector::size() const {
	return this->vecsize;
}

CRatVector &CRatVector::operator=(const CRatVector &other) {
	if (&other != this) {
		this->data.clear();
		this->vecsize = other.vecsize;
		this->data.resize(vecsize);
		std::copy(other.data.begin(), other.data.end(), this->data.begin());
	}
	return *this;
}

CRatVector &CRatVector::operator=(CRatVector &&other) noexcept {
	if (&other != this) {
		this->data.clear();
		this->vecsize = other.vecsize;
		this->data = other.data;
		other.vecsize = 0;
		other.data.clear();
	}
	return *this;
}

CRationalNumber &CRatVector::operator[](int i) {
	assert(i >= 0 && i < vecsize);
	return this->data[i];
}

const CRationalNumber &CRatVector::operator[](int i) const {
	assert(i >= 0 && i < vecsize);
	return this->data[i];
}

CRatVector &CRatVector::operator+=(const CRatVector &right) {
	for (int i = 0; i < std::min(this->vecsize, right.vecsize); i++) {
		this->data[i] += right[i];
	}
	return *this;
}

CRatVector &CRatVector::operator-=(const CRatVector &right) {
	for (int i = 0; i < std::min(this->vecsize, right.vecsize); i++) {
		this->data[i] -= right[i];
	}
	return *this;
}

CRationalNumber operator*(const CRatVector &left, const CRatVector &right) {
	CRationalNumber num;
	for (int i = 0; i < std::min(left.size(), right.size()); i++) {
		num += left[i] * right[i];
	}
	return num;
}
