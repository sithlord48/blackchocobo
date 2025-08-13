// SPDX-FileCopyrightText: 2010 -2024 Chris Rizzitello <sithlord48@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

/*~~~~~~~~~~~Includes~~~~~~~~*/
#include <QAction>
#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMessageBox>
#include <QScrollBar>
#include <QScreen>
#include <QSpinBox>
#include <QString>
#include <QToolBox>
#include <QTabWidget>
#include <QWidget>

//Project Includes
#include <about.h>
#include <bcdialog.h>
#include <errbox.h>
#include <options.h>
#include <qhexedit.h>
#include "bcsettings.h"
#include "blackchocobo.h"
#include "ui_blackchocobo.h"

//ff7tk includes
#include <ff7tkInfo>
#include <FF7Char>
#include <FF7Item>
#include <FF7ItemModel>
#include <FF7Location>
#include <FF7Save>
#include <FF7Materia>
#include <SaveIcon>
#include <OptionsWidget>
#include <MateriaEditor>
#include <SlotSelect>
#include <ChocoboEditor>
#include <CharEditor>
#include <ItemListView>
#include <MetadataCreator>
#include <PhsListWidget>
#include <MenuListWidget>
#include <ChocoboManager>
#include <LocationViewer>

#include "widgets/partytab.h"
#include "widgets/itemtab.h"

/*~~~~~~~~GUI Set Up~~~~~~~*/
BlackChocobo::BlackChocobo(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BlackChocobo)
    , hexCursorPos(0)
    , _init(true)
    , load(true)
    , ff7(new FF7Save)
    , saveIcon(new SaveIcon)
    , s(0)
    , curchar(0)
    , mslotsel(-1)
    , phsList(new PhsListWidget)
    , menuList(new MenuListWidget)
    , optionsWidget(new OptionsWidget)
    , materia_editor(new MateriaEditor(this))
    , partyTab(new PartyTab)
    , itemTab(new ItemTab)
    , hexEditor(new QHexEdit)
    , chocoboManager(new ChocoboManager)
    , ff7ItemModel(new FF7ItemModel(this))
{
//Initilze Remaining Data
    QIcon::setFallbackSearchPaths(QIcon::fallbackSearchPaths() << ":/icons/common");
    QIcon::setFallbackSearchPaths(QIcon::fallbackSearchPaths() << QStringLiteral(":/icons/%1").arg(checkIconTheme()));
    if (!QIcon::hasThemeIcon(QStringLiteral("games-highscores"))) {
        QIcon::setThemeName(QStringLiteral("bc-%1").arg(checkIconTheme()));
    } else{
        QIcon::setFallbackThemeName(QStringLiteral("bc-%1").arg(checkIconTheme()));
    }
    setWindowIcon(QIcon(":/icons/common/blackchocobo"));
    QApplication::setDesktopFileName(QStringLiteral("io.github.sithlord48.blackchocobo"));
    buffer_materia = FF7Materia::encodeMateria(FF7Materia::EmptyId, FF7Materia::MaxMateriaAp);
    setAcceptDrops(true);
    ui->setupUi(this);
    loadBasicSettings();
    detectTranslations();
    initDisplay();
    setItemSizes();
    populateCombos();
    init_style();
    loadChildWidgetSettings();
    init_connections();
    actionNewGame_triggered();
    partyTab->pressCharacterButton(FF7Char::Cloud);
    ff7->setFormat(FF7SaveInfo::FORMAT::UNKNOWN);
    ff7->setFileModified(false, 0);
}

QString BlackChocobo::checkIconTheme()
{
    return palette().text().color().value() >= QColor(Qt::lightGray).value() ? QStringLiteral("dark") : QStringLiteral("light");
}

void BlackChocobo::detectTranslations()
{
    m_translations.clear();

    QMap<QString, QTranslator *> ff7tk_translations = ff7tkInfo::translations();
    QStringList nameFilter ={QStringLiteral("blackchocobo_*.qm")};
    QMap<QString, QTranslator *> app_translations;
    QDir dir (QStringLiteral("%1").arg(BCSettings::value(SETTINGS::LANGPATH).toString()));
    QStringList langList = dir.entryList(nameFilter,QDir::Files, QDir::Name);
    for (const QString &translation : std::as_const(langList)) {
        QTranslator *translator = new QTranslator;
        std::ignore = translator->load(translation, dir.absolutePath());
        QString lang = translation.mid(13, translation.lastIndexOf('.') - 13);
        app_translations.insert(lang, translator);
        bool currentLang = (BCSettings::value(SETTINGS::LANG, QStringLiteral("en")).toString() == lang);
        if (currentLang) {
            BCSettings::setValue(SETTINGS::LANG, lang);
            QApplication::installTranslator(translator);
            QApplication::installTranslator(ff7tk_translations.value(lang));
        }
    }

    QMap<QString, QTranslator *> qt_translations;
    nameFilter = QStringList{QStringLiteral("qt_*.qm")};
    dir.setPath(QStringLiteral("%1/%2").arg(QCoreApplication::applicationDirPath(), QStringLiteral("translations")));
    langList = dir.entryList(nameFilter, QDir::Files, QDir::Name);
    if (langList.isEmpty()) {
        dir.setPath(QStringLiteral("%1/%2").arg(QCoreApplication::applicationDirPath(), QStringLiteral("translations")));
        langList = dir.entryList(nameFilter, QDir::Files, QDir::Name);
        if (langList.isEmpty()) {
            dir.setPath(QStringLiteral("%1/../share/qt/translations").arg(QCoreApplication::applicationDirPath()));
            langList = dir.entryList(nameFilter, QDir::Files, QDir::Name);
            if(langList.isEmpty()) {
                dir.setPath(QStringLiteral("%1/%2").arg(QDir::homePath(), QStringLiteral(".local/share/qt/translations")));
                langList = dir.entryList(nameFilter, QDir::Files, QDir::Name);
                if(langList.isEmpty()) {
                    dir.setPath(QStringLiteral("/usr/local/share/qt/translations"));
                    langList = dir.entryList(nameFilter, QDir::Files, QDir::Name);
                    if(langList.isEmpty()) {
                        dir.setPath(QStringLiteral("/usr/share/qt/translations"));
                        langList = dir.entryList(nameFilter, QDir::Files, QDir::Name);
                    }
                }
            }
        }
    }
    for (const QString &translation : std::as_const(langList)) {
        QTranslator *translator = new QTranslator;
        std::ignore = translator->load(translation, dir.absolutePath());
        QString lang = translation.mid(3, translation.lastIndexOf('.') - 3);
        qt_translations.insert(lang, translator);
        bool currentLang = (BCSettings::value(SETTINGS::LANG, QStringLiteral("en")).toString() == lang);
        if (currentLang)
            QApplication::installTranslator(translator);
    }
    const QStringList keys = app_translations.keys();
    QList<QTranslator *> tempList;
    for (const QString &lang : keys) {
        tempList.clear();
        tempList.append(app_translations.value(lang));
        tempList.append(ff7tk_translations.value(lang));
        if(lang != QStringLiteral("re"))
            tempList.append(qt_translations.value(lang));
        else
            tempList.append(qt_translations.value(QStringLiteral("en")));
        m_translations.insert(lang, tempList);
    }
}

