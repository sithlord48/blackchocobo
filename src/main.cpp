// SPDX-FileCopyrightText: 2010 - 20202 Chris Rizzitello <sithlord48@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include <QApplication>
#include <QLocale>
#include <QStyle>
#include <QStyleFactory>
#include <QTranslator>
#include <QTime>
#include <QRandomGenerator>

#include "bcsettings.h"
#include "blackchocobo.h"

int main(int argc, char *argv[])
{
    if(argc >1) {
        if(QString(argv[1]) == "--help" || QString(argv[1]) =="-h") {
            printf("Usage: blackchocobo [<filename>]\nUsage: blackchocobo --version :Print Version Info\n");
            return 0;
        }

        if(QString(argv[1]) == "--version") {
            printf("Black Chocobo Version:%s \n", BC_VERSION);
            return 0;
        }
    }
    Q_INIT_RESOURCE(icons);

    QApplication a(argc, argv);
    if (BCSettings::value(SETTINGS::APPSTYLE).isNull())
        BCSettings::setValue(SETTINGS::APPSTYLE, QStringLiteral("Fusion"));

#if defined(Q_OS_WIN)
    if (BCSettings::value(SETTINGS::COLORSCHEME).isNull()) {
        QSettings settings(QStringLiteral("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize"), QSettings::NativeFormat);
        int theme = settings.value(QStringLiteral("AppsUseLightTheme"), 0).toInt() + 1;
        BCSettings::setValue(SETTINGS::COLORSCHEME, theme);
    }
#endif
    a.setStyle(QStyleFactory::create(BCSettings::value(SETTINGS::APPSTYLE, a.style()->name()).toString()));
    a.setPalette(BCSettings::paletteForSetting());
    a.setAttribute(Qt::AA_DontUseNativeDialogs, !BCSettings::value(SETTINGS::USENATIVEDIALOGS).toBool());
    a.setApplicationName("Black Chocobo");
    a.setApplicationVersion(BC_VERSION);

    QRandomGenerator(quint32(QTime::currentTime().msec()));
    BlackChocobo w;
    if(argc == 2)
        w.loadFileFull(QString(argv[1]), 0);
    w.show();
    return a.exec();
}
