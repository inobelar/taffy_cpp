#pragma once

#include <taffy/compute/grid/types/cell_occupancy/Grid.hpp>
#include <taffy/compute/grid/types/cell_occupancy/CellOccupancyState.hpp>
#include <taffy/compute/grid/types/grid_track_counts/TrackCounts.hpp>
#include <taffy/compute/grid/types/coordinates/OriginZeroLine.hpp>

#include <taffy/geometry/AbsoluteAxis.hpp>

#include <taffy/support/rust_utils/Option.hpp>
#include <taffy/support/rust_utils/Range.hpp>
#include <taffy/support/rust_utils/utils.hpp> // for: min(), max()

#include <taffy/util/sys/new_vec_with_capacity.hpp>

#include <taffy/support/rust_utils/Debug.hpp>

#include <taffy/support/cpp_utils/unreachable.hpp>

namespace taffy {

/// A dynamically sized matrix (2d grid) which tracks the occupancy of each grid cell during auto-placement
/// It also keeps tabs on how many tracks there are and which tracks are implicit and which are explicit.
/* RUST
    pub(crate) struct CellOccupancyMatrix
*/ 
class CellOccupancyMatrix
{
    /// The grid of occupancy states
    Grid<CellOccupancyState> inner;
    /// The counts of implicit and explicit columns
    TrackCounts columns;
    /// The counts of implicit and explicit rows
    TrackCounts rows;

    // To provide access for private fields in Debug
    friend struct Debug_specialization<CellOccupancyMatrix>;

public:

    CellOccupancyMatrix(
        const Grid<CellOccupancyState>& inner_,
        const TrackCounts& columns_,
        const TrackCounts& rows_)
        : inner(inner_)
        , columns(columns_)
        , rows(rows_)
    {}

    // -------------------------------------------------------------------------

    /// Create a CellOccupancyMatrix given a set of provisional track counts. The grid can expand as needed to fit more tracks,
    /// the provisional track counts represent a best effort attempt to avoid the extra allocations this requires.
    /* RUST
        pub fn with_track_counts(columns: TrackCounts, rows: TrackCounts) -> Self
    */
    static CellOccupancyMatrix with_track_counts(const TrackCounts& columns, const TrackCounts& rows)
    {
        return CellOccupancyMatrix { Grid<CellOccupancyState>::New(rows.len(), columns.len()), columns, rows };
    }

    /// Determines whether the specified area fits within the tracks currently represented by the matrix
    /* RUST
        pub fn is_area_in_range(
            &mut self,
            primary_axis: AbsoluteAxis,
            primary_range: Range<i16>,
            secondary_range: Range<i16>,
        ) -> bool
    */
    bool is_area_in_range(
        AbsoluteAxis primary_axis,
        const Range<int16_t>& primary_range,
        const Range<int16_t>& secondary_range
    ) // TODO: this function may be CONST
    {
        if( (primary_range.start < 0) || (primary_range.end > static_cast<int16_t>(this->track_counts(primary_axis).len())) ) {
            return false;
        }
        if( (secondary_range.start < 0) || (secondary_range.end > static_cast<int16_t>(this->track_counts(primary_axis.other_axis()).len())) )
        {
            return false;
        }
        return true;
    }

    /// Expands the grid (potentially in all 4 directions) in order to ensure that the specified range fits within the allocated space
    /* RUST
        fn expand_to_fit_range(&mut self, row_range: Range<i16>, col_range: Range<i16>)
    */
    void expand_to_fit_range(const Range<int16_t>& row_range, const Range<int16_t>& col_range)
    {
        // Calculate number of rows and columns missing to accomodate ranges (if any)
        const auto req_negative_rows = min(row_range.start, int16_t{0});
        const auto req_positive_rows = max(row_range.end - static_cast<int16_t>(this->rows.len()), 0);
        const auto req_negative_cols = min(col_range.start, int16_t{0});
        const auto req_positive_cols = max(col_range.end - static_cast<int16_t>(this->columns.len()), 0);

        const auto old_row_count = this->rows.len();
        const auto old_col_count = this->columns.len();
        const auto new_row_count = old_row_count + static_cast<size_t>(req_negative_rows + req_positive_rows);
        const auto new_col_count = old_col_count + static_cast<size_t>(req_negative_cols + req_positive_cols);

        auto data = new_vec_with_capacity<CellOccupancyState>(new_row_count * new_col_count); // TODO: in Rust here is 'Vec::with_capacity'. maybe we need to change rust too ?

        // Push new negative rows
        for(size_t _ = 0; _ < (static_cast<size_t>(req_negative_rows) * new_col_count); ++_) {
            data.push_back(CellOccupancyState::Unoccupied());
        }
        
        // Push existing rows
        for(size_t row = 0; row < old_row_count; ++row) {
            // Push new negative columns
            for(int16_t _ = 0; _ < req_negative_cols; ++_) {
                data.push_back(CellOccupancyState::Unoccupied());
            }
            // Push existing columns
            for(size_t col = 0; col < old_col_count; ++col) {
                data.push_back(this->inner.get(row, col).unwrap());
            }
            // Push new positive columns
            for(int16_t _ = 0; _ < req_positive_cols; ++_) {
                data.push_back(CellOccupancyState::Unoccupied());
            }
        }

        // Push new negative rows
        for(size_t _ = 0; _ < (static_cast<size_t>(req_positive_rows) * new_col_count); ++_) {
            data.push_back(CellOccupancyState::Unoccupied());
        }

        // Update self with new data
        this->inner = Grid<CellOccupancyState>::from_vec(data, new_col_count);
        this->rows.negative_implicit += static_cast<uint16_t>(req_negative_rows);
        this->rows.positive_implicit += static_cast<uint16_t>(req_positive_rows);
        this->columns.negative_implicit += static_cast<uint16_t>(req_negative_cols);
        this->columns.positive_implicit += static_cast<uint16_t>(req_positive_cols);
    }

