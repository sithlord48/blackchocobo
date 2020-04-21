/****************************************************************************/
//    copyright 2010-2020 Chris Rizzitello <sithlord48@gmail.com>           //
//                                                                          //
//    This file is part of Black Chocobo.                                   //
//                                                                          //
//    Black Chocobo is free software: you can redistribute it and/or modify //
//    it under the terms of the GNU General Public License as published by  //
//    the Free Software Foundation, either version 3 of the License, or     //
//    (at your option) any later version.                                   //
//                                                                          //
//    Black Chocobo is distributed in the hope that it will be useful,      //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of        //
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
//    GNU General Public License for more details.                          //
/****************************************************************************/
/*~~~~~~~~~~~Includes~~~~~~~~*/
#include <QString>
#include <QScrollBar>
#include <QMessageBox>
#include <QDesktopWidget>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ff7tk/data/FF7Char.h"
#include "ff7tk/data/FF7Item.h"
#include "ff7tk/data/FF7Location.h"
#include "bcdialog.h"
#include "bcsettings.h"
/*~~~~~~~~GUI Set Up~~~~~~~*/
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , hexCursorPos(0)
    , _init(true)
    , load(true)
    , ff7(new FF7Save)
    , s(0)
    , curchar(0)
    , mslotsel(-1)
    , phsList(new PhsListWidget)
    , menuList(new MenuListWidget)
    , optionsWidget(new OptionsWidget)
    , materia_editor(new MateriaEditor(this))
    , hexEditor(new QHexEdit)
    , chocoboManager(new ChocoboManager)
{
//Initilze Remaining Data
    buffer_materia.id = FF7Materia::EmptyId;
    for (int i = 0; i < 3; i++)
        buffer_materia.ap[i] = 0xFF;   //empty buffer incase

    setAcceptDrops(true);
    ui->setupUi(this);
    loadBasicSettings();
    populateLanguageMenu();
    initDisplay();
    setScale(BCSettings::instance()->value(SETTINGS::SCALE).toDouble());
    populateCombos();
    init_style();
    loadChildWidgetSettings();
    init_connections();
    on_actionNew_Game_triggered();
    ui->btn_cloud->clicked();
    ff7->setFileModified(false, 0);
}

void MainWindow::populateLanguageMenu()
{
    m_translations.clear();
    QDir dir(QStringLiteral("%1/lang").arg(BCSettings::instance()->value(SETTINGS::LANGPATH).toString()));
    QStringList langList = dir.entryList(QStringList("bchoco_*.qm"), QDir::Files, QDir::Name);
    for (const QString &translation : langList) {
        QTranslator *translator = new QTranslator;
        translator->load(translation, dir.absolutePath());
        QString lang = translation.mid(7, 2);
        m_translations.insert(lang, translator);
        bool currentLang = (BCSettings::instance()->value(SETTINGS::LANG, QStringLiteral("en")).toString() == lang);
        if (currentLang) {
            BCSettings::instance()->setValue(SETTINGS::LANG, lang);
            QApplication::installTranslator(translator);
        }
    }
}

void MainWindow::initDisplay()
{
    ui->linePsxDesc->setReadOnly(true);

    QHBoxLayout *phsLayout = new QHBoxLayout;
    phsLayout->addWidget(phsList);
    ui->Phs_Box->setLayout(phsLayout);

    QHBoxLayout *menuLayout = new QHBoxLayout;
    menuLayout->addWidget(menuList);
    ui->Menu_Box->setLayout(menuLayout);

    chocoboManager->setContentsMargins(0, 20, 0, 0);
    ui->tabWidget->insertTab(3, chocoboManager, tr("Chocobo"));
    ui->tabWidget->insertTab(7, optionsWidget, tr("Game Options"));

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

    double scale = BCSettings::instance()->value(SETTINGS::SCALE).toDouble();
    char_editor = new CharEditor(scale);
    QHBoxLayout *char_editor_layout = new QHBoxLayout;
    char_editor_layout->setContentsMargins(0, 0, 0, 0);
    char_editor_layout->setSpacing(0);
    char_editor_layout->addWidget(char_editor);
    ui->group_char_editor_box->setLayout(char_editor_layout);

    itemlist = new ItemList(scale);
    ui->group_items->layout()->removeWidget(ui->group_item_options);
    ui->group_items->layout()->addWidget(itemlist);
    ui->group_items->layout()->addWidget(ui->group_item_options);
    ui->group_items->setFixedWidth(itemlist->width() + itemlist->contentsMargins().left() + itemlist->contentsMargins().right() + ui->group_items->contentsMargins().left() + ui->group_items->contentsMargins().right());

    locationViewer = new LocationViewer(scale);
    locationViewer->setTranslationBaseFile(QStringLiteral("%1/lang/bchoco_").arg(BCSettings::instance()->value(SETTINGS::LANGPATH).toString()));
    locationViewer->setRegion("BASCUS-94163FF7-S00");
    QVBoxLayout *locLayout = new QVBoxLayout;
    locLayout->setContentsMargins(0, 0, 0, 0);
    locLayout->addWidget(locationViewer);
    ui->fieldFrame->setLayout(locLayout);

    ui->statusBar->addWidget(ui->frame_status, 1);
    ui->frame_status->setFixedHeight(fontMetrics().height() + 2);
    ui->tbl_materia->setIconSize(QSize(fontMetrics().height(), fontMetrics().height()));
    ui->tbl_unknown->setColumnWidth(0, fontMetrics().horizontalAdvance(QStringLiteral("WW")));
    ui->tbl_unknown->setColumnWidth(1, fontMetrics().horizontalAdvance(QStringLiteral("W")));
    ui->tbl_unknown->setColumnWidth(2, fontMetrics().horizontalAdvance(QStringLiteral("W")));
    ui->tbl_unknown->setColumnWidth(3, fontMetrics().horizontalAdvance(QStringLiteral("WWWWWW")));
    ui->tbl_unknown->setColumnWidth(4, fontMetrics().horizontalAdvance(QStringLiteral("W")));

    ui->tbl_compare_unknown->setColumnWidth(0, fontMetrics().horizontalAdvance(QStringLiteral("WW")));
    ui->tbl_compare_unknown->setColumnWidth(1, fontMetrics().horizontalAdvance(QStringLiteral("W")));
    ui->tbl_compare_unknown->setColumnWidth(2, fontMetrics().horizontalAdvance(QStringLiteral("W")));
    ui->tbl_compare_unknown->setColumnWidth(3, fontMetrics().horizontalAdvance(QStringLiteral("WWWWWW")));
    ui->tbl_compare_unknown->setColumnWidth(4, fontMetrics().horizontalAdvance(QStringLiteral("W")));

    int width = 0;
    for(int i = 0; i < 5; i++)
        width += ui->tbl_unknown->columnWidth(i);

    width +=ui->tbl_unknown->verticalScrollBar()->width();
    ui->table_unknown->setFixedWidth(width);
    ui->tbl_unknown->setFixedWidth(width);

    width -=ui->tbl_unknown->verticalScrollBar()->width();
    ui->compare_table->setFixedWidth(width);
    ui->tbl_compare_unknown->setFixedWidth(width);
}

