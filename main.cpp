#include "common/TextBuilder.h"
#include "hash_map/HashMapAsserts.h"
#include "tasks/MeSpellRite.h"
#include "tasks/TriwizardTournament.h"
#include "tasks/AuntsNamesday.h"
#include "tasks/FullHouse.h"

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
