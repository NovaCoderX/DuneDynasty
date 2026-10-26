/*
 *  This file is part of Dune Legacy.
 *
 *  Dune Legacy is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  Dune Legacy is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Dune Legacy.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <GUI/dune/InGameSettingsMenu.h>

#include <globals.h>

#include <FileClasses/GFXManager.h>
#include <FileClasses/TextManager.h>
#include <FileClasses/music/MusicPlayer.h>
#include <Game.h>
#include <main.h>
#include <House.h>
#include <SoundPlayer.h>
#include <ScreenBorder.h>

#include <GUI/Spacer.h>

#include <algorithm>

/*
    Layout (self-generated themed background, no fixed bitmap):

    The original dialog used the pre-drawn UI_OptionsMenu graphic (192x168) which
    baked the caption and row labels into the bitmap and only had room for three
    rows, with a single volume slider controlling both music and sfx. This version
    generates its background at runtime (like GameOptionsWindow does), which allows
    a taller window with four rows and real Label widgets:

        caption
        Game speed      [-][=======][+]
        Music volume    [-][=======][+]
        Sound volume    [-][=======][+]
        Scroll speed    [-][=======][+]
                 [OK]  [Cancel]
*/

#define DLG_WIDTH        192
#define DLG_HEIGHT       214
#define ROW_PITCH        39
#define ROW0_LABEL_Y     36
#define ROW0_CONTROL_Y   50

