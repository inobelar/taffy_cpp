#pragma once

#include <cstdint> // for: uint64_t
#include <cstddef> // for: size_t

#if defined(TAFFY_FEATURE_TAFFY_TREE)
    #include <taffy/support/rust_utils/crates/slotmap/DefaultKey.hpp>
    #include <taffy/support/cpp_utils/uint_pack.hpp>
#endif // TAFFY_FEATURE_TAFFY_TREE

#include <taffy/support/rust_utils/Debug.hpp>

namespace taffy {

/// A type representing the id of a single node in a tree of nodes
///
/// Internally it is a wrapper around a u64 and a `NodeId` can be converted to and from
/// and u64 if needed.
/* RUST
    #[derive(Copy, Clone, Debug, PartialEq, Eq)]
    pub struct NodeId(u64);
*/
class NodeId
{
    uint64_t _v0;

    // To access private field `_v0` in Debug
    friend struct Debug_specialization<NodeId>;

public:

    constexpr bool operator == (const NodeId other) const
    {
        return (_v0 == other._v0);
    }

    constexpr bool operator != (const NodeId other) const
    {
        return !(*this == other);
    }

    // -------------------------------------------------------------------------

    /// Create a new NodeId from a u64 value
    /* RUST
        pub const fn new(val: u64) -> Self
    */
    static constexpr NodeId New(uint64_t val)
    {
        return NodeId(val);
    }
    constexpr NodeId(uint64_t value)
        : _v0(value)
    {}

    // -------------------------------------------------------------------------

    /* RUST
        impl From<u64> for NodeId {
            #[inline]
            fn from(raw: u64) -> Self
    */
    static constexpr NodeId from(uint64_t raw)
    {
        return NodeId(raw);
    }

    // -------------------------------------------------------------------------

    /* RUST
        impl From<NodeId> for u64 {
            #[inline]
            fn from(id: NodeId) -> Self 
    */
    explicit constexpr operator uint64_t () const
    {
        return _v0;
    }

    // -------------------------------------------------------------------------

    /*
        IMPORTANT NOTE:

        In C++ `uint64_t` and `size_t` can be the same type (on 64-bit systems),
        so it produces compile errors about 'redeclaration for same type', if
        we write the next functions without any type-checks:

            static constexpr NodeId from(uint64_t raw)
            {
                return NodeId(raw);
            }

            static constexpr NodeId from(size_t raw)
            {
                return NodeId( static_cast<uint64_t>(raw) );
            }

        For convenience and safety, between `uint64_t` and `size_t`, here is
        preferred construction from `uint64_t` (since in this structure data in
        that type), BUT if `uint64_t` is not the same as `size_t`, we provide
        the ability for construction from that type, since its declared in rust
        code.

        Reference for the next (unusual) check pattern:

            template <typename Dummy = void,
                      typename = typename std::enable_if< ... , Dummy>::type>

        https://www.foonathan.net/2016/12/conditionally-removing-functions/
    */

    /* RUST
        impl From<usize> for NodeId {
            #[inline]
            fn from(raw: usize) -> Self
    */
    template <typename Dummy = void,
              typename = typename std::enable_if< std::is_same<size_t, uint64_t>::value == false, Dummy>::type>
    static constexpr NodeId from(size_t raw)
    {
        return NodeId( static_cast<uint64_t>(raw) );
    }
    template <typename Dummy = void,
              typename = typename std::enable_if< std::is_same<size_t, uint64_t>::value == false, Dummy>::type>
    constexpr NodeId(size_t raw)
        : NodeId { from(raw) }
    {}

    // -------------------------------------------------------------------------

    /* RUST
        impl From<NodeId> for usize {
            #[inline]
            fn from(id: NodeId) -> Self
    */
    template <typename Dummy = void,
              typename = typename std::enable_if< std::is_same<size_t, uint64_t>::value == false, Dummy>::type>
    explicit constexpr operator size_t () const
    {
        return static_cast<size_t>(_v0);
    }

    // -------------------------------------------------------------------------

    #if defined(TAFFY_FEATURE_TAFFY_TREE)

        /* RUST
            impl From<DefaultKey> for NodeId {
                #[inline]
                fn from(key: DefaultKey) -> Self {
                    Self(key.data().as_ffi())
                }
            }
        */
        template <typename Dummy = void,
                typename = typename std::enable_if< std::is_same<DefaultKey, uint64_t>::value == false, Dummy>::type>
        static inline NodeId from(const DefaultKey& raw) // NOTE: non-costexpr due to non-constexpr `DefaultKey` (that is `std::pair`) and `pack_u32_pair_into_u64()`
        {
            return NodeId( uint_pack::pack_u32_pair_into_u64(raw) );
        }
        template <typename Dummy = void,
                  typename = typename std::enable_if< std::is_same<DefaultKey, uint64_t>::value == false, Dummy>::type>
        inline NodeId(const DefaultKey& raw) // NOTE: non-costexpr due to non-constexpr `from` method above
            : NodeId { from(raw) }
        {}

        // ---------------------------------------------------------------------

        /* RUST
            impl From<NodeId> for DefaultKey {
                #[inline]
                fn from(key: NodeId) -> Self {
                    KeyData::from_ffi(key.0).into()
                }
            }
        */
        template <typename Dummy = void,
                typename = typename std::enable_if< std::is_same<DefaultKey, uint64_t>::value == false, Dummy>::type>
        explicit inline operator DefaultKey () const /// NOTE: non-costexpr due to non-constexpr `DefaultKey` (that is `std::pair`) and `unpack_u64_into_u32_pair()`
        {
            return uint_pack::unpack_u64_into_u32_pair(_v0);
        }

    #endif // TAFFY_FEATURE_TAFFY_TREE
};

// -----------------------------------------------------------------------------

template <>
struct Debug_specialization<NodeId>
    : Debug_interface< Debug_specialization<NodeId>, NodeId >
{
    static std::string Debug_impl_to_string(const NodeId& value)
    {
        return "NodeId(" + Debug(value._v0) + ")";
    }
};

} // namespace taffy
