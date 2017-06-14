#include <hal/hal>
#include <type_traits>

namespace {

enum class enum_u8 : uint8_t {};
enum class enum_u16 : uint16_t {};
enum class enum_u32 : uint32_t {};

enum class enum_i8 : int8_t {};
enum class enum_i16 : int16_t {};
enum class enum_i32 : int32_t {};

static_assert(std::is_same<std::underlying_type<enum_u8>::type, uint8_t>::value, "underlying_type");
static_assert(std::is_same<std::underlying_type<enum_u16>::type, uint16_t>::value, "underlying_type");
static_assert(std::is_same<std::underlying_type<enum_u32>::type, uint32_t>::value, "underlying_type");

static_assert(std::is_same<std::underlying_type<enum_i8>::type, int8_t>::value, "underlying_type");
static_assert(std::is_same<std::underlying_type<enum_i16>::type, int16_t>::value, "underlying_type");
static_assert(std::is_same<std::underlying_type<enum_i32>::type, int32_t>::value, "underlying_type");

}