void MainWindow::setScale(double scale)
{
    scale = std::max(scale, 0.5);
    setStyleSheet(QString("QCheckBox::indicator{width: %1px; height: %1px; padding: -%2px;}\nQListWidget::indicator{width: %1px; height: %1px; padding: -%2px}").arg(fontMetrics().height()).arg(2 * scale));
    ui->btn_cloud->setFixedSize(int(98 * scale), int(110 * scale));
    ui->btn_cloud->setIconSize(QSize(int(92 * scale), int(104 * scale)));
    ui->btn_barret->setIconSize(QSize(int(92 * scale), int(104 * scale)));
    ui->btn_barret->setFixedSize(int(98 * scale), int(110 * scale));
    ui->btn_tifa->setIconSize(QSize(int(92 * scale), int(104 * scale)));
    ui->btn_tifa->setFixedSize(int(98 * scale), int(110 * scale));
    ui->btn_aeris->setFixedSize(int(98 * scale), int(110 * scale));
    ui->btn_aeris->setIconSize(QSize(int(92 * scale), int(104 * scale)));
    ui->btn_red->setFixedSize(int(98 * scale), int(110 * scale));
    ui->btn_red->setIconSize(QSize(int(92 * scale), int(104 * scale)));
    ui->btn_yuffie->setFixedSize(int(98 * scale), int(110 * scale));
    ui->btn_yuffie->setIconSize(QSize(int(92 * scale), int(104 * scale)));
    ui->btn_cait->setFixedSize(int(98 * scale), int(110 * scale));
    ui->btn_cait->setIconSize(QSize(int(92 * scale), int(104 * scale)));
    ui->btn_vincent->setFixedSize(int(98 * scale), int(110 * scale));
    ui->btn_vincent->setIconSize(QSize(int(92 * scale), int(104 * scale)));
    ui->btn_cid->setFixedSize(int(98 * scale), int(110 * scale));
    ui->btn_cid->setIconSize(QSize(int(92 * scale), int(104 * scale)));
    ui->combo_party1->setFixedHeight(int(32 * scale));
    ui->combo_party1->setIconSize(QSize(int(32 * scale), int(32 * scale)));
    ui->combo_party2->setFixedHeight(int(32 * scale));
    ui->combo_party2->setIconSize(QSize(int(32 * scale), int(32 * scale)));
    ui->combo_party3->setFixedHeight(int(32 * scale));
    ui->combo_party3->setIconSize(QSize(int(32 * scale), int(32 * scale)));
    ui->groupBox_11->setFixedWidth(int(375 * scale));
    ui->groupBox_18->setFixedWidth(int(273 * scale)); //materia table group.
    ui->scrollArea->setFixedWidth(int(310 * scale));
    ui->scrollAreaWidgetContents->adjustSize();
    ui->world_map_frame->setFixedSize(int(446 * scale), int(381 * scale));
    ui->world_map_view->setPixmap(QPixmap(":/icon/world_map").scaled(ui->world_map_frame->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->world_map_view->setGeometry(int(5 * scale), int(32 * scale), int(432 * scale), int(336 * scale));
    ui->combo_map_controls->setFixedHeight(32);
    ui->slide_world_x->setGeometry(-1, int(369 * scale), int(443 * scale), int(10 * scale));
    ui->slide_world_y->setGeometry(int(437 * scale), int(26 * scale), int(10 * scale), int(347 * scale));
    ui->lbl_love_aeris->setFixedSize(int(50 * scale), int(68 * scale));
    ui->lbl_love_aeris->setPixmap(FF7Char::instance()->pixmap(FF7Char::Aerith).scaled(ui->lbl_love_aeris->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->lbl_love_barret->setFixedSize(int(50 * scale), int(68 * scale));
    ui->lbl_love_barret->setPixmap(FF7Char::instance()->pixmap(FF7Char::Barret).scaled(ui->lbl_love_barret->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->lbl_love_tifa->setFixedSize(int(50 * scale), int(68 * scale));
    ui->lbl_love_tifa->setPixmap(FF7Char::instance()->pixmap(FF7Char::Tifa).scaled(ui->lbl_love_tifa->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->lbl_love_yuffie->setFixedSize(int(50 * scale), int(68 * scale));
    ui->lbl_love_yuffie->setPixmap(FF7Char::instance()->pixmap(FF7Char::Yuffie).scaled(ui->lbl_love_yuffie->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->lbl_battle_love_aeris->setFixedSize(ui->sb_b_love_aeris->width(), int(74 * scale));
    ui->lbl_battle_love_aeris->setPixmap(FF7Char::instance()->pixmap(FF7Char::Aerith).scaled(ui->lbl_battle_love_aeris->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->lbl_battle_love_barret->setFixedSize(ui->sb_b_love_barret->width(), int(74 * scale));
    ui->lbl_battle_love_barret->setPixmap(FF7Char::instance()->pixmap(FF7Char::Barret).scaled(ui->lbl_battle_love_barret->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->lbl_battle_love_tifa->setFixedSize(ui->sb_b_love_tifa->width(), int(74 * scale));
    ui->lbl_battle_love_tifa->setPixmap(FF7Char::instance()->pixmap(FF7Char::Tifa).scaled(ui->lbl_battle_love_tifa->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->lbl_battle_love_yuffie->setFixedSize(ui->sb_b_love_yuffie->width(), int(74 * scale));
    ui->lbl_battle_love_yuffie->setPixmap(FF7Char::instance()->pixmap(FF7Char::Yuffie).scaled(ui->lbl_battle_love_yuffie->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    materia_editor->setStarsSize(int(48 * scale));
    guirefresh(0);
}

void MainWindow::populateCombos()
{
//Party Combos
    if (ui->combo_party1->count() != 0) {
        for (int i = 0; i < 11; i++) {
            ui->combo_party1->setItemText(i, FF7Char::instance()->defaultName(i));
            ui->combo_party2->setItemText(i, FF7Char::instance()->defaultName(i));
            ui->combo_party3->setItemText(i, FF7Char::instance()->defaultName(i));
        }
        ui->combo_party1->setItemText(12, tr("-Empty-"));
        ui->combo_party2->setItemText(12, tr("-Empty-"));
        ui->combo_party3->setItemText(12, tr("-Empty-"));
    } else {
        for (int i = 0; i < 11; i++) {
            ui->combo_party1->addItem(FF7Char::instance()->icon(i), FF7Char::instance()->defaultName(i));
            ui->combo_party2->addItem(FF7Char::instance()->icon(i), FF7Char::instance()->defaultName(i));
            ui->combo_party3->addItem(FF7Char::instance()->icon(i), FF7Char::instance()->defaultName(i));
        }
        ui->combo_party1->addItem(QString("0x0B"));
        ui->combo_party2->addItem(QString("0x0B"));
        ui->combo_party3->addItem(QString("0x0B"));
        ui->combo_party1->addItem(tr("-Empty-"));
        ui->combo_party2->addItem(tr("-Empty-"));
        ui->combo_party3->addItem(tr("-Empty-"));
    }
//World party leader Combo.
    if (ui->cb_world_party_leader->count() != 0) {
        ui->cb_world_party_leader->setItemText(0, FF7Char::instance()->defaultName(FF7Char::Cloud));
        ui->cb_world_party_leader->setItemText(1, FF7Char::instance()->defaultName(FF7Char::Tifa));
        ui->cb_world_party_leader->setItemText(2, FF7Char::instance()->defaultName(FF7Char::Cid));
    } else {
        ui->cb_world_party_leader->addItem(FF7Char::instance()->icon(FF7Char::Cloud), FF7Char::instance()->defaultName(FF7Char::Cloud));
        ui->cb_world_party_leader->addItem(FF7Char::instance()->icon(FF7Char::Tifa), FF7Char::instance()->defaultName(FF7Char::Tifa));
        ui->cb_world_party_leader->addItem(FF7Char::instance()->icon(FF7Char::Cid), FF7Char::instance()->defaultName(FF7Char::Cid));
    }
}

void MainWindow::init_style()
{
    QString sliderStyleSheet("QSlider:sub-page{background-color: qlineargradient(spread:pad, x1:0.472, y1:0.011, x2:0.483, y2:1, stop:0 rgba(186, 1, 87,192), stop:0.505682 rgba(209, 128, 173,192), stop:0.931818 rgba(209, 44, 136, 192));}");
    sliderStyleSheet.append(QString("QSlider::add-page{background: qlineargradient(spread:pad, x1:0.5, y1:0.00568182, x2:0.497, y2:1, stop:0 rgba(91, 91, 91, 255), stop:0.494318 rgba(122, 122, 122, 255), stop:1 rgba(106, 106, 106, 255));}"));
    sliderStyleSheet.append(QString("QSlider{border:3px solid;border-left-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(123, 123, 123, 255), stop:1 rgba(172, 172, 172, 255));border-right-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(123, 123, 123, 255), stop:1 rgba(172, 172, 172, 255));border-bottom-color: rgb(172, 172, 172);border-top-color: rgb(172, 172, 172);border-radius: 5px;}"));
    sliderStyleSheet.append(QString("QSlider::groove{height: 12px;background: qlineargradient(spread:pad, x1:0.5, y1:0.00568182, x2:0.497, y2:1, stop:0 rgba(91, 91, 91, 255), stop:0.494318 rgba(122, 122, 122, 255), stop:1 rgba(106, 106, 106, 255));}"));
    sliderStyleSheet.append(QString("QSlider::handle{background: rgba(172, 172, 172,255);border: 1px solid #5c5c5c;width: 3px;border-radius: 2px;}"));
    char_editor->setSliderStyle(sliderStyleSheet);

    QString tabStyle = QString("::tab:hover{background-color:rgba(%1, %2, %3, 128);}").arg(QString::number(this->palette().highlight().color().red()), QString::number(this->palette().highlight().color().green()), QString::number(this->palette().highlight().color().blue()));
    char_editor->setToolBoxStyle(tabStyle);
    ui->locationToolBox->setStyleSheet(tabStyle);

    ui->slide_world_y->setStyleSheet(QString("::handle{image: url(:/icon/prev);}"));
    ui->slide_world_x->setStyleSheet(QString("::handle{image: url(:/icon/slider_up);}"));
}

void MainWindow::init_connections()
{
    connect(ui->tbl_unknown->verticalScrollBar(), &QScrollBar::valueChanged, ui->tbl_compare_unknown->verticalScrollBar(), &QScrollBar::setValue);
    connect(ui->tbl_compare_unknown->verticalScrollBar(), &QScrollBar::valueChanged, ui->tbl_unknown->verticalScrollBar(), &QScrollBar::setValue);

    connect(ff7, &FF7Save::fileChanged, this, &MainWindow::fileModified);

    connect(itemlist, &ItemList::itemsChanged, this, &MainWindow::Items_Changed);

    connect(materia_editor, &MateriaEditor::apChanged, this, &MainWindow::materia_ap_changed);
    connect(materia_editor, &MateriaEditor::idChanged, this, &MainWindow::materia_id_changed);

    connect(phsList, &PhsListWidget::allowedToggled, this, &MainWindow::phsList_box_allowed_toggled);
    connect(phsList, &PhsListWidget::visibleToggled, this, &MainWindow::phsList_box_visible_toggled);

    connect(menuList, &MenuListWidget::lockedToggled, this, &MainWindow::menuList_box_locked_toggled);
    connect(menuList, &MenuListWidget::visibleToggled, this, &MainWindow::menuList_box_visible_toggled);

    connect(char_editor, &CharEditor::id_changed, this, &MainWindow::char_id_changed);
    connect(char_editor, &CharEditor::level_changed, this, &MainWindow::char_level_changed);
    connect(char_editor, &CharEditor::str_changed, this, &MainWindow::char_str_changed);
    connect(char_editor, &CharEditor::vit_changed, this, &MainWindow::char_vit_changed);
    connect(char_editor, &CharEditor::mag_changed, this, &MainWindow::char_mag_changed);
    connect(char_editor, &CharEditor::spi_changed, this, &MainWindow::char_spi_changed);
    connect(char_editor, &CharEditor::dex_changed, this, &MainWindow::char_dex_changed);
    connect(char_editor, &CharEditor::lck_changed, this, &MainWindow::char_lck_changed);
    connect(char_editor, &CharEditor::strBonus_changed, this, &MainWindow::char_strBonus_changed);
    connect(char_editor, &CharEditor::vitBonus_changed, this, &MainWindow::char_vitBonus_changed);
    connect(char_editor, &CharEditor::magBonus_changed, this, &MainWindow::char_magBonus_changed);
    connect(char_editor, &CharEditor::spiBonus_changed, this, &MainWindow::char_spiBonus_changed);
    connect(char_editor, &CharEditor::dexBonus_changed, this, &MainWindow::char_dexBonus_changed);
    connect(char_editor, &CharEditor::lckBonus_changed, this, &MainWindow::char_lckBonus_changed);
    connect(char_editor, &CharEditor::limitLevel_changed, this, &MainWindow::char_limitLevel_changed);
    connect(char_editor, &CharEditor::limitBar_changed, this, &MainWindow::char_limitBar_changed);
    connect(char_editor, &CharEditor::name_changed, this, &MainWindow::char_name_changed);
    connect(char_editor, &CharEditor::weapon_changed, this, &MainWindow::char_weapon_changed);
    connect(char_editor, &CharEditor::armor_changed, this, &MainWindow::char_armor_changed);
    connect(char_editor, &CharEditor::accessory_changed, this, &MainWindow::char_accessory_changed);
    connect(char_editor, &CharEditor::curHp_changed, this, &MainWindow::char_curHp_changed);
    connect(char_editor, &CharEditor::maxHp_changed, this, &MainWindow::char_maxHp_changed);
    connect(char_editor, &CharEditor::curMp_changed, this, &MainWindow::char_curMp_changed);
    connect(char_editor, &CharEditor::maxMp_changed, this, &MainWindow::char_maxMp_changed);
    connect(char_editor, &CharEditor::kills_changed, this, &MainWindow::char_kills_changed);
    connect(char_editor, &CharEditor::row_changed, this, &MainWindow::char_row_changed);
    connect(char_editor, &CharEditor::levelProgress_changed, this, &MainWindow::char_levelProgress_changed);
    connect(char_editor, &CharEditor::sadnessfury_changed, this, &MainWindow::char_sadnessfury_changed);
    connect(char_editor, &CharEditor::limits_changed, this, &MainWindow::char_limits_changed);
    connect(char_editor, &CharEditor::timesused1_changed, this, &MainWindow::char_timesused1_changed);
    connect(char_editor, &CharEditor::timesused2_changed, this, &MainWindow::char_timeused2_changed);
    connect(char_editor, &CharEditor::timesused3_changed, this, &MainWindow::char_timeused3_changed);
    connect(char_editor, &CharEditor::baseHp_changed, this, &MainWindow::char_baseHp_changed);
    connect(char_editor, &CharEditor::baseMp_changed, this, &MainWindow::char_baseMp_changed);
    connect(char_editor, &CharEditor::exp_changed, this, &MainWindow::char_exp_changed);
    connect(char_editor, &CharEditor::mslotChanged, this, &MainWindow::char_mslot_changed);
    connect(char_editor, &CharEditor::Materias_changed, this, &MainWindow::char_materia_changed);
    connect(char_editor, &CharEditor::expNext_changed, this, &MainWindow::char_expNext_changed);

    connect(chocoboManager, &ChocoboManager::ownedChanged, this, &MainWindow::cm_stablesOwnedChanged);
    connect(chocoboManager, &ChocoboManager::stableMaskChanged, this, &MainWindow::cm_stableMaskChanged);
    connect(chocoboManager, &ChocoboManager::occupiedChanged, this, &MainWindow::cm_stablesOccupiedChanged);
    connect(chocoboManager, &ChocoboManager::nameChanged, this, &MainWindow::cm_nameChanged);
    connect(chocoboManager, &ChocoboManager::cantMateChanged, this, &MainWindow::cm_mated_toggled);
    connect(chocoboManager, &ChocoboManager::speedChanged, this, &MainWindow::cm_speedChanged);
    connect(chocoboManager, &ChocoboManager::mSpeedChanged, this, &MainWindow::cm_maxspeedChanged);
    connect(chocoboManager, &ChocoboManager::sprintChanged, this, &MainWindow::cm_sprintChanged);
    connect(chocoboManager, &ChocoboManager::mSprintChanged, this, &MainWindow::cm_maxsprintChanged);
    connect(chocoboManager, &ChocoboManager::staminaChanged, this, &MainWindow::cm_staminaChanged);
    connect(chocoboManager, &ChocoboManager::sexChanged, this, &MainWindow::cm_sexChanged);
    connect(chocoboManager, &ChocoboManager::typeChanged, this, &MainWindow::cm_typeChanged);
    connect(chocoboManager, &ChocoboManager::accelChanged, this, &MainWindow::cm_accelChanged);
    connect(chocoboManager, &ChocoboManager::coopChanged, this, &MainWindow::cm_coopChanged);
    connect(chocoboManager, &ChocoboManager::intelligenceChanged, this, &MainWindow::cm_intelChanged);
    connect(chocoboManager, &ChocoboManager::personalityChanged, this, &MainWindow::cm_personalityChanged);
    connect(chocoboManager, &ChocoboManager::pCountChanged, this, &MainWindow::cm_pcountChanged);
    connect(chocoboManager, &ChocoboManager::winsChanged, this, &MainWindow::cm_raceswonChanged);
    connect(chocoboManager, &ChocoboManager::penChanged, this, &MainWindow::cm_pensChanged);
    connect(chocoboManager, &ChocoboManager::ratingChanged, this, &MainWindow::cm_ratingChanged);

    connect(locationViewer, &LocationViewer::locationStringChanged, this, &MainWindow::location_textChanged);
    connect(locationViewer, &LocationViewer::locIdChanged, this, &MainWindow::loc_id_valueChanged);
    connect(locationViewer, &LocationViewer::mapIdChanged, this, &MainWindow::map_id_valueChanged);
    connect(locationViewer, &LocationViewer::xChanged, this, &MainWindow::coord_x_valueChanged);
    connect(locationViewer, &LocationViewer::yChanged, this, &MainWindow::coord_y_valueChanged);
    connect(locationViewer, &LocationViewer::tChanged, this, &MainWindow::coord_t_valueChanged);
    connect(locationViewer, &LocationViewer::dChanged, this, &MainWindow::coord_d_valueChanged);
    connect(locationViewer, &LocationViewer::locationChanged, this, &MainWindow::locationSelectionChanged);
    connect(locationViewer, &LocationViewer::fieldItemConnectRequest, this, &MainWindow::connectFieldItem);
    connect(locationViewer, &LocationViewer::fieldItemCheck, this, &MainWindow::checkFieldItem);
    connect(locationViewer, &LocationViewer::fieldItemChanged, this, &MainWindow::fieldItemStateChanged);

    connect(optionsWidget, &OptionsWidget::dialogColorLLChanged, this, &MainWindow::setDialogColorLL);
    connect(optionsWidget, &OptionsWidget::dialogColorLRChanged, this, &MainWindow::setDialogColorLR);
    connect(optionsWidget, &OptionsWidget::dialogColorULChanged, this, &MainWindow::setDialogColorUL);
    connect(optionsWidget, &OptionsWidget::dialogColorURChanged, this, &MainWindow::setDialogColorUR);
    connect(optionsWidget, &OptionsWidget::magicOrderChanged, this, &MainWindow::setMagicOrder);
    connect(optionsWidget, &OptionsWidget::cameraChanged, this, &MainWindow::setCameraMode);
    connect(optionsWidget, &OptionsWidget::atbChanged, this, &MainWindow::setAtbMode);
    connect(optionsWidget, &OptionsWidget::cursorChanged, this, &MainWindow::setCursorMode);
    connect(optionsWidget, &OptionsWidget::controllerModeChanged, this, &MainWindow::setControlMode);
    connect(optionsWidget, &OptionsWidget::soundChanged, this, &MainWindow::setSoundMode);
    connect(optionsWidget, &OptionsWidget::fieldMessageSpeedChanged, this, &MainWindow::setFieldMessageSpeed);
    connect(optionsWidget, &OptionsWidget::battleMessageSpeedChanged, this, &MainWindow::setBattleMessageSpeed);
    connect(optionsWidget, &OptionsWidget::battleSpeedChanged, this, &MainWindow::setBattleSpeed);
    connect(optionsWidget, &OptionsWidget::fieldHelpChanged, this, &MainWindow::setFieldHelp);
    connect(optionsWidget, &OptionsWidget::battleTargetsChanged, this, &MainWindow::setBattleTargets);
    connect(optionsWidget, &OptionsWidget::battleHelpChanged, this, &MainWindow::setBattleHelp);
    connect(optionsWidget, &OptionsWidget::inputChanged, this, &MainWindow::setButtonMapping);
}

void MainWindow::loadBasicSettings()
{
    if (BCSettings::instance()->value(SETTINGS::SCALE).isNull()) {
        double stdDPI = 96.0;
#ifdef Q_OS_MAC
        stdDPI = 72.0;
#endif
        double scale = QString::number(qApp->desktop()->logicalDpiX() / stdDPI, 'f', 2).toDouble();
        double sy = int(scale * 100) % 25;
        scale -= (sy / 100);
        scale = ( sy < 12.49) ? scale : scale + 0.25;
        BCSettings::instance()->setValue(SETTINGS::SCALE, std::max(scale, 0.5));
    }

    if (BCSettings::instance()->value(SETTINGS::MAINGEOMETRY).isNull()) {
        setGeometry(x(), y(), minimumWidth(), minimumHeight());
        saveGeometry();
    }
    restoreGeometry(BCSettings::instance()->value(SETTINGS::MAINGEOMETRY).toByteArray());
}

void MainWindow::loadChildWidgetSettings()
{
    QApplication::setAttribute(Qt::AA_DontUseNativeDialogs, !BCSettings::instance()->value(SETTINGS::USENATIVEDIALOGS, false).toBool());
    for(const QString &url : BCSettings::instance()->value(SETTINGS::SIDEBARURLS).toStringList())
        m_sideBarUrls.append(QUrl::fromLocalFile(url));
    char_editor->setEditableComboBoxes(BCSettings::instance()->value(SETTINGS::EDITABLECOMBOS, true).toBool());
    materia_editor->setEditableMateriaCombo(BCSettings::instance()->value(SETTINGS::EDITABLECOMBOS, true).toBool());
    itemlist->setEditableItemCombo(BCSettings::instance()->value(SETTINGS::EDITABLECOMBOS, true).toBool());
    char_editor->setAdvancedMode(BCSettings::instance()->value(SETTINGS::CHARADVANCED, false).toBool());
    char_editor->setAutoLevel(BCSettings::instance()->value(SETTINGS::AUTOGROWTH, true).toBool());
    char_editor->setAutoStatCalc(BCSettings::instance()->value(SETTINGS::AUTOGROWTH, true).toBool());
    chocoboManager->setAdvancedMode(BCSettings::instance()->value(SETTINGS::CHOCOADVANCED, false).toBool());
    locationViewer->setAdvancedMode(BCSettings::instance()->value(SETTINGS::LOCVIEWADVANCED, false).toBool());
    ui->tabWidget->setTabEnabled(9, BCSettings::instance()->value(SETTINGS::ENABLETEST, false).toBool());
    if (ff7->format() == FF7SaveInfo::FORMAT::PC || ff7->format() == FF7SaveInfo::FORMAT::SWITCH || ff7->format() == FF7SaveInfo::FORMAT::UNKNOWN)
        setControllerMappingVisible(BCSettings::instance()->value(SETTINGS::ALWAYSSHOWCONTROLLERMAP, false).toBool());
    ui->bm_unknown->setVisible(BCSettings::instance()->value(SETTINGS::PROGRESSADVANCED, false).toBool());
    ui->bh_id->setVisible(BCSettings::instance()->value(SETTINGS::WORLDMAPADVANCED, false).toBool());
    ui->leader_id->setVisible(BCSettings::instance()->value(SETTINGS::WORLDMAPADVANCED, false).toBool());
}
/*~~~~~~ END GUI SETUP ~~~~~~~*/
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::PaletteChange) {
        QPalette palette = BCSettings::instance()->paletteForSetting();
        for (QWidget * widget : findChildren<QWidget *>(QString(), Qt::FindChildrenRecursively))
             widget->setPalette(palette);
        hexEditor->setAddressAreaColor(palette.alternateBase().color());
    } else if (e->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
        ui->tabWidget->setTabText(3, tr("Chocobo"));
        ui->tabWidget->setTabText(7, tr("Game Options"));
        populateCombos();
        materiaupdate();
        updateStolenMateria();
        if (ui->psxExtras->isVisible())
            update_hexEditor_PSXInfo();
    }
}
void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
    e->accept();
}
void MainWindow::dropEvent(QDropEvent *e)
{
    if (ff7->isFileModified()) {
        if (!saveChanges())
            return;
    }

    auto mimeData = e->mimeData();
    if (mimeData->hasUrls())
        loadFileFull(mimeData->urls().at(0).toLocalFile(), 0);
}

bool MainWindow::saveChanges(void)
{
    //return 0 to ingore the event/ return 1 to process event.
    int result;
    result = QMessageBox::question(this, tr("Unsaved Changes"), tr("Save Changes to the File:\n%1").arg(ff7->fileName()), QMessageBox::Yes, QMessageBox::No, QMessageBox::Cancel);
    switch (result) {
    case QMessageBox::Yes:
        on_action_Save_triggered();
        return true;
    case QMessageBox::No:
        return true;
    default: return false;
    }
}
void MainWindow::closeEvent(QCloseEvent *e)
{
    if (ff7->isFileModified()) {
        if(!saveChanges())
            e->ignore();
        else
            e->accept();
    }
    BCSettings::instance()->setValue(SETTINGS::MAINGEOMETRY, saveGeometry());
}
void MainWindow::resizeEvent(QResizeEvent *)
{
    BCSettings::instance()->setValue(SETTINGS::MAINGEOMETRY, saveGeometry());
}
void MainWindow::moveEvent(QMoveEvent *)
{
    BCSettings::instance()->setValue(SETTINGS::MAINGEOMETRY, saveGeometry());
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~LOAD/SAVE FUNCTIONS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void MainWindow::on_actionOpen_Save_File_triggered()
{
    if (ff7->isFileModified()) {
        if (!saveChanges())
            return;//cancel load.
    }

    QString fileName = BCDialog::getOpenFileName(this, tr("Open Final Fantasy 7 Save"), BCSettings::instance()->value(SETTINGS::LOADPATH).toString(), FF7SaveInfo::instance()->knownTypesFilter());
    if (!fileName.isEmpty())
        loadFileFull(fileName, 0);
}
void MainWindow::on_actionReload_triggered()
{
    if (!ff7->fileName().isEmpty())
        loadFileFull(ff7->fileName(), 1);
}
/*~~~~~~~~~~~~~~~~~Load Full ~~~~~~~~~~~~~~~~~~*/
void MainWindow::loadFileFull(const QString &fileName, int reload)
{
    //if called from reload then int reload ==1 (don't call slot select)
    QFile file(fileName);

    if (!file.open(QFile::ReadOnly)) {
        QMessageBox::warning(this, tr("Black Chocobo"), tr("Cannot read file %1:\n%2.") .arg(fileName).arg(file.errorString()));
        return;
    }

    prevFile = ff7->fileName();
    if (ff7->loadFile(fileName)) {
        _init = false; //we have now loaded a file
        fileModified(false);
    } else {
        QMessageBox::information(this, tr("Load Failed"), tr("Failed to Load File"));
        return;
    }

    if (ff7->numberOfSlots() > 1) {
        if (reload)
            guirefresh(0);
        else
            on_actionShow_Selection_Dialog_triggered();
    } else {
        s = 0;
        guirefresh(0);
    }

    hexEditor->setCursorPosition(0);
    hexCursorPos = 0;
}
/*~~~~~~~~~~~~~~~~~IMPORT PSX~~~~~~~~~~~~~~~~~~*/
void MainWindow::on_actionImport_Slot_From_File_triggered()
{
    QString fileName = BCDialog::getOpenFileName(this,
                       tr("Open Final Fantasy 7 Save"), BCSettings::instance()->value(SETTINGS::LOADPATH).toString(),
                       FF7SaveInfo::instance()->knownTypesFilter());
    if (!fileName.isEmpty()) {
        FF7Save *tempSave = new FF7Save();
        if (tempSave->loadFile(fileName)) {
            int fileSlot = 0;
            if (FF7SaveInfo::instance()->slotCount(tempSave->format()) > 1) {
                SlotSelect *SSelect = new SlotSelect(BCSettings::instance()->value(SETTINGS::SCALE).toDouble(), tempSave, false);
                SSelect->move(x() + ((width() - SSelect->width()) / 2), y() + (SSelect->height() /2));
                fileSlot = SSelect->exec();
                if (fileSlot == -1) {
                    on_actionImport_Slot_From_File_triggered();
                    return;
                }
                ui->statusBar->showMessage(QString(tr("Imported Slot:%2 from %1 -> Slot:%3")).arg(fileName, QString::number(fileSlot + 1), QString::number(s + 1)), 2000);
            } else {
                ui->statusBar->showMessage(QString(tr("Imported %1 -> Slot:%2")).arg(fileName, QString::number(s + 1)), 2000);
            }
            ff7->importSlot(s, fileName, fileSlot);
            guirefresh(0);
        } else {
            ui->statusBar->showMessage(QString(tr("Error Loading File %1")).arg(fileName), 2000);
        }
    }
    ff7->setFileModified(true, 0);
}
/*~~~~~~~~~~~~~~~~~IMPORT Char~~~~~~~~~~~~~~~~~*/
void MainWindow::on_actionImport_char_triggered()
{
    QString fileName = BCDialog::getOpenFileName(this, tr("Select FF7 Character Stat File"), BCSettings::instance()->value(SETTINGS::STATFOLDER).toString(), tr("FF7 Character Stat File(*.char)"));
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly)) {
        QMessageBox::warning(this, tr("Black Chocobo"), tr("Cannot read file %1:\n%2.").arg(fileName).arg(file.errorString()));
        return;
    }
    if (file.size() != 0x84) {
        QMessageBox::warning(this, tr("Black Chocobo"), tr("%1:\n%2 is Not a FF7 Character Stat File.").arg(fileName).arg(file.errorString()));
        return;
    }
    QByteArray new_char;
    new_char = file.readAll();
    ff7->importCharacter(s, curchar, new_char);
    char_editor->setChar(ff7->character(s, curchar), ff7->charName(s, curchar));
    set_char_buttons();
}

void MainWindow::on_actionExport_char_triggered()
{
    QString fileName = BCDialog::getSaveFileName(this, ff7->region(s),
                       tr("Save FF7 Character File"), BCSettings::instance()->value(SETTINGS::STATFOLDER).toString(),
                       tr("FF7 Character Stat File(*.char)"));
    if (!fileName.isEmpty()) {
        if (ff7->exportCharacter(s, curchar, fileName))
            ui->statusBar->showMessage(tr("Character Export Successful"), 1000);
        else
            ui->statusBar->showMessage(tr("Character Export Failed"), 2000);
    }
}
bool MainWindow::on_action_Save_triggered()
{
    if (_init || ff7->fileName().isEmpty())
        return on_actionSave_File_As_triggered();
    return saveFileFull(ff7->fileName());
}

bool MainWindow::on_actionSave_File_As_triggered()
{
    QMap<QString, FF7SaveInfo::FORMAT> typeMap;
    typeMap[FF7SaveInfo::instance()->typeFilter(FF7SaveInfo::FORMAT::PC)] = FF7SaveInfo::FORMAT::PC;
    typeMap[FF7SaveInfo::instance()->typeFilter(FF7SaveInfo::FORMAT::SWITCH)] = FF7SaveInfo::FORMAT::SWITCH;
    typeMap[FF7SaveInfo::instance()->typeFilter(FF7SaveInfo::FORMAT::VMC)] = FF7SaveInfo::FORMAT::VMC;
    typeMap[FF7SaveInfo::instance()->typeFilter(FF7SaveInfo::FORMAT::VGS)] = FF7SaveInfo::FORMAT::VGS;
    typeMap[FF7SaveInfo::instance()->typeFilter(FF7SaveInfo::FORMAT::DEX)] = FF7SaveInfo::FORMAT::DEX;
    typeMap[FF7SaveInfo::instance()->typeFilter(FF7SaveInfo::FORMAT::PSP)] = FF7SaveInfo::FORMAT::PSP;
    typeMap[FF7SaveInfo::instance()->typeFilter(FF7SaveInfo::FORMAT::PSX)] = FF7SaveInfo::FORMAT::PSX;
    typeMap[FF7SaveInfo::instance()->typeFilter(FF7SaveInfo::FORMAT::PS3)] = FF7SaveInfo::FORMAT::PS3;
    typeMap[FF7SaveInfo::instance()->typeFilter(FF7SaveInfo::FORMAT::PGE)] = FF7SaveInfo::FORMAT::PGE;
    typeMap[FF7SaveInfo::instance()->typeFilter(FF7SaveInfo::FORMAT::PDA)] = FF7SaveInfo::FORMAT::PDA;
    QString selectedType = typeMap.key(ff7->format(), QString());

    QString path;
    if (ff7->format() == FF7SaveInfo::FORMAT::PC)
            path = BCSettings::instance()->value(SETTINGS::PCSAVEPATH).toString();
    else if ((ff7->format() == FF7SaveInfo::FORMAT::VMC)
             || (ff7->format() == FF7SaveInfo::FORMAT::VGS)
             || (ff7->format() == FF7SaveInfo::FORMAT::DEX))
        path = BCSettings::instance()->value(SETTINGS::EMUSAVEPATH).toString();

    QString fileName = BCDialog::getSaveFileName(this, ff7->region(s), tr("Select A File to Save As"), path , typeMap.keys().join(";;"), &selectedType, QFile(ff7->fileName()).fileName());

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
/*~~~~~~~~~~~SHORT SAVE~~~~~~~~~~~~*/
bool MainWindow::saveFileFull(const QString &fileName)
{
    if (ff7->saveFile(fileName, s)) {
        //if no save was loaded and new game was clicked be sure to act like a game was loaded.
        if (_init)
            _init = false;

        fileModified(false);
        guirefresh(0);
        return true;
    }

    QMessageBox::information(this, tr("Save Error"), tr("Failed to save file\n%1").arg(fileName));
    return false;
}
/*~~~~~~~~~~~~~~~New_Game~~~~~~~~~~~*/

void MainWindow::on_actionNew_Game_triggered()
{
    QString save_name = BCSettings::instance()->value(SETTINGS::CUSTOMDEFAULTSAVE).toBool() ?
                BCSettings::instance()->value(SETTINGS::DEFAULTSAVE).toString() : QString();

    QString region = ff7->region(s).isEmpty() ?
                BCSettings::instance()->value(SETTINGS::REGION).toString() : ff7->region(s);

    ff7->newGame(s, region, save_name);//call the new game function
    ui->statusBar->showMessage(tr("New Game Created - Using: %1")
                               .arg(save_name.isEmpty() ? tr("Builtin Data") : save_name), 2000);
    _init = false;
    guirefresh(1);
}
/*~~~~~~~~~~End New_Game~~~~~~~~~~~*/
/*~~~~~~~~~~New Game + ~~~~~~~~~~~~*/
void MainWindow::on_actionNew_Game_Plus_triggered()
{
    QString save_name;
    if (BCSettings::instance()->value(SETTINGS::CUSTOMDEFAULTSAVE).toBool())
        save_name = BCSettings::instance()->value(SETTINGS::DEFAULTSAVE).toString();

    ff7->newGamePlus(s, ff7->fileName(), save_name);
    ui->statusBar->showMessage(tr("New Game Plus Created - Using: %1")
                               .arg(save_name.isEmpty() ? tr("Builtin Data") : save_name), 2000);
    guirefresh(0);
}
/*~~~~~~~~~~End New_Game +~~~~~~~~~~~*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~END LOAD/SAVE FUNCTIONS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MENU ACTIONS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*~~~~~~~~~~~~Simple Menu Stuff~~~~~~~~~~~~~~~~*/
void MainWindow::on_actionClear_Slot_triggered()
{
    ff7->clearSlot(s);
    guirefresh(0);
}
void MainWindow::on_actionPrevious_Slot_triggered()
{
    if (ff7->format() == FF7SaveInfo::FORMAT::UNKNOWN)
        return;

    if (s > 0) {
        s--;
        guirefresh(0);
    }
}
void MainWindow::on_actionNext_Slot_triggered()
{
    if (ff7->format() == FF7SaveInfo::FORMAT::UNKNOWN)
        return;

    if (s < 14) {
        s++;
        guirefresh(0);
    }
}
void MainWindow::on_actionAbout_triggered()
{
    About adialog(this);
    adialog.exec();
}
void MainWindow::on_actionCopy_Slot_triggered()
{
    ff7->copySlot(s);
}
void MainWindow::on_actionPaste_Slot_triggered()
{
    ff7->pasteSlot(s);
    guirefresh(0);
}
void MainWindow::on_actionShow_Options_triggered()
{
    Options odialog(this);
    connect(&odialog, &Options::requestLanguageChange, this, &MainWindow::changeLanguage);
    connect(&odialog, &Options::requestChangeNativeDialog, this, [] (bool useNative){
        QApplication::setAttribute(Qt::AA_DontUseNativeDialogs, !useNative);
    });
    odialog.move(x() + ((width() - odialog.width()) / 2), y() + ((height() - odialog.sizeHint().height()) / 2));
    if (odialog.exec()) {
        setScale(BCSettings::instance()->value(SETTINGS::SCALE).toDouble());
        loadChildWidgetSettings();
    }
    disconnect(&odialog, nullptr, nullptr, nullptr);
}

void MainWindow::on_actionCreateNewMetadata_triggered()
{
    MetadataCreator mdata(this, ff7);
    mdata.exec();
}

void MainWindow::on_actionShow_Selection_Dialog_triggered()
{
    SlotSelect slotselect(BCSettings::instance()->value(SETTINGS::SCALE).toDouble(), ff7, true);
    slotselect.move(x() + ((width() - slotselect.width()) / 2), y() + (slotselect.height() /2));

    int i = slotselect.exec();
    if(i == -1) {
        on_actionOpen_Save_File_triggered();
    } else {
        s = i;
        guirefresh(0);
    }
}

void MainWindow::on_actionOpen_Achievement_File_triggered()
{
    QString temp = ff7->fileName();
    temp.chop(temp.length() - (temp.lastIndexOf("/")));
    temp.append(QString("%1achievement.dat").arg(QDir::separator()));
    QFile tmp(temp);
    if (!tmp.exists())
        temp = BCDialog::getOpenFileName(this, tr("Select Achievement File"), QDir::homePath(), tr("Dat File (*.dat)"));

    if (temp.isEmpty())
        return;

    achievementDialog achDialog(temp);
    achDialog.move(x() + (width() - achDialog.width()) / 2, y() + (height() - achDialog.height())/2);
    achDialog.exec();
}

/*~~~~~~~~~~~~LANGUAGE & REGION ACTIONS~~~~~~~~~~~~~~*/

void MainWindow::changeLanguage(const QVariant &data)
{
    BCSettings::instance()->setValue(SETTINGS::LANG, data);
    if(!m_translations.contains(data.toString()))
        populateLanguageMenu();
    QApplication::installTranslator(m_translations.value(data.toString()));
}
/*~~~~~~~~~~~~~SET USA MC HEADER~~~~~~~~~~~~~~~~*/
void MainWindow::on_action_Region_USA_triggered(bool checked)
{
    if (!load) {
        if (!checked) {
            ff7->setRegion(s, QString());
            ui->lbl_sg_region->clear();
            itemlist->setMaximumItemQty(127);
        } else {
            if (ff7->isPAL(s))
                set_ntsc_time();   //Convert Time?

            ff7->setRegion(s, "NTSC-U");
            itemlist->setMaximumItemQty(127);
            ui->action_Region_PAL_Generic->setChecked(false);
            ui->action_Region_PAL_French->setChecked(false);
            ui->action_Region_PAL_German->setChecked(false);
            ui->action_Region_PAL_Spanish->setChecked(false);
            ui->action_Region_JPN->setChecked(false);
            ui->action_Region_JPN_International->setChecked(false);
            load = true;
            ui->lbl_sg_region->setText(ff7->region(s).mid(0, ff7->region(s).lastIndexOf("-") + 1));
            ui->cb_Region_Slot->setCurrentIndex(ff7->region(s).mid(ff7->region(s).lastIndexOf("S") + 1, 2).toInt() - 1);
            load = false;
        }
    }
    locationViewer->setRegion(ff7->region(s));
}
/*~~~~~~~~~~~~~SET PAL MC HEADER~~~~~~~~~~~~~~~~*/
void MainWindow::on_action_Region_PAL_Generic_triggered(bool checked)
{
    if (!load) {
        if (!checked) {
            ff7->setRegion(s, QString());
            ui->lbl_sg_region->clear();
            itemlist->setMaximumItemQty(127);
        } else {
            if (ff7->isNTSC(s))
                set_pal_time();   //Call RegionTime Converter

            ff7->setRegion(s, "PAL-E");
            itemlist->setMaximumItemQty(127);
            ui->action_Region_USA->setChecked(false);
            ui->action_Region_PAL_German->setChecked(false);
            ui->action_Region_PAL_French->setChecked(false);
            ui->action_Region_PAL_Spanish->setChecked(false);
            ui->action_Region_JPN->setChecked(false);
            ui->action_Region_JPN_International->setChecked(false);
            load = true;
            ui->lbl_sg_region->setText(ff7->region(s).mid(0, ff7->region(s).lastIndexOf("-") + 1));
            ui->cb_Region_Slot->setCurrentIndex(ff7->region(s).mid(ff7->region(s).lastIndexOf("S") + 1, 2).toInt() - 1);
            load = false;
        }
    } locationViewer->setRegion(ff7->region(s));
}
/*~~~~~~~~~~~~~SET PAL_German MC HEADER~~~~~~~~~~~~~~~~*/
void MainWindow::on_action_Region_PAL_German_triggered(bool checked)
{
    if (!load) {
        if (!checked) {
            ff7->setRegion(s, QString());
            ui->lbl_sg_region->clear();
            itemlist->setMaximumItemQty(127);
        } else {
            if (ff7->isNTSC(s))
                set_pal_time();   //Call RegionTime Converter

            ff7->setRegion(s, "PAL-DE");
            itemlist->setMaximumItemQty(127);
            ui->action_Region_USA->setChecked(false);
            ui->action_Region_PAL_Generic->setChecked(false);
            ui->action_Region_PAL_French->setChecked(false);
            ui->action_Region_PAL_Spanish->setChecked(false);
            ui->action_Region_JPN->setChecked(false);
            ui->action_Region_JPN_International->setChecked(false);
            load = true;
            ui->lbl_sg_region->setText(ff7->region(s).mid(0, ff7->region(s).lastIndexOf("-") + 1));
            ui->cb_Region_Slot->setCurrentIndex(ff7->region(s).mid(ff7->region(s).lastIndexOf("S") + 1, 2).toInt() - 1);
            load = false;
        }
    } locationViewer->setRegion(ff7->region(s));
}
/*~~~~~~~~~~~~~SET PAL_Spanish MC HEADER~~~~~~~~~~~~~~~~*/
void MainWindow::on_action_Region_PAL_Spanish_triggered(bool checked)
{
    if (!load) {
        if (!checked) {
            ff7->setRegion(s, QString());
            ui->lbl_sg_region->clear();
            itemlist->setMaximumItemQty(127);
        } else {
            if (ff7->isNTSC(s))
                set_pal_time();   //Call RegionTime Converter

            ff7->setRegion(s, "PAL-ES");
            itemlist->setMaximumItemQty(127);
            ui->action_Region_USA->setChecked(false);
            ui->action_Region_PAL_Generic->setChecked(false);
            ui->action_Region_PAL_French->setChecked(false);
            ui->action_Region_PAL_German->setChecked(false);
            ui->action_Region_JPN->setChecked(false);
            ui->action_Region_JPN_International->setChecked(false);
            load = true;
            ui->lbl_sg_region->setText(ff7->region(s).mid(0, ff7->region(s).lastIndexOf("-") + 1));
            ui->cb_Region_Slot->setCurrentIndex(ff7->region(s).mid(ff7->region(s).lastIndexOf("S") + 1, 2).toInt() - 1);
            load = false;
        }
    } locationViewer->setRegion(ff7->region(s));
}
/*~~~~~~~~~~~~~SET PAL_French MC HEADER~~~~~~~~~~~~~~~~*/
void MainWindow::on_action_Region_PAL_French_triggered(bool checked)
{
    if (!load) {
        if (!checked) {
            ff7->setRegion(s, QString());
            ui->lbl_sg_region->clear();
            itemlist->setMaximumItemQty(127);
        } else {
            if (ff7->isNTSC(s))
                set_pal_time();   //Call RegionTime Converter

            ff7->setRegion(s, "PAL-FR");
            itemlist->setMaximumItemQty(127);
            ui->action_Region_USA->setChecked(false);
            ui->action_Region_PAL_Generic->setChecked(false);
            ui->action_Region_PAL_Spanish->setChecked(false);
            ui->action_Region_PAL_German->setChecked(false);
            ui->action_Region_JPN->setChecked(false);
            ui->action_Region_JPN_International->setChecked(false);
            load = true;
            ui->lbl_sg_region->setText(ff7->region(s).mid(0, ff7->region(s).lastIndexOf("-") + 1));
            ui->cb_Region_Slot->setCurrentIndex(ff7->region(s).mid(ff7->region(s).lastIndexOf("S") + 1, 2).toInt() - 1);
            load = false;
        }
    } locationViewer->setRegion(ff7->region(s));
}
/*~~~~~~~~~~~~~SET JPN MC HEADER~~~~~~~~~~~~~~~~*/
void MainWindow::on_action_Region_JPN_triggered(bool checked)
{
    if (!load) {
        if (!checked) {
            ff7->setRegion(s, QString());
            ui->lbl_sg_region->clear();
            itemlist->setMaximumItemQty(127);
        } else {
            //First Check If Coming From PAL
            if (ff7->isPAL(s))
                set_ntsc_time();   //Convert Time?
            ff7->setRegion(s, "NTSC-J");
            itemlist->setMaximumItemQty(99);
            ui->action_Region_USA->setChecked(false);
            ui->action_Region_PAL_Generic->setChecked(false);
            ui->action_Region_PAL_French->setChecked(false);
            ui->action_Region_PAL_German->setChecked(false);
            ui->action_Region_PAL_Spanish->setChecked(false);
            ui->action_Region_JPN_International->setChecked(false);
            load = true;
            ui->lbl_sg_region->setText(ff7->region(s).mid(0, ff7->region(s).lastIndexOf("-") + 1));
            ui->cb_Region_Slot->setCurrentIndex(ff7->region(s).mid(ff7->region(s).lastIndexOf("S") + 1, 2).toInt() - 1);
            load = false;
        }
    } locationViewer->setRegion(ff7->region(s));
}
/*~~~~~~~~~~~~~SET JPN_International MC HEADER~~~~~~~~~~~~~~~~*/
void MainWindow::on_action_Region_JPN_International_triggered(bool checked)
{
    if (!load) {
        if (!checked) {
            ff7->setRegion(s, QString());
            ui->lbl_sg_region->clear();
            itemlist->setMaximumItemQty(127);
        } else {
            if (ff7->isPAL(s))
                set_ntsc_time();   //Convert Time?
            ff7->setRegion(s, "NTSC-JI");
            itemlist->setMaximumItemQty(127);
            ui->action_Region_USA->setChecked(false);
            ui->action_Region_PAL_Generic->setChecked(false);
            ui->action_Region_PAL_French->setChecked(false);
            ui->action_Region_PAL_German->setChecked(false);
            ui->action_Region_PAL_Spanish->setChecked(false);
            ui->action_Region_JPN->setChecked(false);
            load = true;
            ui->lbl_sg_region->setText(ff7->region(s).mid(0, ff7->region(s).lastIndexOf("-") + 1));
            ui->cb_Region_Slot->setCurrentIndex(ff7->region(s).mid(ff7->region(s).lastIndexOf("S") + 1, 2).toInt() - 1);
            load = false;
        }
    } locationViewer->setRegion(ff7->region(s));
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~END MENU ACTIONS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~GUI FUNCTIONS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*~~~~~~~~Set Menu Items~~~~~~~~~~*/
void MainWindow::setmenu(bool newgame)
{
    load = true;
    /*~~Disable All Items that are dependent on File Type~~*/
    ui->actionClear_Slot->setEnabled(0);
    ui->action_Region_USA->setChecked(false);
    ui->action_Region_PAL_Generic->setChecked(false);
    ui->action_Region_PAL_German->setChecked(false);
    ui->action_Region_PAL_French->setChecked(false);
    ui->action_Region_PAL_Spanish->setChecked(false);
    ui->action_Region_JPN->setChecked(false);
    ui->action_Region_JPN_International->setChecked(false);
    ui->actionNext_Slot->setEnabled(0);
    ui->actionPrevious_Slot->setEnabled(0);
    ui->actionShow_Selection_Dialog->setEnabled(0);
    ui->actionNew_Game->setEnabled(0);
    ui->compare_table->setEnabled(0);
    ui->lbl_current_slot_txt->clear();
    ui->actionImport_char->setEnabled(1);
    ui->actionExport_char->setEnabled(1);
    /*~~End Clear Menu Items~~*/
    /*~~~~~~~Set Actions By Type~~~~~~~*/
    //For first file load.Don't Bother to disable these again.
    //new game should always be exported. no header...

    //if not FF7 user is stuck in the hex editor tab.
    if (!ff7->isFF7(s) && !ff7->region(s).isEmpty()) {
        if (ui->combo_hexEditor->currentIndex() != 0)
            ui->combo_hexEditor->setCurrentIndex(0);
        ui->tabWidget->setCurrentIndex(8);
        for (int i = 0; i < 8; i++)
            ui->tabWidget->setTabEnabled(i, false);
        ui->tabWidget->setTabEnabled(9, false);
    } else {
        for (int i = 0; i < 9; i++)
            ui->tabWidget->setTabEnabled(i, true);
        ui->tabWidget->setTabEnabled(9, BCSettings::instance()->value(SETTINGS::ENABLETEST).toBool());
    }

    if (!newgame && !ff7->fileName().isEmpty()) {
        ui->actionSave_File_As->setEnabled(1);
        ui->actionReload->setEnabled(1);
    }

    ui->actionImport_char->setEnabled(1);
    ui->action_Save->setEnabled(1);

    //we haven't loaded a file yet.
    if (!_init) {
        ui->actionNew_Game_Plus->setEnabled(1);
        ui->actionImport_Slot_From_File->setEnabled(1);
        ui->actionCopy_Slot->setEnabled(1);
        ui->actionPaste_Slot->setEnabled(1);
        ui->actionNew_Game->setEnabled(1);
    }

    if ((ff7->format() != FF7SaveInfo::FORMAT::PSX && ff7->format() != FF7SaveInfo::FORMAT::PS3 && (!_init)) && (ff7->format() != FF7SaveInfo::FORMAT::UNKNOWN)) { //more then one slot, or unknown Type
        ui->actionNext_Slot->setEnabled(1);
        ui->actionPrevious_Slot->setEnabled(1);
        ui->actionShow_Selection_Dialog->setEnabled(1);
        ui->actionClear_Slot->setEnabled(1);
        ui->actionNew_Game->setEnabled(1);
        ui->compare_table->setEnabled(1);
        ui->lbl_current_slot_txt->setText(tr("Current Slot:%1").arg(QString::number(s + 1), 2, QChar('0')));
    }
    /*~~~End Set Actions By Type~~~*/
    /*~~Set Detected Region ~~*/
    if (ff7->region(s).contains("94163"))
        ui->action_Region_USA->setChecked(true);
    else if (ff7->region(s).contains("00867"))
        ui->action_Region_PAL_Generic->setChecked(true);
    else if (ff7->region(s).contains("00868"))
        ui->action_Region_PAL_French->setChecked(true);
    else if (ff7->region(s).contains("00869"))
        ui->action_Region_PAL_German->setChecked(true);
    else if (ff7->region(s).contains("00900"))
        ui->action_Region_PAL_Spanish->setChecked(true);
    else if (ff7->region(s).contains("00700"))
        ui->action_Region_JPN->setChecked(true);
    else if (ff7->region(s).contains("01057"))
        ui->action_Region_JPN_International->setChecked(true);
    else if (!ff7->region(s).isEmpty()) {
        //not FF7 unset some menu options.
        ui->actionNew_Game_Plus->setEnabled(0);
        ui->actionCopy_Slot->setEnabled(0);
        ui->actionExport_char->setEnabled(0);
        ui->actionImport_char->setEnabled(0);
    }
    load = false;
}
void MainWindow::fileModified(bool changed)
{
    ui->lbl_fileName->setText(ff7->fileName());
    if (changed)
        ui->lbl_fileName->setText(ui->lbl_fileName->text().append("*"));
}
/*~~~~~~~~~End Set Menu~~~~~~~~~~~*/
void MainWindow::set_ntsc_time(void)
{
    if (BCDialog::fixTimeDialog(this, ff7->isPAL(s)) == QMessageBox::Yes) {
        ff7->setTime(s, quint32(ff7->time(s) * 1.2));
        load = true;
        ui->sb_time_hour->setValue(ff7->time(s) / 3600);
        ui->sb_time_min->setValue(ff7->time(s) / 60 % 60);
        ui->sb_time_sec->setValue(int(ff7->time(s)) - ((ui->sb_time_hour->value() * 3600) + ui->sb_time_min->value() * 60));
        load = false;
    }
}
void MainWindow::set_pal_time(void)
{
    if (BCDialog::fixTimeDialog(this, ff7->isPAL(s)) == QMessageBox::Yes) {
        ff7->setTime(s, quint32(ff7->time(s) / 1.2));
        load = true;
        ui->sb_time_hour->setValue(ff7->time(s) / 3600);
        ui->sb_time_min->setValue(ff7->time(s) / 60 % 60);
        ui->sb_time_sec->setValue(int(ff7->time(s)) - ((ui->sb_time_hour->value() * 3600) + ui->sb_time_min->value() * 60));
        load = false;
    }
}
void MainWindow::materiaupdate(void)
{
    load = true;
    int j = std::max(0, ui->tbl_materia->currentRow());
    ui->tbl_materia->reset();
    ui->tbl_materia->clearContents();
    ui->tbl_materia->setColumnWidth(0, int(ui->tbl_materia->width()*.65));
    ui->tbl_materia->setColumnWidth(1, int(ui->tbl_materia->width()*.25));
    ui->tbl_materia->setRowCount(200);

    for (int mat = 0; mat < 200; mat++) { // partys materias
        QTableWidgetItem *newItem;
        ui->tbl_materia->setRowHeight(mat, fontMetrics().height() + 9);
        qint32 current_ap = ff7->partyMateriaAp(s, mat);
        quint8 current_id = ff7->partyMateriaId(s, mat);
        QString ap;

        if (current_id <= 0x5A) {
            newItem = new QTableWidgetItem(QIcon(QPixmap::fromImage(Materias.image(current_id).scaledToHeight(fontMetrics().height(), Qt::SmoothTransformation))), Materias.name(current_id), 0);
            ui->tbl_materia->setItem(mat, 0, newItem);
        }

        if (current_id == FF7Materia::EnemySkill) {
            if (current_ap == FF7Materia::MaxMateriaAp) {
                newItem = new QTableWidgetItem(tr("Master"));
                ui->tbl_materia->setItem(mat, 1, newItem);
            } else {
                newItem = new QTableWidgetItem(QString(), 0);
                ui->tbl_materia->setItem(mat, 1, newItem);
            }
        }

        else if (current_id == FF7Materia::MasterCommand || current_id == FF7Materia::MasterMagic || current_id == FF7Materia::MasterSummon || current_id == FF7Materia::Underwater) {
            newItem = new QTableWidgetItem(QString(), 0);
            ui->tbl_materia->setItem(mat, 1, newItem);
        } else if (current_id != FF7Materia::EmptyId) {
            if (current_ap == FF7Materia::MaxMateriaAp) {
                newItem = new QTableWidgetItem(tr("Master"));
                ui->tbl_materia->setItem(mat, 1, newItem);
            } else {
                newItem = new QTableWidgetItem(ap.setNum(current_ap));
                ui->tbl_materia->setItem(mat, 1, newItem);
            }
        } else {
            //We need to clear invalid to prevent data issues. to keep file changes correct we back up our change vars and replace later.
            bool fileTemp = ff7->isFileModified();
            ff7->setPartyMateria(s, mat, FF7Materia::EmptyId, FF7Materia::MaxMateriaAp); //invalid insure its clear.
            newItem = new QTableWidgetItem(tr("===Empty Slot==="), 0);
            ui->tbl_materia->setItem(mat, 0, newItem);
            newItem = new QTableWidgetItem(QString(), 0);
            ui->tbl_materia->setItem(mat, 1, newItem);
            ff7->setFileModified(fileTemp, s);
        }
    }
    if (ff7->partyMateriaId(s, j) == FF7Materia::EnemySkill)
        mat_spacer->changeSize(0, 0, QSizePolicy::Fixed, QSizePolicy::Fixed);
    else
        mat_spacer->changeSize(0, 0, QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
    materia_editor->setMateria(ff7->partyMateriaId(s, j), ff7->partyMateriaAp(s, j));
    ui->tbl_materia->setCurrentCell(j, 1); //so that right side is set correctly.
    load = false;
}
void MainWindow::materia_ap_changed(qint32 ap)
{
    if (!load) {
        ff7->setPartyMateria(s, ui->tbl_materia->currentRow(), ff7->partyMateriaId(s, ui->tbl_materia->currentRow()), ap);
        materiaupdate();
    }
}
void MainWindow::materia_id_changed(qint8 id)
{
    if (!load) {
        ff7->setPartyMateria(s, ui->tbl_materia->currentRow(), quint8(id), ff7->partyMateriaAp(s, ui->tbl_materia->currentRow()));
        materiaupdate();
    }
}
void MainWindow::CheckGame()
{
    if ((!ff7->isFF7(s) && !ff7->region(s).isEmpty())
            || ((!ff7->isFF7(s)) && (ff7->format() != FF7SaveInfo::FORMAT::PC || ff7->format() != FF7SaveInfo::FORMAT::SWITCH) && (ff7->psx_block_type(s) != char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_EMPTY)))) {
        // NOT FF7
        errbox error(nullptr, ff7, s);
        if ((ff7->format() == FF7SaveInfo::FORMAT::PSX) || (ff7->format() == FF7SaveInfo::FORMAT::PS3) || ff7->format() == FF7SaveInfo::FORMAT::PDA || ff7->format() == FF7SaveInfo::FORMAT::PGE)
            error.setSingleSlot(true);
        error.move(x() + ((width() - error.width()) / 2), y() + (height() /2));
        switch (error.exec()) {
        case 0://View Anyway..
            setmenu(0);
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
            typeMap[FF7SaveInfo::instance()->typeFilter(FF7SaveInfo::FORMAT::PSX)] = FF7SaveInfo::FORMAT::PSX;
            typeMap[FF7SaveInfo::instance()->typeFilter(FF7SaveInfo::FORMAT::PS3)] = FF7SaveInfo::FORMAT::PS3;
            typeMap[FF7SaveInfo::instance()->typeFilter(FF7SaveInfo::FORMAT::PGE)] = FF7SaveInfo::FORMAT::PGE;
            typeMap[FF7SaveInfo::instance()->typeFilter(FF7SaveInfo::FORMAT::PDA)] = FF7SaveInfo::FORMAT::PDA;
            QString selectedType = typeMap.key(FF7SaveInfo::FORMAT::PSX);

            QString fileName = BCDialog::getSaveFileName(this, ff7->region(s), tr("Select A File to Save As"), QStringLiteral("%1/%2").arg(QDir::homePath(), ff7->region(s)), typeMap.keys().join(";;"), &selectedType);

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
        guirefresh(0);
    }
}
void MainWindow::othersUpdate()
{
    load = true;

    ui->cb_ruby_dead->setChecked(ff7->killedRubyWeapon(s));
    ui->cb_emerald_dead->setChecked(ff7->killedEmeraldWeapon(s));

    ui->cbPandorasBox->setChecked(ff7->seenPandorasBox(s));
    ui->cbSubGameWon->setChecked(ff7->subMiniGameVictory(s));
    ui->sbCondorWins->setValue(ff7->condorWins(s));
    ui->sbCondorLosses->setValue(ff7->condorLosses(s));
    ui->sbCondorFunds->setValue(ff7->condorFunds(s));

    ui->sb_coster_1->setValue(ff7->speedScore(s, 1));
    ui->sb_coster_2->setValue(ff7->speedScore(s, 2));
    ui->sb_coster_3->setValue(ff7->speedScore(s, 3));

    for (int i = 0; i < 9; i++) //Allowed in Phs
            phsList->setChecked(i, PhsListWidget::PHSALLOWED, !ff7->phsAllowed(s, i));

    for (int i = 0; i < 9; i++) //Visible
            phsList->setChecked(i, PhsListWidget::PHSVISIBLE, ff7->phsVisible(s, i));

    for (int i = 0; i < 10; i++) //visible_menu
            menuList->setChecked(i, MenuListWidget::MENUVISIBLE, ff7->menuVisible(s, i));

    for (int i = 0; i < 10; i++) //menu_locked
            menuList->setChecked(i, MenuListWidget::MENULOCKED, ff7->menuLocked(s, i));

    ui->sb_steps->setValue(ff7->steps(s));

    ui->sb_love_barret->setValue(ff7->love(s, false, FF7Save::LOVE_BARRET));
    ui->sb_love_tifa->setValue(ff7->love(s, false, FF7Save::LOVE_TIFA));
    ui->sb_love_aeris->setValue(ff7->love(s, false, FF7Save::LOVE_AERIS));
    ui->sb_love_yuffie->setValue(ff7->love(s, false, FF7Save::LOVE_YUFFIE));

    ui->sb_time_hour->setValue(ff7->time(s) / 3600);
    ui->sb_time_min->setValue(ff7->time(s) / 60 % 60);
    ui->sb_time_sec->setValue(int(ff7->time(s)) - ((ui->sb_time_hour->value() * 3600) + ui->sb_time_min->value() * 60));

    ui->sb_timer_time_hour->setValue(ff7->countdownTimer(s) / 3600);
    ui->sb_timer_time_min->setValue(ff7->countdownTimer(s) / 60 % 60);
    ui->sb_timer_time_sec->setValue(int(ff7->countdownTimer(s)) - ((ui->sb_timer_time_hour->value() * 3600) + ui->sb_timer_time_min->value() * 60));
    ui->cb_yuffieforest->setChecked(ff7->canFightNinjaInForest(s));
    ui->cb_reg_yuffie->setChecked(ff7->yuffieUnlocked(s));
    ui->cb_reg_vinny->setChecked(ff7->vincentUnlocked(s));

    /*~~~~~Stolen Materia~~~~~~~*/
    ui->tbl_materia_2->reset();
    ui->tbl_materia_2->clearContents();
    ui->tbl_materia_2->setColumnWidth(0, int(ui->tbl_materia_2->width()*.65));
    ui->tbl_materia_2->setColumnWidth(1, int(ui->tbl_materia_2->width()*.25));
    ui->tbl_materia_2->setRowCount(48);
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

    ui->sb_BikeHighScore->setValue(ff7->bikeHighScore(s));
    ui->sb_BattlePoints->setValue(ff7->battlePoints(s));
    ui->cb_FlashbackPiano->setChecked(ff7->playedPianoOnFlashback(s));
    load = false;
}
void MainWindow::updateStolenMateria()
{
    for (int mat = 0; mat < 48; mat++) { //materias stolen by yuffie
        QString ap;
        quint8 current_id = ff7->stolenMateriaId(s, mat);
        QTableWidgetItem *newItem;
        if (current_id != FF7Materia::EmptyId) {
            newItem = new QTableWidgetItem(QPixmap::fromImage(Materias.image(current_id)), Materias.name(current_id), 0);
            ui->tbl_materia_2->setItem(mat, 0, newItem);
            qint32 current_ap = ff7->stolenMateriaAp(s, mat);
            if (current_ap == FF7Materia::MaxMateriaAp) {
                newItem = new QTableWidgetItem(tr("Master"));
                ui->tbl_materia_2->setItem(mat, 1, newItem);
            } else {
                newItem = new QTableWidgetItem(ap.setNum(current_ap));
                ui->tbl_materia_2->setItem(mat, 1, newItem);
            }
        } else {
            newItem = new QTableWidgetItem(tr("===Empty Slot==="), 0);
            ui->tbl_materia_2->setItem(mat, 0, newItem);
        }
        ui->tbl_materia_2->setRowHeight(mat, fontMetrics().height() + 9);
    }
}
void MainWindow::update_hexEditor_PSXInfo(void)
{
    load = true;
    SaveIcon *save_icon = new SaveIcon(ff7->slotIcon(s));
    ui->lblPsxIcon->setPixmap(save_icon->icon().scaled(ui->lblPsxIcon->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    //connect(save_icon, SIGNAL(nextIcon(QPixmap)), ui->lblPsxIcon, SLOT(setPixmap(QPixmap)));

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
void MainWindow::on_tabWidget_currentChanged(int index)
{
    //Update the shown tab.
    load = true;
    hexCursorPos = hexEditor->cursorPosition();
    switch (index) {
    case 0://Party Tab
        if (ff7->party(s, 0) >= 0x0C)
            ui->combo_party1->setCurrentIndex(12);
        else
            ui->combo_party1->setCurrentIndex(ff7->party(s, 0));

        if (ff7->party(s, 1) >= 0x0C)
            ui->combo_party2->setCurrentIndex(12);
        else
            ui->combo_party2->setCurrentIndex(ff7->party(s, 1));

        if (ff7->party(s, 2) >= 0x0C)
            ui->combo_party3->setCurrentIndex(12);
        else
            ui->combo_party3->setCurrentIndex(ff7->party(s, 2));

        set_char_buttons();
        switch (curchar) {
        case 0: ui->btn_cloud->click(); break;
        case 1: ui->btn_barret->click(); break;
        case 2: ui->btn_tifa->click(); break;
        case 3: ui->btn_aeris->click(); break;
        case 4: ui->btn_red->click(); break;
        case 5: ui->btn_yuffie->click(); break;
        case 6: ui->btn_cait->click(); break;
        case 7: ui->btn_vincent->click(); break;
        case 8: ui->btn_cid->click(); break;
        }
        break;

    case 1://Item Tab
        itemlist->setItems(ff7->items(s));
        ui->sb_gil->setValue(ff7->gil(s));
        ui->sb_gp->setValue(ff7->gp(s));
        ui->sb_runs->setValue(ff7->runs(s));
        ui->sb_battles->setValue(ff7->battles(s));
        ui->cb_mysteryPanties->setChecked(ff7->keyItem(s, FF7Save::MYSTERYPANTIES));
        ui->cb_letterToDaughter->setChecked(ff7->keyItem(s, FF7Save::LETTERTOADAUGHTER));
        ui->cb_letterToWife->setChecked(ff7->keyItem(s, FF7Save::LETTERTOAWIFE));
        break;

    case 2://Materia
        materiaupdate();
        break;

    case 3://Chocobo Tab
        chocoboManager->setData(ff7->chocobos(s), ff7->chocobosNames(s), ff7->chocobosStaminas(s), ff7->chocoboCantMates(s), ff7->stablesOwned(s), ff7->stablesOccupied(s), ff7->stableMask(s), ff7->chocoboPens(s), ff7->chocoboRatings(s));
        break;

    case 4://Location Tab
        on_locationToolBox_currentChanged(ui->locationToolBox->currentIndex());
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
        if ((ff7->format() != FF7SaveInfo::FORMAT::PC && ff7->format() != FF7SaveInfo::FORMAT::SWITCH && ff7->format() != FF7SaveInfo::FORMAT::UNKNOWN)
                || BCSettings::instance()->value(SETTINGS::ALWAYSSHOWCONTROLLERMAP).toBool()) {
            setControllerMappingVisible(true);
            if (optionsWidget->verticalScrollBar()->isVisible()) {
                optionsWidget->setFixedWidth(optionsWidget->width() - 1);
            }
        } else {
            setControllerMappingVisible(false);
        }
        break;

    case 8://HexEditor Tab
        hexTabUpdate(ui->combo_hexEditor->currentIndex());
        break;

    case 9: //Test Data Tab
        on_testDataTabWidget_currentChanged(ui->testDataTabWidget->currentIndex());
        break;
    }
    load = false;
}
void MainWindow::hexTabUpdate(int viewMode)
{
    ui->psxExtras->setVisible(false);
    ui->boxHexData->setVisible(false);
    disconnect(hexEditor, &QHexEdit::dataChanged, this, &MainWindow::hexEditorChanged);
    if (ff7->format() == FF7SaveInfo::FORMAT::PC || ff7->format() == FF7SaveInfo::FORMAT::SWITCH || ff7->format() == FF7SaveInfo::FORMAT::UNKNOWN) {
        hexEditor->setData(ff7->slotFF7Data(s));
    } else {
        ui->psxExtras->setVisible(true);
        update_hexEditor_PSXInfo();
        if (ff7->isFF7(s)) {
            ui->boxHexData->setVisible(true);
            switch (viewMode) {
            case 0:
                hexEditor->setData(ff7->slotPsxRawData(s));
                break;
            case 1:
                hexEditor->setData(ff7->slotFF7Data(s));
                break;
            }
        } else {
            hexEditor->setData(ff7->slotPsxRawData(s));
        }
    }
    hexEditor->setCursorPosition(hexCursorPos);
    connect(hexEditor, &QHexEdit::dataChanged, this, &MainWindow::hexEditorChanged);
}

void MainWindow::setControllerMappingVisible(bool Visible)
{
    optionsWidget->setControllerMappingVisible(Visible);
}
/*~~~~~~~~~~~~~~~~~~~~~GUIREFRESH~~~~~~~~~~~~~~~~~~~~~~*/
void MainWindow::guirefresh(bool newgame)
{
    load = true;
    /*~~~~Check for SG type and ff7~~~~*/
    if ((!ff7->isFF7(s) && !ff7->region(s).isEmpty()) ||
            ((!ff7->isFF7(s)) && (ff7->format() != FF7SaveInfo::FORMAT::PC || ff7->format() != FF7SaveInfo::FORMAT::SWITCH)
             && (ff7->psx_block_type(s) != char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_EMPTY)) && (ff7->psx_block_type(s) != '\x00'))) {
        CheckGame();//Not FF7! Handled By CheckGame()
    } else {
        //IS FF7 Slot
        if (ff7->format() == FF7SaveInfo::FORMAT::PC || ff7->format() == FF7SaveInfo::FORMAT::SWITCH || ff7->format() == FF7SaveInfo::FORMAT::UNKNOWN) {
            if (ui->combo_hexEditor->currentIndex() != 1)
                ui->combo_hexEditor->setCurrentIndex(1);
        }
        //QByteArray text;
        if (ff7->region(s).isEmpty()
                && (ff7->format() == FF7SaveInfo::FORMAT::VMC || ff7->format() == FF7SaveInfo::FORMAT::VGS || ff7->format() == FF7SaveInfo::FORMAT::DEX || ff7->format() == FF7SaveInfo::FORMAT::PSP)
                && ff7->psx_block_type(s) == char(FF7SaveInfo::PSXBLOCKTYPE::BLOCK_EMPTY)) {
            //if empty region string and a virtual memcard format and dir frame says empty.
            ff7->clearSlot(s); //fileModified(false);//checking only
        }
        locationViewer->setRegion(ff7->region(s));
        setmenu(newgame);
        on_tabWidget_currentChanged(ui->tabWidget->currentIndex());
        load = false;
    }
}/*~~~~~~~~~~~~~~~~~~~~End GUIREFRESH ~~~~~~~~~~~~~~~~~*/
void MainWindow::set_char_buttons()
{
    ui->btn_cloud->setIcon(QIcon(FF7Char::instance()->pixmap(ff7->charID(s, 0)).scaled(ui->btn_cloud->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    ui->btn_barret->setIcon(QIcon(FF7Char::instance()->pixmap(ff7->charID(s, 1)).scaled(ui->btn_cloud->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    ui->btn_tifa->setIcon(QIcon(FF7Char::instance()->pixmap(ff7->charID(s, 2)).scaled(ui->btn_cloud->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    ui->btn_aeris->setIcon(QIcon(FF7Char::instance()->pixmap(ff7->charID(s, 3)).scaled(ui->btn_cloud->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    ui->btn_red->setIcon(QIcon(FF7Char::instance()->pixmap(ff7->charID(s, 4)).scaled(ui->btn_cloud->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    ui->btn_yuffie->setIcon(QIcon(FF7Char::instance()->pixmap(ff7->charID(s, 5)).scaled(ui->btn_cloud->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    ui->btn_cait->setIcon(QIcon(FF7Char::instance()->pixmap(ff7->charID(s, 6)).scaled(ui->btn_cloud->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    ui->btn_vincent->setIcon(QIcon(FF7Char::instance()->pixmap(ff7->charID(s, 7)).scaled(ui->btn_cloud->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    ui->btn_cid->setIcon(QIcon(FF7Char::instance()->pixmap(ff7->charID(s, 8)).scaled(ui->btn_cloud->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
}
void MainWindow::progress_update()
{
    load = true;
    ui->sb_curdisc->setValue(ff7->disc(s));
    ui->sb_mprogress->setValue(ff7->mainProgress(s));

    ui->sb_turkschurch->setValue(ff7->churchProgress(s));
    ui->sb_donprog->setValue(ff7->donProgress(s));
    ui->combo_s7_slums->setCurrentIndex(0);

    ui->cb_bm1_1->setChecked(ff7->bmProgress1(s, 0));
    ui->cb_bm1_2->setChecked(ff7->bmProgress1(s, 1));
    ui->cb_bm1_3->setChecked(ff7->bmProgress1(s, 2));
    ui->cb_bm1_4->setChecked(ff7->bmProgress1(s, 3));
    ui->cb_bm1_5->setChecked(ff7->bmProgress1(s, 4));
    ui->cb_bm1_6->setChecked(ff7->bmProgress1(s, 5));
    ui->cb_bm1_7->setChecked(ff7->bmProgress1(s, 6));
    ui->cb_bm1_8->setChecked(ff7->bmProgress1(s, 7));
    ui->cb_bm2_1->setChecked(ff7->bmProgress2(s, 0));
    ui->cb_bm2_2->setChecked(ff7->bmProgress2(s, 1));
    ui->cb_bm2_3->setChecked(ff7->bmProgress2(s, 2));
    ui->cb_bm2_4->setChecked(ff7->bmProgress2(s, 3));
    ui->cb_bm2_5->setChecked(ff7->bmProgress2(s, 4));
    ui->cb_bm2_6->setChecked(ff7->bmProgress2(s, 5));
    ui->cb_bm2_7->setChecked(ff7->bmProgress2(s, 6));
    ui->cb_bm2_8->setChecked(ff7->bmProgress2(s, 7));
    ui->cb_bm3_1->setChecked(ff7->bmProgress3(s, 0));
    ui->cb_bm3_2->setChecked(ff7->bmProgress3(s, 1));
    ui->cb_bm3_3->setChecked(ff7->bmProgress3(s, 2));
    ui->cb_bm3_4->setChecked(ff7->bmProgress3(s, 3));
    ui->cb_bm3_5->setChecked(ff7->bmProgress3(s, 4));
    ui->cb_bm3_6->setChecked(ff7->bmProgress3(s, 5));
    ui->cb_bm3_7->setChecked(ff7->bmProgress3(s, 6));
    ui->cb_bm3_8->setChecked(ff7->bmProgress3(s, 7));
    ui->cb_midgartrain_1->setChecked(ff7->midgarTrainFlags(s, 0));
    ui->cb_midgartrain_2->setChecked(ff7->midgarTrainFlags(s, 1));
    ui->cb_midgartrain_3->setChecked(ff7->midgarTrainFlags(s, 2));
    ui->cb_midgartrain_4->setChecked(ff7->midgarTrainFlags(s, 3));
    ui->cb_midgartrain_5->setChecked(ff7->midgarTrainFlags(s, 4));
    ui->cb_midgartrain_6->setChecked(ff7->midgarTrainFlags(s, 5));
    ui->cb_midgartrain_7->setChecked(ff7->midgarTrainFlags(s, 6));
    ui->cb_midgartrain_8->setChecked(ff7->midgarTrainFlags(s, 7));
    ui->cb_bombing_int->setChecked(ff7->startBombingMission(s));

    ui->cb_s7pl_1->setChecked((ff7->unknown(s, 26).at(0) & (1 << 0)));
    ui->cb_s7pl_2->setChecked((ff7->unknown(s, 26).at(0) & (1 << 1)));
    ui->cb_s7pl_3->setChecked((ff7->unknown(s, 26).at(0) & (1 << 2)));
    ui->cb_s7pl_4->setChecked((ff7->unknown(s, 26).at(0) & (1 << 3)));
    ui->cb_s7pl_5->setChecked((ff7->unknown(s, 26).at(0) & (1 << 4)));
    ui->cb_s7pl_6->setChecked((ff7->unknown(s, 26).at(0) & (1 << 5)));
    ui->cb_s7pl_7->setChecked((ff7->unknown(s, 26).at(0) & (1 << 6)));
    ui->cb_s7pl_8->setChecked((ff7->unknown(s, 26).at(0) & (1 << 7)));

    ui->cb_s7ts_1->setChecked((ff7->unknown(s, 26).at(8) & (1 << 0)));
    ui->cb_s7ts_2->setChecked((ff7->unknown(s, 26).at(8) & (1 << 1)));
    ui->cb_s7ts_3->setChecked((ff7->unknown(s, 26).at(8) & (1 << 2)));
    ui->cb_s7ts_4->setChecked((ff7->unknown(s, 26).at(8) & (1 << 3)));
    ui->cb_s7ts_5->setChecked((ff7->unknown(s, 26).at(8) & (1 << 4)));
    ui->cb_s7ts_6->setChecked((ff7->unknown(s, 26).at(8) & (1 << 5)));
    ui->cb_s7ts_7->setChecked((ff7->unknown(s, 26).at(8) & (1 << 6)));
    ui->cb_s7ts_8->setChecked((ff7->unknown(s, 26).at(8) & (1 << 7)));
    
    if (ff7->unknown(s, 26).mid(0, 6) == "\x00\x00\x00\x00\x00\x00")
        ui->combo_s7_slums->setCurrentIndex(1);
    else if (ff7->unknown(s, 26).mid(0, 6) == "\xFF\x03\x04\x0F\x1F\x6F" || ff7->unknown(s, 26).mid(0, 6) == "\xBF\x51\x05\x17\x5D\xEF")
        ui->combo_s7_slums->setCurrentIndex(2);
    else if (static_cast<unsigned char>(ff7->unknown(s, 26).at(2)) == 0x13)
        ui->combo_s7_slums->setCurrentIndex(3);
    else
        ui->combo_s7_slums->setCurrentIndex(0);
    
    load = false;
}
/*~~~~~~~~~Char Buttons.~~~~~~~~~~~*/
void MainWindow::on_btn_cloud_clicked()
{
    curchar = 0;
    char_editor->setChar(ff7->character(s, 0), ff7->charName(s, 0));
}
void MainWindow::on_btn_barret_clicked()
{
    curchar = 1;
    char_editor->setChar(ff7->character(s, 1), ff7->charName(s, 1));
}
void MainWindow::on_btn_tifa_clicked()
{
    curchar = 2;
    char_editor->setChar(ff7->character(s, 2), ff7->charName(s, 2));
}
void MainWindow::on_btn_aeris_clicked()
{
    curchar = 3;
    char_editor->setChar(ff7->character(s, 3), ff7->charName(s, 3));
}
void MainWindow::on_btn_red_clicked()
{
    curchar = 4;
    char_editor->setChar(ff7->character(s, 4), ff7->charName(s, 4));
}
void MainWindow::on_btn_yuffie_clicked()
{
    curchar = 5;
    char_editor->setChar(ff7->character(s, 5), ff7->charName(s, 5));
}
void MainWindow::on_btn_cait_clicked()
{
    curchar = 6;
    char_editor->setChar(ff7->character(s, 6), ff7->charName(s, 6));
}
void MainWindow::on_btn_vincent_clicked()
{
    curchar = 7;
    char_editor->setChar(ff7->character(s, 7), ff7->charName(s, 7));
}
void MainWindow::on_btn_cid_clicked()
{
    curchar = 8;
    char_editor->setChar(ff7->character(s, 8), ff7->charName(s, 8));
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Party TAB~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void MainWindow::on_combo_party1_currentIndexChanged(int index)
{
    if (!load) {
        if (index == 0x0C) { //empty char slot (index 12)
            ff7->setParty(s, 0, 0xFF);
            //wipe all desc data if noone is there
            ff7->setDescParty(s, 0, ff7->party(s, 0));
            ff7->setDescCurHP(s, 0);
            ff7->setDescMaxHP(s, 0);
            ff7->setDescCurMP(s, 0);
            ff7->setDescMaxMP(s, 0);
            ff7->setDescLevel(s, 0);
            ff7->setDescName(s, QString(QByteArray(16, char(0xFF))));
        } else {
            ff7->setParty(s, 0, index);
            ff7->setDescParty(s, 0, ff7->party(s, 0));
            // IF ID >8 no char slot so for 9, 10, 11 Use slot 6,7,8 char data.
            if (ff7->party(s, 0) == FF7Char::YoungCloud) {
                ff7->setDescCurHP(s, ff7->charCurrentHp(s, 6));
                ff7->setDescMaxHP(s, ff7->charMaxHp(s, 6));
                ff7->setDescCurMP(s, ff7->charCurrentMp(s, 6));
                ff7->setDescMaxMP(s, ff7->charMaxMp(s, 6));
                ff7->setDescLevel(s, ff7->charLevel(s, 6));
                ff7->setDescName(s, ff7->charName(s, 6));
            } else if (ff7->party(s, 0) == FF7Char::Sephiroth) {
                ff7->setDescCurHP(s, ff7->charCurrentHp(s, 7));
                ff7->setDescMaxHP(s, ff7->charMaxHp(s, 7));
                ff7->setDescCurMP(s, ff7->charCurrentMp(s, 7));
                ff7->setDescMaxMP(s, ff7->charMaxMp(s, 7));
                ff7->setDescLevel(s, ff7->charLevel(s, 7));
                ff7->setDescName(s, ff7->charName(s, 7));
            } else if (ff7->party(s, 0) == 11) {
                //chocobo? that never really works.
                ff7->setDescCurHP(s, ff7->charCurrentHp(s, 8));
                ff7->setDescMaxHP(s, ff7->charMaxHp(s, 8));
                ff7->setDescCurMP(s, ff7->charCurrentMp(s, 8));
                ff7->setDescMaxMP(s, ff7->charMaxMp(s, 8));
                ff7->setDescLevel(s, ff7->charLevel(s, 8));
                ff7->setDescName(s, ff7->charName(s, 8));
            } else {
                ff7->setDescCurHP(s, ff7->charCurrentHp(s, ff7->party(s, 0)));
                ff7->setDescMaxHP(s, ff7->charMaxHp(s, ff7->party(s, 0)));
                ff7->setDescCurMP(s, ff7->charCurrentMp(s, ff7->party(s, 0)));
                ff7->setDescMaxMP(s, ff7->charMaxMp(s, ff7->party(s, 0)));
                ff7->setDescLevel(s, ff7->charLevel(s, ff7->party(s, 0)));
                ff7->setDescName(s, ff7->charName(s, ff7->party(s, 0)));
            }
        }
    }
}

void MainWindow::on_combo_party2_currentIndexChanged(int index)
{
    if (!load) {
        if (index == 12)
            ff7->setParty(s, 1, FF7Char::Empty);
        else
            ff7->setParty(s, 1, index);
        //either way set the desc
        ff7->setDescParty(s, 1, ff7->party(s, 1));
    }
}

void MainWindow::on_combo_party3_currentIndexChanged(int index)
{
    if (!load) {
        if (index == 12)
            ff7->setParty(s, 2, FF7Char::Empty);
        else
            ff7->setParty(s, 2, index);
        //either way set the desc
        ff7->setDescParty(s, 2, ff7->party(s, 2));
    }
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~Chocobo Tab~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void MainWindow::cm_stablesOwnedChanged(qint8 owned)
{
    if (!load)
        ff7->setStablesOwned(s, owned);
}
void MainWindow::cm_stableMaskChanged(qint8 mask)
{
    if (!load)
        ff7->setStableMask(s, mask);
}
void MainWindow::cm_stablesOccupiedChanged(qint8 occupied)
{
    if (!load)
        ff7->setStablesOccupied(s, occupied);
}
//set data for stables inside
void MainWindow::cm_nameChanged(int stable, QString text)
{
    if (!load)
        ff7->setChocoName(s, stable, text);
}
void MainWindow::cm_staminaChanged(int stable, quint16 value)
{
    if (!load)
        ff7->setChocoStamina(s, stable, value);
}
void MainWindow::cm_speedChanged(int stable, quint16 value)
{
    if (!load)
        ff7->setChocoSpeed(s, stable, value);
}
void MainWindow::cm_maxspeedChanged(int stable, quint16 value)
{
    if (!load)
        ff7->setChocoMaxSpeed(s, stable, value);
}
void MainWindow::cm_sprintChanged(int stable, quint16 value)
{
    if (!load)
        ff7->setChocoSprintSpeed(s, stable, value);
}
void MainWindow::cm_maxsprintChanged(int stable, quint16 value)
{
    if (!load)
        ff7->setChocoMaxSprintSpeed(s, stable, value);
}
void MainWindow::cm_sexChanged(int stable, quint8 index)
{
    if (!load)
        ff7->setChocoSex(s, stable, index);
}
void MainWindow::cm_typeChanged(int stable, quint8 index)
{
    if (!load)
        ff7->setChocoType(s, stable, index);
}
void MainWindow::cm_coopChanged(int stable, quint8 value)
{
    if (!load)
        ff7->setChocoCoop(s, stable, value);
}
void MainWindow::cm_accelChanged(int stable, quint8 value)
{
    if (!load)
        ff7->setChocoAccel(s, stable, value);
}
void MainWindow::cm_intelChanged(int stable, quint8 value)
{
    if (!load)
        ff7->setChocoIntelligence(s, stable, value);
}
void MainWindow::cm_raceswonChanged(int stable, quint8 value)
{
    if (!load)
        ff7->setChocoRaceswon(s, stable, value);
}
void MainWindow::cm_pcountChanged(int stable, quint8 value)
{
    if (!load)
        ff7->setChocoPCount(s, stable, value);
}
void MainWindow::cm_personalityChanged(int stable, quint8 value)
{
    if (!load)
        ff7->setChocoPersonality(s, stable, value);
}
void MainWindow::cm_mated_toggled(int stable, bool checked)
{
    if (!load)
        ff7->setChocoCantMate(s, stable, checked);
}
void MainWindow::cm_ratingChanged(int stable, quint8 rating)
{
    if (!load)
        ff7->setChocoboRating(s, stable, rating);
}
//set data for pens outside
void MainWindow::cm_pensChanged(int pen, int index)
{
    if (!load)
        ff7->setChocoboPen(s, pen, index);
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~OTHERS TAB~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void MainWindow::on_sb_love_barret_valueChanged(int value)
{
    if (!load)
        ff7->setLove(s, false, FF7Save::LOVE_BARRET, quint8(value));
}
void MainWindow::on_sb_love_aeris_valueChanged(int value)
{
    if (!load)
        ff7->setLove(s, false, FF7Save::LOVE_AERIS, quint8(value));
}
void MainWindow::on_sb_love_tifa_valueChanged(int value)
{
    if (!load)
        ff7->setLove(s, false, FF7Save::LOVE_TIFA, quint8(value));
}
void MainWindow::on_sb_love_yuffie_valueChanged(int value)
{
    if (!load)
        ff7->setLove(s, false, FF7Save::LOVE_YUFFIE, quint8(value));
}

void MainWindow::on_sb_time_hour_valueChanged(int value)
{
    if (!load)
        ff7->setTime(s, quint32((value * 3600) + (ui->sb_time_min->value() * 60) + (ui->sb_time_sec->value())));
}
void MainWindow::on_sb_time_min_valueChanged(int value)
{
    if (!load)
        ff7->setTime(s, quint32((ui->sb_time_hour->value() * 3600) + ((value * 60)) + (ui->sb_time_sec->value())));
}
void MainWindow::on_sb_time_sec_valueChanged(int value)
{
    if (!load)
        ff7->setTime(s, quint32((ui->sb_time_hour->value() * 3600) + (ui->sb_time_min->value() * 60) + (value)));
}

void MainWindow::on_sb_steps_valueChanged(int value)
{
    if (!load)
        ff7->setSteps(s, value);
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Item Tab~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void MainWindow::on_sb_gil_valueChanged(double value)
{
    if (!load)
        ff7->setGil(s, quint32(value));
}
void MainWindow::on_sb_gp_valueChanged(int value)
{
    if (!load)
        ff7->setGp(s, value);
}
void MainWindow::on_sb_battles_valueChanged(int value)
{
    if (!load)
        ff7->setBattles(s, value);
}
void MainWindow::on_sb_runs_valueChanged(int value)
{
    if (!load)
        ff7->setRuns(s, value);
}

void MainWindow::on_cb_mysteryPanties_toggled(bool checked)
{
    if (!load)
        ff7->setKeyItem(s, FF7Save::MYSTERYPANTIES, checked);
}
void MainWindow::on_cb_letterToDaughter_toggled(bool checked)
{
    if (!load)
        ff7->setKeyItem(s, FF7Save::LETTERTOADAUGHTER, checked);
}
void MainWindow::on_cb_letterToWife_toggled(bool checked)
{
    if (!load)
        ff7->setKeyItem(s, FF7Save::LETTERTOAWIFE, checked);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~MATERIA TAB~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void MainWindow::on_tbl_materia_currentCellChanged(int row)
{
    if (!load) {
        load = true;
        materia_editor->setMateria(ff7->partyMateriaId(s, row), ff7->partyMateriaAp(s, row));
        load = false;
    }
}

void MainWindow::on_btn_add_all_materia_clicked()
{
    //place one of each at lowest possible point
    for (int i = 117; i < 142; i++) {
        //Starting With Magic Materia
        if (i < 132)
            ff7->setPartyMateria(s, i, quint8(i - 68), FF7Materia::MaxMateriaAp);
        else if ((i >= 132) && (i < 136))
            ff7->setPartyMateria(s, (i - 1), quint8(i - 68), FF7Materia::MaxMateriaAp);
        else if ((i >= 136) && (i < 142))
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
void MainWindow::locationSelectionChanged(QString fieldName)
{
    if (!load) {
        ff7->setMapId(s, FF7Location::instance()->mapID(fieldName).toUShort());
        ff7->setLocationId(s, FF7Location::instance()->locationID(fieldName).toUShort());
        ff7->setLocationX(s, FF7Location::instance()->x(fieldName).toShort());
        ff7->setLocationY(s, FF7Location::instance()->y(fieldName).toShort());
        ff7->setLocationT(s, FF7Location::instance()->t(fieldName).toUShort());
        ff7->setLocationD(s, quint8(FF7Location::instance()->d(fieldName).toInt()));
        ff7->setLocation(s, FF7Location::instance()->locationString(fieldName));
        statusBar()->showMessage(tr("Set Save Location: %1").arg(fieldName), 750);
    }
}
void MainWindow::map_id_valueChanged(int value)
{
    if (!load)
        ff7->setMapId(s, quint16(value));
}
void MainWindow::loc_id_valueChanged(int value)
{
    if (!load)
        ff7->setLocationId(s, quint16(value));
}
void MainWindow::coord_x_valueChanged(int value)
{
    if (!load)
        ff7->setLocationX(s, qint16(value));
}
void MainWindow::coord_y_valueChanged(int value)
{
    if (!load)
        ff7->setLocationY(s, qint16(value));
}
void MainWindow::coord_t_valueChanged(int value)
{
    if (!load)
        ff7->setLocationT(s, quint16(value));
}
void MainWindow::coord_d_valueChanged(int value)
{
    if (!load)
        ff7->setLocationD(s, quint8(value));
}
void MainWindow::location_textChanged(QString text)
{
    if (!load)
        ff7->setLocation(s, text);
}

/*~~~~~~~~~~~~~~~~~~~ Game Options~~~~~~~~~~~~~~~~~~*/
void MainWindow::setDialogColorUL(QColor color)
{
    if (!load)
        ff7->setDialogColorUL(s, color);
}
void MainWindow::setDialogColorUR(QColor color)
{
    if (!load)
        ff7->setDialogColorUR(s, color);
}
void MainWindow::setDialogColorLL(QColor color)
{
    if (!load)
        ff7->setDialogColorLL(s, color);
}
void MainWindow::setDialogColorLR(QColor color)
{
    if (!load)
        ff7->setDialogColorLR(s, color);
}

void MainWindow::setBattleSpeed(int value)
{
    if (!load)
        ff7->setBattleSpeed(s, value);
}
void MainWindow::setBattleMessageSpeed(int value)
{
    if (!load)
        ff7->setBattleMessageSpeed(s, value);
}
void MainWindow::setFieldMessageSpeed(int value)
{
    if (!load)
        ff7->setMessageSpeed(s, value);
}
void MainWindow::setBattleHelp(bool checked)
{
    if (!load)
        ff7->setBattleHelp(s, checked);
}
void MainWindow::setFieldHelp(bool checked)
{
    if (!load)
        ff7->setFieldHelp(s, checked);
}
void MainWindow::setBattleTargets(bool checked)
{
    if (!load)
        ff7->setBattleTargets(s, checked);
}

void MainWindow::setControlMode(int mode)
{
    if (!load)
        ff7->setControlMode(s, mode);
}
void MainWindow::setSoundMode(int mode)
{
    if (!load)
        ff7->setSoundMode(s, mode);
}
void MainWindow::setCursorMode(int mode)
{
    if (!load)
        ff7->setCursorMode(s, mode);
}
void MainWindow::setAtbMode(int mode)
{
    if (!load)
        ff7->setAtbMode(s, mode);
}
void MainWindow::setCameraMode(int mode)
{
    if (!load)
        ff7->setCameraMode(s, mode);
}
void MainWindow::setMagicOrder(int order)
{
    if (!load)
        ff7->setMagicOrder(s, order);
}

/*--------GAME PROGRESS-------*/
void MainWindow::on_sb_curdisc_valueChanged(int value)
{
    if (!load)
        ff7->setDisc(s, value);
}
void MainWindow::on_sb_mprogress_valueChanged(int value)
{
    if (!load)
        ff7->setMainProgress(s, value);
}
void MainWindow::on_sb_turkschurch_valueChanged(int value)
{
    if (!load)
        ff7->setChurchProgress(s, value);
}
void MainWindow::on_sb_donprog_valueChanged(int value)
{
    if (!load)
        ff7->setDonProgress(s, value);
}
void MainWindow::on_cb_bm1_1_toggled(bool checked)
{
    if (!load)
        ff7->setBmProgress1(s, 0, checked);
}
void MainWindow::on_cb_bm1_2_toggled(bool checked)
{
    if (!load)
        ff7->setBmProgress1(s, 1, checked);
}
void MainWindow::on_cb_bm1_3_toggled(bool checked)
{
    if (!load)
        ff7->setBmProgress1(s, 2, checked);
}
void MainWindow::on_cb_bm1_4_toggled(bool checked)
{
    if (!load)
        ff7->setBmProgress1(s, 3, checked);
}
void MainWindow::on_cb_bm1_5_toggled(bool checked)
{
    if (!load)
        ff7->setBmProgress1(s, 4, checked);
}
void MainWindow::on_cb_bm1_6_toggled(bool checked)
{
    if (!load)
        ff7->setBmProgress1(s, 5, checked);
}
void MainWindow::on_cb_bm1_7_toggled(bool checked)
{
    if (!load)
        ff7->setBmProgress1(s, 6, checked);
}
void MainWindow::on_cb_bm1_8_toggled(bool checked)
{
    if (!load)
        ff7->setBmProgress1(s, 7, checked);
}
void MainWindow::on_cb_bm2_1_toggled(bool checked)
{
    if (!load)
        ff7->setBmProgress2(s, 0, checked);
}
void MainWindow::on_cb_bm2_2_toggled(bool checked)
{
    if (!load)
        ff7->setBmProgress2(s, 1, checked);
}
void MainWindow::on_cb_bm2_3_toggled(bool checked)
{
    if (!load)
        ff7->setBmProgress2(s, 2, checked);
}
void MainWindow::on_cb_bm2_4_toggled(bool checked)
{
    if (!load)
        ff7->setBmProgress2(s, 3, checked);
}
void MainWindow::on_cb_bm2_5_toggled(bool checked)
{
    if (!load)
        ff7->setBmProgress2(s, 4, checked);
}
void MainWindow::on_cb_bm2_6_toggled(bool checked)
{
    if (!load)
        ff7->setBmProgress2(s, 5, checked);
}
void MainWindow::on_cb_bm2_7_toggled(bool checked)
{
    if (!load)
        ff7->setBmProgress2(s, 6, checked);
}
void MainWindow::on_cb_bm2_8_toggled(bool checked)
{
    if (!load)
        ff7->setBmProgress2(s, 7, checked);
}
void MainWindow::on_cb_bm3_1_toggled(bool checked)
{
    if (!load)
        ff7->setBmProgress3(s, 0, checked);
}
void MainWindow::on_cb_bm3_2_toggled(bool checked)
{
    if (!load)
        ff7->setBmProgress3(s, 1, checked);
}
void MainWindow::on_cb_bm3_3_toggled(bool checked)
{
    if (!load)
        ff7->setBmProgress3(s, 2, checked);
}
void MainWindow::on_cb_bm3_4_toggled(bool checked)
{
    if (!load)
        ff7->setBmProgress3(s, 3, checked);
}
void MainWindow::on_cb_bm3_5_toggled(bool checked)
{
    if (!load)
        ff7->setBmProgress3(s, 4, checked);
}
void MainWindow::on_cb_bm3_6_toggled(bool checked)
{
    if (!load)
        ff7->setBmProgress3(s, 5, checked);
}
void MainWindow::on_cb_bm3_7_toggled(bool checked)
{
    if (!load)
        ff7->setBmProgress3(s, 6, checked);
}
void MainWindow::on_cb_bm3_8_toggled(bool checked)
{
    if (!load)
        ff7->setBmProgress3(s, 7, checked);
}

void MainWindow::on_cb_s7pl_1_toggled(bool checked)
{
    if (!load) {
        QByteArray temp = ff7->unknown(s, 26); char t = temp.at(0);
        if (checked)
            t |= (1 << 0);
        else
            t &= ~(1 << 0);
        temp[0] = t;
        ff7->setUnknown(s, 26, temp);
    }
}
void MainWindow::on_cb_s7pl_2_toggled(bool checked)
{
    if (!load) {
        QByteArray temp = ff7->unknown(s, 26); char t = temp.at(0);
        if (checked)
            t |= (1 << 1);
        else
            t &= ~(1 << 1);
        temp[0] = t;
        ff7->setUnknown(s, 26, temp);
    }
}
void MainWindow::on_cb_s7pl_3_toggled(bool checked)
{
    if (!load) {
        QByteArray temp = ff7->unknown(s, 26); char t = temp.at(0);
        if (checked)
            t |= (1 << 2);
        else
            t &= ~(1 << 2);
        temp[0] = t;
        ff7->setUnknown(s, 26, temp);
    }
}
void MainWindow::on_cb_s7pl_4_toggled(bool checked)
{
    if (!load) {
        QByteArray temp = ff7->unknown(s, 26); char t = temp.at(0);
        if (checked)
            t |= (1 << 3);
        else
            t &= ~(1 << 3);
        temp[0] = t;
        ff7->setUnknown(s, 26, temp);
    }
}
void MainWindow::on_cb_s7pl_5_toggled(bool checked)
{
    if (!load) {
        QByteArray temp = ff7->unknown(s, 26); char t = temp.at(0);
        if (checked)
            t |= (1 << 4);
        else
            t &= ~(1 << 4);
        temp[0] = t;
        ff7->setUnknown(s, 26, temp);
    }
}
void MainWindow::on_cb_s7pl_6_toggled(bool checked)
{
    if (!load) {
        QByteArray temp = ff7->unknown(s, 26); char t = temp.at(0);
        if (checked)
            t |= (1 << 5);
        else
            t &= ~(1 << 5);
        temp[0] = t;
        ff7->setUnknown(s, 26, temp);
    }
}
void MainWindow::on_cb_s7pl_7_toggled(bool checked)
{
    if (!load) {
        QByteArray temp = ff7->unknown(s, 26); char t = temp.at(0);
        if (checked)
            t |= (1 << 6);
        else
            t &= ~(1 << 6);
        temp[0] = t;
        ff7->setUnknown(s, 26, temp);
    }
}
void MainWindow::on_cb_s7pl_8_toggled(bool checked)
{
    if (!load) {
        QByteArray temp = ff7->unknown(s, 26); char t = temp.at(0);
        if (checked)
            t |= (1 << 7);
        else
            t &= ~(1 << 7);
        temp[0] = t;
        ff7->setUnknown(s, 26, temp);
    }
}

void MainWindow::on_cb_s7ts_1_toggled(bool checked)
{
    if (!load) {
        QByteArray temp = ff7->unknown(s, 26); char t = temp.at(8);
        if (checked)
            t |= (1 << 0);
        else
            t &= ~(1 << 0);
        temp[8] = t;
        ff7->setUnknown(s, 26, temp);
    }
}

void MainWindow::on_cb_s7ts_2_toggled(bool checked)
{
    if (!load) {
        QByteArray temp = ff7->unknown(s, 26); char t = temp.at(8);
        if (checked)
            t |= (1 << 1);
        else
            t &= ~(1 << 1);
        temp[8] = t;
        ff7->setUnknown(s, 26, temp);
    }
}

void MainWindow::on_cb_s7ts_3_toggled(bool checked)
{
    if (!load) {
        QByteArray temp = ff7->unknown(s, 26); char t = temp.at(8);
        if (checked)
            t |= (1 << 2);
        else
            t &= ~(1 << 2);
        temp[8] = t;
        ff7->setUnknown(s, 26, temp);
    }
}

void MainWindow::on_cb_s7ts_4_toggled(bool checked)
{
    if (!load) {
        QByteArray temp = ff7->unknown(s, 26); char t = temp.at(8);
        if (checked)
            t |= (1 << 3);
        else
            t &= ~(1 << 3);
        temp[8] = t;
        ff7->setUnknown(s, 26, temp);
    }
}

void MainWindow::on_cb_s7ts_5_toggled(bool checked)
{
    if (!load) {
        QByteArray temp = ff7->unknown(s, 26); char t = temp.at(8);
        if (checked)
            t |= (1 << 4);
        else
            t &= ~(1 << 4);
        temp[8] = t;
        ff7->setUnknown(s, 26, temp);
    }
}

void MainWindow::on_cb_s7ts_6_toggled(bool checked)
{
    if (!load) {
        QByteArray temp = ff7->unknown(s, 26); char t = temp.at(8);
        if (checked)
            t |= (1 << 5);
        else
            t &= ~(1 << 5);
        temp[8] = t;
        ff7->setUnknown(s, 26, temp);
    }
}

void MainWindow::on_cb_s7ts_7_toggled(bool checked)
{
    if (!load) {
        QByteArray temp = ff7->unknown(s, 26); char t = temp.at(8);
        if (checked)
            t |= (1 << 6);
        else
            t &= ~(1 << 6);
        temp[8] = t;
        ff7->setUnknown(s, 26, temp);
    }
}

void MainWindow::on_cb_s7ts_8_toggled(bool checked)
{
    if (!load) {
        QByteArray temp = ff7->unknown(s, 26); char t = temp.at(8);
        if (checked)
            t |= (1 << 7);
        else
            t &= ~(1 << 7);
        temp[8] = t;
        ff7->setUnknown(s, 26, temp);
    }
}

void MainWindow::on_cb_bombing_int_stateChanged(int checked)
{
    if (!load)
        ff7->setStartBombingMission(s, checked);
}

void MainWindow::on_cb_replay_currentIndexChanged(int index)
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
void MainWindow::on_btnReplay_clicked()
{
    if (ui->cb_replay->currentIndex() == 1) { // bombing mission
        ui->sb_curdisc->setValue(1);
        ui->sb_mprogress->setValue(1);
        ff7->setBmProgress1(s, 0);
        ff7->setBmProgress2(s, 0);
        ff7->setBmProgress3(s, 0);
        ff7->setMidgarTrainFlags(s, 0);
        ui->cb_bombing_int->setChecked(true);
        ui->combo_s7_slums->setCurrentIndex(1);
        ui->sb_turkschurch->setValue(0); // reset turks.
        locationViewer->setMapId(1);
        locationViewer->setLocationId(116);
        if (!locationViewer->locationChangesSaved()) {
            //toggle saving of locations if they are not being saved by the widget
            locationViewer->setLocationChangesSaved(true);
            locationViewer->setLocationChangesSaved(false);
        }
        statusBar()->showMessage(tr("Progression Reset Complete"), 750);
    } else if (ui->cb_replay->currentIndex() == 2) { // The Church In The Slums
        ui->sb_curdisc->setValue(1);
        ui->sb_mprogress->setValue(130);
        ui->sb_turkschurch->setValue(0);
        ff7->setBmProgress1(s, 120);
        ff7->setBmProgress2(s, 198);
        ff7->setBmProgress3(s, 3);
        ui->cb_bombing_int->setChecked(false);
        locationViewer->setMapId(1);
        locationViewer->setLocationId(183);
        if (!locationViewer->locationChangesSaved()) {
            //toggle saving of locations if they are not being saved by the widget
            locationViewer->setLocationChangesSaved(true);
            locationViewer->setLocationChangesSaved(false);
        }
        ui->combo_party1->setCurrentIndex(0);
        ui->combo_party2->setCurrentIndex(12);
        ui->combo_party3->setCurrentIndex(12);
        statusBar()->showMessage(tr("Progression Reset Complete"), 750);
    } else if (ui->cb_replay->currentIndex() == 3) { // Flash back
        ui->sb_curdisc->setValue(1);
        ui->sb_mprogress->setValue(341);
        ff7->setBmProgress1(s, 120);
        ff7->setBmProgress2(s, 198);
        ff7->setBmProgress3(s, 3);
        ui->cb_bombing_int->setChecked(false);
        locationViewer->setMapId(1);
        locationViewer->setLocationId(332);
        if (!locationViewer->locationChangesSaved()) {
            //toggle saving of locations if they are not being saved by the widget
            locationViewer->setLocationChangesSaved(true);
            locationViewer->setLocationChangesSaved(false);
        }
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
            char_editor->setChar(ff7->character(s, 6), ff7->charName(s, 6));
        else if (curchar == FF7Char::Vincent)
            char_editor->setChar(ff7->character(s, 7), ff7->charName(s, 7));
        statusBar()->showMessage(tr("Progression Reset Complete"), 750);
    }

    else if (ui->cb_replay->currentIndex() == 4) { // The Date Scene
        ui->sb_curdisc->setValue(1);
        ui->sb_mprogress->setValue(583);
        ff7->setBmProgress1(s, 120);
        ff7->setBmProgress2(s, 198);
        ff7->setBmProgress3(s, 3);
        ui->cb_bombing_int->setChecked(false);
        locationViewer->setMapId(1);
        locationViewer->setLocationId(496);
        if (!locationViewer->locationChangesSaved()) {
            //toggle saving of locations if they are not being saved by the widget
            locationViewer->setLocationChangesSaved(true);
            locationViewer->setLocationChangesSaved(false);
        }
        statusBar()->showMessage(tr("Progression Reset Complete"), 750);
    }

    else if (ui->cb_replay->currentIndex() == 5) { //Aeris Death
        ui->sb_curdisc->setValue(1);
        ui->sb_mprogress->setValue(664);
        ff7->setBmProgress1(s, 120);
        ff7->setBmProgress2(s, 198);
        ff7->setBmProgress3(s, 3);
        ui->cb_bombing_int->setChecked(false);
        locationViewer->setMapId(1);
        locationViewer->setLocationId(646);
        if (!locationViewer->locationChangesSaved()) {
            //toggle saving of locations if they are not being saved by the widget
            locationViewer->setLocationChangesSaved(true);
            locationViewer->setLocationChangesSaved(false);
        }
        phsList->setChecked(FF7Char::Aerith, PhsListWidget::PHSALLOWED, false);
        phsList->setChecked(FF7Char::Aerith, PhsListWidget::PHSVISIBLE, false);
        statusBar()->showMessage(tr("Progression Reset Complete"), 750);
    }
    ui->cb_replay->setCurrentIndex(0);
    if (!load)
        progress_update();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~FUNCTIONS FOR TESTING~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void MainWindow::on_btn_remove_all_items_clicked()
{
    for (int i = 0; i < 320; i++)
        ff7->setItem(s, i, FF7Item::EmptyItemData);
    itemlist->setItems(ff7->items(s));
}

void MainWindow::on_btn_remove_all_materia_clicked()
{
    for (int i = 0; i < 200; i++)
        ff7->setPartyMateria(s, i, FF7Materia::EmptyId, FF7Materia::MaxMateriaAp);
    materiaupdate();
}

void MainWindow::on_btn_remove_all_stolen_clicked()
{
    for (int i = 0; i < 48; i++)
        ff7->setStolenMateria(s, i, FF7Materia::EmptyId, FF7Materia::MaxMateriaAp);
    guirefresh(0);
}

void MainWindow::on_sb_b_love_aeris_valueChanged(int value)
{
    if (!load)
        ff7->setLove(s, true, FF7Save::LOVE_AERIS, quint8(value));
}
void MainWindow::on_sb_b_love_tifa_valueChanged(int value)
{
    if (!load)
        ff7->setLove(s, true, FF7Save::LOVE_TIFA, quint8(value));
}
void MainWindow::on_sb_b_love_yuffie_valueChanged(int value)
{
    if (!load)
        ff7->setLove(s, true, FF7Save::LOVE_YUFFIE, quint8(value));
}
void MainWindow::on_sb_b_love_barret_valueChanged(int value)
{
    if (!load)
        ff7->setLove(s, true, FF7Save::LOVE_BARRET, quint8(value));
}
void MainWindow::on_sb_coster_1_valueChanged(int value)
{
    if (!load)
        ff7->setSpeedScore(s, 1, quint16(value));
}
void MainWindow::on_sb_coster_2_valueChanged(int value)
{
    if (!load)
        ff7->setSpeedScore(s, 2, quint16(value));
}
void MainWindow::on_sb_coster_3_valueChanged(int value)
{
    if (!load)
        ff7->setSpeedScore(s, 3, quint16(value));
}
void MainWindow::on_sb_timer_time_hour_valueChanged(int value)
{
    if (!load)
        ff7->setCountdownTimer(s, quint32((value * 3600) + (ui->sb_timer_time_min->value() * 60) + (ui->sb_timer_time_sec->value())));
}
void MainWindow::on_sb_timer_time_min_valueChanged(int value)
{
    if (!load)
        ff7->setCountdownTimer(s, quint32((ui->sb_timer_time_hour->value() * 3600) + ((value * 60)) + (ui->sb_timer_time_sec->value())));
}
void MainWindow::on_sb_timer_time_sec_valueChanged(int value)
{
    if (!load)
        ff7->setCountdownTimer(s, quint32((ui->sb_timer_time_hour->value() * 3600) + (ui->sb_timer_time_min->value() * 60) + (value)));
}
void MainWindow::on_sb_u_weapon_hp_valueChanged(int value)
{
    if (!load)
        ff7->setUWeaponHp(s, value);
}
void MainWindow::on_cb_reg_vinny_toggled(bool checked)
{
    if (!load)
        ff7->setVincentUnlocked(s, checked);
}
void MainWindow::on_cb_reg_yuffie_toggled(bool checked)
{
    if (!load)
        ff7->setYuffieUnlocked(s, checked);
}
void MainWindow::on_cb_yuffieforest_toggled(bool checked)
{
    if (!load)
        ff7->setCanFightNinjaInForest(s, checked);
}

void MainWindow::on_cb_midgartrain_1_toggled(bool checked)
{
    if (!load)
        ff7->setMidgarTrainFlags(s, 0, checked);
}
void MainWindow::on_cb_midgartrain_2_toggled(bool checked)
{
    if (!load)
        ff7->setMidgarTrainFlags(s, 1, checked);
}
void MainWindow::on_cb_midgartrain_3_toggled(bool checked)
{
    if (!load)
        ff7->setMidgarTrainFlags(s, 2, checked);
}
void MainWindow::on_cb_midgartrain_4_toggled(bool checked)
{
    if (!load)
        ff7->setMidgarTrainFlags(s, 3, checked);
}
void MainWindow::on_cb_midgartrain_5_toggled(bool checked)
{
    if (!load)
        ff7->setMidgarTrainFlags(s, 4, checked);
}
void MainWindow::on_cb_midgartrain_6_toggled(bool checked)
{
    if (!load)
        ff7->setMidgarTrainFlags(s, 5, checked);
}
void MainWindow::on_cb_midgartrain_7_toggled(bool checked)
{
    if (!load)
        ff7->setMidgarTrainFlags(s, 6, checked);

}
void MainWindow::on_cb_midgartrain_8_toggled(bool checked)
{
    if (!load)
        ff7->setMidgarTrainFlags(s, 7, checked);
}

void MainWindow::on_cb_tut_worldsave_stateChanged(int value)
{
    if (!load) {
        if (value == 0)
            ff7->setTutSave(s, 0x00);
        else if (value == 1)
            ff7->setTutSave(s, 0x32);
        else if (value == 2)
            ff7->setTutSave(s, 0x3A);
        ui->lcdNumber_7->display(ff7->tutSave(s));
    }
}

void MainWindow::on_cb_Region_Slot_currentIndexChanged(int index)
{
    if (!load) {
        if (ff7->isFF7(s)) {
            ff7->setSaveNumber(s, index);
            guirefresh(0);
        }
    }
}

void MainWindow::on_cb_tut_sub_toggled(bool checked)
{
    if (!load) {
        ff7->setTutSub(s, 2, checked);
        ui->lcdTutSub->display(ff7->tutSub(s));
    }
}

void MainWindow::on_cb_ruby_dead_toggled(bool checked)
{
    if (!load)
        ff7->setKilledRubyWeapon(s, checked);
}
void MainWindow::on_cb_emerald_dead_toggled(bool checked)
{
    if (!load)
        ff7->setKilledEmeraldWeapon(s, checked);
}

void MainWindow::on_combo_highwind_buggy_currentIndexChanged(int index)
{
    if (!load) {
        switch (index) {
        case 0: ui->bh_id->setValue(0x00); ui->cb_visible_buggy->setChecked(false); ui->cb_visible_highwind->setChecked(false); break;
        case 1: ui->bh_id->setValue(0x06); ui->cb_visible_buggy->setChecked(true); break; //buggy
        case 2: ui->bh_id->setValue(0x03); ui->cb_visible_highwind->setChecked(true); break; //highwind
        default: break;
        }
    }
}
void MainWindow::on_cb_visible_buggy_toggled(bool checked)
{
    if (!load) {
        ff7->setWorldVehicle(s, FF7Save::WVEHCILE_BUGGY, checked);
        if (checked) {
            if (ui->cb_visible_highwind->isChecked())
                ui->cb_visible_highwind->setChecked(false);
            load = true;
            ui->combo_highwind_buggy->setCurrentIndex(1);
            ui->bh_id->setValue(0x06);
            load = false;
        } else {
            if (!ui->cb_visible_buggy->isChecked()) {
                load = true;
                ui->combo_highwind_buggy->setCurrentIndex(0);
                ui->bh_id->setValue(0x00);
                load = false;
            }
        }

    }
}
void MainWindow::on_cb_visible_bronco_toggled(bool checked)
{
    if (!load)
        ff7->setWorldVehicle(s, FF7Save::WVEHCILE_TBRONCO, checked);
}
void MainWindow::on_cb_visible_highwind_toggled(bool checked)
{
    if (!load) {
        ff7->setWorldVehicle(s, FF7Save::WVEHCILE_HIGHWIND, checked);
        if (checked) {
            if (ui->cb_visible_buggy->isChecked()) {
                ui->cb_visible_buggy->setChecked(false);
            }
            load = true;
            ui->combo_highwind_buggy->setCurrentIndex(2);
            ui->bh_id->setValue(0x03);
            load = false;
        } else {
            if (!ui->cb_visible_highwind->isChecked()) {
                load = true;
                ui->combo_highwind_buggy->setCurrentIndex(0);
                ui->bh_id->setValue(0x00);
                load = false;
            }
        }
    }
}
void MainWindow::on_cb_visible_wild_chocobo_toggled(bool checked)
{
    if (!load)
        ff7->setWorldChocobo(s, FF7Save::WCHOCO_WILD, checked);

    if (!checked) {
        ui->cb_visible_yellow_chocobo->setChecked(false);
        ui->cb_visible_green_chocobo->setChecked(false);
        ui->cb_visible_blue_chocobo->setChecked(false);
        ui->cb_visible_black_chocobo->setChecked(false);
        ui->cb_visible_gold_chocobo->setChecked(false);
    }
    ui->cb_visible_yellow_chocobo->setEnabled(checked);
    ui->cb_visible_green_chocobo->setEnabled(checked);
    ui->cb_visible_blue_chocobo->setEnabled(checked);
    ui->cb_visible_black_chocobo->setEnabled(checked);
    ui->cb_visible_gold_chocobo->setEnabled(checked);

}
void MainWindow::on_cb_visible_yellow_chocobo_toggled(bool checked)
{
    if (!load) {
        ff7->setWorldChocobo(s, FF7Save::WCHOCO_YELLOW, checked);
        if (checked) {
            ui->cb_visible_green_chocobo->setChecked(false);
            ui->cb_visible_blue_chocobo->setChecked(false);
            ui->cb_visible_black_chocobo->setChecked(false);
            ui->cb_visible_gold_chocobo->setChecked(false);
        }
    }
}
void MainWindow::on_cb_visible_green_chocobo_toggled(bool checked)
{
    if (!load) {
        ff7->setWorldChocobo(s, FF7Save::WCHOCO_GREEN, checked);
        if (checked) {
            ui->cb_visible_yellow_chocobo->setChecked(false);
            ui->cb_visible_blue_chocobo->setChecked(false);
            ui->cb_visible_black_chocobo->setChecked(false);
            ui->cb_visible_gold_chocobo->setChecked(false);
        }
    }
}
void MainWindow::on_cb_visible_blue_chocobo_toggled(bool checked)
{
    if (!load) {
        ff7->setWorldChocobo(s, FF7Save::WCHOCO_BLUE, checked);
        if (checked) {
            ui->cb_visible_yellow_chocobo->setChecked(false);
            ui->cb_visible_green_chocobo->setChecked(false);
            ui->cb_visible_black_chocobo->setChecked(false);
            ui->cb_visible_gold_chocobo->setChecked(false);
        }
    }
}

void MainWindow::on_cb_visible_black_chocobo_toggled(bool checked)
{
    if (!load) {
        ff7->setWorldChocobo(s, FF7Save::WCHOCO_BLACK, checked);
        if (checked) {
            ui->cb_visible_yellow_chocobo->setChecked(false);
            ui->cb_visible_green_chocobo->setChecked(false);
            ui->cb_visible_blue_chocobo->setChecked(false);
            ui->cb_visible_gold_chocobo->setChecked(false);
        }
    }
}

void MainWindow::on_cb_visible_gold_chocobo_toggled(bool checked)
{
    if (!load) {
        ff7->setWorldChocobo(s, FF7Save::WCHOCO_GOLD, checked);
        if (checked) {
            ui->cb_visible_yellow_chocobo->setChecked(false);
            ui->cb_visible_green_chocobo->setChecked(false);
            ui->cb_visible_blue_chocobo->setChecked(false);
            ui->cb_visible_black_chocobo->setChecked(false);
        }
    }
}
// Leader's world map stuff. 0
void MainWindow::on_leader_id_valueChanged(int value)
{
    if (!load)
        ff7->setWorldCoordsLeaderID(s, value);
}
void MainWindow::on_leader_angle_valueChanged(int value)
{
    if (!load)
        ff7->setWorldCoordsLeaderAngle(s, value);
}
void MainWindow::on_leader_z_valueChanged(int value)
{
    if (!load)
        ff7->setWorldCoordsLeaderZ(s, value);
}
void MainWindow::on_leader_x_valueChanged(int value)
{
    if (!load) {
        ff7->setWorldCoordsLeaderX(s, value);
        if (ui->combo_map_controls->currentIndex() == 0) {
            load = true;
            ui->slide_world_x->setValue(value);
            load = false;
        }
    }
}

void MainWindow::on_leader_y_valueChanged(int value)
{
    if (!load) {
        ff7->setWorldCoordsLeaderY(s, value);
        if (ui->combo_map_controls->currentIndex() == 0) {
            load = true;
            ui->slide_world_y->setValue(value);
            load = false;
        }
    }
}

//Tiny bronco / chocobo world 1
void MainWindow::on_tc_id_valueChanged(int value)
{
    if (!load)
        ff7->setWorldCoordsTcID(s, value);
}
void MainWindow::on_tc_angle_valueChanged(int value)
{
    if (!load)
        ff7->setWorldCoordsTcAngle(s, value);
}
void MainWindow::on_tc_z_valueChanged(int value)
{
    if (!load)
        ff7->setWorldCoordsTcZ(s, value);
}
void MainWindow::on_tc_x_valueChanged(int value)
{
    if (!load) {
        ff7->setWorldCoordsTcX(s, value);
        if (ui->combo_map_controls->currentIndex() == 1) {
            load = true;
            ui->slide_world_x->setValue(value);
            load = false;
        }
    }
}
void MainWindow::on_tc_y_valueChanged(int value)
{
    if (!load) {
        ff7->setWorldCoordsTcY(s, value);
        if (ui->combo_map_controls->currentIndex() == 1) {
            load = true;
            ui->slide_world_y->setValue(value);
            load = false;
        }
    }
}

//buggy / highwind world 2
void MainWindow::on_bh_id_valueChanged(int value)
{
    if (!load)
        ff7->setWorldCoordsBhID(s, value);
}
void MainWindow::on_bh_angle_valueChanged(int value)
{
    if (!load)
        ff7->setWorldCoordsBhAngle(s, value);
}
void MainWindow::on_bh_z_valueChanged(int value)
{
    if (!load)
        ff7->setWorldCoordsBhZ(s, value);
}
void MainWindow::on_bh_x_valueChanged(int value)
{
    if (!load) {
        ff7->setWorldCoordsBhX(s, value);
        if (ui->combo_map_controls->currentIndex() == 2) {
            load = true;
            ui->slide_world_x->setValue(value);
            load = false;
        }
    }
}
void MainWindow::on_bh_y_valueChanged(int value)
{
    if (!load) {
        ff7->setWorldCoordsBhY(s, value);
        if (ui->combo_map_controls->currentIndex() == 2) {
            load = true;
            ui->slide_world_y->setValue(value);
            load = false;
        }
    }
}
// sub world 3
void MainWindow::on_sub_id_valueChanged(int value)
{
    if (!load)
        ff7->setWorldCoordsSubID(s, value);
}
void MainWindow::on_sub_angle_valueChanged(int value)
{
    if (!load)
        ff7->setWorldCoordsSubAngle(s, value);
}
void MainWindow::on_sub_z_valueChanged(int value)
{
    if (!load)
        ff7->setWorldCoordsSubZ(s, value);
}
void MainWindow::on_sub_x_valueChanged(int value)
{
    if (!load) {
        ff7->setWorldCoordsSubX(s, value);
        if (ui->combo_map_controls->currentIndex() == 3) {
            load = true;
            ui->slide_world_x->setValue(value);
            load = false;
        }
    }
}
void MainWindow::on_sub_y_valueChanged(int value)
{
    if (!load) {
        ff7->setWorldCoordsSubY(s, value);
        if (ui->combo_map_controls->currentIndex() == 3) {
            load = true;
            ui->slide_world_y->setValue(value);
            load = false;
        }
    }
}

//Wild Chocobo 4
void MainWindow::on_wc_id_valueChanged(int value)
{
    if (!load)
        ff7->setWorldCoordsWchocoID(s, value);
}
void MainWindow::on_wc_angle_valueChanged(int value)
{
    if (!load)
        ff7->setWorldCoordsWchocoAngle(s, value);
}
void MainWindow::on_wc_z_valueChanged(int value)
{
    if (!load)
        ff7->setWorldCoordsWchocoZ(s, value);
}
void MainWindow::on_wc_x_valueChanged(int value)
{
    if (!load) {
        ff7->setWorldCoordsWchocoX(s, value);
        if (ui->combo_map_controls->currentIndex() == 4) {
            load = true;
            ui->slide_world_x->setValue(value);
            load = false;
        }
    }
}
void MainWindow::on_wc_y_valueChanged(int value)
{
    if (!load) {
        ff7->setWorldCoordsWchocoY(s, value);
        if (ui->combo_map_controls->currentIndex() == 4) {
            load = true;
            ui->slide_world_y->setValue(value);
            load = false;
        }
    }
}

//Ruby world stuff 5
void MainWindow::on_durw_id_valueChanged(int value)
{
    if (!load)
        ff7->setWorldCoordsDurwID(s, value);
}
void MainWindow::on_durw_angle_valueChanged(int value)
{
    if (!load)
        ff7->setWorldCoordsDurwAngle(s, value);
}
void MainWindow::on_durw_z_valueChanged(int value)
{
    if (!load)
        ff7->setWorldCoordsDurwZ(s, value);
}
void MainWindow::on_durw_x_valueChanged(int value)
{
    if (!load) {
        ff7->setWorldCoordsDurwX(s, value);
        if (ui->combo_map_controls->currentIndex() == 5) {
            load = true;
            ui->slide_world_x->setValue(value);
            load = false;
        }
    }
}
void MainWindow::on_durw_y_valueChanged(int value)
{
    if (!load) {
        ff7->setWorldCoordsDurwY(s, value);
        if (ui->combo_map_controls->currentIndex() == 5) {
            load = true;
            ui->slide_world_y->setValue(value);
            load = false;
        }
    }
}
void MainWindow::on_combo_map_controls_currentIndexChanged(int index)
{
    load = true;
    switch (index) {
    case 0: ui->slide_world_x->setValue(ff7->worldCoordsLeaderX(s)); ui->slide_world_y->setValue(ff7->worldCoordsLeaderY(s));   break;
    case 1: ui->slide_world_x->setValue(ff7->worldCoordsTcX(s));     ui->slide_world_y->setValue(ff7->worldCoordsTcY(s));       break;
    case 2: ui->slide_world_x->setValue(ff7->worldCoordsBhX(s));     ui->slide_world_y->setValue(ff7->worldCoordsBhY(s));       break;
    case 3: ui->slide_world_x->setValue(ff7->worldCoordsSubX(s));    ui->slide_world_y->setValue(ff7->worldCoordsSubY(s));      break;
    case 4: ui->slide_world_x->setValue(ff7->worldCoordsWchocoX(s));  ui->slide_world_y->setValue(ff7->worldCoordsWchocoY(s));   break;
    case 5: ui->slide_world_x->setValue(ff7->worldCoordsDurwX(s));   ui->slide_world_y->setValue(ff7->worldCoordsDurwY(s));     break;
    }
    load = false;
}

void MainWindow::on_slide_world_x_valueChanged(int value)
{
    if (!load) {
        fileModified(true);
        switch (ui->combo_map_controls->currentIndex()) {
        case 0: ui->leader_x->setValue(value);  break;
        case 1: ui->tc_x->setValue(value);      break;
        case 2: ui->bh_x->setValue(value);      break;
        case 3: ui->sub_x->setValue(value);     break;
        case 4: ui->wc_x->setValue(value);      break;
        case 5: ui->durw_x->setValue(value);    break;
        }
    }
}

void MainWindow::on_slide_world_y_valueChanged(int value)
{
    if (!load) {
        fileModified(true);
        switch (ui->combo_map_controls->currentIndex()) {
        case 0: ui->leader_y->setValue(value);  break;
        case 1: ui->tc_y->setValue(value);      break;
        case 2: ui->bh_y->setValue(value);      break;
        case 3: ui->sub_y->setValue(value);     break;
        case 4: ui->wc_y->setValue(value);      break;
        case 5: ui->durw_y->setValue(value);    break;
        }
    }
}

void MainWindow::on_world_map_view_customContextMenuRequested(QPoint pos)
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
    sel = menu.exec(ui->world_map_view->mapToGlobal(pos));
    if (!sel)
        return;

    fileModified(true);
    if (sel->text() == tr("&Place Leader")) {
        ui->leader_x->setValue(pos.x() * (295000 / ui->world_map_view->width()));
        ui->leader_y->setValue(pos.y() * (230000 / ui->world_map_view->height()));
    } else if (sel->text() == tr("Place &Tiny Bronco/Chocobo")) {
        ui->tc_x->setValue(pos.x() * (295000 / ui->world_map_view->width()));
        ui->tc_y->setValue(pos.y() * (230000 / ui->world_map_view->height()));
    } else if (sel->text() == tr("Place &Buggy/Highwind")) {
        ui->bh_x->setValue(pos.x() * (295000 / ui->world_map_view->width()));
        ui->bh_y->setValue(pos.y() * (230000 / ui->world_map_view->height()));
    } else if (sel->text() == tr("Place &Sub")) {
        ui->sub_x->setValue(pos.x() * (295000 / ui->world_map_view->width()));
        ui->sub_y->setValue(pos.y() * (230000 / ui->world_map_view->height()));
    } else if (sel->text() == tr("Place &Wild Chocobo")) {
        ui->wc_x->setValue(pos.x() * (295000 / ui->world_map_view->width()));
        ui->wc_y->setValue(pos.y() * (230000 / ui->world_map_view->height()));
    } else if (sel->text() == tr("Place &Diamond/Ultimate/Ruby Weapon")) {
        ui->durw_x->setValue(pos.x() * (295000 / ui->world_map_view->width()));
        ui->durw_y->setValue(pos.y() * (230000 / ui->world_map_view->height()));
    } else {
        return;
    }
}//End Of Map Context Menu

void MainWindow::on_btn_item_add_each_item_clicked()
{
    ui->btn_remove_all_items->click();
    for (int i = 0; i < 320; i++) {
        //Replaced by new item engine. (Vegeta_Ss4)
        if (FF7Item::instance()->name(i) != tr("DON'T USE")) {
            if (i < 106)
                ff7->setItem(s, i, quint16(i), 127);
            else // after the block of empty items shift up 23 spots.
                ff7->setItem(s, (i - 23), quint16(i), 127);
        } else {
            ff7->setItem(s, i, 0x1FF, 0x7F);   //exclude the test items
        }
        if (i > 296)
            ff7->setItem(s, i, 0x1FF, 0x7F);   //replace the shifted ones w/ empty slots
    }
    itemlist->setItems(ff7->items(s));
    statusBar()->showMessage(tr("All Items Added"), 750);
}

void MainWindow::unknown_refresh(int z)//remember to add/remove case statments in all 3 switches when number of z vars changes.
{
    load = true;

    int rows = 0;
    QTableWidgetItem *newItem;
    QByteArray temp, temp2;
    int s2;

    ui->tbl_unknown->reset();
    ui->tbl_compare_unknown->reset();

    if (z <= ff7->unknown_zmax())
        temp = ff7->unknown(s, z);
    else if (z == ff7->unknown_zmax() + 1)
        temp = ff7->slotFF7Data(s);

    rows = temp.size();

    ui->tbl_unknown->setRowCount(rows);
    if (ui->combo_compare_slot->currentIndex() != 0)
        ui->tbl_compare_unknown->setRowCount(rows);

    for (int i = 0; i < rows; i++) {
        if (ui->combo_z_var->currentText() == "SLOT") {
            QString hex_str = QString("%1").arg(i, 4, 16, QChar('0')).toUpper(); //format ex: 000C
            newItem = new QTableWidgetItem(hex_str, 0);
            ui->tbl_unknown->setItem(i, 0, newItem);
        } else {
            newItem = new QTableWidgetItem(QString::number(i), 0);
            ui->tbl_unknown->setItem(i, 0, newItem);
        }

        quint8 value = quint8(temp.at(i));

        //Write Hex
        newItem = new QTableWidgetItem(QString("%1").arg(value, 2, 16, QChar('0')).toUpper(), 0);
        newItem->setTextAlignment(Qt::AlignHCenter);
        ui->tbl_unknown->setItem(i, 1, newItem);
        //Write Dec
        newItem = new QTableWidgetItem(QString("%1").arg(value, 3, 10, QChar('0')), 0);
        newItem->setTextAlignment(Qt::AlignHCenter);
        ui->tbl_unknown->setItem(i, 2, newItem);
        //Write Bin
        newItem = new QTableWidgetItem(QString("%1").arg(value, 8, 2, QChar('0')), 0);
        newItem->setTextAlignment(Qt::AlignHCenter);
        ui->tbl_unknown->setItem(i, 3, newItem);
        //Write Char
        newItem = new QTableWidgetItem(QString("%1").arg(QChar(value)), 0);
        newItem->setTextAlignment(Qt::AlignHCenter);
        ui->tbl_unknown->setItem(i, 4, newItem);
        //Set Height
        ui->tbl_unknown->setRowHeight(i, fontMetrics().height() + 6);

        if (ui->combo_compare_slot->currentIndex() != 0) {
            //do the same for the compare slot if one has been selected.
            if (ui->combo_z_var->currentText() == "SLOT") {
                newItem = new QTableWidgetItem(QString("%1").arg(i, 4, 16, QChar('0')).toUpper(), 0);
                ui->tbl_compare_unknown->setItem(i, 0, newItem);
            } else {
                newItem = new QTableWidgetItem(QString::number(i), 0);
                newItem->setTextAlignment(Qt::AlignHCenter);
                ui->tbl_compare_unknown->setItem(i, 0, newItem);
            }

            s2 = ui->combo_compare_slot->currentIndex() - 1;
            if (z <= ff7->unknown_zmax())
                temp2 = ff7->unknown(s2, z);
            else if (z == ff7->unknown_zmax() + 1)
                temp2 = ff7->slotFF7Data(s2);
            value = quint8(temp2.at(i));

            //Write Hex
            newItem = new QTableWidgetItem(QString("%1").arg(value, 2, 16, QChar('0')).toUpper(), 0);
            newItem->setTextAlignment(Qt::AlignHCenter);
            ui->tbl_compare_unknown->setItem(i, 1, newItem);
            //Write Dec
            newItem = new QTableWidgetItem(QString("%1").arg(value, 3, 10, QChar('0')), 0);
            newItem->setTextAlignment(Qt::AlignHCenter);
            ui->tbl_compare_unknown->setItem(i, 2, newItem);
            //Write Bin
            newItem = new QTableWidgetItem(QString("%1").arg(value, 8, 2, QChar('0')), 0);
            newItem->setTextAlignment(Qt::AlignHCenter);
            ui->tbl_compare_unknown->setItem(i, 3, newItem);
            //Write Char
            newItem = new QTableWidgetItem(QChar(value), 0);
            newItem->setTextAlignment(Qt::AlignHCenter);
            ui->tbl_compare_unknown->setItem(i, 4, newItem);

            ui->tbl_compare_unknown->setRowHeight(i, fontMetrics().height() +6);
            if (ui->tbl_compare_unknown->item(i, 1)->text() != ui->tbl_unknown->item(i, 1)->text()) {
                for (int c = 0; c < 5; c++) {
                    //color the diffs ;)
                    ui->tbl_compare_unknown->item(i, c)->setBackground(Qt::yellow);
                    ui->tbl_compare_unknown->item(i, c)->setForeground(Qt::red);
                    ui->tbl_unknown->item(i, c)->setBackground(Qt::yellow);
                    ui->tbl_unknown->item(i, c)->setForeground(Qt::red);
                }
            }
        }
    }
    for (int i = 0; i < rows; i++) { //set up the item flags
        ui->tbl_unknown->item(i, 0)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        ui->tbl_unknown->item(i, 1)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
        ui->tbl_unknown->item(i, 2)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
        ui->tbl_unknown->item(i, 3)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
        ui->tbl_unknown->item(i, 4)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);

        if (ui->combo_compare_slot->currentIndex() != 0) {
            ui->tbl_compare_unknown->item(i, 0)->setFlags(Qt::ItemIsEnabled);
            ui->tbl_compare_unknown->item(i, 1)->setFlags(Qt::ItemIsEnabled);
            ui->tbl_compare_unknown->item(i, 2)->setFlags(Qt::ItemIsEnabled);
            ui->tbl_compare_unknown->item(i, 3)->setFlags(Qt::ItemIsEnabled);
            ui->tbl_compare_unknown->item(i, 4)->setFlags(Qt::ItemIsEnabled);
        }
    }
    load = false;
}

void MainWindow::on_combo_z_var_currentIndexChanged(int z)
{
    unknown_refresh(z);
}

void MainWindow::on_combo_compare_slot_currentIndexChanged(int index)
{
    if (index == 0) {
        ui->tbl_compare_unknown->clearContents();
        ui->tbl_compare_unknown->setRowCount(0);
    } else
        unknown_refresh(ui->combo_z_var->currentIndex());
}

void MainWindow::on_tbl_unknown_itemChanged(QTableWidgetItem *item)
{
    if (!load) {
        QByteArray temp;

        int z = ui->combo_z_var->currentIndex();
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
}

void MainWindow::on_combo_s7_slums_currentIndexChanged(int index)
{
    if (!load) {
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
}

void MainWindow::char_materia_changed(materia mat)
{
    if (!load) {} ff7->setCharMateria(s, curchar, mslotsel, mat);
}
void MainWindow::char_accessory_changed(quint8 accessory)
{
    ff7->setCharAccessory(s, curchar, accessory);
}
void MainWindow::char_armor_changed(quint8 armor)
{
    ff7->setCharArmor(s, curchar, armor);
}
void MainWindow::char_baseHp_changed(quint16 hp)
{
    ff7->setCharBaseHp(s, curchar, hp);
}
void MainWindow::char_baseMp_changed(quint16 mp)
{
    ff7->setCharBaseMp(s, curchar, mp);
}
void MainWindow::char_curHp_changed(quint16 hp)
{
    ff7->setCharCurrentHp(s, curchar, hp);
    if (curchar == ff7->party(s, 0))
        ff7->setDescCurHP(s, hp);
}
void MainWindow::char_curMp_changed(quint16 mp)
{
    ff7->setCharCurrentMp(s, curchar, mp);
    if (curchar == ff7->party(s, 0))
        ff7->setDescCurMP(s, mp);
}
void MainWindow::char_id_changed(qint8 id)
{
    ff7->setCharID(s, curchar, id);
    set_char_buttons();
}
void MainWindow::char_level_changed(qint8 level)
{
    ff7->setCharLevel(s, curchar, level);
    if (curchar == ff7->party(s, 0))
        ff7->setDescLevel(s, level);
}
void MainWindow::char_str_changed(quint8 str)
{
    ff7->setCharStr(s, curchar, str);
}
void MainWindow::char_vit_changed(quint8 vit)
{
    ff7->setCharVit(s, curchar, vit);
}
void MainWindow::char_mag_changed(quint8 mag)
{
    ff7->setCharMag(s, curchar, mag);
}
void MainWindow::char_spi_changed(quint8 spi)
{
    ff7->setCharSpi(s, curchar, spi);
}
void MainWindow::char_dex_changed(quint8 dex)
{
    ff7->setCharDex(s, curchar, dex);
}
void MainWindow::char_lck_changed(quint8 lck)
{
    ff7->setCharLck(s, curchar, lck);
}
void MainWindow::char_strBonus_changed(quint8 value)
{
    ff7->setCharStrBonus(s, curchar, value);
}
void MainWindow::char_vitBonus_changed(quint8 value)
{
    ff7->setCharVitBonus(s, curchar, value);
}
void MainWindow::char_magBonus_changed(quint8 value)
{
    ff7->setCharMagBonus(s, curchar, value);
}
void MainWindow::char_spiBonus_changed(quint8 value)
{
    ff7->setCharSpiBonus(s, curchar, value);
}
void MainWindow::char_dexBonus_changed(quint8 value)
{
    ff7->setCharDexBonus(s, curchar, value);
}
void MainWindow::char_lckBonus_changed(quint8 value)
{
    ff7->setCharLckBonus(s, curchar, value);
}
void MainWindow::char_limitLevel_changed(qint8 value)
{
    ff7->setCharLimitLevel(s, curchar, value);
}
void MainWindow::char_limitBar_changed(quint8 value)
{
    ff7->setCharLimitBar(s, curchar, value);
}
void MainWindow::char_weapon_changed(quint8 value)
{
    ff7->setCharWeapon(s, curchar, value);
}
void MainWindow::char_kills_changed(quint16 value)
{
    ff7->setCharKills(s, curchar, value);
}
void MainWindow::char_row_changed(quint8 value)
{
    ff7->setCharFlag(s, curchar, 1, value);
}
void MainWindow::char_levelProgress_changed(quint8 value)
{
    ff7->setCharFlag(s, curchar, 2, value);
}
void MainWindow::char_sadnessfury_changed(quint8 value)
{
    ff7->setCharFlag(s, curchar, 0, value);
}
void MainWindow::char_limits_changed(quint16 value)
{
    ff7->setCharLimits(s, curchar, value);
}
void MainWindow::char_timesused1_changed(quint16 value)
{
    ff7->setCharTimeLimitUsed(s, curchar, 1, value);
}
void MainWindow::char_timeused2_changed(quint16 value)
{
    ff7->setCharTimeLimitUsed(s, curchar, 2, value);
}
void MainWindow::char_timeused3_changed(quint16 value)
{
    ff7->setCharTimeLimitUsed(s, curchar, 3, value);
}
void MainWindow::char_exp_changed(quint32 value)
{
    ff7->setCharCurrentExp(s, curchar, value);
}
void MainWindow::char_expNext_changed(quint32 value)
{
    ff7->setCharNextExp(s, curchar, value);
}
void MainWindow::char_mslot_changed(int slot)
{
    mslotsel = slot;
}

void MainWindow::char_name_changed(QString name)
{
    ff7->setCharName(s, curchar, name);
    if (curchar == ff7->party(s, 0))
        ff7->setDescName(s, name);
}

void MainWindow::char_maxHp_changed(quint16 value)
{
    ff7->setCharMaxHp(s, curchar, value);
    if (curchar == ff7->party(s, 0))
        ff7->setDescMaxHP(s, value);
}
void MainWindow::char_maxMp_changed(quint16 value)
{
    ff7->setCharMaxMp(s, curchar, value);
    if (curchar == ff7->party(s, 0))
        ff7->setDescMaxMP(s, value);
}

void MainWindow::on_btn_maxChar_clicked()
{
    if (ff7->charID(s, curchar) == FF7Char::YoungCloud || ff7->charID(s, curchar) == FF7Char::Sephiroth  ||  _init)
        return;   //no char selected, sephiroth and young cloud.

    int result = QMessageBox::question(this, tr("Black Chocobo"), tr("Do You Want To Also Replace %1's Equipment and Materia?").arg(ff7->charName(s, curchar)), QMessageBox::Yes, QMessageBox::No);
    switch (result) {
    case QMessageBox::Yes: char_editor->MaxEquip(); char_editor->MaxStats(); break;
    case QMessageBox::No: char_editor->MaxStats(); break;
    }
    switch (curchar) {
    case 0: on_btn_cloud_clicked(); break;
    case 1: on_btn_barret_clicked(); break;
    case 2: on_btn_tifa_clicked(); break;
    case 3: on_btn_aeris_clicked(); break;
    case 4: on_btn_red_clicked(); break;
    case 5: on_btn_yuffie_clicked(); break;
    case 6: on_btn_cait_clicked(); break;
    case 7: on_btn_vincent_clicked(); break;
    case 8: on_btn_cid_clicked(); break;
    }

}
void MainWindow::Items_Changed(QList<quint16> items)
{
    ff7->setItems(s, items);
}
void MainWindow::on_sbSnowBegScore_valueChanged(int value)
{
    if (!load)
        ff7->setSnowboardScore(s, 0, quint8(value));
}
void MainWindow::on_sbSnowExpScore_valueChanged(int value)
{
    if (!load)
        ff7->setSnowboardScore(s, 1, quint8(value));
}
void MainWindow::on_sbSnowCrazyScore_valueChanged(int value)
{
    if (!load)
        ff7->setSnowboardScore(s, 2, quint8(value));
}

void MainWindow::on_sbSnowBegMin_valueChanged(int value)
{
    if (!load) {
        QString time = ff7->snowboardTime(s, 0);
        time.replace(0, 2, QString("%1").arg(value, 2, 10, QChar('0')));
        ff7->setSnowboardTime(s, 0, time);
    }
}

void MainWindow::on_sbSnowBegSec_valueChanged(int value)
{
    if (!load) {
        QString time = ff7->snowboardTime(s, 0);
        time.replace(2, 2, QString("%1").arg(value, 2, 10, QChar('0')));
        ff7->setSnowboardTime(s, 0, time);
    }
}

void MainWindow::on_sbSnowBegMsec_valueChanged(int value)
{
    if (!load) {
        QString time = ff7->snowboardTime(s, 0);
        time.replace(4, 3, QString("%1").arg(value, 3, 10, QChar('0')));
        ff7->setSnowboardTime(s, 0, time);
    }
}

void MainWindow::on_sbSnowExpMin_valueChanged(int value)
{
    if (!load) {
        QString time = ff7->snowboardTime(s, 1);
        time.replace(0, 2, QString("%1").arg(value, 2, 10, QChar('0')));
        ff7->setSnowboardTime(s, 1, time);
    }
}

void MainWindow::on_sbSnowExpSec_valueChanged(int value)
{
    if (!load) {
        QString time = ff7->snowboardTime(s, 1);
        time.replace(2, 2, QString("%1").arg(value, 2, 10, QChar('0')));
        ff7->setSnowboardTime(s, 1, time);
    }
}

void MainWindow::on_sbSnowExpMsec_valueChanged(int value)
{
    if (!load) {
        QString time = ff7->snowboardTime(s, 1);
        time.replace(4, 3, QString("%1").arg(value, 3, 10, QChar('0')));
        ff7->setSnowboardTime(s, 1, time);
    }
}

void MainWindow::on_sbSnowCrazyMin_valueChanged(int value)
{
    if (!load) {
        QString time = ff7->snowboardTime(s, 2);
        time.replace(0, 2, QString("%1").arg(value, 2, 10, QChar('0')));
        ff7->setSnowboardTime(s, 2, time);
    }
}

void MainWindow::on_sbSnowCrazySec_valueChanged(int value)
{
    if (!load) {
        QString time = ff7->snowboardTime(s, 2);
        time.replace(2, 2, QString("%1").arg(value, 2, 10, QChar('0')));
        ff7->setSnowboardTime(s, 2, time);
    }
}

void MainWindow::on_sbSnowCrazyMsec_valueChanged(int value)
{
    if (!load) {
        QString time = ff7->snowboardTime(s, 2);
        time.replace(4, 3, QString("%1").arg(value, 3, 10, QChar('0')));
        ff7->setSnowboardTime(s, 2, time);
    }
}
void MainWindow::on_sb_BikeHighScore_valueChanged(int arg1)
{
    if (!load)
        ff7->setBikeHighScore(s, quint16(arg1));
}
void MainWindow::on_sb_BattlePoints_valueChanged(int arg1)
{
    if (!load)
        ff7->setBattlePoints(s, quint16(arg1));
}

void MainWindow::on_combo_hexEditor_currentIndexChanged(int index)
{
    hexTabUpdate(index);
}

void MainWindow::hexEditorChanged(void)
{
    if (ff7->format() == FF7SaveInfo::FORMAT::PC || ff7->format() == FF7SaveInfo::FORMAT::SWITCH) {
        ff7->setSlotFF7Data(s, hexEditor->data());
    } else {
        switch (ui->combo_hexEditor->currentIndex()) {
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

void MainWindow::phsList_box_allowed_toggled(int row, bool checked)
{
    if (!load)
        ff7->setPhsAllowed(s, row, !checked);
}
void MainWindow::phsList_box_visible_toggled(int row, bool checked)
{
    if (!load)
        ff7->setPhsVisible(s, row, checked);
}
void MainWindow::menuList_box_locked_toggled(int row, bool checked)
{
    if (!load)
        ff7->setMenuLocked(s, row, checked);
}
void MainWindow::menuList_box_visible_toggled(int row, bool checked)
{
    if (!load)
        ff7->setMenuVisible(s, row, checked);
}

void MainWindow::on_locationToolBox_currentChanged(int index)
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
        ui->cb_visible_buggy->setChecked(ff7->worldVehicle(s, FF7Save::WVEHCILE_BUGGY));
        ui->cb_visible_bronco->setChecked(ff7->worldVehicle(s, FF7Save::WVEHCILE_TBRONCO));
        ui->cb_visible_highwind->setChecked(ff7->worldVehicle(s, FF7Save::WVEHCILE_HIGHWIND));
        ui->cb_visible_wild_chocobo->setChecked(ff7->worldChocobo(s, FF7Save::WCHOCO_WILD));
        ui->cb_visible_yellow_chocobo->setChecked(ff7->worldChocobo(s, FF7Save::WCHOCO_YELLOW));
        ui->cb_visible_green_chocobo->setChecked(ff7->worldChocobo(s, FF7Save::WCHOCO_GREEN));
        ui->cb_visible_blue_chocobo->setChecked(ff7->worldChocobo(s, FF7Save::WCHOCO_BLUE));
        ui->cb_visible_black_chocobo->setChecked(ff7->worldChocobo(s, FF7Save::WCHOCO_BLACK));
        ui->cb_visible_gold_chocobo->setChecked(ff7->worldChocobo(s, FF7Save::WCHOCO_GOLD));

        switch (ui->combo_map_controls->currentIndex()) {
        case 0: ui->slide_world_x->setValue(ff7->worldCoordsLeaderX(s));
            ui->slide_world_y->setValue(ff7->worldCoordsLeaderY(s));
            break;
        case 1: ui->slide_world_x->setValue(ff7->worldCoordsTcX(s));
            ui->slide_world_y->setValue(ff7->worldCoordsTcY(s));
            break;
        case 2:  ui->slide_world_x->setValue(ff7->worldCoordsBhX(s));
            ui->slide_world_y->setValue(ff7->worldCoordsBhY(s));
            break;
        case 3: ui->slide_world_x->setValue(ff7->worldCoordsSubX(s));
            ui->slide_world_y->setValue(ff7->worldCoordsSubY(s));
            break;
        case 4: ui->slide_world_x->setValue(ff7->worldCoordsWchocoX(s));
            ui->slide_world_y->setValue(ff7->worldCoordsWchocoY(s));
            break;
        case 5: ui->slide_world_x->setValue(ff7->worldCoordsDurwX(s));
            ui->slide_world_y->setValue(ff7->worldCoordsDurwY(s));
            break;
        }
        //WORLD TAB
        ui->leader_x->setValue(ff7->worldCoordsLeaderX(s));
        ui->leader_id->setValue(ff7->worldCoordsLeaderID(s));
        ui->leader_angle->setValue(ff7->worldCoordsLeaderAngle(s));
        ui->leader_y->setValue(ff7->worldCoordsLeaderY(s));
        ui->leader_z->setValue(ff7->worldCoordsLeaderZ(s));

        ui->durw_x->setValue(ff7->worldCoordsDurwX(s));
        ui->durw_id->setValue(ff7->worldCoordsDurwID(s));
        ui->durw_angle->setValue(ff7->worldCoordsDurwAngle(s));
        ui->durw_y->setValue(ff7->worldCoordsDurwY(s));
        ui->durw_z->setValue(ff7->worldCoordsDurwZ(s));

        ui->wc_x->setValue(ff7->worldCoordsWchocoX(s));
        ui->wc_id->setValue(ff7->worldCoordsWchocoID(s));
        ui->wc_angle->setValue(ff7->worldCoordsWchocoAngle(s));
        ui->wc_y->setValue(ff7->worldCoordsWchocoY(s));
        ui->wc_z->setValue(ff7->worldCoordsWchocoZ(s));

        ui->tc_x->setValue(ff7->worldCoordsTcX(s));
        ui->tc_id->setValue(ff7->worldCoordsTcID(s));
        ui->tc_angle->setValue(ff7->worldCoordsTcAngle(s));
        ui->tc_y->setValue(ff7->worldCoordsTcY(s));
        ui->tc_z->setValue(ff7->worldCoordsTcZ(s));

        ui->bh_x->setValue(ff7->worldCoordsBhX(s));
        ui->bh_id->setValue(ff7->worldCoordsBhID(s));

        switch (ui->bh_id->value()) {
        case 0: ui->combo_highwind_buggy->setCurrentIndex(0); break; //empty
        case 6: ui->combo_highwind_buggy->setCurrentIndex(1); break; //buggy
        case 3: ui->combo_highwind_buggy->setCurrentIndex(2); break; //highwind
        default: QMessageBox::information(this, tr("Black Chocobo"), tr("Unknown Id in Buggy/Highwind Location")); break;
        }

        ui->bh_angle->setValue(ff7->worldCoordsBhAngle(s));
        ui->bh_y->setValue(ff7->worldCoordsBhY(s));
        ui->bh_z->setValue(ff7->worldCoordsBhZ(s));

        ui->sub_x->setValue(ff7->worldCoordsSubX(s));
        ui->sub_id->setValue(ff7->worldCoordsSubID(s));
        ui->sub_angle->setValue(ff7->worldCoordsSubAngle(s));
        ui->sub_y->setValue(ff7->worldCoordsSubY(s));
        ui->sub_z->setValue(ff7->worldCoordsSubZ(s));
        break;
    }
    load = false;
}

void MainWindow::on_testDataTabWidget_currentChanged(int index)
{

    switch (index) {
    case 0:
        load = true;
        ui->sb_b_love_aeris->setValue(ff7->love(s, true, FF7Save::LOVE_AERIS));
        ui->sb_b_love_tifa->setValue(ff7->love(s, true, FF7Save::LOVE_TIFA));
        ui->sb_b_love_yuffie->setValue(ff7->love(s, true, FF7Save::LOVE_YUFFIE));
        ui->sb_b_love_barret->setValue(ff7->love(s, true, FF7Save::LOVE_BARRET));
        ui->sb_u_weapon_hp->setValue(int(ff7->uWeaponHp(s)));
        ui->cb_tut_sub->setChecked(ff7->tutSub(s, 2));

        ui->lcdTutSub->display(ff7->tutSub(s));

        if (ff7->tutSave(s) == 0x3A)
            ui->cb_tut_worldsave->setCheckState(Qt::Checked);
        else if (ff7->tutSave(s) == 0x32)
            ui->cb_tut_worldsave->setCheckState(Qt::PartiallyChecked);
        else
            ui->cb_tut_worldsave->setCheckState(Qt::Unchecked);

        ui->lcdNumber_7->display(ff7->tutSave(s));

        ui->cb_reg_yuffie->setChecked(ff7->yuffieUnlocked(s));
        ui->cb_reg_vinny->setChecked(ff7->vincentUnlocked(s));

        ui->sb_saveMapId->setValue(ff7->craterSavePointMapID(s));
        ui->sb_saveX->setValue(ff7->craterSavePointX(s));
        ui->sb_saveY->setValue(ff7->craterSavePointY(s));
        ui->sb_saveZ->setValue(ff7->craterSavePointZ(s));

        ui->lbl_sg_region->setText(ff7->region(s).mid(0, ff7->region(s).lastIndexOf("-") + 1));
        ui->cb_Region_Slot->setCurrentIndex(ff7->region(s).mid(ff7->region(s).lastIndexOf("S") + 1, 2).toInt() - 1);
        if (ff7->format() != FF7SaveInfo::FORMAT::PC && ff7->format() != FF7SaveInfo::FORMAT::SWITCH && ff7->format() != FF7SaveInfo::FORMAT::UNKNOWN) //we Display an icon. for all formats except for pc and switch.
            ui->lbl_slot_icon->setPixmap(SaveIcon(ff7->slotIcon(s)).icon().scaled(ui->lbl_slot_icon->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        load = false;
        break;

    case 1: unknown_refresh(ui->combo_z_var->currentIndex()); break;
    }
}

void MainWindow::on_sbCondorFunds_valueChanged(int arg1)
{
    if (!load)
        ff7->setCondorFunds(s, quint16(arg1));
}
void MainWindow::on_sbCondorWins_valueChanged(int arg1)
{
    if (!load)
        ff7->setCondorWins(s, quint8(arg1));
}
void MainWindow::on_sbCondorLosses_valueChanged(int arg1)
{
    if (!load)
        ff7->setCondorLosses(s, quint8(arg1));
}
void MainWindow::on_cbPandorasBox_toggled(bool checked)
{
    if (!load)
        ff7->setSeenPandorasBox(s, checked);
}
void MainWindow::on_cbSubGameWon_toggled(bool checked)
{
    if (!load)
        ff7->setSubMiniGameVictory(s, checked);
}

void MainWindow::connectFieldItem(quint8 boxID, QList<quint16>Offset, QList<quint8> Bit)
{
    if (boxID == 0) {
        //if box is 0 then new list.
        fieldItemOffset = new QList<fieldItemOffsetList>;
        fieldItemBit = new QList<fieldItemBitList>;
    }
    fieldItemOffset->append(Offset);
    fieldItemBit->append(Bit);
}
void MainWindow::checkFieldItem(int boxID)
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
void MainWindow::fieldItemStateChanged(int boxID, bool checked)
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

void MainWindow::on_sb_saveMapId_valueChanged(int arg1)
{
    if (!load)
        ff7->setCraterSavePointMapID(s, arg1);
}
void MainWindow::on_sb_saveX_valueChanged(int arg1)
{
    if (!load)
        ff7->setCraterSavePointX(s, arg1);
}
void MainWindow::on_sb_saveY_valueChanged(int arg1)
{
    if (!load)
        ff7->setCraterSavePointY(s, arg1);
}
void MainWindow::on_sb_saveZ_valueChanged(int arg1)
{
    if (!load)
        ff7->setCraterSavePointZ(s, arg1);
}

void MainWindow::on_btnSearchFlyers_clicked()
{
    ui->tabWidget->setCurrentIndex(4);
    ui->locationToolBox->setCurrentIndex(0);
    locationViewer->setFilterString(tr("Turtle Paradise"), LocationViewer::ITEM);
}

void MainWindow::on_btnSearchKeyItems_clicked()
{
    ui->tabWidget->setCurrentIndex(4);
    ui->locationToolBox->setCurrentIndex(0);
    locationViewer->setFilterString(tr("KeyItem"), LocationViewer::ITEM);
}

void MainWindow::on_linePsxDesc_textChanged(const QString &arg1)
{
    if (!load) {
        ff7->setPsxDesc(arg1, s);
        update_hexEditor_PSXInfo();
    }
}
void MainWindow::on_cb_FlashbackPiano_toggled(bool checked)
{
    if (!load)
        ff7->setPlayedPianoOnFlashback(s, checked);
}
void MainWindow::setButtonMapping(int controlAction, int newButton)
{
    if (!load)
        ff7->setControllerMapping(s, controlAction, newButton);
}
