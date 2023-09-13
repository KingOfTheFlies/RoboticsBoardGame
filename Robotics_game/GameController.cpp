#include "GameController.h"

void GameController::Run() {
    Run(std::move(TimeSpan::max()));
}
void GameController::Run(const TimeSpan& max_app_time) {
    while (app_->next()) {
        if (!app_->isEventListEmpty()) {
            continue;
        }
        if (app_->updatedTime > max_app_time) {
            break;
        }
    }
}