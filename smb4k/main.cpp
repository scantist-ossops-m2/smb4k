/***************************************************************************
    main.cpp  -  Main file of the Smb4K program.
                             -------------------
    begin                : Sam Mär  1 14:57:21 CET 2003
    copyright            : (C) 2003-2015 by Alexander Reinholdt
    email                : alexander.reinholdt@kdemail.net
 ***************************************************************************/

/***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   General Public License for more details.                              *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc., 51 Franklin Street, Suite 500, Boston,*
 *   MA 02110-1335, USA                                                    *
 ***************************************************************************/

#include <config.h>

// application specific includes
#include "smb4kmainwindow.h"
#include "core/smb4ksettings.h"
#include "core/smb4kglobal.h"

// Qt includes
#include <QString>
#include <QApplication>

// KDE includes
#include <KI18n/KLocalizedString>
#include <KCoreAddons/KAboutData>
#include <KDBusAddons/KDBusService>

using namespace Smb4KGlobal;


int main(int argc, char **argv)
{
  // Create the application.
  QApplication app(argc, argv);
  
  // Connect the application with the translation catalog
  KLocalizedString::setApplicationDomain("smb4k");
  
  // Create the about data for Smb4K  
  KAboutData aboutData(QStringLiteral("smb4k"), i18n("Smb4K"), QStringLiteral(VERSION),
    i18n("The advanced network neighborhood browser and Samba share mounting utility for KDE."),
    KAboutLicense::GPL_V2, i18n("\u00A9 2003-2015 Alexander Reinholdt"), QString(), 
    QStringLiteral("http://smb4k.sourceforge.net"), QStringLiteral("smb4k-bugs@lists.sourceforge.net"));
  
  // DBus prefix
  aboutData.setOrganizationDomain("sourceforge.net");
  
  // Authors
  aboutData.addAuthor(i18n("Alexander Reinholdt"),
                      i18n("Developer"),
                      QStringLiteral("alexander.reinholdt@kdemail.net"));
  
  // Register about data
  KAboutData::setApplicationData(aboutData);
  
  // Now add the data to the application
  app.setApplicationName(aboutData.componentName());
  app.setApplicationDisplayName(aboutData.displayName());
  app.setOrganizationDomain(aboutData.organizationDomain());
  app.setApplicationVersion(aboutData.version());
  
  // We need to set this property because otherwise the application
  // will quit when it is embedded into the system tray, the main window
  // is hidden and the last window that was opened through the system
  // tray is closed.
  app.setQuitOnLastWindowClosed(false);
  
  // Program icon
  app.setWindowIcon(QIcon::fromTheme(QLatin1String("smb4k")));
  
  // Launch the main window
  Smb4KMainWindow *main_window = new Smb4KMainWindow();
  main_window->setVisible(!Smb4KSettings::startMainWindowDocked());

  // Initialize the core. Use a busy cursor.
  initCore(true);
  
  // Unique application
  const KDBusService service(KDBusService::Unique);
  
  // Start the application
  return app.exec();
}