void BlackChocobo::initDisplay()
{
    QHBoxLayout *phsLayout = new QHBoxLayout;
    phsLayout->addWidget(phsList);
    ui->Phs_Box->setLayout(phsLayout);

    QHBoxLayout *menuLayout = new QHBoxLayout;
    menuLayout->addWidget(menuList);
    ui->Menu_Box->setLayout(menuLayout);

    chocoboManager->setContentsMargins(0, 20, 0, 0);
    ui->tabWidget->insertTab(0, partyTab, tr("Party"));
    ui->tabWidget->insertTab(1, itemTab, tr("Items"));
    ui->tabWidget->insertTab(3, chocoboManager, tr("Chocobo"));
    ui->tabWidget->insertTab(7, optionsWidget, tr("Game Options"));
    ui->tabWidget->setCurrentIndex(0);

    optionsWidget->setControllerMappingVisible(false);
    QVBoxLayout *materia_editor_layout = new QVBoxLayout();
    mat_spacer = new QSpacerItem(0, 0, QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
    materia_editor_layout->addWidget(materia_editor);
    materia_editor_layout->addSpacerItem(mat_spacer);
    ui->group_materia->setLayout(materia_editor_layout);

#ifdef Q_OS_MAC
    hexEditor->setFont(this->font());
#endif
    hexEditor->setAddressAreaColor(palette().alternateBase().color());
    hexEditor->setHighlightingColor(palette().linkVisited().color());
    hexEditor->setSelectionColor(palette().highlight().color());
    hexEditor->setHexCaps(true);
    QVBoxLayout *hexLayout = new QVBoxLayout;
    hexLayout->setContentsMargins(0, 0, 0, 0);
    hexLayout->addWidget(hexEditor);
    ui->group_hexedit->setLayout(hexLayout);


    itemTab->itemList()->setModel(ff7ItemModel);

    locationViewer = new LocationViewer(this);
    locationViewer->setRegion(QStringLiteral("BASCUS-94163FF7-S00"));

    QVBoxLayout *locLayout = new QVBoxLayout;
    locLayout->setContentsMargins(0, 0, 0, 0);
    locLayout->addWidget(locationViewer);
    ui->fieldFrame->setLayout(locLayout);

    ui->statusBar->addWidget(ui->frame_status, 1);
    ui->frame_status->setFixedHeight(fontMetrics().height() + 2);
    ui->tblMateria->setIconSize(QSize(fontMetrics().height(), fontMetrics().height()));
    ui->tblUnknown->setColumnWidth(0, fontMetrics().horizontalAdvance(QStringLiteral("WW")));
    ui->tblUnknown->setColumnWidth(1, fontMetrics().horizontalAdvance(QStringLiteral("W")));
    ui->tblUnknown->setColumnWidth(2, fontMetrics().horizontalAdvance(QStringLiteral("W")));
    ui->tblUnknown->setColumnWidth(3, fontMetrics().horizontalAdvance(QStringLiteral("WWWWWW")));
    ui->tblUnknown->setColumnWidth(4, fontMetrics().horizontalAdvance(QStringLiteral("W")));

    ui->tblCompareUnknown->setColumnWidth(0, fontMetrics().horizontalAdvance(QStringLiteral("WW")));
    ui->tblCompareUnknown->setColumnWidth(1, fontMetrics().horizontalAdvance(QStringLiteral("W")));
    ui->tblCompareUnknown->setColumnWidth(2, fontMetrics().horizontalAdvance(QStringLiteral("W")));
    ui->tblCompareUnknown->setColumnWidth(3, fontMetrics().horizontalAdvance(QStringLiteral("WWWWWW")));
    ui->tblCompareUnknown->setColumnWidth(4, fontMetrics().horizontalAdvance(QStringLiteral("W")));

    int width = 0;
    for(int i = 0; i < 5; i++)
        width += ui->tblUnknown->columnWidth(i);

    width +=ui->tblUnknown->verticalScrollBar()->width();
    ui->table_unknown->setFixedWidth(width);
    ui->tblUnknown->setFixedWidth(width);

    width -=ui->tblUnknown->verticalScrollBar()->width();
    ui->compare_table->setFixedWidth(width);
    ui->tblCompareUnknown->setFixedWidth(width);

    QStringList _zvars {tr("-None-")};
    for (int i=1; i<= ff7->unknown_zmax(); i++ )
        _zvars.append(QStringLiteral("z_%1").arg(i));
    _zvars.append(tr("Slot"));
    ui->comboZVar->addItems(_zvars);

    ui->worldMapView->setScaledContents(true);
    ui->worldMapView->setPixmap(QPixmap(":/icons/common/world_map").scaled(ui->world_map_frame->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    ui->lbl_love_aeris->setScaledContents(true);
    ui->lbl_love_barret->setScaledContents(true);
    ui->lbl_love_tifa->setScaledContents(true);
    ui->lbl_love_yuffie->setScaledContents(true);
    ui->lbl_battle_love_aeris->setScaledContents(true);
    ui->lbl_battle_love_barret->setScaledContents(true);
    ui->lbl_battle_love_tifa->setScaledContents(true);
    ui->lbl_battle_love_yuffie->setScaledContents(true);
    ui->lbl_love_aeris->setPixmap(FF7Char::pixmap(FF7Char::Aerith));
    ui->lbl_love_barret->setPixmap(FF7Char::pixmap(FF7Char::Barret));
    ui->lbl_love_tifa->setPixmap(FF7Char::pixmap(FF7Char::Tifa));
    ui->lbl_love_yuffie->setPixmap(FF7Char::pixmap(FF7Char::Yuffie));
    ui->lbl_battle_love_aeris->setPixmap(FF7Char::pixmap(FF7Char::Aerith));
    ui->lbl_battle_love_barret->setPixmap(FF7Char::pixmap(FF7Char::Barret));
    ui->lbl_battle_love_tifa->setPixmap(FF7Char::pixmap(FF7Char::Tifa));
    ui->lbl_battle_love_yuffie->setPixmap(FF7Char::pixmap(FF7Char::Yuffie));
}

void BlackChocobo::setItemSizes()
{
    ui->progress_frame_left->setFixedWidth(415);
    ui->groupBox_18->setFixedWidth(273); //materia table group.
    ui->scrollArea->setFixedWidth(310);
    ui->scrollAreaWidgetContents->adjustSize();
    ui->world_map_frame->setFixedSize(446, 381);

    ui->worldMapView->setGeometry(5 , 32, 432, 336);

    ui->comboMapControls->setFixedHeight(32);

    ui->slideWorldX->setGeometry(-1, 369, 443, 10);
    ui->slideWorldY->setGeometry(437, 26, 10, 347);

    const QSize lovePointSize(50, 68);
    ui->lbl_love_aeris->setFixedSize(lovePointSize);
    ui->lbl_love_barret->setFixedSize(lovePointSize);
    ui->lbl_love_tifa->setFixedSize(lovePointSize);
    ui->lbl_love_yuffie->setFixedSize(lovePointSize);
    ui->lbl_battle_love_aeris->setFixedSize(lovePointSize);
    ui->lbl_battle_love_barret->setFixedSize(lovePointSize);
    ui->lbl_battle_love_tifa->setFixedSize(lovePointSize);
    ui->lbl_battle_love_yuffie->setFixedSize(lovePointSize);

    materia_editor->setStarsSize(48);
    guirefresh();
}

void BlackChocobo::populateCombos()
{
//World party leader Combo.
    if (ui->comboWorldPartyLeader->count() != 0) {
        ui->comboWorldPartyLeader->setItemText(0, FF7Char::defaultName(FF7Char::Cloud));
        ui->comboWorldPartyLeader->setItemText(1, FF7Char::defaultName(FF7Char::Tifa));
        ui->comboWorldPartyLeader->setItemText(2, FF7Char::defaultName(FF7Char::Cid));
    } else {
        ui->comboWorldPartyLeader->addItem(FF7Char::icon(FF7Char::Cloud), FF7Char::defaultName(FF7Char::Cloud));
        ui->comboWorldPartyLeader->addItem(FF7Char::icon(FF7Char::Tifa), FF7Char::defaultName(FF7Char::Tifa));
        ui->comboWorldPartyLeader->addItem(FF7Char::icon(FF7Char::Cid), FF7Char::defaultName(FF7Char::Cid));
    }
}

void BlackChocobo::init_style()
{
    QString sliderStyleSheet(QStringLiteral("QSlider:sub-page{background-color: qlineargradient(spread:pad, x1:0.472, y1:0.011, x2:0.483, y2:1, stop:0 rgba(186, 1, 87,192), stop:0.505682 rgba(209, 128, 173,192), stop:0.931818 rgba(209, 44, 136, 192));}"));
    sliderStyleSheet.append(QStringLiteral("QSlider::add-page{background: qlineargradient(spread:pad, x1:0.5, y1:0.00568182, x2:0.497, y2:1, stop:0 rgba(91, 91, 91, 255), stop:0.494318 rgba(122, 122, 122, 255), stop:1 rgba(106, 106, 106, 255));}"));
    sliderStyleSheet.append(QStringLiteral("QSlider{border:3px solid;border-left-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(123, 123, 123, 255), stop:1 rgba(172, 172, 172, 255));border-right-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(123, 123, 123, 255), stop:1 rgba(172, 172, 172, 255));border-bottom-color: rgb(172, 172, 172);border-top-color: rgb(172, 172, 172);border-radius: 5px;}"));
    sliderStyleSheet.append(QStringLiteral("QSlider::groove{height: 12px;background: qlineargradient(spread:pad, x1:0.5, y1:0.00568182, x2:0.497, y2:1, stop:0 rgba(91, 91, 91, 255), stop:0.494318 rgba(122, 122, 122, 255), stop:1 rgba(106, 106, 106, 255));}"));
    sliderStyleSheet.append(QStringLiteral("QSlider::handle{background: rgba(172, 172, 172,255);border: 1px solid #5c5c5c;width: 3px;border-radius: 2px;}"));
    partyTab->characterEditor()->setSliderStyle(sliderStyleSheet);

    QString tabStyle = QStringLiteral("::tab:hover{background-color:rgba(%1, %2, %3, 128);}").arg(QString::number(this->palette().highlight().color().red()), QString::number(this->palette().highlight().color().green()), QString::number(this->palette().highlight().color().blue()));
    partyTab->characterEditor()->setToolBoxStyle(tabStyle);
    ui->locationToolBox->setStyleSheet(tabStyle);

    ui->slideWorldY->setStyleSheet(QStringLiteral("::handle{image: url(:/icons/common/map-slide-left);}"));
    ui->slideWorldX->setStyleSheet(QStringLiteral("::handle{image: url(:/icons/common/map-slide-up);}"));
    if (style()->name() == "fusion") {
        auto cboxes = findChildren<QComboBox*>(QString(), Qt::FindChildrenRecursively);
        for (auto box : std::as_const(cboxes)) {
            box->view()->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
            box->setStyleSheet(QStringLiteral("QComboBox { combobox-popup: 0;}"));
        }
    }
}

void BlackChocobo::init_connections()
{
    //Actions
    connect(ui->actionQuit, &QAction::triggered, this, &BlackChocobo::close);
    connect(ui->actionOpenSaveFile, &QAction::triggered, this, &BlackChocobo::actionOpenSaveFile_triggered);
    connect(ui->actionReload, &QAction::triggered, this, &BlackChocobo::actionReload_triggered);
    connect(ui->actionImportChar, &QAction::triggered, this , &BlackChocobo::actionImportChar_triggered);
    connect(ui->actionExportChar, &QAction::triggered, this , &BlackChocobo::actionExportChar_triggered);
    connect(ui->actionSave, &QAction::triggered, this , &BlackChocobo::actionSave_triggered);
    connect(ui->actionSaveFileAs, &QAction::triggered, this , &BlackChocobo::actionSaveFileAs_triggered);
    connect(ui->actionNewGame, &QAction::triggered, this, &BlackChocobo::actionNewGame_triggered);
    connect(ui->actionNewGamePlus, &QAction::triggered, this, &BlackChocobo::actionNewGamePlus_triggered);
    connect(ui->actionShowSelectionDialog, &QAction::triggered, this, &BlackChocobo::actionShowSelectionDialog_triggered);
    connect(ui->actionClearSlot, &QAction::triggered, this, &BlackChocobo::actionClearSlot_triggered);
    connect(ui->actionPreviousSlot, &QAction::triggered, this, &BlackChocobo::actionPreviousSlot_triggered);
    connect(ui->actionNextSlot, &QAction::triggered, this, &BlackChocobo::actionNextSlot_triggered);
    connect(ui->actionAbout, &QAction::triggered, this, &BlackChocobo::actionAbout_triggered);
    connect(ui->actionCopySlot, &QAction::triggered, this, &BlackChocobo::actionCopySlot_triggered);
    connect(ui->actionPasteSlot, &QAction::triggered, this, &BlackChocobo::actionPasteSlot_triggered);
    connect(ui->actionShowOptions, &QAction::triggered, this, &BlackChocobo::actionShowOptions_triggered);
    connect(ui->actionOpenAchievementFile, &QAction::triggered, this, &BlackChocobo::actionOpenAchievementFile_triggered);
    connect(ui->actionCreateNewMetadata, &QAction::triggered, this, &BlackChocobo::actionCreateNewMetadata_triggered);
    connect(ui->actionImportSlotFromFile, &QAction::triggered, this, &BlackChocobo::actionImportSlotFromFile_triggered);
    connect(ui->actionRegionUSA, &QAction::triggered, this, &BlackChocobo::actionRegionUSA_triggered);
    connect(ui->actionRegionPALGeneric, &QAction::triggered, this, &BlackChocobo::actionRegionPALGeneric_triggered);
    connect(ui->actionRegionPALFrench, &QAction::triggered, this, &BlackChocobo::actionRegionPALFrench_triggered);
    connect(ui->actionRegionPALGerman, &QAction::triggered, this, &BlackChocobo::actionRegionPALGerman_triggered);
    connect(ui->actionRegionPALSpanish, &QAction::triggered, this, &BlackChocobo::actionRegionPALSpanish_triggered);
    connect(ui->actionRegionJPN, &QAction::triggered, this, &BlackChocobo::actionRegionJPN_triggered);
    connect(ui->actionRegionJPNInternational, &QAction::triggered, this, &BlackChocobo::actionRegionJPNInternational_triggered);
    //Buttons

    connect(ui->btnReplay, &QPushButton::clicked, this, &BlackChocobo::btnReplay_clicked);
    connect(ui->btnRemoveAllMateria, &QPushButton::clicked, this, &BlackChocobo::btnRemoveAllMateria_clicked);
    connect(ui->btnRemoveAllStolen, &QPushButton::clicked, this, &BlackChocobo::btnRemoveAllStolen_clicked);
    connect(ui->btnAddAllMateria, &QPushButton::clicked, this, &BlackChocobo::btnAddAllMateria_clicked);
    //SpinBoxes
    connect(ui->sbCurdisc, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbCurdisc_valueChanged);
    connect(ui->sbLoveYuffie, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbLoveYuffie_valueChanged);
    connect(ui->sbLoveTifa, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbLoveTifa_valueChanged);
    connect(ui->sbLoveAeris, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbLoveAeris_valueChanged);
    connect(ui->sbLoveBarret, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbLoveBarret_valueChanged);
    connect(ui->sbTimeSec, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbTimeSec_valueChanged);
    connect(ui->sbTimeMin, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbTimeMin_valueChanged);
    connect(ui->sbTimeHour, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbTimeHour_valueChanged);
    connect(ui->sbTimerTimeSec, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbTimerTimeSec_valueChanged);
    connect(ui->sbTimerTimeMin, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbTimerTimeMin_valueChanged);
    connect(ui->sbTimerTimeHour, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbTimerTimeHour_valueChanged);
    connect(ui->sbBloveYuffie, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbBloveYuffie_valueChanged);
    connect(ui->sbBloveTifa, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbBloveTifa_valueChanged);
    connect(ui->sbBloveAeris, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbBloveAeris_valueChanged);
    connect(ui->sbBloveBarret, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbBloveBarret_valueChanged);
    connect(ui->sbUweaponHp, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbUweaponHp_valueChanged);
    connect(ui->sbCoster1, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbCoster1_valueChanged);
    connect(ui->sbCoster2, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbCoster2_valueChanged);
    connect(ui->sbCoster3, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbCoster3_valueChanged);
    connect(ui->sbTurkschurch, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbTurkschurch_valueChanged);
    connect(ui->sbMprogress, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbMprogress_valueChanged);
    connect(ui->sbDonprog, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbDonprog_valueChanged);
    connect(ui->sbSteps, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbSteps_valueChanged);
    connect(ui->sbSnowBegScore, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbSnowBegScore_valueChanged);
    connect(ui->sbSnowExpScore, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbSnowExpScore_valueChanged);
    connect(ui->sbSnowCrazyScore, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbSnowCrazyScore_valueChanged);
    connect(ui->sbSnowBegMin, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbSnowBegMin_valueChanged);
    connect(ui->sbSnowBegSec, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbSnowBegSec_valueChanged);
    connect(ui->sbSnowBegMsec, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbSnowBegMsec_valueChanged);
    connect(ui->sbSnowExpMin, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbSnowExpMin_valueChanged);
    connect(ui->sbSnowExpSec, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbSnowExpSec_valueChanged);
    connect(ui->sbSnowExpMsec, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbSnowExpMsec_valueChanged);
    connect(ui->sbSnowCrazyMin, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbSnowCrazyMin_valueChanged);
    connect(ui->sbSnowCrazySec, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbSnowCrazySec_valueChanged);
    connect(ui->sbSnowCrazyMsec, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbSnowCrazyMsec_valueChanged);
    connect(ui->sbBikeHighScore, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbBikeHighScore_valueChanged);
    connect(ui->sbBattlePoints, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbBattlePoints_valueChanged);
    connect(ui->sbBattleSWins, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbBattleSWins_valueChanged);
    connect(ui->sbCondorFunds, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbCondorFunds_valueChanged);
    connect(ui->sbCondorWins, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbCondorWins_valueChanged);
    connect(ui->sbCondorLosses, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbCondorLosses_valueChanged);
    connect(ui->sbSaveMapId, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbSaveMapId_valueChanged);
    connect(ui->sbSaveX, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbSaveX_valueChanged);
    connect(ui->sbSaveY, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbSaveY_valueChanged);
    connect(ui->sbSaveZ, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbSaveZ_valueChanged);
    connect(ui->sbLeaderX, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbLeaderX_valueChanged);
    connect(ui->sbLeaderY, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbLeaderY_valueChanged);
    connect(ui->sbLeaderZ, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbLeaderZ_valueChanged);
    connect(ui->sbLeaderId, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbLeaderId_valueChanged);
    connect(ui->sbLeaderAngle, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbLeaderAngle_valueChanged);
    connect(ui->sbTcX, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbTcX_valueChanged);
    connect(ui->sbTcY, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbTcY_valueChanged);
    connect(ui->sbTcZ, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbTcZ_valueChanged);
    connect(ui->sbTcId, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbTcId_valueChanged);
    connect(ui->sbTcAngle, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbTcAngle_valueChanged);
    connect(ui->sbBhX, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbBhX_valueChanged);
    connect(ui->sbBhY, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbBhY_valueChanged);
    connect(ui->sbBhZ, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbBhZ_valueChanged);
    connect(ui->sbBhId, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbBhId_valueChanged);
    connect(ui->sbBhAngle, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbBhAngle_valueChanged);
    connect(ui->sbSubX, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbSubX_valueChanged);
    connect(ui->sbSubY, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbSubY_valueChanged);
    connect(ui->sbSubZ, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbSubZ_valueChanged);
    connect(ui->sbSubId, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbSubId_valueChanged);
    connect(ui->sbSubAngle, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbSubAngle_valueChanged);
    connect(ui->sbWcX, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbWcX_valueChanged);
    connect(ui->sbWcY, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbWcY_valueChanged);
    connect(ui->sbWcZ, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbWcZ_valueChanged);
    connect(ui->sbWcId, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbWcId_valueChanged);
    connect(ui->sbWcAngle, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbWcAngle_valueChanged);
    connect(ui->sbDurwX, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbDurwX_valueChanged);
    connect(ui->sbDurwY, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbDurwY_valueChanged);
    connect(ui->sbDurwZ, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbDurwZ_valueChanged);
    connect(ui->sbDurwId, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbDurwId_valueChanged);
    connect(ui->sbDurwAngle, qOverload<int>(&QSpinBox::valueChanged), this, &BlackChocobo::sbDurwAngle_valueChanged);
    //CheckBoxes
    connect(ui->cbTutWorldSave, &QCheckBox::stateChanged, this, &BlackChocobo::cbTutWorldSave_stateChanged);
    connect(ui->cbBombingInt, &QCheckBox::stateChanged, this, &BlackChocobo::cbBombingInt_stateChanged);
    connect(ui->cbFlashbackPiano, &QCheckBox::toggled, this, &BlackChocobo::cbFlashbackPiano_toggled);
    connect(ui->cbSubGameWon, &QCheckBox::toggled, this, &BlackChocobo::cbSubGameWon_toggled);
    connect(ui->cbPandorasBox, &QCheckBox::toggled, this, &BlackChocobo::cbPandorasBox_toggled);
    connect(ui->cbVisibleBuggy, &QCheckBox::toggled, this, &BlackChocobo::cbVisibleBuggy_toggled);
    connect(ui->cbVisibleBronco, &QCheckBox::toggled, this, &BlackChocobo::cbVisibleBronco_toggled);
    connect(ui->cbVisibleHighwind, &QCheckBox::toggled, this, &BlackChocobo::cbVisibleHighwind_toggled);
    connect(ui->cbVisibleWildChocobo, &QCheckBox::toggled, this, &BlackChocobo::cbVisibleWildChocobo_toggled);
    connect(ui->cbVisibleYellowChocobo, &QCheckBox::toggled, this, &BlackChocobo::cbVisibleYellowChocobo_toggled);
    connect(ui->cbVisibleGreenChocobo, &QCheckBox::toggled, this, &BlackChocobo::cbVisibleGreenChocobo_toggled);
    connect(ui->cbVisibleBlueChocobo, &QCheckBox::toggled, this, &BlackChocobo::cbVisibleBlueChocobo_toggled);
    connect(ui->cbVisibleBlackChocobo, &QCheckBox::toggled, this, &BlackChocobo::cbVisibleBlackChocobo_toggled);
    connect(ui->cbVisibleGoldChocobo, &QCheckBox::toggled, this, &BlackChocobo::cbVisibleGoldChocobo_toggled);
    connect(ui->cbRubyDead, &QCheckBox::toggled, this, &BlackChocobo::cbRubyDead_toggled);
    connect(ui->cbEmeraldDead, &QCheckBox::toggled, this, &BlackChocobo::cbEmeraldDead_toggled);
    connect(ui->cbBm1_1, &QCheckBox::toggled, this, &BlackChocobo::cbBm1_1_toggled);
    connect(ui->cbBm1_2, &QCheckBox::toggled, this, &BlackChocobo::cbBm1_2_toggled);
    connect(ui->cbBm1_3, &QCheckBox::toggled, this, &BlackChocobo::cbBm1_3_toggled);
    connect(ui->cbBm1_4, &QCheckBox::toggled, this, &BlackChocobo::cbBm1_4_toggled);
    connect(ui->cbBm1_5, &QCheckBox::toggled, this, &BlackChocobo::cbBm1_5_toggled);
    connect(ui->cbBm1_6, &QCheckBox::toggled, this, &BlackChocobo::cbBm1_6_toggled);
    connect(ui->cbBm1_7, &QCheckBox::toggled, this, &BlackChocobo::cbBm1_7_toggled);
    connect(ui->cbBm1_8, &QCheckBox::toggled, this, &BlackChocobo::cbBm1_8_toggled);
    connect(ui->cbBm2_1, &QCheckBox::toggled, this, &BlackChocobo::cbBm2_1_toggled);
    connect(ui->cbBm2_2, &QCheckBox::toggled, this, &BlackChocobo::cbBm2_2_toggled);
    connect(ui->cbBm2_3, &QCheckBox::toggled, this, &BlackChocobo::cbBm2_3_toggled);
    connect(ui->cbBm2_4, &QCheckBox::toggled, this, &BlackChocobo::cbBm2_4_toggled);
    connect(ui->cbBm2_5, &QCheckBox::toggled, this, &BlackChocobo::cbBm2_5_toggled);
    connect(ui->cbBm2_6, &QCheckBox::toggled, this, &BlackChocobo::cbBm2_6_toggled);
    connect(ui->cbBm2_7, &QCheckBox::toggled, this, &BlackChocobo::cbBm2_7_toggled);
    connect(ui->cbBm2_8, &QCheckBox::toggled, this, &BlackChocobo::cbBm2_8_toggled);
    connect(ui->cbBm3_1, &QCheckBox::toggled, this, &BlackChocobo::cbBm3_1_toggled);
    connect(ui->cbBm3_2, &QCheckBox::toggled, this, &BlackChocobo::cbBm3_2_toggled);
    connect(ui->cbBm3_3, &QCheckBox::toggled, this, &BlackChocobo::cbBm3_3_toggled);
    connect(ui->cbBm3_4, &QCheckBox::toggled, this, &BlackChocobo::cbBm3_4_toggled);
    connect(ui->cbBm3_5, &QCheckBox::toggled, this, &BlackChocobo::cbBm3_5_toggled);
    connect(ui->cbBm3_6, &QCheckBox::toggled, this, &BlackChocobo::cbBm3_6_toggled);
    connect(ui->cbBm3_7, &QCheckBox::toggled, this, &BlackChocobo::cbBm3_7_toggled);
    connect(ui->cbBm3_8, &QCheckBox::toggled, this, &BlackChocobo::cbBm3_8_toggled);
    connect(ui->cbS7pl_1, &QCheckBox::toggled, this, &BlackChocobo::cbS7pl_1_toggled);
    connect(ui->cbS7pl_2, &QCheckBox::toggled, this, &BlackChocobo::cbS7pl_2_toggled);
    connect(ui->cbS7pl_3, &QCheckBox::toggled, this, &BlackChocobo::cbS7pl_3_toggled);
    connect(ui->cbS7pl_4, &QCheckBox::toggled, this, &BlackChocobo::cbS7pl_4_toggled);
    connect(ui->cbS7pl_5, &QCheckBox::toggled, this, &BlackChocobo::cbS7pl_5_toggled);
    connect(ui->cbS7pl_6, &QCheckBox::toggled, this, &BlackChocobo::cbS7pl_6_toggled);
    connect(ui->cbS7pl_7, &QCheckBox::toggled, this, &BlackChocobo::cbS7pl_7_toggled);
    connect(ui->cbS7pl_8, &QCheckBox::toggled, this, &BlackChocobo::cbS7pl_8_toggled);
    connect(ui->cbS7ts_1, &QCheckBox::toggled, this, &BlackChocobo::cbS7ts_1_toggled);
    connect(ui->cbS7ts_2, &QCheckBox::toggled, this, &BlackChocobo::cbS7ts_2_toggled);
    connect(ui->cbS7ts_3, &QCheckBox::toggled, this, &BlackChocobo::cbS7ts_3_toggled);
    connect(ui->cbS7ts_4, &QCheckBox::toggled, this, &BlackChocobo::cbS7ts_4_toggled);
    connect(ui->cbS7ts_5, &QCheckBox::toggled, this, &BlackChocobo::cbS7ts_5_toggled);
    connect(ui->cbS7ts_6, &QCheckBox::toggled, this, &BlackChocobo::cbS7ts_6_toggled);
    connect(ui->cbS7ts_7, &QCheckBox::toggled, this, &BlackChocobo::cbS7ts_7_toggled);
    connect(ui->cbS7ts_8, &QCheckBox::toggled, this, &BlackChocobo::cbS7ts_8_toggled);
    connect(ui->cbTutSub, &QCheckBox::toggled, this, &BlackChocobo::cbTutSub_toggled);
    connect(ui->cbMidgartrain_8, &QCheckBox::toggled, this, &BlackChocobo::cbMidgartrain_8_toggled);
    connect(ui->cbMidgartrain_7, &QCheckBox::toggled, this, &BlackChocobo::cbMidgartrain_7_toggled);
    connect(ui->cbMidgartrain_6, &QCheckBox::toggled, this, &BlackChocobo::cbMidgartrain_6_toggled);
    connect(ui->cbMidgartrain_5, &QCheckBox::toggled, this, &BlackChocobo::cbMidgartrain_5_toggled);
    connect(ui->cbMidgartrain_4, &QCheckBox::toggled, this, &BlackChocobo::cbMidgartrain_4_toggled);
    connect(ui->cbMidgartrain_3, &QCheckBox::toggled, this, &BlackChocobo::cbMidgartrain_3_toggled);
    connect(ui->cbMidgartrain_2, &QCheckBox::toggled, this, &BlackChocobo::cbMidgartrain_2_toggled);
    connect(ui->cbMidgartrain_1, &QCheckBox::toggled, this, &BlackChocobo::cbMidgartrain_1_toggled);
    connect(ui->cbYuffieForest, &QCheckBox::toggled, this, &BlackChocobo::cbYuffieForest_toggled);
    connect(ui->cbRegYuffie, &QCheckBox::toggled, this, &BlackChocobo::cbRegYuffie_toggled);
    connect(ui->cbRegVinny, &QCheckBox::toggled, this, &BlackChocobo::cbRegVinny_toggled);
    //QComboBoxes
    connect(ui->comboHexEditor, qOverload<int>(&QComboBox::currentIndexChanged), this, &BlackChocobo::comboHexEditor_currentIndexChanged);
    connect(ui->comboSlotNumber, qOverload<int>(&QComboBox::currentIndexChanged), this, &BlackChocobo::comboSlotNumber_currentIndexChanged);
    connect(ui->comboHighwindBuggy, qOverload<int>(&QComboBox::currentIndexChanged), this, &BlackChocobo::comboHighwindBuggy_currentIndexChanged);
    connect(ui->comboMapControls, qOverload<int>(&QComboBox::currentIndexChanged), this, &BlackChocobo::comboMapControls_currentIndexChanged);
    connect(ui->comboZVar, qOverload<int>(&QComboBox::currentIndexChanged), this, &BlackChocobo::comboZVar_currentIndexChanged);
    connect(ui->comboCompareSlot, qOverload<int>(&QComboBox::currentIndexChanged), this, &BlackChocobo::comboCompareSlot_currentIndexChanged);
    connect(ui->comboS7Slums, qOverload<int>(&QComboBox::currentIndexChanged), this, &BlackChocobo::comboS7Slums_currentIndexChanged);
    connect(ui->comboReplay, qOverload<int>(&QComboBox::currentIndexChanged), this, &BlackChocobo::comboReplay_currentIndexChanged);
    //Misc
    connect(ui->tblUnknown, &QTableWidget::itemChanged, this, &BlackChocobo::tblUnknown_itemChanged);
    connect(ui->slideWorldX, &QSlider::valueChanged, this, &BlackChocobo::slideWorldX_valueChanged);
    connect(ui->slideWorldY, &QSlider::valueChanged, this, &BlackChocobo::slideWorldY_valueChanged);
    connect(ui->worldMapView, &QWidget::customContextMenuRequested, this, &BlackChocobo::worldMapView_customContextMenuRequested);
    
    connect(ui->linePsxDesc, &QLineEdit::textChanged, this, &BlackChocobo::linePsxDesc_textChanged);
    connect(ui->comboSlotRegion, &QComboBox::currentIndexChanged, this, &BlackChocobo::comboSlotRegionChanged);
    connect(ui->tblMateria, &QTableWidget::currentCellChanged, this, &BlackChocobo::tblMateria_currentCellChanged);
    connect(ui->tabWidget, &QTabWidget::currentChanged, this, &BlackChocobo::tabWidget_currentChanged);
    connect(ui->locationToolBox, &QToolBox::currentChanged, this, &BlackChocobo::locationToolBox_currentChanged);
    connect(ui->testDataTabWidget, &QTabWidget::currentChanged, this, &BlackChocobo::testDataTabWidget_currentChanged);
    //UI -> UI
    connect(ui->tblUnknown->verticalScrollBar(), &QScrollBar::valueChanged, ui->tblCompareUnknown->verticalScrollBar(), &QScrollBar::setValue);
    connect(ui->tblCompareUnknown->verticalScrollBar(), &QScrollBar::valueChanged, ui->tblUnknown->verticalScrollBar(), &QScrollBar::setValue);
    connect(ui->comboWorldPartyLeader, qOverload<int>(&QComboBox::currentIndexChanged), ui->sbLeaderId, &QSpinBox::setValue);
    connect(ui->sbLeaderId, qOverload<int>(&QSpinBox::valueChanged), ui->comboWorldPartyLeader, &QComboBox::setCurrentIndex);

    connect(saveIcon, &SaveIcon::nextIcon, ui->lblPsxIcon, &QLabel::setPixmap);

    connect(ff7, &FF7Save::fileChanged, this, &BlackChocobo::fileModified);

    connect(ff7ItemModel, &FF7ItemModel::itemsChanged, this, &BlackChocobo::Items_Changed);

    connect(materia_editor, &MateriaEditor::apChanged, this, &BlackChocobo::materia_ap_changed);
    connect(materia_editor, &MateriaEditor::idChanged, this, &BlackChocobo::materia_id_changed);

    connect(phsList, &PhsListWidget::allowedToggled, this, &BlackChocobo::phsList_box_allowed_toggled);
    connect(phsList, &PhsListWidget::visibleToggled, this, &BlackChocobo::phsList_box_visible_toggled);

    connect(menuList, &MenuListWidget::lockedToggled, this, &BlackChocobo::menuList_box_locked_toggled);
    connect(menuList, &MenuListWidget::visibleToggled, this, &BlackChocobo::menuList_box_visible_toggled);

    connect(itemTab, &ItemTab::addedAllItems, this, [=] { statusBar()->showMessage(tr("All Items Added"), 750);});
    connect(itemTab, &ItemTab::clearedAllItems, this, [=] { statusBar()->showMessage(tr("Cleared All Items"), 750);});
    connect(itemTab, &ItemTab::gilChanged, this, &BlackChocobo::gilChanged);
    connect(itemTab, &ItemTab::gpChanged, this, &BlackChocobo::gpChanged);
    connect(itemTab, &ItemTab::battlesChanged, this, &BlackChocobo::battlesChanged);
    connect(itemTab, &ItemTab::runsChanged, this, &BlackChocobo::runsChanged);
    connect(itemTab, &ItemTab::requestFlyerSearch, this, &BlackChocobo::searchForFlyers);
    connect(itemTab, &ItemTab::requestKeyItemSearch, this, &BlackChocobo::searchForKeyItems);
    connect(itemTab, &ItemTab::mysteryPantiesChanged, this, &BlackChocobo::mysteryPantiesChanged);
    connect(itemTab, &ItemTab::daughterLetterChanged, this, &BlackChocobo::letterToDaughterChanged);
    connect(itemTab, &ItemTab::wifeLetterChanged, this, &BlackChocobo::letterToWifeChanged);

    connect(partyTab, &PartyTab::partyChanged, this, &BlackChocobo::partyMembersChanged);
    connect(partyTab, &PartyTab::requestCharacterSlotLoad, this, &BlackChocobo::charButtonClicked);

    connect(partyTab->characterEditor(), &CharEditor::idChanged, this, &BlackChocobo::char_id_changed);
    connect(partyTab->characterEditor(), &CharEditor::levelChanged, this, &BlackChocobo::char_level_changed);
    connect(partyTab->characterEditor(), &CharEditor::strengthChanged, this, &BlackChocobo::char_str_changed);
    connect(partyTab->characterEditor(), &CharEditor::vitalityChanged, this, &BlackChocobo::char_vit_changed);
    connect(partyTab->characterEditor(), &CharEditor::magicChanged, this, &BlackChocobo::char_mag_changed);
    connect(partyTab->characterEditor(), &CharEditor::spiritChanged, this, &BlackChocobo::char_spi_changed);
    connect(partyTab->characterEditor(), &CharEditor::dexterityChanged, this, &BlackChocobo::char_dex_changed);
    connect(partyTab->characterEditor(), &CharEditor::luckChanged, this, &BlackChocobo::char_lck_changed);
    connect(partyTab->characterEditor(), &CharEditor::strengthBonusChanged, this, &BlackChocobo::char_strBonus_changed);
    connect(partyTab->characterEditor(), &CharEditor::vitalityBonusChanged, this, &BlackChocobo::char_vitBonus_changed);
    connect(partyTab->characterEditor(), &CharEditor::magicBonusChanged, this, &BlackChocobo::char_magBonus_changed);
    connect(partyTab->characterEditor(), &CharEditor::spiritBonusChanged, this, &BlackChocobo::char_spiBonus_changed);
    connect(partyTab->characterEditor(), &CharEditor::dexterityBonusChanged, this, &BlackChocobo::char_dexBonus_changed);
    connect(partyTab->characterEditor(), &CharEditor::luckBonusChanged, this, &BlackChocobo::char_lckBonus_changed);
    connect(partyTab->characterEditor(), &CharEditor::limitLevelChanged, this, &BlackChocobo::char_limitLevel_changed);
    connect(partyTab->characterEditor(), &CharEditor::limitBarChanged, this, &BlackChocobo::char_limitBar_changed);
    connect(partyTab->characterEditor(), &CharEditor::nameChanged, this, &BlackChocobo::char_name_changed);
    connect(partyTab->characterEditor(), &CharEditor::weaponChanged, this, &BlackChocobo::char_weapon_changed);
    connect(partyTab->characterEditor(), &CharEditor::armorChanged, this, &BlackChocobo::char_armor_changed);
    connect(partyTab->characterEditor(), &CharEditor::accessoryChanged, this, &BlackChocobo::char_accessory_changed);
    connect(partyTab->characterEditor(), &CharEditor::curHpChanged, this, &BlackChocobo::char_curHp_changed);
    connect(partyTab->characterEditor(), &CharEditor::maxHpChanged, this, &BlackChocobo::char_maxHp_changed);
    connect(partyTab->characterEditor(), &CharEditor::curMpChanged, this, &BlackChocobo::char_curMp_changed);
    connect(partyTab->characterEditor(), &CharEditor::maxMpChanged, this, &BlackChocobo::char_maxMp_changed);
    connect(partyTab->characterEditor(), &CharEditor::killsChanged, this, &BlackChocobo::char_kills_changed);
    connect(partyTab->characterEditor(), &CharEditor::rowChanged, this, &BlackChocobo::char_row_changed);
    connect(partyTab->characterEditor(), &CharEditor::levelProgressChanged, this, &BlackChocobo::char_levelProgress_changed);
    connect(partyTab->characterEditor(), &CharEditor::stateChanged, this, &BlackChocobo::char_sadnessfury_changed);
    connect(partyTab->characterEditor(), &CharEditor::limitsChanged, this, &BlackChocobo::char_limits_changed);
    connect(partyTab->characterEditor(), &CharEditor::times1UsedChanged, this, &BlackChocobo::char_timesused1_changed);
    connect(partyTab->characterEditor(), &CharEditor::times2UsedChanged, this, &BlackChocobo::char_timeused2_changed);
    connect(partyTab->characterEditor(), &CharEditor::times3UsedChanged, this, &BlackChocobo::char_timeused3_changed);
    connect(partyTab->characterEditor(), &CharEditor::baseHpChanged, this, &BlackChocobo::char_baseHp_changed);
    connect(partyTab->characterEditor(), &CharEditor::baseMpChanged, this, &BlackChocobo::char_baseMp_changed);
    connect(partyTab->characterEditor(), &CharEditor::expChanged, this, &BlackChocobo::char_exp_changed);
    connect(partyTab->characterEditor(), &CharEditor::mslotChanged, this, &BlackChocobo::char_mslot_changed);
    connect(partyTab->characterEditor(), &CharEditor::materiaChanged, this, &BlackChocobo::char_materia_changed);
    connect(partyTab->characterEditor(), &CharEditor::expNextChanged, this, &BlackChocobo::char_expNext_changed);

    connect(chocoboManager, &ChocoboManager::ownedChanged, this, &BlackChocobo::cm_stablesOwnedChanged);
    connect(chocoboManager, &ChocoboManager::stableMaskChanged, this, &BlackChocobo::cm_stableMaskChanged);
    connect(chocoboManager, &ChocoboManager::occupiedChanged, this, &BlackChocobo::cm_stablesOccupiedChanged);
    connect(chocoboManager, &ChocoboManager::nameChanged, this, &BlackChocobo::cm_nameChanged);
    connect(chocoboManager, &ChocoboManager::cantMateChanged, this, &BlackChocobo::cm_mated_toggled);
    connect(chocoboManager, &ChocoboManager::speedChanged, this, &BlackChocobo::cm_speedChanged);
    connect(chocoboManager, &ChocoboManager::mSpeedChanged, this, &BlackChocobo::cm_maxspeedChanged);
    connect(chocoboManager, &ChocoboManager::sprintChanged, this, &BlackChocobo::cm_sprintChanged);
    connect(chocoboManager, &ChocoboManager::mSprintChanged, this, &BlackChocobo::cm_maxsprintChanged);
    connect(chocoboManager, &ChocoboManager::staminaChanged, this, &BlackChocobo::cm_staminaChanged);
    connect(chocoboManager, &ChocoboManager::sexChanged, this, &BlackChocobo::cm_sexChanged);
    connect(chocoboManager, &ChocoboManager::typeChanged, this, &BlackChocobo::cm_typeChanged);
    connect(chocoboManager, &ChocoboManager::accelChanged, this, &BlackChocobo::cm_accelChanged);
    connect(chocoboManager, &ChocoboManager::coopChanged, this, &BlackChocobo::cm_coopChanged);
    connect(chocoboManager, &ChocoboManager::intelligenceChanged, this, &BlackChocobo::cm_intelChanged);
    connect(chocoboManager, &ChocoboManager::personalityChanged, this, &BlackChocobo::cm_personalityChanged);
    connect(chocoboManager, &ChocoboManager::pCountChanged, this, &BlackChocobo::cm_pcountChanged);
    connect(chocoboManager, &ChocoboManager::winsChanged, this, &BlackChocobo::cm_raceswonChanged);
    connect(chocoboManager, &ChocoboManager::penChanged, this, &BlackChocobo::cm_pensChanged);
    connect(chocoboManager, &ChocoboManager::ratingChanged, this, &BlackChocobo::cm_ratingChanged);

    connect(locationViewer, &LocationViewer::locationStringChanged, this, &BlackChocobo::location_textChanged);
    connect(locationViewer, &LocationViewer::locIdChanged, this, &BlackChocobo::loc_id_valueChanged);
    connect(locationViewer, &LocationViewer::mapIdChanged, this, &BlackChocobo::map_id_valueChanged);
    connect(locationViewer, &LocationViewer::xChanged, this, &BlackChocobo::coord_x_valueChanged);
    connect(locationViewer, &LocationViewer::yChanged, this, &BlackChocobo::coord_y_valueChanged);
    connect(locationViewer, &LocationViewer::tChanged, this, &BlackChocobo::coord_t_valueChanged);
    connect(locationViewer, &LocationViewer::dChanged, this, &BlackChocobo::coord_d_valueChanged);
    connect(locationViewer, &LocationViewer::locationChanged, this, &BlackChocobo::locationSelectionChanged);
    connect(locationViewer, &LocationViewer::fieldItemConnectRequest, this, &BlackChocobo::connectFieldItem);
    connect(locationViewer, &LocationViewer::fieldItemCheck, this, &BlackChocobo::checkFieldItem);
    connect(locationViewer, &LocationViewer::fieldItemChanged, this, &BlackChocobo::fieldItemStateChanged);

    connect(optionsWidget, &OptionsWidget::dialogColorLLChanged, this, &BlackChocobo::setDialogColorLL);
    connect(optionsWidget, &OptionsWidget::dialogColorLRChanged, this, &BlackChocobo::setDialogColorLR);
    connect(optionsWidget, &OptionsWidget::dialogColorULChanged, this, &BlackChocobo::setDialogColorUL);
    connect(optionsWidget, &OptionsWidget::dialogColorURChanged, this, &BlackChocobo::setDialogColorUR);
    connect(optionsWidget, &OptionsWidget::magicOrderChanged, this, &BlackChocobo::setMagicOrder);
    connect(optionsWidget, &OptionsWidget::cameraChanged, this, &BlackChocobo::setCameraMode);
    connect(optionsWidget, &OptionsWidget::atbChanged, this, &BlackChocobo::setAtbMode);
    connect(optionsWidget, &OptionsWidget::cursorChanged, this, &BlackChocobo::setCursorMode);
    connect(optionsWidget, &OptionsWidget::controllerModeChanged, this, &BlackChocobo::setControlMode);
    connect(optionsWidget, &OptionsWidget::soundChanged, this, &BlackChocobo::setSoundMode);
    connect(optionsWidget, &OptionsWidget::fieldMessageSpeedChanged, this, &BlackChocobo::setFieldMessageSpeed);
    connect(optionsWidget, &OptionsWidget::battleMessageSpeedChanged, this, &BlackChocobo::setBattleMessageSpeed);
    connect(optionsWidget, &OptionsWidget::battleSpeedChanged, this, &BlackChocobo::setBattleSpeed);
    connect(optionsWidget, &OptionsWidget::fieldHelpChanged, this, &BlackChocobo::setFieldHelp);
    connect(optionsWidget, &OptionsWidget::battleTargetsChanged, this, &BlackChocobo::setBattleTargets);
    connect(optionsWidget, &OptionsWidget::battleHelpChanged, this, &BlackChocobo::setBattleHelp);
    connect(optionsWidget, &OptionsWidget::inputChanged, this, &BlackChocobo::setButtonMapping);
}

void BlackChocobo::loadBasicSettings()
{
    if (!BCSettings::value(SETTINGS::MAINGEOMETRY).isNull())
        restoreGeometry(BCSettings::value(SETTINGS::MAINGEOMETRY).toByteArray());
    else {
        adjustSize();
        saveGeometry();
    }
}

void BlackChocobo::loadChildWidgetSettings()
{
    QApplication::setAttribute(Qt::AA_DontUseNativeDialogs, !BCSettings::value(SETTINGS::USENATIVEDIALOGS, false).toBool());
    materia_editor->setEditableMateriaCombo(BCSettings::value(SETTINGS::EDITABLECOMBOS, true).toBool());
    materia_editor->setShowPlaceHolderMateria(BCSettings::value(SETTINGS::SHOWPLACEHOLDERS, false).toBool());
    itemTab->itemList()->setEditableItemCombo(BCSettings::value(SETTINGS::EDITABLECOMBOS, true).toBool());
    itemTab->itemList()->setShowPlaceholderItems(BCSettings::value(SETTINGS::SHOWPLACEHOLDERS, false).toBool());
    partyTab->characterEditor()->setEditableComboBoxes(BCSettings::value(SETTINGS::EDITABLECOMBOS, true).toBool());
    partyTab->characterEditor()->setAdvancedMode(BCSettings::value(SETTINGS::CHARADVANCED, false).toBool());
    partyTab->characterEditor()->setAutoLevel(BCSettings::value(SETTINGS::AUTOGROWTH, true).toBool());
    partyTab->characterEditor()->setAutoStatCalc(BCSettings::value(SETTINGS::AUTOGROWTH, true).toBool());
    partyTab->characterEditor()->setShowPlaceholderMateria(BCSettings::value(SETTINGS::SHOWPLACEHOLDERS, false).toBool());
    chocoboManager->setAdvancedMode(BCSettings::value(SETTINGS::CHOCOADVANCED, false).toBool());
    locationViewer->setAdvancedMode(BCSettings::value(SETTINGS::LOCVIEWADVANCED, false).toBool());
    ui->tabWidget->setTabEnabled(9, BCSettings::value(SETTINGS::ENABLETEST, false).toBool());
    if (FF7SaveInfo::isTypePC(ff7->format()) || ff7->format() == FF7SaveInfo::FORMAT::UNKNOWN)
        setControllerMappingVisible(BCSettings::value(SETTINGS::ALWAYSSHOWCONTROLLERMAP, false).toBool());
    ui->bm_unknown->setVisible(BCSettings::value(SETTINGS::PROGRESSADVANCED, false).toBool());
    ui->sbBhId->setVisible(BCSettings::value(SETTINGS::WORLDMAPADVANCED, false).toBool());
    ui->sbLeaderId->setVisible(BCSettings::value(SETTINGS::WORLDMAPADVANCED, false).toBool());
    if(BCSettings::value(SETTINGS::ITEMCAP99).toBool())
        itemTab->itemList()->setMaximumItemQty(99);
    else
        itemTab->itemList()->setMaximumItemQty(127);
}

/*~~~~~~ END GUI SETUP ~~~~~~~*/
BlackChocobo::~BlackChocobo()
{
    delete ui;
}

void BlackChocobo::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::PaletteChange) {
        QPalette palette = BCSettings::paletteForSetting();
        QList<QWidget*> widgets = findChildren<QWidget *>(QString(), Qt::FindChildrenRecursively);
        for (QWidget * widget : std::as_const(widgets))
             widget->setPalette(palette);
        hexEditor->setAddressAreaColor(palette.alternateBase().color());
        QIcon::setThemeSearchPaths(QIcon::themeSearchPaths() << QStringLiteral(":/icons"));
#if defined(QT_OS_WIN32) || defined(QT_OS_MAC)
        QIcon::setThemeName(QStringLiteral("bc-%1").arg(checkIconTheme()));
#else
        if(QIcon::themeName().startsWith(QStringLiteral("bc")))
            QIcon::setThemeName(QStringLiteral("bc-%1").arg(checkIconTheme()));
        else
            QIcon::setFallbackThemeName(QStringLiteral("bc-%1").arg(checkIconTheme()));
#endif
    } else if (e->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
        ui->tabWidget->setTabText(0, tr("Party"));
        ui->tabWidget->setTabText(1, tr("Items"));
        ui->tabWidget->setTabText(3, tr("Chocobo"));
        ui->tabWidget->setTabText(7, tr("Game Options"));
        populateCombos();
        materiaupdate();
        updateStolenMateria();
        if (ui->psxExtras->isVisible())
            update_hexEditor_PSXInfo();
    } else {
        QWidget::changeEvent(e);
    }
}

void BlackChocobo::dragEnterEvent(QDragEnterEvent *e)
{
    e->accept();
}

void BlackChocobo::dropEvent(QDropEvent *e)
{
    if (ff7->isFileModified()) {
        if (!saveChanges())
            return;
    }

    auto mimeData = e->mimeData();
    if (mimeData->hasUrls())
        loadFileFull(mimeData->urls().at(0).toLocalFile(), 0);
}

bool BlackChocobo::saveChanges(void)
{
    auto result = QMessageBox::question(this, tr("Unsaved Changes"), tr("Save Changes to the File:\n%1").arg(ff7->fileName())
                                   , QMessageBox::StandardButton::Yes | QMessageBox::StandardButton::No | QMessageBox::StandardButton::Cancel);
    switch (result) {
    case QMessageBox::StandardButton::Yes:
        actionSave_triggered();
        return true;
    case QMessageBox::StandardButton::No:
        return true;
    default: return false;
    }
}

void BlackChocobo::closeEvent(QCloseEvent *e)
{
    if (ff7->isFileModified()) {
        if(!saveChanges())
            e->ignore();
        else
            e->accept();
    }
    BCSettings::setValue(SETTINGS::MAINGEOMETRY, saveGeometry());
}

void BlackChocobo::resizeEvent(QResizeEvent *)
{
    BCSettings::setValue(SETTINGS::MAINGEOMETRY, saveGeometry());
    fileModified(ff7->isFileModified());
}

void BlackChocobo::moveEvent(QMoveEvent *)
{
    BCSettings::setValue(SETTINGS::MAINGEOMETRY, saveGeometry());
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~LOAD/SAVE FUNCTIONS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void BlackChocobo::actionOpenSaveFile_triggered()
{
    if (ff7->isFileModified()) {
        if (!saveChanges())
            return;//cancel load.
    }

    QString fileName = BCDialog::getOpenFileName(this, tr("Open Final Fantasy 7 Save"), BCSettings::value(SETTINGS::LOADPATH).toString(), FF7SaveInfo::knownTypesFilter());
    if (!fileName.isEmpty())
        loadFileFull(fileName, 0);
}

void BlackChocobo::actionReload_triggered()
{
    if (!ff7->fileName().isEmpty())
        loadFileFull(ff7->fileName(), 1);
}

void BlackChocobo::loadFileFull(const QString &fileName, int reload)
{
    //if called from reload then int reload ==1 (don't call slot select)
    QFile file(fileName);

    if (!file.open(QFile::ReadOnly)) {
        QMessageBox::warning(this, tr("Black Chocobo"), tr("Cannot read file %1:\n%2.") .arg(fileName, file.errorString()));
        return;
    }
    if(!reload)
        prevFile = ff7->fileName();

    hexEditor->setCursorPosition(0);
    hexCursorPos = 0;

    if (!ff7->loadFile(fileName)) {
        QMessageBox::information(this, tr("Load Failed"), tr("Failed to Load File"));
        return;
    }

    _init = false;
    fileModified(false);

    if (ff7->numberOfSlots() == 1 ) {
        s = 0;
        guirefresh();
        return;
    }

    if (reload) {
        guirefresh();
        return;
    }

    SlotSelect slotselect(ff7, true, this);
    int i = slotselect.exec();

    switch(i) {
        case SlotSelect::LOAD_NEW: {
            actionOpenSaveFile_triggered();
            return;
        }
        case SlotSelect::CANCEL: {
            s = 0;
            break;
        }
        default: s = i;
    }
    guirefresh();
}

void BlackChocobo::actionImportSlotFromFile_triggered()
{
    QString fileName = BCDialog::getOpenFileName(this,
                       tr("Open Final Fantasy 7 Save"), BCSettings::value(SETTINGS::LOADPATH).toString(),
                       FF7SaveInfo::knownTypesFilter());
    if (fileName.isEmpty())
        return;

    FF7Save *tempSave = new FF7Save();
    if (!tempSave->loadFile(fileName)) {
        ui->statusBar->showMessage(tr("Error Loading File %1").arg(fileName), 2000);
        return;
    }

    int fileSlot = 0;
    QString message;
    if (FF7SaveInfo::slotCount(tempSave->format()) > 1) {
        SlotSelect *SSelect = new SlotSelect(tempSave, false, this);
        fileSlot = SSelect->exec();
        if (fileSlot == SlotSelect::CANCEL) {
            message = tr("Import Canceled");
            return;
        }
        message = tr("Imported Slot:%2 from %1 -> Slot:%3").arg(fileName, QString::number(fileSlot + 1), QString::number(s + 1));
    } else {
        message = tr("Imported %1 -> Slot:%2").arg(fileName, QString::number(s + 1));
    }

    if (!ff7->importSlot(s, fileName, fileSlot)) {
        ui->statusBar->showMessage(tr("Error Importing Slot %1").arg(QString::number(s+1)), 2000);
        return;
    }
    ui->statusBar->showMessage(message, 2000);
    guirefresh();
    ff7->setFileModified(true, s);
}

void BlackChocobo::actionImportChar_triggered()
{
    QString fileName = BCDialog::getOpenFileName(this, tr("Select FF7 Character Stat File"), BCSettings::value(SETTINGS::STATFOLDER).toString(), tr("FF7 Character Stat File(*.char)"));
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly)) {
        QMessageBox::warning(this, tr("Black Chocobo"), tr("Cannot read file %1:\n%2.").arg(fileName, file.errorString()));
        return;
    }
    if (file.size() != 0x84) {
        QMessageBox::warning(this, tr("Black Chocobo"), tr("%1:\n%2 is Not a FF7 Character Stat File.").arg(fileName, file.errorString()));
        return;
    }
    QByteArray new_char;
    new_char = file.readAll();
    ff7->importCharacter(s, curchar, new_char);
    partyTab->setCharacter(ff7->character(s, curchar), ff7->charName(s, curchar));
    partyTab->setButtonImageToId(curchar, ff7->character(s, curchar).id);
}

