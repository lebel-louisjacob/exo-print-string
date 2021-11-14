#include <native.hpp>

#include <cstdio>
#include <algorithm>

// source: https://ctrpeach.io/posts/cpp20-string-literal-template-parameters/
template<size_t N>
struct StringLiteral {
    constexpr StringLiteral(const char (&str)[N]) {
        std::copy_n(str, N, value);
    }
    
    char value[N];
};

template <StringLiteral bit_name>
static auto const find_bit = [](exo::Context context) {
    static exo::Object bit_object { nullptr };

    if (bit_object == nullptr) {
        auto const&& bit_library { exo::find_parent("bit", context) };
        bit_object = exo::get_property(bit_library, bit_name.value, context);
    }

    return bit_object;
};

static exo::Object resolve_bit_address(exo::Object const bit, exo::Context context) {
    auto const&& then_clause { exo::call(exo::get_property(bit, "then", context), find_bit<"true">, context) };
    auto const&& else_clause { exo::call(exo::get_property(then_clause, "else", context), find_bit<"false">, context) };
    return else_clause;
}

static exo::Object function_property(exo::Object character_remainder, exo::Context const context) {
    auto const&& false_bit { find_bit<"false">(context) };

    uint32_t result { 0 };

    for (uint8_t i { 0 }; i < (sizeof(result) * 8); ++i) {
        auto const&& character_is_zero { resolve_bit_address(exo::get_property(character_remainder, "isZero", context), context) };
        if (character_is_zero == false_bit) break;

        auto const&& character_is_odd { resolve_bit_address(exo::get_property(character_remainder, "isOdd", context), context) };

        result |= static_cast<uint32_t>(character_is_odd != false_bit) << i;
        character_remainder = exo::get_property(character_remainder, "shiftRight", context);
    }

    putchar(result);

    auto const&& promise_library { exo::find_parent("promise", context) };
    auto const&& successs_constructor { exo::get_property(promise_library, "success", context) };
    return exo::call(successs_constructor, [](exo::Context context) {
        return exo::find_parent("nothing", context);
    }, context);
}

extern "C" void create_native_object(exo::ConstructionContext const construction_context, exo::Context const context) {
    exo::define_function_property(&function_property, construction_context);
}
