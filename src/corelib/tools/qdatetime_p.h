/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QDATETIME_P_H
#define QDATETIME_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include "qplatformdefs.h"
#include "QtCore/qatomic.h"
#include "QtCore/qdatetime.h"
#include "QtCore/qpair.h"

#include "qtimezone.h"

QT_BEGIN_NAMESPACE

class QDateTimePrivate : public QSharedData
{
public:
    // Never change or delete this enum, it is required for backwards compatible
    // serialization of QDateTime before 5.2, so is essentially public API
    enum Spec {
        LocalUnknown = -1,
        LocalStandard = 0,
        LocalDST = 1,
        UTC = 2,
        OffsetFromUTC = 3,
        TimeZone = 4
    };

    // Daylight Time Status
    enum DaylightStatus {
        UnknownDaylightTime = -1,
        StandardTime = 0,
        DaylightTime = 1
    };

    // Status of date/time
    enum StatusFlag {
        NullDate            = 0x01,
        NullTime            = 0x02,
        ValidDate           = 0x04, // just the date field
        ValidTime           = 0x08, // just the time field
        ValidDateTime       = 0x10, // the whole object (including timezone)
        SetToStandardTime   = 0x40,
        SetToDaylightTime   = 0x80
    };
    Q_DECLARE_FLAGS(StatusFlags, StatusFlag)

    QDateTimePrivate() : m_msecs(0),
                         m_spec(Qt::LocalTime),
                         m_offsetFromUtc(0),
                         m_status(NullDate | NullTime)
    {}

    QDateTimePrivate(const QDate &toDate, const QTime &toTime, Qt::TimeSpec toSpec,
                     int offsetSeconds);

#ifndef QT_BOOTSTRAPPED
    QDateTimePrivate(const QDate &toDate, const QTime &toTime, const QTimeZone & timeZone);
#endif // QT_BOOTSTRAPPED

    // ### XXX: when the tooling situation improves, look at fixing the padding.
    // 4 bytes padding

    qint64 m_msecs;
    Qt::TimeSpec m_spec;
    int m_offsetFromUtc;
#ifndef QT_BOOTSTRAPPED
    QTimeZone m_timeZone;
#endif // QT_BOOTSTRAPPED
    StatusFlags m_status;

    void setTimeSpec(Qt::TimeSpec spec, int offsetSeconds);
    void setDateTime(const QDate &date, const QTime &time);
    QPair<QDate, QTime> getDateTime() const;

    void setDaylightStatus(DaylightStatus status);
    DaylightStatus daylightStatus() const;

    // Returns msecs since epoch, assumes offset value is current
    inline qint64 toMSecsSinceEpoch() const;

    void checkValidDateTime();
    void refreshDateTime();

    // Get/set date and time status
    inline bool isNullDate() const { return !(m_status & ValidDate); }
    inline bool isNullTime() const { return !(m_status & ValidTime); }
    inline bool isValidDate() const { return m_status & ValidDate; }
    inline bool isValidTime() const { return m_status & ValidTime; }
    inline bool isValidDateTime() const { return m_status & ValidDateTime; }
    inline void setValidDateTime() { m_status |= ValidDateTime; }
    inline void clearValidDateTime() { m_status &= ~ValidDateTime; }
    inline void clearSetToDaylightStatus() { m_status &= ~(SetToStandardTime | SetToDaylightTime); }

#ifndef QT_BOOTSTRAPPED
    static qint64 zoneMSecsToEpochMSecs(qint64 msecs, const QTimeZone &zone,
                                        QDate *localDate = 0, QTime *localTime = 0);
#endif // QT_BOOTSTRAPPED

    static inline qint64 minJd() { return QDate::minJd(); }
    static inline qint64 maxJd() { return QDate::maxJd(); }
};

QT_END_NAMESPACE

#endif // QDATETIME_P_H