void BlackChocobo::actionExportChar_triggered()
{
    QString fileName = BCDialog::getSaveFileName(this, ff7->region(s),
                       tr("Save FF7 Character File"), BCSettings::value(SETTINGS::STATFOLDER).toString(),
                       tr("FF7 Character Stat File(*.char)"));
    if (fileName.isEmpty())
        return;

    if (ff7->exportCharacter(s, curchar, fileName))
        ui->statusBar->showMessage(tr("Character Export Successful"), 1000);
    else
        ui->statusBar->showMessage(tr("Character Export Failed"), 2000);
}

bool BlackChocobo::actionSave_triggered()
{
    if (_init || ff7->fileName().isEmpty())
        return actionSaveFileAs_triggered();

    if(!ff7->isFileModified())
        return true;

    if(BCSettings::value(SETTINGS::MAKEBACKUPS, false).toBool()) {
        auto name = QFileInfo(ff7->fileName()).fileName();
        auto path = BCSettings::value(SETTINGS::STATFOLDER, QDir::homePath()).toString();
        QString outfile = QStringLiteral("%1/%2.bak").arg(path, name);
        int i = 1;
        while(QFile(outfile).exists()) {
            outfile = QStringLiteral("%1/%2(%3).bak").arg(path, name, QString::number(i));
            i++;
        }
        QFile::copy(ff7->fileName(), outfile);
    }

    return saveFileFull(ff7->fileName());
}

bool BlackChocobo::actionSaveFileAs_triggered()
{
    QMap<QString, FF7SaveInfo::FORMAT> typeMap;
    typeMap[FF7SaveInfo::typeFilter(FF7SaveInfo::FORMAT::PC)] = FF7SaveInfo::FORMAT::PC;
    typeMap[FF7SaveInfo::typeFilter(FF7SaveInfo::FORMAT::SWITCH)] = FF7SaveInfo::FORMAT::SWITCH;
    typeMap[FF7SaveInfo::typeFilter(FF7SaveInfo::FORMAT::VMC)] = FF7SaveInfo::FORMAT::VMC;
    typeMap[FF7SaveInfo::typeFilter(FF7SaveInfo::FORMAT::VGS)] = FF7SaveInfo::FORMAT::VGS;
    typeMap[FF7SaveInfo::typeFilter(FF7SaveInfo::FORMAT::DEX)] = FF7SaveInfo::FORMAT::DEX;
    typeMap[FF7SaveInfo::typeFilter(FF7SaveInfo::FORMAT::PSP)] = FF7SaveInfo::FORMAT::PSP;
    typeMap[FF7SaveInfo::typeFilter(FF7SaveInfo::FORMAT::PSX)] = FF7SaveInfo::FORMAT::PSX;
    typeMap[FF7SaveInfo::typeFilter(FF7SaveInfo::FORMAT::PS3)] = FF7SaveInfo::FORMAT::PS3;
    typeMap[FF7SaveInfo::typeFilter(FF7SaveInfo::FORMAT::PGE)] = FF7SaveInfo::FORMAT::PGE;
    typeMap[FF7SaveInfo::typeFilter(FF7SaveInfo::FORMAT::PDA)] = FF7SaveInfo::FORMAT::PDA;
    const QStringList typeKeys = typeMap.keys();
    QString selectedType = ff7->format() == FF7SaveInfo::FORMAT::UNKNOWN ? FF7SaveInfo::typeFilter(FF7SaveInfo::FORMAT::PC) : typeMap.key(ff7->format(), QString());
    QString selectedFile = ff7->format() == FF7SaveInfo::FORMAT::UNKNOWN ? QStringLiteral("save00.ff7") : QFile(ff7->fileName()).fileName();
    QString path;

    if (ff7->format() == FF7SaveInfo::FORMAT::PC)
            path = BCSettings::value(SETTINGS::PCSAVEPATH).toString();
    else if ((ff7->format() == FF7SaveInfo::FORMAT::VMC)
             || (ff7->format() == FF7SaveInfo::FORMAT::VGS)
             || (ff7->format() == FF7SaveInfo::FORMAT::DEX))
        path = BCSettings::value(SETTINGS::EMUSAVEPATH).toString();

    QString fileName = BCDialog::getSaveFileName(this,
                                                 ff7->region(s),
                                                 tr("Select A File to Save As"),
                                                 path,
                                                 typeKeys.join(QStringLiteral(";;")),
                                                 &selectedType,
                                                 selectedFile);

    if (fileName.isEmpty())
        return false;
    FF7SaveInfo::FORMAT newType = typeMap[selectedType];

    if (ff7->format() == newType)
        return saveFileFull(fileName);

    if (ff7->exportFile(fileName, newType, s)) {
        ui->statusBar->showMessage(tr("Export Successful"), 1000);
        fileModified(false);
        return true;
    }

    ui->statusBar->showMessage(tr("Export Failed"), 2000);
    return false;
}

bool BlackChocobo::saveFileFull(const QString &fileName)
{
    if (ff7->saveFile(fileName, s)) {
        //if no save was loaded and new game was clicked be sure to act like a game was loaded.
        if (_init)
            _init = false;

        fileModified(false);
        guirefresh();
        return true;
    }

    QMessageBox::information(this, tr("Save Error"), tr("Failed to save file\n%1").arg(fileName));
    return false;
}

void BlackChocobo::actionNewGame_triggered()
{
    QString save_name = BCSettings::value(SETTINGS::CUSTOMDEFAULTSAVE).toBool() ?
                BCSettings::value(SETTINGS::DEFAULTSAVE).toString() : QString();

    QString region = ff7->region(s).isEmpty() ?
                BCSettings::value(SETTINGS::REGION).toString() : ff7->region(s);

    ff7->newGame(s, region, save_name);//call the new game function
    ui->statusBar->showMessage(tr("New Game Created - Using: %1")
                               .arg(save_name.isEmpty() ? tr("Builtin Data") : save_name), 2000);
    _init = false;
    guirefresh();
}

