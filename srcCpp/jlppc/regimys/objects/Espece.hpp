#ifndef ESPECE_HPP
#define ESPECE_HPP

#include <iostream>
#include "srcCpp/jlppc/regimys/evolution/Evolution.hpp"
#include "srcCpp/jlppc/regimys/enums/Type.hpp"
#include "srcCpp/jlppc/utils/HashArray.hpp"
#include "srcCpp/jlppc/regimys/start/main.hpp"
#include "RegimysObject.hpp"
#include "../../jlppc/utils/NumberedArray.hpp"

using namespace std;

enum CourbeExp{
	ERRATIQUE,FLUCTUANTE,LENTE,MOYENNE,PARABOLIQUE,RAPIDE
};

class Espece : public RegimysObject
{
    public:
	virtual ~Espece();
        Espece(int atk, int def, int atkSpe, int defSpe, int vit, int pv, string name, Type type1, Type type2,int maniereEvolution, int niveauEvolution, Evolution *evolType, NumberedArray attacksByLevels[],CT ctCombatibles[], Stats EVGiven[], float taille, float poids, string entreePokedex, int expGiven,int expMax, int tauxDeCapture);
        void checkEvol() const;
        void checkAtkLvls() const;
        static int pokedexNumberInit = 0;
        static Class<Espece> *classe = new Class<Espece>("Espece", 4987386);
        int getBaseAtk() const {return baseAtk;}
        int getBaseDef() const {return baseDef;}
        int getBaseAtkSpe() const {return baseAtkSpe;}
        int getBaseDefSpe() const {return baseDefSpe;}
        int getBaseVit() const {return baseVit;}
        int getBasePV() const {return basePV;}
        int getNom() const {return nom;}
        int getTauxDeCapture() const {return tauxDeCapture;}
        Type getType1() const {return type1;}
        Type getType2() const {return type2;}
        CourbeExp getCourbe() const {return courbe;}
        int getExp() const {return expGiven;}
        Evolution* getEvolType() const {return evolType;}
        Stats* getEv() const {return &EVgiven;}
        Espece getEvolution() const {return evolution;}
        virtual Class<Espece>* getClass() const {return classe;}
    protected:

    private:
        string nom;
        int numeroPokedex;
        Espece evolution;
        int niveauEvolution;
        Evolution *evolType;
        Type type1;
        Type type2;
        NumberedArray atksByLevels[];
        string entreePokedex;
        float taille;
        float poids;
        CT ctCompatibles[];
        int baseAtk;
        int baseDef;
        int baseAtkSpe;
        int baseDefSpe;
        int baseVit;
        int basePV;
        CourbeExp courbe;
        int expMax;
        Stats EVgiven[];
        //Images
        int expGiven;
        int tauxDeCapture;

};

#endif // ESPECE_HPP
