/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ISoundLib.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <nflores@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 10:15:15 by nflores           #+#    #+#             */
/*   Updated: 2018/05/24 10:51:21 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef I_SOUND_LIB_HPP
#define I_SOUND_LIB_HPP

#include <iostream>

class ISoundLib {
public:
	virtual 			~ISoundLib() {}
	virtual void 		playMusic(std::string file, bool loop) = 0;
	virtual std::string getError() const = 0;
};

typedef ISoundLib* (*t_snd_openner)(void);
typedef void (*t_snd_closer)(ISoundLib*);

#endif
