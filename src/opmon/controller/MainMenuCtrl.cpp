#include "./MainMenuCtrl.hpp"
#include "../view/Window.hpp"

#include "../model/storage/Data.hpp"
#include "./OptionsMenuCtrl.hpp"
#include "./StartSceneCtrl.hpp"

namespace OpMon {
    namespace Controller {

      MainMenuCtrl::MainMenuCtrl(Model::UiData* data)
          : data(Model::MainMenuData(data)), view(this->data) {
            nope.setBuffer(Model::Data::Sounds::nope);
            arrow.setBuffer(Model::Data::Sounds::arrow);
            push.setBuffer(Model::Data::Sounds::push);
        }

        GameStatus MainMenuCtrl::checkEvent(sf::Event const &event) {
            if(event.type == sf::Event::KeyPressed) {
                switch(event.key.code) {
                case sf::Keyboard::Return:
                    switch(view.getCursorPosition()) {
                    case 0:
		      _next_gs = new StartSceneCtrl(data.getUiDataPtr());
                        push.play();
                        return GameStatus::NEXT;
                    case 1:
                        nope.play();
                        return GameStatus::CONTINUE;
                    case 2:
		      _next_gs = new OptionsMenuCtrl(data.getUiDataPtr());
                        push.play();
                        return GameStatus::NEXT;
                    case 3:
                        push.play();
                        return GameStatus::STOP;
                    }
                    break;
                case sf::Keyboard::Up:
                    view.moveArrow(true);
                    arrow.play();
                    break;
                case sf::Keyboard::Down:
                    view.moveArrow(false);
                    arrow.play();
                    break;

                default:
                    break;
                }
            }
            return GameStatus::CONTINUE;
        }

      GameStatus MainMenuCtrl::update(sf::RenderTexture& frame) {
            view.draw(frame);
            return GameStatus::CONTINUE;
        }

        void MainMenuCtrl::suspend() {
            view.pause();
        }

        void MainMenuCtrl::resume() {
            view.play();
        }

    } // namespace Controller
} // namespace OpMon
