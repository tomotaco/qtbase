/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the test suite of the Qt Toolkit.
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
struct LV {
    const char *name;
    const char *logical;
    const char *visual;
    int basicDir;
};

const LV logical_visual[] = {
    { "data0", "Hello", "Hello", QChar::DirL },
    { "data1", "\327\251\327\234\327\225\327\235", "\327\235\327\225\327\234\327\251", QChar::DirR },
    { "data2", "Hello \327\251\327\234\327\225\327\235", "Hello \327\235\327\225\327\234\327\251", QChar::DirL },
    { "data3", "car is \327\236\327\233\327\225\327\240\327\231\327\252 \327\220\327\225\327\230\327\225 in hebrew", "car is \327\225\327\230\327\225\327\220 \327\252\327\231\327\240\327\225\327\233\327\236 in hebrew", QChar::DirL },
    { "data4", "\327\236\327\233\327\225\327\240\327\231\327\252 \327\224\327\231\327\220 the car \327\221\327\251\327\244\327\224 \327\224\327\220\327\240\327\222\327\234\327\231\327\252", "\327\252\327\231\327\234\327\222\327\240\327\220\327\224 \327\224\327\244\327\251\327\221 the car \327\220\327\231\327\224 \327\252\327\231\327\240\327\225\327\233\327\236", QChar::DirR },
    { "data5", "he said \"\327\226\327\224 \327\251\327\225\327\225\327\224 123, 456, \327\221\327\241\327\223\327\250\" ", "he said \"\327\250\327\223\327\241\327\221 ,456 ,123 \327\224\327\225\327\225\327\251 \327\224\327\226\" ", QChar::DirL },
    { "data6", "he said \"\327\226\327\224 \327\251\327\225\327\225\327\224 (123, 456), \327\221\327\241\327\223\327\250\"", "he said \"\327\250\327\223\327\241\327\221 ,(456 ,123) \327\224\327\225\327\225\327\251 \327\224\327\226\"", QChar::DirL },
    { "data7", "he said \"\327\226\327\224 \327\251\327\225\327\225\327\224 123,456, \327\221\327\241\327\223\327\250\"", "he said \"\327\250\327\223\327\241\327\221 ,123,456 \327\224\327\225\327\225\327\251 \327\224\327\226\"", QChar::DirL },
    { "data8", "he said \"\327\226\327\224 \327\251\327\225\327\225\327\224 ,(123,456) \327\221\327\241\327\223\327\250\"", "he said \"\327\250\327\223\327\241\327\221 (123,456), \327\224\327\225\327\225\327\251 \327\224\327\226\"", QChar::DirL },
    { "data9", "\327\224\327\225\327\220 \327\220\327\236\327\250 \"it is 123, 456, ok\"", "\"it is 123, 456, ok\" \327\250\327\236\327\220 \327\220\327\225\327\224", QChar::DirR },
    { "data10", "<\327\233123>shalom</\327\233123>", "<123\327\233/>shalom<123\327\233>", QChar::DirR },
    { "data11", "<h123>\327\251\327\234\327\225\327\235</h123>", "<h123>\327\235\327\225\327\234\327\251</h123>", QChar::DirL },
    { "data12", "\327\224\327\225\327\220 \327\220\327\236\327\250 \"it is a car!\" \327\225\327\220\327\226 \327\250\327\245", "\327\245\327\250 \327\226\327\220\327\225 \"!it is a car\" \327\250\327\236\327\220 \327\220\327\225\327\224", QChar::DirR },
    { "data13", "\327\224\327\225\327\220 \327\220\327\236\327\250 \"it is a car!x\" \327\225\327\220\327\226 \327\250\327\245", "\327\245\327\250 \327\226\327\220\327\225 \"it is a car!x\" \327\250\327\236\327\220 \327\220\327\225\327\224", QChar::DirR },
    { "data14", "-2 \327\236\327\242\327\234\327\225\327\252 \327\226\327\224 \327\247\327\250", "\327\250\327\247 \327\224\327\226 \327\252\327\225\327\234\327\242\327\236 2-", QChar::DirR },
    { "data15", "-10% \327\251\327\231\327\240\327\225\327\231", "\327\231\327\225\327\240\327\231\327\251 10%-", QChar::DirR },
    { "data16", "\327\224\327\230\327\225\327\225\327\227 \327\224\327\231\327\240\327\225 2.5..5", "5..2.5 \327\225\327\240\327\231\327\224 \327\227\327\225\327\225\327\230\327\224", QChar::DirR },
    { "data17", "he said \"\327\226\327\225 \327\236\327\233\327\225\327\240\327\231\327\252!\"", "he said \"\327\252\327\231\327\240\327\225\327\233\327\236 \327\225\327\226!\"", QChar::DirL },
    { "data18", "he said \"\327\226\327\225 \327\236\327\233\327\225\327\240\327\231\327\252!\327\251\"", "he said \"\327\251!\327\252\327\231\327\240\327\225\327\233\327\236 \327\225\327\226\"", QChar::DirL },
    { "data19", "(\327\240\327\231\327\241\327\225\327\231) abc", "abc (\327\231\327\225\327\241\327\231\327\240)", QChar::DirR },
    { "data20", "abc (\327\240\327\231\327\241\327\225\327\231)", "abc (\327\231\327\225\327\241\327\231\327\240)", QChar::DirL },
    { "data21", "\327\240\327\231\327\241\327\225\327\231 23 \327\231\327\227\327\231\327\223 abc", "abc \327\223\327\231\327\227\327\231 23 \327\231\327\225\327\241\327\231\327\240", QChar::DirR },
    { "data22", "#@$ \327\240\327\231\327\241\327\225\327\231", "\327\231\327\225\327\241\327\231\327\240 $@#", QChar::DirR },
    { "data23", "\327\240\327\231\327\241\327\225\327\231 ~~~23%%% \327\231\327\227\327\231\327\223 abc ", " abc \327\223\327\231\327\227\327\231 23%%%~~~ \327\231\327\225\327\241\327\231\327\240", QChar::DirR },
    { "data24", "\327\240\327\231\327\241\327\225\327\231 abc ~~~23%%% \327\231\327\227\327\231\327\223 abc", "abc \327\223\327\231\327\227\327\231 abc ~~~23%%% \327\231\327\225\327\241\327\231\327\240", QChar::DirR },
    { "data25", "\327\240\327\231\327\241\327\225\327\231 abc@23@cde \327\231\327\227\327\231\327\223", "\327\223\327\231\327\227\327\231 abc@23@cde \327\231\327\225\327\241\327\231\327\240", QChar::DirR },
    { "data26", "\327\240\327\231\327\241\327\225\327\231 abc 23 cde \327\231\327\227\327\231\327\223", "\327\223\327\231\327\227\327\231 abc 23 cde \327\231\327\225\327\241\327\231\327\240", QChar::DirR },
    { "data27", "\327\240\327\231\327\241\327\225\327\231 abc 23 \327\231\327\227\327\231\327\223 cde", "cde \327\223\327\231\327\227\327\231 abc 23 \327\231\327\225\327\241\327\231\327\240", QChar::DirR },
    { "data28", "\327\222a 2 \327\251", "\327\251 a 2\327\222", QChar::DirR },
    { "data29", "\327\244\327\252\327\225\327\250 1*5 1-5 1/5 1+5", "1+5 1/5 1-5 5*1 \327\250\327\225\327\252\327\244", QChar::DirR },
    { "data30", "\330\272 1*5 1-5 1/5 1+5", "5+1 1/5 5-1 5*1 \330\272", QChar::DirR },
    { "data31", "\330\250 \333\261\333\262.\333\263", "\333\261\333\262.\333\263 \330\250", QChar::DirR },
    { "data32", "\330\250 12.3", "12.3 \330\250", QChar::DirR },
    { "data33", "\330\250 1.23", "1.23 \330\250", QChar::DirR },
    { "data34", "\331\276 \333\261.\333\262\333\263", "\333\261.\333\262\333\263 \331\276", QChar::DirR },
    { "data35", "\331\276\333\261.\333\262\333\263", "\333\261.\333\262\333\263\331\276", QChar::DirR },
    { "data36", "1) \327\251", "\327\251 (1", QChar::DirR },
    { "data37", "1) \327\251", "1) \327\251", QChar::DirL },
    { "data38", "\327\224-w3c", "w3c-\327\224", QChar::DirR },
    { "data39", "\327\224-w3c", "\327\224-w3c", QChar::DirL },
    { "data40", "17:25, foo", "17:25, foo", QChar::DirL },
    { "data41", "5, foo", "foo ,5", QChar::DirR },
    { "data42", "foo\nfoo", "foo\nfoo", QChar::DirL },
    { "data43", "\327\251\327\234\327\225\327\235\n\327\251\327\234\327\225\327\235", "\327\235\327\225\327\234\327\251\n\327\235\327\225\327\234\327\251", QChar::DirR },
    { "data44", "foo\n\327\251\327\234\327\225\327\235", "foo\n\327\235\327\225\327\234\327\251", QChar::DirL },
    { "data45", "\327\251\327\234\327\225\327\235\nfoo", "\327\235\327\225\327\234\327\251\nfoo", QChar::DirR },
    { "data46", "\330\250 1.23 \330\250", "\330\250 1.23 \330\250", QChar::DirR },
    { "data47", "\331\204\330\250 1.23 \331\202\330\250", "\330\250\331\202 1.23 \330\250\331\204", QChar::DirR },
    { "data48", "\330\250 1.2 \330\250", "\330\250 1.2 \330\250", QChar::DirR },
    { "data49", "\331\204\330\250 1.2 \331\202\330\250", "\330\250\331\202 1.2 \330\250\331\204", QChar::DirR },
    { "data50", "a\331\204\330\250 1.2 \331\202\330\250", "a\330\250\331\202 1.2 \330\250\331\204", QChar::DirL },

    { "data51", "ab(\327\240\327\231)cd", "ab(\327\231\327\240)cd", QChar::DirL },
    { "data52", "ab(\327\240\327\231)cd", "cd(\327\231\327\240)ab", QChar::DirR },
    { "data53", "a(\327\231)c", "a(\327\231)c", QChar::DirL },
    { "data54", "a(\327\231)c", "c(\327\231)a", QChar::DirR },
    { "data55", "\"[\327\220]\"", "\"[\327\220]\"", QChar::DirR },
    { "data56", "\"[\327\220]\"", "\"[\327\220]\"", QChar::DirL },
    { "data57", "\331\204\330\250 \331\202\330\250", "\330\250\331\202 \330\250\331\204", QChar::DirR },
    { "data58", "\331\204\330\250 \331\202\330\250", "\330\250\331\202 \330\250\331\204", QChar::DirL },
    { "data59", "3layout", "3layout", QChar::DirL },
    { "data60", "3layout", "3layout", QChar::DirR },
    { "data61", "3l", "3l", QChar::DirR },
    { "data62", "3la", "3la", QChar::DirR },
    { "data63", "3lay", "3lay", QChar::DirR },

// explicit levels
// LRE: \342\200\252
// RLE: \342\200\253
// PDF: \342\200\254
// LRO: \342\200\255
// RLO: \342\200\256

    { "override1", "\342\200\256hello\342\200\254", "\342\200\254olleh\342\200\256", QChar::DirL },
    { "override2", "\342\200\255hello\342\200\254", "\342\200\255hello\342\200\254", QChar::DirL },
    { "override3", "\342\200\255\327\251\327\234\327\225\327\235\342\200\254", "\342\200\255\327\251\327\234\327\225\327\235\342\200\254", QChar::DirL },
    { "override4", "\342\200\256\327\251\327\234\327\225\327\235\342\200\254", "\342\200\254\327\235\327\225\327\234\327\251\342\200\256", QChar::DirL },
    { "override5", "\342\200\256hello\342\200\254", "\342\200\254olleh\342\200\256", QChar::DirR },
    { "override6", "\342\200\255hello\342\200\254", "\342\200\255hello\342\200\254", QChar::DirR },
    { "override7", "\342\200\255\327\251\327\234\327\225\327\235\342\200\254", "\342\200\255\327\251\327\234\327\225\327\235\342\200\254", QChar::DirR },
    { "override8", "\342\200\256\327\251\327\234\327\225\327\235\342\200\254", "\342\200\254\327\235\327\225\327\234\327\251\342\200\256", QChar::DirR },

    { "override9", "\327\224\342\200\255\327\251\327\234\342\200\256hello\342\200\254\327\225\327\235\342\200\254", "\342\200\255\327\251\327\234\342\200\254olleh\342\200\256\327\225\327\235\342\200\254\327\224", QChar::DirL },
    { "override10", "\327\224\342\200\255\327\251\327\234\342\200\256hello\342\200\254\327\225\327\235\342\200\254", "\342\200\255\327\251\327\234\342\200\254olleh\342\200\256\327\225\327\235\342\200\254\327\224", QChar::DirR },


    { "embed1", "\342\200\252hello\342\200\254", "\342\200\252hello\342\200\254", QChar::DirL },
    { "embed2", "\342\200\253hello\342\200\254", "\342\200\254hello\342\200\253", QChar::DirL },
    { "embed3", "\342\200\252hello\342\200\254", "\342\200\252hello\342\200\254", QChar::DirR },
    { "embed4", "\342\200\253hello\342\200\254", "\342\200\254hello\342\200\253", QChar::DirR },
    { "embed5", "\342\200\252\327\251\327\234\327\225\327\235\342\200\254", "\342\200\252\327\235\327\225\327\234\327\251\342\200\254", QChar::DirL },
    { "embed6", "\342\200\253\327\251\327\234\327\225\327\235\342\200\254", "\342\200\254\327\235\327\225\327\234\327\251\342\200\253", QChar::DirL },
    { "embed7", "\342\200\252\327\251\327\234\327\225\327\235\342\200\254", "\342\200\252\327\235\327\225\327\234\327\251\342\200\254", QChar::DirR },
    { "embed8", "\342\200\253\327\251\327\234\327\225\327\235\342\200\254", "\342\200\254\327\235\327\225\327\234\327\251\342\200\253", QChar::DirR },

    { "embed9", "\342\200\252x \327\251\327\234\327\225\327\235 y\342\200\254", "\342\200\252x \327\235\327\225\327\234\327\251 y\342\200\254", QChar::DirL },
    { "embed10", "\342\200\253x \327\251\327\234\327\225\327\235 y\342\200\254", "\342\200\254y \327\235\327\225\327\234\327\251 x\342\200\253", QChar::DirL },
    { "embed11", "\342\200\252x \327\251\327\234\327\225\327\235 y\342\200\254", "\342\200\252x \327\235\327\225\327\234\327\251 y\342\200\254", QChar::DirR },
    { "embed12", "\342\200\253x \327\251\327\234\327\225\327\235 y\342\200\254", "\342\200\254y \327\235\327\225\327\234\327\251 x\342\200\253", QChar::DirR },
    { "zwsp", "+0\342\200\213f-1", "+0\342\200\213f-1", QChar::DirL },

    { 0, 0, 0, QChar::DirON }
};
