/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the plugins of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "complexwidgets.h"

#include <qaccessible.h>
#include <qapplication.h>
#include <qabstractbutton.h>
#include <qevent.h>
#include <qheaderview.h>
#include <qtabbar.h>
#include <qcombobox.h>
#include <qlistview.h>
#include <qtableview.h>
#include <qlineedit.h>
#include <qstyle.h>
#include <qstyleoption.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qtreeview.h>
#include <private/qtabbar_p.h>
#include <QAbstractScrollArea>
#include <QScrollArea>
#include <QScrollBar>
#include <QDebug>

#ifndef QT_NO_ACCESSIBILITY

QT_BEGIN_NAMESPACE

QString Q_GUI_EXPORT qt_accStripAmp(const QString &text);

#ifndef QT_NO_TABBAR
/*!
  \class QAccessibleTabBar
  \brief The QAccessibleTabBar class implements the QAccessibleInterface for tab bars.
  \internal

  \ingroup accessibility
*/

class QAccessibleTabButton: public QAccessibleInterface, public QAccessibleActionInterface
{
public:
    QAccessibleTabButton(QTabBar *parent, int index)
        : m_parent(parent), m_index(index)
    {}

    void *interface_cast(QAccessible::InterfaceType t) {
        if (t == QAccessible::ActionInterface) {
            return static_cast<QAccessibleActionInterface*>(this);
        }
        return 0;
    }

    QObject *object() const { return 0; }
    QAccessible::Role role() const { return QAccessible::PageTab; }
    QAccessible::State state() const {
        QAccessibleInterface *parentInterface = parent();
        QAccessible::State state = parentInterface->state();
        delete parentInterface;
        return state;
    }
    QRect rect() const {
        if (!isValid())
            return QRect();

        QPoint tp = m_parent->mapToGlobal(QPoint(0,0));
        QRect rec = m_parent->tabRect(m_index);
        rec = QRect(tp.x() + rec.x(), tp.y() + rec.y(), rec.width(), rec.height());
        return rec;
    }

    bool isValid() const { return true; }// (!m_parent.isNull()) && m_parent->count() > m_index; }

    QAccessibleInterface *childAt(int, int) const { return 0; }
    int childCount() const { return 0; }
    int indexOfChild(const QAccessibleInterface *) const  { return -1; }

    QString text(QAccessible::Text) const { return qt_accStripAmp(m_parent->tabText(m_index)); }
    void setText(QAccessible::Text, const QString &) {}

    QAccessibleInterface *parent() const {
        return QAccessible::queryAccessibleInterface(m_parent);
    }
    QAccessibleInterface *child(int) const { return 0; }
    int navigate(QAccessible::RelationFlag relation, int index, QAccessibleInterface **iface) const
    {
        Q_UNUSED(relation);
        Q_UNUSED(index);
        Q_UNUSED(iface);
        return -1;
    }
    // action interface
    QStringList actionNames() const
    {
        return QStringList(pressAction());
    }

    void doAction(const QString &actionName)
    {
        if (actionName == pressAction())
            m_parent->setCurrentIndex(m_index);
    }

    QStringList keyBindingsForAction(const QString &) const
    {
        return QStringList();
    }

private:
    QPointer<QTabBar> m_parent;
    int m_index;
};

/*!
  Constructs a QAccessibleTabBar object for \a w.
*/
QAccessibleTabBar::QAccessibleTabBar(QWidget *w)
: QAccessibleWidget(w, QAccessible::PageTabList)
{
    Q_ASSERT(tabBar());
}

/*! Returns the QTabBar. */
QTabBar *QAccessibleTabBar::tabBar() const
{
    return qobject_cast<QTabBar*>(object());
}

QAccessibleInterface* QAccessibleTabBar::child(int index) const
{
    // first the tabs, then 2 buttons
    if (index < tabBar()->count()) {
        QAccessibleTabButton *button = new QAccessibleTabButton(tabBar(), index);
        return button;
    } else if (index >= tabBar()->count()) {
        // left button
        if (index - tabBar()->count() == 0) {
            return QAccessible::queryAccessibleInterface(tabBar()->d_func()->leftB);
        }
        // right button
        if (index - tabBar()->count() == 1) {
            return QAccessible::queryAccessibleInterface(tabBar()->d_func()->rightB);
        }
    }
    return 0;
}

int QAccessibleTabBar::indexOfChild(const QAccessibleInterface *child) const
{
    // FIXME this looks broken

    if (child->object() && child->object() == tabBar()->d_func()->leftB)
        return tabBar()->count();
    if (child->object() && child->object() == tabBar()->d_func()->rightB)
        return tabBar()->count() + 1;
    return -1;
}

