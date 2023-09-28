#include "Player.h"

#include <iostream>

bool Player::CreateRobots() {
	for (int i = 0; i < robots_num_; ++i) {
		robots.push_back(Robot(index_, i, field_));
	}
    return true;
}

int Player::GetIndex() {
    return index_;
}

bool Player::PlayerWins() {
    std::cout << "Player " << index_ << " wins!" << std::endl;
    return true;
}

bool Player::ChargeRobots() {
    for (Robot& r : robots) {
        if (r.GetStatus() == "charging") {
            r.IncBattery();
        }
    }
    return true;
}

int Player::GetCurPoints() {
    return points;
}

bool Player::CheckIfLose() {
    return lose;
}
bool Player::CreateQ() {
    for (Robot& r : robots) {
        robots_queue.push_back(&r);
    }
    return true;
}

bool Player::SkipMove() {
    field_->IncMoves();
    field_->PrintField();
    std::cout << "Player " << index_ << " skipped a move" << std::endl;
    return true;
}

void Player::PrintRobotsStatus() {
    for (Robot& r : robots) {
        std::cout << "Player-" << index_ << "  robot-" << r.GetIndex() << " battery: " << r.GetBattery() << " status: " << r.GetStatus();
        if (r.GetStatus() == "delivering") {
            std::cout << " (to " << r.GetNumOfDelivering() << ')';
        }
        std::cout << std::endl;
    }
    std::cout << "Player-" << index_ << " points: " << points << std::endl;
}

bool Player::MakeMove() {
    if (robots_queue.empty()) {
        std::cout << "Player " << index_ << " lose" << std::endl;
        lose = true;
        return false;
    }
    Robot* r = robots_queue.front();
    if (!r->OnField()) {
        std::vector<std::vector<bool>>& net_to_throw = field_->GetCellsToThrowRobots();
        for (int row = 0; row < field_->GetWidth(); ++row) {         // TODO: not random
            for (int col = 0; col < field_->GetHeight(); ++col) {
                if (net_to_throw[row][col]) {
                    field_->IncMoves();
                    r->ThrowField({ col, row });
                    field_->PrintField();
                    std::cout << "Move: " << std::to_string(index_) + '-' + std::to_string(r->GetIndex()) << " to {" << r->GetCurPos().x << ", " << r->GetCurPos().y << "}\n";
                    robots_queue.erase(robots_queue.begin());
                    robots_queue.push_back(r);
                    return true;
                }
            }
        }
    }

    bool all_blocked = true;
    for (int i = 0; i < robots_queue.size(); ++i) {
        try {
            robots_queue[i]->CalculatePath();
        }
        catch (std::exception& e) {
            IpException::ErrorCode errorCode = IpException::ErrorCode::RobotCalcError;
            throw IpException(errorCode, "impossible to calculate path for robot-" +
                std::to_string(robots_queue[i]->GetIndex()) + "of player-" + std::to_string(index_));
        }
        if (robots_queue[i]->GetStatus() == "dead") {
            robots_queue.erase(robots_queue.begin() + i);
        }
    }
    for (int i = 0; i < robots_queue.size(); ++i) {
        if (!robots_queue[i]->IsBlocked()) {
            all_blocked = false;
            break;
        }
    }
    if (all_blocked) {          // skipping move
        return false;
    }
    int move_status;
    try {
        move_status = r->MakeMove();
    }
    catch (std::exception& e) {
        IpException::ErrorCode errorCode = IpException::ErrorCode::RobotCalcError;
        throw IpException(errorCode, "impossible to make move by robot-" +
            std::to_string(r->GetIndex()) + "of player-" + std::to_string(index_));
    }
    
    if (r->IsPointGranted()) {
        ++points;
    }
    if (move_status == -1) {
        if (r->GetStatus() == "blocked") {
            robots_queue.erase(robots_queue.begin());
            robots_queue.push_back(r);
        } else if (robots_queue.size() >= 2) {
            r->move_missed = true;
            for (int i = 1; i < robots_num_; ++i) {
                if (!robots_queue[i]->move_missed && robots_queue[i]->GetStatus() != "blocked") {
                    std::swap(robots_queue[0], robots_queue[i]);
                    break;
                }
            }
        }
        else if (robots_queue.size() == 1 && r->IsOnChargeSpot()) {
            robots_queue[0]->IncBattery();
            return false;
        }
        else {
            r->move_missed = true;
        }
        return MakeMove();              
    }
    else if (move_status == 0) {
        if (r->GetStatus() == "dead") {
            robots_queue.erase(robots_queue.begin());
        }
        else {
            if (robots_queue.size() >= 2) {
                for (int i = 1; i < robots_queue.size(); ++i) {
                    if (robots_queue[i]->IsOnChargeSpot()) {
                        robots_queue[i]->IncBattery();
                    }
                }
            }
            robots_queue.erase(robots_queue.begin());
            robots_queue.push_back(r);
        }
        
    }
    field_->IncMoves();

    field_->PrintField();
    std::cout << "Move: " << std::to_string(index_) + '-' + std::to_string(r->GetIndex()) << " to {" << r->GetCurPos().x << ", " << r->GetCurPos().y << "}\n";
    
    return true;
}
