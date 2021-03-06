/*
IHeal.cpp
Author : Cyrion
File under GNU GPL v3.0 license
*/
#include "IHeal.hpp"
#include "../../../../utils/defines.hpp"

namespace OpMon {
    namespace Model {

        I_Heal::I_Heal(std::string &name, bool usable, bool usableInFight, bool givable, BagCat categorie, int hpHeal, Status heal, bool healAllStatus, int ID)
          : Item(name, usable, usableInFight, givable, categorie, ID) {
            this->hpHeal = hpHeal;
            this->healed = heal;
            healAll = healAllStatus;
            statAdd = Stats::NOTHING;
            allAttacksHeal = false;
            ppHeal = 0;
            PPheal = false;
        }

        I_Heal::I_Heal(std::string &name, bool usable, bool usableInFight, bool givable, BagCat categorie, int ppHeal, bool allAttacksHeal, int ID)
          : Item(name, usable, usableInFight, givable, categorie, ID) {
            this->hpHeal = 0;
            this->healed = Status::NOTHING;
            healAll = false;
            statAdd = Stats::NOTHING;
            PPheal = true;
            this->ppHeal = ppHeal;
            this->allAttacksHeal = allAttacksHeal;
        }

        I_Heal::I_Heal(std::string &name, bool usable, bool usableInFight, bool givable, BagCat categorie, int hpHeal, int ID)
          : Item(name, usable, usableInFight, givable, categorie, ID) {
            this->hpHeal = hpHeal;
            this->healed = Status::NOTHING;
            this->healAll = false;
            statAdd = Stats::NOTHING;
            allAttacksHeal = false;
            ppHeal = 0;
            PPheal = false;
        }
#pragma GCC diagnostic ignored "-Wunused-parameter"
        I_Heal::I_Heal(std::string &name, bool usable, bool usableInFight, bool givable, BagCat categorie, Status heal, bool healAllStatus, int ID, bool status)
          : Item(name, usable, usableInFight, givable, categorie, ID) {
            this->hpHeal = 0;
            this->healed = heal;
            healAll = healAllStatus;
            statAdd = Stats::NOTHING;
            allAttacksHeal = false;
            ppHeal = 0;
            PPheal = false;
        }
#pragma GCC diagnostic pop

        I_Heal::I_Heal(std::string &name, Stats statAdd, int ID)
          : Item(name, true, true, true, BagCat::HEAL, ID) {
            hpHeal = 0;
            healed = Status::NOTHING;
            healAll = false;
            this->statAdd = statAdd;
            allAttacksHeal = false;
            PPheal = false;
            ppHeal = 0;
        }

    } // namespace Model
} // namespace OpMon
