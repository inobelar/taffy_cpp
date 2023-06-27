#pragma once

#include <vector> // for: std::vector<T>

#include <taffy/support/rust_utils/Option.hpp>

#include <cassert> // for: assert()

namespace taffy {

/// Stores elements of a certain type in a 2D grid structure.
///
/// Uses a rust `Vec<T>` type to reference the grid data on the heap.
/// Also the number of rows and columns are stored in the grid data structure.
///
/// The size limit of a grid is `rows * cols < usize`.
///
/// The grid data is stored in a row-major memory layout.
/* RUST
    pub struct Grid<T>
*/
template <typename T>
class Grid
{
    std::vector<T> _data;
    size_t _cols;
    size_t _rows;

public:

    Grid(const std::vector<T>& data_,
        size_t cols_,
        size_t rows_
    )
        : _data(data_)
        , _cols(cols_)
        , _rows(rows_)
    {}

    static Grid New(size_t rows, size_t cols)
    {
        if( rows == 0 || cols == 0 ) {
            return Grid { std::vector<T>{}, 0, 0 };
        }

        auto data = std::vector<T>{};
        data.resize(rows * cols, T{}); // TODO: checked_mul here
        return Grid{ data, cols, rows };
    }
    Grid(size_t rows, size_t cols)
        : Grid{ New(rows, cols) }
    {}

    static Grid from_vec(const std::vector<T>& vec, size_t cols)
    {
        const auto rows = (cols == 0) ? 0 : (vec.size() / cols); // Additional check to imitate: `vec.len().checked_div(cols).unwrap_or(0);` here
        assert(
            (rows * cols) == vec.size() &&
            "Vector length should be a multiple of cols"
        );
        if( rows == 0 || cols == 0 ) {
            return Grid{ vec, 0, 0 };
        } else {
            return Grid{ vec, cols, rows };
        }
    }

    constexpr T const& get_unchecked(size_t row, size_t col) const
    {
        return _data[row * this->_cols + col];
    }

    inline T& get_unchecked_mut(size_t row, size_t col)
    {
        return _data[row * this->_cols + col];
    }

    inline Option< std::reference_wrapper<T const> > get(size_t row, size_t col) const
    {
        return
            (row < this->_rows && col < this->_cols) ?
                Some(std::cref(this->get_unchecked(row, col)))
            :
                None;
    }

    inline Option< std::reference_wrapper<T> > get_mut(size_t row, size_t col)
    {
        return
            (row < this->_rows && col < this->_cols) ?
                Some(std::ref(this->get_unchecked_mut(row, col)))
            :
                None;
    }

    constexpr size_t rows() const
    {
        return this->_rows;
    }

    constexpr size_t cols() const
    {
        return this->_cols;
    }

    // Rust::Iter'-less shortcut for `.iter_row(row_index).any( ... )`
    template <typename F>
    bool iter_row_any(size_t row_index, F&& f) const
    {
        assert(row_index < this->_rows);

        // TODO: This must be tested carefully, is it correct ?
        for(size_t col_index = 0; col_index < this->_cols; ++col_index) {
            if( f( get_unchecked(row_index, col_index) ) ) {
                return true;
            }
        }

        return false;
    }

    // Rust::Iter'-less shortcut for `.iter_col(column_index).any( ... )`
    template <typename F>
    bool iter_col_any(size_t column_index, F&& f) const
    {
        assert(column_index < this->_cols);

        // TODO: This must be tested carefully, is it correct ?
        for(size_t row_index = 0; row_index < this->_rows; ++row_index) {
            if( f( get_unchecked(row_index, column_index) ) ) {
                return true;
            }
        }

        return false;
    }

    // Rust::Iter'-less shortcut for `.iter_row(row_index).rposition( ... )`
    template <typename F>
    Option<size_t> iter_row_rposition(size_t row_index, F&& f) const
    {
        assert(row_index < this->_rows);

        if(this->_cols == 0) {
            return None;
        }

        // TODO: This must be tested carefully, is it correct ?
        /* NOTE
            Instead of writing:

                for(size_t col_index = (this->_cols-1); col_index >= 0; --col_index)

            which produces the next warning:

                warning: comparison of unsigned expression in ‘>= 0’ is always true [-Wtype-limits]

            here is used alternate 'idiomatic' way: https://stackoverflow.com/a/41076051/
        */
        for(size_t col_index = this->_cols; col_index-- > 0;) {
            if( f( get_unchecked(row_index, col_index) ) ) {
                return Option<size_t>{col_index};
            }
        }

        return None;
    }

    // Rust::Iter'-less shortcut for `.iter_col(column_index).rposition( ... )`
    template <typename F>
    Option<size_t> iter_col_rposition(size_t column_index, F&& f) const
    {
        assert(column_index < this->_cols);

        if(this->_rows == 0) {
            return None;
        }

        // TODO: This must be tested carefully, is it correct ?
        /* NOTE
            Instead of writing:

                for(size_t row_index = (this->_rows-1); row_index >= 0; --row_index)

            which produces the next warning:

                warning: comparison of unsigned expression in ‘>= 0’ is always true [-Wtype-limits]

            here is used alternate 'idiomatic' way: https://stackoverflow.com/a/41076051/
        */
        for(size_t row_index = this->_rows; row_index-- > 0;) {
            if( f( get_unchecked(row_index, column_index) ) ) {
                return Option<size_t>(row_index);
            }
        }

        return None;
    }
};

} // namespace taffy
