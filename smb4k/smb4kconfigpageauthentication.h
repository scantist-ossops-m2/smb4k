/***************************************************************************
    The configuration page for the authentication settings of Smb4K
                             -------------------
    begin                : Sa Nov 15 2003
    copyright            : (C) 2003-2019 by Alexander Reinholdt
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

#ifndef SMB4KCONFIGPAGEAUTHENTICATION_H
#define SMB4KCONFIGPAGEAUTHENTICATION_H

// Application specific includes
#include "core/smb4kauthinfo.h"

// Qt includes
#include <QList>
#include <QTableWidget>
#include <QCheckBox>
#include <QPushButton>
#include <QTabWidget>
#include <QListWidget>

// KDE includes
#include <KWidgetsAddons/KActionMenu>
#include <KXmlGui/KActionCollection>

/**
 * This is the configuration tab for the authentication settings
 * of Smb4K.
 *
 * @author Alexander Reinholdt <alexander.reinholdt@kdemail.net>
 */


class Smb4KConfigPageAuthentication : public QWidget
{
  Q_OBJECT

  public:
    /**
     * The constructor.
     *
     * @param parent          The parent widget
     */
    explicit Smb4KConfigPageAuthentication(QWidget *parent = 0);

    /**
     * The destructor.
     */
    virtual ~Smb4KConfigPageAuthentication();
    
    /**
     * Insert the list of authentication information entries into the internal
     * list of wallet entries. This function will not display the entries. You
     * need to call displayWalletEntries() for this.
     * 
     * @param entries       The list of entries
     */
    void insertWalletEntries(const QList<Smb4KAuthInfo *> &entries);
    
    /**
     * Get the - maybe modified - entries.
     * 
     * @returns the list of entries.
     */
    const QList<Smb4KAuthInfo *> &getWalletEntries() { return m_entries_list; }
    
    /**
     * Display the authentication information in the list widget.
     * Use this function AFTER setEntries() if necessary.
     */
    void displayWalletEntries();
    
    /**
     * Returns TRUE if the wallet entries are displayed and FALSE otherwise.
     * 
     * @returns TRUE if the wallet entries are displayed
     */
    bool walletEntriesDisplayed() { return m_entries_displayed; }
    
    /**
     * Returns TRUE in the case the wallet entries might have changed. You need
     * to check this outside this widget, whether a change indeed occurred.
     * 
     * @returns TRUE if the wallet entries might have changed.
     */
    bool walletEntriesMaybeChanged() { return m_maybe_changed; }
    
  signals:
    /**
     * Emitted when the "Load" button is clicked.
     */
    void loadWalletEntries();
    
    /**
     * Emitted when the "Save" button is clicked.
     */
    void saveWalletEntries();
    
    /**
     * Emitted when the default login should be (re-)defined.
     */
    void setDefaultLogin();
    
    /**
     * This signal is emitted every time the wallet entries potentially were 
     * modified by the user. When this signal is emitted, it does not necessarily 
     * mean that any wallet entry indeed changed. It only means that the user 
     * edited one.
     */
    void walletEntriesModified();
    
  protected:
    /**
     * Reimplemented.
     */
    bool eventFilter(QObject *object, QEvent *event) override;
    
  protected slots:
    /**
     * This slot is called when the "Use wallet" check box is toggled.
     *
     * @param checked       TRUE if the check box is checked and otherwise
     *                      FALSE.
     */
    void slotKWalletButtonToggled(bool checked);

    /**
     * This slot is invoked when the "Default login" check box is toggled.
     *
     * @param checked       TRUE if the check box is checked and otherwise
     *                      FALSE.
     */
    void slotDefaultLoginToggled(bool checked);
    
    /**
     * This slot is connected to the "Details" button and shows the details
     * of the selected wallet entry.
     * 
     * @param checked       TRUE if the button is checked
     */
    void slotDetailsClicked(bool checked);
    
    /**
     * This slot is connected to the KListWidget::itemSelectionChanged() signal.
     * It unmarks and enables/disables the "Show details" checkbox and clears the
     * the details widget.
     */
    void slotItemSelectionChanged();
    
    /**
     * This slot is connected to the QTableWidget::cellChanged() signal and commits
     * changes the user applied to the entries to the internal list and enables the
     * "Undo" action. 
     *
     * @param row             The row of the cell that was changed
     * 
     * @param column          The column of the cell that was changed
     */
    void slotDetailsChanged(int row, int column);
    
    /**
     * This slot is connected to the "Remove" action
     * 
     * @param checked         TRUE if the action is checked
     */
    void slotRemoveActionTriggered(bool checked);
    
    /**
     * This slot is connected to the "Clear List" action
     * 
     * @param checked         TRUE if the action is checked
     */
    void slotClearActionTriggered(bool checked);
    
    /**
     * This slot is connected to the "Edit" action in the table widget.
     * 
     * @param checked         TRUE if the action is checked
     */
    void slotEditActionTriggered(bool checked);
    
    /**
     * This slot is connected to the "Save" button and resets all actions.
     * 
     * @param checked         TRUE if the action is checked
     */
    void slotSaveClicked(bool checked);
    
  private:
    void showDetails(Smb4KAuthInfo *authInfo);
    void clearDetails();
    QListWidget *m_entries_widget;
    QCheckBox *m_details_box;
    QTableWidget *m_details_widget;
    QList<Smb4KAuthInfo *> m_entries_list;
    bool m_entries_displayed;
    bool m_loading_details;
    bool m_maybe_changed;
};

#endif
