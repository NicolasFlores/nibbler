/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrrKlangSoundLib.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <nflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 14:45:43 by nflores           #+#    #+#             */
/*   Updated: 2018/05/25 12:08:01 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IrrKlangSoundLib.hpp"

// Constructors

IrrKlangSoundLib::IrrKlangSoundLib () {
    _engine = irrklang::createIrrKlangDevice();
    if (_engine == NULL)
        _error = "Error starting up the engine";
    else
        _error = "";
}

IrrKlangSoundLib::~IrrKlangSoundLib() {
    _engine->drop();
}

// Operators

IrrKlangSoundLib &  IrrKlangSoundLib::operator=(IrrKlangSoundLib const & iks) {
    this->_engine = iks.getEngine();
    this->_error = iks.getError();
    return *this;
}

// Getters Setters

std::string     IrrKlangSoundLib::getError() const {
    return _error;
}

void            IrrKlangSoundLib::setError(std::string error) {
    _error = error;
}

irrklang::ISoundEngine * IrrKlangSoundLib::getEngine() const {
    return _engine;
}

// Methods

void            IrrKlangSoundLib::playMusic(std::string file, bool loop) {
    _engine->play2D(file.c_str(), loop);
}


ISoundLib * createSoundLib() {
    return new IrrKlangSoundLib();
}

void        deleteSoundLib(ISoundLib *lib) {
    IrrKlangSoundLib * sound = dynamic_cast<IrrKlangSoundLib *>(lib);
	delete sound;
}