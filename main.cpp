#include "TriwizardTournament.h"
#include "AuntsNamesday.h"
#include "MeSpellRite.h"
#include <vector>

int main() {
    TextBuilder::buildText();

    std::vector<SpellCheckingAlgorithm*> spellCheckers = { new NaiveSpellCheckingAlgorithm() };
    for (const auto & spellChecker: spellCheckers){
        spellChecker->spellCheck("text.txt");
    }

    AuntsNamesday::test();

    TriwizardTournament::test();

    return 0;
}