    /// Mark an area of the matrix as occupied, expanding the allocated space as necessary to accomodate the passed area.
    /* RUST
        pub fn mark_area_as(
            &mut self,
            primary_axis: AbsoluteAxis,
            primary_span: Line<OriginZeroLine>,
            secondary_span: Line<OriginZeroLine>,
            value: CellOccupancyState,
        )
    */
    void mark_area_as(
        AbsoluteAxis primary_axis,
        const Line<OriginZeroLine>& primary_span,
        const Line<OriginZeroLine>& secondary_span,
        CellOccupancyState value
    ) {
        Line<OriginZeroLine> row_span = {OriginZeroLine(0), OriginZeroLine(0)}, column_span = {OriginZeroLine(0), OriginZeroLine(0)};
        switch(primary_axis.type()) {
        case AbsoluteAxis::Type::Horizontal: { row_span = secondary_span; column_span = primary_span; } break;
        case AbsoluteAxis::Type::Vertical:   { row_span = primary_span;   column_span = secondary_span; } break;
        }

        auto col_range = this->columns.oz_line_range_to_track_range(column_span);
        auto row_range = this->rows.oz_line_range_to_track_range(row_span);

        // Check that if the resolved ranges fit within the allocated grid. And if they don't then expand the grid to fit
        // and then re-resolve the ranges once the grid has been expanded as the resolved indexes may have changed
        const auto is_in_range = this->is_area_in_range(AbsoluteAxis::Horizontal(), col_range, row_range); // TODO: col_range.clone(), row_range.clone() here
        if( !is_in_range ) {
            this->expand_to_fit_range(row_range, col_range); // TODO: row_range.clone(), col_range.clone() here
            col_range = this->columns.oz_line_range_to_track_range(column_span);
            row_range = this->rows.oz_line_range_to_track_range(row_span);
        }

        for(auto x = row_range.start; x < row_range.end; ++x) {
            for(auto y = col_range.start; y < col_range.end; ++y) {
                this->inner.get_mut(static_cast<size_t>(x), static_cast<size_t>(y)).unwrap().get() = value;
            }
        }
    }

    /// Determines whether a grid area specified by the bounding grid lines in OriginZero coordinates
    /// is entirely unnocupied. Returns true if all grid cells within the grid area are unnocupied, else false.
    /* RUST
        pub fn line_area_is_unoccupied(
            &self,
            primary_axis: AbsoluteAxis,
            primary_span: Line<OriginZeroLine>,
            secondary_span: Line<OriginZeroLine>,
        ) -> bool
    */
    bool line_area_is_unoccupied(
        AbsoluteAxis primary_axis,
        const Line<OriginZeroLine>& primary_span,
        const Line<OriginZeroLine>& secondary_span
    ) const
    {
        const auto primary_range = this->track_counts(primary_axis).oz_line_range_to_track_range(primary_span);
        const auto secondary_range = this->track_counts(primary_axis.other_axis()).oz_line_range_to_track_range(secondary_span);
        return this->track_area_is_unoccupied(primary_axis, primary_range, secondary_range);
    }

    /// Determines whether a grid area specified by a range of indexes into this CellOccupancyMatrix
    /// is entirely unnocupied. Returns true if all grid cells within the grid area are unnocupied, else false.
    /* RUST
        pub fn track_area_is_unoccupied(
            &self,
            primary_axis: AbsoluteAxis,
            primary_range: Range<i16>,
            secondary_range: Range<i16>,
        ) -> bool
    */
    bool track_area_is_unoccupied(
        AbsoluteAxis primary_axis,
        const Range<int16_t>& primary_range,
        const Range<int16_t>& secondary_range
    ) const
    {
        Range<int16_t> row_range = {0, 0}, col_range = {0, 0};
        switch(primary_axis.type()) {
        case AbsoluteAxis::Type::Horizontal: { row_range = secondary_range; col_range = primary_range; } break;
        case AbsoluteAxis::Type::Vertical:   { row_range = primary_range; col_range = secondary_range; } break;
        }

        // Search for occupied cells in the specified area. Out of bounds cells are considered unoccupied.
        for(auto x = row_range.start; x < row_range.end; ++x) {
            for(auto y = col_range.start; y < col_range.end; ++y) {
                const auto& _val = this->inner.get(static_cast<size_t>(x), static_cast<size_t>(y));
                if(_val.is_none() || _val->get().type() == CellOccupancyState::Type::Unoccupied) {
                    continue;
                } else {
                    return false;
                }
            }
        }

        return true;
    }

