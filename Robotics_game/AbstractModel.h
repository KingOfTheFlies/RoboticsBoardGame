#pragma once
#include <string>
#include <list>
#include <map>
#include <chrono>

typedef std::chrono::time_point<std::chrono::system_clock> TimeSpan;

class AbstractObject;

class AbstractEvent {
public:
    virtual void runEvent(std::list<AbstractObject*>& objects, TimeSpan time_span) = 0;
};


class AbstractObject {
public:
    virtual std::pair<TimeSpan, AbstractEvent*> getNearestEvent(std::list<AbstractObject*> objects) = 0;
    virtual void update(TimeSpan time_span) = 0;

    std::string uid;        // TODO: generate uid
    TimeSpan lastUpdated;
};

class AbstractWrapper {
protected:
    void updateObjects(TimeSpan time_span);

    void addEvent(TimeSpan time_span, AbstractEvent &model_event);

    //virtual void checkState() = 0;

public:
    bool next();

public:
    std::list<AbstractObject*> objects;
    std::map<TimeSpan, AbstractEvent*> event_list;
    std::list<std::pair<TimeSpan, AbstractEvent*>> event_l;
    TimeSpan updatedTime;
};