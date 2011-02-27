/***************************************************************************
    smb4ksynchronizer_p  -  This file contains private helper classes for
    the Smb4KSynchronizer class.
                             -------------------
    begin                : Fr Okt 24 2008
    copyright            : (C) 2008-2011 by Alexander Reinholdt
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
 *   Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston,   *
 *   MA  02111-1307 USA                                                    *
 ***************************************************************************/

#ifndef SMB4KSYNCHRONIZER_P_H
#define SMB4KSYNCHRONIZER_P_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

// KDE includes
#include <kjob.h>
#include <kurlrequester.h>
#include <kdialog.h>

// application specific includes
#include <smb4ksynchronizer.h>
#include <smb4kprocess.h>


class Smb4KSyncJob : public KJob
{
  Q_OBJECT

  public:
    /**
     * Constructor
     */
    Smb4KSyncJob( QObject *parent = 0 );

    /**
     * Destructor
     */
    ~Smb4KSyncJob();

    /**
     * Returns TRUE if the job was started and FALSE
     * otherwise
     * 
     * @returns TRUE if the job was started
     */
    bool isStarted() { return m_started; }

    /**
     * Starts the synchronization
     */
    void start();

    /**
     * Sets the path of the source @param src and of the destination
     * @param dest.
     *
     * This function must be called before start() is run.
     *
     * @param src       The source
     *
     * @param dest      The destination
     */
    void setPaths( const KUrl &src,
                   const KUrl &dest );

    /**
     * Returns the source directory.
     *
     * @returns the source directory.
     */
    const KUrl &source() { return m_src; }

    /**
     * Returns the destination directory.
     *
     * @returns the destination directory.
     */
    const KUrl &destination() { return m_dest; }
     
  protected:
    /**
     * Reimplemented from KJob. Kills the internal process and
     * then the job itself.
     */
    bool doKill();
    
  protected slots:
    void slotStartSynchronization();
    void slotReadStandardOutput();
    void slotReadStandardError();
    void slotProcessFinished( int exitCode, QProcess::ExitStatus status );

  private:
    bool m_started;
    KUrl m_src;
    KUrl m_dest;
    Smb4KProcess *m_proc;
};


class Smb4KSynchronizationDialog : public KDialog
{
  Q_OBJECT

  public:
    /**
     * The constructor
     *
     * @param share         The share item
     *
     * @param parent        The parent widget
     */
    Smb4KSynchronizationDialog( Smb4KShare *share, QWidget *parent = 0 );

    /**
     * The destructor
     */
    ~Smb4KSynchronizationDialog();

    /**
     * The source URL
     */
    const KUrl source();

    /**
     * The destination URL
     */
    const KUrl destination();

  protected slots:
    /**
     * This slot is called when the User1 button is clicked.
     * It initializes the synchronization.
     */
    void slotUser1Clicked();

    /**
     * This slot is called when the User2 button is clicked.
     * It swaps the source and destination.
     */
    void slotUser2Clicked();

    /**
     * This slot is called when the Cancel button is clicked.
     * It aborts any action the synchronizer is performing.
     */
    void slotUser3Clicked();

  private:
    /**
     * A pointer to the share object
     */
    Smb4KShare *m_share;

    /**
     * The source URL requester
     */
    KUrlRequester *m_source;

    /**
     * The destination URL requester
     */
    KUrlRequester *m_destination;
};


class Smb4KSynchronizerPrivate
{
  public:
    Smb4KSynchronizerPrivate() {};
    ~Smb4KSynchronizerPrivate() {};
    Smb4KSynchronizer instance;
};

#endif