void BlackChocobo::actionNewGamePlus_triggered()
{
    QString save_name;
    if (BCSettings::value(SETTINGS::CUSTOMDEFAULTSAVE).toBool())
        save_name = BCSettings::value(SETTINGS::DEFAULTSAVE).toString();

    ff7->newGamePlus(s, ff7->fileName(), save_name);
    ui->statusBar->showMessage(tr("New Game Plus Created - Using: %1")
                               .arg(save_name.isEmpty() ? tr("Builtin Data") : save_name), 2000);
    guirefresh();
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~END LOAD/SAVE FUNCTIONS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MENU ACTIONS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void BlackChocobo::actionClearSlot_triggered()
{
    ff7->clearSlot(s);
    guirefresh();
}

void BlackChocobo::actionPreviousSlot_triggered()
{
    if (ff7->format() == FF7SaveInfo::FORMAT::UNKNOWN || s <= 0)
        return;
    s--;
    guirefresh();
}

void BlackChocobo::actionNextSlot_triggered()
{
    if (ff7->format() == FF7SaveInfo::FORMAT::UNKNOWN || s >= 14)
        return;
    s++;
    guirefresh();
}

void BlackChocobo::actionAbout_triggered()
{
    About adialog(this);
    adialog.exec();
}

void BlackChocobo::actionCopySlot_triggered()
{
    ff7->copySlot(s);
    ui->actionPasteSlot->setEnabled(true);
}

void BlackChocobo::actionPasteSlot_triggered()
{
    ff7->pasteSlot(s);
    guirefresh();
}

void BlackChocobo::actionShowOptions_triggered()
{
    Options odialog(this);
    connect(&odialog, &Options::requestLanguageChange, this, &BlackChocobo::changeLanguage);
    connect(&odialog, &Options::requestChangeNativeDialog, this, [] (bool useNative){
        QApplication::setAttribute(Qt::AA_DontUseNativeDialogs, !useNative);
    });
    if (odialog.exec()) {
        loadChildWidgetSettings();
    }
    odialog.deleteLater();
}

void BlackChocobo::actionCreateNewMetadata_triggered()
{
    MetadataCreator mdata(this, ff7);
    mdata.exec();
}

void BlackChocobo::actionShowSelectionDialog_triggered()
{
    SlotSelect slotselect(ff7, false, this);
    int slot = slotselect.exec();
    switch(slot) {
        case SlotSelect::LOAD_NEW:
        case SlotSelect::CANCEL: return;
        default: s = slot;
    };
    guirefresh();
}

void BlackChocobo::actionOpenAchievementFile_triggered()
{
    QString temp = ff7->fileName();
    temp.chop(temp.length() - (temp.lastIndexOf(QStringLiteral("/"))));
    temp.append(QStringLiteral("/achievement.dat"));
    QFile tmp(temp);
    if (!tmp.exists())
        temp = BCDialog::getOpenFileName(this, tr("Select Achievement File"), QDir::homePath(), tr("Dat File (*.dat)"));

    if (temp.isEmpty())
        return;

    BCDialog::achievementDialog(this, temp);
}

/*~~~~~~~~~~~~LANGUAGE & REGION ACTIONS~~~~~~~~~~~~~~*/

void BlackChocobo::changeLanguage(const QVariant &data)
{
    if(!m_translations.contains(data.toString()))
        detectTranslations();

    const auto translations = m_translations.value(BCSettings::value(SETTINGS::LANG).toString());
    for(auto translation : std::as_const(translations))
        QApplication::removeTranslator(translation);

    BCSettings::setValue(SETTINGS::LANG, data);

    const auto translation_values = m_translations.value(data.toString());
    for(auto translation : translation_values)
        QApplication::installTranslator(translation);
}

void BlackChocobo::setOpenFileText(const QString &openFile)
{
    int maxWidth = width() * .85;
    ui->lbl_fileName->setMaximumWidth(maxWidth);
    ui->lbl_fileName->setText(fontMetrics().elidedText(openFile, Qt::ElideMiddle, maxWidth));
}

void BlackChocobo::setRegion(QString region)
{
    if(!load) {
        bool NTSC = ff7->isNTSC(s);
        QString oldRegion = ff7->region(s);
        if (NTSC) {
            if (region.contains(QStringLiteral("PAL")))
                set_pal_time();
        } else {
            if (region.contains(QStringLiteral("NTSC")))
                set_ntsc_time();
        }

        ff7->setRegion(s, region);

        if(region == QStringLiteral("NTSC-J") || BCSettings::value(SETTINGS::ITEMCAP99).toBool())
            itemTab->itemList()->setMaximumItemQty(99);
        else
            itemTab->itemList()->setMaximumItemQty(127);

        if(oldRegion.contains(QStringLiteral("01057")))
            ui->linePsxDesc->setText(ui->linePsxDesc->text().replace(QStringLiteral("ＦＦ７Ｉ"), QStringLiteral("ＦＦ７")));
        else if(ff7->region(s).contains(QStringLiteral("01057")))
            ui->linePsxDesc->setText(ui->linePsxDesc->text().replace(QStringLiteral("ＦＦ７"), QStringLiteral("ＦＦ７Ｉ")));

        if(ff7->isJPN(s))
            ui->linePsxDesc->setText(ui->linePsxDesc->text().replace(QStringLiteral("ＳＡＶＥ"), QStringLiteral("セーブ")));
        else if(!ff7->isJPN(s))
            ui->linePsxDesc->setText(ui->linePsxDesc->text().replace(QStringLiteral("セーブ"), QStringLiteral("ＳＡＶＥ")));
    }
    locationViewer->setRegion(ff7->region(s));

}

void BlackChocobo::actionRegionUSA_triggered(bool checked)
{
    if(!load && checked) {
        setRegion(QStringLiteral("NTSC-U"));
        ui->actionRegionPALGeneric->setChecked(false);
        ui->actionRegionPALFrench->setChecked(false);
        ui->actionRegionPALGerman->setChecked(false);
        ui->actionRegionPALSpanish->setChecked(false);
        ui->actionRegionJPN->setChecked(false);
        ui->actionRegionJPNInternational->setChecked(false);
    }
}

void BlackChocobo::actionRegionPALGeneric_triggered(bool checked)
{
    if(!load && checked) {
        setRegion(QStringLiteral("PAL-E"));
        ui->actionRegionUSA->setChecked(false);
        ui->actionRegionPALGerman->setChecked(false);
        ui->actionRegionPALFrench->setChecked(false);
        ui->actionRegionPALSpanish->setChecked(false);
        ui->actionRegionJPN->setChecked(false);
        ui->actionRegionJPNInternational->setChecked(false);
    }
}

void BlackChocobo::actionRegionPALGerman_triggered(bool checked)
{
    if(!load && checked) {
        setRegion(QStringLiteral("PAL-DE"));
        ui->actionRegionUSA->setChecked(false);
        ui->actionRegionPALGeneric->setChecked(false);
        ui->actionRegionPALFrench->setChecked(false);
        ui->actionRegionPALSpanish->setChecked(false);
        ui->actionRegionJPN->setChecked(false);
        ui->actionRegionJPNInternational->setChecked(false);
    }
}

void BlackChocobo::actionRegionPALSpanish_triggered(bool checked)
{
    if(!load && checked) {
        setRegion(QStringLiteral("PAL-ES"));
        ui->actionRegionUSA->setChecked(false);
        ui->actionRegionPALGeneric->setChecked(false);
        ui->actionRegionPALFrench->setChecked(false);
        ui->actionRegionPALGerman->setChecked(false);
        ui->actionRegionJPN->setChecked(false);
        ui->actionRegionJPNInternational->setChecked(false);
    }
}

void BlackChocobo::actionRegionPALFrench_triggered(bool checked)
{
    if(!load && checked) {
        setRegion(QStringLiteral("PAL-FR"));
        ui->actionRegionUSA->setChecked(false);
        ui->actionRegionPALGeneric->setChecked(false);
        ui->actionRegionPALSpanish->setChecked(false);
        ui->actionRegionPALGerman->setChecked(false);
        ui->actionRegionJPN->setChecked(false);
        ui->actionRegionJPNInternational->setChecked(false);
    }
}

void BlackChocobo::actionRegionJPN_triggered(bool checked)
{
    if(!load && checked) {
        setRegion(QStringLiteral("NTSC-J"));
        ui->actionRegionUSA->setChecked(false);
        ui->actionRegionPALGeneric->setChecked(false);
        ui->actionRegionPALFrench->setChecked(false);
        ui->actionRegionPALGerman->setChecked(false);
        ui->actionRegionPALSpanish->setChecked(false);
        ui->actionRegionJPNInternational->setChecked(false);
    }
}

void BlackChocobo::actionRegionJPNInternational_triggered(bool checked)
{
    if(!load && checked) {
        setRegion(QStringLiteral("NTSC-JI"));
        ui->actionRegionUSA->setChecked(false);
        ui->actionRegionPALGeneric->setChecked(false);
        ui->actionRegionPALFrench->setChecked(false);
        ui->actionRegionPALGerman->setChecked(false);
        ui->actionRegionPALSpanish->setChecked(false);
        ui->actionRegionJPN->setChecked(false);
    }
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~END MENU ACTIONS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~GUI FUNCTIONS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~Set Menu Items~~~~~~~~~~*/
void BlackChocobo::setmenu()
{
    load = true;
    /*~~Disable All Items that are dependent on File Type~~*/
    ui->actionClearSlot->setEnabled(0);
    ui->actionRegionUSA->setChecked(false);
    ui->actionRegionPALGeneric->setChecked(false);
    ui->actionRegionPALGerman->setChecked(false);
    ui->actionRegionPALFrench->setChecked(false);
    ui->actionRegionPALSpanish->setChecked(false);
    ui->actionRegionJPN->setChecked(false);
    ui->actionRegionJPNInternational->setChecked(false);
    ui->actionNextSlot->setEnabled(0);
    ui->actionPreviousSlot->setEnabled(0);
    ui->actionShowSelectionDialog->setEnabled(0);
    ui->actionNewGame->setEnabled(0);
    ui->compare_table->setEnabled(0);
    ui->lbl_current_slot_txt->clear();
    ui->actionImportChar->setEnabled(1);
    ui->actionExportChar->setEnabled(1);
    /*~~End Clear Menu Items~~*/
    /*~~~~~~~Set Actions By Type~~~~~~~*/
    //For first file load.Don't Bother to disable these again.
    //new game should always be exported. no header...

    //if not FF7 user is stuck in the hex editor tab.
    if (!ff7->isFF7(s) && !ff7->region(s).isEmpty()) {
        if (ui->comboHexEditor->currentIndex() != 0)
            ui->comboHexEditor->setCurrentIndex(0);
        ui->tabWidget->setCurrentIndex(8);
        for (int i = 0; i < 8; i++)
            ui->tabWidget->setTabEnabled(i, false);
        ui->tabWidget->setTabEnabled(9, false);
    } else {
        for (int i = 0; i < 9; i++)
            ui->tabWidget->setTabEnabled(i, true);
        ui->tabWidget->setTabEnabled(9, BCSettings::value(SETTINGS::ENABLETEST).toBool());
    }

    if (!ff7->fileName().isEmpty()) {
        ui->actionSaveFileAs->setEnabled(1);
        ui->actionReload->setEnabled(1);
    }

    ui->actionImportChar->setEnabled(1);
    ui->actionSave->setEnabled(1);

    //we haven't loaded a file yet.
    if (!_init) {
        ui->actionNewGamePlus->setEnabled(1);
        ui->actionImportSlotFromFile->setEnabled(1);
        ui->actionCopySlot->setEnabled(1);
        ui->actionPasteSlot->setEnabled(ff7->isBufferSlotPopulated());
        ui->actionNewGame->setEnabled(1);
    }

    if ( FF7SaveInfo::slotCount(ff7->format()) > 1) { //more then one slot, or unknown Type
        ui->actionNextSlot->setEnabled(s != 14);
        ui->actionPreviousSlot->setEnabled(s != 0);
        ui->actionShowSelectionDialog->setEnabled(1);
        ui->actionClearSlot->setEnabled(1);
        ui->actionNewGame->setEnabled(1);
        ui->compare_table->setEnabled(1);
        ui->lbl_current_slot_txt->setText(tr("Current Slot:%1").arg(QString::number(s + 1), 2, QChar('0')));
    }
    /*~~~End Set Actions By Type~~~*/
    /*~~Set Detected Region ~~*/
    if (ff7->region(s).contains(QStringLiteral("94163")))
        ui->actionRegionUSA->setChecked(true);
    else if (ff7->region(s).contains(QStringLiteral("00867")))
        ui->actionRegionPALGeneric->setChecked(true);
    else if (ff7->region(s).contains(QStringLiteral("00868")))
        ui->actionRegionPALFrench->setChecked(true);
    else if (ff7->region(s).contains(QStringLiteral("00869")))
        ui->actionRegionPALGerman->setChecked(true);
    else if (ff7->region(s).contains(QStringLiteral("00900")))
        ui->actionRegionPALSpanish->setChecked(true);
    else if (ff7->region(s).contains(QStringLiteral("00700")))
        ui->actionRegionJPN->setChecked(true);
    else if (ff7->region(s).contains(QStringLiteral("01057")))
        ui->actionRegionJPNInternational->setChecked(true);
    else if (!ff7->region(s).isEmpty()) {
        //not FF7 unset some menu options.
        ui->actionNewGamePlus->setEnabled(0);
        ui->actionCopySlot->setEnabled(0);
        ui->actionExportChar->setEnabled(0);
        ui->actionImportChar->setEnabled(0);
    }
    load = false;
}

void BlackChocobo::fileModified(bool changed)
{
    if (changed)
        setOpenFileText(ff7->fileName().append(QStringLiteral("*")));
    else
        setOpenFileText(ff7->fileName());
}
/*~~~~~~~~~End Set Menu~~~~~~~~~~~*/

void BlackChocobo::set_ntsc_time(void)
{
    if (BCDialog::fixTimeDialog(this, ff7->isPAL(s)) == QMessageBox::Yes) {
        ff7->setTime(s, quint32(ff7->time(s) * 1.2));
        load = true;
        ui->sbTimeHour->setValue(ff7->time(s) / 3600);
        ui->sbTimeMin->setValue(ff7->time(s) / 60 % 60);
        ui->sbTimeSec->setValue(int(ff7->time(s)) - ((ui->sbTimeHour->value() * 3600) + ui->sbTimeMin->value() * 60));
        load = false;
    }
}

void BlackChocobo::set_pal_time(void)
{
    if (BCDialog::fixTimeDialog(this, ff7->isPAL(s)) == QMessageBox::Yes) {
        ff7->setTime(s, quint32(ff7->time(s) / 1.2));
        load = true;
        ui->sbTimeHour->setValue(ff7->time(s) / 3600);
        ui->sbTimeMin->setValue(ff7->time(s) / 60 % 60);
        ui->sbTimeSec->setValue(int(ff7->time(s)) - ((ui->sbTimeHour->value() * 3600) + ui->sbTimeMin->value() * 60));
        load = false;
    }
}

void BlackChocobo::materiaupdate(void)
{
    load = true;
    int j = std::max(0, ui->tblMateria->currentRow());
    ui->tblMateria->reset();
    ui->tblMateria->clearContents();
    ui->tblMateria->setColumnWidth(0, int(ui->tblMateria->width()*.65));
    ui->tblMateria->setColumnWidth(1, int(ui->tblMateria->width()*.25));
    ui->tblMateria->setRowCount(200);

    for (int mat = 0; mat < 200; mat++) { // partys materias
        QTableWidgetItem *newItem;
        ui->tblMateria->setRowHeight(mat, fontMetrics().height() + 9);
        qint32 current_ap = ff7->partyMateriaAp(s, mat);
        quint8 current_id = ff7->partyMateriaId(s, mat);
        QString ap;

        if (current_id <= 0x5A) {
            newItem = new QTableWidgetItem(FF7Materia::icon(current_id), FF7Materia::name(current_id), 0);
            ui->tblMateria->setItem(mat, 0, newItem);
        }

        if (current_id == FF7Materia::EnemySkill) {
            if (current_ap == FF7Materia::MaxMateriaAp) {
                newItem = new QTableWidgetItem(tr("Master"));
                ui->tblMateria->setItem(mat, 1, newItem);
            } else {
                newItem = new QTableWidgetItem(QString(), 0);
                ui->tblMateria->setItem(mat, 1, newItem);
            }
        }

        else if (current_id == FF7Materia::MasterCommand || current_id == FF7Materia::MasterMagic || current_id == FF7Materia::MasterSummon || current_id == FF7Materia::Underwater) {
            newItem = new QTableWidgetItem(QString(), 0);
            ui->tblMateria->setItem(mat, 1, newItem);
        } else if (current_id != FF7Materia::EmptyId) {
            if (current_ap == FF7Materia::MaxMateriaAp) {
                newItem = new QTableWidgetItem(tr("Master"));
                ui->tblMateria->setItem(mat, 1, newItem);
            } else {
                newItem = new QTableWidgetItem(ap.setNum(current_ap));
                ui->tblMateria->setItem(mat, 1, newItem);
            }
        } else {
            //We need to clear invalid to prevent data issues. to keep file changes correct we back up our change vars and replace later.
            bool fileTemp = ff7->isFileModified();
            ff7->setPartyMateria(s, mat, FF7Materia::EmptyId, FF7Materia::MaxMateriaAp); //invalid insure its clear.
            newItem = new QTableWidgetItem(tr("===Empty Slot==="), 0);
            ui->tblMateria->setItem(mat, 0, newItem);
            newItem = new QTableWidgetItem(QString(), 0);
            ui->tblMateria->setItem(mat, 1, newItem);
            ff7->setFileModified(fileTemp, s);
        }
    }
    if (ff7->partyMateriaId(s, j) == FF7Materia::EnemySkill)
        mat_spacer->changeSize(0, 0, QSizePolicy::Fixed, QSizePolicy::Fixed);
    else
        mat_spacer->changeSize(0, 0, QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
    materia_editor->setMateria(ff7->partyMateriaId(s, j), ff7->partyMateriaAp(s, j));
    ui->tblMateria->setCurrentCell(j, 1); //so that right side is set correctly.
    load = false;
}

void BlackChocobo::materia_ap_changed(qint32 ap)
{
    if (load)
        return;
    ff7->setPartyMateria(s, ui->tblMateria->currentRow(), ff7->partyMateriaId(s, ui->tblMateria->currentRow()), ap);
    materiaupdate();
}

void BlackChocobo::materia_id_changed(qint8 id)
{
    if (load)
        return;
    ff7->setPartyMateria(s, ui->tblMateria->currentRow(), quint8(id), ff7->partyMateriaAp(s, ui->tblMateria->currentRow()));
    materiaupdate();
}

void BlackChocobo::CheckGame()
{
    if ((!ff7->isFF7(s) && !ff7->region(s).isEmpty())
            || ((!ff7->isFF7(s)) && !FF7SaveInfo::isTypePC(ff7->format()) && (ff7->psx_block_type(s) != char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_EMPTY)))) {
        // NOT FF7
        errbox error(this, ff7, s);
        if (FF7SaveInfo::slotCount(ff7->format()) == 1)
            error.setSingleSlot(true);
        switch (error.exec()) {
        case 0://View Anyway..
            setmenu();
            hexTabUpdate(0);
            break;
        case 1://Previous Clicked
            s--;
            CheckGame();
            break;

        case 2://Next Clicked
            s++;
            CheckGame();
            break;

        case 3://exported Clicked
            QMap<QString, FF7SaveInfo::FORMAT> typeMap;
            typeMap[FF7SaveInfo::typeFilter(FF7SaveInfo::FORMAT::PSX)] = FF7SaveInfo::FORMAT::PSX;
            typeMap[FF7SaveInfo::typeFilter(FF7SaveInfo::FORMAT::PS3)] = FF7SaveInfo::FORMAT::PS3;
            typeMap[FF7SaveInfo::typeFilter(FF7SaveInfo::FORMAT::PGE)] = FF7SaveInfo::FORMAT::PGE;
            typeMap[FF7SaveInfo::typeFilter(FF7SaveInfo::FORMAT::PDA)] = FF7SaveInfo::FORMAT::PDA;
            QString selectedType = typeMap.key(FF7SaveInfo::FORMAT::PSX);
            const QStringList typeKeys = typeMap.keys();

            QString fileName = BCDialog::getSaveFileName(this,
                                                         ff7->region(s),
                                                         tr("Select A File to Save As"),
                                                         QStringLiteral("%1/%2").arg(QDir::homePath(),ff7->region(s)),
                                                         typeKeys.join(QStringLiteral(";;")),
                                                         &selectedType);

            if (fileName.isEmpty())
                return;
            FF7SaveInfo::FORMAT newType = typeMap[selectedType];

            if (ff7->exportFile(fileName, newType, s))
                ui->statusBar->showMessage(QString(tr("Exported Slot:%2 from %1 -> %3")).arg(ff7->fileName(), QString::number(s + 1), fileName), 2000);
            else 
                ui->statusBar->showMessage(tr("Export Failed"));
            break;
        }
    } else {
        guirefresh();
    }
}

void BlackChocobo::othersUpdate()
{
    load = true;

    ui->cbRubyDead->setChecked(ff7->killedRubyWeapon(s));
    ui->cbEmeraldDead->setChecked(ff7->killedEmeraldWeapon(s));

    ui->cbPandorasBox->setChecked(ff7->seenPandorasBox(s));
    ui->cbSubGameWon->setChecked(ff7->subMiniGameVictory(s));
    ui->sbCondorWins->setValue(ff7->condorWins(s));
    ui->sbCondorLosses->setValue(ff7->condorLosses(s));
    ui->sbCondorFunds->setValue(ff7->condorFunds(s));

    ui->sbCoster1->setValue(ff7->speedScore(s, 1));
    ui->sbCoster2->setValue(ff7->speedScore(s, 2));
    ui->sbCoster3->setValue(ff7->speedScore(s, 3));

    for (int i = 0; i < 9; i++) //Allowed in Phs
            phsList->setChecked(i, PhsListWidget::PHSALLOWED, !ff7->phsAllowed(s, i));

    for (int i = 0; i < 9; i++) //Visible
            phsList->setChecked(i, PhsListWidget::PHSVISIBLE, ff7->phsVisible(s, i));

    for (int i = 0; i < 10; i++) //visible_menu
            menuList->setChecked(i, MenuListWidget::MENUVISIBLE, ff7->menuVisible(s, i));

    for (int i = 0; i < 10; i++) //menu_locked
            menuList->setChecked(i, MenuListWidget::MENULOCKED, ff7->menuLocked(s, i));

    ui->sbSteps->setValue(ff7->steps(s));

    ui->sbLoveBarret->setValue(ff7->love(s, false, FF7Save::LOVE_BARRET));
    ui->sbLoveTifa->setValue(ff7->love(s, false, FF7Save::LOVE_TIFA));
    ui->sbLoveAeris->setValue(ff7->love(s, false, FF7Save::LOVE_AERIS));
    ui->sbLoveYuffie->setValue(ff7->love(s, false, FF7Save::LOVE_YUFFIE));

    ui->sbTimeHour->setValue(ff7->time(s) / 3600);
    ui->sbTimeMin->setValue(ff7->time(s) / 60 % 60);
    ui->sbTimeSec->setValue(int(ff7->time(s)) - ((ui->sbTimeHour->value() * 3600) + ui->sbTimeMin->value() * 60));

    ui->sbTimerTimeHour->setValue(ff7->countdownTimer(s) / 3600);
    ui->sbTimerTimeMin->setValue(ff7->countdownTimer(s) / 60 % 60);
    ui->sbTimerTimeSec->setValue(int(ff7->countdownTimer(s)) - ((ui->sbTimerTimeHour->value() * 3600) + ui->sbTimerTimeMin->value() * 60));
    ui->cbYuffieForest->setChecked(ff7->canFightNinjaInForest(s));
    ui->cbRegYuffie->setChecked(ff7->yuffieUnlocked(s));
    ui->cbRegVinny->setChecked(ff7->vincentUnlocked(s));

    /*~~~~~Stolen Materia~~~~~~~*/
    ui->tblMateriaStolen->reset();
    ui->tblMateriaStolen->clearContents();
    ui->tblMateriaStolen->setColumnWidth(0, int(ui->tblMateriaStolen->width()*.65));
    ui->tblMateriaStolen->setColumnWidth(1, int(ui->tblMateriaStolen->width()*.25));
    ui->tblMateriaStolen->setRowCount(48);
    updateStolenMateria();

    //SnowBoard Mini Game Data.
    ui->sbSnowBegMin->setValue(ff7->snowboardTime(s, 0).mid(0, 2).toInt());
    ui->sbSnowBegSec->setValue(ff7->snowboardTime(s, 0).mid(2, 2).toInt());
    ui->sbSnowBegMsec->setValue(ff7->snowboardTime(s, 0).mid(4, 3).toInt());
    ui->sbSnowBegScore->setValue(ff7->snowboardScore(s, 0));

    ui->sbSnowExpMin->setValue(ff7->snowboardTime(s, 1).mid(0, 2).toInt());
    ui->sbSnowExpSec->setValue(ff7->snowboardTime(s, 1).mid(2, 2).toInt());
    ui->sbSnowExpMsec->setValue(ff7->snowboardTime(s, 1).mid(4, 3).toInt());
    ui->sbSnowExpScore->setValue(ff7->snowboardScore(s, 1));

    ui->sbSnowCrazyMin->setValue(ff7->snowboardTime(s, 2).mid(0, 2).toInt());
    ui->sbSnowCrazySec->setValue(ff7->snowboardTime(s, 2).mid(2, 2).toInt());
    ui->sbSnowCrazyMsec->setValue(ff7->snowboardTime(s, 2).mid(4, 3).toInt());
    ui->sbSnowCrazyScore->setValue(ff7->snowboardScore(s, 2));

    ui->sbBikeHighScore->setValue(ff7->bikeHighScore(s));
    ui->sbBattleSWins->setValue(ff7->specialBattleWins(s));
    ui->sbBattlePoints->setValue(ff7->battlePoints(s));
    ui->cbFlashbackPiano->setChecked(ff7->playedPianoOnFlashback(s));
    load = false;
}

void BlackChocobo::updateStolenMateria()
{
    for (int mat = 0; mat < 48; mat++) { //materias stolen by yuffie
        quint8 current_id = ff7->stolenMateriaId(s, mat);
        QTableWidgetItem *newItem;
        if (current_id == FF7Materia::EmptyId) {
            newItem = new QTableWidgetItem(tr("===Empty Slot==="), 0);
            ui->tblMateriaStolen->setItem(mat, 0, newItem);
        } else {
            newItem = new QTableWidgetItem(FF7Materia::icon(current_id), FF7Materia::name(current_id), 0);
            ui->tblMateriaStolen->setItem(mat, 0, newItem);
            qint32 current_ap = ff7->stolenMateriaAp(s, mat);
            if ( current_ap >= FF7Materia::apForLevel(current_id, FF7Materia::levels(current_id) - 1))
                newItem = new QTableWidgetItem(tr("Master"));
            else {
                if (current_id == FF7Materia::EnemySkill)
                    newItem = new QTableWidgetItem(QStringLiteral("---"));
                else
                   newItem = new QTableWidgetItem(QString::number(current_ap));
            }
            ui->tblMateriaStolen->setItem(mat, 1, newItem);
        }
        ui->tblMateriaStolen->setRowHeight(mat, fontMetrics().height() + 9);
    }
}

void BlackChocobo::update_hexEditor_PSXInfo(void)
{
    load = true;

    disconnect(saveIcon, nullptr, nullptr, nullptr);
    saveIcon->setAll(ff7->slotIcon(s));
    connect(saveIcon, &SaveIcon::nextIcon, ui->lblPsxIcon, &QLabel::setPixmap);

    ui->comboSlotNumber->setCurrentIndex(ff7->region(s).mid(ff7->region(s).lastIndexOf(QStringLiteral("S")) + 1, 2).toInt() - 1);
    if(ff7->region(s).contains(QStringLiteral("BASCUS-94163")))
        ui->comboSlotRegion->setCurrentIndex(0);
    else if(ff7->region(s).contains(QStringLiteral("BESCES-00867")))
        ui->comboSlotRegion->setCurrentIndex(1);
    else if(ff7->region(s).contains(QStringLiteral("BESCES-00868")))
        ui->comboSlotRegion->setCurrentIndex(2);
    else if(ff7->region(s).contains(QStringLiteral("BESCES-00869")))
        ui->comboSlotRegion->setCurrentIndex(3);
    else if(ff7->region(s).contains(QStringLiteral("BESCES-00900")))
        ui->comboSlotRegion->setCurrentIndex(4);
    else if(ff7->region(s).contains(QStringLiteral("BISLPS-00700")))
        ui->comboSlotRegion->setCurrentIndex(5);
    else if(ff7->region(s).contains(QStringLiteral("BISLPS-01057")))
        ui->comboSlotRegion->setCurrentIndex(6);
    else
        ui->comboSlotRegion->setCurrentIndex(-1);

    ui->lblRegionString->setText(ff7->region(s));
    QString SlotSizeText;

    if (ff7->psx_block_type(s) != char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_MIDLINK)
      && ff7->psx_block_type(s) != char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_ENDLINK)
      && ff7->psx_block_type(s) != char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_DELETED_MIDLINK)
      && ff7->psx_block_type(s) != char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_DELETED_ENDLINK))
        ui->linePsxDesc->setText(ff7->psxDesc(s));

    if (ff7->psx_block_type(s) == char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_MIDLINK)
      || ff7->psx_block_type(s) == char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_DELETED_MIDLINK))
        SlotSizeText.append(tr("\n Mid-Linked Block "));

    else if (ff7->psx_block_type(s) == char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_ENDLINK)
      || ff7->psx_block_type(s) == char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_DELETED_ENDLINK))
        SlotSizeText.append(tr("\n End Of Linked Data"));

    if (ff7->psx_block_type(s) == char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_DELETED)
      || ff7->psx_block_type(s) == char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_DELETED_MIDLINK)
      || ff7->psx_block_type(s) == char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_DELETED_ENDLINK))
        SlotSizeText.append(tr("(Deleted)"));

    if (ff7->psx_block_type(s) != char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_MIDLINK)
      && ff7->psx_block_type(s) != char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_ENDLINK)
      && ff7->psx_block_type(s) != char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_DELETED_MIDLINK)
      && ff7->psx_block_type(s) != char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_DELETED_ENDLINK))
        SlotSizeText.append(tr("Game Uses %n Save Block(s)", nullptr, ff7->psx_block_size(s)));

    if (ff7->psx_block_size(s) != 1) {
        if (ff7->format() != FF7SaveInfo::FORMAT::PSX
                && ff7->format() != FF7SaveInfo::FORMAT::PS3
                && ff7->psx_block_next(s) != 0xFF) {
            SlotSizeText.append(tr("\n  Next Data Chunk @ Slot:%1").arg(QString::number(ff7->psx_block_next(s) + 1)));
        }
    }
    ui->lblSlotSize->setText(SlotSizeText);
    load = false;
}