InGameSettingsMenu::InGameSettingsMenu() : Window(0,0,DLG_WIDTH,DLG_HEIGHT) {
    int houseID = pLocalHouse->getHouseID();
    Uint32 color1 = SDL2RGB(palette[houseToPaletteIndex[houseID]+2]);
    Uint32 color2 = SDL2RGB(palette[houseToPaletteIndex[houseID]+3]);

    // set up window; no bitmap background is set, so the Window base class
    // self-generates a themed background at our chosen size
    setWindowWidget(&windowWidget);

    captionLabel.setText(_("Game settings"));
    captionLabel.setTextColor(color2);
    captionLabel.setAlignment(Alignment_HCenter);
    windowWidget.addWidget(&captionLabel, Point(0,12), Point(DLG_WIDTH,20));

    // Game speed
    gameSpeedLabel.setText(_("Game speed"));
    gameSpeedLabel.setTextColor(color2);
    windowWidget.addWidget(&gameSpeedLabel, Point(23,ROW0_LABEL_Y + 0*ROW_PITCH), Point(146,12));

    gameSpeedMinus.setTextures(pGFXManager->getUIGraphic(UI_Minus, houseID), false, pGFXManager->getUIGraphic(UI_Minus_Pressed, houseID), false);
    gameSpeedMinus.setOnClick(std::bind(&InGameSettingsMenu::onGameSpeedMinus, this));
    windowWidget.addWidget(&gameSpeedMinus, Point(5,ROW0_CONTROL_Y + 0*ROW_PITCH), gameSpeedMinus.getSize());

    gameSpeedBar.setColor(color1);
    windowWidget.addWidget(&gameSpeedBar, Point(23,ROW0_CONTROL_Y + 0*ROW_PITCH + 4), Point(146,6));

    gameSpeedPlus.setTextures(pGFXManager->getUIGraphic(UI_Plus, houseID), false, pGFXManager->getUIGraphic(UI_Plus_Pressed, houseID), false);
    gameSpeedPlus.setOnClick(std::bind(&InGameSettingsMenu::onGameSpeedPlus, this));
    windowWidget.addWidget(&gameSpeedPlus, Point(172,ROW0_CONTROL_Y + 0*ROW_PITCH), gameSpeedPlus.getSize());

    // Music volume
    musicVolumeLabel.setText(_("Music volume"));
    musicVolumeLabel.setTextColor(color2);
    windowWidget.addWidget(&musicVolumeLabel, Point(23,ROW0_LABEL_Y + 1*ROW_PITCH), Point(146,12));

    musicVolumeMinus.setTextures(pGFXManager->getUIGraphic(UI_Minus, houseID), false, pGFXManager->getUIGraphic(UI_Minus_Pressed, houseID), false);
    musicVolumeMinus.setOnClick(std::bind(&InGameSettingsMenu::onMusicVolumeMinus, this));
    windowWidget.addWidget(&musicVolumeMinus, Point(5,ROW0_CONTROL_Y + 1*ROW_PITCH), musicVolumeMinus.getSize());

    musicVolumeBar.setColor(color1);
    windowWidget.addWidget(&musicVolumeBar, Point(23,ROW0_CONTROL_Y + 1*ROW_PITCH + 4), Point(146,6));

    musicVolumePlus.setTextures(pGFXManager->getUIGraphic(UI_Plus, houseID), false, pGFXManager->getUIGraphic(UI_Plus_Pressed, houseID), false);
    musicVolumePlus.setOnClick(std::bind(&InGameSettingsMenu::onMusicVolumePlus, this));
    windowWidget.addWidget(&musicVolumePlus, Point(172,ROW0_CONTROL_Y + 1*ROW_PITCH), musicVolumePlus.getSize());

    // Sound (sfx) volume
    sfxVolumeLabel.setText(_("Sound volume"));
    sfxVolumeLabel.setTextColor(color2);
    windowWidget.addWidget(&sfxVolumeLabel, Point(23,ROW0_LABEL_Y + 2*ROW_PITCH), Point(146,12));

    sfxVolumeMinus.setTextures(pGFXManager->getUIGraphic(UI_Minus, houseID), false, pGFXManager->getUIGraphic(UI_Minus_Pressed, houseID), false);
    sfxVolumeMinus.setOnClick(std::bind(&InGameSettingsMenu::onSfxVolumeMinus, this));
    windowWidget.addWidget(&sfxVolumeMinus, Point(5,ROW0_CONTROL_Y + 2*ROW_PITCH), sfxVolumeMinus.getSize());

    sfxVolumeBar.setColor(color1);
    windowWidget.addWidget(&sfxVolumeBar, Point(23,ROW0_CONTROL_Y + 2*ROW_PITCH + 4), Point(146,6));

    sfxVolumePlus.setTextures(pGFXManager->getUIGraphic(UI_Plus, houseID), false, pGFXManager->getUIGraphic(UI_Plus_Pressed, houseID), false);
    sfxVolumePlus.setOnClick(std::bind(&InGameSettingsMenu::onSfxVolumePlus, this));
    windowWidget.addWidget(&sfxVolumePlus, Point(172,ROW0_CONTROL_Y + 2*ROW_PITCH), sfxVolumePlus.getSize());

    // Scroll speed
    scrollSpeedLabel.setText(_("Scroll speed"));
    scrollSpeedLabel.setTextColor(color2);
    windowWidget.addWidget(&scrollSpeedLabel, Point(23,ROW0_LABEL_Y + 3*ROW_PITCH), Point(146,12));

    scrollSpeedMinus.setTextures(pGFXManager->getUIGraphic(UI_Minus, houseID), false, pGFXManager->getUIGraphic(UI_Minus_Pressed, houseID), false);
    scrollSpeedMinus.setOnClick(std::bind(&InGameSettingsMenu::onScrollSpeedMinus, this));
    windowWidget.addWidget(&scrollSpeedMinus, Point(5,ROW0_CONTROL_Y + 3*ROW_PITCH), scrollSpeedMinus.getSize());

    scrollSpeedBar.setColor(color1);
    windowWidget.addWidget(&scrollSpeedBar, Point(23,ROW0_CONTROL_Y + 3*ROW_PITCH + 4), Point(146,6));

    scrollSpeedPlus.setTextures(pGFXManager->getUIGraphic(UI_Plus, houseID), false, pGFXManager->getUIGraphic(UI_Plus_Pressed, houseID), false);
    scrollSpeedPlus.setOnClick(std::bind(&InGameSettingsMenu::onScrollSpeedPlus, this));
    windowWidget.addWidget(&scrollSpeedPlus, Point(172,ROW0_CONTROL_Y + 3*ROW_PITCH), scrollSpeedPlus.getSize());

    // buttons
    okButton.setText(_("OK"));
    okButton.setTextColor(color2);
    okButton.setOnClick(std::bind(&InGameSettingsMenu::onOK, this));
    windowWidget.addWidget(&okButton, Point(12,DLG_HEIGHT-23), Point(79,15));

    cancelButton.setText(_("Cancel"));
    cancelButton.setTextColor(color2);
    cancelButton.setOnClick(std::bind(&InGameSettingsMenu::onCancel, this));
    windowWidget.addWidget(&cancelButton, Point(101,DLG_HEIGHT-23), Point(79,15));

    // center the window on screen
    int xpos = std::max<int>(0, (getRendererWidth() - getSize().x)/2);
    int ypos = std::max<int>(0, (getRendererHeight() - getSize().y)/2);
    setCurrentPosition(xpos, ypos, getSize().x, getSize().y);

    init();
}

InGameSettingsMenu::~InGameSettingsMenu() {
}