int QAccessibleTabBar::childCount() const
{
    // tabs + scroll buttons
    return tabBar()->count() + 2;
}

QString QAccessibleTabBar::text(QAccessible::Text t) const
{
    if (t == QAccessible::Name) {
        return qt_accStripAmp(tabBar()->tabText(tabBar()->currentIndex()));
    }
    return QString();
}

/*!
    Selects the item with index \a child if \a on is true; otherwise
    unselects it. If \a extend is true and the selection mode is not
    \c Single and there is an existing selection, the selection is
    extended to include all the items from the existing selection up
    to and including the item with index \a child. Returns true if a
    selection was made or extended; otherwise returns false.

    \sa selection() clearSelection()
*/
bool QAccessibleTabBar::setSelected(int child, bool on, bool extend)
{
    if (!child || !on || extend || child > tabBar()->count())
        return false;

    if (!tabBar()->isTabEnabled(child - 1))
        return false;
    tabBar()->setCurrentIndex(child - 1);
    return true;
}

/*!
    Returns a (possibly empty) list of indexes of the items selected
    in the list box.

    \sa setSelected() clearSelection()
*/
QVector<int> QAccessibleTabBar::selection() const
{
    QVector<int> array;
    if (tabBar()->currentIndex() != -1)
        array +=tabBar()->currentIndex() + 1;
    return array;
}

#endif // QT_NO_TABBAR

#ifndef QT_NO_COMBOBOX
/*!
  \class QAccessibleComboBox
  \brief The QAccessibleComboBox class implements the QAccessibleInterface for editable and read-only combo boxes.
  \internal

  \ingroup accessibility
*/

/*!
  Constructs a QAccessibleComboBox object for \a w.
*/
QAccessibleComboBox::QAccessibleComboBox(QWidget *w)
: QAccessibleWidget(w, QAccessible::ComboBox)
{
    Q_ASSERT(comboBox());
}

/*!
  Returns the combobox.
*/
QComboBox *QAccessibleComboBox::comboBox() const
{
    return qobject_cast<QComboBox*>(object());
}

QAccessibleInterface *QAccessibleComboBox::child(int index) const
{
    if (index == 0) {
        QAbstractItemView *view = comboBox()->view();
        //QWidget *parent = view ? view->parentWidget() : 0;
        return QAccessible::queryAccessibleInterface(view);
    } else if (index == 1 && comboBox()->isEditable()) {
        return QAccessible::queryAccessibleInterface(comboBox()->lineEdit());
    }
    return 0;
}

int QAccessibleComboBox::childCount() const
{
    // list and text edit
    return comboBox()->isEditable() ? 2 : 1;
}

QAccessibleInterface *QAccessibleComboBox::childAt(int x, int y) const
{
    if (comboBox()->isEditable() && comboBox()->lineEdit()->rect().contains(x, y))
        return child(1);
    return 0;
}

int QAccessibleComboBox::indexOfChild(const QAccessibleInterface *child) const
{
    if (comboBox()->view() == child->object())
        return 0;
    if (comboBox()->isEditable() && comboBox()->lineEdit() == child->object())
        return 1;
    return -1;
}

/*! \reimp */
QString QAccessibleComboBox::text(QAccessible::Text t) const
{
    QString str;

    switch (t) {
    case QAccessible::Name:
#ifndef Q_OS_UNIX // on Linux we use relations for this, name is text (fall through to Value)
        str = QAccessibleWidget::text(t);
        break;
#endif
    case QAccessible::Value:
        if (comboBox()->isEditable())
            str = comboBox()->lineEdit()->text();
        else
            str = comboBox()->currentText();
        break;
#ifndef QT_NO_SHORTCUT
    case QAccessible::Accelerator:
        str = (QString)QKeySequence(Qt::Key_Down);
        break;
#endif
    default:
        break;
    }
    if (str.isEmpty())
        str = QAccessibleWidget::text(t);
    return str;
}

QStringList QAccessibleComboBox::actionNames() const
{
    return QStringList(showMenuAction());
}

QString QAccessibleComboBox::localizedActionDescription(const QString &actionName) const
{
    if (actionName == showMenuAction())
        return QComboBox::tr("Open the combo box selection popup");
    return QString();
}

