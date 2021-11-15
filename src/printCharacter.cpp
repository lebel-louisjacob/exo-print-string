#include <native.hpp>

#include <cstdio>

exo::Object function_property(exo::Object character_remainder, exo::Object const self) {
    auto const&& bit_library { exo::find("bit", self) };
    auto const&& true_bit { exo::get("true", bit_library) };

    uint32_t result { 0 };

    for (uint8_t i { 0 }; i < (sizeof(result) * 8); ++i) {
        auto const&& character_is_zero { exo::get("isZero", character_remainder) };
        if (character_is_zero == true_bit) break;

        auto const&& character_is_odd { exo::get("isOdd", character_remainder) };

        result |= static_cast<uint32_t>(character_is_odd == true_bit) << i;
        character_remainder = exo::get("shiftRight", character_remainder);
    }

    putchar(result);

    auto const&& empty_library { exo::find("empty", self) };

    auto const&& promise_library { exo::find("promise", self) };
    auto const&& success_constructor { exo::get("success", promise_library) };
    return exo::call(empty_library, success_constructor);
}

extern "C" void create_native_object(exo::Context const context, exo::Object const self) {
    exo::define_function_property(&function_property, context);
}
