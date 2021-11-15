#include <native.hpp>

#include <cstdio>

exo::Object function_property(exo::Object character_remainder, exo::Context const context) {
    auto const&& bit_library { exo::find_parent("bit", context) };
    auto const&& true_bit { exo::get_property("true", bit_library) };

    uint32_t result { 0 };

    for (uint8_t i { 0 }; i < (sizeof(result) * 8); ++i) {
        auto const&& character_is_zero { exo::get_property("isZero", character_remainder) };
        if (character_is_zero == true_bit) break;

        auto const&& character_is_odd { exo::get_property("isOdd", character_remainder) };

        result |= static_cast<uint32_t>(character_is_odd == true_bit) << i;
        character_remainder = exo::get_property("shiftRight", character_remainder);
    }

    putchar(result);

    auto const&& empty_library { exo::find_parent("empty", context) };

    auto const&& promise_library { exo::find_parent("promise", context) };
    auto const&& success_constructor { exo::get_property("success", promise_library) };
    return exo::call(empty_library, success_constructor);
}

extern "C" void create_native_object(exo::ConstructionContext const construction_context, exo::Context const context) {
    exo::define_function_property(&function_property, construction_context);
}
