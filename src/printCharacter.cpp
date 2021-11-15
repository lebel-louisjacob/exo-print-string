#include <native.hpp>

#include <cstdio>
#include <algorithm>

static exo::Object function_property(exo::Object character_remainder, exo::Context const context) {
    auto const&& bit_library { exo::find_parent("bit", context) };
    auto const&& true_bit { exo::get_property(bit_library, "true", context) };

    uint32_t result { 0 };

    for (uint8_t i { 0 }; i < (sizeof(result) * 8); ++i) {
        auto const&& character_is_zero { exo::get_property(character_remainder, "isZero", context) };
        if (character_is_zero == true_bit) break;

        auto const&& character_is_odd { exo::get_property(character_remainder, "isOdd", context) };

        result |= static_cast<uint32_t>(character_is_odd == true_bit) << i;
        character_remainder = exo::get_property(character_remainder, "shiftRight", context);
    }

    putchar(result);

    auto const&& promise_library { exo::find_parent("promise", context) };
    auto const&& success_constructor { exo::get_property(promise_library, "success", context) };
    return exo::call(success_constructor, [](exo::Context context) {
        return exo::find_parent("empty", context);
    }, context);
}

extern "C" void create_native_object(exo::ConstructionContext const construction_context, exo::Context const context) {
    exo::define_function_property(&function_property, construction_context);
}
