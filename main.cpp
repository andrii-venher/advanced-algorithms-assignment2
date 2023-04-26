
#include "me_spell_rite/MeSpellRite.h"
#include "TriwizardTournament.h"
#include "AuntsNamesday.h"
#include "FullHouse.h"
#include "common/HashMapAsserts.h"

int main() {
    TextBuilder::init();
    HashMapAsserts::run();

    std::cout << std::endl;

    MeSpellRite::test();

    AuntsNamesday::test();

    TriwizardTournament::test();

    FullHouse::measure();

    return 0;
}
