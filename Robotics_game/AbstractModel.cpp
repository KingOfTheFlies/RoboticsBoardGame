#include "AbstractModel.h"
void AbstractWrapper::updateObjects(TimeSpan time_span) {
    for (auto obj : objects) {
            obj->update(time_span);
        }
}

void AbstractWrapper::addEvent(TimeSpan time_span, AbstractEvent &model_event) {
    while (event_list.contains(time_span)) {
        ++time_span;                                 // ??? add tick
    }
    event_list.emplace(time_span, model_event);
}

bool AbstractWrapper::next() {
    //checkState();
    TimeSpan near_object_event_time = TimeSpan::max();
    AbstractEvent* model_event = NULL;

    for (auto obj : objects) {
        std::pair<TimeSpan, AbstractEvent*> nr = obj->getNearestEvent(objects);
        if (nr.first < near_object_event_time) {
            near_object_event_time = nr.first;
            model_event = nr.second;
        }
    }

    if (event_list.size() == 0 && model_event == NULL)
        return false;

    if (event_list.size() > 0 && event_list.begin()->first < near_object_event_time) {
        std::map<TimeSpan, AbstractEvent*>::iterator task = event_list.begin();
        updateObjects(task->first);
        updatedTime = task->first;
        event_list.erase(task->first);
        task->second->runEvent(objects, task->first);
    }
    else {
        std::list<AbstractEvent*> model_events;
        for (auto obj : objects) {
            std::pair<TimeSpan, AbstractEvent*> nr = obj->getNearestEvent(objects);
            if (nr.first == near_object_event_time) {
                model_events.push_back(nr.second);
            }
        }
        updateObjects(near_object_event_time);
        updatedTime = near_object_event_time;
        for (auto m_e : model_events) {
            m_e->runEvent(objects, near_object_event_time);
        }
    }
}