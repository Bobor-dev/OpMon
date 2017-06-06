#include "MainFrame.hpp"
#include <iostream>
#include "../start/main.hpp"
#include <SFML/Graphics.hpp>
#include <cstring>
#include "../start/StringKeys.hpp"
#include "../start/main.hpp"
#include <string>
#include <SFML/Audio.hpp>
#include "MainMenu.hpp"
#include "../start/Initializer.hpp"
#include "Overworld.hpp"
#include "OptionsMenu.hpp"
#include <thread>
#include "../save/OptionsSave.hpp"

#include "StartScene.hpp"

bool keyPressed = false;

UNS

namespace MainFrame {
    sf::RenderTexture frame;
    sf::RenderWindow window;
    sf::Sprite fond;
    sf::Event events;
    sf::Font font;
    sf::Sprite dialog;
    sf::Text dialogText[3];
    bool init = false;
    sf::Sprite ppSprite;
    sf::Sprite ppAnim;
    sf::Sound dialogPass;
    sf::Thread* windowRefresh = NULL;
    bool fullScreen = false;


void initAllStrings(){
    MainMenu::OptionsMenu::initStrings();
    MainMenu::initStrings();
    StartScene::initStrings();
}

void printText(sf::RenderTexture &framee, sf::String text[]) {
    int minusPos = 32;
    FOR_EACH(sf::String, text, 3, {)
        dialogText[itor].setString(text[itor]);
        dialogText[itor].setFont(font);
        dialogText[itor].setCharacterSize(FONT_SIZE_DEFAULT);
        dialogText[itor].setColor(sf::Color::Black);
        dialogText[itor].setPosition(25, dialog.getPosition().y + minusPos);
        minusPos+=32;

        framee.draw(dialogText[itor]);
    }

}

void initAll(){
    MainMenu::initVars();
    StartScene::initVars();
    Overworld::initVars();
}

void destroyAll(){
    MainMenu::deleteVars();
    StartScene::destroyVars();
}

void open() {
#ifdef _WIN32
        if(!font.loadFromFile("ressources\\fonts\\Default.ttf"))
#else
        if(!font.loadFromFile(RESSOURCES_PATH + "fonts/Default.ttf"))
#endif // _WIN32
    {
        gererErreur("Erreur d'initialisation de la police d'�criture.", true);
    }
    rlog << PRINT_TICKS << "Initialisation de la police termin�e" << endl;

    init = true;
    //Ouverture de la fenetre
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    if(!OptionsSave::checkParam("fullscreen")){
        OptionsSave::addOrModifParam("fullscreen", "false");
    }
    if(OptionsSave::getParam("fullscreen").getValue() == "true"){
        fullScreen = true;
        window.create(sf::VideoMode::getFullscreenModes().at(0), "OpMon Lazuli", sf::Style::Fullscreen, settings);
    }else{
        window.create(sf::VideoMode(512, 512), "OpMon Lazuli", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize, settings);
    }
    frame.create(512, 512);
    //Cr�ation du renderer.
    rlog << PRINT_TICKS << "Initialisation de la fenetre et du renderer termin�e" << endl;
    //Ouverture d'un son
    sf::SoundBuffer buf;
    //window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(180);
#ifdef _WIN32
    if(!buf.loadFromFile("ressources\\audio\\sounds\\dialogChange.ogg"))
#else
    if(!buf.loadFromFile(RESSOURCES_PATH + "audio/sounds/dialogChange.ogg"))
#endif
    {
        gererErreur("Impossible d'ouvrir le son de changement de dialogue.", false);
    }
    window.setKeyRepeatEnabled(false);
    dialogPass.setBuffer(buf);
    rlog << PRINT_TICKS << "Chargement des sprites globaux (Initializer)" << endl;
    Initializer::initSprites();
    rlog << PRINT_TICKS << "Chargement des variables de chaque partie" << endl;
    initAll();
    frame.clear(sf::Color::White);
    //#define TEST
    #ifdef TEST
    ifstream strm(RESSOURCES_PATH + "keys/francais.rkeys");
    string read;
    getline(strm, read);
    getline(strm, read);
    getline(strm, read);
    getline(strm, read);
    getline(strm, read);
    getline(strm, read);
    getline(strm, read);
    getline(strm, read);
    getline(strm, read);
    getline(strm, read);
    getline(strm, read);
    sf::String sfstr = sf::String::fromUtf8(read.begin(), read.end());
    sf::Text txt;
    txt.setString(sfstr);
    txt.setColor(sf::Color::Blue);
    frame.clear(sf::Color::White);
    cout << read << endl;
    frame.draw(txt);
    frame.display();
    winRefresh();
    Utils::wait(1000 * 5);
    #endif
    frame.clear(sf::Color::White);
    frame.display();
    winRefresh();

    dialogPass.setVolume(50);
    frame.clear(sf::Color::Black);
    rlog << PRINT_TICKS << "Lancement du menu." << endl;
    //Lancement du jeu
    if(MainMenu::mainMenu() != -1) {
        MainMenu::bruitPush.play();
        MainMenu::fondMusTitle.stop();
        if(StartScene::startScene() != -1) {
                StartScene::fondMus.stop();
            if(Overworld::overworld() != -1){
                if(Overworld::overworld() == 2){
                    Main::reboot = true;

                }
            }
        }
    } else {
        MainMenu::bruitPush.play();
    }

    rlog << PRINT_TICKS << "Suppression des variables de chaque partie" << endl;
    destroyAll();
    rlog << PRINT_TICKS << "Fermeture de la fenetre" << endl;
    window.close();
    init = false;
    delete(windowRefresh);
}


void winRefresh(){
    sf::Texture txture = frame.getTexture();
    sf::Sprite sprite;
    sprite.setTexture(txture);

    if(fullScreen){
        float coef = window.getSize().y / (sprite.getGlobalBounds().height * 1.0);
        sprite.setScale(coef, coef);
        sprite.setPosition(((window.getSize().x / 2) - (sprite.getGlobalBounds().width / 2)), 0);

    }
    window.clear(sf::Color::Black);
    window.draw(sprite);
    window.display();
    /*int ancientTick = 0;
    while(window.isOpen()){
        if(GET_TICKS - ancientTick < FPS_TICKS){

        }else{
            Utils::wait(GET_TICKS - ancientTick);
        }
    }*/
}


}