    /// Determines whether the specified row contains any items
    /* RUST
        pub fn row_is_occupied(&self, row_index: usize) -> bool
    */
    bool row_is_occupied(size_t row_index) const {
        return this->inner.iter_row_any(row_index, [](const CellOccupancyState& cell) { return !(cell.type() == CellOccupancyState::Type::Unoccupied); });
    }

    /// Determines whether the specified column contains any items
    /* RUST
        pub fn column_is_occupied(&self, column_index: usize) -> bool
    */
    bool column_is_occupied(size_t column_index) const {
        return this->inner.iter_col_any(column_index, [](const CellOccupancyState& cell) { return !(cell.type() == CellOccupancyState::Type::Unoccupied); });
    }

    /// Returns the track counts of this CellOccunpancyMatrix in the relevant axis
    /* RUST
        pub fn track_counts(&self, track_type: AbsoluteAxis) -> &TrackCounts
    */
    const TrackCounts& track_counts(AbsoluteAxis track_type) const {
        return
            (track_type.type() == AbsoluteAxis::Type::Horizontal) ?
                this->columns
            : // AbsoluteAxis::Type::Vertical
                this->rows;
    }

    /// Given an axis and a track index
    /// Search backwards from the end of the track and find the last grid cell matching the specified state (if any)
    /// Return the index of that cell or None.
    /* RUST
        pub fn last_of_type(
            &self,
            track_type: AbsoluteAxis,
            start_at: OriginZeroLine,
            kind: CellOccupancyState,
        ) -> Option<OriginZeroLine>
    */
    Option<OriginZeroLine> last_of_type(
        AbsoluteAxis track_type,
        OriginZeroLine start_at,
        CellOccupancyState kind
    ) const
    {
        const auto track_counts = this->track_counts(track_type.other_axis());
        const auto track_computed_index = track_counts.oz_line_to_next_track(start_at);

        const auto maybe_index = [&]
        {
            switch(track_type.type()) {
            case AbsoluteAxis::Type::Horizontal: {
                return this->inner.iter_row_rposition(static_cast<size_t>(track_computed_index), [&](const CellOccupancyState& item) { return item == kind; });
            } break;
            case AbsoluteAxis::Type::Vertical: {
                return this->inner.iter_col_rposition(static_cast<size_t>(track_computed_index), [&](const CellOccupancyState& item) { return item == kind; });
            } break;
            }

            taffy_unreachable;
        }();

        return maybe_index.map<OriginZeroLine>([&](size_t idx) { return track_counts.track_to_prev_oz_line(static_cast<uint16_t>(idx)); });
    }
};

// -----------------------------------------------------------------------------

/// Debug impl that represents the matrix in a compact 2d text format
/* RUST
    impl Debug for CellOccupancyMatrix {
        fn fmt(&self, f: &mut core::fmt::Formatter<'_>) -> core::fmt::Result
*/
template <>
struct Debug_specialization<CellOccupancyMatrix>
    : Debug_interface< Debug_specialization<CellOccupancyMatrix>, CellOccupancyMatrix >
{
    static std::string Debug_impl_to_string(const CellOccupancyMatrix& self)
    {
        std::string str;

        str += "Rows: neg_implicit=" + std::to_string(self.rows.negative_implicit) +
               " explicit=" + std::to_string(self.rows.Explicit) +
               " pos_implicit=" + std::to_string(self.rows.positive_implicit) + "\n";
        str += "Cols: neg_implicit=" + std::to_string(self.columns.negative_implicit) +
               " explicit=" + std::to_string(self.columns.Explicit) +
               " pos_implicit=" + std::to_string(self.columns.positive_implicit) + "\n";
        str += "State\n";

        for(size_t col_idx = 0; col_idx < self.inner.cols(); ++col_idx)
        {
            for(size_t row_idx = 0; row_idx < self.inner.rows(); ++row_idx)
            {
                const auto& cell = self.inner.get_unchecked(row_idx, col_idx);
                const char letter = [&] {
                    switch(cell.type()) {
                    case CellOccupancyState::Type::Unoccupied       : return '_';
                    case CellOccupancyState::Type::DefinitelyPlaced : return 'D';
                    case CellOccupancyState::Type::AutoPlaced       : return 'A';
                    }

                    taffy_unreachable;
                }();
                str += letter;
            }
            str += '\n';
        }

        return str;
    }
};

} // namespace taffy
