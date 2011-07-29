/*
 * $Id: PasswordCallback.h 24 2010-10-07 12:35:00Z werner $
 *
 * File:   PasswordCallback.h
 * Author: Werner Jaeger
 *
 * Created on September 1, 2010, 4:20 PM
 *
 * Copyright 2010 Werner Jaeger.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PASSWORDCALLBACK_H
#define	PASSWORDCALLBACK_H

class L2tpIPsecVpnApplication;

class PasswordCallback
{
public:
   PasswordCallback(L2tpIPsecVpnApplication& application);
   virtual ~PasswordCallback();

   int exec() const;

private:
   PasswordCallback(const PasswordCallback& orig);
   PasswordCallback& operator=(const PasswordCallback& orig);

   L2tpIPsecVpnApplication& m_Application;
};

#endif	/* PASSWORDCALLBACK_H */