void InGameSettingsMenu::init() {
    newGamespeed = settings.gameOptions.gameSpeed;
    gameSpeedBar.setProgress(100.0 - ((newGamespeed-GAMESPEED_MIN)*100.0)/(GAMESPEED_MAX - GAMESPEED_MIN));

    previousMusicVolume = musicVolume = musicPlayer->getMusicVolume();
    musicVolumeBar.setProgress((100.0*musicVolume)/MIX_MAX_VOLUME);

    previousSfxVolume = sfxVolume = soundPlayer->getSfxVolume();
    sfxVolumeBar.setProgress((100.0*sfxVolume)/MIX_MAX_VOLUME);

    scrollSpeed = settings.general.scrollSpeed;
    scrollSpeedBar.setProgress(scrollSpeed);
}

bool InGameSettingsMenu::handleKeyPress(SDL_KeyboardEvent& key) {
    switch( key.keysym.sym ) {
        case SDLK_RETURN:
            if(SDL_GetModState() & KMOD_ALT) {
                toogleFullscreen();
            }
            break;

        case SDLK_TAB:
            if(SDL_GetModState() & KMOD_ALT) {
                SDL_MinimizeWindow(window);
            }
            break;

        default:
            break;
    }

    return Window::handleKeyPress(key);
}

void InGameSettingsMenu::onCancel() {
    soundPlayer->setSfxVolume(previousSfxVolume);
    musicPlayer->setMusicVolume(previousMusicVolume);

    Window* pParentWindow = dynamic_cast<Window*>(getParent());
    if(pParentWindow != nullptr) {
        pParentWindow->closeChildWindow();
    }
}

void InGameSettingsMenu::onOK() {
    settings.general.scrollSpeed = scrollSpeed;
    settings.audio.sfxVolume = soundPlayer->getSfxVolume();
    settings.audio.musicVolume = musicPlayer->getMusicVolume();
    settings.gameOptions.gameSpeed = newGamespeed;

    INIFile myINIFile(getConfigFilepath());
    myINIFile.setIntValue("General","Scroll Speed", settings.general.scrollSpeed);
    myINIFile.setIntValue("Audio","Music Volume", settings.audio.musicVolume);
    myINIFile.setIntValue("Audio","SFX Volume", settings.audio.sfxVolume);
    myINIFile.setIntValue("Game Options","Game Speed", settings.gameOptions.gameSpeed);
    myINIFile.saveChangesTo(getConfigFilepath());

    Window* pParentWindow = dynamic_cast<Window*>(getParent());
    if(pParentWindow != nullptr) {
        pParentWindow->closeChildWindow();
    }
}

void InGameSettingsMenu::onGameSpeedPlus() {
    if(newGamespeed > GAMESPEED_MIN)
        newGamespeed -= 1;

    gameSpeedBar.setProgress(100 - ((newGamespeed-GAMESPEED_MIN)*100)/(GAMESPEED_MAX - GAMESPEED_MIN));
}

void InGameSettingsMenu::onGameSpeedMinus() {
    if(newGamespeed < GAMESPEED_MAX)
        newGamespeed += 1;

    gameSpeedBar.setProgress(100 - ((newGamespeed-GAMESPEED_MIN)*100)/(GAMESPEED_MAX - GAMESPEED_MIN));
}

void InGameSettingsMenu::onMusicVolumePlus() {
    if(musicVolume <= MIX_MAX_VOLUME - 4) {
        musicVolume += 4;
        musicVolumeBar.setProgress((100*musicVolume)/MIX_MAX_VOLUME);
        musicPlayer->setMusicVolume(musicVolume);
    }
}

void InGameSettingsMenu::onMusicVolumeMinus() {
    if(musicVolume >= 4) {
        musicVolume -= 4;
        musicVolumeBar.setProgress((100*musicVolume)/MIX_MAX_VOLUME);
        musicPlayer->setMusicVolume(musicVolume);
    }
}

void InGameSettingsMenu::onSfxVolumePlus() {
    if(sfxVolume <= MIX_MAX_VOLUME - 4) {
        sfxVolume += 4;
        sfxVolumeBar.setProgress((100*sfxVolume)/MIX_MAX_VOLUME);
        soundPlayer->setSfxVolume(sfxVolume);
    }
}

void InGameSettingsMenu::onSfxVolumeMinus() {
    if(sfxVolume >= 4) {
        sfxVolume -= 4;
        sfxVolumeBar.setProgress((100*sfxVolume)/MIX_MAX_VOLUME);
        soundPlayer->setSfxVolume(sfxVolume);
    }
}

void InGameSettingsMenu::onScrollSpeedPlus() {
    scrollSpeed = std::min<int>(scrollSpeed+4, 100);
    scrollSpeedBar.setProgress(scrollSpeed);
}

void InGameSettingsMenu::onScrollSpeedMinus() {
    scrollSpeed = std::max<int>(scrollSpeed-4, 1);
    scrollSpeedBar.setProgress(scrollSpeed);
}
