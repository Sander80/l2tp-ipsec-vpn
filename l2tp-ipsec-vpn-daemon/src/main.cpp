/*
 * $Id: main.cpp 10 2010-09-17 09:13:01Z werner $
 *
 * File:   main.cpp
 * Author: Werner Jaeger
 *
 * Created on August 25, 2010, 4:52 PM
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
#include "VpnControlDaemonApplication.h"

int main(int iArgc, char* pcaArgv[])
{
   VpnControlDaemonApplication service(iArgc, pcaArgv);
   return(service.daemonize());
}
