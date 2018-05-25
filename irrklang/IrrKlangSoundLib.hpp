/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrrKlangSoundLib.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <nflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 14:39:12 by nflores           #+#    #+#             */
/*   Updated: 2018/05/25 13:03:16 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRR_KLANG_SOUND_LIB_HPP
#define IRR_KLANG_SOUND_LIB_HPP

#include "../lib/irrKlang/irrKlang-64bit-1.6.0/include/irrKlang.h"
#include "../src/ISoundLib.hpp"

class IrrKlangSoundLib : public ISoundLib {
public:
	IrrKlangSoundLib();
	~IrrKlangSoundLib();

	IrrKlangSoundLib & 			operator=(IrrKlangSoundLib const & iks);

	void        				playMusic(std::string file, bool loop);

	std::string 				getError() const;
	void        				setError(std::string error);
	irrklang::ISoundEngine *	getEngine() const;

private:
	IrrKlangSoundLib(IrrKlangSoundLib const & iks);
	irrklang::ISoundEngine *	_engine;
	std::string					_error;
};

extern "C" {
	ISoundLib *		createSoundLib();
	void			deleteSoundLib(ISoundLib * lib);
}

#endif