void BlackChocobo::tabWidget_currentChanged(int index)
{
    //Update the shown tab.
    load = true;
    hexCursorPos = hexEditor->cursorPosition();
    switch (index) {
    case 0://Party Tab
        partyTab->setPartyMembers(ff7->party(s, 0), ff7->party(s, 1), ff7->party(s, 2));
        set_char_buttons();
        partyTab->pressCharacterButton(curchar);
        break;

    case 1://Item Tab
        ff7ItemModel->resetItems(ff7->items(s));
        itemTab->setGil(ff7->gil(s));
        itemTab->setGp(ff7->gp(s));
        itemTab->setBattles(ff7->battles(s));
        itemTab->setRuns(ff7->runs(s));
        itemTab->setMysteryPanties(ff7->keyItem(s, FF7Save::MYSTERYPANTIES));
        itemTab->setDaughterLetter(ff7->keyItem(s, FF7Save::LETTERTOADAUGHTER));
        itemTab->setWifeLetter(ff7->keyItem(s, FF7Save::LETTERTOAWIFE));
        break;

    case 2://Materia
        materiaupdate();
        break;

    case 3://Chocobo Tab
        chocoboManager->setData(ff7->chocobos(s), ff7->chocobosNames(s), ff7->chocobosStaminas(s), ff7->chocoboCantMates(s), ff7->stablesOwned(s), ff7->stablesOccupied(s), ff7->stableMask(s), ff7->chocoboPens(s), ff7->chocoboRatings(s));
        break;

    case 4://Location Tab
        locationToolBox_currentChanged(ui->locationToolBox->currentIndex());
        break;

    case 5://Game Progress Tab
        progress_update();
        break;

    case 6:// Other Tab
        othersUpdate();
        break;

    case 7:// Game Options Tab
        optionsWidget->setDialogColors(ff7->dialogColorUL(s), ff7->dialogColorUR(s), ff7->dialogColorLL(s), ff7->dialogColorLR(s));
        optionsWidget->setFieldHelp(ff7->fieldHelp(s));
        optionsWidget->setBattleHelp(ff7->battleHelp(s));
        optionsWidget->setBattleTargets(ff7->battleTargets(s));
        optionsWidget->setSoundMode(ff7->soundMode(s));
        optionsWidget->setControllerMode(ff7->controlMode(s));
        optionsWidget->setCursor(ff7->cursorMode(s));
        optionsWidget->setCamera(ff7->cameraMode(s));
        optionsWidget->setAtbMode(ff7->atbMode(s));
        optionsWidget->setMagicOrder(ff7->magicOrder(s));
        optionsWidget->setBattleSpeed(ff7->battleSpeed(s));
        optionsWidget->setBattleMessageSpeed(ff7->battleMessageSpeed(s));
        optionsWidget->setFieldMessageSpeed(ff7->messageSpeed(s));
        for (int i = 0; i < 16; i++) {
            optionsWidget->setInput(i, ff7->controllerMapping(s, i));
        }
        if ((!FF7SaveInfo::isTypePC(ff7->format()) && ff7->format() != FF7SaveInfo::FORMAT::UNKNOWN)
                || BCSettings::value(SETTINGS::ALWAYSSHOWCONTROLLERMAP).toBool()) {
            setControllerMappingVisible(true);
            if (optionsWidget->verticalScrollBar()->isVisible()) {
                optionsWidget->setFixedWidth(optionsWidget->width() - 1);
            }
        } else {
            setControllerMappingVisible(false);
        }
        break;

    case 8://HexEditor Tab
        hexTabUpdate(ui->comboHexEditor->currentIndex());
        break;

    case 9: //Test Data Tab
        testDataTabWidget_currentChanged(ui->testDataTabWidget->currentIndex());
        break;
    }
    load = false;
}

void BlackChocobo::hexTabUpdate(int viewMode)
{
    ui->psxExtras->setVisible(false);
    ui->hexShowsGroup->setVisible(false);
    ui->lblSlotSize->setVisible(false);
    ui->psxff7Extras->setVisible(false);
    disconnect(hexEditor, &QHexEdit::dataChanged, this, &BlackChocobo::hexEditorChanged);
    if (FF7SaveInfo::isTypePC(ff7->format()) || ff7->format() == FF7SaveInfo::FORMAT::UNKNOWN) {
        hexEditor->setData(ff7->slotFF7Data(s));
    } else {
        ui->psxExtras->setVisible(true);
        update_hexEditor_PSXInfo();
        if (ff7->isFF7(s)) {
            ui->hexShowsGroup->setVisible(true);
            ui->psxff7Extras->setVisible(true);
            switch (viewMode) {
            case 0:
                hexEditor->setData(ff7->slotPsxRawData(s));
                break;
            case 1:
                hexEditor->setData(ff7->slotFF7Data(s));
                break;
            }
        } else {
            ui->lblSlotSize->setVisible(true);
            hexEditor->setData(ff7->slotPsxRawData(s));
        }
    }
    hexEditor->setCursorPosition(hexCursorPos);
    connect(hexEditor, &QHexEdit::dataChanged, this, &BlackChocobo::hexEditorChanged);
}

void BlackChocobo::setControllerMappingVisible(bool Visible)
{
    optionsWidget->setControllerMappingVisible(Visible);
}

void BlackChocobo::guirefresh()
{
    load = true;
    /*~~~~Check for SG type and ff7~~~~*/
    if ((!ff7->isFF7(s) && !ff7->region(s).isEmpty()) ||
            ((!ff7->isFF7(s)) && !FF7SaveInfo::isTypePC(ff7->format())
             && (ff7->psx_block_type(s) != char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_EMPTY)) && (ff7->psx_block_type(s) != '\x00'))) {
        CheckGame();//Not FF7! Handled By CheckGame()
    } else {
        //IS FF7 Slot
        if (FF7SaveInfo::isTypePC(ff7->format()) || ff7->format() == FF7SaveInfo::FORMAT::UNKNOWN) {
            if (ui->comboHexEditor->currentIndex() != 1)
                ui->comboHexEditor->setCurrentIndex(1);
        }
        //QByteArray text;
        if (ff7->region(s).isEmpty()
                && (ff7->format() == FF7SaveInfo::FORMAT::VMC || ff7->format() == FF7SaveInfo::FORMAT::VGS || ff7->format() == FF7SaveInfo::FORMAT::DEX || ff7->format() == FF7SaveInfo::FORMAT::PSP)
                && ff7->psx_block_type(s) == char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_EMPTY)) {
            //if empty region string and a virtual memcard format and dir frame says empty.
            ff7->clearSlot(s); //fileModified(false);//checking only
        }
        locationViewer->setRegion(ff7->region(s));
        setmenu();
        tabWidget_currentChanged(ui->tabWidget->currentIndex());
    }
    load = false;
}

void BlackChocobo::set_char_buttons()
{
    QList<int> ids;
         for (int i =0; i < 9; i++)
             ids.append(ff7->charID(s,i));
         partyTab->setButtonImagesToIds(ids);
}

