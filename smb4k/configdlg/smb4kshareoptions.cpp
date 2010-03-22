/***************************************************************************
    smb4kshareoptions  -  The configuration page for the settings of
    Smb4K regarding share management
                             -------------------
    begin                : Sa Nov 15 2003
    copyright            : (C) 2003-2010 by Alexander Reinholdt
    email                : dustpuppy@users.berlios.de
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
 *   Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston,   *
 *   MA  02111-1307 USA                                                    *
 ***************************************************************************/

// Qt includes
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QCheckBox>
#include <QButtonGroup>

// KDE includes
#include <klocale.h>
#include <kurlrequester.h>
#include <knuminput.h>
#include <klineedit.h>

// applications specific includes
#include "smb4kshareoptions.h"
#include <core/smb4ksettings.h>


Smb4KShareOptions::Smb4KShareOptions( QWidget *parent )
: QWidget( parent )
{
  QGridLayout *layout           = new QGridLayout( this );
  layout->setSpacing( 5 );
  layout->setMargin( 0 );

  // Directories
  QGroupBox *directory_box      = new QGroupBox( i18n( "Directories" ), this );

  QGridLayout *directory_layout = new QGridLayout( directory_box );
  directory_layout->setSpacing( 5 );

  QLabel *prefix_label          = new QLabel( Smb4KSettings::self()->mountPrefixItem()->label(),
                                  directory_box );

  KUrlRequester *prefix         = new KUrlRequester( directory_box );
  prefix->setMode( KFile::Directory | KFile::LocalOnly );
  prefix->setObjectName( "kcfg_MountPrefix" );

  QCheckBox *lowercase_subdirs  = new QCheckBox( Smb4KSettings::self()->forceLowerCaseSubdirsItem()->label(),
                                  directory_box );
  lowercase_subdirs->setObjectName( "kcfg_ForceLowerCaseSubdirs" );

  directory_layout->addWidget( prefix_label, 0, 0, 0 );
  directory_layout->addWidget( prefix, 0, 1, 0 );
  directory_layout->addWidget( lowercase_subdirs, 1, 0, 1, 2, 0 );

  // Mounting and unmounting
  QGroupBox *mount_box          = new QGroupBox( i18n( "Mounting && Unmounting" ), this );

  QGridLayout *mount_layout     = new QGridLayout( mount_box );
  mount_layout->setSpacing( 5 );

  QCheckBox *unmount_all_shares = new QCheckBox( Smb4KSettings::self()->unmountSharesOnExitItem()->label(),
                                  mount_box );
  unmount_all_shares->setObjectName( "kcfg_UnmountSharesOnExit" );


  QCheckBox *remount_shares     = new QCheckBox( Smb4KSettings::self()->remountSharesItem()->label(),
                                  mount_box );
  remount_shares->setObjectName( "kcfg_RemountShares" );

  QCheckBox *allow_foreign      = new QCheckBox( Smb4KSettings::self()->unmountForeignSharesItem()->label(),
                                  mount_box );
  allow_foreign->setObjectName( "kcfg_UnmountForeignShares" );

  mount_layout->addWidget( unmount_all_shares, 0, 0, 0 );
  mount_layout->addWidget( remount_shares, 1, 0, 0 );
  mount_layout->addWidget( allow_foreign, 2, 0, 0 );

  // Checks
  QGroupBox *checks_box         = new QGroupBox( i18n( "Checks" ), this );

  QGridLayout *checks_layout    = new QGridLayout( checks_box );
  checks_layout->setSpacing( 5 );

  QLabel *check_interval_label  = new QLabel( Smb4KSettings::self()->checkIntervalItem()->label(),
                                  checks_box );

  KIntNumInput *check_interval  = new KIntNumInput( checks_box );
  check_interval->setObjectName( "kcfg_CheckInterval" );
  check_interval->setSuffix( " ms" );

  checks_layout->addWidget( check_interval_label, 0, 0, 0 );
  checks_layout->addWidget( check_interval, 0, 1, 0 );

  QSpacerItem *spacer = new QSpacerItem( 10, 10, QSizePolicy::Preferred, QSizePolicy::Expanding );

  layout->addWidget( directory_box, 0, 0, 0 );
  layout->addWidget( mount_box, 1, 0, 0 );
  layout->addWidget( checks_box, 2, 0, 0 );
  layout->addItem( spacer, 3, 0, 1, 1, 0 );
}

Smb4KShareOptions::~Smb4KShareOptions()
{
}


#include "smb4kshareoptions.moc"
