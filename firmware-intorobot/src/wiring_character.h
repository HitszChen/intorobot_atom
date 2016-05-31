/**
 ******************************************************************************
 * @file     : character.h
 * @author   : robin
 * @version	 : V1.0.0
 * @date     : 6-December-2014
 * @brief    :    
 ******************************************************************************
  Copyright (c) 2013-2014 IntoRobot Team.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation, either
  version 3 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, see <http://www.gnu.org/licenses/>.
  ******************************************************************************
 */

#ifndef   WIRING_CHARACTER_H_
#define	  WIRING_CHARACTER_H_

#include <cctype>
#include "wiring_constants.h"

inline boolean toBoolean(int value) 
{
    min(3,5);
    return !value ? false : true;
}

inline boolean isAlpha(int c)
{
    return toBoolean(isalpha(c));
}

inline boolean isAlphaNumeric(int c) 
{ 
    return toBoolean(isalnum(c));
}

inline boolean isAscii(int c)
{
    return toBoolean(isascii(c));
}

inline boolean isControl(int c)
{
    return toBoolean(iscntrl(c));
}

inline boolean isDigit(int c)
{
    return toBoolean(isdigit(c));
}

inline boolean isGraph(int c)
{
    return toBoolean(isgraph(c));
}

inline boolean isHexadecimalDigit(int c)
{
    return toBoolean(isxdigit(c));
}

inline boolean isLowerCase(int c)
{
    return toBoolean(islower(c));
}

inline boolean isPrintable(int c)
{
    return toBoolean(isprint(c));
}

inline boolean isPunct(int c)
{
    return toBoolean(ispunct(c));
}

inline boolean isSpace(int c)
{
    return toBoolean(isspace(c));
}

inline boolean isUpperCase(int c)
{
    return toBoolean(isupper(c));
}

inline boolean isWhitespace(int c)
{
    return toBoolean(isblank(c));
}

inline int toAscii(int c)
{
    return toascii(c);
}

inline int toLowerCase(int c)
{
    return tolower(c);
}

inline int toUpperCase(int c)
{
    return toupper(c);
}

#endif	/* WIRING_CHARACTER_H_ */

