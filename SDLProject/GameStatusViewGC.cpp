#include "GameStatusViewGC.h"

#include "GameManager.h"
GameStatusViewGC::GameStatusViewGC() {}

GameStatusViewGC::~GameStatusViewGC() {}

void GameStatusViewGC::render(Container *c, Uint32 time) {
  GameManager *gm = static_cast<GameManager *>(c);

  string msg = "";
  switch (gm->getStatus()) {
  case GameManager::WAITING:
    msg = "Waiting for Players to Connect";
    break;
  case GameManager::READY:
    msg = "Press any key to continue";
    break;
  case GameManager::RUNNING:
    msg = "";
    break;
  }

  if (msg.length() > 0) {
    // show the winner
    Texture t(gm->getGame()->getRenderer(), msg,
              *(gm->getGame()->getServiceLocator()->getFonts()->getFont(
                  Resources::ARIAL24)),
              {COLOR(0xff0000ff)});
    t.render(gm->getGame()->getRenderer(),
             gm->getGame()->getWindowWidth() / 2 - t.getWidth() / 2,
             gm->getGame()->getWindowHeight() - t.getHeight() - 100);
  }

  if (gm->getWinner() != -1) {
    string winner;
    if (gm->getWinner() == 0)
      winner = "Fighter 0";
    else
      winner = "Fighter 1";
    Texture w(gm->getGame()->getRenderer(), winner,
              *(gm->getGame()->getServiceLocator()->getFonts()->getFont(
                  Resources::ARIAL24)),
              {COLOR(0xff0000ff)});
    w.render(gm->getGame()->getRenderer(), gm->getGame()->getWindowWidth() / 2,
             gm->getGame()->getWindowHeight() / 2);
  }
}