void BlackChocobo::progress_update()
{
    load = true;
    ui->sbCurdisc->setValue(ff7->disc(s));
    ui->sbMprogress->setValue(ff7->mainProgress(s));

    ui->sbTurkschurch->setValue(ff7->churchProgress(s));
    ui->sbDonprog->setValue(ff7->donProgress(s));
    ui->comboS7Slums->setCurrentIndex(0);

    ui->cbBm1_1->setChecked(ff7->bmProgress1(s, 0));
    ui->cbBm1_2->setChecked(ff7->bmProgress1(s, 1));
    ui->cbBm1_3->setChecked(ff7->bmProgress1(s, 2));
    ui->cbBm1_4->setChecked(ff7->bmProgress1(s, 3));
    ui->cbBm1_5->setChecked(ff7->bmProgress1(s, 4));
    ui->cbBm1_6->setChecked(ff7->bmProgress1(s, 5));
    ui->cbBm1_7->setChecked(ff7->bmProgress1(s, 6));
    ui->cbBm1_8->setChecked(ff7->bmProgress1(s, 7));
    ui->cbBm2_1->setChecked(ff7->bmProgress2(s, 0));
    ui->cbBm2_2->setChecked(ff7->bmProgress2(s, 1));
    ui->cbBm2_3->setChecked(ff7->bmProgress2(s, 2));
    ui->cbBm2_4->setChecked(ff7->bmProgress2(s, 3));
    ui->cbBm2_5->setChecked(ff7->bmProgress2(s, 4));
    ui->cbBm2_6->setChecked(ff7->bmProgress2(s, 5));
    ui->cbBm2_7->setChecked(ff7->bmProgress2(s, 6));
    ui->cbBm2_8->setChecked(ff7->bmProgress2(s, 7));
    ui->cbBm3_1->setChecked(ff7->bmProgress3(s, 0));
    ui->cbBm3_2->setChecked(ff7->bmProgress3(s, 1));
    ui->cbBm3_3->setChecked(ff7->bmProgress3(s, 2));
    ui->cbBm3_4->setChecked(ff7->bmProgress3(s, 3));
    ui->cbBm3_5->setChecked(ff7->bmProgress3(s, 4));
    ui->cbBm3_6->setChecked(ff7->bmProgress3(s, 5));
    ui->cbBm3_7->setChecked(ff7->bmProgress3(s, 6));
    ui->cbBm3_8->setChecked(ff7->bmProgress3(s, 7));
    ui->cbMidgartrain_1->setChecked(ff7->midgarTrainFlags(s, 0));
    ui->cbMidgartrain_2->setChecked(ff7->midgarTrainFlags(s, 1));
    ui->cbMidgartrain_3->setChecked(ff7->midgarTrainFlags(s, 2));
    ui->cbMidgartrain_4->setChecked(ff7->midgarTrainFlags(s, 3));
    ui->cbMidgartrain_5->setChecked(ff7->midgarTrainFlags(s, 4));
    ui->cbMidgartrain_6->setChecked(ff7->midgarTrainFlags(s, 5));
    ui->cbMidgartrain_7->setChecked(ff7->midgarTrainFlags(s, 6));
    ui->cbMidgartrain_8->setChecked(ff7->midgarTrainFlags(s, 7));
    ui->cbBombingInt->setChecked(ff7->startBombingMission(s));

    ui->cbS7pl_1->setChecked((ff7->unknown(s, 26).at(0) & (1 << 0)));
    ui->cbS7pl_2->setChecked((ff7->unknown(s, 26).at(0) & (1 << 1)));
    ui->cbS7pl_3->setChecked((ff7->unknown(s, 26).at(0) & (1 << 2)));
    ui->cbS7pl_4->setChecked((ff7->unknown(s, 26).at(0) & (1 << 3)));
    ui->cbS7pl_5->setChecked((ff7->unknown(s, 26).at(0) & (1 << 4)));
    ui->cbS7pl_6->setChecked((ff7->unknown(s, 26).at(0) & (1 << 5)));
    ui->cbS7pl_7->setChecked((ff7->unknown(s, 26).at(0) & (1 << 6)));
    ui->cbS7pl_8->setChecked((ff7->unknown(s, 26).at(0) & (1 << 7)));

    ui->cbS7ts_1->setChecked((ff7->unknown(s, 26).at(8) & (1 << 0)));
    ui->cbS7ts_2->setChecked((ff7->unknown(s, 26).at(8) & (1 << 1)));
    ui->cbS7ts_3->setChecked((ff7->unknown(s, 26).at(8) & (1 << 2)));
    ui->cbS7ts_4->setChecked((ff7->unknown(s, 26).at(8) & (1 << 3)));
    ui->cbS7ts_5->setChecked((ff7->unknown(s, 26).at(8) & (1 << 4)));
    ui->cbS7ts_6->setChecked((ff7->unknown(s, 26).at(8) & (1 << 5)));
    ui->cbS7ts_7->setChecked((ff7->unknown(s, 26).at(8) & (1 << 6)));
    ui->cbS7ts_8->setChecked((ff7->unknown(s, 26).at(8) & (1 << 7)));
    
    if (ff7->unknown(s, 26).mid(0, 6) == "\x00\x00\x00\x00\x00\x00")
        ui->comboS7Slums->setCurrentIndex(1);
    else if (ff7->unknown(s, 26).mid(0, 6) == "\xFF\x03\x04\x0F\x1F\x6F" || ff7->unknown(s, 26).mid(0, 6) == "\xBF\x51\x05\x17\x5D\xEF")
        ui->comboS7Slums->setCurrentIndex(2);
    else if (static_cast<unsigned char>(ff7->unknown(s, 26).at(2)) == 0x13)
        ui->comboS7Slums->setCurrentIndex(3);
    else
        ui->comboS7Slums->setCurrentIndex(0);
    
    load = false;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Party TAB~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void BlackChocobo::charButtonClicked(int charSlot)
{
    curchar = charSlot;
    partyTab->setCharacter(ff7->character(s, curchar), ff7->charName(s, curchar));
}

void BlackChocobo::partyMembersChanged(int partySlot, int id)
{
    if (load)
        return;

    if (partySlot > 2 || partySlot < 0)
        return;

    if(id == ff7->party(s, partySlot) || id < 0)
        return;

    ff7->setParty(s, partySlot, id);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~Chocobo Tab~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void BlackChocobo::cm_stablesOwnedChanged(qint8 owned)
{
    if (load)
        return;
    ff7->setStablesOwned(s, owned);
}

void BlackChocobo::cm_stableMaskChanged(qint8 mask)
{
    if (load)
        return;
    ff7->setStableMask(s, mask);
}

void BlackChocobo::cm_stablesOccupiedChanged(qint8 occupied)
{
    if (load)
        return;
    ff7->setStablesOccupied(s, occupied);
}
//set data for stables inside

void BlackChocobo::cm_nameChanged(int stable, QString text)
{
    if (load)
        return;
    ff7->setChocoName(s, stable, text);
}

void BlackChocobo::cm_staminaChanged(int stable, quint16 value)
{
    if (load)
        return;
    ff7->setChocoStamina(s, stable, value);
}

void BlackChocobo::cm_speedChanged(int stable, quint16 value)
{
    if (load)
        return;
    ff7->setChocoSpeed(s, stable, value);
}

void BlackChocobo::cm_maxspeedChanged(int stable, quint16 value)
{
    if (load)
        return;
    ff7->setChocoMaxSpeed(s, stable, value);
}

void BlackChocobo::cm_sprintChanged(int stable, quint16 value)
{
    if (load)
        return;
    ff7->setChocoSprintSpeed(s, stable, value);
}

void BlackChocobo::cm_maxsprintChanged(int stable, quint16 value)
{
    if (load)
        return;
    ff7->setChocoMaxSprintSpeed(s, stable, value);
}

void BlackChocobo::cm_sexChanged(int stable, quint8 index)
{
    if (load)
        return;
    ff7->setChocoSex(s, stable, index);
}

void BlackChocobo::cm_typeChanged(int stable, quint8 index)
{
    if (load)
        return;
    ff7->setChocoType(s, stable, index);
}

void BlackChocobo::cm_coopChanged(int stable, quint8 value)
{
    if (load)
        return;
    ff7->setChocoCoop(s, stable, value);
}

void BlackChocobo::cm_accelChanged(int stable, quint8 value)
{
    if (load)
        return;
    ff7->setChocoAccel(s, stable, value);
}

void BlackChocobo::cm_intelChanged(int stable, quint8 value)
{
    if (load)
        return;
    ff7->setChocoIntelligence(s, stable, value);
}

void BlackChocobo::cm_raceswonChanged(int stable, quint8 value)
{
    if (load)
        return;
    ff7->setChocoRaceswon(s, stable, value);
}

void BlackChocobo::cm_pcountChanged(int stable, quint8 value)
{
    if (load)
        return;
    ff7->setChocoPCount(s, stable, value);
}

void BlackChocobo::cm_personalityChanged(int stable, quint8 value)
{
    if (load)
        return;
    ff7->setChocoPersonality(s, stable, value);
}

void BlackChocobo::cm_mated_toggled(int stable, bool checked)
{
    if (load)
        return;
    ff7->setChocoCantMate(s, stable, checked);
}

void BlackChocobo::cm_ratingChanged(int stable, quint8 rating)
{
    if (load)
        return;
    ff7->setChocoboRating(s, stable, rating);
}

//set data for pens outside
void BlackChocobo::cm_pensChanged(int pen, int index)
{
    if (load)
        return;
    ff7->setChocoboPen(s, pen, index);
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~OTHERS TAB~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void BlackChocobo::sbLoveBarret_valueChanged(int value)
{
    if (load)
        return;
    ff7->setLove(s, false, FF7Save::LOVE_BARRET, quint8(value));
}

void BlackChocobo::sbLoveAeris_valueChanged(int value)
{
    if (load)
        return;
    ff7->setLove(s, false, FF7Save::LOVE_AERIS, quint8(value));
}

void BlackChocobo::sbLoveTifa_valueChanged(int value)
{
    if (load)
        return;
    ff7->setLove(s, false, FF7Save::LOVE_TIFA, quint8(value));
}

void BlackChocobo::sbLoveYuffie_valueChanged(int value)
{
    if (load)
        return;
    ff7->setLove(s, false, FF7Save::LOVE_YUFFIE, quint8(value));
}

void BlackChocobo::sbTimeHour_valueChanged(int value)
{
    if (load)
        return;
    ff7->setTime(s, quint32((value * 3600) + (ui->sbTimeMin->value() * 60) + (ui->sbTimeSec->value())));
}

void BlackChocobo::sbTimeMin_valueChanged(int value)
{
    if (load)
        return;
    ff7->setTime(s, quint32((ui->sbTimeHour->value() * 3600) + ((value * 60)) + (ui->sbTimeSec->value())));
}

void BlackChocobo::sbTimeSec_valueChanged(int value)
{
    if (load)
        return;
    ff7->setTime(s, quint32((ui->sbTimeHour->value() * 3600) + (ui->sbTimeMin->value() * 60) + (value)));
}

void BlackChocobo::sbSteps_valueChanged(int value)
{
    if (load)
        return;
    ff7->setSteps(s, value);
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Item Tab~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void BlackChocobo::gilChanged(quint32 value)
{
    if (load)
        return;
    ff7->setGil(s, value);
}

void BlackChocobo::gpChanged(int value)
{
    if (load)
        return;
    ff7->setGp(s, value);
}

void BlackChocobo::battlesChanged(int value)
{
    if (load)
        return;
    ff7->setBattles(s, value);
}

void BlackChocobo::runsChanged(int value)
{
    if (load)
        return;
    ff7->setRuns(s, value);
}

void BlackChocobo::mysteryPantiesChanged(bool checked)
{
    if (load)
        return;
    ff7->setKeyItem(s, FF7Save::MYSTERYPANTIES, checked);
}

void BlackChocobo::letterToDaughterChanged(bool checked)
{
    if (load)
        return;
    ff7->setKeyItem(s, FF7Save::LETTERTOADAUGHTER, checked);
}

void BlackChocobo::letterToWifeChanged(bool checked)
{
    if (load)
        return;
    ff7->setKeyItem(s, FF7Save::LETTERTOAWIFE, checked);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MATERIA TAB~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void BlackChocobo::tblMateria_currentCellChanged(int row)
{
    if (load)
        return;
    load = true;
    materia_editor->setMateria(ff7->partyMateriaId(s, row), ff7->partyMateriaAp(s, row));
    load = false;
}

void BlackChocobo::btnAddAllMateria_clicked()
{
    //place one of each at lowest possible point
    for (int i = 117; i < 142; i++) {
        //Starting With Magic Materia
        if (i < 132)
            ff7->setPartyMateria(s, i, quint8(i - 68), FF7Materia::MaxMateriaAp);
        else if (i < 136)
            ff7->setPartyMateria(s, (i - 1), quint8(i - 68), FF7Materia::MaxMateriaAp);
        else if (i < 142)
            ff7->setPartyMateria(s, (i - 3), quint8(i - 68), FF7Materia::MaxMateriaAp);
    }
    // Then Support
    for (int i = 139; i < 152; i++)
        ff7->setPartyMateria(s, i, quint8(i - 116), FF7Materia::MaxMateriaAp);

    for (int i = 152; i < 166; i++) {
        //Then Command
        if (i < 154)
            ff7->setPartyMateria(s, i, quint8(i - 138), FF7Materia::MaxMateriaAp);
        else if (i < 157)
            ff7->setPartyMateria(s, i, quint8(i - 135), FF7Materia::MaxMateriaAp);
        else if (i < 159)
            ff7->setPartyMateria(s, i, quint8(i - 121), FF7Materia::MaxMateriaAp);
        else if (i < 165)
            ff7->setPartyMateria(s, i, quint8(i - 120), FF7Materia::MaxMateriaAp);
        else
            ff7->setPartyMateria(s, i, 0x30, FF7Materia::MaxMateriaAp);
    }
    for (int i = 166; i < 183; i++) {
        //And Independent
        if (i < 180)
            ff7->setPartyMateria(s, i,  quint8(i - 166), FF7Materia::MaxMateriaAp);
        else
            ff7->setPartyMateria(s, i,  quint8(i - 164), FF7Materia::MaxMateriaAp);
    }
    //Finish With Summons
    for (int i = 183; i < 200; i++)
        ff7->setPartyMateria(s, i,  quint8(i - 109), FF7Materia::MaxMateriaAp);
    materiaupdate();
    statusBar()->showMessage(tr("All Materia Added!"), 750);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~SAVE LOCATION TAB~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void BlackChocobo::locationSelectionChanged(QString fieldName)
{
    if (load)
        return;
    ff7->setMapId(s, FF7Location::mapID(fieldName).toUShort());
    ff7->setLocationId(s, FF7Location::locationID(fieldName).toUShort());
    ff7->setLocationX(s, FF7Location::x(fieldName).toShort());
    ff7->setLocationY(s, FF7Location::y(fieldName).toShort());
    ff7->setLocationT(s, FF7Location::t(fieldName).toUShort());
    ff7->setLocationD(s, quint8(FF7Location::d(fieldName).toInt()));
    ff7->setLocation(s, FF7Location::locationString(fieldName));
    statusBar()->showMessage(tr("Set Save Location: %1").arg(fieldName), 750);
}

void BlackChocobo::map_id_valueChanged(int value)
{
    if (load)
        return;
    ff7->setMapId(s, quint16(value));
}

void BlackChocobo::loc_id_valueChanged(int value)
{
    if (load)
        return;
    ff7->setLocationId(s, quint16(value));
}

void BlackChocobo::coord_x_valueChanged(int value)
{
    if (load)
        return;
    ff7->setLocationX(s, qint16(value));
}

void BlackChocobo::coord_y_valueChanged(int value)
{
    if (load)
        return;
    ff7->setLocationY(s, qint16(value));
}

void BlackChocobo::coord_t_valueChanged(int value)
{
    if (load)
        return;
    ff7->setLocationT(s, quint16(value));
}

void BlackChocobo::coord_d_valueChanged(int value)
{
    if (load)
        return;
    ff7->setLocationD(s, quint8(value));
}

void BlackChocobo::location_textChanged(QString text)
{
    if (load)
        return;
    ff7->setLocation(s, text);
}

/*~~~~~~~~~~~~~~~~~~~ Game Options~~~~~~~~~~~~~~~~~~*/
void BlackChocobo::setDialogColorUL(QColor color)
{
    if (load)
        return;
    ff7->setDialogColorUL(s, color);
}

void BlackChocobo::setDialogColorUR(QColor color)
{
    if (load)
        return;
    ff7->setDialogColorUR(s, color);
}

void BlackChocobo::setDialogColorLL(QColor color)
{
    if (load)
        return;
    ff7->setDialogColorLL(s, color);
}

void BlackChocobo::setDialogColorLR(QColor color)
{
    if (load)
        return;
    ff7->setDialogColorLR(s, color);
}

void BlackChocobo::setBattleSpeed(int value)
{
    if (load)
        return;
    ff7->setBattleSpeed(s, value);
}

void BlackChocobo::setBattleMessageSpeed(int value)
{
    if (load)
        return;
    ff7->setBattleMessageSpeed(s, value);
}

void BlackChocobo::setFieldMessageSpeed(int value)
{
    if (load)
        return;
    ff7->setMessageSpeed(s, value);
}

void BlackChocobo::setBattleHelp(bool checked)
{
    if (load)
        return;
    ff7->setBattleHelp(s, checked);
}

void BlackChocobo::setFieldHelp(bool checked)
{
    if (load)
        return;
    ff7->setFieldHelp(s, checked);
}
void BlackChocobo::setBattleTargets(bool checked)
{
    if (load)
        return;
    ff7->setBattleTargets(s, checked);
}

void BlackChocobo::setControlMode(int mode)
{
    if (load)
        return;
    ff7->setControlMode(s, mode);
}

void BlackChocobo::setSoundMode(int mode)
{
    if (load)
        return;
    ff7->setSoundMode(s, mode);
}

void BlackChocobo::setCursorMode(int mode)
{
    if (load)
        return;
    ff7->setCursorMode(s, mode);
}

void BlackChocobo::setAtbMode(int mode)
{
    if (load)
        return;
    ff7->setAtbMode(s, mode);
}

void BlackChocobo::setCameraMode(int mode)
{
    if (load)
        return;
    ff7->setCameraMode(s, mode);
}

void BlackChocobo::setMagicOrder(int order)
{
    if (load)
        return;
    ff7->setMagicOrder(s, order);
}

/*--------GAME PROGRESS-------*/
void BlackChocobo::sbCurdisc_valueChanged(int value)
{
    if (load)
        return;
    ff7->setDisc(s, value);
}

void BlackChocobo::sbMprogress_valueChanged(int value)
{
    if (load)
        return;
    ff7->setMainProgress(s, value);
}

void BlackChocobo::sbTurkschurch_valueChanged(int value)
{
    if (load)
        return;
    ff7->setChurchProgress(s, value);
}

void BlackChocobo::sbDonprog_valueChanged(int value)
{
    if (load)
        return;
    ff7->setDonProgress(s, value);
}

void BlackChocobo::cbBm1_1_toggled(bool checked)
{
    if (load)
        return;
    ff7->setBmProgress1(s, 0, checked);
}

void BlackChocobo::cbBm1_2_toggled(bool checked)
{
    if (load)
        return;
    ff7->setBmProgress1(s, 1, checked);
}

void BlackChocobo::cbBm1_3_toggled(bool checked)
{
    if (load)
        return;
    ff7->setBmProgress1(s, 2, checked);
}

void BlackChocobo::cbBm1_4_toggled(bool checked)
{
    if (load)
        return;
    ff7->setBmProgress1(s, 3, checked);
}

void BlackChocobo::cbBm1_5_toggled(bool checked)
{
    if (load)
        return;
    ff7->setBmProgress1(s, 4, checked);
}

void BlackChocobo::cbBm1_6_toggled(bool checked)
{
    if (load)
        return;
    ff7->setBmProgress1(s, 5, checked);
}

void BlackChocobo::cbBm1_7_toggled(bool checked)
{
    if (load)
        return;
    ff7->setBmProgress1(s, 6, checked);
}

void BlackChocobo::cbBm1_8_toggled(bool checked)
{
    if (load)
        return;
    ff7->setBmProgress1(s, 7, checked);
}

void BlackChocobo::cbBm2_1_toggled(bool checked)
{
    if (load)
        return;
    ff7->setBmProgress2(s, 0, checked);
}

void BlackChocobo::cbBm2_2_toggled(bool checked)
{
    if (load)
        return;
    ff7->setBmProgress2(s, 1, checked);
}

void BlackChocobo::cbBm2_3_toggled(bool checked)
{
    if (load)
        return;
    ff7->setBmProgress2(s, 2, checked);
}

void BlackChocobo::cbBm2_4_toggled(bool checked)
{
    if (load)
        return;
    ff7->setBmProgress2(s, 3, checked);
}

void BlackChocobo::cbBm2_5_toggled(bool checked)
{
    if (load)
        return;
    ff7->setBmProgress2(s, 4, checked);
}

void BlackChocobo::cbBm2_6_toggled(bool checked)
{
    if (load)
        return;
    ff7->setBmProgress2(s, 5, checked);
}

void BlackChocobo::cbBm2_7_toggled(bool checked)
{
    if (load)
        return;
    ff7->setBmProgress2(s, 6, checked);
}

void BlackChocobo::cbBm2_8_toggled(bool checked)
{
    if (load)
        return;
    ff7->setBmProgress2(s, 7, checked);
}

void BlackChocobo::cbBm3_1_toggled(bool checked)
{
    if (load)
        return;
    ff7->setBmProgress3(s, 0, checked);
}

void BlackChocobo::cbBm3_2_toggled(bool checked)
{
    if (load)
        return;
    ff7->setBmProgress3(s, 1, checked);
}

void BlackChocobo::cbBm3_3_toggled(bool checked)
{
    if (load)
        return;
    ff7->setBmProgress3(s, 2, checked);
}

void BlackChocobo::cbBm3_4_toggled(bool checked)
{
    if (load)
        return;
    ff7->setBmProgress3(s, 3, checked);
}

void BlackChocobo::cbBm3_5_toggled(bool checked)
{
    if (load)
        return;
    ff7->setBmProgress3(s, 4, checked);
}

void BlackChocobo::cbBm3_6_toggled(bool checked)
{
    if (load)
        return;
    ff7->setBmProgress3(s, 5, checked);
}

void BlackChocobo::cbBm3_7_toggled(bool checked)
{
    if (load)
        return;
    ff7->setBmProgress3(s, 6, checked);
}

void BlackChocobo::cbBm3_8_toggled(bool checked)
{
    if (load)
        return;
    ff7->setBmProgress3(s, 7, checked);
}

void BlackChocobo::cbS7pl_1_toggled(bool checked)
{
    if (load)
        return;
    QByteArray temp = ff7->unknown(s, 26); char t = temp.at(0);
    if (checked)
        t |= (1 << 0);
    else
        t &= ~(1 << 0);
    temp[0] = t;
    ff7->setUnknown(s, 26, temp);
}

void BlackChocobo::cbS7pl_2_toggled(bool checked)
{
    if (load)
        return;
    QByteArray temp = ff7->unknown(s, 26); char t = temp.at(0);
    if (checked)
        t |= (1 << 1);
    else
        t &= ~(1 << 1);
    temp[0] = t;
    ff7->setUnknown(s, 26, temp);
}

void BlackChocobo::cbS7pl_3_toggled(bool checked)
{
    if (load)
        return;
    QByteArray temp = ff7->unknown(s, 26); char t = temp.at(0);
    if (checked)
        t |= (1 << 2);
    else
        t &= ~(1 << 2);
    temp[0] = t;
    ff7->setUnknown(s, 26, temp);
}

void BlackChocobo::cbS7pl_4_toggled(bool checked)
{
    if (load)
        return;
    QByteArray temp = ff7->unknown(s, 26); char t = temp.at(0);
    if (checked)
        t |= (1 << 3);
    else
        t &= ~(1 << 3);
    temp[0] = t;
    ff7->setUnknown(s, 26, temp);
}

void BlackChocobo::cbS7pl_5_toggled(bool checked)
{
    if (load)
        return;
    QByteArray temp = ff7->unknown(s, 26); char t = temp.at(0);
    if (checked)
        t |= (1 << 4);
    else
        t &= ~(1 << 4);
    temp[0] = t;
    ff7->setUnknown(s, 26, temp);
}

void BlackChocobo::cbS7pl_6_toggled(bool checked)
{
    if (load)
        return;
    QByteArray temp = ff7->unknown(s, 26); char t = temp.at(0);
    if (checked)
        t |= (1 << 5);
    else
        t &= ~(1 << 5);
    temp[0] = t;
    ff7->setUnknown(s, 26, temp);
}

void BlackChocobo::cbS7pl_7_toggled(bool checked)
{
    if (load)
        return;
    QByteArray temp = ff7->unknown(s, 26); char t = temp.at(0);
    if (checked)
        t |= (1 << 6);
    else
        t &= ~(1 << 6);
    temp[0] = t;
    ff7->setUnknown(s, 26, temp);
}

void BlackChocobo::cbS7pl_8_toggled(bool checked)
{
    if (load)
        return;
    QByteArray temp = ff7->unknown(s, 26); char t = temp.at(0);
    if (checked)
        t |= (1 << 7);
    else
        t &= ~(1 << 7);
    temp[0] = t;
    ff7->setUnknown(s, 26, temp);
}

void BlackChocobo::cbS7ts_1_toggled(bool checked)
{
    if (load)
        return;
    QByteArray temp = ff7->unknown(s, 26); char t = temp.at(8);
    if (checked)
        t |= (1 << 0);
    else
        t &= ~(1 << 0);
    temp[8] = t;
    ff7->setUnknown(s, 26, temp);
}

void BlackChocobo::cbS7ts_2_toggled(bool checked)
{
    if (load)
        return;
    QByteArray temp = ff7->unknown(s, 26); char t = temp.at(8);
    if (checked)
        t |= (1 << 1);
    else
        t &= ~(1 << 1);
    temp[8] = t;
    ff7->setUnknown(s, 26, temp);
}

void BlackChocobo::cbS7ts_3_toggled(bool checked)
{
    if (load)
        return;
    QByteArray temp = ff7->unknown(s, 26); char t = temp.at(8);
    if (checked)
        t |= (1 << 2);
    else
        t &= ~(1 << 2);
    temp[8] = t;
    ff7->setUnknown(s, 26, temp);
}

void BlackChocobo::cbS7ts_4_toggled(bool checked)
{
    if (load)
        return;
    QByteArray temp = ff7->unknown(s, 26); char t = temp.at(8);
    if (checked)
        t |= (1 << 3);
    else
        t &= ~(1 << 3);
    temp[8] = t;
    ff7->setUnknown(s, 26, temp);
}

void BlackChocobo::cbS7ts_5_toggled(bool checked)
{
    if (load)
        return;
    QByteArray temp = ff7->unknown(s, 26); char t = temp.at(8);
    if (checked)
        t |= (1 << 4);
    else
        t &= ~(1 << 4);
    temp[8] = t;
    ff7->setUnknown(s, 26, temp);
}

void BlackChocobo::cbS7ts_6_toggled(bool checked)
{
    if (load)
        return;
    QByteArray temp = ff7->unknown(s, 26); char t = temp.at(8);
    if (checked)
        t |= (1 << 5);
    else
        t &= ~(1 << 5);
    temp[8] = t;
    ff7->setUnknown(s, 26, temp);
}

void BlackChocobo::cbS7ts_7_toggled(bool checked)
{
    if (load)
        return;
    QByteArray temp = ff7->unknown(s, 26); char t = temp.at(8);
    if (checked)
        t |= (1 << 6);
    else
        t &= ~(1 << 6);
    temp[8] = t;
    ff7->setUnknown(s, 26, temp);
}

void BlackChocobo::cbS7ts_8_toggled(bool checked)
{
    if (load)
        return;
    QByteArray temp = ff7->unknown(s, 26); char t = temp.at(8);
    if (checked)
        t |= (1 << 7);
    else
        t &= ~(1 << 7);
    temp[8] = t;
    ff7->setUnknown(s, 26, temp);
}

void BlackChocobo::cbBombingInt_stateChanged(int checked)
{
    if (load)
        return;
    ff7->setStartBombingMission(s, checked);
}

void BlackChocobo::comboReplay_currentIndexChanged(int index)
{
    if (index > 0)
        ui->btnReplay->setEnabled(true);
    else
        ui->btnReplay->setEnabled(false);

    //Display Info on the Selected Reset
    //see on_btnReplay_clicked() for the reset data
    if (index == 1) //Bombing Mission Reset
        ui->label_replaynote->setText(tr("Replay the bombing mission from right after you get off the train."));
    else if (index == 2) //Church in the Slums Reset
        ui->label_replaynote->setText(tr("Meeting Aeris"));
    else if (index == 3) //Cloud's Flashback Reset
        ui->label_replaynote->setText(tr("This Will Copy Cloud as is to young cloud (caitsith's slot). Sephiroth's stats will come directly from the Default Save. Be Sure to back up your CaitSith and Vincent if you want to use them again"));
    else if (index == 4) //Date Scene
        ui->label_replaynote->setText(tr("Replay the Date Scene, Your Location will be set To The Ropeway Station Talk to man by the Tram to start event. If Your Looking for a special Date be sure to set your love points too."));
    else if (index == 5) //Aerith's Death
        ui->label_replaynote->setText(tr("Replay the death of Aeris.This option Will remove Aeris from your PHS"));
    else
        ui->label_replaynote->setText(tr("         INFO ON CURRENTLY SELECTED REPLAY MISSION"));
}

void BlackChocobo::btnReplay_clicked()
{
    if (ui->comboReplay->currentIndex() == 1) { // bombing mission
        ui->sbCurdisc->setValue(1);
        ui->sbMprogress->setValue(1);
        ff7->setBmProgress1(s, 0);
        ff7->setBmProgress2(s, 0);
        ff7->setBmProgress3(s, 0);
        ff7->setMidgarTrainFlags(s, 0);
        ui->cbBombingInt->setChecked(true);
        ui->comboS7Slums->setCurrentIndex(1);
        ui->sbTurkschurch->setValue(0); // reset turks.
        locationViewer->setMapId(1);
        locationViewer->setLocationId(116);
        statusBar()->showMessage(tr("Progression Reset Complete"), 750);
    } else if (ui->comboReplay->currentIndex() == 2) { // The Church In The Slums
        ui->sbCurdisc->setValue(1);
        ui->sbMprogress->setValue(130);
        ui->sbTurkschurch->setValue(0);
        ff7->setBmProgress1(s, 120);
        ff7->setBmProgress2(s, 198);
        ff7->setBmProgress3(s, 3);
        ui->cbBombingInt->setChecked(false);
        locationViewer->setMapId(1);
        locationViewer->setLocationId(183);
        partyTab->setPartyMembers(0, 0xFF, 0xFF);
        statusBar()->showMessage(tr("Progression Reset Complete"), 750);
    } else if (ui->comboReplay->currentIndex() == 3) { // Flash back
        ui->sbCurdisc->setValue(1);
        ui->sbMprogress->setValue(341);
        ff7->setBmProgress1(s, 120);
        ff7->setBmProgress2(s, 198);
        ff7->setBmProgress3(s, 3);
        ui->cbBombingInt->setChecked(false);
        locationViewer->setMapId(1);
        locationViewer->setLocationId(332);
        // set up young cloud, Copy Cloud Change ID to young Cloud
        ff7->setCharacter(s, FF7Char::CaitSith, ff7->character(s, FF7Char::Cloud));
        ff7->setCharID(s, FF7Char::CaitSith, FF7Char::YoungCloud);
        //set up Sephiroth
        FF7Save *temp = new FF7Save();
        temp->newGame(s);
        ff7->setCharacter(s, FF7Char::Vincent, temp->character(s, FF7Char::Vincent));
        if (ff7->isJPN(s))
            ff7->setCharName(s, 7, QString::fromUtf8("セフィロス"));
        else
            ff7->setCharName(s, 7, QString::fromUtf8("Sephiroth"));

        set_char_buttons();
        if (curchar == FF7Char::CaitSith)
            partyTab->setCharacter(ff7->character(s, 6), ff7->charName(s, 6));
        else if (curchar == FF7Char::Vincent)
            partyTab->setCharacter(ff7->character(s, 7), ff7->charName(s, 7));
        statusBar()->showMessage(tr("Progression Reset Complete"), 750);
    }

    else if (ui->comboReplay->currentIndex() == 4) { // The Date Scene
        ui->sbCurdisc->setValue(1);
        ui->sbMprogress->setValue(583);
        ff7->setBmProgress1(s, 120);
        ff7->setBmProgress2(s, 198);
        ff7->setBmProgress3(s, 3);
        ui->cbBombingInt->setChecked(false);
        locationViewer->setMapId(1);
        locationViewer->setLocationId(496);
        statusBar()->showMessage(tr("Progression Reset Complete"), 750);
    }

    else if (ui->comboReplay->currentIndex() == 5) { //Aeris Death
        ui->sbCurdisc->setValue(1);
        ui->sbMprogress->setValue(664);
        ff7->setBmProgress1(s, 120);
        ff7->setBmProgress2(s, 198);
        ff7->setBmProgress3(s, 3);
        ui->cbBombingInt->setChecked(false);
        locationViewer->setMapId(1);
        locationViewer->setLocationId(646);
        phsList->setChecked(FF7Char::Aerith, PhsListWidget::PHSALLOWED, false);
        phsList->setChecked(FF7Char::Aerith, PhsListWidget::PHSVISIBLE, false);
        statusBar()->showMessage(tr("Progression Reset Complete"), 750);
    }
    ui->comboReplay->setCurrentIndex(0);
    if (!load)
        progress_update();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~FUNCTIONS FOR TESTING~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void BlackChocobo::btnRemoveAllMateria_clicked()
{
    for (int i = 0; i < 200; i++)
        ff7->setPartyMateria(s, i, FF7Materia::EmptyId, FF7Materia::MaxMateriaAp);
    materiaupdate();
}

void BlackChocobo::btnRemoveAllStolen_clicked()
{
    for (int i = 0; i < 48; i++)
        ff7->setStolenMateria(s, i, FF7Materia::EmptyId, FF7Materia::MaxMateriaAp);
    guirefresh();
}

void BlackChocobo::sbBloveAeris_valueChanged(int value)
{
    if (load)
        return;
    ff7->setLove(s, true, FF7Save::LOVE_AERIS, quint8(value));
}

void BlackChocobo::sbBloveTifa_valueChanged(int value)
{
    if (load)
        return;
    ff7->setLove(s, true, FF7Save::LOVE_TIFA, quint8(value));
}

void BlackChocobo::sbBloveYuffie_valueChanged(int value)
{
    if (load)
        return;
    ff7->setLove(s, true, FF7Save::LOVE_YUFFIE, quint8(value));
}

void BlackChocobo::sbBloveBarret_valueChanged(int value)
{
    if (load)
        return;
    ff7->setLove(s, true, FF7Save::LOVE_BARRET, quint8(value));
}

void BlackChocobo::sbCoster1_valueChanged(int value)
{
    if (load)
        return;
    ff7->setSpeedScore(s, 1, quint16(value));
}

void BlackChocobo::sbCoster2_valueChanged(int value)
{
    if (load)
        return;
    ff7->setSpeedScore(s, 2, quint16(value));
}

void BlackChocobo::sbCoster3_valueChanged(int value)
{
    if (load)
        return;
    ff7->setSpeedScore(s, 3, quint16(value));
}

void BlackChocobo::sbTimerTimeHour_valueChanged(int value)
{
    if (load)
        return;
    ff7->setCountdownTimer(s, quint32((value * 3600) + (ui->sbTimerTimeMin->value() * 60) + (ui->sbTimerTimeSec->value())));
}

void BlackChocobo::sbTimerTimeMin_valueChanged(int value)
{
    if (load)
        return;
    ff7->setCountdownTimer(s, quint32((ui->sbTimerTimeHour->value() * 3600) + ((value * 60)) + (ui->sbTimerTimeSec->value())));
}

void BlackChocobo::sbTimerTimeSec_valueChanged(int value)
{
    if (load)
        return;
    ff7->setCountdownTimer(s, quint32((ui->sbTimerTimeHour->value() * 3600) + (ui->sbTimerTimeMin->value() * 60) + (value)));
}

void BlackChocobo::sbUweaponHp_valueChanged(int value)
{
    if (load)
        return;
    ff7->setUWeaponHp(s, value);
}

void BlackChocobo::cbRegVinny_toggled(bool checked)
{
    if (load)
        return;
    ff7->setVincentUnlocked(s, checked);
}

void BlackChocobo::cbRegYuffie_toggled(bool checked)
{
    if (load)
        return;
    ff7->setYuffieUnlocked(s, checked);
}

void BlackChocobo::cbYuffieForest_toggled(bool checked)
{
    if (load)
        return;
    ff7->setCanFightNinjaInForest(s, checked);
}

void BlackChocobo::cbMidgartrain_1_toggled(bool checked)
{
    if (load)
        return;
    ff7->setMidgarTrainFlags(s, 0, checked);
}

void BlackChocobo::cbMidgartrain_2_toggled(bool checked)
{
    if (load)
        return;
    ff7->setMidgarTrainFlags(s, 1, checked);
}

void BlackChocobo::cbMidgartrain_3_toggled(bool checked)
{
    if (load)
        return;
    ff7->setMidgarTrainFlags(s, 2, checked);
}

void BlackChocobo::cbMidgartrain_4_toggled(bool checked)
{
    if (load)
        return;
    ff7->setMidgarTrainFlags(s, 3, checked);
}

void BlackChocobo::cbMidgartrain_5_toggled(bool checked)
{
    if (load)
        return;
    ff7->setMidgarTrainFlags(s, 4, checked);
}

void BlackChocobo::cbMidgartrain_6_toggled(bool checked)
{
    if (load)
        return;
    ff7->setMidgarTrainFlags(s, 5, checked);
}

void BlackChocobo::cbMidgartrain_7_toggled(bool checked)
{
    if (load)
        return;
    ff7->setMidgarTrainFlags(s, 6, checked);

}

void BlackChocobo::cbMidgartrain_8_toggled(bool checked)
{
    if (load)
        return;
    ff7->setMidgarTrainFlags(s, 7, checked);
}

void BlackChocobo::cbTutWorldSave_stateChanged(int value)
{
    if (load)
        return;
    if (value == 0)
        ff7->setTutSave(s, 0x00);
    else if (value == 1)
        ff7->setTutSave(s, 0x32);
    else if (value == 2)
        ff7->setTutSave(s, 0x3A);
    ui->lcdNumber_7->display(ff7->tutSave(s));
}

void BlackChocobo::comboSlotNumber_currentIndexChanged(int index)
{
    if (load)
        return;
    if (ff7->isFF7(s)) {
        ff7->setSaveNumber(s, index);
        guirefresh();
    }
}

void BlackChocobo::cbTutSub_toggled(bool checked)
{
    if (load)
        return;
    ff7->setTutSub(s, 2, checked);
    ui->lcdTutSub->display(ff7->tutSub(s));
}

void BlackChocobo::cbRubyDead_toggled(bool checked)
{
    if (load)
        return;
    ff7->setKilledRubyWeapon(s, checked);
}

void BlackChocobo::cbEmeraldDead_toggled(bool checked)
{
    if (load)
        return;
    ff7->setKilledEmeraldWeapon(s, checked);
}

void BlackChocobo::comboHighwindBuggy_currentIndexChanged(int index)
{
    if (load)
        return;
    switch (index) {
        case 0: ui->sbBhId->setValue(0x00); ui->cbVisibleBuggy->setChecked(false); ui->cbVisibleHighwind->setChecked(false); break;
        case 1: ui->sbBhId->setValue(0x06); ui->cbVisibleBuggy->setChecked(true); break; //buggy
        case 2: ui->sbBhId->setValue(0x03); ui->cbVisibleHighwind->setChecked(true); break; //highwind
        default: break;
    }
}

void BlackChocobo::cbVisibleBuggy_toggled(bool checked)
{
    if (load)
        return;
    ff7->setWorldVehicle(s, FF7Save::WVEHCILE_BUGGY, checked);
    if (checked) {
        if (ui->cbVisibleHighwind->isChecked())
            ui->cbVisibleHighwind->setChecked(false);
        load = true;
        ui->comboHighwindBuggy->setCurrentIndex(1);
        ui->sbBhId->setValue(0x06);
        load = false;
    } else {
        if (!ui->cbVisibleBuggy->isChecked()) {
            load = true;
            ui->comboHighwindBuggy->setCurrentIndex(0);
            ui->sbBhId->setValue(0x00);
            load = false;
        }
    }
}

void BlackChocobo::cbVisibleBronco_toggled(bool checked)
{
    if (load)
        return;
    ff7->setWorldVehicle(s, FF7Save::WVEHCILE_TBRONCO, checked);
}

void BlackChocobo::cbVisibleHighwind_toggled(bool checked)
{
    if (load)
        return;
    ff7->setWorldVehicle(s, FF7Save::WVEHCILE_HIGHWIND, checked);
    if (checked) {
        if (ui->cbVisibleBuggy->isChecked()) {
            ui->cbVisibleBuggy->setChecked(false);
        }
        load = true;
        ui->comboHighwindBuggy->setCurrentIndex(2);
        ui->sbBhId->setValue(0x03);
        load = false;
    } else {
        if (!ui->cbVisibleHighwind->isChecked()) {
            load = true;
            ui->comboHighwindBuggy->setCurrentIndex(0);
            ui->sbBhId->setValue(0x00);
            load = false;
        }
    }
}

void BlackChocobo::cbVisibleWildChocobo_toggled(bool checked)
{
    if (!load)
        ff7->setWorldChocobo(s, FF7Save::WCHOCO_WILD, checked);

    if (!checked) {
        ui->cbVisibleYellowChocobo->setChecked(false);
        ui->cbVisibleGreenChocobo->setChecked(false);
        ui->cbVisibleBlueChocobo->setChecked(false);
        ui->cbVisibleBlackChocobo->setChecked(false);
        ui->cbVisibleGoldChocobo->setChecked(false);
    }
    ui->cbVisibleYellowChocobo->setEnabled(checked);
    ui->cbVisibleGreenChocobo->setEnabled(checked);
    ui->cbVisibleBlueChocobo->setEnabled(checked);
    ui->cbVisibleBlackChocobo->setEnabled(checked);
    ui->cbVisibleGoldChocobo->setEnabled(checked);

}

void BlackChocobo::cbVisibleYellowChocobo_toggled(bool checked)
{
    if (load)
        return;
    ff7->setWorldChocobo(s, FF7Save::WCHOCO_YELLOW, checked);
    if (checked) {
        ui->cbVisibleGreenChocobo->setChecked(false);
        ui->cbVisibleBlueChocobo->setChecked(false);
        ui->cbVisibleBlackChocobo->setChecked(false);
        ui->cbVisibleGoldChocobo->setChecked(false);
    }
}

void BlackChocobo::cbVisibleGreenChocobo_toggled(bool checked)
{
    if (load)
        return;
    ff7->setWorldChocobo(s, FF7Save::WCHOCO_GREEN, checked);
    if (checked) {
        ui->cbVisibleYellowChocobo->setChecked(false);
        ui->cbVisibleBlueChocobo->setChecked(false);
        ui->cbVisibleBlackChocobo->setChecked(false);
        ui->cbVisibleGoldChocobo->setChecked(false);
    }
}

void BlackChocobo::cbVisibleBlueChocobo_toggled(bool checked)
{
    if (load)
        return;
    ff7->setWorldChocobo(s, FF7Save::WCHOCO_BLUE, checked);
    if (checked) {
        ui->cbVisibleYellowChocobo->setChecked(false);
        ui->cbVisibleGreenChocobo->setChecked(false);
        ui->cbVisibleBlackChocobo->setChecked(false);
        ui->cbVisibleGoldChocobo->setChecked(false);
    }
}

void BlackChocobo::cbVisibleBlackChocobo_toggled(bool checked)
{
    if (load)
        return;
    ff7->setWorldChocobo(s, FF7Save::WCHOCO_BLACK, checked);
    if (checked) {
        ui->cbVisibleYellowChocobo->setChecked(false);
        ui->cbVisibleGreenChocobo->setChecked(false);
        ui->cbVisibleBlueChocobo->setChecked(false);
        ui->cbVisibleGoldChocobo->setChecked(false);
    }
}

void BlackChocobo::cbVisibleGoldChocobo_toggled(bool checked)
{
    if (load)
        return;
    ff7->setWorldChocobo(s, FF7Save::WCHOCO_GOLD, checked);
    if (checked) {
        ui->cbVisibleYellowChocobo->setChecked(false);
        ui->cbVisibleGreenChocobo->setChecked(false);
        ui->cbVisibleBlueChocobo->setChecked(false);
        ui->cbVisibleBlackChocobo->setChecked(false);
    }
}
// Leader's world map stuff. 0
void BlackChocobo::sbLeaderId_valueChanged(int value)
{
    if (load)
        return;
    ff7->setWorldCoordsLeaderID(s, value);
}

void BlackChocobo::sbLeaderAngle_valueChanged(int value)
{
    if (load)
        return;
    ff7->setWorldCoordsLeaderAngle(s, value);
}

void BlackChocobo::sbLeaderZ_valueChanged(int value)
{
    if (load)
        return;
    ff7->setWorldCoordsLeaderZ(s, value);
}

void BlackChocobo::sbLeaderX_valueChanged(int value)
{
    if (load)
        return;
    ff7->setWorldCoordsLeaderX(s, value);
    if (ui->comboMapControls->currentIndex() == 0) {
        load = true;
        ui->slideWorldX->setValue(value);
        load = false;
    }
}

void BlackChocobo::sbLeaderY_valueChanged(int value)
{
    if (load)
        return;
    ff7->setWorldCoordsLeaderY(s, value);
    if (ui->comboMapControls->currentIndex() == 0) {
        load = true;
        ui->slideWorldY->setValue(value);
        load = false;
    }
}

//Tiny bronco / chocobo world 1
void BlackChocobo::sbTcId_valueChanged(int value)
{
    if (load)
        return;
    ff7->setWorldCoordsTcID(s, value);
}

void BlackChocobo::sbTcAngle_valueChanged(int value)
{
    if (load)
        return;
    ff7->setWorldCoordsTcAngle(s, value);
}

void BlackChocobo::sbTcZ_valueChanged(int value)
{
    if (load)
        return;
    ff7->setWorldCoordsTcZ(s, value);
}

void BlackChocobo::sbTcX_valueChanged(int value)
{
    if (load)
        return;
    ff7->setWorldCoordsTcX(s, value);
    if (ui->comboMapControls->currentIndex() == 1) {
        load = true;
        ui->slideWorldX->setValue(value);
        load = false;
    }
}

void BlackChocobo::sbTcY_valueChanged(int value)
{
    if (load)
        return;
    ff7->setWorldCoordsTcY(s, value);
    if (ui->comboMapControls->currentIndex() == 1) {
        load = true;
        ui->slideWorldY->setValue(value);
        load = false;
    }
}

//buggy / highwind world 2
void BlackChocobo::sbBhId_valueChanged(int value)
{
    if (load)
        return;
    ff7->setWorldCoordsBhID(s, value);
}

void BlackChocobo::sbBhAngle_valueChanged(int value)
{
    if (load)
        return;
    ff7->setWorldCoordsBhAngle(s, value);
}

void BlackChocobo::sbBhZ_valueChanged(int value)
{
    if (load)
        return;
    ff7->setWorldCoordsBhZ(s, value);
}

void BlackChocobo::sbBhX_valueChanged(int value)
{
    if (load)
        return;
    ff7->setWorldCoordsBhX(s, value);
    if (ui->comboMapControls->currentIndex() == 2) {
        load = true;
        ui->slideWorldX->setValue(value);
        load = false;
    }
}

void BlackChocobo::sbBhY_valueChanged(int value)
{
    if (load)
        return;
    ff7->setWorldCoordsBhY(s, value);
    if (ui->comboMapControls->currentIndex() == 2) {
        load = true;
        ui->slideWorldY->setValue(value);
        load = false;
    }
}
// sub world 3

void BlackChocobo::sbSubId_valueChanged(int value)
{
    if (load)
        return;
    ff7->setWorldCoordsSubID(s, value);
}

void BlackChocobo::sbSubAngle_valueChanged(int value)
{
    if (load)
        return;
    ff7->setWorldCoordsSubAngle(s, value);
}

void BlackChocobo::sbSubZ_valueChanged(int value)
{
    if (load)
        return;
    ff7->setWorldCoordsSubZ(s, value);
}

void BlackChocobo::sbSubX_valueChanged(int value)
{
    if (load)
        return;
    ff7->setWorldCoordsSubX(s, value);
    if (ui->comboMapControls->currentIndex() == 3) {
        load = true;
        ui->slideWorldX->setValue(value);
        load = false;
    }
}

void BlackChocobo::sbSubY_valueChanged(int value)
{
    if (load)
        return;
    ff7->setWorldCoordsSubY(s, value);
    if (ui->comboMapControls->currentIndex() == 3) {
        load = true;
        ui->slideWorldY->setValue(value);
        load = false;
    }
}

//Wild Chocobo 4
void BlackChocobo::sbWcId_valueChanged(int value)
{
    if (load)
        return;
    ff7->setWorldCoordsWchocoID(s, value);
}

void BlackChocobo::sbWcAngle_valueChanged(int value)
{
    if (load)
        return;
    ff7->setWorldCoordsWchocoAngle(s, value);
}

void BlackChocobo::sbWcZ_valueChanged(int value)
{
    if (load)
        return;
    ff7->setWorldCoordsWchocoZ(s, value);
}

void BlackChocobo::sbWcX_valueChanged(int value)
{
    if (load)
        return;
    ff7->setWorldCoordsWchocoX(s, value);
    if (ui->comboMapControls->currentIndex() == 4) {
        load = true;
        ui->slideWorldX->setValue(value);
        load = false;
    }
}

void BlackChocobo::sbWcY_valueChanged(int value)
{
    if (load)
        return;
    ff7->setWorldCoordsWchocoY(s, value);
    if (ui->comboMapControls->currentIndex() == 4) {
        load = true;
        ui->slideWorldY->setValue(value);
        load = false;
    }
}

//Ruby world stuff 5
void BlackChocobo::sbDurwId_valueChanged(int value)
{
    if (load)
        return;
    ff7->setWorldCoordsDurwID(s, value);
}

void BlackChocobo::sbDurwAngle_valueChanged(int value)
{
    if (load)
        return;
    ff7->setWorldCoordsDurwAngle(s, value);
}

void BlackChocobo::sbDurwZ_valueChanged(int value)
{
    if (load)
        return;
    ff7->setWorldCoordsDurwZ(s, value);
}

void BlackChocobo::sbDurwX_valueChanged(int value)
{
    if (load)
        return;
    ff7->setWorldCoordsDurwX(s, value);
    if (ui->comboMapControls->currentIndex() == 5) {
        load = true;
        ui->slideWorldX->setValue(value);
        load = false;
    }
}

void BlackChocobo::sbDurwY_valueChanged(int value)
{
    if (load)
        return;
    ff7->setWorldCoordsDurwY(s, value);
    if (ui->comboMapControls->currentIndex() == 5) {
        load = true;
        ui->slideWorldY->setValue(value);
        load = false;
    }
}

void BlackChocobo::comboMapControls_currentIndexChanged(int index)
{
    load = true;
    switch (index) {
    case 0: ui->slideWorldX->setValue(ff7->worldCoordsLeaderX(s)); ui->slideWorldY->setValue(ff7->worldCoordsLeaderY(s));   break;
    case 1: ui->slideWorldX->setValue(ff7->worldCoordsTcX(s));     ui->slideWorldY->setValue(ff7->worldCoordsTcY(s));       break;
    case 2: ui->slideWorldX->setValue(ff7->worldCoordsBhX(s));     ui->slideWorldY->setValue(ff7->worldCoordsBhY(s));       break;
    case 3: ui->slideWorldX->setValue(ff7->worldCoordsSubX(s));    ui->slideWorldY->setValue(ff7->worldCoordsSubY(s));      break;
    case 4: ui->slideWorldX->setValue(ff7->worldCoordsWchocoX(s));  ui->slideWorldY->setValue(ff7->worldCoordsWchocoY(s));   break;
    case 5: ui->slideWorldX->setValue(ff7->worldCoordsDurwX(s));   ui->slideWorldY->setValue(ff7->worldCoordsDurwY(s));     break;
    }
    load = false;
}

void BlackChocobo::slideWorldX_valueChanged(int value)
{
    if (load)
        return;
    fileModified(true);
    switch (ui->comboMapControls->currentIndex()) {
        case 0: ui->sbLeaderX->setValue(value);  break;
        case 1: ui->sbTcX->setValue(value);      break;
        case 2: ui->sbBhX->setValue(value);      break;
        case 3: ui->sbSubX->setValue(value);     break;
        case 4: ui->sbWcX->setValue(value);      break;
        case 5: ui->sbDurwX->setValue(value);    break;
    }
}

void BlackChocobo::slideWorldY_valueChanged(int value)
{
    if (load)
        return;
    fileModified(true);
    switch (ui->comboMapControls->currentIndex()) {
        case 0: ui->sbLeaderY->setValue(value);  break;
        case 1: ui->sbTcY->setValue(value);      break;
        case 2: ui->sbBhY->setValue(value);      break;
        case 3: ui->sbSubY->setValue(value);     break;
        case 4: ui->sbWcY->setValue(value);      break;
        case 5: ui->sbDurwY->setValue(value);    break;
    }
}

void BlackChocobo::worldMapView_customContextMenuRequested(QPoint pos)
{
    //Need to create a Paint System Here To put Dots where Chars Are Placed.
    QMenu menu(this);
    QAction *sel;
    menu.addAction(tr("&Place Leader"));
    menu.addAction(tr("Place &Tiny Bronco/Chocobo"));
    menu.addAction(tr("Place &Buggy/Highwind"));
    menu.addAction(tr("Place &Sub"));
    menu.addAction(tr("Place &Wild Chocobo"));
    menu.addAction(tr("Place &Diamond/Ultimate/Ruby Weapon"));
    /* Do Nothing. Don't know emerald weapon Coords
    menu.addAction(tr("Place Emerald Weapon?"));
    */
    sel = menu.exec(ui->worldMapView->mapToGlobal(pos));
    if (!sel)
        return;

    fileModified(true);
    if (sel->text() == tr("&Place Leader")) {
        ui->sbLeaderX->setValue(pos.x() * (295000 / ui->worldMapView->width()));
        ui->sbLeaderY->setValue(pos.y() * (230000 / ui->worldMapView->height()));
    } else if (sel->text() == tr("Place &Tiny Bronco/Chocobo")) {
        ui->sbTcX->setValue(pos.x() * (295000 / ui->worldMapView->width()));
        ui->sbTcY->setValue(pos.y() * (230000 / ui->worldMapView->height()));
    } else if (sel->text() == tr("Place &Buggy/Highwind")) {
        ui->sbBhX->setValue(pos.x() * (295000 / ui->worldMapView->width()));
        ui->sbBhY->setValue(pos.y() * (230000 / ui->worldMapView->height()));
    } else if (sel->text() == tr("Place &Sub")) {
        ui->sbSubX->setValue(pos.x() * (295000 / ui->worldMapView->width()));
        ui->sbSubY->setValue(pos.y() * (230000 / ui->worldMapView->height()));
    } else if (sel->text() == tr("Place &Wild Chocobo")) {
        ui->sbWcX->setValue(pos.x() * (295000 / ui->worldMapView->width()));
        ui->sbWcY->setValue(pos.y() * (230000 / ui->worldMapView->height()));
    } else if (sel->text() == tr("Place &Diamond/Ultimate/Ruby Weapon")) {
        ui->sbDurwX->setValue(pos.x() * (295000 / ui->worldMapView->width()));
        ui->sbDurwY->setValue(pos.y() * (230000 / ui->worldMapView->height()));
    } else {
        return;
    }
}//End Of Map Context Menu

void BlackChocobo::unknown_refresh(int z)//remember to add/remove case statments in all 3 switches when number of z vars changes.
{
    load = true;

    int rows = 0;
    QTableWidgetItem *newItem;
    QByteArray temp, temp2;
    int s2;

    ui->tblUnknown->reset();
    ui->tblCompareUnknown->reset();
    if (z <= ff7->unknown_zmax())
        temp = ff7->unknown(s, z);
    else if (z == ff7->unknown_zmax() + 1)
        temp = ff7->slotFF7Data(s);

    rows = temp.size();

    ui->tblUnknown->setRowCount(rows);
    if (ui->comboCompareSlot->currentIndex() != 0)
        ui->tblCompareUnknown->setRowCount(rows);

    for (int i = 0; i < rows; i++) {
        if (ui->comboZVar->currentText() == "SLOT") {
            QString hex_str = QString("%1").arg(i, 4, 16, QChar('0')).toUpper(); //format ex: 000C
            newItem = new QTableWidgetItem(hex_str, 0);
            ui->tblUnknown->setItem(i, 0, newItem);
        } else {
            newItem = new QTableWidgetItem(QString::number(i), 0);
            ui->tblUnknown->setItem(i, 0, newItem);
        }

        quint8 value = quint8(temp.at(i));

        //Write Hex
        newItem = new QTableWidgetItem(QString("%1").arg(value, 2, 16, QChar('0')).toUpper(), 0);
        newItem->setTextAlignment(Qt::AlignHCenter);
        ui->tblUnknown->setItem(i, 1, newItem);
        //Write Dec
        newItem = new QTableWidgetItem(QString("%1").arg(value, 3, 10, QChar('0')), 0);
        newItem->setTextAlignment(Qt::AlignHCenter);
        ui->tblUnknown->setItem(i, 2, newItem);
        //Write Bin
        newItem = new QTableWidgetItem(QString("%1").arg(value, 8, 2, QChar('0')), 0);
        newItem->setTextAlignment(Qt::AlignHCenter);
        ui->tblUnknown->setItem(i, 3, newItem);
        //Write Char
        newItem = new QTableWidgetItem(QString("%1").arg(QChar(value)), 0);
        newItem->setTextAlignment(Qt::AlignHCenter);
        ui->tblUnknown->setItem(i, 4, newItem);
        //Set Height
        ui->tblUnknown->setRowHeight(i, fontMetrics().height() + 6);

        if (ui->comboCompareSlot->currentIndex() != 0) {
            //do the same for the compare slot if one has been selected.
            if (ui->comboZVar->currentText() == "SLOT") {
                newItem = new QTableWidgetItem(QString("%1").arg(i, 4, 16, QChar('0')).toUpper(), 0);
                ui->tblCompareUnknown->setItem(i, 0, newItem);
            } else {
                newItem = new QTableWidgetItem(QString::number(i), 0);
                newItem->setTextAlignment(Qt::AlignHCenter);
                ui->tblCompareUnknown->setItem(i, 0, newItem);
            }

            s2 = ui->comboCompareSlot->currentIndex() - 1;
            if (z <= ff7->unknown_zmax())
                temp2 = ff7->unknown(s2, z);
            else if (z == ff7->unknown_zmax() + 1)
                temp2 = ff7->slotFF7Data(s2);
            value = quint8(temp2.at(i));

            //Write Hex
            newItem = new QTableWidgetItem(QString("%1").arg(value, 2, 16, QChar('0')).toUpper(), 0);
            newItem->setTextAlignment(Qt::AlignHCenter);
            ui->tblCompareUnknown->setItem(i, 1, newItem);
            //Write Dec
            newItem = new QTableWidgetItem(QString("%1").arg(value, 3, 10, QChar('0')), 0);
            newItem->setTextAlignment(Qt::AlignHCenter);
            ui->tblCompareUnknown->setItem(i, 2, newItem);
            //Write Bin
            newItem = new QTableWidgetItem(QString("%1").arg(value, 8, 2, QChar('0')), 0);
            newItem->setTextAlignment(Qt::AlignHCenter);
            ui->tblCompareUnknown->setItem(i, 3, newItem);
            //Write Char
            newItem = new QTableWidgetItem(QChar(value), 0);
            newItem->setTextAlignment(Qt::AlignHCenter);
            ui->tblCompareUnknown->setItem(i, 4, newItem);

            ui->tblCompareUnknown->setRowHeight(i, fontMetrics().height() +6);
            if (ui->tblCompareUnknown->item(i, 1)->text() != ui->tblUnknown->item(i, 1)->text()) {
                for (int c = 0; c < 5; c++) {
                    //color the diffs ;)
                    ui->tblCompareUnknown->item(i, c)->setBackground(Qt::yellow);
                    ui->tblCompareUnknown->item(i, c)->setForeground(Qt::red);
                    ui->tblUnknown->item(i, c)->setBackground(Qt::yellow);
                    ui->tblUnknown->item(i, c)->setForeground(Qt::red);
                }
            }
        }
    }
    for (int i = 0; i < rows; i++) { //set up the item flags
        ui->tblUnknown->item(i, 0)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        ui->tblUnknown->item(i, 1)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
        ui->tblUnknown->item(i, 2)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
        ui->tblUnknown->item(i, 3)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
        ui->tblUnknown->item(i, 4)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);

        if (ui->comboCompareSlot->currentIndex() != 0) {
            ui->tblCompareUnknown->item(i, 0)->setFlags(Qt::ItemIsEnabled);
            ui->tblCompareUnknown->item(i, 1)->setFlags(Qt::ItemIsEnabled);
            ui->tblCompareUnknown->item(i, 2)->setFlags(Qt::ItemIsEnabled);
            ui->tblCompareUnknown->item(i, 3)->setFlags(Qt::ItemIsEnabled);
            ui->tblCompareUnknown->item(i, 4)->setFlags(Qt::ItemIsEnabled);
        }
    }
    load = false;
}

void BlackChocobo::comboZVar_currentIndexChanged(int z)
{
    unknown_refresh(z);
}

void BlackChocobo::comboCompareSlot_currentIndexChanged(int index)
{
    if (index == 0) {
        ui->tblCompareUnknown->clearContents();
        ui->tblCompareUnknown->setRowCount(0);
    } else
        unknown_refresh(ui->comboZVar->currentIndex());
}

void BlackChocobo::tblUnknown_itemChanged(QTableWidgetItem *item)
{
    if (load)
        return;

    QByteArray temp;

    int z = ui->comboZVar->currentIndex();
    if (z <= ff7->unknown_zmax())
        temp = ff7->unknown(s, z);
    else if (z == ff7->unknown_zmax() + 1)
        temp = ff7->slotFF7Data(s);

    switch (item->column()) {
        case 1: temp[item->row()] = char(item->text().toInt(nullptr, 16));  break;
        case 2: temp[item->row()] = char(item->text().toInt());      break;
        case 3: temp[item->row()] = char(item->text().toInt(nullptr, 2));   break;
    }

    if (z <= ff7->unknown_zmax())
        ff7->setUnknown(s, z, temp);
    else if (z == ff7->unknown_zmax() + 1)
        ff7->setSlotFF7Data(s, temp);

    unknown_refresh(z);
}

void BlackChocobo::comboS7Slums_currentIndexChanged(int index)
{
    if (load)
        return;
    QByteArray temp(ff7->unknown(s, 26));
    switch (index) {
        default: break; //do nothing
        case 1: //initial slums setting
            temp.replace(0, 6, "\x00\x00\x00\x00\x00\x00");
            break;

        case 2://after first scene. needs game global progress set to 105
            temp.replace(0, 6, "\xBF\x03\x05\x17\x5D\xEF");
            break;

        case 3://plate falling
            temp.replace(0, 6, "\xBF\x13\x05\x17\x5D\xEF");
            break;
    }
    ff7->setUnknown(s, 26, temp);
}

void BlackChocobo::char_materia_changed(materia mat)
{
    ff7->setCharMateria(s, curchar, mslotsel, mat);
}

void BlackChocobo::char_accessory_changed(quint8 accessory)
{
    ff7->setCharAccessory(s, curchar, accessory);
}

void BlackChocobo::char_armor_changed(quint8 armor)
{
    ff7->setCharArmor(s, curchar, armor);
}

void BlackChocobo::char_baseHp_changed(quint16 hp)
{
    ff7->setCharBaseHp(s, curchar, hp);
}

void BlackChocobo::char_baseMp_changed(quint16 mp)
{
    ff7->setCharBaseMp(s, curchar, mp);
}

void BlackChocobo::char_curHp_changed(quint16 hp)
{
    ff7->setCharCurrentHp(s, curchar, hp);
    if (curchar == ff7->party(s, 0))
        ff7->setDescCurHP(s, hp);
}

void BlackChocobo::char_curMp_changed(quint16 mp)
{
    ff7->setCharCurrentMp(s, curchar, mp);
    if (curchar == ff7->party(s, 0))
        ff7->setDescCurMP(s, mp);
}

void BlackChocobo::char_id_changed(qint8 id)
{
    ff7->setCharID(s, curchar, id);
    partyTab->setButtonImageToId(curchar, id);
}

void BlackChocobo::char_level_changed(qint8 level)
{
    ff7->setCharLevel(s, curchar, level);
    if (curchar == ff7->party(s, 0))
        ff7->setDescLevel(s, level);
}

void BlackChocobo::char_str_changed(quint8 str)
{
    ff7->setCharStr(s, curchar, str);
}

void BlackChocobo::char_vit_changed(quint8 vit)
{
    ff7->setCharVit(s, curchar, vit);
}

void BlackChocobo::char_mag_changed(quint8 mag)
{
    ff7->setCharMag(s, curchar, mag);
}

void BlackChocobo::char_spi_changed(quint8 spi)
{
    ff7->setCharSpi(s, curchar, spi);
}

void BlackChocobo::char_dex_changed(quint8 dex)
{
    ff7->setCharDex(s, curchar, dex);
}

void BlackChocobo::char_lck_changed(quint8 lck)
{
    ff7->setCharLck(s, curchar, lck);
}

void BlackChocobo::char_strBonus_changed(quint8 value)
{
    ff7->setCharStrBonus(s, curchar, value);
}

void BlackChocobo::char_vitBonus_changed(quint8 value)
{
    ff7->setCharVitBonus(s, curchar, value);
}

void BlackChocobo::char_magBonus_changed(quint8 value)
{
    ff7->setCharMagBonus(s, curchar, value);
}

void BlackChocobo::char_spiBonus_changed(quint8 value)
{
    ff7->setCharSpiBonus(s, curchar, value);
}

void BlackChocobo::char_dexBonus_changed(quint8 value)
{
    ff7->setCharDexBonus(s, curchar, value);
}

void BlackChocobo::char_lckBonus_changed(quint8 value)
{
    ff7->setCharLckBonus(s, curchar, value);
}

void BlackChocobo::char_limitLevel_changed(qint8 value)
{
    ff7->setCharLimitLevel(s, curchar, value);
}

void BlackChocobo::char_limitBar_changed(quint8 value)
{
    ff7->setCharLimitBar(s, curchar, value);
}

void BlackChocobo::char_weapon_changed(quint8 value)
{
    ff7->setCharWeapon(s, curchar, value);
}

void BlackChocobo::char_kills_changed(quint16 value)
{
    ff7->setCharKills(s, curchar, value);
}

void BlackChocobo::char_row_changed(quint8 value)
{
    ff7->setCharFlag(s, curchar, 1, value);
}

void BlackChocobo::char_levelProgress_changed(quint8 value)
{
    ff7->setCharFlag(s, curchar, 2, value);
}

void BlackChocobo::char_sadnessfury_changed(quint8 value)
{
    ff7->setCharFlag(s, curchar, 0, value);
}

void BlackChocobo::char_limits_changed(quint16 value)
{
    ff7->setCharLimits(s, curchar, value);
}

void BlackChocobo::char_timesused1_changed(quint16 value)
{
    ff7->setCharTimeLimitUsed(s, curchar, 1, value);
}

void BlackChocobo::char_timeused2_changed(quint16 value)
{
    ff7->setCharTimeLimitUsed(s, curchar, 2, value);
}

void BlackChocobo::char_timeused3_changed(quint16 value)
{
    ff7->setCharTimeLimitUsed(s, curchar, 3, value);
}

void BlackChocobo::char_exp_changed(quint32 value)
{
    ff7->setCharCurrentExp(s, curchar, value);
}

void BlackChocobo::char_expNext_changed(quint32 value)
{
    ff7->setCharNextExp(s, curchar, value);
}

void BlackChocobo::char_mslot_changed(int slot)
{
    mslotsel = slot;
}

void BlackChocobo::char_name_changed(QString name)
{
    ff7->setCharName(s, curchar, name);
    if (curchar == ff7->party(s, 0))
        ff7->setDescName(s, name);
}

void BlackChocobo::char_maxHp_changed(quint16 value)
{
    ff7->setCharMaxHp(s, curchar, value);
    if (curchar == ff7->party(s, 0))
        ff7->setDescMaxHP(s, value);
}

void BlackChocobo::char_maxMp_changed(quint16 value)
{
    ff7->setCharMaxMp(s, curchar, value);
    if (curchar == ff7->party(s, 0))
        ff7->setDescMaxMP(s, value);
}

void BlackChocobo::Items_Changed(QList<quint16> items)
{
    ff7->setItems(s, items);
}

void BlackChocobo::sbSnowBegScore_valueChanged(int value)
{
    if (load)
        return;
    ff7->setSnowboardScore(s, 0, quint8(value));
}

void BlackChocobo::sbSnowExpScore_valueChanged(int value)
{
    if (load)
        return;
    ff7->setSnowboardScore(s, 1, quint8(value));
}

void BlackChocobo::sbSnowCrazyScore_valueChanged(int value)
{
    if (load)
        return;
    ff7->setSnowboardScore(s, 2, quint8(value));
}

void BlackChocobo::sbSnowBegMin_valueChanged(int value)
{
    if (load)
        return;
    QString time = ff7->snowboardTime(s, 0);
    time.replace(0, 2, QString("%1").arg(value, 2, 10, QChar('0')));
    ff7->setSnowboardTime(s, 0, time);
}

void BlackChocobo::sbSnowBegSec_valueChanged(int value)
{
    if (load)
        return;
    QString time = ff7->snowboardTime(s, 0);
    time.replace(2, 2, QString("%1").arg(value, 2, 10, QChar('0')));
    ff7->setSnowboardTime(s, 0, time);
}

void BlackChocobo::sbSnowBegMsec_valueChanged(int value)
{
    if (load)
        return;
    QString time = ff7->snowboardTime(s, 0);
    time.replace(4, 3, QString("%1").arg(value, 3, 10, QChar('0')));
    ff7->setSnowboardTime(s, 0, time);
}

void BlackChocobo::sbSnowExpMin_valueChanged(int value)
{
    if (load)
        return;
    QString time = ff7->snowboardTime(s, 1);
    time.replace(0, 2, QString("%1").arg(value, 2, 10, QChar('0')));
    ff7->setSnowboardTime(s, 1, time);
}

void BlackChocobo::sbSnowExpSec_valueChanged(int value)
{
    if (load)
        return;
    QString time = ff7->snowboardTime(s, 1);
    time.replace(2, 2, QString("%1").arg(value, 2, 10, QChar('0')));
    ff7->setSnowboardTime(s, 1, time);
}

void BlackChocobo::sbSnowExpMsec_valueChanged(int value)
{
    if (load)
        return;
    QString time = ff7->snowboardTime(s, 1);
    time.replace(4, 3, QString("%1").arg(value, 3, 10, QChar('0')));
    ff7->setSnowboardTime(s, 1, time);

}

void BlackChocobo::sbSnowCrazyMin_valueChanged(int value)
{
    if (load)
        return;
    QString time = ff7->snowboardTime(s, 2);
    time.replace(0, 2, QString("%1").arg(value, 2, 10, QChar('0')));
    ff7->setSnowboardTime(s, 2, time);
}

void BlackChocobo::sbSnowCrazySec_valueChanged(int value)
{
    if (load)
        return;
    QString time = ff7->snowboardTime(s, 2);
    time.replace(2, 2, QString("%1").arg(value, 2, 10, QChar('0')));
    ff7->setSnowboardTime(s, 2, time);
}

void BlackChocobo::sbSnowCrazyMsec_valueChanged(int value)
{
    if (load)
        return;
    QString time = ff7->snowboardTime(s, 2);
    time.replace(4, 3, QString("%1").arg(value, 3, 10, QChar('0')));
    ff7->setSnowboardTime(s, 2, time);
}

void BlackChocobo::sbBikeHighScore_valueChanged(int arg1)
{
    if (load)
        return;
    ff7->setBikeHighScore(s, quint16(arg1));
}

void BlackChocobo::sbBattlePoints_valueChanged(int arg1)
{
    if (load)
        return;
    ff7->setBattlePoints(s, quint16(arg1));
}

void BlackChocobo::sbBattleSWins_valueChanged(int arg1)
{
    if (load)
        return;
    ff7->setSpecialBattleWins(s, quint8(arg1));
}

void BlackChocobo::comboHexEditor_currentIndexChanged(int index)
{
    hexTabUpdate(index);
}

void BlackChocobo::comboSlotRegionChanged(int index)
{
    auto region = ff7->region(s);
    if(!load) {
        switch(index) {
            case 0: ui->actionRegionUSA->trigger(); break;
            case 1: ui->actionRegionPALGeneric->trigger(); break;
            case 2: ui->actionRegionPALFrench->trigger(); break;
            case 3: ui->actionRegionPALGerman->trigger(); break;
            case 4: ui->actionRegionPALSpanish->trigger(); break;
            case 5: ui->actionRegionJPN->trigger(); break;
            case 6: ui->actionRegionJPNInternational->trigger(); break;
        }
    }
    if (region != ff7->region(s))
        hexTabUpdate(ui->comboHexEditor->currentIndex());
}

void BlackChocobo::hexEditorChanged(void)
{
    if (FF7SaveInfo::isTypePC(ff7->format())) {
        ff7->setSlotFF7Data(s, hexEditor->data());
    } else {
        switch (ui->comboHexEditor->currentIndex()) {
        case 0:
            ff7->setSlotPsxRawData(s, hexEditor->data());
            update_hexEditor_PSXInfo();
            break;
        case 1:
            ff7->setSlotFF7Data(s, hexEditor->data());
            break;
        }
    }
    fileModified(true);
}

void BlackChocobo::phsList_box_allowed_toggled(int row, bool checked)
{
    if (load)
        return;
    ff7->setPhsAllowed(s, row, !checked);
}

void BlackChocobo::phsList_box_visible_toggled(int row, bool checked)
{
    if (load)
        return;
    ff7->setPhsVisible(s, row, checked);
}

void BlackChocobo::menuList_box_locked_toggled(int row, bool checked)
{
    if (load)
        return;
    ff7->setMenuLocked(s, row, checked);
}

void BlackChocobo::menuList_box_visible_toggled(int row, bool checked)
{
    if (load)
        return;
    ff7->setMenuVisible(s, row, checked);
}

void BlackChocobo::locationToolBox_currentChanged(int index)
{
    //LocationTabs
    load = true;
    switch (index) {
    case 0:
        locationViewer->setX(ff7->locationX(s));
        locationViewer->setY(ff7->locationY(s));
        locationViewer->setT(ff7->locationT(s));
        locationViewer->setD(ff7->locationD(s));
        locationViewer->setMapId(ff7->mapId(s));
        locationViewer->setLocationId(ff7->locationId(s));
        locationViewer->setLocationString(ff7->location(s));
        locationViewer->init_fieldItems();
        break;

    case 1:
        ui->cbVisibleBuggy->setChecked(ff7->worldVehicle(s, FF7Save::WVEHCILE_BUGGY));
        ui->cbVisibleBronco->setChecked(ff7->worldVehicle(s, FF7Save::WVEHCILE_TBRONCO));
        ui->cbVisibleHighwind->setChecked(ff7->worldVehicle(s, FF7Save::WVEHCILE_HIGHWIND));
        ui->cbVisibleWildChocobo->setChecked(ff7->worldChocobo(s, FF7Save::WCHOCO_WILD));
        ui->cbVisibleYellowChocobo->setChecked(ff7->worldChocobo(s, FF7Save::WCHOCO_YELLOW));
        ui->cbVisibleGreenChocobo->setChecked(ff7->worldChocobo(s, FF7Save::WCHOCO_GREEN));
        ui->cbVisibleBlueChocobo->setChecked(ff7->worldChocobo(s, FF7Save::WCHOCO_BLUE));
        ui->cbVisibleBlackChocobo->setChecked(ff7->worldChocobo(s, FF7Save::WCHOCO_BLACK));
        ui->cbVisibleGoldChocobo->setChecked(ff7->worldChocobo(s, FF7Save::WCHOCO_GOLD));

        switch (ui->comboMapControls->currentIndex()) {
        case 0: ui->slideWorldX->setValue(ff7->worldCoordsLeaderX(s));
            ui->slideWorldY->setValue(ff7->worldCoordsLeaderY(s));
            break;
        case 1: ui->slideWorldX->setValue(ff7->worldCoordsTcX(s));
            ui->slideWorldY->setValue(ff7->worldCoordsTcY(s));
            break;
        case 2:  ui->slideWorldX->setValue(ff7->worldCoordsBhX(s));
            ui->slideWorldY->setValue(ff7->worldCoordsBhY(s));
            break;
        case 3: ui->slideWorldX->setValue(ff7->worldCoordsSubX(s));
            ui->slideWorldY->setValue(ff7->worldCoordsSubY(s));
            break;
        case 4: ui->slideWorldX->setValue(ff7->worldCoordsWchocoX(s));
            ui->slideWorldY->setValue(ff7->worldCoordsWchocoY(s));
            break;
        case 5: ui->slideWorldX->setValue(ff7->worldCoordsDurwX(s));
            ui->slideWorldY->setValue(ff7->worldCoordsDurwY(s));
            break;
        }
        //WORLD TAB
        ui->sbLeaderId->setValue(ff7->worldCoordsLeaderID(s));
        ui->sbLeaderX->setValue(ff7->worldCoordsLeaderX(s));
        ui->sbLeaderAngle->setValue(ff7->worldCoordsLeaderAngle(s));
        ui->sbLeaderY->setValue(ff7->worldCoordsLeaderY(s));
        ui->sbLeaderZ->setValue(ff7->worldCoordsLeaderZ(s));

        ui->sbDurwX->setValue(ff7->worldCoordsDurwX(s));
        ui->sbDurwId->setValue(ff7->worldCoordsDurwID(s));
        ui->sbDurwAngle->setValue(ff7->worldCoordsDurwAngle(s));
        ui->sbDurwY->setValue(ff7->worldCoordsDurwY(s));
        ui->sbDurwZ->setValue(ff7->worldCoordsDurwZ(s));

        ui->sbWcX->setValue(ff7->worldCoordsWchocoX(s));
        ui->sbWcId->setValue(ff7->worldCoordsWchocoID(s));
        ui->sbWcAngle->setValue(ff7->worldCoordsWchocoAngle(s));
        ui->sbWcY->setValue(ff7->worldCoordsWchocoY(s));
        ui->sbWcZ->setValue(ff7->worldCoordsWchocoZ(s));

        ui->sbTcX->setValue(ff7->worldCoordsTcX(s));
        ui->sbTcId->setValue(ff7->worldCoordsTcID(s));
        ui->sbTcAngle->setValue(ff7->worldCoordsTcAngle(s));
        ui->sbTcY->setValue(ff7->worldCoordsTcY(s));
        ui->sbTcZ->setValue(ff7->worldCoordsTcZ(s));

        ui->sbBhX->setValue(ff7->worldCoordsBhX(s));
        ui->sbBhId->setValue(ff7->worldCoordsBhID(s));

        switch (ui->sbBhId->value()) {
        case 0: ui->comboHighwindBuggy->setCurrentIndex(0); break; //empty
        case 6: ui->comboHighwindBuggy->setCurrentIndex(1); break; //buggy
        case 3: ui->comboHighwindBuggy->setCurrentIndex(2); break; //highwind
        default: QMessageBox::information(this, tr("Black Chocobo"), tr("Unknown Id in Buggy/Highwind Location")); break;
        }

        ui->sbBhAngle->setValue(ff7->worldCoordsBhAngle(s));
        ui->sbBhY->setValue(ff7->worldCoordsBhY(s));
        ui->sbBhZ->setValue(ff7->worldCoordsBhZ(s));

        ui->sbSubX->setValue(ff7->worldCoordsSubX(s));
        ui->sbSubId->setValue(ff7->worldCoordsSubID(s));
        ui->sbSubAngle->setValue(ff7->worldCoordsSubAngle(s));
        ui->sbSubY->setValue(ff7->worldCoordsSubY(s));
        ui->sbSubZ->setValue(ff7->worldCoordsSubZ(s));
        break;
    }
    load = false;
}

void BlackChocobo::testDataTabWidget_currentChanged(int index)
{
    switch (index) {
    case 0:
        load = true;
        ui->sbBloveAeris->setValue(ff7->love(s, true, FF7Save::LOVE_AERIS));
        ui->sbBloveTifa->setValue(ff7->love(s, true, FF7Save::LOVE_TIFA));
        ui->sbBloveYuffie->setValue(ff7->love(s, true, FF7Save::LOVE_YUFFIE));
        ui->sbBloveBarret->setValue(ff7->love(s, true, FF7Save::LOVE_BARRET));
        ui->sbUweaponHp->setValue(int(ff7->uWeaponHp(s)));
        ui->cbTutSub->setChecked(ff7->tutSub(s, 2));

        ui->lcdTutSub->display(ff7->tutSub(s));

        if (ff7->tutSave(s) == 0x3A)
            ui->cbTutWorldSave->setCheckState(Qt::Checked);
        else if (ff7->tutSave(s) == 0x32)
            ui->cbTutWorldSave->setCheckState(Qt::PartiallyChecked);
        else
            ui->cbTutWorldSave->setCheckState(Qt::Unchecked);

        ui->lcdNumber_7->display(ff7->tutSave(s));

        ui->cbRegYuffie->setChecked(ff7->yuffieUnlocked(s));
        ui->cbRegVinny->setChecked(ff7->vincentUnlocked(s));

        ui->sbSaveMapId->setValue(ff7->craterSavePointMapID(s));
        ui->sbSaveX->setValue(ff7->craterSavePointX(s));
        ui->sbSaveY->setValue(ff7->craterSavePointY(s));
        ui->sbSaveZ->setValue(ff7->craterSavePointZ(s));

        load = false;
        break;

    case 1: unknown_refresh(ui->comboZVar->currentIndex()); break;
    }
}

void BlackChocobo::sbCondorFunds_valueChanged(int arg1)
{
    if (load)
        return;
    ff7->setCondorFunds(s, quint16(arg1));
}

void BlackChocobo::sbCondorWins_valueChanged(int arg1)
{
    if (load)
        return;
    ff7->setCondorWins(s, quint8(arg1));
}

void BlackChocobo::sbCondorLosses_valueChanged(int arg1)
{
    if (load)
        return;
    ff7->setCondorLosses(s, quint8(arg1));
}

void BlackChocobo::cbPandorasBox_toggled(bool checked)
{
    if (load)
        return;
    ff7->setSeenPandorasBox(s, checked);
}

void BlackChocobo::cbSubGameWon_toggled(bool checked)
{
    if (load)
        return;
    ff7->setSubMiniGameVictory(s, checked);
}

void BlackChocobo::connectFieldItem(quint8 boxID, QList<quint16>Offset, QList<quint8> Bit)
{
    if (boxID == 0) {
        //if box is 0 then new list.
        fieldItemOffset = new QList<fieldItemOffsetList>;
        fieldItemBit = new QList<fieldItemBitList>;
    }
    fieldItemOffset->append(Offset);
    fieldItemBit->append(Bit);
}

void BlackChocobo::checkFieldItem(int boxID)
{
    //Will always be called in numerical Order
    fieldItemOffsetList offsetList = fieldItemOffset->at(boxID);
    fieldItemBitList bitList = fieldItemBit->at(boxID);

    if (offsetList.count() == bitList.count()) {
        bool checked = false;
        bool check1 = false;
        for (int i = 0; i < offsetList.count(); i++) {
            //attempt to cope with multi bits.
            int offset = offsetList.at(i);
            int bit = bitList.at(i);
            if ((ff7->slotFF7Data(s).at(offset) & (1 << bit)))
                check1 = true;
            else
                check1 = false;

            if (i == 0)
                checked = check1;
            else
                checked = (check1 & checked);
        }
        locationViewer->setFieldItemChecked(boxID, checked);
    }
}

void BlackChocobo::fieldItemStateChanged(int boxID, bool checked)
{
    fieldItemOffsetList offsetList = fieldItemOffset->at(boxID);
    fieldItemBitList bitList = fieldItemBit->at(boxID);
    if (offsetList.count() == bitList.count()) {
        for (int i = 0; i < offsetList.count(); i++) {
            int offset = offsetList.at(i);
            int bit = bitList.at(i);
            QByteArray temp = ff7->slotFF7Data(s); char t = temp.at(offset);
            if (checked)
                t |= (1 << bit);
            else
                t &= ~(1 << bit);

            temp[offset] = t;
            ff7->setSlotFF7Data(s, temp);
        }
    }
}

void BlackChocobo::sbSaveMapId_valueChanged(int arg1)
{
    if (load)
        return;
    ff7->setCraterSavePointMapID(s, arg1);
}

void BlackChocobo::sbSaveX_valueChanged(int arg1)
{
    if (load)
        return;
    ff7->setCraterSavePointX(s, arg1);
}

void BlackChocobo::sbSaveY_valueChanged(int arg1)
{
    if (load)
        return;
    ff7->setCraterSavePointY(s, arg1);
}

void BlackChocobo::sbSaveZ_valueChanged(int arg1)
{
    if (load)
        return;
    ff7->setCraterSavePointZ(s, arg1);
}

void BlackChocobo::searchForFlyers()
{
    ui->tabWidget->setCurrentIndex(4);
    ui->locationToolBox->setCurrentIndex(0);
    locationViewer->setFilterString(tr("Turtle Paradise"), LocationViewer::ITEM);
}

void BlackChocobo::searchForKeyItems()
{
    ui->tabWidget->setCurrentIndex(4);
    ui->locationToolBox->setCurrentIndex(0);
    locationViewer->setFilterString(tr("KeyItem"), LocationViewer::ITEM);
}

void BlackChocobo::linePsxDesc_textChanged(const QString &arg1)
{
    if (load)
        return;
    ff7->setPsxDesc(arg1, s);
    update_hexEditor_PSXInfo();
}

void BlackChocobo::cbFlashbackPiano_toggled(bool checked)
{
    if (load)
        return;
    ff7->setPlayedPianoOnFlashback(s, checked);
}

void BlackChocobo::setButtonMapping(int controlAction, int newButton)
{
    if (load)
        return;
    ff7->setControllerMapping(s, controlAction, newButton);
}
