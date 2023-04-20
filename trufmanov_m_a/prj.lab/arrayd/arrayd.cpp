#include <arrayd/arrayd.hpp>

#include <stdexcept>
#include <cstring>


ArrayD::ArrayD(const std::ptrdiff_t size)
    : ssize_(size)
{
    if (size < 0) {
        throw std::invalid_argument("size must be more 0");
    }
    else {
        ArrayD::resize(size);
    }
}

ArrayD::ArrayD(const ArrayD& lhs) {
    ssize_ = lhs.ssize_;
    caparcity = lhs.caparcity;

    if (caparcity > 0) {
        data_ = new double[caparcity];
        for (std::ptrdiff_t i = 0; i < ssize_; ++i) {
            data_[i] = lhs.data_[i];
        }

    }
    else {
        data_ = nullptr;
    }
}

ArrayD::~ArrayD() {
    delete data_;
}


void ArrayD::insert(const std::ptrdiff_t index, const double value) {
    if (index < 0 || index > ssize_) {
        throw std::invalid_argument("index out of range (insert)");
    }

    if (ssize_ == caparcity) {
        resize(ssize_ + 1);
    }

    if (ssize_ == 0) {
        data_[0] = value;
    }
    else {

        for (std::ptrdiff_t i = ssize_; i > index; i--) {
            data_[i] = data_[i - 1];
        }

        data_[index] = value;
    }
    ssize_ += 1;
}

void ArrayD::resize(const std::ptrdiff_t new_size) {
    if (new_size < 0) {
        throw std::invalid_argument("index out of range (resize)");
    }
    if (new_size <= ssize_) {
        ssize_ = new_size;
        return;
    }

    if (new_size > ssize_) {
        double* new_data = new double[new_size]();
        if (data_ != nullptr) {
            auto copy_size = std::min(ssize_, new_size) * sizeof(double);
            std::memcpy(new_data, data_, copy_size);
            delete[] data_;
        }

        delete[] data_;
        data_ = new_data;
        //delete[] new_data;
        ssize_ = new_size;
        caparcity = new_size * 2;
        return;

    }

    if (new_size <= caparcity) {
        ssize_ = new_size;

    }



}

void ArrayD::remove(const std::ptrdiff_t i) {
    if (ssize_ == 0) {
        return;
    }
    if (i < 0 || i >= ssize_) {
        throw std::invalid_argument("Index out of range");
    }
    for (ptrdiff_t j = i; j < ssize_ - 1; ++j) {
        data_[j] = data_[j + 1];
    }
    ssize_--;
}


double& ArrayD::operator[](const std::ptrdiff_t indx) {
    if (indx < 0 || indx >= ssize_) {
        throw std::invalid_argument("index must be in size range");
    }
    return data_[indx];
}

const double& ArrayD::operator[](const std::ptrdiff_t indx) const {
    if (indx < 0 || indx >= ssize_) {
        throw std::invalid_argument("index must be in size range");
    }
    return data_[indx];
}

ArrayD& ArrayD::operator=(const ArrayD& other) {
    if (this != &other) {
        delete[] data_;
        data_ = nullptr;
        ssize_ = 0;
        caparcity = 0;

        if (other.caparcity > 0) {
            data_ = new double[other.caparcity];
            caparcity = other.caparcity;
            for (std::ptrdiff_t i = 0; i < other.ssize_; ++i) {
                data_[i] = other.data_[i];
            }
        }
        ssize_ = other.ssize_;
    }
    return *this;
}


std::ptrdiff_t ArrayD::ssize() const noexcept {
    return ssize_;
}


