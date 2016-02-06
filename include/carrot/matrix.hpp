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

class simple_matrix final : public matrix
{
public:
    simple_matrix(long int rows_ = 0, long int columns_ = 0);
    virtual ~simple_matrix() = default;

    void set(long int row, long int column, char value) override;

    std::string to_string() const;

    void clear();
private:
    void resize_if_outside_matrix(long int row, long int column);

    boost::multi_array<char, 2> data_;
};
}

#endif
