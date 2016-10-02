/***************************************************************************
 * This file is part of ArmSTALKER.
 *
 * ArmSTALKER is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ArmSTALKER is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ArmSTALKER. If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#include "LauncherPresenter.h"

LauncherPresenter::LauncherPresenter(LauncherView *launcherView) : launcherView(launcherView), BasePresenter("LauncherPresenter") {

    Logger::debug(TAG, TAG);

    connect(this, &LauncherPresenter::viewChange, this, &LauncherPresenter::onViewChange);
    connect(launcherView, &LauncherView::viewChange, this, &LauncherPresenter::onViewChange);

    emit viewChange(DASHBOARD);
    updateStyle();
}

LauncherPresenter::~LauncherPresenter() {

    Logger::debug(TAG, "~LauncherPresenter");

    delete dashBoardView;
    delete gameSettingsView;
}

void LauncherPresenter::updateStyle() {

    Logger::info(TAG, "updateStyle");

    QFile f(":/qdarkstyle/darkstyle.qss");
    if (f.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream ts(&f);
        qApp->setStyleSheet(ts.readAll());
        f.close();
    } else {
        Logger::fatal(TAG, "updateStyle");
    }
}

void LauncherPresenter::onViewChange(int viewTypeIndex) {

    Logger::info(TAG, "onViewChange") << "viewIndex - " << viewTypeIndex;

    switch (viewTypeIndex) {
        case DASHBOARD:
            if (dashBoardView == nullptr) {
                dashBoardView = new DashboardView();
                launcherView->insertView(DASHBOARD, dashBoardView);
                connect(dashBoardView, &DashboardView::viewChange, this, &LauncherPresenter::onViewChange);
            }
            break;
        case GAME_SETTINGS:
            if(gameSettingsView == nullptr) {
                gameSettingsView = new GameSettingsView();
                launcherView->insertView(GAME_SETTINGS, gameSettingsView);
            }
            break;
        default:
            return;
    }

    launcherView->showView(viewTypeIndex);
}