void QAccessibleComboBox::doAction(const QString &actionName)
{
    if (actionName == showMenuAction()) {
        if (comboBox()->view()->isVisible()) {
            comboBox()->hidePopup();
        } else {
            comboBox()->showPopup();
        }
    }
}

QStringList QAccessibleComboBox::keyBindingsForAction(const QString &/*actionName*/) const
{
    return QStringList();
}

#endif // QT_NO_COMBOBOX

static inline void removeInvisibleWidgetsFromList(QWidgetList *list)
{
    if (!list || list->isEmpty())
        return;

    for (int i = 0; i < list->count(); ++i) {
        QWidget *widget = list->at(i);
        if (!widget->isVisible())
            list->removeAt(i);
    }
}

#ifndef QT_NO_SCROLLAREA
// ======================= QAccessibleAbstractScrollArea =======================
QAccessibleAbstractScrollArea::QAccessibleAbstractScrollArea(QWidget *widget)
    : QAccessibleWidget(widget, QAccessible::Client)
{
    Q_ASSERT(qobject_cast<QAbstractScrollArea *>(widget));
}

QAccessibleInterface *QAccessibleAbstractScrollArea::child(int index) const
{
    return QAccessible::queryAccessibleInterface(accessibleChildren().at(index));
}

int QAccessibleAbstractScrollArea::childCount() const
{
    return accessibleChildren().count();
}

int QAccessibleAbstractScrollArea::indexOfChild(const QAccessibleInterface *child) const
{
    if (!child || !child->object())
        return -1;
    return accessibleChildren().indexOf(qobject_cast<QWidget *>(child->object()));
}

bool QAccessibleAbstractScrollArea::isValid() const
{
    return (QAccessibleWidget::isValid() && abstractScrollArea() && abstractScrollArea()->viewport());
}

QAccessibleInterface *QAccessibleAbstractScrollArea::childAt(int x, int y) const
{
    if (!abstractScrollArea()->isVisible())
        return 0;

    for (int i = 0; i < childCount(); ++i) {
        QPoint wpos = accessibleChildren().at(i)->mapToGlobal(QPoint(0, 0));
        QRect rect = QRect(wpos, accessibleChildren().at(i)->size());
        if (rect.contains(x, y))
            return child(i);
    }
    return 0;
}

QAbstractScrollArea *QAccessibleAbstractScrollArea::abstractScrollArea() const
{
    return static_cast<QAbstractScrollArea *>(object());
}

QWidgetList QAccessibleAbstractScrollArea::accessibleChildren() const
{
    QWidgetList children;

    // Viewport.
    QWidget * viewport = abstractScrollArea()->viewport();
    if (viewport)
        children.append(viewport);

    // Horizontal scrollBar container.
    QScrollBar *horizontalScrollBar = abstractScrollArea()->horizontalScrollBar();
    if (horizontalScrollBar && horizontalScrollBar->isVisible()) {
        children.append(horizontalScrollBar->parentWidget());
    }

    // Vertical scrollBar container.
    QScrollBar *verticalScrollBar = abstractScrollArea()->verticalScrollBar();
    if (verticalScrollBar && verticalScrollBar->isVisible()) {
        children.append(verticalScrollBar->parentWidget());
    }

    // CornerWidget.
    QWidget *cornerWidget = abstractScrollArea()->cornerWidget();
    if (cornerWidget && cornerWidget->isVisible())
        children.append(cornerWidget);

    return children;
}

QAccessibleAbstractScrollArea::AbstractScrollAreaElement
QAccessibleAbstractScrollArea::elementType(QWidget *widget) const
{
    if (!widget)
        return Undefined;

    if (widget == abstractScrollArea())
        return Self;
    if (widget == abstractScrollArea()->viewport())
        return Viewport;
    if (widget->objectName() == QLatin1String("qt_scrollarea_hcontainer"))
        return HorizontalContainer;
    if (widget->objectName() == QLatin1String("qt_scrollarea_vcontainer"))
        return VerticalContainer;
    if (widget == abstractScrollArea()->cornerWidget())
        return CornerWidget;

    return Undefined;
}

bool QAccessibleAbstractScrollArea::isLeftToRight() const
{
    return abstractScrollArea()->isLeftToRight();
}

// ======================= QAccessibleScrollArea ===========================
QAccessibleScrollArea::QAccessibleScrollArea(QWidget *widget)
    : QAccessibleAbstractScrollArea(widget)
{
    Q_ASSERT(qobject_cast<QScrollArea *>(widget));
}
#endif // QT_NO_SCROLLAREA

QT_END_NAMESPACE

#endif // QT_NO_ACCESSIBILITY
