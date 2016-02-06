#ifndef CARROT_MATRIX_HPP
#define CARROT_MATRIX_HPP

#include <boost/multi_array.hpp>

namespace carrot
{

class matrix
{
public:
    virtual ~matrix() = default;
    virtual void set(long int row, long int column, char value) = 0;
};

class simple_matrix : public matrix
{
public:
    simple_matrix(long int rows_, long int columns_);
    virtual ~simple_matrix() = default;

    void set(long int row, long int column, char value) override;

    std::string to_string() const;

private:
    boost::multi_array<char, 2> data_;
};
}

#endif
