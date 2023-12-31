#include "MoveEvent.h"

bool MoveEvent::SetPf(PlayersFactory* pf) {
    pf_ptr = pf;
    std::vector<Player>& players = pf->GetPlayers();
    for (Player& p : players) {
        players_q.push(&p);
    }
    return true;
}

bool MoveEvent::IsThereAWinner() {
    return there_is_a_winner;
}

void MoveEvent::runEvent(std::list<AbstractObject*>& objects, TimeSpan time_span) {
    Player* p = players_q.front();
    if (players_q.size() == 1 || p->GetCurPoints() >= MAX_POINTS_VAL) {
        p->PlayerWins();
        there_is_a_winner = true;
        return;
    }
    bool move_ret_value;
    try {
        move_ret_value = p->MakeMove();
    }
    catch (const IpException& e) {
        throw e;
    }
    catch (std::exception& e) {
        IpException::ErrorCode errorCode = IpException::ErrorCode::PlayerMoveError;
        throw IpException(errorCode, "impossible to make move by a player-" + std::to_string(p->GetIndex()));
    }

    if (move_ret_value) {
        for (Player& pl : pf_ptr->GetPlayers()) {
            pl.PrintRobotsStatus();
        }
    }
    else {
        if (p->CheckIfLose()) {
            players_q.pop();
            return;
        }
        p->SkipMove();
        for (Player& pl : pf_ptr->GetPlayers()) {
            pl.PrintRobotsStatus();
        }
    }

    players_q.pop();
    std::queue<Player*> temp_q(players_q);
    while (!temp_q.empty()) {
        Player* pl = temp_q.front();
        if (!pl->CheckIfLose()) {
            pl->ChargeRobots();
        }
        temp_q.pop();
    }
    players_q.push(p);
}